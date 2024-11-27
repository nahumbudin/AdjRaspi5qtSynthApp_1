/**
* @file		Dialog_InstrumentConnections.cpp
*	@author		Nahum Budin
*	@date		5-Jul-2024
*	@version	1.0
*
*	@brief		Used for selecting MIDI inputs and JackAudio outputs,
*				as well as the active MIDI channels
*
*/

#include <time.h>

#include <QString>
#include <QThread>

#include "libAdjRaspi5SynthAPI.h"

#include "Dialog_InstrumentConnections.h"
#include "ui_Dialog_InstrumentConnections.h"

#include "utils.h"

/* Used as a mutex to enable only a single oppened dialog. */
bool Dialog_InstrumentConnections::dialog_is_open;


void connections_control_box_event_update_ui_callback_wrapper(int evnt, uint16_t val)
{
	Dialog_InstrumentConnections::get_instance()->control_box_ui_update_callback(evnt, val);
}

Dialog_InstrumentConnections *Dialog_InstrumentConnections::dialog_InstrumentConnectionsInstance = NULL;

/** Constructor */
Dialog_InstrumentConnections::Dialog_InstrumentConnections(
	QWidget *parent, 
	QString inst_name)
	: QDialog(parent)
	, ui(new Ui::Dialog_InstrumentConnections)
{
	ui->setupUi(this);
	dialog_InstrumentConnectionsInstance = this;
	
	this->setFocus(Qt::ActiveWindowFocusReason);
	
	instrument_name = inst_name;
	
	midi_input_clients_select_pb[0] = ui->checkBox_source_1;
	midi_input_clients_select_pb[1] = ui->checkBox_source_2;
	midi_input_clients_select_pb[2] = ui->checkBox_source_3;
	midi_input_clients_select_pb[3] = ui->checkBox_source_4;
	midi_input_clients_select_pb[4] = ui->checkBox_source_5;
	midi_input_clients_select_pb[5] = ui->checkBox_source_6;
	midi_input_clients_select_pb[6] = ui->checkBox_source_7;
	midi_input_clients_select_pb[7] = ui->checkBox_source_8;
	midi_input_clients_select_pb[8] = ui->checkBox_source_9;
	midi_input_clients_select_pb[9] = ui->checkBox_source_10;
	midi_input_clients_select_pb[10] = ui->checkBox_source_11;
	midi_input_clients_select_pb[11] = ui->checkBox_source_12;
	
	jack_output_clients_select_pb[0] = ui->checkBox_JackOut_1;
	jack_output_clients_select_pb[1] = ui->checkBox_JackOut_2;
	jack_output_clients_select_pb[2] = ui->checkBox_JackOut_3;
	jack_output_clients_select_pb[3] = ui->checkBox_JackOut_4;
	jack_output_clients_select_pb[4] = ui->checkBox_JackOut_5;
	jack_output_clients_select_pb[5] = ui->checkBox_JackOut_6;
	jack_output_clients_select_pb[6] = ui->checkBox_JackOut_7;
	jack_output_clients_select_pb[7] = ui->checkBox_JackOut_8;
	jack_output_clients_select_pb[8] = ui->checkBox_JackOut_9;
	jack_output_clients_select_pb[9] = ui->checkBox_JackOut_10;
	jack_output_clients_select_pb[10] = ui->checkBox_JackOut_11;
	jack_output_clients_select_pb[11] = ui->checkBox_JackOut_12;
	
	active_midi_channel_pb[0] = ui->checkBox_ch_1;
	active_midi_channel_pb[1] = ui->checkBox_ch_2;
	active_midi_channel_pb[2] = ui->checkBox_ch_3;
	active_midi_channel_pb[3] = ui->checkBox_ch_4;
	active_midi_channel_pb[4] = ui->checkBox_ch_5;
	active_midi_channel_pb[5] = ui->checkBox_ch_6;
	active_midi_channel_pb[6] = ui->checkBox_ch_7;
	active_midi_channel_pb[7] = ui->checkBox_ch_8;
	active_midi_channel_pb[8] = ui->checkBox_ch_9;
	active_midi_channel_pb[9] = ui->checkBox_ch_10;
	active_midi_channel_pb[10] = ui->checkBox_ch_11;
	active_midi_channel_pb[11] = ui->checkBox_ch_12;
	active_midi_channel_pb[12] = ui->checkBox_ch_13;
	active_midi_channel_pb[13] = ui->checkBox_ch_14;
	active_midi_channel_pb[14] = ui->checkBox_ch_15;
	active_midi_channel_pb[15] = ui->checkBox_ch_16;
	
	this->ui->label_InstrumentName->setText(instrument_name);
	
	selected_pannel = _MIDI_PANNEL_SELECTED;
	ui->frame_MIDI->setFrameShadow(QFrame::Sunken);
	ui->frame_MIDI->setLineWidth(5);
	ui->frame_MIDI->setMidLineWidth(5);	
	ui->frame_Jack->setFrameShadow(QFrame::Plain);
	ui->frame_Jack->setLineWidth(0);
	ui->frame_Jack->setMidLineWidth(0);
	ui->radioButton_MIDI->setChecked(true);
	ui->radioButton_Jack->setChecked(false);
	
	mod_synth_register_callback_control_box_event_update_ui(
		&connections_control_box_event_update_ui_callback_wrapper);

	update();
	
	connect(ui->pushButton_Ok,
		SIGNAL(clicked()),
		this,
		SLOT(on_dialog_ok()));
	
	connect(ui->pushButton_Refresh,
		SIGNAL(clicked()),
		this,
		SLOT(on_dialog_refresh()));
	
	connect(ui->radioButton_MIDI,
		SIGNAL(clicked()),
		this,
		SLOT(on_select_MIDI_pannel_clicked()));
	
	connect(ui->radioButton_Jack,
		SIGNAL(clicked()),
		this,
		SLOT(on_select_Jack_pannel_clicked()));
	
	connect(ui->checkBox_source_1,
		SIGNAL(toggled(bool)),
		this,
		SLOT(on_select_midi_in_toggled_1(bool)));
	
	connect(ui->checkBox_source_2,
		SIGNAL(toggled(bool)),
		this,
		SLOT(on_select_midi_in_toggled_2(bool)));
	
	connect(ui->checkBox_source_3,
		SIGNAL(toggled(bool)),
		this,
		SLOT(on_select_midi_in_toggled_3(bool)));
	
	connect(ui->checkBox_source_4,
		SIGNAL(toggled(bool)),
		this,
		SLOT(on_select_midi_in_toggled_4(bool)));
	
	connect(ui->checkBox_source_5,
		SIGNAL(toggled(bool)),
		this,
		SLOT(on_select_midi_in_toggled_5(bool)));
	
	connect(ui->checkBox_source_6,
		SIGNAL(toggled(bool)),
		this,
		SLOT(on_select_midi_in_toggled_6(bool)));
	
	connect(ui->checkBox_source_7,
		SIGNAL(toggled(bool)),
		this,
		SLOT(on_select_midi_in_toggled_7(bool)));
	
	connect(ui->checkBox_source_8,
		SIGNAL(toggled(bool)),
		this,
		SLOT(on_select_midi_in_toggled_8(bool)));
	
	connect(ui->checkBox_source_9,
		SIGNAL(toggled(bool)),
		this,
		SLOT(on_select_midi_in_toggled_9(bool)));
	
	connect(ui->checkBox_source_10,
		SIGNAL(toggled(bool)),
		this,
		SLOT(on_select_midi_in_toggled_10(bool)));
	
	connect(ui->checkBox_source_11,
		SIGNAL(toggled(bool)),
		this,
		SLOT(on_select_midi_in_toggled_11(bool)));
	
	connect(ui->checkBox_source_12,
		SIGNAL(toggled(bool)),
		this,
		SLOT(on_select_midi_in_toggled_12(bool)));
	
	connect(ui->checkBox_JackOut_1,
		SIGNAL(toggled(bool)),
		this,
		SLOT(on_select_jack_out_toggled_1(bool)));
	
	connect(ui->checkBox_JackOut_2,
		SIGNAL(toggled(bool)),
		this,
		SLOT(on_select_jack_out_toggled_2(bool)));
	
	connect(ui->checkBox_JackOut_3,
		SIGNAL(toggled(bool)),
		this,
		SLOT(on_select_jack_out_toggled_3(bool)));
	
	connect(ui->checkBox_JackOut_4,
		SIGNAL(toggled(bool)),
		this,
		SLOT(on_select_jack_out_toggled_4(bool)));
	
	connect(ui->checkBox_JackOut_5,
		SIGNAL(toggled(bool)),
		this,
		SLOT(on_select_jack_out_toggled_5(bool)));
	
	connect(ui->checkBox_JackOut_6,
		SIGNAL(toggled(bool)),
		this,
		SLOT(on_select_jack_out_toggled_6(bool)));
	
	connect(ui->checkBox_JackOut_7,
		SIGNAL(toggled(bool)),
		this,
		SLOT(on_select_jack_out_toggled_7(bool)));
	
	connect(ui->checkBox_JackOut_8,
		SIGNAL(toggled(bool)),
		this,
		SLOT(on_select_jack_out_toggled_8(bool)));
	
	connect(ui->checkBox_JackOut_9,
		SIGNAL(toggled(bool)),
		this,
		SLOT(on_select_jack_out_toggled_9(bool)));
	
	connect(ui->checkBox_JackOut_10,
		SIGNAL(toggled(bool)),
		this,
		SLOT(on_select_jack_out_toggled_10(bool)));
	
	connect(ui->checkBox_JackOut_11,
		SIGNAL(toggled(bool)),
		this,
		SLOT(on_select_jack_out_toggled_11(bool)));
	
	connect(ui->checkBox_JackOut_12,
		SIGNAL(toggled(bool)),
		this,
		SLOT(on_select_jack_out_toggled_12(bool)));
	
	connect(ui->checkBox_ch_1,
		SIGNAL(toggled(bool)),
		this,
		SLOT(on_select_active_midi_channel_1(bool)));
	
	connect(ui->checkBox_ch_2,
		SIGNAL(toggled(bool)),
		this,
		SLOT(on_select_active_midi_channel_2(bool)));
	
	connect(ui->checkBox_ch_3,
		SIGNAL(toggled(bool)),
		this,
		SLOT(on_select_active_midi_channel_3(bool)));
	
	connect(ui->checkBox_ch_4,
		SIGNAL(toggled(bool)),
		this,
		SLOT(on_select_active_midi_channel_4(bool)));
	
	connect(ui->checkBox_ch_1,
		SIGNAL(toggled(bool)),
		this,
		SLOT(on_select_active_midi_channel_1(bool)));
	
	connect(ui->checkBox_ch_5,
		SIGNAL(toggled(bool)),
		this,
		SLOT(on_select_active_midi_channel_5(bool)));
	
	connect(ui->checkBox_ch_6,
		SIGNAL(toggled(bool)),
		this,
		SLOT(on_select_active_midi_channel_6(bool)));
	
	connect(ui->checkBox_ch_7,
		SIGNAL(toggled(bool)),
		this,
		SLOT(on_select_active_midi_channel_7(bool)));
	
	connect(ui->checkBox_ch_8,
		SIGNAL(toggled(bool)),
		this,
		SLOT(on_select_active_midi_channel_8(bool)));
	
	connect(ui->checkBox_ch_9,
		SIGNAL(toggled(bool)),
		this,
		SLOT(on_select_active_midi_channel_9(bool)));
	
	connect(ui->checkBox_ch_10,
		SIGNAL(toggled(bool)),
		this,
		SLOT(on_select_active_midi_channel_10(bool)));
	
	connect(ui->checkBox_ch_11,
		SIGNAL(toggled(bool)),
		this,
		SLOT(on_select_active_midi_channel_11(bool)));
	
	connect(ui->checkBox_ch_12,
		SIGNAL(toggled(bool)),
		this,
		SLOT(on_select_active_midi_channel_12(bool)));
	
	connect(ui->checkBox_ch_13,
		SIGNAL(toggled(bool)),
		this,
		SLOT(on_select_active_midi_channel_13(bool)));
	
	connect(ui->checkBox_ch_14,
		SIGNAL(toggled(bool)),
		this,
		SLOT(on_select_active_midi_channel_14(bool)));
	
	connect(ui->checkBox_ch_15,
		SIGNAL(toggled(bool)),
		this,
		SLOT(on_select_active_midi_channel_15(bool)));
	
	connect(ui->checkBox_ch_16,
		SIGNAL(toggled(bool)),
		this,
		SLOT(on_select_active_midi_channel_16(bool)));
	
	MainWindow::get_instance()->register_active_dialog(this);
}

Dialog_InstrumentConnections::~Dialog_InstrumentConnections()
{
	
}

Dialog_InstrumentConnections *Dialog_InstrumentConnections::get_instance()
{	
	return dialog_InstrumentConnectionsInstance;
}

void Dialog_InstrumentConnections::closeEvent(QCloseEvent *event)
{
	//mod_synth_unregister_callback_control_box_event_update_ui(
	//	&connections_control_box_event_update_ui_callback_wrapper);
	
	MainWindow::get_instance()->unregister_active_dialog(this);
	dialog_is_open = false;
	hide();
}

void Dialog_InstrumentConnections::control_box_ui_update_callback(int evnt, uint16_t val)
{
	int pb_num;
	int selected;
	
	if (!this->hasFocus())
	{
		return;
	}
	
	if ((evnt >= _CONTROL_PUSHBUTTON_BLUE_BLACK) &&
		(evnt <= _CONTROL_PUSHBUTTON_ORANGE_YELLOW) &&
		(val == 0))
	{
		/* Pushbuttons pressed event */
		pb_num = evnt - _CONTROL_PUSHBUTTON_BLUE_BLACK;
		
		if (selected_pannel == _MIDI_PANNEL_SELECTED)
		{
			/* MIDI inputs selection */
			switch (pb_num)
			{
			case 0:
				if (!midi_input_clients_select_pb[0]->isEnabled())
				{
					break;
				}
				
				selected = midi_input_clients_select_pb[0]->checkState();
				if (selected == Qt::CheckState::Checked)
				{
					/* Toggle */
					midi_input_clients_select_pb[0]->setCheckState(Qt::CheckState::Unchecked);
					on_select_midi_in_toggled_1(false);
				}
				else
				{
					midi_input_clients_select_pb[0]->setCheckState(Qt::CheckState::Checked);
					on_select_midi_in_toggled_1(true);
				}
				
				break;
				
			case 1:
				if (!midi_input_clients_select_pb[1]->isEnabled())
				{
					break;
				}
				
				selected = midi_input_clients_select_pb[1]->checkState();
				if (selected == Qt::CheckState::Checked)
				{
					/* Toggle */
					midi_input_clients_select_pb[1]->setCheckState(Qt::CheckState::Unchecked);
					on_select_midi_in_toggled_2(false);
				}
				else
				{
					midi_input_clients_select_pb[1]->setCheckState(Qt::CheckState::Checked);
					on_select_midi_in_toggled_2(true);
				}
					
				break;
				
			case 2:
				if (!midi_input_clients_select_pb[2]->isEnabled())
				{
					break;
				}
				
				selected = midi_input_clients_select_pb[2]->checkState();
				if (selected == Qt::CheckState::Checked)
				{
					/* Toggle */
					midi_input_clients_select_pb[2]->setCheckState(Qt::CheckState::Unchecked);
					on_select_midi_in_toggled_3(false);
				}
				else
				{
					midi_input_clients_select_pb[2]->setCheckState(Qt::CheckState::Checked);
					on_select_midi_in_toggled_3(true);
				}
					
				break;
				
			case 3:
				if (!midi_input_clients_select_pb[3]->isEnabled())
				{
					break;
				}
				
				selected = midi_input_clients_select_pb[3]->checkState();
				if (selected == Qt::CheckState::Checked)
				{
					/* Toggle */
					midi_input_clients_select_pb[3]->setCheckState(Qt::CheckState::Unchecked);
					on_select_midi_in_toggled_4(false);
				}
				else
				{
					midi_input_clients_select_pb[3]->setCheckState(Qt::CheckState::Checked);
					on_select_midi_in_toggled_4(true);
				}
					
				break;
				
			case 4:
				if (!midi_input_clients_select_pb[4]->isEnabled())
				{
					break;
				}
				
				selected = midi_input_clients_select_pb[4]->checkState();
				if (selected == Qt::CheckState::Checked)
				{
					/* Toggle */
					midi_input_clients_select_pb[4]->setCheckState(Qt::CheckState::Unchecked);
					on_select_midi_in_toggled_5(false);
				}
				else
				{
					midi_input_clients_select_pb[4]->setCheckState(Qt::CheckState::Checked);
					on_select_midi_in_toggled_5(true);
				}
					
				break;
				
			case 5:
				if (!midi_input_clients_select_pb[5]->isEnabled())
				{
					break;
				}
				
				selected = midi_input_clients_select_pb[5]->checkState();
				if (selected == Qt::CheckState::Checked)
				{
					/* Toggle */
					midi_input_clients_select_pb[5]->setCheckState(Qt::CheckState::Unchecked);
					on_select_midi_in_toggled_6(false);
				}
				else
				{
					midi_input_clients_select_pb[5]->setCheckState(Qt::CheckState::Checked);
					on_select_midi_in_toggled_6(true);
				}
					
				break;
				
			case 6:
				if (!midi_input_clients_select_pb[6]->isEnabled())
				{
					break;
				}
				
				selected = midi_input_clients_select_pb[6]->checkState();
				if (selected == Qt::CheckState::Checked)
				{
					/* Toggle */
					midi_input_clients_select_pb[6]->setCheckState(Qt::CheckState::Unchecked);
					on_select_midi_in_toggled_7(false);
				}
				else
				{
					midi_input_clients_select_pb[6]->setCheckState(Qt::CheckState::Checked);
					on_select_midi_in_toggled_7(true);
				}
					
				break;
				
			case 7:
				if (!midi_input_clients_select_pb[7]->isEnabled())
				{
					break;
				}
				
				selected = midi_input_clients_select_pb[7]->checkState();
				if (selected == Qt::CheckState::Checked)
				{
					/* Toggle */
					midi_input_clients_select_pb[7]->setCheckState(Qt::CheckState::Unchecked);
					on_select_midi_in_toggled_8(false);
				}
				else
				{
					midi_input_clients_select_pb[7]->setCheckState(Qt::CheckState::Checked);
					on_select_midi_in_toggled_8(true);
				}
					
				break;
				
			case 8:
				if (!midi_input_clients_select_pb[8]->isEnabled())
				{
					break;
				}
				
				selected = midi_input_clients_select_pb[8]->checkState();
				if (selected == Qt::CheckState::Checked)
				{
					/* Toggle */
					midi_input_clients_select_pb[8]->setCheckState(Qt::CheckState::Unchecked);
					on_select_midi_in_toggled_9(false);
				}
				else
				{
					midi_input_clients_select_pb[8]->setCheckState(Qt::CheckState::Checked);
					on_select_midi_in_toggled_9(true);
				}
					
				break;
				
			case 9:
				if (!midi_input_clients_select_pb[9]->isEnabled())
				{
					break;
				}
				
				selected = midi_input_clients_select_pb[9]->checkState();
				if (selected == Qt::CheckState::Checked)
				{
					/* Toggle */
					midi_input_clients_select_pb[9]->setCheckState(Qt::CheckState::Unchecked);
					on_select_midi_in_toggled_10(false);
				}
				else
				{
					midi_input_clients_select_pb[9]->setCheckState(Qt::CheckState::Checked);
					on_select_midi_in_toggled_10(true);
				}
					
				break;
				
			case 10:
				if (!midi_input_clients_select_pb[10]->isEnabled())
				{
					break;
				}
				
				selected = midi_input_clients_select_pb[10]->checkState();
				if (selected == Qt::CheckState::Checked)
				{
					/* Toggle */
					midi_input_clients_select_pb[10]->setCheckState(Qt::CheckState::Unchecked);
					on_select_midi_in_toggled_11(false);
				}
				else
				{
					midi_input_clients_select_pb[10]->setCheckState(Qt::CheckState::Checked);
					on_select_midi_in_toggled_11(true);
				}
					
				break;
				
			case 11:
				if (!midi_input_clients_select_pb[11]->isEnabled())
				{
					break;
				}
				
				selected = midi_input_clients_select_pb[11]->checkState();
				if (selected == Qt::CheckState::Checked)
				{
					/* Toggle */
					midi_input_clients_select_pb[11]->setCheckState(Qt::CheckState::Unchecked);
					on_select_midi_in_toggled_12(false);
				}
				else
				{
					midi_input_clients_select_pb[11]->setCheckState(Qt::CheckState::Checked);
					on_select_midi_in_toggled_12(true);
				}
					
				break;
				
			}
		
			
		}
		else if (selected_pannel == _JACK_PANNEL_SELECTED)
		{
			/* Jack outputs selection */
			switch (pb_num)
			{
				case 0:
					if (!jack_output_clients_select_pb[0]->isEnabled())
					{
						break;						
					}
				
					selected = jack_output_clients_select_pb[0]->checkState();
					if (selected == Qt::CheckState::Checked)
					{
						/* Toggle */
						jack_output_clients_select_pb[0]->setCheckState(Qt::CheckState::Unchecked);
						on_select_jack_out_toggled_1(false);
					}
					else
					{
						jack_output_clients_select_pb[0]->setCheckState(Qt::CheckState::Checked);
						on_select_jack_out_toggled_1(true);
					}
					
					break;
				
				case 1:
					if (!jack_output_clients_select_pb[1]->isEnabled())
					{
						break;						
					}
				
					selected = jack_output_clients_select_pb[1]->checkState();
					if (selected == Qt::CheckState::Checked)
					{
						/* Toggle */
						jack_output_clients_select_pb[1]->setCheckState(Qt::CheckState::Unchecked);
						on_select_jack_out_toggled_2(false);
					}
					else
					{
						jack_output_clients_select_pb[1]->setCheckState(Qt::CheckState::Checked);
						on_select_jack_out_toggled_2(true);
					}
						
					break;
				
				case 2:
					if (!jack_output_clients_select_pb[2]->isEnabled())
					{
						break;						
					}
				
					selected = jack_output_clients_select_pb[2]->checkState();
					if (selected == Qt::CheckState::Checked)
					{
						/* Toggle */
						jack_output_clients_select_pb[2]->setCheckState(Qt::CheckState::Unchecked);
						on_select_jack_out_toggled_3(false);
					}
					else
					{
						jack_output_clients_select_pb[2]->setCheckState(Qt::CheckState::Checked);
						on_select_jack_out_toggled_3(true);
					}
						
					break;
				
				case 3:
					if (!jack_output_clients_select_pb[3]->isEnabled())
					{
						break;						
					}
				
					selected = jack_output_clients_select_pb[3]->checkState();
					if (selected == Qt::CheckState::Checked)
					{
						/* Toggle */
						jack_output_clients_select_pb[3]->setCheckState(Qt::CheckState::Unchecked);
						on_select_jack_out_toggled_4(false);
					}
					else
					{
						jack_output_clients_select_pb[3]->setCheckState(Qt::CheckState::Checked);
						on_select_jack_out_toggled_4(true);
					}
						
					break;
				
				case 4:
					if (!jack_output_clients_select_pb[4]->isEnabled())
					{
						break;						
					}
				
					selected = jack_output_clients_select_pb[4]->checkState();
					if (selected == Qt::CheckState::Checked)
					{
						/* Toggle */
						jack_output_clients_select_pb[4]->setCheckState(Qt::CheckState::Unchecked);
						on_select_jack_out_toggled_5(false);
					}
					else
					{
						jack_output_clients_select_pb[4]->setCheckState(Qt::CheckState::Checked);
						on_select_jack_out_toggled_5(true);
					}
							
					break;
				
				case 5:
					if (!jack_output_clients_select_pb[5]->isEnabled())
					{
						break;						
					}
				
					selected = jack_output_clients_select_pb[5]->checkState();
					if (selected == Qt::CheckState::Checked)
					{
						/* Toggle */
						jack_output_clients_select_pb[5]->setCheckState(Qt::CheckState::Unchecked);
						on_select_jack_out_toggled_6(false);
					}
					else
					{
						jack_output_clients_select_pb[5]->setCheckState(Qt::CheckState::Checked);
						on_select_jack_out_toggled_6(true);
					}
						
					break;
				
				case 6:
					if (!jack_output_clients_select_pb[6]->isEnabled())
					{
						break;						
					}
				
					selected = jack_output_clients_select_pb[6]->checkState();
					if (selected == Qt::CheckState::Checked)
					{
						/* Toggle */
						jack_output_clients_select_pb[6]->setCheckState(Qt::CheckState::Unchecked);
						on_select_jack_out_toggled_7(false);
					}
					else
					{
						jack_output_clients_select_pb[6]->setCheckState(Qt::CheckState::Checked);
						on_select_jack_out_toggled_7(true);
					}
							
					break;
				
				case 7:
					if (!jack_output_clients_select_pb[7]->isEnabled())
					{
						break;						
					}
				
					selected = jack_output_clients_select_pb[7]->checkState();
					if (selected == Qt::CheckState::Checked)
					{
						/* Toggle */
						jack_output_clients_select_pb[7]->setCheckState(Qt::CheckState::Unchecked);
						on_select_jack_out_toggled_8(false);
					}
					else
					{
						jack_output_clients_select_pb[7]->setCheckState(Qt::CheckState::Checked);
						on_select_jack_out_toggled_8(true);
					}
						
					break;
				
				case 8:
					if (!jack_output_clients_select_pb[8]->isEnabled())
					{
						break;						
					}
				
					selected = jack_output_clients_select_pb[8]->checkState();
					if (selected == Qt::CheckState::Checked)
					{
						/* Toggle */
						jack_output_clients_select_pb[8]->setCheckState(Qt::CheckState::Unchecked);
						on_select_jack_out_toggled_9(false);
					}
					else
					{
						jack_output_clients_select_pb[8]->setCheckState(Qt::CheckState::Checked);
						on_select_jack_out_toggled_9(true);
					}
							
					break;
				
				case 9:
					if (!jack_output_clients_select_pb[9]->isEnabled())
					{
						break;						
					}
				
					selected = jack_output_clients_select_pb[9]->checkState();
					if (selected == Qt::CheckState::Checked)
					{
						/* Toggle */
						jack_output_clients_select_pb[9]->setCheckState(Qt::CheckState::Unchecked);
						on_select_jack_out_toggled_10(false);
					}
					else
					{
						jack_output_clients_select_pb[9]->setCheckState(Qt::CheckState::Checked);
						on_select_jack_out_toggled_10(true);
					}
						
					break;
				
				case 10:
					if (!jack_output_clients_select_pb[10]->isEnabled())
					{
						break;						
					}
				
					selected = jack_output_clients_select_pb[10]->checkState();
					if (selected == Qt::CheckState::Checked)
					{
						/* Toggle */
						jack_output_clients_select_pb[10]->setCheckState(Qt::CheckState::Unchecked);
						on_select_jack_out_toggled_11(false);
					}
					else
					{
						jack_output_clients_select_pb[10]->setCheckState(Qt::CheckState::Checked);
						on_select_jack_out_toggled_11(true);
					}
						
					break;
				
				case 11:
					if (!jack_output_clients_select_pb[11]->isEnabled())
					{
						break;						
					}
				
					selected = jack_output_clients_select_pb[11]->checkState();
					if (selected == Qt::CheckState::Checked)
					{
						/* Toggle */
						jack_output_clients_select_pb[11]->setCheckState(Qt::CheckState::Unchecked);
						on_select_jack_out_toggled_12(false);
					}
					else
					{
						jack_output_clients_select_pb[11]->setCheckState(Qt::CheckState::Checked);
						on_select_jack_out_toggled_12(true);
					}
						
					break;
			}
		}
	}
	else if ((evnt == _CONTROL_FUNCTION_PUSHBUTTON_UP) &&
			 (val == 0))
	{
		/* Toggle selected pannel */
		if (selected_pannel == _MIDI_PANNEL_SELECTED)
		{
			on_select_Jack_pannel_clicked();			
		}
		else
		{
			on_select_MIDI_pannel_clicked();
		}
		
		/* Avoid fast switching ???*/
		QThread::msleep(1500);
		
	}
	else if ((evnt == _CONTROL_FUNCTION_PUSHBUTTON_ENTER) &&
			 (val == 0))
	{
		/* Close the dialog */
		on_dialog_ok();
	}
	
}

void Dialog_InstrumentConnections::update()
{	
	int cln;
	std::string cln_name, port_name, input_name;
	int num_of_alsa_input_clients, connection_number;
	int num_of_jack_input_clients;
	int num_of_connected_jack_input_clients_left, num_of_connected_jack_input_clients_right;
	int num_of_ports, port, input_ports_count;
	std::list<std::string> connected_to_midi_clients_names_list;
	std::list<std::string> connected_to_jack_clients_names_list_left;
	std::list<std::string> connected_to_jack_clients_names_list_right;
	
	list<string>::iterator names_it;
	list<string>::iterator connections_it;
	
	mod_synth_refresh_alsa_clients_data();
	mod_synth_refresh_jack_clients_data();
	
	/* Update the list of ALSA input clients.  
	 * Names order is the same as in the alsa input clients tables prder.
	 * So, the 1st name corresponds to the 1st client in the input clients table. */
	list<string> midi_inputs_names = mod_synth_get_midi_input_client_name_strings();
	
	num_of_alsa_input_clients = midi_inputs_names.size();
	/* Get the instrument client number. */
	client_number = mod_synth_get_midi_client_connection_num(instrument_name.toStdString());
	/* Get a list of the clients that this instrument is connected to. */
	mod_synth_get_midi_client_connected_to_clients_names_list(client_number, true, 
																&connected_to_midi_clients_names_list);
	
	if (num_of_alsa_input_clients > 0)
	{
		names_it = midi_inputs_names.begin();
		
		for (int i = 0; i < num_of_alsa_input_clients && i < 12; i++)
		{
			midi_input_clients_select_pb[i]->setEnabled(true);
			midi_input_clients_select_pb[i]->setText(QString::fromStdString(names_it->c_str()));
			alsa_connections_names[i] = names_it->c_str();
			
			/* Uncheck all - connected will be checked below*/
			midi_input_clients_select_pb[i]->blockSignals(true);
			midi_input_clients_select_pb[i]->setChecked(false);
			midi_input_clients_select_pb[i]->blockSignals(false);
			
			advance(names_it, 1);
		}
		
		for (int i = num_of_alsa_input_clients; i < 12; i++)
		{
			midi_input_clients_select_pb[i]->setEnabled(false);
			midi_input_clients_select_pb[i]->setText("");
			
			/* Uncheck all - connected will be checked below*/
			midi_input_clients_select_pb[i]->blockSignals(true);
			midi_input_clients_select_pb[i]->setChecked(false);
			midi_input_clients_select_pb[i]->blockSignals(false);
		}
	}
	
	/* Connected to? */
	if (connected_to_midi_clients_names_list.size() > 0)
	{
		connections_it = connected_to_midi_clients_names_list.begin();
				
		for (int c = 0; c < connected_to_midi_clients_names_list.size(); c++)
		{
			names_it = midi_inputs_names.begin();
		
			for (int i = 0; i < num_of_alsa_input_clients; i++)
			{
				if (strip_client_name_prefix(names_it->c_str()) == connections_it->c_str())
				{
					midi_input_clients_select_pb[i]->blockSignals(true);
					midi_input_clients_select_pb[i]->setChecked(true);
					midi_input_clients_select_pb[i]->blockSignals(false);
				}
				
				advance(names_it, 1);
			}
					
			advance(connections_it, 1);
		}
	}
				
	/* Update the list of Jack iput clients */	
	num_of_jack_input_clients = mod_synth_get_num_of_input_jack_clients();
	
	if (num_of_jack_input_clients > _MAX_NUM_OF_GUI_JACK_CLIENTS)
	{
		num_of_jack_input_clients = _MAX_NUM_OF_GUI_JACK_CLIENTS;
	}
	
	input_ports_count = 0;
	
	if (num_of_jack_input_clients > 0)
	{		
		for (cln = 0; cln < num_of_jack_input_clients && input_ports_count < 6; cln++)
		{
			cln_name = mod_synth_get_jack_input_client_name(cln);
			
			num_of_ports = mod_synth_get_num_of_jack_input_client_ports(cln);
			
			if (num_of_ports > 0)
			{
				for (port = 0; port < num_of_ports && input_ports_count < 6; port++)
				{
					port_name = mod_synth_get_jack_input_client_port_name(cln, port);
					
					if ((port_name != "") && (port_name.find("midi_playback") == std::string::npos))
					{
						jack_output_client_names[input_ports_count] = cln_name;
						jack_output_client_port_names[input_ports_count] = port_name;
						input_name = cln_name + ":" + port_name;
						/* Instrument Right output connections */
						jack_output_clients_select_pb[input_ports_count]->setEnabled(true);
						jack_output_clients_select_pb[input_ports_count]->setText(QString::fromStdString(input_name.c_str()));
						jack_connections_names[input_ports_count] = input_name.c_str();
						/* Uncheck all - connected will be checked below*/
						jack_output_clients_select_pb[input_ports_count]->blockSignals(true);
						jack_output_clients_select_pb[input_ports_count]->setChecked(false);
						jack_output_clients_select_pb[input_ports_count]->blockSignals(false);
						/* Instrument Left output connections */
						jack_output_clients_select_pb[input_ports_count + 6]->setEnabled(true);
						jack_output_clients_select_pb[input_ports_count + 6]->setText(QString::fromStdString(input_name.c_str()));
						jack_connections_names[input_ports_count +6 ] = input_name.c_str();
						/* Uncheck all - connected will be checked below*/
						jack_output_clients_select_pb[input_ports_count + 6]->blockSignals(true);
						jack_output_clients_select_pb[input_ports_count + 6]->setChecked(false);
						jack_output_clients_select_pb[input_ports_count + 6]->blockSignals(false);
						
						input_ports_count++;
					}
				}
				
				for (port = input_ports_count; port < 6; port++)
				{
					/* Instrument Right output connections */
					jack_output_clients_select_pb[input_ports_count]->setEnabled(false);
					jack_output_clients_select_pb[input_ports_count]->setText("");
					/* Uncheck all */
					jack_output_clients_select_pb[input_ports_count]->blockSignals(true);
					jack_output_clients_select_pb[input_ports_count]->setChecked(false);
					jack_output_clients_select_pb[input_ports_count]->blockSignals(false);
					/* Instrument Left output connections */
					jack_output_clients_select_pb[input_ports_count + 6]->setEnabled(false);
					jack_output_clients_select_pb[input_ports_count + 6]->setText("");
					/* Uncheck all */
					jack_output_clients_select_pb[input_ports_count + 6]->blockSignals(true);
					jack_output_clients_select_pb[input_ports_count + 6]->setChecked(false);
					jack_output_clients_select_pb[input_ports_count + 6]->blockSignals(false);
				}
			}			
		}		
	}
	
	for (int i = input_ports_count; i < 6; i++)
	{
		jack_output_clients_select_pb[i]->setEnabled(false);
		jack_output_clients_select_pb[i]->setText("");
		
		jack_output_clients_select_pb[i+6]->setEnabled(false);
		jack_output_clients_select_pb[i+6]->setText("");
	}
	
	/* Connected to? */

	num_of_connected_jack_input_clients_left = mod_synth_get_jack_input_connections(
						instrument_name.toStdString(),
		"left",
		&connected_to_jack_clients_names_list_left);
	
	num_of_connected_jack_input_clients_right = mod_synth_get_jack_input_connections(
						instrument_name.toStdString(),
		"right",
		&connected_to_jack_clients_names_list_right);
	
	if (num_of_connected_jack_input_clients_left > 0)
	{
		connections_it = connected_to_jack_clients_names_list_left.begin();
		
		for (int j = 0; j < num_of_connected_jack_input_clients_left; j++)
		{
			for (int c = 0; c < 6; c++)
			{
				if (connections_it->c_str() == jack_connections_names[c])
				{
					jack_output_clients_select_pb[c]->blockSignals(true);
					jack_output_clients_select_pb[c]->setChecked(true);
					jack_output_clients_select_pb[c]->blockSignals(false);
				}
			}
			
			advance(connections_it, 1);
		} 
	}
	
	if (num_of_connected_jack_input_clients_right > 0)
	{
		connections_it = connected_to_jack_clients_names_list_right.begin();
		
		for (int j = 0; j < num_of_connected_jack_input_clients_right; j++)
		{
			for (int c = 6; c < 12; c++)
			{
				if (connections_it->c_str() == jack_connections_names[c])
				{
					jack_output_clients_select_pb[c]->blockSignals(true);
					jack_output_clients_select_pb[c]->setChecked(true);
					jack_output_clients_select_pb[c]->blockSignals(false);
				}
			}
			
			advance(connections_it, 1);
		} 
	}
	
	active_midi_channels = mod_synth_get_instrument_active_midi_channels(instrument_name.toStdString());
	
	for (int i = 0; i < 16; i++)
	{
		if ((active_midi_channels & (1 << i)) != 0)
		{
			active_midi_channel_pb[i]->setCheckState(Qt::Checked);
		}
		else
		{
			active_midi_channel_pb[i]->setCheckState(Qt::Unchecked);
		}
	}
	
	
}

uint16_t Dialog_InstrumentConnections::build_channels_mask(uint16_t mask, int chan, bool en)
{
	uint16_t new_mask;
	
	if ((chan < 0) && (chan > 16))
	{
		return mask;
	}

	
	if (en)
	{
		new_mask = mask | (1 << chan); 
	}
	else
	{
		new_mask = (mask & ~(1 << chan)) & 0xffff;
	}
	
	return new_mask;
}

void Dialog_InstrumentConnections::on_dialog_ok()
{	
	mod_synth_unregister_callback_control_box_event_update_ui(
		&connections_control_box_event_update_ui_callback_wrapper);
	
	close();
}

void Dialog_InstrumentConnections::on_dialog_refresh()
{
	update();
	
	/* Set focus back on the Dialog */
	this->setFocus(Qt::ActiveWindowFocusReason);
}

void Dialog_InstrumentConnections::on_select_MIDI_pannel_clicked()
{
	selected_pannel = _MIDI_PANNEL_SELECTED;
	
	ui->frame_MIDI->setFrameShadow(QFrame::Sunken);
	ui->frame_MIDI->setLineWidth(5);
	ui->frame_MIDI->setMidLineWidth(5);
	ui->frame_Jack->setFrameShadow(QFrame::Plain);
	ui->frame_Jack->setLineWidth(0);
	ui->frame_Jack->setMidLineWidth(0);
	ui->radioButton_MIDI->setChecked(true);
	ui->radioButton_Jack->setChecked(false);
	
	/* Set focus back on the Dialog */
	this->setFocus(Qt::ActiveWindowFocusReason);
}

void Dialog_InstrumentConnections::on_select_Jack_pannel_clicked()
{
	selected_pannel = _JACK_PANNEL_SELECTED;
	
	ui->frame_MIDI->setFrameShadow(QFrame::Plain);
	ui->frame_MIDI->setLineWidth(0);
	ui->frame_MIDI->setMidLineWidth(0);
	ui->frame_Jack->setFrameShadow(QFrame::Sunken);
	ui->frame_Jack->setLineWidth(5);
	ui->frame_Jack->setMidLineWidth(5);
	ui->radioButton_MIDI->setChecked(false);
	ui->radioButton_Jack->setChecked(true);
	
	/* Set focus back on the Dialog */
	this->setFocus(Qt::ActiveWindowFocusReason);
	
}

void Dialog_InstrumentConnections::on_select_midi_in_toggled_1(bool sel)
{
	mod_synth_connect_midi_clients(instrument_name.toStdString(), 0, 0, sel);
	
	/* Set focus back on the Dialog */
	this->setFocus(Qt::ActiveWindowFocusReason);
}

void Dialog_InstrumentConnections::on_select_midi_in_toggled_2(bool sel)
{
	mod_synth_connect_midi_clients(instrument_name.toStdString(), 1, 0, sel);
	
	/* Set focus back on the Dialog */
	this->setFocus(Qt::ActiveWindowFocusReason);
}

void Dialog_InstrumentConnections::on_select_midi_in_toggled_3(bool sel)
{
	mod_synth_connect_midi_clients(instrument_name.toStdString(), 2, 0, sel);
	
	/* Set focus back on the Dialog */
	this->setFocus(Qt::ActiveWindowFocusReason);
}

void Dialog_InstrumentConnections::on_select_midi_in_toggled_4(bool sel)
{
	mod_synth_connect_midi_clients(instrument_name.toStdString(), 3, 0, sel);
	
	/* Set focus back on the Dialog */
	this->setFocus(Qt::ActiveWindowFocusReason);
}

void Dialog_InstrumentConnections::on_select_midi_in_toggled_5(bool sel)
{
	mod_synth_connect_midi_clients(instrument_name.toStdString(), 4, 0, sel);
	
	/* Set focus back on the Dialog */
	this->setFocus(Qt::ActiveWindowFocusReason);
}

void Dialog_InstrumentConnections::on_select_midi_in_toggled_6(bool sel)
{
	mod_synth_connect_midi_clients(instrument_name.toStdString(), 5, 0, sel);
	
	/* Set focus back on the Dialog */
	this->setFocus(Qt::ActiveWindowFocusReason);
}

void Dialog_InstrumentConnections::on_select_midi_in_toggled_7(bool sel)
{
	mod_synth_connect_midi_clients(instrument_name.toStdString(), 6, 0, sel);
	
	/* Set focus back on the Dialog */
	this->setFocus(Qt::ActiveWindowFocusReason);
}

void Dialog_InstrumentConnections::on_select_midi_in_toggled_8(bool sel)
{
	mod_synth_connect_midi_clients(instrument_name.toStdString(), 7, 0, sel);
	
	/* Set focus back on the Dialog */
	this->setFocus(Qt::ActiveWindowFocusReason);
}

void Dialog_InstrumentConnections::on_select_midi_in_toggled_9(bool sel)
{
	mod_synth_connect_midi_clients(instrument_name.toStdString(), 8, 0, sel);
	
	/* Set focus back on the Dialog */
	this->setFocus(Qt::ActiveWindowFocusReason);
}

void Dialog_InstrumentConnections::on_select_midi_in_toggled_10(bool sel)
{
	mod_synth_connect_midi_clients(instrument_name.toStdString(), 9, 0, sel);
	
	/* Set focus back on the Dialog */
	this->setFocus(Qt::ActiveWindowFocusReason);
}

void Dialog_InstrumentConnections::on_select_midi_in_toggled_11(bool sel)
{
	mod_synth_connect_midi_clients(instrument_name.toStdString(), 10, 0, sel);
	
	/* Set focus back on the Dialog */
	this->setFocus(Qt::ActiveWindowFocusReason);
}

void Dialog_InstrumentConnections::on_select_midi_in_toggled_12(bool sel)
{
	mod_synth_connect_midi_clients(instrument_name.toStdString(), 11, 0, sel);
	
	/* Set focus back on the Dialog */
	this->setFocus(Qt::ActiveWindowFocusReason);
}


void Dialog_InstrumentConnections::on_select_jack_out_toggled_1(bool sel)
{
	mod_synth_connect_jack_connection(
		replace_white_spaces(jack_output_client_names[0]),
		replace_white_spaces(jack_output_client_port_names[0]),
		instrument_name.toStdString(),
		"left",
		sel);
	
	/* Set focus back on the Dialog */
	this->setFocus(Qt::ActiveWindowFocusReason);
}

void Dialog_InstrumentConnections::on_select_jack_out_toggled_2(bool sel)
{
	mod_synth_connect_jack_connection(
		replace_white_spaces(jack_output_client_names[1]),
		replace_white_spaces(jack_output_client_port_names[1]),
		instrument_name.toStdString(),
		"left",
		sel);
	
	/* Set focus back on the Dialog */
	this->setFocus(Qt::ActiveWindowFocusReason);
}

void Dialog_InstrumentConnections::on_select_jack_out_toggled_3(bool sel)
{
	mod_synth_connect_jack_connection(
		replace_white_spaces(jack_output_client_names[2]),
		replace_white_spaces(jack_output_client_port_names[2]),
		instrument_name.toStdString(),
		"left",
		sel);
	
	/* Set focus back on the Dialog */
	this->setFocus(Qt::ActiveWindowFocusReason);
}

void Dialog_InstrumentConnections::on_select_jack_out_toggled_4(bool sel)
{
	mod_synth_connect_jack_connection(
		replace_white_spaces(jack_output_client_names[3]),
		replace_white_spaces(jack_output_client_port_names[3]),
		instrument_name.toStdString(),
		"left",
		sel);
	
	/* Set focus back on the Dialog */
	this->setFocus(Qt::ActiveWindowFocusReason);
}

void Dialog_InstrumentConnections::on_select_jack_out_toggled_5(bool sel)
{
	mod_synth_connect_jack_connection(
		replace_white_spaces(jack_output_client_names[4]),
		replace_white_spaces(jack_output_client_port_names[4]),
		instrument_name.toStdString(),
		"left",
		sel);
	
	/* Set focus back on the Dialog */
	this->setFocus(Qt::ActiveWindowFocusReason);
}

void Dialog_InstrumentConnections::on_select_jack_out_toggled_6(bool sel)
{
	mod_synth_connect_jack_connection(
		replace_white_spaces(jack_output_client_names[5]),
		replace_white_spaces(jack_output_client_port_names[5]),
		instrument_name.toStdString(),
		"left",
		sel);
	
	/* Set focus back on the Dialog */
	this->setFocus(Qt::ActiveWindowFocusReason);
}

void Dialog_InstrumentConnections::on_select_jack_out_toggled_7(bool sel)
{
	mod_synth_connect_jack_connection(
		replace_white_spaces(jack_output_client_names[0]),
		replace_white_spaces(jack_output_client_port_names[0]),
		instrument_name.toStdString(),
		"right",
		sel);
	
	/* Set focus back on the Dialog */
	this->setFocus(Qt::ActiveWindowFocusReason);
}

void Dialog_InstrumentConnections::on_select_jack_out_toggled_8(bool sel)
{
	mod_synth_connect_jack_connection(
		replace_white_spaces(jack_output_client_names[1]),
		replace_white_spaces(jack_output_client_port_names[1]),
		instrument_name.toStdString(),
		"right",
		sel);
	
	/* Set focus back on the Dialog */
	this->setFocus(Qt::ActiveWindowFocusReason);
}

void Dialog_InstrumentConnections::on_select_jack_out_toggled_9(bool sel)
{
	mod_synth_connect_jack_connection(
		replace_white_spaces(jack_output_client_names[2]),
		replace_white_spaces(jack_output_client_port_names[2]),
		instrument_name.toStdString(),
		"right",
		sel);
	
	/* Set focus back on the Dialog */
	this->setFocus(Qt::ActiveWindowFocusReason);
}

void Dialog_InstrumentConnections::on_select_jack_out_toggled_10(bool sel)
{
	mod_synth_connect_jack_connection(
		replace_white_spaces(jack_output_client_names[3]),
		replace_white_spaces(jack_output_client_port_names[3]),
		instrument_name.toStdString(),
		"right",
		sel);
	
	/* Set focus back on the Dialog */
	this->setFocus(Qt::ActiveWindowFocusReason);
}

void Dialog_InstrumentConnections::on_select_jack_out_toggled_11(bool sel)
{
	mod_synth_connect_jack_connection(
		replace_white_spaces(jack_output_client_names[4]),
		replace_white_spaces(jack_output_client_port_names[4]),
		instrument_name.toStdString(),
		"right",
		sel);
	
	/* Set focus back on the Dialog */
	this->setFocus(Qt::ActiveWindowFocusReason);
}

void Dialog_InstrumentConnections::on_select_jack_out_toggled_12(bool sel)
{
	mod_synth_connect_jack_connection(
		replace_white_spaces(jack_output_client_names[5]),
		replace_white_spaces(jack_output_client_port_names[5]),
		instrument_name.toStdString(),
		"right",
		sel);
	
	/* Set focus back on the Dialog */
	this->setFocus(Qt::ActiveWindowFocusReason);
}

void Dialog_InstrumentConnections::on_select_active_midi_channel_1(bool sel)
{
	mod_synth_set_instrument_active_midi_channels(instrument_name.toStdString(),
												  build_channels_mask(active_midi_channels, 0, sel));
	
	/* Set focus back on the Dialog */
	this->setFocus(Qt::ActiveWindowFocusReason);
}

void Dialog_InstrumentConnections::on_select_active_midi_channel_2(bool sel)
{
	mod_synth_set_instrument_active_midi_channels(instrument_name.toStdString(),
		build_channels_mask(active_midi_channels, 1, sel));
	
	/* Set focus back on the Dialog */
	this->setFocus(Qt::ActiveWindowFocusReason);
}

void Dialog_InstrumentConnections::on_select_active_midi_channel_3(bool sel)
{
	mod_synth_set_instrument_active_midi_channels(instrument_name.toStdString(),
		build_channels_mask(active_midi_channels, 2, sel));
	
	/* Set focus back on the Dialog */
	this->setFocus(Qt::ActiveWindowFocusReason);
}

void Dialog_InstrumentConnections::on_select_active_midi_channel_4(bool sel)
{
	mod_synth_set_instrument_active_midi_channels(instrument_name.toStdString(),
		build_channels_mask(active_midi_channels, 3, sel));
	
	/* Set focus back on the Dialog */
	this->setFocus(Qt::ActiveWindowFocusReason);
}

void Dialog_InstrumentConnections::on_select_active_midi_channel_5(bool sel)
{
	mod_synth_set_instrument_active_midi_channels(instrument_name.toStdString(),
		build_channels_mask(active_midi_channels, 4, sel));
	
	/* Set focus back on the Dialog */
	this->setFocus(Qt::ActiveWindowFocusReason);
}

void Dialog_InstrumentConnections::on_select_active_midi_channel_6(bool sel)
{
	mod_synth_set_instrument_active_midi_channels(instrument_name.toStdString(),
		build_channels_mask(active_midi_channels, 5, sel));
	
	/* Set focus back on the Dialog */
	this->setFocus(Qt::ActiveWindowFocusReason);
}

void Dialog_InstrumentConnections::on_select_active_midi_channel_7(bool sel)
{
	mod_synth_set_instrument_active_midi_channels(instrument_name.toStdString(),
		build_channels_mask(active_midi_channels, 6, sel));
	
	/* Set focus back on the Dialog */
	this->setFocus(Qt::ActiveWindowFocusReason);
}

void Dialog_InstrumentConnections::on_select_active_midi_channel_8(bool sel)
{
	mod_synth_set_instrument_active_midi_channels(instrument_name.toStdString(),
		build_channels_mask(active_midi_channels, 7, sel));
	
	/* Set focus back on the Dialog */
	this->setFocus(Qt::ActiveWindowFocusReason);
}

void Dialog_InstrumentConnections::on_select_active_midi_channel_9(bool sel)
{
	mod_synth_set_instrument_active_midi_channels(instrument_name.toStdString(),
		build_channels_mask(active_midi_channels, 8, sel));
	
	/* Set focus back on the Dialog */
	this->setFocus(Qt::ActiveWindowFocusReason);
}

void Dialog_InstrumentConnections::on_select_active_midi_channel_10(bool sel)
{
	mod_synth_set_instrument_active_midi_channels(instrument_name.toStdString(),
		build_channels_mask(active_midi_channels, 9, sel));
	
	/* Set focus back on the Dialog */
	this->setFocus(Qt::ActiveWindowFocusReason);
}

void Dialog_InstrumentConnections::on_select_active_midi_channel_11(bool sel)
{
	mod_synth_set_instrument_active_midi_channels(instrument_name.toStdString(),
		build_channels_mask(active_midi_channels, 10, sel));
	
	/* Set focus back on the Dialog */
	this->setFocus(Qt::ActiveWindowFocusReason);
}

void Dialog_InstrumentConnections::on_select_active_midi_channel_12(bool sel)
{
	mod_synth_set_instrument_active_midi_channels(instrument_name.toStdString(),
		build_channels_mask(active_midi_channels, 11, sel));
	
	/* Set focus back on the Dialog */
	this->setFocus(Qt::ActiveWindowFocusReason);
}

void Dialog_InstrumentConnections::on_select_active_midi_channel_13(bool sel)
{
	mod_synth_set_instrument_active_midi_channels(instrument_name.toStdString(),
		build_channels_mask(active_midi_channels, 12, sel));
	
	/* Set focus back on the Dialog */
	this->setFocus(Qt::ActiveWindowFocusReason);
}

void Dialog_InstrumentConnections::on_select_active_midi_channel_14(bool sel)
{
	mod_synth_set_instrument_active_midi_channels(instrument_name.toStdString(),
		build_channels_mask(active_midi_channels, 13, sel));
	
	/* Set focus back on the Dialog */
	this->setFocus(Qt::ActiveWindowFocusReason);
}

void Dialog_InstrumentConnections::on_select_active_midi_channel_15(bool sel)
{
	mod_synth_set_instrument_active_midi_channels(instrument_name.toStdString(),
		build_channels_mask(active_midi_channels, 14, sel));
	
	/* Set focus back on the Dialog */
	this->setFocus(Qt::ActiveWindowFocusReason);
}

void Dialog_InstrumentConnections::on_select_active_midi_channel_16(bool sel)
{
	mod_synth_set_instrument_active_midi_channels(instrument_name.toStdString(),
		build_channels_mask(active_midi_channels, 15, sel));
	
	/* Set focus back on the Dialog */
	this->setFocus(Qt::ActiveWindowFocusReason);
}
