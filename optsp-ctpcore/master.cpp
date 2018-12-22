#include "master.h"
#include <boost/thread.hpp>


Master::Master()
{

}


void Master::run()
{
	boost::thread logger_thrd(boost::bind(&Logger::run, &this->logger));

	/// TODO


	logger_thrd.join();
}