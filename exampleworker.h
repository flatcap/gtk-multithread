#ifndef GTKMM_EXAMPLEWORKER_H
#define GTKMM_EXAMPLEWORKER_H

#include <gtkmm.h>

class ExampleWindow;

class ExampleWorker
{
public:
	ExampleWorker();

	// Thread function.
	void do_work(ExampleWindow* caller);

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

#endif // GTKMM_EXAMPLEWORKER_H
