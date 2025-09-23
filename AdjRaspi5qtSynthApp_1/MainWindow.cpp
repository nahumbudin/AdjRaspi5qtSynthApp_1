/**
*	@file		MainWindow.cpp
*	@author		Nahum Budin
*	@date		22-Sep-2025
*	@version	1.1 
*					1. Code refactoring and comments
*
*	@brief		Application Main Window that hosts the modules pannels as acolomn.
*	
*	History:	version 1.0		8-May-2024  initial
*/

#include <QVBoxLayout>
#include <QFrame>
#include <QFileDialog>
#include <QTHread>
#include <QTimer>
//#include <aarch64-linux-gnu/qt5/QtWidgets/qboxlayout.h>
#include <QtWidgets/qboxlayout.h>

#include <stdio.h>

#include "MainWindow.h"

#include "ui_MainWindow.h"
#include "ui_ModulePannel.h"

#include "InstrumentPannel.h"

#include "Dialog_AdjFluidSynth.h"

SavePatchFileThread *save_patch_file_thread;
LoadPatchFileThread *load_patch_file_thread;

QString patch_file_name;

/** Callback wrapper */

void wrapper_close_instrument_pannel_id(en_instruments_ids_t inst_id)
{
	MainWindow::get_instance()->close_instrument_pannel_id(inst_id);
}
void wrapper_request_close_instrument_pannel_id(en_instruments_ids_t inst_id)
{
	MainWindow::get_instance()->request_close_instrument_pannel_id(inst_id);
}

void wrapper_request_open_instrument_window_name(string instrument_name)
{
	MainWindow::get_instance()->pending_open_instruments_list.push_back(instrument_name);
}


void wrapper_request_close_instrument_pannel_name(string inst_name)
{
	MainWindow::get_instance()->request_close_instrument_pannel_name(inst_name);
}

void main_window_control_box_event_update_ui_callback_wrapper(int evnt, uint16_t val)
{
	MainWindow::get_instance()->control_box_ui_update_callback(evnt, val);
}

std::vector <std::string> get_active_instruments_names_list_wrapper()
{
	return MainWindow::get_instance()->get_active_instruments_names_list();
}

void SavePatchFileThread::run() 
{		
	QString result = QString("Patch File Saved");
	mod_synth_save_patch_file(patch_file_name.toStdString());
	emit savePatchFileDone(result);
}

void LoadPatchFileThread::run() 
{		
	int res;
	
	QString result = QString("Patch File Loaded");
	res = mod_synth_load_patch_file(patch_file_name.toStdString());
	if (res > 0)
	{
		// At least one new module in patch file
		
	}	
	
	emit loadPatchFileDone(result);
}

MainWindow *MainWindow::mwind = NULL;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
	
	mwind = this;
	mwind->move(100, 100);
	
	ui->centralwidget->setLayout(new QVBoxLayout);
	layout = qobject_cast<QVBoxLayout*>(ui->centralwidget->layout());
	
	// Create tools bar menus ections.
	create_actions();
	// Create tools bar menus.
	create_menus();
	
	// Register callbacks.
	mod_synth_register_callback_control_box_event_update_ui(
		&main_window_control_box_event_update_ui_callback_wrapper);
	
	mod_synth_register_callback_get_active_instruments_names_list(
		&get_active_instruments_names_list_wrapper);
	
	mod_synth_register_callback_wrapper_close_instrument_pannel_id(
		&wrapper_request_close_instrument_pannel_id);
	
	mod_synth_register_callback_wrapper_close_instrument_pannel_name(
		&wrapper_request_close_instrument_pannel_name);
	
	mod_synth_register_callback_wrapper_open_instrument_pannel_name(
		&wrapper_request_open_instrument_window_name);
	
	// Build the instruments map - 
	// Note: currently this list conatains all currentlly knowns instruments.
	//       Not all of them are implemented yet in this version.
	instruments_ids_map[_INSTRUMENT_NAME_FLUID_SYNTH_STR_KEY] = 
		en_instruments_ids_t::fluid_synth;
	instruments_ids_map[_INSTRUMENT_NAME_HAMMON_ORGAN_STR_KEY] = 
		en_instruments_ids_t::adj_hammond_organ;
	instruments_ids_map[_INSTRUMENT_NAME_ANALOG_SYNTH_STR_KEY] = 
		en_instruments_ids_t::adj_analog_synth;
	instruments_ids_map[_INSTRUMENT_NAME_KARPLUS_STRONG_STRING_SYNTH_STR_KEY] = 
		en_instruments_ids_t::adj_karplusstrong_string_synth;
	instruments_ids_map[_INSTRUMENT_NAME_MORPHED_SINUS_SYNTH_STR_KEY] = 
		en_instruments_ids_t::adj_morphed_sin_synth;
	instruments_ids_map[_INSTRUMENT_NAME_PADSYNTH_SYNTH_STR_KEY] = 
		en_instruments_ids_t::adj_pad_synth;
	instruments_ids_map[_INSTRUMENT_NAME_MIDI_PLAYER_STR_KEY] = 
		en_instruments_ids_t::adj_midi_player;
	instruments_ids_map[_INSTRUMENT_NAME_MIDI_MIXER_STR_KEY] = 
		en_instruments_ids_t::midi_mixer;
	instruments_ids_map[_INSTRUMENT_NAME_MIDI_MAPPER_STR_KEY] = 
		en_instruments_ids_t::adj_midi_mapper;
	instruments_ids_map[_INSTRUMENT_NAME_REVERB_STR_KEY] = 
		en_instruments_ids_t::adj_reverb_effect;
	instruments_ids_map[_INSTRUMENT_NAME_DISTORTION_STR_KEY] = 
		en_instruments_ids_t::adj_distortion_effect;
	instruments_ids_map[_INSTRUMENT_NAME_GRAPHIC_EQUALIZER_STR_KEY] = 
		en_instruments_ids_t::adj_graphic_equilizer;
	instruments_ids_map[_INSTRUMENT_NAME_EXT_MIDI_INT_CONTROL_STR_KEY] = 
		en_instruments_ids_t::adj_ext_midi_interface;
	instruments_ids_map[_INSTRUMENT_NAME_KEYBOARD_CONTROL_STR_KEY] = 
		en_instruments_ids_t::adj_keyboard_control;
	
	// start the periodic gui update timer after this timeout - 
	start_update_timer(200);
}

MainWindow::~MainWindow()
{
    delete ui;
}

MainWindow *MainWindow::get_instance() {

	if (!mwind)
		mwind = new MainWindow();

	return mwind;
}

/**
*	@brief	Handels the control messages received from the Control Box that shall update the GUI
*	@param	evnt	the event ID
*	@param	val		the event value
*	@return none
*/
void MainWindow::control_box_ui_update_callback(int evnt, uint16_t val)
{
	/*  Counts over all active dialogs */
	static int last_opened_dialog_index = 0;
	/* Holds a dialog position */
	QPoint position;
	
	if (evnt == _CONTROL_FUNCTION_PUSHBUTTON_REDOO)
	{
		if (val == 0)
		{
			// The button is pushed only 
			// Used for round-robin selection between all open dialogs.
			// NOTE - in Raspberry Pi 5 Wayland, Openbox window manger must be set to X11 backend
			//		  to enable Qt control over dialogs position!!!
			
			
			// Next dialog - ststic: kepy from last time
			last_opened_dialog_index++; 
			
			if (last_opened_dialog_index >= active_dialogs_list.size())
			{
				// Wrap around
				last_opened_dialog_index = 0;
			}
			
			int next_opened_dialog = 0;
			
			for (QDialog *dialog : active_dialogs_list) {
				
				if (dialog->isHidden())
				{
					// Skip hidden dialogs
					last_opened_dialog_index++;
					next_opened_dialog++;
			
					if (last_opened_dialog_index >= active_dialogs_list.size())
					{
						last_opened_dialog_index = 0;
					}	
					
					continue;
				}
				
				if (next_opened_dialog == last_opened_dialog_index)
				{
					position = dialog->pos();
					//position = mapToGlobal(dialog->rect().center());
					printf("%i %i\n", position.x(), position.y());
					dialog->hide();
					dialog->show();
					dialog->move(position);
					//dialog->move(mapFromGlobal(position));
					dialog->setFocus(Qt::ActiveWindowFocusReason);
					printf("%i %i\n", position.x(), position.y());
					break;
				}
				
				next_opened_dialog++;
			}
		}
	}
}


void MainWindow::on_patch_file_saved(const QString &s)
{
	
}

void MainWindow::on_patch_file_loaded(const QString &s)
{
	
}

/**
*	@brief	Copy the source Sketch parameters to the desitnation Sketch parametrs
*	@param	src		source sketch index
*	@param	dest	destination sketch index
*	@return none
*/
void MainWindow::copy_sketch(int src, int dest)
{
	char mssg[64];
	
	if ((src >= 0) && (src < _NUM_OF_SKETCHES) && 
		(dest >= 0) && (dest < _NUM_OF_SKETCHES) &&
		(dest != src))
	{
		QMessageBox msgBox;
		msgBox.setIcon(QMessageBox::Critical);
		msgBox.setWindowTitle("Warning");
		
		sprintf(mssg, "Are you sure you want to overide Sketch %i?", dest+1);		
		msgBox.setText(QString(mssg));
		msgBox.setStandardButtons(QMessageBox::Yes);
		msgBox.addButton(QMessageBox::No);
		msgBox.setDefaultButton(QMessageBox::No);
		if (msgBox.exec() == QMessageBox::Yes) 
		{
			mod_synth_copy_sketch(_SKETCH_PROGRAM_1 + src, _SKETCH_PROGRAM_1 + dest);
			Dialog_AnalogSynth::get_instance()->update_all();
		}
		else 
		{
			return;
		}		
	}
}

/**
*	@brief	Add a dialog to the active dialogs list
*	@param	dialog		a pointer to the Dialog object
*	@return none
*/
void MainWindow::register_active_dialog(QDialog *dialog)
{
	int i;
	bool found = false;

	std::list<QDialog*>::iterator it_dialogs = active_dialogs_list.begin();
	// Already registered?
	for (i = 0; i < active_dialogs_list.size(); i++)
	{
		if (*it_dialogs == dialog)
		{
			// Already registered
			found = true;
			break;
		}

		it_dialogs++;
	}

	if (!found)
	{
		active_dialogs_list.push_back(dialog);
	}
}

/**
*	@brief	Remove a dialog to the active dialogs list
*	@param	dialog		a pointer to the Dialog object
*	@return none
*/
void MainWindow::unregister_active_dialog(QDialog *dialog)
{
	active_dialogs_list.remove(dialog);
}

/**
*	@brief	Create the tools bar menus actions
*	@param	None
*	@return none
*/

void MainWindow::create_actions()
{
	add_fluid_synth_act = new QAction(tr("&FluidSynth"), this);
	add_fluid_synth_act->setStatusTip(tr("Open FluidSynth"));
	connect(add_fluid_synth_act, SIGNAL(triggered()), this, SLOT(on_add_fluid_synth_instrument()));
	
	add_hammond_organ_act = new QAction(tr("&Hammond Organ"), this);
	add_hammond_organ_act->setStatusTip(tr("Open Hammond Organ"));
	connect(add_hammond_organ_act, SIGNAL(triggered()), this, SLOT(on_add_hammond_organ_instrument()));
	
	add_adj_analog_synth_act = new QAction(tr("&Analog Synth"), this);
	add_adj_analog_synth_act->setStatusTip(tr("Open AdjHeart Analog Synth"));
	connect(add_adj_analog_synth_act, SIGNAL(triggered()), this, SLOT(on_add_adj_analog_synth_instrument()));
	
	add_adj_karplus_strong_strings_synth_act = new QAction(tr("&Karpuls Strong String Synth"), this);
	add_adj_karplus_strong_strings_synth_act->setStatusTip(tr("Open AdjHeart Karpuls Strong Strings Synth"));
	connect(add_adj_karplus_strong_strings_synth_act, SIGNAL(triggered()), this, SLOT(on_add_adj_karplus_strong_strings_synth_instrument()));
	
	add_adj_morphed_sin_synth_act = new QAction(tr("&Morphed Sinus Synth"), this);
	add_adj_morphed_sin_synth_act->setStatusTip(tr("Open AdjHeart Morphed Sinus Synth"));
	connect(add_adj_morphed_sin_synth_act, SIGNAL(triggered()), this, SLOT(on_add_adj_morphed_sin_synth_instrument()));
	
	add_adj_pad_synth_act = new QAction(tr("&PADsynth"), this);
	add_adj_pad_synth_act->setStatusTip(tr("Open AdjHeart PADsynth Synth"));
	connect(add_adj_pad_synth_act, SIGNAL(triggered()), this, SLOT(on_add_adj_pad_synth_instrument()));
	
	add_adj_midi_player_act = new QAction(tr("&MIDI Player"), this);
	add_adj_midi_player_act->setStatusTip(tr("Open AdjHeart MIDI Player"));
	connect(add_adj_midi_player_act, SIGNAL(triggered()), this, SLOT(on_add_adj_midi_player_instrument()));
	
	add_adj_reverb_effect_act = new QAction(tr("&Reverb Edffect"), this);
	add_adj_reverb_effect_act->setStatusTip(tr("Open AdjHeart Reveb Effect"));
	connect(add_adj_reverb_effect_act, SIGNAL(triggered()), this, SLOT(on_add_adj_reverb_effect_instrument()));
	
	add_adj_distortion_effect_act = new QAction(tr("&Distortion Edffect"), this);
	add_adj_distortion_effect_act->setStatusTip(tr("Open AdjHeart Distortion Effect"));
	connect(add_adj_distortion_effect_act, SIGNAL(triggered()), this, SLOT(on_add_adj_distortion_effect_instrument()));
	
	add_adj_graphic_equilizer_act = new QAction(tr("&Graphic Equilizer"), this);
	add_adj_graphic_equilizer_act->setStatusTip(tr("Open AdjHeart Graphic Equilizer"));
	connect(add_adj_graphic_equilizer_act, SIGNAL(triggered()), this, SLOT(on_add_adj_graphic_equilizer_instrument()));
	
	add_midi_mixer_act = new QAction(tr("&Midi Mixer"), this);
	add_midi_mixer_act->setStatusTip(tr("Open Midi Mixer"));
	connect(add_midi_mixer_act, SIGNAL(triggered()), this, SLOT(on_add_midi_mixer_instrument()));
	
	add_adj_midi_mapper_act = new QAction(tr("&MIDI Mapper"), this);
	add_adj_midi_mapper_act->setStatusTip(tr("Open AdjHeart MIDI Mapper"));
	connect(add_adj_midi_mapper_act, SIGNAL(triggered()), this, SLOT(on_add_adj_midi_mapper_instrument()));

	add_adj_external_midi_interface_control_act = new QAction(tr("&External MIDI Interface Control"), this);
	add_adj_external_midi_interface_control_act->setStatusTip(tr("Open AdjHeart External MIDI Interface Control"));
	connect(add_adj_external_midi_interface_control_act, SIGNAL(triggered()), this, 
									SLOT(on_add_adj_external_midi_interface_control_instrument()));
	
	add_adj_keyboard_control_act = new QAction(tr("&Keyboard Control"), this);
	add_adj_keyboard_control_act->setStatusTip(tr("Open AdjHeart Keyboard Control"));
	connect(add_adj_keyboard_control_act, SIGNAL(triggered()), this, SLOT(on_add_adj_keyboard_control_instrument()));
	
	save_patch_file_act = new QAction(tr("&Save Patch File"), this);
	save_patch_file_act->setStatusTip(tr("Saves AdjHeart Patch File"));
	connect(save_patch_file_act, SIGNAL(triggered()), this, SLOT(on_save_patch_file()));
	
	load_patch_file_act = new QAction(tr("&Load Patch File"), this);
	load_patch_file_act->setStatusTip(tr("Loads AdjHeart Patch File"));
	connect(load_patch_file_act, SIGNAL(triggered()), this, SLOT(on_load_patch_file()));
	
	copy_sketch1_to_sketch2_act = new QAction(tr("&Copy Sketch 1 to Sketch 2"), this);
	copy_sketch1_to_sketch2_act->setStatusTip(tr("Copy Sketch 1 to Sketch 2"));
	connect(copy_sketch1_to_sketch2_act, SIGNAL(triggered()), this, SLOT(on_copy_sketch1_to_sketch2()));
	
	copy_sketch1_to_sketch3_act = new QAction(tr("&Copy Sketch 1 to Sketch 3"), this);
	copy_sketch1_to_sketch3_act->setStatusTip(tr("Copy Sketch 1 to Sketch 3"));
	connect(copy_sketch1_to_sketch3_act, SIGNAL(triggered()), this, SLOT(on_copy_sketch1_to_sketch3()));
	
	copy_sketch2_to_sketch1_act = new QAction(tr("&Copy Sketch 2 to Sketch 1"), this);
	copy_sketch2_to_sketch1_act->setStatusTip(tr("Copy Sketch 2 to Sketch 1"));
	connect(copy_sketch2_to_sketch1_act, SIGNAL(triggered()), this, SLOT(on_copy_sketch2_to_sketch1()));
	
	copy_sketch2_to_sketch3_act = new QAction(tr("&Copy Sketch 2 to Sketch 3"), this);
	copy_sketch2_to_sketch3_act->setStatusTip(tr("Copy Sketch 2 to Sketch 3"));
	connect(copy_sketch2_to_sketch3_act, SIGNAL(triggered()), this, SLOT(on_copy_sketch2_to_sketch3()));
	
	copy_sketch3_to_sketch1_act = new QAction(tr("&Copy Sketch 3 to Sketch 1"), this);
	copy_sketch3_to_sketch1_act->setStatusTip(tr("Copy Sketch 3 to Sketch 1"));
	connect(copy_sketch3_to_sketch1_act, SIGNAL(triggered()), this, SLOT(on_copy_sketch3_to_sketch1()));
	
	copy_sketch3_to_sketch2_act = new QAction(tr("&Copy Sketch 3 to Sketch 2"), this);
	copy_sketch3_to_sketch2_act->setStatusTip(tr("Copy Sketch 3 to Sketch 2"));
	connect(copy_sketch3_to_sketch2_act, SIGNAL(triggered()), this, SLOT(on_copy_sketch3_to_sketch2()));
	
	
	//add_modules_group = new QActionGroup(this);
	//add_modules_group->addAction(add_fluid_synth_act);
	
}

/**
*	@brief	Create the tools bar menus
*	@param	None
*	@return none
*/
void MainWindow::create_menus()
{
	file_menu = menuBar()->addMenu(tr("&File"));
	file_menu->addAction(save_patch_file_act);
	file_menu->addAction(load_patch_file_act);
	file_menu->addSeparator();
	
	add_module_menu = menuBar()->addMenu(tr("&Add Instrument"));
	add_module_menu->addAction(add_fluid_synth_act);
	add_module_menu->addAction(add_hammond_organ_act);
	add_module_menu->addAction(add_adj_analog_synth_act);
	add_module_menu->addAction(add_adj_karplus_strong_strings_synth_act);
	add_module_menu->addAction(add_adj_morphed_sin_synth_act);
	add_module_menu->addAction(add_adj_pad_synth_act);
	add_module_menu->addSeparator();
	add_module_menu->addAction(add_adj_midi_player_act);
	add_module_menu->addSeparator();
	add_module_menu->addAction(add_adj_reverb_effect_act);
	add_module_menu->addAction(add_adj_distortion_effect_act);
	add_module_menu->addAction(add_adj_graphic_equilizer_act);
	add_module_menu->addSeparator();
	add_module_menu->addAction(add_midi_mixer_act);
	add_module_menu->addSeparator();
	add_module_menu->addAction(add_adj_midi_mapper_act);
	add_module_menu->addAction(add_adj_external_midi_interface_control_act);
	add_module_menu->addAction(add_adj_keyboard_control_act);
	
	sketches_menu = menuBar()->addMenu(tr("&Sketches"));
	sketches_menu->addAction(copy_sketch1_to_sketch2_act);
	sketches_menu->addAction(copy_sketch1_to_sketch3_act);
	sketches_menu->addAction(copy_sketch2_to_sketch1_act);
	sketches_menu->addAction(copy_sketch2_to_sketch3_act);
	sketches_menu->addAction(copy_sketch3_to_sketch1_act);
	sketches_menu->addAction(copy_sketch3_to_sketch2_act);	
	
	sketches_menu->setDisabled(true);
	
	help_menu = menuBar()->addMenu(tr("&Help"));
}
/**
*	@brief	Add an instrument pannel
*	@param	None
*	@return none
*/

InstrumentPannel* MainWindow::add_instrument_pannel(QString instrument_name_string)
{	
	QPoint last_posotion = QPoint(this->x(), this->y());
	
	if (instruments_ids_map.find(instrument_name_string.toStdString()) != instruments_ids_map.end())
	{
		/* No such instrument name */	
	}
	
	en_instruments_ids_t instrument_id = instruments_ids_map[instrument_name_string.toStdString()];
	
	
	if (instrument_id == en_instruments_ids_t::none_instrument_id)
	{
		return NULL;
	}
	
	InstrumentPannel *new_pannel = new InstrumentPannel(this,
							instrument_name_string, 
							&wrapper_close_instrument_pannel_id, 
							instrument_id);
	layout->addWidget(new_pannel);
	
	active_instrument_data_t new_instrument;
	new_instrument.instrument_id = instrument_id;
	new_instrument.instrument_name = instrument_name_string;
	new_instrument.instrument_pannel_object = new_pannel;
	new_instrument.pending_close_event = false;
	active_instruments_list.push_back(new_instrument);
	
	update_layout_geometry();
	
//	mod_synth_add_active_module(module_id);
	
	move(last_posotion);
	 
	return new_pannel;
}

int MainWindow::remove_instrument_pannel(InstrumentPannel *instrument)
{
	if ((instrument == Q_NULLPTR) || (layout == Q_NULLPTR))
	{
		return -1;
	}
	else
	{
		layout->removeWidget(instrument);
		//delete(module);
		instrument->hide();
		
		update_layout_geometry();
		
//		mod_synth_remove_active_module(module->module_id); 
		
		if (instrument->instrument_id == en_instruments_ids_t::fluid_synth)
		{
			
		}
		else if (instrument->instrument_id == en_instruments_ids_t::adj_midi_player)
		{
			
		}
	}
	
	return 0;
}


/**
*   @brief Returns the instrument position in the active instruments list if th instrument is oppened.
*   @param  en_instrumentsIds_t					a unique enum identifier of each instrument type.
*	@return instrument position; -1 otherwise 
*/
int MainWindow::is_instrument_openned(en_instruments_ids_t instId)
{
	for (int i = 0; i < active_instruments_list.size(); ++i)
	{
		if (active_instruments_list[i].instrument_id == instId)
			return i;
	}
	
	return -1;
}


int MainWindow::update_layout_geometry()
{
	if (layout == Q_NULLPTR)
	{
		return -1;
	}
	else
	{
		QRect layoutSize = QRect(20, 20, 800 + 20, 120 * active_instruments_list.size() + 60);
	
		this->setGeometry(layoutSize);
	}
	
	return 0;
}

void MainWindow::close_instrument_pannel_id(en_instruments_ids_t inst_id)
{
	InstrumentPannel *instrument;
	
	int pos = is_instrument_openned(inst_id);
	
	if (pos >= 0)
	{
		instrument = active_instruments_list[pos].instrument_pannel_object;		
		active_instruments_list.erase(active_instruments_list.begin() + pos);
		
		remove_instrument_pannel(instrument);
	}
	
}

void MainWindow::close_instrument_pannel_name(string inst_name)
{
	if (instruments_ids_map.find(inst_name) != instruments_ids_map.end()) {
		// found
		close_instrument_pannel_id(instruments_ids_map[inst_name]);
	}
}

std::vector<std::string> MainWindow::get_active_instruments_names_list()
{
	std::vector<std::string> names_list_str;
	
	for (active_instrument_data_t module : active_instruments_list)
	{
		names_list_str.push_back(module.instrument_name.toStdString());
	}
	
	return names_list_str;
}

void MainWindow::request_close_instrument_pannel_id(en_instruments_ids_t inst_id)
{
	for (int m = 0; m < active_instruments_list.size(); m++)
	{
		if (active_instruments_list.at(m).instrument_id == inst_id)
		{
			active_instruments_list.at(m).pending_close_event = true;
			break;
		}
	}
}

void MainWindow::request_close_instrument_pannel_name(string inst_name)
{
	for (int m = 0; m < active_instruments_list.size(); m++)
	{
		if (active_instruments_list.at(m).instrument_name.toStdString() == inst_name)
		{
			active_instruments_list.at(m).pending_close_event = true;
			break;
		}
	}
}

void MainWindow::start_update_timer(int interval)
{
	QTimer *timer = new QTimer(this);
	connect(timer, SIGNAL(timeout()), this, SLOT(timerEvent()));
	timer->start(interval);
}

void MainWindow::timerEvent()
{
	update_gui();
}

void MainWindow::update_gui()
{
	int m;
	
	for (m = 0; m < active_instruments_list.size(); m++)
	{
		if (active_instruments_list.at(m).pending_close_event)
		{
			close_instrument_pannel_id(active_instruments_list.at(m).instrument_id);
		}
	}
	
	for (m = 0; m < pending_open_instruments_list.size(); m++)
	{
		add_instrument_pannel(QString::fromStdString(pending_open_instruments_list.at(m)));
	}
	
	pending_open_instruments_list.erase(pending_open_instruments_list.begin(),
		pending_open_instruments_list.begin() + m);
}

void MainWindow::on_add_fluid_synth_instrument()
{
	InstrumentPannel *newPannel;

	if ((is_instrument_openned(en_instruments_ids_t::fluid_synth) < 0) &&
		(active_instruments_list.size() < MAX_NUM_OF_MODULES))
	{
		// instrument is not already oppened

		newPannel = add_instrument_pannel(_INSTRUMENT_NAME_FLUID_SYNTH_STR_KEY);
	}
}

void MainWindow::on_add_hammond_organ_instrument()
{
	InstrumentPannel *newPannel;

	if ((is_instrument_openned(en_instruments_ids_t::adj_hammond_organ) < 0) &&
		(active_instruments_list.size() < MAX_NUM_OF_MODULES))
	{
		// instrument is not already oppened

		newPannel = add_instrument_pannel(_INSTRUMENT_NAME_HAMMON_ORGAN_STR_KEY);
	}
}

void MainWindow::on_add_adj_analog_synth_instrument()
{
	InstrumentPannel *newPannel;
	
	if ((is_instrument_openned(en_instruments_ids_t::adj_analog_synth) < 0)&&
		(active_instruments_list.size() < MAX_NUM_OF_MODULES))
	{
		// instrument is not already oppened

		newPannel = add_instrument_pannel(_INSTRUMENT_NAME_ANALOG_SYNTH_STR_KEY);
	}
	
	
}

void MainWindow::on_add_adj_karplus_strong_strings_synth_instrument()
{
	InstrumentPannel *newPannel;
	
	if ((is_instrument_openned(en_instruments_ids_t::adj_karplusstrong_string_synth) < 0)&&
		(active_instruments_list.size() < MAX_NUM_OF_MODULES))
	{
		// instrument is not already oppened

		newPannel = add_instrument_pannel(_INSTRUMENT_NAME_KARPLUS_STRONG_STRING_SYNTH_STR_KEY);
	}
}

void MainWindow::on_add_adj_morphed_sin_synth_instrument()
{
	InstrumentPannel *newPannel;
	
	if ((is_instrument_openned(en_instruments_ids_t::adj_morphed_sin_synth) < 0) &&
		(active_instruments_list.size() < MAX_NUM_OF_MODULES))
	{
		// instrument is not already oppened

		newPannel = add_instrument_pannel(_INSTRUMENT_NAME_MORPHED_SINUS_SYNTH_STR_KEY);
	}
}

void MainWindow::on_add_adj_pad_synth_instrument()
{
	InstrumentPannel *newPannel;
	
	if ((is_instrument_openned(en_instruments_ids_t::adj_pad_synth) < 0)&&
		(active_instruments_list.size() < MAX_NUM_OF_MODULES))
	{
		// instrument is not already oppened

		newPannel = add_instrument_pannel(_INSTRUMENT_NAME_PADSYNTH_SYNTH_STR_KEY);
	}
}

void MainWindow::on_add_adj_midi_player_instrument()
{
	InstrumentPannel *newPannel;
	
	if ((is_instrument_openned(en_instruments_ids_t::adj_midi_player) < 0)&&
		(active_instruments_list.size() < MAX_NUM_OF_MODULES))
	{
		// instrument is not already oppened

		newPannel = add_instrument_pannel(_INSTRUMENT_NAME_MIDI_PLAYER_STR_KEY);
	}
}

void MainWindow::on_add_adj_reverb_effect_instrument()
{
	InstrumentPannel *newPannel;
	
	if ((is_instrument_openned(en_instruments_ids_t::adj_reverb_effect) < 0)&&
		(active_instruments_list.size() < MAX_NUM_OF_MODULES))
	{
		// instrument is not already oppened

		newPannel = add_instrument_pannel(_INSTRUMENT_NAME_REVERB_STR_KEY);
	}
}

void MainWindow::on_add_adj_distortion_effect_instrument()
{
	InstrumentPannel *newPannel;
	
	if ((is_instrument_openned(en_instruments_ids_t::adj_distortion_effect) < 0)&&
		(active_instruments_list.size() < MAX_NUM_OF_MODULES))
	{
		// instrument is not already oppened

		newPannel = add_instrument_pannel(_INSTRUMENT_NAME_DISTORTION_STR_KEY);
	}
}

void MainWindow::on_add_adj_graphic_equilizer_instrument()
{
	InstrumentPannel *newPannel;
	
	if ((is_instrument_openned(en_instruments_ids_t::adj_graphic_equilizer) < 0)&&
		(active_instruments_list.size() < MAX_NUM_OF_MODULES))
	{
		// instrument is not already oppened

		newPannel = add_instrument_pannel(_INSTRUMENT_NAME_GRAPHIC_EQUALIZER_STR_KEY);
	}
}

void MainWindow::on_add_midi_mixer_instrument()
{
	InstrumentPannel *newPannel;
	
	if ((is_instrument_openned(en_instruments_ids_t::midi_mixer) < 0)&&
		(active_instruments_list.size() < MAX_NUM_OF_MODULES))
	{
		// instrument is not already oppened

		newPannel = add_instrument_pannel(_INSTRUMENT_NAME_MIDI_MIXER_STR_KEY);
	}
}

void MainWindow::on_add_adj_midi_mapper_instrument()
{
	InstrumentPannel *newPannel;
	
	if ((is_instrument_openned(en_instruments_ids_t::adj_midi_mapper) < 0)&&
		(active_instruments_list.size() < MAX_NUM_OF_MODULES))
	{
		// instrument is not already oppened

		newPannel = add_instrument_pannel(_INSTRUMENT_NAME_MIDI_MAPPER_STR_KEY);
	}
}

void MainWindow::on_add_adj_external_midi_interface_control_instrument()
{
	InstrumentPannel *newPannel;
	
	if ((is_instrument_openned(en_instruments_ids_t::adj_ext_midi_interface) < 0) &&
		(active_instruments_list.size() < MAX_NUM_OF_MODULES))
	{
		// instrument is not already oppened

		newPannel = add_instrument_pannel(_INSTRUMENT_NAME_EXT_MIDI_INT_CONTROL_STR_KEY);

		newPannel->hide_checkBox_InstrumentMIDIin();
	}
}

void MainWindow::on_add_adj_keyboard_control_instrument()
{
	InstrumentPannel *newPannel;
	
	if ((is_instrument_openned(en_instruments_ids_t::adj_keyboard_control) < 0)&&
		(active_instruments_list.size() < MAX_NUM_OF_MODULES))
	{
		// instrument is not already oppened

		newPannel = add_instrument_pannel(_INSTRUMENT_NAME_KEYBOARD_CONTROL_STR_KEY);
	}
}

void MainWindow::on_save_patch_file()
{
	QFileDialog dialog;
	int res;
	
	patch_file_name = dialog.getSaveFileName(this,
		tr("Save Patch File "),
		QString(_PATCHES_FILES_DEFAULT_DIR),
		tr("Presets (*.json *.JSON);;All Files (*)"));

	if (!patch_file_name.isEmpty())
	{
		save_patch_file_thread = new SavePatchFileThread();
		
		connect(save_patch_file_thread,
			&SavePatchFileThread::finished,
			save_patch_file_thread,
			&QObject::deleteLater);
		connect(save_patch_file_thread,
			&SavePatchFileThread::savePatchFileDone, 
			this,
			&MainWindow::on_patch_file_saved);
		
		save_patch_file_thread->start();		
	}
}

void MainWindow::on_load_patch_file()
{
	QFileDialog dialog;
	int res;
	
	patch_file_name = dialog.getOpenFileName(this,
		tr("Open Patch File "),
		QString(_PATCHES_FILES_DEFAULT_DIR),
		tr("Presets (*.json *.JSON);;All Files (*)"));

	if (!patch_file_name.isEmpty())
	{
		load_patch_file_thread = new LoadPatchFileThread();
		
		connect(load_patch_file_thread,
			&LoadPatchFileThread::finished,
			load_patch_file_thread,
			&QObject::deleteLater);
		connect(load_patch_file_thread,
			&LoadPatchFileThread::loadPatchFileDone, 
			this,
			&MainWindow::on_patch_file_loaded);
		
		load_patch_file_thread->start();
	}
	
}

void MainWindow::on_copy_sketch1_to_sketch2()
{
	copy_sketch(0, 1);
}

void MainWindow::on_copy_sketch1_to_sketch3()
{
	copy_sketch(0, 2);
}

void MainWindow::on_copy_sketch2_to_sketch1()
{
	copy_sketch(1, 0);
}

void MainWindow::on_copy_sketch2_to_sketch3()
{
	copy_sketch(1, 2);
}

void MainWindow::on_copy_sketch3_to_sketch1()
{
	copy_sketch(2, 0);
}

void MainWindow::on_copy_sketch3_to_sketch2()
{
	copy_sketch(2, 1);
}


	
