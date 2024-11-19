/**
* @file		Dialog_AnalogSynthFiltersAmpsTab.h
*	@author		Nahum Budin
*	@date		18-Nov-2024
*	@version	1.0
*
*	@brief		Analog Synthesizer instrument Filters and Output Amplifiers Tab handling
*				
*	History:
*			Based on the AdjModSynth project ver 1.1 16-Jan-2021 
*
*/

#include "Dialog_AnalogSynth.h"
#include "ui_Dialog_AnalogSynth.h"
#include "utils.h"

#include "libAdjRaspi5SynthAPI.h"

void Dialog_AnalogSynth::set_filters_amps_signals_connections()
{
	
}

void Dialog_AnalogSynth::init_filters_amps_combboxes_and_labels()
{
	string_filter_bands_list.append("Lowpass");
	string_filter_bands_list.append("Highpass");
	string_filter_bands_list.append("Bandpass");
	string_filter_bands_list.append("Allpass");
	
	ui->comboBox_FilterBand_1->blockSignals(true);
	ui->comboBox_FilterBand_1->addItems(string_filter_bands_list);
	ui->comboBox_FilterBand_1->blockSignals(false);
	
	ui->comboBox_FilterBand_2->blockSignals(true);
	ui->comboBox_FilterBand_2->addItems(string_filter_bands_list);
	ui->comboBox_FilterBand_2->blockSignals(false);
	
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
	
	ui->comboBox_FilterFreqModAdsr_1->blockSignals(true);
	ui->comboBox_FilterFreqModAdsr_1->addItems(string_adsr_values);
	ui->comboBox_FilterFreqModAdsr_1->blockSignals(false);

	ui->comboBox_FilterFreqModLfo_1->blockSignals(true);
	ui->comboBox_FilterFreqModLfo_1->addItems(string_lfo_values);
	ui->comboBox_FilterFreqModLfo_1->blockSignals(false);
	
	ui->comboBox_FilterFreqModAdsr_2->blockSignals(true);
	ui->comboBox_FilterFreqModAdsr_2->addItems(string_adsr_values);
	ui->comboBox_FilterFreqModAdsr_2->blockSignals(false);

	ui->comboBox_FilterFreqModLfo_2->blockSignals(true);
	ui->comboBox_FilterFreqModLfo_2->addItems(string_lfo_values);
	ui->comboBox_FilterFreqModLfo_2->blockSignals(false);
	
	ui->comboBox_AmpPanModLfo_1->blockSignals(true);
	ui->comboBox_AmpPanModLfo_1->addItem("-----");
	ui->comboBox_AmpPanModLfo_1->addItem("LFO 1");
	ui->comboBox_AmpPanModLfo_1->addItem("LFO 2");
	ui->comboBox_AmpPanModLfo_1->addItem("LFO 3");
	ui->comboBox_AmpPanModLfo_1->addItem("LFO 4");
	ui->comboBox_AmpPanModLfo_1->addItem("LFO 5");
	ui->comboBox_AmpPanModLfo_1->blockSignals(false);
		
	ui->comboBox_AmpPanModLfo_2->blockSignals(true);
	ui->comboBox_AmpPanModLfo_2->addItem("-----");
	ui->comboBox_AmpPanModLfo_2->addItem("LFO 1");
	ui->comboBox_AmpPanModLfo_2->addItem("LFO 2");
	ui->comboBox_AmpPanModLfo_2->addItem("LFO 3");
	ui->comboBox_AmpPanModLfo_2->addItem("LFO 4");
	ui->comboBox_AmpPanModLfo_2->addItem("LFO 5");
	ui->comboBox_AmpPanModLfo_2->blockSignals(false);
}

void Dialog_AnalogSynth::filters_update()
{
	
}

void Dialog_AnalogSynth::amps_update()
{
	
}


