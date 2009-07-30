#include "LVFringeTracker.h"
#include "LVStringUtils.h"
#include "LVconfig.h"

int LV::FringeTracker::Connect(LStrHandle fringeTrackerNameHdl)
{
	//Define Fringe Tracker name
	CosNaming::Name fringeTrackerName;
	std::vector<std::string> tokens;
	LV::StringUtils::Tokenize(fringeTrackerNameHdl,tokens,".");
	fringeTrackerName.length(tokens.size());
	for (unsigned int i=0;i<tokens.size();i++)
		fringeTrackerName[i].id = CORBA::string_dup((char*)tokens[i].c_str());

	//Get reference to Fringe Tracker
	try { mFringeTracker = FringeTrackerModule::FringeTracker::_narrow(LV::OrbSingleton::NameService()->resolve(fringeTrackerName)); }
	catch(...) { if(omniORB::traceLevel) DbgPrintf("LVFringeTracker: cannot connect to Fringe Tracker"); return(ERROR); };

	//No errors !
	return(OK);
};

int LV::FringeTracker::Disconnect(void)
{
	return(OK);
};

int LV::FringeTracker::ServoAlignRaster(long channel, long goToPeak, double *xOffset, double *yOffset)
{
	CORBA::Double mXOffset;
	CORBA::Double mYOffset;
	try { mFringeTracker->ServoAlignRaster(channel, goToPeak, mXOffset, mYOffset); }
	catch(...) { if(omniORB::traceLevel) DbgPrintf("LVFringeTracker: raster scan Fringe Tracker"); return(ERROR); };
	*xOffset = mXOffset;
	*yOffset = mYOffset;
	return(OK);
};

int LV::FringeTracker::Track(void)
{
	try { mFringeTracker->Track(); }
	catch(...) { if(omniORB::traceLevel) DbgPrintf("LVFringeTracker: cannot track Fringe Tracker"); return(ERROR); };
	return(OK);
};

int LV::FringeTracker::Idle(void)
{
	try { mFringeTracker->Idle(); }
	catch(...) { if(omniORB::traceLevel) DbgPrintf("LVFringeTracker: cannot idle Fringe Tracker"); return(ERROR); };
	return(OK);
};

int LV::FringeTracker::SetCommandOffset(double offset)
{
	try { mFringeTracker->SetCommandOffset(offset); }
	catch(...) { if(omniORB::traceLevel) DbgPrintf("LVFringeTracker: cannot set command offset for Fringe Tracker"); return(ERROR); };
	return(OK);
};

int LV::FringeTracker::CalibrateBright(long seconds)
{
	try { mFringeTracker->CalibrateBright(seconds); }
	catch(...) { if(omniORB::traceLevel) DbgPrintf("LVFringeTracker: cannot calibrate bright for Fringe Tracker"); return(ERROR); };
	return(OK);
};

int LV::FringeTracker::CalibrateRatio(long seconds)
{
	try { mFringeTracker->CalibrateRatio(seconds); }
	catch(...) { if(omniORB::traceLevel) DbgPrintf("LVFringeTracker: cannot calibrate K1 ratio for Fringe Tracker"); return(ERROR); };
	return(OK);
};

int LV::FringeTracker::CalibrateRatio2(long seconds)
{
	try { mFringeTracker->CalibrateRatio2(seconds); }
	catch(...) { if(omniORB::traceLevel) DbgPrintf("LVFringeTracker: cannot calibrate K2 ratio for Fringe Tracker"); return(ERROR); };
	return(OK);
};

int LV::FringeTracker::CalibrateDark(long seconds)
{
	try { mFringeTracker->CalibrateDark(seconds); }
	catch(...) { if(omniORB::traceLevel) DbgPrintf("LVFringeTracker: cannot calibrate dark for Fringe Tracker"); return(ERROR); };
	return(OK);
};