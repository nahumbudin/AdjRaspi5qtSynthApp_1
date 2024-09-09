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

#include "MainWindow.h"
#include "ui_MainWindow.h"
#include "ui_ModulePannel.h"

#include "ModulePannel.h"
#include <QVBoxLayout>
#include <QFrame>
#include <aarch64-linux-gnu/qt5/QtWidgets/qboxlayout.h>


/** Callback wrapper */
void wrapper_closeModulePannel(en_modules_ids_t moId)
{
	MainWindow::getInstance()->closeModulePannel(moId);
}

MainWindow *MainWindow::mwind = NULL;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
	
	mwind = this;
	mwind->move(10, 10);
	
	ui->centralwidget->setLayout(new QVBoxLayout);
	layout = qobject_cast<QVBoxLayout*>(ui->centralwidget->layout());
	
	create_actions();
	create_menus();
	
}

MainWindow::~MainWindow()
{
    delete ui;
}

MainWindow *MainWindow::getInstance() {

	if (!mwind)
		mwind = new MainWindow();

	return mwind;
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
	connect(add_adj_morphed_sin_synth_act, SIGNAL(triggered()), this, SLOT(on__add_adj_morphed_sin_synth_module()));
	
	add_adj_pad_synth_act = new QAction(tr("&PADsynth"), this);
	add_adj_pad_synth_act->setStatusTip(tr("Open AdjHeart PADsynth Synth"));
	connect(add_adj_pad_synth_act, SIGNAL(triggered()), this, SLOT(on_add_adj_pad_synth_module()));
	
	add_adj_reverb_effect_act = new QAction(tr("&Reverb Edffect"), this);
	add_adj_reverb_effect_act->setStatusTip(tr("Open AdjHeart Reveb Effect"));
	connect(add_adj_reverb_effect_act, SIGNAL(triggered()), this, SLOT(on_add_adj_reverb_effect_module()));
	
	add_adj_distortion_effect_act = new QAction(tr("&Distortion Edffect"), this);
	add_adj_distortion_effect_act->setStatusTip(tr("Open AdjHeart Distortion Effect"));
	connect(add_adj_distortion_effect_act, SIGNAL(triggered()), this, SLOT(on_add_adj_distortion_effect_module()));
	
	add_adj_graphic_equilizer_act = new QAction(tr("&Graphic Equilizer"), this);
	add_adj_graphic_equilizer_act->setStatusTip(tr("Open AdjHeart Graphic Equilizer"));
	connect(add_adj_graphic_equilizer_act, SIGNAL(triggered()), this, SLOT(on_add_adj_graphic_equilizer_module()));
	
	add_adj_output_mixer_act = new QAction(tr("&Output Mixer"), this);
	add_adj_output_mixer_act->setStatusTip(tr("Open AdjHeart Output Mixer"));
	connect(add_adj_output_mixer_act, SIGNAL(triggered()), this, SLOT(on_add_adj_output_mixer_module()));
	
	add_adj_midi_mapper_act = new QAction(tr("&MIDI Mapper"), this);
	add_adj_midi_mapper_act->setStatusTip(tr("Open AdjHeart MIDI Mapper"));
	connect(add_adj_midi_mapper_act, SIGNAL(triggered()), this, SLOT(on_add_adj_midi_mapper_module()));

	add_adj_external_midi_interface_control_act = new QAction(tr("&External MIDI Interface Control"), this);
	add_adj_external_midi_interface_control_act->setStatusTip(tr("Open AdjHeart External MIDI Interface Control"));
	connect(add_adj_external_midi_interface_control_act, SIGNAL(triggered()), this, SLOT(on_add_adj_external_midi_interface_control_module()));
	
	add_adj_keyboard_control_act = new QAction(tr("&Keyboard Control"), this);
	add_adj_keyboard_control_act->setStatusTip(tr("Open AdjHeart Keyboard Control"));
	connect(add_adj_keyboard_control_act, SIGNAL(triggered()), this, SLOT(on_add_adj_keyboard_control_module()));
	
	
	add_modules_group = new QActionGroup(this);
	add_modules_group->addAction(add_fluid_synth_act);
	
}

void MainWindow::create_menus()
{
	file_menu = menuBar()->addMenu(tr("&File"));
	
	add_module_menu = menuBar()->addMenu(tr("&Add Module"));
	add_module_menu->addAction(add_fluid_synth_act);
	add_module_menu->addAction(add_hammond_organ_act);
	add_module_menu->addAction(add_adj_analog_synth_act);
	add_module_menu->addAction(add_adj_karplus_strong_strings_synth_act);
	add_module_menu->addAction(add_adj_morphed_sin_synth_act);
	add_module_menu->addAction(add_adj_pad_synth_act);
	add_module_menu->addSeparator();
	add_module_menu->addAction(add_adj_reverb_effect_act);
	add_module_menu->addAction(add_adj_distortion_effect_act);
	add_module_menu->addAction(add_adj_graphic_equilizer_act);
	add_module_menu->addSeparator();
	add_module_menu->addAction(add_adj_output_mixer_act);
	add_module_menu->addSeparator();
	add_module_menu->addAction(add_adj_midi_mapper_act);
	add_module_menu->addAction(add_adj_external_midi_interface_control_act);
	add_module_menu->addAction(add_adj_keyboard_control_act);
	
	help_menu = menuBar()->addMenu(tr("&Help"));
	
}

ModulePannel* MainWindow::add_module_pannel(en_modules_ids_t module_id = en_modules_ids_t::none, 
								QString moduleNameString = "")
{	
	if (module_id == en_modules_ids_t::none)
	{
		return NULL;
	}
	
	ModulePannel *newPannel = new ModulePannel(this, moduleNameString, &wrapper_closeModulePannel, module_id);
	layout->addWidget(newPannel);
	
	activeModule_data_t newModule;
	newModule.module_id = module_id;
	newModule.module_name = moduleNameString;
	newModule.module_pannel_object = newPannel;
	active_modules_list.push_back(newModule);
	
	update_layout_geometry();
	 
	return newPannel;
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
		delete(module);
		
		update_layout_geometry();
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

void MainWindow::closeModulePannel(en_modules_ids_t mod_id)
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

void MainWindow::on_add_fluid_synth_module()
{
	ModulePannel *newPannel;

	if ((is_module_openned(en_modules_ids_t::fluid_synth) < 0) &&
		(active_modules_list.size() < MAX_NUM_OF_MODULES))
	{
		// Module is not already oppened

		newPannel = add_module_pannel(en_modules_ids_t::fluid_synth, _INSTRUMENT_NAME_FLUID_SYNTH_STR_KEY);
	}
}

void MainWindow::on_add_hammond_organ_module()
{
	ModulePannel *newPannel;

	if ((is_module_openned(en_modules_ids_t::adj_hammond_organ) < 0) &&
		(active_modules_list.size() < MAX_NUM_OF_MODULES))
	{
		// Module is not already oppened

		newPannel = add_module_pannel(en_modules_ids_t::adj_hammond_organ, _INSTRUMENT_NAME_HAMMON_ORGAN_STR_KEY);
	}
}

void MainWindow::on_add_adj_analog_synth_module()
{
	ModulePannel *newPannel;
	
	if ((is_module_openned(en_modules_ids_t::adj_analog_synth) < 0)&&
		(active_modules_list.size() < MAX_NUM_OF_MODULES))
	{
		// Module is not already oppened

		newPannel = add_module_pannel(en_modules_ids_t::adj_analog_synth, "Analog Synth");
	}
	
	
}

void MainWindow::on_add_adj_karplus_strong_strings_synth_module()
{
	ModulePannel *newPannel;
	
	if ((is_module_openned(en_modules_ids_t::adj_karplusstrong_string_synth) < 0)&&
		(active_modules_list.size() < MAX_NUM_OF_MODULES))
	{
		// Module is not already oppened

		newPannel = add_module_pannel(en_modules_ids_t::adj_karplusstrong_string_synth, "Karplus Strong Strings Synth");
	}
}

void MainWindow::on_add_adj_morphed_sin_synth_module()
{
	ModulePannel *newPannel;
	
	if ((is_module_openned(en_modules_ids_t::adj_morphed_sin_synth) < 0) &&
		(active_modules_list.size() < MAX_NUM_OF_MODULES))
	{
		// Module is not already oppened

		newPannel = add_module_pannel(en_modules_ids_t::adj_morphed_sin_synth, "Morphed Sinus Synth");
	}
}

void MainWindow::on_add_adj_pad_synth_module()
{
	ModulePannel *newPannel;
	
	if ((is_module_openned(en_modules_ids_t::adj_pad_synth) < 0)&&
		(active_modules_list.size() < MAX_NUM_OF_MODULES))
	{
		// Module is not already oppened

		newPannel = add_module_pannel(en_modules_ids_t::adj_pad_synth, "PADsynth Synth");
	}
}

void MainWindow::on_add_adj_reverb_effect_module()
{
	ModulePannel *newPannel;
	
	if ((is_module_openned(en_modules_ids_t::adj_reverb_effect) < 0)&&
		(active_modules_list.size() < MAX_NUM_OF_MODULES))
	{
		// Module is not already oppened

		newPannel = add_module_pannel(en_modules_ids_t::adj_reverb_effect, "Reverb");
	}
}

void MainWindow::on_add_adj_distortion_effect_module()
{
	ModulePannel *newPannel;
	
	if ((is_module_openned(en_modules_ids_t::adj_distortion_effect) < 0)&&
		(active_modules_list.size() < MAX_NUM_OF_MODULES))
	{
		// Module is not already oppened

		newPannel = add_module_pannel(en_modules_ids_t::adj_distortion_effect, "Distortion");
	}
}

void MainWindow::on_add_adj_graphic_equilizer_module()
{
	ModulePannel *newPannel;
	
	if ((is_module_openned(en_modules_ids_t::adj_graphic_equilizer) < 0)&&
		(active_modules_list.size() < MAX_NUM_OF_MODULES))
	{
		// Module is not already oppened

		newPannel = add_module_pannel(en_modules_ids_t::adj_graphic_equilizer, "Graphic Equilizer");
	}
}

void MainWindow::on_add_adj_output_mixer_module()
{
	ModulePannel *newPannel;
	
	if ((is_module_openned(en_modules_ids_t::adj_output_mixer) < 0)&&
		(active_modules_list.size() < MAX_NUM_OF_MODULES))
	{
		// Module is not already oppened

		newPannel = add_module_pannel(en_modules_ids_t::adj_output_mixer, "Output Mixer");
	}
}

void MainWindow::on_add_adj_midi_mapper_module()
{
	ModulePannel *newPannel;
	
	if ((is_module_openned(en_modules_ids_t::adj_midi_mapper) < 0)&&
		(active_modules_list.size() < MAX_NUM_OF_MODULES))
	{
		// Module is not already oppened

		newPannel = add_module_pannel(en_modules_ids_t::adj_midi_mapper, "MIDI Mapper");
	}
}

void MainWindow::on_add_adj_external_midi_interface_control_module()
{
	ModulePannel *newPannel;
	
	if ((is_module_openned(en_modules_ids_t::adj_ext_midi_interface) < 0) &&
		(active_modules_list.size() < MAX_NUM_OF_MODULES))
	{
		// Module is not already oppened

		newPannel = add_module_pannel(en_modules_ids_t::adj_ext_midi_interface, "Ext. MIDI Int. Control");

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

		newPannel = add_module_pannel(en_modules_ids_t::adj_keyboard_control, "Keyboard Control");
	}
}
	
