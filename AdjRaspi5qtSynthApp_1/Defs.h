#pragma once

#include <QColor>

#define _CHANNELS_SHEET_1_8		0
#define _CHANNELS_SHEET_9_16	1

#define _CONTROL_COLOR_BLACK	QColor(110, 110, 110)
#define _CONTROL_COLOR_GREEN	QColor(22, 205, 75)
#define _CONTROL_COLOR_RED		QColor(255, 0, 0)
#define _CONTROL_COLOR_BLUE		QColor(10, 149, 255)
#define _CONTROL_COLOR_WHITE	QColor(255, 255, 255)
#define _CONTROL_COLOR_YELLOW	QColor(255, 255, 0)

class ModulePannel;

typedef struct activeModules
{
	en_modules_ids_t module_id;
	QString module_name;
	ModulePannel *module_pannel_object;
	bool pending_close_event;
	
	activeModules(en_modules_ids_t module_id = en_modules_ids_t::none_module_id)
		: module_id(module_id)
	{}
	
	
} active_module_data_t;



