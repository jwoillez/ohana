#ifndef _LV_KAT_H_
#define _LV_KAT_H_

#include "Kat.hh"
#include "LVOrbSingleton.h"
#include "LVdefinitions.h"

namespace LV
{
	class Kat
	{
	public:
		long Connect(LStrHandle katNameHdl);
		long Disconnect(void);
		long Track(void);
		long Idle(void);
		long SetLockTarget(double x, double y);
	private:
		KatModule::Kat_var					mKat;
	};
};

#endif //_LV_KAT_H_