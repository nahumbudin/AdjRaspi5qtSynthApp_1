/**
* @file		ControlBoxEventsHandler_AnalogSynthPad
*	@author		Nahum Budin
*	@date		11-Nov-2024
*	@version	1.0
*
*	@brief		Used for controling the Analog Synthesizer PADSynth Synthesizer Tab 
*				
*	History:
*			
*
*/

#include "Dialog_AnalogSynth.h"
#include "ui_Dialog_AnalogSynth.h"
#include "utils.h"

#include "libAdjRaspi5SynthAPI.h"

void Dialog_AnalogSynth::control_box_events_handler_pad(int evnt, uint16_t val)
{
	int level, level_slider_gap;
	Qt::CheckState checked;	
	
	static int prev_knob_pad_send_filter_1_level = 64;
	static int prev_knob_pad_send_filter_2_level = 64;
	static int prev_knob_pad_freq_modulation_lfo_level = 64;
	static int prev_knob_pad_freq_modulation_adsr_level = 64;
	static int prev_knob_pad_amp_modulation_lfo_level = 64;
	static int prev_knob_pad_amp_modulation_adsr_level = 64;
	
	static int prev_combobox_pad_octave_detune = 64;
	static int prev_combobox_pad_semitones_detune = 64;
	static int prev_combobox_pad_cents_detune = 64;
	static int prev_combobox_pad_freq_mod_lfo = 64;
	static int prev_combobox_pad_freq_mod_adsr = 64;
	static int prev_combobox_pad_amp_mod_lfo = 64;
	static int prev_combobox_pad_amp_mod_adsr = 64;
	static int prev_combobox_pad_quality = 64;
	static int prev_combobox_pad_base_note = 64;
	static int prev_combobox_pad_shape = 64;
	static int prev_combobox_pad_shape_cutoff = 64;
	
	
	if (!this->hasFocus())
	{
		return;
	}
	
	if ((evnt == _CONTROL_FUNCTION_PUSHBUTTON_ENTER) &&
			 (val == 0))
	{
		/* Switch active frames */
		active_frames_group_pad++;
		
		if (active_frames_group_pad > _FRAMES_GROUP_3)
		{
			active_frames_group_pad = _FRAMES_GROUP_1;
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
							
			on_pad_enable_checkbox_changed(checked);
		}
	}	
	
	if (!pad_enabled)
	{
		return;
	}
	
	if (evnt == _CONTROL_PUSHBUTTON_ORANGE_RED)
	{
		if (val == 0)
		{
			/* Only when pushbutton is pressed */
			if (active_frames_group_kps == _FRAMES_GROUP_2)
			{
				/* Generate */
				on_pad_generate_pushbutton_clicked();
			}
		}
	}
	else if (evnt == _CONTROL_SLIDER_BLUE_BLACK)
	{
		if (active_frames_group_pad == _FRAMES_GROUP_3)
		{
			/* Harmony 1 level */
			level = normalize_slider_value(val, _PAD_MAX_SLIDER_VALUE, _PAD_MIN_SLIDER_VALUE);
			/* Change slider value only when it matches the UI slider position */
			if (pad_harmony_1_level > _PAD_MAX_SLIDER_VALUE)
			{
				pad_harmony_1_level = _PAD_MAX_SLIDER_VALUE; 
			}
			
			level_slider_gap = pad_harmony_1_level - level;
			
			if (abs((float)level_slider_gap) < ((_PAD_MAX_SLIDER_VALUE - _PAD_MIN_SLIDER_VALUE) / 5.0))
			{
				on_pad_harmony1_level_slider_changed(level);			
			}	
		}
	}
	else if (evnt == _CONTROL_SLIDER_BLUE_GRAY)
	{
		if (active_frames_group_pad == _FRAMES_GROUP_3)
		{
			/* Harmony 2 level */
			level = normalize_slider_value(val, _PAD_MAX_SLIDER_VALUE, _PAD_MIN_SLIDER_VALUE);
			/* Change slider value only when it matches the UI slider position */
			if (pad_harmony_2_level > _PAD_MAX_SLIDER_VALUE)
			{
				pad_harmony_2_level = _PAD_MAX_SLIDER_VALUE; 
			}
			
			level_slider_gap = pad_harmony_2_level - level;
			
			if (abs((float)level_slider_gap) < ((_PAD_MAX_SLIDER_VALUE - _PAD_MIN_SLIDER_VALUE) / 5.0))
			{
				on_pad_harmony2_level_slider_changed(level);			
			}	
		}
	}
	else if (evnt == _CONTROL_SLIDER_BLUE_RED)
	{
		if (active_frames_group_pad == _FRAMES_GROUP_3)
		{
			/* Harmony 3 level */
			level = normalize_slider_value(val, _PAD_MAX_SLIDER_VALUE, _PAD_MIN_SLIDER_VALUE);
			/* Change slider value only when it matches the UI slider position */
			if (pad_harmony_3_level > _PAD_MAX_SLIDER_VALUE)
			{
				pad_harmony_3_level = _PAD_MAX_SLIDER_VALUE; 
			}
			
			level_slider_gap = pad_harmony_3_level - level;
			
			if (abs((float)level_slider_gap) < ((_PAD_MAX_SLIDER_VALUE - _PAD_MIN_SLIDER_VALUE) / 5.0))
			{
				on_pad_harmony3_level_slider_changed(level);			
			}	
		}
	}
	else if (evnt == _CONTROL_SLIDER_BLUE_BLUE)
	{
		if (active_frames_group_pad == _FRAMES_GROUP_3)
		{
			/* Harmony 4 level */
			level = normalize_slider_value(val, _PAD_MAX_SLIDER_VALUE, _PAD_MIN_SLIDER_VALUE);
			/* Change slider value only when it matches the UI slider position */
			if (pad_harmony_4_level > _PAD_MAX_SLIDER_VALUE)
			{
				pad_harmony_4_level = _PAD_MAX_SLIDER_VALUE; 
			}
			
			level_slider_gap = pad_harmony_4_level - level;
			
			if (abs((float)level_slider_gap) < ((_PAD_MAX_SLIDER_VALUE - _PAD_MIN_SLIDER_VALUE) / 5.0))
			{
				on_pad_harmony4_level_slider_changed(level);			
			}	
		}
	}
	else if (evnt == _CONTROL_SLIDER_BLUE_WHITE)
	{
		if (active_frames_group_pad == _FRAMES_GROUP_3)
		{
			/* Harmony 5 level */
			level = normalize_slider_value(val, _PAD_MAX_SLIDER_VALUE, _PAD_MIN_SLIDER_VALUE);
			/* Change slider value only when it matches the UI slider position */
			if (pad_harmony_5_level > _PAD_MAX_SLIDER_VALUE)
			{
				pad_harmony_5_level = _PAD_MAX_SLIDER_VALUE; 
			}
			
			level_slider_gap = pad_harmony_5_level - level;
			
			if (abs((float)level_slider_gap) < ((_PAD_MAX_SLIDER_VALUE - _PAD_MIN_SLIDER_VALUE) / 5.0))
			{
				on_pad_harmony5_level_slider_changed(level);			
			}	
		}
	}
	else if (evnt == _CONTROL_SLIDER_BLUE_YELLOW)
	{
		if (active_frames_group_pad == _FRAMES_GROUP_3)
		{
			/* Harmony 6 level */
			level = normalize_slider_value(val, _PAD_MAX_SLIDER_VALUE, _PAD_MIN_SLIDER_VALUE);
			/* Change slider value only when it matches the UI slider position */
			if (pad_harmony_6_level > _PAD_MAX_SLIDER_VALUE)
			{
				pad_harmony_6_level = _PAD_MAX_SLIDER_VALUE; 
			}
			
			level_slider_gap = pad_harmony_6_level - level;
			
			if (abs((float)level_slider_gap) < ((_PAD_MAX_SLIDER_VALUE - _PAD_MIN_SLIDER_VALUE) / 5.0))
			{
				on_pad_harmony6_level_slider_changed(level);			
			}	
		}
	}
	if (evnt == _CONTROL_SLIDER_ORANGE_BLACK)
	{
		if (active_frames_group_pad == _FRAMES_GROUP_2)
		{
			/* Base Width */
			level = normalize_slider_value(val, _PAD_MAX_SLIDER_VALUE, _PAD_MIN_SLIDER_VALUE);
			/* Change slider value only when it matches the UI slider position */
			if (pad_base_width > _PAD_MAX_SLIDER_VALUE)
			{
				pad_base_width = _PAD_MAX_SLIDER_VALUE; 
			}
			
			level_slider_gap = pad_base_width - level;
			
			if (abs((float)level_slider_gap) < ((_PAD_MAX_SLIDER_VALUE - _PAD_MIN_SLIDER_VALUE) / 5.0))
			{
				on_pad_base_width_slider_changed(level);			
			}
		}
		else if (active_frames_group_pad == _FRAMES_GROUP_3)
		{
			/* Harmony 7 level */
			level = normalize_slider_value(val, _PAD_MAX_SLIDER_VALUE, _PAD_MIN_SLIDER_VALUE);
			/* Change slider value only when it matches the UI slider position */
			if (pad_harmony_7_level > _PAD_MAX_SLIDER_VALUE)
			{
				pad_harmony_7_level = _PAD_MAX_SLIDER_VALUE; 
			}
			
			level_slider_gap = pad_harmony_7_level - level;
			
			if (abs((float)level_slider_gap) < ((_PAD_MAX_SLIDER_VALUE - _PAD_MIN_SLIDER_VALUE) / 5.0))
			{
				on_pad_harmony7_level_slider_changed(level);			
			}	
		}
	}
	else if (evnt == _CONTROL_SLIDER_ORANGE_GRAY)
	{
		if (active_frames_group_pad == _FRAMES_GROUP_3)
		{
			/* Harmony 8 level */
			level = normalize_slider_value(val, _PAD_MAX_SLIDER_VALUE, _PAD_MIN_SLIDER_VALUE);
			/* Change slider value only when it matches the UI slider position */
			if (pad_harmony_8_level > _PAD_MAX_SLIDER_VALUE)
			{
				pad_harmony_8_level = _PAD_MAX_SLIDER_VALUE; 
			}
			
			level_slider_gap = pad_harmony_8_level - level;
			
			if (abs((float)level_slider_gap) < ((_PAD_MAX_SLIDER_VALUE - _PAD_MIN_SLIDER_VALUE) / 5.0))
			{
				on_pad_harmony8_level_slider_changed(level);			
			}	
		}
	}
	else if (evnt == _CONTROL_SLIDER_ORANGE_RED)
	{
		if (active_frames_group_pad == _FRAMES_GROUP_3)
		{
			/* Harmony 9 level */
			level = normalize_slider_value(val, _PAD_MAX_SLIDER_VALUE, _PAD_MIN_SLIDER_VALUE);
			/* Change slider value only when it matches the UI slider position */
			if (pad_harmony_9_level > _PAD_MAX_SLIDER_VALUE)
			{
				pad_harmony_9_level = _PAD_MAX_SLIDER_VALUE; 
			}
			
			level_slider_gap = pad_harmony_9_level - level;
			
			if (abs((float)level_slider_gap) < ((_PAD_MAX_SLIDER_VALUE - _PAD_MIN_SLIDER_VALUE) / 5.0))
			{
				on_pad_harmony9_level_slider_changed(level);			
			}	
		}
	}
	else if (evnt == _CONTROL_SLIDER_ORANGE_BLUE)
	{
		if (active_frames_group_pad == _FRAMES_GROUP_3)
		{
			/* Harmony 10 level */
			level = normalize_slider_value(val, _PAD_MAX_SLIDER_VALUE, _PAD_MIN_SLIDER_VALUE);
			/* Change slider value only when it matches the UI slider position */
			if (pad_harmony_10_level > _PAD_MAX_SLIDER_VALUE)
			{
				pad_harmony_10_level = _PAD_MAX_SLIDER_VALUE; 
			}
			
			level_slider_gap = pad_harmony_10_level - level;
			
			if (abs((float)level_slider_gap) < ((_PAD_MAX_SLIDER_VALUE - _PAD_MIN_SLIDER_VALUE) / 5.0))
			{
				on_pad_harmony10_level_slider_changed(level);			
			}	
		}
	}
	else if (evnt == _CONTROL_SLIDER_ORANGE_YELLOW)
	{
		if (active_frames_group_pad == _FRAMES_GROUP_3)
		{
			/* Harmonies Detune */
			level = normalize_slider_value(val, _PAD_MAX_SLIDER_VALUE, _PAD_MIN_SLIDER_VALUE);
			/* Change slider value only when it matches the UI slider position */
			if (pad_harmony_detune > _PAD_MAX_SLIDER_VALUE)
			{
				pad_harmony_detune = _PAD_MAX_SLIDER_VALUE; 
			}
			
			level_slider_gap = pad_harmony_detune - level;
			
			if (abs((float)level_slider_gap) < ((_PAD_MAX_SLIDER_VALUE - _PAD_MIN_SLIDER_VALUE) / 5.0))
			{
				on_pad_harmonies_detune_slider_changed(level);			
			}	
		}
	}
	else if (evnt == _CONTROL_ENCODER_BLUE_PURPLE)
	{
		if (active_frames_group_pad == _FRAMES_GROUP_1)
		{
			/* Send Filter 1 */
			pad_send_filter_1_level = update_rotary_encoder_value(
				pad_send_filter_1_level,
				val,
				&prev_knob_pad_send_filter_1_level,
				_SEND_FILTER_MIN,
				_SEND_FILTER_MAX,
				4);
			
			on_pad_send_filter1_dial_changed(pad_send_filter_1_level);
		}
		else if (active_frames_group_pad == _FRAMES_GROUP_2)
		{
			/* Amp Mod LFO Level */
			pad_amp_mod_lfo_level = update_rotary_encoder_value(
				pad_amp_mod_lfo_level,
				val,
				&prev_knob_pad_amp_modulation_lfo_level,
				_MODULATION_LEVEL_MIN,
				_MODULATION_LEVEL_MAX,
				4);
			
			on_pad_amp_mod_lfo_level_dial_changed(pad_amp_mod_lfo_level);
		}
	}
	else if (evnt == _CONTROL_ENCODER_BLUE_GREEN)
	{
		if (active_frames_group_pad == _FRAMES_GROUP_1)
		{
			/* Send Filter 2 */
			pad_send_filter_2_level = update_rotary_encoder_value(
				pad_send_filter_2_level,
				val,
				&prev_knob_pad_send_filter_2_level,
				_SEND_FILTER_MIN,
				_SEND_FILTER_MAX,
				4);
			
			on_pad_send_filter2_dial_changed(pad_send_filter_2_level);
		}
		else if (active_frames_group_pad == _FRAMES_GROUP_2)
		{
			/* Amp Mod LFO Combo */
			pad_amp_mod_lfo_num = update_rotary_encoder_value(
				pad_amp_mod_lfo_num,
				val,
				&prev_combobox_pad_amp_mod_lfo,
				_LFO_NONE,
				_LFO_6_DELAYED_2000MS,
				1);
			
			on_pad_amp_mod_lfo_combobox_changed(pad_amp_mod_lfo_num);
		}
	}
	else if (evnt == _CONTROL_ENCODER_BLUE_RED)
	{
		if (active_frames_group_pad == _FRAMES_GROUP_2)
		{
			/* Amp Mod ADSR Level */
			pad_amp_mod_adsr_level = update_rotary_encoder_value(
				pad_amp_mod_adsr_level,
				val,
				&prev_knob_pad_amp_modulation_adsr_level,
				_MODULATION_LEVEL_MIN,
				_MODULATION_LEVEL_MAX,
				4);
			
			on_pad_amp_mod_env_level_dial_changed(pad_amp_mod_adsr_level);
		}
	}
	else if (evnt == _CONTROL_ENCODER_BLUE_BLUE)
	{
		if (active_frames_group_pad == _FRAMES_GROUP_1)
		{
			/* Octave Detune Combo */
			pad_tune_octave = update_rotary_encoder_value(
				pad_tune_octave,
				val,
				&prev_combobox_pad_octave_detune,
				0,
				_OSC_DETUNE_MAX_OCTAVE - _OSC_DETUNE_MIN_OCTAVE,
				1);
			
			on_pad_detune_octave_combobox_changed(pad_tune_octave);
		}
		else if (active_frames_group_pad == _FRAMES_GROUP_2)
		{
			/* Amp Mod ADSR Combo */
			pad_amp_mod_adsr_num = update_rotary_encoder_value(
				pad_amp_mod_adsr_num,
				val,
				&prev_combobox_pad_amp_mod_adsr,
				_ENV_NONE,
				_ENV_6,
				1);
			
			on_pad_amp_mod_env_combobox_changed(pad_amp_mod_adsr_num);
		}
	}
	else if (evnt == _CONTROL_ENCODER_BLUE_WHITE)
	{
		if (active_frames_group_pad == _FRAMES_GROUP_1)
		{
			/* Semitones Detune Cpmbo */
			pad_tune_semitones = update_rotary_encoder_value(
				pad_tune_semitones,
				val,
				&prev_combobox_pad_semitones_detune,
				0,
				_OSC_DETUNE_MAX_SEMITONES - _OSC_DETUNE_MIN_SEMITONES,
				1);
			
			on_pad_detune_semitones_combobox_changed(pad_tune_semitones);
		}
	}
	else if (evnt == _CONTROL_ENCODER_BLUE_YELLOW)
	{
		if (active_frames_group_pad == _FRAMES_GROUP_1)
		{
			/* Cents Detune Cpmbo */
			pad_tune_cents = update_rotary_encoder_value(
				pad_tune_cents,
				val,
				&prev_combobox_pad_cents_detune,
				0,
				(int)((_OSC_DETUNE_MAX_CENTS - _OSC_DETUNE_MIN_CENTS) / _OSC_DETUNE_CENTS_FACTORIAL),
				1);
			
			on_pad_detune_cents_combobox_changed(pad_tune_cents);
		}
	}
	else if (evnt == _CONTROL_ENCODER_ORANGE_PURPLE)
	{
		if (active_frames_group_pad == _FRAMES_GROUP_1)
		{
			/* Freq  Mod LFO Level */
			pad_freq_mod_lfo_level = update_rotary_encoder_value(
				pad_freq_mod_lfo_level,
				val,
				&prev_knob_pad_freq_modulation_lfo_level,
				_MODULATION_LEVEL_MIN,
				_MODULATION_LEVEL_MAX,
				4);
			
			on_pad_freq_mod_lfo_level_dial_changed(pad_freq_mod_lfo_level);
		}
	}
	else if (evnt == _CONTROL_ENCODER_ORANGE_GREEN)
	{
		if (active_frames_group_pad == _FRAMES_GROUP_1)
		{
			/* Freq  Mod LFO Combo */
			pad_freq_mod_lfo_num = update_rotary_encoder_value(
				pad_freq_mod_lfo_num,
				val,
				&prev_combobox_pad_freq_mod_lfo,
				_LFO_NONE,
				_LFO_6_DELAYED_2000MS,
				1);
			
			on_pad_freq_mod_lfo_combobox_changed(pad_freq_mod_lfo_num);
		}
		else if (active_frames_group_pad == _FRAMES_GROUP_2)
		{
			/* Quality Combo */
			pad_quality = update_rotary_encoder_value(
				pad_quality,
				val,
				&prev_combobox_pad_quality,
				_PAD_QUALITY_32K,
				_PAD_QUALITY_1024K,
				1);
			
			on_pad_quality_combobox_changed(pad_quality);
		}
	}
	else if (evnt == _CONTROL_ENCODER_ORANGE_RED)
	{
		if (active_frames_group_pad == _FRAMES_GROUP_1)
		{
			/* Freq  Mod ADSR Level */
			pad_freq_mod_adsr_level = update_rotary_encoder_value(
				pad_freq_mod_adsr_level,
				val,
				&prev_knob_pad_freq_modulation_adsr_level,
				_MODULATION_LEVEL_MIN,
				_MODULATION_LEVEL_MAX,
				4);
			
			on_pad_freq_mod_env_level_dial_changed(pad_freq_mod_adsr_level);
		}
	}
	else if (evnt == _CONTROL_ENCODER_ORANGE_BLUE)
	{
		if (active_frames_group_pad == _FRAMES_GROUP_1)
		{
			/* Freq  Mod ADSR */
			pad_freq_mod_adsr_num = update_rotary_encoder_value(
				pad_freq_mod_adsr_num,
				val,
				&prev_combobox_pad_freq_mod_adsr,
				_ENV_NONE,
				_ENV_6,
				1);
			
			on_pad_freq_mod_env_combobox_changed(pad_freq_mod_adsr_num);
		}
		else if (active_frames_group_pad == _FRAMES_GROUP_2)
		{
			/* Base Note Combo */
			pad_base_note = update_rotary_encoder_value(
				pad_base_note,
				val,
				&prev_combobox_pad_base_note,
				_PAD_BASE_NOTE_C2,
				_PAD_BASE_NOTE_G6,
				1);
			
			on_pad_base_note_combobox_changed(pad_base_note);
		}
	}
	else if (evnt == _CONTROL_ENCODER_ORANGE_WHITE)
	{
		if (active_frames_group_pad == _FRAMES_GROUP_2)
		{
			/* Shape Cutoff Combo */
			pad_shape_cutoff = update_rotary_encoder_value(
				pad_shape_cutoff,
				val,
				&prev_combobox_pad_shape_cutoff,
				_PAD_SHAPE_CUTOFF_FULL,
				_PAD_SHAPE_CUTOFF_LOWER,
				1);
			
			on_pad_shape_cutoff_combobox_changed(pad_shape_cutoff);
		}
	}
	else if (evnt == _CONTROL_ENCODER_ORANGE_YELLOW)
	{
		if (active_frames_group_pad == _FRAMES_GROUP_2)
		{
			/* Shape Combo */
			pad_shape = update_rotary_encoder_value(
				pad_shape,
				val,
				&prev_combobox_pad_shape,
				_PAD_SHAPE_RECTANGULAR,
				_PAD_SHAPE_DOUBLE_EXP,
				1);
			
			on_pad_shape_combobox_changed(pad_shape);
		}
	}
}
