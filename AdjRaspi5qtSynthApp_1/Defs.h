#pragma once

#include <QColor>

#define _MIDI_MIXER_CHANNELS_1_8	0
#define _MIDI_MIXER_CHANNELS_9_16	1

#define _OSC_1_TAB					0
#define _OSC_2_NOISE_TAB			1
#define _MSO_TAB					2
#define _KARPLUS_TAB				3
#define _PAD_SYNTH_TAB				4
#define _FILTERS_AMPS_TAB			5
#define _MODULATORS_ADSRS_TAB		6
#define _MODULATORS_LFOS_TAB		7
#define _DISTORTION_TAB				8

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

#define _FILTER_KNOB_MAX_VALUE		100
#define _FILTER_KNOB_MIN_VALUE		0

#define _AMP_KNOB_MAX_VALUE			100
#define _AMP_KNOB_MIN_VALUE			0

#define _MSO_PRESET_USER			0
#define _MSO_PRESET_SINE			1
#define _MSO_PRESET_SQUARE			2
#define _MSO_PRESET_PULSE			3
#define _MSO_PRESET_SAW				4

#define _LFO_RATE_ENTRY_MAX			100
#define _LFO_RATE_ENTRY_MIN			0
#define _LFO_SYMMETRY_ENTRY_MAX		95
#define _LFO_SYMMETRY_ENTRY_MIN		5

#define _ADSR_SLIDER_VALUE_MAX		100
#define _ADSR_SLIDER_VALUE_MIN		0

#define _DISTORTION_ENTRY_MAX		100
#define _DISTORTION_ENTRY_MIN		0

#define _ADSR_CURVE_START_POINT					0
#define _ADSR_CURVE_TIME_MULTIPLIER				10		// 10 pixels per second
#define _ADSR_CURVE_SUSTAIN_SEGMENT_LENGTH		40
#define _ADSR_CURVE_HEIGHT						100

#define _ADSR_CURVE_VIEW_WIDGET_SHOW_TIME_SEC	5

#define _MAX_NUM_OF_INSTRUMENTS					128


class InstrumentPannel;

typedef struct activeInstruments
{
	en_instruments_ids_t instrument_id;
	QString instrument_name;
	InstrumentPannel *instrument_pannel_object;
	bool pending_close_event;
	
	activeInstruments(en_instruments_ids_t instrument_id = en_instruments_ids_t::none_instrument_id)
		: instrument_id(instrument_id)
	{}
	
	
} active_instrument_data_t;



