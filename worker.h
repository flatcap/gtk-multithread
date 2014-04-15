#ifndef _WORKER_H_
#define _WORKER_H_

#include <mutex>

#include <gtkmm.h>

class Window;

class Worker
{
public:
	Worker();

	// Thread function.
	void do_work(Window* caller);

	void get_data(double& fraction_done, std::string& message) const;
	void stop_work();
	bool has_stopped() const;

private:
	// Synchronizes access to member data.
	mutable std::mutex m_Mutex;

	// Data used by both GUI thread and worker thread.
	bool m_shall_stop = false;
	bool m_has_stopped = false;
	double m_fraction_done = 0.0;
	std::string m_message;
};

#endif // _WORKER_H_

