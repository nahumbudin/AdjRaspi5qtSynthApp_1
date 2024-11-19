/**
* @file		ControlBoxEventsHandler_AnalogSynthKps
*	@author		Nahum Budin
*	@date		11-Nov-2024
*	@version	1.0
*
*	@brief		Used for controling the Analog Synthesizer Karplus Strong String Synthesizer Tab 
*				
*	History:
*			
*
*/

#include "Dialog_AnalogSynth.h"
#include "ui_Dialog_AnalogSynth.h"
#include "utils.h"

#include "libAdjRaspi5SynthAPI.h"

void Dialog_AnalogSynth::control_box_events_handler_kps(int evnt, uint16_t val)
{
	int level, level_slider_gap;
	Qt::CheckState checked;	
	
	static int prev_knob_kps_send_filter_1_val = 64;
	static int prev_knob_kps_send_filter_2_val = 64;
	
	static int prev_combobox_kps_waveform = 64;
	static int prev_combobox_kps_calc_mode = 64;
	
	if (!this->hasFocus())
	{
		return;
	}
	
	if ((evnt == _CONTROL_FUNCTION_PUSHBUTTON_ENTER) &&
			 (val == 0))
	{
		/* Switch active frames Place holder */
		active_frames_group_kps++;
		
		if (active_frames_group_kps > _FRAMES_GROUP_1)
		{
			active_frames_group_kps = _FRAMES_GROUP_1;
		}		
	}
	else if (evnt == _CONTROL_PUSHBUTTON_BLUE_BLACK)
	{
		/* Enable KPS - allways active */
		if (val == 0)
		{
			/* Only when pushbutton is pressed */			
			checked = ui->checkBox_KarplusSynth_Active->checkState();
			
			/* Toggle */
			if (checked == Qt::CheckState::Checked)
			{
				checked = Qt::CheckState::Unchecked;
			}
			else
			{
				checked = Qt::CheckState::Checked;
			}
							
			on_karplus_enable_checkbox_changed(checked);
		}
	}	
	
	if (!kps_enabled)
	{
		return;
	}
	
	if (evnt == _CONTROL_SLIDER_BLUE_BLACK)
	{
		if (active_frames_group_kps == _FRAMES_GROUP_1)
		{
			/* Waveform Variations */
			level = normalize_slider_value(val, _KPS_MAX_SLIDER_VALUE, _KPS_MIN_SLIDER_VALUE);
			/* Change slider value only when it matches the UI slider position */
			if (kps_waveform_variations > _KPS_MAX_SLIDER_VALUE)
			{
				kps_waveform_variations = _KPS_MAX_SLIDER_VALUE; // TODO: how did we get here?
			}
			level_slider_gap = kps_waveform_variations - level;
			
			if (abs((float)level_slider_gap) < ((_KPS_MAX_SLIDER_VALUE - _KPS_MIN_SLIDER_VALUE) / 5.0))
			{
				on_karplus_excitation_waveform_variations_slider_changed(level);
			}
		}
	}
	else if (evnt == _CONTROL_SLIDER_BLUE_GRAY)
	{
		if (active_frames_group_kps == _FRAMES_GROUP_1)
		{
			/* On Decay */
			level = normalize_slider_value(val, _KPS_MAX_SLIDER_VALUE, _KPS_MIN_SLIDER_VALUE);
			/* Change slider value only when it matches the UI slider position */
			if (kps_on_decay > _KPS_MAX_SLIDER_VALUE)
			{
				kps_on_decay = _KPS_MAX_SLIDER_VALUE; // TODO: how did we get here?
			}
			level_slider_gap = kps_on_decay - level;
			
			if (abs((float)level_slider_gap) < ((_KPS_MAX_SLIDER_VALUE - _KPS_MIN_SLIDER_VALUE) / 5.0))
			{
				on_karplus_on_decay_slider_changed(level);
			}
		}
	}
	else if (evnt == _CONTROL_SLIDER_BLUE_RED)
	{
		if (active_frames_group_kps == _FRAMES_GROUP_1)
		{
			/* Off Decay */
			level = normalize_slider_value(val, _KPS_MAX_SLIDER_VALUE, _KPS_MIN_SLIDER_VALUE);
			/* Change slider value only when it matches the UI slider position */
			if (kps_off_decay > _KPS_MAX_SLIDER_VALUE)
			{
				kps_off_decay = _KPS_MAX_SLIDER_VALUE; // TODO: how did we get here?
			}
			level_slider_gap = kps_off_decay - level;
			
			if (abs((float)level_slider_gap) < ((_KPS_MAX_SLIDER_VALUE - _KPS_MIN_SLIDER_VALUE) / 5.0))
			{
				on_karplus_off_decay_slider_changed(level);
			}
		}
	}
	else if (evnt == _CONTROL_SLIDER_BLUE_BLUE)
	{
		if (active_frames_group_kps == _FRAMES_GROUP_1)
		{
			/* String Damping */
			if (active_frames_group_kps == _FRAMES_GROUP_1)
			{
				/* Off Decay */
				level = normalize_slider_value(val, _KPS_MAX_SLIDER_VALUE, _KPS_MIN_SLIDER_VALUE);
				/* Change slider value only when it matches the UI slider position */
				if (kps_string_damping > _KPS_MAX_SLIDER_VALUE)
				{
					kps_string_damping = _KPS_MAX_SLIDER_VALUE; // TODO: how did we get here?
				}
				level_slider_gap = kps_string_damping - level;
			
				if (abs((float)level_slider_gap) < ((_KPS_MAX_SLIDER_VALUE - _KPS_MIN_SLIDER_VALUE) / 5.0))
				{
					on_karplus_string_damping_slider_changed(level);
				}
			}
		}
	}
	else if (evnt == _CONTROL_SLIDER_BLUE_WHITE)
	{
		if (active_frames_group_kps == _FRAMES_GROUP_1)
		{
			/* String Damping Variations */
			if (active_frames_group_kps == _FRAMES_GROUP_1)
			{
				/* Off Decay */
				level = normalize_slider_value(val, _KPS_MAX_SLIDER_VALUE, _KPS_MIN_SLIDER_VALUE);
				/* Change slider value only when it matches the UI slider position */
				if (kps_string_damping_variations > _KPS_MAX_SLIDER_VALUE)
				{
					kps_string_damping_variations = _KPS_MAX_SLIDER_VALUE; // TODO: how did we get here?
				}
				level_slider_gap = kps_string_damping_variations - level;
			
				if (abs((float)level_slider_gap) < ((_KPS_MAX_SLIDER_VALUE - _KPS_MIN_SLIDER_VALUE) / 5.0))
				{
					on_karplus_string_damping_variation_slider_changed(level);
				}
			}
		}
	}
	else if (evnt == _CONTROL_SLIDER_BLUE_YELLOW)
	{
		if (active_frames_group_kps == _FRAMES_GROUP_1)
		{
			/* Pluck Damping */
			level = normalize_slider_value(val, _KPS_MAX_SLIDER_VALUE, _KPS_MIN_SLIDER_VALUE);
			/* Change slider value only when it matches the UI slider position */
			if (kps_pluck_damping > _KPS_MAX_SLIDER_VALUE)
			{
				kps_pluck_damping = _KPS_MAX_SLIDER_VALUE; // TODO: how did we get here?
			}
			level_slider_gap = kps_pluck_damping - level;
			
			if (abs((float)level_slider_gap) < ((_KPS_MAX_SLIDER_VALUE - _KPS_MIN_SLIDER_VALUE) / 5.0))
			{
				on_karplus_pluck_damping_slider_changed(level);
			}
		}
	}
	else if (evnt == _CONTROL_SLIDER_ORANGE_BLACK)
	{
		if (active_frames_group_kps == _FRAMES_GROUP_1)
		{
			/* Pluck Damping Variations */
			level = normalize_slider_value(val, _KPS_MAX_SLIDER_VALUE, _KPS_MIN_SLIDER_VALUE);
			/* Change slider value only when it matches the UI slider position */
			if (kps_pluck_damping_variations > _KPS_MAX_SLIDER_VALUE)
			{
				kps_pluck_damping_variations = _KPS_MAX_SLIDER_VALUE; // TODO: how did we get here?
			}
			level_slider_gap = kps_pluck_damping_variations - level;
			
			if (abs((float)level_slider_gap) < ((_KPS_MAX_SLIDER_VALUE - _KPS_MIN_SLIDER_VALUE) / 5.0))
			{
				on_karplus_pluck_damping_variation_slider_changed(level);
			}
		}
	}
	else if (evnt == _CONTROL_ENCODER_BLUE_PURPLE)
	{
		if (active_frames_group_kps == _FRAMES_GROUP_1)
		{
			/* Send Filter 1 */
			kps_send_filter_1_level = update_rotary_encoder_value(
				kps_send_filter_1_level,
				val,
				&prev_knob_kps_send_filter_1_val,
				_SEND_FILTER_MIN,
				_SEND_FILTER_MAX,
				4);
			
			on_karplus_send_filter1_dial_changed(kps_send_filter_1_level);
		}
	}
	else if (evnt == _CONTROL_ENCODER_BLUE_GREEN)
	{
		if (active_frames_group_kps == _FRAMES_GROUP_1)
		{
			/* Send Filter 2 */
			kps_send_filter_2_level = update_rotary_encoder_value(
				kps_send_filter_2_level,
				val,
				&prev_knob_kps_send_filter_2_val,
				_SEND_FILTER_MIN,
				_SEND_FILTER_MAX,
				4);
			
			on_karplus_send_filter2_dial_changed(kps_send_filter_2_level);
		}
	}
	else if (evnt == _CONTROL_ENCODER_BLUE_BLUE)
	{
		if (active_frames_group_kps == _FRAMES_GROUP_1)
		{
			/* Waveform Combobox */
			kps_excitation_waveform = update_rotary_encoder_value(
				kps_excitation_waveform,
				val,
				&prev_combobox_kps_waveform,
				_KARPLUS_STRONG_EXCITATION_WHITE_NOISE,
				_KARPLUS_STRONG_EXCITATION_SQUARE_WAVE,
				1);
			
			on_karplus_excitation_waveform_combobox_changed(kps_excitation_waveform);
		}
	}
	else if (evnt == _CONTROL_ENCODER_BLUE_WHITE)
	{
		if (active_frames_group_kps == _FRAMES_GROUP_1)
		{
			/* Calc Mode Combobox */
			kps_string_dump_calculation_mode = update_rotary_encoder_value(
				kps_string_dump_calculation_mode,
				val,
				&prev_combobox_kps_calc_mode,
				_KARPLUS_STRONG_STRING_DAMPING_CALC_DIRECT,
				_KARPLUS_STRONG_STRING_DAMPING_CALC_MAGIC,
				1);
			
			on_karplus_string_damping_calc_mode_combobox_hanged(kps_string_dump_calculation_mode);
		}
	}	
}

