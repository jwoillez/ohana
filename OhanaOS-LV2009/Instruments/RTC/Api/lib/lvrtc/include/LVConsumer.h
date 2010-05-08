#ifndef _LV_CONSUMER_H_
#define _LV_CONSUMER_H_

#include "TelemetryServer.hh"
#include "LVdefinitions.h"
#include <string>

namespace LV
{
	class Consumer : virtual public POA_RTC::Telemetry::PushConsumer
	{
	public:
		Consumer(std::string channelName, LVUserEventRef* lvUserEventRefPtr);
	private:
		void push(const CORBA::Any& data);
		void disconnect_push_consumer(void);
		void Notify(RTC::Telemetry::PushConsumer::NotificationType Value) {};

		RTC::Telemetry::ProxySupplier_var	mProxySupplier;
		LVUserEventRef*						mLVUserEventRefPtr;
		std::string							mChannelName;
	};
};

#endif  _LV_CONSUMER_H_