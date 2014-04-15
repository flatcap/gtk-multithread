#ifndef _WORKER_H_
#define _WORKER_H_

#include <mutex>
#include <thread>

#include <gtkmm.h>

class Window;

class Worker
{
public:
	Worker (void);
	virtual ~Worker();

	void do_work (Window* caller);

	void get_data (double& fraction_done, std::string& message);
	void stop_work (void);
	bool has_stopped (void);

private:
	std::mutex m_Mutex;

	// Shared data
	bool m_shall_stop = false;
	bool m_has_stopped = false;
	double m_fraction_done = 0.0;
	std::string m_message;
};

#endif // _WORKER_H_

