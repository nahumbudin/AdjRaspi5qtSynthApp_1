/**
* @file		Dialog_FluidSynthSelectProgram.h
*	@author		Nahum Budin
*	@date		20-Jul-2024
*	@version	1.1
*					1. Code refactoring
*
*	@brief		Used for selecting a program from the available
*				programs in the loaded sounfonts banks.
*				
*	History:
*				V1.0 26-Oct-2019
*
*/

#pragma once

#include <QDialog>
#include <QDialogButtonBox>

#include "Defs.h"
#include "NQgridWidget.h"

namespace Ui {
class Dialog_FluidSynthSelectProgram;
}

void sound_font_selected_wrapper(int *row, int *col);
void bank_selected_wrapper(int *row, int *col);
void program_selected_wrapper(int *row, int *col);

void on_row_double_clicked_wraper(int *row, int *col);

class Dialog_FluidSynthSelectProgram : public QDialog
{
	Q_OBJECT

public:
	explicit Dialog_FluidSynthSelectProgram(QWidget *parent = 0);
	~Dialog_FluidSynthSelectProgram();

	static Dialog_FluidSynthSelectProgram *get_instance();

	void close_event(QCloseEvent *event);
	
	void set_active_channels_group(int acg);
	int get_active_channels_group();
	
	void update_soundfonts_table(std::vector<_sondfont_disp_data_t> *sf_names);
	void update_banks_table();
	void update_bank_presets_table(int bank, int sound_font_id);
	
	void update();

	void soundfont_selected(int *row, int *col);
	void bank_selected(int *row, int *col);
	void program_selected(int *row, int *col);
	
	void on_row_double_clicked(int *raw, int *col);


protected slots:
	void program_selection_done();
	void program_selection_cancell();
	void program_selection_other(QAbstractButton *button);
	

private:
	Ui::Dialog_FluidSynthSelectProgram *ui;

	static Dialog_FluidSynthSelectProgram *dialog_fluid_synth_select_program_instance;

	NQgridWidget *fluid_select_program_banks_sheet;
	NQgridWidget *fluid_select_soundfont_sheet;
	NQgridWidget *fluid_bank_presets_sheet;

	std::vector<std::string> presets_table_horizontal_headers, presets_table_vertical_headers;
	std::vector<int> presets_table_rows_heights, presets_table_columns_width;

	int selected_soundfont_id;
	int selected_bank;
	int selected_program;
	
	int active_channels_group;
};


