/**
* @file		Dialog_MidiMapper.h
*	@author		Nahum Budin
*	@date		19-Oct-2024
*	@version	1.0
*
*	@brief		Used for mapping MIDI channels events to instruments
*				
*	History:
*
*/

#pragma once

#include <QDialog>
#include <QPushButton>
#include <QComboBox>
#include <QMutex>

#include "MainWindow.h"

#include "libAdjRaspi5SynthAPI.h"




namespace Ui
{
	class Dialog_MidiMapper;
}

class Dialog_MidiMapper : public QDialog
{
	Q_OBJECT
		
public :
	
	~Dialog_MidiMapper();
	
	static Dialog_MidiMapper *get_instance(QWidget *parent = 0, bool showit = false);
	
	void control_box_ui_update_callback(int evnt, uint16_t val);
	
	QPoint get_last_position();
	
	virtual void update_gui();
	
	Ui::Dialog_MidiMapper *ui;
	
public slots :
	
	virtual void timerEvent(); // Called by a Timer
	void closeEvent(QCloseEvent *event);
	void moveEvent(QMoveEvent *event);
	bool event(QEvent *event);
	
	int set_channel_instrument(int ch, int inst);
	
	void ch_1_instrument_changed(int inst);
	void ch_2_instrument_changed(int inst);
	void ch_3_instrument_changed(int inst);
	void ch_4_instrument_changed(int inst);
	void ch_5_instrument_changed(int inst);
	void ch_6_instrument_changed(int inst);
	void ch_7_instrument_changed(int inst);
	void ch_8_instrument_changed(int inst);
	void ch_9_instrument_changed(int inst);
	void ch_10_instrument_changed(int inst);
	void ch_11_instrument_changed(int inst);
	void ch_12_instrument_changed(int inst);
	void ch_13_instrument_changed(int inst);
	void ch_14_instrument_changed(int inst);
	void ch_15_instrument_changed(int inst);
	void ch_16_instrument_changed(int inst);
	
	void set_all_channels_instrument_changed(int inst);
	
protected slots :

	void on_dialog_close();
	 

private:
	
	explicit Dialog_MidiMapper(QWidget *parent = 0);
	
	
	static Dialog_MidiMapper *dialog_adj_midi_mapper_instance;	
	
	func_ptr_void_void_t close_event_callback_ptr;
	
	void start_update_timer(int interval);
	
	void update_channels_combo_boxes();
	
	QPoint last_position;
	
	QComboBox *channels_combos[17];
	
	QMutex *active_modules_mutex;
	
};

class UpdateGuiThread : public QThread
{
	Q_OBJECT	
	void run();
		
};
