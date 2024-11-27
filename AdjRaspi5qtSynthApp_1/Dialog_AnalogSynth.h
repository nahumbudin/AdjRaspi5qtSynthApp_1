/**
* @file		Dialog_AnalogSynth.h
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

#pragma once

#include <QDialog>
#include <QTHread>
#include <QSlider>

#include "libAdjRaspi5SynthAPI.h"
#include "Defs.h"

#include "qcustomplot.h"

namespace Ui
{
	class Dialog_AnalogSynth;
}

class Dialog_AnalogSynth : public QDialog
{
	Q_OBJECT
		
public :
	
	~Dialog_AnalogSynth();
	
	static Dialog_AnalogSynth *get_instance(QWidget *parent = 0);
	
	void control_box_ui_update_callback(int evnt, uint16_t val);
	
	void control_box_events_handler_osc_1(int evnt, uint16_t val);
	void control_box_events_handler_osc_2_noise(int evnt, uint16_t val);
	void control_box_events_handler_mso(int evnt, uint16_t val);
	void control_box_events_handler_kps(int evnt, uint16_t val);
	void control_box_events_handler_pad(int evnt, uint16_t val);
	void control_box_events_handler_filters_amps(int evnt, uint16_t val);
	
	void osc1_set_unison_mode(int mode);
	
		
public slots :	
	void closeEvent(QCloseEvent *event);
	virtual void update_gui(); // Called by a Timer

protected:
	void timerEvent(QTimerEvent *event);
	
protected slots:
	void on_dialog_close();
	
	void on_tab_selected(int tab);
	
	
	void on_osc1_enable_changed(bool en);
	
	void on_osc1_waveform_symetry_spinbox_changed(int val);
	void on_osc1_send_filter_1_spinbox_changed(int val);
	void on_osc1_send_filter_2_spinbox_changed(int val);
	void on_osc1_freq_mod_lfo_level_spinbox_changed(int val);
	void on_osc1_freq_mod_adsr_level_spinbox_changed(int val);
	void on_osc1_pwm_mod_lfo_level_spinbox_changed(int val);
	void on_osc1_pwm_mod_adsr_level_spinbox_changed(int val);
	void on_osc1_amp_mod_lfo_level_spinbox_changed(int val);
	void on_osc1_amp_mod_adsr_level_spinbox_changed(int val);
	
	void on_osc1_unison_level_1_spinbox_changed(int val);
	void on_osc1_unison_level_2_spinbox_changed(int val);
	void on_osc1_unison_level_3_spinbox_changed(int val);
	void on_osc1_unison_level_4_spinbox_changed(int val);
	void on_osc1_unison_level_5_spinbox_changed(int val);
	void on_osc1_unison_level_6_spinbox_changed(int val);
	void on_osc1_unison_level_7_spinbox_changed(int val);
	void on_osc1_unison_level_8_spinbox_changed(int val);
	void on_osc1_unison_level_9_spinbox_changed(int val);
	void on_osc1_unison_distortion_spinbox_changed(int val);
	void on_osc1_unison_detune_spinbox_changed(int val);
	
	void on_osc1_waveform_symetry_slider_cahanged(int val);
	
	void on_osc1_unison_sqare_enable_changed(bool en);
	void on_osc1_unison_level_1_slider_changed(int val);
	void on_osc1_unison_level_2_slider_changed(int val);
	void on_osc1_unison_level_3_slider_changed(int val);
	void on_osc1_unison_level_4_slider_changed(int val);
	void on_osc1_unison_level_5_slider_changed(int val);
	void on_osc1_unison_level_6_slider_changed(int val);
	void on_osc1_unison_level_7_slider_changed(int val);
	void on_osc1_unison_level_8_slider_changed(int val);
	void on_osc1_unison_level_9_slider_changed(int val);
	void on_osc1_unison_distortion_slider_changed(int val);
	void on_osc1_unison_detune_slider_changed(int val);
	
	void on_osc1_send_filter_1_dial_changed(int val);
	void on_osc1_send_filter_2_dial_changed(int val);
	void on_osc1_freq_mod_lfo_level_dial_changed(int val);
	void on_osc1_freq_mod_adsr_level_dial_changed(int val);
	void on_osc1_pwm_mod_lfo_level_dial_changed(int val);
	void on_osc1_pwm_mod_adsr_level_dial_changed(int val);
	void on_osc1_amp_mod_lfo_level_dial_changed(int val);
	void on_osc1_amp_mod_adsr_level_dial_changed(int val);
	
	void on_osc1_waveform_combobox_changed(int val);
	void on_osc1_tune_octave_combobox_changed(int val);
	void on_osc1_tune_semitones_combobox_changed(int val);
	void on_osc1_tune_cents_combobox_changed(int val);
	void on_osc1_freq_mod_lfo_combobox_changed(int val);
	void on_osc1_freq_mod_adsr_combobox_changed(int val);
	void on_osc1_pwm_mod_lfo_combobox_changed(int val);
	void on_osc1_pwm_mod_adsr_combobox_changed(int val);
	void on_osc1_amp_mod_lfo_combobox_changed(int val);
	void on_osc1_amp_mod_adsr_combobox_changed(int val);
	void on_osc1_hammond_percussion_mode_combobox_changed(int val);
	void on_osc1_unison_mode_combobox_changed(int val);
	
	
	void on_osc2_enable_changed(bool en);
	
	void on_osc2_waveform_symetry_spinbox_changed(int val);
	void on_osc2_send_filter_1_spinbox_changed(int val);
	void on_osc2_send_filter_2_spinbox_changed(int val);
	void on_osc2_freq_mod_lfo_level_spinbox_changed(int val);
	void on_osc2_freq_mod_adsr_level_spinbox_changed(int val);
	void on_osc2_pwm_mod_lfo_level_spinbox_changed(int val);
	void on_osc2_pwm_mod_adsr_level_spinbox_changed(int val);
	void on_osc2_amp_mod_lfo_level_spinbox_changed(int val);
	void on_osc2_amp_mod_adsr_level_spinbox_changed(int val);
	
	void on_osc2_send_filter_1_dial_changed(int val);
	void on_osc2_send_filter_2_dial_changed(int val);
	void on_osc2_freq_mod_lfo_level_dial_changed(int val);
	void on_osc2_freq_mod_adsr_level_dial_changed(int val);
	void on_osc2_pwm_mod_lfo_level_dial_changed(int val);
	void on_osc2_pwm_mod_adsr_level_dial_changed(int val);
	void on_osc2_amp_mod_lfo_level_dial_changed(int val);
	void on_osc2_amp_mod_adsr_level_dial_changed(int val);
	
	void on_osc2_waveform_symetry_slider_cahanged(int val);
	
	void on_osc2_waveform_combobox_changed(int val);
	void on_osc2_tune_octave_combobox_changed(int val);
	void on_osc2_tune_semitones_combobox_changed(int val);
	void on_osc2_tune_cents_combobox_changed(int val);
	void on_osc2_freq_mod_lfo_combobox_changed(int val);
	void on_osc2_freq_mod_adsr_combobox_changed(int val);
	void on_osc2_pwm_mod_lfo_combobox_changed(int val);
	void on_osc2_pwm_mod_adsr_combobox_changed(int val);
	void on_osc2_amp_mod_lfo_combobox_changed(int val);
	void on_osc2_amp_mod_adsr_combobox_changed(int val);
	
	void on_osc2_sync_on_osc1_enable_changed(bool en);
	
	
	void on_noise_enable_changed(bool en);
	
	void on_noise_send_filter_1_spinbox_changed(int val);
	void on_noise_send_filter_2_spinbox_changed(int val);
	void on_noise_amp_mod_lfo_level_spinbox_changed(int val);
	void on_noise_amp_mod_adsr_level_spinbox_changed(int val);
	
	void on_noise_send_filter_1_dial_changed(int val);
	void on_noise_send_filter_2_dial_changed(int val);
	void on_noise_amp_mod_lfo_level_dial_changed(int val);
	void on_noise_amp_mod_adsr_level_dial_changed(int val);
	
	void on_noise_color_combobox_changed(int val);
	void on_noise_amp_mod_lfo_combobox_changed(int val);
	void on_noise_amp_mod_adsr_combobox_changed(int val);
	
	void on_mso_point_a_slider_moved(int val);
	void on_mso_point_b_slider_moved(int val);
	void on_mso_point_c_slider_moved(int val);
	void on_mso_point_d_slider_moved(int val);
	void on_mso_point_e_slider_moved(int val);
	void on_mso_point_f_slider_moved(int val);
	void on_mso_symetry_slider_changed(int val);

	void on_mso_detune_octave_combobox_changed(int val);
	void on_mso_detune_semitones_combobox_changed(int val);
	void on_mso_detune_cents_combobox_changed(int val);
	
	void on_mso_freq_mod_lfo_combobox_changed(int val);
	void on_mso_freq_mod_env_combobox_changed(int val);
	void on_mso_pwm_mod_lfo_combobox_changed(int val);
	void on_mso_pwm_mod_env_combobox_changed(int val);
	void on_mso_amp_mod_lfo_combobox_changed(int val);
	void on_mso_amp_mod_env_combobox_changed(int val);
	void on_mso_preset_combobox_changed(int val);
	
	void on_mso_send_filter_1_dial_changed(int val);
	void on_mso_send_filter_2_dial_changed(int val);
	void on_mso_freq_mod_lfo_level_dial_changed(int val);
	void on_mso_freq_mod_env_level_dial_changed(int val);
	void on_mso_pwm_mod_lfo_level_dial_changed(int val);
	void on_mso_pwm_mod_env_level_dial_changed(int val);
	void on_mso_amp_mod_lfo_level_dial_changed(int val);
	void on_mso_amp_mod_env_level_dial_changed(int val);
		 	   
	void on_mso_enable_checkbox_changed(bool val);
	
	void on_karplus_excitation_waveform_combobox_changed(int val);
	void on_karplus_excitation_waveform_variations_slider_changed(int val);
	void on_karplus_string_damping_slider_changed(int val);
	void on_karplus_string_damping_variation_slider_changed(int val);
	void on_karplus_string_damping_calc_mode_combobox_hanged(int val);
	void on_karplus_pluck_damping_slider_changed(int val);
	void on_karplus_pluck_damping_variation_slider_changed(int val);
	void on_karplus_on_decay_slider_changed(int val);
	void on_karplus_off_decay_slider_changed(int val);
	void on_karplus_send_filter1_dial_changed(int val);
	void on_karplus_send_filter2_dial_changed(int val);
	
	void on_karplus_enable_checkbox_changed(bool val);
	
	void on_pad_enable_checkbox_changed(bool val);

	void on_pad_detune_octave_combobox_changed(int val);
	void on_pad_detune_semitones_combobox_changed(int val);
	void on_pad_detune_cents_combobox_changed(int val);
	void on_pad_send_filter1_dial_changed(int val);
	void on_pad_send_filter2_dial_changed(int val);
	void on_pad_freq_mod_lfo_combobox_changed(int val);
	void on_pad_freq_mod_lfo_level_dial_changed(int val);
	void on_pad_freq_mod_env_combobox_changed(int val);
	void on_pad_freq_mod_env_level_dial_changed(int val);
	void on_pad_amp_mod_lfo_combobox_changed(int val);
	void on_pad_amp_mod_lfo_level_dial_changed(int val);
	void on_pad_amp_mod_env_combobox_changed(int val);
	void on_pad_amp_mod_env_level_dial_changed(int val);

	void on_pad_quality_combobox_changed(int val);
	void on_pad_base_note_combobox_changed(int val);
	void on_pad_base_width_slider_changed(int val);
	void on_pad_shape_combobox_changed(int val);
	void on_pad_shape_cutoff_combobox_changed(int val);
	void on_pad_generate_pushbutton_clicked();

	void on_pad_harmony1_level_slider_changed(int val);
	void on_pad_harmony2_level_slider_changed(int val);
	void on_pad_harmony3_level_slider_changed(int val);
	void on_pad_harmony4_level_slider_changed(int val);
	void on_pad_harmony5_level_slider_changed(int val);
	void on_pad_harmony6_level_slider_changed(int val);
	void on_pad_harmony7_level_slider_changed(int val);
	void on_pad_harmony8_level_slider_changed(int val);
	void on_pad_harmony9_level_slider_changed(int val);
	void on_pad_harmony10_level_slider_changed(int val);

	void on_pad_harmonies_detune_slider_changed(int val);
	
	void on_filter1_freq_dial_changed(int val);
	void on_filter1_q_dial_changed(int val);
	void on_filter1_octave_dial_changed(int val);
	void on_filter1_kbd_track_dial_changed(int val);
	void on_filter1_band_combo_hanged(int val);
	void on_filter1_freq_mod_lfo_combo_changed(int val);
	void on_filter1_freq_mod_level_lfo_dial_changed(int val);
	void on_filter1_freq_mod_adsr_combo_changed(int val);
	void on_filter1_freq_mod_level_adsr_dial_hanged(int val);

	void on_filter2_freq_dial_changed(int val);
	void on_filter2_q_dial_changed(int val);
	void on_filter2_octave_dial_changed(int val);
	void on_filter2_kbd_track_dial_changed(int val);
	void on_filter2_band_combo_hanged(int val);
	void on_filter2_freq_mod_lfo_combo_changed(int val);
	void on_filter2_freq_mod_level_lfo_dial_changed(int val);
	void on_filter2_freq_mod_adsr_combo_changed(int val);
	void on_filter2_freq_mod_level_adsr_dial_hanged(int val);
	void on_filter2_track_filter1_checkbox_changed(bool val);
	
	void on_amp1_level_dial_hanged(int val);
	void on_amp1_pan_dial_changed(int val);
	void on_amp1_send_dial_changed(int val);
	void on_amp1_pan_mod_lfo_combo_changed(int val);
	void on_amp1_pan_mod_level_lfo_dial_changed(int val);

	void on_amp2_level_dial_hanged(int val);
	void on_amp2_pan_dial_changed(int val);
	void on_amp2_send_dial_changed(int val);
	void on_amp2_pan_mod_lfo_combo_changed(int val);
	void on_amp2_pan_mod_level_lfo_dial_changed(int val);

	void on_fixed_amp_checkbox_Changed(bool val);

	
	
private:
	
	explicit Dialog_AnalogSynth(QWidget *parent = 0);
	
	Ui::Dialog_AnalogSynth *ui;
	
	static Dialog_AnalogSynth *dialog_analog_synth_instance;
	
	int active_tab, prev_active_tab;
	int active_frames_group_osc1, prev_active_frames_group_osc1;
	int active_frames_group_osc2noise, prev_active_frames_group_osc2noise;
	int active_frames_group_mso, prev_active_frames_group_mso;
	int active_frames_group_kps, prev_active_frames_group_kps;
	int active_frames_group_pad, prev_active_frames_group_pad;
	int active_frames_group_filters_amps, prev_active_frames_group_filters_amps;
	
	bool osc1_enabled = true;
	bool osc1_unison_square = false;
	
	int osc1_send_filter_1_level = 0;
	int osc1_send_filter_2_level = 0;
	
	int osc1_unison_levels[9] = { 0 };
	int osc_1_unison_distortion = 0;
	int osc_1_unison_detune = 0;
	
	int osc1_unison_mode = _OSC_UNISON_MODE_12345678;
	int osc1_hammond_percussion_mode = _HAMMOND_PERCUSION_MODE_OFF;
	
	int osc1_waveform = _OSC_WAVEFORM_SINE;
	int osc1_waveform_symetry = 50;
	
	int osc1_tune_octave = 0;
	int osc1_tune_semitones = 0;
	int osc1_tune_cents = 0;
	
	int osc1_freq_mod_lfo_level = 0; 
	int osc1_freq_mod_adsr_level = 0;
	int osc1_freq_mod_lfo_num = _LFO_NONE;
	int osc1_freq_mod_adsr_num = _ENV_NONE;
	
	int osc1_pwm_mod_lfo_level = 0; 
	int osc1_pwm_mod_adsr_level = 0;
	int osc1_pwm_mod_lfo_num = _LFO_NONE;
	int osc1_pwm_mod_adsr_num = _ENV_NONE;
	
	int osc1_amp_mod_lfo_level = 0; 
	int osc1_amp_mod_adsr_level = 0;
	int osc1_amp_mod_lfo_num = _LFO_NONE;
	int osc1_amp_mod_adsr_num = _ENV_NONE;
	
	bool osc2_enabled = false;
	
	int osc2_send_filter_1_level = 0;
	int osc2_send_filter_2_level = 0;
	
	int osc2_waveform = _OSC_WAVEFORM_SINE;
	int osc2_waveform_symetry = 50;
	
	int osc2_tune_octave = 0;
	int osc2_tune_semitones = 0;
	int osc2_tune_cents = 0;
	
	int osc2_freq_mod_lfo_level = 0; 
	int osc2_freq_mod_adsr_level = 0;
	int osc2_freq_mod_lfo_num = _LFO_NONE;
	int osc2_freq_mod_adsr_num = _ENV_NONE;
	
	int osc2_pwm_mod_lfo_level = 0; 
	int osc2_pwm_mod_adsr_level = 0;
	int osc2_pwm_mod_lfo_num = _LFO_NONE;
	int osc2_pwm_mod_adsr_num = _ENV_NONE;
	
	int osc2_amp_mod_lfo_level = 0; 
	int osc2_amp_mod_adsr_level = 0;
	int osc2_amp_mod_lfo_num = _LFO_NONE;
	int osc2_amp_mod_adsr_num = _ENV_NONE;
	
	bool osc_2_sync_on_osc_1 = false;
	
	bool noise_enabled = false;
	
	int noise_send_filter_1_level = 0;
	int noise_send_filter_2_level = 0;
	
	int noise_amp_mod_lfo_level = 0; 
	int noise_amp_mod_adsr_level = 0;
	int noise_amp_mod_lfo_num = _LFO_NONE;
	int noise_amp_mod_adsr_num = _ENV_NONE;
	
	int noise_color = _WHITE_NOISE;
	
	bool mso_enabled = false;
	bool update_mso_plot = true;
	
	int mso_pos_a, mso_pos_b, mso_pos_c, mso_pos_d, mso_pos_e, mso_pos_f;
	int mso_symetry = 70;
	int mso_tune_octave = 0;
	int mso_tune_semitones = 0;
	int mso_tune_cents = 0;
	int mso_send_filter_1_level = 0;
	int mso_send_filter_2_level = 0;
	
	int mso_freq_mod_lfo_level = 0; 
	int mso_freq_mod_adsr_level = 0;
	int mso_freq_mod_lfo_num = _LFO_NONE;
	int mso_freq_mod_adsr_num = _ENV_NONE;
	
	int mso_pwm_mod_lfo_level = 0; 
	int mso_pwm_mod_adsr_level = 0;
	int mso_pwm_mod_lfo_num = _LFO_NONE;
	int mso_pwm_mod_adsr_num = _ENV_NONE;
	
	int mso_amp_mod_lfo_level = 0; 
	int mso_amp_mod_adsr_level = 0;
	int mso_amp_mod_lfo_num = _LFO_NONE;
	int mso_amp_mod_adsr_num = _ENV_NONE;
	
	int mso_preset = 0;
	
	bool mso_replot_waveform = false;
	
	bool kps_enabled = false;
	
	int kps_excitation_waveform = _KARPLUS_STRONG_EXCITATION_WHITE_NOISE;
	int kps_string_dump_calculation_mode = _KARPLUS_STRONG_STRING_DAMPING_CALC_DIRECT;
	int kps_waveform_variations = 0;
	int kps_string_damping = 0;
	int kps_string_damping_variations = 0;
	int kps_pluck_damping = 0;
	int kps_pluck_damping_variations = 0;
	int kps_on_decay = 0;
	int kps_off_decay = 0;
	int kps_send_filter_1_level = 0;
	int kps_send_filter_2_level = 0;
	
	bool pad_enabled = false;
	bool update_profile_plot = true;
	bool update_spectrum_plot = true;
	
	int pad_tune_octave = 0;
	int pad_tune_semitones = 0;
	int pad_tune_cents = 0;
	int pad_send_filter_1_level = 0;
	int pad_send_filter_2_level = 0;
	
	int pad_freq_mod_lfo_level = 0; 
	int pad_freq_mod_adsr_level = 0;
	int pad_freq_mod_lfo_num = _LFO_NONE;
	int pad_freq_mod_adsr_num = _ENV_NONE;
	
	int pad_amp_mod_lfo_level = 0; 
	int pad_amp_mod_adsr_level = 0;
	int pad_amp_mod_lfo_num = _LFO_NONE;
	int pad_amp_mod_adsr_num = _ENV_NONE;
	
	int pad_quality = 0;
	int pad_base_note = 0;
	int pad_shape = 0;
	int pad_shape_cutoff = 0;
	
	int pad_base_width = 1;
	
	int pad_harmony_1_level = 100;
	int pad_harmony_2_level = 0;
	int pad_harmony_3_level = 30;
	int pad_harmony_4_level = 0;
	int pad_harmony_5_level = 0;
	int pad_harmony_6_level = 0;
	int pad_harmony_7_level = 0;
	int pad_harmony_8_level = 0;
	int pad_harmony_9_level = 0;
	int pad_harmony_10_level = 0;
	int pad_harmony_detune = 0;
	
	int filter1_frequency_entry = 0;
	int filter1_q_entry = 1;
	int filter1_octave_entry = 0;
	int filter1_keyboard_track = 100;
	int filter1_band = 0;
	int filter1_freq_mod_lfo = 0;
	int filter1_freq_mod_lfo_level = 0;
	int filter1_freq_mod_adsr = 0;
	int filter1_freq_mod_adsr_level = 0;
	
	
	int filter2_frequency_entry = 0;
	int filter2_q_entry = 1;
	int filter2_octave_entry = 0;
	int filter2_keyboard_track = 100;
	int filter2_band = 0;
	int filter2_freq_mod_lfo = 0;
	int filter2_freq_mod_lfo_level = 0;
	int filter2_freq_mod_adsr = 0;
	int filter2_freq_mod_adsr_level = 0;
	
	bool filter_2_follows_filter_1 = false;
	
	int amp1_level = 50;
	int amp1_pan = 50;
	int amp1_send = 50;
	int amp1_pan_mod_lfo = 0;
	int amp1_pan_mod_lfo_level = 0;
	
	
	int amp2_level = 50;
	int amp2_pan = 50;
	int amp2_send = 50;
	int amp2_pan_mod_lfo = 0;
	int amp2_pan_mod_lfo_level = 0;
	
	bool amp_fixed = false;
	
	
	void start_update_timer(int interval);
	
	void set_osc1_signals_connections();
	void init_osc1_combboxes_and_labels();
	
	void set_osc2_signals_connections();
	void init_osc2_combboxes_and_labels();
	
	void set_noise_signals_connections();
	void init_noise_combboxes_and_labels();
	
	void set_mso_signals_connections();
	void init_mso_combboxes_and_labels();
	
	void set_kps_signals_connections();
	void init_kps_combboxes_and_labels();
	
	void set_pad_signals_connections();
	void init_pad_combboxes_and_labels();
	
	void set_filters_amps_signals_connections();
	void init_filters_amps_combboxes_and_labels();
	
	void setup_mso_plot(QCustomPlot *custom_plot);
	void update_mso_waveform_plot();
	
	void mso_handle_preset_change(int newPres);
	void mso_set_preset_positions(const int pos[]);
	
	void pad_setup_profile_plot(QCustomPlot *profilePlot);
	void pad_setup_spectrum_plot(QCustomPlot *spectrumPlot);
	
	void pad_replot_profile();
	void pad_replot_spectrum();
	
	void osc1_set_unison_labales(QList<QString> str, uint16_t mask);
	void osc1_set_unison_labales(int mode);
	void osc1_en_dis_sliders(uint16_t mask);
	
	void copy_filter1_to_filter2();
	
	void osc1_update();
	void osc2_update();
	void noise_update();
	void mso_update();
	void kps_update();
	void pad_update();
	void filters_update();
	void amps_update();
	
	QList<QString> string_unison_labels_hammond;
	QList<QString> string_unison_labels_octaves;
	QList<QString> string_unison_labels_c_chord;
	QList<QString> string_unison_labels_cm_chord;
	QList<QString> string_unison_labels_c7_chord;
	QList<QString> string_unison_labels_cm7_chord;
	
	QList<QString> string_waveforms_list;
	QList<QString> string_unison_modes_list;
	QList<QString> string_hammond_modes_list;

	QList<QString> string_unison_labels_harmonized;
	
	QList<QString> string_adsr_values;
	QList<QString> string_lfo_values;
	QList<QString> string_waveforms;
	
	QList<QString> string_noise_colors_list;
	
	QList<QString> string_mso_presets_list;
	
	QList<QString> string_karplus_excitation_waveform_list;
	QList<QString> string_karplus_string_damping_calc_mode_list;
	
	QList<QString> string_pad_qualities_list;
	QList<QString> string_pad_base_notes_list;
	QList<QString> string_pad_shapes_list;
	QList<QString> string_pad_shape_cutoffs_list;
	
	QList<QString> string_filter_bands_list;
	
	QSlider *unison_level_sliders[9];
	
};
