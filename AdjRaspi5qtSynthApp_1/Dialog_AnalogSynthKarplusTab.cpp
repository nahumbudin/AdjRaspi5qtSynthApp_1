/**
* @file		Dialog_AnalogSynthKarplusTab.h
*	@author		Nahum Budin
*	@date		11-Nov-2024
*	@version	1.0
*
*	@brief		Analog Synthesizer instrument Karplus Strong String Synthesizer Tab handling
*				
*	History:
*			Based on the AdjModSynth project ver 1.1 16-Jan-2021 
*
*/

#include "Dialog_AnalogSynth.h"
#include "ui_Dialog_AnalogSynth.h"
#include "utils.h"

#include "libAdjRaspi5SynthAPI.h"

void Dialog_AnalogSynth::set_kps_signals_connections()
{
	connect(ui->comboBox_KarplusSynth_ExcitationWaveform,
		SIGNAL(currentIndexChanged(int)),
		this,
		SLOT(on_karplus_excitation_waveform_combobox_changed(int)));

	connect(ui->horizontalSlider_KarplusSynth_WaveformVariations,
		SIGNAL(valueChanged(int)),
		this,
		SLOT(on_karplus_excitation_waveform_variations_slider_changed(int)));

	connect(ui->comboBox_KarplusSynth_CalculationMode,
		SIGNAL(currentIndexChanged(int)),
		this,
		SLOT(on_karplus_string_damping_calc_mode_combobox_hanged(int)));

	connect(ui->horizontalSlider_KarplusSynth_StringDamping,
		SIGNAL(valueChanged(int)),
		this,
		SLOT(on_karplus_string_damping_slider_changed(int)));

	connect(ui->horizontalSlider_KarplusSynth_StringDampingVariations,
		SIGNAL(valueChanged(int)),
		this,
		SLOT(on_karplus_string_damping_variation_slider_changed(int)));
	
	connect(ui->horizontalSlider_KarplusSynth_PluckDamping,
		SIGNAL(valueChanged(int)),
		this,
		SLOT(on_karplus_pluck_damping_slider_changed(int)));

	connect(ui->horizontalSlider_KarplusSynth_PluckDampingVariations,
		SIGNAL(valueChanged(int)),
		this,
		SLOT(on_karplus_pluck_damping_variation_slider_changed(int)));

	connect(ui->horizontalSlider_KarplusSynth_OnDecay,
		SIGNAL(valueChanged(int)),
		this,
		SLOT(on_karplus_on_decay_slider_changed(int)));

	connect(ui->horizontalSlider_KarplusSynth_OffDecay,
		SIGNAL(valueChanged(int)),
		this,
		SLOT(on_karplus_off_decay_slider_changed(int)));

	connect(ui->dial_KarplusSynth_SendFilter1,
		SIGNAL(valueChanged(int)),
		this,
		SLOT(on_karplus_send_filter1_dial_changed(int)));

	connect(ui->dial_KarplusSynth_SendFilter2,
		SIGNAL(valueChanged(int)),
		this,
		SLOT(on_karplus_send_filter2_dial_changed(int)));

	connect(ui->checkBox_KarplusSynth_Active,
		SIGNAL(toggled(bool)),
		this,
		SLOT(on_karplus_enable_checkbox_changed(bool)));
}

void Dialog_AnalogSynth::init_kps_combboxes_and_labels()
{
	string_karplus_excitation_waveform_list.append("White Noise");
	string_karplus_excitation_waveform_list.append("Pink Noise");
	string_karplus_excitation_waveform_list.append("Brown Noise");
	string_karplus_excitation_waveform_list.append("Sine Chirp");
	string_karplus_excitation_waveform_list.append("Decayed Sine");
	string_karplus_excitation_waveform_list.append("Sawtooth Wave");
	string_karplus_excitation_waveform_list.append("Square Wave");
	
	ui->comboBox_KarplusSynth_ExcitationWaveform->blockSignals(true);
	ui->comboBox_KarplusSynth_ExcitationWaveform->addItems(string_karplus_excitation_waveform_list);
	ui->comboBox_KarplusSynth_ExcitationWaveform->blockSignals(false);
	
	string_karplus_string_damping_calc_mode_list.append("Direct");
	string_karplus_string_damping_calc_mode_list.append("Magic");
	
	ui->comboBox_KarplusSynth_CalculationMode->blockSignals(true);
	ui->comboBox_KarplusSynth_CalculationMode->addItems(string_karplus_string_damping_calc_mode_list);
	ui->comboBox_KarplusSynth_CalculationMode->blockSignals(false);
}

void Dialog_AnalogSynth::kps_update()
{
	ui->comboBox_KarplusSynth_ExcitationWaveform->blockSignals(true);
	ui->comboBox_KarplusSynth_ExcitationWaveform->setCurrentIndex(mod_synth_get_active_karplus_excitation_waveform_type());
	ui->comboBox_KarplusSynth_ExcitationWaveform->blockSignals(false);

	ui->comboBox_KarplusSynth_CalculationMode->blockSignals(true);
	ui->comboBox_KarplusSynth_CalculationMode->setCurrentIndex(mod_synth_get_active_karplus_string_damping_calculation_mode());
	ui->comboBox_KarplusSynth_CalculationMode->blockSignals(false);

	ui->horizontalSlider_KarplusSynth_StringDamping->blockSignals(true);
	ui->horizontalSlider_KarplusSynth_StringDamping->setValue(mod_synth_get_active_karplus_string_damping());
	ui->horizontalSlider_KarplusSynth_StringDamping->blockSignals(false);
	
	ui->horizontalSlider_KarplusSynth_PluckDamping->blockSignals(true);
	ui->horizontalSlider_KarplusSynth_PluckDamping->setValue(mod_synth_get_active_karplus_pluck_damping());
	ui->horizontalSlider_KarplusSynth_PluckDamping->blockSignals(false);

	ui->horizontalSlider_KarplusSynth_OnDecay->blockSignals(true);
	ui->horizontalSlider_KarplusSynth_OnDecay->setValue(mod_synth_get_active_karplus_string_on_decay());
	ui->horizontalSlider_KarplusSynth_OnDecay->blockSignals(false);

	ui->horizontalSlider_KarplusSynth_OffDecay->blockSignals(true);
	ui->horizontalSlider_KarplusSynth_OffDecay->setValue(mod_synth_get_active_karplus_string_off_decay());
	ui->horizontalSlider_KarplusSynth_OffDecay->blockSignals(false);

	ui->horizontalSlider_KarplusSynth_StringDampingVariations->blockSignals(true);
	ui->horizontalSlider_KarplusSynth_StringDampingVariations->setValue(mod_synth_get_active_karplus_string_damping_variation());
	ui->horizontalSlider_KarplusSynth_StringDampingVariations->blockSignals(false);
	
	ui->horizontalSlider_KarplusSynth_PluckDampingVariations->blockSignals(true);
	ui->horizontalSlider_KarplusSynth_PluckDampingVariations->setValue(mod_synth_get_active_karplus_pluck_damping_variation());
	ui->horizontalSlider_KarplusSynth_PluckDampingVariations->blockSignals(false);

	ui->dial_KarplusSynth_SendFilter1->blockSignals(true);
	ui->dial_KarplusSynth_SendFilter1->setValue(mod_synth_get_active_karplus_send_filter_1());
	ui->dial_KarplusSynth_SendFilter1->blockSignals(false);
									  
	ui->dial_KarplusSynth_SendFilter2->blockSignals(true);
	ui->dial_KarplusSynth_SendFilter2->setValue(mod_synth_get_active_karplus_send_filter_2());
	ui->dial_KarplusSynth_SendFilter2->blockSignals(false);
	
	ui->spinBox_KarplusSynth_StringDamping->blockSignals(true);
	ui->spinBox_KarplusSynth_StringDamping->setValue(mod_synth_get_active_karplus_string_damping());
	ui->spinBox_KarplusSynth_StringDamping->blockSignals(false);
	
	ui->spinBox_KarplusSynth_PluckDamping->blockSignals(true);
	ui->spinBox_KarplusSynth_PluckDamping->setValue(mod_synth_get_active_karplus_pluck_damping());
	ui->spinBox_KarplusSynth_PluckDamping->blockSignals(false);

	ui->spinBox_KarplusSynth_OnDecay->blockSignals(true);
	ui->spinBox_KarplusSynth_OnDecay->setValue(mod_synth_get_active_karplus_string_on_decay());
	ui->spinBox_KarplusSynth_OnDecay->blockSignals(false);

	ui->spinBox_KarplusSynth_OffDecay->blockSignals(true);
	ui->spinBox_KarplusSynth_OffDecay->setValue(mod_synth_get_active_karplus_string_off_decay());
	ui->spinBox_KarplusSynth_OffDecay->blockSignals(false);

	ui->spinBox_KarplusSynth_StringDampingVariations->blockSignals(true);
	ui->spinBox_KarplusSynth_StringDampingVariations->setValue(mod_synth_get_active_karplus_string_damping_variation());
	ui->spinBox_KarplusSynth_StringDampingVariations->blockSignals(false);
	
	ui->spinBox_KarplusSynth_PluckDampingVariations->blockSignals(true);
	ui->spinBox_KarplusSynth_PluckDampingVariations->setValue(mod_synth_get_active_karplus_pluck_damping_variation());
	ui->spinBox_KarplusSynth_PluckDampingVariations->blockSignals(false);

	ui->spinBox_KarplusSynth_SendFilter1->blockSignals(true);
	ui->spinBox_KarplusSynth_SendFilter1->setValue(mod_synth_get_active_karplus_send_filter_1());
	ui->spinBox_KarplusSynth_SendFilter1->blockSignals(false);
									  
	ui->spinBox_KarplusSynth_SendFilter2->blockSignals(true);
	ui->spinBox_KarplusSynth_SendFilter2->setValue(mod_synth_get_active_karplus_send_filter_2());
	ui->spinBox_KarplusSynth_SendFilter2->blockSignals(false);

	kps_enabled  = mod_synth_get_active_karplus_enable_state();
	
	ui->checkBox_KarplusSynth_Active->blockSignals(true);
	ui->checkBox_KarplusSynth_Active->setChecked(kps_enabled);
	ui->checkBox_KarplusSynth_Active->blockSignals(false);
	
	if (kps_enabled)
	{
		ui->frame_KarplusMain->setEnabled(true);
		ui->frame_KarplusSecond->setEnabled(true);
		ui->frame_KarplusSend->setEnabled(true);
	}
	else
	{
		ui->frame_KarplusMain->setEnabled(false);
		ui->frame_KarplusSecond->setEnabled(false);
		ui->frame_KarplusSend->setEnabled(false);
	}
}

void Dialog_AnalogSynth::on_karplus_excitation_waveform_combobox_changed(int val)
{
	ui->comboBox_KarplusSynth_ExcitationWaveform->blockSignals(true);
	ui->comboBox_KarplusSynth_ExcitationWaveform->setCurrentIndex(val);
	ui->comboBox_KarplusSynth_ExcitationWaveform->blockSignals(false);
	
	kps_excitation_waveform = val;
	mod_synth_karplus_event_int(_KARPLUS_1_EVENT, _KARPLUS_STRONG_EXCITATION_WAVEFORM, val);
	
	/* Set focus back on the Dialog */
	this->setFocus(Qt::ActiveWindowFocusReason);
}

void Dialog_AnalogSynth::on_karplus_excitation_waveform_variations_slider_changed(int val)
{
	ui->horizontalSlider_KarplusSynth_WaveformVariations->blockSignals(true);
	ui->horizontalSlider_KarplusSynth_WaveformVariations->setValue(val);
	ui->horizontalSlider_KarplusSynth_WaveformVariations->blockSignals(false);
	
	ui->spinBox_KarplusSynth_WaveformVariations->blockSignals(true);
	ui->spinBox_KarplusSynth_WaveformVariations->setValue(val);
	ui->spinBox_KarplusSynth_WaveformVariations->blockSignals(false);
	
	kps_waveform_variations = val;
	
	mod_synth_karplus_event_int(_KARPLUS_1_EVENT, _KARPLUS_STRONG_EXCITATION_WAVEFORM_VARIATIONS, val);
	
	/* Set focus back on the Dialog */
	this->setFocus(Qt::ActiveWindowFocusReason);
}

void Dialog_AnalogSynth::on_karplus_string_damping_slider_changed(int val)
{
	ui->horizontalSlider_KarplusSynth_StringDamping->blockSignals(true);
	ui->horizontalSlider_KarplusSynth_StringDamping->setValue(val);
	ui->horizontalSlider_KarplusSynth_StringDamping->blockSignals(false);
	
	ui->spinBox_KarplusSynth_StringDamping->blockSignals(true);
	ui->spinBox_KarplusSynth_StringDamping->setValue(val);
	ui->spinBox_KarplusSynth_StringDamping->blockSignals(false);
	
	kps_string_damping = val;
	
	mod_synth_karplus_event_int(_KARPLUS_1_EVENT, _KARPLUS_STRONG_STRING_DAMPING, val);
	
	/* Set focus back on the Dialog */
	this->setFocus(Qt::ActiveWindowFocusReason);
}

void Dialog_AnalogSynth::on_karplus_string_damping_variation_slider_changed(int val)
{
	ui->horizontalSlider_KarplusSynth_StringDampingVariations->blockSignals(true);
	ui->horizontalSlider_KarplusSynth_StringDampingVariations->setValue(val);
	ui->horizontalSlider_KarplusSynth_StringDampingVariations->blockSignals(false);
	
	ui->spinBox_KarplusSynth_StringDampingVariations->blockSignals(true);
	ui->spinBox_KarplusSynth_StringDampingVariations->setValue(val);
	ui->spinBox_KarplusSynth_StringDampingVariations->blockSignals(false);
	
	kps_string_damping_variations = val;
	
	mod_synth_karplus_event_int(_KARPLUS_1_EVENT, _KARPLUS_STRONG_STRING_DAMPING_VARIATION, val);
	
	/* Set focus back on the Dialog */
	this->setFocus(Qt::ActiveWindowFocusReason);
}

void Dialog_AnalogSynth::on_karplus_string_damping_calc_mode_combobox_hanged(int val)
{
	ui->comboBox_KarplusSynth_CalculationMode->blockSignals(true);
	ui->comboBox_KarplusSynth_CalculationMode->setCurrentIndex(val);
	ui->comboBox_KarplusSynth_CalculationMode->blockSignals(false);
	
	kps_string_dump_calculation_mode = val;
	mod_synth_karplus_event_int(_KARPLUS_1_EVENT, _KARPLUS_STRONG_STRING_DUMP_CALC_MODE, val);
	
	/* Set focus back on the Dialog */
	this->setFocus(Qt::ActiveWindowFocusReason);
}

void Dialog_AnalogSynth::on_karplus_pluck_damping_slider_changed(int val)
{
	ui->horizontalSlider_KarplusSynth_PluckDamping->blockSignals(true);
	ui->horizontalSlider_KarplusSynth_PluckDamping->setValue(val);
	ui->horizontalSlider_KarplusSynth_PluckDamping->blockSignals(false);
	
	ui->spinBox_KarplusSynth_PluckDamping->blockSignals(true);
	ui->spinBox_KarplusSynth_PluckDamping->setValue(val);
	ui->spinBox_KarplusSynth_PluckDamping->blockSignals(false);
	
	kps_pluck_damping = val;
	
	mod_synth_karplus_event_int(_KARPLUS_1_EVENT, _KARPLUS_STRONG_PLUCK_DAMPING, val);
	
	/* Set focus back on the Dialog */
	this->setFocus(Qt::ActiveWindowFocusReason);
}

void Dialog_AnalogSynth::on_karplus_pluck_damping_variation_slider_changed(int val)
{
	ui->horizontalSlider_KarplusSynth_PluckDampingVariations->blockSignals(true);
	ui->horizontalSlider_KarplusSynth_PluckDampingVariations->setValue(val);
	ui->horizontalSlider_KarplusSynth_PluckDampingVariations->blockSignals(false);
	
	ui->spinBox_KarplusSynth_PluckDampingVariations->blockSignals(true);
	ui->spinBox_KarplusSynth_PluckDampingVariations->setValue(val);
	ui->spinBox_KarplusSynth_PluckDampingVariations->blockSignals(false);
	
	kps_pluck_damping_variations = val;
	
	mod_synth_karplus_event_int(_KARPLUS_1_EVENT, _KARPLUS_STRONG_PLUCK_DAMPING_VARIATION, val);
	
	/* Set focus back on the Dialog */
	this->setFocus(Qt::ActiveWindowFocusReason);
}

void Dialog_AnalogSynth::on_karplus_on_decay_slider_changed(int val)
{
	ui->horizontalSlider_KarplusSynth_OnDecay->blockSignals(true);
	ui->horizontalSlider_KarplusSynth_OnDecay->setValue(val);
	ui->horizontalSlider_KarplusSynth_OnDecay->blockSignals(false);
	
	ui->spinBox_KarplusSynth_OnDecay->blockSignals(true);
	ui->spinBox_KarplusSynth_OnDecay->setValue(val);
	ui->spinBox_KarplusSynth_OnDecay->blockSignals(false);
	
	kps_on_decay = val;
	
	mod_synth_karplus_event_int(_KARPLUS_1_EVENT, _KARPLUS_STRONG_ON_DECAY, val);
	
	/* Set focus back on the Dialog */
	this->setFocus(Qt::ActiveWindowFocusReason);
}

void Dialog_AnalogSynth::on_karplus_off_decay_slider_changed(int val)
{
	ui->horizontalSlider_KarplusSynth_OffDecay->blockSignals(true);
	ui->horizontalSlider_KarplusSynth_OffDecay->setValue(val);
	ui->horizontalSlider_KarplusSynth_OffDecay->blockSignals(false);
	
	ui->spinBox_KarplusSynth_OffDecay->blockSignals(true);
	ui->spinBox_KarplusSynth_OffDecay->setValue(val);
	ui->spinBox_KarplusSynth_OffDecay->blockSignals(false);
	
	kps_off_decay = val;
	
	mod_synth_karplus_event_int(_KARPLUS_1_EVENT, _KARPLUS_STRONG_OFF_DECAY, val);
	
	/* Set focus back on the Dialog */
	this->setFocus(Qt::ActiveWindowFocusReason);
}

void Dialog_AnalogSynth::on_karplus_send_filter1_dial_changed(int val)
{
	ui->dial_KarplusSynth_SendFilter1->blockSignals(true);
	ui->dial_KarplusSynth_SendFilter1->setValue(val);
	ui->dial_KarplusSynth_SendFilter1->blockSignals(false);
	
	ui->spinBox_KarplusSynth_SendFilter1->blockSignals(true);
	ui->spinBox_KarplusSynth_SendFilter1->setValue(val);
	ui->spinBox_KarplusSynth_SendFilter1->blockSignals(false);
	
	kps_send_filter_1_level = val;
	mod_synth_karplus_event_int(_KARPLUS_1_EVENT, _KARPLUS_STRONG_SEND_1, val);
	
	/* Set focus back on the Dialog */
	this->setFocus(Qt::ActiveWindowFocusReason);
}

void Dialog_AnalogSynth::on_karplus_send_filter2_dial_changed(int val)
{
	ui->dial_KarplusSynth_SendFilter2->blockSignals(true);
	ui->dial_KarplusSynth_SendFilter2->setValue(val);
	ui->dial_KarplusSynth_SendFilter2->blockSignals(false);
	
	ui->spinBox_KarplusSynth_SendFilter2->blockSignals(true);
	ui->spinBox_KarplusSynth_SendFilter2->setValue(val);
	ui->spinBox_KarplusSynth_SendFilter2->blockSignals(false);
	
	kps_send_filter_2_level = val;
	mod_synth_karplus_event_int(_KARPLUS_1_EVENT, _KARPLUS_STRONG_SEND_2, val);
	
	/* Set focus back on the Dialog */
	this->setFocus(Qt::ActiveWindowFocusReason);
}

void Dialog_AnalogSynth::on_karplus_enable_checkbox_changed(bool en)
{
	ui->checkBox_KarplusSynth_Active->blockSignals(true);
	
	if (en)
	{
		ui->checkBox_KarplusSynth_Active->setCheckState(Qt::Checked);
		mod_synth_enable_karplus();
	}
	else
	{
		ui->checkBox_KarplusSynth_Active->setCheckState(Qt::Unchecked);
		mod_synth_disable_karplus();
	}
	
	ui->checkBox_KarplusSynth_Active->blockSignals(false);
	
	kps_enabled = en;
	
	mod_synth_karplus_event_bool(_KARPLUS_1_EVENT, _KARPLUS_STRONG_ENABLE, en);
	
	kps_update();
	
	/* Set focus back on the Dialog */
	this->setFocus(Qt::ActiveWindowFocusReason);
}

