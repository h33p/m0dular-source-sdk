#include "netvars.h"
#include <string>
#include <vector>
#include <unordered_map>
#include "recv.h"
#include "send_table.h"
#include "../framework/utils/crc32.h"
#include "baseclient.h"

#ifdef NETVAR_DUMP
FILE* nfp = nullptr;
#endif

template<typename PROP_TYPE>
struct NetvarEntry
{
	int offset;
	PROP_TYPE* prop;

	NetvarEntry(int o, PROP_TYPE* p) : offset(o), prop(p) {}
};

//TODO: This may actually leak
static std::unordered_map<unsigned int, std::unordered_map<unsigned int, NetvarEntry<RecvProp>> >* crcDatabase = nullptr;
static std::unordered_map<unsigned int, std::unordered_map<unsigned int, NetvarEntry<SendProp>> >* crcDatabaseServer = nullptr;

template<typename PROP_TYPE>
struct NetvarTable
{
	std::string name;
	PROP_TYPE* prop;
	uint32_t offset;
	std::vector<PROP_TYPE*> childProps;
	std::vector<NetvarTable> childTables;
};

template<typename PROP_TYPE, typename TABLE_TYPE>
static void LoadCRCTable(std::unordered_map<unsigned int, NetvarEntry<PROP_TYPE>>* db, TABLE_TYPE* recvTable, int offset)
{

	for(int i = 0; i < recvTable->nProps; i++) {
	    PROP_TYPE* prop = &recvTable->props[i];

		if(!prop || isdigit(prop->varName[0]))
			continue;
		if(strcmp("baseclass", prop->varName) == 0)
			continue;

		unsigned int tbKey = Crc32(prop->varName, strlen(prop->varName));

		if(prop->propType == DPT_DataTable && prop->dataTable)
			LoadCRCTable(db, prop->dataTable, offset + prop->offset);
		else if (db->find(tbKey) == db->end()) {
#ifdef NETVAR_DUMP
			fprintf(nfp, "\t%s\t[%x]\n", prop->varName, offset + prop->offset);
#endif
			db->insert(std::make_pair(tbKey, NetvarEntry(offset + prop->offset, prop)));
		}
	}
}

void SourceNetvars::Initialize(CBaseClient* cl)
{
	crcDatabase = new std::unordered_map<unsigned int, std::unordered_map<unsigned int, NetvarEntry<RecvProp>>>();

#ifdef NETVAR_DUMP
	nfp = fopen(PosixWin("/tmp/netvars.txt", "C:\\Temp\\netvars.txt"), "w");
#endif

	for(auto clientclass = cl->GetAllClasses();
		clientclass != nullptr;
		clientclass = clientclass->next) {
		if(clientclass->recvTable) {

#ifdef NETVAR_DUMP
			fprintf(nfp, "%s:\n", clientclass->recvTable->netTableName);
#endif

			unsigned int tbKey = Crc32(clientclass->recvTable->netTableName, strlen(clientclass->recvTable->netTableName));
			if (crcDatabase->find(tbKey) == crcDatabase->end())
				crcDatabase->insert(std::make_pair(tbKey, std::unordered_map<unsigned int, NetvarEntry<RecvProp>>()));
			LoadCRCTable(&crcDatabase->at(tbKey), clientclass->recvTable, 0);
		}
	}

#ifdef NETVAR_DUMP
	fclose(nfp);
#endif
}

void SourceNetvars::InitializeServer(CServerGame* server)
{
	crcDatabaseServer = new std::unordered_map<unsigned int, std::unordered_map<unsigned int, NetvarEntry<SendProp>>>();

#ifdef NETVAR_DUMP
	nfp = fopen(PosixWin("/tmp/netvars_server.txt", "C:\\Temp\\netvars_server.txt"), "w");
#endif

	for(auto serverclass = server->GetAllServerClasses();
	    serverclass != nullptr;
	    serverclass = serverclass->next) {
		if(serverclass->sendTable) {

#ifdef NETVAR_DUMP
			fprintf(nfp, "%s:\n", serverclass->sendTable->netTableName);
#endif

			unsigned int tbKey = Crc32(serverclass->sendTable->netTableName, strlen(serverclass->sendTable->netTableName));
			if (crcDatabaseServer->find(tbKey) == crcDatabaseServer->end())
				crcDatabaseServer->insert(std::make_pair(tbKey, std::unordered_map<unsigned int, NetvarEntry<SendProp>>()));
			LoadCRCTable(&crcDatabaseServer->at(tbKey), serverclass->sendTable, 0);
		}
	}

#ifdef NETVAR_DUMP
	fclose(nfp);
#endif
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

int SourceNetvars::GetOffsetServer(uintptr_t k1, uintptr_t k2)
{
	if (!crcDatabaseServer)
		return 0;
	if (crcDatabaseServer->find(k1) != crcDatabaseServer->end())
		if (crcDatabaseServer->at(k1).find(k2) != crcDatabaseServer->at(k1).end())
			return crcDatabaseServer->at(k1).at(k2).offset;
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
				hooks[i].original = prop->proxyFn;
				prop->proxyFn = hooks[i].hook;
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
				crcDatabase->at(hooks[i].table).at(hooks[i].prop).prop->proxyFn = hooks[i].original;
	}
}
