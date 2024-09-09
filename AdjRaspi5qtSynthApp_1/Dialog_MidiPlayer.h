/**
* @file		Dialog_MidiPlayer.h
*	@author		Nahum Budin
*	@date		11-Aug-2024
*	@version	1.0
*
*	@brief		Used for playing MIDI files
*				
*	History:
*
*/

#pragma once

#include <QDialog>
#include <QPushButton>
#include <QTHread>

#include "libAdjRaspi5SynthAPI.h"

namespace Ui
{
	class Dialog_MidiPlayer;
}

class Dialog_MidiPlayer : public QDialog
{
	Q_OBJECT
		
public :
	
	~Dialog_MidiPlayer();
	
	static Dialog_MidiPlayer *get_instance(QWidget *parent = 0);
	
	
	void control_box_ui_update_callback(int evnt, uint16_t val);
	
	Ui::Dialog_MidiPlayer *ui;

public slots :
	virtual void timerEvent(); // Called by a Timer
	void closeEvent(QCloseEvent *event);
	
protected slots :
	
	void on_open_file_clicked();
	
	void on_play_clicked();
	void on_pause_clicked();
	void on_stop_clicked();
	
	void on_dialog_close();
	
	void on_midi_file_loaded(const QString &s);
	
protected:
	virtual void update_gui(); 
	
	
private:
	
	explicit Dialog_MidiPlayer(QWidget *parent = 0);
	
	static Dialog_MidiPlayer *dialog_adj_midi_player_instance;	
	
	func_ptr_void_void_t close_event_callback_ptr;
	
	void start_update_timer(int interval);
};

class OpenFileThread : public QThread
{
	Q_OBJECT	
	void run();
	
signals:
	void resultReady(const QString &s);	
		
};
