#ifndef SEND_TABLE_H
#define SEND_TABLE_H

#include "sdk.h"

class SendTable;
class SendProp;

typedef int (*ArrayLengthSendProxyFn)(const void* pStruct, int objectID);

typedef void* (*SendTableProxyFn)(const SendProp* prop, const void* structBase, const void* data, void* recipients, int objectID);
typedef void (*SendVarProxyFn)(const SendProp* pProp, const void* structBase, const void* data, DVariant* out, int element, int objectID);

class SendProp
{
  public:
	virtual ~SendProp() {};

	RecvProp* matchingRecvProp;

	SendPropType propType;
	int bits;
	float lowValue;
	float highValue;
	int stringBufferSize;
	SendProp* arrayProp;
	ArrayLengthSendProxyFn arrayLengthProxy;
	int elements;
	int elementStride;

	union
	{
		char* excludeDTName;
		char* parentArrayPropName;
	};

	char* varName;
	float highLowMul;

	int flags;

	//TODO: figure this out, there is a high chance this is in wrong place
	long pad;

	SendVarProxyFn proxyFn;
	SendTableProxyFn dataTableProxyFn;
	SendTable* dataTable;
	int offset;
	const void* extraData;
};

class SendTable
{
  public:
//CSS is likely to use vtables in this instance, but we will figure this out later
#if 0
	virtual ~SendTable() {};
#endif
	SendProp* props;
	int nProps;
	char* netTableName;
	void* precalc;
	bool iniialized;
	bool hasBeenWritten;
	bool hasPropsBeenEncodedAgainstCurrentTickCount;
};

#endif
