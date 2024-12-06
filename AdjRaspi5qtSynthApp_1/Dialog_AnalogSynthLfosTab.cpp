/**
* @file		Dialog_AnalogSynthLfosTab.h
*	@author		Nahum Budin
*	@date		27-Nov-2024
*	@version	1.0
*
*	@brief		Analog Synthesizer instrument LFOs Modulators Tab handling
*				
*	History:
*			Based on the AdjModSynth project ver 1.1 16-Jan-2021 
*
*/

#include "Dialog_AnalogSynth.h"
#include "ui_Dialog_AnalogSynth.h"
#include "utils.h"

#include "libAdjRaspi5SynthAPI.h"

void Dialog_AnalogSynth::set_lfos_signals_connections()
{
	connect(ui->comboBox_LFOwaveform_1,
		SIGNAL(currentIndexChanged(int)),
		this,
		SLOT(on_lfo1_waveform_combo_changed(int)));
	
	connect(ui->dial_LFOrate_1,
		SIGNAL(valueChanged(int)),
		this,
		SLOT(on_lfo1_rate_dial_changed(int)));

	connect(ui->dial_LFOsymmetry_1,
		SIGNAL(valueChanged(int)),
		this,
		SLOT(on_lfo1_symmetry_dial_changed(int)));
	
	connect(ui->comboBox_LFOwaveform_2,
		SIGNAL(currentIndexChanged(int)),
		this,
		SLOT(on_lfo2_waveform_combo_changed(int)));
	
	connect(ui->dial_LFOrate_2,
		SIGNAL(valueChanged(int)),
		this,
		SLOT(on_lfo2_rate_dial_changed(int)));

	connect(ui->dial_LFOsymmetry_2,
		SIGNAL(valueChanged(int)),
		this,
		SLOT(on_lfo2_symmetry_dial_changed(int)));
	
	connect(ui->comboBox_LFOwaveform_3,
		SIGNAL(currentIndexChanged(int)),
		this,
		SLOT(on_lfo3_waveform_combo_changed(int)));
	
	connect(ui->dial_LFOrate_3,
		SIGNAL(valueChanged(int)),
		this,
		SLOT(on_lfo3_rate_dial_changed(int)));

	connect(ui->dial_LFOsymmetry_3,
		SIGNAL(valueChanged(int)),
		this,
		SLOT(on_lfo3_symmetry_dial_changed(int)));

	connect(ui->comboBox_LFOwaveform_4,
		SIGNAL(currentIndexChanged(int)),
		this,
		SLOT(on_lfo4_waveform_combo_changed(int)));
	
	connect(ui->dial_LFOrate_4,
		SIGNAL(valueChanged(int)),
		this,
		SLOT(on_lfo4_rate_dial_changed(int)));

	connect(ui->dial_LFOsymmetry_4,
		SIGNAL(valueChanged(int)),
		this,
		SLOT(on_lfo4_symmetry_dial_changed(int)));
	
	connect(ui->comboBox_LFOwaveform_5,
		SIGNAL(currentIndexChanged(int)),
		this,
		SLOT(on_lfo5_waveform_combo_changed(int)));
	
	connect(ui->dial_LFOrate_5,
		SIGNAL(valueChanged(int)),
		this,
		SLOT(on_lfo5_rate_dial_changed(int)));

	connect(ui->dial_LFOsymmetry_5,
		SIGNAL(valueChanged(int)),
		this,
		SLOT(on_lfo5_symmetry_dial_changed(int)));
	
	connect(ui->comboBox_LFOwaveform_6,
		SIGNAL(currentIndexChanged(int)),
		this,
		SLOT(on_lfo6_waveform_combo_changed(int)));
	
	connect(ui->dial_LFOrate_6,
		SIGNAL(valueChanged(int)),
		this,
		SLOT(on_lfo6_rate_dial_changed(int)));

	connect(ui->dial_LFOsymmetry_6,
		SIGNAL(valueChanged(int)),
		this,
		SLOT(on_lfo6_symmetry_dial_changed(int)));
}

void Dialog_AnalogSynth::init_lfos_combboxes_and_labels()
{
	if (string_waveforms_list.size() == 0)
	{
		/* Do only once for all */
		string_waveforms_list.append("Sine");
		string_waveforms_list.append("Square");
		string_waveforms_list.append("Pulse");
		string_waveforms_list.append("Triangle");
		string_waveforms_list.append("Sample & Hold");
	}
	
	ui->comboBox_LFOwaveform_1->blockSignals(true);
	ui->comboBox_LFOwaveform_1->addItems(string_waveforms_list);
	ui->comboBox_LFOwaveform_1->blockSignals(false);
	
	ui->comboBox_LFOwaveform_2->blockSignals(true);
	ui->comboBox_LFOwaveform_2->addItems(string_waveforms_list);
	ui->comboBox_LFOwaveform_2->blockSignals(false);
	
	ui->comboBox_LFOwaveform_3->blockSignals(true);
	ui->comboBox_LFOwaveform_3->addItems(string_waveforms_list);
	ui->comboBox_LFOwaveform_3->blockSignals(false);
	
	ui->comboBox_LFOwaveform_4->blockSignals(true);
	ui->comboBox_LFOwaveform_4->addItems(string_waveforms_list);
	ui->comboBox_LFOwaveform_4->blockSignals(false);
	
	ui->comboBox_LFOwaveform_5->blockSignals(true);
	ui->comboBox_LFOwaveform_5->addItems(string_waveforms_list);
	ui->comboBox_LFOwaveform_5->blockSignals(false);
	
	ui->comboBox_LFOwaveform_6->blockSignals(true);
	ui->comboBox_LFOwaveform_6->addItems(string_waveforms_list);
	ui->comboBox_LFOwaveform_6->blockSignals(false);
	
	
}

void Dialog_AnalogSynth::lfos_update()
{
	char text[64];
	
	ui->comboBox_LFOwaveform_1->blockSignals(true);
	ui->comboBox_LFOwaveform_1->setCurrentIndex(mod_synth_get_active_lfo_mod_1_waveform());
	ui->comboBox_LFOwaveform_1->blockSignals(false);
	
	ui->dial_LFOsymmetry_1->blockSignals(true);
	ui->dial_LFOsymmetry_1->setValue(mod_synth_get_active_lfo_mod_1_symmetry());
	ui->dial_LFOsymmetry_1->blockSignals(false);
	sprintf(text, "%i%c", mod_synth_get_active_lfo_mod_1_symmetry(), '%');
	
	ui->dial_LFOrate_1->blockSignals(true);
	ui->dial_LFOrate_1->setValue(mod_synth_get_active_lfo_mod_1_rate());		
	ui->dial_LFOrate_1->blockSignals(false);
	
	sprintf(text, "%.2fHz", 
		mod_synth_log_scale_100_float(mod_synth_get_lfo_min_frequency(), 
			mod_synth_get_lfo_max_frequency(), 10.0, 
			mod_synth_get_active_lfo_mod_1_rate()));
	
	ui->lineEdit_LFOrate_1->setText(QString(text));
	
	ui->comboBox_LFOwaveform_2->blockSignals(true);
	ui->comboBox_LFOwaveform_2->setCurrentIndex(mod_synth_get_active_lfo_mod_2_waveform());
	ui->comboBox_LFOwaveform_2->blockSignals(false);
	
	ui->dial_LFOsymmetry_2->blockSignals(true);
	ui->dial_LFOsymmetry_2->setValue(mod_synth_get_active_lfo_mod_2_symmetry());
	ui->dial_LFOsymmetry_2->blockSignals(false);
	sprintf(text, "%i%c", mod_synth_get_active_lfo_mod_2_symmetry(), '%');
	
	ui->dial_LFOrate_2->blockSignals(true);
	ui->dial_LFOrate_2->setValue(mod_synth_get_active_lfo_mod_2_rate());		
	ui->dial_LFOrate_2->blockSignals(false);
	
	sprintf(text,
		"%.2fHz", 
		mod_synth_log_scale_100_float(mod_synth_get_lfo_min_frequency(), 
			mod_synth_get_lfo_max_frequency(),
			10.0, 
			mod_synth_get_active_lfo_mod_2_rate()));
	
	ui->lineEdit_LFOrate_2->setText(QString(text));
	
	ui->comboBox_LFOwaveform_3->blockSignals(true);
	ui->comboBox_LFOwaveform_3->setCurrentIndex(mod_synth_get_active_lfo_mod_3_waveform());
	ui->comboBox_LFOwaveform_3->blockSignals(false);
	
	ui->dial_LFOsymmetry_3->blockSignals(true);
	ui->dial_LFOsymmetry_3->setValue(mod_synth_get_active_lfo_mod_3_symmetry());
	ui->dial_LFOsymmetry_3->blockSignals(false);
	sprintf(text, "%i%c", mod_synth_get_active_lfo_mod_3_symmetry(), '%');
	
	ui->dial_LFOrate_3->blockSignals(true);
	ui->dial_LFOrate_3->setValue(mod_synth_get_active_lfo_mod_3_rate());		
	ui->dial_LFOrate_3->blockSignals(false);
	
	sprintf(text,
		"%.2fHz", 
		mod_synth_log_scale_100_float(mod_synth_get_lfo_min_frequency(), 
			mod_synth_get_lfo_max_frequency(),
			10.0, 
			mod_synth_get_active_lfo_mod_3_rate()));
	
	ui->lineEdit_LFOrate_3->setText(QString(text));
	
	ui->comboBox_LFOwaveform_4->blockSignals(true);
	ui->comboBox_LFOwaveform_4->setCurrentIndex(mod_synth_get_active_lfo_mod_4_waveform());
	ui->comboBox_LFOwaveform_4->blockSignals(false);
	
	ui->dial_LFOsymmetry_4->blockSignals(true);
	ui->dial_LFOsymmetry_4->setValue(mod_synth_get_active_lfo_mod_4_symmetry());
	ui->dial_LFOsymmetry_4->blockSignals(false);
	sprintf(text, "%i%c", mod_synth_get_active_lfo_mod_4_symmetry(), '%');
	
	ui->dial_LFOrate_4->blockSignals(true);
	ui->dial_LFOrate_4->setValue(mod_synth_get_active_lfo_mod_4_rate());		
	ui->dial_LFOrate_4->blockSignals(false);
	
	sprintf(text,
		"%.2fHz", 
		mod_synth_log_scale_100_float(mod_synth_get_lfo_min_frequency(), 
			mod_synth_get_lfo_max_frequency(),
			10.0, 
			mod_synth_get_active_lfo_mod_4_rate()));
	
	ui->lineEdit_LFOrate_4->setText(QString(text));
	
	ui->comboBox_LFOwaveform_5->blockSignals(true);
	ui->comboBox_LFOwaveform_5->setCurrentIndex(mod_synth_get_active_lfo_mod_5_waveform());
	ui->comboBox_LFOwaveform_5->blockSignals(false);
	
	ui->dial_LFOsymmetry_5->blockSignals(true);
	ui->dial_LFOsymmetry_5->setValue(mod_synth_get_active_lfo_mod_5_symmetry());
	ui->dial_LFOsymmetry_5->blockSignals(false);
	sprintf(text, "%i%c", mod_synth_get_active_lfo_mod_5_symmetry(), '%');
	
	ui->dial_LFOrate_5->blockSignals(true);
	ui->dial_LFOrate_5->setValue(mod_synth_get_active_lfo_mod_5_rate());		
	ui->dial_LFOrate_5->blockSignals(false);
	
	sprintf(text,
		"%.2fHz", 
		mod_synth_log_scale_100_float(mod_synth_get_lfo_min_frequency(), 
			mod_synth_get_lfo_max_frequency(),
			10.0, 
			mod_synth_get_active_lfo_mod_5_rate()));
	
	ui->lineEdit_LFOrate_5->setText(QString(text));
	
	ui->comboBox_LFOwaveform_6->blockSignals(true);
	ui->comboBox_LFOwaveform_6->setCurrentIndex(mod_synth_get_active_lfo_mod_6_waveform());
	ui->comboBox_LFOwaveform_6->blockSignals(false);
	
	ui->dial_LFOsymmetry_6->blockSignals(true);
	ui->dial_LFOsymmetry_6->setValue(mod_synth_get_active_lfo_mod_6_symmetry());
	ui->dial_LFOsymmetry_6->blockSignals(false);
	sprintf(text, "%i%c", mod_synth_get_active_lfo_mod_6_symmetry(), '%');
	
	ui->dial_LFOrate_6->blockSignals(true);
	ui->dial_LFOrate_6->setValue(mod_synth_get_active_lfo_mod_6_rate());		
	ui->dial_LFOrate_6->blockSignals(false);
	
	sprintf(text,
		"%.2fHz", 
		mod_synth_log_scale_100_float(mod_synth_get_lfo_min_frequency(), 
			mod_synth_get_lfo_max_frequency(),
			10.0, 
			mod_synth_get_active_lfo_mod_6_rate()));
	
	ui->lineEdit_LFOrate_6->setText(QString(text));
}

void Dialog_AnalogSynth::on_lfo1_waveform_combo_changed(int val)
{
	ui->comboBox_LFOwaveform_1->blockSignals(true);
	ui->comboBox_LFOwaveform_1->setCurrentIndex(val);
	ui->comboBox_LFOwaveform_1->blockSignals(false);
	
	lfo1_waveform_entry = val;
	mod_synth_modulator_event_int(_LFO_1_EVENT, _MOD_LFO_WAVEFORM, val);
}

void Dialog_AnalogSynth::on_lfo1_symmetry_dial_changed(int val)
{	
	ui->dial_LFOsymmetry_1->blockSignals(true);
	ui->dial_LFOsymmetry_1->setValue(val);
	ui->dial_LFOsymmetry_1->blockSignals(false);
	
	lfo1_symmetry_entry = val;
	
	ui->spinBox_LFOsymmetry_1->blockSignals(true);
	ui->spinBox_LFOsymmetry_1->setValue(val);		
	ui->spinBox_LFOsymmetry_1->blockSignals(false);
	
	mod_synth_modulator_event_int(_LFO_1_EVENT, _MOD_LFO_SYMMETRY, val);
}

void Dialog_AnalogSynth::on_lfo1_rate_dial_changed(int val)
{
	char text[64];
	
	ui->dial_LFOrate_1->blockSignals(true);
	ui->dial_LFOrate_1->setValue(val);
	ui->dial_LFOrate_1->blockSignals(false);
	
	lfo1_rate_entry = val;
	
	sprintf(text,
		"%.2fHz", 
		mod_synth_log_scale_100_float(mod_synth_get_lfo_min_frequency(), 
			mod_synth_get_lfo_max_frequency(),
			10.0, val));
	
	ui->lineEdit_LFOrate_1->setText(QString(text));
	
	mod_synth_modulator_event_int(_LFO_1_EVENT, _MOD_LFO_RATE, val);
}

void Dialog_AnalogSynth::on_lfo2_waveform_combo_changed(int val)
{
	ui->comboBox_LFOwaveform_2->blockSignals(true);
	ui->comboBox_LFOwaveform_2->setCurrentIndex(val);
	ui->comboBox_LFOwaveform_2->blockSignals(false);
	
	lfo1_waveform_entry = val;
	mod_synth_modulator_event_int(_LFO_2_EVENT, _MOD_LFO_WAVEFORM, val);
}

void Dialog_AnalogSynth::on_lfo2_symmetry_dial_changed(int val)
{	
	ui->dial_LFOsymmetry_2->blockSignals(true);
	ui->dial_LFOsymmetry_2->setValue(val);
	ui->dial_LFOsymmetry_2->blockSignals(false);
	
	lfo2_symmetry_entry = val;
	
	ui->spinBox_LFOsymmetry_2->blockSignals(true);
	ui->spinBox_LFOsymmetry_2->setValue(val);		
	ui->spinBox_LFOsymmetry_2->blockSignals(false);
	
	mod_synth_modulator_event_int(_LFO_2_EVENT, _MOD_LFO_SYMMETRY, val);
}

void Dialog_AnalogSynth::on_lfo2_rate_dial_changed(int val)
{
	char text[64];
	
	ui->dial_LFOrate_2->blockSignals(true);
	ui->dial_LFOrate_2->setValue(val);
	ui->dial_LFOrate_2->blockSignals(false);
	
	lfo2_rate_entry = val;
	
	sprintf(text,
		"%.2fHz", 
		mod_synth_log_scale_100_float(mod_synth_get_lfo_min_frequency(), 
			mod_synth_get_lfo_max_frequency(),
			10.0,
			val));
	
	ui->lineEdit_LFOrate_2->setText(QString(text));
	
	mod_synth_modulator_event_int(_LFO_2_EVENT, _MOD_LFO_RATE, val);
}

void Dialog_AnalogSynth::on_lfo3_waveform_combo_changed(int val)
{
	ui->comboBox_LFOwaveform_3->blockSignals(true);
	ui->comboBox_LFOwaveform_3->setCurrentIndex(val);
	ui->comboBox_LFOwaveform_3->blockSignals(false);
	
	lfo3_waveform_entry = val;
	mod_synth_modulator_event_int(_LFO_3_EVENT, _MOD_LFO_WAVEFORM, val);
}

void Dialog_AnalogSynth::on_lfo3_symmetry_dial_changed(int val)
{	
	ui->dial_LFOsymmetry_3->blockSignals(true);
	ui->dial_LFOsymmetry_3->setValue(val);
	ui->dial_LFOsymmetry_3->blockSignals(false);
	
	lfo3_symmetry_entry = val;
	
	ui->spinBox_LFOsymmetry_3->blockSignals(true);
	ui->spinBox_LFOsymmetry_3->setValue(val);		
	ui->spinBox_LFOsymmetry_3->blockSignals(false);
	
	mod_synth_modulator_event_int(_LFO_3_EVENT, _MOD_LFO_SYMMETRY, val);
}

void Dialog_AnalogSynth::on_lfo3_rate_dial_changed(int val)
{
	char text[64];
	
	ui->dial_LFOrate_3->blockSignals(true);
	ui->dial_LFOrate_3->setValue(val);
	ui->dial_LFOrate_3->blockSignals(false);
	
	lfo1_rate_entry = val;
	
	sprintf(text,
		"%.2fHz", 
		mod_synth_log_scale_100_float(mod_synth_get_lfo_min_frequency(), 
			mod_synth_get_lfo_max_frequency(),
			10.0,
			val));
	
	ui->lineEdit_LFOrate_3->setText(QString(text));
	
	mod_synth_modulator_event_int(_LFO_3_EVENT, _MOD_LFO_RATE, val);
}

void Dialog_AnalogSynth::on_lfo4_waveform_combo_changed(int val)
{
	ui->comboBox_LFOwaveform_4->blockSignals(true);
	ui->comboBox_LFOwaveform_4->setCurrentIndex(val);
	ui->comboBox_LFOwaveform_4->blockSignals(false);
	
	lfo4_waveform_entry = val;
	mod_synth_modulator_event_int(_LFO_4_EVENT, _MOD_LFO_WAVEFORM, val);
}

void Dialog_AnalogSynth::on_lfo4_symmetry_dial_changed(int val)
{	
	ui->dial_LFOsymmetry_4->blockSignals(true);
	ui->dial_LFOsymmetry_4->setValue(val);
	ui->dial_LFOsymmetry_4->blockSignals(false);
	
	lfo4_symmetry_entry = val;
	
	ui->spinBox_LFOsymmetry_4->blockSignals(true);
	ui->spinBox_LFOsymmetry_4->setValue(val);		
	ui->spinBox_LFOsymmetry_4->blockSignals(false);
	
	mod_synth_modulator_event_int(_LFO_4_EVENT, _MOD_LFO_SYMMETRY, val);
}

void Dialog_AnalogSynth::on_lfo4_rate_dial_changed(int val)
{
	char text[64];
	
	ui->dial_LFOrate_4->blockSignals(true);
	ui->dial_LFOrate_4->setValue(val);
	ui->dial_LFOrate_4->blockSignals(false);
	
	lfo1_rate_entry = val;
	
	sprintf(text,
		"%.2fHz", 
		mod_synth_log_scale_100_float(mod_synth_get_lfo_min_frequency(), 
			mod_synth_get_lfo_max_frequency(),
			10.0,
			val));
	
	ui->lineEdit_LFOrate_4->setText(QString(text));
	
	mod_synth_modulator_event_int(_LFO_4_EVENT, _MOD_LFO_RATE, val);
}

void Dialog_AnalogSynth::on_lfo5_waveform_combo_changed(int val)
{
	ui->comboBox_LFOwaveform_5->blockSignals(true);
	ui->comboBox_LFOwaveform_5->setCurrentIndex(val);
	ui->comboBox_LFOwaveform_5->blockSignals(false);
	
	lfo5_waveform_entry = val;
	mod_synth_modulator_event_int(_LFO_5_EVENT, _MOD_LFO_WAVEFORM, val);
}

void Dialog_AnalogSynth::on_lfo5_symmetry_dial_changed(int val)
{	
	ui->dial_LFOsymmetry_5->blockSignals(true);
	ui->dial_LFOsymmetry_5->setValue(val);
	ui->dial_LFOsymmetry_5->blockSignals(false);
	
	lfo5_symmetry_entry = val;
	
	ui->spinBox_LFOsymmetry_5->blockSignals(true);
	ui->spinBox_LFOsymmetry_5->setValue(val);		
	ui->spinBox_LFOsymmetry_5->blockSignals(false);
	
	mod_synth_modulator_event_int(_LFO_5_EVENT, _MOD_LFO_SYMMETRY, val);
}

void Dialog_AnalogSynth::on_lfo5_rate_dial_changed(int val)
{
	char text[64];
	
	ui->dial_LFOrate_5->blockSignals(true);
	ui->dial_LFOrate_5->setValue(val);
	ui->dial_LFOrate_5->blockSignals(false);
	
	lfo5_rate_entry = val;
	
	sprintf(text,
		"%.2fHz", 
		mod_synth_log_scale_100_float(mod_synth_get_lfo_min_frequency(), 
			mod_synth_get_lfo_max_frequency(),
			10.0,
			val));
	
	ui->lineEdit_LFOrate_5->setText(QString(text));
	
	mod_synth_modulator_event_int(_LFO_5_EVENT, _MOD_LFO_RATE, val);
}

void Dialog_AnalogSynth::on_lfo6_waveform_combo_changed(int val)
{
	ui->comboBox_LFOwaveform_6->blockSignals(true);
	ui->comboBox_LFOwaveform_6->setCurrentIndex(val);
	ui->comboBox_LFOwaveform_6->blockSignals(false);
	
	lfo6_waveform_entry = val;
	mod_synth_modulator_event_int(_LFO_6_EVENT, _MOD_LFO_WAVEFORM, val);
}

void Dialog_AnalogSynth::on_lfo6_symmetry_dial_changed(int val)
{	
	ui->dial_LFOsymmetry_6->blockSignals(true);
	ui->dial_LFOsymmetry_6->setValue(val);
	ui->dial_LFOsymmetry_6->blockSignals(false);
	
	lfo6_symmetry_entry = val;
	
	ui->spinBox_LFOsymmetry_6->blockSignals(true);
	ui->spinBox_LFOsymmetry_6->setValue(val);		
	ui->spinBox_LFOsymmetry_6->blockSignals(false);
	
	mod_synth_modulator_event_int(_LFO_6_EVENT, _MOD_LFO_SYMMETRY, val);
}

void Dialog_AnalogSynth::on_lfo6_rate_dial_changed(int val)
{
	char text[64];
	
	ui->dial_LFOrate_6->blockSignals(true);
	ui->dial_LFOrate_6->setValue(val);
	ui->dial_LFOrate_6->blockSignals(false);
	
	lfo6_rate_entry = val;
	
	sprintf(text,
		"%.2fHz", 
		mod_synth_log_scale_100_float(mod_synth_get_lfo_min_frequency(), 
			mod_synth_get_lfo_max_frequency(),
			10.0,
			val));
	
	ui->lineEdit_LFOrate_6->setText(QString(text));
	
	mod_synth_modulator_event_int(_LFO_6_EVENT, _MOD_LFO_RATE, val);
}


