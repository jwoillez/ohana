#ifndef _LV_DELAY_LINE_H_
#define _LV_DELAY_LINE_H_

#include "DelayLine.hh"
#include "LVOrbSingleton.h"
#include "LVdefinitions.h"

namespace LV
{
	class DelayLine
	{
	public:
		int Connect(LStrHandle delayLineNameHdl);
		int Disconnect(void);
		int LV::DelayLine::SetOpenLoopTarget(double laserPosition, double rate, unsigned long activationTimeLo, unsigned long activationTimeHi);
		int LV::DelayLine::SetManualTarget(double laserPosition, double rate, unsigned long activationTimeLo, unsigned long activationTimeHi);
	private:
		KeckDelayLineModule::DelayLine_var					mDelayLine;
	};
};

#endif //_LV_DELAY_LINE_H_