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
	void DLLAPI LVtopo_star(const double LVjd_tt, const double LVdelta_t, const LVcat_entry *LVstar, const LVon_surface *LVposition, const short int LVaccuracy, double *LVra, double *LVdec);
	void DLLAPI LVequ2hor(const double LVjd_ut1, const double LVdelta_t, const short int LVaccuracy, const double LVx, const double LVy, LVon_surface *LVlocation, const double LVra, const double LVdec, const short int LVref_option, double *LVzd, double *LVaz, double *LVrar, double *LVdecr);
}

#pragma pack()

#endif //_NOVAS_DLL_H_