/**
* @file		NQgridWidget.h
*	@author		Nahum Budin
*	@date		22-Jul-2024
*	@version	1.1
*					1. Add setTabItemIntegerValue() with color
*
*	@brief		A Qt based grid widget based on QTableWidget that provides
*				a spreadsheet like data display and entry.
*				Based on the spreadsheet example by Qt
*				
*	History:
*				V1.0 24-Oct-2019
*
*/

#ifndef _NQ_GRIS_WIDGET
#define _NQ_GRIS_WIDGET

#include <QMainWindow>
#include <string>
#include <vector>

#include "NQgridWidgetItem.h"

using namespace std;

typedef struct _sondfont_disp_data
{
	int sfid;
	std::string name;

} _sondfont_disp_data_t;


class QTableWidget;
class QTableWidgetItem;
class QLabel;
class QAction;
class QToolBar;

typedef void(*funcVoidPtrIntPtrInt)(int*, int*);

class NQgridWidget : public QMainWindow
{
	Q_OBJECT

public:

	NQgridWidget(int rows, int cols, QWidget *parent = NULL);

	void registerOnDoubleClickEvent(funcVoidPtrIntPtrInt ptr);
	void registerOnClickEvent(funcVoidPtrIntPtrInt ptr);

	int setHorizontalHeaders(std::vector<std::string> *headers);
	int setVerticalHeaders(std::vector<std::string> *headers);
	int setRowColsSize(std::vector<int> *rowsHeight, std::vector<int> *colsWidths);
	
	
	int setTabItemStringValue(int row, int col, QString qstrval);
	int setTabItemIntegerValue(int row, int col, int intval);
	int setTabItemIntegerValue(int row, int col, int intval, QColor color);

	QTableWidget *getTableWidget();

public slots:
	void onDoubleCliked(int row, int column);
	void onCliked(int row, int column);


//	void updateStatus(QTableWidgetItem *item);
//	void updateLineEdit(QTableWidgetItem *item);
//	void returnPressed();
//	void selectFont();
//	void clear();
//	void showAbout();

protected:
	void createActions();

	
	
	void setupContextMenu();
	
	void setupContents();

	void setupMenuBar();


private:
//	QToolBar *toolBar;
//	QAction *colorAction;

//	QAction *fontAction;
//	QAction *firstSeparator;
//	QAction *secondSeparator;
//	QAction *clearAction;
//	QAction *aboutSpreadSheet;
	QLabel *cellLabel;
	
	QTableWidget *table;

	funcVoidPtrIntPtrInt onDoubleClickCallbackPtr;
	funcVoidPtrIntPtrInt onClickCallbackPtr;
};


#endif


