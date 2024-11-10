/**
* @file		Dialog_MidiMixer.h
*	@author		Nahum Budin
*	@date		22-Aug-2024
*	@version	1.0
*
*	@brief		Midi Mixer control dialog
*
*/

#pragma once

#include <QDialog>
#include <QTHread>

#include "libAdjRaspi5SynthAPI.h"


namespace Ui
{
	class Dialog_MidiMixer;
}

class Dialog_MidiMixer : public QDialog
{
	Q_OBJECT
		
public :
	
	~Dialog_MidiMixer();
	
	static Dialog_MidiMixer *get_instance(QWidget *parent = 0);
	
	
	void control_box_ui_update_callback(int evnt, uint16_t val);
	void channels_volumes_update_callback(int chan, int vol);
	void channels_pans_update_callback(int chan, int vol);
	void channels_static_volume_update_callback(int chan, bool state);
	void channels_program_update_callback(int chan, int prog);
	
public slots :
	virtual void update_gui(); // Called by a Timer
	void closeEvent(QCloseEvent *event);
	
protected slots :
	
	void on_dialog_close();
	
	void on_volume_slider_changed_ch_1(int vol);
	void on_volume_slider_changed_ch_2(int vol);
	void on_volume_slider_changed_ch_3(int vol);
	void on_volume_slider_changed_ch_4(int vol);
	void on_volume_slider_changed_ch_5(int vol);
	void on_volume_slider_changed_ch_6(int vol);
	void on_volume_slider_changed_ch_7(int vol);
	void on_volume_slider_changed_ch_8(int vol);
	void on_volume_slider_changed_ch_9(int vol);
	void on_volume_slider_changed_ch_10(int vol);
	void on_volume_slider_changed_ch_11(int vol);
	void on_volume_slider_changed_ch_12(int vol);
	void on_volume_slider_changed_ch_13(int vol);
	void on_volume_slider_changed_ch_14(int vol);
	void on_volume_slider_changed_ch_15(int vol);
	void on_volume_slider_changed_ch_16(int vol);
	
	void on_volume_spinbox_changed_ch_1(int vol);
	void on_volume_spinbox_changed_ch_2(int vol);
	void on_volume_spinbox_changed_ch_3(int vol);
	void on_volume_spinbox_changed_ch_4(int vol);
	void on_volume_spinbox_changed_ch_5(int vol);
	void on_volume_spinbox_changed_ch_6(int vol);
	void on_volume_spinbox_changed_ch_7(int vol);
	void on_volume_spinbox_changed_ch_8(int vol);
	void on_volume_spinbox_changed_ch_9(int vol);
	void on_volume_spinbox_changed_ch_10(int vol);
	void on_volume_spinbox_changed_ch_11(int vol);
	void on_volume_spinbox_changed_ch_12(int vol);
	void on_volume_spinbox_changed_ch_13(int vol);
	void on_volume_spinbox_changed_ch_14(int vol);
	void on_volume_spinbox_changed_ch_15(int vol);
	void on_volume_spinbox_changed_ch_16(int vol);
	
	void on_pan_dial_changed_ch_1(int pan);
	void on_pan_dial_changed_ch_2(int pan);
	void on_pan_dial_changed_ch_3(int pan);
	void on_pan_dial_changed_ch_4(int pan);
	void on_pan_dial_changed_ch_5(int pan);
	void on_pan_dial_changed_ch_6(int pan);
	void on_pan_dial_changed_ch_7(int pan);
	void on_pan_dial_changed_ch_8(int pan);
	void on_pan_dial_changed_ch_9(int pan);
	void on_pan_dial_changed_ch_10(int pan);
	void on_pan_dial_changed_ch_11(int pan);
	void on_pan_dial_changed_ch_12(int pan);
	void on_pan_dial_changed_ch_13(int pan);
	void on_pan_dial_changed_ch_14(int pan);
	void on_pan_dial_changed_ch_15(int pan);
	void on_pan_dial_changed_ch_16(int pan);
	
	void on_static_vol_checkbox_changed_ch_1(bool state);
	void on_static_vol_checkbox_changed_ch_2(bool state);
	void on_static_vol_checkbox_changed_ch_3(bool state);
	void on_static_vol_checkbox_changed_ch_4(bool state);
	void on_static_vol_checkbox_changed_ch_5(bool state);
	void on_static_vol_checkbox_changed_ch_6(bool state);
	void on_static_vol_checkbox_changed_ch_7(bool state);
	void on_static_vol_checkbox_changed_ch_8(bool state);
	void on_static_vol_checkbox_changed_ch_9(bool state);
	void on_static_vol_checkbox_changed_ch_10(bool state);
	void on_static_vol_checkbox_changed_ch_11(bool state);
	void on_static_vol_checkbox_changed_ch_12(bool state);
	void on_static_vol_checkbox_changed_ch_13(bool state);
	void on_static_vol_checkbox_changed_ch_14(bool state);
	void on_static_vol_checkbox_changed_ch_15(bool state);
	void on_static_vol_checkbox_changed_ch_16(bool state);
	
protected:
	void timerEvent(QTimerEvent *event);
	
private:
	
	explicit Dialog_MidiMixer(QWidget *parent = 0);
	
	Ui::Dialog_MidiMixer *ui;
	
	static Dialog_MidiMixer *dialog_midi_mixer_instance;
	
	func_ptr_void_void_t close_event_callback_ptr;
	
	int active_channels_tab;
	
	int channels_volume[16];
	int channel_volume_max = 100;
	int channels_volume_min = 0;
	
	int channels_pan[16];
	int channels_pan_max = 50;
	int channels_pan_min = -50;
	
	bool channels_static_volume[16];
	
	QString channels_programs_names[16];
	
	void on_volume_changed(int chan, int vol);
	void on_pan_changed(int chan, int pan);
	void on_static_volume_changed(int chan, bool state);

	void start_update_timer(int interval);
	
};
