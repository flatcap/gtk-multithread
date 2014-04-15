#ifndef _WINDOW_H_
#define _WINDOW_H_

#include <gtkmm.h>
#include "worker.h"

class Window : public Gtk::Window
{
public:
	Window();

	void notify();

private:
	void on_start_button_clicked();
	void on_stop_button_clicked();
	void on_quit_button_clicked();

	void update_start_stop_buttons();
	void update_widgets();

	void on_notification_from_worker_thread();

	Gtk::Box m_VBox;
	Gtk::ButtonBox m_ButtonBox;
	Gtk::Button m_ButtonStart;
	Gtk::Button m_ButtonStop;
	Gtk::ProgressBar m_ProgressBar;
	Gtk::Entry m_Entry;

	Glib::Dispatcher m_Dispatcher;
	Worker m_Worker;
	Glib::Threads::Thread* m_WorkerThread;
};

#endif // _WINDOW_H_

