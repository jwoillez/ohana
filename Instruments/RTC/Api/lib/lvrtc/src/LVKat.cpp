#include "LVKat.h"
#include "LVStringUtils.h"
#include "LVconfig.h"

long LV::Kat::Connect(LStrHandle katNameHdl)
{
	//Define KAT name
	CosNaming::Name katName;
	std::vector<std::string> tokens;
	LV::StringUtils::Tokenize(katNameHdl,tokens,".");
	katName.length(tokens.size());
	for (unsigned int i=0;i<tokens.size();i++)
		katName[i].id = CORBA::string_dup((char*)tokens[i].c_str());

	//Get reference to KAT
	try { mKat = KatModule::Kat::_narrow(LV::OrbSingleton::NameService()->resolve(katName)); }
	catch(...) { if(omniORB::traceLevel) DbgPrintf("LVKat: cannot connect to KAT"); return(ERROR); };

	//No errors !
	return(OK);
};

long LV::Kat::Disconnect(void)
{
	return(OK);
};

long LV::Kat::Track(void)
{
	try { mKat->Track(); }
	catch(...) { if(omniORB::traceLevel) DbgPrintf("LVKat: cannot track on KAT"); return(ERROR); };
	return(OK);
};

long LV::Kat::Idle(void)
{
	try { mKat->Idle(); }
	catch(...) { if(omniORB::traceLevel) DbgPrintf("LVKat: cannot idle KAT"); return(ERROR); };
	return(OK);
};

long LV::Kat::SetLockTarget(double x, double y)
{
	KatModule::Target_var lockTarget = new KatModule::Target;
	lockTarget->x=x;
	lockTarget->y=y;
	try { mKat->SetLockTarget(lockTarget); }
	catch(...) { if(omniORB::traceLevel) DbgPrintf("LVKat: cannot set Kat Lock Target"); return(ERROR); };
	return(OK);
};