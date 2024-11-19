/**
* @file		Dialog_AnalogSynthPadTab.h
*	@author		Nahum Budin
*	@date		14-Nov-2024
*	@version	1.0
*
*	@brief		Analog Synthesizer instrument PADSynth Synthesizer Tab handling
*				
*	History:
*			Based on the AdjModSynth project ver 1.1 16-Jan-2021 
*
*/

#include "Dialog_AnalogSynth.h"
#include "ui_Dialog_AnalogSynth.h"
#include "utils.h"

#include "libAdjRaspi5SynthAPI.h"

void Dialog_AnalogSynth::set_pad_signals_connections()
{
	connect(ui->checkBox_PadActive,
		SIGNAL(toggled(bool)),
		this,
		SLOT(on_pad_enable_checkbox_changed(bool)));

	connect(ui->pushButton_PadGenerate,
		SIGNAL(clicked()),
		this,
		SLOT(on_pad_generate_pushbutton_clicked()));

	connect(ui->comboBox_PadTuneOctave,
		SIGNAL(currentIndexChanged(int)),
		this,
		SLOT(on_pad_detune_octave_combobox_changed(int)));

	connect(ui->comboBox_PadTuneSemitones,
		SIGNAL(currentIndexChanged(int)),
		this,
		SLOT(on_pad_detune_seminotes_combobox_changed(int)));

	connect(ui->comboBox_PadTuneCents,
		SIGNAL(currentIndexChanged(int)),
		this,
		SLOT(on_pad_detune_cents_combobox_changed(int)));

	connect(ui->dial_PadSendFilter1,
		SIGNAL(valueChanged(int)),
		this,
		SLOT(on_pad_send_filter1_dial_changed(int)));

	connect(ui->dial_PadSendFilter2,
		SIGNAL(valueChanged(int)),
		this,
		SLOT(on_pad_send_filter2_dial_changed(int)));

	connect(ui->comboBox_PadFreqModLFO,
		SIGNAL(currentIndexChanged(int)),
		this,
		SLOT(on_pad_freq_mod_lfo_combobox_changed(int)));

	connect(ui->dial_PadFreqModLFOLevel,
		SIGNAL(valueChanged(int)),
		this,
		SLOT(on_pad_freq_mod_lfo_level_dial_changed(int)));

	connect(ui->comboBox_PadFreqModAdsr,
		SIGNAL(currentIndexChanged(int)),
		this,
		SLOT(on_pad_freq_mod_env_combobox_canged(int)));

	connect(ui->dial_PadFreqModAdsrLevel,
		SIGNAL(valueChanged(int)),
		this,
		SLOT(on_pad_freq_mod_env_level_dial_changed(int)));

	connect(ui->comboBox_PadAmpModLFO,
		SIGNAL(currentIndexChanged(int)),
		this,
		SLOT(on_pad_amp_mod_lfo_combobox_changed(int)));

	connect(ui->dial_PadAmpModLFOLevel,
		SIGNAL(valueChanged(int)),
		this,
		SLOT(on_pad_amp_mod_lfo_level_dial_changed(int)));

	connect(ui->comboBox_PadAmpModAdsr,
		SIGNAL(currentIndexChanged(int)),
		this,
		SLOT(on_pad_amp_mod_env_combobox_changed(int)));

	connect(ui->dial_PadAmpModAdsrLevel,
		SIGNAL(valueChanged(int)),
		this,
		SLOT(on_pad_amp_mod_env_level_dial_changed(int)));

	connect(ui->comboBox_PadBaseNote,
		SIGNAL(currentIndexChanged(int)),
		this,
		SLOT(on_pad_base_note_combobox_changed(int)));

	connect(ui->comboBox_PadQuality,
		SIGNAL(currentIndexChanged(int)),
		this,
		SLOT(on_pad_quality_combobox_changed(int)));

	connect(ui->comboBox_PadShape,
		SIGNAL(currentIndexChanged(int)),
		this,
		SLOT(on_pad_shape_combobox_changed(int)));

	connect(ui->comboBox_PadShapeCutoff,
		SIGNAL(currentIndexChanged(int)),
		this,
		SLOT(on_pad_shape_cutoff_combobox_changed(int)));

	connect(ui->horizontalSlider_PadBaseWidth,
		SIGNAL(valueChanged(int)),
		this,
		SLOT(on_pad_base_width_slider_changed(int)));

	connect(ui->verticalSlider_PadHarmony_1,
		SIGNAL(valueChanged(int)),
		this,
		SLOT(on_pad_harmony1_level_slider_changed(int)));

	connect(ui->verticalSlider_PadHarmony_2,
		SIGNAL(valueChanged(int)),
		this,
		SLOT(on_pad_harmony2_level_slider_changed(int)));

	connect(ui->verticalSlider_PadHarmony_3,
		SIGNAL(valueChanged(int)),
		this,
		SLOT(on_pad_harmony3_level_slider_changed(int)));

	connect(ui->verticalSlider_PadHarmony_4,
		SIGNAL(valueChanged(int)),
		this,
		SLOT(on_pad_harmony4_level_slider_changed(int)));

	connect(ui->verticalSlider_PadHarmony_5,
		SIGNAL(valueChanged(int)),
		this,
		SLOT(on_pad_harmony5_level_slider_changed(int)));

	connect(ui->verticalSlider_PadHarmony_6,
		SIGNAL(valueChanged(int)),
		this,
		SLOT(on_pad_harmony6_level_slider_changed(int)));

	connect(ui->verticalSlider_PadHarmony_7,
		SIGNAL(valueChanged(int)),
		this,
		SLOT(on_pad_harmony7_level_slider_changed(int)));

	connect(ui->verticalSlider_PadHarmony_8,
		SIGNAL(valueChanged(int)),
		this,
		SLOT(on_pad_harmony8_level_slider_changed(int)));
	
	connect(ui->verticalSlider_PadHarmony_9,
		SIGNAL(valueChanged(int)),
		this,
		SLOT(on_pad_harmony9_level_slider_changed(int)));
	
	connect(ui->verticalSlider_PadHarmony_10,
		SIGNAL(valueChanged(int)),
		this,
		SLOT(on_pad_harmony10_level_slider_changed(int)));

	connect(ui->verticalSlider_PadHarmonyDetune,
		SIGNAL(valueChanged(int)),
		this,
		SLOT(on_pad_harmonies_detune_slider_changed(int)));
}

void Dialog_AnalogSynth::init_pad_combboxes_and_labels()
{
	string_pad_qualities_list.append("32K");
	string_pad_qualities_list.append("64K");
	string_pad_qualities_list.append("128K");
	string_pad_qualities_list.append("256K");
	string_pad_qualities_list.append("512K");
	string_pad_qualities_list.append("1024K");
	
	ui->comboBox_PadQuality->blockSignals(true);
	ui->comboBox_PadQuality->addItems(string_pad_qualities_list);
	ui->comboBox_PadQuality->blockSignals(false);

	string_pad_base_notes_list.append("C2");
	string_pad_base_notes_list.append("G2");
	string_pad_base_notes_list.append("C3");
	string_pad_base_notes_list.append("G3");
	string_pad_base_notes_list.append("C4");
	string_pad_base_notes_list.append("G4");
	string_pad_base_notes_list.append("C5");
	string_pad_base_notes_list.append("G5");
	string_pad_base_notes_list.append("C6");
	string_pad_base_notes_list.append("G6");
	
	ui->comboBox_PadBaseNote->blockSignals(true);
	ui->comboBox_PadBaseNote->addItems(string_pad_base_notes_list);
	ui->comboBox_PadBaseNote->blockSignals(false);

	string_pad_shapes_list.append("Rectangular");
	string_pad_shapes_list.append("Gaussian");
	string_pad_shapes_list.append("Double Exp.");
	
	ui->comboBox_PadShape->blockSignals(true);
	ui->comboBox_PadShape->addItems(string_pad_shapes_list);
	ui->comboBox_PadShape->blockSignals(false);

	string_pad_shape_cutoffs_list.append("Full");
	string_pad_shape_cutoffs_list.append("Upper");
	string_pad_shape_cutoffs_list.append("Lower");	
	
	ui->comboBox_PadShapeCutoff->blockSignals(true);
	ui->comboBox_PadShapeCutoff->addItems(string_pad_shape_cutoffs_list);
	ui->comboBox_PadShapeCutoff->blockSignals(false);
	
	ui->comboBox_PadTuneOctave->blockSignals(true);
	ui->comboBox_PadTuneSemitones->blockSignals(true);
	ui->comboBox_PadTuneCents->blockSignals(true);
	for (int i = mod_synth_get_osc_detune_min_octave(); i <= mod_synth_get_osc_detune_max_octave(); i++)
	{
		ui->comboBox_PadTuneOctave->addItem(QString::number(i));
	}

	for (int i = mod_synth_get_osc_detune_min_semitones(); i <= mod_synth_get_osc_detune_max_semitones(); i++)
	{
		ui->comboBox_PadTuneSemitones->addItem(QString::number(i));
	}

	for (int i = 4 * mod_synth_get_osc_detune_min_cents(); i <= 4 * mod_synth_get_osc_detune_max_cents(); i++)
	{
		// 0.25 steps
		ui->comboBox_PadTuneCents->addItem(QString::number(i / 4.f));
	}

	ui->comboBox_PadTuneOctave->blockSignals(false);
	ui->comboBox_PadTuneSemitones->blockSignals(false);
	ui->comboBox_PadTuneCents->blockSignals(false);
	
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
	
	ui->comboBox_PadFreqModAdsr->blockSignals(true);
	ui->comboBox_PadFreqModAdsr->addItems(string_adsr_values);
	ui->comboBox_PadFreqModAdsr->blockSignals(false);

	ui->comboBox_PadFreqModLFO->blockSignals(true);
	ui->comboBox_PadFreqModLFO->addItems(string_lfo_values);
	ui->comboBox_PadFreqModLFO->blockSignals(false);

	ui->comboBox_PadAmpModAdsr->blockSignals(true);
	ui->comboBox_PadAmpModAdsr->addItems(string_adsr_values);
	ui->comboBox_PadAmpModAdsr->blockSignals(false);

	ui->comboBox_PadAmpModLFO->blockSignals(true);
	ui->comboBox_PadAmpModLFO->addItems(string_lfo_values);
	ui->comboBox_PadAmpModLFO->blockSignals(false);
}

void Dialog_AnalogSynth::pad_update()
{
	pad_enabled = mod_synth_get_active_pad_enable_state();
	
	ui->checkBox_PadActive->blockSignals(true);
	ui->checkBox_PadActive->setChecked(pad_enabled);
	ui->checkBox_PadActive->blockSignals(false);
	
	if (pad_enabled)
	{
		ui->frame_PAD_AmpMod->setEnabled(true);
		ui->frame_PAD_FreqMod->setEnabled(true);
		ui->frame_PAD_Haromonys1_6->setEnabled(true);
		ui->frame__PAD_Haromonys7_10->setEnabled(true);
		ui->frame_PAD_Profile->setEnabled(true);
		ui->frame_PAD_SendFiltersTuneOffset->setEnabled(true);
	}
	else
	{
		ui->frame_PAD_AmpMod->setEnabled(false);
		ui->frame_PAD_FreqMod->setEnabled(false);
		ui->frame_PAD_Haromonys1_6->setEnabled(false);
		ui->frame__PAD_Haromonys7_10->setEnabled(false);
		ui->frame_PAD_Profile->setEnabled(false);
		ui->frame_PAD_SendFiltersTuneOffset->setEnabled(false);
	}

	ui->comboBox_PadTuneOctave->blockSignals(true);
	ui->comboBox_PadTuneOctave->setCurrentIndex(mod_synth_get_active_pad_detune_octave() - _OSC_DETUNE_MIN_OCTAVE);
	ui->comboBox_PadTuneOctave->blockSignals(false);

	ui->comboBox_PadTuneSemitones->blockSignals(true);
	ui->comboBox_PadTuneSemitones->setCurrentIndex(mod_synth_get_active_pad_detune_semitones() - _OSC_DETUNE_MIN_SEMITONES);
	ui->comboBox_PadTuneSemitones->blockSignals(false);

	ui->comboBox_PadTuneCents->blockSignals(true);
	ui->comboBox_PadTuneCents->setCurrentIndex(mod_synth_get_active_pad_detune_cents() - _OSC_DETUNE_MIN_CENTS * 4.f);
	ui->comboBox_PadTuneCents->blockSignals(false);

	ui->dial_PadSendFilter1->blockSignals(true);
	ui->dial_PadSendFilter1->setValue(mod_synth_get_active_pad_send_filter_1());
	ui->dial_PadSendFilter1->blockSignals(false);

	ui->dial_PadSendFilter2->blockSignals(true);
	ui->dial_PadSendFilter2->setValue(mod_synth_get_active_pad_send_filter_2());
	ui->dial_PadSendFilter2->blockSignals(false);

	ui->comboBox_PadFreqModLFO->blockSignals(true);
	ui->comboBox_PadFreqModLFO->setCurrentIndex(mod_synth_get_active_pad_freq_mod_lfo());
	ui->comboBox_PadFreqModLFO->blockSignals(false);

	ui->dial_PadFreqModLFOLevel->blockSignals(true);
	ui->dial_PadFreqModLFOLevel->setValue(mod_synth_get_active_pad_freq_mod_lfo_level());
	ui->dial_PadFreqModLFOLevel->blockSignals(false);

	ui->comboBox_PadFreqModAdsr->blockSignals(true);
	ui->comboBox_PadFreqModAdsr->setCurrentIndex(mod_synth_get_active_pad_freq_mod_env());
	ui->comboBox_PadFreqModAdsr->blockSignals(false);

	ui->dial_PadFreqModAdsrLevel->blockSignals(true);
	ui->dial_PadFreqModAdsrLevel->setValue(mod_synth_get_active_pad_freq_mod_env_level());
	ui->dial_PadFreqModAdsrLevel->blockSignals(false);

	ui->comboBox_PadAmpModLFO->blockSignals(true);
	ui->comboBox_PadAmpModLFO->setCurrentIndex(mod_synth_get_active_pad_amp_mod_lfo());
	ui->comboBox_PadAmpModLFO->blockSignals(false);

	ui->dial_PadAmpModLFOLevel->blockSignals(true);
	ui->dial_PadAmpModLFOLevel->setValue(mod_synth_get_active_pad_amp_mod_lfo_level());
	ui->dial_PadAmpModLFOLevel->blockSignals(false);

	ui->comboBox_PadAmpModAdsr->blockSignals(true);
	ui->comboBox_PadAmpModAdsr->setCurrentIndex(mod_synth_get_active_pad_amp_mod_env());
	ui->comboBox_PadAmpModAdsr->blockSignals(false);

	ui->dial_PadAmpModAdsrLevel->blockSignals(true);
	ui->dial_PadAmpModAdsrLevel->setValue(mod_synth_get_active_pad_amp_mod_env_level());
	ui->dial_PadAmpModAdsrLevel->blockSignals(false);

	ui->comboBox_PadQuality->blockSignals(true);
	ui->comboBox_PadQuality->setCurrentIndex(mod_synth_get_active_pad_quality());
	ui->comboBox_PadQuality->blockSignals(false);

	ui->comboBox_PadShape->blockSignals(true);
	ui->comboBox_PadShape->setCurrentIndex(mod_synth_get_active_pad_shape());
	ui->comboBox_PadShape->blockSignals(false);

	ui->comboBox_PadShapeCutoff->blockSignals(true);
	ui->comboBox_PadShapeCutoff->setCurrentIndex(mod_synth_get_active_pad_shape_cutoff());
	ui->comboBox_PadShapeCutoff->blockSignals(false);

	ui->comboBox_PadBaseNote->blockSignals(true);
	ui->comboBox_PadBaseNote->setCurrentIndex(mod_synth_get_active_pad_base_note());
	ui->comboBox_PadBaseNote->blockSignals(false);

	ui->horizontalSlider_PadBaseWidth->blockSignals(true);
	ui->horizontalSlider_PadBaseWidth->setValue(mod_synth_get_active_pad_base_width());
	ui->horizontalSlider_PadBaseWidth->blockSignals(false);

	ui->verticalSlider_PadHarmony_1->blockSignals(true);
	ui->verticalSlider_PadHarmony_1->setValue(mod_synth_get_active_pad_harmony_level(0));
	ui->verticalSlider_PadHarmony_1->blockSignals(false);

	ui->verticalSlider_PadHarmony_2->blockSignals(true);
	ui->verticalSlider_PadHarmony_2->setValue(mod_synth_get_active_pad_harmony_level(1));
	ui->verticalSlider_PadHarmony_2->blockSignals(false);

	ui->verticalSlider_PadHarmony_3->blockSignals(true);
	ui->verticalSlider_PadHarmony_3->setValue(mod_synth_get_active_pad_harmony_level(2));
	ui->verticalSlider_PadHarmony_3->blockSignals(false);

	ui->verticalSlider_PadHarmony_4->blockSignals(true);
	ui->verticalSlider_PadHarmony_4->setValue(mod_synth_get_active_pad_harmony_level(3));
	ui->verticalSlider_PadHarmony_4->blockSignals(false);

	ui->verticalSlider_PadHarmony_5->blockSignals(true);
	ui->verticalSlider_PadHarmony_5->setValue(mod_synth_get_active_pad_harmony_level(4));
	ui->verticalSlider_PadHarmony_5->blockSignals(false);

	ui->verticalSlider_PadHarmony_6->blockSignals(true);
	ui->verticalSlider_PadHarmony_6->setValue(mod_synth_get_active_pad_harmony_level(5));
	ui->verticalSlider_PadHarmony_6->blockSignals(false);

	ui->verticalSlider_PadHarmony_7->blockSignals(true);
	ui->verticalSlider_PadHarmony_7->setValue(mod_synth_get_active_pad_harmony_level(6));
	ui->verticalSlider_PadHarmony_7->blockSignals(false);

	ui->verticalSlider_PadHarmony_8->blockSignals(true);
	ui->verticalSlider_PadHarmony_8->setValue(mod_synth_get_active_pad_harmony_level(7));
	ui->verticalSlider_PadHarmony_8->blockSignals(false);
	
	ui->verticalSlider_PadHarmony_9->blockSignals(true);
	ui->verticalSlider_PadHarmony_9->setValue(mod_synth_get_active_pad_harmony_level(8));
	ui->verticalSlider_PadHarmony_9->blockSignals(false);
	
	ui->verticalSlider_PadHarmony_10->blockSignals(true);
	ui->verticalSlider_PadHarmony_10->setValue(mod_synth_get_active_pad_harmony_level(9));
	ui->verticalSlider_PadHarmony_10->blockSignals(false);
	
	ui->verticalSlider_PadHarmonyDetune->blockSignals(true);
	ui->verticalSlider_PadHarmonyDetune->setValue(mod_synth_get_active_pad_harmony_detune());
	ui->verticalSlider_PadHarmonyDetune->blockSignals(false);
	
	ui->spinBox_PadHarmony_1->blockSignals(true);
	ui->spinBox_PadHarmony_1->setValue(mod_synth_get_active_pad_harmony_level(0));
	ui->spinBox_PadHarmony_1->blockSignals(false);

	ui->spinBox_PadHarmony_2->blockSignals(true);
	ui->spinBox_PadHarmony_2->setValue(mod_synth_get_active_pad_harmony_level(1));
	ui->spinBox_PadHarmony_2->blockSignals(false);

	ui->spinBox_PadHarmony_3->blockSignals(true);
	ui->spinBox_PadHarmony_3->setValue(mod_synth_get_active_pad_harmony_level(2));
	ui->spinBox_PadHarmony_3->blockSignals(false);

	ui->spinBox_PadHarmony_4->blockSignals(true);
	ui->spinBox_PadHarmony_4->setValue(mod_synth_get_active_pad_harmony_level(3));
	ui->spinBox_PadHarmony_4->blockSignals(false);

	ui->spinBox_PadHarmony_5->blockSignals(true);
	ui->spinBox_PadHarmony_5->setValue(mod_synth_get_active_pad_harmony_level(4));
	ui->spinBox_PadHarmony_5->blockSignals(false);

	ui->spinBox_PadHarmony_6->blockSignals(true);
	ui->spinBox_PadHarmony_6->setValue(mod_synth_get_active_pad_harmony_level(5));
	ui->spinBox_PadHarmony_6->blockSignals(false);

	ui->spinBox_PadHarmony_7->blockSignals(true);
	ui->spinBox_PadHarmony_7->setValue(mod_synth_get_active_pad_harmony_level(6));
	ui->spinBox_PadHarmony_7->blockSignals(false);

	ui->spinBox_PadHarmony_8->blockSignals(true);
	ui->spinBox_PadHarmony_8->setValue(mod_synth_get_active_pad_harmony_level(7));
	ui->spinBox_PadHarmony_8->blockSignals(false);
	
	ui->spinBox_PadHarmony_9->blockSignals(true);
	ui->spinBox_PadHarmony_9->setValue(mod_synth_get_active_pad_harmony_level(8));
	ui->spinBox_PadHarmony_9->blockSignals(false);
	
	ui->spinBox_PadHarmony_10->blockSignals(true);
	ui->spinBox_PadHarmony_10->setValue(mod_synth_get_active_pad_harmony_level(9));
	ui->spinBox_PadHarmony_10->blockSignals(false);
	
	ui->spinBox_PadHarmonyDetune->blockSignals(true);
	ui->spinBox_PadHarmonyDetune->setValue(mod_synth_get_active_pad_harmony_detune());
	ui->spinBox_PadHarmonyDetune->blockSignals(false);
	
	update_profile_plot = true;
	update_spectrum_plot = true;
}

void Dialog_AnalogSynth::pad_setup_profile_plot(QCustomPlot *profilePlot)
{
	if (update_profile_plot && mod_synth_get_pad_base_harmony_profile())
	{
		// add two new graphs and set their look:
		QPen pen;
		pen.setStyle(Qt::SolidLine);
		pen.setWidth(3);
		pen.setColor(Qt::blue);
		profilePlot->addGraph();
		profilePlot->graph(0)->setPen(pen);
		profilePlot->addGraph();

		profilePlot->setBackground(QBrush(QColor("#929292")));
		
		//		customPlot->graph(1)->setPen(QPen(Qt::red));  // line color red for second graph
		QVector<double> x(mod_synth_get_pad_base_harmony_profile_size() + 1), y0(mod_synth_get_pad_base_harmony_profile_size() + 1);
		
		for (int i = 0; i < mod_synth_get_pad_base_harmony_profile_size(); ++i)
		{
			x[i] = i;
			y0[i] = *(mod_synth_get_pad_base_harmony_profile() + i);
		}
		profilePlot->xAxis->setVisible(false);
		profilePlot->xAxis->setTickLabels(false);
		profilePlot->yAxis->setVisible(false);
		profilePlot->yAxis->setTickLabels(false);
		profilePlot->graph(0)->setData(x, y0);
		// let the ranges scale themselves so graph 0 fits perfectly in the visible area:
		profilePlot->graph(0)->rescaleAxes();
	}
}

void Dialog_AnalogSynth::pad_setup_spectrum_plot(QCustomPlot *spectrumPlot)
{
	const int width = 12;
	float sum;
	
	if (update_spectrum_plot && (mod_synth_get_pad_spectrum() /*!= NULL*/))
	{
		// add two new graphs and set their look:
		QPen pen;
		pen.setStyle(Qt::SolidLine);
		pen.setWidth(3);
		pen.setColor(Qt::blue);
		spectrumPlot->addGraph();
		spectrumPlot->graph(0)->setPen(pen);
		spectrumPlot->addGraph();

		spectrumPlot->setBackground(QBrush(QColor("#929292")));
		
		int spectrumSize = mod_synth_get_pad_spectrum_size();
		int step = spectrumSize / 1024;
		QVector<double> x(1024), y0(1024);
		for (int i = 0; i < 1024; ++i)
		{
			x[i] = i;
			sum = 0;
			for (int j = -width / 2; j < width / 2 + 1; j++)
			{
				if (((i * step / width + j) >= 0) && ((i * step / width + j) < spectrumSize))
				{
					sum += *(mod_synth_get_pad_spectrum() + i * step / width + j);
				}
			}
			y0[i] = sum / width;
			//			y0[i] = *(mod_synth_get_pad_spectrum() + i * step / width );   //  /2 no such high freq
		}
		spectrumPlot->xAxis->setVisible(false);
		spectrumPlot->xAxis->setTickLabels(false);
		spectrumPlot->yAxis->setVisible(false);
		spectrumPlot->yAxis->setTickLabels(false);
		spectrumPlot->graph(0)->setData(x, y0);
		// let the ranges scale themselves so graph 0 fits perfectly in the visible area:
		spectrumPlot->graph(0)->rescaleAxes();
	}
}

void Dialog_AnalogSynth::pad_replot_profile()
{
	mod_synth_pad_event_int(_PAD_1_EVENT, _PAD_GENERATE, 1);
	pad_setup_profile_plot(ui->widget_PadPlotProfile);
	ui->widget_PadPlotProfile->replot();
}

void Dialog_AnalogSynth::pad_replot_spectrum()
{
	pad_setup_spectrum_plot(ui->widget_PadPlotSpectrum);
	ui->widget_PadPlotSpectrum->replot();
}

void Dialog_AnalogSynth::on_pad_enable_checkbox_changed(bool val)
{
	ui->checkBox_PadActive->blockSignals(true);
	
	if (val)
	{
		ui->checkBox_PadActive->setCheckState(Qt::Checked);
	}
	else
	{
		ui->checkBox_PadActive->setCheckState(Qt::Unchecked);
	}
	
	ui->checkBox_PadActive->blockSignals(false);
	
	pad_enabled = val;
	
	mod_synth_pad_event_bool(_PAD_1_EVENT, _PAD_ENABLE, val);
	
	pad_update();
	
	/* Set focus back on the Dialog */
	this->setFocus(Qt::ActiveWindowFocusReason);
}

void Dialog_AnalogSynth::on_pad_detune_octave_combobox_changed(int val)
{
	ui->comboBox_PadTuneOctave->blockSignals(true);
	ui->comboBox_PadTuneOctave->setCurrentIndex(val);
	ui->comboBox_PadTuneOctave->blockSignals(false);
	
	pad_tune_octave = val;
	mod_synth_pad_event_int(_PAD_1_EVENT, _PAD_DETUNE_OCTAVE, val);
	
	/* Set focus back on the Dialog */
	this->setFocus(Qt::ActiveWindowFocusReason);
}

void Dialog_AnalogSynth::on_pad_detune_semitones_combobox_changed(int val)
{
	ui->comboBox_PadTuneSemitones->blockSignals(true);
	ui->comboBox_PadTuneSemitones->setCurrentIndex(val);
	ui->comboBox_PadTuneSemitones->blockSignals(false);
	
	pad_tune_semitones = val;
	mod_synth_pad_event_int(_PAD_1_EVENT, _PAD_DETUNE_SEMITONES, val);
	
	/* Set focus back on the Dialog */
	this->setFocus(Qt::ActiveWindowFocusReason);
}

void Dialog_AnalogSynth::on_pad_detune_cents_combobox_changed(int val)
{
	ui->comboBox_PadTuneCents->blockSignals(true);
	ui->comboBox_PadTuneCents->setCurrentIndex(val);
	ui->comboBox_PadTuneCents->blockSignals(false);
	
	pad_tune_semitones = val;
	mod_synth_pad_event_int(_PAD_1_EVENT, _PAD_DETUNE_CENTS, val);
	
	/* Set focus back on the Dialog */
	this->setFocus(Qt::ActiveWindowFocusReason);
}

void Dialog_AnalogSynth::on_pad_send_filter1_dial_changed(int val)
{
	ui->dial_PadSendFilter1->blockSignals(true);
	ui->dial_PadSendFilter1->setValue(val);
	ui->dial_PadSendFilter1->blockSignals(false);
	
	ui->spinBox_PadSendFilter1->blockSignals(true);
	ui->spinBox_PadSendFilter1->setValue(val);
	ui->spinBox_PadSendFilter1->blockSignals(false);
	
	pad_send_filter_1_level = val;
	mod_synth_pad_event_int(_PAD_1_EVENT, _PAD_FILTER_SEND_1, val);
	
	/* Set focus back on the Dialog */
	this->setFocus(Qt::ActiveWindowFocusReason);
}

void Dialog_AnalogSynth::on_pad_send_filter2_dial_changed(int val)
{
	ui->dial_PadSendFilter2->blockSignals(true);
	ui->dial_PadSendFilter2->setValue(val);
	ui->dial_PadSendFilter2->blockSignals(false);
	
	ui->spinBox_PadSendFilter2->blockSignals(true);
	ui->spinBox_PadSendFilter2->setValue(val);
	ui->spinBox_PadSendFilter2->blockSignals(false);
	
	pad_send_filter_2_level = val;
	mod_synth_pad_event_int(_PAD_1_EVENT, _PAD_FILTER_SEND_2, val);
	
	/* Set focus back on the Dialog */
	this->setFocus(Qt::ActiveWindowFocusReason);
}

void Dialog_AnalogSynth::on_pad_freq_mod_lfo_combobox_changed(int val)
{
	ui->comboBox_PadFreqModLFO->blockSignals(true);
	ui->comboBox_PadFreqModLFO->setCurrentIndex(val);
	ui->comboBox_PadFreqModLFO->blockSignals(false);
	
	pad_freq_mod_lfo_num = val;
	mod_synth_pad_event_int(_PAD_1_EVENT, _PAD_FREQ_MOD_LFO, val);
	
	/* Set focus back on the Dialog */
	this->setFocus(Qt::ActiveWindowFocusReason);
}

void Dialog_AnalogSynth::on_pad_freq_mod_lfo_level_dial_changed(int val)
{
	ui->dial_PadFreqModLFOLevel->blockSignals(true);
	ui->dial_PadFreqModLFOLevel->setValue(val);
	ui->dial_PadFreqModLFOLevel->blockSignals(false);
	
	ui->spinBox_PadFreqModLfoLevel->blockSignals(true);
	ui->spinBox_PadFreqModLfoLevel->setValue(val);
	ui->spinBox_PadFreqModLfoLevel->blockSignals(false);
	
	pad_freq_mod_lfo_level = val;
	mod_synth_pad_event_int(_PAD_1_EVENT, _PAD_FREQ_MOD_LFO_LEVEL, val);
	
	/* Set focus back on the Dialog */
	this->setFocus(Qt::ActiveWindowFocusReason);
}

void Dialog_AnalogSynth::on_pad_freq_mod_env_combobox_changed(int val)
{
	ui->comboBox_PadFreqModAdsr->blockSignals(true);
	ui->comboBox_PadFreqModAdsr->setCurrentIndex(val);
	ui->comboBox_PadFreqModAdsr->blockSignals(false);
	
	pad_freq_mod_adsr_num = val;
	mod_synth_pad_event_int(_PAD_1_EVENT, _PAD_FREQ_MOD_ENV, val);
	
	/* Set focus back on the Dialog */
	this->setFocus(Qt::ActiveWindowFocusReason);
}

void Dialog_AnalogSynth::on_pad_freq_mod_env_level_dial_changed(int val)
{
	ui->dial_PadFreqModAdsrLevel->blockSignals(true);
	ui->dial_PadFreqModAdsrLevel->setValue(val);
	ui->dial_PadFreqModAdsrLevel->blockSignals(false);
	
	ui->spinBox_PadFreqModAdsrLevel->blockSignals(true);
	ui->spinBox_PadFreqModAdsrLevel->setValue(val);
	ui->spinBox_PadFreqModAdsrLevel->blockSignals(false);
	
	pad_freq_mod_lfo_level = val;
	mod_synth_pad_event_int(_PAD_1_EVENT, _PAD_FREQ_MOD_ENV_LEVEL, val);
	
	/* Set focus back on the Dialog */
	this->setFocus(Qt::ActiveWindowFocusReason);
}

void Dialog_AnalogSynth::on_pad_amp_mod_lfo_combobox_changed(int val)
{
	ui->comboBox_PadAmpModLFO->blockSignals(true);
	ui->comboBox_PadAmpModLFO->setCurrentIndex(val);
	ui->comboBox_PadAmpModLFO->blockSignals(false);
	
	pad_amp_mod_lfo_num = val;
	mod_synth_pad_event_int(_PAD_1_EVENT, _PAD_AMP_MOD_LFO, val);
	
	/* Set focus back on the Dialog */
	this->setFocus(Qt::ActiveWindowFocusReason);
}

void Dialog_AnalogSynth::on_pad_amp_mod_lfo_level_dial_changed(int val)
{
	ui->dial_PadAmpModLFOLevel->blockSignals(true);
	ui->dial_PadAmpModLFOLevel->setValue(val);
	ui->dial_PadAmpModLFOLevel->blockSignals(false);
	
	ui->spinBox_PadAmpModLfoLevel->blockSignals(true);
	ui->spinBox_PadAmpModLfoLevel->setValue(val);
	ui->spinBox_PadAmpModLfoLevel->blockSignals(false);
	
	pad_amp_mod_lfo_level = val;
	mod_synth_pad_event_int(_PAD_1_EVENT, _PAD_AMP_MOD_LFO_LEVEL, val);
	
	/* Set focus back on the Dialog */
	this->setFocus(Qt::ActiveWindowFocusReason);
}

void Dialog_AnalogSynth::on_pad_amp_mod_env_combobox_changed(int val)
{
	ui->comboBox_PadAmpModAdsr->blockSignals(true);
	ui->comboBox_PadAmpModAdsr->setCurrentIndex(val);
	ui->comboBox_PadAmpModAdsr->blockSignals(false);
	
	pad_amp_mod_adsr_num = val;
	mod_synth_pad_event_int(_PAD_1_EVENT, _PAD_AMP_MOD_ENV, val);
	
	/* Set focus back on the Dialog */
	this->setFocus(Qt::ActiveWindowFocusReason);
}

void Dialog_AnalogSynth::on_pad_amp_mod_env_level_dial_changed(int val)
{
	ui->dial_PadAmpModAdsrLevel->blockSignals(true);
	ui->dial_PadAmpModAdsrLevel->setValue(val);
	ui->dial_PadAmpModAdsrLevel->blockSignals(false);
	
	ui->spinBox_PadAmpModAdsrLevel->blockSignals(true);
	ui->spinBox_PadAmpModAdsrLevel->setValue(val);
	ui->spinBox_PadAmpModAdsrLevel->blockSignals(false);
	
	pad_amp_mod_lfo_level = val;
	mod_synth_pad_event_int(_PAD_1_EVENT, _PAD_AMP_MOD_ENV_LEVEL, val);
	
	/* Set focus back on the Dialog */
	this->setFocus(Qt::ActiveWindowFocusReason);
}

void Dialog_AnalogSynth::on_pad_quality_combobox_changed(int val)
{
	ui->comboBox_PadQuality->blockSignals(true);
	ui->comboBox_PadQuality->setCurrentIndex(val);
	ui->comboBox_PadQuality->blockSignals(false);
	
	pad_quality = val;
	
	mod_synth_disable_pad_synth();
	mod_synth_pad_event_int(_PAD_1_EVENT, _PAD_QUALITY, val);
	
	update_profile_plot = true;
	update_spectrum_plot = true;
	mod_synth_enable_pad_synth();
	
	/* Set focus back on the Dialog */
	this->setFocus(Qt::ActiveWindowFocusReason);
}

void Dialog_AnalogSynth::on_pad_base_note_combobox_changed(int val)
{
	ui->comboBox_PadBaseNote->blockSignals(true);
	ui->comboBox_PadBaseNote->setCurrentIndex(val);
	ui->comboBox_PadBaseNote->blockSignals(false);
	
	pad_base_note = val;
	
	mod_synth_disable_pad_synth();
	mod_synth_pad_event_int(_PAD_1_EVENT, _PAD_BASE_NOTE, val);
	
	update_profile_plot = true;
	update_spectrum_plot = true;
	mod_synth_enable_pad_synth();
	
	/* Set focus back on the Dialog */
	this->setFocus(Qt::ActiveWindowFocusReason);
}

void Dialog_AnalogSynth::on_pad_base_width_slider_changed(int val)
{
	ui->horizontalSlider_PadBaseWidth->blockSignals(true);
	ui->horizontalSlider_PadBaseWidth->setValue(val);
	ui->horizontalSlider_PadBaseWidth->blockSignals(false);
	
	ui->spinBox_PadBaseWidth->blockSignals(true);
	ui->spinBox_PadBaseWidth->setValue(val);
	ui->spinBox_PadBaseWidth->blockSignals(false);
	
	pad_base_width = val;
	
	mod_synth_disable_pad_synth();
	mod_synth_pad_event_int(_PAD_1_EVENT, _PAD_BASE_WIDTH, val);
	
	update_profile_plot = true;
	update_spectrum_plot = true;
	mod_synth_enable_pad_synth();
	
	/* Set focus back on the Dialog */
	this->setFocus(Qt::ActiveWindowFocusReason);
}

void Dialog_AnalogSynth::on_pad_shape_combobox_changed(int val)
{
	ui->comboBox_PadShape->blockSignals(true);
	ui->comboBox_PadShape->setCurrentIndex(val);
	ui->comboBox_PadShape->blockSignals(false);
	
	pad_shape = val;
	
	mod_synth_disable_pad_synth();
	mod_synth_pad_event_int(_PAD_1_EVENT, _PAD_SHAPE, val);
	
	update_profile_plot = true;
	update_spectrum_plot = true;
	mod_synth_enable_pad_synth();
	
	/* Set focus back on the Dialog */
	this->setFocus(Qt::ActiveWindowFocusReason);
}

void Dialog_AnalogSynth::on_pad_shape_cutoff_combobox_changed(int val)
{
	ui->comboBox_PadShapeCutoff->blockSignals(true);
	ui->comboBox_PadShapeCutoff->setCurrentIndex(val);
	ui->comboBox_PadShapeCutoff->blockSignals(false);
	
	pad_shape_cutoff = val;
	
	mod_synth_disable_pad_synth();
	mod_synth_pad_event_int(_PAD_1_EVENT, _PAD_SHAPE_CUTOFF, val);
	
	update_profile_plot = true;
	update_spectrum_plot = true;
	mod_synth_enable_pad_synth();
	
	/* Set focus back on the Dialog */
	this->setFocus(Qt::ActiveWindowFocusReason);	
}

void Dialog_AnalogSynth::on_pad_generate_pushbutton_clicked()
{
	
	mod_synth_disable_pad_synth(); // ????
	update_profile_plot = true;
	update_spectrum_plot = true;
	mod_synth_enable_pad_synth();
	
	/* Set focus back on the Dialog */
	this->setFocus(Qt::ActiveWindowFocusReason);
}


void Dialog_AnalogSynth::on_pad_harmony1_level_slider_changed(int val)
{
	ui->verticalSlider_PadHarmony_1->blockSignals(true);
	ui->verticalSlider_PadHarmony_1->setValue(val);
	ui->verticalSlider_PadHarmony_1->blockSignals(false);
	
	ui->spinBox_PadHarmony_1->blockSignals(true);
	ui->spinBox_PadHarmony_1->setValue(val);
	ui->spinBox_PadHarmony_1->blockSignals(false);
	
	pad_harmony_1_level = val;
	
	mod_synth_disable_pad_synth();
	mod_synth_pad_event_int(_PAD_1_EVENT, _PAD_HARMONY_LEVEL_1, val);
	
	update_profile_plot = true;
	update_spectrum_plot = true;
	mod_synth_enable_pad_synth();
	
	/* Set focus back on the Dialog */
	this->setFocus(Qt::ActiveWindowFocusReason);
}

void Dialog_AnalogSynth::on_pad_harmony2_level_slider_changed(int val)
{
	ui->verticalSlider_PadHarmony_2->blockSignals(true);
	ui->verticalSlider_PadHarmony_2->setValue(val);
	ui->verticalSlider_PadHarmony_2->blockSignals(false);
	
	ui->spinBox_PadHarmony_2->blockSignals(true);
	ui->spinBox_PadHarmony_2->setValue(val);
	ui->spinBox_PadHarmony_2->blockSignals(false);
	
	pad_harmony_2_level = val;
	
	mod_synth_disable_pad_synth();
	mod_synth_pad_event_int(_PAD_1_EVENT, _PAD_HARMONY_LEVEL_2, val);
	
	update_profile_plot = true;
	update_spectrum_plot = true;
	mod_synth_enable_pad_synth();
	
	/* Set focus back on the Dialog */
	this->setFocus(Qt::ActiveWindowFocusReason);
}

void Dialog_AnalogSynth::on_pad_harmony3_level_slider_changed(int val)
{
	ui->verticalSlider_PadHarmony_3->blockSignals(true);
	ui->verticalSlider_PadHarmony_3->setValue(val);
	ui->verticalSlider_PadHarmony_3->blockSignals(false);
	
	ui->spinBox_PadHarmony_3->blockSignals(true);
	ui->spinBox_PadHarmony_3->setValue(val);
	ui->spinBox_PadHarmony_3->blockSignals(false);
	
	pad_harmony_3_level = val;
	
	mod_synth_disable_pad_synth();
	mod_synth_pad_event_int(_PAD_1_EVENT, _PAD_HARMONY_LEVEL_3, val);
	
	update_profile_plot = true;
	update_spectrum_plot = true;
	mod_synth_enable_pad_synth();
	
	/* Set focus back on the Dialog */
	this->setFocus(Qt::ActiveWindowFocusReason);
}

void Dialog_AnalogSynth::on_pad_harmony4_level_slider_changed(int val)
{
	ui->verticalSlider_PadHarmony_4->blockSignals(true);
	ui->verticalSlider_PadHarmony_4->setValue(val);
	ui->verticalSlider_PadHarmony_4->blockSignals(false);
	
	ui->spinBox_PadHarmony_4->blockSignals(true);
	ui->spinBox_PadHarmony_4->setValue(val);
	ui->spinBox_PadHarmony_4->blockSignals(false);
	
	pad_harmony_4_level = val;
	
	mod_synth_disable_pad_synth();
	mod_synth_pad_event_int(_PAD_1_EVENT, _PAD_HARMONY_LEVEL_4, val);
	
	update_profile_plot = true;
	update_spectrum_plot = true;
	mod_synth_enable_pad_synth();
	
	/* Set focus back on the Dialog */
	this->setFocus(Qt::ActiveWindowFocusReason);
}

void Dialog_AnalogSynth::on_pad_harmony5_level_slider_changed(int val)
{
	ui->verticalSlider_PadHarmony_5->blockSignals(true);
	ui->verticalSlider_PadHarmony_5->setValue(val);
	ui->verticalSlider_PadHarmony_5->blockSignals(false);
	
	ui->spinBox_PadHarmony_5->blockSignals(true);
	ui->spinBox_PadHarmony_5->setValue(val);
	ui->spinBox_PadHarmony_5->blockSignals(false);
	
	pad_harmony_5_level = val;
	
	mod_synth_disable_pad_synth();
	mod_synth_pad_event_int(_PAD_1_EVENT, _PAD_HARMONY_LEVEL_5, val);
	
	update_profile_plot = true;
	update_spectrum_plot = true;
	mod_synth_enable_pad_synth();
	
	/* Set focus back on the Dialog */
	this->setFocus(Qt::ActiveWindowFocusReason);
}

void Dialog_AnalogSynth::on_pad_harmony6_level_slider_changed(int val)
{
	ui->verticalSlider_PadHarmony_6->blockSignals(true);
	ui->verticalSlider_PadHarmony_6->setValue(val);
	ui->verticalSlider_PadHarmony_6->blockSignals(false);
	
	ui->spinBox_PadHarmony_6->blockSignals(true);
	ui->spinBox_PadHarmony_6->setValue(val);
	ui->spinBox_PadHarmony_6->blockSignals(false);
	
	pad_harmony_6_level = val;
	
	mod_synth_disable_pad_synth();
	mod_synth_pad_event_int(_PAD_1_EVENT, _PAD_HARMONY_LEVEL_6, val);
	
	update_profile_plot = true;
	update_spectrum_plot = true;
	mod_synth_enable_pad_synth();
	
	/* Set focus back on the Dialog */
	this->setFocus(Qt::ActiveWindowFocusReason);
}

void Dialog_AnalogSynth::on_pad_harmony7_level_slider_changed(int val)
{
	ui->verticalSlider_PadHarmony_7->blockSignals(true);
	ui->verticalSlider_PadHarmony_7->setValue(val);
	ui->verticalSlider_PadHarmony_7->blockSignals(false);
	
	ui->spinBox_PadHarmony_7->blockSignals(true);
	ui->spinBox_PadHarmony_7->setValue(val);
	ui->spinBox_PadHarmony_7->blockSignals(false);
	
	pad_harmony_7_level = val;
	
	mod_synth_disable_pad_synth();
	mod_synth_pad_event_int(_PAD_1_EVENT, _PAD_HARMONY_LEVEL_7, val);
	
	update_profile_plot = true;
	update_spectrum_plot = true;
	mod_synth_enable_pad_synth();
	
	/* Set focus back on the Dialog */
	this->setFocus(Qt::ActiveWindowFocusReason);
}

void Dialog_AnalogSynth::on_pad_harmony8_level_slider_changed(int val)
{
	ui->verticalSlider_PadHarmony_8->blockSignals(true);
	ui->verticalSlider_PadHarmony_8->setValue(val);
	ui->verticalSlider_PadHarmony_8->blockSignals(false);
	
	ui->spinBox_PadHarmony_8->blockSignals(true);
	ui->spinBox_PadHarmony_8->setValue(val);
	ui->spinBox_PadHarmony_8->blockSignals(false);
	
	pad_harmony_8_level = val;
	
	mod_synth_disable_pad_synth();
	mod_synth_pad_event_int(_PAD_1_EVENT, _PAD_HARMONY_LEVEL_8, val);
	
	update_profile_plot = true;
	update_spectrum_plot = true;
	mod_synth_enable_pad_synth();
	
	/* Set focus back on the Dialog */
	this->setFocus(Qt::ActiveWindowFocusReason);
}

void Dialog_AnalogSynth::on_pad_harmony9_level_slider_changed(int val)
{
	ui->verticalSlider_PadHarmony_9->blockSignals(true);
	ui->verticalSlider_PadHarmony_9->setValue(val);
	ui->verticalSlider_PadHarmony_9->blockSignals(false);
	
	ui->spinBox_PadHarmony_9->blockSignals(true);
	ui->spinBox_PadHarmony_9->setValue(val);
	ui->spinBox_PadHarmony_9->blockSignals(false);
	
	pad_harmony_9_level = val;
	
	mod_synth_disable_pad_synth();
	mod_synth_pad_event_int(_PAD_1_EVENT, _PAD_HARMONY_LEVEL_9, val);
	
	update_profile_plot = true;
	update_spectrum_plot = true;
	mod_synth_enable_pad_synth();
	
	/* Set focus back on the Dialog */
	this->setFocus(Qt::ActiveWindowFocusReason);
}

void Dialog_AnalogSynth::on_pad_harmony10_level_slider_changed(int val)
{
	ui->verticalSlider_PadHarmony_10->blockSignals(true);
	ui->verticalSlider_PadHarmony_10->setValue(val);
	ui->verticalSlider_PadHarmony_10->blockSignals(false);
	
	ui->spinBox_PadHarmony_10->blockSignals(true);
	ui->spinBox_PadHarmony_10->setValue(val);
	ui->spinBox_PadHarmony_10->blockSignals(false);
	
	pad_harmony_10_level = val;
	
	mod_synth_disable_pad_synth();
	mod_synth_pad_event_int(_PAD_1_EVENT, _PAD_HARMONY_LEVEL_10, val);
	
	update_profile_plot = true;
	update_spectrum_plot = true;
	mod_synth_enable_pad_synth();
	
	/* Set focus back on the Dialog */
	this->setFocus(Qt::ActiveWindowFocusReason);
}

void Dialog_AnalogSynth::on_pad_harmonies_detune_slider_changed(int val)
{
	ui->verticalSlider_PadHarmonyDetune->blockSignals(true);
	ui->verticalSlider_PadHarmonyDetune->setValue(val);
	ui->verticalSlider_PadHarmonyDetune->blockSignals(false);
	
	ui->spinBox_PadHarmonyDetune->blockSignals(true);
	ui->spinBox_PadHarmonyDetune->setValue(val);
	ui->spinBox_PadHarmonyDetune->blockSignals(false);
	
	pad_harmony_detune = val;
	
	mod_synth_disable_pad_synth();
	mod_synth_pad_event_int(_PAD_1_EVENT, _PAD_DETUNE, val);
	
	update_profile_plot = true;
	update_spectrum_plot = true;
	mod_synth_enable_pad_synth();
	
	/* Set focus back on the Dialog */
	this->setFocus(Qt::ActiveWindowFocusReason);
}
