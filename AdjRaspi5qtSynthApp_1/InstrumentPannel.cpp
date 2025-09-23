/**
*	@file		ModulePannel.cpp
*	@author		Nahum Budin
*	@date		8-May-2024
*	@date		22-Sep-2025
*	@version	1.1 
*			1. Renaming file from ModulePannel to InstrumentPannel
*			2. Refactoring rename modules to instruments
*	
*	History:
*			Version	1.0		8-May-2024	Initial
*
*	@brief		Handles a single module pannel.
*/

#include "InstrumentPannel.h"
#include "ui_InstrumentPannel.h"

/**
*   @brief Creates a new instrument pannel object.
*   @param  *parent					parent QWidget (at MainWindow)
*   @param  instrumentNameStr		QString that holds the instrument name (displayed text)
*   @param  func_ptr_void_int_t		a pointer to a callback void foo(int) that handeles the instrument close operation.
*   @param  instId					a unique integer number identifier of each instrument type.
*	@return 0 if done; -1 otherwise 
*/
InstrumentPannel::InstrumentPannel(QWidget *parent, 
							QString instrument_name_str,
							func_ptr_void_en_instruments_ids_t_t close_instrument_pannel_callback_ptr,
	en_instruments_ids_t inst_id)
	: QFrame(parent)
	, ui(new Ui::InstrumentPannel)
{
	ui->setupUi(this);
	
	widget_parent = parent;
	
	instrument_name = instrument_name_str;
	ui->label_InstrumentName->setText(instrument_name);
	
	ui->label_InstrumentName->setAttribute(Qt::WA_TranslucentBackground);
	
	// ui->checkBox_ModuleMIDIin->palette(QWidget::);
	ui->checkBox_InstrumentMIDIin->setAttribute(Qt::WA_TranslucentBackground);
	
	instrument_id = inst_id;
	close_callback_ptr = close_instrument_pannel_callback_ptr;
	
	connections_dialog = NULL;	
	dialog_adj_fluid_synth = NULL;
	dialog_analog_synth = NULL;
	dialog_adj_midi_player = NULL;
	dialog_midi_mixer = NULL;
	dialog_midi_mapper = NULL;
	
	connect(
		ui->pushButton_InstrumentExit, 
		SIGNAL(clicked()), 
		this, 
		SLOT(on_instrument_exit_clicked()));
	
	connect(
		ui->pushButton_InstrumentOpen, 
		SIGNAL(clicked()), 
		this, 
		SLOT(on_instrument_open_clicked()));
	
	connect(ui->pushButton_InstrumentConnections, 
		SIGNAL(clicked()), 
		this, 
		SLOT(on_instrument_connections_clicked()));
	
	if ((inst_id == adj_midi_player) || 
		(inst_id == adj_reverb_effect) || 
		(inst_id == adj_distortion_effect) ||
		(inst_id == adj_graphic_equilizer) || 
		(inst_id == midi_mixer) || 
		(inst_id == adj_ext_midi_interface))
	{
		ui->pushButton_InstrumentConnections->setDisabled(true);
	}
}


	

InstrumentPannel::~InstrumentPannel()
{
	delete ui;
}

InstrumentPannel *InstrumentPannel::get_the_instrument_pannel()
{
	return this;
}

void InstrumentPannel::hide_checkBox_InstrumentMIDIin()
{
	ui->checkBox_InstrumentMIDIin->hide(); 
}

void InstrumentPannel::on_instrument_exit_clicked()
{
	if (close_callback_ptr != Q_NULLPTR)
	{
		close_callback_ptr(instrument_id);
	}
}

void InstrumentPannel::on_instrument_open_clicked()
{
	if (instrument_name == _INSTRUMENT_NAME_FLUID_SYNTH_STR_KEY)
	{	
		if (dialog_adj_fluid_synth == NULL)
		{
			dialog_adj_fluid_synth = Dialog_AdjFluidSynth::get_instance(this);
			dialog_adj_fluid_synth->show();
		}
		else
		{
			if (!dialog_adj_fluid_synth->isVisible())
			{
				/* Only one instance */
				dialog_adj_fluid_synth = Dialog_AdjFluidSynth::get_instance(this);
				//dialog_adj_fluid_synth->setAttribute(Qt::WA_DeleteOnClose);
				dialog_adj_fluid_synth->show();
			}
		}
	}
	else if (instrument_name == _INSTRUMENT_NAME_ANALOG_SYNTH_STR_KEY)
	{	
		if (dialog_analog_synth == NULL)
		{
			dialog_analog_synth = Dialog_AnalogSynth::get_instance(this);
			dialog_analog_synth->show();
			MainWindow::get_instance()->sketches_menu->setDisabled(false);
		}
		else
		{
			if (!dialog_analog_synth->isVisible())
			{
				/* Only one instance */
				dialog_analog_synth = Dialog_AnalogSynth::get_instance(this);
				dialog_analog_synth->show();
				MainWindow::get_instance()->sketches_menu->setDisabled(false);
			}
		}
	}
	else if (instrument_name == _INSTRUMENT_NAME_MIDI_PLAYER_STR_KEY)
	{
		if (dialog_adj_midi_player == NULL)
		{
			dialog_adj_midi_player = Dialog_MidiPlayer::get_instance(widget_parent);
			dialog_adj_midi_player->show();
		}
		else
		{
			if (!dialog_adj_midi_player->isVisible())
			{
				/* Only one instance */
				dialog_adj_midi_player = Dialog_MidiPlayer::get_instance(widget_parent);
				//dialog_adj_fluid_synth->setAttribute(Qt::WA_DeleteOnClose);
				dialog_adj_midi_player->show();
			}
		}
	}
	else if (instrument_name == _INSTRUMENT_NAME_MIDI_MIXER_STR_KEY)
	{
		if (dialog_midi_mixer == NULL)
		{
			dialog_midi_mixer = Dialog_MidiMixer::get_instance(this);
			dialog_midi_mixer->show();
		}
		else
		{
			if (!dialog_midi_mixer->isVisible())
			{
				/* Only one instance */
				dialog_midi_mixer = Dialog_MidiMixer::get_instance(this);
				//dialog_adj_fluid_synth->setAttribute(Qt::WA_DeleteOnClose);
				dialog_midi_mixer->show();
			}
		}
	}
	else if (instrument_name == _INSTRUMENT_NAME_MIDI_MAPPER_STR_KEY)
	{
		if (dialog_midi_mapper == NULL)
		{
			dialog_midi_mapper = Dialog_MidiMapper::get_instance(this, true);
			dialog_midi_mapper->show();
		}
		else
		{
			if (!dialog_midi_mapper->isVisible())
			{
				/* Only one instance */
				dialog_midi_mapper = Dialog_MidiMapper::get_instance(this, true);
				//dialog_adj_fluid_synth->setAttribute(Qt::WA_DeleteOnClose);
				dialog_midi_mapper->show();
			}
		}
	}
	
}

void InstrumentPannel::on_instrument_connections_clicked()
{
	if (!Dialog_InstrumentConnections::dialog_is_open)
	{
		/* Only one connection dialog can be oppened */
		if (connections_dialog == NULL)
		{
			connections_dialog = new Dialog_InstrumentConnections(this, instrument_name);
			MainWindow::get_instance()->register_active_dialog(connections_dialog);
			connections_dialog->show();
			connections_dialog->
			Dialog_InstrumentConnections::dialog_is_open = true;
		}
		else
		{
			if (!connections_dialog->isVisible())
			{
				//connections_dialog = new Dialog_InstrumentConnections(this, module_name);
				MainWindow::get_instance()->register_active_dialog(connections_dialog);
				connections_dialog->show();
				Dialog_InstrumentConnections::dialog_is_open = true;
			}
		}
	}
}

void InstrumentPannel::close_connections_dialog()
{
	connections_dialog->close();
}

void InstrumentPannel::close_instrument_dialog()
{
	
}
