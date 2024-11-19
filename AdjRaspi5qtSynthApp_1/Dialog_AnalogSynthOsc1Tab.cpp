/**
* @file		Dialog_AnalogSynthOsc1Tab.h
*	@author		Nahum Budin
*	@date		25-Oct-2024
*	@version	1.0
*
*	@brief		Analog Synthesizer instrument Osc1 Tab handling
*				
*	History:
*			Based on the AdjModSynth project ver 1.1 16-Jan-2021 
*
*/

#include "Dialog_AnalogSynth.h"
#include "ui_Dialog_AnalogSynth.h"
#include "utils.h"

#include "libAdjRaspi5SynthAPI.h"

void osc1_unison_mode_selected_wrapper(int mod)
{ 
	Dialog_AnalogSynth::get_instance()->osc1_set_unison_mode(mod);
}

void Dialog_AnalogSynth::set_osc1_signals_connections()
{
	connect(ui->horizontalSlider_Osc1Symetry,
		SIGNAL(valueChanged(int)),
		this,
		SLOT(on_osc1_waveform_symetry_slider_cahanged(int)));
	
	
	connect(ui->verticalSlider_Osc1UnisonLevel_1,
		SIGNAL(valueChanged(int)),
		this,
		SLOT(on_osc1_unison_level_1_slider_changed(int)));
	
	connect(ui->verticalSlider_Osc1UnisonLevel_2,
		SIGNAL(valueChanged(int)),
		this,
		SLOT(on_osc1_unison_level_2_slider_changed(int)));
	
	connect(ui->verticalSlider_Osc1UnisonLevel_3,
		SIGNAL(valueChanged(int)),
		this,
		SLOT(on_osc1_unison_level_3_slider_changed(int)));
	
	connect(ui->verticalSlider_Osc1UnisonLevel_4,
		SIGNAL(valueChanged(int)),
		this,
		SLOT(on_osc1_unison_level_4_slider_changed(int)));
	
	connect(ui->verticalSlider_Osc1UnisonLevel_5,
		SIGNAL(valueChanged(int)),
		this,
		SLOT(on_osc1_unison_level_5_slider_changed(int)));
	
	connect(ui->verticalSlider_Osc1UnisonLevel_6,
		SIGNAL(valueChanged(int)),
		this,
		SLOT(on_osc1_unison_level_6_slider_changed(int)));
	
	connect(ui->verticalSlider_Osc1UnisonLevel_7,
		SIGNAL(valueChanged(int)),
		this,
		SLOT(on_osc1_unison_level_7_slider_changed(int)));
	
	connect(ui->verticalSlider_Osc1UnisonLevel_8,
		SIGNAL(valueChanged(int)),
		this,
		SLOT(on_osc1_unison_level_8_slider_changed(int)));
	
	connect(ui->verticalSlider_Osc1UnisonLevel_9,
		SIGNAL(valueChanged(int)),
		this,
		SLOT(on_osc1_unison_level_9_slider_changed(int)));
	
	connect(ui->verticalSlider_Osc1HarmonyDistortLevel,
		SIGNAL(valueChanged(int)),
		this,
		SLOT(on_osc1_unison_distortion_slider_changed(int)));
	
	connect(ui->verticalSlider_Osc1HarmonyDetuneLevel,
		SIGNAL(valueChanged(int)),
		this,
		SLOT(on_osc1_unison_detune_slider_changed(int)));
	
	connect(ui->spinBox_Osc1Symetry,
		SIGNAL(valueChanged(int)),
		this,
		SLOT(on_osc1_waveform_symetry_spinbox_changed(int)));
	
	connect(ui->spinBox_Osc1SendFilter1,
		SIGNAL(valueChanged(int)),
		this,
		SLOT(on_osc1_send_filter_1_spinbox_changed(int)));
	
	connect(ui->spinBox_Osc1SendFilter2,
		SIGNAL(valueChanged(int)),
		this,
		SLOT(on_osc1_send_filter_2_spinbox_changed(int)));
	
	connect(ui->spinBox_Osc1FreqModLfoLevel,
		SIGNAL(valueChanged(int)),
		this,
		SLOT(on_osc1_freq_mod_lfo_level_spinbox_changed(int)));
	
	connect(ui->spinBox_Osc1FreqModAdsrLevel,
		SIGNAL(valueChanged(int)),
		this,
		SLOT(on_osc1_freq_mod_adsr_level_spinbox_changed(int)));
	
	connect(ui->spinBox_Osc1PwmModLfoLevel,
		SIGNAL(valueChanged(int)),
		this,
		SLOT(on_osc1_pwm_mod_lfo_level_spinbox_changed(int)));
	
	connect(ui->spinBox_Osc1PwmModAdsrLevel,
		SIGNAL(valueChanged(int)),
		this,
		SLOT(on_osc1_freq_mod_adsr_level_spinbox_changed(int)));
	
	connect(ui->spinBox_Osc1AmpModLfoLevel,
		SIGNAL(valueChanged(int)),
		this,
		SLOT(on_osc1_amp_mod_lfo_level_spinbox_changed(int)));
	
	connect(ui->spinBox_Osc1AmpModAdsrLevel,
		SIGNAL(valueChanged(int)),
		this,
		SLOT(on_osc1_amp_mod_adsr_level_spinbox_changed(int)));
	
	connect(ui->spinBox_Osc1UnisonLevel_1,
		SIGNAL(valueChanged(int)),
		this,
		SLOT(on_osc1_unison_level_1_spinbox_changed(int)));
	
	connect(ui->spinBox_Osc1UnisonLevel_2,
		SIGNAL(valueChanged(int)),
		this,
		SLOT(on_osc1_unison_level_2_spinbox_changed(int)));
	
	connect(ui->spinBox_Osc1UnisonLevel_3,
		SIGNAL(valueChanged(int)),
		this,
		SLOT(on_osc1_unison_level_3_spinbox_changed(int)));
	
	connect(ui->spinBox_Osc1UnisonLevel_4,
		SIGNAL(valueChanged(int)),
		this,
		SLOT(on_osc1_unison_level_4_spinbox_changed(int)));
	
	connect(ui->spinBox_Osc1UnisonLevel_5,
		SIGNAL(valueChanged(int)),
		this,
		SLOT(on_osc1_unison_level_5_spinbox_changed(int)));
	
	connect(ui->spinBox_Osc1UnisonLevel_6,
		SIGNAL(valueChanged(int)),
		this,
		SLOT(on_osc1_unison_level_6_spinbox_changed(int)));
	
	connect(ui->spinBox_Osc1UnisonLevel_7,
		SIGNAL(valueChanged(int)),
		this,
		SLOT(on_osc1_unison_level_7_spinbox_changed(int)));
	
	connect(ui->spinBox_Osc1UnisonLevel_8,
		SIGNAL(valueChanged(int)),
		this,
		SLOT(on_osc1_unison_level_8_spinbox_changed(int)));
	
	connect(ui->spinBox_Osc1UnisonLevel_9,
		SIGNAL(valueChanged(int)),
		this,
		SLOT(on_osc1_unison_level_9_spinbox_changed(int)));
	
	connect(ui->spinBox_Osc1HarmonyDistort,
		SIGNAL(valueChanged(int)),
		this,
		SLOT(on_osc1_unison_distortion_spinbox_changed(int)));
	
	connect(ui->spinBox_Osc1HarmonyDetune,
		SIGNAL(valueChanged(int)),
		this,
		SLOT(on_osc1_unison_detune_spinbox_changed(int)));
	
	connect(ui->dial_Osc1SendFilter1,
		SIGNAL(valueChanged(int)),
		this,
		SLOT(on_osc1_send_filter_1_dial_changed(int)));
	
	connect(ui->dial_Osc1SendFilter2,
		SIGNAL(valueChanged(int)),
		this,
		SLOT(on_osc1_send_filter_2_dial_changed(int)));
	
	connect(ui->dial_Osc1FreqModLFOLevel,
		SIGNAL(valueChanged(int)),
		this,
		SLOT(on_osc1_freq_mod_lfo_level_dial_changed(int)));
	
	connect(ui->dial_Osc1FreqModAdsrLevel,
		SIGNAL(valueChanged(int)),
		this,
		SLOT(on_osc1_freq_mod_adsr_level_dial_changed(int)));
	
	connect(ui->dial_Osc1PwmModLFOLevel,
		SIGNAL(valueChanged(int)),
		this,
		SLOT(on_osc1_pwm_mod_lfo_level_dial_changed(int)));
	
	connect(ui->dial_Osc1PwmModAdsrLevel,
		SIGNAL(valueChanged(int)),
		this,
		SLOT(on_osc1_pwm_mod_adsr_level_dial_changed(int)));
	
	connect(ui->dial_Osc1AmpModLFOLevel,
		SIGNAL(valueChanged(int)),
		this,
		SLOT(on_osc1_amp_mod_lfo_level_dial_changed(int)));
	
	connect(ui->dial_Osc1AmpModAdsrLevel,
		SIGNAL(valueChanged(int)),
		this,
		SLOT(on_osc1_amp_mod_adsr_level_dial_changed(int)));
	
	connect(ui->comboBox_Osc1AmpModAdsr,
		SIGNAL(currentIndexChanged(int)),
		this,
		SLOT(on_osc1_amp_mod_adsr_combobox_changed(int)));
	
	connect(ui->comboBox_Osc1AmpModLFO,
		SIGNAL(currentIndexChanged(int)),
		this,
		SLOT(on_osc1_amp_mod_lfo_combobox_changed(int)));
	
	connect(ui->comboBox_Osc1FreqModAdsr,
		SIGNAL(currentIndexChanged(int)),
		this,
		SLOT(on_osc1_freq_mod_adsr_combobox_changed(int)));
	
	connect(ui->comboBox_Osc1FreqModLFO,
		SIGNAL(currentIndexChanged(int)),
		this,
		SLOT(on_osc1_freq_mod_lfo_combobox_changed(int)));
	
	connect(ui->comboBox_Osc1PwmModAdsr,
		SIGNAL(currentIndexChanged(int)),
		this,
		SLOT(on_osc1_pwm_mod_adsr_combobox_changed(int)));
	
	connect(ui->comboBox_Osc1PwmModLFO,
		SIGNAL(currentIndexChanged(int)),
		this,
		SLOT(on_osc1_pwm_mod_lfo_combobox_changed(int)));
	
	connect(ui->comboBox_Osc1TuneCents,
		SIGNAL(currentIndexChanged(int)),
		this,
		SLOT(on_osc1_tune_cents_combobox_changed(int)));
	
	connect(ui->comboBox_Osc1TuneOctave,
		SIGNAL(currentIndexChanged(int)),
		this,
		SLOT(on_osc1_tune_octave_combobox_changed(int)));
	
	connect(ui->comboBox_Osc1TuneSemitones,
		SIGNAL(currentIndexChanged(int)),
		this,
		SLOT(on_osc1_tune_semitones_combobox_changed(int)));
	
	connect(ui->comboBox_Osc1Waveform,
		SIGNAL(currentIndexChanged(int)),
		this,
		SLOT(on_osc1_waveform_combobox_changed(int)));
	
	connect(ui->comboBox_Osc1UnisonMode,
		SIGNAL(currentIndexChanged(int)),
		this,
		SLOT(on_osc1_unison_mode_combobox_changed(int)));
	
	connect(ui->comboBox_Osc1HammondPercussionMode,
		SIGNAL(currentIndexChanged(int)),
		this,
		SLOT(on_osc1_hammond_percussion_mode_combobox_changed(int)));
	
	connect(ui->checkBox_Osc1Active,
		SIGNAL(toggled(bool)),
		this,
		SLOT(on_osc1_enable_changed(bool)));

	connect(ui->checkBox_Osc1UnisonSquareWave,
		SIGNAL(toggled(bool)),
		this,
		SLOT(on_osc1_unison_sqare_enable_changed(bool)));
}

void Dialog_AnalogSynth::init_osc1_combboxes_and_labels()
{		
	if (string_waveforms_list.size() == 0)
	{
		/* Do only once for Osc1 and 2*/
		string_waveforms_list.append("Sine");
		string_waveforms_list.append("Square");
		string_waveforms_list.append("Pulse");
		string_waveforms_list.append("Triangle");
		string_waveforms_list.append("Sample & Hold");
	}
	
	ui->comboBox_Osc1Waveform->blockSignals(true);
	ui->comboBox_Osc1Waveform->addItems(string_waveforms_list);
	ui->comboBox_Osc1Waveform->blockSignals(false);

	string_unison_modes_list.append("Harmonized");
	string_unison_modes_list.append("Hammond");
	string_unison_modes_list.append("Octaves");
	string_unison_modes_list.append("C Chord");
	string_unison_modes_list.append("Cm Chord");
	string_unison_modes_list.append("C7 Chord");
	string_unison_modes_list.append("Cm7 Chord");
					   
	ui->comboBox_Osc1UnisonMode->blockSignals(true);
	ui->comboBox_Osc1UnisonMode->addItems(string_unison_modes_list);
	ui->comboBox_Osc1UnisonMode->blockSignals(false);
	
	if (string_adsr_values.size() == 0)
	{
		/* Do only once for Osc1 and Osc2 */
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
	
	ui->comboBox_Osc1FreqModAdsr->blockSignals(true);
	ui->comboBox_Osc1FreqModAdsr->addItems(string_adsr_values);
	ui->comboBox_Osc1FreqModAdsr->blockSignals(false);

	ui->comboBox_Osc1FreqModLFO->blockSignals(true);
	ui->comboBox_Osc1FreqModLFO->addItems(string_lfo_values);
	ui->comboBox_Osc1FreqModLFO->blockSignals(false);

	ui->comboBox_Osc1PwmModAdsr->blockSignals(true);
	ui->comboBox_Osc1PwmModAdsr->addItems(string_adsr_values);
	ui->comboBox_Osc1PwmModAdsr->blockSignals(false);

	ui->comboBox_Osc1PwmModLFO->blockSignals(true);
	ui->comboBox_Osc1PwmModLFO->addItems(string_lfo_values);
	ui->comboBox_Osc1PwmModLFO->blockSignals(false);

	ui->comboBox_Osc1AmpModAdsr->blockSignals(true);
	ui->comboBox_Osc1AmpModAdsr->addItems(string_adsr_values);
	ui->comboBox_Osc1AmpModAdsr->blockSignals(false);

	ui->comboBox_Osc1AmpModLFO->blockSignals(true);
	ui->comboBox_Osc1AmpModLFO->addItems(string_lfo_values);
	ui->comboBox_Osc1AmpModLFO->blockSignals(false);
	
	string_hammond_modes_list.append("Percusion OFF");
	string_hammond_modes_list.append("Percusion 2nd Soft Slow");
	string_hammond_modes_list.append("Percusion 2nd Soft Fast");
	string_hammond_modes_list.append("Percusion 2nd Norm Slow");
	string_hammond_modes_list.append("Percusion 2nd Norm Fast");
	string_hammond_modes_list.append("Percusion 3rd Soft Slow");
	string_hammond_modes_list.append("Percusion 3rd Soft Fast");
	string_hammond_modes_list.append("Percusion 3rd Norm Slow");
	string_hammond_modes_list.append("Percusion 3rd Norm Fast");
	
	ui->comboBox_Osc1HammondPercussionMode->blockSignals(true);
	ui->comboBox_Osc1HammondPercussionMode->addItems(string_hammond_modes_list);
	ui->comboBox_Osc1HammondPercussionMode->setVisible(false);
	ui->comboBox_Osc1HammondPercussionMode->blockSignals(false);
	
	ui->label_Osc1HammondPercussionMode->setVisible(false);
	
	ui->comboBox_Osc1TuneOctave->blockSignals(true);
	ui->comboBox_Osc1TuneSemitones->blockSignals(true);
	ui->comboBox_Osc1TuneCents->blockSignals(true);
	
	for (int i = _OSC_DETUNE_MIN_OCTAVE; i <= _OSC_DETUNE_MAX_OCTAVE; i++)
	{
		ui->comboBox_Osc1TuneOctave->addItem(QString::number(i));
	}

	for (int i = _OSC_DETUNE_MIN_SEMITONES; i <= _OSC_DETUNE_MAX_SEMITONES; i++)
	{
		ui->comboBox_Osc1TuneSemitones->addItem(QString::number(i));
	}

	for (int i = 4 * _OSC_DETUNE_MIN_CENTS; i <= 4 * _OSC_DETUNE_MAX_CENTS; i++)
	{
		// 0.25 steps
		ui->comboBox_Osc1TuneCents->addItem(QString::number(i / 4.f));
	}

	ui->comboBox_Osc1TuneOctave->blockSignals(false);
	ui->comboBox_Osc1TuneSemitones->blockSignals(false);
	ui->comboBox_Osc1TuneCents->blockSignals(false);
	
	// TODO Set current active selected values in UI update
	

	string_unison_labels_harmonized.append("1");
	string_unison_labels_harmonized.append("2");
	string_unison_labels_harmonized.append("3");
	string_unison_labels_harmonized.append("4");
	string_unison_labels_harmonized.append("5");
	string_unison_labels_harmonized.append("6");
	string_unison_labels_harmonized.append("7");
	string_unison_labels_harmonized.append("8  ");

	string_unison_labels_hammond.append("16");
	string_unison_labels_hammond.append("5 1/3");
	string_unison_labels_hammond.append("8");
	string_unison_labels_hammond.append("4");
	string_unison_labels_hammond.append("2 2/3");
	string_unison_labels_hammond.append("2");
	string_unison_labels_hammond.append("1 3/5");
	string_unison_labels_hammond.append("1 1/3");
	string_unison_labels_hammond.append("1");	

	string_unison_labels_octaves.append("1");
	string_unison_labels_octaves.append("2");
	string_unison_labels_octaves.append("4");
	string_unison_labels_octaves.append("8  ");

	string_unison_labels_c_chord.append("I");
	string_unison_labels_c_chord.append("III");
	string_unison_labels_c_chord.append("V");

	string_unison_labels_cm_chord.append("i");
	string_unison_labels_cm_chord.append("iii");
	string_unison_labels_cm_chord.append("v");

	string_unison_labels_c7_chord.append("I");
	string_unison_labels_c7_chord.append("III");
	string_unison_labels_c7_chord.append("V");
	string_unison_labels_c7_chord.append("VII");

	string_unison_labels_cm7_chord.append("i");
	string_unison_labels_cm7_chord.append("iii");
	string_unison_labels_cm7_chord.append("v");
	string_unison_labels_cm7_chord.append("vii");
	
	mod_synth_register_set_osc_1_unison_mode_callback(
		&osc1_unison_mode_selected_wrapper);
}

void Dialog_AnalogSynth::osc1_set_unison_mode(int mode)
{
	int i;

	osc1_set_unison_labales(mode);
	
	if (mode != _OSC_UNISON_MODE_HAMMOND)
	{
		for (i = 0; i < mod_synth_get_osc1_num_of_drawbars(); i++)
		{
			unison_level_sliders[i]->blockSignals(true);
			unison_level_sliders[i]->setSingleStep(1);
			unison_level_sliders[i]->setMaximum(100);
			unison_level_sliders[i]->setMinimum(0);
			unison_level_sliders[i]->setInvertedAppearance(false);
			unison_level_sliders[i]->blockSignals(false);
		}

		ui->comboBox_Osc1HammondPercussionMode->blockSignals(true);
		ui->comboBox_Osc1HammondPercussionMode->setVisible(false);
		ui->comboBox_Osc1HammondPercussionMode->blockSignals(false);

		ui->checkBox_Osc1UnisonSquareWave->blockSignals(true);
		ui->checkBox_Osc1UnisonSquareWave->setVisible(true);
		ui->checkBox_Osc1UnisonSquareWave->blockSignals(false);
		
		ui->label_Osc1HammondPercussionMode->setVisible(false);

	}
	else if (mode == _OSC_UNISON_MODE_HAMMOND)
	{
		for (i = 0; i < mod_synth_get_osc1_num_of_drawbars(); i++)
		{
			unison_level_sliders[i]->blockSignals(true);
			unison_level_sliders[i]->setSingleStep(12);
			unison_level_sliders[i]->setMaximum(96);
			unison_level_sliders[i]->setMinimum(0);
			unison_level_sliders[i]->setInvertedAppearance(true);
			unison_level_sliders[i]->blockSignals(false);
		}

		ui->comboBox_Osc1HammondPercussionMode->blockSignals(true);
		ui->comboBox_Osc1HammondPercussionMode->setVisible(true);
		ui->comboBox_Osc1HammondPercussionMode->blockSignals(false);

		ui->checkBox_Osc1UnisonSquareWave->blockSignals(true);
		ui->checkBox_Osc1UnisonSquareWave->setVisible(false);
		ui->checkBox_Osc1UnisonSquareWave->blockSignals(false);
		
		ui->checkBox_Osc1UnisonSquareWave->blockSignals(true);
		ui->checkBox_Osc1UnisonSquareWave->setChecked(false);
		ui->checkBox_Osc1UnisonSquareWave->blockSignals(false);
		
		ui->label_Osc1HammondPercussionMode->setVisible(true);
	}
}


void Dialog_AnalogSynth::osc1_set_unison_labales(QList<QString> str, uint16_t mask)
{
	int i = 0;

	if (mask & 0x01)
	{
		ui->label_Osc1HarmonyLevel_1->setText(str.at(i++));
	}
	else
	{
		ui->label_Osc1HarmonyLevel_1->setText(" ");
	}

	if (mask & 0x02)
	{
		ui->label_Osc1HarmonyLevel_2->setText(str.at(i++));
	}
	else
	{
		ui->label_Osc1HarmonyLevel_2->setText(" ");
	}

	if (mask & 0x04)
	{
		ui->label_Osc1HarmonyLevel_3->setText(str.at(i++));
	}
	else
	{
		ui->label_Osc1HarmonyLevel_3->setText(" ");
	}

	if (mask & 0x08)
	{
		ui->label_Osc1HarmonyLevel_4->setText(str.at(i++));
	}
	else
	{
		ui->label_Osc1HarmonyLevel_4->setText(" ");
	}

	if (mask & 0x10)
	{
		ui->label_Osc1HarmonyLevel_5->setText(str.at(i++));
	}
	else
	{
		ui->label_Osc1HarmonyLevel_5->setText(" ");
	}

	if (mask & 0x20)
	{
		ui->label_Osc1HarmonyLevel_6->setText(str.at(i++));
	}
	else
	{
		ui->label_Osc1HarmonyLevel_6->setText(" ");
	}

	if (mask & 0x40)
	{
		ui->label_Osc1HarmonyLevel_7->setText(str.at(i++));
	}
	else
	{
		ui->label_Osc1HarmonyLevel_7->setText(" ");
	}

	if (mask & 0x80)
	{
		ui->label_Osc1HarmonyLevel_8->setText(str.at(i++));
	}
	else
	{
		ui->label_Osc1HarmonyLevel_8->setText(" ");
	}

	if (mask & 0x100)
	{
		ui->label_Osc1HarmonyLevel_9->setText(str.at(i++));
	}
	else
	{
		ui->label_Osc1HarmonyLevel_9->setText(" ");
	}
}

void Dialog_AnalogSynth::osc1_set_unison_labales(int mode)
{
	switch (mode)
	{
	case _OSC_UNISON_MODE_12345678:
		osc1_en_dis_sliders(0xff);
		osc1_set_unison_labales(string_unison_labels_harmonized, 0xff);
		break;

	case _OSC_UNISON_MODE_HAMMOND:
		osc1_en_dis_sliders(0x1ff);
		osc1_set_unison_labales(string_unison_labels_hammond, 0x1ff);
		break;

	case _OSC_UNISON_MODE_OCTAVES:
		osc1_en_dis_sliders(0x8b);
		osc1_set_unison_labales(string_unison_labels_octaves, 0x8b);
		break;

	case _OSC_UNISON_MODE_C_CHORD:
		osc1_en_dis_sliders(0x07);
		osc1_set_unison_labales(string_unison_labels_c_chord, 0x07);
		break;

	case _OSC_UNISON_MODE_Cm_CHORD:
		osc1_en_dis_sliders(0x07);
		osc1_set_unison_labales(string_unison_labels_cm_chord, 0x07);
		break;

	case _OSC_UNISON_MODE_C7_CHORD:
		osc1_en_dis_sliders(0x0f);
		osc1_set_unison_labales(string_unison_labels_c7_chord, 0x0f);
		break;

	case _OSC_UNISON_MODE_Cm7_CHORD:
		osc1_en_dis_sliders(0x0f);
		osc1_set_unison_labales(string_unison_labels_cm7_chord, 0x0f);
		break;

	default:
		return;
	}
}

void Dialog_AnalogSynth::osc1_en_dis_sliders(uint16_t mask)
{
	if (mask & 0x01)
	{
		ui->verticalSlider_Osc1UnisonLevel_1->setVisible(true);
	}
	else
	{
		ui->verticalSlider_Osc1UnisonLevel_1->setVisible(false);
	}

	if (mask & 0x02)
	{
		ui->verticalSlider_Osc1UnisonLevel_2->setVisible(true);
	}
	else
	{
		ui->verticalSlider_Osc1UnisonLevel_2->setVisible(false);
	}

	if (mask & 0x04)
	{
		ui->verticalSlider_Osc1UnisonLevel_3->setVisible(true);
	}
	else
	{
		ui->verticalSlider_Osc1UnisonLevel_3->setVisible(false);
	}

	if (mask & 0x08)
	{
		ui->verticalSlider_Osc1UnisonLevel_4->setVisible(true);
	}
	else
	{
		ui->verticalSlider_Osc1UnisonLevel_4->setVisible(false);
	}

	if (mask & 0x10)
	{
		ui->verticalSlider_Osc1UnisonLevel_5->setVisible(true);
	}
	else
	{
		ui->verticalSlider_Osc1UnisonLevel_5->setVisible(false);
	}

	if (mask & 0x20)
	{
		ui->verticalSlider_Osc1UnisonLevel_6->setVisible(true);
	}
	else
	{
		ui->verticalSlider_Osc1UnisonLevel_6->setVisible(false);
	}

	if (mask & 0x40)
	{
		ui->verticalSlider_Osc1UnisonLevel_7->setVisible(true);
	}
	else
	{
		ui->verticalSlider_Osc1UnisonLevel_7->setVisible(false);
	}

	if (mask & 0x80)
	{
		ui->verticalSlider_Osc1UnisonLevel_8->setVisible(true);
	}
	else
	{
		ui->verticalSlider_Osc1UnisonLevel_8->setVisible(false);
	}

	if (mask & 0x100)
	{
		ui->verticalSlider_Osc1UnisonLevel_9->setVisible(true);
	}
	else
	{
		ui->verticalSlider_Osc1UnisonLevel_9->setVisible(false);
	}
}

void Dialog_AnalogSynth::osc1_update()
{
	static bool one_time_initialized = false;
	
	if (!one_time_initialized)
	{
		one_time_initialized = true;
		//init_osc1_combboxes_and_labels();
	}
	
	ui->comboBox_Osc1Waveform->blockSignals(true);
	ui->comboBox_Osc1Waveform->setCurrentIndex(mod_synth_get_active_osc1_waveform());
	ui->comboBox_Osc1Waveform->blockSignals(false);

	ui->horizontalSlider_Osc1Symetry->blockSignals(true);
	ui->horizontalSlider_Osc1Symetry->setValue(mod_synth_get_active_osc1_pwm_percents());
	ui->horizontalSlider_Osc1Symetry->blockSignals(false);
	
	ui->spinBox_Osc1Symetry->blockSignals(true);
	ui->spinBox_Osc1Symetry->setValue(mod_synth_get_active_osc1_pwm_percents());
	ui->spinBox_Osc1Symetry->blockSignals(false);

	ui->comboBox_Osc1TuneOctave->blockSignals(true);
	ui->comboBox_Osc1TuneOctave->setCurrentIndex(mod_synth_get_active_osc1_detune_octave() - mod_synth_get_osc_detune_min_octave());
	ui->comboBox_Osc1TuneOctave->blockSignals(false);

	ui->comboBox_Osc1TuneSemitones->blockSignals(true);
	ui->comboBox_Osc1TuneSemitones->setCurrentIndex(mod_synth_get_active_osc1_detune_semitones() - mod_synth_get_osc_detune_min_semitones());
	ui->comboBox_Osc1TuneSemitones->blockSignals(false);

	ui->comboBox_Osc1TuneCents->blockSignals(true);
	ui->comboBox_Osc1TuneCents->setCurrentIndex(mod_synth_get_active_osc1_detune_cents() - mod_synth_get_osc_detune_min_cents() * 4.f);
	ui->comboBox_Osc1TuneCents->blockSignals(false);

	ui->dial_Osc1SendFilter1->blockSignals(true);
	ui->dial_Osc1SendFilter1->setValue(mod_synth_get_active_osc1_send_filter_1());
	ui->dial_Osc1SendFilter1->blockSignals(false);
	
	ui->spinBox_Osc1SendFilter1->blockSignals(true);
	ui->spinBox_Osc1SendFilter1->setValue(mod_synth_get_active_osc1_send_filter_1());
	ui->spinBox_Osc1SendFilter1->blockSignals(false);

	ui->dial_Osc1SendFilter2->blockSignals(true);
	ui->dial_Osc1SendFilter2->setValue(mod_synth_get_active_osc1_send_filter_2());
	ui->dial_Osc1SendFilter2->blockSignals(false);
	
	ui->spinBox_Osc1SendFilter2->blockSignals(true);
	ui->spinBox_Osc1SendFilter2->setValue(mod_synth_get_active_osc1_send_filter_2());
	ui->spinBox_Osc1SendFilter2->blockSignals(false);

	ui->comboBox_Osc1FreqModLFO->blockSignals(true);
	ui->comboBox_Osc1FreqModLFO->setCurrentIndex(mod_synth_get_active_osc1_freq_mod_lfo());
	ui->comboBox_Osc1FreqModLFO->blockSignals(false);

	ui->dial_Osc1FreqModLFOLevel->blockSignals(true);
	ui->dial_Osc1FreqModLFOLevel->setValue(mod_synth_get_active_osc1_freq_mod_lfo_level());
	ui->dial_Osc1FreqModLFOLevel->blockSignals(false);
	
	ui->spinBox_Osc1FreqModLfoLevel->blockSignals(true);
	ui->spinBox_Osc1FreqModLfoLevel->setValue(mod_synth_get_active_osc1_freq_mod_lfo_level());
	ui->spinBox_Osc1FreqModLfoLevel->blockSignals(false);

	ui->comboBox_Osc1FreqModAdsr->blockSignals(true);
	ui->comboBox_Osc1FreqModAdsr->setCurrentIndex(mod_synth_get_active_osc1_freq_mod_env());
	ui->comboBox_Osc1FreqModAdsr->blockSignals(false);

	ui->dial_Osc1FreqModAdsrLevel->blockSignals(true);
	ui->dial_Osc1FreqModAdsrLevel->setValue(mod_synth_get_active_osc1_freq_mod_env_level());
	ui->dial_Osc1FreqModAdsrLevel->blockSignals(false);
	
	ui->spinBox_Osc1FreqModAdsrLevel->blockSignals(true);
	ui->spinBox_Osc1FreqModAdsrLevel->setValue(mod_synth_get_active_osc1_freq_mod_env_level());
	ui->spinBox_Osc1FreqModAdsrLevel->blockSignals(false);

	ui->comboBox_Osc1PwmModLFO->blockSignals(true);
	ui->comboBox_Osc1PwmModLFO->setCurrentIndex(mod_synth_get_active_osc1_pwm_mod_lfo());
	ui->comboBox_Osc1PwmModLFO->blockSignals(false);

	ui->dial_Osc1PwmModLFOLevel->blockSignals(true);
	ui->dial_Osc1PwmModLFOLevel->setValue(mod_synth_get_active_osc1_pwm_mod_lfo_level());
	ui->dial_Osc1PwmModLFOLevel->blockSignals(false);
	
	ui->spinBox_Osc1PwmModLfoLevel->blockSignals(true);
	ui->spinBox_Osc1PwmModLfoLevel->setValue(mod_synth_get_active_osc1_pwm_mod_lfo_level());
	ui->spinBox_Osc1PwmModLfoLevel->blockSignals(false);

	ui->comboBox_Osc1PwmModAdsr->blockSignals(true);
	ui->comboBox_Osc1PwmModAdsr->setCurrentIndex(mod_synth_get_active_osc1_pwm_mod_env());
	ui->comboBox_Osc1PwmModAdsr->blockSignals(false);

	ui->dial_Osc1PwmModAdsrLevel->blockSignals(true);
	ui->dial_Osc1PwmModAdsrLevel->setValue(mod_synth_get_active_osc1_pwm_mod_env_level());
	ui->dial_Osc1PwmModAdsrLevel->blockSignals(false);
	
	ui->spinBox_Osc1PwmModAdsrLevel->blockSignals(true);
	ui->spinBox_Osc1PwmModAdsrLevel->setValue(mod_synth_get_active_osc1_pwm_mod_env_level());
	ui->spinBox_Osc1PwmModAdsrLevel->blockSignals(false);

	ui->comboBox_Osc1AmpModLFO->blockSignals(true);
	ui->comboBox_Osc1AmpModLFO->setCurrentIndex(mod_synth_get_active_osc1_amp_mod_lfo());
	ui->comboBox_Osc1AmpModLFO->blockSignals(false);

	ui->dial_Osc1AmpModLFOLevel->blockSignals(true);
	ui->dial_Osc1AmpModLFOLevel->setValue(mod_synth_get_active_osc1_amp_mod_lfo_level());
	ui->dial_Osc1AmpModLFOLevel->blockSignals(false);
	
	ui->spinBox_Osc1AmpModLfoLevel->blockSignals(true);
	ui->spinBox_Osc1AmpModLfoLevel->setValue(mod_synth_get_active_osc1_amp_mod_lfo_level());
	ui->spinBox_Osc1AmpModLfoLevel->blockSignals(false);

	ui->comboBox_Osc1AmpModAdsr->blockSignals(true);
	ui->comboBox_Osc1AmpModAdsr->setCurrentIndex(mod_synth_get_active_osc1_amp_mod_env());
	ui->comboBox_Osc1AmpModAdsr->blockSignals(false);

	ui->dial_Osc1AmpModAdsrLevel->blockSignals(true);
	ui->dial_Osc1AmpModAdsrLevel->setValue(mod_synth_get_active_osc1_amp_mod_env_level());
	ui->dial_Osc1AmpModAdsrLevel->blockSignals(false);
	
	ui->spinBox_Osc1AmpModAdsrLevel->blockSignals(true);
	ui->spinBox_Osc1AmpModAdsrLevel->setValue(mod_synth_get_active_osc1_amp_mod_env_level());
	ui->spinBox_Osc1AmpModAdsrLevel->blockSignals(false);

	ui->comboBox_Osc1UnisonMode->blockSignals(true);
	ui->comboBox_Osc1UnisonMode->setCurrentIndex(mod_synth_get_active_osc1_unison_mode());
	ui->comboBox_Osc1UnisonMode->blockSignals(false);

	//	osc1unisonModeSelected(getActiveOsc1unisonMode()); <<<<<<<<<<<<<<<<<<

	ui->verticalSlider_Osc1UnisonLevel_1->blockSignals(true);
	ui->verticalSlider_Osc1UnisonLevel_1->setValue(mod_synth_get_active_osc1_harmonies_levels(0));
	ui->verticalSlider_Osc1UnisonLevel_1->blockSignals(false);

	ui->verticalSlider_Osc1UnisonLevel_2->blockSignals(true);
	ui->verticalSlider_Osc1UnisonLevel_2->setValue(mod_synth_get_active_osc1_harmonies_levels(1));
	ui->verticalSlider_Osc1UnisonLevel_2->blockSignals(false);

	ui->verticalSlider_Osc1UnisonLevel_3->blockSignals(true);
	ui->verticalSlider_Osc1UnisonLevel_3->setValue(mod_synth_get_active_osc1_harmonies_levels(2));
	ui->verticalSlider_Osc1UnisonLevel_3->blockSignals(false);

	ui->verticalSlider_Osc1UnisonLevel_4->blockSignals(true);
	ui->verticalSlider_Osc1UnisonLevel_4->setValue(mod_synth_get_active_osc1_harmonies_levels(3));
	ui->verticalSlider_Osc1UnisonLevel_4->blockSignals(false);

	ui->verticalSlider_Osc1UnisonLevel_5->blockSignals(true);
	ui->verticalSlider_Osc1UnisonLevel_5->setValue(mod_synth_get_active_osc1_harmonies_levels(4));
	ui->verticalSlider_Osc1UnisonLevel_5->blockSignals(false);

	ui->verticalSlider_Osc1UnisonLevel_6->blockSignals(true);
	ui->verticalSlider_Osc1UnisonLevel_6->setValue(mod_synth_get_active_osc1_harmonies_levels(5));
	ui->verticalSlider_Osc1UnisonLevel_6->blockSignals(false);

	ui->verticalSlider_Osc1UnisonLevel_7->blockSignals(true);
	ui->verticalSlider_Osc1UnisonLevel_7->setValue(mod_synth_get_active_osc1_harmonies_levels(6));
	ui->verticalSlider_Osc1UnisonLevel_7->blockSignals(false);

	ui->verticalSlider_Osc1UnisonLevel_8->blockSignals(true);
	ui->verticalSlider_Osc1UnisonLevel_8->setValue(mod_synth_get_active_osc1_harmonies_levels(7));
	ui->verticalSlider_Osc1UnisonLevel_8->blockSignals(false);

	ui->verticalSlider_Osc1HarmonyDetuneLevel->blockSignals(true);
	ui->verticalSlider_Osc1HarmonyDetuneLevel->setValue(mod_synth_get_active_osc1_harmonies_detune_factor());
	ui->verticalSlider_Osc1HarmonyDetuneLevel->blockSignals(false);

	ui->verticalSlider_Osc1HarmonyDistortLevel->blockSignals(true);
	ui->verticalSlider_Osc1HarmonyDistortLevel->setValue(mod_synth_get_active_osc1_harmonies_dist_factor());
	ui->verticalSlider_Osc1HarmonyDistortLevel->blockSignals(false);
	
	ui->spinBox_Osc1UnisonLevel_1->blockSignals(true);
	ui->spinBox_Osc1UnisonLevel_1->setValue(mod_synth_get_active_osc1_harmonies_levels(0));
	ui->spinBox_Osc1UnisonLevel_1->blockSignals(false);

	ui->spinBox_Osc1UnisonLevel_2->blockSignals(true);
	ui->spinBox_Osc1UnisonLevel_2->setValue(mod_synth_get_active_osc1_harmonies_levels(1));
	ui->spinBox_Osc1UnisonLevel_2->blockSignals(false);

	ui->spinBox_Osc1UnisonLevel_3->blockSignals(true);
	ui->spinBox_Osc1UnisonLevel_3->setValue(mod_synth_get_active_osc1_harmonies_levels(2));
	ui->spinBox_Osc1UnisonLevel_3->blockSignals(false);

	ui->spinBox_Osc1UnisonLevel_4->blockSignals(true);
	ui->spinBox_Osc1UnisonLevel_4->setValue(mod_synth_get_active_osc1_harmonies_levels(3));
	ui->spinBox_Osc1UnisonLevel_4->blockSignals(false);

	ui->spinBox_Osc1UnisonLevel_5->blockSignals(true);
	ui->spinBox_Osc1UnisonLevel_5->setValue(mod_synth_get_active_osc1_harmonies_levels(4));
	ui->spinBox_Osc1UnisonLevel_5->blockSignals(false);

	ui->spinBox_Osc1UnisonLevel_6->blockSignals(true);
	ui->spinBox_Osc1UnisonLevel_6->setValue(mod_synth_get_active_osc1_harmonies_levels(5));
	ui->spinBox_Osc1UnisonLevel_6->blockSignals(false);

	ui->spinBox_Osc1UnisonLevel_7->blockSignals(true);
	ui->spinBox_Osc1UnisonLevel_7->setValue(mod_synth_get_active_osc1_harmonies_levels(6));
	ui->spinBox_Osc1UnisonLevel_7->blockSignals(false);

	ui->spinBox_Osc1UnisonLevel_8->blockSignals(true);
	ui->spinBox_Osc1UnisonLevel_8->setValue(mod_synth_get_active_osc1_harmonies_levels(7));
	ui->spinBox_Osc1UnisonLevel_8->blockSignals(false);

	ui->spinBox_Osc1HarmonyDetune->blockSignals(true);
	ui->spinBox_Osc1HarmonyDetune->setValue(mod_synth_get_active_osc1_harmonies_detune_factor());
	ui->spinBox_Osc1HarmonyDetune->blockSignals(false);

	ui->spinBox_Osc1HarmonyDistort->blockSignals(true);
	ui->spinBox_Osc1HarmonyDistort->setValue(mod_synth_get_active_osc1_harmonies_dist_factor());
	ui->spinBox_Osc1HarmonyDistort->blockSignals(false);

	if (mod_synth_get_active_osc1_unison_mode() == _OSC_UNISON_MODE_HAMMOND)
	{
		ui->comboBox_Osc1HammondPercussionMode->blockSignals(true);
		ui->comboBox_Osc1HammondPercussionMode->setVisible(true);
		ui->comboBox_Osc1HammondPercussionMode->setCurrentIndex(mod_synth_get_active_osc1_hammond_mode());
		ui->comboBox_Osc1HammondPercussionMode->blockSignals(false);

		ui->checkBox_Osc1UnisonSquareWave->blockSignals(true);
		ui->checkBox_Osc1UnisonSquareWave->setVisible(false);
		ui->checkBox_Osc1UnisonSquareWave->blockSignals(false);
		// Disable square wave
		mod_synth_vco_event_bool(_OSC_1_EVENT, _OSC_1_UNISON_SQUARE, false);
		ui->checkBox_Osc1UnisonSquareWave->blockSignals(true);
		ui->checkBox_Osc1UnisonSquareWave->setChecked(false);
		ui->checkBox_Osc1UnisonSquareWave->blockSignals(false);
	}
	
	osc1_enabled = mod_synth_get_active_osc1_enable_state();  
	ui->checkBox_Osc1Active->blockSignals(true);		
	ui->checkBox_Osc1Active->setChecked(osc1_enabled);
	ui->checkBox_Osc1Active->blockSignals(false);
	
	if (osc1_enabled)
	{
		ui->frame_Osc1AmpMod->setEnabled(true);
		ui->frame_Osc1Drawbars_1_6->setEnabled(true);
		ui->frame_Osc1Drawbars_7_9->setEnabled(true);
		ui->frame_Osc1FreqMod->setEnabled(true);
		ui->frame_Osc1PwmMod->setEnabled(true);
		ui->frame_Osc1TuneOffset->setEnabled(true);
		ui->frame_Osc1Waveform->setEnabled(true);
	}
	else
	{
		ui->frame_Osc1AmpMod->setEnabled(false);
		ui->frame_Osc1Drawbars_1_6->setEnabled(false);
		ui->frame_Osc1Drawbars_7_9->setEnabled(false);
		ui->frame_Osc1FreqMod->setEnabled(false);
		ui->frame_Osc1PwmMod->setEnabled(false);
		ui->frame_Osc1TuneOffset->setEnabled(false);
		ui->frame_Osc1Waveform->setEnabled(false);
	}
}

void Dialog_AnalogSynth::on_osc1_enable_changed(bool en)
{
	ui->checkBox_Osc1Active->blockSignals(true);
	if (en)
	{
		ui->checkBox_Osc1Active->setCheckState(Qt::Checked);
		mod_synth_enable_osc1();
	}
	else
	{
		ui->checkBox_Osc1Active->setCheckState(Qt::Unchecked);
		mod_synth_disable_osc1();
	}
	ui->checkBox_Osc1Active->blockSignals(false);
	
	osc1_enabled = en;
	
	mod_synth_vco_event_bool(_OSC_1_EVENT, _OSC_ENABLE, en);
	
	osc1_update();
	
	/* Set focus back on the Dialog */
	this->setFocus(Qt::ActiveWindowFocusReason);
}



void Dialog_AnalogSynth::on_osc1_waveform_symetry_spinbox_changed(int val)
{
	on_osc1_waveform_symetry_slider_cahanged(val);
}

void Dialog_AnalogSynth::on_osc1_send_filter_1_spinbox_changed(int val)
{
	on_osc1_send_filter_1_dial_changed(val);
}

void Dialog_AnalogSynth::on_osc1_send_filter_2_spinbox_changed(int val)
{
	on_osc1_send_filter_2_dial_changed(val);
}

void Dialog_AnalogSynth::on_osc1_freq_mod_lfo_level_spinbox_changed(int val)
{
	on_osc1_freq_mod_lfo_level_dial_changed(val);
}

void Dialog_AnalogSynth::on_osc1_freq_mod_adsr_level_spinbox_changed(int val)
{
	on_osc1_freq_mod_adsr_level_dial_changed(val);
}

void Dialog_AnalogSynth::on_osc1_pwm_mod_lfo_level_spinbox_changed(int val)
{
	on_osc1_pwm_mod_lfo_level_dial_changed(val);
}

void Dialog_AnalogSynth::on_osc1_pwm_mod_adsr_level_spinbox_changed(int val)
{
	on_osc1_pwm_mod_adsr_level_dial_changed(val);
}

void Dialog_AnalogSynth::on_osc1_amp_mod_lfo_level_spinbox_changed(int val)
{
	on_osc1_amp_mod_lfo_level_dial_changed(val);
}

void Dialog_AnalogSynth::on_osc1_amp_mod_adsr_level_spinbox_changed(int val)
{
	on_osc1_amp_mod_adsr_level_dial_changed(val);
}
	
void Dialog_AnalogSynth::on_osc1_unison_level_1_spinbox_changed(int val)
{
	on_osc1_unison_level_1_slider_changed(val);
}

void Dialog_AnalogSynth::on_osc1_unison_level_2_spinbox_changed(int val)
{
	on_osc1_unison_level_2_slider_changed(val);
}

void Dialog_AnalogSynth::on_osc1_unison_level_3_spinbox_changed(int val)
{
	on_osc1_unison_level_3_slider_changed(val);
}

void Dialog_AnalogSynth::on_osc1_unison_level_4_spinbox_changed(int val)
{
	on_osc1_unison_level_4_slider_changed(val);
}

void Dialog_AnalogSynth::on_osc1_unison_level_5_spinbox_changed(int val)
{
	on_osc1_unison_level_5_slider_changed(val);
}

void Dialog_AnalogSynth::on_osc1_unison_level_6_spinbox_changed(int val)
{
	on_osc1_unison_level_6_slider_changed(val);
}

void Dialog_AnalogSynth::on_osc1_unison_level_7_spinbox_changed(int val)
{
	on_osc1_unison_level_7_slider_changed(val);
}

void Dialog_AnalogSynth::on_osc1_unison_level_8_spinbox_changed(int val)
{
	on_osc1_unison_level_8_slider_changed(val);
}

void Dialog_AnalogSynth::on_osc1_unison_level_9_spinbox_changed(int val)
{
	on_osc1_unison_level_9_slider_changed(val);
}

void Dialog_AnalogSynth::on_osc1_unison_distortion_spinbox_changed(int val)
{
	on_osc1_unison_distortion_slider_changed(val);
}

void Dialog_AnalogSynth::on_osc1_unison_detune_spinbox_changed(int val)
{
	on_osc1_unison_detune_slider_changed(val);
}


void Dialog_AnalogSynth::on_osc1_waveform_symetry_slider_cahanged(int val)
{
	if ((val < _OSC_WAVEFORM_SYMETRY_MIN) || (val > _OSC_WAVEFORM_SYMETRY_MAX))
	{
		return; 
	}
	
	ui->horizontalSlider_Osc1Symetry->blockSignals(true);
	ui->horizontalSlider_Osc1Symetry->setValue(val);
	ui->horizontalSlider_Osc1Symetry->blockSignals(false);
	
	ui->spinBox_Osc1Symetry->blockSignals(true);
	ui->spinBox_Osc1Symetry->setValue(val);
	ui->spinBox_Osc1Symetry->blockSignals(false);
	
	osc1_waveform_symetry = val;
	
	mod_synth_vco_event_int(_OSC_1_EVENT, _OSC_PWM_SYMMETRY, val);
	
	/* Set focus back on the Dialog */
	this->setFocus(Qt::ActiveWindowFocusReason);
}
	
void Dialog_AnalogSynth::on_osc1_unison_sqare_enable_changed(bool en)
{
	ui->checkBox_Osc1UnisonSquareWave->blockSignals(true);
	if (en)
	{
		ui->checkBox_Osc1UnisonSquareWave->setCheckState(Qt::Checked);
	}
	else
	{
		ui->checkBox_Osc1UnisonSquareWave->setCheckState(Qt::Unchecked);
	}
	ui->checkBox_Osc1UnisonSquareWave->blockSignals(false);
	
	osc1_unison_square = en;
	
	mod_synth_vco_event_bool(_OSC_1_EVENT, _OSC_1_UNISON_SQUARE, en);
	
	/* Set focus back on the Dialog */
	this->setFocus(Qt::ActiveWindowFocusReason);
}

void Dialog_AnalogSynth::on_osc1_unison_level_1_slider_changed(int val)
{
	if ((val < _OSC1_UNISON_LEVEL_MIN) || (val > _OSC1_UNISON_LEVEL_MAX))
	{
		return; 
	}
	
	if (mod_synth_get_active_osc1_unison_mode() != _OSC_UNISON_MODE_HAMMOND)
	{
		ui->verticalSlider_Osc1UnisonLevel_1->blockSignals(true);
		ui->verticalSlider_Osc1UnisonLevel_1->setValue(val);
		ui->verticalSlider_Osc1UnisonLevel_1->blockSignals(false);
		
		ui->spinBox_Osc1UnisonLevel_1->blockSignals(true);
		ui->spinBox_Osc1UnisonLevel_1->setValue(val);
		ui->spinBox_Osc1UnisonLevel_1->blockSignals(false);
		
		osc1_unison_levels[0] = val;
		
		mod_synth_vco_event_int(_OSC_1_EVENT, _OSC_UNISON_LEVEL_1, val);
	}
	else if (mod_synth_get_active_osc1_unison_mode() == _OSC_UNISON_MODE_HAMMOND)
	{
		// Hmmond registers: 0-8
		int reg = val / 12; // 0-96 -> "0-8"
		
		ui->verticalSlider_Osc1UnisonLevel_1->blockSignals(true);
		ui->verticalSlider_Osc1UnisonLevel_1->setValue(reg * 12);
		ui->verticalSlider_Osc1UnisonLevel_1->blockSignals(false);
		
		ui->spinBox_Osc1UnisonLevel_1->blockSignals(true);
		ui->spinBox_Osc1UnisonLevel_1->setValue(reg);
		ui->spinBox_Osc1UnisonLevel_1->blockSignals(false);
		
		osc1_unison_levels[0] = reg * 12;
		
		mod_synth_vco_event_int(_OSC_1_EVENT, _OSC_UNISON_LEVEL_1, reg * 12);
	}
	
	/* Set focus back on the Dialog */
	this->setFocus(Qt::ActiveWindowFocusReason);
}

void Dialog_AnalogSynth::on_osc1_unison_level_2_slider_changed(int val)
{
	if ((val < _OSC1_UNISON_LEVEL_MIN) || (val > _OSC1_UNISON_LEVEL_MAX))
	{
		return; 
	}
	
	if (mod_synth_get_active_osc1_unison_mode() != _OSC_UNISON_MODE_HAMMOND)
	{
		ui->verticalSlider_Osc1UnisonLevel_2->blockSignals(true);
		ui->verticalSlider_Osc1UnisonLevel_2->setValue(val);
		ui->verticalSlider_Osc1UnisonLevel_2->blockSignals(false);
		
		ui->spinBox_Osc1UnisonLevel_2->blockSignals(true);
		ui->spinBox_Osc1UnisonLevel_2->setValue(val);
		ui->spinBox_Osc1UnisonLevel_2->blockSignals(false);
		
		osc1_unison_levels[1] = val;
		
		mod_synth_vco_event_int(_OSC_1_EVENT, _OSC_UNISON_LEVEL_2, val);
	}
	else if (mod_synth_get_active_osc1_unison_mode() == _OSC_UNISON_MODE_HAMMOND)
	{
		// Hmmond registers: 0-8
		int reg = val / 12; // 0-96 -> "0-8"
		
		ui->verticalSlider_Osc1UnisonLevel_2->blockSignals(true);
		ui->verticalSlider_Osc1UnisonLevel_2->setValue(reg * 12);
		ui->verticalSlider_Osc1UnisonLevel_2->blockSignals(false);
		
		ui->spinBox_Osc1UnisonLevel_2->blockSignals(true);
		ui->spinBox_Osc1UnisonLevel_2->setValue(reg);
		ui->spinBox_Osc1UnisonLevel_2->blockSignals(false);
		
		osc1_unison_levels[1] = reg * 12;
		
		mod_synth_vco_event_int(_OSC_1_EVENT, _OSC_UNISON_LEVEL_2, reg * 12);
	}
	
	/* Set focus back on the Dialog */
	this->setFocus(Qt::ActiveWindowFocusReason);
}

void Dialog_AnalogSynth::on_osc1_unison_level_3_slider_changed(int val)
{
	if ((val < _OSC1_UNISON_LEVEL_MIN) || (val > _OSC1_UNISON_LEVEL_MAX))
	{
		return; 
	}
	
	if (mod_synth_get_active_osc1_unison_mode() != _OSC_UNISON_MODE_HAMMOND)
	{
		ui->verticalSlider_Osc1UnisonLevel_3->blockSignals(true);
		ui->verticalSlider_Osc1UnisonLevel_3->setValue(val);
		ui->verticalSlider_Osc1UnisonLevel_3->blockSignals(false);
		
		ui->spinBox_Osc1UnisonLevel_3->blockSignals(true);
		ui->spinBox_Osc1UnisonLevel_3->setValue(val);
		ui->spinBox_Osc1UnisonLevel_3->blockSignals(false);
		
		osc1_unison_levels[2] = val;
		
		mod_synth_vco_event_int(_OSC_1_EVENT, _OSC_UNISON_LEVEL_3, val);
	}
	else if (mod_synth_get_active_osc1_unison_mode() == _OSC_UNISON_MODE_HAMMOND)
	{
		// Hmmond registers: 0-8
		int reg = val / 12; // 0-96 -> "0-8"
		
		ui->verticalSlider_Osc1UnisonLevel_3->blockSignals(true);
		ui->verticalSlider_Osc1UnisonLevel_3->setValue(reg * 12);
		ui->verticalSlider_Osc1UnisonLevel_3->blockSignals(false);
		
		ui->spinBox_Osc1UnisonLevel_3->blockSignals(true);
		ui->spinBox_Osc1UnisonLevel_3->setValue(reg);
		ui->spinBox_Osc1UnisonLevel_3->blockSignals(false);
		
		osc1_unison_levels[2] = reg * 12;
		
		mod_synth_vco_event_int(_OSC_1_EVENT, _OSC_UNISON_LEVEL_3, reg * 12);
	}
	
	/* Set focus back on the Dialog */
	this->setFocus(Qt::ActiveWindowFocusReason);
}

void Dialog_AnalogSynth::on_osc1_unison_level_4_slider_changed(int val)
{
	if ((val < _OSC1_UNISON_LEVEL_MIN) || (val > _OSC1_UNISON_LEVEL_MAX))
	{
		return; 
	}
	
	if (mod_synth_get_active_osc1_unison_mode() != _OSC_UNISON_MODE_HAMMOND)
	{
		ui->verticalSlider_Osc1UnisonLevel_4->blockSignals(true);
		ui->verticalSlider_Osc1UnisonLevel_4->setValue(val);
		ui->verticalSlider_Osc1UnisonLevel_4->blockSignals(false);
		
		ui->spinBox_Osc1UnisonLevel_4->blockSignals(true);
		ui->spinBox_Osc1UnisonLevel_4->setValue(val);
		ui->spinBox_Osc1UnisonLevel_4->blockSignals(false);
		
		osc1_unison_levels[3] = val;
		
		mod_synth_vco_event_int(_OSC_1_EVENT, _OSC_UNISON_LEVEL_4, val);
	}
	else if (mod_synth_get_active_osc1_unison_mode() == _OSC_UNISON_MODE_HAMMOND)
	{
		// Hmmond registers: 0-8
		int reg = val / 12; // 0-96 -> "0-8"
		
		ui->verticalSlider_Osc1UnisonLevel_4->blockSignals(true);
		ui->verticalSlider_Osc1UnisonLevel_4->setValue(reg * 12);
		ui->verticalSlider_Osc1UnisonLevel_4->blockSignals(false);
		
		ui->spinBox_Osc1UnisonLevel_4->blockSignals(true);
		ui->spinBox_Osc1UnisonLevel_4->setValue(reg);
		ui->spinBox_Osc1UnisonLevel_4->blockSignals(false);
		
		osc1_unison_levels[3] = reg * 12;
		
		mod_synth_vco_event_int(_OSC_1_EVENT, _OSC_UNISON_LEVEL_4, reg * 12);
	}
	
	/* Set focus back on the Dialog */
	this->setFocus(Qt::ActiveWindowFocusReason);
}

void Dialog_AnalogSynth::on_osc1_unison_level_5_slider_changed(int val)
{
	if ((val < _OSC1_UNISON_LEVEL_MIN) || (val > _OSC1_UNISON_LEVEL_MAX))
	{
		return; 
	}
	
	if (mod_synth_get_active_osc1_unison_mode() != _OSC_UNISON_MODE_HAMMOND)
	{
		ui->verticalSlider_Osc1UnisonLevel_5->blockSignals(true);
		ui->verticalSlider_Osc1UnisonLevel_5->setValue(val);
		ui->verticalSlider_Osc1UnisonLevel_5->blockSignals(false);
		
		ui->spinBox_Osc1UnisonLevel_5->blockSignals(true);
		ui->spinBox_Osc1UnisonLevel_5->setValue(val);
		ui->spinBox_Osc1UnisonLevel_5->blockSignals(false);
		
		osc1_unison_levels[4] = val;
		
		mod_synth_vco_event_int(_OSC_1_EVENT, _OSC_UNISON_LEVEL_5, val);
	}
	else if (mod_synth_get_active_osc1_unison_mode() == _OSC_UNISON_MODE_HAMMOND)
	{
		// Hmmond registers: 0-8
		int reg = val / 12; // 0-96 -> "0-8"
		
		ui->verticalSlider_Osc1UnisonLevel_5->blockSignals(true);
		ui->verticalSlider_Osc1UnisonLevel_5->setValue(reg * 12);
		ui->verticalSlider_Osc1UnisonLevel_5->blockSignals(false);
		
		ui->spinBox_Osc1UnisonLevel_5->blockSignals(true);
		ui->spinBox_Osc1UnisonLevel_5->setValue(reg);
		ui->spinBox_Osc1UnisonLevel_5->blockSignals(false);
		
		osc1_unison_levels[4] = reg * 12;
		
		mod_synth_vco_event_int(_OSC_1_EVENT, _OSC_UNISON_LEVEL_5, reg * 12);
	}
	
	/* Set focus back on the Dialog */
	this->setFocus(Qt::ActiveWindowFocusReason);
}

void Dialog_AnalogSynth::on_osc1_unison_level_6_slider_changed(int val)
{
	if ((val < _OSC1_UNISON_LEVEL_MIN) || (val > _OSC1_UNISON_LEVEL_MAX))
	{
		return; 
	}
	
	if (mod_synth_get_active_osc1_unison_mode() != _OSC_UNISON_MODE_HAMMOND)
	{
		ui->verticalSlider_Osc1UnisonLevel_6->blockSignals(true);
		ui->verticalSlider_Osc1UnisonLevel_6->setValue(val);
		ui->verticalSlider_Osc1UnisonLevel_6->blockSignals(false);
		
		ui->spinBox_Osc1UnisonLevel_6->blockSignals(true);
		ui->spinBox_Osc1UnisonLevel_6->setValue(val);
		ui->spinBox_Osc1UnisonLevel_6->blockSignals(false);
		
		osc1_unison_levels[5] = val;
		
		mod_synth_vco_event_int(_OSC_1_EVENT, _OSC_UNISON_LEVEL_6, val);
	}
	else if (mod_synth_get_active_osc1_unison_mode() == _OSC_UNISON_MODE_HAMMOND)
	{
		// Hmmond registers: 0-8
		int reg = val / 12; // 0-96 -> "0-8"
		
		ui->verticalSlider_Osc1UnisonLevel_6->blockSignals(true);
		ui->verticalSlider_Osc1UnisonLevel_6->setValue(reg * 12);
		ui->verticalSlider_Osc1UnisonLevel_6->blockSignals(false);
		
		ui->spinBox_Osc1UnisonLevel_6->blockSignals(true);
		ui->spinBox_Osc1UnisonLevel_6->setValue(reg);
		ui->spinBox_Osc1UnisonLevel_6->blockSignals(false);
		
		osc1_unison_levels[5] = reg * 12;
		
		mod_synth_vco_event_int(_OSC_1_EVENT, _OSC_UNISON_LEVEL_6, reg * 12);
	}
	
	/* Set focus back on the Dialog */
	this->setFocus(Qt::ActiveWindowFocusReason);
}

void Dialog_AnalogSynth::on_osc1_unison_level_7_slider_changed(int val)
{
	if ((val < _OSC1_UNISON_LEVEL_MIN) || (val > _OSC1_UNISON_LEVEL_MAX))
	{
		return; 
	}
	
	if (mod_synth_get_active_osc1_unison_mode() != _OSC_UNISON_MODE_HAMMOND)
	{
		ui->verticalSlider_Osc1UnisonLevel_7->blockSignals(true);
		ui->verticalSlider_Osc1UnisonLevel_7->setValue(val);
		ui->verticalSlider_Osc1UnisonLevel_7->blockSignals(false);
		
		ui->spinBox_Osc1UnisonLevel_7->blockSignals(true);
		ui->spinBox_Osc1UnisonLevel_7->setValue(val);
		ui->spinBox_Osc1UnisonLevel_7->blockSignals(false);
		
		osc1_unison_levels[6] = val;
		
		mod_synth_vco_event_int(_OSC_1_EVENT, _OSC_UNISON_LEVEL_7, val);
	}
	else if (mod_synth_get_active_osc1_unison_mode() == _OSC_UNISON_MODE_HAMMOND)
	{
		// Hmmond registers: 0-8
		int reg = val / 12; // 0-96 -> "0-8"
		
		ui->verticalSlider_Osc1UnisonLevel_7->blockSignals(true);
		ui->verticalSlider_Osc1UnisonLevel_7->setValue(reg * 12);
		ui->verticalSlider_Osc1UnisonLevel_7->blockSignals(false);
		
		ui->spinBox_Osc1UnisonLevel_7->blockSignals(true);
		ui->spinBox_Osc1UnisonLevel_7->setValue(reg);
		ui->spinBox_Osc1UnisonLevel_7->blockSignals(false);
		
		osc1_unison_levels[6] = reg * 12;
		
		mod_synth_vco_event_int(_OSC_1_EVENT, _OSC_UNISON_LEVEL_7, reg * 12);
	}
	
	/* Set focus back on the Dialog */
	this->setFocus(Qt::ActiveWindowFocusReason);
}

void Dialog_AnalogSynth::on_osc1_unison_level_8_slider_changed(int val)
{
	if ((val < _OSC1_UNISON_LEVEL_MIN) || (val > _OSC1_UNISON_LEVEL_MAX))
	{
		return; 
	}
	
	if (mod_synth_get_active_osc1_unison_mode() != _OSC_UNISON_MODE_HAMMOND)
	{
		ui->verticalSlider_Osc1UnisonLevel_8->blockSignals(true);
		ui->verticalSlider_Osc1UnisonLevel_8->setValue(val);
		ui->verticalSlider_Osc1UnisonLevel_8->blockSignals(false);
		
		ui->spinBox_Osc1UnisonLevel_8->blockSignals(true);
		ui->spinBox_Osc1UnisonLevel_8->setValue(val);
		ui->spinBox_Osc1UnisonLevel_8->blockSignals(false);
		
		osc1_unison_levels[7] = val;
		
		mod_synth_vco_event_int(_OSC_1_EVENT, _OSC_UNISON_LEVEL_8, val);
	}
	else if (mod_synth_get_active_osc1_unison_mode() == _OSC_UNISON_MODE_HAMMOND)
	{
		// Hmmond registers: 0-8
		int reg = val / 12; // 0-96 -> "0-8"
		
		ui->verticalSlider_Osc1UnisonLevel_8->blockSignals(true);
		ui->verticalSlider_Osc1UnisonLevel_8->setValue(reg * 12);
		ui->verticalSlider_Osc1UnisonLevel_8->blockSignals(false);
		
		ui->spinBox_Osc1UnisonLevel_8->blockSignals(true);
		ui->spinBox_Osc1UnisonLevel_8->setValue(reg);
		ui->spinBox_Osc1UnisonLevel_8->blockSignals(false);
		
		osc1_unison_levels[7] = reg * 12;
		
		mod_synth_vco_event_int(_OSC_1_EVENT, _OSC_UNISON_LEVEL_8, reg * 12);
	}
	;
	
	/* Set focus back on the Dialog */
	this->setFocus(Qt::ActiveWindowFocusReason);
}

void Dialog_AnalogSynth::on_osc1_unison_level_9_slider_changed(int val)
{
	if ((val < _OSC1_UNISON_LEVEL_MIN) || (val > _OSC1_UNISON_LEVEL_MAX))
	{
		return; 
	}
	
	if (mod_synth_get_active_osc1_unison_mode() != _OSC_UNISON_MODE_HAMMOND)
	{
		ui->verticalSlider_Osc1UnisonLevel_9->blockSignals(true);
		ui->verticalSlider_Osc1UnisonLevel_9->setValue(val);
		ui->verticalSlider_Osc1UnisonLevel_9->blockSignals(false);
		
		ui->spinBox_Osc1UnisonLevel_9->blockSignals(true);
		ui->spinBox_Osc1UnisonLevel_9->setValue(val);
		ui->spinBox_Osc1UnisonLevel_9->blockSignals(false);
		
		osc1_unison_levels[8] = val;
		
		mod_synth_vco_event_int(_OSC_1_EVENT, _OSC_UNISON_LEVEL_1, val);
	}
	else if (mod_synth_get_active_osc1_unison_mode() == _OSC_UNISON_MODE_HAMMOND)
	{
		// Hmmond registers: 0-8
		int reg = val / 12; // 0-96 -> "0-8"
		
		ui->verticalSlider_Osc1UnisonLevel_9->blockSignals(true);
		ui->verticalSlider_Osc1UnisonLevel_9->setValue(reg * 12);
		ui->verticalSlider_Osc1UnisonLevel_9->blockSignals(false);
		
		ui->spinBox_Osc1UnisonLevel_9->blockSignals(true);
		ui->spinBox_Osc1UnisonLevel_9->setValue(reg);
		ui->spinBox_Osc1UnisonLevel_9->blockSignals(false);
		
		osc1_unison_levels[8] = reg * 12;
		
		mod_synth_vco_event_int(_OSC_1_EVENT, _OSC_UNISON_LEVEL_9, reg * 12);
	}
	
	/* Set focus back on the Dialog */
	this->setFocus(Qt::ActiveWindowFocusReason);
}

void Dialog_AnalogSynth::on_osc1_unison_distortion_slider_changed(int val)
{
	if ((val < _OSC1_UNISON_DISTORTION_MIN) || (val > _OSC1_UNISON_DISTORTION_MAX))
	{
		return; 
	}
	
	ui->verticalSlider_Osc1HarmonyDistortLevel->blockSignals(true);
	ui->verticalSlider_Osc1HarmonyDistortLevel->setValue(val);
	ui->verticalSlider_Osc1HarmonyDistortLevel->blockSignals(false);
	
	ui->spinBox_Osc1HarmonyDistort->blockSignals(true);
	ui->spinBox_Osc1HarmonyDistort->setValue(val);
	ui->spinBox_Osc1HarmonyDistort->blockSignals(false);
	
	osc_1_unison_distortion = val;
	
	mod_synth_vco_event_int(_OSC_1_EVENT, _OSC_UNISON_DISTORTION, val);
	
	/* Set focus back on the Dialog */
	this->setFocus(Qt::ActiveWindowFocusReason);
}

void Dialog_AnalogSynth::on_osc1_unison_detune_slider_changed(int val)
{
	if ((val < _OSC1_UNISON_DETUNE_MIN) || (val > _OSC1_UNISON_DETUNE_MAX))
	{
		return; 
	}
	
	ui->verticalSlider_Osc1HarmonyDetuneLevel->blockSignals(true);
	ui->verticalSlider_Osc1HarmonyDetuneLevel->setValue(val);
	ui->verticalSlider_Osc1HarmonyDetuneLevel->blockSignals(false);
	
	ui->spinBox_Osc1HarmonyDetune->blockSignals(true);
	ui->spinBox_Osc1HarmonyDetune->setValue(val);
	ui->spinBox_Osc1HarmonyDetune->blockSignals(false);
	
	osc_1_unison_detune = val;
	
	mod_synth_vco_event_int(_OSC_1_EVENT, _OSC_UNISON_DETUNE, val);
	
	/* Set focus back on the Dialog */
	this->setFocus(Qt::ActiveWindowFocusReason);
}


void Dialog_AnalogSynth::on_osc1_send_filter_1_dial_changed(int val)
{
	ui->dial_Osc1SendFilter1->blockSignals(true);
	ui->dial_Osc1SendFilter1->setValue(val);
	ui->dial_Osc1SendFilter1->blockSignals(false);
	
	ui->spinBox_Osc1SendFilter1->blockSignals(true);
	ui->spinBox_Osc1SendFilter1->setValue(val);
	ui->spinBox_Osc1SendFilter1->blockSignals(false);
	
	osc1_send_filter_1_level = val;
	mod_synth_vco_event_int(_OSC_1_EVENT, _OSC_FILTER_SEND_1, val);
	
	/* Set focus back on the Dialog */
	this->setFocus(Qt::ActiveWindowFocusReason);
}

void Dialog_AnalogSynth::on_osc1_send_filter_2_dial_changed(int val)
{
	ui->dial_Osc1SendFilter2->blockSignals(true);
	ui->dial_Osc1SendFilter2->setValue(val);
	ui->dial_Osc1SendFilter2->blockSignals(false);
	
	ui->spinBox_Osc1SendFilter2->blockSignals(true);
	ui->spinBox_Osc1SendFilter2->setValue(val);
	ui->spinBox_Osc1SendFilter2->blockSignals(false);
	
	osc1_send_filter_2_level = val;
	mod_synth_vco_event_int(_OSC_1_EVENT, _OSC_FILTER_SEND_2, val);
	
	/* Set focus back on the Dialog */
	this->setFocus(Qt::ActiveWindowFocusReason);
}

void Dialog_AnalogSynth::on_osc1_freq_mod_lfo_level_dial_changed(int val)
{
	// int log_val = mod_synth_log_scale_100_int(0, 100, 10, val);
	
	ui->dial_Osc1FreqModLFOLevel->blockSignals(true);
	ui->dial_Osc1FreqModLFOLevel->setValue(val);
	ui->dial_Osc1FreqModLFOLevel->blockSignals(false);
	
	ui->spinBox_Osc1FreqModLfoLevel->blockSignals(true);
	ui->spinBox_Osc1FreqModLfoLevel->setValue(val);
	ui->spinBox_Osc1FreqModLfoLevel->blockSignals(false);
	
	osc1_freq_mod_lfo_level = val;
	mod_synth_vco_event_int(_OSC_1_EVENT, _OSC_FREQ_MOD_LFO_LEVEL, val);
	
	/* Set focus back on the Dialog */
	this->setFocus(Qt::ActiveWindowFocusReason);
}

void Dialog_AnalogSynth::on_osc1_freq_mod_adsr_level_dial_changed(int val)
{
	ui->dial_Osc1FreqModAdsrLevel->blockSignals(true);
	ui->dial_Osc1FreqModAdsrLevel->setValue(val);
	ui->dial_Osc1FreqModAdsrLevel->blockSignals(false);
	
	ui->spinBox_Osc1FreqModAdsrLevel->blockSignals(true);
	ui->spinBox_Osc1FreqModAdsrLevel->setValue(val);
	ui->spinBox_Osc1FreqModAdsrLevel->blockSignals(false);
	
	osc1_freq_mod_adsr_level = val;
	mod_synth_vco_event_int(_OSC_1_EVENT, _OSC_FREQ_MOD_ENV_LEVEL, val);
	
	/* Set focus back on the Dialog */
	this->setFocus(Qt::ActiveWindowFocusReason);
}

void Dialog_AnalogSynth::on_osc1_pwm_mod_lfo_level_dial_changed(int val)
{
	ui->dial_Osc1PwmModLFOLevel->blockSignals(true);
	ui->dial_Osc1PwmModLFOLevel->setValue(val);
	ui->dial_Osc1PwmModLFOLevel->blockSignals(false);
	
	ui->spinBox_Osc1PwmModLfoLevel->blockSignals(true);
	ui->spinBox_Osc1PwmModLfoLevel->setValue(val);
	ui->spinBox_Osc1PwmModLfoLevel->blockSignals(false);
	
	osc1_pwm_mod_lfo_level = val;
	mod_synth_vco_event_int(_OSC_1_EVENT, _OSC_PWM_MOD_LFO_LEVEL, val);
	
	/* Set focus back on the Dialog */
	this->setFocus(Qt::ActiveWindowFocusReason);
}

void Dialog_AnalogSynth::on_osc1_pwm_mod_adsr_level_dial_changed(int val)
{
	ui->dial_Osc1PwmModAdsrLevel->blockSignals(true);
	ui->dial_Osc1PwmModAdsrLevel->setValue(val);
	ui->dial_Osc1PwmModAdsrLevel->blockSignals(false);
	
	ui->spinBox_Osc1PwmModAdsrLevel->blockSignals(true);
	ui->spinBox_Osc1PwmModAdsrLevel->setValue(val);
	ui->spinBox_Osc1PwmModAdsrLevel->blockSignals(false);
	
	osc1_pwm_mod_adsr_level = val;
	mod_synth_vco_event_int(_OSC_1_EVENT, _OSC_PWM_MOD_ENV_LEVEL, val);
	
	/* Set focus back on the Dialog */
	this->setFocus(Qt::ActiveWindowFocusReason);
}

void Dialog_AnalogSynth::on_osc1_amp_mod_lfo_level_dial_changed(int val)
{
	ui->dial_Osc1AmpModLFOLevel->blockSignals(true);
	ui->dial_Osc1AmpModLFOLevel->setValue(val);
	ui->dial_Osc1AmpModLFOLevel->blockSignals(false);
	
	ui->spinBox_Osc1AmpModLfoLevel->blockSignals(true);
	ui->spinBox_Osc1AmpModLfoLevel->setValue(val);
	ui->spinBox_Osc1AmpModLfoLevel->blockSignals(false);
	
	osc1_amp_mod_lfo_level = val;
	mod_synth_vco_event_int(_OSC_1_EVENT, _OSC_AMP_MOD_LFO_LEVEL, val);
	
	/* Set focus back on the Dialog */
	this->setFocus(Qt::ActiveWindowFocusReason);
}

void Dialog_AnalogSynth::on_osc1_amp_mod_adsr_level_dial_changed(int val)
{
	ui->dial_Osc1AmpModAdsrLevel->blockSignals(true);
	ui->dial_Osc1AmpModAdsrLevel->setValue(val);
	ui->dial_Osc1AmpModAdsrLevel->blockSignals(false);
	
	ui->spinBox_Osc1AmpModAdsrLevel->blockSignals(true);
	ui->spinBox_Osc1AmpModAdsrLevel->setValue(val);
	ui->spinBox_Osc1AmpModAdsrLevel->blockSignals(false);
	
	osc1_amp_mod_adsr_level = val;
	mod_synth_vco_event_int(_OSC_1_EVENT, _OSC_AMP_MOD_ENV_LEVEL, val);
	
	/* Set focus back on the Dialog */
	this->setFocus(Qt::ActiveWindowFocusReason);
}


void Dialog_AnalogSynth::on_osc1_waveform_combobox_changed(int val)
{
	ui->comboBox_Osc1Waveform->blockSignals(true);
	ui->comboBox_Osc1Waveform->setCurrentIndex(val);
	ui->comboBox_Osc1Waveform->blockSignals(false);
	
	osc1_waveform = val;
	mod_synth_vco_event_int(_OSC_1_EVENT, _OSC_PARAM_WAVEFORM, val);
	
	/* Set focus back on the Dialog */
	this->setFocus(Qt::ActiveWindowFocusReason);
}

void Dialog_AnalogSynth::on_osc1_tune_octave_combobox_changed(int val)
{
	ui->comboBox_Osc1TuneOctave->blockSignals(true);
	ui->comboBox_Osc1TuneOctave->setCurrentIndex(val);
	ui->comboBox_Osc1TuneOctave->blockSignals(false);
	
	osc1_tune_octave = val;
	mod_synth_vco_event_int(_OSC_1_EVENT, _OSC_DETUNE_OCTAVE, val);
	
	/* Set focus back on the Dialog */
	this->setFocus(Qt::ActiveWindowFocusReason);
}

void Dialog_AnalogSynth::on_osc1_tune_semitones_combobox_changed(int val)
{
	ui->comboBox_Osc1TuneSemitones->blockSignals(true);
	ui->comboBox_Osc1TuneSemitones->setCurrentIndex(val);
	ui->comboBox_Osc1TuneSemitones->blockSignals(false);
	
	osc1_tune_cents = val;
	mod_synth_vco_event_int(_OSC_1_EVENT, _OSC_DETUNE_SEMITONES, val);
	
	/* Set focus back on the Dialog */
	this->setFocus(Qt::ActiveWindowFocusReason);
}

void Dialog_AnalogSynth::on_osc1_tune_cents_combobox_changed(int val)
{
	ui->comboBox_Osc1TuneCents->blockSignals(true);
	ui->comboBox_Osc1TuneCents->setCurrentIndex(val);
	ui->comboBox_Osc1TuneCents->blockSignals(false);
	
	osc1_tune_cents = val;
	mod_synth_vco_event_int(_OSC_1_EVENT, _OSC_DETUNE_CENTS, val);
	
	/* Set focus back on the Dialog */
	this->setFocus(Qt::ActiveWindowFocusReason);
}

void Dialog_AnalogSynth::on_osc1_freq_mod_lfo_combobox_changed(int val)
{
	ui->comboBox_Osc1FreqModLFO->blockSignals(true);
	ui->comboBox_Osc1FreqModLFO->setCurrentIndex(val);
	ui->comboBox_Osc1FreqModLFO->blockSignals(false);
	
	osc1_freq_mod_lfo_num = val;
	mod_synth_vco_event_int(_OSC_1_EVENT, _OSC_FREQ_MOD_LFO, val);
	
	/* Set focus back on the Dialog */
	this->setFocus(Qt::ActiveWindowFocusReason);
}

void Dialog_AnalogSynth::on_osc1_freq_mod_adsr_combobox_changed(int val)
{
	ui->comboBox_Osc1FreqModAdsr->blockSignals(true);
	ui->comboBox_Osc1FreqModAdsr->setCurrentIndex(val);
	ui->comboBox_Osc1FreqModAdsr->blockSignals(false);
	
	osc1_freq_mod_adsr_num = val;
	mod_synth_vco_event_int(_OSC_1_EVENT, _OSC_FREQ_MOD_ENV, val);
	
	/* Set focus back on the Dialog */
	this->setFocus(Qt::ActiveWindowFocusReason);
}

void Dialog_AnalogSynth::on_osc1_pwm_mod_lfo_combobox_changed(int val)
{
	ui->comboBox_Osc1PwmModLFO->blockSignals(true);
	ui->comboBox_Osc1PwmModLFO->setCurrentIndex(val);
	ui->comboBox_Osc1PwmModLFO->blockSignals(false);
	
	osc1_pwm_mod_lfo_num = val;
	mod_synth_vco_event_int(_OSC_1_EVENT, _OSC_PWM_MOD_LFO, val);
	
	/* Set focus back on the Dialog */
	this->setFocus(Qt::ActiveWindowFocusReason);
}

void Dialog_AnalogSynth::on_osc1_pwm_mod_adsr_combobox_changed(int val)
{
	ui->comboBox_Osc1PwmModAdsr->blockSignals(true);
	ui->comboBox_Osc1PwmModAdsr->setCurrentIndex(val);
	ui->comboBox_Osc1PwmModAdsr->blockSignals(false);
	
	osc1_pwm_mod_adsr_num = val;
	mod_synth_vco_event_int(_OSC_1_EVENT, _OSC_PWM_MOD_ENV, val);
	
	/* Set focus back on the Dialog */
	this->setFocus(Qt::ActiveWindowFocusReason);
}

void Dialog_AnalogSynth::on_osc1_amp_mod_lfo_combobox_changed(int val)
{
	ui->comboBox_Osc1AmpModLFO->blockSignals(true);
	ui->comboBox_Osc1AmpModLFO->setCurrentIndex(val);
	ui->comboBox_Osc1AmpModLFO->blockSignals(false);
	
	osc1_amp_mod_lfo_num = val;
	mod_synth_vco_event_int(_OSC_1_EVENT, _OSC_AMP_MOD_LFO, val);
	
	/* Set focus back on the Dialog */
	this->setFocus(Qt::ActiveWindowFocusReason);
}

void Dialog_AnalogSynth::on_osc1_amp_mod_adsr_combobox_changed(int val)
{
	ui->comboBox_Osc1AmpModAdsr->blockSignals(true);
	ui->comboBox_Osc1AmpModAdsr->setCurrentIndex(val);
	ui->comboBox_Osc1AmpModAdsr->blockSignals(false);
	
	osc1_amp_mod_adsr_num = val;
	mod_synth_vco_event_int(_OSC_1_EVENT, _OSC_AMP_MOD_ENV, val);
	
	/* Set focus back on the Dialog */
	this->setFocus(Qt::ActiveWindowFocusReason);
}

void Dialog_AnalogSynth::on_osc1_hammond_percussion_mode_combobox_changed(int val)
{
	ui->comboBox_Osc1HammondPercussionMode->blockSignals(true);
	ui->comboBox_Osc1HammondPercussionMode->setCurrentIndex(val);
	ui->comboBox_Osc1HammondPercussionMode->blockSignals(false);
	
	osc1_hammond_percussion_mode = val;
	mod_synth_vco_event_int(_OSC_1_EVENT, _OSC_HAMMOND_PERCUSION_MODE, val);
	
	osc1_update();
	
	/* Set focus back on the Dialog */
	this->setFocus(Qt::ActiveWindowFocusReason);
}

void Dialog_AnalogSynth::on_osc1_unison_mode_combobox_changed(int val)
{
	ui->comboBox_Osc1UnisonMode->blockSignals(true);
	ui->comboBox_Osc1UnisonMode->setCurrentIndex(val);
	ui->comboBox_Osc1UnisonMode->blockSignals(false);
	
	osc1_unison_mode = val;
	mod_synth_vco_event_int(_OSC_1_EVENT, _OSC_UNISON_MODE, val);
	
	/* Set focus back on the Dialog */
	this->setFocus(Qt::ActiveWindowFocusReason);
}
