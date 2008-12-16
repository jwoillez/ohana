//LVRTC includes
#include "LVConsumer.h"
#include "LVconfig.h"
#include "LVStringUtils.h"
#include "LVOrbSingleton.h"

//RTC includes
#include "SequenceTypes.hh"

LV::Consumer::Consumer(std::string channelName, LVUserEventRef* lvUserEventRefPtr)
{
	mLVUserEventRefPtr=lvUserEventRefPtr;
	mChannelName=channelName;
};

void LV::Consumer::push (const CORBA::Any& data)
{
	// Debug Message
	if(omniORB::traceLevel) DbgPrintf("LVTelemetryServer::push");

	// Structures are extracted by pointer from an Any
	RTC::Telemetry::Packet* packet;

	// Attempt to extract data into a telemetry packet
	if (data >>= packet) 
	{

		if(omniORB::traceLevel) DbgPrintf("pushing a packet");

		//Setup of the LVTelemetryServerPacket
		LVTelemetryServerPacket* mLVTelemetryServerPacketPtr  = (LVTelemetryServerPacket*)DSNewPClr(sizeof(LVTelemetryServerPacket));
		mLVTelemetryServerPacketPtr->mHeader.lId              = packet->Header.Id;
		mLVTelemetryServerPacketPtr->mHeader.lSequenceNumber  = packet->Header.lSequenceNumber;
		mLVTelemetryServerPacketPtr->mHeader.lTimeFirstLo     = (unsigned long)  packet->Header.llTimeFirst;
		mLVTelemetryServerPacketPtr->mHeader.lTimeFirstHi     = (unsigned long) (packet->Header.llTimeFirst >> 32);
		mLVTelemetryServerPacketPtr->mHeader.lTimeLastLo      = (unsigned long)  packet->Header.llTimeLast;
		mLVTelemetryServerPacketPtr->mHeader.lTimeLastHi      = (unsigned long) (packet->Header.llTimeLast >> 32);
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
					default:
					break;
				} //End switch(content_tckind)
				break;
			}
			default:
			break;
		} //switch (a_tckind)
		PostLVUserEvent(*mLVUserEventRefPtr, mLVTelemetryServerPacketPtr);
	}; // End data packet extraction

};

void LV::Consumer::disconnect_push_consumer (void)
{
	try
	{
		mProxySupplier->disconnect_push_supplier();
		PortableServer::ObjectId_var objectId = LV::OrbSingleton::RootPOA()->servant_to_id(this);
		LV::OrbSingleton::RootPOA()->deactivate_object(objectId.in());
	}
	catch(...) { DbgPrintf("TelemetryServer::disconnect_push_consumer: exception!"); };
};