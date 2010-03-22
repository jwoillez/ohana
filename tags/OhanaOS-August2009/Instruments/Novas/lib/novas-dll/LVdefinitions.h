
#ifndef _LV_DEFINITIONS_H_
#define _LV_DEFINITIONS_H_

#pragma pack(1)

#include <extcode.h>

typedef struct {
	char type;
	char number;
	LStrHandle name;
} LVbody;

typedef struct {
	double latitude;
	double longitude;
	double height;
	double temperature;
	double pressure;
} LVsite_info;

typedef struct {
	LStrHandle catalog;
	LStrHandle starname;
	long starnumber;
	double ra;
	double dec;
	double promora;
	double promodec;
	double parallax;
	double radialvelocity;
} LVcat_entry;

#pragma pack()

#endif