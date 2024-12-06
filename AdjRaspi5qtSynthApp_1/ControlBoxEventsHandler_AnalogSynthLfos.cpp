/**
* @file		ControlBoxEventsHandler_AnalogSynthLfos
*	@author		Nahum Budin
*	@date		27-Nov-2024
*	@version	1.0
*
*	@brief		Used for controling the Analog Synthesizer LFOs Tab 
*				
*	History:
*			
*
*/

#include "Dialog_AnalogSynth.h"
#include "ui_Dialog_AnalogSynth.h"
#include "utils.h"

#include "libAdjRaspi5SynthAPI.h"

void Dialog_AnalogSynth::control_box_events_handler_lfos(int evnt, uint16_t val)
{	
	static int prev_knob_lfo1_symmetry = 64;
	static int prev_knob_lfo1_rate = 64;
	static int prev_combobox_lfo1_waveform = 64;
	static int prev_knob_lfo2_symmetry = 64;
	static int prev_knob_lfo2_rate = 64;
	static int prev_combobox_lfo2_waveform = 64;
	static int prev_knob_lfo3_symmetry = 64;
	static int prev_knob_lfo3_rate = 64;
	static int prev_combobox_lfo3_waveform = 64;
	static int prev_knob_lfo4_symmetry = 64;
	static int prev_knob_lfo4_rate = 64;
	static int prev_combobox_lfo4_waveform = 64;
	static int prev_knob_lfo5_symmetry = 64;
	static int prev_knob_lfo5_rate = 64;
	static int prev_combobox_lfo5_waveform = 64;
	static int prev_knob_lfo6_symmetry = 64;
	static int prev_knob_lfo6_rate = 64;
	static int prev_combobox_lfo6_waveform = 64;
	
	if (!this->hasFocus())
	{
		return;
	}
	
	if ((evnt == _CONTROL_FUNCTION_PUSHBUTTON_ENTER) &&
			 (val == 0))
	{
		/* Switch active frames */
		active_frames_group_lfos++;
		
		if (active_frames_group_lfos > _FRAMES_GROUP_2)
		{
			active_frames_group_lfos = _FRAMES_GROUP_1;
		}		
	}
	else if (evnt == _CONTROL_ENCODER_BLUE_PURPLE)
	{
		if (active_frames_group_lfos == _FRAMES_GROUP_1)
		{
			/* LFO 1 Waveform */
			lfo1_waveform_entry = update_rotary_encoder_value(
				lfo1_waveform_entry,
				val,
				&prev_combobox_lfo1_waveform,
				_OSC_WAVEFORM_SINE,
				_OSC_WAVEFORM_SAMPHOLD,
				1);
			
			on_lfo1_waveform_combo_changed(lfo1_waveform_entry);
			
		}
		else if (active_frames_group_lfos == _FRAMES_GROUP_2)
		{
			/* LFO 5 Waveform */
			lfo5_waveform_entry = update_rotary_encoder_value(
				lfo5_waveform_entry,
				val,
				&prev_combobox_lfo5_waveform,
				_OSC_WAVEFORM_SINE,
				_OSC_WAVEFORM_SAMPHOLD,
				1);
			
			on_lfo5_waveform_combo_changed(lfo5_waveform_entry);
		}
	}
	else if (evnt == _CONTROL_ENCODER_BLUE_GREEN)
	{
		if (active_frames_group_lfos == _FRAMES_GROUP_1)
		{
			/* LFO 1 Symmetry */
			lfo1_symmetry_entry = update_rotary_encoder_value(
				lfo1_symmetry_entry,
				val,
				&prev_knob_lfo1_symmetry,
				_LFO_SYMMETRY_ENTRY_MIN,
				_LFO_SYMMETRY_ENTRY_MAX,
				5);
			
			on_lfo1_symmetry_dial_changed(lfo1_symmetry_entry);
		}
		else if (active_frames_group_lfos == _FRAMES_GROUP_2)
		{
			/* LFO 5 Stmetry */
			lfo5_symmetry_entry = update_rotary_encoder_value(
				lfo5_symmetry_entry,
				val,
				&prev_knob_lfo5_symmetry,
				_LFO_SYMMETRY_ENTRY_MIN,
				_LFO_SYMMETRY_ENTRY_MAX,
				5);
			
			on_lfo5_symmetry_dial_changed(lfo5_symmetry_entry);
		}
	}
	else if (evnt == _CONTROL_ENCODER_BLUE_RED)
	{
		if (active_frames_group_lfos == _FRAMES_GROUP_1)
		{
			/* LFO 1 Rate */
			lfo1_rate_entry = update_rotary_encoder_value(
				lfo1_rate_entry,
				val,
				&prev_knob_lfo1_rate,
				_LFO_RATE_ENTRY_MIN,
				_LFO_RATE_ENTRY_MAX,
				5);
			
			on_lfo1_rate_dial_changed(lfo1_rate_entry);
		}
		else if (active_frames_group_lfos == _FRAMES_GROUP_2)
		{
			/* LFO 5 Rate */
			lfo5_rate_entry = update_rotary_encoder_value(
				lfo5_rate_entry,
				val,
				&prev_knob_lfo5_rate,
				_LFO_RATE_ENTRY_MIN,
				_LFO_RATE_ENTRY_MAX,
				5);
			
			on_lfo5_rate_dial_changed(lfo5_rate_entry);
		}
	}
	else if (evnt == _CONTROL_ENCODER_BLUE_BLUE)
	{
		if (active_frames_group_lfos == _FRAMES_GROUP_1)
		{
			/* LFO 3 Waveform */
			lfo3_waveform_entry = update_rotary_encoder_value(
				lfo3_waveform_entry,
				val,
				&prev_combobox_lfo3_waveform,
				_OSC_WAVEFORM_SINE,
				_OSC_WAVEFORM_SAMPHOLD,
				1);
			
			on_lfo3_waveform_combo_changed(lfo3_waveform_entry);
		}
	}
	else if (evnt == _CONTROL_ENCODER_BLUE_WHITE)
	{
		if (active_frames_group_lfos == _FRAMES_GROUP_1)
		{
			/* LFO 3 Symetry */
			lfo3_symmetry_entry = update_rotary_encoder_value(
				lfo3_symmetry_entry,
				val,
				&prev_knob_lfo3_symmetry,
				_LFO_SYMMETRY_ENTRY_MIN,
				_LFO_SYMMETRY_ENTRY_MAX,
				5);
			
			on_lfo3_symmetry_dial_changed(lfo3_symmetry_entry);
		}
	}
	else if (evnt == _CONTROL_ENCODER_BLUE_YELLOW)
	{
		if (active_frames_group_lfos == _FRAMES_GROUP_1)
		{
			/* LFO 3 Rate */
			lfo3_rate_entry = update_rotary_encoder_value(
				lfo3_rate_entry,
				val,
				&prev_knob_lfo3_rate,
				_LFO_RATE_ENTRY_MIN,
				_LFO_RATE_ENTRY_MAX,
				5);
			
			on_lfo3_rate_dial_changed(lfo3_rate_entry);
		}
	}
	else if (evnt == _CONTROL_ENCODER_ORANGE_PURPLE)
	{
		if (active_frames_group_lfos == _FRAMES_GROUP_1)
		{
			/* LFO 2 Waveform */
			lfo2_waveform_entry = update_rotary_encoder_value(
				lfo2_waveform_entry,
				val,
				&prev_combobox_lfo2_waveform,
				_OSC_WAVEFORM_SINE,
				_OSC_WAVEFORM_SAMPHOLD,
				1);
			
			on_lfo2_waveform_combo_changed(lfo2_waveform_entry);
		}
		else if (active_frames_group_lfos == _FRAMES_GROUP_2)
		{
			/* LFO 6 Waveform */
			lfo6_waveform_entry = update_rotary_encoder_value(
				lfo6_waveform_entry,
				val,
				&prev_combobox_lfo6_waveform,
				_OSC_WAVEFORM_SINE,
				_OSC_WAVEFORM_SAMPHOLD,
				1);
			
			on_lfo6_waveform_combo_changed(lfo6_waveform_entry);
		}
	}
	else if (evnt == _CONTROL_ENCODER_ORANGE_GREEN)
	{
		if (active_frames_group_lfos == _FRAMES_GROUP_1)
		{
			/* LFO 2 Symmetry */
			lfo2_symmetry_entry = update_rotary_encoder_value(
				lfo2_symmetry_entry,
				val,
				&prev_knob_lfo2_symmetry,
				_LFO_SYMMETRY_ENTRY_MIN,
				_LFO_SYMMETRY_ENTRY_MAX,
				5);
			
			on_lfo2_symmetry_dial_changed(lfo2_symmetry_entry);
		}
		else if (active_frames_group_lfos == _FRAMES_GROUP_2)
		{
			/* LFO 6 Stmetry */
			lfo6_symmetry_entry = update_rotary_encoder_value(
				lfo6_symmetry_entry,
				val,
				&prev_knob_lfo6_symmetry,
				_LFO_SYMMETRY_ENTRY_MIN,
				_LFO_SYMMETRY_ENTRY_MAX,
				5);
			
			on_lfo6_symmetry_dial_changed(lfo6_symmetry_entry);
		}
	}
	else if (evnt == _CONTROL_ENCODER_ORANGE_RED)
	{
		if (active_frames_group_lfos == _FRAMES_GROUP_1)
		{
			/* LFO 2 Rate */
			lfo2_rate_entry = update_rotary_encoder_value(
				lfo2_rate_entry,
				val,
				&prev_knob_lfo2_rate,
				_LFO_RATE_ENTRY_MIN,
				_LFO_RATE_ENTRY_MAX,
				5);
			
			on_lfo2_rate_dial_changed(lfo2_rate_entry);
		}
		else if (active_frames_group_lfos == _FRAMES_GROUP_2)
		{
			/* LFO 6 Rate */
			lfo6_rate_entry = update_rotary_encoder_value(
				lfo6_rate_entry,
				val,
				&prev_knob_lfo6_rate,
				_LFO_RATE_ENTRY_MIN,
				_LFO_RATE_ENTRY_MAX,
				5);
			
			on_lfo6_rate_dial_changed(lfo6_rate_entry);
		}
	}
	else if (evnt == _CONTROL_ENCODER_ORANGE_BLUE)
	{
		if (active_frames_group_lfos == _FRAMES_GROUP_1)
		{
			/* LFO 4 Waveform */
			lfo4_waveform_entry = update_rotary_encoder_value(
				lfo4_waveform_entry,
				val,
				&prev_combobox_lfo4_waveform,
				_OSC_WAVEFORM_SINE,
				_OSC_WAVEFORM_SAMPHOLD,
				1);
			
			on_lfo4_waveform_combo_changed(lfo4_waveform_entry);
		}
	}
	else if (evnt == _CONTROL_ENCODER_ORANGE_WHITE)
	{
		if (active_frames_group_lfos == _FRAMES_GROUP_1)
		{
			/* LFO 4 Symetry */
			lfo4_symmetry_entry = update_rotary_encoder_value(
				lfo4_symmetry_entry,
				val,
				&prev_knob_lfo4_symmetry,
				_LFO_SYMMETRY_ENTRY_MIN,
				_LFO_SYMMETRY_ENTRY_MAX,
				5);
			
			on_lfo4_symmetry_dial_changed(lfo4_symmetry_entry);
		}
	}
	else if (evnt == _CONTROL_ENCODER_ORANGE_YELLOW)
	{
		if (active_frames_group_lfos == _FRAMES_GROUP_1)
		{
			/* LFO 4 Rate */
			lfo4_rate_entry = update_rotary_encoder_value(
				lfo4_rate_entry,
				val,
				&prev_knob_lfo4_rate,
				_LFO_RATE_ENTRY_MIN,
				_LFO_RATE_ENTRY_MAX,
				5);
			
			on_lfo4_rate_dial_changed(lfo4_rate_entry);
		}
	}
}
