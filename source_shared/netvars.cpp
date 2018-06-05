#include "netvars.h"
#include <string>
#include <vector>
#include <unordered_map>
#include "recv.h"
#include "../framework/utils/crc32.h"
#include "baseclient.h"

static std::unordered_map<unsigned int, std::unordered_map<unsigned int, int> >* crcDatabase = nullptr;

struct NetvarTable
{
	std::string name;
	RecvProp* prop;
	uint32_t offset;
	std::vector<RecvProp*> childProps;
	std::vector<NetvarTable> childTables;
};

static void LoadCRCTable(std::unordered_map<unsigned int, int>* db, RecvTable* recvTable, int offset)
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
			db->insert(std::make_pair(tbKey, offset + prop->m_Offset));
	}
}

void SourceNetvars::Initialize(CBaseClient* cl)
{
	crcDatabase = new std::unordered_map<unsigned int, std::unordered_map<unsigned int, int>>();

	for(auto clientclass = cl->GetAllClasses();
		clientclass != nullptr;
		clientclass = clientclass->m_pNext) {
		if(clientclass->m_pRecvTable) {
			unsigned int tbKey = Crc32(clientclass->m_pRecvTable->m_pNetTableName, strlen(clientclass->m_pRecvTable->m_pNetTableName));
			if (crcDatabase->find(tbKey) == crcDatabase->end())
				crcDatabase->insert(std::make_pair(tbKey, std::unordered_map<unsigned int, int>()));
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
			return crcDatabase->at(k1).at(k2);
	return 0;
}
