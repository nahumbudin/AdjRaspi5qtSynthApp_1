/**
* @file		Dialog_AdjFluidSynth.h
*	@author		Nahum Budin
*	@date		13-Jul-2024
*	@version	1.0
*
*	@brief		Adj FluidSynth control dialog
*
*/

#pragma once

#include <QDialog>
#include <QCheckBox>
#include <QRadioButton>

#include "libAdjRaspi5SynthAPI.h"

#include "Dialog_FluidSynthChannels.h"

namespace Ui
{
	class Dialog_AdjFluidSynth;
}

class Dialog_AdjFluidSynth : public QDialog
{
	Q_OBJECT
		
public :
	
	
	
	~Dialog_AdjFluidSynth();
	
	static Dialog_AdjFluidSynth *get_instance(QWidget *parent = 0);
	
	
	
	void control_box_ui_update_callback(int evnt, uint16_t val);
	
	
	void get_active_settings_values();
	void set_default_settings_values(bool update_flag=true);
	void update();
	
public slots:
	void closeEvent(QCloseEvent *event);

protected slots :	
	void fluid_gain_changed(int vol);
	
	void reverb_room_size_changed(int val);
	void reverb_damp_changed(int val);
	void reverb_width_changed(int val);
	void reverb_level_changed(int val);
	void reverb_activation_changed(bool val);

	void chorus_number_changed(int val);
	void chorus_level_changed(int val);
	void chorus_speed_changed(int val);
	void chorus_depth_changed(int val);
	void chorus_waveform_changed(int val);
	void chorus_waveform_select_changed(int val);

	void chorus_activation_changed(bool val);
	
	
	void on_dialog_close();
	
	
	void on_default_settings_clicked();
	void on_load_presets_clicked();
	void on_save_presets_clicked();
	
	void on_preset_1_selected(bool state);
	void on_preset_2_selected(bool state);
	void on_preset_3_selected(bool state);
	
	void on_module_channels_clicked();
	
	
	
private:
	
	explicit Dialog_AdjFluidSynth(QWidget *parent = 0);
	
	Ui::Dialog_AdjFluidSynth *ui;
	
	static Dialog_AdjFluidSynth *dialog_adj_fluid_synth_instance;
	
	Dialog_FluidSynthChannels *dialog_fluid_synth_channels;
	
	func_ptr_void_void_t close_event_callback_ptr;
	
	int fluid_gain;
	int fluid_gain_max;
	int fluid_gain_min;
	
	int reverb_room_size;
	int reverb_room_size_max;
	int reverb_room_size_min;
	
	int reverb_damp;
	int reverb_damp_max;
	int reverb_damp_min;
	
	int reverb_width;
	int reverb_width_max;
	int reverb_width_min;
		
	int reverb_level;
	int reverb_level_max;
	int reverb_level_min;
	
	bool reverb_activation;

	int chorus_number;
	int chorus_number_max;
	int chorus_number_min;
	
	int chorus_level;
	int chorus_level_max;
	int chorus_level_min;
	
	int chorus_speed;
	int chorus_speed_max;
	int chorus_speed_min;
	
	int chorus_depth;
	int chorus_depth_max;
	int chorus_depth_min;

	int chorus_waveform;
	int chorus_waveform_max = _AFS_CHORUS_WAVEFORM_TRIANGLE;
	int chorus_waveform_min = _AFS_CHORUS_WAVEFORM_SINE;
	bool chorus_activation;	
	
	int active_preset;
	
	QRadioButton *preset_radio_buttons[_NUM_OF_FLUID_PRESETS];
};
