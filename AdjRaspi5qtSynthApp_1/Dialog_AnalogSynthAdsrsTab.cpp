/**
* @file		Dialog_AnalogSynthAdsrsTab.h
*	@author		Nahum Budin
*	@date		27-Nov-2024
*	@version	1.0
*
*	@brief		Analog Synthesizer instrument ADSRs Enevelope Generators Tab handling
*				
*	History:
*			Based on the AdjModSynth project ver 1.1 16-Jan-2021 
*
*/

#include "Dialog_AnalogSynth.h"
#include "ui_Dialog_AnalogSynth.h"
#include "utils.h"

#include "libAdjRaspi5SynthAPI.h"

void Dialog_AnalogSynth::set_adsrs_signals_connections()
{
	connect(ui->verticalSlider_AdsrA_1,
		SIGNAL(valueChanged(int)),
		this,
		SLOT(on_adsr1_attack_slider_changed(int)));
	
	connect(ui->verticalSlider_AdsrD_1,
		SIGNAL(valueChanged(int)),
		this,
		SLOT(on_adsr1_decay_slider_changed(int)));
	
	connect(ui->verticalSlider_AdsrS_1,
		SIGNAL(valueChanged(int)),
		this,
		SLOT(on_adsr1_sustain_slider_changed(int)));
	
	connect(ui->verticalSlider_AdsrR_1,
		SIGNAL(valueChanged(int)),
		this,
		SLOT(on_adsr1_release_slider_changed(int)));
	
	connect(ui->verticalSlider_AdsrA_2,
		SIGNAL(valueChanged(int)),
		this,
		SLOT(on_adsr2_attack_slider_changed(int)));
	
	connect(ui->verticalSlider_AdsrD_2,
		SIGNAL(valueChanged(int)),
		this,
		SLOT(on_adsr2_decay_slider_changed(int)));
	
	connect(ui->verticalSlider_AdsrS_2,
		SIGNAL(valueChanged(int)),
		this,
		SLOT(on_adsr2_sustain_slider_changed(int)));
	
	connect(ui->verticalSlider_AdsrR_2,
		SIGNAL(valueChanged(int)),
		this,
		SLOT(on_adsr2_release_slider_changed(int)));
	
	connect(ui->verticalSlider_AdsrA_3,
		SIGNAL(valueChanged(int)),
		this,
		SLOT(on_adsr3_attack_slider_changed(int)));
	
	connect(ui->verticalSlider_AdsrD_3,
		SIGNAL(valueChanged(int)),
		this,
		SLOT(on_adsr3_decay_slider_changed(int)));
	
	connect(ui->verticalSlider_AdsrS_3,
		SIGNAL(valueChanged(int)),
		this,
		SLOT(on_adsr3_sustain_slider_changed(int)));
	
	connect(ui->verticalSlider_AdsrR_3,
		SIGNAL(valueChanged(int)),
		this,
		SLOT(on_adsr3_release_slider_changed(int)));
	
	connect(ui->verticalSlider_AdsrA_4,
		SIGNAL(valueChanged(int)),
		this,
		SLOT(on_adsr4_attack_slider_changed(int)));
	
	connect(ui->verticalSlider_AdsrD_4,
		SIGNAL(valueChanged(int)),
		this,
		SLOT(on_adsr4_decay_slider_changed(int)));
	
	connect(ui->verticalSlider_AdsrS_4,
		SIGNAL(valueChanged(int)),
		this,
		SLOT(on_adsr4_sustain_slider_changed(int)));
	
	connect(ui->verticalSlider_AdsrR_4,
		SIGNAL(valueChanged(int)),
		this,
		SLOT(on_adsr4_release_slider_changed(int)));
	
	connect(ui->verticalSlider_AdsrA_5,
		SIGNAL(valueChanged(int)),
		this,
		SLOT(on_adsr5_attack_slider_changed(int)));
	
	connect(ui->verticalSlider_AdsrD_5,
		SIGNAL(valueChanged(int)),
		this,
		SLOT(on_adsr5_decay_slider_changed(int)));
	
	connect(ui->verticalSlider_AdsrS_5,
		SIGNAL(valueChanged(int)),
		this,
		SLOT(on_adsr5_sustain_slider_changed(int)));
	
	connect(ui->verticalSlider_AdsrR_5,
		SIGNAL(valueChanged(int)),
		this,
		SLOT(on_adsr5_release_slider_changed(int)));
	
	connect(ui->verticalSlider_AdsrA_6,
		SIGNAL(valueChanged(int)),
		this,
		SLOT(on_adsr6_attack_slider_changed(int)));
	
	connect(ui->verticalSlider_AdsrD_6,
		SIGNAL(valueChanged(int)),
		this,
		SLOT(on_adsr6_decay_slider_changed(int)));
	
	connect(ui->verticalSlider_AdsrS_6,
		SIGNAL(valueChanged(int)),
		this,
		SLOT(on_adsr6_sustain_slider_changed(int)));
	
	connect(ui->verticalSlider_AdsrR_6,
		SIGNAL(valueChanged(int)),
		this,
		SLOT(on_adsr6_release_slider_changed(int)));
}

void Dialog_AnalogSynth::init_adsrs_combboxes_and_labels()
{
	
}

void Dialog_AnalogSynth::adsrs_update()
{
	char text[64];
	
	ui->verticalSlider_AdsrA_1->blockSignals(true);
	ui->verticalSlider_AdsrA_1->setValue(mod_synth_get_active_env_mod_1_attack());
	ui->verticalSlider_AdsrA_1->blockSignals(false);
	
	sprintf(text, "%.2fSec", 
		mod_synth_log_scale_100_float(0.0, mod_synth_get_adsr_max_attack_time_sec(), 10.0, 
		mod_synth_get_active_env_mod_1_attack()));
	
	ui->lineEdit_AdsrA_1->setText(QString(text));
	
	ui->verticalSlider_AdsrD_1->blockSignals(true);
	ui->verticalSlider_AdsrD_1->setValue(mod_synth_get_active_env_mod_1_decay());
	ui->verticalSlider_AdsrD_1->blockSignals(false);
	
	sprintf(text,
		"%.2fSec", 
		mod_synth_log_scale_100_float(0.0,
			mod_synth_get_adsr_max_decay_time_sec(),
			10.0, 
			mod_synth_get_active_env_mod_1_decay()));
	
	ui->lineEdit_AdsrD_1->setText(QString(text));
	
	ui->verticalSlider_AdsrS_1->blockSignals(true);
	ui->verticalSlider_AdsrS_1->setValue(mod_synth_get_active_env_mod_1_sustain());
	ui->verticalSlider_AdsrS_1->blockSignals(false);
	
	sprintf(text, "%i%c", mod_synth_get_active_env_mod_1_sustain(), '%');	
	ui->lineEdit_AdsrS_1->setText(QString(text));
	
	ui->verticalSlider_AdsrR_1->blockSignals(true);
	ui->verticalSlider_AdsrR_1->setValue(mod_synth_get_active_env_mod_1_release());
	ui->verticalSlider_AdsrR_1->blockSignals(false);
	
	sprintf(text,
		"%.2fSec", 
		mod_synth_log_scale_100_float(0.0,
			mod_synth_get_adsr_max_release_time_sec(),
			10.0, 
			mod_synth_get_active_env_mod_1_release()));
	
	ui->lineEdit_AdsrR_1->setText(QString(text));
	
	ui->verticalSlider_AdsrA_2->blockSignals(true);
	ui->verticalSlider_AdsrA_2->setValue(mod_synth_get_active_env_mod_2_attack());
	ui->verticalSlider_AdsrA_2->blockSignals(false);
	
	sprintf(text,
		"%.2fSec", 
		mod_synth_log_scale_100_float(0.0,
			mod_synth_get_adsr_max_attack_time_sec(),
			10.0, 
			mod_synth_get_active_env_mod_2_attack()));
	
	ui->lineEdit_AdsrA_2->setText(QString(text));
	
	ui->verticalSlider_AdsrD_2->blockSignals(true);
	ui->verticalSlider_AdsrD_2->setValue(mod_synth_get_active_env_mod_2_decay());
	ui->verticalSlider_AdsrD_2->blockSignals(false);
	
	sprintf(text,
		"%.2fSec", 
		mod_synth_log_scale_100_float(0.0,
			mod_synth_get_adsr_max_decay_time_sec(),
			10.0, 
			mod_synth_get_active_env_mod_2_decay()));
	
	ui->lineEdit_AdsrD_2->setText(QString(text));
	
	ui->verticalSlider_AdsrS_2->blockSignals(true);
	ui->verticalSlider_AdsrS_2->setValue(mod_synth_get_active_env_mod_1_sustain());
	ui->verticalSlider_AdsrS_2->blockSignals(false);
	
	sprintf(text, "%i%c", mod_synth_get_active_env_mod_2_sustain(), '%');	
	ui->lineEdit_AdsrS_2->setText(QString(text));
	
	ui->verticalSlider_AdsrR_2->blockSignals(true);
	ui->verticalSlider_AdsrR_2->setValue(mod_synth_get_active_env_mod_2_release());
	ui->verticalSlider_AdsrR_2->blockSignals(false);
	
	sprintf(text,
		"%.2fSec", 
		mod_synth_log_scale_100_float(0.0,
			mod_synth_get_adsr_max_release_time_sec(),
			10.0, 
			mod_synth_get_active_env_mod_2_release()));
	
	ui->lineEdit_AdsrR_2->setText(QString(text));
	
	ui->verticalSlider_AdsrA_3->blockSignals(true);
	ui->verticalSlider_AdsrA_3->setValue(mod_synth_get_active_env_mod_3_attack());
	ui->verticalSlider_AdsrA_3->blockSignals(false);
	
	sprintf(text,
		"%.2fSec", 
		mod_synth_log_scale_100_float(0.0,
			mod_synth_get_adsr_max_attack_time_sec(),
			10.0, 
			mod_synth_get_active_env_mod_3_attack()));
	
	ui->lineEdit_AdsrA_3->setText(QString(text));
	
	ui->verticalSlider_AdsrD_3->blockSignals(true);
	ui->verticalSlider_AdsrD_3->setValue(mod_synth_get_active_env_mod_3_decay());
	ui->verticalSlider_AdsrD_3->blockSignals(false);
	
	sprintf(text,
		"%.2fSec", 
		mod_synth_log_scale_100_float(0.0,
			mod_synth_get_adsr_max_decay_time_sec(),
			10.0, 
			mod_synth_get_active_env_mod_3_decay()));
	
	ui->lineEdit_AdsrD_3->setText(QString(text));
	
	ui->verticalSlider_AdsrS_3->blockSignals(true);
	ui->verticalSlider_AdsrS_3->setValue(mod_synth_get_active_env_mod_3_sustain());
	ui->verticalSlider_AdsrS_3->blockSignals(false);
	
	sprintf(text, "%i%c", mod_synth_get_active_env_mod_3_sustain(), '%');	
	ui->lineEdit_AdsrS_3->setText(QString(text));
	
	ui->verticalSlider_AdsrR_3->blockSignals(true);
	ui->verticalSlider_AdsrR_3->setValue(mod_synth_get_active_env_mod_3_release());
	ui->verticalSlider_AdsrR_3->blockSignals(false);
	
	sprintf(text,
		"%.2fSec", 
		mod_synth_log_scale_100_float(0.0,
			mod_synth_get_adsr_max_release_time_sec(),
			10.0, 
			mod_synth_get_active_env_mod_3_release()));
	
	ui->lineEdit_AdsrR_3->setText(QString(text));
	
	ui->verticalSlider_AdsrA_4->blockSignals(true);
	ui->verticalSlider_AdsrA_4->setValue(mod_synth_get_active_env_mod_4_attack());
	ui->verticalSlider_AdsrA_4->blockSignals(false);
	
	sprintf(text,
		"%.2fSec", 
		mod_synth_log_scale_100_float(0.0,
			mod_synth_get_adsr_max_attack_time_sec(),
			10.0, 
			mod_synth_get_active_env_mod_4_attack()));
	
	ui->lineEdit_AdsrA_4->setText(QString(text));
	
	ui->verticalSlider_AdsrD_4->blockSignals(true);
	ui->verticalSlider_AdsrD_4->setValue(mod_synth_get_active_env_mod_4_decay());
	ui->verticalSlider_AdsrD_4->blockSignals(false);
	
	sprintf(text,
		"%.2fSec", 
		mod_synth_log_scale_100_float(0.0,
			mod_synth_get_adsr_max_decay_time_sec(),
			10.0, 
			mod_synth_get_active_env_mod_4_decay()));
	
	ui->lineEdit_AdsrD_4->setText(QString(text));
	
	ui->verticalSlider_AdsrS_4->blockSignals(true);
	ui->verticalSlider_AdsrS_4->setValue(mod_synth_get_active_env_mod_4_sustain());
	ui->verticalSlider_AdsrS_4->blockSignals(false);
	
	sprintf(text, "%i%c", mod_synth_get_active_env_mod_4_sustain(), '%');	
	ui->lineEdit_AdsrS_4->setText(QString(text));
	
	ui->verticalSlider_AdsrR_4->blockSignals(true);
	ui->verticalSlider_AdsrR_4->setValue(mod_synth_get_active_env_mod_4_release());
	ui->verticalSlider_AdsrR_4->blockSignals(false);
	
	sprintf(text,
		"%.2fSec", 
		mod_synth_log_scale_100_float(0.0,
			mod_synth_get_adsr_max_release_time_sec(),
			10.0, 
			mod_synth_get_active_env_mod_4_release()));
	
	ui->lineEdit_AdsrR_4->setText(QString(text));
	
	ui->verticalSlider_AdsrA_5->blockSignals(true);
	ui->verticalSlider_AdsrA_5->setValue(mod_synth_get_active_env_mod_5_attack());
	ui->verticalSlider_AdsrA_5->blockSignals(false);
	
	sprintf(text,
		"%.2fSec", 
		mod_synth_log_scale_100_float(0.0,
			mod_synth_get_adsr_max_attack_time_sec(),
			10.0, 
			mod_synth_get_active_env_mod_5_attack()));
	
	ui->lineEdit_AdsrA_5->setText(QString(text));
	
	ui->verticalSlider_AdsrD_5->blockSignals(true);
	ui->verticalSlider_AdsrD_5->setValue(mod_synth_get_active_env_mod_5_decay());
	ui->verticalSlider_AdsrD_5->blockSignals(false);
	
	sprintf(text,
		"%.2fSec", 
		mod_synth_log_scale_100_float(0.0,
			mod_synth_get_adsr_max_decay_time_sec(),
			10.0, 
			mod_synth_get_active_env_mod_5_decay()));
	
	ui->lineEdit_AdsrD_5->setText(QString(text));
	
	ui->verticalSlider_AdsrS_5->blockSignals(true);
	ui->verticalSlider_AdsrS_5->setValue(mod_synth_get_active_env_mod_5_sustain());
	ui->verticalSlider_AdsrS_5->blockSignals(false);
	
	sprintf(text, "%i%c", mod_synth_get_active_env_mod_5_sustain(), '%');	
	ui->lineEdit_AdsrS_5->setText(QString(text));
	
	ui->verticalSlider_AdsrR_5->blockSignals(true);
	ui->verticalSlider_AdsrR_5->setValue(mod_synth_get_active_env_mod_1_release());
	ui->verticalSlider_AdsrR_5->blockSignals(false);
	
	sprintf(text,
		"%.2fSec", 
		mod_synth_log_scale_100_float(0.0,
			mod_synth_get_adsr_max_release_time_sec(),
			10.0, 
			mod_synth_get_active_env_mod_5_release()));
	
	ui->lineEdit_AdsrR_5->setText(QString(text));
	
	ui->verticalSlider_AdsrA_6->blockSignals(true);
	ui->verticalSlider_AdsrA_6->setValue(mod_synth_get_active_env_mod_6_attack());
	ui->verticalSlider_AdsrA_6->blockSignals(false);
	
	sprintf(text,
		"%.2fSec", 
		mod_synth_log_scale_100_float(0.0,
			mod_synth_get_adsr_max_attack_time_sec(),
			10.0, 
			mod_synth_get_active_env_mod_6_attack()));
	
	ui->lineEdit_AdsrA_6->setText(QString(text));
	
	ui->verticalSlider_AdsrD_6->blockSignals(true);
	ui->verticalSlider_AdsrD_6->setValue(mod_synth_get_active_env_mod_6_decay());
	ui->verticalSlider_AdsrD_6->blockSignals(false);
	
	sprintf(text,
		"%.2fSec", 
		mod_synth_log_scale_100_float(0.0,
			mod_synth_get_adsr_max_decay_time_sec(),
			10.0, 
			mod_synth_get_active_env_mod_6_decay()));
	
	ui->lineEdit_AdsrD_6->setText(QString(text));
	
	ui->verticalSlider_AdsrS_6->blockSignals(true);
	ui->verticalSlider_AdsrS_6->setValue(mod_synth_get_active_env_mod_6_sustain());
	ui->verticalSlider_AdsrS_6->blockSignals(false);
	
	sprintf(text, "%i%c", mod_synth_get_active_env_mod_6_sustain(), '%');	
	ui->lineEdit_AdsrS_6->setText(QString(text));
	
	ui->verticalSlider_AdsrR_6->blockSignals(true);
	ui->verticalSlider_AdsrR_6->setValue(mod_synth_get_active_env_mod_6_release());
	ui->verticalSlider_AdsrR_6->blockSignals(false);
	
	sprintf(text,
		"%.2fSec", 
		mod_synth_log_scale_100_float(0.0,
			mod_synth_get_adsr_max_release_time_sec(),
			10.0, 
			mod_synth_get_active_env_mod_6_release()));
	
	ui->lineEdit_AdsrR_6->setText(QString(text));
	
	refresh_adsr_curve_view(ui->widget_ADSRplot);
}

void Dialog_AnalogSynth::set_adsr_view_widget_points()
{
	const int max_param_value = 100;
	
	switch (last_modified_adsr)
	{
		case _ENV_1:
			adsr_view_widget_attack = mod_synth_get_active_env_mod_1_attack();
			adsr_view_widget_decay = mod_synth_get_active_env_mod_1_decay();
			adsr_view_widget_sustain = mod_synth_get_active_env_mod_1_sustain();
			adsr_view_widget_release = mod_synth_get_active_env_mod_1_release();
			ui->frame_ADSRplot->move(375, 300);
			break;
		case _ENV_2:
			adsr_view_widget_attack = mod_synth_get_active_env_mod_2_attack();
			adsr_view_widget_decay = mod_synth_get_active_env_mod_2_decay();
			adsr_view_widget_sustain = mod_synth_get_active_env_mod_2_sustain();
			adsr_view_widget_release = mod_synth_get_active_env_mod_2_release();
			ui->frame_ADSRplot->move(375, 300);
			break;
		case _ENV_3:
			adsr_view_widget_attack = mod_synth_get_active_env_mod_3_attack();
			adsr_view_widget_decay = mod_synth_get_active_env_mod_3_decay();
			adsr_view_widget_sustain = mod_synth_get_active_env_mod_3_sustain();
			adsr_view_widget_release = mod_synth_get_active_env_mod_3_release();
			ui->frame_ADSRplot->move(10, 300);
			break;
		case _ENV_4:
			adsr_view_widget_attack = mod_synth_get_active_env_mod_4_attack();
			adsr_view_widget_decay = mod_synth_get_active_env_mod_4_decay();
			adsr_view_widget_sustain = mod_synth_get_active_env_mod_4_sustain();
			adsr_view_widget_release = mod_synth_get_active_env_mod_4_release();
			ui->frame_ADSRplot->move(10, 300);
			break;
		case _ENV_5:
			adsr_view_widget_attack = mod_synth_get_active_env_mod_5_attack();
			adsr_view_widget_decay = mod_synth_get_active_env_mod_5_decay();
			adsr_view_widget_sustain = mod_synth_get_active_env_mod_5_sustain();
			adsr_view_widget_release = mod_synth_get_active_env_mod_5_release();
			ui->frame_ADSRplot->move(375, 300);
			break;
		case _ENV_6:
			adsr_view_widget_attack = mod_synth_get_active_env_mod_6_attack();
			adsr_view_widget_decay = mod_synth_get_active_env_mod_6_decay();
			adsr_view_widget_sustain = mod_synth_get_active_env_mod_6_sustain();
			adsr_view_widget_release = mod_synth_get_active_env_mod_6_release();
			ui->frame_ADSRplot->move(375, 300);
			break;
		default:
			return;
	}
	
	adsr_view_widget_attack = mod_synth_log_scale_100_int(0, max_param_value, 10, adsr_view_widget_attack);
	adsr_view_widget_decay = mod_synth_log_scale_100_int(0, max_param_value, 10, adsr_view_widget_decay);	
	adsr_view_widget_release = mod_synth_log_scale_100_int(0, max_param_value, 10, adsr_view_widget_release);	
	
	adsr_curve_attack_end_point = 
		_ADSR_CURVE_START_POINT + 1 + 
		((adsr_view_widget_attack * adsr_curve_max_attack * _ADSR_CURVE_TIME_MULTIPLIER) / 
		max_param_value);
	
	adsr_curve_decay_end_point = 
		adsr_curve_attack_end_point + 1 +
		((adsr_view_widget_decay * adsr_curve_max_decay * _ADSR_CURVE_TIME_MULTIPLIER) / 
		max_param_value);
	
	adsr_curve_sustain_end_point = 
		adsr_curve_decay_end_point + 1 + 
		_ADSR_CURVE_SUSTAIN_SEGMENT_LENGTH;
	
	adsr_curve_release_end_point = 
		adsr_curve_sustain_end_point + 1 + 
		((adsr_view_widget_release * adsr_curve_max_release *
		_ADSR_CURVE_TIME_MULTIPLIER)  / 
		max_param_value); 
}

void Dialog_AnalogSynth::refresh_adsr_curve_view(QCustomPlot *adsr_plot)
{
	set_adsr_view_widget_points();
	
	if (update_adsr_plot && (adsr_plot != NULL))
	{
		QVector<double> x(8), y(8);
		
		x[0] = 0;
		y[0] = 0;
		
		x[1] = _ADSR_CURVE_START_POINT;
		y[1] = 0;
		
		x[2] = adsr_curve_attack_end_point;
		y[2] = _ADSR_CURVE_HEIGHT;
		
		x[3] = adsr_curve_decay_end_point;
		y[3] = adsr_view_widget_sustain;
		
		x[4] = adsr_curve_sustain_end_point;
		y[4] = adsr_view_widget_sustain;
		
		x[5] = adsr_curve_release_end_point;
		y[5] = 0;
		
		x[6] = adsr_plot_length;
		y[6] = 0;
			
		adsr_plot->graph(0)->setData(x, y);
		adsr_plot->xAxis->setRange(0, adsr_plot_length);

		QPen pen;
		pen.setStyle(Qt::SolidLine);
		pen.setWidth(1);
		pen.setColor(QColor("#FFE018"));
		adsr_plot->addGraph();
		adsr_plot->graph(0)->setPen(pen);
		adsr_plot->addGraph();

		adsr_plot->setBackground(QBrush(QColor("#606060")));
		
		adsr_plot->replot();
		
		adsr_plot->show();
		
		ui->frame_ADSRplot->show();
		ui->frame_ADSRplot->raise();
		
		adsr_view_gadget_timer = 0;	
		
		// update_adsr_plot = false;
	}
}


void Dialog_AnalogSynth::on_adsr1_attack_slider_changed(int val)
{
	char text[64];
	
	ui->verticalSlider_AdsrA_1->blockSignals(true);
	ui->verticalSlider_AdsrA_1->setValue(val);
	ui->verticalSlider_AdsrA_1->blockSignals(false);
	
	sprintf(text,
		"%.2fSec", 
		mod_synth_log_scale_100_float(0.0,
			mod_synth_get_adsr_max_attack_time_sec(),
			10.0, val));
	
	ui->lineEdit_AdsrA_1->setText(QString(text));
	
	mod_synth_modulator_event_int(_ENV_1_EVENT, _MOD_ADSR_ATTACK, val);
	adsr1_attack_entry = val;
	
	last_modified_adsr = _ENV_1;
	
	update_adsr_plot = true;	
}

void Dialog_AnalogSynth::on_adsr1_decay_slider_changed(int val)
{
	char text[64];
	
	ui->verticalSlider_AdsrD_1->blockSignals(true);
	ui->verticalSlider_AdsrD_1->setValue(val);
	ui->verticalSlider_AdsrD_1->blockSignals(false);
	
	sprintf(text,
		"%.2fSec", 
		mod_synth_log_scale_100_float(0.0,
			mod_synth_get_adsr_max_decay_time_sec(),
			10.0, val));
	
	ui->lineEdit_AdsrD_1->setText(QString(text));
	
	mod_synth_modulator_event_int(_ENV_1_EVENT, _MOD_ADSR_DECAY, val);
	adsr1_decay_entry = val;
	
	last_modified_adsr = _ENV_1;
	
	update_adsr_plot = true;
}

void Dialog_AnalogSynth::on_adsr1_sustain_slider_changed(int val)
{
	char text[64];
	
	ui->verticalSlider_AdsrS_1->blockSignals(true);
	ui->verticalSlider_AdsrS_1->setValue(val);
	ui->verticalSlider_AdsrS_1->blockSignals(false);
	
	sprintf(text, "%i%c", val, '%');	
	ui->lineEdit_AdsrS_1->setText(QString(text));
	
	mod_synth_modulator_event_int(_ENV_1_EVENT, _MOD_ADSR_SUSTAIN, val);
	adsr1_sustain_entry = val;
	
	last_modified_adsr = _ENV_1;
	
	update_adsr_plot = true;
}

void Dialog_AnalogSynth::on_adsr1_release_slider_changed(int val)
{
	char text[64];
	
	ui->verticalSlider_AdsrR_1->blockSignals(true);
	ui->verticalSlider_AdsrR_1->setValue(val);
	ui->verticalSlider_AdsrR_1->blockSignals(false);
	
	sprintf(text,
		"%.2fSec", 
		mod_synth_log_scale_100_float(0.0,
			mod_synth_get_adsr_max_release_time_sec(),
			10.0, val));
	
	ui->lineEdit_AdsrR_1->setText(QString(text));
	
	mod_synth_modulator_event_int(_ENV_1_EVENT, _MOD_ADSR_RELEASE, val);
	adsr1_release_entry = val;
	
	last_modified_adsr = _ENV_1;
	
	update_adsr_plot = true;
}

void Dialog_AnalogSynth::on_adsr2_attack_slider_changed(int val)
{
	char text[64];
	
	ui->verticalSlider_AdsrA_2->blockSignals(true);
	ui->verticalSlider_AdsrA_2->setValue(val);
	ui->verticalSlider_AdsrA_2->blockSignals(false);
	
	sprintf(text,
		"%.2fSec", 
		mod_synth_log_scale_100_float(0.0,
			mod_synth_get_adsr_max_attack_time_sec(),
			10.0,
			val));
	
	ui->lineEdit_AdsrA_2->setText(QString(text));
	
	mod_synth_modulator_event_int(_ENV_2_EVENT, _MOD_ADSR_ATTACK, val);
	adsr2_attack_entry = val;
	
	last_modified_adsr = _ENV_2;
	
	update_adsr_plot = true;
}

void Dialog_AnalogSynth::on_adsr2_decay_slider_changed(int val)
{
	char text[64];
	
	ui->verticalSlider_AdsrD_2->blockSignals(true);
	ui->verticalSlider_AdsrD_2->setValue(val);
	ui->verticalSlider_AdsrD_2->blockSignals(false);
	
	sprintf(text,
		"%.2fSec", 
		mod_synth_log_scale_100_float(0.0,
			mod_synth_get_adsr_max_decay_time_sec(),
			10.0,
			val));
	
	ui->lineEdit_AdsrD_2->setText(QString(text));
	
	mod_synth_modulator_event_int(_ENV_2_EVENT, _MOD_ADSR_DECAY, val);
	adsr2_decay_entry = val;
	
	last_modified_adsr = _ENV_2;
	
	update_adsr_plot = true;
}

void Dialog_AnalogSynth::on_adsr2_sustain_slider_changed(int val)
{
	char text[64];
	
	ui->verticalSlider_AdsrS_2->blockSignals(true);
	ui->verticalSlider_AdsrS_2->setValue(val);
	ui->verticalSlider_AdsrS_2->blockSignals(false);
	
	sprintf(text, "%i%c", val, '%');	
	ui->lineEdit_AdsrS_2->setText(QString(text));
	
	mod_synth_modulator_event_int(_ENV_2_EVENT, _MOD_ADSR_SUSTAIN, val);
	adsr2_sustain_entry = val;
	
	last_modified_adsr = _ENV_2;
	
	update_adsr_plot = true;
}

void Dialog_AnalogSynth::on_adsr2_release_slider_changed(int val)
{
	char text[64];
	
	ui->verticalSlider_AdsrR_2->blockSignals(true);
	ui->verticalSlider_AdsrR_2->setValue(val);
	ui->verticalSlider_AdsrR_2->blockSignals(false);
	
	sprintf(text,
		"%.2fSec", 
		mod_synth_log_scale_100_float(0.0,
			mod_synth_get_adsr_max_release_time_sec(),
			10.0,
			val));
	
	ui->lineEdit_AdsrR_2->setText(QString(text));
	
	mod_synth_modulator_event_int(_ENV_2_EVENT, _MOD_ADSR_RELEASE, val);
	adsr2_release_entry = val;
	
	last_modified_adsr = _ENV_2;
	
	update_adsr_plot = true;
}

void Dialog_AnalogSynth::on_adsr3_attack_slider_changed(int val)
{
	char text[64];
	
	ui->verticalSlider_AdsrA_3->blockSignals(true);
	ui->verticalSlider_AdsrA_3->setValue(val);
	ui->verticalSlider_AdsrA_3->blockSignals(false);
	
	sprintf(text,
		"%.2fSec", 
		mod_synth_log_scale_100_float(0.0,
			mod_synth_get_adsr_max_attack_time_sec(),
			10.0,
			val));
	
	ui->lineEdit_AdsrA_3->setText(QString(text));
	
	mod_synth_modulator_event_int(_ENV_3_EVENT, _MOD_ADSR_ATTACK, val);
	adsr3_attack_entry = val;
	
	last_modified_adsr = _ENV_3;
	
	update_adsr_plot = true;
}

void Dialog_AnalogSynth::on_adsr3_decay_slider_changed(int val)
{
	char text[64];
	
	ui->verticalSlider_AdsrD_3->blockSignals(true);
	ui->verticalSlider_AdsrD_3->setValue(val);
	ui->verticalSlider_AdsrD_3->blockSignals(false);
	
	sprintf(text,
		"%.2fSec", 
		mod_synth_log_scale_100_float(0.0,
			mod_synth_get_adsr_max_decay_time_sec(),
			10.0,
			val));
	
	ui->lineEdit_AdsrD_3->setText(QString(text));
	
	mod_synth_modulator_event_int(_ENV_3_EVENT, _MOD_ADSR_DECAY, val);
	adsr3_decay_entry = val;
	
	last_modified_adsr = _ENV_3;
	
	update_adsr_plot = true;
}

void Dialog_AnalogSynth::on_adsr3_sustain_slider_changed(int val)
{
	char text[64];
	
	ui->verticalSlider_AdsrS_3->blockSignals(true);
	ui->verticalSlider_AdsrS_3->setValue(val);
	ui->verticalSlider_AdsrS_3->blockSignals(false);
	
	sprintf(text, "%i%c", val, '%');	
	ui->lineEdit_AdsrS_3->setText(QString(text));
	
	mod_synth_modulator_event_int(_ENV_3_EVENT, _MOD_ADSR_SUSTAIN, val);
	adsr3_sustain_entry = val;
	
	last_modified_adsr = _ENV_3;
	
	update_adsr_plot = true;
}

void Dialog_AnalogSynth::on_adsr3_release_slider_changed(int val)
{
	char text[64];
	
	ui->verticalSlider_AdsrR_3->blockSignals(true);
	ui->verticalSlider_AdsrR_3->setValue(val);
	ui->verticalSlider_AdsrR_3->blockSignals(false);
	
	sprintf(text,
		"%.2fSec", 
		mod_synth_log_scale_100_float(0.0,
			mod_synth_get_adsr_max_release_time_sec(),
			10.0,
			val));
	
	ui->lineEdit_AdsrR_3->setText(QString(text));
	
	mod_synth_modulator_event_int(_ENV_3_EVENT, _MOD_ADSR_RELEASE, val);
	adsr3_release_entry = val;
	
	last_modified_adsr = _ENV_3;
	
	update_adsr_plot = true;
}

void Dialog_AnalogSynth::on_adsr4_attack_slider_changed(int val)
{
	char text[64];
	
	ui->verticalSlider_AdsrA_4->blockSignals(true);
	ui->verticalSlider_AdsrA_4->setValue(val);
	ui->verticalSlider_AdsrA_4->blockSignals(false);
	
	sprintf(text,
		"%.2fSec", 
		mod_synth_log_scale_100_float(0.0,
			mod_synth_get_adsr_max_attack_time_sec(),
			10.0,
			val));
	
	ui->lineEdit_AdsrA_4->setText(QString(text));
	
	mod_synth_modulator_event_int(_ENV_4_EVENT, _MOD_ADSR_ATTACK, val);
	adsr4_attack_entry = val;
	
	last_modified_adsr = _ENV_4;
	
	update_adsr_plot = true;
}

void Dialog_AnalogSynth::on_adsr4_decay_slider_changed(int val)
{
	char text[64];
	
	ui->verticalSlider_AdsrD_4->blockSignals(true);
	ui->verticalSlider_AdsrD_4->setValue(val);
	ui->verticalSlider_AdsrD_4->blockSignals(false);
	
	sprintf(text,
		"%.2fSec", 
		mod_synth_log_scale_100_float(0.0,
			mod_synth_get_adsr_max_decay_time_sec(),
			10.0,
			val));
	
	ui->lineEdit_AdsrD_4->setText(QString(text));
	
	mod_synth_modulator_event_int(_ENV_4_EVENT, _MOD_ADSR_DECAY, val);
	adsr4_decay_entry = val;
	
	last_modified_adsr = _ENV_4;
	
	update_adsr_plot = true;
}

void Dialog_AnalogSynth::on_adsr4_sustain_slider_changed(int val)
{
	char text[64];
	
	ui->verticalSlider_AdsrS_4->blockSignals(true);
	ui->verticalSlider_AdsrS_4->setValue(val);
	ui->verticalSlider_AdsrS_4->blockSignals(false);
	
	sprintf(text, "%i%c", val, '%');	
	ui->lineEdit_AdsrS_4->setText(QString(text));
	
	mod_synth_modulator_event_int(_ENV_4_EVENT, _MOD_ADSR_SUSTAIN, val);
	adsr4_sustain_entry = val;
	
	last_modified_adsr = _ENV_4;
	
	update_adsr_plot = true;
}

void Dialog_AnalogSynth::on_adsr4_release_slider_changed(int val)
{
	char text[64];
	
	ui->verticalSlider_AdsrR_4->blockSignals(true);
	ui->verticalSlider_AdsrR_4->setValue(val);
	ui->verticalSlider_AdsrR_4->blockSignals(false);
	
	sprintf(text,
		"%.2fSec", 
		mod_synth_log_scale_100_float(0.0,
			mod_synth_get_adsr_max_release_time_sec(),
			10.0,
			val));
	
	ui->lineEdit_AdsrR_4->setText(QString(text));
	
	mod_synth_modulator_event_int(_ENV_4_EVENT, _MOD_ADSR_RELEASE, val);
	adsr4_release_entry = val;
	
	last_modified_adsr = _ENV_4;
	
	update_adsr_plot = true;
}

void Dialog_AnalogSynth::on_adsr5_attack_slider_changed(int val)
{
	char text[64];
	
	ui->verticalSlider_AdsrA_5->blockSignals(true);
	ui->verticalSlider_AdsrA_5->setValue(val);
	ui->verticalSlider_AdsrA_5->blockSignals(false);
	
	sprintf(text,
		"%.2fSec", 
		mod_synth_log_scale_100_float(0.0,
			mod_synth_get_adsr_max_attack_time_sec(),
			10.0,
			val));
	
	ui->lineEdit_AdsrA_5->setText(QString(text));
	
	mod_synth_modulator_event_int(_ENV_5_EVENT, _MOD_ADSR_ATTACK, val);
	adsr5_attack_entry = val;
	
	last_modified_adsr = _ENV_5;
	
	update_adsr_plot = true;
}

void Dialog_AnalogSynth::on_adsr5_decay_slider_changed(int val)
{
	char text[64];
	
	ui->verticalSlider_AdsrD_5->blockSignals(true);
	ui->verticalSlider_AdsrD_5->setValue(val);
	ui->verticalSlider_AdsrD_5->blockSignals(false);
	
	sprintf(text,
		"%.2fSec", 
		mod_synth_log_scale_100_float(0.0,
			mod_synth_get_adsr_max_decay_time_sec(),
			10.0,
			val));
	
	ui->lineEdit_AdsrD_5->setText(QString(text));
	
	mod_synth_modulator_event_int(_ENV_5_EVENT, _MOD_ADSR_DECAY, val);
	adsr5_decay_entry = val;
	
	last_modified_adsr = _ENV_5;
	
	update_adsr_plot = true;
}

void Dialog_AnalogSynth::on_adsr5_sustain_slider_changed(int val)
{
	char text[64];
	
	ui->verticalSlider_AdsrS_5->blockSignals(true);
	ui->verticalSlider_AdsrS_5->setValue(val);
	ui->verticalSlider_AdsrS_5->blockSignals(false);
	
	sprintf(text, "%i%c", val, '%');	
	ui->lineEdit_AdsrS_5->setText(QString(text));
	
	mod_synth_modulator_event_int(_ENV_5_EVENT, _MOD_ADSR_SUSTAIN, val);
	adsr5_sustain_entry = val;
	
	last_modified_adsr = _ENV_5;
	
	update_adsr_plot = true;
}

void Dialog_AnalogSynth::on_adsr5_release_slider_changed(int val)
{
	char text[64];
	
	ui->verticalSlider_AdsrR_5->blockSignals(true);
	ui->verticalSlider_AdsrR_5->setValue(val);
	ui->verticalSlider_AdsrR_5->blockSignals(false);
	
	sprintf(text,
		"%.2fSec", 
		mod_synth_log_scale_100_float(0.0,
			mod_synth_get_adsr_max_release_time_sec(),
			10.0,
			val));
	
	ui->lineEdit_AdsrR_5->setText(QString(text));
	
	mod_synth_modulator_event_int(_ENV_5_EVENT, _MOD_ADSR_RELEASE, val);
	adsr5_release_entry = val;
	
	last_modified_adsr = _ENV_5;
	
	update_adsr_plot = true;
}

void Dialog_AnalogSynth::on_adsr6_attack_slider_changed(int val)
{
	char text[64];
	
	ui->verticalSlider_AdsrA_6->blockSignals(true);
	ui->verticalSlider_AdsrA_6->setValue(val);
	ui->verticalSlider_AdsrA_6->blockSignals(false);
	
	sprintf(text,
		"%.2fSec", 
		mod_synth_log_scale_100_float(0.0,
			mod_synth_get_adsr_max_attack_time_sec(),
			10.0,
			val));
	
	ui->lineEdit_AdsrA_6->setText(QString(text));
	
	mod_synth_modulator_event_int(_ENV_6_EVENT, _MOD_ADSR_ATTACK, val);
	adsr6_attack_entry = val;
	
	last_modified_adsr = _ENV_6;
	
	update_adsr_plot = true;
}

void Dialog_AnalogSynth::on_adsr6_decay_slider_changed(int val)
{
	char text[64];
	
	ui->verticalSlider_AdsrD_6->blockSignals(true);
	ui->verticalSlider_AdsrD_6->setValue(val);
	ui->verticalSlider_AdsrD_6->blockSignals(false);
	
	sprintf(text,
		"%.2fSec", 
		mod_synth_log_scale_100_float(0.0,
			mod_synth_get_adsr_max_decay_time_sec(),
			10.0,
			val));
	
	ui->lineEdit_AdsrD_6->setText(QString(text));
	
	mod_synth_modulator_event_int(_ENV_6_EVENT, _MOD_ADSR_DECAY, val);
	adsr6_decay_entry = val;
	
	last_modified_adsr = _ENV_6;
	update_adsr_plot = true;
}

void Dialog_AnalogSynth::on_adsr6_sustain_slider_changed(int val)
{
	char text[64];
	
	ui->verticalSlider_AdsrS_6->blockSignals(true);
	ui->verticalSlider_AdsrS_6->setValue(val);
	ui->verticalSlider_AdsrS_6->blockSignals(false);
	
	sprintf(text, "%i%c", val, '%');	
	ui->lineEdit_AdsrS_6->setText(QString(text));
	
	mod_synth_modulator_event_int(_ENV_6_EVENT, _MOD_ADSR_SUSTAIN, val);
	adsr6_sustain_entry = val;
	
	last_modified_adsr = _ENV_6;
	update_adsr_plot = true;
}

void Dialog_AnalogSynth::on_adsr6_release_slider_changed(int val)
{
	char text[64];
	
	ui->verticalSlider_AdsrR_6->blockSignals(true);
	ui->verticalSlider_AdsrR_6->setValue(val);
	ui->verticalSlider_AdsrR_6->blockSignals(false);
	
	sprintf(text,
		"%.2fSec", 
		mod_synth_log_scale_100_float(0.0,
			mod_synth_get_adsr_max_release_time_sec(),
			10.0,
			val));
	
	ui->lineEdit_AdsrR_6->setText(QString(text));
	
	mod_synth_modulator_event_int(_ENV_6_EVENT, _MOD_ADSR_RELEASE, val);
	adsr6_release_entry = val;
	
	last_modified_adsr = _ENV_6;
	update_adsr_plot = true;
}

