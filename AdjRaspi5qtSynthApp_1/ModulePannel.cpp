/**
*	@file		ModulePannel.cpp
*	@author		Nahum Budin
*	@date		8-May-2024
*	@version	1.0 
*	
*	Version	1.0		8-May-2024
*
*	@brief		Handles a single module pannel.
*/

#include "ModulePannel.h"
#include "ui_ModulePannel.h"

/**
*   @brief Creates a new module pannel object.
*   @param  *parent					parent QWidget (at MainWindow)
*   @param  moduleNameStr			QString that holds the module name (displayed text)
*   @param  func_ptr_void_int_t		a pointer to a callback void foo(int) that handeles the module close operation.
*   @param  moduleId				a unique integer number identifier of each module type.
*	@return 0 if done; -1 otherwise 
*/
ModulePannel::ModulePannel(QWidget *parent, 
						   QString module_name_str,
						   func_ptr_void_en_modules_ids_t_t close_module_pannel_callback_ptr,
						   en_modules_ids_t mod_id)
	: QFrame(parent)
	, ui(new Ui::ModulePannel)
{
	ui->setupUi(this);
	
	widget_parent = parent;
	
	module_name = module_name_str;
	ui->label->setText(module_name);
	
	ui->label->setAttribute(Qt::WA_TranslucentBackground);
	
	// ui->checkBox_ModuleMIDIin->palette(QWidget::);
	ui->checkBox_ModuleMIDIin->setAttribute(Qt::WA_TranslucentBackground);
	
	module_id = mod_id;
	close_callback_ptr = close_module_pannel_callback_ptr;
	
	connections_dialog = NULL;	
	dialog_adj_fluid_synth = NULL;
	dialog_adj_midi_player = NULL;
	dialog_midi_mixer = NULL;
	dialog_midi_mapper = NULL;
	
	connect(
		ui->pushButton_ModuleExit, 
		SIGNAL(clicked()), 
		this, 
		SLOT(on_module_exit_clicked()));
	
	connect(
		ui->pushButton_ModuleOpen, 
		SIGNAL(clicked()), 
		this, 
		SLOT(on_module_open_clicked()));
	
	connect(ui->pushButton_ModuleConnections, 
		SIGNAL(clicked()), 
		this, 
		SLOT(on_module_connections_clicked()));
	
	connections_dialog = NULL;
	
	dialog_adj_fluid_synth = NULL;
	dialog_adj_midi_player = NULL;
	
	if ((module_id == adj_midi_player) || (module_id == adj_reverb_effect) ||
		(module_id == adj_reverb_effect) || (module_id == adj_distortion_effect) ||
		(module_id == adj_graphic_equilizer) || (module_id == midi_mixer) ||
		(module_id == midi_mixer) || (module_id == adj_ext_midi_interface))
	{
		ui->pushButton_ModuleConnections->setDisabled(true);
	}
}


	

ModulePannel::~ModulePannel()
{
	delete ui;
}

ModulePannel *ModulePannel::get_the_module_pannel()
{
	return this;
}

void ModulePannel::on_module_exit_clicked()
{
	if (close_callback_ptr != Q_NULLPTR)
	{
		close_callback_ptr(module_id);
	}
}

void ModulePannel::on_module_open_clicked()
{
	if (module_name == _INSTRUMENT_NAME_FLUID_SYNTH_STR_KEY)
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
	else if (module_name == _INSTRUMENT_NAME_MIDI_PLAYER_STR_KEY)
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
	else if (module_name == _INSTRUMENT_NAME_MIDI_MIXER_STR_KEY)
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
	else if (module_name == _INSTRUMENT_NAME_MIDI_MAPPER_STR_KEY)
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

void ModulePannel::on_module_connections_clicked()
{
	if (!Dialog_InstrumentConnections::dialog_is_open)
	{
		/* Only one connection dialog can be oppened */
		if (connections_dialog == NULL)
		{
			connections_dialog = new Dialog_InstrumentConnections(this, module_name);
			MainWindow::get_instance()->register_active_dialog(connections_dialog);
			connections_dialog->show();
			connections_dialog->
			Dialog_InstrumentConnections::dialog_is_open = true;
		}
		else
		{
			if (!connections_dialog->isVisible())
			{
				connections_dialog = new Dialog_InstrumentConnections(this, module_name);
				MainWindow::get_instance()->register_active_dialog(connections_dialog);
				connections_dialog->show();
				Dialog_InstrumentConnections::dialog_is_open = true;
			}
		}
	}
}

void ModulePannel::close_connections_dialog()
{
	connections_dialog->close();
}

void ModulePannel::close_module_dialog()
{
	
}
