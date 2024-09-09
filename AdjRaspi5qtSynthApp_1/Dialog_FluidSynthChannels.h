/**
* @file		Dialog_FluidSynthChannels.h
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

#pragma once

#include <QDialog>

#include "NQgridWidget.h"
#include "NQgridWidgetItem.h"

#include "libAdjRaspi5SynthAPI.h"

#include "Dialog_FluidSynthSelectProgram.h"

#include "Defs.h"

//void on_row_double_click_wraper(int *row, int *col);

namespace Ui
{
	class Dialog_FluidSynthChannels;
}

class Dialog_FluidSynthChannels : public QDialog
{
	Q_OBJECT
		
public :
	
	
	
	~Dialog_FluidSynthChannels();
	
	static Dialog_FluidSynthChannels *get_instance(QWidget *parent = 0, bool refresh=false);
	
	void control_box_ui_update_callback(int evnt, uint16_t val);
	
	
	std::vector<_soundfont_presets_data_t> *get_active_soundfont_presets();
	
	int init_channels_table_widget(int chan_group);
	int refresh_channels_table_widget(int chan_group);
	
	int channel_selected(int channel, int col, int chan_group);
	
	void get_banks(int sfid);
	
	void on_row_double_click_ch_1_8(int *raw, int *col);
	void on_row_double_click_ch_9_16(int *raw, int *col);
	
	int selected_channel;
	int active_channels_tab;
	
	std::vector<std::string> channels_table_horizontal_headers, 
		channels_table_vertical_headers_1_8,
		channels_table_vertical_headers_9_16;
	std::vector<int> channels_table_rows_heights, channels_table_columns_width;
	
	NQgridWidget *fluid_channels_sheet_1_8;
	NQgridWidget *fluid_channels_sheet_9_16;
	
	static std::vector<int> loaded_soundfont_ids;
	static std::vector<int> active_soundfont_bank_nums;
	static std::vector<_soundfont_presets_data_t> active_soundfont_presets;
	
public slots :
	void closeEvent(QCloseEvent *event);
	
protected slots :
	void program_selection_done();
	void program_selection_cancell();
	void open_soundfont_file();
	
	
	
private:
	
	explicit Dialog_FluidSynthChannels(QWidget *parent = 0);
	
	Ui::Dialog_FluidSynthChannels *ui;
	
	static Dialog_FluidSynthChannels *dialog_fluid_synth_channels_instance;
	
	Dialog_FluidSynthSelectProgram *dialog_fluid_synth_select_program;
	
};





