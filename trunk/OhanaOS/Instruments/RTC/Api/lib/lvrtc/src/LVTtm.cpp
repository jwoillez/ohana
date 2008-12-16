#include "LVTtm.h"
#include "LVStringUtils.h"
#include "LVconfig.h"

long LV::Ttm::Connect(LStrHandle ttmNameHdl)
{
	//Define TTM name
	CosNaming::Name ttmName;
	std::vector<std::string> tokens;
	LV::StringUtils::Tokenize(ttmNameHdl,tokens,".");
	ttmName.length(tokens.size());
	for (unsigned int i=0;i<tokens.size();i++)
		ttmName[i].id = CORBA::string_dup((char*)tokens[i].c_str());

	//Get reference to TTM
	try { mTtm = TtmModule::Ttm::_narrow(LV::OrbSingleton::NameService()->resolve(ttmName)); }
	catch(...) { if(omniORB::traceLevel) DbgPrintf("LVTtm: cannot connect to TTM"); return(ERROR); };

	//No errors !
	return(OK);
};

long LV::Ttm::Set(double NewX, double NewY)
{
	try { mTtm->SetTtms(NewX,NewY); }
	catch(...) { if(omniORB::traceLevel) DbgPrintf("LVTtm: cannot set TTM"); return(ERROR); };
	return(OK);
};

long LV::Ttm::Disconnect(void)
{
	return(OK);
};
