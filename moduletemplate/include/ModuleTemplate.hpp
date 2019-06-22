#ifndef TEST_MODULE_HPP
#define TEST_MODULE_HPP

#include <string>
#include <vector>
#include <signal.h>

#include "std_msgs/String.h"
#include "ros/ros.h"

#include "services/SchedulerServerData.h"
#include "messages/FinishMessage.h"

struct moduleDescriptor {
	std::string name;
	float frequency;
	uint32_t deadline; //Microsseconds
	uint32_t wce; //Microsseconds
	bool connection;
};


class ModuleTemplate {

	private:
		ModuleTemplate(const ModuleTemplate &);
		ModuleTemplate &operator=(const ModuleTemplate &);

		void schedulingCallback(const std_msgs::StringConstPtr& msg);

	public:

		virtual void setUp();

		//virtual void tearDown()

		virtual void run();

		ModuleTemplate(const int32_t &argc, char **argv);

		virtual ~ModuleTemplate();

		static void schedulingSigIntHandler(int sig);

	private:
		moduleDescriptor md;

		std::string received_name;

		ros::Publisher scheduling_pub;

		ros::Subscriber sched;

		ros::ServiceClient client_module;

		std::string topic_name;

		std::string finish_topic_name;

		float check_frequency;

		float period;
};

#endif