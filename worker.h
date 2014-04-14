#ifndef _WORKER_H_
#define _WORKER_H_

#include <gtkmm.h>

class Window;

class Worker
{
public:
	Worker();

	// Thread function.
	void do_work(Window* caller);

	void get_data(double* fraction_done, Glib::ustring* message) const;
	void stop_work();
	bool has_stopped() const;

private:
	// Synchronizes access to member data.
	mutable Glib::Threads::Mutex m_Mutex;

	// Data used by both GUI thread and worker thread.
	bool m_shall_stop;
	bool m_has_stopped;
	double m_fraction_done;
	Glib::ustring m_message;
};

#endif // _WORKER_H_

