/**
*	@file		MainWindow.h
*	@author		Nahum Budin
*	@date		8-May-2024
*	@version	1.0 
*	
*	Version	1.0		8-May-2024
*
*	@brief		Application Main Window that hosts the modules pannels.
*/

#pragma once

#include <QMainWindow>
#include <QActionGroup>
#include <QAction>
#include <QDialog>
#include <QThread>

#include "libAdjRaspi5SynthAPI.h"
#include "Defs.h"
#include "ModulePannel.h"

class ModulePannel;

void wrapper_closeModulePannel(en_modules_ids_t moId);

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
	
	static MainWindow *get_instance();
	
	void close_module_pannel_id(en_modules_ids_t mo_id);
	void close_module_pannel_name(string mod_name);
	
	void request_close_module_pannel_id(en_modules_ids_t mo_id);
	void request_close_module_pannel_name(string mod_name);
	
	vector<string> get_active_modules_names_list();
	
	void control_box_ui_update_callback(int evnt, uint16_t val);
	
	void register_active_dialog(QDialog *dialog);
	void unregister_active_dialog(QDialog *dialog);
	
	void on_patch_file_saved(const QString &s);
	void on_patch_file_loaded(const QString &s);
	
	void copy_sketch(int src, int dest);
	
	vector<string> pending_open_modules_list;
	
	vector<active_module_data_t> active_modules_list;
	
	QMenu *sketches_menu;
	
	
public slots:
	virtual void timerEvent(); // Called by a Timer

private slots :
	void on_add_fluid_synth_module();
	void on_add_hammond_organ_module();
	void on_add_adj_analog_synth_module();
	void on_add_adj_karplus_strong_strings_synth_module();
	void on_add_adj_morphed_sin_synth_module();
	void on_add_adj_pad_synth_module();
	void on_add_adj_midi_player_module();
	void on_add_adj_reverb_effect_module();
	void on_add_adj_distortion_effect_module();
	void on_add_adj_graphic_equilizer_module();	
	void on_add_midi_mixer_module();
	void on_add_adj_midi_mapper_module();
	void on_add_adj_external_midi_interface_control_module();
	void on_add_adj_keyboard_control_module();
	
	void on_save_patch_file();
	void on_load_patch_file();
	
	void on_copy_sketch1_to_sketch2();
	void on_copy_sketch1_to_sketch3();
	void on_copy_sketch2_to_sketch1();
	void on_copy_sketch2_to_sketch3();
	void on_copy_sketch3_to_sketch1();
	void on_copy_sketch3_to_sketch2();
	
protected:
//	void timerEvent(QTimerEvent *event);
	virtual void update_gui(); 
    

private:
	ModulePannel* add_module_pannel(QString module_name_string="");	
	int remove_module_pannel(ModulePannel *module);
	int is_module_openned(en_modules_ids_t moId);
	
	int update_layout_geometry();
	
	void create_actions();
	void create_menus();
	
	void start_update_timer(int interval);
	
		
    Ui::MainWindow *ui;
	static MainWindow *mwind;	
	
	QLayout *layout;
	
	map<string, en_modules_ids_t> modules_ids_map;
	
	list<QDialog*> active_dialogs_list;
	
	QMenu *file_menu;
	QMenu *add_module_menu;
	
	QMenu *help_menu;

	
	QActionGroup *add_modules_group;
	QAction *add_fluid_synth_act;
	QAction *add_hammond_organ_act;
	QAction *add_adj_analog_synth_act;
	QAction *add_adj_karplus_strong_strings_synth_act;
	QAction *add_adj_morphed_sin_synth_act;
	QAction *add_adj_pad_synth_act;
	QAction *add_adj_midi_player_act;
	QAction *add_adj_reverb_effect_act;
	QAction *add_adj_distortion_effect_act;
	QAction *add_adj_graphic_equilizer_act;
	QAction *add_midi_mixer_act;
	QAction *add_adj_midi_mapper_act;
	QAction *add_adj_external_midi_interface_control_act;
	QAction *add_adj_keyboard_control_act;
	
	QActionGroup *patch_files_group;
	QAction *save_patch_file_act;
	QAction *load_patch_file_act;
	
	QActionGroup *sketches_group;
	QAction *copy_sketch1_to_sketch2_act;
	QAction *copy_sketch1_to_sketch3_act;
	QAction *copy_sketch2_to_sketch1_act;
	QAction *copy_sketch2_to_sketch3_act;
	QAction *copy_sketch3_to_sketch1_act;
	QAction *copy_sketch3_to_sketch2_act;
	
};

class SavePatchFileThread : public QThread
{
	Q_OBJECT	
	void run();
	
signals:
	void savePatchFileDone(const QString &s);	
		
};

class LoadPatchFileThread : public QThread
{
	Q_OBJECT	
	void run();
	
signals:
	void loadPatchFileDone(const QString &s);	
		
};

