#ifndef _LVRTC_H_
#define _LVRTC_H_

#include "LVdefinitions.h"

#include <windows.h>

#ifdef LVRTC_EXPORTS
	#define DLLAPI __declspec(dllexport)
#else
	#define DLLAPI __declspec(dllimport)
#endif

#pragma pack(1)

BOOL APIENTRY DllMain(HANDLE hModule, DWORD  ul_reason_for_call, LPVOID lpReserved);

extern "C" 
{
	//ORB methodes
	long DLLAPI Orb_Initialize(short int debug);
	long DLLAPI Orb_Shutdown(void);

	//TelemetryServer methodes
	long DLLAPI TelemetryServer_Connect(LStrHandle channelNameHdl, LStrHandle serverNameHdl, LVUserEventRef* lvUserEventRefPtr, unsigned long *idPtr);
	long DLLAPI TelemetryServer_Disconnect(LStrHandle channelNameHdl);
	long DLLAPI TelemetryServer_ChannelList(LStrHandle serverNameHdl, ArrayLStrHdl channelList);

	//TTM methodes
	long DLLAPI Ttm_Connect   (LStrHandle ttmNameHdl);
	long DLLAPI Ttm_Set       (LStrHandle ttmNameHdl, double NewX, double NewY);
	long DLLAPI Ttm_Disconnect(LStrHandle ttmNameHdl);

	//KAT methodes
	long DLLAPI Kat_Connect			(LStrHandle katNameHdl);
	long DLLAPI Kat_Disconnect		(LStrHandle katNameHdl);
	long DLLAPI Kat_Track			(LStrHandle katNameHdl);
	long DLLAPI Kat_Idle			(LStrHandle katNameHdl);
	long DLLAPI Kat_SetLockTarget	(LStrHandle katNameHdl, double x, double y);

	//FringeTracker methodes
	long DLLAPI FringeTracker_Connect          (LStrHandle fringeTrackerNameHdl);
	long DLLAPI FringeTracker_Disconnect       (LStrHandle fringeTrackerNameHdl);
	long DLLAPI FringeTracker_Track            (LStrHandle fringeTrackerNameHdl);
	long DLLAPI FringeTracker_Idle             (LStrHandle fringeTrackerNameHdl);
	long DLLAPI FringeTracker_SetCommandOffset (LStrHandle fringeTrackerNameHdl, double offset);
	long DLLAPI FringeTracker_ServoAlignRaster (LStrHandle fringeTrackerNameHdl, long channel, long goToPeak, double *xOffset, double *yOffset);

	//DelayLine methodes
	long DLLAPI DelayLine_Connect			(LStrHandle delayLineNameHdl);
	long DLLAPI DelayLine_Disconnect		(LStrHandle delayLineNameHdl);
	long DLLAPI DelayLine_SetOpenLoopTarget	(LStrHandle delayLineNameHdl, double laserPosition, double rate, unsigned long activationTimeLo, unsigned long activationTimeHi);
	long DLLAPI DelayLine_SetManualTarget	(LStrHandle delayLineNameHdl, double laserPosition, double rate, unsigned long activationTimeLo, unsigned long activationTimeHi);

}

#pragma pack()

#endif //_LVRTC_H_