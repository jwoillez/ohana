#include "LVRTC.h"
#include "LVOrbSingleton.h"
#include "LVTelemetryServer.h"
#include "LVTtm.h"
#include "LVKat.h"
#include "LVFringeTracker.h"
#include "LVStringUtils.h"
#include "LVDelayLine.h"

#include "LVconfig.h"

#include "Name.hh"

#include <map>

/*¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦*/
//                          Logging function
/*¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦*/

void logFunction(const char* msg)
{
	std::string stringMsg=msg;
	std::vector<std::string> vectorStringMsg;
	LV::StringUtils::Tokenize(stringMsg, vectorStringMsg, "\n");
	for(unsigned int i=0;i<vectorStringMsg.size();i++)
		DbgPrintf((char*)vectorStringMsg[i].c_str());
}

/*¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦*/
//                           DLL entry point
/*¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦*/

BOOL APIENTRY DllMain(HANDLE hModule, DWORD  ul_reason_for_call, LPVOID lpReserved)
{
    return TRUE;
}

/**********************************************************************/
//                            ORB methodes
/**********************************************************************/

long DLLAPI Orb_Initialize(short int debug)
{
	//Setup omniORB specifics
	omniORB::setLogFunction(&logFunction);
	omniORB::traceLevel=debug;

	// ORB Options
	int argc = 1;
	char* argv[] = { "dummy" };
	if(!LV::OrbSingleton::Initialize(argc,argv)) return(ERROR);

	return(OK);
}

long DLLAPI Orb_Shutdown(void)
{
	if(!LV::OrbSingleton::Shutdown()) return(ERROR);

	return(OK);
}

/*¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦*/
//                      TelemetryServer methodes
/*¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦*/

std::map<std::string,LV::TelemetryServer*> lvTelemetryServerMap;

long DLLAPI TelemetryServer_Connect(LStrHandle channelNameHdl, LStrHandle serverNameHdl, LVUserEventRef* lvUserEventRefPtr, unsigned long *idPtr)
{
	//Create and store LVTelemetryServer object
	LV::TelemetryServer* lvTelemetryServer = new(LV::TelemetryServer);
	lvTelemetryServerMap[LV::StringUtils::LStr2String(channelNameHdl)]=lvTelemetryServer;

	//Connect Channel
	if(!lvTelemetryServer->ConnectChannel(serverNameHdl, channelNameHdl, lvUserEventRefPtr, lvTelemetryServerMap.size())) { return ERROR; };

	if(omniORB::traceLevel)
	{
		std::string message("----> Connect: "+LV::StringUtils::LStr2String(channelNameHdl));
		LV::StringUtils::DbgStringPrintf(message);
	};

	//Return the channel ID
	*idPtr = lvTelemetryServerMap.size();

	return OK;
}

long DLLAPI TelemetryServer_Disconnect(LStrHandle channelNameHdl)
{
	//Find the LVTelemetryServer object associated with the given channel name
	LV::TelemetryServer *lvTelemetryServer;
	lvTelemetryServer=lvTelemetryServerMap.find(LV::StringUtils::LStr2String(channelNameHdl))->second;

	//Disconnect the channel
	if(!lvTelemetryServer->DisconnectChannel()) { return ERROR; };

	//Un-store and delete LVTelemetryServer object
	lvTelemetryServerMap.erase(LV::StringUtils::LStr2String(channelNameHdl));
	delete lvTelemetryServer;

	if(omniORB::traceLevel)
	{
		std::string message("----> Disconnect: "+LV::StringUtils::LStr2String(channelNameHdl));
		LV::StringUtils::DbgStringPrintf(message);
	};

	return OK;
}

long DLLAPI TelemetryServer_ChannelList(LStrHandle serverNameHdl, ArrayLStrHdl channelList)
{
	RTC::Telemetry::Server_var					server;
	RTC::NameSequenceType_var					channelNameList;
	RTC::NameType_var							channelName;
	RTC::Telemetry::NameIdPairSequenceType_var	nameIdPairList;
	RTC::Telemetry::NameIdPair_var				nameIdPair;
	RTC::Telemetry::IdIterator_var				idIterator;
	
	if(omniORB::traceLevel) DbgPrintf("---------------> Connecting to telemetry server");

	//Define Telemetry Server Name
	CosNaming::Name_var serverName = new CosNaming::Name(5);
	std::vector<std::string> serverNameTokens;
	LV::StringUtils::Tokenize(serverNameHdl,serverNameTokens,".");
	serverName->length(serverNameTokens.size());
	for (unsigned int i=0;i<serverNameTokens.size();i++)
	{
		serverName[i].id = CORBA::string_dup((char*)serverNameTokens[i].c_str());
		serverName[i].kind=(const char*) "";
	};

	//Resolve Telemetry Server
	try { server = RTC::Telemetry::Server::_narrow(LV::OrbSingleton::NameService()->resolve(serverName)); }
	catch(...) {
		std::string message("LV::TelemetryServer::ChannelList: cannot resolve telemetry server "+LV::StringUtils::LStr2String(serverNameHdl));
		LV::StringUtils::DbgStringPrintf(message);
		return(ERROR);
	};

	if(omniORB::traceLevel) DbgPrintf("---------------> Retrieving channel iterator");

	//Get Channel List iterator
	try { server->IdList(0,nameIdPairList,idIterator); }
	catch(...)
	{
		DbgPrintf("LV:TelemetryServer::ChannelList: cannot get iterator");
		return(ERROR);
	};

	if(omniORB::traceLevel) DbgPrintf("---------------> Retrieving channel list");

	//Use iterator to populate a vector of string buffer
	std::vector<std::string> channelListBuffer;
	while(idIterator->NextOne(nameIdPair))
	{
		std::string channelBuffer("");
		for(unsigned int i=0;i<nameIdPair->Name.length();i++)
		{
			if(i!=0) channelBuffer += ".";
			channelBuffer += nameIdPair->Name[i];
		};
		channelListBuffer.push_back(channelBuffer);
	};
	
	if(omniORB::traceLevel) DbgPrintf("---------------> Transfering channel list");

	//Transfer the vector of string buffer to channelList
	NumericArrayResize(uL, 1, (UHandle*)&channelList, channelListBuffer.size());
	(*channelList)->dimSize=channelListBuffer.size();
	for(unsigned int i=0;i<channelListBuffer.size();i++)
	{
		(*channelList)->elt[i]=(LStrHandle)DSNewHandle(sizeof(LStr)+channelListBuffer[i].size());
		LStrLen(*((*channelList)->elt[i])) = channelListBuffer[i].size();
		MoveBlock(channelListBuffer[i].c_str(), LStrBuf(*(*channelList)->elt[i]), channelListBuffer[i].size());
	};

	return(OK);
}

/*¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦*/
//                           TTM methodes
/*¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦*/

std::map<std::string,LV::Ttm*> lvTtmMap;

long DLLAPI Ttm_Connect(LStrHandle ttmNameHdl)
{
	//Create and store TTM Object
	LV::Ttm* lvTtm = new(LV::Ttm);
	lvTtmMap[LV::StringUtils::LStr2String(ttmNameHdl)]=lvTtm;

	//Connect TTM
	if(!lvTtm->Connect(ttmNameHdl)) return(ERROR);

	return(OK);
}

long DLLAPI Ttm_Set(LStrHandle ttmNameHdl, double NewX, double NewY)
{
	//Find the LVTtm object associated with the given TTM name
	LV::Ttm *lvTtm;
	lvTtm=lvTtmMap.find(LV::StringUtils::LStr2String(ttmNameHdl))->second;

	//Set TTM position
	if(!lvTtm->Set(NewX,NewY)) return(ERROR);

	return(OK);
}

long DLLAPI Ttm_Disconnect(LStrHandle ttmNameHdl)
{
	//Find the LVTelemetryServer object associated with the given channel name
	LV::Ttm *lvTtm;
	lvTtm=lvTtmMap.find(LV::StringUtils::LStr2String(ttmNameHdl))->second;

	//Disconnect TTM
	if(!lvTtm->Disconnect()) return(ERROR);

	//Un-store and delete LVTtm object
	lvTtmMap.erase(LV::StringUtils::LStr2String(ttmNameHdl));
	delete lvTtm;

	return(OK);
}

/*¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦*/
//                           KAT methodes
/*¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦*/

std::map<std::string,LV::Kat*> lvKatMap;

long DLLAPI Kat_Connect(LStrHandle katNameHdl)
{
	//Create and store LVKAT Object
	LV::Kat* lvKat = new(LV::Kat);
	lvKatMap[LV::StringUtils::LStr2String(katNameHdl)]=lvKat;

	//Connect KAT
	if(!lvKat->Connect(katNameHdl)) return(ERROR);

	return(OK);
}

long DLLAPI Kat_Disconnect(LStrHandle katNameHdl)
{
	//Find the LVKAT object associated with the given channel name
	LV::Kat *lvKat;
	lvKat=lvKatMap.find(LV::StringUtils::LStr2String(katNameHdl))->second;

	//Disconnect KAT
	if(!lvKat->Disconnect()) return(ERROR);

	//Un-store and delete LVKat object
	lvKatMap.erase(LV::StringUtils::LStr2String(katNameHdl));
	delete lvKat;

	return(OK);
}

long DLLAPI Kat_Track(LStrHandle katNameHdl)
{
	//Find the LVKAT object associated with the given channel name
	LV::Kat *lvKat;
	lvKat=lvKatMap.find(LV::StringUtils::LStr2String(katNameHdl))->second;

	//Track KAT
	if(!lvKat->Track()) return(ERROR);

	return(OK);
}

long DLLAPI Kat_Idle(LStrHandle katNameHdl)
{
	//Find the LVKAT object associated with the given channel name
	LV::Kat *lvKat;
	lvKat=lvKatMap.find(LV::StringUtils::LStr2String(katNameHdl))->second;

	//Idle KAT
	if(!lvKat->Idle()) return(ERROR);

	return(OK);
}

long DLLAPI Kat_SetLockTarget(LStrHandle katNameHdl, double x, double y)
{
	//Find the LVKAT object associated with the given channel name
	LV::Kat *lvKat;
	lvKat=lvKatMap.find(LV::StringUtils::LStr2String(katNameHdl))->second;

	//Idle KAT
	if(!lvKat->SetLockTarget(x,y)) return(ERROR);

	return(OK);
}

/*¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦*/
//                     Fringe Tracker methodes
/*¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦*/

std::map<std::string,LV::FringeTracker*> lvFringeTrackerMap;

long DLLAPI FringeTracker_Connect(LStrHandle fringeTrackerNameHdl)
{
	//Create and store LVFringeTracker Object
	LV::FringeTracker* lvFringeTracker = new(LV::FringeTracker);
	lvFringeTrackerMap[LV::StringUtils::LStr2String(fringeTrackerNameHdl)]=lvFringeTracker;

	//Connect FringeTracker
	if(!lvFringeTracker->Connect(fringeTrackerNameHdl)) return(ERROR);

	return(OK);
}

long DLLAPI FringeTracker_Disconnect(LStrHandle fringeTrackerNameHdl)
{
	//Find the LVFringeTracker object associated with the given channel name
	LV::FringeTracker *lvFringeTracker;
	lvFringeTracker=lvFringeTrackerMap.find(LV::StringUtils::LStr2String(fringeTrackerNameHdl))->second;

	//Disconnect FringeTracker
	if(!lvFringeTracker->Disconnect()) return(ERROR);

	//Un-store and delete LVFringeTracker object
	lvFringeTrackerMap.erase(LV::StringUtils::LStr2String(fringeTrackerNameHdl));
	delete lvFringeTracker;

	return(OK);
}

long DLLAPI FringeTracker_Track(LStrHandle fringeTrackerNameHdl)
{
	//Find the LVFringeTracker object associated with the given channel name
	LV::FringeTracker *lvFringeTracker;
	lvFringeTracker=lvFringeTrackerMap.find(LV::StringUtils::LStr2String(fringeTrackerNameHdl))->second;

	//Track FringeTracker
	if(!lvFringeTracker->Track()) return(ERROR);

	return(OK);
}

long DLLAPI FringeTracker_Idle(LStrHandle fringeTrackerNameHdl)
{
	//Find the LVFringeTracker object associated with the given channel name
	LV::FringeTracker *lvFringeTracker;
	lvFringeTracker=lvFringeTrackerMap.find(LV::StringUtils::LStr2String(fringeTrackerNameHdl))->second;

	//Idle FringeTracker
	if(!lvFringeTracker->Idle()) return(ERROR);

	return(OK);
}

long DLLAPI FringeTracker_SetCommandOffset(LStrHandle fringeTrackerNameHdl, double offset)
{
	//Find the LVFringeTracker object associated with the given channel name
	LV::FringeTracker *lvFringeTracker;
	lvFringeTracker=lvFringeTrackerMap.find(LV::StringUtils::LStr2String(fringeTrackerNameHdl))->second;

	//Idle FringeTracker
	if(!lvFringeTracker->SetCommandOffset(offset)) return(ERROR);

	return(OK);
}

long DLLAPI FringeTracker_ServoAlignRaster(LStrHandle fringeTrackerNameHdl, long channel, long goToPeak, double *xOffset, double *yOffset)
{
	//Find the LVFringeTracker object associated with the given channel name
	LV::FringeTracker *lvFringeTracker;
	lvFringeTracker=lvFringeTrackerMap.find(LV::StringUtils::LStr2String(fringeTrackerNameHdl))->second;

	//Idle FringeTracker
	if(!lvFringeTracker->ServoAlignRaster(channel, goToPeak, xOffset, yOffset)) return(ERROR);

	return(OK);
}

long DLLAPI FringeTracker_CalibrateBright(LStrHandle fringeTrackerNameHdl, long seconds)
{
	//Find the LVFringeTracker object associated with the given channel name
	LV::FringeTracker *lvFringeTracker;
	lvFringeTracker=lvFringeTrackerMap.find(LV::StringUtils::LStr2String(fringeTrackerNameHdl))->second;

	//Idle FringeTracker
	if(!lvFringeTracker->CalibrateBright(seconds)) return(ERROR);

	return(OK);
}

long DLLAPI FringeTracker_CalibrateRatio(LStrHandle fringeTrackerNameHdl, long seconds)
{
	//Find the LVFringeTracker object associated with the given channel name
	LV::FringeTracker *lvFringeTracker;
	lvFringeTracker=lvFringeTrackerMap.find(LV::StringUtils::LStr2String(fringeTrackerNameHdl))->second;

	//Idle FringeTracker
	if(!lvFringeTracker->CalibrateRatio(seconds)) return(ERROR);

	return(OK);
}

long DLLAPI FringeTracker_CalibrateRatio2(LStrHandle fringeTrackerNameHdl, long seconds)
{
	//Find the LVFringeTracker object associated with the given channel name
	LV::FringeTracker *lvFringeTracker;
	lvFringeTracker=lvFringeTrackerMap.find(LV::StringUtils::LStr2String(fringeTrackerNameHdl))->second;

	//Idle FringeTracker
	if(!lvFringeTracker->CalibrateRatio2(seconds)) return(ERROR);

	return(OK);
}

long DLLAPI FringeTracker_CalibrateDark(LStrHandle fringeTrackerNameHdl, long seconds)
{
	//Find the LVFringeTracker object associated with the given channel name
	LV::FringeTracker *lvFringeTracker;
	lvFringeTracker=lvFringeTrackerMap.find(LV::StringUtils::LStr2String(fringeTrackerNameHdl))->second;

	//Idle FringeTracker
	if(!lvFringeTracker->CalibrateDark(seconds)) return(ERROR);

	return(OK);
}

/*¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦*/
//                       Delay Line methodes
/*¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦*/

std::map<std::string,LV::DelayLine*> lvDelayLineMap;

long DLLAPI DelayLine_Connect(LStrHandle delayLineNameHdl)
{
	//Create and store LVDelayLine Object
	LV::DelayLine* lvDelayLine = new(LV::DelayLine);
	lvDelayLineMap[LV::StringUtils::LStr2String(delayLineNameHdl)]=lvDelayLine;

	//Connect DelayLine
	if(!lvDelayLine->Connect(delayLineNameHdl)) return(ERROR);

	return(OK);
};

long DLLAPI DelayLine_Disconnect(LStrHandle delayLineNameHdl)
{
	//Find the LVDelayLine object associated with the given channel name
	LV::DelayLine *lvDelayLine;
	lvDelayLine=lvDelayLineMap.find(LV::StringUtils::LStr2String(delayLineNameHdl))->second;

	//Disconnect DelayLine
	if(!lvDelayLine->Disconnect()) return(ERROR);

	//Un-store and delete LVDelayLine object
	lvDelayLineMap.erase(LV::StringUtils::LStr2String(delayLineNameHdl));
	delete lvDelayLine;

	return(OK);
};

long DLLAPI DelayLine_SetOpenLoopTarget(LStrHandle delayLineNameHdl, double laserPosition, double rate, unsigned long activationTimeLo, unsigned long activationTimeHi)
{
	//Find the LVDelayLine object associated with the given channel name
	LV::DelayLine *lvDelayLine;
	lvDelayLine=lvDelayLineMap.find(LV::StringUtils::LStr2String(delayLineNameHdl))->second;

	//Set Open Loop Target
	if(!lvDelayLine->SetOpenLoopTarget(laserPosition, rate, activationTimeLo, activationTimeHi)) return(ERROR);

	return(OK);
};

long DLLAPI DelayLine_SetManualTarget(LStrHandle delayLineNameHdl, double laserPosition, double rate, unsigned long activationTimeLo, unsigned long activationTimeHi)
{
	//Find the LVDelayLine object associated with the given channel name
	LV::DelayLine *lvDelayLine;
	lvDelayLine=lvDelayLineMap.find(LV::StringUtils::LStr2String(delayLineNameHdl))->second;

	//Set Open Loop Target
	if(!lvDelayLine->SetManualTarget(laserPosition, rate, activationTimeLo, activationTimeHi)) return(ERROR);

	return(OK);
};
