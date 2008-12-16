#ifndef _LV_TELEMETRY_SERVER_H_
#define _LV_TELEMETRY_SERVER_H_

#include "TelemetryServer.hh"
#include "Image.hh"
#include "LVOrbSingleton.h"
#include "LVdefinitions.h"
#include <string>

/*--------------------------------------------------------------------*/
// Keyword Consumer Class Definition
// KeywordConsumer is based on the server class 
// RTC::Telemetry::PushConsumer generated from the TelemetryServer IDL.  
// The declaration for our keyword consumer object is given below:
// In addition to the interface operations (push and disconnect_push_consumer) 
// KeywordConsumer defines a constructor 
/*--------------------------------------------------------------------*/

namespace LV
{
	class TelemetryServer : virtual public POA_RTC::Telemetry::PushConsumer
	{
		public:
			long ConnectChannel(LStrHandle serverNameHdl, LStrHandle channelNameHdl, LVUserEventRef* lvUserEventRefPtr, unsigned long id);
			long DisconnectChannel(void);
		private:
			void push(const CORBA::Any& data);
			void disconnect_push_consumer(void);
			void Notify(RTC::Telemetry::PushConsumer::NotificationType Value) {};

			RTC::Telemetry::Server_var			mServer;
			RTC::Telemetry::ProxySupplier_var	mProxySupplier;
			LVUserEventRef*						mLVUserEventRefPtr;
			std::string							mChannelName;
			unsigned long						mId;
	};
};

#endif // _LV_TELEMETRY_SERVER_H_
