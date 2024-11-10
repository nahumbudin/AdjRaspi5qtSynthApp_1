/**
* @file		FluidSynthSelectProgramDialog.cpp
*	@author		Nahum Budin
*	@date		26-Oct-2019
*	@version	1.0
*
*	@brief		Used for selecting a program from the available
*				programs in the loaded sounfonts banks.
*
*/

#include <filesystem>

#include <QDialog>
#include <QString>
#include "libAdjRaspi5SynthAPI.h"
//#include "MainTab.h"
#include "ui_Dialog_FluidSynthSelectProgram.h"
#include "Dialog_FluidSynthSelectProgram.h"
#include "Dialog_FluidSynthChannels.h"

Dialog_FluidSynthSelectProgram *Dialog_FluidSynthSelectProgram::dialog_fluid_synth_select_program_instance = NULL;

/**
*   @brief  A wrapper used far callback activation of the soundFontSelected function.
*   @param  row a pointer to an integer varaiable holding the selected row number
*   @param  col a pointer to an integer varaiable holding the selected column number
*   @return 0 if OK -1 otherwise
*/
void soundfont_selected_wrapper(int *row, int *col)
{
	Dialog_FluidSynthSelectProgram::get_instance()->soundfont_selected(row, col);
}

/**
*   @brief  A wrapper used far callback activation of the bankSelected function.
*   @param  row a pointer to an integer varaiable holding the selected row number
*   @param  col a pointer to an integer varaiable holding the selected column number
*   @return 0 if OK -1 otherwise
*/
void bank_selected_wrapper(int *row, int *col)
{
	Dialog_FluidSynthSelectProgram::get_instance()->bank_selected(row, col);
}

/**
*   @brief  A wrapper used far callback activation of the programSelected function.
*   @param  row a pointer to an integer varaiable holding the selected row number
*   @param  col a pointer to an integer varaiable holding the selected column number
*   @return 0 if OK -1 otherwise
*/
void program_selected_wrapper(int *row, int *col)
{
	Dialog_FluidSynthSelectProgram::get_instance()->program_selected(row, col);
}

/**
*   @brief  A wrapper used far callback activation of the on_row_double_click function.
*   @param  row a pointer to an integer varaiable holding the selected row number
*   @param  col a pointer to an integer varaiable holding the selected column number
*   @return 0 if OK -1 otherwise
*/
void on_row_double_clicked_wrapper(int *row, int *col)
{
	Dialog_FluidSynthSelectProgram::get_instance()->on_row_double_clicked(row, col);
}

/** Constructor */
Dialog_FluidSynthSelectProgram::Dialog_FluidSynthSelectProgram(QWidget *parent)
	: QDialog(parent),
	 ui(new Ui::Dialog_FluidSynthSelectProgram)
{
	ui->setupUi(this);
	dialog_fluid_synth_select_program_instance = this;
	fluid_select_soundfont_sheet = NULL;
	
	//setOpenedBy(_SET_PATCH_DIALOG_OPEND_BY_NONE);

	connect(ui->buttonBox_dialog_selectProgram, 
			SIGNAL(accepted()), 
			this, 
			SLOT(program_selection_done()));

	connect(ui->buttonBox_dialog_selectProgram, 
			SIGNAL(rejected()), 
			this, 
			SLOT(program_selection_cancell()));
	
	connect(ui->buttonBox_dialog_selectProgram, 
			SIGNAL(clicked(QAbstractButton*)), 
			this, 
			SLOT(program_selection_other(QAbstractButton*)));
	
	active_channels_group = _MIDI_MIXER_CHANNELS_1_8;
	
	Dialog_FluidSynthChannels::get_instance()->refresh_channels_table_widget(active_channels_group);
}

Dialog_FluidSynthSelectProgram::~Dialog_FluidSynthSelectProgram()
{

}

/**
*   @brief  Returns a pointer to the Dialog_FluidSynthSelectProgram object instance.
*   @param  none
*   @return a pointer to the Dialog_FluidSynthSelectProgram object instance
*/
Dialog_FluidSynthSelectProgram *Dialog_FluidSynthSelectProgram::get_instance()
{
	return dialog_fluid_synth_select_program_instance;
}

void Dialog_FluidSynthSelectProgram::close_event(QCloseEvent *event)
{

}

/**
*   @brief  Set the active channels group selection 1-8 or 9-16.
*   @param  acg	_CHANNELS_SHEET_1_8  _CHANNELS_SHEET_9_16
*   @return None
*/
void Dialog_FluidSynthSelectProgram::set_active_channels_group(int acg)
{
	active_channels_group = acg;
}

/**
*   @brief  Return the active channels group selection 1-8 or 9-16.
*   @param  none
*   @return _CHANNELS_SHEET_1_8  _CHANNELS_SHEET_9_16
*/
int Dialog_FluidSynthSelectProgram::get_active_channels_group()
{
	return active_channels_group;
}

/**
*   @brief  Updates the SoundFonts table.
*   @param  sf_names a pointer to a vector of _sondfont_disp_data_t data elements
*   @return void
*/
void Dialog_FluidSynthSelectProgram::update_soundfonts_table(std::vector<_sondfont_disp_data_t> *sf_names)
{
	QTableWidgetItem *item;
	std::vector<std::string> soundfonts_table_horizontal_headers, soundfonts_table_vertical_headers;
	std::vector<int> soundfonts_table_rows_heights, soundfonts_table_columns_width;

	if (sf_names == NULL)
	{
		return;
	}

	// Create a banks table - columns headers
	soundfonts_table_horizontal_headers.push_back("SoundFont");
	soundfonts_table_horizontal_headers.push_back("SFID");
	soundfonts_table_columns_width.push_back(165);
	soundfonts_table_columns_width.push_back(50);

	// Clear the rows headers and set rows height
	for (int i = 0; i < sf_names->size(); i++)
	{
		soundfonts_table_vertical_headers.push_back("");
		soundfonts_table_rows_heights.push_back(18);
	}

	fluid_select_soundfont_sheet = new NQgridWidget(sf_names->size(), 2);

	fluid_select_soundfont_sheet->registerOnClickEvent(&soundfont_selected_wrapper);

	fluid_select_soundfont_sheet->getTableWidget()->setToolTip("Loaded SoundFonts");
	fluid_select_soundfont_sheet->getTableWidget()->setFont(QFont("Helvetica", 11));
	fluid_select_soundfont_sheet->getTableWidget()->setSelectionBehavior(QAbstractItemView::SelectionBehavior::SelectRows);
	// Set table headers and cells sizes
	fluid_select_soundfont_sheet->setHorizontalHeaders(&soundfonts_table_horizontal_headers);
	fluid_select_soundfont_sheet->setVerticalHeaders(&soundfonts_table_vertical_headers);
	fluid_select_soundfont_sheet->setRowColsSize(&soundfonts_table_rows_heights, &soundfonts_table_columns_width);

	for (int r = 0; r < sf_names->size(); r++)
	{
		// Fill table data
		fluid_select_soundfont_sheet->setTabItemStringValue(r, 0, QString::fromStdString(filesystem::path(sf_names->at(r).name).filename()));
		fluid_select_soundfont_sheet->setTabItemIntegerValue(r, 1, sf_names->at(r).sfid);
		
		fluid_select_soundfont_sheet->getTableWidget()->setEditTriggers(QAbstractItemView::NoEditTriggers);
		
//		item = fluidSelectSoundFontSheet->getTableWidget()->item(r, 0);
		// Make cells not editable.
//		if (item)
//		{
//			item->setFlags(item->flags() & ~Qt::ItemIsEditable);
//		}
	}
	// Make the table scrollable
	ui->scrollArea_dialogFluidSelectProgram_soundfonts->setWidget(fluid_select_soundfont_sheet);

	fluid_select_soundfont_sheet->show();
}

/**
*   @brief  Updates the soundfont banks table.
*   @param  none
*   @return void
*/
void Dialog_FluidSynthSelectProgram::update_banks_table()
{
	QTableWidgetItem *item;
	std::vector<std::string> banks_table_horizontal_headers, banks_table_vertical_headers;
	std::vector<int> banks_table_rows_heights, banks_table_columns_width;

	// Create banks table
	banks_table_horizontal_headers.push_back("Bank");
	banks_table_columns_width.push_back(60);

	for (int i = 0; i < Dialog_FluidSynthChannels::active_soundfont_bank_nums.size(); i++)
	{
		banks_table_vertical_headers.push_back("");
		banks_table_rows_heights.push_back(18);
	}
	fluid_select_program_banks_sheet = new NQgridWidget(Dialog_FluidSynthChannels::active_soundfont_bank_nums.size(), 1);
	fluid_select_program_banks_sheet->registerOnClickEvent(&bank_selected_wrapper);
	fluid_select_program_banks_sheet->getTableWidget()->setToolTip("SoundFont Banks");
	fluid_select_program_banks_sheet->getTableWidget()->setFont(QFont("Helvetica", 11));
	fluid_select_program_banks_sheet->getTableWidget()->setSelectionBehavior(QAbstractItemView::SelectionBehavior::SelectRows);

	//	fluidSelectProgramBanksSheet->setParent(ui->widget_dialogFluidSelectProgram_banks);
	fluid_select_program_banks_sheet->setHorizontalHeaders(&banks_table_horizontal_headers);
	fluid_select_program_banks_sheet->setVerticalHeaders(&banks_table_vertical_headers);
	fluid_select_program_banks_sheet->setRowColsSize(&banks_table_rows_heights, &banks_table_columns_width);

	fluid_select_program_banks_sheet->getTableWidget()->setEditTriggers(QAbstractItemView::NoEditTriggers);
	
	for (int r = 0; r < Dialog_FluidSynthChannels::active_soundfont_bank_nums.size(); r++)
	{
		fluid_select_program_banks_sheet->setTabItemIntegerValue(r, 0, Dialog_FluidSynthChannels::active_soundfont_bank_nums.at(r));
//		item = fluidSelectProgramBanksSheet->getTableWidget()->item(r, 0);
//		if (item)
//		{
//			item->setFlags(item->flags() & ~Qt::ItemIsEditable);
//		}
	}

	ui->scrollArea_dialogFluidSelectProgram_banks->setWidget(fluid_select_program_banks_sheet);

	fluid_select_program_banks_sheet->show();
}

/**
*   @brief  Updates selected soundfont bank presets table.
*   @param  bank bank number
*	@param	soundfontid soundfont id number
*   @return void
*/
void Dialog_FluidSynthSelectProgram::update_bank_presets_table(int bank, int soundfontid)
{
	std::vector<std::string> bank_presets_table_horizontal_headers, bank_presets_table_vertical_headers;
	std::vector<int> bank_presets_table_rows_heights, bank_presets_table_columns_width;
	std::vector<_soundfont_presets_data_t> active_soundfont_presets;
	QTableWidgetItem item;

	// Build a vector of all the presets that belongs to the selected soundfont and bank
	for (int i = 0; i < Dialog_FluidSynthChannels::get_instance()->get_active_soundfont_presets()->size(); i++)
	{
		if ((Dialog_FluidSynthChannels::get_instance()->get_active_soundfont_presets()->at(i).banknum == bank) &&
			(Dialog_FluidSynthChannels::get_instance()->get_active_soundfont_presets()->at(i).sound_font_id == soundfontid))
		{
			active_soundfont_presets.push_back(Dialog_FluidSynthChannels::get_instance()->get_active_soundfont_presets()->at(i));
		}
	}

	bank_presets_table_horizontal_headers.push_back("Prog");
	bank_presets_table_horizontal_headers.push_back("Name");
	bank_presets_table_horizontal_headers.push_back("SFID");
	bank_presets_table_horizontal_headers.push_back("SoundFont");

	for (int i = 0; i < active_soundfont_presets.size(); i++)
	{
		bank_presets_table_vertical_headers.push_back("");
		bank_presets_table_rows_heights.push_back(16);
	}

	bank_presets_table_columns_width.push_back(50);
	bank_presets_table_columns_width.push_back(200);
	bank_presets_table_columns_width.push_back(50);
	bank_presets_table_columns_width.push_back(150);
	
	fluid_bank_presets_sheet = new NQgridWidget(active_soundfont_presets.size(), 4);
	fluid_bank_presets_sheet->registerOnClickEvent(&program_selected_wrapper);
	fluid_bank_presets_sheet->registerOnDoubleClickEvent(&on_row_double_clicked_wrapper);
	fluid_bank_presets_sheet->getTableWidget()->setToolTip("FluidSynth selected sound font and bank presets");
	fluid_bank_presets_sheet->getTableWidget()->setFont(QFont("Helvetica", 10));
	fluid_bank_presets_sheet->getTableWidget()->setSelectionBehavior(QAbstractItemView::SelectionBehavior::SelectRows);
	fluid_bank_presets_sheet->getTableWidget()->setSizeAdjustPolicy(QTableWidget::AdjustToContents);
	fluid_bank_presets_sheet->getTableWidget()->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
	fluid_bank_presets_sheet->getTableWidget()->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);

	fluid_bank_presets_sheet->setHorizontalHeaders(&bank_presets_table_horizontal_headers);
	fluid_bank_presets_sheet->setVerticalHeaders(&bank_presets_table_vertical_headers);
	fluid_bank_presets_sheet->setRowColsSize(&bank_presets_table_rows_heights, &bank_presets_table_columns_width);
	
	fluid_bank_presets_sheet->getTableWidget()->setEditTriggers(QAbstractItemView::NoEditTriggers);

	for (int i = 0; i < active_soundfont_presets.size(); i++)
	{
		fluid_bank_presets_sheet->setTabItemIntegerValue(i, 0, active_soundfont_presets.at(i).program);
		fluid_bank_presets_sheet->setTabItemStringValue(i, 1, active_soundfont_presets.at(i).presetname);
		fluid_bank_presets_sheet->setTabItemIntegerValue(i, 2, active_soundfont_presets.at(i).sound_font_id);
		fluid_bank_presets_sheet->setTabItemStringValue(i, 3, 
			QString::fromStdString(filesystem::path(mod_synth_get_fluid_synth_soundfont_id_name(
				active_soundfont_presets.at(i).sound_font_id)).filename()));
	}
	   
	ui->scrollArea_dialogFluidSelectProgram_presets->setWidget(fluid_bank_presets_sheet);
	fluid_bank_presets_sheet->show();

}

/**
*   @brief  Called when the user cliks the OK button.
*   @param  bank bank number
*	@param	soundfontid soundfont id number
*   @return void
*/
void Dialog_FluidSynthSelectProgram::program_selection_done()
{
	// Select and close the dialog
	this->close();
	mod_synth_set_fluid_synth_program_select(Dialog_FluidSynthChannels::get_instance()->selected_channel,
		selected_soundfont_id,
		selected_bank,
		selected_program);
	Dialog_FluidSynthChannels::get_instance()->refresh_channels_table_widget(active_channels_group);
}

/**
*   @brief  Called when the user cliks the Cancel button.
*   @param  none
*   @return void
*/
void Dialog_FluidSynthSelectProgram::program_selection_cancell()
{
	// Close the dialog
	this->close();
}

/**
*   @brief  Called when the user cliks the Apply button.
*   @param  button pressed button
*   @return void
*/

void Dialog_FluidSynthSelectProgram::program_selection_other(QAbstractButton *button)
{
	if (button == (QAbstractButton*)ui->buttonBox_dialog_selectProgram->button(QDialogButtonBox::Apply))
	{
		// Select and do not close the dialog
		mod_synth_set_fluid_synth_program_select(Dialog_FluidSynthChannels::get_instance()->selected_channel, // 0-15
			selected_soundfont_id,
			selected_bank,
			selected_program);
		Dialog_FluidSynthChannels::get_instance()->refresh_channels_table_widget(active_channels_group);
	} 
}


void Dialog_FluidSynthSelectProgram::update()
{
	
}

/**
*   @brief  Called when a soundfont is selectes.
*   @param  row a pointer to an integer varaiable holding the selected row number
*   @param  col a pointer to an integer varaiable holding the selected column number
*   @return void
*/
void Dialog_FluidSynthSelectProgram::soundfont_selected(int *row, int *col)
{
	selected_soundfont_id = fluid_select_soundfont_sheet->getTableWidget()->item(*row, 1)->text().toInt();
	
	Dialog_FluidSynthChannels::get_instance()->get_banks(selected_soundfont_id);
	update_banks_table();	
}

/**
*   @brief  Called when a bank is selectes.
*   @param  row a pointer to an integer varaiable holding the selected row number
*   @param  col a pointer to an integer varaiable holding the selected column number
*   @return void
*/
void Dialog_FluidSynthSelectProgram::bank_selected(int *row, int *col)
{
	selected_bank = fluid_select_program_banks_sheet->getTableWidget()->item(*row, 0)->text().toInt();

	update_bank_presets_table(selected_bank, selected_soundfont_id);
}

/**
*   @brief  Called when a program is selectes.
*   @param  row a pointer to an integer varaiable holding the selected row number
*   @param  col a pointer to an integer varaiable holding the selected column number
*   @return void
*/
void Dialog_FluidSynthSelectProgram::program_selected(int *row, int *col)
{
	selected_program = fluid_bank_presets_sheet->getTableWidget()->item(*row, 0)->text().toInt();
}

/**
*   @brief  Activated when a cell is doubleclicked.
*   @param  none
*   @return void
*/
void Dialog_FluidSynthSelectProgram::on_row_double_clicked(int *raw, int *col)
{
	// Select and do not close the dialog
	mod_synth_set_fluid_synth_program_select(Dialog_FluidSynthChannels::get_instance()->selected_channel, // 0-15
		selected_soundfont_id,
		selected_bank,
		selected_program);
	Dialog_FluidSynthChannels::get_instance()->refresh_channels_table_widget(active_channels_group);
}



