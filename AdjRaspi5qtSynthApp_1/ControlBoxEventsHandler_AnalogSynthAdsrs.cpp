/**
* @file		ControlBoxEventsHandler_AnalogSynthAdsrs
*	@author		Nahum Budin
*	@date		27-Nov-2024
*	@version	1.0
*
*	@brief		Used for controling the Analog Synthesizer Adsrss Tab 
*				
*	History:
*			
*
*/

#include "Dialog_AnalogSynth.h"
#include "ui_Dialog_AnalogSynth.h"
#include "utils.h"

#include "libAdjRaspi5SynthAPI.h"

void Dialog_AnalogSynth::control_box_events_handler_adsrs(int evnt, uint16_t val)
{
	int level, level_slider_gap;	
	
	if (!this->hasFocus())
	{
		return;
	}
	
	if ((evnt == _CONTROL_FUNCTION_PUSHBUTTON_ENTER) &&
			 (val == 0))
	{
		/* Switch active frames */
		active_frames_group_adsrs++;
		
		if (active_frames_group_adsrs > _FRAMES_GROUP_3)
		{
			active_frames_group_adsrs = _FRAMES_GROUP_1;
		}		
	}
	else if (evnt == _CONTROL_SLIDER_BLUE_GRAY)
	{
		if (active_frames_group_adsrs == _FRAMES_GROUP_1)
		{
			/* ADSR 1 Attack */
			level = normalize_slider_value(val, _ADSR_SLIDER_VALUE_MAX, _ADSR_SLIDER_VALUE_MIN);
			/* Change slider value only when it matches the UI slider position */
			if (adsr1_attack_entry > _PAD_MAX_SLIDER_VALUE)
			{
				adsr1_attack_entry = _PAD_MAX_SLIDER_VALUE; 
			}
			
			level_slider_gap = adsr1_attack_entry - level;
			
			if (abs((float)level_slider_gap) < ((_ADSR_SLIDER_VALUE_MAX - _ADSR_SLIDER_VALUE_MIN) / 5.0))
			{
				on_adsr1_attack_slider_changed(level);			
			}	
		}
		else if (active_frames_group_adsrs == _FRAMES_GROUP_2)
		{
			/* ADSR 3 Attack */
			level = normalize_slider_value(val, _ADSR_SLIDER_VALUE_MAX, _ADSR_SLIDER_VALUE_MIN);
			/* Change slider value only when it matches the UI slider position */
			if (adsr3_attack_entry > _PAD_MAX_SLIDER_VALUE)
			{
				adsr3_attack_entry = _PAD_MAX_SLIDER_VALUE; 
			}
			
			level_slider_gap = adsr3_attack_entry - level;
			
			if (abs((float)level_slider_gap) < ((_ADSR_SLIDER_VALUE_MAX - _ADSR_SLIDER_VALUE_MIN) / 5.0))
			{
				on_adsr3_attack_slider_changed(level);			
			}	
		}
		else if (active_frames_group_adsrs == _FRAMES_GROUP_3)
		{
			/* ADSR 5 Attack */
			level = normalize_slider_value(val, _ADSR_SLIDER_VALUE_MAX, _ADSR_SLIDER_VALUE_MIN);
			/* Change slider value only when it matches the UI slider position */
			if (adsr5_attack_entry > _PAD_MAX_SLIDER_VALUE)
			{
				adsr5_attack_entry = _PAD_MAX_SLIDER_VALUE; 
			}
			
			level_slider_gap = adsr5_attack_entry - level;
			
			if (abs((float)level_slider_gap) < ((_ADSR_SLIDER_VALUE_MAX - _ADSR_SLIDER_VALUE_MIN) / 5.0))
			{
				on_adsr5_attack_slider_changed(level);			
			}	
		}
	}
	else if (evnt == _CONTROL_SLIDER_BLUE_RED)
	{
		if (active_frames_group_adsrs == _FRAMES_GROUP_1)
		{
			/* ADSR 1 Decay */
			level = normalize_slider_value(val, _ADSR_SLIDER_VALUE_MAX, _ADSR_SLIDER_VALUE_MIN);
			/* Change slider value only when it matches the UI slider position */
			if (adsr1_decay_entry > _PAD_MAX_SLIDER_VALUE)
			{
				adsr1_decay_entry = _PAD_MAX_SLIDER_VALUE; 
			}
			
			level_slider_gap = adsr1_decay_entry - level;
			
			if (abs((float)level_slider_gap) < ((_ADSR_SLIDER_VALUE_MAX - _ADSR_SLIDER_VALUE_MIN) / 5.0))
			{
				on_adsr1_decay_slider_changed(level);			
			}	
		}
		else if (active_frames_group_adsrs == _FRAMES_GROUP_2)
		{
			/* ADSR 3 Decay */
			level = normalize_slider_value(val, _ADSR_SLIDER_VALUE_MAX, _ADSR_SLIDER_VALUE_MIN);
			/* Change slider value only when it matches the UI slider position */
			if (adsr3_decay_entry > _PAD_MAX_SLIDER_VALUE)
			{
				adsr3_decay_entry = _PAD_MAX_SLIDER_VALUE; 
			}
			
			level_slider_gap = adsr3_decay_entry - level;
			
			if (abs((float)level_slider_gap) < ((_ADSR_SLIDER_VALUE_MAX - _ADSR_SLIDER_VALUE_MIN) / 5.0))
			{
				on_adsr3_decay_slider_changed(level);			
			}	
		}
		else if (active_frames_group_adsrs == _FRAMES_GROUP_3)
		{
			/* ADSR 5 Decay */
			level = normalize_slider_value(val, _ADSR_SLIDER_VALUE_MAX, _ADSR_SLIDER_VALUE_MIN);
			/* Change slider value only when it matches the UI slider position */
			if (adsr5_decay_entry > _PAD_MAX_SLIDER_VALUE)
			{
				adsr5_decay_entry = _PAD_MAX_SLIDER_VALUE; 
			}
			
			level_slider_gap = adsr5_decay_entry - level;
			
			if (abs((float)level_slider_gap) < ((_ADSR_SLIDER_VALUE_MAX - _ADSR_SLIDER_VALUE_MIN) / 5.0))
			{
				on_adsr5_decay_slider_changed(level);			
			}	
		}
	}
	else if (evnt == _CONTROL_SLIDER_BLUE_BLUE)
	{
		if (active_frames_group_adsrs == _FRAMES_GROUP_1)
		{
			/* ADSR 1 Sustain */
			level = normalize_slider_value(val, _ADSR_SLIDER_VALUE_MAX, _ADSR_SLIDER_VALUE_MIN);
			/* Change slider value only when it matches the UI slider position */
			if (adsr1_sustain_entry > _PAD_MAX_SLIDER_VALUE)
			{
				adsr1_sustain_entry = _PAD_MAX_SLIDER_VALUE; 
			}
			
			level_slider_gap = adsr1_sustain_entry - level;
			
			if (abs((float)level_slider_gap) < ((_ADSR_SLIDER_VALUE_MAX - _ADSR_SLIDER_VALUE_MIN) / 5.0))
			{
				on_adsr1_sustain_slider_changed(level);			
			}	
		}
		else if (active_frames_group_adsrs == _FRAMES_GROUP_2)
		{
			/* ADSR 3 Sustain */
			level = normalize_slider_value(val, _ADSR_SLIDER_VALUE_MAX, _ADSR_SLIDER_VALUE_MIN);
			/* Change slider value only when it matches the UI slider position */
			if (adsr3_sustain_entry > _PAD_MAX_SLIDER_VALUE)
			{
				adsr3_sustain_entry = _PAD_MAX_SLIDER_VALUE; 
			}
			
			level_slider_gap = adsr3_sustain_entry - level;
			
			if (abs((float)level_slider_gap) < ((_ADSR_SLIDER_VALUE_MAX - _ADSR_SLIDER_VALUE_MIN) / 5.0))
			{
				on_adsr3_sustain_slider_changed(level);			
			}	
		}
		else if (active_frames_group_adsrs == _FRAMES_GROUP_3)
		{
			/* ADSR 5 Sustain */
			level = normalize_slider_value(val, _ADSR_SLIDER_VALUE_MAX, _ADSR_SLIDER_VALUE_MIN);
			/* Change slider value only when it matches the UI slider position */
			if (adsr5_sustain_entry > _PAD_MAX_SLIDER_VALUE)
			{
				adsr5_sustain_entry = _PAD_MAX_SLIDER_VALUE; 
			}
			
			level_slider_gap = adsr5_sustain_entry - level;
			
			if (abs((float)level_slider_gap) < ((_ADSR_SLIDER_VALUE_MAX - _ADSR_SLIDER_VALUE_MIN) / 5.0))
			{
				on_adsr5_sustain_slider_changed(level);			
			}	
		}
	}
	else if (evnt == _CONTROL_SLIDER_BLUE_WHITE)
	{
		if (active_frames_group_adsrs == _FRAMES_GROUP_1)
		{
			/* ADSR 1 Release */
			level = normalize_slider_value(val, _ADSR_SLIDER_VALUE_MAX, _ADSR_SLIDER_VALUE_MIN);
			/* Change slider value only when it matches the UI slider position */
			if (adsr1_release_entry > _PAD_MAX_SLIDER_VALUE)
			{
				adsr1_release_entry = _PAD_MAX_SLIDER_VALUE; 
			}
			
			level_slider_gap = adsr1_release_entry - level;
			
			if (abs((float)level_slider_gap) < ((_ADSR_SLIDER_VALUE_MAX - _ADSR_SLIDER_VALUE_MIN) / 5.0))
			{
				on_adsr1_release_slider_changed(level);			
			}	
		}
		else if (active_frames_group_adsrs == _FRAMES_GROUP_2)
		{
			/* ADSR 3 Release */
			level = normalize_slider_value(val, _ADSR_SLIDER_VALUE_MAX, _ADSR_SLIDER_VALUE_MIN);
			/* Change slider value only when it matches the UI slider position */
			if (adsr3_release_entry > _PAD_MAX_SLIDER_VALUE)
			{
				adsr3_release_entry = _PAD_MAX_SLIDER_VALUE; 
			}
			
			level_slider_gap = adsr3_release_entry - level;
			
			if (abs((float)level_slider_gap) < ((_ADSR_SLIDER_VALUE_MAX - _ADSR_SLIDER_VALUE_MIN) / 5.0))
			{
				on_adsr3_release_slider_changed(level);			
			}	
		}
		else if (active_frames_group_adsrs == _FRAMES_GROUP_3)
		{
			/* ADSR 5 Release */
			level = normalize_slider_value(val, _ADSR_SLIDER_VALUE_MAX, _ADSR_SLIDER_VALUE_MIN);
			/* Change slider value only when it matches the UI slider position */
			if (adsr5_release_entry > _PAD_MAX_SLIDER_VALUE)
			{
				adsr5_release_entry = _PAD_MAX_SLIDER_VALUE; 
			}
			
			level_slider_gap = adsr5_release_entry - level;
			
			if (abs((float)level_slider_gap) < ((_ADSR_SLIDER_VALUE_MAX - _ADSR_SLIDER_VALUE_MIN) / 5.0))
			{
				on_adsr5_release_slider_changed(level);			
			}	
		}
	}
	else if (evnt == _CONTROL_SLIDER_ORANGE_GRAY)
	{
		if (active_frames_group_adsrs == _FRAMES_GROUP_1)
		{
			/* ADSR 2 Attack */
			level = normalize_slider_value(val, _ADSR_SLIDER_VALUE_MAX, _ADSR_SLIDER_VALUE_MIN);
			/* Change slider value only when it matches the UI slider position */
			if (adsr2_attack_entry > _PAD_MAX_SLIDER_VALUE)
			{
				adsr2_attack_entry = _PAD_MAX_SLIDER_VALUE; 
			}
			
			level_slider_gap = adsr2_attack_entry - level;
			
			if (abs((float)level_slider_gap) < ((_ADSR_SLIDER_VALUE_MAX - _ADSR_SLIDER_VALUE_MIN) / 5.0))
			{
				on_adsr2_attack_slider_changed(level);			
			}	
		}
		else if (active_frames_group_adsrs == _FRAMES_GROUP_2)
		{
			/* ADSR 4 Attack */
			level = normalize_slider_value(val, _ADSR_SLIDER_VALUE_MAX, _ADSR_SLIDER_VALUE_MIN);
			/* Change slider value only when it matches the UI slider position */
			if (adsr4_attack_entry > _PAD_MAX_SLIDER_VALUE)
			{
				adsr4_attack_entry = _PAD_MAX_SLIDER_VALUE; 
			}
			
			level_slider_gap = adsr4_attack_entry - level;
			
			if (abs((float)level_slider_gap) < ((_ADSR_SLIDER_VALUE_MAX - _ADSR_SLIDER_VALUE_MIN) / 5.0))
			{
				on_adsr4_attack_slider_changed(level);			
			}	
		}
		else if (active_frames_group_adsrs == _FRAMES_GROUP_3)
		{
			/* ADSR 6 Attack */
			level = normalize_slider_value(val, _ADSR_SLIDER_VALUE_MAX, _ADSR_SLIDER_VALUE_MIN);
			/* Change slider value only when it matches the UI slider position */
			if (adsr6_attack_entry > _PAD_MAX_SLIDER_VALUE)
			{
				adsr6_attack_entry = _PAD_MAX_SLIDER_VALUE; 
			}
			
			level_slider_gap = adsr6_attack_entry - level;
			
			if (abs((float)level_slider_gap) < ((_ADSR_SLIDER_VALUE_MAX - _ADSR_SLIDER_VALUE_MIN) / 5.0))
			{
				on_adsr6_attack_slider_changed(level);			
			}	
		}
	}
	else if (evnt == _CONTROL_SLIDER_ORANGE_RED)
	{
		if (active_frames_group_adsrs == _FRAMES_GROUP_1)
		{
			/* ADSR 2 Decay */
			level = normalize_slider_value(val, _ADSR_SLIDER_VALUE_MAX, _ADSR_SLIDER_VALUE_MIN);
			/* Change slider value only when it matches the UI slider position */
			if (adsr2_decay_entry > _PAD_MAX_SLIDER_VALUE)
			{
				adsr2_decay_entry = _PAD_MAX_SLIDER_VALUE; 
			}
			
			level_slider_gap = adsr2_decay_entry - level;
			
			if (abs((float)level_slider_gap) < ((_ADSR_SLIDER_VALUE_MAX - _ADSR_SLIDER_VALUE_MIN) / 5.0))
			{
				on_adsr2_decay_slider_changed(level);			
			}	
		}
		else if (active_frames_group_adsrs == _FRAMES_GROUP_2)
		{
			/* ADSR 4 Decay */
			level = normalize_slider_value(val, _ADSR_SLIDER_VALUE_MAX, _ADSR_SLIDER_VALUE_MIN);
			/* Change slider value only when it matches the UI slider position */
			if (adsr4_decay_entry > _PAD_MAX_SLIDER_VALUE)
			{
				adsr4_decay_entry = _PAD_MAX_SLIDER_VALUE; 
			}
			
			level_slider_gap = adsr4_decay_entry - level;
			
			if (abs((float)level_slider_gap) < ((_ADSR_SLIDER_VALUE_MAX - _ADSR_SLIDER_VALUE_MIN) / 5.0))
			{
				on_adsr4_decay_slider_changed(level);			
			}	
		}
		else if (active_frames_group_adsrs == _FRAMES_GROUP_3)
		{
			/* ADSR 6 Decay */
			level = normalize_slider_value(val, _ADSR_SLIDER_VALUE_MAX, _ADSR_SLIDER_VALUE_MIN);
			/* Change slider value only when it matches the UI slider position */
			if (adsr6_decay_entry > _PAD_MAX_SLIDER_VALUE)
			{
				adsr6_decay_entry = _PAD_MAX_SLIDER_VALUE; 
			}
			
			level_slider_gap = adsr1_decay_entry - level;
			
			if (abs((float)level_slider_gap) < ((_ADSR_SLIDER_VALUE_MAX - _ADSR_SLIDER_VALUE_MIN) / 5.0))
			{
				on_adsr6_decay_slider_changed(level);			
			}	
		}
	}
	else if (evnt == _CONTROL_SLIDER_ORANGE_BLUE)
	{
		if (active_frames_group_adsrs == _FRAMES_GROUP_1)
		{
			/* ADSR 2 Sustain */
			level = normalize_slider_value(val, _ADSR_SLIDER_VALUE_MAX, _ADSR_SLIDER_VALUE_MIN);
			/* Change slider value only when it matches the UI slider position */
			if (adsr2_sustain_entry > _PAD_MAX_SLIDER_VALUE)
			{
				adsr2_sustain_entry = _PAD_MAX_SLIDER_VALUE; 
			}
			
			level_slider_gap = adsr2_sustain_entry - level;
			
			if (abs((float)level_slider_gap) < ((_ADSR_SLIDER_VALUE_MAX - _ADSR_SLIDER_VALUE_MIN) / 5.0))
			{
				on_adsr2_sustain_slider_changed(level);			
			}	
		}
		else if (active_frames_group_adsrs == _FRAMES_GROUP_2)
		{
			/* ADSR 4 Sustain */
			level = normalize_slider_value(val, _ADSR_SLIDER_VALUE_MAX, _ADSR_SLIDER_VALUE_MIN);
			/* Change slider value only when it matches the UI slider position */
			if (adsr4_sustain_entry > _PAD_MAX_SLIDER_VALUE)
			{
				adsr4_sustain_entry = _PAD_MAX_SLIDER_VALUE; 
			}
			
			level_slider_gap = adsr4_sustain_entry - level;
			
			if (abs((float)level_slider_gap) < ((_ADSR_SLIDER_VALUE_MAX - _ADSR_SLIDER_VALUE_MIN) / 5.0))
			{
				on_adsr4_sustain_slider_changed(level);			
			}	
		}
		else if (active_frames_group_adsrs == _FRAMES_GROUP_3)
		{
			/* ADSR 6 Sustain */
			level = normalize_slider_value(val, _ADSR_SLIDER_VALUE_MAX, _ADSR_SLIDER_VALUE_MIN);
			/* Change slider value only when it matches the UI slider position */
			if (adsr6_sustain_entry > _PAD_MAX_SLIDER_VALUE)
			{
				adsr6_sustain_entry = _PAD_MAX_SLIDER_VALUE; 
			}
			
			level_slider_gap = adsr6_sustain_entry - level;
			
			if (abs((float)level_slider_gap) < ((_ADSR_SLIDER_VALUE_MAX - _ADSR_SLIDER_VALUE_MIN) / 5.0))
			{
				on_adsr6_sustain_slider_changed(level);			
			}	
		}
	}
	else if (evnt == _CONTROL_SLIDER_ORANGE_WHITE)
	{
		if (active_frames_group_adsrs == _FRAMES_GROUP_1)
		{
			/* ADSR 2 Release */
			level = normalize_slider_value(val, _ADSR_SLIDER_VALUE_MAX, _ADSR_SLIDER_VALUE_MIN);
			/* Change slider value only when it matches the UI slider position */
			if (adsr2_release_entry > _PAD_MAX_SLIDER_VALUE)
			{
				adsr2_release_entry = _PAD_MAX_SLIDER_VALUE; 
			}
			
			level_slider_gap = adsr2_release_entry - level;
			
			if (abs((float)level_slider_gap) < ((_ADSR_SLIDER_VALUE_MAX - _ADSR_SLIDER_VALUE_MIN) / 5.0))
			{
				on_adsr2_release_slider_changed(level);			
			}	
		}
		else if (active_frames_group_adsrs == _FRAMES_GROUP_2)
		{
			/* ADSR 4 Release */
			level = normalize_slider_value(val, _ADSR_SLIDER_VALUE_MAX, _ADSR_SLIDER_VALUE_MIN);
			/* Change slider value only when it matches the UI slider position */
			if (adsr4_release_entry > _PAD_MAX_SLIDER_VALUE)
			{
				adsr4_release_entry = _PAD_MAX_SLIDER_VALUE; 
			}
			
			level_slider_gap = adsr4_release_entry - level;
			
			if (abs((float)level_slider_gap) < ((_ADSR_SLIDER_VALUE_MAX - _ADSR_SLIDER_VALUE_MIN) / 5.0))
			{
				on_adsr4_release_slider_changed(level);			
			}	
		}
		else if (active_frames_group_adsrs == _FRAMES_GROUP_3)
		{
			/* ADSR 6 Release */
			level = normalize_slider_value(val, _ADSR_SLIDER_VALUE_MAX, _ADSR_SLIDER_VALUE_MIN);
			/* Change slider value only when it matches the UI slider position */
			if (adsr6_release_entry > _PAD_MAX_SLIDER_VALUE)
			{
				adsr6_release_entry = _PAD_MAX_SLIDER_VALUE; 
			}
			
			level_slider_gap = adsr6_release_entry - level;
			
			if (abs((float)level_slider_gap) < ((_ADSR_SLIDER_VALUE_MAX - _ADSR_SLIDER_VALUE_MIN) / 5.0))
			{
				on_adsr6_release_slider_changed(level);			
			}	
		}
	}
}