/**
* @file		ControlBoxEventsHandler_AnalogSynthMso
*	@author		Nahum Budin
*	@date		1-Nov-2024
*	@version	1.0
*
*	@brief		Used for controling the Analog Synthesizer MSO Tab 
*				
*	History:
*			
*
*/

#include "Dialog_AnalogSynth.h"
#include "ui_Dialog_AnalogSynth.h"
#include "utils.h"

#include "libAdjRaspi5SynthAPI.h"

void Dialog_AnalogSynth::control_box_events_handler_mso(int evnt, uint16_t val)
{
	int level, level_slider_gap;
	Qt::CheckState checked;	
	
	static int prev_knob_mso_send_filter_1_val = 64;
	static int prev_knob_mso_send_filter_2_val = 64;
	static int prev_knob_mso_freq_lfo_mod_level = 64;
	static int prev_knob_mso_freq_adsr_mod_level = 64;
	static int prev_knob_mso_pwm_lfo_mod_level = 64;
	static int prev_knob_mso_pwm_adsr_mod_level = 64;
	static int prev_knob_mso_amp_lfo_mod_level = 64;
	static int prev_knob_mso_amp_adsr_mod_level = 64;
	
	static int prev_combobox_mso_freq_lfo = 64;
	static int prev_combobox_mso_pwm_lfo = 64;
	static int prev_combobox_mso_amp_lfo = 64;
	static int prev_combobox_mso_freq_adsr = 64;
	static int prev_combobox_mso_pwm_adsr = 64;
	static int prev_combobox_mso_amp_adsr = 64;
	static int prev_combobox_mso_preset = 64;	
	static int prev_combobox_mso_tune_octave = 64;
	static int prev_combobox_mso_tune_semitones = 64;
	static int prev_combobox_mso_tune_cents = 64;
	
	
	if (!this->hasFocus())
	{
		return;
	}
	
	if ((evnt == _CONTROL_FUNCTION_PUSHBUTTON_ENTER) &&
			 (val == 0))
	{
		/* Switch active frames */
		active_frames_group_mso++;
		
		if (active_frames_group_mso > _FRAMES_GROUP_3)
		{
			active_frames_group_mso = _FRAMES_GROUP_1;
		}		
	}
	else if (evnt == _CONTROL_PUSHBUTTON_BLUE_BLACK)
	{
		/* Enable Mso - allways active */
		if (val == 0)
		{
			/* Only when pushbutton is pressed */			
			checked = ui->checkBox_MsoActive->checkState();
			
			/* Toggle */
			if (checked == Qt::CheckState::Checked)
			{
				checked = Qt::CheckState::Unchecked;
			}
			else
			{
				checked = Qt::CheckState::Checked;
			}
							
			on_mso_enable_checkbox_changed(checked);
		}
	}	
	
	if (!mso_enabled)
	{
		return;
	}
	
	if (evnt == _CONTROL_SLIDER_BLUE_BLACK)
	{
		if (active_frames_group_mso == _FRAMES_GROUP_1)
		{
			/* Point a */
			level = normalize_slider_value(val, _MSO_POINT_MAX_VALUE, _MSO_POINT_MIN_VALUE);
			/* Change slider value only when it matches the UI slider position */
			if (mso_pos_a > _MSO_POINT_MAX_VALUE)
			{
				mso_pos_a = _MSO_POINT_MAX_VALUE; 
			}
			
			level_slider_gap = mso_pos_a - level;
			
			if (abs((float)level_slider_gap) < ((_MSO_POINT_MAX_VALUE - _MSO_POINT_MIN_VALUE) / 5.0))
			{
				on_mso_point_a_slider_moved(level);			
			}	
		}
	}	
	else if (evnt == _CONTROL_SLIDER_BLUE_GRAY)
	{
		if (active_frames_group_mso == _FRAMES_GROUP_1)
		{
			/* Point b */
			level = normalize_slider_value(val, _MSO_POINT_MAX_VALUE, _MSO_POINT_MIN_VALUE);
			/* Change slider value only when it matches the UI slider position */
			if (mso_pos_b > _MSO_POINT_MAX_VALUE)
			{
				mso_pos_b = _MSO_POINT_MAX_VALUE; 
			}
			
			level_slider_gap = mso_pos_b - level;
			
			if (abs((float)level_slider_gap) < ((_MSO_POINT_MAX_VALUE - _MSO_POINT_MIN_VALUE) / 5.0))
			{
				on_mso_point_b_slider_moved(level);			
			}	
		}
	}
	else if (evnt == _CONTROL_SLIDER_BLUE_RED)
	{
		if (active_frames_group_mso == _FRAMES_GROUP_1)
		{
			/* Point c */
			level = normalize_slider_value(val, _MSO_POINT_MAX_VALUE, _MSO_POINT_MIN_VALUE);
			/* Change slider value only when it matches the UI slider position */
			if (mso_pos_c > _MSO_POINT_MAX_VALUE)
			{
				mso_pos_c = _MSO_POINT_MAX_VALUE; 
			}
			
			level_slider_gap = mso_pos_c - level;
			
			if (abs((float)level_slider_gap) < ((_MSO_POINT_MAX_VALUE - _MSO_POINT_MIN_VALUE) / 5.0))
			{
				on_mso_point_c_slider_moved(level);			
			}	
		}
	}
	else if (evnt == _CONTROL_SLIDER_BLUE_BLUE)
	{
		if (active_frames_group_mso == _FRAMES_GROUP_1)
		{
			/* Point d */
			level = normalize_slider_value(val, _MSO_POINT_MAX_VALUE, _MSO_POINT_MIN_VALUE);
			/* Change slider value only when it matches the UI slider position */
			if (mso_pos_d > _MSO_POINT_MAX_VALUE)
			{
				mso_pos_d = _MSO_POINT_MAX_VALUE; 
			}
			
			level_slider_gap = mso_pos_d - level;
			
			if (abs((float)level_slider_gap) < ((_MSO_POINT_MAX_VALUE - _MSO_POINT_MIN_VALUE) / 5.0))
			{
				on_mso_point_d_slider_moved(level);			
			}	
		}
	}
	else if (evnt == _CONTROL_SLIDER_BLUE_WHITE)
	{
		if (active_frames_group_mso == _FRAMES_GROUP_1)
		{
			/* Point e */
			level = normalize_slider_value(val, _MSO_POINT_MAX_VALUE, _MSO_POINT_MIN_VALUE);
			/* Change slider value only when it matches the UI slider position */
			if (mso_pos_e > _MSO_POINT_MAX_VALUE)
			{
				mso_pos_e = _MSO_POINT_MAX_VALUE; 
			}
			
			level_slider_gap = mso_pos_e - level;
			
			if (abs((float)level_slider_gap) < ((_MSO_POINT_MAX_VALUE - _MSO_POINT_MIN_VALUE) / 5.0))
			{
				on_mso_point_e_slider_moved(level);			
			}	
		}
	}
	else if (evnt == _CONTROL_SLIDER_BLUE_YELLOW)
	{
		if (active_frames_group_mso == _FRAMES_GROUP_1)
		{
			/* Point f */
			level = normalize_slider_value(val, _MSO_POINT_MAX_VALUE, _MSO_POINT_MIN_VALUE);
			/* Change slider value only when it matches the UI slider position */
			if (mso_pos_f > _MSO_POINT_MAX_VALUE)
			{
				mso_pos_f = _MSO_POINT_MAX_VALUE; 
			}
			
			level_slider_gap = mso_pos_f - level;
			
			if (abs((float)level_slider_gap) < ((_MSO_POINT_MAX_VALUE - _MSO_POINT_MIN_VALUE) / 5.0))
			{
				on_mso_point_f_slider_moved(level);			
			}	
		}
	}
	else if (evnt == _CONTROL_SLIDER_ORANGE_BLACK)
	{
		
		if (active_frames_group_mso == _FRAMES_GROUP_1)
		{
			/* Symetry */
			level = normalize_slider_value(val, _MSO_MAX_SYMETRY, _MSO_MIN_SYMETRY);
			/* Change slider value only when it matches the UI slider position */
			if (mso_symetry > _MSO_MAX_SYMETRY)
			{
				mso_symetry = _MSO_MAX_SYMETRY; 
			}
			
			level_slider_gap = mso_symetry - level;
			
			if (abs((float)level_slider_gap) < ((_MSO_MAX_SYMETRY - _MSO_MIN_SYMETRY) / 5.0))
			{
				on_mso_symetry_slider_changed(level);			
			}	
		}
	}
	else if (evnt == _CONTROL_ENCODER_BLUE_PURPLE)
	{
		if (active_frames_group_mso == _FRAMES_GROUP_2)
		{
			/* Freq Mod LFO */
			mso_freq_mod_lfo_num = update_rotary_encoder_value(
				mso_freq_mod_lfo_num,
				val,
				&prev_combobox_mso_freq_lfo,
				_LFO_NONE,
				_LFO_6_DELAYED_2000MS,
				1);
			
			on_mso_freq_mod_lfo_combobox_changed(mso_freq_mod_lfo_num);
		}
		else if (active_frames_group_mso == _FRAMES_GROUP_3)
		{
			/* Send Filter 1 */
			mso_send_filter_1_level = update_rotary_encoder_value(
				mso_send_filter_1_level,
				val,
				&prev_knob_mso_send_filter_1_val,
				_SEND_FILTER_MIN,
				_SEND_FILTER_MAX,
				4);
			
			on_mso_send_filter_1_dial_changed(mso_send_filter_1_level);
		}
	}
	else if (evnt == _CONTROL_ENCODER_BLUE_GREEN)
	{
		if (active_frames_group_mso == _FRAMES_GROUP_2)
		{
			/* Freq Mod LFO Level */
			mso_freq_mod_lfo_level = update_rotary_encoder_value(
				mso_freq_mod_lfo_level,
				val,
				&prev_knob_mso_freq_lfo_mod_level,
				_MODULATION_LEVEL_MIN,
				_MODULATION_LEVEL_MAX,
				4);
			
			on_mso_freq_mod_lfo_level_dial_changed(mso_freq_mod_lfo_level);
		}
		else if (active_frames_group_mso == _FRAMES_GROUP_3)
		{
			/* Send Filter 2 */
			mso_send_filter_2_level = update_rotary_encoder_value(
				mso_send_filter_2_level,
				val,
				&prev_knob_mso_send_filter_2_val,
				_SEND_FILTER_MIN,
				_SEND_FILTER_MAX,
				4);
			
			on_mso_send_filter_2_dial_changed(mso_send_filter_2_level);
		}
	}
	else if (evnt == _CONTROL_ENCODER_BLUE_BLUE)
	{
		if (active_frames_group_mso == _FRAMES_GROUP_2)
		{
			/* Frequency Mod ADSR Level */
			mso_freq_mod_adsr_level = update_rotary_encoder_value(
				mso_freq_mod_adsr_level,
				val,
				&prev_knob_mso_freq_adsr_mod_level,
				_MODULATION_LEVEL_MIN,
				_MODULATION_LEVEL_MAX,
				4);

			on_mso_freq_mod_env_level_dial_changed(mso_freq_mod_adsr_level);
		}
		else if (active_frames_group_mso == _FRAMES_GROUP_3)
		{
			/* Tune Octave */
			mso_tune_octave = update_rotary_encoder_value(
				mso_tune_octave,
				val,
				&prev_combobox_mso_tune_octave,
				0,
				_OSC_DETUNE_MAX_OCTAVE - _OSC_DETUNE_MIN_OCTAVE,
				1);
			
			on_mso_detune_octave_combobox_changed(mso_tune_octave);
		}
	}
	else if (evnt == _CONTROL_ENCODER_BLUE_RED)
	{
		if (active_frames_group_mso == _FRAMES_GROUP_2)
		{
			/* Freq Mod ADSR */
			mso_freq_mod_adsr_num = update_rotary_encoder_value(
				mso_freq_mod_adsr_num,
				val,
				&prev_combobox_mso_freq_adsr,
				_ENV_NONE,
				_ENV_6,
				1);
			
			on_mso_freq_mod_env_combobox_changed(mso_freq_mod_adsr_num);
		}
	}
	else if (evnt == _CONTROL_ENCODER_BLUE_WHITE)
	{
		if (active_frames_group_mso == _FRAMES_GROUP_3)
		{
			/* Tune Semitones */
			mso_tune_semitones = update_rotary_encoder_value(
				mso_tune_semitones,
				val,
				&prev_combobox_mso_tune_semitones,
				0,
				_OSC_DETUNE_MAX_SEMITONES - _OSC_DETUNE_MIN_SEMITONES,
				1);
			
			on_mso_detune_semitones_combobox_changed(mso_tune_semitones);
		}
	}
	else if (evnt == _CONTROL_ENCODER_BLUE_YELLOW)
	{
		if (active_frames_group_mso == _FRAMES_GROUP_3)
		{
			/* Tune Cents */
			mso_tune_cents = update_rotary_encoder_value(
				mso_tune_cents,
				val,
				&prev_combobox_mso_tune_cents,
				0,
				(int)((_OSC_DETUNE_MAX_CENTS - _OSC_DETUNE_MIN_CENTS) / _OSC_DETUNE_CENTS_FACTORIAL),
				1);
			
			on_mso_detune_cents_combobox_changed(mso_tune_cents);
		}
	}
	else if (evnt == _CONTROL_ENCODER_ORANGE_RED)
	{
		if (active_frames_group_mso == _FRAMES_GROUP_1)
		{
			/* Presets */
			mso_preset = update_rotary_encoder_value(
				mso_preset,
				val,
				&prev_combobox_mso_preset,
				_MSO_PRESET_USER,
				_MSO_PRESET_SAW,
				1);
			
			on_mso_preset_combobox_changed(mso_preset);
		}
		else if (active_frames_group_mso == _FRAMES_GROUP_2)
		{
			/* PWM Mod ADSR */
			mso_pwm_mod_adsr_num = update_rotary_encoder_value(
				mso_pwm_mod_adsr_num,
				val,
				&prev_combobox_mso_pwm_adsr,
				_ENV_NONE,
				_ENV_6,
				1);
			
			on_mso_pwm_mod_env_combobox_changed(mso_pwm_mod_adsr_num);
		}
		else if (active_frames_group_mso == _FRAMES_GROUP_3)
		{
			/* Amp Mod ADSR */
			mso_amp_mod_adsr_num = update_rotary_encoder_value(
				mso_amp_mod_adsr_num,
				val,
				&prev_combobox_mso_amp_adsr,
				_ENV_NONE,
				_ENV_6,
				1);
			
			on_mso_amp_mod_env_combobox_changed(mso_amp_mod_adsr_num);
		}
	}
	else if (evnt == _CONTROL_ENCODER_ORANGE_PURPLE)
	{
		if (active_frames_group_mso == _FRAMES_GROUP_2)
		{
			/* PWM Mod LFO */
			mso_pwm_mod_lfo_num = update_rotary_encoder_value(
				mso_pwm_mod_lfo_num,
				val,
				&prev_combobox_mso_pwm_lfo,
				_LFO_NONE,
				_LFO_6_DELAYED_2000MS,
				1);
			
			on_mso_pwm_mod_lfo_combobox_changed(mso_pwm_mod_lfo_num);
		}
		else if (active_frames_group_mso == _FRAMES_GROUP_3)
		{
			/* Amp Mod LFO */
			mso_amp_mod_lfo_num = update_rotary_encoder_value(
				mso_amp_mod_lfo_num,
				val,
				&prev_combobox_mso_amp_lfo,
				_LFO_NONE,
				_LFO_6_DELAYED_2000MS,
				1);
			
			on_mso_amp_mod_lfo_combobox_changed(mso_amp_mod_lfo_num);
		}
	}
	else if (evnt == _CONTROL_ENCODER_ORANGE_GREEN)
	{
		if (active_frames_group_mso == _FRAMES_GROUP_2)
		{
			/* PWM Mod LFO Level */
			mso_pwm_mod_lfo_level = update_rotary_encoder_value(
				mso_pwm_mod_lfo_level,
				val,
				&prev_knob_mso_pwm_lfo_mod_level,
				_MODULATION_LEVEL_MIN,
				_MODULATION_LEVEL_MAX,
				4);
			
			on_mso_pwm_mod_lfo_level_dial_changed(mso_pwm_mod_lfo_level);
		}
		else if (active_frames_group_mso == _FRAMES_GROUP_3)
		{
			/* Amp Mod LFO Level */
			mso_amp_mod_lfo_level = update_rotary_encoder_value(
				mso_amp_mod_lfo_level,
				val,
				&prev_knob_mso_amp_lfo_mod_level,
				_MODULATION_LEVEL_MIN,
				_MODULATION_LEVEL_MAX,
				4);
			
			on_mso_amp_mod_lfo_level_dial_changed(mso_amp_mod_lfo_level);
		}
	}
	else if (evnt == _CONTROL_ENCODER_ORANGE_BLUE)
	{
		if (active_frames_group_mso == _FRAMES_GROUP_2)
		{
			/* Pwm Mod ADSR Level */
			mso_pwm_mod_adsr_level = update_rotary_encoder_value(
				mso_pwm_mod_adsr_level,
				val,
				&prev_knob_mso_pwm_adsr_mod_level,
				_MODULATION_LEVEL_MIN,
				_MODULATION_LEVEL_MAX,
				4);

			on_mso_pwm_mod_env_level_dial_changed(mso_pwm_mod_adsr_level);
		}
		else if (active_frames_group_mso == _FRAMES_GROUP_3)
		{
			/* Amp Mod ADSR Level */
			mso_amp_mod_adsr_level = update_rotary_encoder_value(
				mso_amp_mod_adsr_level,
				val,
				&prev_knob_mso_amp_adsr_mod_level,
				_MODULATION_LEVEL_MIN,
				_MODULATION_LEVEL_MAX,
				4);

			on_mso_amp_mod_env_level_dial_changed(mso_amp_mod_adsr_level);
		}
	}	
}
