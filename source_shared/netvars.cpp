#include "netvars.h"
#include <string>
#include <vector>
#include <unordered_map>
#include "recv.h"
#include "../framework/utils/crc32.h"
#include "baseclient.h"

struct NetvarEntry
{
	int offset;
	RecvProp* prop;

	NetvarEntry(int o, RecvProp* p) : offset(o), prop(p) {}
};

static std::unordered_map<unsigned int, std::unordered_map<unsigned int, NetvarEntry> >* crcDatabase = nullptr;

struct NetvarTable
{
	std::string name;
	RecvProp* prop;
	uint32_t offset;
	std::vector<RecvProp*> childProps;
	std::vector<NetvarTable> childTables;
};

static void LoadCRCTable(std::unordered_map<unsigned int, NetvarEntry>* db, RecvTable* recvTable, int offset)
{

	for(int i = 0; i < recvTable->m_nProps; ++i) {
		RecvProp* prop = &recvTable->m_pProps[i];

		if(!prop || isdigit(prop->m_pVarName[0]))
			continue;
		if(strcmp("baseclass", prop->m_pVarName) == 0)
			continue;

		unsigned int tbKey = Crc32(prop->m_pVarName, strlen(prop->m_pVarName));

		if(prop->m_RecvType == DPT_DataTable && prop->m_pDataTable)
			LoadCRCTable(db, prop->m_pDataTable, offset + prop->m_Offset);
		else if (db->find(tbKey) == db->end())
			db->insert(std::make_pair(tbKey, NetvarEntry(offset + prop->m_Offset, prop)));
	}
}

void SourceNetvars::Initialize(CBaseClient* cl)
{
	crcDatabase = new std::unordered_map<unsigned int, std::unordered_map<unsigned int, NetvarEntry>>();

	for(auto clientclass = cl->GetAllClasses();
		clientclass != nullptr;
		clientclass = clientclass->m_pNext) {
		if(clientclass->m_pRecvTable) {
			unsigned int tbKey = Crc32(clientclass->m_pRecvTable->m_pNetTableName, strlen(clientclass->m_pRecvTable->m_pNetTableName));
			if (crcDatabase->find(tbKey) == crcDatabase->end())
				crcDatabase->insert(std::make_pair(tbKey, std::unordered_map<unsigned int, NetvarEntry>()));
			LoadCRCTable(&crcDatabase->at(tbKey), clientclass->m_pRecvTable, 0);
		}
	}
}

int SourceNetvars::GetOffset(uintptr_t k1, uintptr_t k2)
{
	if (!crcDatabase)
		return 0;
	if (crcDatabase->find(k1) != crcDatabase->end())
		if (crcDatabase->at(k1).find(k2) != crcDatabase->at(k1).end())
			return crcDatabase->at(k1).at(k2).offset;
	return 0;
}

void SourceNetvars::HookAll(NetvarHook* hooks, size_t size)
{

	if (!crcDatabase)
		return;

	for (size_t i = 0; i < size; i++) {
		if (crcDatabase->find(hooks[i].table) != crcDatabase->end())
			if (crcDatabase->at(hooks[i].table).find(hooks[i].prop) != crcDatabase->at(hooks[i].table).end()) {
				RecvProp* prop = crcDatabase->at(hooks[i].table).at(hooks[i].prop).prop;
				hooks[i].original = prop->m_ProxyFn;
				prop->m_ProxyFn = hooks[i].hook;
			}
	}
}

void SourceNetvars::UnhookAll(NetvarHook* hooks, size_t size)
{

	if (!crcDatabase)
		return;

	for (size_t i = 0; i < size; i++) {
		if (crcDatabase->find(hooks[i].table) != crcDatabase->end())
			if (crcDatabase->at(hooks[i].table).find(hooks[i].prop) != crcDatabase->at(hooks[i].table).end())
				crcDatabase->at(hooks[i].table).at(hooks[i].prop).prop->m_ProxyFn = hooks[i].original;
	}
}
