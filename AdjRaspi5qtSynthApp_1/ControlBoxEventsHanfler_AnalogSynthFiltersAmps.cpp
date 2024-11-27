/**
* @file		ControlBoxEventsHandler_AnalogSynthFiltersAmps
*	@author		Nahum Budin
*	@date		18-Nov-2024
*	@version	1.0
*
*	@brief		Used for controling the Analog Synthesizer Filters and Output Amplifiers Tab 
*				
*	History:
*			
*
*/

#include "Dialog_AnalogSynth.h"
#include "ui_Dialog_AnalogSynth.h"
#include "utils.h"

#include "libAdjRaspi5SynthAPI.h"

void Dialog_AnalogSynth::control_box_events_handler_filters_amps(int evnt, uint16_t val)
{
	Qt::CheckState checked;
	
	static int prev_knob_filter1_freq = 64;
	static int prev_knob_filter1_octave = 64;
	static int prev_knob_filter1_q = 64;
	static int prev_knob_filter1_kbd_track = 64;
	static int prev_combobox_filter1_band = 64;
	static int prev_combobox_filter1_freq_mod_lfo = 64;
	static int prev_knob_filter1_freq_mod_lfo_level = 64;
	static int prev_combobox_filter1_freq_mod_adsr = 64;
	static int prev_knob_filter1_freq_mod_adsr_level = 64;
	
	static int prev_knob_filter2_freq = 64;
	static int prev_knob_filter2_octave = 64;
	static int prev_knob_filter2_q = 64;
	static int prev_knob_filter2_kbd_track = 64;
	static int prev_combobox_filter2_band = 64;
	static int prev_combobox_filter2_freq_mod_lfo = 64;
	static int prev_knob_filter2_freq_mod_lfo_level = 64;
	static int prev_combobox_filter2_freq_mod_adsr = 64;
	static int prev_knob_filter2_freq_mod_adsr_level = 64;
	
	static int prev_knob_amp1_level = 64;
	static int prev_knob_amp1_pan = 64;
	static int prev_knob_amp1_send = 64;
	static int prev_combobox_amp1_pan_mod_lfo = 64;
	static int prev_knob_amp1_pan_mod_lfo_level = 64;
	
	static int prev_knob_amp2_level = 64;
	static int prev_knob_amp2_pan = 64;
	static int prev_knob_amp2_send = 64;
	static int prev_combobox_amp2_pan_mod_lfo = 64;
	static int prev_knob_amp2_pan_mod_lfo_level = 64;	
	
	if (!this->hasFocus())
	{
		return;
	}
	
	if ((evnt == _CONTROL_FUNCTION_PUSHBUTTON_ENTER) &&
			 (val == 0))
	{
		/* Switch active frames */
		active_frames_group_filters_amps++;
		
		if (active_frames_group_filters_amps > _FRAMES_GROUP_3)
		{
			active_frames_group_filters_amps = _FRAMES_GROUP_1;
		}		
	}
	else if (evnt == _CONTROL_PUSHBUTTON_BLUE_GREEN)
	{
		/* Filter 2 follows filter 1 */
		if (val == 0)
		{
			/* Only when pushbutton is pressed */
			checked = ui->checkBox_Filter2FollowFilter1->checkState();
			
			/* Toggle */
			if (checked == Qt::CheckState::Checked)
			{
				checked = Qt::CheckState::Unchecked;
			}
			else
			{
				checked = Qt::CheckState::Checked;
			}
							
			on_filter2_track_filter1_checkbox_changed(checked);			
		}
	
	}
	else if (evnt == _CONTROL_PUSHBUTTON_BLUE_BLUE)
	{
		/* Amp Fix */
		if (val == 0)
		{
			/* Only when pushbutton is pressed */
			checked = ui->checkBox_AmpFix->checkState();
			
			/* Toggle */
			if (checked == Qt::CheckState::Checked)
			{
				checked = Qt::CheckState::Unchecked;
			}
			else
			{
				checked = Qt::CheckState::Checked;
			}
							
			on_fixed_amp_checkbox_Changed(checked);		
		}
	}
	else if (evnt == _CONTROL_ENCODER_BLUE_PURPLE)
	{
		if (active_frames_group_filters_amps == _FRAMES_GROUP_1)
		{
			/* Filter 1 Freq */
			filter1_frequency_entry = update_rotary_encoder_value(
				filter1_frequency_entry,
				val,
				&prev_knob_filter1_freq,
				_FILTER_KNOB_MIN_VALUE,
				_FILTER_KNOB_MAX_VALUE,
				4);
			
			on_filter1_freq_dial_changed(filter1_frequency_entry);
			
		}
		else if (active_frames_group_filters_amps == _FRAMES_GROUP_2)
		{
			/* Filter 2 Freq */
			filter2_frequency_entry = update_rotary_encoder_value(
				filter2_frequency_entry,
				val,
				&prev_knob_filter2_freq,
				_FILTER_KNOB_MIN_VALUE,
				_FILTER_KNOB_MAX_VALUE,
				4);
			
			on_filter2_freq_dial_changed(filter2_frequency_entry);
		}
		else if (active_frames_group_filters_amps == _FRAMES_GROUP_3)
		{
			/* Amp 1 Amp */
			amp1_level = update_rotary_encoder_value(
				amp1_level,
				val,
				&prev_knob_amp1_level,
				_AMP_KNOB_MIN_VALUE,
				_AMP_KNOB_MAX_VALUE,
				4);
			
			on_amp1_level_dial_hanged(amp1_level);
		}		
	}
	else if (evnt == _CONTROL_ENCODER_BLUE_GREEN)
	{
		if (active_frames_group_filters_amps == _FRAMES_GROUP_1)
		{
			/* Filter 1 Octave */
			filter1_octave_entry = update_rotary_encoder_value(
				filter1_octave_entry,
				val,
				&prev_knob_filter1_octave,
				_FILTER_KNOB_MIN_VALUE,
				_FILTER_KNOB_MAX_VALUE,
				4);
			
			on_filter1_octave_dial_changed(filter1_octave_entry);
		}
		else if (active_frames_group_filters_amps == _FRAMES_GROUP_2)
		{
			/* Filter 2 Octave */
			filter2_octave_entry = update_rotary_encoder_value(
				filter2_octave_entry,
				val,
				&prev_knob_filter2_octave,
				_FILTER_KNOB_MIN_VALUE,
				_FILTER_KNOB_MAX_VALUE,
				4);
			
			on_filter2_octave_dial_changed(filter2_octave_entry);
		}
		else if (active_frames_group_filters_amps == _FRAMES_GROUP_3)
		{
			/* Amp 1 Pan */
			amp1_pan = update_rotary_encoder_value(
				amp1_pan,
				val,
				&prev_knob_amp1_pan,
				_AMP_KNOB_MIN_VALUE,
				_AMP_KNOB_MAX_VALUE,
				4);
			
			on_amp1_pan_dial_changed(amp1_pan);
		}		
	}
	else if (evnt == _CONTROL_ENCODER_BLUE_RED)
	{
		if (active_frames_group_filters_amps == _FRAMES_GROUP_1)
		{
			/* Filter 1 Q */
			filter1_q_entry = update_rotary_encoder_value(
				filter1_q_entry,
				val,
				&prev_knob_filter1_q,
				_FILTER_KNOB_MIN_VALUE,
				_FILTER_KNOB_MAX_VALUE,
				4);
			
			on_filter1_q_dial_changed(filter1_q_entry);
		}
		else if (active_frames_group_filters_amps == _FRAMES_GROUP_2)
		{
			/* Filter 2 Q */
			filter2_q_entry = update_rotary_encoder_value(
				filter2_q_entry,
				val,
				&prev_knob_filter2_q,
				_FILTER_KNOB_MIN_VALUE,
				_FILTER_KNOB_MAX_VALUE,
				4);
			
			on_filter2_q_dial_changed(filter2_q_entry);
		}
		else if (active_frames_group_filters_amps == _FRAMES_GROUP_3)
		{
			/* Amp 1 Send */
			amp1_send = update_rotary_encoder_value(
				amp1_send,
				val,
				&prev_knob_amp1_send,
				_AMP_KNOB_MIN_VALUE,
				_AMP_KNOB_MAX_VALUE,
				4);
			
			on_amp1_send_dial_changed(amp1_send);
		}		
	}
	else if (evnt == _CONTROL_ENCODER_BLUE_BLUE)
	{
		if (active_frames_group_filters_amps == _FRAMES_GROUP_1)
		{
			/* Filter 1 Kbd Track */
			filter1_keyboard_track = update_rotary_encoder_value(
				filter1_keyboard_track,
				val,
				&prev_knob_filter1_kbd_track,
				_FILTER_KNOB_MIN_VALUE,
				_FILTER_KNOB_MAX_VALUE,
				4);
			
			on_filter1_kbd_track_dial_changed(filter1_keyboard_track);
		}
		else if (active_frames_group_filters_amps == _FRAMES_GROUP_2)
		{
			/* Filter 2 Kbd Track */
			filter2_keyboard_track = update_rotary_encoder_value(
				filter2_keyboard_track,
				val,
				&prev_knob_filter2_kbd_track,
				_FILTER_KNOB_MIN_VALUE,
				_FILTER_KNOB_MAX_VALUE,
				4);
			
			on_filter2_kbd_track_dial_changed(filter2_keyboard_track);
		}
		else if (active_frames_group_filters_amps == _FRAMES_GROUP_3)
		{
			/* Amp 1 Pan mod LFO Level */
			amp1_pan_mod_lfo_level = update_rotary_encoder_value(
				amp1_pan_mod_lfo_level,
				val,
				&prev_knob_amp1_pan_mod_lfo_level,
				_AMP_KNOB_MIN_VALUE,
				_AMP_KNOB_MAX_VALUE,
				4);
			
			on_amp1_pan_mod_level_lfo_dial_changed(amp1_pan_mod_lfo_level);
		}		
	}
	else if (evnt == _CONTROL_ENCODER_BLUE_WHITE)
	{
		if (active_frames_group_filters_amps == _FRAMES_GROUP_3)
		{
			/* Amp 1 Pan Mod LFO */
			amp1_pan_mod_lfo = update_rotary_encoder_value(
				amp1_pan_mod_lfo,
				val,
				&prev_combobox_amp1_pan_mod_lfo,
				_LFO_NONE,
				_LFO_5,
				1);
			
			on_amp1_pan_mod_lfo_combo_changed(amp1_pan_mod_lfo);
		}
	}
	else if (evnt == _CONTROL_ENCODER_ORANGE_PURPLE)
	{
		if (active_frames_group_filters_amps == _FRAMES_GROUP_1)
		{
			/* Filter 1 band */
			filter1_band = update_rotary_encoder_value(
				filter1_band,
				val,
				&prev_combobox_filter1_band,
				_FILTER_BAND_LPF,
				_FILTER_BAND_PASS_ALL,
				1);
			
			on_filter1_band_combo_hanged(filter1_band);
		}
		else if (active_frames_group_filters_amps == _FRAMES_GROUP_2)
		{
			/* Filter 2 band */
			filter2_band = update_rotary_encoder_value(
				filter2_band,
				val,
				&prev_combobox_filter2_band,
				_FILTER_BAND_LPF,
				_FILTER_BAND_PASS_ALL,
				1);
			
			on_filter2_band_combo_hanged(filter2_band);
		}
		else if (active_frames_group_filters_amps == _FRAMES_GROUP_3)
		{
			/* Amp 2 Amp */
			amp2_level = update_rotary_encoder_value(
				amp2_level,
				val,
				&prev_knob_amp2_level,
				_AMP_KNOB_MIN_VALUE,
				_AMP_KNOB_MAX_VALUE,
				4);
			
			on_amp2_level_dial_hanged(amp2_level);
		}		
	}
	else if (evnt == _CONTROL_ENCODER_ORANGE_GREEN)
	{
		if (active_frames_group_filters_amps == _FRAMES_GROUP_1)
		{
			/* Filter 1 Freq Mod LFO */
			filter1_freq_mod_lfo = update_rotary_encoder_value(
				filter1_freq_mod_lfo,
				val,
				&prev_combobox_filter1_freq_mod_lfo,
				_LFO_NONE,
				_LFO_6_DELAYED_2000MS,
				1);
			
			on_filter1_freq_mod_lfo_combo_changed(filter1_freq_mod_lfo);
		}
		else if (active_frames_group_filters_amps == _FRAMES_GROUP_2)
		{
			/* Filter 2 Freq Mod LFO */
			filter2_freq_mod_lfo = update_rotary_encoder_value(
				filter2_freq_mod_lfo,
				val,
				&prev_combobox_filter2_freq_mod_lfo,
				_LFO_NONE,
				_LFO_6_DELAYED_2000MS,
				1);
			
			on_filter2_freq_mod_lfo_combo_changed(filter2_freq_mod_lfo);
		}
		else if (active_frames_group_filters_amps == _FRAMES_GROUP_3)
		{
			/* Amp 2 Pan */
			amp2_pan = update_rotary_encoder_value(
				amp2_pan,
				val,
				&prev_knob_amp2_pan,
				_AMP_KNOB_MIN_VALUE,
				_AMP_KNOB_MAX_VALUE,
				4);
			
			on_amp2_pan_dial_changed(amp2_pan);
		}		
	}
	else if (evnt == _CONTROL_ENCODER_ORANGE_RED)
	{
		if (active_frames_group_filters_amps == _FRAMES_GROUP_1)
		{
			/* Filter 1 Freq Mod LFO Level */
			filter1_freq_mod_lfo_level = update_rotary_encoder_value(
				filter1_freq_mod_lfo_level,
				val,
				&prev_knob_filter1_freq_mod_lfo_level,
				_FILTER_KNOB_MIN_VALUE,
				_FILTER_KNOB_MAX_VALUE,
				4);
			
			on_filter1_freq_mod_level_lfo_dial_changed(filter1_freq_mod_lfo_level);
		}
		else if (active_frames_group_filters_amps == _FRAMES_GROUP_2)
		{
			/* Filter 2 Freq Mod LFO Level */
			filter2_freq_mod_lfo_level = update_rotary_encoder_value(
				filter2_freq_mod_lfo_level,
				val,
				&prev_knob_filter2_freq_mod_lfo_level,
				_FILTER_KNOB_MIN_VALUE,
				_FILTER_KNOB_MAX_VALUE,
				4);
			
			on_filter2_freq_mod_level_lfo_dial_changed(filter2_freq_mod_lfo_level);
		}
		else if (active_frames_group_filters_amps == _FRAMES_GROUP_3)
		{
			/* Amp 2 Send */
			amp2_send = update_rotary_encoder_value(
				amp2_send,
				val,
				&prev_knob_amp2_send,
				_AMP_KNOB_MIN_VALUE,
				_AMP_KNOB_MAX_VALUE,
				4);
			
			on_amp2_send_dial_changed(amp2_send);
		}		
	}
	else if (evnt == _CONTROL_ENCODER_ORANGE_BLUE)
	{
		if (active_frames_group_filters_amps == _FRAMES_GROUP_1)
		{
			/* Filter 1 Freq Mod ADSR */
			filter1_freq_mod_adsr = update_rotary_encoder_value(
				filter1_freq_mod_adsr,
				val,
				&prev_combobox_filter1_freq_mod_adsr,
				_ENV_NONE,
				_ENV_6,
				1);
			
			on_filter1_freq_mod_adsr_combo_changed(filter1_freq_mod_adsr);
		}
		else if (active_frames_group_filters_amps == _FRAMES_GROUP_2)
		{
			/* Filter 2 Freq Mod ADSR */
			filter2_freq_mod_adsr = update_rotary_encoder_value(
				filter2_freq_mod_adsr,
				val,
				&prev_combobox_filter2_freq_mod_adsr,
				_ENV_NONE,
				_ENV_6,
				1);
			
			on_filter2_freq_mod_adsr_combo_changed(filter2_freq_mod_adsr);
		}
		else if (active_frames_group_filters_amps == _FRAMES_GROUP_3)
		{
			/* Amp 2 Pan mod LFO Level */
			amp2_pan_mod_lfo_level = update_rotary_encoder_value(
				amp2_pan_mod_lfo_level,
				val,
				&prev_knob_amp2_pan_mod_lfo_level,
				_AMP_KNOB_MIN_VALUE,
				_AMP_KNOB_MAX_VALUE,
				4);
			
			on_amp2_pan_mod_level_lfo_dial_changed(amp2_pan_mod_lfo_level);
		}		
	}
	else if (evnt == _CONTROL_ENCODER_ORANGE_WHITE)
	{
		if (active_frames_group_filters_amps == _FRAMES_GROUP_1)
		{
			/* Filter 1 Freq Mod ADSR Level */
			filter1_freq_mod_adsr_level = update_rotary_encoder_value(
				filter1_freq_mod_adsr_level,
				val,
				&prev_knob_filter1_freq_mod_adsr_level,
				_FILTER_KNOB_MIN_VALUE,
				_FILTER_KNOB_MAX_VALUE,
				4);
			
			on_filter1_freq_mod_level_adsr_dial_hanged(filter1_freq_mod_adsr_level);
		}
		else if (active_frames_group_filters_amps == _FRAMES_GROUP_2)
		{
			/* Filter 2 Freq Mod ADSR Level */
			filter2_freq_mod_adsr_level = update_rotary_encoder_value(
				filter2_freq_mod_adsr_level,
				val,
				&prev_knob_filter2_freq_mod_adsr_level,
				_FILTER_KNOB_MIN_VALUE,
				_FILTER_KNOB_MAX_VALUE,
				4);
			
			on_filter2_freq_mod_level_adsr_dial_hanged(filter2_freq_mod_adsr_level);
		}
		else if (active_frames_group_filters_amps == _FRAMES_GROUP_3)
		{
			/* Amp 2 Pan Mod LFO */
			amp2_pan_mod_lfo = update_rotary_encoder_value(
				amp2_pan_mod_lfo,
				val,
				&prev_combobox_amp2_pan_mod_lfo,
				_LFO_NONE,
				_LFO_5,
				1);
			
			on_amp2_pan_mod_lfo_combo_changed(amp2_pan_mod_lfo);
		}
	}
}

