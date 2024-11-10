/**
* @file		Dialog_AnalogSynthOsc1Tab.h
*	@author		Nahum Budin
*	@date		2-Nov-2024
*	@version	1.0
*
*	@brief		Analog Synthesizer instrument Osc2 and Noise Tab handling
*				
*	History:
*			Based on the AdjModSynth project ver 1.1 16-Jan-2021 
*
*/

#include "Dialog_AnalogSynth.h"
#include "ui_Dialog_AnalogSynth.h"
#include "utils.h"

#include "libAdjRaspi5SynthAPI.h"


void Dialog_AnalogSynth::set_osc2_signals_connections()
{
	connect(ui->horizontalSlider_Osc2Symetry,
		SIGNAL(valueChanged(int)),
		this,
		SLOT(on_osc2_waveform_symetry_slider_cahanged(int)));
	
	connect(ui->spinBox_Osc2Symetry,
		SIGNAL(valueChanged(int)),
		this,
		SLOT(on_osc2_waveform_symetry_spinbox_changed(int)));
	
	connect(ui->spinBox_Osc2SendFilter1,
		SIGNAL(valueChanged(int)),
		this,
		SLOT(on_osc2_send_filter_1_spinbox_changed(int)));
	
	connect(ui->spinBox_Osc2SendFilter2,
		SIGNAL(valueChanged(int)),
		this,
		SLOT(on_osc2_send_filter_2_spinbox_changed(int)));
	
	connect(ui->spinBox_Osc2FreqModLfoLevel,
		SIGNAL(valueChanged(int)),
		this,
		SLOT(on_osc2_freq_mod_lfo_level_spinbox_changed(int)));
	
	connect(ui->spinBox_Osc2FreqModAdsrLevel,
		SIGNAL(valueChanged(int)),
		this,
		SLOT(on_osc2_freq_mod_adsr_level_spinbox_changed(int)));
	
	connect(ui->spinBox_Osc2PwmModLfoLevel,
		SIGNAL(valueChanged(int)),
		this,
		SLOT(on_osc2_pwm_mod_lfo_level_spinbox_changed(int)));
	
	connect(ui->spinBox_Osc2PwmModAdsrLevel,
		SIGNAL(valueChanged(int)),
		this,
		SLOT(on_osc2_pwm_mod_adsr_level_spinbox_changed(int)));
	
	connect(ui->spinBox_Osc2AmpModLfoLevel,
		SIGNAL(valueChanged(int)),
		this,
		SLOT(on_osc2_amp_mod_lfo_level_spinbox_changed(int)));
	
	connect(ui->spinBox_Osc2AmpModAdsrLevel,
		SIGNAL(valueChanged(int)),
		this,
		SLOT(on_osc2_amp_mod_adsr_level_spinbox_changed(int)));
	
	connect(ui->dial_Osc2SendFilter1,
		SIGNAL(valueChanged(int)),
		this,
		SLOT(on_osc2_send_filter_1_dial_changed(int)));
	
	connect(ui->dial_Osc2SendFilter2,
		SIGNAL(valueChanged(int)),
		this,
		SLOT(on_osc2_send_filter_2_dial_changed(int)));
	
	connect(ui->dial_Osc2FreqModLFOLevel,
		SIGNAL(valueChanged(int)),
		this,
		SLOT(on_osc2_freq_mod_lfo_level_dial_changed(int)));
	
	connect(ui->dial_Osc2FreqModAdsrLevel,
		SIGNAL(valueChanged(int)),
		this,
		SLOT(on_osc2_freq_mod_adsr_level_dial_changed(int)));
	
	connect(ui->dial_Osc2PwmModLFOLevel,
		SIGNAL(valueChanged(int)),
		this,
		SLOT(on_osc2_pwm_mod_lfo_level_dial_changed(int)));
	
	connect(ui->dial_Osc2PwmModAdsrLevel,
		SIGNAL(valueChanged(int)),
		this,
		SLOT(on_osc2_pwm_mod_adsr_level_dial_changed(int)));
	
	connect(ui->dial_Osc2AmpModLFOLevel,
		SIGNAL(valueChanged(int)),
		this,
		SLOT(on_osc2_amp_mod_lfo_level_dial_changed(int)));
	
	connect(ui->dial_Osc2AmpModAdsrLevel,
		SIGNAL(valueChanged(int)),
		this,
		SLOT(on_osc2_amp_mod_adsr_level_dial_changed(int)));
	
	connect(ui->comboBox_Osc2AmpModAdsr,
		SIGNAL(currentIndexChanged(int)),
		this,
		SLOT(on_osc2_amp_mod_adsr_combobox_changed(int)));
	
	connect(ui->comboBox_Osc2AmpModLFO,
		SIGNAL(currentIndexChanged(int)),
		this,
		SLOT(on_osc2_amp_mod_lfo_combobox_changed(int)));
	
	connect(ui->comboBox_Osc2FreqModAdsr,
		SIGNAL(currentIndexChanged(int)),
		this,
		SLOT(on_osc2_freq_mod_adsr_combobox_changed(int)));
	
	connect(ui->comboBox_Osc2FreqModLFO,
		SIGNAL(currentIndexChanged(int)),
		this,
		SLOT(on_osc2_freq_mod_lfo_combobox_changed(int)));
	
	connect(ui->comboBox_Osc2PwmModAdsr,
		SIGNAL(currentIndexChanged(int)),
		this,
		SLOT(on_osc2_pwm_mod_adsr_combobox_changed(int)));
	
	connect(ui->comboBox_Osc2PwmModLFO,
		SIGNAL(currentIndexChanged(int)),
		this,
		SLOT(on_osc2_pwm_mod_lfo_combobox_changed(int)));
	
	connect(ui->comboBox_Osc2TuneCents,
		SIGNAL(currentIndexChanged(int)),
		this,
		SLOT(on_osc2_tune_cents_combobox_changed(int)));
	
	connect(ui->comboBox_Osc2TuneOctave,
		SIGNAL(currentIndexChanged(int)),
		this,
		SLOT(on_osc2_tune_octave_combobox_changed(int)));
	
	connect(ui->comboBox_Osc2TuneSemitones,
		SIGNAL(currentIndexChanged(int)),
		this,
		SLOT(on_osc2_tune_semitones_combobox_changed(int)));
	
	connect(ui->comboBox_Osc2Waveform,
		SIGNAL(currentIndexChanged(int)),
		this,
		SLOT(on_osc2_waveform_combobox_changed(int)));
	
	connect(ui->checkBox_Osc2Active,
		SIGNAL(toggled(bool)),
		this,
		SLOT(on_osc2_enable_changed(bool)));

	connect(ui->checkBox_Osc2SyncOnOsc1,
		SIGNAL(toggled(bool)),
		this,
		SLOT(on_osc2_sync_on_osc1_enable_changed(bool)));
}

void Dialog_AnalogSynth::init_osc2_combboxes_and_labels()
{
	if (string_waveforms_list.size() == 0)
	{
		/* Do only once for Osc1 and Osc2 */
		string_waveforms_list.append("Sine");
		string_waveforms_list.append("Square");
		string_waveforms_list.append("Pulse");
		string_waveforms_list.append("Triangle");
		string_waveforms_list.append("Sample & Hold");
	}
	
	ui->comboBox_Osc2Waveform->blockSignals(true);
	ui->comboBox_Osc2Waveform->addItems(string_waveforms_list);
	ui->comboBox_Osc2Waveform->blockSignals(false);
	
	if (string_adsr_values.size() == 0)
	{
		/* Do only once for all */
		string_adsr_values.append("-----");
		string_adsr_values.append("ENV 1");
		string_adsr_values.append("ENV 2");
		string_adsr_values.append("ENV 3");
		string_adsr_values.append("ENV 4");
		string_adsr_values.append("ENV 5");
	
		string_lfo_values.append("-----");
		string_lfo_values.append("LFO 1");
		string_lfo_values.append("LFO 2");
		string_lfo_values.append("LFO 3");
		string_lfo_values.append("LFO 4");
		string_lfo_values.append("LFO 5");
		string_lfo_values.append("LFO 1 0.5s");
		string_lfo_values.append("LFO 2 0.5s");
		string_lfo_values.append("LFO 3 0.5s");
		string_lfo_values.append("LFO 4 0.5s");
		string_lfo_values.append("LFO 5 0.5s");
		string_lfo_values.append("LFO 1 1.0s");
		string_lfo_values.append("LFO 2 1.0s");
		string_lfo_values.append("LFO 3 1.0s");
		string_lfo_values.append("LFO 4 1.0s");
		string_lfo_values.append("LFO 5 1.0s");
		string_lfo_values.append("LFO 1 1.5s");
		string_lfo_values.append("LFO 2 1.5s");
		string_lfo_values.append("LFO 3 1.5s");
		string_lfo_values.append("LFO 4 1.5s");
		string_lfo_values.append("LFO 5 1.5s");
		string_lfo_values.append("LFO 1 2.0s");
		string_lfo_values.append("LFO 2 2.0s");
		string_lfo_values.append("LFO 3 2.0s");
		string_lfo_values.append("LFO 4 2.0s");
		string_lfo_values.append("LFO 5 2.0s");
	}
	
	ui->comboBox_Osc2FreqModAdsr->blockSignals(true);
	ui->comboBox_Osc2FreqModAdsr->addItems(string_adsr_values);
	ui->comboBox_Osc2FreqModAdsr->blockSignals(false);

	ui->comboBox_Osc2FreqModLFO->blockSignals(true);
	ui->comboBox_Osc2FreqModLFO->addItems(string_lfo_values);
	ui->comboBox_Osc2FreqModLFO->blockSignals(false);

	ui->comboBox_Osc2PwmModAdsr->blockSignals(true);
	ui->comboBox_Osc2PwmModAdsr->addItems(string_adsr_values);
	ui->comboBox_Osc2PwmModAdsr->blockSignals(false);

	ui->comboBox_Osc2PwmModLFO->blockSignals(true);
	ui->comboBox_Osc2PwmModLFO->addItems(string_lfo_values);
	ui->comboBox_Osc2PwmModLFO->blockSignals(false);

	ui->comboBox_Osc2AmpModAdsr->blockSignals(true);
	ui->comboBox_Osc2AmpModAdsr->addItems(string_adsr_values);
	ui->comboBox_Osc2AmpModAdsr->blockSignals(false);

	ui->comboBox_Osc2AmpModLFO->blockSignals(true);
	ui->comboBox_Osc2AmpModLFO->addItems(string_lfo_values);
	ui->comboBox_Osc2AmpModLFO->blockSignals(false);
	
	ui->comboBox_Osc2TuneOctave->blockSignals(true);
	ui->comboBox_Osc2TuneSemitones->blockSignals(true);
	ui->comboBox_Osc2TuneCents->blockSignals(true);
	
	for (int i = _OSC_DETUNE_MIN_OCTAVE; i <= _OSC_DETUNE_MAX_OCTAVE; i++)
	{
		ui->comboBox_Osc2TuneOctave->addItem(QString::number(i));
	}

	for (int i = _OSC_DETUNE_MIN_SEMITONES; i <= _OSC_DETUNE_MAX_SEMITONES; i++)
	{
		ui->comboBox_Osc2TuneSemitones->addItem(QString::number(i));
	}

	for (int i = 4 * _OSC_DETUNE_MIN_CENTS; i <= 4 * _OSC_DETUNE_MAX_CENTS; i++)
	{
		// 0.25 steps
		ui->comboBox_Osc2TuneCents->addItem(QString::number(i / 4.f));
	}

	ui->comboBox_Osc2TuneOctave->blockSignals(false);
	ui->comboBox_Osc2TuneSemitones->blockSignals(false);
	ui->comboBox_Osc2TuneCents->blockSignals(false);
}

void Dialog_AnalogSynth::osc2_update()
{
	ui->comboBox_Osc2Waveform->blockSignals(true);
	ui->comboBox_Osc2Waveform->setCurrentIndex(mod_synth_get_active_osc2_waveform());
	ui->comboBox_Osc2Waveform->blockSignals(false);

	ui->horizontalSlider_Osc2Symetry->blockSignals(true);
	ui->horizontalSlider_Osc2Symetry->setValue(mod_synth_get_active_osc2_pwm_percents());
	ui->horizontalSlider_Osc2Symetry->blockSignals(false);

	ui->comboBox_Osc2TuneOctave->blockSignals(true);
	ui->comboBox_Osc2TuneOctave->setCurrentIndex(mod_synth_get_active_osc2_detune_octave() - 
		mod_synth_get_osc_detune_min_octave());
	ui->comboBox_Osc2TuneOctave->blockSignals(false);

	ui->comboBox_Osc2TuneSemitones->blockSignals(true);
	ui->comboBox_Osc2TuneSemitones->setCurrentIndex(mod_synth_get_active_osc2_detune_semitones() - 
		mod_synth_get_osc_detune_min_semitones());
	ui->comboBox_Osc2TuneSemitones->blockSignals(false);

	ui->comboBox_Osc2TuneCents->blockSignals(true);
	ui->comboBox_Osc2TuneCents->setCurrentIndex(mod_synth_get_active_osc2_detune_cents() - 
		mod_synth_get_osc_detune_min_cents() * 4.f);
	ui->comboBox_Osc2TuneCents->blockSignals(false);

	ui->dial_Osc2SendFilter1->blockSignals(true);
	ui->dial_Osc2SendFilter1->setValue(mod_synth_get_active_osc2_send_filter_1());
	ui->dial_Osc2SendFilter1->blockSignals(false);

	ui->dial_Osc2SendFilter2->blockSignals(true);
	ui->dial_Osc2SendFilter2->setValue(mod_synth_get_active_osc2_send_filter_2());
	ui->dial_Osc2SendFilter2->blockSignals(false);

	ui->comboBox_Osc2FreqModLFO->blockSignals(true);
	ui->comboBox_Osc2FreqModLFO->setCurrentIndex(mod_synth_get_active_osc2_freq_mod_lfo());
	ui->comboBox_Osc2FreqModLFO->blockSignals(false);

	ui->dial_Osc2FreqModLFOLevel->blockSignals(true);
	ui->dial_Osc2FreqModLFOLevel->setValue(mod_synth_get_active_osc2_freq_mod_lfo_level());
	ui->dial_Osc2FreqModLFOLevel->blockSignals(false);

	ui->comboBox_Osc2FreqModAdsr->blockSignals(true);
	ui->comboBox_Osc2FreqModAdsr->setCurrentIndex(mod_synth_get_active_osc2_freq_mod_env());
	ui->comboBox_Osc2FreqModAdsr->blockSignals(false);

	ui->dial_Osc2FreqModAdsrLevel->blockSignals(true);
	ui->dial_Osc2FreqModAdsrLevel->setValue(mod_synth_get_active_osc2_freq_mod_env_level());
	ui->dial_Osc2FreqModAdsrLevel->blockSignals(false);

	ui->comboBox_Osc2PwmModLFO->blockSignals(true);
	ui->comboBox_Osc2PwmModLFO->setCurrentIndex(mod_synth_get_active_osc2_pwm_mod_lfo());
	ui->comboBox_Osc2PwmModLFO->blockSignals(false);

	ui->dial_Osc2PwmModLFOLevel->blockSignals(true);
	ui->dial_Osc2PwmModLFOLevel->setValue(mod_synth_get_active_osc2_pwm_mod_lfo_level());
	ui->dial_Osc2PwmModLFOLevel->blockSignals(false);

	ui->comboBox_Osc2PwmModAdsr->blockSignals(true);
	ui->comboBox_Osc2PwmModAdsr->setCurrentIndex(mod_synth_get_active_osc2_pwm_mod_env());
	ui->comboBox_Osc2PwmModAdsr->blockSignals(false);

	ui->dial_Osc2PwmModAdsrLevel->blockSignals(true);
	ui->dial_Osc2PwmModAdsrLevel->setValue(mod_synth_get_active_osc2_pwm_mod_env_level());
	ui->dial_Osc2PwmModAdsrLevel->blockSignals(false);

	ui->comboBox_Osc1AmpModLFO->blockSignals(true);
	ui->comboBox_Osc1AmpModLFO->setCurrentIndex(mod_synth_get_active_osc1_amp_mod_lfo());
	ui->comboBox_Osc1AmpModLFO->blockSignals(false);

	ui->dial_Osc2AmpModLFOLevel->blockSignals(true);
	ui->dial_Osc2AmpModLFOLevel->setValue(mod_synth_get_active_osc2_amp_mod_lfo_level());
	ui->dial_Osc2AmpModLFOLevel->blockSignals(false);

	ui->comboBox_Osc2AmpModAdsr->blockSignals(true);
	ui->comboBox_Osc2AmpModAdsr->setCurrentIndex(mod_synth_get_active_osc2_amp_mod_env());
	ui->comboBox_Osc2AmpModAdsr->blockSignals(false);

	ui->dial_Osc2AmpModAdsrLevel->blockSignals(true);
	ui->dial_Osc2AmpModAdsrLevel->setValue(mod_synth_get_active_osc2_amp_mod_env_level());
	ui->dial_Osc2AmpModAdsrLevel->blockSignals(false);

	
	
	osc2_enabled = mod_synth_get_active_osc2_enable_state();  
	ui->checkBox_Osc2Active->blockSignals(true);		
	ui->checkBox_Osc2Active->setChecked(osc2_enabled);
	ui->checkBox_Osc2Active->blockSignals(false);
	
	if (osc2_enabled)
	{
		ui->frame_Osc2AmpMod->setEnabled(true);
		ui->frame_Osc2FreqMod->setEnabled(true);
		ui->frame_Osc2PwmMod->setEnabled(true);
		ui->checkBox_Osc2SyncOnOsc1->setEnabled(true);
		ui->frame_Osc2TuneOffset->setEnabled(true);
		ui->frame_Osc2Waveform->setEnabled(true);
	}
	else
	{
		ui->frame_Osc2AmpMod->setEnabled(false);
		ui->frame_Osc2FreqMod->setEnabled(false);
		ui->frame_Osc2PwmMod->setEnabled(false);
		ui->checkBox_Osc2SyncOnOsc1->setEnabled(false);
		ui->frame_Osc2TuneOffset->setEnabled(false);
		ui->frame_Osc2Waveform->setEnabled(false);
	}
}



void Dialog_AnalogSynth::on_osc2_enable_changed(bool en)
{
	ui->checkBox_Osc2Active->blockSignals(true);
	if (en)
	{
		ui->checkBox_Osc2Active->setCheckState(Qt::Checked);
	}
	else
	{
		ui->checkBox_Osc2Active->setCheckState(Qt::Unchecked);
	}
	ui->checkBox_Osc2Active->blockSignals(false);
	
	osc2_enabled = en;
	
	mod_synth_vco_event_bool(_OSC_2_EVENT, _OSC_ENABLE, en);
	
	osc2_update();
	
	/* Set focus back on the Dialog */
	this->setFocus(Qt::ActiveWindowFocusReason);
}

void Dialog_AnalogSynth::on_osc2_sync_on_osc1_enable_changed(bool en)
{
	ui->checkBox_Osc2SyncOnOsc1->blockSignals(true);
	if (en)
	{
		ui->checkBox_Osc2SyncOnOsc1->setCheckState(Qt::Checked);
	}
	else
	{
		ui->checkBox_Osc2SyncOnOsc1->setCheckState(Qt::Unchecked);
	}
	ui->checkBox_Osc2SyncOnOsc1->blockSignals(false);
	
	osc_2_sync_on_osc_1 = en;
	
	mod_synth_vco_event_bool(_OSC_2_EVENT, _OSC_SYNC, en);
	
	osc2_update();
	
	/* Set focus back on the Dialog */
	this->setFocus(Qt::ActiveWindowFocusReason);
}

void Dialog_AnalogSynth::on_osc2_waveform_symetry_spinbox_changed(int val)
{
	on_osc2_waveform_symetry_slider_cahanged(val);
}

void Dialog_AnalogSynth::on_osc2_send_filter_1_spinbox_changed(int val)
{
	on_osc2_send_filter_1_dial_changed(val);
}

void Dialog_AnalogSynth::on_osc2_send_filter_2_spinbox_changed(int val)
{
	on_osc2_send_filter_2_dial_changed(val);
}

void Dialog_AnalogSynth::on_osc2_freq_mod_lfo_level_spinbox_changed(int val)
{
	on_osc2_freq_mod_lfo_level_dial_changed(val);
}

void Dialog_AnalogSynth::on_osc2_freq_mod_adsr_level_spinbox_changed(int val)
{
	on_osc2_freq_mod_adsr_level_dial_changed(val);
}

void Dialog_AnalogSynth::on_osc2_pwm_mod_lfo_level_spinbox_changed(int val)
{
	on_osc2_pwm_mod_lfo_level_dial_changed(val);
}

void Dialog_AnalogSynth::on_osc2_pwm_mod_adsr_level_spinbox_changed(int val)
{
	on_osc2_pwm_mod_adsr_level_dial_changed(val);
}

void Dialog_AnalogSynth::on_osc2_amp_mod_lfo_level_spinbox_changed(int val)
{
	on_osc2_amp_mod_lfo_level_dial_changed(val);
}

void Dialog_AnalogSynth::on_osc2_amp_mod_adsr_level_spinbox_changed(int val)
{
	on_osc2_amp_mod_adsr_level_dial_changed(val);
}

void Dialog_AnalogSynth::on_osc2_waveform_symetry_slider_cahanged(int val)
{
	if ((val < _OSC_WAVEFORM_SYMETRY_MIN) || (val > _OSC_WAVEFORM_SYMETRY_MAX))
	{
		return; 
	}
	
	ui->horizontalSlider_Osc2Symetry->blockSignals(true);
	ui->horizontalSlider_Osc2Symetry->setValue(val);
	ui->horizontalSlider_Osc2Symetry->blockSignals(false);
	
	ui->spinBox_Osc2Symetry->blockSignals(true);
	ui->spinBox_Osc2Symetry->setValue(val);
	ui->spinBox_Osc2Symetry->blockSignals(false);
	
	osc2_waveform_symetry = val;
	
	mod_synth_vco_event_int(_OSC_2_EVENT, _OSC_PWM_SYMMETRY, val);
	
	/* Set focus back on the Dialog */
	this->setFocus(Qt::ActiveWindowFocusReason);
}

void Dialog_AnalogSynth::on_osc2_send_filter_1_dial_changed(int val)
{
	ui->dial_Osc2SendFilter1->blockSignals(true);
	ui->dial_Osc2SendFilter1->setValue(val);
	ui->dial_Osc2SendFilter1->blockSignals(false);
	
	ui->spinBox_Osc2SendFilter1->blockSignals(true);
	ui->spinBox_Osc2SendFilter1->setValue(val);
	ui->spinBox_Osc2SendFilter1->blockSignals(false);
	
	osc2_send_filter_1_level = val;
	mod_synth_vco_event_int(_OSC_2_EVENT, _OSC_FILTER_SEND_1, val);
	
	/* Set focus back on the Dialog */
	this->setFocus(Qt::ActiveWindowFocusReason);
}

void Dialog_AnalogSynth::on_osc2_send_filter_2_dial_changed(int val)
{
	ui->dial_Osc2SendFilter2->blockSignals(true);
	ui->dial_Osc2SendFilter2->setValue(val);
	ui->dial_Osc2SendFilter2->blockSignals(false);
	
	ui->spinBox_Osc2SendFilter2->blockSignals(true);
	ui->spinBox_Osc2SendFilter2->setValue(val);
	ui->spinBox_Osc2SendFilter2->blockSignals(false);
	
	osc2_send_filter_2_level = val;
	mod_synth_vco_event_int(_OSC_2_EVENT, _OSC_FILTER_SEND_2, val);
	
	/* Set focus back on the Dialog */
	this->setFocus(Qt::ActiveWindowFocusReason);
}

void Dialog_AnalogSynth::on_osc2_freq_mod_lfo_level_dial_changed(int val)
{
	// int log_val = mod_synth_log_scale_100_int(0, 100, 10, val);
	
	ui->dial_Osc2FreqModLFOLevel->blockSignals(true);
	ui->dial_Osc2FreqModLFOLevel->setValue(val);
	ui->dial_Osc2FreqModLFOLevel->blockSignals(false);
	
	ui->spinBox_Osc2FreqModLfoLevel->blockSignals(true);
	ui->spinBox_Osc2FreqModLfoLevel->setValue(val);
	ui->spinBox_Osc2FreqModLfoLevel->blockSignals(false);
	
	osc2_freq_mod_lfo_level = val;
	mod_synth_vco_event_int(_OSC_2_EVENT, _OSC_FREQ_MOD_LFO_LEVEL, val);
	
	/* Set focus back on the Dialog */
	this->setFocus(Qt::ActiveWindowFocusReason);
}

void Dialog_AnalogSynth::on_osc2_freq_mod_adsr_level_dial_changed(int val)
{
	ui->dial_Osc2FreqModAdsrLevel->blockSignals(true);
	ui->dial_Osc2FreqModAdsrLevel->setValue(val);
	ui->dial_Osc2FreqModAdsrLevel->blockSignals(false);
	
	ui->spinBox_Osc2FreqModAdsrLevel->blockSignals(true);
	ui->spinBox_Osc2FreqModAdsrLevel->setValue(val);
	ui->spinBox_Osc2FreqModAdsrLevel->blockSignals(false);
	
	osc2_freq_mod_adsr_level = val;
	mod_synth_vco_event_int(_OSC_2_EVENT, _OSC_FREQ_MOD_ENV_LEVEL, val);
	
	/* Set focus back on the Dialog */
	this->setFocus(Qt::ActiveWindowFocusReason);
}

void Dialog_AnalogSynth::on_osc2_pwm_mod_lfo_level_dial_changed(int val)
{
	ui->dial_Osc2PwmModLFOLevel->blockSignals(true);
	ui->dial_Osc2PwmModLFOLevel->setValue(val);
	ui->dial_Osc2PwmModLFOLevel->blockSignals(false);
	
	ui->spinBox_Osc2PwmModLfoLevel->blockSignals(true);
	ui->spinBox_Osc2PwmModLfoLevel->setValue(val);
	ui->spinBox_Osc2PwmModLfoLevel->blockSignals(false);
	
	osc2_pwm_mod_lfo_level = val;
	mod_synth_vco_event_int(_OSC_2_EVENT, _OSC_PWM_MOD_LFO_LEVEL, val);
	
	/* Set focus back on the Dialog */
	this->setFocus(Qt::ActiveWindowFocusReason);
}

void Dialog_AnalogSynth::on_osc2_pwm_mod_adsr_level_dial_changed(int val)
{
	ui->dial_Osc2PwmModAdsrLevel->blockSignals(true);
	ui->dial_Osc2PwmModAdsrLevel->setValue(val);
	ui->dial_Osc2PwmModAdsrLevel->blockSignals(false);
	
	ui->spinBox_Osc2PwmModAdsrLevel->blockSignals(true);
	ui->spinBox_Osc2PwmModAdsrLevel->setValue(val);
	ui->spinBox_Osc2PwmModAdsrLevel->blockSignals(false);
	
	osc2_pwm_mod_adsr_level = val;
	mod_synth_vco_event_int(_OSC_2_EVENT, _OSC_PWM_MOD_ENV_LEVEL, val);
	
	/* Set focus back on the Dialog */
	this->setFocus(Qt::ActiveWindowFocusReason);
}

void Dialog_AnalogSynth::on_osc2_amp_mod_lfo_level_dial_changed(int val)
{
	ui->dial_Osc2AmpModLFOLevel->blockSignals(true);
	ui->dial_Osc2AmpModLFOLevel->setValue(val);
	ui->dial_Osc2AmpModLFOLevel->blockSignals(false);
	
	ui->spinBox_Osc2AmpModLfoLevel->blockSignals(true);
	ui->spinBox_Osc2AmpModLfoLevel->setValue(val);
	ui->spinBox_Osc2AmpModLfoLevel->blockSignals(false);
	
	osc2_amp_mod_lfo_level = val;
	mod_synth_vco_event_int(_OSC_2_EVENT, _OSC_AMP_MOD_LFO_LEVEL, val);
	
	/* Set focus back on the Dialog */
	this->setFocus(Qt::ActiveWindowFocusReason);
}

void Dialog_AnalogSynth::on_osc2_amp_mod_adsr_level_dial_changed(int val)
{
	ui->dial_Osc2AmpModAdsrLevel->blockSignals(true);
	ui->dial_Osc2AmpModAdsrLevel->setValue(val);
	ui->dial_Osc2AmpModAdsrLevel->blockSignals(false);
	
	ui->spinBox_Osc2AmpModAdsrLevel->blockSignals(true);
	ui->spinBox_Osc2AmpModAdsrLevel->setValue(val);
	ui->spinBox_Osc2AmpModAdsrLevel->blockSignals(false);
	
	osc2_amp_mod_adsr_level = val;
	mod_synth_vco_event_int(_OSC_2_EVENT, _OSC_AMP_MOD_ENV_LEVEL, val);
	
	/* Set focus back on the Dialog */
	this->setFocus(Qt::ActiveWindowFocusReason);
}


void Dialog_AnalogSynth::on_osc2_waveform_combobox_changed(int val)
{
	ui->comboBox_Osc2Waveform->blockSignals(true);
	ui->comboBox_Osc2Waveform->setCurrentIndex(val);
	ui->comboBox_Osc2Waveform->blockSignals(false);
	
	osc2_waveform = val;
	mod_synth_vco_event_int(_OSC_2_EVENT, _OSC_PARAM_WAVEFORM, val);
	
	/* Set focus back on the Dialog */
	this->setFocus(Qt::ActiveWindowFocusReason);
}

void Dialog_AnalogSynth::on_osc2_tune_octave_combobox_changed(int val)
{
	ui->comboBox_Osc2TuneOctave->blockSignals(true);
	ui->comboBox_Osc2TuneOctave->setCurrentIndex(val);
	ui->comboBox_Osc2TuneOctave->blockSignals(false);
	
	osc2_tune_octave = val;
	mod_synth_vco_event_int(_OSC_2_EVENT, _OSC_DETUNE_OCTAVE, val);
	
	/* Set focus back on the Dialog */
	this->setFocus(Qt::ActiveWindowFocusReason);
}

void Dialog_AnalogSynth::on_osc2_tune_semitones_combobox_changed(int val)
{
	ui->comboBox_Osc2TuneSemitones->blockSignals(true);
	ui->comboBox_Osc2TuneSemitones->setCurrentIndex(val);
	ui->comboBox_Osc2TuneSemitones->blockSignals(false);
	
	osc2_tune_cents = val;
	mod_synth_vco_event_int(_OSC_2_EVENT, _OSC_DETUNE_SEMITONES, val);
	
	/* Set focus back on the Dialog */
	this->setFocus(Qt::ActiveWindowFocusReason);
}

void Dialog_AnalogSynth::on_osc2_tune_cents_combobox_changed(int val)
{
	ui->comboBox_Osc2TuneCents->blockSignals(true);
	ui->comboBox_Osc2TuneCents->setCurrentIndex(val);
	ui->comboBox_Osc2TuneCents->blockSignals(false);
	
	osc2_tune_cents = val;
	mod_synth_vco_event_int(_OSC_2_EVENT, _OSC_DETUNE_CENTS, val);
	
	/* Set focus back on the Dialog */
	this->setFocus(Qt::ActiveWindowFocusReason);
}

void Dialog_AnalogSynth::on_osc2_freq_mod_lfo_combobox_changed(int val)
{
	ui->comboBox_Osc2FreqModLFO->blockSignals(true);
	ui->comboBox_Osc2FreqModLFO->setCurrentIndex(val);
	ui->comboBox_Osc2FreqModLFO->blockSignals(false);
	
	osc2_freq_mod_lfo_num = val;
	mod_synth_vco_event_int(_OSC_2_EVENT, _OSC_FREQ_MOD_LFO, val);
	
	/* Set focus back on the Dialog */
	this->setFocus(Qt::ActiveWindowFocusReason);
}

void Dialog_AnalogSynth::on_osc2_freq_mod_adsr_combobox_changed(int val)
{
	ui->comboBox_Osc2FreqModAdsr->blockSignals(true);
	ui->comboBox_Osc2FreqModAdsr->setCurrentIndex(val);
	ui->comboBox_Osc2FreqModAdsr->blockSignals(false);
	
	osc2_freq_mod_adsr_num = val;
	mod_synth_vco_event_int(_OSC_2_EVENT, _OSC_FREQ_MOD_ENV, val);
	
	/* Set focus back on the Dialog */
	this->setFocus(Qt::ActiveWindowFocusReason);
}

void Dialog_AnalogSynth::on_osc2_pwm_mod_lfo_combobox_changed(int val)
{
	ui->comboBox_Osc2PwmModLFO->blockSignals(true);
	ui->comboBox_Osc2PwmModLFO->setCurrentIndex(val);
	ui->comboBox_Osc2PwmModLFO->blockSignals(false);
	
	osc2_pwm_mod_lfo_num = val;
	mod_synth_vco_event_int(_OSC_2_EVENT, _OSC_PWM_MOD_LFO, val);
	
	/* Set focus back on the Dialog */
	this->setFocus(Qt::ActiveWindowFocusReason);
}

void Dialog_AnalogSynth::on_osc2_pwm_mod_adsr_combobox_changed(int val)
{
	ui->comboBox_Osc2PwmModAdsr->blockSignals(true);
	ui->comboBox_Osc2PwmModAdsr->setCurrentIndex(val);
	ui->comboBox_Osc2PwmModAdsr->blockSignals(false);
	
	osc2_pwm_mod_adsr_num = val;
	mod_synth_vco_event_int(_OSC_1_EVENT, _OSC_PWM_MOD_ENV, val);
	
	/* Set focus back on the Dialog */
	this->setFocus(Qt::ActiveWindowFocusReason);
}

void Dialog_AnalogSynth::on_osc2_amp_mod_lfo_combobox_changed(int val)
{
	ui->comboBox_Osc2AmpModLFO->blockSignals(true);
	ui->comboBox_Osc2AmpModLFO->setCurrentIndex(val);
	ui->comboBox_Osc2AmpModLFO->blockSignals(false);
	
	osc2_amp_mod_lfo_num = val;
	mod_synth_vco_event_int(_OSC_2_EVENT, _OSC_AMP_MOD_LFO, val);
	
	/* Set focus back on the Dialog */
	this->setFocus(Qt::ActiveWindowFocusReason);
}

void Dialog_AnalogSynth::on_osc2_amp_mod_adsr_combobox_changed(int val)
{
	ui->comboBox_Osc2AmpModAdsr->blockSignals(true);
	ui->comboBox_Osc2AmpModAdsr->setCurrentIndex(val);
	ui->comboBox_Osc2AmpModAdsr->blockSignals(false);
	
	osc2_amp_mod_adsr_num = val;
	mod_synth_vco_event_int(_OSC_2_EVENT, _OSC_AMP_MOD_ENV, val);
	
	/* Set focus back on the Dialog */
	this->setFocus(Qt::ActiveWindowFocusReason);
}



void Dialog_AnalogSynth::set_noise_signals_connections()
{
	connect(ui->spinBox_NoiseSendFilter1,
		SIGNAL(valueChanged(int)),
		this,
		SLOT(on_noise_send_filter_1_spinbox_changed(int)));
	
	connect(ui->spinBox_NoiseSendFilter2,
		SIGNAL(valueChanged(int)),
		this,
		SLOT(on_noise_send_filter_2_spinbox_changed(int)));
	
	connect(ui->dial_NoiseSendFilter1,
		SIGNAL(valueChanged(int)),
		this,
		SLOT(on_noise_send_filter_1_dial_changed(int)));
	
	connect(ui->dial_NoiseSendFilter2,
		SIGNAL(valueChanged(int)),
		this,
		SLOT(on_noise_send_filter_2_dial_changed(int)));
	
	connect(ui->spinBox_NoiseAmpModLfoLevel,
		SIGNAL(valueChanged(int)),
		this,
		SLOT(on_noise_amp_mod_lfo_level_spinbox_changed(int)));
	
	connect(ui->spinBox_NoiseAmpModAdsrLevel,
		SIGNAL(valueChanged(int)),
		this,
		SLOT(on_noise_amp_mod_adsr_level_spinbox_changed(int)));
	
	connect(ui->dial_NoiseAmpModLFOLevel,
		SIGNAL(valueChanged(int)),
		this,
		SLOT(on_noise_amp_mod_lfo_level_dial_changed(int)));
	
	connect(ui->dial_NoiseAmpModAdsrLevel,
		SIGNAL(valueChanged(int)),
		this,
		SLOT(on_noise_amp_mod_adsr_level_dial_changed(int)));
	
	connect(ui->comboBox_NoiseAmpModAdsr,
		SIGNAL(currentIndexChanged(int)),
		this,
		SLOT(on_noise_amp_mod_adsr_combobox_changed(int)));
	
	connect(ui->comboBox_NoiseAmpModLFO,
		SIGNAL(currentIndexChanged(int)),
		this,
		SLOT(on_noise_amp_mod_lfo_combobox_changed(int)));
	
	connect(ui->comboBox_NoiseColor,
		SIGNAL(currentIndexChanged(int)),
		this,
		SLOT(on_noise_color_combobox_changed(int)));
	
	connect(ui->checkBox_NoiseActive,
		SIGNAL(toggled(bool)),
		this,
		SLOT(on_noise_enable_changed(bool)));
}

void Dialog_AnalogSynth::init_noise_combboxes_and_labels()
{
	string_noise_colors_list.append("White");
	string_noise_colors_list.append("Pink");
	string_noise_colors_list.append("Brown");
	
	ui->comboBox_NoiseColor->blockSignals(true);
	ui->comboBox_NoiseColor->addItems(string_noise_colors_list);
	ui->comboBox_NoiseColor->blockSignals(false);

	ui->comboBox_NoiseAmpModAdsr->blockSignals(true);
	ui->comboBox_NoiseAmpModAdsr->addItems(string_adsr_values);
	ui->comboBox_NoiseAmpModAdsr->blockSignals(false);

	ui->comboBox_NoiseAmpModLFO->blockSignals(true);
	ui->comboBox_NoiseAmpModLFO->addItems(string_lfo_values);
	ui->comboBox_NoiseAmpModLFO->blockSignals(false);
}

void Dialog_AnalogSynth::noise_update()
{
	ui->comboBox_NoiseColor->blockSignals(true);
	ui->comboBox_NoiseColor->setCurrentIndex(mod_synth_get_active_noise_color());
	ui->comboBox_NoiseColor->blockSignals(false);

	ui->dial_NoiseSendFilter1->blockSignals(true);
	ui->dial_NoiseSendFilter1->setValue(mod_synth_get_active_noise_send_filter_1());
	ui->dial_NoiseSendFilter1->blockSignals(false);

	ui->dial_NoiseSendFilter2->blockSignals(true);
	ui->dial_NoiseSendFilter2->setValue(mod_synth_get_active_noise_send_filter_2());
	ui->dial_NoiseSendFilter2->blockSignals(false);

	ui->comboBox_NoiseAmpModLFO->blockSignals(true);
	ui->comboBox_NoiseAmpModLFO->setCurrentIndex(mod_synth_get_active_noise_amp_mod_lfo());
	ui->comboBox_NoiseAmpModLFO->blockSignals(false);

	ui->dial_NoiseAmpModLFOLevel->blockSignals(true);
	ui->dial_NoiseAmpModLFOLevel->setValue(mod_synth_get_active_noise_amp_mod_lfo_level());
	ui->dial_NoiseAmpModLFOLevel->blockSignals(false);

	ui->comboBox_NoiseAmpModAdsr->blockSignals(true);
	ui->comboBox_NoiseAmpModAdsr->setCurrentIndex(mod_synth_get_active_noise_amp_mod_env());
	ui->comboBox_NoiseAmpModAdsr->blockSignals(false);

	ui->dial_NoiseAmpModAdsrLevel->blockSignals(true);
	ui->dial_NoiseAmpModAdsrLevel->setValue(mod_synth_get_active_noise_amp_mod_env_level());
	ui->dial_NoiseAmpModAdsrLevel->blockSignals(false);

	noise_enabled = mod_synth_get_active_noise_enable_state();
	ui->checkBox_NoiseActive->blockSignals(true);
	ui->checkBox_NoiseActive->setChecked(noise_enabled);
	ui->checkBox_NoiseActive->blockSignals(false);
	
	if (noise_enabled)
	{
		ui->frame_NoiseAmpMod->setEnabled(true);
		ui->frame_NoiseColor->setEnabled(true);
	}
	else
	{
		ui->frame_NoiseAmpMod->setEnabled(false);
		ui->frame_NoiseColor->setEnabled(false);
	}
}

void Dialog_AnalogSynth::on_noise_enable_changed(bool en)
{
	ui->checkBox_NoiseActive->blockSignals(true);
	if (en)
	{
		ui->checkBox_NoiseActive->setCheckState(Qt::Checked);
	}
	else
	{
		ui->checkBox_NoiseActive->setCheckState(Qt::Unchecked);
	}
	ui->checkBox_NoiseActive->blockSignals(false);
	
	noise_enabled = en;
	
	mod_synth_noise_event_bool(_NOISE_1_EVENT, _NOISE_ENABLE, en);
	
	noise_update();
	
	/* Set focus back on the Dialog */
	this->setFocus(Qt::ActiveWindowFocusReason);
}

void Dialog_AnalogSynth::on_noise_send_filter_1_spinbox_changed(int val)
{
	on_noise_send_filter_1_dial_changed(val);
}

void Dialog_AnalogSynth::on_noise_send_filter_2_spinbox_changed(int val)
{
	on_noise_send_filter_2_dial_changed(val);
}

void Dialog_AnalogSynth::on_noise_amp_mod_lfo_level_spinbox_changed(int val)
{
	on_noise_amp_mod_lfo_level_dial_changed(val);
}

void Dialog_AnalogSynth::on_noise_amp_mod_adsr_level_spinbox_changed(int val)
{
	on_noise_amp_mod_adsr_level_dial_changed(val);
}

void Dialog_AnalogSynth::on_noise_send_filter_1_dial_changed(int val)
{
	ui->dial_NoiseSendFilter1->blockSignals(true);
	ui->dial_NoiseSendFilter1->setValue(val);
	ui->dial_NoiseSendFilter1->blockSignals(false);
	
	ui->spinBox_NoiseSendFilter1->blockSignals(true);
	ui->spinBox_NoiseSendFilter1->setValue(val);
	ui->spinBox_NoiseSendFilter1->blockSignals(false);
	
	noise_send_filter_1_level = val;
	mod_synth_vco_event_int(_NOISE_1_EVENT, _NOISE_SEND_1, val);
	
	/* Set focus back on the Dialog */
	this->setFocus(Qt::ActiveWindowFocusReason);
}

void Dialog_AnalogSynth::on_noise_send_filter_2_dial_changed(int val)
{
	ui->dial_NoiseSendFilter2->blockSignals(true);
	ui->dial_NoiseSendFilter2->setValue(val);
	ui->dial_NoiseSendFilter2->blockSignals(false);
	
	ui->spinBox_NoiseSendFilter2->blockSignals(true);
	ui->spinBox_NoiseSendFilter2->setValue(val);
	ui->spinBox_NoiseSendFilter2->blockSignals(false);
	
	noise_send_filter_2_level = val;
	mod_synth_vco_event_int(_NOISE_1_EVENT, _NOISE_SEND_2, val);
	
	/* Set focus back on the Dialog */
	this->setFocus(Qt::ActiveWindowFocusReason);
}

void Dialog_AnalogSynth::on_noise_amp_mod_lfo_level_dial_changed(int val)
{
	ui->dial_NoiseAmpModLFOLevel->blockSignals(true);
	ui->dial_NoiseAmpModLFOLevel->setValue(val);
	ui->dial_NoiseAmpModLFOLevel->blockSignals(false);
	
	ui->spinBox_NoiseAmpModLfoLevel->blockSignals(true);
	ui->spinBox_NoiseAmpModLfoLevel->setValue(val);
	ui->spinBox_NoiseAmpModLfoLevel->blockSignals(false);
	
	noise_amp_mod_lfo_level = val;
	mod_synth_vco_event_int(_NOISE_1_EVENT, _NOISE_AMP_MOD_LFO_LEVEL, val);
	
	/* Set focus back on the Dialog */
	this->setFocus(Qt::ActiveWindowFocusReason);
}

void Dialog_AnalogSynth::on_noise_amp_mod_adsr_level_dial_changed(int val)
{
	ui->dial_NoiseAmpModAdsrLevel->blockSignals(true);
	ui->dial_NoiseAmpModAdsrLevel->setValue(val);
	ui->dial_NoiseAmpModAdsrLevel->blockSignals(false);
	
	ui->spinBox_NoiseAmpModAdsrLevel->blockSignals(true);
	ui->spinBox_NoiseAmpModAdsrLevel->setValue(val);
	ui->spinBox_NoiseAmpModAdsrLevel->blockSignals(false);
	
	noise_amp_mod_adsr_level = val;
	mod_synth_vco_event_int(_NOISE_1_EVENT, _NOISE_AMP_MOD_ENV_LEVEL, val);
	
	/* Set focus back on the Dialog */
	this->setFocus(Qt::ActiveWindowFocusReason);
}

void Dialog_AnalogSynth::on_noise_color_combobox_changed(int val)
{
	ui->comboBox_NoiseColor->blockSignals(true);
	ui->comboBox_NoiseColor->setCurrentIndex(val);
	ui->comboBox_NoiseColor->blockSignals(false);
	
	noise_color = val;
	mod_synth_vco_event_int(_NOISE_1_EVENT, _NOISE_COLOR, val);
	
	/* Set focus back on the Dialog */
	this->setFocus(Qt::ActiveWindowFocusReason);
}

void Dialog_AnalogSynth::on_noise_amp_mod_lfo_combobox_changed(int val)
{
	ui->comboBox_NoiseAmpModLFO->blockSignals(true);
	ui->comboBox_NoiseAmpModLFO->setCurrentIndex(val);
	ui->comboBox_NoiseAmpModLFO->blockSignals(false);
	
	noise_amp_mod_lfo_num = val;
	mod_synth_vco_event_int(_NOISE_1_EVENT, _NOISE_AMP_MOD_LFO, val);
	
	/* Set focus back on the Dialog */
	this->setFocus(Qt::ActiveWindowFocusReason);
}

void Dialog_AnalogSynth::on_noise_amp_mod_adsr_combobox_changed(int val)
{
	ui->comboBox_NoiseAmpModAdsr->blockSignals(true);
	ui->comboBox_NoiseAmpModAdsr->setCurrentIndex(val);
	ui->comboBox_NoiseAmpModAdsr->blockSignals(false);
	
	noise_amp_mod_adsr_num = val;
	mod_synth_vco_event_int(_NOISE_1_EVENT, _NOISE_AMP_MOD_ENV, val);
	
	/* Set focus back on the Dialog */
	this->setFocus(Qt::ActiveWindowFocusReason);
}



