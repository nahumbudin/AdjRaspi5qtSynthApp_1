/**
*	@file		ModulePannel.h
*	@author		Nahum Budin
*	@date		8-May-2024
*	@version	1.0 
*	
*	Version	1.0		8-May-2024
*
*	@brief		Handles a single module pannel.
*/

#ifndef _MODULES_PANNEL
#define _MODULES_PANNEL 

#include <QFrame>

#include "libAdjRaspi5SynthAPI.h"

#include "Dialog_InstrumentConnections.h"
#include "Dialog_AdjFluidSynth.h"
#include "Dialog_MidiPlayer.h"
#include "Dialog_MidiMixer.h"

class Dialog_InstrumentConnections;

namespace Ui {
	class ModulePannel;
}

/* void foo(en_modulesIds_t) function pointer */
typedef void(*func_ptr_void_en_modules_ids_t_t)(en_modules_ids_t);


class ModulePannel : public QFrame
{
	Q_OBJECT
    
public :
/**
*   @brief Creates a new module pannel object.
*   @param  *parent							parent QWidget (at MainWindow)
*   @param  moduleNameStr					QString that holds the module name (displayed text)
*   @param  func_ptr_void_en_modulesIds_t_t	a pointer to a callback void foo(en_modulesIds_t) that handeles the module close operation.
*   @param  en_modulesIds_t					a unique enum identifier of each module type.
*	@return 0 if done; -1 otherwise 
*/
	explicit ModulePannel(QWidget *parent = 0, 
						  QString module_name_str = "Module",
						  func_ptr_void_en_modules_ids_t_t close_module_pannel_callback_ptr = NULL,
						  en_modules_ids_t mod_id = en_modules_ids_t::none);
	~ModulePannel();

	ModulePannel *get_the_module_pannel();

	Ui::ModulePannel *ui;
	
	en_modules_ids_t module_id;
	QString module_name;
	

protected slots :
	void on_module_exit_clicked(); 
	void on_module_open_clicked();
	void on_module_connections_clicked();

  private:
	void close_connections_dialog();
	void close_module_dialog();
	
	func_ptr_void_en_modules_ids_t_t close_callback_ptr;
	
	Dialog_InstrumentConnections *connections_dialog;	
	Dialog_AdjFluidSynth *dialog_adj_fluid_synth;
	Dialog_MidiPlayer *dialog_adj_midi_player;
	Dialog_MidiMixer *dialog_midi_mixer;
};


#endif

