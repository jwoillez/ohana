#include "LVDelayLine.h"
#include "LVStringUtils.h"
#include "LVconfig.h"

int LV::DelayLine::Connect(LStrHandle delayLineNameHdl)
{
	//Define Delay Line name
	CosNaming::Name delayLineName;
	std::vector<std::string> tokens;
	LV::StringUtils::Tokenize(delayLineNameHdl,tokens,".");
	delayLineName.length(tokens.size());
	for (unsigned int i=0;i<tokens.size();i++)
		delayLineName[i].id = CORBA::string_dup((char*)tokens[i].c_str());

	//Get reference to Delay Line
	try { mDelayLine = KeckDelayLineModule::DelayLine::_narrow(LV::OrbSingleton::NameService()->resolve(delayLineName)); }
	catch(...) { if(omniORB::traceLevel) DbgPrintf("LVDelayLine: cannot connect to Delay Line"); return(ERROR); };

	//No errors !
	return(OK);
};

int LV::DelayLine::Disconnect(void)
{
	return(OK);
};

int LV::DelayLine::SetOpenLoopTarget(double laserPosition, double rate, unsigned long activationTimeLo, unsigned long activationTimeHi)
{
	try 
	{
		KeckDelayLineModule::Target target;
		target.dLaserPosition=laserPosition;
		target.dRate=rate;
		__int64 activationTime = (((__int64)activationTimeHi)*1000000000)+(__int64)activationTimeLo;
		target.iActivationTime=activationTime;
		mDelayLine->SetOpenLoopTarget(target);
	}
	catch(...) { if(omniORB::traceLevel) DbgPrintf("LVDelayLine: cannot set Open Loop Target"); return(ERROR); }
	return(OK);
};

int LV::DelayLine::SetManualTarget(double laserPosition, double rate, unsigned long activationTimeLo, unsigned long activationTimeHi)
{
	try 
	{
		KeckDelayLineModule::Target target;
		target.dLaserPosition=laserPosition;
		target.dRate=rate;
		__int64 activationTime = (((__int64)activationTimeHi)*1000000000)+(__int64)activationTimeLo;
		target.iActivationTime=activationTime;
		mDelayLine->SetManualTarget(target);
	}
	catch(...) { if(omniORB::traceLevel) DbgPrintf("LVDelayLine: cannot set Manual Target"); return(ERROR); }
	return(OK);
};