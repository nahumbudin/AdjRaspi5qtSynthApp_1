/**
*	@file		ModulePannel.cpp
*	@author		Nahum Budin
*	@date		8-May-2024
*	@version	1.0 
*	
*	Version	1.0		8-May-2024
*
*	@brief		Handles a single module pannel.
*/

#include "ModulePannel.h"
#include "ui_ModulePannel.h"


/**
*   @brief Creates a new module pannel object.
*   @param  *parent					parent QWidget (at MainWindow)
*   @param  moduleNameStr			QString that holds the module name (displayed text)
*   @param  func_ptr_void_int_t		a pointer to a callback void foo(int) that handeles the module close operation.
*   @param  moduleId				a unique integer number identifier of each module type.
*	@return 0 if done; -1 otherwise 
*/
ModulePannel::ModulePannel(QWidget *parent, 
						   QString module_name_str,
						   func_ptr_void_en_modules_ids_t_t close_module_pannel_callback_ptr,
						   en_modules_ids_t moduleId)
	: QFrame(parent)
	, ui(new Ui::ModulePannel)
{
	ui->setupUi(this);
	
	module_name = module_name_str;
	
	ui->label->setText(module_name);
	
	ui->label->setAttribute(Qt::WA_TranslucentBackground);
	
	// ui->checkBox_ModuleMIDIin->palette(QWidget::);
	ui->checkBox_ModuleMIDIin->setAttribute(Qt::WA_TranslucentBackground);
	
	moduleID = moduleId;
	close_callback_ptr = close_module_pannel_callback_ptr;
	
	connect(ui->pushButton_ModuleExit, SIGNAL(clicked(bool)), this, SLOT(on_module_exit_clicked(bool)));
	connect(ui->pushButton_ModuleOpen, SIGNAL(clicked(bool)), this, SLOT(on_module_open_clicked(bool)));
	connect(ui->pushButton_ModuleConnections, SIGNAL(clicked(bool)), this, SLOT(on_module_connections_clicked(bool)));
	
	
}

ModulePannel::~ModulePannel()
{
	delete ui;
}

ModulePannel *ModulePannel::get_the_module_pannel()
{
	return this;
}

void ModulePannel::on_module_exit_clicked(bool checked)
{
	if (close_callback_ptr != Q_NULLPTR)
	{
		close_callback_ptr(moduleID);
	}
}

void ModulePannel::on_module_open_clicked(bool checked)
{
	if (checked)
	{
		
	}
	else
	{
		
	}
}

void ModulePannel::on_module_connections_clicked(bool checked)
{
	if (checked)
	{
		connections_dialog = new Dialog_InstrumentConnections(this, module_name);
		connections_dialog->show();
	}
	else
	{
		connections_dialog->close();
	}
}
