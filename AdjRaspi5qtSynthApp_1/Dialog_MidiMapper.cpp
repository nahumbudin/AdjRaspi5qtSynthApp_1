/**
* @file		Dialog_MidiMapper.cpp
*	@author		Nahum Budin
*	@date		19-Oct-2024
*	@version	1.0
*
*	@brief		Used for mapping MIDI channels events to instruments
*				
*	History:
*
*/

#include <QObject>
#include <QTimer>
#include <QMoveEvent>

#include "MainWindow.h"
#include "Dialog_MidiMapper.h"
#include "ui_Dialog_MidiMapper.h"
#include "Defs.h"

UpdateGuiThread *update_gui_thread;

vector<active_module_data_t> active_synth_modules, prev_active_synth_modules;
vector<active_module_data_t> added_synth_modules, removed_synth_modules;
vector<active_module_data_t> active_modules_data;

int channels_combo_box_selection_index[16] = { 0 };
active_module_data_t channels_combo_box_selected_module_data[16];

bool found;

void midi_mapper_control_box_event_update_ui_callback_wrapper(int evnt, uint16_t val)
{
	Dialog_MidiMapper::get_instance()->control_box_ui_update_callback(evnt, val);
}

void update_gui_wrapper()
{
	Dialog_MidiMapper::get_instance()->update_gui();
}

void UpdateGuiThread::run() 
{		
	update_gui_wrapper();
}

Dialog_MidiMapper *Dialog_MidiMapper::dialog_adj_midi_mapper_instance = NULL;

Dialog_MidiMapper::Dialog_MidiMapper(QWidget *parent)
	: QDialog(parent)
	, ui(new Ui::Dialog_MidiMapper)
{
	ui->setupUi(this);
	dialog_adj_midi_mapper_instance = this;
	active_synth_modules.clear();
	prev_active_synth_modules.clear();
	
	move(100, 100);
	
	this->setFocus(Qt::ActiveWindowFocusReason);
	
	close_event_callback_ptr = NULL;
	
	mod_synth_register_callback_control_box_event_update_ui(
		&midi_mapper_control_box_event_update_ui_callback_wrapper);
	
	MainWindow::get_instance()->register_active_dialog(this);
	
	channels_combos[0] = ui->comboBox_MidiMapperCh_1;
	channels_combos[1] = ui->comboBox_MidiMapperCh_2;
	channels_combos[2] = ui->comboBox_MidiMapperCh_3;
	channels_combos[3] = ui->comboBox_MidiMapperCh_4;
	channels_combos[4] = ui->comboBox_MidiMapperCh_5;
	channels_combos[5] = ui->comboBox_MidiMapperCh_6;
	channels_combos[6] = ui->comboBox_MidiMapperCh_7;
	channels_combos[7] = ui->comboBox_MidiMapperCh_8;
	channels_combos[8] = ui->comboBox_MidiMapperCh_9;
	channels_combos[9] = ui->comboBox_MidiMapperCh_10;
	channels_combos[10] = ui->comboBox_MidiMapperCh_11;
	channels_combos[11] = ui->comboBox_MidiMapperCh_12;
	channels_combos[12] = ui->comboBox_MidiMapperCh_13;
	channels_combos[13] = ui->comboBox_MidiMapperCh_14;
	channels_combos[14] = ui->comboBox_MidiMapperCh_15;
	channels_combos[15] = ui->comboBox_MidiMapperCh_16;
	
	update_channels_combo_boxes();
	
	connect(ui->comboBox_MidiMapperCh_1,
		SIGNAL(currentIndexChanged(int)),
		this,
		SLOT(ch_1_instrument_changed(int)));
	
	connect(ui->comboBox_MidiMapperCh_2,
		SIGNAL(currentIndexChanged(int)),
		this,
		SLOT(ch_2_instrument_changed(int)));
	
	connect(ui->comboBox_MidiMapperCh_3,
		SIGNAL(currentIndexChanged(int)),
		this,
		SLOT(ch_3_instrument_changed(int)));
	
	connect(ui->comboBox_MidiMapperCh_4,
		SIGNAL(currentIndexChanged(int)),
		this,
		SLOT(ch_4_instrument_changed(int)));
	
	connect(ui->comboBox_MidiMapperCh_5,
		SIGNAL(currentIndexChanged(int)),
		this,
		SLOT(ch_5_instrument_changed(int)));
	
	connect(ui->comboBox_MidiMapperCh_6,
		SIGNAL(currentIndexChanged(int)),
		this,
		SLOT(ch_6_instrument_changed(int)));
	
	connect(ui->comboBox_MidiMapperCh_7,
		SIGNAL(currentIndexChanged(int)),
		this,
		SLOT(ch_7_instrument_changed(int)));
	
	connect(ui->comboBox_MidiMapperCh_8,
		SIGNAL(currentIndexChanged(int)),
		this,
		SLOT(ch_8_instrument_changed(int)));
	
	connect(ui->comboBox_MidiMapperCh_9,
		SIGNAL(currentIndexChanged(int)),
		this,
		SLOT(ch_9_instrument_changed(int)));
	
	connect(ui->comboBox_MidiMapperCh_10,
		SIGNAL(currentIndexChanged(int)),
		this,
		SLOT(ch_10_instrument_changed(int)));
	
	connect(ui->comboBox_MidiMapperCh_11,
		SIGNAL(currentIndexChanged(int)),
		this,
		SLOT(ch_11_instrument_changed(int)));
	
	connect(ui->comboBox_MidiMapperCh_12,
		SIGNAL(currentIndexChanged(int)),
		this,
		SLOT(ch_12_instrument_changed(int)));
	
	connect(ui->comboBox_MidiMapperCh_13,
		SIGNAL(currentIndexChanged(int)),
		this,
		SLOT(ch_13_instrument_changed(int)));
	
	connect(ui->comboBox_MidiMapperCh_14,
		SIGNAL(currentIndexChanged(int)),
		this,
		SLOT(ch_14_instrument_changed(int)));
	
	connect(ui->comboBox_MidiMapperCh_15,
		SIGNAL(currentIndexChanged(int)),
		this,
		SLOT(ch_15_instrument_changed(int)));
	
	connect(ui->comboBox_MidiMapperCh_16,
		SIGNAL(currentIndexChanged(int)),
		this,
		SLOT(ch_16_instrument_changed(int)));
	
	active_modules_mutex = new QMutex();
	
	
	// start a periodic timer after this timeout - 
	start_update_timer(200);
	
}

Dialog_MidiMapper::~Dialog_MidiMapper()
{
	
}

Dialog_MidiMapper *Dialog_MidiMapper::get_instance(QWidget *parent, bool showit)
{
	if (dialog_adj_midi_mapper_instance == NULL)
	{
		dialog_adj_midi_mapper_instance = new Dialog_MidiMapper(parent);
	}
	
	if (showit)
	{
		dialog_adj_midi_mapper_instance->show();
	}
	
	return dialog_adj_midi_mapper_instance;
}

void Dialog_MidiMapper::closeEvent(QCloseEvent *event)
{
	if (close_event_callback_ptr != NULL)
	{
		close_event_callback_ptr();
	}
	
	hide();
}

void Dialog_MidiMapper::moveEvent(QMoveEvent *event) {
	QWidget::moveEvent(event); // Call the base class implementation first

	last_position = event->pos();
	//printf("Mapper position %i:%i\n", last_position.x(), last_position.y());
}

bool Dialog_MidiMapper::event(QEvent *event)
{
	//printf("Event type: %i pos: %i:%i\n", event->type(), this->x(), this->y());

	return QWidget::event(event);
	

}

int Dialog_MidiMapper::set_channel_instrument(int ch, int inst)
{
	en_modules_ids_t module_id;
	
	if (inst == 0)
	{
		module_id = en_modules_ids_t::none_module_id;
	}
	else
	{
		module_id = channels_combo_box_selected_module_data[ch].module_id; // 1st is null "-----"
	}
	
	mod_synth_allocate_midi_channel_synth(ch, module_id);
	
	return 0;
}

void Dialog_MidiMapper::ch_1_instrument_changed(int inst)
{
	channels_combo_box_selection_index[0] = inst;
	if (inst == 0)
	{
		channels_combo_box_selected_module_data[0] = en_modules_ids_t::none_module_id;
	}
	else
	{
		channels_combo_box_selected_module_data[0] = active_modules_data[inst - 1]; // 1st is null "-----"
	}
	
	set_channel_instrument(0, inst);
}

void Dialog_MidiMapper::ch_2_instrument_changed(int inst)
{
	channels_combo_box_selection_index[1] = inst;
	if (inst == 0)
	{
		channels_combo_box_selected_module_data[1] = en_modules_ids_t::none_module_id;
	}
	else
	{
		channels_combo_box_selected_module_data[1] = active_modules_data[inst - 1]; // 1st is null "-----"
	}
	
	set_channel_instrument(1, inst);
}

void Dialog_MidiMapper::ch_3_instrument_changed(int inst)
{
	channels_combo_box_selection_index[2] = inst;
	if (inst == 0)
	{
		channels_combo_box_selected_module_data[2] = en_modules_ids_t::none_module_id;
	}
	else
	{
		channels_combo_box_selected_module_data[2] = active_modules_data[inst - 1]; // 1st is null "-----"
	}
	
	set_channel_instrument(2, inst);
}

void Dialog_MidiMapper::ch_4_instrument_changed(int inst)
{
	channels_combo_box_selection_index[3] = inst;
	if (inst == 0)
	{
		channels_combo_box_selected_module_data[3] = en_modules_ids_t::none_module_id;
	}
	else
	{
		channels_combo_box_selected_module_data[3] = active_modules_data[inst - 1]; // 1st is null "-----"
	}
	
	set_channel_instrument(3, inst);
}

void Dialog_MidiMapper::ch_5_instrument_changed(int inst)
{
	channels_combo_box_selection_index[4] = inst;
	if (inst == 0)
	{
		channels_combo_box_selected_module_data[4] = en_modules_ids_t::none_module_id;
	}
	else
	{
		channels_combo_box_selected_module_data[4] = active_modules_data[inst - 1]; // 1st is null "-----"
	}
	
	set_channel_instrument(4, inst);
}

void Dialog_MidiMapper::ch_6_instrument_changed(int inst)
{
	channels_combo_box_selection_index[5] = inst;
	if (inst == 0)
	{
		channels_combo_box_selected_module_data[5] = en_modules_ids_t::none_module_id;
	}
	else
	{
		channels_combo_box_selected_module_data[5] = active_modules_data[inst - 1]; // 1st is null "-----"
	}
	set_channel_instrument(5, inst);
}

void Dialog_MidiMapper::ch_7_instrument_changed(int inst)
{
	channels_combo_box_selection_index[6] = inst;
	if (inst == 0)
	{
		channels_combo_box_selected_module_data[6] = en_modules_ids_t::none_module_id;
	}
	else
	{
		channels_combo_box_selected_module_data[6] = active_modules_data[inst - 1]; // 1st is null "-----"
	}
	
	set_channel_instrument(6, inst);
}

void Dialog_MidiMapper::ch_8_instrument_changed(int inst)
{
	channels_combo_box_selection_index[7] = inst;
	if (inst == 0)
	{
		channels_combo_box_selected_module_data[7] = en_modules_ids_t::none_module_id;
	}
	else
	{
		channels_combo_box_selected_module_data[7] = active_modules_data[inst - 1]; // 1st is null "-----"
	}
	
	set_channel_instrument(7, inst);
}

void Dialog_MidiMapper::ch_9_instrument_changed(int inst)
{
	channels_combo_box_selection_index[8] = inst;
	if (inst == 0)
	{
		channels_combo_box_selected_module_data[8] = en_modules_ids_t::none_module_id;
	}
	else
	{
		channels_combo_box_selected_module_data[8] = active_modules_data[inst - 1]; // 1st is null "-----"
	}
	
	set_channel_instrument(8, inst);
}

void Dialog_MidiMapper::ch_10_instrument_changed(int inst)
{
	channels_combo_box_selection_index[9] = inst;
	if (inst == 0)
	{
		channels_combo_box_selected_module_data[9] = en_modules_ids_t::none_module_id;
	}
	else
	{
		channels_combo_box_selected_module_data[9] = active_modules_data[inst - 1]; // 1st is null "-----"
	}
	
	set_channel_instrument(9, inst);
}

void Dialog_MidiMapper::ch_11_instrument_changed(int inst)
{
	channels_combo_box_selection_index[10] = inst;
	if (inst == 0)
	{
		channels_combo_box_selected_module_data[10] = en_modules_ids_t::none_module_id;
	}
	else
	{
		channels_combo_box_selected_module_data[10] = active_modules_data[inst - 1]; // 1st is null "-----"
	}
	
	set_channel_instrument(10, inst);
}

void Dialog_MidiMapper::ch_12_instrument_changed(int inst)
{
	channels_combo_box_selection_index[11] = inst;
	if (inst == 0)
	{
		channels_combo_box_selected_module_data[11] = en_modules_ids_t::none_module_id;
	}
	else
	{
		channels_combo_box_selected_module_data[11] = active_modules_data[inst - 1]; // 1st is null "-----"
	}
	
	set_channel_instrument(11, inst);
}

void Dialog_MidiMapper::ch_13_instrument_changed(int inst)
{
	channels_combo_box_selection_index[12] = inst;
	if (inst == 0)
	{
		channels_combo_box_selected_module_data[12] = en_modules_ids_t::none_module_id;
	}
	else
	{
		channels_combo_box_selected_module_data[12] = active_modules_data[inst - 1]; // 1st is null "-----"
	}
	
	set_channel_instrument(12, inst);
}

void Dialog_MidiMapper::ch_14_instrument_changed(int inst)
{
	channels_combo_box_selection_index[13] = inst;
	if (inst == 0)
	{
		channels_combo_box_selected_module_data[13] = en_modules_ids_t::none_module_id;
	}
	else
	{
		channels_combo_box_selected_module_data[13] = active_modules_data[inst - 1]; // 1st is null "-----"
	}
	
	set_channel_instrument(13, inst);
}

void Dialog_MidiMapper::ch_15_instrument_changed(int inst)
{
	channels_combo_box_selection_index[14] = inst;
	if (inst == 0)
	{
		channels_combo_box_selected_module_data[14] = en_modules_ids_t::none_module_id;
	}
	else
	{
		channels_combo_box_selected_module_data[14] = active_modules_data[inst - 1]; // 1st is null "-----"
	}
	
	set_channel_instrument(14, inst);
}

void Dialog_MidiMapper::ch_16_instrument_changed(int inst)
{
	channels_combo_box_selection_index[15] = inst;
	if (inst == 0)
	{
		channels_combo_box_selected_module_data[15] = en_modules_ids_t::none_module_id;
	}
	else
	{
		channels_combo_box_selected_module_data[15] = active_modules_data[inst - 1]; // 1st is null "-----"
	}
	
	set_channel_instrument(15, inst);
}

void Dialog_MidiMapper::control_box_ui_update_callback(int evnt, uint16_t val)
{
	if (!this->hasFocus())
	{
		return;
	}
	
	if (evnt == _CONTROL_PUSHBUTTON_BLUE_GREEN)
	{
		
	}
	
}

QPoint Dialog_MidiMapper::get_last_position()
{
	return last_position;
}

void Dialog_MidiMapper::on_dialog_close()
{
	//mod_synth_unregister_callback_control_box_event_update_ui(
	//	&fluid_control_box_event_update_ui_callback_wrapper);
	
	hide();
}

void Dialog_MidiMapper::start_update_timer(int interval)
{
	QTimer *timer = new QTimer(this);
	connect(timer, SIGNAL(timeout()), this, SLOT(timerEvent()));
	timer->start(interval);
}

void Dialog_MidiMapper::update_channels_combo_boxes()
{
	bool last_selected = false;
	
	for (int ch = 0; ch < 16; ch++)
	{
		channels_combos[ch]->blockSignals(true);
		channels_combos[ch]->clear();
		channels_combos[ch]->addItem(QString("--------------"));
		//if (ch == 0) { fprintf(stderr, "List cleared. Lenth %i\n", active_modules_data.size()); }
		
		int i = 1;
		for (active_module_data_t module : active_modules_data)
		{
			channels_combos[ch]->addItem(QString(module.module_name));
			//if (ch == 0) { fprintf(stderr, "Add to list: %s ", module.module_name.toStdString().data()); }
			/* Locate the last selected item */
			if (module.module_id == channels_combo_box_selected_module_data[ch].module_id)
			{
				channels_combo_box_selection_index[ch] = i;
				last_selected = true;
			}
			i++;
		}
		
		//if (ch == 0) { fprintf(stderr, "\n"); }
		
		if (last_selected)
		{
			channels_combos[ch]->setCurrentIndex(channels_combo_box_selection_index[ch]);
			last_selected = false;
		}
		else
		{
			/* Last selected is no longer active. */
			channels_combo_box_selected_module_data[ch].module_id = en_modules_ids_t::none_module_id;
			channels_combo_box_selection_index[ch] = 0;
			channels_combos[ch]->setCurrentIndex(0);
			//fprintf(stderr, "Last selected is no longer active. ch%i\n", ch);
			mod_synth_allocate_midi_channel_synth(ch, en_modules_ids_t::none_module_id);
		}
		
		channels_combos[ch]->blockSignals(false);
	}
}

void Dialog_MidiMapper::timerEvent()
{
	update_gui_thread = new UpdateGuiThread();
	update_gui_thread->start();
}

void Dialog_MidiMapper::update_gui()
{
	en_modules_ids_t inst_id;
	static bool first_time = true;
	
	active_synth_modules.clear();
	added_synth_modules.clear();
	removed_synth_modules.clear();
	
	/* Get all currently active modules */
	for (active_module_data_t module : MainWindow::get_instance()->active_modules_list)
	{
		if (mod_synth_get_instrument_type(module.module_id) == en_modules_types_t::synth)
		{
			active_synth_modules.push_back(module);
		}
	}
	
	if (active_synth_modules.size() == 0)
	{
		/* No active modules. */
		if (prev_active_synth_modules.size() != 0)
		{
			/* All active modules were just removed */			
			for (active_module_data_t prev_active_module : prev_active_synth_modules)
			{
				removed_synth_modules.push_back(prev_active_module);
			}
		}
	}
	else
	{
		/* There are active modules. */
		if (prev_active_synth_modules.size() == 0)
		{
			/* All active modules were just added. */
			for (active_module_data_t active_module : active_synth_modules)
			{
				added_synth_modules.push_back(active_module);
			}
		}
		else
		{
			/* Some active modules might be added and some might be removed. */
			/* Look for added modules */
			for (active_module_data_t active_module : active_synth_modules)
			{
				found = false;
				/* Check if active module was already in prev list */
				for (active_module_data_t prev_active_module : prev_active_synth_modules)
				{
					if (active_module.module_id == prev_active_module.module_id)
					{
						found = true; 
					}
				}
				
				if (!found)
				{
					/* Was not found in prev list */
					added_synth_modules.push_back(active_module);
				}
			}
			/* Look for removed modules */
			for (active_module_data_t prev_active_module : prev_active_synth_modules)
			{
				found = false;
				/* Check if prev module is still an active module */
				for (active_module_data_t active_module : active_synth_modules)
				{
					if (active_module.module_id == prev_active_module.module_id)
					{
						found = true;
					}
				}
				
				if (!found)
				{
					/* No longer active */
					removed_synth_modules.push_back(prev_active_module);
				}
			}			
		}
	}
	
	/* Update prev with current */
	prev_active_synth_modules.clear();
	for (active_module_data_t module : active_synth_modules)
	{
		prev_active_synth_modules.push_back(module);
	}
	
	//active_modules_mutex->lock();
	
	if (added_synth_modules.size() > 0)
	{
		/* New modules added */
		for (active_module_data_t module : added_synth_modules)
		{
			//fprintf(stderr, "Add module %s\n", module.module_name.toStdString().data());
			active_modules_data.push_back(module);
		}
		
		update_channels_combo_boxes();
	}
	
	if (removed_synth_modules.size() > 0)
	{
		/* Prev module removed */
		for (active_module_data_t module : removed_synth_modules)
		{
			int i = 0;
			for (active_module_data_t mod : active_modules_data)
			{
				if (module.module_id == mod.module_id)
				{
					//fprintf(stderr, "Remove module %i %s\n", i, module.module_name.toStdString().data());
					active_modules_data.erase(active_modules_data.begin() + i);
					break;
				}
				
				i++;
			}
			
			/* Disconnect MIDI channel */
		}

		update_channels_combo_boxes();
	}
	
	//active_modules_mutex->unlock();
}


