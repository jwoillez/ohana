#include "LVOrbSingleton.h"
#include "LVdefinitions.h"
#include "LVconfig.h"
#include "windows.h"

bool							LV::OrbSingleton::msInitialized=false;
CORBA::ORB_var					LV::OrbSingleton::msOrb;
PortableServer::POA_var			LV::OrbSingleton::msRootPOA;
PortableServer::POAManager_var	LV::OrbSingleton::msPOAManager;
CosNaming::NamingContext_var	LV::OrbSingleton::msNameService;
HANDLE							LV::OrbSingleton::mshOrbThread=NULL;


long WINAPI LV::OrbSingleton::run()
{
	msOrb->run();
	return true;
};

long LV::OrbSingleton::Initialize(int argc, char* argv[])
{
	if(omniORB::traceLevel) DbgPrintf("---------------> Initializing the ORB");
	try {
		msOrb = CORBA::ORB_init(argc,argv);
		msInitialized = true;
		msRootPOA = resolve_initial_references<PortableServer::POA>("RootPOA");
		msPOAManager = msRootPOA->the_POAManager();
		msPOAManager->activate();
		msNameService = resolve_initial_references<CosNaming::NamingContext>("NameService");
		mshOrbThread = CreateThread(NULL,0,(LPTHREAD_START_ROUTINE)run,NULL,0,NULL);
	}
	catch(...) { return(ERROR); };
	return(OK);
};

long LV::OrbSingleton::Shutdown()
{
	try
	{
		DWORD ExitCode;
		if(omniORB::traceLevel) DbgPrintf("---------------> Shutting down the ORB");
		msOrb->shutdown(1);
		msOrb->destroy();
		msInitialized = false;
		GetExitCodeThread(mshOrbThread,&ExitCode);
		if((ExitCode == STILL_ACTIVE) && (omniORB::traceLevel))  DbgPrintf("---------------> ORB thread looks still active");
	}
	catch(...) { DbgPrintf("LV::OrbSingleton::Shutdown: exception!"); return(ERROR); };

	return(OK);
};

CORBA::ORB* LV::OrbSingleton::Orb()
{
	if(msInitialized == false)
	{
		int argc = 1;
		char* argv[] = { "dummy" };
		Initialize(argc,argv);
	};
	return CORBA::ORB::_duplicate(msOrb.in());
};

PortableServer::POA* LV::OrbSingleton::RootPOA()
{
	if(msInitialized == false)
	{
		int argc = 1;
		char* argv[] = { "dummy" };
		Initialize(argc,argv);
	};
	return PortableServer::POA::_duplicate(msRootPOA.in());
};

PortableServer::POAManager* LV::OrbSingleton::POAManager()
{
	if(msInitialized == false)
	{
		int argc = 1;
		char* argv[] = { "dummy" };
		Initialize(argc,argv);
	};
	return PortableServer::POAManager::_duplicate(msPOAManager.in());
};

CosNaming::NamingContext::_ptr_type LV::OrbSingleton::NameService()
{
	if(msInitialized == false)
	{
		int argc = 1;
		char* argv[] = { "dummy" };
		Initialize(argc,argv);
	};
	return CosNaming::NamingContext::_duplicate(msNameService.in());
};

template <class T>
typename T::_ptr_type LV::OrbSingleton::resolve_initial_references(const char* s) throw(RTC::NotInitialized,CORBA::SystemException,CORBA::ORB::InvalidName)
{
	CORBA::Object_var Generic;
	typename T::_var_type Specific;

	if(OrbSingleton::msInitialized == false) throw(RTC::NotInitialized());

	Generic = OrbSingleton::msOrb->resolve_initial_references(s);
	Specific = T::_narrow(Generic.in());

	return Specific._retn();
};