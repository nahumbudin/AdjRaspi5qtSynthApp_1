/**
* @file		Dialog_InstrumentConnections.h
*	@author		Nahum Budin
*	@date		5-Jul-2024
*	@version	1.0
*
*	@brief		Used for selecting MIDI inputs and JackAudio outputs,
*				as well as the active MIDI channels
*
*/

#pragma once

#include <QDialog>
#include <QCheckBox>

#include "MainWindow.h"

#include "libAdjRaspi5SynthAPI.h"

#define _MIDI_PANNEL_SELECTED	0
#define _JACK_PANNEL_SELECTED	1

namespace Ui
{
	class Dialog_InstrumentConnections;
}

class Dialog_InstrumentConnections : public QDialog
{
	Q_OBJECT
		
public :
	explicit Dialog_InstrumentConnections(QWidget *parent = 0,
		QString inst_name = "");
	
	~Dialog_InstrumentConnections();
	
	static Dialog_InstrumentConnections *get_instance();

	
	void control_box_ui_update_callback(int evnt, uint16_t val);

	void update();
	
	static bool dialog_is_open;
	
public slots:
	void closeEvent(QCloseEvent *event);

protected slots:
	
	void on_dialog_ok();
	void on_dialog_refresh();
	
	void on_select_MIDI_pannel_clicked();
	void on_select_Jack_pannel_clicked();
	
	void on_select_midi_in_toggled_1(bool sel);
	void on_select_midi_in_toggled_2(bool sel);
	void on_select_midi_in_toggled_3(bool sel);
	void on_select_midi_in_toggled_4(bool sel);
	void on_select_midi_in_toggled_5(bool sel);
	void on_select_midi_in_toggled_6(bool sel);
	void on_select_midi_in_toggled_7(bool sel);
	void on_select_midi_in_toggled_8(bool sel);
	void on_select_midi_in_toggled_9(bool sel);
	void on_select_midi_in_toggled_10(bool sel);
	void on_select_midi_in_toggled_11(bool sel);
	void on_select_midi_in_toggled_12(bool sel);
	
	void on_select_jack_out_toggled_1(bool sel);
	void on_select_jack_out_toggled_2(bool sel);
	void on_select_jack_out_toggled_3(bool sel);
	void on_select_jack_out_toggled_4(bool sel);
	void on_select_jack_out_toggled_5(bool sel);
	void on_select_jack_out_toggled_6(bool sel);
	void on_select_jack_out_toggled_7(bool sel);
	void on_select_jack_out_toggled_8(bool sel);
	void on_select_jack_out_toggled_9(bool sel);
	void on_select_jack_out_toggled_10(bool sel);
	void on_select_jack_out_toggled_11(bool sel);
	void on_select_jack_out_toggled_12(bool sel);
	
	void on_select_active_midi_channel_1(bool sel);
	void on_select_active_midi_channel_2(bool sel);
	void on_select_active_midi_channel_3(bool sel);
	void on_select_active_midi_channel_4(bool sel);
	void on_select_active_midi_channel_5(bool sel);
	void on_select_active_midi_channel_6(bool sel);
	void on_select_active_midi_channel_7(bool sel);
	void on_select_active_midi_channel_8(bool sel);
	void on_select_active_midi_channel_9(bool sel);
	void on_select_active_midi_channel_10(bool sel);
	void on_select_active_midi_channel_11(bool sel);
	void on_select_active_midi_channel_12(bool sel);
	void on_select_active_midi_channel_13(bool sel);
	void on_select_active_midi_channel_14(bool sel);
	void on_select_active_midi_channel_15(bool sel);
	void on_select_active_midi_channel_16(bool sel);
	
private:
	
	uint16_t build_channels_mask(uint16_t mask, int chan, bool en);
	
	Ui::Dialog_InstrumentConnections *ui;
	
	QString instrument_name;
	int client_number;
	
	QCheckBox *midi_input_clients_select_pb[12];
	QCheckBox *jack_output_clients_select_pb[12];
	QCheckBox *active_midi_channel_pb[16];
	
	std::string jack_output_client_names[6];
	std::string jack_output_client_port_names[6];
	
	static Dialog_InstrumentConnections *dialog_InstrumentConnectionsInstance;
	
	int selected_pannel;
	
	uint16_t active_midi_channels;
	
	std::string alsa_connections_names[12];
	std::string jack_connections_names[12];		
};
