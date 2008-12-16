#ifndef _LV_FRINGE_TRACKER_H_
#define _LV_FRINGE_TRACKER_H_

#include "FringeTracker.hh"
#include "LVOrbSingleton.h"
#include "LVdefinitions.h"

namespace LV
{
	class FringeTracker
	{
	public:
		int Connect(LStrHandle fringeTrackerNameHdl);
		int Disconnect(void);
		int Track(void);
		int Idle(void);
		int SetCommandOffset(double offset);
		int ServoAlignRaster(long channel, long goToPeak, double *xOffset, double *yOffset);
	private:
		FringeTrackerModule::FringeTracker_var		mFringeTracker;
	};
};

#endif //_LV_FRINGE_TRACKER_H_