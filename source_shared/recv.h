#ifndef RECV_H
#define RECV_H

enum SendPropType
{
	DPT_Int = 0,
	DPT_Float,
	DPT_Vector,
	DPT_VectorXY,
	DPT_String,
	DPT_Array,
	DPT_DataTable,
	DPT_Int64,
	DPT_NUMSendPropTypes
};

class DVariant
{
  public:
	union
	{
		float Float;
		long Int;
		char* String;
		void* Data;
		float Vector[3];
		long long Int64;
	};
	SendPropType type;
};

class RecvTable;
class RecvProp;

class CRecvProxyData
{
  public:
	const RecvProp* recvProp; // The property it's receiving.
	DVariant value; // The value given to you to store.
	int element; // Which array element you're getting.
	int objectID; // The object being referred to.
};

//-----------------------------------------------------------------------------
// pStruct = the base structure of the datatable this variable is in (like C_BaseEntity)
// pOut = the variable that this this proxy represents (like C_BaseEntity::someValue).
//
// Convert the network-standard-type value in value into your own format in pStruct/pOut.
//-----------------------------------------------------------------------------
typedef void(*RecvVarProxyFn)(const CRecvProxyData *pData, void *pStruct, void *pOut);

// ------------------------------------------------------------------------ //
// ArrayLengthRecvProxies are optionally used to Get the length of the
// incoming array when it changes.
// ------------------------------------------------------------------------ //
typedef void(*ArrayLengthRecvProxyFn)(void *pStruct, int objectID, int currentArrayLength);

// NOTE: DataTable receive proxies work differently than the other proxies.
// pData points at the object + the recv table's offset.
// pOut should be Set to the location of the object to unpack the data table into.
// If the parent object just contains the child object, the default proxy just does *pOut = pData.
// If the parent object points at the child object, you need to dereference the pointer here.
// NOTE: don't ever return null from a DataTable receive proxy function. Bad things will happen.
typedef void(*DataTableRecvVarProxyFn)(const RecvProp *pProp, void **pOut, void *pData, int objectID);

class RecvProp
{
  public:
	char* varName;
	SendPropType propType;
	int flags;
	int stringBufferSize;
	int insideArray;
	const void* extraData;
	RecvProp* arrayProp;
	ArrayLengthRecvProxyFn arrayLengthProxy;
	RecvVarProxyFn proxyFn;
	DataTableRecvVarProxyFn dataTableProxyFn;
	RecvTable* dataTable;
	int offset;
	int elementStride;
	int elements;
	const char* parentArrayPropName;

	RecvVarProxyFn GetProxyFn() const;
	void SetProxyFn(RecvVarProxyFn fn);
	DataTableRecvVarProxyFn GetDataTableProxyFn() const;
	void SetDataTableProxyFn(DataTableRecvVarProxyFn fn);

};

class RecvTable
{
  public:
	RecvProp* props;
	int nProps;
	void* decoder;
	char* netTableName;
	bool initialized;
	bool inMainList;
};

inline RecvVarProxyFn RecvProp::GetProxyFn() const
{
	return proxyFn;
}

inline void RecvProp::SetProxyFn(RecvVarProxyFn fn)
{
	proxyFn = fn;
}

inline DataTableRecvVarProxyFn RecvProp::GetDataTableProxyFn() const
{
	return dataTableProxyFn;
}

inline void RecvProp::SetDataTableProxyFn(DataTableRecvVarProxyFn fn)
{
	dataTableProxyFn = fn;
}

#endif
