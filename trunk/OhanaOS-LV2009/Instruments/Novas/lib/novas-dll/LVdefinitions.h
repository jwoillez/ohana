
#ifndef _LV_DEFINITIONS_H_
#define _LV_DEFINITIONS_H_

#pragma pack(1)

#include <extcode.h>

typedef struct {
	double latitude;
	double longitude;
	double height;
	double temperature;
	double pressure;
} LVon_surface;

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