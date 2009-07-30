
#ifndef _LV_DEFINITIONS_H_
#define _LV_DEFINITIONS_H_

#pragma pack(1)

#include "extcode.h"

typedef struct header {
	unsigned long lId;
	unsigned long lSequenceNumber;
	unsigned long lTimeFirstLo;
	unsigned long lTimeFirstHi;
	unsigned long lTimeLastLo;
	unsigned long lTimeLastHi;
	double dRate;
	} Header;

typedef struct arrayExt {
	long dimSize;
	floatExt elt[1];
	} ArrayExt;
typedef ArrayExt **ArrayExtHdl;

typedef struct arrayDbl {
	long dimSize;
	double elt[1];
	} ArrayDbl;
typedef ArrayDbl **ArrayDblHdl;

typedef struct arrayI16 {
	long dimSize;
	short int elt[1];
	} ArrayI16;
typedef ArrayI16 **ArrayI16Hdl;

typedef struct arrayI32 {
	long dimSize;
	long elt[1];
	} ArrayI32;
typedef ArrayI32 **ArrayI32Hdl;

typedef struct arrayLStr {
	long dimSize;
	LStrHandle elt[1];
	} ArrayLStr;
typedef ArrayLStr **ArrayLStrHdl;

typedef struct lvTelemetryServerPacket {
	Header mHeader;
	ArrayDblHdl mArrayDblHdl;
	ArrayExtHdl mArrayExtHdl;
	ArrayI16Hdl mArrayI16Hdl;
	ArrayI32Hdl mArrayI32Hdl;
	} LVTelemetryServerPacket;

typedef struct errorStruct {
	LVBoolean status;
	long code;
	LStrHandle source;
	} ErrorStruct;

#pragma pack()

#endif