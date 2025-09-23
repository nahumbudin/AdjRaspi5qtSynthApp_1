/**
*	@file		InstrumentPannel.h
*	Pannel.h
*	@author		Nahum Budin
*	@date		22-Sep-2025
*	@version	1.1 
*			1. Renaming file from ModulePannel to InstrumentPannel
*			2. Refactoring rename modules to instruments
*	
*	History:
*			Version	1.0		8-May-2024	Initial
*
*	@brief		Handles a single Instrument pannel.
*/

#ifndef _INSTRUMENTS_PANNEL
#define _INSTRUMENTS_PANNEL 

#include <QFrame>

#include "libAdjRaspi5SynthAPI.h"

#include "Dialog_InstrumentConnections.h"
#include "Dialog_AdjFluidSynth.h"
#include "Dialog_MidiPlayer.h"
#include "Dialog_MidiMixer.h"
#include "Dialog_MidiMapper.h"
#include "Dialog_AnalogSynth.h"

class Dialog_InstrumentConnections;

namespace Ui {
	class InstrumentPannel;
}

/* void foo(en_instrumentsIds_t) function pointer */
typedef void(*func_ptr_void_en_instruments_ids_t_t)(en_instruments_ids_t);


class InstrumentPannel : public QFrame
{
	Q_OBJECT
    
public :
/**
*   @brief Creates a new instrument pannel object.
*   @param  *parent									parent QWidget (at MainWindow)
*   @param  instrumentNameStr						QString that holds the instrument name (displayed text)
*   @param  func_ptr_void_en_instrumentsIds_t_t		a pointer to a callback void foo(en_instrumentsIds_t) that 
*													handeles the instrument close operation.
*   @param  en_instrumentsIds_t						a unique enum identifier of each instrument type.
*	@return 0 if done; -1 otherwise 
*/
	explicit InstrumentPannel(QWidget *parent = 0, 
		QString instrument_name_str = "Instrument",
		func_ptr_void_en_instruments_ids_t_t close_instrument_pannel_callback_ptr = NULL,
		en_instruments_ids_t inst = en_instruments_ids_t::none_instrument_id);
	~InstrumentPannel();

	InstrumentPannel *get_the_instrument_pannel();
	
	void hide_checkBox_InstrumentMIDIin();

	Ui::InstrumentPannel *ui;
	
	en_instruments_ids_t instrument_id;
	QString instrument_name;
	

protected slots :
	void on_instrument_exit_clicked(); 
	void on_instrument_open_clicked();
	void on_instrument_connections_clicked();

  private:
	void close_connections_dialog();
	void close_instrument_dialog();
	
	func_ptr_void_en_instruments_ids_t_t close_callback_ptr;
	
	Dialog_InstrumentConnections *connections_dialog;	
	Dialog_AdjFluidSynth *dialog_adj_fluid_synth;
	Dialog_AnalogSynth *dialog_analog_synth;
	Dialog_MidiPlayer *dialog_adj_midi_player;
	Dialog_MidiMixer *dialog_midi_mixer;
	Dialog_MidiMapper * dialog_midi_mapper;
	
	QWidget *widget_parent;
};


#endif

