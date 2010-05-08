#ifndef _LV_TTM_H_
#define _LV_TTM_H_

#include "Ttm.hh"
#include "LVOrbSingleton.h"
#include "LVdefinitions.h"

namespace LV
{
	class Ttm
	{
	public:
		long Connect(LStrHandle ttmNameHdl);
		long Set(double NewX, double NewY);
		long Disconnect(void);
	private:
		TtmModule::Ttm_var					mTtm;
	};
};

#endif //_LV_TTM_H_