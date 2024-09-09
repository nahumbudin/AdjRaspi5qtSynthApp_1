/**
* @file		Dialog_MidiPlayer.h
*	@author		Nahum Budin
*	@date		11-Aug-2024
*	@version	1.0
*
*	@brief		Used for playing MIDI files
*				
*	History:
*
*/

#include <filesystem>

#include <QObject>
#include <QFileDialog>
#include <QTimer>

#include "MainWindow.h"
#include "Dialog_MidiPlayer.h"
#include "ui_Dialog_MidiPlayer.h"

QString midi_file_name;
OpenFileThread *open_file_thread;

int playback_progres_percentegas = 0;

int song_total_playing_time_minutes = 0;
int song_total_playing_time_seconds = 0;
int song_playing_time_minutes = 0;
int song_playing_time_seconds = 0;
int song_remaining_playing_time_minutes = 0;
int song_remaining_playing_time_seconds = 0;

void midi_player_control_box_event_update_ui_callback_wrapper(int evnt, uint16_t val)
{
	Dialog_MidiPlayer::get_instance()->control_box_ui_update_callback(evnt, val);
}


void update_ui_progress_percentages(int progress)
{	
	if (progress < 0)
	{
		progress = 0;
	}
	else if (progress > 100)
	{
		progress = 100;
	}
	
	playback_progres_percentegas = progress;
}

void OpenFileThread::run() 
{		
	QString result = QString("File loaded");
	mod_synth_open_midi_file(midi_file_name.toStdString());
	emit resultReady(result);
}

void update_ui_total_song_playing_time(int min, int sec)
{
	song_total_playing_time_minutes = min;
	song_total_playing_time_seconds = sec;
}
void update_ui_song_playing_time(int min, int sec)
{
	song_playing_time_minutes = min;
	song_playing_time_seconds = sec;
}

void update_ui_song_remaining_playing_time(int min, int sec)
{
	song_remaining_playing_time_minutes = min;
	song_remaining_playing_time_seconds = sec;
}
	

Dialog_MidiPlayer *Dialog_MidiPlayer::dialog_adj_midi_player_instance = NULL;

Dialog_MidiPlayer::Dialog_MidiPlayer(QWidget *parent)
	: QDialog(parent)
	, ui(new Ui::Dialog_MidiPlayer)
{
	ui->setupUi(this);
	dialog_adj_midi_player_instance = this;
	
	this->setFocus(Qt::ActiveWindowFocusReason);
	
	ui->lineEdit_MidiPlayeFileName->setText("");
	
	close_event_callback_ptr = NULL;
	
	mod_synth_register_midi_player_potision_update_callback(&update_ui_progress_percentages);
	mod_synth_register_midi_player_total_song_playing_time_update_callback(&update_ui_total_song_playing_time);
	mod_synth_register_midi_player_song_playing_time_update_callback(&update_ui_song_playing_time);
	mod_synth_register_midi_player_song_remaining_playing_time_update_callback(&update_ui_song_remaining_playing_time);
	
	//open_file_thread = new OpenFileThread();
	//connect(open_file_thread, &OpenFileThread::finished, open_file_thread, &QObject::deleteLater);
	
	mod_synth_register_callback_control_box_event_update_ui(
		&midi_player_control_box_event_update_ui_callback_wrapper);
	
	connect(ui->pushButton_MidiPlayerOpenFile,
		SIGNAL(clicked()),
		this,
		SLOT(on_open_file_clicked()));
	
	connect(ui->pushButton_MidiPlayerPlay,
		SIGNAL(clicked()),
		this,
		SLOT(on_play_clicked()));
	
	connect(ui->pushButton_MidiPlayerPause,
		SIGNAL(clicked()),
		this,
		SLOT(on_pause_clicked()));
	
	connect(ui->pushButton_MidiPlayerStop,
		SIGNAL(clicked()),
		this,
		SLOT(on_stop_clicked()));
	
	MainWindow::get_instance()->register_active_dialog(this);
	
	// start a periodic timer after this timeout - 
	start_update_timer(200);
	
}

Dialog_MidiPlayer::~Dialog_MidiPlayer()
{
	
}

Dialog_MidiPlayer *Dialog_MidiPlayer::get_instance(QWidget *parent)
{
	if (dialog_adj_midi_player_instance == NULL)
	{
		dialog_adj_midi_player_instance = new Dialog_MidiPlayer(parent);
	}
	
	dialog_adj_midi_player_instance->show();
	
	return dialog_adj_midi_player_instance;
}

void Dialog_MidiPlayer::closeEvent(QCloseEvent *event)
{
	if (close_event_callback_ptr != NULL)
	{
		close_event_callback_ptr();
	}
	
	hide();
}

void Dialog_MidiPlayer::control_box_ui_update_callback(int evnt, uint16_t val)
{
	if (!this->hasFocus())
	{
		return;
	}
	
	if(evnt == _CONTROL_PUSHBUTTON_BLUE_GREEN)
	{
		/* Preset 2 */
		if (val == 0)
		{
			/* Only when pressed */
			on_play_clicked();
			
		}
	}
	else if(evnt == _CONTROL_PUSHBUTTON_BLUE_RED)
	{
		/* Preset 3 */
		if (val == 0)
		{
			/* Only when pressed */
			on_pause_clicked();
		}
	}
	else if(evnt == _CONTROL_PUSHBUTTON_BLUE_BLUE)
	{
		/* Load */
		if (val == 0)
		{
			/* Only when pressed */
			on_stop_clicked();
		}
	}
}

void Dialog_MidiPlayer::on_dialog_close()
{
	//mod_synth_unregister_callback_control_box_event_update_ui(
	//	&fluid_control_box_event_update_ui_callback_wrapper);
	
	hide();
}

void Dialog_MidiPlayer::on_midi_file_loaded(const QString &s)
{
	std::string file_name;
		
	file_name = std::string("Ready: ");
	file_name += std::filesystem::path(midi_file_name.toStdString()).stem();
	
	ui->lineEdit_MidiPlayeFileName->setText(QString::fromStdString(file_name));
	
	ui->pushButton_MidiPlayerPlay->setEnabled(true);
	ui->pushButton_MidiPlayerPause->setEnabled(true);
	ui->pushButton_MidiPlayerStop->setEnabled(true);
	
}

void Dialog_MidiPlayer::on_open_file_clicked()
{
	
	QFileDialog dialog;
	// dialog.setOptions(QFileDialog::DontUseNativeDialog);
	midi_file_name = dialog.getOpenFileName(this,
		tr("Open MIDI File "),
		QString(_MIDI_PLAYBACK_FILES_DEFAULT_DIR),
		tr("Presets (*.mid *.MID);;All Files (*)"));

	if (!midi_file_name.isEmpty())
	{
		std::string file_name;
		
		file_name = std::string("Now Loading: ");
		file_name += std::filesystem::path(midi_file_name.toStdString()).stem();
	
		ui->lineEdit_MidiPlayeFileName->setText(QString::fromStdString(file_name));
		
		//mod_synth_open_midi_file(midi_file_name.toStdString());
		open_file_thread = new OpenFileThread();
		connect(open_file_thread,
			&OpenFileThread::finished, open_file_thread, &QObject::deleteLater);
		connect(open_file_thread, &OpenFileThread::resultReady, this, &Dialog_MidiPlayer::on_midi_file_loaded);
		open_file_thread->start();
		
		ui->pushButton_MidiPlayerPlay->setEnabled(false);
		ui->pushButton_MidiPlayerPause->setEnabled(false);
		ui->pushButton_MidiPlayerStop->setEnabled(false);
	}
	
}

void Dialog_MidiPlayer::on_play_clicked()
{
	std::string file_name;
	
	mod_synth_midi_player_play();
	
	file_name = std::string("Playing: ");
	file_name += std::filesystem::path(midi_file_name.toStdString()).stem();
	ui->lineEdit_MidiPlayeFileName->setText(QString::fromStdString(file_name));
}

void Dialog_MidiPlayer::on_pause_clicked()
{
	mod_synth_midi_player_pause();
}

void Dialog_MidiPlayer::on_stop_clicked()
{
	mod_synth_midi_player_stop();	
}

void Dialog_MidiPlayer::start_update_timer(int interval)
{
	QTimer *timer = new QTimer(this);
	connect(timer, SIGNAL(timeout()), this, SLOT(timerEvent()));
	timer->start(interval);
}

void Dialog_MidiPlayer::timerEvent()
{
	update_gui();
}

void Dialog_MidiPlayer::update_gui()
{
	char text[16];
	QString qtext;
	
	ui->progressBar_MidiPlayerProgressPercents->setValue(playback_progres_percentegas);
	
	sprintf(text, "%02i:%02i", song_total_playing_time_minutes, song_total_playing_time_seconds);
	qtext = text;
	ui->label_MidiPlayerSongTotalPlayingTime->setText(qtext);
	
	sprintf(text, "%02i:%02i", song_playing_time_minutes, song_playing_time_seconds);
	qtext = text;
	ui->label_MidiPlayerSongPlayingTime->setText(qtext);
	
	sprintf(text, "%02i:%02i", song_remaining_playing_time_minutes, song_remaining_playing_time_seconds);
	qtext = text;
	ui->label_MidiPlayerSongRemainingPlayingTime->setText(qtext);
}
