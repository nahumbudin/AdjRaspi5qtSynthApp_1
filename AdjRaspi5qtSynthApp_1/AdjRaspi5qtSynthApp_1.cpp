/**
* @file		AdjRaspi5qtSynthApp.cpp
*	@author		Nahum Budin
*	@Date		8-May-2024
*	@version	1.0 
*
*	History:\n
*/

#include "MainWindow.h"
#include <QApplication>

#include <qprocess.h>

#include <unistd.h> // for nice()

#include "Log.h"

/**
*   @brief  Runs on application exit.
*   @param  none
*   @return void
*/
void exit_handler(void)
{
	//	int err;

	printf("Program terminated! Press any key to exit.");
	
	// Disable screen saver
	system("xset s blank");
	system("xset s on");
	system("xset -dpms");
	
	system("pactl unload-module module-jack-sink");
	system("pactl unload-module module-jack-source");
	
	system("cpu.gov -g ondemand");
	
	//	err = errno;
	//	getchar();
}

int main(int argc, char *argv[])
{
	// Set clock control and priority	
	/*
	* https://github.com/DavidM42/rpi-cpu.gov
	*
	* install: wget https://raw.githubusercontent.com/DavidM42/rpi-cpu.gov/master/install.sh && sudo chmod +x ./install.sh && sudo ./install.sh --nochown && sudo rm install.sh
	*
	**/
	system("cpu.gov -g performance");
	// Disable screen saver
	system("xset s noblank");
	system("xset s off");
	system("xset -dpms");
	

	nice(20);

	setbuf(stderr, NULL);
	atexit(exit_handler);
	
	// Debuger
//	FILELog::ReportingLevel() = FILELog::FromString("DEBUG4");
	FILE* pFile = fopen("AdjHeartRaspi5FlSynth1_0.log", "a");
	Output2FILE::Stream() = pFile;
	//	FILE_LOG(logINFO) << "...";
	
	mod_synth_init();
	mod_synth_start_audio();
	
	mod_synth_init_bt_services();

	mod_synth_init_ext_midi_services(_MIDI_EXT_INTERFACE_SERIAL_PORT_NUM);

	mod_synth_init_midi_services();
	
	
	QApplication a(argc, argv);
    MainWindow w;
    w.show();
    
    return a.exec();
}
