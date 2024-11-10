/**
* @file		Dialog_FluidSynthChannels.cpp
*	@author		Nahum Budin
*	@date		21-Jul-2024
*	@version	1.0
*
*	@brief		Adj FluidSynth channels dialog
*	
*	History
*	
*		Based on AdjModSynth_2 project MainWindow.h V1.1 16-Jan-2021
*
*/

#include <QMessageBox>
#include <QFileDialog>

#include "MainWindow.h"

#include "Dialog_FluidSynthChannels.h"
#include "ui_Dialog_FluidSynthChannels.h"

#include "Dialog_AdjFluidSynth.h"

#include "NQgridWidget.h"

QColor control_colors[6] = { 
	_CONTROL_COLOR_BLACK, 
	_CONTROL_COLOR_GREEN,
	_CONTROL_COLOR_RED,
	_CONTROL_COLOR_BLUE,
	_CONTROL_COLOR_WHITE,
	_CONTROL_COLOR_YELLOW
};

Dialog_FluidSynthChannels *Dialog_FluidSynthChannels::dialog_fluid_synth_channels_instance = NULL;

/* Holds the loaded soundfonts id numbers */
std::vector<int> Dialog_FluidSynthChannels::loaded_soundfont_ids;
/* Holds the active soundfont banks numbers */
std::vector<int> Dialog_FluidSynthChannels::active_soundfont_bank_nums;
/* Holds al the active soundfonts presets data */
std::vector<_soundfont_presets_data_t> Dialog_FluidSynthChannels::active_soundfont_presets;
/* Holds the soundfont names and associated id numbers */
std::vector<_sondfont_disp_data_t> sound_fonts_names_dispaly_data;

void fluid_channels_control_box_event_update_ui_callback_wrapper(int evnt, uint16_t val)
{
	Dialog_FluidSynthChannels::get_instance()->control_box_ui_update_callback(evnt, val);
}

/**
*   @brief  A wrapper used far callback activation of the on_row_double_click function.
*   @param  row a pointer to an integer varaiable holding the selected row number
*   @param  col a pointer to an integer varaiable holding the selected column number
*   @return 0 if OK -1 otherwise
*/
void on_row_double_click_wraper_1_8(int *row, int *col)
{
	Dialog_FluidSynthChannels::get_instance()->on_row_double_click_ch_1_8(row, col);
}

void on_row_double_click_wraper_9_16(int *row, int *col)
{
	Dialog_FluidSynthChannels::get_instance()->on_row_double_click_ch_9_16(row, col);
}

void refresh_channels_table_widget_wraper(int channels_group)
{
	Dialog_FluidSynthChannels::get_instance()->refresh_channels_table_widget(channels_group);
}

void init_channels_table_widget_wraper(int channels_group)
{
	Dialog_FluidSynthChannels::get_instance()->init_channels_table_widget(channels_group);
}


Dialog_FluidSynthChannels::Dialog_FluidSynthChannels(QWidget *parent)
	: QDialog(parent)
	, ui(new Ui::Dialog_FluidSynthChannels)
{
	ui->setupUi(this);
	dialog_fluid_synth_channels_instance = this;
	
	init_channels_table_widget(_MIDI_MIXER_CHANNELS_1_8);
	init_channels_table_widget(_MIDI_MIXER_CHANNELS_9_16);
	
	refresh_channels_table_widget(_MIDI_MIXER_CHANNELS_1_8);
	refresh_channels_table_widget(_MIDI_MIXER_CHANNELS_9_16);
	
	dialog_fluid_synth_select_program = new Dialog_FluidSynthSelectProgram(this);
	dialog_fluid_synth_select_program->move(10, 150);
	
	//mod_synth_register_callback_control_box_event_update_ui(
	//	&fluid_channels_control_box_event_update_ui_callback_wrapper);
	
	active_channels_tab = _MIDI_MIXER_CHANNELS_1_8;
	
	this->setFocus(Qt::ActiveWindowFocusReason);
	
	connect(ui->buttonBox_Dialog_Channels, 
		SIGNAL(accepted()), 
		this, 
		SLOT(program_selection_done()));

	connect(ui->buttonBox_Dialog_Channels, 
		SIGNAL(rejected()), 
		this, 
		SLOT(program_selection_cancell()));
	
	connect(ui->pushButton_Fluid_Channels_SoundFonts, 
		SIGNAL(clicked()), 
		this, 
		SLOT(open_soundfont_file()));
	
	//MainWindow::get_instance()->register_active_dialog(this);
}

/**
*   @brief  Init the channels table.
*   @param  none
*   @return 0
*/
Dialog_FluidSynthChannels::~Dialog_FluidSynthChannels()
{
	
}

Dialog_FluidSynthChannels *Dialog_FluidSynthChannels::get_instance(QWidget *parent, bool refresh)
{
	if (dialog_fluid_synth_channels_instance == NULL)
	{
		dialog_fluid_synth_channels_instance = new Dialog_FluidSynthChannels(parent);
	}
	
	if (refresh)
	{
		//init_channels_table_widget_wraper(_CHANNELS_SHEET_1_8);
		//init_channels_table_widget_wraper(_CHANNELS_SHEET_9_16);
		
		refresh_channels_table_widget_wraper(_MIDI_MIXER_CHANNELS_1_8);
		refresh_channels_table_widget_wraper(_MIDI_MIXER_CHANNELS_9_16);
	}
	
	return dialog_fluid_synth_channels_instance;
}

void Dialog_FluidSynthChannels::closeEvent(QCloseEvent *event)
{
	// Close the dialog
	Dialog_AdjFluidSynth::get_instance()->setFocus(Qt::ActiveWindowFocusReason);
	this->hide();
}

void Dialog_FluidSynthChannels::control_box_ui_update_callback(int evnt, uint16_t val)
{
	int selected_raw;
	int selected_col = 0;
	
	if (!this->hasFocus())
	{
		return;
	}
	
	if ((evnt == _CONTROL_FUNCTION_PUSHBUTTON_UP) &&
			 (val == 0))
	{
		/* Toggle selected channels group */
		if (active_channels_tab == _MIDI_MIXER_CHANNELS_1_8)
		{
			active_channels_tab = _MIDI_MIXER_CHANNELS_9_16;
			ui->tabWidget_channels_table->setCurrentIndex(active_channels_tab);
		}
		else
		{
			active_channels_tab = _MIDI_MIXER_CHANNELS_1_8;
			ui->tabWidget_channels_table->setCurrentIndex(active_channels_tab);
		}
	}
	else if (evnt == _CONTROL_PUSHBUTTON_BLUE_BLACK)
	{
		/* En/Dis Reverb */
		if (val == 0)
		{
			selected_raw = 0;
			/* Only when pressed */
			if (active_channels_tab == _MIDI_MIXER_CHANNELS_1_8)
			{
				fluid_channels_sheet_1_8->onDoubleCliked(0, 0);
			}
			else
			{
				fluid_channels_sheet_9_16->onDoubleCliked(0, 0);
			}			
		}
	}
}

/**
*   @brief  Returns a pointer to the vector of _soundfont_presets_data_t elements holding presets data.
*   @param  none
*   @return a pointer to the vector of _soundfont_presets_data_t elements holding presets data.
*/
std::vector<_soundfont_presets_data_t> *Dialog_FluidSynthChannels::get_active_soundfont_presets()
{
	return &active_soundfont_presets;
}

/**
*   @brief  Init the channels table.
*   @param  int channels: _CHANNELS_SHEET_1_8 or _CHANNELS_SHEET_9_16
*   @return 0
*/
int Dialog_FluidSynthChannels::init_channels_table_widget(int chan_group)
{
	int width;
	NQgridWidget *fluid_channels_sheet;
	
	channels_table_horizontal_headers.push_back("Channel");
	//channels_table_horizontal_headers.push_back("Synth");
	channels_table_horizontal_headers.push_back("Bank");
	channels_table_horizontal_headers.push_back("Prog");
	channels_table_horizontal_headers.push_back("Name");
	channels_table_horizontal_headers.push_back("SFID");
	channels_table_horizontal_headers.push_back("SoundFont");
	
	for (int i = 0; i < 8; i++)
	{
		if (chan_group == _MIDI_MIXER_CHANNELS_1_8)
		{
			channels_table_vertical_headers_1_8.push_back("");
		}
		else if (chan_group == _MIDI_MIXER_CHANNELS_9_16)
		{
			channels_table_vertical_headers_9_16.push_back("");
		}
		
		channels_table_rows_heights.push_back(14);
	}
	
	channels_table_columns_width.push_back(70);
	//channels_table_columns_width.push_back(95); // used for combo box to select module - future option
	channels_table_columns_width.push_back(40);
	channels_table_columns_width.push_back(50);
	channels_table_columns_width.push_back(250);
	channels_table_columns_width.push_back(50);
	channels_table_columns_width.push_back(200);
	
	if (chan_group == _MIDI_MIXER_CHANNELS_1_8)
	{
		fluid_channels_sheet_1_8 = new NQgridWidget(8, 6);
		fluid_channels_sheet = fluid_channels_sheet_1_8;
	}
	else if (chan_group == _MIDI_MIXER_CHANNELS_9_16)
	{
		fluid_channels_sheet_9_16 = new NQgridWidget(8, 6);
		fluid_channels_sheet = fluid_channels_sheet_9_16;
	}
	
	fluid_channels_sheet->getTableWidget()->setFont(QFont("Helvetica", 12));
	fluid_channels_sheet->getTableWidget()->setSelectionBehavior(QAbstractItemView::SelectionBehavior::SelectRows);
	fluid_channels_sheet->getTableWidget()->setSizeAdjustPolicy(QTableWidget::AdjustToContents);
	fluid_channels_sheet->getTableWidget()->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	fluid_channels_sheet->getTableWidget()->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
	
	fluid_channels_sheet->setHorizontalHeaders(&channels_table_horizontal_headers);
	
	if (chan_group == _MIDI_MIXER_CHANNELS_1_8)
	{
		fluid_channels_sheet->setVerticalHeaders(&channels_table_vertical_headers_1_8);
	}
	else if (chan_group == _MIDI_MIXER_CHANNELS_9_16)
	{
		fluid_channels_sheet->setVerticalHeaders(&channels_table_vertical_headers_9_16);
	}	
	
	fluid_channels_sheet->setRowColsSize(&channels_table_rows_heights, &channels_table_columns_width);
	
	fluid_channels_sheet->getTableWidget()->setEditTriggers(QAbstractItemView::NoEditTriggers);
	
	// Set all cells not editable
	//QTableWidgetItem *item;
	//for (int r = 0; r <= fluid_channels_sheet->getTableWidget()->rowCount(); r++)
	//{
		/* This section added the combo box to select synth type per channel - currently this is not implemented !*/
		/*
		selectSynthCombo[r] = new QComboBox();
		width = channelsTabaleColumnsWidth.at(1);
		selectSynthCombo[r]->view()->setMinimumWidth(width - 2);
		selectSynthCombo[r]->addItem("None");
		selectSynthCombo[r]->addItem("FluidSynth");
		selectSynthCombo[r]->addItem("AdjSynth");
		fluid_channels_sheet->getTableWidget()->setCellWidget(r, 1, selectSynthCombo[r]);
		
		switch (r)
		{
			case (0):
				QObject::connect(selectSynthCombo[r], SIGNAL(currentIndexChanged(int)), this, SLOT(Channel1SynthSelected(int)));
				break;
				
			case (1):
				QObject::connect(selectSynthCombo[r], SIGNAL(currentIndexChanged(int)), this, SLOT(Channel2SynthSelected(int)));
				break;
				
			case (2):
				QObject::connect(selectSynthCombo[r], SIGNAL(currentIndexChanged(int)), this, SLOT(Channel3SynthSelected(int)));
				break;
				
			case (3):
				QObject::connect(selectSynthCombo[r], SIGNAL(currentIndexChanged(int)), this, SLOT(Channel4SynthSelected(int)));
				break;
				
			case (4):
				QObject::connect(selectSynthCombo[r], SIGNAL(currentIndexChanged(int)), this, SLOT(Channel5SynthSelected(int)));
				break;
				
			case (5):
				QObject::connect(selectSynthCombo[r], SIGNAL(currentIndexChanged(int)), this, SLOT(Channel6SynthSelected(int)));
				break;
				
			case (6):
				QObject::connect(selectSynthCombo[r], SIGNAL(currentIndexChanged(int)), this, SLOT(Channel7SynthSelected(int)));
				break;
				
			case (7):
				QObject::connect(selectSynthCombo[r], SIGNAL(currentIndexChanged(int)), this, SLOT(Channel8SynthSelected(int)));
				break;
			}
		*/
	//}
		
	if (chan_group == _MIDI_MIXER_CHANNELS_1_8)
	{
		fluid_channels_sheet->registerOnDoubleClickEvent(&on_row_double_click_wraper_1_8);	
		ui->scrollArea_channels_1_8->setWidget(fluid_channels_sheet);
		// Set Channels current presets  data
		refresh_channels_table_widget(_MIDI_MIXER_CHANNELS_1_8);
	}
	else if (chan_group == _MIDI_MIXER_CHANNELS_9_16)
	{
		fluid_channels_sheet->registerOnDoubleClickEvent(&on_row_double_click_wraper_9_16);	
		ui->scrollArea_channels_9_16->setWidget(fluid_channels_sheet);
		// Set Channels current presets  data
		refresh_channels_table_widget(_MIDI_MIXER_CHANNELS_9_16);
	}

	fluid_channels_sheet->show();

	return 0;
}

/**
*   @brief  refresh the channels table.
*   @param  int channels: _CHANNELS_SHEET_1_8 or _CHANNELS_SHEET_9_16
*   @return 0
*/
int Dialog_FluidSynthChannels::refresh_channels_table_widget(int chan_group)
{
	int row_count, start_chan;
	NQgridWidget *fluid_channels_sheet;
	
	int bank, program, sfont_id; 
	std::string	preset_name, sf_name;
	
	if (chan_group == _MIDI_MIXER_CHANNELS_1_8)
	{
		fluid_channels_sheet = fluid_channels_sheet_1_8;
		start_chan = 0;
	}
	else if (chan_group == _MIDI_MIXER_CHANNELS_9_16)
	{
		fluid_channels_sheet = fluid_channels_sheet_9_16;
		start_chan = 8;
	}	

	row_count = fluid_channels_sheet->getTableWidget()->rowCount();

	// Set Channels current presets  data
	for (int i = 0; i < row_count; i++)
	{
		fluid_channels_sheet->setTabItemIntegerValue(i, 0, i + 1 + start_chan); //, 
													 //control_colors[i % 4]); // Use only 4 1st colors
					
		bank = mod_synth_get_fluid_synth_channel_bank(i + start_chan);
		program = mod_synth_get_fluid_synth_channel_program(i + start_chan);
		preset_name = mod_synth_get_fluid_synth_channel_preset_name(i + start_chan);
		sfont_id = mod_synth_get_fluid_synth_channel_sfont_id(i + start_chan);
		sf_name = mod_synth_get_fluid_synth_channel_preset_soundfont_name(i + start_chan);
		
		fluid_channels_sheet->setTabItemIntegerValue(i, 1, bank);
		fluid_channels_sheet->setTabItemIntegerValue(i, 2, program + 1);
		fluid_channels_sheet->setTabItemStringValue(i, 3, QString::fromStdString(preset_name));
		fluid_channels_sheet->setTabItemIntegerValue(i, 4, sfont_id);
		fluid_channels_sheet->setTabItemStringValue(i, 5, QString::fromStdString(sf_name));		
	}	

	fluid_channels_sheet->show();

	return 0;
}

/**
*   @brief  called when a channel was selected.
*   @param  channel selected channel
*   @return 0
*/
int Dialog_FluidSynthChannels::channel_selected(int channel, int col, int chan_group)
{
	int num_of_loaded_soundFonts, res, count, i, j;
	bool bank_exist = false;
	bool sfid_exist = false;
	_sondfont_disp_data_t soundfonts_name_dat;

	selected_channel = channel;

	if (col == 1)
	{
		// Set assigned synthesizer TODO remove this column	or future option
		
	}
		
	// FluidSynth - select program
	loaded_soundfont_ids.clear();
	active_soundfont_bank_nums.clear();
	active_soundfont_presets.clear();
	sound_fonts_names_dispaly_data.clear();
	// Get the presets of all fluid soundfont files
	res = mod_synth_get_fluid_synth_loaded_soundfonts_presets(&Dialog_FluidSynthChannels::active_soundfont_presets);

	// Look for soundfonts ids
	loaded_soundfont_ids.push_back(active_soundfont_presets.at(0).sound_font_id);
	soundfonts_name_dat.sfid = active_soundfont_presets.at(0).sound_font_id;
	soundfonts_name_dat.name = mod_synth_get_fluid_synth_soundfont_id_name(soundfonts_name_dat.sfid);
	sound_fonts_names_dispaly_data.push_back(soundfonts_name_dat);
	for (i = 1; i < active_soundfont_presets.size(); i++)
	{
		// Go over all loaded sounfonts - load only once
		sfid_exist = false;
		for (j = 0; j < loaded_soundfont_ids.size() && !sfid_exist; j++)
		{
			//					sfid_exist = false;
			if (active_soundfont_presets.at(i).sound_font_id == loaded_soundfont_ids.at(j))
			{
				// Already loaded
				sfid_exist = true;
			}
		}

		if (!sfid_exist)
		{
			loaded_soundfont_ids.push_back(active_soundfont_presets.at(i).sound_font_id);
			soundfonts_name_dat.sfid = active_soundfont_presets.at(i).sound_font_id;
			soundfonts_name_dat.name = mod_synth_get_fluid_synth_soundfont_id_name(soundfonts_name_dat.sfid);
			sound_fonts_names_dispaly_data.push_back(soundfonts_name_dat);
		}
	}
	
	dialog_fluid_synth_select_program->set_active_channels_group(chan_group);
	dialog_fluid_synth_select_program->show();
	dialog_fluid_synth_select_program->update_soundfonts_table(&sound_fonts_names_dispaly_data);

	if (chan_group == _MIDI_MIXER_CHANNELS_1_8)
	{
		fluid_channels_sheet_1_8->getTableWidget()->clearSelection();
	}
	if (chan_group == _MIDI_MIXER_CHANNELS_9_16)
	{
		fluid_channels_sheet_9_16->getTableWidget()->clearSelection();
	}
	
	return 0;
}

/**
*   @brief  Activated when a cell is doubleclicked.
*   @param  none
*   @return void
*/
void Dialog_FluidSynthChannels::on_row_double_click_ch_1_8(int *raw, int *col)
{
	channel_selected(*raw, *col, _MIDI_MIXER_CHANNELS_1_8);
}

void Dialog_FluidSynthChannels::on_row_double_click_ch_9_16(int *raw, int *col)
{
	channel_selected(*raw + 8, *col, _MIDI_MIXER_CHANNELS_9_16);
}

/**
*   @brief  Get the bank of the provided soundfont id and push tham into 
*	 the active _soundfont_bank_nums vector.
*   @param  sfid soundfont id number
*   @return void
*/
void Dialog_FluidSynthChannels::get_banks(int sfid)
{
	int i, j;
	bool bank_exist = false;

	active_soundfont_bank_nums.clear();
	
	for (i = 0; i < active_soundfont_presets.size(); i++)
	{
		// Look for the 1st apperance of preset of the given soundfont id.
		if (active_soundfont_presets.at(i).sound_font_id == sfid)
		{
			active_soundfont_bank_nums.push_back(active_soundfont_presets.at(i).banknum);
			break;
		}
	}

	if (active_soundfont_bank_nums.size() == 0)
	{
		// No bank found.
		return;
	}
	// Start from the next element
	i++;
	
	for (i; i < active_soundfont_presets.size(); i++)
	{
		if (active_soundfont_presets.at(i).sound_font_id == sfid)
		{
			// Refer only to the selected soundfont id banks.
			for (j = 0; j < active_soundfont_bank_nums.size(); j++)
			{
				bank_exist = false;
				if (active_soundfont_presets.at(i).banknum == active_soundfont_bank_nums.at(j))
				{
					// This bank number was alreaddy registered.
					bank_exist = true;
				}
			}

			if (!bank_exist)
			{
				// Push a new bank number
				active_soundfont_bank_nums.push_back(active_soundfont_presets.at(i).banknum);
			}
		}
	}
}

/**
*   @brief  Called when the user cliks the OK button.
*   @param  bank bank number
*	@param	soundfontid soundfont id number
*   @return void
*/
void Dialog_FluidSynthChannels::program_selection_done()
{
	// Close the dialog
	Dialog_AdjFluidSynth::get_instance()->setFocus(Qt::ActiveWindowFocusReason);
	this->close();
}

/**
*   @brief  Called when the user cliks the Cancel button.
*   @param  none
*   @return void
*/
void Dialog_FluidSynthChannels::program_selection_cancell()
{
	// Close the dialog
	Dialog_AdjFluidSynth::get_instance()->setFocus(Qt::ActiveWindowFocusReason);
	this->close();
}

/**
 * A SLOT callback activated when the soundfont Open pushbutton is pressed.
 * @param None.
 * @return none
 */
void Dialog_FluidSynthChannels::open_soundfont_file()
{
	bool ok;
	int ret;
	QMessageBox msgBox;

	QString fileName = QFileDialog::getOpenFileName(this,
		tr("Open SoundFont File"),
		_FLUID_DEFAULT_SOUNDFONT_DIR,
		tr("SoundFont 2 (*.sf2 *.SF2);;SoundFont 3 (*.sf3 *.SF3);;All Files (*)"));

	if (!fileName.isEmpty())
	{
		msgBox.setIcon(QMessageBox::Warning);
		msgBox.setText("Soundfont file has been selected.");
		msgBox.setInformativeText("Are you sure you want to use it?");
		msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::Cancel);
		msgBox.setDefaultButton(QMessageBox::Cancel);
		ret = msgBox.exec();

		if (ret == QMessageBox::Yes)
		{
			char mssg[256];
			sprintf(mssg, "%s SoundFont was loaded.", fileName.toStdString().c_str());
			//MainWindow::getInstance()->updateStatusDisplayText(mssg);
			mod_synth_load_and_set_fluid_synth_soundfont(fileName.toStdString());
			printf("%s", mssg);
		}
	}
}


