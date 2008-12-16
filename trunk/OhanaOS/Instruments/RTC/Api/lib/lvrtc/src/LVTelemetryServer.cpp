
#include <string>

#include "LVTelemetryServer.h"
#include "LVconfig.h"
#include "LVStringUtils.h"

#include "SequenceTypes.hh"

/*--------------------------------------------------------------------*/
// The Initialize method setup the orb communication and subsribes
// to the telemetry channel
/*--------------------------------------------------------------------*/
long LV::TelemetryServer::ConnectChannel(LStrHandle serverNameHdl,
										LStrHandle channelNameHdl,
										LVUserEventRef* lvUserEventRefPtr,
										unsigned long id)
{
	//Save User Event Reference
	mLVUserEventRefPtr=lvUserEventRefPtr;

	//Save channel name
	mChannelName=LV::StringUtils::LStr2String(channelNameHdl);

	//Save ID
	mId=id;

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
	try {
		mServer = RTC::Telemetry::Server::_narrow(LV::OrbSingleton::NameService()->resolve(serverName));
	}
	catch(...) {
		std::string message("LVTelemetryServer::ConnectChannel: cannot resolve telemetry server "+LV::StringUtils::LStr2String(serverNameHdl));
		LV::StringUtils::DbgStringPrintf(message);
		return(ERROR);
	};

	//Define Channel Name
	RTC::NameType_var channelName = new RTC::NameType(5);
	std::vector<std::string> channelNameTokens;
	LV::StringUtils::Tokenize(channelNameHdl,channelNameTokens,".");
	channelName->length(channelNameTokens.size());
	for (unsigned int i=0;i<channelNameTokens.size();i++)
		channelName[i] = CORBA::string_dup((char*)channelNameTokens[i].c_str());

	//Subscribe Channel on Telemetry Server
	try {
		mProxySupplier = mServer->Subscribe(channelName,_this());
	}
	catch(...) {
		DbgPrintf("LVTelemetryServer::ConnectChannel: cannot subscribe telemetry channel!");
		return(ERROR);
	};

	return(OK);
}
/*--------------------------------------------------------------------*/
// DisconnectChannel method disconnect the push consumer
// from the proxy supplier
/*--------------------------------------------------------------------*/
long LV::TelemetryServer::DisconnectChannel(void)
{
	try
	{
		mProxySupplier->disconnect_push_supplier();
	}
	catch(...) { DbgPrintf("TelemetryServer::DisconnectChannel: could not disconnect from ProxyPushSupplier!"); return(ERROR); };
	try
	{
		PortableServer::ObjectId_var objectId = LV::OrbSingleton::RootPOA()->servant_to_id(this);
		LV::OrbSingleton::RootPOA()->deactivate_object(objectId.in());
	}
	catch(...) { DbgPrintf("TelemetryServer::DisconnectChannel: could not deactivate PushConsumer!"); return(ERROR); };

	return(OK);
}
/*--------------------------------------------------------------------*/
// The push method defines what the consumer does with the data it receives 
// from the telemetry channel.  In our case if the data is a 
// telemetry data packet the consumer send it to LabView as a User Event
/*--------------------------------------------------------------------*/
void LV::TelemetryServer::push (const CORBA::Any& data)
{
	// Structures are extracted by pointer from an Any
	RTC::Telemetry::Packet* packet;

	// Attempt to extract data into a telemetry packet
	if (data >>= packet) 
	{

		//Setup of the LVTelemetryServerPacket
		LVTelemetryServerPacket* mLVTelemetryServerPacketPtr  = (LVTelemetryServerPacket*)DSNewPClr(sizeof(LVTelemetryServerPacket));
		mLVTelemetryServerPacketPtr->mHeader.lId              = mId;
		mLVTelemetryServerPacketPtr->mHeader.lSequenceNumber  = packet->Header.lSequenceNumber;
		mLVTelemetryServerPacketPtr->mHeader.lTimeFirstLo     = (unsigned long) (packet->Header.llTimeFirst % 1000000000);
		mLVTelemetryServerPacketPtr->mHeader.lTimeFirstHi     = (unsigned long) (packet->Header.llTimeFirst / 1000000000);
		mLVTelemetryServerPacketPtr->mHeader.lTimeLastLo      = (unsigned long) (packet->Header.llTimeLast  % 1000000000);
		mLVTelemetryServerPacketPtr->mHeader.lTimeLastHi      = (unsigned long) (packet->Header.llTimeLast  / 1000000000);
		mLVTelemetryServerPacketPtr->mHeader.dRate            = packet->Header.dRate;

		// Extract out the data
		CORBA::Any data = packet->Data;
		CORBA::TypeCode_var tc(data.type());
		while (tc->kind() == CORBA::tk_alias) tc = tc->content_type();

		CORBA::TCKind a_tckind=tc->kind ();
		switch (a_tckind) 
		{
			case CORBA::tk_sequence: 
			{
				CORBA::TypeCode_var content_tc(tc->content_type());
				CORBA::TCKind content_tckind=content_tc->kind();
				switch (content_tckind) 
				{
					case CORBA::tk_double:
					{
						RTC::DoubleSequenceType* sequencePtr;
						RTC::DoubleSequenceType sequence;
						if (packet->Data >>= sequencePtr) 
						{
							//Post data as a LabView User Event
							sequence=*sequencePtr;
							NumericArrayResize(fD,1,(unsigned char ***)&(mLVTelemetryServerPacketPtr->mArrayDblHdl),sequence.length());
							(*(mLVTelemetryServerPacketPtr->mArrayDblHdl))->dimSize=sequence.length();
							for(unsigned int i=0;i<sequence.length();i++) (*(mLVTelemetryServerPacketPtr->mArrayDblHdl))->elt[i]=sequence[i];
						}
						break;
					}
					case CORBA::tk_float:
					{
						break;
					}
					case CORBA::tk_short:
					{
						break;
					}
					case CORBA::tk_long:
					{
						break;
					}
					case CORBA::tk_string:
					{
						break;
					}
					case CORBA::tk_boolean:
					{
						break;
					}
					case CORBA::tk_struct:
					{
						RTC::Image16SequenceType* image16SequencePtr;
						RTC::Image16SequenceType image16Sequence;
						if (packet->Data >>= image16SequencePtr)
						{
							//Post data as a LabView User Event
							image16Sequence = *image16SequencePtr;
							NumericArrayResize(fD,1,(unsigned char ***)&(mLVTelemetryServerPacketPtr->mArrayDblHdl),image16Sequence[0].Header.lH*image16Sequence[0].Header.lV*image16Sequence.length());
							(*(mLVTelemetryServerPacketPtr->mArrayDblHdl))->dimSize=image16Sequence[0].Header.lH*image16Sequence[0].Header.lV*image16Sequence.length();
							for(unsigned int i=0;i<image16Sequence.length();i++)
								for(long j=0;j<image16Sequence[0].Header.lV*image16Sequence[0].Header.lH;j++)
									(*(mLVTelemetryServerPacketPtr->mArrayDblHdl))->elt[i*image16Sequence[0].Header.lV*image16Sequence[0].Header.lH+j]=image16Sequence[i].Pixels[j];
						}
						break;
					}
					default:
					break;
				} //End switch(content_tckind)
				break;
			}
			default:
			break;
		} //switch (a_tckind)

		PostLVUserEvent(*mLVUserEventRefPtr, mLVTelemetryServerPacketPtr);
		DSDisposeHandle(mLVTelemetryServerPacketPtr->mArrayDblHdl);
		DSDisposePtr(mLVTelemetryServerPacketPtr);

	if(omniORB::traceLevel)
	{
		LV::StringUtils::DbgStringPrintf(std::string("----> Packet: ")+mChannelName);
	};

	}; // End data packet extraction

}
/*--------------------------------------------------------------------*/
// The disconnect_push_consumer method uses a canned procedure to 
// deactivate itself..
/*--------------------------------------------------------------------*/
void LV::TelemetryServer::disconnect_push_consumer (void)
{
	try
	{
		this->DisconnectChannel();
	}
	catch(...) { DbgPrintf("TelemetryServer::disconnect_push_consumer: could not deactivate push consumer!"); };
}