#ifndef _LV_ORB_H_
#define _LV_ORB_H_

#include <omniORB4/CORBA.h>
#include "RTCCore.hh"

namespace LV
{
	class OrbSingleton
	{
	public:
		static long Initialize(int argc, char* argv[]);
		static long Shutdown();
		static CORBA::ORB* Orb()
			throw(RTC::NotInitialized);
		static PortableServer::POA* RootPOA();
		static PortableServer::POAManager* POAManager();
		static CosNaming::NamingContext::_ptr_type NameService();
		template<class T>
			static typename T::_ptr_type resolve_initial_references(const char* Name)
			throw(RTC::NotInitialized,CORBA::SystemException,CORBA::ORB::InvalidName);
	private:
		static long WINAPI run();
		static bool msInitialized;
		static CORBA::ORB_var msOrb;
		static PortableServer::POA_var msRootPOA;
		static PortableServer::POAManager_var msPOAManager;
		static CosNaming::NamingContext_var msNameService;
		static HANDLE mshOrbThread;
	};
};

#endif  _LV_ORB_H_