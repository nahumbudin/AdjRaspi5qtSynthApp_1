/**
* @file		Dialog_AnalogSynth.cpp
*	@author		Nahum Budin
*	@date		25-Oct-2024
*	@version	1.0
*
*	@brief		Used for controling the Analog Synthesizer instrument
*				
*	History:
*			Based on the AdjModSynth project ver 1.1 16-Jan-2021 
*
*/

#include <QTimer>

#include "Dialog_AnalogSynth.h"
#include "ui_Dialog_AnalogSynth.h"
#include "Defs.h"
#include "MainWindow.h"

Dialog_AnalogSynth *Dialog_AnalogSynth::dialog_analog_synth_instance = NULL;

void analog_synth_control_box_event_update_ui_callback_wrapper(int evnt, uint16_t val)
{
	Dialog_AnalogSynth::get_instance()->control_box_ui_update_callback(evnt, val);
}

Dialog_AnalogSynth::Dialog_AnalogSynth(QWidget *parent)
	: QDialog(parent)
	, ui(new Ui::Dialog_AnalogSynth)
{
	ui->setupUi(this);
	dialog_analog_synth_instance = this;
	
	this->setFocus(Qt::ActiveWindowFocusReason);
	
	active_tab = _OSC_1_TAB;
	prev_active_tab = -1;
	active_frames_group_osc1 = _FRAMES_GROUP_1;
	prev_active_frames_group_osc1 = -1;
	active_frames_group_osc2noise = _FRAMES_GROUP_1;
	prev_active_frames_group_osc2noise = -1;
	active_frames_group_mso = _FRAMES_GROUP_1;
	prev_active_frames_group_mso = -1;
	active_frames_group_kps = _FRAMES_GROUP_1;
	prev_active_frames_group_kps = -1;
	active_frames_group_pad = _FRAMES_GROUP_1;
	prev_active_frames_group_pad = -1;
	active_frames_group_filters_amps = _FRAMES_GROUP_1;
	prev_active_frames_group_filters_amps = -1;
	
	osc1_unison_levels[0] = 100;
	
	unison_level_sliders[0] = ui->verticalSlider_Osc1UnisonLevel_1;
	unison_level_sliders[1] = ui->verticalSlider_Osc1UnisonLevel_2;
	unison_level_sliders[2] = ui->verticalSlider_Osc1UnisonLevel_3;
	unison_level_sliders[3] = ui->verticalSlider_Osc1UnisonLevel_4;
	unison_level_sliders[4] = ui->verticalSlider_Osc1UnisonLevel_5;
	unison_level_sliders[5] = ui->verticalSlider_Osc1UnisonLevel_6;
	unison_level_sliders[6] = ui->verticalSlider_Osc1UnisonLevel_7;
	unison_level_sliders[7] = ui->verticalSlider_Osc1UnisonLevel_8;
	unison_level_sliders[8] = ui->verticalSlider_Osc1UnisonLevel_9;
	
	set_osc1_signals_connections();
	init_osc1_combboxes_and_labels();
	osc1_update();
	
	set_osc2_signals_connections();
	init_osc2_combboxes_and_labels();
	osc2_update();
	
	set_noise_signals_connections();
	init_noise_combboxes_and_labels();
	noise_update();
	
	set_mso_signals_connections();
	init_mso_combboxes_and_labels();
	mso_update();
	
	set_kps_signals_connections();
	init_kps_combboxes_and_labels();
	kps_update();
	
	set_pad_signals_connections();
	init_pad_combboxes_and_labels();
	pad_update();
	
	set_filters_amps_signals_connections();
	init_filters_amps_combboxes_and_labels();
	filters_update();
	amps_update();
	
	ui->frame_Osc1Waveform->setStyleSheet(_BACKGROUND_COLOR_CYAN);
	ui->frame_Osc1TuneOffset->setStyleSheet(_BACKGROUND_COLOR_CYAN);
	ui->frame_Osc1FreqMod->setStyleSheet(_BACKGROUND_COLOR_ORANGE);
				
	ui->frame_Osc1PwmMod->setStyleSheet(_BACKGROUND_COLOR_GRAY);
	ui->frame_Osc1AmpMod->setStyleSheet(_BACKGROUND_COLOR_GRAY);
				
	ui->frame_Osc1Drawbars_1_6->setStyleSheet(_BACKGROUND_COLOR_GRAY);
	ui->frame_Osc1Drawbars_7_9->setStyleSheet(_BACKGROUND_COLOR_GRAY);
	
	ui->frame_Osc2Waveform->setStyleSheet(_BACKGROUND_COLOR_CYAN);
	ui->frame_Osc2FreqMod->setStyleSheet(_BACKGROUND_COLOR_ORANGE);
	ui->frame_Osc2SyncOnOsc1->setStyleSheet(_BACKGROUND_COLOR_CYAN);
				
	ui->frame_Osc2PwmMod->setStyleSheet(_BACKGROUND_COLOR_GRAY);
	ui->frame_Osc2AmpMod->setStyleSheet(_BACKGROUND_COLOR_GRAY);				
	ui->frame_Osc2TuneOffset->setStyleSheet(_BACKGROUND_COLOR_GRAY);
				
	ui->frame_NoiseColor->setStyleSheet(_BACKGROUND_COLOR_GRAY);
	ui->frame_NoiseAmpMod->setStyleSheet(_BACKGROUND_COLOR_GRAY);
	
	ui->frame_MsoSegments->setStyleSheet(_BACKGROUND_COLOR_CYAN);
	ui->frame_MsoMorphPreset->setStyleSheet(_BACKGROUND_COLOR_ORANGE);
				
	ui->frame_MsoFreqMod->setStyleSheet(_BACKGROUND_COLOR_GRAY);
	ui->frame_MsoPwmMod->setStyleSheet(_BACKGROUND_COLOR_GRAY);
				
	ui->frame_MsoAmpMod->setStyleSheet(_BACKGROUND_COLOR_GRAY);
	ui->frame_MsoSendFiltersTuneOffset->setStyleSheet(_BACKGROUND_COLOR_GRAY);
	
	ui->frame_PAD_SendFiltersTuneOffset->setStyleSheet(_BACKGROUND_COLOR_CYAN);
	ui->frame_PAD_FreqMod->setStyleSheet(_BACKGROUND_COLOR_ORANGE);
	
	ui->frame_PAD_AmpMod->setStyleSheet(_BACKGROUND_COLOR_GRAY);
	ui->frame_PAD_Profile->setStyleSheet(_BACKGROUND_COLOR_GRAY);
	
	ui->frame_PAD_Haromonys1_6->setStyleSheet(_BACKGROUND_COLOR_GRAY);
	ui->frame__PAD_Haromonys7_10->setStyleSheet(_BACKGROUND_COLOR_GRAY);
	
	ui->frame_FilterParams_1->setStyleSheet(_BACKGROUND_COLOR_CYAN);
	ui->frame_FilterWaveformFreqMod_1->setStyleSheet(_BACKGROUND_COLOR_ORANGE);
	
	ui->frame_FilterParams_2->setStyleSheet(_BACKGROUND_COLOR_GRAY);
	ui->frame_FilterWaveformFreqMod_2->setStyleSheet(_BACKGROUND_COLOR_GRAY);
	
	ui->frame_Amp1->setStyleSheet(_BACKGROUND_COLOR_GRAY);
	ui->frame_Amp2->setStyleSheet(_BACKGROUND_COLOR_GRAY);
	
	mod_synth_register_callback_control_box_event_update_ui(
		&analog_synth_control_box_event_update_ui_callback_wrapper);
	
	MainWindow::get_instance()->register_active_dialog(this);
	
	connect(ui->tabWidget,
		SIGNAL(currentChanged(int)),
		this,
		SLOT(on_tab_selected(int)));
	
	// start a periodic timer after this timeout - 
	start_update_timer(500);
	
}

Dialog_AnalogSynth::~Dialog_AnalogSynth()
{
	
}

Dialog_AnalogSynth *Dialog_AnalogSynth::get_instance(QWidget *parent)
{
	if (dialog_analog_synth_instance == NULL)
	{
		dialog_analog_synth_instance = new Dialog_AnalogSynth(parent);
	}
	
	return dialog_analog_synth_instance;
}

void Dialog_AnalogSynth::closeEvent(QCloseEvent *event)
{
	//if (close_event_callback_ptr != NULL)
	//{
	//	close_event_callback_ptr();
	//}
	
	hide();
}

void Dialog_AnalogSynth::control_box_ui_update_callback(int evnt, uint16_t val)
{
	if (!this->hasFocus())
	{
		return;
	}
	
	if ((evnt == _CONTROL_FUNCTION_PUSHBUTTON_UP) &&
			 (val == 0))
	{
		/* Switch TAB */
		active_tab++;
		if (active_tab > _MODULATORS_2_TAB)
		{
			active_tab = _OSC_1_TAB;
		}
	}
	
	if (active_tab == _OSC_1_TAB)
	{
		control_box_events_handler_osc_1(evnt, val);
	}
	else if (active_tab == _OSC_2_NOISE_TAB)
	{
		control_box_events_handler_osc_2_noise(evnt, val);
	}
	else if (active_tab == _MSO_TAB)
	{
		control_box_events_handler_mso(evnt, val);
	}
	else if (active_tab == _KARPLUS_TAB)
	{
		control_box_events_handler_kps(evnt, val);
	}
	else if (active_tab == _PAD_SYNTH_TAB)
	{
		control_box_events_handler_pad(evnt, val);
	}
	else if (active_tab == _FILTERS_AMPS_TAB)
	{
		control_box_events_handler_filters_amps(evnt, val);
	}
	else if ((active_tab == _MODULATORS_1_TAB) || (active_tab == _MODULATORS_2_TAB))
	{
		
	}
	
}

void Dialog_AnalogSynth::start_update_timer(int interval)
{
	QTimer *timer = new QTimer(this);
	connect(timer, SIGNAL(timeout()), this, SLOT(update_gui()));
	timer->start(interval);
}

void Dialog_AnalogSynth::timerEvent(QTimerEvent *event)
{
	killTimer(event->timerId());
	start_update_timer(100);
}

void Dialog_AnalogSynth::update_gui()
{
	if (active_tab != prev_active_tab)
	{
		ui->tabWidget->setCurrentIndex(active_tab);
		
		prev_active_tab = active_tab;
	}
	
	if (mso_replot_waveform)
	{
		setup_mso_plot(ui->widget_MsoWaveformPlot);
		ui->widget_MsoWaveformPlot->replot();
		
		mso_replot_waveform = false;
	}
	
	if (update_profile_plot)
	{
		pad_replot_profile();
		
		update_profile_plot = false;
	}
	
	if (update_spectrum_plot)
	{
		pad_replot_spectrum();
		
		update_profile_plot = false;
	}
	
	if (active_tab == _OSC_1_TAB)
	{	
		if (active_frames_group_osc1 != prev_active_frames_group_osc1)
		{
			if (active_frames_group_osc1 == _FRAMES_GROUP_1)
			{
				ui->frame_Osc1Waveform->setStyleSheet(_BACKGROUND_COLOR_CYAN);
				ui->frame_Osc1TuneOffset->setStyleSheet(_BACKGROUND_COLOR_CYAN);
				ui->frame_Osc1FreqMod->setStyleSheet(_BACKGROUND_COLOR_ORANGE);
				
				ui->frame_Osc1PwmMod->setStyleSheet(_BACKGROUND_COLOR_GRAY);
				ui->frame_Osc1AmpMod->setStyleSheet(_BACKGROUND_COLOR_GRAY);
				
				ui->frame_Osc1Drawbars_1_6->setStyleSheet(_BACKGROUND_COLOR_GRAY);
				ui->frame_Osc1Drawbars_7_9->setStyleSheet(_BACKGROUND_COLOR_GRAY);
			}
			else if (active_frames_group_osc1 == _FRAMES_GROUP_2)
			{
				ui->frame_Osc1Waveform->setStyleSheet(_BACKGROUND_COLOR_GRAY);
				ui->frame_Osc1TuneOffset->setStyleSheet(_BACKGROUND_COLOR_GRAY);
				ui->frame_Osc1FreqMod->setStyleSheet(_BACKGROUND_COLOR_GRAY);
				
				ui->frame_Osc1PwmMod->setStyleSheet(_BACKGROUND_COLOR_CYAN);
				ui->frame_Osc1AmpMod->setStyleSheet(_BACKGROUND_COLOR_ORANGE);
				
				ui->frame_Osc1Drawbars_1_6->setStyleSheet(_BACKGROUND_COLOR_GRAY);
				ui->frame_Osc1Drawbars_7_9->setStyleSheet(_BACKGROUND_COLOR_GRAY);
			}
			else if (active_frames_group_osc1 == _FRAMES_GROUP_3)
			{
				ui->frame_Osc1Waveform->setStyleSheet(_BACKGROUND_COLOR_GRAY);
				ui->frame_Osc1TuneOffset->setStyleSheet(_BACKGROUND_COLOR_GRAY);
				ui->frame_Osc1FreqMod->setStyleSheet(_BACKGROUND_COLOR_GRAY);
				
				ui->frame_Osc1PwmMod->setStyleSheet(_BACKGROUND_COLOR_GRAY);
				ui->frame_Osc1AmpMod->setStyleSheet(_BACKGROUND_COLOR_GRAY);
				
				ui->frame_Osc1Drawbars_1_6->setStyleSheet(_BACKGROUND_COLOR_CYAN);
				ui->frame_Osc1Drawbars_7_9->setStyleSheet(_BACKGROUND_COLOR_ORANGE);
			}
			
			prev_active_frames_group_osc1 = active_frames_group_osc1;
		}
	}
	else if (active_tab == _OSC_2_NOISE_TAB)
	{	
		if (active_frames_group_osc2noise != prev_active_frames_group_osc2noise)
		{
			if (active_frames_group_osc2noise == _FRAMES_GROUP_1)
			{
				ui->frame_Osc2Waveform->setStyleSheet(_BACKGROUND_COLOR_CYAN);
				ui->frame_Osc2FreqMod->setStyleSheet(_BACKGROUND_COLOR_ORANGE);
				ui->frame_Osc2SyncOnOsc1->setStyleSheet(_BACKGROUND_COLOR_CYAN);
				
				ui->frame_Osc2PwmMod->setStyleSheet(_BACKGROUND_COLOR_GRAY);
				ui->frame_Osc2AmpMod->setStyleSheet(_BACKGROUND_COLOR_GRAY);				
				ui->frame_Osc2TuneOffset->setStyleSheet(_BACKGROUND_COLOR_GRAY);
				
				ui->frame_NoiseColor->setStyleSheet(_BACKGROUND_COLOR_GRAY);
				ui->frame_NoiseAmpMod->setStyleSheet(_BACKGROUND_COLOR_GRAY);
			}
			else if (active_frames_group_osc2noise == _FRAMES_GROUP_2)
			{
				ui->frame_Osc2Waveform->setStyleSheet(_BACKGROUND_COLOR_GRAY);
				ui->frame_Osc2FreqMod->setStyleSheet(_BACKGROUND_COLOR_GRAY);
				ui->frame_Osc2SyncOnOsc1->setStyleSheet(_BACKGROUND_COLOR_CYAN);
				
				ui->frame_Osc2PwmMod->setStyleSheet(_BACKGROUND_COLOR_CYAN);
				ui->frame_Osc2AmpMod->setStyleSheet(_BACKGROUND_COLOR_ORANGE);				
				ui->frame_Osc2TuneOffset->setStyleSheet(_BACKGROUND_COLOR_CYAN);
				
				ui->frame_NoiseColor->setStyleSheet(_BACKGROUND_COLOR_GRAY);
				ui->frame_NoiseAmpMod->setStyleSheet(_BACKGROUND_COLOR_GRAY);
			}
			else if (active_frames_group_osc2noise == _FRAMES_GROUP_3)
			{
				ui->frame_Osc2Waveform->setStyleSheet(_BACKGROUND_COLOR_GRAY);
				ui->frame_Osc2FreqMod->setStyleSheet(_BACKGROUND_COLOR_GRAY);
				ui->frame_Osc2SyncOnOsc1->setStyleSheet(_BACKGROUND_COLOR_CYAN);
				
				ui->frame_Osc2PwmMod->setStyleSheet(_BACKGROUND_COLOR_GRAY);
				ui->frame_Osc2AmpMod->setStyleSheet(_BACKGROUND_COLOR_GRAY);				
				ui->frame_Osc2TuneOffset->setStyleSheet(_BACKGROUND_COLOR_GRAY);
				
				ui->frame_NoiseColor->setStyleSheet(_BACKGROUND_COLOR_CYAN);
				ui->frame_NoiseAmpMod->setStyleSheet(_BACKGROUND_COLOR_ORANGE);
			}
			
			prev_active_frames_group_osc2noise = active_frames_group_osc2noise;
		}
	}
	else if (active_tab == _MSO_TAB)
	{
		if (active_frames_group_mso != prev_active_frames_group_mso)
		{
			if (active_frames_group_mso == _FRAMES_GROUP_1)
			{
				ui->frame_MsoSegments->setStyleSheet(_BACKGROUND_COLOR_CYAN);
				ui->frame_MsoMorphPreset->setStyleSheet(_BACKGROUND_COLOR_ORANGE);
				
				ui->frame_MsoFreqMod->setStyleSheet(_BACKGROUND_COLOR_GRAY);
				ui->frame_MsoPwmMod->setStyleSheet(_BACKGROUND_COLOR_GRAY);
				
				ui->frame_MsoAmpMod->setStyleSheet(_BACKGROUND_COLOR_GRAY);
				ui->frame_MsoSendFiltersTuneOffset->setStyleSheet(_BACKGROUND_COLOR_GRAY);
			}
			else if (active_frames_group_mso == _FRAMES_GROUP_2)
			{
				ui->frame_MsoSegments->setStyleSheet(_BACKGROUND_COLOR_GRAY);
				ui->frame_MsoMorphPreset->setStyleSheet(_BACKGROUND_COLOR_GRAY);
				
				ui->frame_MsoFreqMod->setStyleSheet(_BACKGROUND_COLOR_CYAN);
				ui->frame_MsoPwmMod->setStyleSheet(_BACKGROUND_COLOR_ORANGE);
				
				ui->frame_MsoAmpMod->setStyleSheet(_BACKGROUND_COLOR_GRAY);
				ui->frame_MsoSendFiltersTuneOffset->setStyleSheet(_BACKGROUND_COLOR_GRAY);
			}
			else if (active_frames_group_mso == _FRAMES_GROUP_3)
			{
				ui->frame_MsoSegments->setStyleSheet(_BACKGROUND_COLOR_GRAY);
				ui->frame_MsoMorphPreset->setStyleSheet(_BACKGROUND_COLOR_GRAY);
				
				ui->frame_MsoFreqMod->setStyleSheet(_BACKGROUND_COLOR_GRAY);
				ui->frame_MsoPwmMod->setStyleSheet(_BACKGROUND_COLOR_GRAY);
				
				ui->frame_MsoAmpMod->setStyleSheet(_BACKGROUND_COLOR_ORANGE);
				ui->frame_MsoSendFiltersTuneOffset->setStyleSheet(_BACKGROUND_COLOR_CYAN);
			}
			
			prev_active_frames_group_mso = active_frames_group_mso;
		}
		
	}
	else if (active_tab == _KARPLUS_TAB)
	{
		if (active_frames_group_mso != prev_active_frames_group_mso)
		{
			if (active_frames_group_mso == _FRAMES_GROUP_1)
			{
				
			}
			
			prev_active_frames_group_kps = active_frames_group_kps;
		}
	}
	else if (active_tab == _PAD_SYNTH_TAB)
	{
		if (active_frames_group_pad != prev_active_frames_group_pad)
		{
			if (active_frames_group_pad == _FRAMES_GROUP_1)
			{
				ui->frame_PAD_SendFiltersTuneOffset->setStyleSheet(_BACKGROUND_COLOR_CYAN);
				ui->frame_PAD_FreqMod->setStyleSheet(_BACKGROUND_COLOR_ORANGE);
				
				ui->frame_PAD_AmpMod->setStyleSheet(_BACKGROUND_COLOR_GRAY);
				ui->frame_PAD_Profile->setStyleSheet(_BACKGROUND_COLOR_GRAY);
				
				ui->frame_PAD_Haromonys1_6->setStyleSheet(_BACKGROUND_COLOR_GRAY);
				ui->frame__PAD_Haromonys7_10->setStyleSheet(_BACKGROUND_COLOR_GRAY);
			}
			else if (active_frames_group_pad == _FRAMES_GROUP_2)
			{
				ui->frame_PAD_SendFiltersTuneOffset->setStyleSheet(_BACKGROUND_COLOR_GRAY);
				ui->frame_PAD_FreqMod->setStyleSheet(_BACKGROUND_COLOR_GRAY);
				
				ui->frame_PAD_AmpMod->setStyleSheet(_BACKGROUND_COLOR_CYAN);
				ui->frame_PAD_Profile->setStyleSheet(_BACKGROUND_COLOR_ORANGE);
				
				ui->frame_PAD_Haromonys1_6->setStyleSheet(_BACKGROUND_COLOR_GRAY);
				ui->frame__PAD_Haromonys7_10->setStyleSheet(_BACKGROUND_COLOR_GRAY);
			}
			else if (active_frames_group_pad == _FRAMES_GROUP_3)
			{
				ui->frame_PAD_SendFiltersTuneOffset->setStyleSheet(_BACKGROUND_COLOR_GRAY);
				ui->frame_PAD_FreqMod->setStyleSheet(_BACKGROUND_COLOR_GRAY);
				
				ui->frame_PAD_AmpMod->setStyleSheet(_BACKGROUND_COLOR_GRAY);
				ui->frame_PAD_Profile->setStyleSheet(_BACKGROUND_COLOR_GRAY);
				
				ui->frame_PAD_Haromonys1_6->setStyleSheet(_BACKGROUND_COLOR_CYAN);
				ui->frame__PAD_Haromonys7_10->setStyleSheet(_BACKGROUND_COLOR_ORANGE);
			}
			
			prev_active_frames_group_pad = active_frames_group_pad;
		}
	}
	else if (active_tab == _FILTERS_AMPS_TAB)
	{
		if (active_frames_group_filters_amps != prev_active_frames_group_filters_amps)
		{
			if (active_frames_group_filters_amps == _FRAMES_GROUP_1)
			{
				ui->frame_FilterParams_1->setStyleSheet(_BACKGROUND_COLOR_CYAN);
				ui->frame_FilterWaveformFreqMod_1->setStyleSheet(_BACKGROUND_COLOR_ORANGE);
	
				ui->frame_FilterParams_2->setStyleSheet(_BACKGROUND_COLOR_GRAY);
				ui->frame_FilterWaveformFreqMod_2->setStyleSheet(_BACKGROUND_COLOR_GRAY);
	
				ui->frame_Amp1->setStyleSheet(_BACKGROUND_COLOR_GRAY);
				ui->frame_Amp2->setStyleSheet(_BACKGROUND_COLOR_GRAY);
			}
			else if (active_frames_group_filters_amps == _FRAMES_GROUP_2)
			{
				ui->frame_FilterParams_1->setStyleSheet(_BACKGROUND_COLOR_GRAY);
				ui->frame_FilterWaveformFreqMod_1->setStyleSheet(_BACKGROUND_COLOR_GRAY);
	
				ui->frame_FilterParams_2->setStyleSheet(_BACKGROUND_COLOR_CYAN);
				ui->frame_FilterWaveformFreqMod_2->setStyleSheet(_BACKGROUND_COLOR_ORANGE);
	
				ui->frame_Amp1->setStyleSheet(_BACKGROUND_COLOR_GRAY);
				ui->frame_Amp2->setStyleSheet(_BACKGROUND_COLOR_GRAY);
			}
			else if (active_frames_group_filters_amps == _FRAMES_GROUP_3)
			{
				ui->frame_FilterParams_1->setStyleSheet(_BACKGROUND_COLOR_GRAY);
				ui->frame_FilterWaveformFreqMod_1->setStyleSheet(_BACKGROUND_COLOR_GRAY);
	
				ui->frame_FilterParams_2->setStyleSheet(_BACKGROUND_COLOR_GRAY);
				ui->frame_FilterWaveformFreqMod_2->setStyleSheet(_BACKGROUND_COLOR_GRAY);
	
				ui->frame_Amp1->setStyleSheet(_BACKGROUND_COLOR_CYAN);
				ui->frame_Amp2->setStyleSheet(_BACKGROUND_COLOR_ORANGE);
			}
		}
	}
}

void Dialog_AnalogSynth::on_dialog_close()
{
	hide();
}

void Dialog_AnalogSynth::on_tab_selected(int tab)
{
	active_tab = _OSC_1_TAB + tab;
}
	
	

