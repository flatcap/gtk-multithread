#include <sstream>
#include "worker.h"
#include "window.h"

Worker::Worker()
{
}

// Accesses to these data are synchronized by a mutex.
// Some microseconds can be saved by getting all data at once, instead of having
// separate get_fraction_done() and get_message() methods.
void Worker::get_data(double& fraction_done, std::string& message) const
{
	std::lock_guard<std::mutex> lock (m_Mutex);

	fraction_done = m_fraction_done;
	message = m_message;
}

void Worker::stop_work()
{
	std::lock_guard<std::mutex> lock (m_Mutex);
	m_shall_stop = true;
}

bool Worker::has_stopped() const
{
	std::lock_guard<std::mutex> lock (m_Mutex);
	return m_has_stopped;
}

void Worker::do_work(Window* caller)
{
	m_Mutex.lock();
	m_has_stopped = false;
	m_fraction_done = 0.0;
	m_message = "";
	m_Mutex.unlock();

	// Simulate a long calculation.
	for (int i = 0; ; ++i) { // do until break
		Glib::usleep(250000); // microseconds

		{// Scope lock
			std::lock_guard<std::mutex> lock (m_Mutex);

			m_fraction_done += 0.01;

			if (i % 4 == 3) {
				std::stringstream str;
				str << (m_fraction_done * 100.0) << "% done\n";
				m_message += str.str();
			}

			if (m_fraction_done >= 1.0) {
				m_message += "Finished";
				break;
			}
			if (m_shall_stop) {
				m_message += "Stopped";
				break;
			}
		} // End of scope
		caller->notify();
	}

	m_Mutex.lock();
	m_shall_stop = false;
	m_has_stopped = true;
	m_Mutex.unlock();
	caller->notify();
}

