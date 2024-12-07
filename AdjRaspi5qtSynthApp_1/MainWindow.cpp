/**
*	@file		MainWindow.cpp
*	@author		Nahum Budin
*	@date		8-May-2024
*	@version	1.0 
*	
*	Version	1.0		8-May-2024
*
*	@brief		Application Main Window that hosts the modules pannels as acolomn.
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

#include "ModulePannel.h"

#include "Dialog_AdjFluidSynth.h"

SavePatchFileThread *save_patch_file_thread;
LoadPatchFileThread *load_patch_file_thread;

QString patch_file_name;

/** Callback wrapper */

void wrapper_close_module_pannel_id(en_modules_ids_t mo_id)
{
	MainWindow::get_instance()->close_module_pannel_id(mo_id);
}
void wrapper_request_close_module_pannel_id(en_modules_ids_t mo_id)
{
	MainWindow::get_instance()->request_close_module_pannel_id(mo_id);
}

void wrapper_request_open_module_window_name(string module_name)
{
	MainWindow::get_instance()->pending_open_modules_list.push_back(module_name);
}


void wrapper_request_close_module_pannel_name(string mod_name)
{
	MainWindow::get_instance()->request_close_module_pannel_name(mod_name);
}

void main_window_control_box_event_update_ui_callback_wrapper(int evnt, uint16_t val)
{
	MainWindow::get_instance()->control_box_ui_update_callback(evnt, val);
}

std::vector <std::string> get_active_modules_names_list_wrapper()
{
	return MainWindow::get_instance()->get_active_modules_names_list();
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
	
	create_actions();
	create_menus();
	
	mod_synth_register_callback_control_box_event_update_ui(
		&main_window_control_box_event_update_ui_callback_wrapper);
	
	mod_synth_register_callback_get_active_modules_names_list(
		&get_active_modules_names_list_wrapper);
	
	mod_synth_register_callback_wrapper_close_module_pannel_id(
		&wrapper_request_close_module_pannel_id);
	
	mod_synth_register_callback_wrapper_close_module_pannel_name(
		&wrapper_request_close_module_pannel_name);
	
	mod_synth_register_callback_wrapper_open_module_pannel_name(
		&wrapper_request_open_module_window_name);
	
	modules_ids_map[_INSTRUMENT_NAME_FLUID_SYNTH_STR_KEY] = 
		en_modules_ids_t::fluid_synth;
	modules_ids_map[_INSTRUMENT_NAME_HAMMON_ORGAN_STR_KEY] = 
		en_modules_ids_t::adj_hammond_organ;
	modules_ids_map[_INSTRUMENT_NAME_ANALOG_SYNTH_STR_KEY] = 
		en_modules_ids_t::adj_analog_synth;
	modules_ids_map[_INSTRUMENT_NAME_KARPLUS_STRONG_STRING_SYNTH_STR_KEY] = 
		en_modules_ids_t::adj_karplusstrong_string_synth;
	modules_ids_map[_INSTRUMENT_NAME_MORPHED_SINUS_SYNTH_STR_KEY] = 
		en_modules_ids_t::adj_morphed_sin_synth;
	modules_ids_map[_INSTRUMENT_NAME_PADSYNTH_SYNTH_STR_KEY] = 
		en_modules_ids_t::adj_pad_synth;
	modules_ids_map[_INSTRUMENT_NAME_MIDI_PLAYER_STR_KEY] = 
		en_modules_ids_t::adj_midi_player;
	modules_ids_map[_INSTRUMENT_NAME_MIDI_MIXER_STR_KEY] = 
		en_modules_ids_t::midi_mixer;
	modules_ids_map[_INSTRUMENT_NAME_MIDI_MAPPER_STR_KEY] = 
		en_modules_ids_t::adj_midi_mapper;
	modules_ids_map[_INSTRUMENT_NAME_REVERB_STR_KEY] = 
		en_modules_ids_t::adj_reverb_effect;
	modules_ids_map[_INSTRUMENT_NAME_DISTORTION_STR_KEY] = 
		en_modules_ids_t::adj_distortion_effect;
	modules_ids_map[_INSTRUMENT_NAME_GRAPHIC_EQUALIZER_STR_KEY] = 
		en_modules_ids_t::adj_graphic_equilizer;
	modules_ids_map[_INSTRUMENT_NAME_EXT_MIDI_INT_CONTROL_STR_KEY] = 
		en_modules_ids_t::adj_ext_midi_interface;
	modules_ids_map[_INSTRUMENT_NAME_KEYBOARD_CONTROL_STR_KEY] = 
		en_modules_ids_t::adj_keyboard_control;
	
	// start a periodic timer after this timeout - 
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

void MainWindow::control_box_ui_update_callback(int evnt, uint16_t val)
{
	static int index = 0;
	QPoint position;
	
	if (evnt == _CONTROL_FUNCTION_PUSHBUTTON_REDOO)
	{
		if (val == 0)
		{
			/* Pushed only */
			/* Used for round-robin selection of open dialogs. */
			index++;
			
			if (index >= active_dialogs_list.size())
			{
				index = 0;
			}
			
			int count = 0;
			
			for (QDialog *dialog : active_dialogs_list) {
				
				if (dialog->isHidden())
				{
					/* Skip hidden dialogs */
					index++;
					count++;
			
					if (index >= active_dialogs_list.size())
					{
						index = 0;
					}	
					
					continue;
				}
				
				if (count == index)
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
				
				count++;
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

void MainWindow::register_active_dialog(QDialog *dialog)
{
	int i;
	bool found = false;

	std::list<QDialog*>::iterator it_dialogs = active_dialogs_list.begin();
	/* Already registered? */
	for (i = 0; i < active_dialogs_list.size(); i++)
	{
		if (*it_dialogs == dialog)
		{
			/* Already registered */
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
void MainWindow::unregister_active_dialog(QDialog *dialog)
{
	active_dialogs_list.remove(dialog);
}

void MainWindow::create_actions()
{
	add_fluid_synth_act = new QAction(tr("&FluidSynth"), this);
	add_fluid_synth_act->setStatusTip(tr("Open FluidSynth"));
	connect(add_fluid_synth_act, SIGNAL(triggered()), this, SLOT(on_add_fluid_synth_module()));
	
	add_hammond_organ_act = new QAction(tr("&Hammond Organ"), this);
	add_hammond_organ_act->setStatusTip(tr("Open Hammond Organ"));
	connect(add_hammond_organ_act, SIGNAL(triggered()), this, SLOT(on_add_hammond_organ_module()));
	
	add_adj_analog_synth_act = new QAction(tr("&Analog Synth"), this);
	add_adj_analog_synth_act->setStatusTip(tr("Open AdjHeart Analog Synth"));
	connect(add_adj_analog_synth_act, SIGNAL(triggered()), this, SLOT(on_add_adj_analog_synth_module()));
	
	add_adj_karplus_strong_strings_synth_act = new QAction(tr("&Karpuls Strong String Synth"), this);
	add_adj_karplus_strong_strings_synth_act->setStatusTip(tr("Open AdjHeart Karpuls Strong Strings Synth"));
	connect(add_adj_karplus_strong_strings_synth_act, SIGNAL(triggered()), this, SLOT(on_add_adj_karplus_strong_strings_synth_module()));
	
	add_adj_morphed_sin_synth_act = new QAction(tr("&Morphed Sinus Synth"), this);
	add_adj_morphed_sin_synth_act->setStatusTip(tr("Open AdjHeart Morphed Sinus Synth"));
	connect(add_adj_morphed_sin_synth_act, SIGNAL(triggered()), this, SLOT(on_add_adj_morphed_sin_synth_module()));
	
	add_adj_pad_synth_act = new QAction(tr("&PADsynth"), this);
	add_adj_pad_synth_act->setStatusTip(tr("Open AdjHeart PADsynth Synth"));
	connect(add_adj_pad_synth_act, SIGNAL(triggered()), this, SLOT(on_add_adj_pad_synth_module()));
	
	add_adj_midi_player_act = new QAction(tr("&MIDI Player"), this);
	add_adj_midi_player_act->setStatusTip(tr("Open AdjHeart MIDI Player"));
	connect(add_adj_midi_player_act, SIGNAL(triggered()), this, SLOT(on_add_adj_midi_player_module()));
	
	add_adj_reverb_effect_act = new QAction(tr("&Reverb Edffect"), this);
	add_adj_reverb_effect_act->setStatusTip(tr("Open AdjHeart Reveb Effect"));
	connect(add_adj_reverb_effect_act, SIGNAL(triggered()), this, SLOT(on_add_adj_reverb_effect_module()));
	
	add_adj_distortion_effect_act = new QAction(tr("&Distortion Edffect"), this);
	add_adj_distortion_effect_act->setStatusTip(tr("Open AdjHeart Distortion Effect"));
	connect(add_adj_distortion_effect_act, SIGNAL(triggered()), this, SLOT(on_add_adj_distortion_effect_module()));
	
	add_adj_graphic_equilizer_act = new QAction(tr("&Graphic Equilizer"), this);
	add_adj_graphic_equilizer_act->setStatusTip(tr("Open AdjHeart Graphic Equilizer"));
	connect(add_adj_graphic_equilizer_act, SIGNAL(triggered()), this, SLOT(on_add_adj_graphic_equilizer_module()));
	
	add_midi_mixer_act = new QAction(tr("&Midi Mixer"), this);
	add_midi_mixer_act->setStatusTip(tr("Open Midi Mixer"));
	connect(add_midi_mixer_act, SIGNAL(triggered()), this, SLOT(on_add_midi_mixer_module()));
	
	add_adj_midi_mapper_act = new QAction(tr("&MIDI Mapper"), this);
	add_adj_midi_mapper_act->setStatusTip(tr("Open AdjHeart MIDI Mapper"));
	connect(add_adj_midi_mapper_act, SIGNAL(triggered()), this, SLOT(on_add_adj_midi_mapper_module()));

	add_adj_external_midi_interface_control_act = new QAction(tr("&External MIDI Interface Control"), this);
	add_adj_external_midi_interface_control_act->setStatusTip(tr("Open AdjHeart External MIDI Interface Control"));
	connect(add_adj_external_midi_interface_control_act, SIGNAL(triggered()), this, SLOT(on_add_adj_external_midi_interface_control_module()));
	
	add_adj_keyboard_control_act = new QAction(tr("&Keyboard Control"), this);
	add_adj_keyboard_control_act->setStatusTip(tr("Open AdjHeart Keyboard Control"));
	connect(add_adj_keyboard_control_act, SIGNAL(triggered()), this, SLOT(on_add_adj_keyboard_control_module()));
	
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

void MainWindow::create_menus()
{
	file_menu = menuBar()->addMenu(tr("&File"));
	file_menu->addAction(save_patch_file_act);
	file_menu->addAction(load_patch_file_act);
	file_menu->addSeparator();
	
	add_module_menu = menuBar()->addMenu(tr("&Add Module"));
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

ModulePannel* MainWindow::add_module_pannel(QString module_name_string)
{	
	QPoint last_posotion = QPoint(this->x(), this->y());
	
	if (modules_ids_map.find(module_name_string.toStdString()) != modules_ids_map.end())
	{
		/* No such module name */	
	}
	
	en_modules_ids_t module_id = modules_ids_map[module_name_string.toStdString()];
	
	
	if (module_id == en_modules_ids_t::none_module_id)
	{
		return NULL;
	}
	
	ModulePannel *new_pannel = new ModulePannel(this,
							module_name_string, 
							&wrapper_close_module_pannel_id, 
							module_id);
	layout->addWidget(new_pannel);
	
	active_module_data_t new_module;
	new_module.module_id = module_id;
	new_module.module_name = module_name_string;
	new_module.module_pannel_object = new_pannel;
	new_module.pending_close_event = false;
	active_modules_list.push_back(new_module);
	
	update_layout_geometry();
	
//	mod_synth_add_active_module(module_id);
	
	move(last_posotion);
	 
	return new_pannel;
}

int MainWindow::remove_module_pannel(ModulePannel *module)
{
	if ((module == Q_NULLPTR) || (layout == Q_NULLPTR))
	{
		return -1;
	}
	else
	{
		layout->removeWidget(module);
		//delete(module);
		module->hide();
		
		update_layout_geometry();
		
//		mod_synth_remove_active_module(module->module_id); 
		
		if (module->module_id == en_modules_ids_t::fluid_synth)
		{
			
		}
		else if (module->module_id == en_modules_ids_t::adj_midi_player)
		{
			
		}
	}
	
	return 0;
}


/**
*   @brief Returns the module position in the active modules list if th module is oppened.
*   @param  en_modulesIds_t					a unique enum identifier of each module type.
*	@return module position; -1 otherwise 
*/
int MainWindow::is_module_openned(en_modules_ids_t moId)
{
	for (int i = 0; i < active_modules_list.size(); ++i)
	{
		if (active_modules_list[i].module_id == moId)
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
		QRect layoutSize = QRect(20, 20, 800 + 20, 120 * active_modules_list.size() + 60);
	
		this->setGeometry(layoutSize);
	}
	
	return 0;
}

void MainWindow::close_module_pannel_id(en_modules_ids_t mod_id)
{
	ModulePannel *module;
	
	int pos = is_module_openned(mod_id);
	
	if (pos >= 0)
	{
		module = active_modules_list[pos].module_pannel_object;		
		active_modules_list.erase(active_modules_list.begin() + pos);
		
		remove_module_pannel(module);
	}
	
}

void MainWindow::close_module_pannel_name(string mod_name)
{
	if (modules_ids_map.find(mod_name) != modules_ids_map.end()) {
		// found
		close_module_pannel_id(modules_ids_map[mod_name]);
	}
}

std::vector<std::string> MainWindow::get_active_modules_names_list()
{
	std::vector<std::string> names_list_str;
	
	for (active_module_data_t module : active_modules_list)
	{
		names_list_str.push_back(module.module_name.toStdString());
	}
	
	return names_list_str;
}

void MainWindow::request_close_module_pannel_id(en_modules_ids_t mo_id)
{
	for (int m = 0; m < active_modules_list.size(); m++)
	{
		if (active_modules_list.at(m).module_id == mo_id)
		{
			active_modules_list.at(m).pending_close_event = true;
			break;
		}
	}
}

void MainWindow::request_close_module_pannel_name(string mod_name)
{
	for (int m = 0; m < active_modules_list.size(); m++)
	{
		if (active_modules_list.at(m).module_name.toStdString() == mod_name)
		{
			active_modules_list.at(m).pending_close_event = true;
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
	
	for (m = 0; m < active_modules_list.size(); m++)
	{
		if (active_modules_list.at(m).pending_close_event)
		{
			close_module_pannel_id(active_modules_list.at(m).module_id);
		}
	}
	
	for (m = 0; m < pending_open_modules_list.size(); m++)
	{
		add_module_pannel(QString::fromStdString(pending_open_modules_list.at(m)));
	}
	
	pending_open_modules_list.erase(pending_open_modules_list.begin(),
									pending_open_modules_list.begin() + m);
}

void MainWindow::on_add_fluid_synth_module()
{
	ModulePannel *newPannel;

	if ((is_module_openned(en_modules_ids_t::fluid_synth) < 0) &&
		(active_modules_list.size() < MAX_NUM_OF_MODULES))
	{
		// Module is not already oppened

		newPannel = add_module_pannel(_INSTRUMENT_NAME_FLUID_SYNTH_STR_KEY);
	}
}

void MainWindow::on_add_hammond_organ_module()
{
	ModulePannel *newPannel;

	if ((is_module_openned(en_modules_ids_t::adj_hammond_organ) < 0) &&
		(active_modules_list.size() < MAX_NUM_OF_MODULES))
	{
		// Module is not already oppened

		newPannel = add_module_pannel(_INSTRUMENT_NAME_HAMMON_ORGAN_STR_KEY);
	}
}

void MainWindow::on_add_adj_analog_synth_module()
{
	ModulePannel *newPannel;
	
	if ((is_module_openned(en_modules_ids_t::adj_analog_synth) < 0)&&
		(active_modules_list.size() < MAX_NUM_OF_MODULES))
	{
		// Module is not already oppened

		newPannel = add_module_pannel(_INSTRUMENT_NAME_ANALOG_SYNTH_STR_KEY);
	}
	
	
}

void MainWindow::on_add_adj_karplus_strong_strings_synth_module()
{
	ModulePannel *newPannel;
	
	if ((is_module_openned(en_modules_ids_t::adj_karplusstrong_string_synth) < 0)&&
		(active_modules_list.size() < MAX_NUM_OF_MODULES))
	{
		// Module is not already oppened

		newPannel = add_module_pannel(_INSTRUMENT_NAME_KARPLUS_STRONG_STRING_SYNTH_STR_KEY);
	}
}

void MainWindow::on_add_adj_morphed_sin_synth_module()
{
	ModulePannel *newPannel;
	
	if ((is_module_openned(en_modules_ids_t::adj_morphed_sin_synth) < 0) &&
		(active_modules_list.size() < MAX_NUM_OF_MODULES))
	{
		// Module is not already oppened

		newPannel = add_module_pannel(_INSTRUMENT_NAME_MORPHED_SINUS_SYNTH_STR_KEY);
	}
}

void MainWindow::on_add_adj_pad_synth_module()
{
	ModulePannel *newPannel;
	
	if ((is_module_openned(en_modules_ids_t::adj_pad_synth) < 0)&&
		(active_modules_list.size() < MAX_NUM_OF_MODULES))
	{
		// Module is not already oppened

		newPannel = add_module_pannel(_INSTRUMENT_NAME_PADSYNTH_SYNTH_STR_KEY);
	}
}

void MainWindow::on_add_adj_midi_player_module()
{
	ModulePannel *newPannel;
	
	if ((is_module_openned(en_modules_ids_t::adj_midi_player) < 0)&&
		(active_modules_list.size() < MAX_NUM_OF_MODULES))
	{
		// Module is not already oppened

		newPannel = add_module_pannel(_INSTRUMENT_NAME_MIDI_PLAYER_STR_KEY);
	}
}

void MainWindow::on_add_adj_reverb_effect_module()
{
	ModulePannel *newPannel;
	
	if ((is_module_openned(en_modules_ids_t::adj_reverb_effect) < 0)&&
		(active_modules_list.size() < MAX_NUM_OF_MODULES))
	{
		// Module is not already oppened

		newPannel = add_module_pannel(_INSTRUMENT_NAME_REVERB_STR_KEY);
	}
}

void MainWindow::on_add_adj_distortion_effect_module()
{
	ModulePannel *newPannel;
	
	if ((is_module_openned(en_modules_ids_t::adj_distortion_effect) < 0)&&
		(active_modules_list.size() < MAX_NUM_OF_MODULES))
	{
		// Module is not already oppened

		newPannel = add_module_pannel(_INSTRUMENT_NAME_DISTORTION_STR_KEY);
	}
}

void MainWindow::on_add_adj_graphic_equilizer_module()
{
	ModulePannel *newPannel;
	
	if ((is_module_openned(en_modules_ids_t::adj_graphic_equilizer) < 0)&&
		(active_modules_list.size() < MAX_NUM_OF_MODULES))
	{
		// Module is not already oppened

		newPannel = add_module_pannel(_INSTRUMENT_NAME_GRAPHIC_EQUALIZER_STR_KEY);
	}
}

void MainWindow::on_add_midi_mixer_module()
{
	ModulePannel *newPannel;
	
	if ((is_module_openned(en_modules_ids_t::midi_mixer) < 0)&&
		(active_modules_list.size() < MAX_NUM_OF_MODULES))
	{
		// Module is not already oppened

		newPannel = add_module_pannel(_INSTRUMENT_NAME_MIDI_MIXER_STR_KEY);
	}
}

void MainWindow::on_add_adj_midi_mapper_module()
{
	ModulePannel *newPannel;
	
	if ((is_module_openned(en_modules_ids_t::adj_midi_mapper) < 0)&&
		(active_modules_list.size() < MAX_NUM_OF_MODULES))
	{
		// Module is not already oppened

		newPannel = add_module_pannel(_INSTRUMENT_NAME_MIDI_MAPPER_STR_KEY);
	}
}

void MainWindow::on_add_adj_external_midi_interface_control_module()
{
	ModulePannel *newPannel;
	
	if ((is_module_openned(en_modules_ids_t::adj_ext_midi_interface) < 0) &&
		(active_modules_list.size() < MAX_NUM_OF_MODULES))
	{
		// Module is not already oppened

		newPannel = add_module_pannel(_INSTRUMENT_NAME_EXT_MIDI_INT_CONTROL_STR_KEY);

		newPannel->get_the_module_pannel()->ui->checkBox_ModuleMIDIin->hide();
	}
}

void MainWindow::on_add_adj_keyboard_control_module()
{
	ModulePannel *newPannel;
	
	if ((is_module_openned(en_modules_ids_t::adj_keyboard_control) < 0)&&
		(active_modules_list.size() < MAX_NUM_OF_MODULES))
	{
		// Module is not already oppened

		newPannel = add_module_pannel(_INSTRUMENT_NAME_KEYBOARD_CONTROL_STR_KEY);
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


	
