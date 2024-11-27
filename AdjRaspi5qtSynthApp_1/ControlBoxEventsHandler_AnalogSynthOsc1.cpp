/**
* @file		ControlBoxEventsHandler_AnalogSynthOsc1
*	@author		Nahum Budin
*	@date		26-Oct-2024
*	@version	1.0
*
*	@brief		Used for controling the Analog Synthesizer Osc1 Tab 
*				
*	History:
*			
*
*/

#include "Dialog_AnalogSynth.h"
#include "ui_Dialog_AnalogSynth.h"
#include "utils.h"

#include "libAdjRaspi5SynthAPI.h"

void Dialog_AnalogSynth::control_box_events_handler_osc_1(int evnt, uint16_t val)
{
	int level, level_slider_gap;
	Qt::CheckState checked;
	
	static int prev_knob_send_filter_1_val = 64;
	static int prev_knob_send_filter_2_val = 64;
	static int prev_knob_freq_lfo_mod_level = 64;
	static int prev_knob_freq_adsr_mod_level = 64;
	static int prev_knob_pwm_lfo_mod_level = 64;
	static int prev_knob_pwm_adsr_mod_level = 64;
	static int prev_knob_amp_lfo_mod_level = 64;
	static int prev_knob_amp_adsr_mod_level = 64;
	static int prev_combobox_freq_lfo = 64;
	static int prev_combobox_pwm_lfo = 64;
	static int prev_combobox_amp_lfo = 64;
	static int prev_combobox_freq_adsr = 64;
	static int prev_combobox_pwm_adsr = 64;
	static int prev_combobox_amp_adsr = 64;
	static int prev_combobox_waveform = 64;
	static int prev_combobox_unison_mode = 64;
	static int prev_combobox_hammond_percussion_mode = 64;
	static int prev_combobox_tune_octave = 64;
	static int prev_combobox_tune_semitones = 64;
	static int prev_combobox_tune_cents = 64;
	
	if (!this->hasFocus())
	{
		return;
	}
	
	if ((evnt == _CONTROL_FUNCTION_PUSHBUTTON_ENTER) &&
			 (val == 0))
	{
		/* Switch active frames */
		active_frames_group_osc1++;
		if (active_frames_group_osc1 > _FRAMES_GROUP_3)
		{
			active_frames_group_osc1 = _FRAMES_GROUP_1;
		}		
	}	
	else if (evnt == _CONTROL_PUSHBUTTON_BLUE_BLACK)
	{
		/* Enable Osc1 - allways active */
		if (val == 0)
		{
			/* Only when pushbutton is pressed */			
			checked = ui->checkBox_Osc1Active->checkState();
			
			/* Toggle */
			if (checked == Qt::CheckState::Checked)
			{
				checked = Qt::CheckState::Unchecked;
			}
			else
			{
				checked = Qt::CheckState::Checked;
			}
							
			on_osc1_enable_changed(checked);
		}
	}
	
	if (!osc1_enabled)
	{
		return;
	}
	
	if (evnt == _CONTROL_PUSHBUTTON_BLUE_GREEN)
	{
		if (active_frames_group_osc1 == _FRAMES_GROUP_3)
		{
			/* Unison Square */
			if (val == 0)
			{
				/* Only when pushbutton is pressed */			
				checked = ui->checkBox_Osc1UnisonSquareWave->checkState();
			
				/* Toggle */
				if (checked == Qt::CheckState::Checked)
				{
					checked = Qt::CheckState::Unchecked;
				}
				else
				{
					checked = Qt::CheckState::Checked;
				}
							
				on_osc1_unison_sqare_enable_changed(checked);
			}
		}		
	}
	else if (evnt == _CONTROL_SLIDER_BLUE_BLACK)
	{
		if (active_frames_group_osc1 == _FRAMES_GROUP_1)
		{
			/* Waveform Symetry */
			level = normalize_slider_value(val, _OSC_WAVEFORM_SYMETRY_MAX, _OSC_WAVEFORM_SYMETRY_MIN);
			/* Change slider value only when it matches the UI slider position */
			if (osc1_waveform_symetry > _OSC_WAVEFORM_SYMETRY_MAX)
			{
				osc1_waveform_symetry = _OSC_WAVEFORM_SYMETRY_MAX; // TODO: how did we get here?
			}
			level_slider_gap = osc1_waveform_symetry - level;
			
			if (abs((float)level_slider_gap) < ((_OSC_WAVEFORM_SYMETRY_MAX - _OSC_WAVEFORM_SYMETRY_MIN) / 5.0))
			{
				on_osc1_waveform_symetry_slider_cahanged(level);
			}
		}
		else if (active_frames_group_osc1 == _FRAMES_GROUP_3)
		{
			/* Harmony 1 */
			level = normalize_slider_value(val, _OSC1_UNISON_LEVEL_MAX, _OSC1_UNISON_LEVEL_MIN);
			/* Change slider value only when it matches the UI slider position */
			if (osc1_unison_levels[0] > _OSC1_UNISON_LEVEL_MAX)
			{
				osc1_unison_levels[0] = _OSC1_UNISON_LEVEL_MAX; // TODO: how did we get here?
			}
			level_slider_gap = osc1_unison_levels[0] - level;
			
			if (abs((float)level_slider_gap) < ((_OSC1_UNISON_LEVEL_MAX - _OSC1_UNISON_LEVEL_MIN) / 5.0))
			{
				on_osc1_unison_level_1_slider_changed(level);			
			}		
		}
	}
	else if (evnt == _CONTROL_SLIDER_BLUE_GRAY)
	{
		if (active_frames_group_osc1 == _FRAMES_GROUP_3)
		{
			/* Harmony 2 */
			level = normalize_slider_value(val, _OSC1_UNISON_LEVEL_MAX, _OSC1_UNISON_LEVEL_MIN);
			/* Change slider value only when it matches the UI slider position */
			if (osc1_unison_levels[1] > _OSC1_UNISON_LEVEL_MAX)
			{
				osc1_unison_levels[1] = _OSC1_UNISON_LEVEL_MAX; // TODO: how did we get here?
			}
			level_slider_gap = osc1_unison_levels[1] - level;
			
			if (abs((float)level_slider_gap) < ((_OSC1_UNISON_LEVEL_MAX - _OSC1_UNISON_LEVEL_MIN) / 5.0))
			{
				on_osc1_unison_level_2_slider_changed(level);			
			}		
		}
	}
	else if (evnt == _CONTROL_SLIDER_BLUE_RED)
	{
		if (active_frames_group_osc1 == _FRAMES_GROUP_3)
		{
			/* Harmony 3 */
			level = normalize_slider_value(val, _OSC1_UNISON_LEVEL_MAX, _OSC1_UNISON_LEVEL_MIN);
			/* Change slider value only when it matches the UI slider position */
			if (osc1_unison_levels[2] > _OSC1_UNISON_LEVEL_MAX)
			{
				osc1_unison_levels[2] = _OSC1_UNISON_LEVEL_MAX; // TODO: how did we get here?
			}
			level_slider_gap = osc1_unison_levels[2] - level;
			
			if (abs((float)level_slider_gap) < ((_OSC1_UNISON_LEVEL_MAX - _OSC1_UNISON_LEVEL_MIN) / 5.0))
			{
				on_osc1_unison_level_3_slider_changed(level);			
			}		
		}
	}
	else if (evnt == _CONTROL_SLIDER_BLUE_BLUE)
	{
		if (active_frames_group_osc1 == _FRAMES_GROUP_3)
		{
			/* Harmony 4 */
			level = normalize_slider_value(val, _OSC1_UNISON_LEVEL_MAX, _OSC1_UNISON_LEVEL_MIN);
			/* Change slider value only when it matches the UI slider position */
			if (osc1_unison_levels[3] > _OSC1_UNISON_LEVEL_MAX)
			{
				osc1_unison_levels[3] = _OSC1_UNISON_LEVEL_MAX; // TODO: how did we get here?
			}
			level_slider_gap = osc1_unison_levels[3] - level;
			
			if (abs((float)level_slider_gap) < ((_OSC1_UNISON_LEVEL_MAX - _OSC1_UNISON_LEVEL_MIN) / 5.0))
			{
				on_osc1_unison_level_4_slider_changed(level);			
			}		
		}
	}
	else if (evnt == _CONTROL_SLIDER_BLUE_WHITE)
	{
		if (active_frames_group_osc1 == _FRAMES_GROUP_3)
		{
			/* Harmony 5 */
			level = normalize_slider_value(val, _OSC1_UNISON_LEVEL_MAX, _OSC1_UNISON_LEVEL_MIN);
			/* Change slider value only when it matches the UI slider position */
			if (osc1_unison_levels[4] > _OSC1_UNISON_LEVEL_MAX)
			{
				osc1_unison_levels[4] = _OSC1_UNISON_LEVEL_MAX; // TODO: how did we get here?
			}
			level_slider_gap = osc1_unison_levels[4] - level;
			
			if (abs((float)level_slider_gap) < ((_OSC1_UNISON_LEVEL_MAX - _OSC1_UNISON_LEVEL_MIN) / 5.0))
			{
				on_osc1_unison_level_5_slider_changed(level);			
			}		
		}
	}
	else if (evnt == _CONTROL_SLIDER_BLUE_YELLOW)
	{
		if (active_frames_group_osc1 == _FRAMES_GROUP_3)
		{
			/* Harmony 6 */
			level = normalize_slider_value(val, _OSC1_UNISON_LEVEL_MAX, _OSC1_UNISON_LEVEL_MIN);
			/* Change slider value only when it matches the UI slider position */
			if (osc1_unison_levels[5] > _OSC1_UNISON_LEVEL_MAX)
			{
				osc1_unison_levels[5] = _OSC1_UNISON_LEVEL_MAX; // TODO: how did we get here?
			}
			level_slider_gap = osc1_unison_levels[5] - level;
			
			if (abs((float)level_slider_gap) < ((_OSC1_UNISON_LEVEL_MAX - _OSC1_UNISON_LEVEL_MIN) / 5.0))
			{
				on_osc1_unison_level_6_slider_changed(level);			
			}		
		}
	}
	else if (evnt == _CONTROL_SLIDER_ORANGE_BLACK)
	{
		if (active_frames_group_osc1 == _FRAMES_GROUP_3)
		{
			/* Harmony 7 */
			level = normalize_slider_value(val, _OSC1_UNISON_LEVEL_MAX, _OSC1_UNISON_LEVEL_MIN);
			/* Change slider value only when it matches the UI slider position */
			if (osc1_unison_levels[6] > _OSC1_UNISON_LEVEL_MAX)
			{
				osc1_unison_levels[6] = _OSC1_UNISON_LEVEL_MAX; // TODO: how did we get here?
			}
			level_slider_gap = osc1_unison_levels[6] - level;
			
			if (abs((float)level_slider_gap) < ((_OSC1_UNISON_LEVEL_MAX - _OSC1_UNISON_LEVEL_MIN) / 5.0))
			{
				on_osc1_unison_level_7_slider_changed(level);			
			}		
		}
	}
	else if (evnt == _CONTROL_SLIDER_ORANGE_GRAY)
	{
		if (active_frames_group_osc1 == _FRAMES_GROUP_3)
		{
			/* Harmony 8 */
			level = normalize_slider_value(val, _OSC1_UNISON_LEVEL_MAX, _OSC1_UNISON_LEVEL_MIN);
			/* Change slider value only when it matches the UI slider position */
			if (osc1_unison_levels[7] > _OSC1_UNISON_LEVEL_MAX)
			{
				osc1_unison_levels[7] = _OSC1_UNISON_LEVEL_MAX; // TODO: how did we get here?
			}
			level_slider_gap = osc1_unison_levels[7] - level;
			
			if (abs((float)level_slider_gap) < ((_OSC1_UNISON_LEVEL_MAX - _OSC1_UNISON_LEVEL_MIN) / 5.0))
			{
				on_osc1_unison_level_8_slider_changed(level);			
			}		
		}
	}
	else if (evnt == _CONTROL_SLIDER_ORANGE_RED)
	{
		if (active_frames_group_osc1 == _FRAMES_GROUP_3)
		{
			/* Harmony 9 */
			level = normalize_slider_value(val, _OSC1_UNISON_LEVEL_MAX, _OSC1_UNISON_LEVEL_MIN);
			/* Change slider value only when it matches the UI slider position */
			if (osc1_unison_levels[8] > _OSC1_UNISON_LEVEL_MAX)
			{
				osc1_unison_levels[8] = _OSC1_UNISON_LEVEL_MAX; // TODO: how did we get here?
			}
			level_slider_gap = osc1_unison_levels[8] - level;
			
			if (abs((float)level_slider_gap) < ((_OSC1_UNISON_LEVEL_MAX - _OSC1_UNISON_LEVEL_MIN) / 5.0))
			{
				on_osc1_unison_level_9_slider_changed(level);			
			}		
		}
	}
	else if (evnt == _CONTROL_SLIDER_ORANGE_BLUE)
	{
		if (active_frames_group_osc1 == _FRAMES_GROUP_3)
		{
			/* Unison Distortion */
			level = normalize_slider_value(val, _OSC1_UNISON_DISTORTION_MAX, _OSC1_UNISON_DISTORTION_MIN);
			/* Change slider value only when it matches the UI slider position */
			if (osc_1_unison_distortion > _OSC1_UNISON_DISTORTION_MAX)
			{
				osc_1_unison_distortion = _OSC1_UNISON_DISTORTION_MAX; // TODO: how did we get here?
			}
			level_slider_gap = osc_1_unison_distortion - level;
			
			if (abs((float)level_slider_gap) < ((_OSC1_UNISON_DISTORTION_MAX - _OSC1_UNISON_DISTORTION_MIN) / 5.0))
			{
				on_osc1_unison_distortion_slider_changed(level);			
			}	
		}
	}
	else if (evnt == _CONTROL_SLIDER_ORANGE_WHITE)
	{
		if (active_frames_group_osc1 == _FRAMES_GROUP_3)
		{
			/* Unison Detune */
			level = normalize_slider_value(val, _OSC1_UNISON_DETUNE_MAX, _OSC1_UNISON_DETUNE_MIN);
			/* Change slider value only when it matches the UI slider position */
			if (osc_1_unison_detune > _OSC1_UNISON_DETUNE_MAX)
			{
				osc_1_unison_detune = _OSC1_UNISON_DETUNE_MAX; // TODO: how did we get here?
			}
			level_slider_gap = osc_1_unison_detune - level;
			
			if (abs((float)level_slider_gap) < ((_OSC1_UNISON_DETUNE_MAX - _OSC1_UNISON_DETUNE_MIN) / 5.0))
			{
				on_osc1_unison_detune_slider_changed(level);			
			}
		}
	}
	else if (evnt == _CONTROL_ENCODER_BLUE_PURPLE)
	{
		if (active_frames_group_osc1 == _FRAMES_GROUP_1)
		{
			/* Send Filter 1 */
			osc1_send_filter_1_level = update_rotary_encoder_value(
				osc1_send_filter_1_level,
				val,
				&prev_knob_send_filter_1_val,
				_SEND_FILTER_MIN,
				_SEND_FILTER_MAX,
				4);
			
			on_osc1_send_filter_1_dial_changed(osc1_send_filter_1_level);
		}
		else if (active_frames_group_osc1 == _FRAMES_GROUP_2)
		{
			/* Select PWM Modulation LFO */
			osc1_pwm_mod_lfo_num = update_rotary_encoder_value(
				osc1_pwm_mod_lfo_num,
				val,
				&prev_combobox_pwm_lfo,
				_LFO_NONE,
				_LFO_6_DELAYED_2000MS,
				1);
			
			on_osc1_pwm_mod_lfo_combobox_changed(osc1_pwm_mod_lfo_num);
		}		
	}
	else if (evnt == _CONTROL_ENCODER_BLUE_GREEN)
	{
		if (active_frames_group_osc1 == _FRAMES_GROUP_1)
		{
			/* Send Filter 2 */
			osc1_send_filter_2_level = update_rotary_encoder_value(
				osc1_send_filter_2_level,
				val,
				&prev_knob_send_filter_2_val,
				_SEND_FILTER_MIN,
				_SEND_FILTER_MAX,
				4);
			
			on_osc1_send_filter_2_dial_changed(osc1_send_filter_2_level);
		}
		else if (active_frames_group_osc1 == _FRAMES_GROUP_2)
		{
			/* LFO PWM Modulation Level */
			osc1_pwm_mod_lfo_level = update_rotary_encoder_value(
				osc1_pwm_mod_lfo_level,
				val,
				&prev_knob_pwm_lfo_mod_level,
				_MODULATION_LEVEL_MIN,
				_MODULATION_LEVEL_MAX,
				4);
			
			on_osc1_pwm_mod_lfo_level_dial_changed(osc1_pwm_mod_lfo_level);
		}
	}
	else if (evnt == _CONTROL_ENCODER_BLUE_RED)
	{
		if (active_frames_group_osc1 == _FRAMES_GROUP_1)
		{
			/* Select Waveform */
			osc1_waveform = update_rotary_encoder_value(
				osc1_waveform,
				val,
				&prev_combobox_waveform,
				_OSC_WAVEFORM_SINE,
				_OSC_WAVEFORM_SAMPHOLD,
				1);
			
			on_osc1_waveform_combobox_changed(osc1_waveform);
			
		}
		else if (active_frames_group_osc1 == _FRAMES_GROUP_2)
		{
			/* Select PWM Modulation ADSR */
			osc1_pwm_mod_adsr_num = update_rotary_encoder_value(
				osc1_pwm_mod_adsr_num,
				val,
				&prev_combobox_pwm_adsr,
				_ENV_NONE,
				_ENV_6,
				1);
			
			on_osc1_pwm_mod_adsr_combobox_changed(osc1_pwm_mod_adsr_num);
		}
		else if (active_frames_group_osc1 == _FRAMES_GROUP_3)
		{
			/* Unison Mode */
			osc1_unison_mode = update_rotary_encoder_value(
				osc1_unison_mode,
				val,
				&prev_combobox_unison_mode,
				_OSC_UNISON_MODE_12345678,
				_OSC_UNISON_MODE_Cm7_CHORD,
				1);
			
			on_osc1_unison_mode_combobox_changed(osc1_unison_mode);
		}
	}
	else if (evnt == _CONTROL_ENCODER_BLUE_BLUE)
	{
		if (active_frames_group_osc1 == _FRAMES_GROUP_1)
		{
			/* Tune Octave */
			osc1_tune_octave = update_rotary_encoder_value(
				osc1_tune_octave,
				val,
				&prev_combobox_tune_octave,
				0,
				_OSC_DETUNE_MAX_OCTAVE - _OSC_DETUNE_MIN_OCTAVE,
				1);
			
			on_osc1_tune_octave_combobox_changed(osc1_tune_octave);
		}
		else if (active_frames_group_osc1 == _FRAMES_GROUP_2)
		{
			/* PWM Modulation ADSR Level */
			osc1_pwm_mod_adsr_level = update_rotary_encoder_value(
				osc1_pwm_mod_adsr_level,
				val,
				&prev_knob_pwm_adsr_mod_level,
				_MODULATION_LEVEL_MIN,
				_MODULATION_LEVEL_MAX,
				4);
			
			on_osc1_pwm_mod_adsr_level_dial_changed(osc1_pwm_mod_adsr_level);
		}
	}
	else if (evnt == _CONTROL_ENCODER_BLUE_WHITE)
	{
		if (active_frames_group_osc1 == _FRAMES_GROUP_1)
		{
			/* Tune Semitones */
			osc1_tune_semitones = update_rotary_encoder_value(
				osc1_tune_semitones,
				val,
				&prev_combobox_tune_semitones,
				0,
				_OSC_DETUNE_MAX_SEMITONES - _OSC_DETUNE_MIN_SEMITONES,
				1);
			
			on_osc1_tune_semitones_combobox_changed(osc1_tune_semitones);
		}
	}
	else if (evnt == _CONTROL_ENCODER_BLUE_YELLOW)
	{
		if (active_frames_group_osc1 == _FRAMES_GROUP_1)
		{
			/* Tune Cents */
			osc1_tune_cents = update_rotary_encoder_value(
				osc1_tune_cents,
				val,
				&prev_combobox_tune_cents,
				0,
				(int)((_OSC_DETUNE_MAX_CENTS - _OSC_DETUNE_MIN_CENTS) / _OSC_DETUNE_CENTS_FACTORIAL),
				1);
			
			on_osc1_tune_cents_combobox_changed(osc1_tune_cents);
		}
	}
	else if (evnt == _CONTROL_ENCODER_ORANGE_PURPLE)
	{
		if (active_frames_group_osc1 == _FRAMES_GROUP_1)
		{
			/* Select Frequency Modulation LFO */
			osc1_freq_mod_lfo_num = update_rotary_encoder_value(
				osc1_freq_mod_lfo_num,
				val,
				&prev_combobox_freq_lfo,
				_LFO_NONE,
				_LFO_6_DELAYED_2000MS,
				1);
			
			on_osc1_freq_mod_lfo_combobox_changed(osc1_freq_mod_lfo_num);
		}
		else if (active_frames_group_osc1 == _FRAMES_GROUP_2)
		{
			/* Select Amplitude Modulation LFO */
			osc1_amp_mod_lfo_num = update_rotary_encoder_value(
				osc1_amp_mod_lfo_num,
				val,
				&prev_combobox_amp_lfo,
				_LFO_NONE,
				_LFO_6_DELAYED_2000MS,
				1);
			
			on_osc1_amp_mod_lfo_combobox_changed(osc1_amp_mod_lfo_num);
		}
	}
	else if (evnt == _CONTROL_ENCODER_ORANGE_GREEN)
	{
		if (active_frames_group_osc1 == _FRAMES_GROUP_1)
		{
			/* Frequency Modulation LFO Level */
			osc1_freq_mod_lfo_level = update_rotary_encoder_value(
				osc1_freq_mod_lfo_level,
				val,
				&prev_knob_freq_lfo_mod_level,
				_MODULATION_LEVEL_MIN,
				_MODULATION_LEVEL_MAX,
				4);
			
			on_osc1_freq_mod_lfo_level_dial_changed(osc1_freq_mod_lfo_level);
		}
		else if (active_frames_group_osc1 == _FRAMES_GROUP_2)
		{
			/* Amplitude Modulation LFO Level */
			osc1_amp_mod_lfo_level = update_rotary_encoder_value(
				osc1_amp_mod_lfo_level,
				val,
				&prev_knob_amp_lfo_mod_level,
				_MODULATION_LEVEL_MIN,
				_MODULATION_LEVEL_MAX,
				4);
			
			on_osc1_amp_mod_lfo_level_dial_changed(osc1_amp_mod_lfo_level);
		}
	}
	else if (evnt == _CONTROL_ENCODER_ORANGE_RED)
	{
		if (active_frames_group_osc1 == _FRAMES_GROUP_1)
		{
			/* Select Frequency Modulation ADSR */
			osc1_freq_mod_adsr_num = update_rotary_encoder_value(
				osc1_freq_mod_adsr_num,
				val,
				&prev_combobox_freq_adsr,
				_ENV_NONE,
				_ENV_6,
				1);
			
			on_osc1_freq_mod_adsr_combobox_changed(osc1_freq_mod_adsr_num);
		}
		else if (active_frames_group_osc1 == _FRAMES_GROUP_2)
		{
			/* Select Amplitude Modulation ADSR */
			osc1_amp_mod_adsr_num = update_rotary_encoder_value(
				osc1_amp_mod_adsr_num,
				val,
				&prev_combobox_amp_adsr,
				_ENV_NONE,
				_ENV_6,
				1);
			
			on_osc1_amp_mod_adsr_combobox_changed(osc1_amp_mod_adsr_num);
		}
	}
	else if (evnt == _CONTROL_ENCODER_ORANGE_BLUE)
	{
		if (active_frames_group_osc1 == _FRAMES_GROUP_1)
		{
			/* Frequency Modulation ADSR Level */
			osc1_freq_mod_adsr_level = update_rotary_encoder_value(
				osc1_freq_mod_adsr_level,
				val,
				&prev_knob_freq_adsr_mod_level,
				_MODULATION_LEVEL_MIN,
				_MODULATION_LEVEL_MAX,
				4);

			on_osc1_freq_mod_adsr_level_dial_changed(osc1_freq_mod_adsr_level);
		}
		else if (active_frames_group_osc1 == _FRAMES_GROUP_2)
		{
			/* Amplitude Modulation ADSR Level */
			osc1_amp_mod_adsr_level = update_rotary_encoder_value(
				osc1_amp_mod_adsr_level,
				val,
				&prev_knob_amp_adsr_mod_level,
				_MODULATION_LEVEL_MIN,
				_MODULATION_LEVEL_MAX,
				4);
			
			on_osc1_amp_mod_adsr_level_dial_changed(osc1_amp_mod_adsr_level);
		}
		else if (active_frames_group_osc1 == _FRAMES_GROUP_3)
		{
			/* Select Hammond Percussion Mode */
			osc1_hammond_percussion_mode = update_rotary_encoder_value(
				osc1_hammond_percussion_mode,
				val,
				&prev_combobox_hammond_percussion_mode,
				_HAMMOND_PERCUSION_MODE_OFF,
				_HAMMOND_PERCUSION_MODE_3RD_NORM_FAST,
				1);
			
			on_osc1_hammond_percussion_mode_combobox_changed(osc1_hammond_percussion_mode);
		}
	}
	else if (evnt == _CONTROL_ENCODER_ORANGE_WHITE)
	{
		/* None */
	}
	else if (evnt == _CONTROL_ENCODER_ORANGE_YELLOW)
	{	
		/* None */
	}
}