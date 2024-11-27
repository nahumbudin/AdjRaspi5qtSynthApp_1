/**
* @file		ControlBoxEventsHandler_AnalogSynthOsc2noise
*	@author		Nahum Budin
*	@date		1-Nov-2024
*	@version	1.0
*
*	@brief		Used for controling the Analog Synthesizer Osc2 and Noise Tab 
*				
*	History:
*			
*
*/

#include "Dialog_AnalogSynth.h"
#include "ui_Dialog_AnalogSynth.h"
#include "utils.h"

#include "libAdjRaspi5SynthAPI.h"

void Dialog_AnalogSynth::control_box_events_handler_osc_2_noise(int evnt, uint16_t val)
{
	int level, level_slider_gap;
	Qt::CheckState checked;
	
	static int prev_knob_osc2_send_filter_1_val = 64;
	static int prev_knob_osc2_send_filter_2_val = 64;
	static int prev_knob_osc2_freq_lfo_mod_level = 64;
	static int prev_knob_osc2_freq_adsr_mod_level = 64;
	static int prev_knob_osc2_pwm_lfo_mod_level = 64;
	static int prev_knob_osc2_pwm_adsr_mod_level = 64;
	static int prev_knob_osc2_amp_lfo_mod_level = 64;
	static int prev_knob_osc2_amp_adsr_mod_level = 64;
	static int prev_combobox_osc2_freq_lfo = 64;
	static int prev_combobox_osc2_pwm_lfo = 64;
	static int prev_combobox_osc2_amp_lfo = 64;
	static int prev_combobox_osc2_freq_adsr = 64;
	static int prev_combobox_osc2_pwm_adsr = 64;
	static int prev_combobox_osc2_amp_adsr = 64;
	static int prev_combobox_osc2_waveform = 64;
	
	static int prev_combobox_osc_2_tune_octave = 64;
	static int prev_combobox_osc_2_tune_semitones = 64;
	static int prev_combobox_osc_2_tune_cents = 64;
	
	static int prev_knob_noise_send_filter_1_val = 64;
	static int prev_knob_noise_send_filter_2_val = 64;
	static int prev_knob_noise_amp_lfo_mod_level = 64;
	static int prev_knob_noise_amp_adsr_mod_level = 64;
	static int prev_combobox_noise_amp_lfo = 64;
	static int prev_combobox_noise_amp_adsr = 64;
	static int prev_combobox_noise_color = 64;
	
	
	if (!this->hasFocus())
	{
		return;
	}
	
	if ((evnt == _CONTROL_FUNCTION_PUSHBUTTON_ENTER) &&
			 (val == 0))
	{
		/* Switch active frames */
		active_frames_group_osc2noise++;
		
		if (active_frames_group_osc2noise > _FRAMES_GROUP_3)
		{
			active_frames_group_osc2noise = _FRAMES_GROUP_1;
		}		
	}
	else if (evnt == _CONTROL_PUSHBUTTON_BLUE_BLACK)
	{
		/* Enable Osc2 - allways active */
		if (val == 0)
		{
			/* Only when pushbutton is pressed */			
			checked = ui->checkBox_Osc2Active->checkState();
			
			/* Toggle */
			if (checked == Qt::CheckState::Checked)
			{
				checked = Qt::CheckState::Unchecked;
			}
			else
			{
				checked = Qt::CheckState::Checked;
			}
							
			on_osc2_enable_changed(checked);
		}
	}
	else if (evnt == _CONTROL_PUSHBUTTON_BLUE_BLUE)
	{
		/* Enable Noise */
		if (val == 0)
		{
			/* Only when pushbutton is pressed */			
			checked = ui->checkBox_NoiseActive->checkState();
			
			/* Toggle */
			if (checked == Qt::CheckState::Checked)
			{
				checked = Qt::CheckState::Unchecked;
			}
			else
			{
				checked = Qt::CheckState::Checked;
			}
							
			on_noise_enable_changed(checked);
		}
	}
	
	if (!osc2_enabled && !noise_enabled)
	{
		return;
	}
	
	if (evnt == _CONTROL_PUSHBUTTON_BLUE_GREEN)
	{
		if ((active_frames_group_osc2noise == _FRAMES_GROUP_2) && osc2_enabled)
		{
			/* Enable Osc2 Syncon Osc1 */
			if (val == 0)
			{
				/* Only when pushbutton is pressed */			
				checked = ui->checkBox_Osc2SyncOnOsc1->checkState();
			
				/* Toggle */
				if (checked == Qt::CheckState::Checked)
				{
					checked = Qt::CheckState::Unchecked;
				}
				else
				{
					checked = Qt::CheckState::Checked;
				}
							
				on_osc2_sync_on_osc1_enable_changed(checked);
			}
		}
	}
	else if (evnt == _CONTROL_SLIDER_BLUE_BLACK)
	{
		if ((active_frames_group_osc2noise == _FRAMES_GROUP_1)  && osc2_enabled)
		{
			/* Waveform Symetry */
			level = normalize_slider_value(val, _OSC_WAVEFORM_SYMETRY_MAX, _OSC_WAVEFORM_SYMETRY_MIN);
			/* Change slider value only when it matches the UI slider position */
			if (osc2_waveform_symetry > _OSC_WAVEFORM_SYMETRY_MAX)
			{
				osc2_waveform_symetry = _OSC_WAVEFORM_SYMETRY_MAX; // TODO: how did we get here?
			}
			level_slider_gap = osc2_waveform_symetry - level;
			
			if (abs((float)level_slider_gap) < ((_OSC_WAVEFORM_SYMETRY_MAX - _OSC_WAVEFORM_SYMETRY_MIN) / 5.0))
			{
				on_osc2_waveform_symetry_slider_cahanged(level);
			}
		}
	}
	else if (evnt == _CONTROL_ENCODER_BLUE_PURPLE)
	{
		if ((active_frames_group_osc2noise == _FRAMES_GROUP_1)  && osc2_enabled)
		{
			/* Osc2 Send Filter 1 */
			osc2_send_filter_1_level = update_rotary_encoder_value(
				osc2_send_filter_1_level,
				val,
				&prev_knob_osc2_send_filter_2_val,
				_SEND_FILTER_MIN,
				_SEND_FILTER_MAX,
				4);
			
			on_osc2_send_filter_1_dial_changed(osc2_send_filter_1_level);
		}
		else if ((active_frames_group_osc2noise == _FRAMES_GROUP_2)  && osc2_enabled)
		{
			/* Osc2 Select PWM Modulation LFO */
			osc2_pwm_mod_lfo_num = update_rotary_encoder_value(
				osc2_pwm_mod_lfo_num,
				val,
				&prev_combobox_osc2_pwm_lfo,
				_LFO_NONE,
				_LFO_6_DELAYED_2000MS,
				1);
			
			on_osc2_pwm_mod_lfo_combobox_changed(osc2_pwm_mod_lfo_num);
		}
		else if ((active_frames_group_osc2noise == _FRAMES_GROUP_3) && noise_enabled)
		{
			/* Noise Send Filter 1 */
			noise_send_filter_1_level = update_rotary_encoder_value(
				noise_send_filter_1_level,
				val,
				&prev_knob_noise_send_filter_2_val,
				_SEND_FILTER_MIN,
				_SEND_FILTER_MAX,
				4);
			
			on_noise_send_filter_1_dial_changed(noise_send_filter_1_level);
		}
	}
	else if (evnt == _CONTROL_ENCODER_BLUE_GREEN)
	{
		if ((active_frames_group_osc2noise == _FRAMES_GROUP_1)  && osc2_enabled)
		{
			/* Osc2 Send Filter 2 */
			osc2_send_filter_2_level = update_rotary_encoder_value(
				osc2_send_filter_2_level,
				val,
				&prev_knob_osc2_send_filter_2_val,
				_SEND_FILTER_MIN,
				_SEND_FILTER_MAX,
				4);
			
			on_osc2_send_filter_2_dial_changed(osc2_send_filter_2_level);
		}
		else if ((active_frames_group_osc2noise == _FRAMES_GROUP_2) && osc2_enabled)
		{
			/* Osc2 LFO PWM Modulation Level */
			osc2_pwm_mod_lfo_level = update_rotary_encoder_value(
				osc2_pwm_mod_lfo_level,
				val,
				&prev_knob_osc2_pwm_lfo_mod_level,
				_MODULATION_LEVEL_MIN,
				_MODULATION_LEVEL_MAX,
				4);
			
			on_osc2_pwm_mod_lfo_level_dial_changed(osc2_pwm_mod_lfo_level);
		}
		if ((active_frames_group_osc2noise == _FRAMES_GROUP_3) && noise_enabled)
		{
			/* Noise Send Filter 2 */
			noise_send_filter_2_level = update_rotary_encoder_value(
				noise_send_filter_2_level,
				val,
				&prev_knob_noise_send_filter_2_val,
				_SEND_FILTER_MIN,
				_SEND_FILTER_MAX,
				4);
			
			on_noise_send_filter_2_dial_changed(noise_send_filter_2_level);
		}
	}
	else if (evnt == _CONTROL_ENCODER_BLUE_RED)
	{
		if ((active_frames_group_osc2noise == _FRAMES_GROUP_1)  && osc2_enabled)
		{
			/* Osc2 Select Waveform */
			osc2_waveform = update_rotary_encoder_value(
				osc2_waveform,
				val,
				&prev_combobox_osc2_waveform,
				_OSC_WAVEFORM_SINE,
				_OSC_WAVEFORM_SAMPHOLD,
				1);
			
			on_osc2_waveform_combobox_changed(osc2_waveform);
		}
		else if ((active_frames_group_osc2noise == _FRAMES_GROUP_2) && osc2_enabled)
		{
			/* Osc2 Select PWM Modulation ADSR */
			osc2_pwm_mod_adsr_num = update_rotary_encoder_value(
				osc2_pwm_mod_adsr_num,
				val,
				&prev_combobox_osc2_pwm_adsr,
				_ENV_NONE,
				_ENV_6,
				1);
			
			on_osc2_pwm_mod_adsr_combobox_changed(osc2_pwm_mod_adsr_num);
		}
		else if ((active_frames_group_osc2noise == _FRAMES_GROUP_3) && noise_enabled)
		{
			/* Noise Color */
			noise_color = update_rotary_encoder_value(
				noise_color,
				val,
				&prev_combobox_noise_color,
				_WHITE_NOISE,
				_BROWN_NOISE,
				1);
			
			on_noise_color_combobox_changed(noise_color);
		}
	}
	else if (evnt == _CONTROL_ENCODER_BLUE_BLUE)
	{
		if ((active_frames_group_osc2noise == _FRAMES_GROUP_1) && osc2_enabled)
		{
			/* Osc2 Tune Octave */
			osc2_tune_octave = update_rotary_encoder_value(
				osc2_tune_octave,
				val,
				&prev_combobox_osc_2_tune_octave,
				0,
				_OSC_DETUNE_MAX_OCTAVE - _OSC_DETUNE_MIN_OCTAVE,
				1);
			
			on_osc2_tune_octave_combobox_changed(osc2_tune_octave);
		}		
		else if ((active_frames_group_osc2noise == _FRAMES_GROUP_2) && osc2_enabled)
		{
			/* Osc2 PWM Modulation ADSR Level */
			osc2_pwm_mod_adsr_level = update_rotary_encoder_value(
				osc2_pwm_mod_adsr_level,
				val,
				&prev_knob_osc2_pwm_adsr_mod_level,
				_MODULATION_LEVEL_MIN,
				_MODULATION_LEVEL_MAX,
				4);
			
			on_osc2_pwm_mod_adsr_level_dial_changed(osc2_pwm_mod_adsr_level);
		}
	}
	else if (evnt == _CONTROL_ENCODER_BLUE_WHITE)
	{
		if ((active_frames_group_osc2noise == _FRAMES_GROUP_1) && osc2_enabled)
		{
			/* Osc2 Tune offset Semitones */
			osc2_tune_semitones = update_rotary_encoder_value(
				osc2_tune_semitones,
				val,
				&prev_combobox_osc_2_tune_semitones,
				0,
				_OSC_DETUNE_MAX_SEMITONES - _OSC_DETUNE_MIN_SEMITONES,
				1);
			
			on_osc2_tune_semitones_combobox_changed(osc2_tune_semitones);
		}
	}
	else if (evnt == _CONTROL_ENCODER_BLUE_YELLOW)
	{
		if ((active_frames_group_osc2noise == _FRAMES_GROUP_1) && osc2_enabled)
		{
			/* Osc2 Tune Offset Cents */
			osc2_tune_cents = update_rotary_encoder_value(
				osc2_tune_cents,
				val,
				&prev_combobox_osc_2_tune_cents,
				0,
				(int)((_OSC_DETUNE_MAX_CENTS - _OSC_DETUNE_MIN_CENTS) / _OSC_DETUNE_CENTS_FACTORIAL),
				1);
			
			on_osc2_tune_cents_combobox_changed(osc2_tune_cents);
		}
	}
	else if (evnt == _CONTROL_ENCODER_ORANGE_PURPLE)
	{
		if ((active_frames_group_osc2noise == _FRAMES_GROUP_1) && osc2_enabled)
		{
			/* Osc2 Select Frequency Modulation LFO */
			osc2_freq_mod_lfo_num = update_rotary_encoder_value(
				osc2_freq_mod_lfo_num,
				val,
				&prev_combobox_osc2_freq_lfo,
				_LFO_NONE,
				_LFO_6_DELAYED_2000MS,
				1);
			
			on_osc2_freq_mod_lfo_combobox_changed(osc2_freq_mod_lfo_num);
		}
		else if ((active_frames_group_osc2noise == _FRAMES_GROUP_2) && osc2_enabled)
		{
			/* Osc2 Select Amplitude Modulation LFO */
			osc2_amp_mod_lfo_num = update_rotary_encoder_value(
				osc2_amp_mod_lfo_num,
				val,
				&prev_combobox_osc2_amp_lfo,
				_LFO_NONE,
				_LFO_6_DELAYED_2000MS,
				1);
			
			on_osc2_amp_mod_lfo_combobox_changed(osc2_amp_mod_lfo_num);
		}
		else if ((active_frames_group_osc2noise == _FRAMES_GROUP_3) && noise_enabled)
		{
			/* Noise Select Amplitude Modulation LFO */
			noise_amp_mod_lfo_num = update_rotary_encoder_value(
				noise_amp_mod_lfo_num,
				val,
				&prev_combobox_noise_amp_lfo,
				_LFO_NONE,
				_LFO_6_DELAYED_2000MS,
				1);
			
			on_noise_amp_mod_lfo_combobox_changed(noise_amp_mod_lfo_num);
		}
	}
	else if (evnt == _CONTROL_ENCODER_ORANGE_GREEN)
	{
		if ((active_frames_group_osc2noise == _FRAMES_GROUP_1) && osc2_enabled)
		{
			/* Osc2 Frequency Modulation LFO Level */
			osc2_freq_mod_lfo_level = update_rotary_encoder_value(
				osc2_freq_mod_lfo_level,
				val,
				&prev_knob_osc2_freq_lfo_mod_level,
				_MODULATION_LEVEL_MIN,
				_MODULATION_LEVEL_MAX,
				4);
			
			on_osc2_freq_mod_lfo_level_dial_changed(osc2_freq_mod_lfo_level);
		}
		else if ((active_frames_group_osc2noise == _FRAMES_GROUP_2) && osc2_enabled)
		{
			/* Osc2 Amplitude Modulation LFO Level */
			osc2_amp_mod_lfo_level = update_rotary_encoder_value(
				osc2_amp_mod_lfo_level,
				val,
				&prev_knob_osc2_amp_lfo_mod_level,
				_MODULATION_LEVEL_MIN,
				_MODULATION_LEVEL_MAX,
				4);
			
			on_osc2_amp_mod_lfo_level_dial_changed(osc2_amp_mod_lfo_level);
		}
		else if ((active_frames_group_osc2noise == _FRAMES_GROUP_3) && noise_enabled)
		{
			/* Noise Amplitude Modulation LFO Level */
			noise_amp_mod_lfo_level = update_rotary_encoder_value(
				noise_amp_mod_lfo_level,
				val,
				&prev_knob_noise_amp_lfo_mod_level,
				_MODULATION_LEVEL_MIN,
				_MODULATION_LEVEL_MAX,
				4);
			
			on_noise_amp_mod_lfo_level_dial_changed(noise_amp_mod_lfo_level);
		}
	}
	else if (evnt == _CONTROL_ENCODER_ORANGE_RED)
	{
		if ((active_frames_group_osc2noise == _FRAMES_GROUP_1) && osc2_enabled)
		{
			/* Osc2 Select Frequency Modulation ADSR */
			osc2_freq_mod_adsr_num = update_rotary_encoder_value(
				osc2_freq_mod_adsr_num,
				val,
				&prev_combobox_osc2_freq_adsr,
				_ENV_NONE,
				_ENV_6,
				1);
			
			on_osc2_freq_mod_adsr_combobox_changed(osc2_freq_mod_adsr_num);
		}
		else if ((active_frames_group_osc2noise == _FRAMES_GROUP_2) && osc2_enabled)
		{
			/* Osc2 Select Amplitude Modulation ADSR */
			osc2_amp_mod_adsr_num = update_rotary_encoder_value(
				osc2_amp_mod_adsr_num,
				val,
				&prev_combobox_osc2_amp_adsr,
				_ENV_NONE,
				_ENV_6,
				1);
			
			on_osc2_amp_mod_adsr_combobox_changed(osc2_amp_mod_adsr_num);
		}
		else if ((active_frames_group_osc2noise == _FRAMES_GROUP_3) && noise_enabled)
		{
			/* Noise Select Amplitude Modulation ADSR */
			noise_amp_mod_adsr_num = update_rotary_encoder_value(
				noise_amp_mod_adsr_num,
				val,
				&prev_combobox_noise_amp_adsr,
				_ENV_NONE,
				_ENV_6,
				1);
			
			on_noise_amp_mod_adsr_combobox_changed(noise_amp_mod_adsr_num);
		}
	}
	else if (evnt == _CONTROL_ENCODER_ORANGE_BLUE)
	{
		if ((active_frames_group_osc2noise == _FRAMES_GROUP_1) && osc2_enabled)
		{
			/* Osc2 Frequency Modulation ADSR Level */
			osc2_freq_mod_adsr_level = update_rotary_encoder_value(
				osc2_freq_mod_adsr_level,
				val,
				&prev_knob_osc2_freq_adsr_mod_level,
				_MODULATION_LEVEL_MIN,
				_MODULATION_LEVEL_MAX,
				4);

			on_osc2_freq_mod_adsr_level_dial_changed(osc2_freq_mod_adsr_level);
		}
		else if ((active_frames_group_osc2noise == _FRAMES_GROUP_2) && osc2_enabled)
		{
			/* Osc2 Amplitude Modulation ADSR Level */
			osc2_amp_mod_adsr_level = update_rotary_encoder_value(
				osc2_amp_mod_adsr_level,
				val,
				&prev_knob_osc2_amp_adsr_mod_level,
				_MODULATION_LEVEL_MIN,
				_MODULATION_LEVEL_MAX,
				4);
			
			on_osc2_amp_mod_adsr_level_dial_changed(osc2_amp_mod_adsr_level);
		}
		else if ((active_frames_group_osc2noise == _FRAMES_GROUP_3) && noise_enabled)
		{
			/* Noise Amplitude Modulation ADSR Level */
			noise_amp_mod_adsr_level = update_rotary_encoder_value(
				noise_amp_mod_adsr_level,
				val,
				&prev_knob_noise_amp_adsr_mod_level,
				_MODULATION_LEVEL_MIN,
				_MODULATION_LEVEL_MAX,
				4);
			
			on_noise_amp_mod_adsr_level_dial_changed(noise_amp_mod_adsr_level);
		}
	}
}