#pragma once

#include <QColor>

#define _MIDI_MIXER_CHANNELS_1_8	0
#define _MIDI_MIXER_CHANNELS_9_16	1

#define _OSC_1_TAB					0
#define _OSC_2_NOISE_TAB			1
#define _MSO_TAB					2
#define _KARPLUS_TAB				3
#define _PAD_SYNTH_TAB				4
#define _FILTERS_TAB				5
#define _AMP_TAB					6
#define _MODULATORS_1_TAB			7
#define _MODULATORS_2_TAB			8

#define _FRAMES_GROUP_1				0
#define _FRAMES_GROUP_2				1
#define _FRAMES_GROUP_3				2

#define _CONTROL_COLOR_BLACK		QColor(110, 110, 110)
#define _CONTROL_COLOR_GREEN		QColor(22, 205, 75)
#define _CONTROL_COLOR_RED			QColor(255, 0, 0)
#define _CONTROL_COLOR_BLUE			QColor(10, 149, 255)
#define _CONTROL_COLOR_WHITE		QColor(255, 255, 255)
#define _CONTROL_COLOR_YELLOW		QColor(255, 255, 0)

#define _BACKGROUND_COLOR_CYAN		"background-color: rgb(0, 255, 255);"
#define _BACKGROUND_COLOR_ORANGE	"background-color: rgb(255, 85, 0);"
#define _BACKGROUND_COLOR_GRAY		"background-color: rgb(230, 230, 230);"


#define _SEND_FILTER_MAX			100
#define _SEND_FILTER_MIN			0

#define _MODULATION_LEVEL_MAX		100
#define _MODULATION_LEVEL_MIN		0

#define _OSC_WAVEFORM_SYMETRY_MAX	95
#define _OSC_WAVEFORM_SYMETRY_MIN	5

#define _OSC1_UNISON_LEVEL_MAX		100
#define _OSC1_UNISON_LEVEL_MIN		0
#define _OSC1_UNISON_DETUNE_MAX		100
#define _OSC1_UNISON_DETUNE_MIN		0
#define _OSC1_UNISON_DISTORTION_MAX	100
#define _OSC1_UNISON_DISTORTION_MIN	0

#define _KPS_MAX_SLIDER_VALUE		100
#define _KPS_MIN_SLIDER_VALUE		1

#define _PAD_MAX_SLIDER_VALUE		100
#define _PAD_MIN_SLIDER_VALUE		0

class ModulePannel;

typedef struct activeModules
{
	en_modules_ids_t module_id;
	QString module_name;
	ModulePannel *module_pannel_object;
	bool pending_close_event;
	
	activeModules(en_modules_ids_t module_id = en_modules_ids_t::none_module_id)
		: module_id(module_id)
	{}
	
	
} active_module_data_t;



