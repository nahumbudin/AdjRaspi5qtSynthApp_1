/**
* @file		Dialog_AdjFluidSynth.cpp
*	@author		Nahum Budin
*	@date		13-Jul-2024
*	@version	1.0
*
*	@brief		Adj FluidSynth control dialog
*
*/

#include <string>

#include <QMessageBox>
#include <QFileDialog>

#include "utils.h"

#include "MainWindow.h"
#include "Dialog_AdjFluidSynth.h"
#include "ui_Dialog_AdjFluidSynth.h"

Dialog_AdjFluidSynth *Dialog_AdjFluidSynth::dialog_adj_fluid_synth_instance = NULL;

void fluid_control_box_event_update_ui_callback_wrapper(int evnt, uint16_t val)
{
	Dialog_AdjFluidSynth::get_instance()->control_box_ui_update_callback(evnt, val);
}

void fluid_update_ui_callback_wrapper()
{
	Dialog_AdjFluidSynth::get_instance()->get_active_settings_values();
}

Dialog_AdjFluidSynth::Dialog_AdjFluidSynth(QWidget *parent)
	: QDialog(parent)
	, ui(new Ui::Dialog_AdjFluidSynth)
{
	ui->setupUi(this);
	dialog_adj_fluid_synth_instance = this;
	
	ui->comboBox_adjFluidSynth_Chorus_Type->addItem("Sine");
	ui->comboBox_adjFluidSynth_Chorus_Type->addItem("Triangle");
	
	mod_synth_fluid_synth_register_ui_update_callback(&fluid_update_ui_callback_wrapper);
	
	mod_synth_register_callback_control_box_event_update_ui(
		&fluid_control_box_event_update_ui_callback_wrapper);
	
	active_preset = 0;
	set_default_settings_values(false); 
	
	close_event_callback_ptr = NULL;
	
	preset_radio_buttons[0] = ui->radioButton_Preset_1;
	preset_radio_buttons[1] = ui->radioButton_Preset_2;
	preset_radio_buttons[2] = ui->radioButton_Preset_3;
	
	connect(ui->dial_adjFluidSynth_Reverb_Room,
		SIGNAL(valueChanged(int)),
		this,
		SLOT(reverb_room_size_changed(int)));
	
	connect(ui->dial_adjFluidSynth_Reverb_Damp,
		SIGNAL(valueChanged(int)),
		this,
		SLOT(reverb_damp_changed(int)));
	
	connect(ui->dial_adjFluidSynth_Reverb_Width,
		SIGNAL(valueChanged(int)),
		this,
		SLOT(reverb_width_changed(int)));
	
	connect(ui->dial_adjFluidSynth_Reverb_Level,
		SIGNAL(valueChanged(int)),
		this,
		SLOT(reverb_level_changed(int)));
	
	connect(ui->dial_adjFluidSynth_Chorus_N,
		SIGNAL(valueChanged(int)),
		this,
		SLOT(chorus_number_changed(int)));
	
	connect(ui->dial_adjFluidSynth_Chorus_Level,
		SIGNAL(valueChanged(int)),
		this,
		SLOT(chorus_level_changed(int)));
	
	connect(ui->dial_adjFluidSynth_Chorus_Speed,
		SIGNAL(valueChanged(int)),
		this,
		SLOT(chorus_speed_changed(int)));
	
	connect(ui->dial_adjFluidSynth_Chorus_Depth,
		SIGNAL(valueChanged(int)),
		this,
		SLOT(chorus_depth_changed(int)));
	
	
	connect(ui->spinBox_adjFluidSynth_Reverb_Room,
		SIGNAL(valueChanged(int)),
		this,
		SLOT(reverb_room_size_changed(int)));
	
	connect(ui->spinBox_adjFluidSynth_Reverb_Damp,
		SIGNAL(valueChanged(int)),
		this,
		SLOT(reverb_damp_changed(int)));
	
	connect(ui->spinBox_adjFluidSynth_Reverb_Width,
		SIGNAL(valueChanged(int)),
		this,
		SLOT(reverb_width_changed(int)));
	
	connect(ui->spinBox_adjFluidSynth_Reverb_Level,
		SIGNAL(valueChanged(int)),
		this,
		SLOT(reverb_level_changed(int)));
	
	connect(ui->spinBox_adjFluidSynth_Chorus_N,
		SIGNAL(valueChanged(int)),
		this,
		SLOT(chorus_number_changed(int)));
	
	connect(ui->spinBox_adjFluidSynth_Chorus_Level,
		SIGNAL(valueChanged(int)),
		this,
		SLOT(chorus_level_changed(int)));
	
	connect(ui->spinBox_adjFluidSynth_Chorus_Speed,
		SIGNAL(valueChanged(int)),
		this,
		SLOT(chorus_speed_changed(int)));
	
	connect(ui->spinBox_adjFluidSynth_Chorus_Depth,
		SIGNAL(valueChanged(int)),
		this,
		SLOT(chorus_depth_changed(int)));
	
	connect(ui->verticalSlider_adjFluidSynth_Gain,
		SIGNAL(valueChanged(int)),
		this,
		SLOT(fluid_gain_changed(int)));
	
	connect(ui->checkBox_adjFluidSynth_Reverb_Active,
		SIGNAL(toggled(bool)),
		this,
		SLOT(reverb_activation_changed(bool)));
	
	connect(ui->checkBox_adjFluidSynth_Chorus_Active,
		SIGNAL(toggled(bool)),
		this,
		SLOT(chorus_activation_changed(bool)));
	
	connect(ui->comboBox_adjFluidSynth_Chorus_Type,
		SIGNAL(currentIndexChanged(int)),
		this,
		SLOT(chorus_waveform_changed(int)));
	
	connect(ui->pushButton_adjFluidSynth_Close,
		SIGNAL(clicked()),
		this,
		SLOT(on_dialog_close()));
	
	connect(ui->pushButton_adjFluidSynth_Channels,
		SIGNAL(clicked()),
		this,
		SLOT(on_module_channels_clicked()));
	
	connect(ui->pushButton_adjFluidSynth_Default_settings,
		SIGNAL(clicked()),
		this,
		SLOT(on_default_settings_clicked()));
	
	connect(ui->pushButton_adjFluidSynth_Load_preset,
		SIGNAL(clicked()),
		this,
		SLOT(on_load_presets_clicked()));
	
	connect(ui->pushButton_adjFluidSynth_Save_preset,
		SIGNAL(clicked()),
		this,
		SLOT(on_save_presets_clicked()));
	
	connect(ui->radioButton_Preset_1,
		SIGNAL(clicked(bool)),
		this,
		SLOT(on_preset_1_selected(bool)));
	
	connect(ui->radioButton_Preset_2,
		SIGNAL(clicked(bool)),
		this,
		SLOT(on_preset_2_selected(bool)));
	
	connect(ui->radioButton_Preset_3,
		SIGNAL(clicked(bool)),
		this,
		SLOT(on_preset_3_selected(bool)));

	//update();
	mod_synth_fluid_synth_activate_ui_update_callback();
	
	/* Set focus on the Dialog */
	this->setFocus(Qt::ActiveWindowFocusReason);
	
	MainWindow::get_instance()->register_active_dialog(this);
}

Dialog_AdjFluidSynth::~Dialog_AdjFluidSynth()
{
	
}

Dialog_AdjFluidSynth *Dialog_AdjFluidSynth::get_instance(QWidget *parent)
{
	if (dialog_adj_fluid_synth_instance == NULL)
	{
		dialog_adj_fluid_synth_instance = new Dialog_AdjFluidSynth(parent);
	}
	
	return dialog_adj_fluid_synth_instance;
}

void Dialog_AdjFluidSynth::closeEvent(QCloseEvent *event)
{
	if (close_event_callback_ptr != NULL)
	{
		close_event_callback_ptr();
	}
	
	hide();
}

void Dialog_AdjFluidSynth::control_box_ui_update_callback(int evnt, uint16_t val)
{
	static int prev_knob_reverb_room_size_val = 64;
	static int prev_knob_reverb_damp_val = 64;
	static int prev_knob_reverb_width_val = 64;
	static int prev_knob_reverb_level_val = 64;
	static int prev_knob_chorus_number_val = 64;
	static int prev_knob_chorus_level_val = 64;
	static int prev_knob_chorus_speed_val = 64;
	static int prev_knob_chorus_depth_val = 64;
	static int prev_knob_chorus_waveform_val = 0;
	
	int gain_slider_gap, norm_gain;
	
	if (!this->hasFocus())
	{
		return;
	}
	
	if (evnt == _CONTROL_PUSHBUTTON_BLUE_BLACK)
	{
		/* En/Dis Reverb */
		if (val == 0)
		{
			/* Only when pressed */
			Qt::CheckState selected = ui->checkBox_adjFluidSynth_Reverb_Active->checkState();
			if (selected == Qt::CheckState::Checked)
			{
				/* Toggle */
				reverb_activation_changed(false);
				reverb_activation = false;
			}
			else
			{
				reverb_activation_changed(true);
				reverb_activation = true;
			}
		}
	}
	else if (evnt == _CONTROL_PUSHBUTTON_BLUE_GREEN)
	{
		/* Defaule Settings */
		if (val == 0)
		{
			/* Only when pressed */
			
		}
	}
	else if (evnt == _CONTROL_PUSHBUTTON_BLUE_RED)
	{
		/* Save */
		if (val == 0)
		{
			/* Only when pressed */
			
		}
	}
	else if (evnt == _CONTROL_PUSHBUTTON_BLUE_BLUE)
	{
		/* Load */
		if (val == 0)
		{
			/* Only when pressed */
			
		}
	}
	else if (evnt == _CONTROL_PUSHBUTTON_BLUE_WHITE)
	{
		/* Channels */
		if (val == 0)
		{
			/* Only when pressed */
			on_module_channels_clicked();
		}
	}
	else if (evnt == _CONTROL_PUSHBUTTON_BLUE_YELLOW)
	{
		/* Close */
		if (val == 0)
		{
			/* Only when pressed */
			
		}
	}
	else if (evnt == _CONTROL_PUSHBUTTON_ORANGE_BLACK)
	{
		/* En/Dis Chorus */
		if (val == 0)
		{
			/* Only when pressed */
			Qt::CheckState selected = ui->checkBox_adjFluidSynth_Chorus_Active->checkState();
			if (selected == Qt::CheckState::Checked)
			{
				/* Toggle */
				chorus_activation_changed(false);
				chorus_activation = false;
			}
			else
			{
				chorus_activation_changed(true);
				chorus_activation = true;
			}
		}
	}
	else if (evnt == _CONTROL_PUSHBUTTON_ORANGE_GREEN)
	{
		/* Preset 2 */
		if (val == 0)
		{
			/* Only when pressed */
			
		}
	}
	else if (evnt == _CONTROL_PUSHBUTTON_ORANGE_RED)
	{
		/* Preset 3 */
		if (val == 0)
		{
			/* Only when pressed */
			
		}
	}
	else if (evnt == _CONTROL_PUSHBUTTON_ORANGE_BLUE)
	{
		/* Load */
		if (val == 0)
		{
			/* Only when pressed */
			
		}
	}
	else if (evnt == _CONTROL_PUSHBUTTON_ORANGE_WHITE)
	{
		/* Preset 1 */
		if (val == 0)
		{
			/* Only when pressed */
			
		}
	}
	else if(evnt == _CONTROL_ENCODER_PUSHBUTTON_ORANGE_YELLOW)
	{
		/* Select chorus waveform */
		chorus_waveform_select_changed(val);
	}
	else if (evnt == _CONTROL_ENCODER_BLUE_PURPLE)
	{
		/* Reverb Room */
		if (reverb_activation)
		{
			reverb_room_size = update_rotary_encoder_value(reverb_room_size,
				val,
				&prev_knob_reverb_room_size_val,
				reverb_room_size_min,
				reverb_room_size_max,
				4);			
			
			reverb_room_size_changed(reverb_room_size);
		}		
	}
	else if (evnt == _CONTROL_ENCODER_BLUE_GREEN)
	{
		/* Reverb Damp */
		if (reverb_activation)
		{
			reverb_damp = update_rotary_encoder_value(reverb_damp,
				val,
				&prev_knob_reverb_damp_val,
				reverb_damp_min,
				reverb_damp_max,
				4);
			
			reverb_damp_changed(reverb_damp);
		}		
	}
	else if (evnt == _CONTROL_ENCODER_BLUE_RED)
	{
		/* Reverb Width */
		if (reverb_activation)
		{
			reverb_width = update_rotary_encoder_value(reverb_width,
				val,
				&prev_knob_reverb_width_val,
				reverb_width_min,
				reverb_width_max,
				4);
			
			reverb_width_changed(reverb_width);
		}
	}
	else if (evnt == _CONTROL_ENCODER_BLUE_BLUE)
	{
		/* Reverb Level */
		if (reverb_activation)
		{
			reverb_level = update_rotary_encoder_value(reverb_level,
				val,
				&prev_knob_reverb_level_val,
				reverb_level_min,
				reverb_level_max,
				4);
			
			reverb_level_changed(reverb_level);
		}
	}
	else if (evnt == _CONTROL_ENCODER_ORANGE_PURPLE)
	{
		/* Chorus N */
		if (chorus_activation)
		{
			chorus_number = update_rotary_encoder_value(chorus_number,
				val,
				&prev_knob_chorus_number_val,
				chorus_number_min,
				chorus_number_max,
				4);
			
			chorus_number_changed(chorus_number);
		}
	}
	else if (evnt == _CONTROL_ENCODER_ORANGE_GREEN)
	{
		/* Chorus Level */
		if (chorus_activation)
		{
			chorus_level = update_rotary_encoder_value(chorus_level,
				val,
				&prev_knob_chorus_level_val,
				chorus_level_min,
				chorus_level_max,
				4);
			
			chorus_level_changed(chorus_level);
		}
	}
	else if (evnt == _CONTROL_ENCODER_ORANGE_RED)
	{
		/* Chorus Speed */
		if (chorus_activation)
		{
			chorus_speed = update_rotary_encoder_value(chorus_speed,
				val,
				&prev_knob_chorus_speed_val,
				chorus_speed_min,
				chorus_speed_max,
				10);
			
			chorus_speed_changed(chorus_speed);
		}
	}
	else if (evnt == _CONTROL_ENCODER_ORANGE_BLUE)
	{
		/* Chorus Depth */
		if (chorus_activation)
		{
			chorus_depth = update_rotary_encoder_value(chorus_depth,
				val,
				&prev_knob_chorus_depth_val,
				chorus_depth_min,
				chorus_depth_max,
				10);
			
			chorus_depth_changed(chorus_depth);
		}
	}
	else if (evnt == _CONTROL_ENCODER_ORANGE_YELLOW)
	{
		/* Chorus Type Scroll */
		if (chorus_activation)
		{
			chorus_waveform = update_rotary_encoder_value(chorus_waveform,
				val,
				&prev_knob_chorus_waveform_val,
				chorus_waveform_min,
				chorus_waveform_max,
				1);
			
			chorus_waveform_select_changed(chorus_waveform);			
		}		
	}
	else if (evnt == _CONTROL_SLIDER_BLUE_BLACK)
	{
		/* FluidSynth Gain */
		norm_gain = normalize_slider_value(val, fluid_gain_max, fluid_gain_min); // 0-100 -> 0-200
		/* Change slider value only when it matches the UI slider position */
		gain_slider_gap = fluid_gain - norm_gain;
			
		if (abs((float)gain_slider_gap) < ((fluid_gain_max - fluid_gain_min) / 5.0))
		{
			fluid_gain_changed(norm_gain);	
		}		
	}	
}

void Dialog_AdjFluidSynth::get_active_settings_values()
{
	fluid_gain = mod_synth_get_active_fluid_synth_volume();
	
	reverb_room_size = mod_synth_get_active_fluid_synth_reverb_room_size();
	reverb_damp = mod_synth_get_active_fluid_synth_reverb_damp();
	reverb_width = mod_synth_get_active_fluid_synth_reverb_width();	
	reverb_level = mod_synth_get_active_fluid_synth_reverb_level();	
	reverb_activation = mod_synth_get_active_fluid_synth_reverb_activation_state();

	chorus_number = mod_synth_get_active_fluid_synth_chorus_number();
	chorus_level = mod_synth_get_active_fluid_synth_chorus_level();
	chorus_speed = mod_synth_get_active_fluid_synth_chorus_speed();
	chorus_depth = mod_synth_get_active_fluid_synth_chorus_depth();
	chorus_waveform = mod_synth_get_active_fluid_synth_chorus_waveform();
	chorus_activation = mod_synth_get_active_fluid_synth_chorus_activation_state();
	
	active_preset = mod_synth_fluid_synth_get_active_preset();
	
	update();
}

void Dialog_AdjFluidSynth::set_default_settings_values(bool update_flag)
{	
	fluid_gain = 100;
	fluid_gain_max = 200;
	fluid_gain_min = 0;
	
	reverb_room_size = 20;
	reverb_room_size_max = 120;
	reverb_room_size_min = 0;
	
	reverb_damp = 0;
	reverb_damp_max = 100;
	reverb_damp_min = 0;
	
	reverb_width = 50;
	reverb_width_max = 100;
	reverb_width_min = 0;
	
	reverb_level = 90;
	reverb_level_max = 100;
	reverb_level_min = 0;
	
	reverb_activation = _AFS_REVERB_ENABLED;

	chorus_number = 3;
	chorus_number_max = 99;
	chorus_number_min = 3;
	
	chorus_level = 100;
	chorus_level_max = 100;
	chorus_level_min = 0;
	
	chorus_speed = 99;
	chorus_speed_max = 500;
	chorus_speed_min = 30;
	
	chorus_depth = 80;
	chorus_depth_max = 210;
	chorus_depth_min = 0;
	
	chorus_waveform = _AFS_CHORUS_WAVEFORM_SINE;
	chorus_activation = _AFS_CHORUS_DISABLED;
	
	active_preset = 0;
	
	if (update_flag)
	{
		update();
	}
}

void Dialog_AdjFluidSynth::update()
{
	fluid_gain_changed(fluid_gain);
	
	reverb_room_size_changed(reverb_room_size);
	reverb_damp_changed(reverb_damp);
	reverb_width_changed(reverb_width);
	reverb_level_changed(reverb_level);
	reverb_activation_changed(reverb_activation);

	chorus_number_changed(chorus_number);
	chorus_level_changed(chorus_level);
	chorus_speed_changed(chorus_speed);
	chorus_depth_changed(chorus_depth);
	chorus_waveform_changed(chorus_waveform);
	chorus_activation_changed(chorus_activation);
	
	if (active_preset == 0)
	{
		ui->radioButton_Preset_1->setChecked(true);
		ui->radioButton_Preset_2->setChecked(false);
		ui->radioButton_Preset_3->setChecked(false);
	}
	else if (active_preset == 1)
	{
		ui->radioButton_Preset_1->setChecked(false);
		ui->radioButton_Preset_2->setChecked(true);
		ui->radioButton_Preset_3->setChecked(false);
	}
	else if (active_preset == 2)
	{
		ui->radioButton_Preset_1->setChecked(false);
		ui->radioButton_Preset_2->setChecked(false);
		ui->radioButton_Preset_3->setChecked(true);
	}
}



void Dialog_AdjFluidSynth::fluid_gain_changed(int vol)
{
	ui->verticalSlider_adjFluidSynth_Gain->blockSignals(true);
	ui->verticalSlider_adjFluidSynth_Gain->setValue(vol);
	ui->verticalSlider_adjFluidSynth_Gain->blockSignals(false);
	
	ui->spinBox_adjFluidSynth_Gain->blockSignals(true);
	ui->spinBox_adjFluidSynth_Gain->setValue(vol);
	ui->spinBox_adjFluidSynth_Gain->blockSignals(false);
	
	fluid_gain = vol;
	mod_synth_set_fluid_synth_volume(vol);
		
	/* Set focus back on the Dialog */
	this->setFocus(Qt::ActiveWindowFocusReason);
	
	// printf("%i\n", norm_vol);
	//mod_synth_set_fluid_synth_volume(norm_vol);
}
	
void Dialog_AdjFluidSynth::reverb_room_size_changed(int val)
{
	ui->dial_adjFluidSynth_Reverb_Room->blockSignals(true);
	ui->dial_adjFluidSynth_Reverb_Room->setValue(val);
	ui->dial_adjFluidSynth_Reverb_Room->blockSignals(false);
	
	ui->spinBox_adjFluidSynth_Reverb_Room->blockSignals(true);
	ui->spinBox_adjFluidSynth_Reverb_Room->setValue(val);
	ui->spinBox_adjFluidSynth_Reverb_Room->blockSignals(false);
	
	reverb_room_size = val;
	mod_synth_set_fluid_synth_reverb_room_size(val);
	
	/* Set focus back on the Dialog */
	this->setFocus(Qt::ActiveWindowFocusReason);
	
	// printf("%i\n", reverb_room_size);
	//mod_synth_set_fluid_synth_reverb_room_size(reverb_room_size);
}
	
void Dialog_AdjFluidSynth::reverb_damp_changed(int val)
{
	ui->dial_adjFluidSynth_Reverb_Damp->blockSignals(true);
	ui->dial_adjFluidSynth_Reverb_Damp->setValue(val);
	ui->dial_adjFluidSynth_Reverb_Damp->blockSignals(false);
	
	ui->spinBox_adjFluidSynth_Reverb_Damp->blockSignals(true);
	ui->spinBox_adjFluidSynth_Reverb_Damp->setValue(val);
	ui->spinBox_adjFluidSynth_Reverb_Damp->blockSignals(false);
	
	reverb_damp = val;
	mod_synth_set_fluid_synth_reverb_damp(val);
	
	/* Set focus back on the Dialog */
	this->setFocus(Qt::ActiveWindowFocusReason);
}
	
void Dialog_AdjFluidSynth::reverb_width_changed(int val)
{
	ui->dial_adjFluidSynth_Reverb_Width->blockSignals(true);
	ui->dial_adjFluidSynth_Reverb_Width->setValue(val);
	ui->dial_adjFluidSynth_Reverb_Width->blockSignals(false);
	
	ui->spinBox_adjFluidSynth_Reverb_Width->blockSignals(true);
	ui->spinBox_adjFluidSynth_Reverb_Width->setValue(val);
	ui->spinBox_adjFluidSynth_Reverb_Width->blockSignals(false);
	
	reverb_width = val;
	mod_synth_set_fluid_synth_reverb_width(val);
	
	/* Set focus back on the Dialog */
	this->setFocus(Qt::ActiveWindowFocusReason);
}
	
void Dialog_AdjFluidSynth::reverb_level_changed(int val)
{
	ui->dial_adjFluidSynth_Reverb_Level->blockSignals(true);
	ui->dial_adjFluidSynth_Reverb_Level->setValue(val);
	ui->dial_adjFluidSynth_Reverb_Level->blockSignals(false);
	
	ui->spinBox_adjFluidSynth_Reverb_Level->blockSignals(true);
	ui->spinBox_adjFluidSynth_Reverb_Level->setValue(val);
	ui->spinBox_adjFluidSynth_Reverb_Level->blockSignals(false);
	
	reverb_level = val;
	mod_synth_set_fluid_synth_reverb_level(val);
	
	/* Set focus back on the Dialog */
	this->setFocus(Qt::ActiveWindowFocusReason);
}
	
void Dialog_AdjFluidSynth::reverb_activation_changed(bool val)
{	
	ui->checkBox_adjFluidSynth_Reverb_Active->blockSignals(true);
	
	if (val)
	{
		ui->checkBox_adjFluidSynth_Reverb_Active->setCheckState(Qt::Checked);
		ui->frame_Reverb->setEnabled(true);
		
		reverb_activation = true;
		mod_synth_set_fluid_synth_enable_reverb();
	}
	else
	{
		ui->checkBox_adjFluidSynth_Reverb_Active->setCheckState(Qt::Unchecked);
		ui->frame_Reverb->setEnabled(false);
		
		reverb_activation = false;
		mod_synth_set_fluid_synth_disable_reverb();
	}
	
	ui->checkBox_adjFluidSynth_Reverb_Active->blockSignals(false);
	
	/* Set focus back on the Dialog */
	this->setFocus(Qt::ActiveWindowFocusReason);
}
	

void Dialog_AdjFluidSynth::chorus_number_changed(int val)
{
	ui->dial_adjFluidSynth_Chorus_N->blockSignals(true);
	ui->dial_adjFluidSynth_Chorus_N->setValue(val);
	ui->dial_adjFluidSynth_Chorus_N->blockSignals(false);
	
	ui->spinBox_adjFluidSynth_Chorus_N->blockSignals(true);
	ui->spinBox_adjFluidSynth_Chorus_N->setValue(val);
	ui->spinBox_adjFluidSynth_Chorus_N->blockSignals(false);
	
	chorus_number = val;
	mod_synth_set_fluid_synth_chorus_number(val);
	
	/* Set focus back on the Dialog */
	this->setFocus(Qt::ActiveWindowFocusReason);
}
	
void Dialog_AdjFluidSynth::chorus_level_changed(int val)
{
	ui->dial_adjFluidSynth_Chorus_Level->blockSignals(true);
	ui->dial_adjFluidSynth_Chorus_Level->setValue(val);
	ui->dial_adjFluidSynth_Chorus_Level->blockSignals(false);
	
	ui->spinBox_adjFluidSynth_Chorus_Level->blockSignals(true);
	ui->spinBox_adjFluidSynth_Chorus_Level->setValue(val);
	ui->spinBox_adjFluidSynth_Chorus_Level->blockSignals(false);
	
	chorus_level = val;
	mod_synth_set_fluid_synth_chorus_level(val);
	
	/* Set focus back on the Dialog */
	this->setFocus(Qt::ActiveWindowFocusReason);
}
	
void Dialog_AdjFluidSynth::chorus_speed_changed(int val)
{
	ui->dial_adjFluidSynth_Chorus_Speed->blockSignals(true);
	ui->dial_adjFluidSynth_Chorus_Speed->setValue(val);
	ui->dial_adjFluidSynth_Chorus_Speed->blockSignals(false);
	
	ui->spinBox_adjFluidSynth_Chorus_Speed->blockSignals(true);
	ui->spinBox_adjFluidSynth_Chorus_Speed->setValue(val);
	ui->spinBox_adjFluidSynth_Chorus_Speed->blockSignals(false);
	
	chorus_speed = val;
	mod_synth_set_fluid_synth_chorus_speed(val);
	
	/* Set focus back on the Dialog */
	this->setFocus(Qt::ActiveWindowFocusReason);
}
	
void Dialog_AdjFluidSynth::chorus_depth_changed(int val)
{
	ui->dial_adjFluidSynth_Chorus_Depth->blockSignals(true);
	ui->dial_adjFluidSynth_Chorus_Depth->setValue(val);
	ui->dial_adjFluidSynth_Chorus_Depth->blockSignals(false);
	
	ui->spinBox_adjFluidSynth_Chorus_Depth->blockSignals(true);
	ui->spinBox_adjFluidSynth_Chorus_Depth->setValue(val);
	ui->spinBox_adjFluidSynth_Chorus_Depth->blockSignals(false);
	
	chorus_depth = val;
	mod_synth_set_fluid_synth_chorus_depth(val);
	
	/* Set focus back on the Dialog */
	this->setFocus(Qt::ActiveWindowFocusReason);
}
	
void Dialog_AdjFluidSynth::chorus_waveform_changed(int val)
{
	mod_synth_set_fluid_synth_chorus_waveform(val);	
	/* Avtivated by the combo box */
	this->setFocus(Qt::ActiveWindowFocusReason);
}

void Dialog_AdjFluidSynth::chorus_waveform_select_changed(int val)
{
	ui->comboBox_adjFluidSynth_Chorus_Type->blockSignals(true);
	ui->comboBox_adjFluidSynth_Chorus_Type->setCurrentIndex(val);
	ui->comboBox_adjFluidSynth_Chorus_Type->blockSignals(false);
	
	chorus_waveform = val;
	mod_synth_set_fluid_synth_chorus_waveform(val);
	
	//printf("%i\n", chorus_waveform);
	
	/* Set focus back on the Dialog */
	this->setFocus(Qt::ActiveWindowFocusReason);
}

void Dialog_AdjFluidSynth::chorus_activation_changed(bool val)
{
	ui->checkBox_adjFluidSynth_Chorus_Active->blockSignals(true);
	
	if (val)
	{
		ui->checkBox_adjFluidSynth_Chorus_Active->setCheckState(Qt::Checked);
		ui->frame_Chorus->setEnabled(true);
		
		chorus_activation = true;
		mod_synth_set_fluid_synth_enable_chorus();
	}
	else
	{
		ui->checkBox_adjFluidSynth_Chorus_Active->setCheckState(Qt::Unchecked);
		ui->frame_Chorus->setEnabled(false);
		
		chorus_activation = false;
		mod_synth_set_fluid_synth_disable_chorus();
	}
	
	ui->checkBox_adjFluidSynth_Chorus_Active->blockSignals(false);
	
	/* Set focus back on the Dialog */
	this->setFocus(Qt::ActiveWindowFocusReason);	
}
	

void Dialog_AdjFluidSynth::on_dialog_close()
{
	//mod_synth_unregister_callback_control_box_event_update_ui(
	//	&fluid_control_box_event_update_ui_callback_wrapper);
	
	close();
}

void Dialog_AdjFluidSynth::on_default_settings_clicked()
{
	QMessageBox msgBox;
	msgBox.setIcon(QMessageBox::QMessageBox::Warning);
	msgBox.setWindowTitle("Warning?");
	msgBox.setText("Are you sure you want to load the default values?\nAll current settings may be lost!");
	msgBox.setStandardButtons(QMessageBox::Yes);
	msgBox.addButton(QMessageBox::No);
	msgBox.setDefaultButton(QMessageBox::No);
	if (msgBox.exec() == QMessageBox::Yes)
	{
		set_default_settings_values();
		update();
	}
}

void Dialog_AdjFluidSynth::on_load_presets_clicked()
{
	QString presetName = QFileDialog::getOpenFileName(this,
		tr("Load Preset ") + QString::number(active_preset + 1),
		QString(_FLUID_PRESETS_FILES_DEFAULT_DIR),
		tr("Presets (*.xml *.XML);;All Files (*)"));

	if (!presetName.isEmpty())
	{
		mod_synth_open_fluid_synth_preset_file(presetName.toStdString(), active_preset);
		/* Refresh channels table */
		Dialog_FluidSynthChannels::get_instance(NULL, true);
	}
		
//	preset_radio_buttons[active_preset]->setToolTip(QString::fromStdString(*mod_synth_get_preset_summary_string(active_preset)));
		
//	update();
			
	// mainWindow->pushButton_mainTab_loadPreset->setEnabled(false);
	// mainWindow->pushButton_mainTab_loadPreset->setChecked(false);
	// mainWindow->pushButton_mainTab_loadPreset->setEnabled(true);
}

void Dialog_AdjFluidSynth::on_save_presets_clicked()
{
	QString presetName = QFileDialog::getSaveFileName(this,
		tr("Save Preset File"),
		QString(_FLUID_PRESETS_FILES_DEFAULT_DIR),
		tr("Presets (*.xml *.XML);;All Files (*)"));

	if (!presetName.isEmpty())
	{
		mod_synth_save_fluid_synth_preset_file(presetName.toStdString());
	}
		
	// ui->pushButton_adjFluidSynth_Save_preset->setEnabled(false);
	// ui->pushButton_adjFluidSynth_Save_preset->setChecked(false);
	// ui->pushButton_adjFluidSynth_Save_preset->setEnabled(true);
}

void Dialog_AdjFluidSynth::on_module_channels_clicked()
{
	if (dialog_fluid_synth_channels != NULL)
	{
	//	dialog_fluid_synth_channels = NULL;
	}
	dialog_fluid_synth_channels = Dialog_FluidSynthChannels::get_instance(this, true);
	//dialog_fluid_synth_channels->setAttribute(Qt::WA_DeleteOnClose);
	dialog_fluid_synth_channels->show();
}

void Dialog_AdjFluidSynth::on_preset_1_selected(bool state)
{
	active_preset = 0;
	mod_synth_fluid_synth_set_active_preset(0);
	/* Refresh channels table */
	Dialog_FluidSynthChannels::get_instance(NULL, true);
}

void Dialog_AdjFluidSynth::on_preset_2_selected(bool state)
{
	active_preset = 1;
	mod_synth_fluid_synth_set_active_preset(1);
	/* Refresh channels table */
	Dialog_FluidSynthChannels::get_instance(NULL, true);
}

void Dialog_AdjFluidSynth::on_preset_3_selected(bool state)
{
	active_preset = 2;
	mod_synth_fluid_synth_set_active_preset(2);
	/* Refresh channels table */
	Dialog_FluidSynthChannels::get_instance(NULL, true);
}
