/**
* @file		ControlBoxEventsHandler_AnalogSynthDistortion
*	@author		Nahum Budin
*	@date		27-Nov-2024
*	@version	1.0
*
*	@brief		Used for controling the Analog Synthesizer Distortion Effect Tab 
*				
*	History:
*			
*
*/

#include "Dialog_AnalogSynth.h"
#include "ui_Dialog_AnalogSynth.h"
#include "utils.h"

#include "libAdjRaspi5SynthAPI.h"

void Dialog_AnalogSynth::control_box_events_handler_distortion(int evnt, uint16_t val)
{
	Qt::CheckState checked;	
	
	static int prev_knob_distortion1_drive_entry = 64;
	static int prev_knob_distortion1_range_entry = 64;
	static int prev_knob_distortion1_blend_entry = 64;
		
	static int prev_knob_distortion2_drive_entry = 64;
	static int prev_knob_distortion2_range_entry = 64;
	static int prev_knob_distortion2_blend_entry = 64;
	
	if ((evnt == _CONTROL_FUNCTION_PUSHBUTTON_ENTER) &&
			 (val == 0))
	{
		/* Switch active frames */
		active_frames_group_distortion++;
		
		if (active_frames_group_distortion > _FRAMES_GROUP_1)
		{
			active_frames_group_distortion = _FRAMES_GROUP_1;
		}		
	}	
	else if (evnt == _CONTROL_PUSHBUTTON_BLUE_BLACK)
	{
		/* Active */
		if (val == 0)
		{
			/* Only when pushbutton is pressed */			
			checked = ui->checkBox_DistortionActive->checkState();
			
			/* Toggle */
			if (checked == Qt::CheckState::Checked)
			{
				checked = Qt::CheckState::Unchecked;
			}
			else
			{
				checked = Qt::CheckState::Checked;
			}
							
			on_distortion_active_checkbox_Changed(checked);
		}
	}
	
	if (!distortion_active)
	{
		return;
	}
	
	if (evnt == _CONTROL_PUSHBUTTON_BLUE_BLUE)
	{
		/* Auto Gain */
		if (val == 0)
		{
			/* Only when pushbutton is pressed */			
			checked = ui->checkBox_DistortionAutoGain->checkState();
			
			/* Toggle */
			if (checked == Qt::CheckState::Checked)
			{
				checked = Qt::CheckState::Unchecked;
			}
			else
			{
				checked = Qt::CheckState::Checked;
			}
							
			on_distortion_auto_gain_checkbox_Changed(checked);
		}
	}
	else if (evnt == _CONTROL_ENCODER_BLUE_PURPLE)
	{
		/* Distortion 1 Drive */
		distortion1_drive = update_rotary_encoder_value(
			distortion1_drive,
			val,
			&prev_knob_distortion1_drive_entry,
			_DISTORTION_ENTRY_MIN,
			_DISTORTION_ENTRY_MAX,
			5);
			
		on_distortion1_drive_dial_changed(distortion1_drive);
	}
	else if (evnt == _CONTROL_ENCODER_BLUE_GREEN)
	{
		/* Distortion 1 Range */
		distortion1_range = update_rotary_encoder_value(
			distortion1_range,
			val,
			&prev_knob_distortion1_range_entry,
			_DISTORTION_ENTRY_MIN,
			_DISTORTION_ENTRY_MAX,
			5);
			
		on_distortion1_range_dial_changed(distortion1_range);
	}
	else if (evnt == _CONTROL_ENCODER_BLUE_RED)
	{
		/* Distortion 1 Blend */
		distortion1_blend = update_rotary_encoder_value(
			distortion1_blend,
			val,
			&prev_knob_distortion1_blend_entry,
			_DISTORTION_ENTRY_MIN,
			_DISTORTION_ENTRY_MAX,
			5);
			
		on_distortion1_blend_dial_changed(distortion1_blend);
	}
	else if (evnt == _CONTROL_ENCODER_ORANGE_PURPLE)
	{
		/* Distortion 2 Drive */
		distortion2_drive = update_rotary_encoder_value(
			distortion2_drive,
			val,
			&prev_knob_distortion2_drive_entry,
			_DISTORTION_ENTRY_MIN,
			_DISTORTION_ENTRY_MAX,
			5);
		
		on_distortion2_drive_dial_changed(distortion2_drive);
	}
	else if (evnt == _CONTROL_ENCODER_ORANGE_GREEN)
	{
		/* Distortion 2 Range */
		distortion2_range = update_rotary_encoder_value(
			distortion2_range,
			val,
			&prev_knob_distortion2_range_entry,
			_DISTORTION_ENTRY_MIN,
			_DISTORTION_ENTRY_MAX,
			5);
			
		on_distortion2_range_dial_changed(distortion2_range);
	}
	else if (evnt == _CONTROL_ENCODER_ORANGE_RED)
	{
		/* Distortion 2 Blend */
		distortion2_blend = update_rotary_encoder_value(
			distortion2_blend,
			val,
			&prev_knob_distortion2_blend_entry,
			_DISTORTION_ENTRY_MIN,
			_DISTORTION_ENTRY_MAX,
			5);
			
		on_distortion2_blend_dial_changed(distortion2_blend);
	}
}
