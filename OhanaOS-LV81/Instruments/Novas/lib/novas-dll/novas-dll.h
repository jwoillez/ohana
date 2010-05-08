#ifndef _NOVAS_DLL_H_
#define _NOVAS_DLL_H_

#include "LVdefinitions.h"

#include <windows.h>

#ifdef NOVASDLL_EXPORTS
	#define DLLAPI __declspec(dllexport)
#else
	#define DLLAPI __declspec(dllimport)
#endif

#pragma pack(1)

BOOL APIENTRY DllMain(HANDLE hModule, DWORD  ul_reason_for_call, LPVOID lpReserved);

extern "C" 
{
	void DLLAPI LVapp_star(double LVtjd, LVbody *LVearth, LVcat_entry *LVstar, double *LVra, double *LVdec);
	void DLLAPI LVtopo_star(double LVtjd, LVbody *LVearth, double LVdeltat, LVcat_entry *LVstar, LVsite_info *LVlocation, double *LVra, double *LVdec);
	void DLLAPI LVearthtilt(double LVtjd, double *LVmobl, double *LVtobl, double *LVeq, double *LVdpsi, double *LVdeps);
	void DLLAPI LVsidereal_time(double LVjd_high, double LVjd_low, double LVee, double *LVgst);
	void DLLAPI LVequ2hor(double LVtjd, double LVdeltat, double LVx, double LVy, LVsite_info *LVlocation, double LVra, double LVdec, short int LVref_option, double *LVzd, double *LVaz, double *LVrar, double *LVcr);
}

#pragma pack()

#endif //_NOVAS_DLL_H_