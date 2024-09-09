/**
* @file		Dialog_MidiMixer.cpp
*	@author		Nahum Budin
*	@date		22-Aug-2024
*	@version	1.0
*
*	@brief		Midi Mixer control dialog
*
*/

#include <QTimer>

#include "utils.h"

#include "MainWindow.h"
#include "Dialog_MidiMixer.h"
#include "ui_Dialog_MidiMixer.h"

void midi_mixer_control_box_event_update_ui_callback_wrapper(int evnt, uint16_t val)
{
	Dialog_MidiMixer::get_instance()->control_box_ui_update_callback(evnt, val);
}

void midi_mixer_update_channels_volumes_ui_update_callback_wrapper(int chan, int vol)
{
	Dialog_MidiMixer::get_instance()->channels_volumes_update_callback(chan, vol);
}

void midi_mixer_update_channels_pans_ui_update_callback_wrapper(int chan, int pan)
{
	Dialog_MidiMixer::get_instance()->channels_pans_update_callback(chan, pan);
}

void midi_mixer_update_channels_static_volume_ui_update_callback_wrapper(int chan, bool state)
{
	Dialog_MidiMixer::get_instance()->channels_static_volume_update_callback(chan, state);
}

void midi_mixer_channels_program_update_callback_wrapper(int chan, int prog)
{
	Dialog_MidiMixer::get_instance()->channels_program_update_callback(chan, prog);
}

Dialog_MidiMixer *Dialog_MidiMixer::dialog_midi_mixer_instance = NULL;

Dialog_MidiMixer::Dialog_MidiMixer(QWidget *parent)
	: QDialog(parent)
	, ui(new Ui::Dialog_MidiMixer)
{
	ui->setupUi(this);
	dialog_midi_mixer_instance = this;
	
	for (int ch = 0; ch < 16; ch++)
	{
		channels_static_volume[ch] = false;
		channels_programs_names[ch] = "";
		channels_volume[ch] = 80;
		channels_pan[ch] = 0;
	}
	
	close_event_callback_ptr = NULL;
	
	this->setFocus(Qt::ActiveWindowFocusReason);
	
	active_channels_tab = _MIDI_MIXER_CHANNELS_1_8;
	
	mod_synth_register_callback_control_box_event_update_ui(
		&midi_mixer_control_box_event_update_ui_callback_wrapper);
	
	mod_synth_register_midi_mixer_channel_volume_update_callback(
			&midi_mixer_update_channels_volumes_ui_update_callback_wrapper);
	
	mod_synth_register_midi_mixer_channel_pan_update_callback(
			&midi_mixer_update_channels_pans_ui_update_callback_wrapper);
	
	mod_synth_register_midi_mixer_channel_static_volume_update_callback(
			&midi_mixer_update_channels_static_volume_ui_update_callback_wrapper);
	
	/* Midi mapper channel volume commands trapper */
	mod_synth_register_midi_channel_volume_control_command_trapped_callback
		(&midi_mixer_update_channels_volumes_ui_update_callback_wrapper);
	
	/* Midi mapper channel change program commands trapper */
	mod_synth_register_midi_channel_change_program_command_trapped_callback
		(&midi_mixer_channels_program_update_callback_wrapper);

	
	connect(ui->verticalSlider_MidiMixerChanVol_1,
		SIGNAL(valueChanged(int)),
		this,
		SLOT(on_volume_slider_changed_ch_1(int)));
	
	connect(ui->verticalSlider_MidiMixerChanVol_2,
		SIGNAL(valueChanged(int)),
		this,
		SLOT(on_volume_slider_changed_ch_2(int)));
	
	connect(ui->verticalSlider_MidiMixerChanVol_3,
		SIGNAL(valueChanged(int)),
		this,
		SLOT(on_volume_slider_changed_ch_3(int)));
	
	connect(ui->verticalSlider_MidiMixerChanVol_4,
		SIGNAL(valueChanged(int)),
		this,
		SLOT(on_volume_slider_changed_ch_4(int)));
	
	connect(ui->verticalSlider_MidiMixerChanVol_5,
		SIGNAL(valueChanged(int)),
		this,
		SLOT(on_volume_slider_changed_ch_5(int)));
	
	connect(ui->verticalSlider_MidiMixerChanVol_6,
		SIGNAL(valueChanged(int)),
		this,
		SLOT(on_volume_slider_changed_ch_6(int)));
	
	connect(ui->verticalSlider_MidiMixerChanVol_7,
		SIGNAL(valueChanged(int)),
		this,
		SLOT(on_volume_slider_changed_ch_7(int)));
	
	connect(ui->verticalSlider_MidiMixerChanVol_8,
		SIGNAL(valueChanged(int)),
		this,
		SLOT(on_volume_slider_changed_ch_8(int)));
	
	connect(ui->verticalSlider_MidiMixerChanVol_9,
		SIGNAL(valueChanged(int)),
		this,
		SLOT(on_volume_slider_changed_ch_9(int)));
	
	connect(ui->verticalSlider_MidiMixerChanVol_10,
		SIGNAL(valueChanged(int)),
		this,
		SLOT(on_volume_slider_changed_ch_10(int)));
	
	connect(ui->verticalSlider_MidiMixerChanVol_11,
		SIGNAL(valueChanged(int)),
		this,
		SLOT(on_volume_slider_changed_ch_11(int)));
	
	connect(ui->verticalSlider_MidiMixerChanVol_12,
		SIGNAL(valueChanged(int)),
		this,
		SLOT(on_volume_slider_changed_ch_12(int)));
	
	connect(ui->verticalSlider_MidiMixerChanVol_13,
		SIGNAL(valueChanged(int)),
		this,
		SLOT(on_volume_slider_changed_ch_13(int)));
	
	connect(ui->verticalSlider_MidiMixerChanVol_14,
		SIGNAL(valueChanged(int)),
		this,
		SLOT(on_volume_slider_changed_ch_14(int)));
	
	connect(ui->verticalSlider_MidiMixerChanVol_15,
		SIGNAL(valueChanged(int)),
		this,
		SLOT(on_volume_slider_changed_ch_15(int)));
	
	connect(ui->verticalSlider_MidiMixerChanVol_16,
		SIGNAL(valueChanged(int)),
		this,
		SLOT(on_volume_slider_changed_ch_16(int)));
	
	connect(ui->spinBox_MidiMixerChanVol_1,
		SIGNAL(valueChanged(int)),
		this,
		SLOT(on_volume_spinbox_changed_ch_1(int)));
	
	connect(ui->spinBox_MidiMixerChanVol_2,
		SIGNAL(valueChanged(int)),
		this,
		SLOT(on_volume_spinbox_changed_ch_2(int)));
	
	connect(ui->spinBox_MidiMixerChanVol_3,
		SIGNAL(valueChanged(int)),
		this,
		SLOT(on_volume_spinbox_changed_ch_3(int)));
	
	connect(ui->spinBox_MidiMixerChanVol_4,
		SIGNAL(valueChanged(int)),
		this,
		SLOT(on_volume_spinbox_changed_ch_4(int)));
	
	connect(ui->spinBox_MidiMixerChanVol_5,
		SIGNAL(valueChanged(int)),
		this,
		SLOT(on_volume_spinbox_changed_ch_5(int)));
	
	connect(ui->spinBox_MidiMixerChanVol_6,
		SIGNAL(valueChanged(int)),
		this,
		SLOT(on_volume_spinbox_changed_ch_6(int)));
	
	connect(ui->spinBox_MidiMixerChanVol_7,
		SIGNAL(valueChanged(int)),
		this,
		SLOT(on_volume_spinbox_changed_ch_7(int)));
	
	connect(ui->spinBox_MidiMixerChanVol_8,
		SIGNAL(valueChanged(int)),
		this,
		SLOT(on_volume_spinbox_changed_ch_8(int)));
	
	connect(ui->spinBox_MidiMixerChanVol_9,
		SIGNAL(valueChanged(int)),
		this,
		SLOT(on_volume_spinbox_changed_ch_9(int)));
	
	connect(ui->spinBox_MidiMixerChanVol_10,
		SIGNAL(valueChanged(int)),
		this,
		SLOT(on_volume_spinbox_changed_ch_10(int)));
	
	connect(ui->spinBox_MidiMixerChanVol_11,
		SIGNAL(valueChanged(int)),
		this,
		SLOT(on_volume_spinbox_changed_ch_11(int)));
	
	connect(ui->spinBox_MidiMixerChanVol_12,
		SIGNAL(valueChanged(int)),
		this,
		SLOT(on_volume_spinbox_changed_ch_12(int)));
	
	connect(ui->spinBox_MidiMixerChanVol_13,
		SIGNAL(valueChanged(int)),
		this,
		SLOT(on_volume_spinbox_changed_ch_13(int)));
	
	connect(ui->spinBox_MidiMixerChanVol_14,
		SIGNAL(valueChanged(int)),
		this,
		SLOT(on_volume_spinbox_changed_ch_14(int)));
	
	connect(ui->spinBox_MidiMixerChanVol_15,
		SIGNAL(valueChanged(int)),
		this,
		SLOT(on_volume_spinbox_changed_ch_15(int)));
	
	connect(ui->spinBox_MidiMixerChanVol_16,
		SIGNAL(valueChanged(int)),
		this,
		SLOT(on_volume_spinbox_changed_ch_16(int)));
	
	connect(ui->dial_MidiMixerChanPan_1,
		SIGNAL(valueChanged(int)),
		this,
		SLOT(on_pan_dial_changed_ch_1(int)));
	
	connect(ui->dial_MidiMixerChanPan_2,
		SIGNAL(valueChanged(int)),
		this,
		SLOT(on_pan_dial_changed_ch_2(int)));
	
	connect(ui->dial_MidiMixerChanPan_3,
		SIGNAL(valueChanged(int)),
		this,
		SLOT(on_pan_dial_changed_ch_3(int)));
	
	connect(ui->dial_MidiMixerChanPan_4,
		SIGNAL(valueChanged(int)),
		this,
		SLOT(on_pan_dial_changed_ch_4(int)));
	
	connect(ui->dial_MidiMixerChanPan_5,
		SIGNAL(valueChanged(int)),
		this,
		SLOT(on_pan_dial_changed_ch_5(int)));
	
	connect(ui->dial_MidiMixerChanPan_6,
		SIGNAL(valueChanged(int)),
		this,
		SLOT(on_pan_dial_changed_ch_6(int)));
	
	connect(ui->dial_MidiMixerChanPan_7,
		SIGNAL(valueChanged(int)),
		this,
		SLOT(on_pan_dial_changed_ch_7(int)));
	
	connect(ui->dial_MidiMixerChanPan_8,
		SIGNAL(valueChanged(int)),
		this,
		SLOT(on_pan_dial_changed_ch_8(int)));
	
	connect(ui->dial_MidiMixerChanPan_9,
		SIGNAL(valueChanged(int)),
		this,
		SLOT(on_pan_dial_changed_ch_9(int)));
	
	connect(ui->dial_MidiMixerChanPan_10,
		SIGNAL(valueChanged(int)),
		this,
		SLOT(on_pan_dial_changed_ch_10(int)));
	
	connect(ui->dial_MidiMixerChanPan_11,
		SIGNAL(valueChanged(int)),
		this,
		SLOT(on_pan_dial_changed_ch_11(int)));
	
	connect(ui->dial_MidiMixerChanPan_12,
		SIGNAL(valueChanged(int)),
		this,
		SLOT(on_pan_dial_changed_ch_12(int)));
	
	connect(ui->dial_MidiMixerChanPan_13,
		SIGNAL(valueChanged(int)),
		this,
		SLOT(on_pan_dial_changed_ch_13(int)));
	
	connect(ui->dial_MidiMixerChanPan_14,
		SIGNAL(valueChanged(int)),
		this,
		SLOT(on_pan_dial_changed_ch_14(int)));
	
	connect(ui->dial_MidiMixerChanPan_15,
		SIGNAL(valueChanged(int)),
		this,
		SLOT(on_pan_dial_changed_ch_15(int)));
	
	connect(ui->dial_MidiMixerChanPan_16,
		SIGNAL(valueChanged(int)),
		this,
		SLOT(on_pan_dial_changed_ch_16(int)));
	
	connect(ui->checkBox_MidiMixerChanStaticVol_1,
		SIGNAL(toggled(bool)),
		this,
		SLOT(on_static_vol_checkbox_changed_ch_1(bool)));
	
	connect(ui->checkBox_MidiMixerChanStaticVol_2,
		SIGNAL(toggled(bool)),
		this,
		SLOT(on_static_vol_checkbox_changed_ch_2(bool)));
	
	connect(ui->checkBox_MidiMixerChanStaticVol_3,
		SIGNAL(toggled(bool)),
		this,
		SLOT(on_static_vol_checkbox_changed_ch_3(bool)));
	
	connect(ui->checkBox_MidiMixerChanStaticVol_4,
		SIGNAL(toggled(bool)),
		this,
		SLOT(on_static_vol_checkbox_changed_ch_4(bool)));
	
	connect(ui->checkBox_MidiMixerChanStaticVol_5,
		SIGNAL(toggled(bool)),
		this,
		SLOT(on_static_vol_checkbox_changed_ch_5(bool)));
	
	connect(ui->checkBox_MidiMixerChanStaticVol_6,
		SIGNAL(toggled(bool)),
		this,
		SLOT(on_static_vol_checkbox_changed_ch_6(bool)));
	
	connect(ui->checkBox_MidiMixerChanStaticVol_7,
		SIGNAL(toggled(bool)),
		this,
		SLOT(on_static_vol_checkbox_changed_ch_7(bool)));
	
	connect(ui->checkBox_MidiMixerChanStaticVol_8,
		SIGNAL(toggled(bool)),
		this,
		SLOT(on_static_vol_checkbox_changed_ch_8(bool)));
	
	connect(ui->checkBox_MidiMixerChanStaticVol_9,
		SIGNAL(toggled(bool)),
		this,
		SLOT(on_static_vol_checkbox_changed_ch_9(bool)));
	
	connect(ui->checkBox_MidiMixerChanStaticVol_10,
		SIGNAL(toggled(bool)),
		this,
		SLOT(on_static_vol_checkbox_changed_ch_10(bool)));
	
	connect(ui->checkBox_MidiMixerChanStaticVol_11,
		SIGNAL(toggled(bool)),
		this,
		SLOT(on_static_vol_checkbox_changed_ch_11(bool)));
	
	connect(ui->checkBox_MidiMixerChanStaticVol_12,
		SIGNAL(toggled(bool)),
		this,
		SLOT(on_static_vol_checkbox_changed_ch_12(bool)));
	
	connect(ui->checkBox_MidiMixerChanStaticVol_13,
		SIGNAL(toggled(bool)),
		this,
		SLOT(on_static_vol_checkbox_changed_ch_13(bool)));
	
	connect(ui->checkBox_MidiMixerChanStaticVol_14,
		SIGNAL(toggled(bool)),
		this,
		SLOT(on_static_vol_checkbox_changed_ch_14(bool)));
	
	connect(ui->checkBox_MidiMixerChanStaticVol_15,
		SIGNAL(toggled(bool)),
		this,
		SLOT(on_static_vol_checkbox_changed_ch_15(bool)));
	
	connect(ui->checkBox_MidiMixerChanStaticVol_16,
		SIGNAL(toggled(bool)),
		this,
		SLOT(on_static_vol_checkbox_changed_ch_16(bool)));
	
	MainWindow::get_instance()->register_active_dialog(this);
	
	// start a periodic timer after this timeout - 
	start_update_timer(2000);
}

Dialog_MidiMixer::~Dialog_MidiMixer()
{
	
}

Dialog_MidiMixer *Dialog_MidiMixer::get_instance(QWidget *parent)
{
	if (dialog_midi_mixer_instance == NULL)
	{
		dialog_midi_mixer_instance = new Dialog_MidiMixer(parent);
	}
	
	return dialog_midi_mixer_instance;
}

void Dialog_MidiMixer::closeEvent(QCloseEvent *event)
{
	if (close_event_callback_ptr != NULL)
	{
		close_event_callback_ptr();
	}
	
	hide();
}


void Dialog_MidiMixer::control_box_ui_update_callback(int evnt, uint16_t val)
{
	int channel = -1;
	int volume, volume_slider_gap;
	Qt::CheckState checked;
	
	static int prev_knob_chan_vol_val[16] = { 64 };
	
	if (!this->hasFocus())
	{
		return;
	}
	
	if ((evnt == _CONTROL_FUNCTION_PUSHBUTTON_UP) &&
			 (val == 0))
	{
		/* Toggle selected channels group */
		if (active_channels_tab == _MIDI_MIXER_CHANNELS_1_8)
		{
			active_channels_tab = _MIDI_MIXER_CHANNELS_9_16;
			ui->tabWidget->setCurrentIndex(active_channels_tab);
		}
		else
		{
			active_channels_tab = _MIDI_MIXER_CHANNELS_1_8;
			ui->tabWidget->setCurrentIndex(active_channels_tab);
		}
	}
	else if (evnt == _CONTROL_SLIDER_BLUE_GRAY)
	{
		channel = active_channels_tab * 8;
		
		volume = normalize_slider_value(val, channel_volume_max, channels_volume_min);
		/* Change slider value only when it matches the UI slider position */
		if (channels_volume[channel] > channel_volume_max)
		{
			channels_volume[channel] = channel_volume_max; // TODO: how did we get here?
		}
		volume_slider_gap = channels_volume[channel] - volume;
			
		if (abs((float)volume_slider_gap) < ((channel_volume_max - channels_volume_min) / 5.0))
		{
			if (channel == 0)
			{
				on_volume_slider_changed_ch_1(volume);
			}
			else
			{
				on_volume_slider_changed_ch_9(volume);
			}
		}		
	}
	else if (evnt == _CONTROL_SLIDER_BLUE_RED)
	{
		channel = active_channels_tab * 8 + 1;
		
		volume = normalize_slider_value(val, channel_volume_max, channels_volume_min);
		/* Change slider value only when it matches the UI slider position */
		volume_slider_gap = channels_volume[channel] - volume;
			
		if (abs((float)volume_slider_gap) < ((channel_volume_max - channels_volume_min) / 5.0))
		{
			if (channel == 1)
			{
				on_volume_slider_changed_ch_2(volume);
			}
			else
			{
				on_volume_slider_changed_ch_10(volume);
			}
		}	
	}
	else if (evnt == _CONTROL_SLIDER_BLUE_BLUE)
	{
		channel = active_channels_tab * 8 + 2;
		
		volume = normalize_slider_value(val, channel_volume_max, channels_volume_min);
		/* Change slider value only when it matches the UI slider position */
		volume_slider_gap = channels_volume[channel] - volume;
			
		if (abs((float)volume_slider_gap) < ((channel_volume_max - channels_volume_min) / 5.0))
		{
			if (channel == 2)
			{
				on_volume_slider_changed_ch_3(volume);
			}
			else
			{
				on_volume_slider_changed_ch_11(volume);
			}
		}	
	}
	else if (evnt == _CONTROL_SLIDER_BLUE_WHITE)
	{
		channel = active_channels_tab * 8 + 3;
		
		volume = normalize_slider_value(val, channel_volume_max, channels_volume_min);
		/* Change slider value only when it matches the UI slider position */
		volume_slider_gap = channels_volume[channel] - volume;
			
		if (abs((float)volume_slider_gap) < ((channel_volume_max - channels_volume_min) / 5.0))
		{
			if (channel == 3)
			{
				on_volume_slider_changed_ch_4(volume);
			}
			else
			{
				on_volume_slider_changed_ch_12(volume);
			}
		}	
	}
	else if (evnt == _CONTROL_SLIDER_ORANGE_GRAY)
	{
		channel = active_channels_tab * 8 + 4;
		
		volume = normalize_slider_value(val, channel_volume_max, channels_volume_min);
		/* Change slider value only when it matches the UI slider position */
		volume_slider_gap = channels_volume[channel] - volume;
			
		if (abs((float)volume_slider_gap) < ((channel_volume_max - channels_volume_min) / 5.0))
		{
			if (channel == 4)
			{
				on_volume_slider_changed_ch_5(volume);
			}
			else
			{
				on_volume_slider_changed_ch_13(volume);
			}
		}	
	}
	else if (evnt == _CONTROL_SLIDER_ORANGE_RED)
	{
		channel = active_channels_tab * 8 + 5;
		
		volume = normalize_slider_value(val, channel_volume_max, channels_volume_min);
		/* Change slider value only when it matches the UI slider position */
		volume_slider_gap = channels_volume[channel] - volume;
			
		if (abs((float)volume_slider_gap) < ((channel_volume_max - channels_volume_min) / 5.0))
		{
			if (channel == 5)
			{
				on_volume_slider_changed_ch_6(volume);
			}
			else
			{
				on_volume_slider_changed_ch_14(volume);
			}
		}	
	}
	else if (evnt == _CONTROL_SLIDER_ORANGE_BLUE)
	{
		channel = active_channels_tab * 8 + 6;
		
		volume = normalize_slider_value(val, channel_volume_max, channels_volume_min);
		/* Change slider value only when it matches the UI slider position */
		volume_slider_gap = channels_volume[channel] - volume;
		if (abs((float)volume_slider_gap) < ((channel_volume_max - channels_volume_min) / 5.0))
		{
			if (channel == 6)
			{
				on_volume_slider_changed_ch_7(volume);
			}
			else
			{
				on_volume_slider_changed_ch_15(volume);
			}
		}	
	}
	else if (evnt == _CONTROL_SLIDER_ORANGE_WHITE)
	{
		channel = active_channels_tab * 8 + 7;
		
		volume = normalize_slider_value(val, channel_volume_max, channels_volume_min);
		/* Change slider value only when it matches the UI slider position */
		volume_slider_gap = channels_volume[channel] - volume;
		if (abs((float)volume_slider_gap) < ((channel_volume_max - channels_volume_min) / 5.0))
		{
			if (channel == 7)
			{
				on_volume_slider_changed_ch_8(volume);
			}
			else
			{
				on_volume_slider_changed_ch_16(volume);
			}
		}	
	}
	else if (evnt == _CONTROL_ENCODER_BLUE_GREEN)
	{
		channel = active_channels_tab * 8;
		
		channels_pan[channel] = 
			update_rotary_encoder_value(channels_pan[channel],
			val,
			&prev_knob_chan_vol_val[channel],
			channels_pan_min,
			channels_pan_max,
			4);
		
		if (channel == 0)
		{
			on_pan_dial_changed_ch_1(channels_pan[0]);
		}
		else
		{
			on_pan_dial_changed_ch_9(channels_pan[8]);
		}
	}
	else if (evnt == _CONTROL_ENCODER_BLUE_RED)
	{
		channel = active_channels_tab * 8 + 1;
		
		channels_pan[channel] = 
			update_rotary_encoder_value(channels_pan[channel],
			val,
			&prev_knob_chan_vol_val[channel],
			channels_pan_min,
			channels_pan_max,
			4);
		
		if (channel == 1)
		{
			on_pan_dial_changed_ch_2(channels_pan[1]);
		}
		else
		{
			on_pan_dial_changed_ch_10(channels_pan[9]);
		}
	}
	else if (evnt == _CONTROL_ENCODER_BLUE_BLUE)
	{
		channel = active_channels_tab * 8 + 2;
		
		channels_pan[channel] = 
			update_rotary_encoder_value(channels_pan[channel],
			val,
			&prev_knob_chan_vol_val[channel],
			channels_pan_min,
			channels_pan_max,
			4);
		
		if (channel == 2)
		{
			on_pan_dial_changed_ch_3(channels_pan[2]);
		}
		else
		{
			on_pan_dial_changed_ch_11(channels_pan[10]);
		}
	}
	else if (evnt == _CONTROL_ENCODER_BLUE_WHITE)
	{
		channel = active_channels_tab * 8 + 3;
		
		channels_pan[channel] = 
			update_rotary_encoder_value(channels_pan[channel],
			val,
			&prev_knob_chan_vol_val[channel],
			channels_pan_min,
			channels_pan_max,
			4);
		
		if (channel == 3)
		{
			on_pan_dial_changed_ch_4(channels_pan[3]);
		}
		else
		{
			on_pan_dial_changed_ch_12(channels_pan[11]);
		}
	}
	else if (evnt == _CONTROL_ENCODER_ORANGE_GREEN)
	{
		channel = active_channels_tab * 8 + 4;
		
		channels_pan[channel] = 
			update_rotary_encoder_value(channels_pan[channel],
			val,
			&prev_knob_chan_vol_val[channel],
			channels_pan_min,
			channels_pan_max,
			4);
		
		if (channel == 4)
		{
			on_pan_dial_changed_ch_5(channels_pan[4]);
		}
		else
		{
			on_pan_dial_changed_ch_13(channels_pan[12]);
		}
	}
	else if (evnt == _CONTROL_ENCODER_ORANGE_RED)
	{
		channel = active_channels_tab * 8 + 5;
		
		channels_pan[channel] = 
			update_rotary_encoder_value(channels_pan[channel],
			val,
			&prev_knob_chan_vol_val[channel],
			channels_pan_min,
			channels_pan_max,
			4);
		
		if (channel == 5)
		{
			on_pan_dial_changed_ch_6(channels_pan[5]);
		}
		else
		{
			on_pan_dial_changed_ch_14(channels_pan[13]);
		}
	}
	else if (evnt == _CONTROL_ENCODER_ORANGE_BLUE)
	{
		channel = active_channels_tab * 8 + 6;
		
		channels_pan[channel] = 
			update_rotary_encoder_value(channels_pan[channel],
			val,
			&prev_knob_chan_vol_val[channel],
			channels_pan_min,
			channels_pan_max,
			4);
		
		if (channel == 6)
		{
			on_pan_dial_changed_ch_7(channels_pan[6]);
		}
		else
		{
			on_pan_dial_changed_ch_15(channels_pan[14]);
		}
	}
	else if (evnt == _CONTROL_ENCODER_ORANGE_WHITE)
	{
		channel = active_channels_tab * 8 + 7;
		
		channels_pan[channel] = 
			update_rotary_encoder_value(channels_pan[channel],
			val,
			&prev_knob_chan_vol_val[channel],
			channels_pan_min,
			channels_pan_max,
			4);
		
		if (channel == 7)
		{
			on_pan_dial_changed_ch_8(channels_pan[7]);
		}
		else
		{
			on_pan_dial_changed_ch_16(channels_pan[15]);
		}
	}
	else if (evnt == _CONTROL_PUSHBUTTON_BLUE_GREEN)
	{
		if (val == 0)
		{
			/* Only when pushbutton is pressed */
			channel = active_channels_tab * 8;
			
			if (channel == 0)
			{
				checked = ui->checkBox_MidiMixerChanStaticVol_1->checkState();
			}
			else
			{
				checked = ui->checkBox_MidiMixerChanStaticVol_9->checkState();
			}
			/* Toggle */
			if (checked == Qt::CheckState::Checked)
			{
				checked = Qt::CheckState::Unchecked;
			}
			else
			{
				checked = Qt::CheckState::Checked;
			}
			
			if (channel == 0)
			{				
				on_static_vol_checkbox_changed_ch_1(checked);
			}
			else
			{
				on_static_vol_checkbox_changed_ch_9(checked);
			}
		}
	}
	else if (evnt == _CONTROL_PUSHBUTTON_BLUE_RED)
	{
		if (val == 0)
		{
			/* Only when pushbutton is pressed */
			channel = active_channels_tab * 8 + 1;
			
			if (channel == 1)
			{
				checked = ui->checkBox_MidiMixerChanStaticVol_2->checkState();
			}
			else
			{
				checked = ui->checkBox_MidiMixerChanStaticVol_10->checkState();
			}
			/* Toggle */
			if (checked == Qt::CheckState::Checked)
			{
				checked = Qt::CheckState::Unchecked;
			}
			else
			{
				checked = Qt::CheckState::Checked;
			}
			
			if (channel == 1)
			{				
				on_static_vol_checkbox_changed_ch_2(checked);
			}
			else
			{
				on_static_vol_checkbox_changed_ch_10(checked);
			}
		}
	}
	else if (evnt == _CONTROL_PUSHBUTTON_BLUE_BLUE)
	{
		if (val == 0)
		{
			/* Only when pushbutton is pressed */
			channel = active_channels_tab * 8 + 2;
			
			if (channel == 2)
			{
				checked = ui->checkBox_MidiMixerChanStaticVol_3->checkState();
			}
			else
			{
				checked = ui->checkBox_MidiMixerChanStaticVol_11->checkState();
			}
			/* Toggle */
			if (checked == Qt::CheckState::Checked)
			{
				checked = Qt::CheckState::Unchecked;
			}
			else
			{
				checked = Qt::CheckState::Checked;
			}
			
			if (channel == 2)
			{				
				on_static_vol_checkbox_changed_ch_3(checked);
			}
			else
			{
				on_static_vol_checkbox_changed_ch_11(checked);
			}
		}
	}
	else if (evnt == _CONTROL_PUSHBUTTON_BLUE_WHITE)
	{
		if (val == 0)
		{
			/* Only when pushbutton is pressed */
			channel = active_channels_tab * 8 + 3;
			
			if (channel == 3)
			{
				checked = ui->checkBox_MidiMixerChanStaticVol_4->checkState();
			}
			else
			{
				checked = ui->checkBox_MidiMixerChanStaticVol_12->checkState();
			}
			/* Toggle */
			if (checked == Qt::CheckState::Checked)
			{
				checked = Qt::CheckState::Unchecked;
			}
			else
			{
				checked = Qt::CheckState::Checked;
			}
			
			if (channel == 3)
			{				
				on_static_vol_checkbox_changed_ch_4(checked);
			}
			else
			{
				on_static_vol_checkbox_changed_ch_12(checked);
			}
		}
	}
	else if (evnt == _CONTROL_PUSHBUTTON_ORANGE_GREEN)
	{
		if (val == 0)
		{
			/* Only when pushbutton is pressed */
			channel = active_channels_tab * 8 + 4;
			
			if (channel == 4)
			{
				checked = ui->checkBox_MidiMixerChanStaticVol_5->checkState();
			}
			else
			{
				checked = ui->checkBox_MidiMixerChanStaticVol_13->checkState();
			}
			/* Toggle */
			if (checked == Qt::CheckState::Checked)
			{
				checked = Qt::CheckState::Unchecked;
			}
			else
			{
				checked = Qt::CheckState::Checked;
			}
			
			if (channel == 4)
			{				
				on_static_vol_checkbox_changed_ch_5(checked);
			}
			else
			{
				on_static_vol_checkbox_changed_ch_13(checked);
			}
		}
	}
	else if (evnt == _CONTROL_PUSHBUTTON_ORANGE_RED)
	{
		if (val == 0)
		{
			/* Only when pushbutton is pressed */
			channel = active_channels_tab * 8 + 5;
			
			if (channel == 5)
			{
				checked = ui->checkBox_MidiMixerChanStaticVol_6->checkState();
			}
			else
			{
				checked = ui->checkBox_MidiMixerChanStaticVol_14->checkState();
			}
			/* Toggle */
			if (checked == Qt::CheckState::Checked)
			{
				checked = Qt::CheckState::Unchecked;
			}
			else
			{
				checked = Qt::CheckState::Checked;
			}
			
			if (channel == 5)
			{				
				on_static_vol_checkbox_changed_ch_6(checked);
			}
			else
			{
				on_static_vol_checkbox_changed_ch_14(checked);
			}
		}
	}
	else if (evnt == _CONTROL_PUSHBUTTON_ORANGE_BLUE)
	{
		if (val == 0)
		{
			/* Only when pushbutton is pressed */
			channel = active_channels_tab * 8 + 6;
			
			if (channel == 6)
			{
				checked = ui->checkBox_MidiMixerChanStaticVol_7->checkState();
			}
			else
			{
				checked = ui->checkBox_MidiMixerChanStaticVol_15->checkState();
			}
			/* Toggle */
			if (checked == Qt::CheckState::Checked)
			{
				checked = Qt::CheckState::Unchecked;
			}
			else
			{
				checked = Qt::CheckState::Checked;
			}
			
			if (channel == 6)
			{				
				on_static_vol_checkbox_changed_ch_7(checked);
			}
			else
			{
				on_static_vol_checkbox_changed_ch_15(checked);
			}
		}
	}
	else if (evnt == _CONTROL_PUSHBUTTON_ORANGE_WHITE)
	{
		if (val == 0)
		{
			/* Only when pushbutton is pressed */
			channel = active_channels_tab * 8 + 7;
			
			if (channel == 7)
			{
				checked = ui->checkBox_MidiMixerChanStaticVol_8->checkState();
			}
			else
			{
				checked = ui->checkBox_MidiMixerChanStaticVol_16->checkState();
			}
			/* Toggle */
			if (checked == Qt::CheckState::Checked)
			{
				checked = Qt::CheckState::Unchecked;
			}
			else
			{
				checked = Qt::CheckState::Checked;
			}
			
			if (channel == 7)
			{				
				on_static_vol_checkbox_changed_ch_8(checked);
			}
			else
			{
				on_static_vol_checkbox_changed_ch_16(checked);
			}
		}
	}
}

void Dialog_MidiMixer::channels_volumes_update_callback(int chan, int vol)
{
	if (chan == 0)
	{
		on_volume_slider_changed_ch_1(vol);
	}
	else if (chan == 1)
	{
		on_volume_slider_changed_ch_2(vol);
	}
	else if (chan == 2)
	{
		on_volume_slider_changed_ch_3(vol);
	}
	else if (chan == 3)
	{
		on_volume_slider_changed_ch_4(vol);
	}
	else if (chan == 4)
	{
		on_volume_slider_changed_ch_5(vol);
	}
	else if (chan == 5)
	{
		on_volume_slider_changed_ch_6(vol);
	}
	else if (chan == 6)
	{
		on_volume_slider_changed_ch_7(vol);
	}
	else if (chan == 7)
	{
		on_volume_slider_changed_ch_8(vol);
	}
	else if (chan == 8)
	{
		on_volume_slider_changed_ch_9(vol);
	}
	else if (chan == 9)
	{
		on_volume_slider_changed_ch_10(vol);
	}
	else if (chan == 10)
	{
		on_volume_slider_changed_ch_11(vol);
	}
	else if (chan == 11)
	{
		on_volume_slider_changed_ch_12(vol);
	}
	else if (chan == 12)
	{
		on_volume_slider_changed_ch_13(vol);
	}
	else if (chan == 13)
	{
		on_volume_slider_changed_ch_14(vol);
	}
	else if (chan == 14)
	{
		on_volume_slider_changed_ch_15(vol);
	}
	else if (chan == 15)
	{
		on_volume_slider_changed_ch_16(vol);
	}
}
void Dialog_MidiMixer::channels_pans_update_callback(int chan, int pan)
{
	
}

void Dialog_MidiMixer::channels_static_volume_update_callback(int chan, bool state)
{
	
}

void Dialog_MidiMixer::start_update_timer(int interval)
{
	QTimer *timer = new QTimer(this);
	connect(timer, SIGNAL(timeout()), this, SLOT(update_gui()));
	timer->start(interval);
}

void Dialog_MidiMixer::timerEvent(QTimerEvent *event)
{
	killTimer(event->timerId());
	start_update_timer(250);
}

void Dialog_MidiMixer::update_gui()
{
	ui->textEdit_MidiMixerChanText_1->setText(channels_programs_names[0]);
	ui->textEdit_MidiMixerChanText_2->setText(channels_programs_names[1]);
	ui->textEdit_MidiMixerChanText_3->setText(channels_programs_names[2]);
	ui->textEdit_MidiMixerChanText_4->setText(channels_programs_names[3]);
	ui->textEdit_MidiMixerChanText_5->setText(channels_programs_names[4]);
	ui->textEdit_MidiMixerChanText_6->setText(channels_programs_names[5]);
	ui->textEdit_MidiMixerChanText_7->setText(channels_programs_names[6]);
	ui->textEdit_MidiMixerChanText_8->setText(channels_programs_names[7]);
	ui->textEdit_MidiMixerChanText_9->setText(channels_programs_names[8]);
	ui->textEdit_MidiMixerChanText_10->setText(channels_programs_names[9]);
	ui->textEdit_MidiMixerChanText_11->setText(channels_programs_names[10]);
	ui->textEdit_MidiMixerChanText_12->setText(channels_programs_names[11]);
	ui->textEdit_MidiMixerChanText_13->setText(channels_programs_names[12]);
	ui->textEdit_MidiMixerChanText_14->setText(channels_programs_names[13]);
	ui->textEdit_MidiMixerChanText_15->setText(channels_programs_names[14]);
	ui->textEdit_MidiMixerChanText_16->setText(channels_programs_names[15]);
}

void Dialog_MidiMixer::channels_program_update_callback(int chan, int program)
{
	/* Currently supporting MIDI GM programs */
	
	if ((program >= 0) && (program <= 128) && (chan >= 0) && (chan < 16))
	{
		channels_programs_names[chan] = QString::fromStdString(midi_instruments_names[program]);		
	}
}

void Dialog_MidiMixer::on_volume_changed(int chan, int vol)
{
	//printf("Channel %i Volume Set to: %i\n", chan, vol);
	
	channels_volume[chan] = vol;
	mod_synth_midi_mixer_set_channel_volume(chan, vol);
}

void Dialog_MidiMixer::on_pan_changed(int chan, int pan)
{
	//printf("Channel %i Pan Set to: %i\n", chan, pan);
	
	channels_pan[chan] = pan;
	mod_synth_midi_mixer_set_channel_pan(chan, pan);
}

void Dialog_MidiMixer::on_static_volume_changed(int chan, bool state)
{
	channels_static_volume[chan] = state;
	mod_synth_midi_mixer_set_channel_static_volume(chan, state);
}

void Dialog_MidiMixer::on_dialog_close()
{
	
	
	hide();
}

void Dialog_MidiMixer::on_volume_slider_changed_ch_1(int vol)
{
	if ((vol < 0) || (vol > 100))
	{
		return; 
	}
	
	ui->verticalSlider_MidiMixerChanVol_1->blockSignals(true);
	ui->verticalSlider_MidiMixerChanVol_1->setValue(vol);
	ui->verticalSlider_MidiMixerChanVol_1->blockSignals(false);
	
	ui->spinBox_MidiMixerChanVol_1->blockSignals(true);
	ui->spinBox_MidiMixerChanVol_1->setValue(vol);
	ui->spinBox_MidiMixerChanVol_1->blockSignals(false);
	
	on_volume_changed(0, vol);
	
	/* Set focus back on the Dialog */
	this->setFocus(Qt::ActiveWindowFocusReason);
}
void Dialog_MidiMixer::on_volume_slider_changed_ch_2(int vol)
{
	if ((vol < 0) || (vol > 100))
	{
		return; 
	}
	
	ui->verticalSlider_MidiMixerChanVol_2->blockSignals(true);
	ui->verticalSlider_MidiMixerChanVol_2->setValue(vol);
	ui->verticalSlider_MidiMixerChanVol_2->blockSignals(false);
	
	ui->spinBox_MidiMixerChanVol_2->blockSignals(true);
	ui->spinBox_MidiMixerChanVol_2->setValue(vol);
	ui->spinBox_MidiMixerChanVol_2->blockSignals(false);
	
	on_volume_changed(1, vol);
	
	/* Set focus back on the Dialog */
	this->setFocus(Qt::ActiveWindowFocusReason);
}

void Dialog_MidiMixer::on_volume_slider_changed_ch_3(int vol)
{
	if ((vol < 0) || (vol > 100))
	{
		return; 
	}
	
	ui->verticalSlider_MidiMixerChanVol_3->blockSignals(true);
	ui->verticalSlider_MidiMixerChanVol_3->setValue(vol);
	ui->verticalSlider_MidiMixerChanVol_3->blockSignals(false);
	
	ui->spinBox_MidiMixerChanVol_3->blockSignals(true);
	ui->spinBox_MidiMixerChanVol_3->setValue(vol);
	ui->spinBox_MidiMixerChanVol_3->blockSignals(false);
	
	on_volume_changed(2, vol);
	
	/* Set focus back on the Dialog */
	this->setFocus(Qt::ActiveWindowFocusReason);
}

void Dialog_MidiMixer::on_volume_slider_changed_ch_4(int vol)
{
	if ((vol < 0) || (vol > 100))
	{
		return; 
	}
	
	ui->verticalSlider_MidiMixerChanVol_4->blockSignals(true);
	ui->verticalSlider_MidiMixerChanVol_4->setValue(vol);
	ui->verticalSlider_MidiMixerChanVol_4->blockSignals(false);
	
	ui->spinBox_MidiMixerChanVol_4->blockSignals(true);
	ui->spinBox_MidiMixerChanVol_4->setValue(vol);
	ui->spinBox_MidiMixerChanVol_4->blockSignals(false);
	
	on_volume_changed(3, vol);
	
	/* Set focus back on the Dialog */
	this->setFocus(Qt::ActiveWindowFocusReason);
}

void Dialog_MidiMixer::on_volume_slider_changed_ch_5(int vol)
{
	if ((vol < 0) || (vol > 100))
	{
		return; 
	}
	
	ui->verticalSlider_MidiMixerChanVol_5->blockSignals(true);
	ui->verticalSlider_MidiMixerChanVol_5->setValue(vol);
	ui->verticalSlider_MidiMixerChanVol_5->blockSignals(false);
	
	ui->spinBox_MidiMixerChanVol_5->blockSignals(true);
	ui->spinBox_MidiMixerChanVol_5->setValue(vol);
	ui->spinBox_MidiMixerChanVol_5->blockSignals(false);
	
	on_volume_changed(4, vol);
	
	/* Set focus back on the Dialog */
	this->setFocus(Qt::ActiveWindowFocusReason);
}

void Dialog_MidiMixer::on_volume_slider_changed_ch_6(int vol)
{
	if ((vol < 0) || (vol > 100))
	{
		return; 
	}
	
	ui->verticalSlider_MidiMixerChanVol_6->blockSignals(true);
	ui->verticalSlider_MidiMixerChanVol_6->setValue(vol);
	ui->verticalSlider_MidiMixerChanVol_6->blockSignals(false);
	
	ui->spinBox_MidiMixerChanVol_6->blockSignals(true);
	ui->spinBox_MidiMixerChanVol_6->setValue(vol);
	ui->spinBox_MidiMixerChanVol_6->blockSignals(false);
	
	on_volume_changed(5, vol);
	
	/* Set focus back on the Dialog */
	this->setFocus(Qt::ActiveWindowFocusReason);
}

void Dialog_MidiMixer::on_volume_slider_changed_ch_7(int vol)
{
	if ((vol < 0) || (vol > 100))
	{
		return; 
	}
	
	ui->verticalSlider_MidiMixerChanVol_7->blockSignals(true);
	ui->verticalSlider_MidiMixerChanVol_7->setValue(vol);
	ui->verticalSlider_MidiMixerChanVol_7->blockSignals(false);
	
	ui->spinBox_MidiMixerChanVol_7->blockSignals(true);
	ui->spinBox_MidiMixerChanVol_7->setValue(vol);
	ui->spinBox_MidiMixerChanVol_7->blockSignals(false);
	
	on_volume_changed(6, vol);
	
	/* Set focus back on the Dialog */
	this->setFocus(Qt::ActiveWindowFocusReason);
}

void Dialog_MidiMixer::on_volume_slider_changed_ch_8(int vol)
{
	if ((vol < 0) || (vol > 100))
	{
		return; 
	}
	
	ui->verticalSlider_MidiMixerChanVol_8->blockSignals(true);
	ui->verticalSlider_MidiMixerChanVol_8->setValue(vol);
	ui->verticalSlider_MidiMixerChanVol_8->blockSignals(false);
	
	ui->spinBox_MidiMixerChanVol_8->blockSignals(true);
	ui->spinBox_MidiMixerChanVol_8->setValue(vol);
	ui->spinBox_MidiMixerChanVol_8->blockSignals(false);
	
	on_volume_changed(7, vol);
	
	/* Set focus back on the Dialog */
	this->setFocus(Qt::ActiveWindowFocusReason);
}

void Dialog_MidiMixer::on_volume_slider_changed_ch_9(int vol)
{
	if ((vol < 0) || (vol > 100))
	{
		return; 
	}
	
	ui->verticalSlider_MidiMixerChanVol_9->blockSignals(true);
	ui->verticalSlider_MidiMixerChanVol_9->setValue(vol);
	ui->verticalSlider_MidiMixerChanVol_9->blockSignals(false);
	
	ui->spinBox_MidiMixerChanVol_9->blockSignals(true);
	ui->spinBox_MidiMixerChanVol_9->setValue(vol);
	ui->spinBox_MidiMixerChanVol_9->blockSignals(false);
	
	on_volume_changed(8, vol);
	
	/* Set focus back on the Dialog */
	this->setFocus(Qt::ActiveWindowFocusReason);
}

void Dialog_MidiMixer::on_volume_slider_changed_ch_10(int vol)
{
	if ((vol < 0) || (vol > 100))
	{
		return; 
	}
	
	ui->verticalSlider_MidiMixerChanVol_10->blockSignals(true);
	ui->verticalSlider_MidiMixerChanVol_10->setValue(vol);
	ui->verticalSlider_MidiMixerChanVol_10->blockSignals(false);
	
	ui->spinBox_MidiMixerChanVol_10->blockSignals(true);
	ui->spinBox_MidiMixerChanVol_10->setValue(vol);
	ui->spinBox_MidiMixerChanVol_10->blockSignals(false);
	
	on_volume_changed(9, vol);
	
	/* Set focus back on the Dialog */
	this->setFocus(Qt::ActiveWindowFocusReason);
}

void Dialog_MidiMixer::on_volume_slider_changed_ch_11(int vol)
{
	if ((vol < 0) || (vol > 100))
	{
		return; 
	}
	
	ui->verticalSlider_MidiMixerChanVol_11->blockSignals(true);
	ui->verticalSlider_MidiMixerChanVol_11->setValue(vol);
	ui->verticalSlider_MidiMixerChanVol_11->blockSignals(false);
	
	ui->spinBox_MidiMixerChanVol_11->blockSignals(true);
	ui->spinBox_MidiMixerChanVol_11->setValue(vol);
	ui->spinBox_MidiMixerChanVol_11->blockSignals(false);
	
	on_volume_changed(10, vol);
	
	/* Set focus back on the Dialog */
	this->setFocus(Qt::ActiveWindowFocusReason);
}

void Dialog_MidiMixer::on_volume_slider_changed_ch_12(int vol)
{
	if ((vol < 0) || (vol > 100))
	{
		return; 
	}
	
	ui->verticalSlider_MidiMixerChanVol_12->blockSignals(true);
	ui->verticalSlider_MidiMixerChanVol_12->setValue(vol);
	ui->verticalSlider_MidiMixerChanVol_12->blockSignals(false);
	
	ui->spinBox_MidiMixerChanVol_12->blockSignals(true);
	ui->spinBox_MidiMixerChanVol_12->setValue(vol);
	ui->spinBox_MidiMixerChanVol_12->blockSignals(false);
	
	on_volume_changed(11, vol);
	
	/* Set focus back on the Dialog */
	this->setFocus(Qt::ActiveWindowFocusReason);
}

void Dialog_MidiMixer::on_volume_slider_changed_ch_13(int vol)
{
	if ((vol < 0) || (vol > 100))
	{
		return; 
	}
	
	ui->verticalSlider_MidiMixerChanVol_13->blockSignals(true);
	ui->verticalSlider_MidiMixerChanVol_13->setValue(vol);
	ui->verticalSlider_MidiMixerChanVol_13->blockSignals(false);
	
	ui->spinBox_MidiMixerChanVol_13->blockSignals(true);
	ui->spinBox_MidiMixerChanVol_13->setValue(vol);
	ui->spinBox_MidiMixerChanVol_13->blockSignals(false);
	
	on_volume_changed(12, vol);
	
	/* Set focus back on the Dialog */
	this->setFocus(Qt::ActiveWindowFocusReason);
}

void Dialog_MidiMixer::on_volume_slider_changed_ch_14(int vol)
{
	if ((vol < 0) || (vol > 100))
	{
		return; 
	}
	
	ui->verticalSlider_MidiMixerChanVol_14->blockSignals(true);
	ui->verticalSlider_MidiMixerChanVol_14->setValue(vol);
	ui->verticalSlider_MidiMixerChanVol_14->blockSignals(false);
	
	ui->spinBox_MidiMixerChanVol_14->blockSignals(true);
	ui->spinBox_MidiMixerChanVol_14->setValue(vol);
	ui->spinBox_MidiMixerChanVol_14->blockSignals(false);
	
	on_volume_changed(13, vol);
	
	/* Set focus back on the Dialog */
	this->setFocus(Qt::ActiveWindowFocusReason);
}

void Dialog_MidiMixer::on_volume_slider_changed_ch_15(int vol)
{
	if ((vol < 0) || (vol > 100))
	{
		return; 
	}
	
	ui->verticalSlider_MidiMixerChanVol_15->blockSignals(true);
	ui->verticalSlider_MidiMixerChanVol_15->setValue(vol);
	ui->verticalSlider_MidiMixerChanVol_15->blockSignals(false);
	
	ui->spinBox_MidiMixerChanVol_15->blockSignals(true);
	ui->spinBox_MidiMixerChanVol_15->setValue(vol);
	ui->spinBox_MidiMixerChanVol_15->blockSignals(false);
	
	on_volume_changed(14, vol);
	
	/* Set focus back on the Dialog */
	this->setFocus(Qt::ActiveWindowFocusReason);
}

void Dialog_MidiMixer::on_volume_slider_changed_ch_16(int vol)
{
	if ((vol < 0) || (vol > 100))
	{
		return; 
	}
	
	ui->verticalSlider_MidiMixerChanVol_16->blockSignals(true);
	ui->verticalSlider_MidiMixerChanVol_16->setValue(vol);
	ui->verticalSlider_MidiMixerChanVol_16->blockSignals(false);
	
	ui->spinBox_MidiMixerChanVol_16->blockSignals(true);
	ui->spinBox_MidiMixerChanVol_16->setValue(vol);
	ui->spinBox_MidiMixerChanVol_16->blockSignals(false);
	
	on_volume_changed(15, vol);
	
	/* Set focus back on the Dialog */
	this->setFocus(Qt::ActiveWindowFocusReason);
}

void Dialog_MidiMixer::on_volume_spinbox_changed_ch_1(int vol)
{
	on_volume_changed(0, vol);
}
void Dialog_MidiMixer::on_volume_spinbox_changed_ch_2(int vol)
{
	on_volume_changed(1, vol);
}

void Dialog_MidiMixer::on_volume_spinbox_changed_ch_3(int vol)
{
	on_volume_changed(2, vol);
}

void Dialog_MidiMixer::on_volume_spinbox_changed_ch_4(int vol)
{
	on_volume_changed(3, vol);
}

void Dialog_MidiMixer::on_volume_spinbox_changed_ch_5(int vol)
{
	on_volume_changed(4, vol);
}

void Dialog_MidiMixer::on_volume_spinbox_changed_ch_6(int vol)
{
	on_volume_changed(5, vol);
}

void Dialog_MidiMixer::on_volume_spinbox_changed_ch_7(int vol)
{
	on_volume_changed(6, vol);
}

void Dialog_MidiMixer::on_volume_spinbox_changed_ch_8(int vol)
{
	on_volume_changed(7, vol);
}

void Dialog_MidiMixer::on_volume_spinbox_changed_ch_9(int vol)
{
	on_volume_changed(8, vol);
}

void Dialog_MidiMixer::on_volume_spinbox_changed_ch_10(int vol)
{
	on_volume_changed(9, vol);
}

void Dialog_MidiMixer::on_volume_spinbox_changed_ch_11(int vol)
{
	on_volume_changed(10, vol);
}

void Dialog_MidiMixer::on_volume_spinbox_changed_ch_12(int vol)
{
	on_volume_changed(11, vol);
}

void Dialog_MidiMixer::on_volume_spinbox_changed_ch_13(int vol)
{
	on_volume_changed(12, vol);
}

void Dialog_MidiMixer::on_volume_spinbox_changed_ch_14(int vol)
{
	on_volume_changed(13, vol);
}

void Dialog_MidiMixer::on_volume_spinbox_changed_ch_15(int vol)
{
	on_volume_changed(14, vol);
}

void Dialog_MidiMixer::on_volume_spinbox_changed_ch_16(int vol)
{
	on_volume_changed(15, vol);
}

void Dialog_MidiMixer::on_pan_dial_changed_ch_1(int pan)
{
	ui->dial_MidiMixerChanPan_1->blockSignals(true);
	ui->dial_MidiMixerChanPan_1->setValue(pan);
	ui->dial_MidiMixerChanPan_1->blockSignals(false);
	
	on_pan_changed(0, pan);
}

void Dialog_MidiMixer::on_pan_dial_changed_ch_2(int pan)
{
	ui->dial_MidiMixerChanPan_2->blockSignals(true);
	ui->dial_MidiMixerChanPan_2->setValue(pan);
	ui->dial_MidiMixerChanPan_2->blockSignals(false);
	
	on_pan_changed(1, pan);
}

void Dialog_MidiMixer::on_pan_dial_changed_ch_3(int pan)
{
	ui->dial_MidiMixerChanPan_3->blockSignals(true);
	ui->dial_MidiMixerChanPan_3->setValue(pan);
	ui->dial_MidiMixerChanPan_3->blockSignals(false);
	
	on_pan_changed(2, pan);
}

void Dialog_MidiMixer::on_pan_dial_changed_ch_4(int pan)
{
	ui->dial_MidiMixerChanPan_4->blockSignals(true);
	ui->dial_MidiMixerChanPan_4->setValue(pan);
	ui->dial_MidiMixerChanPan_4->blockSignals(false);
	
	on_pan_changed(3, pan);
}

void Dialog_MidiMixer::on_pan_dial_changed_ch_5(int pan)
{
	ui->dial_MidiMixerChanPan_5->blockSignals(true);
	ui->dial_MidiMixerChanPan_5->setValue(pan);
	ui->dial_MidiMixerChanPan_5->blockSignals(false);
	
	on_pan_changed(4, pan);
}

void Dialog_MidiMixer::on_pan_dial_changed_ch_6(int pan)
{
	ui->dial_MidiMixerChanPan_6->blockSignals(true);
	ui->dial_MidiMixerChanPan_6->setValue(pan);
	ui->dial_MidiMixerChanPan_6->blockSignals(false);
	
	on_pan_changed(5, pan);
}

void Dialog_MidiMixer::on_pan_dial_changed_ch_7(int pan)
{
	ui->dial_MidiMixerChanPan_7->blockSignals(true);
	ui->dial_MidiMixerChanPan_7->setValue(pan);
	ui->dial_MidiMixerChanPan_7->blockSignals(false);
	
	on_pan_changed(6, pan);
}

void Dialog_MidiMixer::on_pan_dial_changed_ch_8(int pan)
{
	ui->dial_MidiMixerChanPan_8->blockSignals(true);
	ui->dial_MidiMixerChanPan_8->setValue(pan);
	ui->dial_MidiMixerChanPan_8->blockSignals(false);
	
	on_pan_changed(7, pan);
}

void Dialog_MidiMixer::on_pan_dial_changed_ch_9(int pan)
{
	ui->dial_MidiMixerChanPan_9->blockSignals(true);
	ui->dial_MidiMixerChanPan_9->setValue(pan);
	ui->dial_MidiMixerChanPan_9->blockSignals(false);
	
	on_pan_changed(8, pan);
}

void Dialog_MidiMixer::on_pan_dial_changed_ch_10(int pan)
{
	ui->dial_MidiMixerChanPan_10->blockSignals(true);
	ui->dial_MidiMixerChanPan_10->setValue(pan);
	ui->dial_MidiMixerChanPan_10->blockSignals(false);
	
	on_pan_changed(9, pan);
}

void Dialog_MidiMixer::on_pan_dial_changed_ch_11(int pan)
{
	ui->dial_MidiMixerChanPan_11->blockSignals(true);
	ui->dial_MidiMixerChanPan_11->setValue(pan);
	ui->dial_MidiMixerChanPan_11->blockSignals(false);
	
	on_pan_changed(10, pan);
}

void Dialog_MidiMixer::on_pan_dial_changed_ch_12(int pan)
{
	ui->dial_MidiMixerChanPan_12->blockSignals(true);
	ui->dial_MidiMixerChanPan_12->setValue(pan);
	ui->dial_MidiMixerChanPan_12->blockSignals(false);
	
	on_pan_changed(11, pan);
}

void Dialog_MidiMixer::on_pan_dial_changed_ch_13(int pan)
{
	ui->dial_MidiMixerChanPan_13->blockSignals(true);
	ui->dial_MidiMixerChanPan_13->setValue(pan);
	ui->dial_MidiMixerChanPan_13->blockSignals(false);
	
	on_pan_changed(12, pan);
}

void Dialog_MidiMixer::on_pan_dial_changed_ch_14(int pan)
{
	ui->dial_MidiMixerChanPan_14->blockSignals(true);
	ui->dial_MidiMixerChanPan_14->setValue(pan);
	ui->dial_MidiMixerChanPan_14->blockSignals(false);
	
	on_pan_changed(13, pan);
}

void Dialog_MidiMixer::on_pan_dial_changed_ch_15(int pan)
{
	ui->dial_MidiMixerChanPan_15->blockSignals(true);
	ui->dial_MidiMixerChanPan_15->setValue(pan);
	ui->dial_MidiMixerChanPan_15->blockSignals(false);
	
	on_pan_changed(14, pan);
}

void Dialog_MidiMixer::on_pan_dial_changed_ch_16(int pan)
{
	ui->dial_MidiMixerChanPan_16->blockSignals(true);
	ui->dial_MidiMixerChanPan_16->setValue(pan);
	ui->dial_MidiMixerChanPan_16->blockSignals(false);
	
	on_pan_changed(15, pan);
}

void Dialog_MidiMixer::on_static_vol_checkbox_changed_ch_1(bool state)
{
	ui->checkBox_MidiMixerChanStaticVol_1->blockSignals(true);
	if (state)
	{
		ui->checkBox_MidiMixerChanStaticVol_1->setCheckState(Qt::Checked);
	}
	else
	{
		ui->checkBox_MidiMixerChanStaticVol_1->setCheckState(Qt::Unchecked);
	}
	ui->checkBox_MidiMixerChanStaticVol_1->blockSignals(false);
	
	on_static_volume_changed(0, state);
}

void Dialog_MidiMixer::on_static_vol_checkbox_changed_ch_2(bool state)
{
	ui->checkBox_MidiMixerChanStaticVol_2->blockSignals(true);
	if (state)
	{
		ui->checkBox_MidiMixerChanStaticVol_2->setCheckState(Qt::Checked);
	}
	else
	{
		ui->checkBox_MidiMixerChanStaticVol_2->setCheckState(Qt::Unchecked);
	}
	ui->checkBox_MidiMixerChanStaticVol_2->blockSignals(false);
	
	on_static_volume_changed(1, state);
}

void Dialog_MidiMixer::on_static_vol_checkbox_changed_ch_3(bool state)
{
	ui->checkBox_MidiMixerChanStaticVol_3->blockSignals(true);
	if (state)
	{
		ui->checkBox_MidiMixerChanStaticVol_3->setCheckState(Qt::Checked);
	}
	else
	{
		ui->checkBox_MidiMixerChanStaticVol_3->setCheckState(Qt::Unchecked);
	}
	ui->checkBox_MidiMixerChanStaticVol_3->blockSignals(false);
	
	on_static_volume_changed(2, state);
}

void Dialog_MidiMixer::on_static_vol_checkbox_changed_ch_4(bool state)
{
	ui->checkBox_MidiMixerChanStaticVol_4->blockSignals(true);
	if (state)
	{
		ui->checkBox_MidiMixerChanStaticVol_4->setCheckState(Qt::Checked);
	}
	else
	{
		ui->checkBox_MidiMixerChanStaticVol_4->setCheckState(Qt::Unchecked);
	}
	ui->checkBox_MidiMixerChanStaticVol_4->blockSignals(false);
	
	on_static_volume_changed(3, state);
}

void Dialog_MidiMixer::on_static_vol_checkbox_changed_ch_5(bool state)
{
	ui->checkBox_MidiMixerChanStaticVol_5->blockSignals(true);
	if (state)
	{
		ui->checkBox_MidiMixerChanStaticVol_5->setCheckState(Qt::Checked);
	}
	else
	{
		ui->checkBox_MidiMixerChanStaticVol_5->setCheckState(Qt::Unchecked);
	}
	ui->checkBox_MidiMixerChanStaticVol_5->blockSignals(false);
	
	on_static_volume_changed(4, state);
}

void Dialog_MidiMixer::on_static_vol_checkbox_changed_ch_6(bool state)
{
	ui->checkBox_MidiMixerChanStaticVol_6->blockSignals(true);
	if (state)
	{
		ui->checkBox_MidiMixerChanStaticVol_6->setCheckState(Qt::Checked);
	}
	else
	{
		ui->checkBox_MidiMixerChanStaticVol_6->setCheckState(Qt::Unchecked);
	}
	ui->checkBox_MidiMixerChanStaticVol_6->blockSignals(false);
	
	on_static_volume_changed(5, state);
}

void Dialog_MidiMixer::on_static_vol_checkbox_changed_ch_7(bool state)
{
	ui->checkBox_MidiMixerChanStaticVol_7->blockSignals(true);
	if (state)
	{
		ui->checkBox_MidiMixerChanStaticVol_7->setCheckState(Qt::Checked);
	}
	else
	{
		ui->checkBox_MidiMixerChanStaticVol_7->setCheckState(Qt::Unchecked);
	}
	ui->checkBox_MidiMixerChanStaticVol_7->blockSignals(false);
	
	on_static_volume_changed(6, state);
}

void Dialog_MidiMixer::on_static_vol_checkbox_changed_ch_8(bool state)
{
	ui->checkBox_MidiMixerChanStaticVol_8->blockSignals(true);
	if (state)
	{
		ui->checkBox_MidiMixerChanStaticVol_8->setCheckState(Qt::Checked);
	}
	else
	{
		ui->checkBox_MidiMixerChanStaticVol_8->setCheckState(Qt::Unchecked);
	}
	ui->checkBox_MidiMixerChanStaticVol_8->blockSignals(false);
	
	on_static_volume_changed(7, state);
}

void Dialog_MidiMixer::on_static_vol_checkbox_changed_ch_9(bool state)
{
	ui->checkBox_MidiMixerChanStaticVol_9->blockSignals(true);
	if (state)
	{
		ui->checkBox_MidiMixerChanStaticVol_9->setCheckState(Qt::Checked);
	}
	else
	{
		ui->checkBox_MidiMixerChanStaticVol_9->setCheckState(Qt::Unchecked);
	}
	ui->checkBox_MidiMixerChanStaticVol_9->blockSignals(false);
	
	on_static_volume_changed(8, state);
}

void Dialog_MidiMixer::on_static_vol_checkbox_changed_ch_10(bool state)
{
	ui->checkBox_MidiMixerChanStaticVol_10->blockSignals(true);
	if (state)
	{
		ui->checkBox_MidiMixerChanStaticVol_10->setCheckState(Qt::Checked);
	}
	else
	{
		ui->checkBox_MidiMixerChanStaticVol_10->setCheckState(Qt::Unchecked);
	}
	ui->checkBox_MidiMixerChanStaticVol_10->blockSignals(false);
	
	on_static_volume_changed(9, state);
}

void Dialog_MidiMixer::on_static_vol_checkbox_changed_ch_11(bool state)
{
	ui->checkBox_MidiMixerChanStaticVol_11->blockSignals(true);
	if (state)
	{
		ui->checkBox_MidiMixerChanStaticVol_11->setCheckState(Qt::Checked);
	}
	else
	{
		ui->checkBox_MidiMixerChanStaticVol_11->setCheckState(Qt::Unchecked);
	}
	ui->checkBox_MidiMixerChanStaticVol_11->blockSignals(false);
	
	on_static_volume_changed(10, state);
}

void Dialog_MidiMixer::on_static_vol_checkbox_changed_ch_12(bool state)
{
	ui->checkBox_MidiMixerChanStaticVol_12->blockSignals(true);
	if (state)
	{
		ui->checkBox_MidiMixerChanStaticVol_12->setCheckState(Qt::Checked);
	}
	else
	{
		ui->checkBox_MidiMixerChanStaticVol_12->setCheckState(Qt::Unchecked);
	}
	ui->checkBox_MidiMixerChanStaticVol_12->blockSignals(false);
	
	on_static_volume_changed(11, state);
}

void Dialog_MidiMixer::on_static_vol_checkbox_changed_ch_13(bool state)
{
	ui->checkBox_MidiMixerChanStaticVol_13->blockSignals(true);
	if (state)
	{
		ui->checkBox_MidiMixerChanStaticVol_13->setCheckState(Qt::Checked);
	}
	else
	{
		ui->checkBox_MidiMixerChanStaticVol_13->setCheckState(Qt::Unchecked);
	}
	ui->checkBox_MidiMixerChanStaticVol_13->blockSignals(false);
	
	on_static_volume_changed(12, state);
}

void Dialog_MidiMixer::on_static_vol_checkbox_changed_ch_14(bool state)
{
	ui->checkBox_MidiMixerChanStaticVol_14->blockSignals(true);
	if (state)
	{
		ui->checkBox_MidiMixerChanStaticVol_14->setCheckState(Qt::Checked);
	}
	else
	{
		ui->checkBox_MidiMixerChanStaticVol_14->setCheckState(Qt::Unchecked);
	}
	ui->checkBox_MidiMixerChanStaticVol_14->blockSignals(false);
	
	on_static_volume_changed(13, state);
}

void Dialog_MidiMixer::on_static_vol_checkbox_changed_ch_15(bool state)
{
	ui->checkBox_MidiMixerChanStaticVol_15->blockSignals(true);
	if (state)
	{
		ui->checkBox_MidiMixerChanStaticVol_15->setCheckState(Qt::Checked);
	}
	else
	{
		ui->checkBox_MidiMixerChanStaticVol_15->setCheckState(Qt::Unchecked);
	}
	ui->checkBox_MidiMixerChanStaticVol_15->blockSignals(false);
	
	on_static_volume_changed(14, state);
}

void Dialog_MidiMixer::on_static_vol_checkbox_changed_ch_16(bool state)
{
	ui->checkBox_MidiMixerChanStaticVol_16->blockSignals(true);
	if (state)
	{
		ui->checkBox_MidiMixerChanStaticVol_16->setCheckState(Qt::Checked);
	}
	else
	{
		ui->checkBox_MidiMixerChanStaticVol_16->setCheckState(Qt::Unchecked);
	}
	ui->checkBox_MidiMixerChanStaticVol_16->blockSignals(false);
	
	on_static_volume_changed(15, state);
}

