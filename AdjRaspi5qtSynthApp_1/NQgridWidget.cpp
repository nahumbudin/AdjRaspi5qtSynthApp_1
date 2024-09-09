
/**
* @file		NQgridWidget.cpp
*	@author		Nahum Budin
*	@date		22-Jul-2024
*	@version	1.1
*					1. Add setTabItemColor()
*
*	@brief		A Qt based grid widget based on QTableWidget that provides
*				a spreadsheet like data display and entry.
*				Based on the spreadsheet example by Qt
*				
*	History:
*				V1.0 24-Oct-2019
*
*/

#include <QtWidgets>

#include "NQgridWidget.h"

/**
*   @brief  constructor.
*   @param  rows the number of rows
*	@param	colos the number of columns
*	@param	the parent widget
*   @return void
*/
NQgridWidget::NQgridWidget(int rows, int cols, QWidget *parent)
	: QMainWindow(parent)
{
	table = new QTableWidget(rows, cols, this);
	table->setSizeAdjustPolicy(QTableWidget::AdjustToContents);
	table->horizontalScrollBar()->setEnabled(true);
	setCentralWidget(table);

	createActions();

	connect(table, 
		SIGNAL(cellClicked(int, int)),
		this, 
		SLOT(onCliked(int, int))); 

	connect(table,
		SIGNAL(cellDoubleClicked(int, int)),
		this,
		SLOT(onDoubleCliked(int, int)));

	onDoubleClickCallbackPtr = NULL;
	onClickCallbackPtr = NULL;
}

/**
*   @brief  Set the horizontal (columns) header.
*   @param  headers a pointer to a vector of type std::vector<std::string>
*			containing the headers strings.
*   @return 0 if OK -1 otherwise
*/
int NQgridWidget::setHorizontalHeaders(std::vector<std::string> *headers)
{
	int i = 0, res = 0;

	if ((headers == NULL) || (headers->size() == 0))
	{
		return -1;
	}

	for (i = 0; i < headers->size() && i < table->columnCount(); i++)
	{
		table->setHorizontalHeaderItem(i, new QTableWidgetItem(headers->at(i).c_str()));
	}

	return 0;
}

/**
*   @brief  Set the vertical (rows) header.
*   @param  headers a pointer to a vector of type std::vector<std::string>
*			containing the headers strings.
*   @return 0 if OK -1 otherwise
*/
int NQgridWidget::setVerticalHeaders(std::vector<std::string> *headers)
{
	int i = 0, res = 0;

	if ((headers == NULL) || (headers->size() == 0))
	{
		return -1;
	}

	for (i = 0; i < headers->size() && i < table->rowCount(); i++)
	{
		table->setVerticalHeaderItem(i, new QTableWidgetItem(headers->at(i).c_str()));
	}

	return 0;
}

/**
*   @brief  Set the columns width and rows heights.
*   @param  rowsHeight a pointer to a vector of type std::vector<int> 
*			containing the rows heights.
*   @param  colsWidths a pointer to a vector of type std::vector<int>
*			containing the columns widths.
*   @return 0
*/
int NQgridWidget::setRowColsSize(std::vector<int> *rowsHeight, std::vector<int> *colsWidths)
{
	for (int i = 0; i < rowsHeight->size(); i++)
	{
		table->setRowHeight(i, rowsHeight->at(i));
	}

	for (int i = 0; i < colsWidths->size(); i++)
	{
		table->setColumnWidth(i, colsWidths->at(i));
	}

	return 0;
}

/**
*   @brief  Set an item string value.
*   @param  row item's row
*   @param  col items column
*	@ qstrval a QString string value.
*   @return 0
*/
int NQgridWidget::setTabItemStringValue(int row, int col, QString qstrval)
{
	NQgridWidgetItem *item;

	item = new NQgridWidgetItem(qstrval);
	item->setForeground(QColor(255, 236, 23));
	table->setItem(row, col, item);
	
	//table->setItem(row, col, new NQgridWidgetItem(qstrval));
	
	return 0;
}

/**
*   @brief  Set an item integer value.
*   @param  row item's row
*   @param  col items column
*	@ intval an integer value.
*   @return 0
*/
int NQgridWidget::setTabItemIntegerValue(int row, int col, int intval)
{
	NQgridWidgetItem *item;

	item = new NQgridWidgetItem(QString::number(intval));
	item->setTextAlignment(Qt::AlignHCenter);
	item->setForeground(QColor(255, 236, 23));
	table->setItem(row, col, item);

	return 0;
}

/**
*   @brief  Set an item integer value and background color.
*   @param  row item's row
*   @param  col items column
*	@param	QColor color value.
*   @return 0
*/
int NQgridWidget::setTabItemIntegerValue(int row, int col, int intval, QColor color)
{
	NQgridWidgetItem *item;

	item = new NQgridWidgetItem(QString::number(intval));
	item->setTextAlignment(Qt::AlignHCenter);
	item->setForeground(QColor(255, 236, 23));
	item->setBackground(color);
	table->setItem(row, col, item);

	return 0;
}


// Slots

/**
*   @brief  A slot function triggered by double clicking on an item.
*			It activates a callback function of type void(*foo)(int*, int*)
*			returning the double clicked item row and column.
*			Call back function should be register by using the
*			registerOnDoubleClickEvent function.
*   @param  row an integer that holds the clicked item row
*   @param  column an integer that holds the clicked item column
*   @return void
*/
void NQgridWidget::onDoubleCliked(int row, int column)
{
	
	if (onDoubleClickCallbackPtr)
	{
		onDoubleClickCallbackPtr(&row, &column);
	}
	
	table->setCurrentCell(row, 0);
}

/**
*   @brief  A slot function triggered by clicking on an item.
*			It activates a callback function of type void(*foo)(int*, int*)
*			returning the clicked item row and column.
*			Call back function should be register by using the
*			registerOnClickEvent function.
*   @param  row an integer that holds the clicked item row
*   @param  column an integer that holds the clicked item column
*   @return void
*/
void NQgridWidget::onCliked(int row, int column)
{

	if (onClickCallbackPtr)
	{
		onClickCallbackPtr(&row, &column);
	}
}



/**
*   @brief  Register a callback function of type void(*foo)(int*, int*)
*			that will be activated  by double clicking on an item.
*   @param  ptr a pointer to a callback function of type void(*foo)(int*, int*)
*   @return void
*/
void NQgridWidget::registerOnDoubleClickEvent(funcVoidPtrIntPtrInt ptr)
{
	onDoubleClickCallbackPtr = ptr;
}

/**
*   @brief  Register a callback function of type void(*foo)(int*, int*)
*			that will be activated  by clicking on an item.
*   @param  ptr a pointer to a callback function of type void(*foo)(int*, int*)
*   @return void
*/
void NQgridWidget::registerOnClickEvent(funcVoidPtrIntPtrInt ptr)
{
	onClickCallbackPtr = ptr;
}

/**
*   @brief  returns a pointer to the QTableWidget table object
*			that will be activated  by double clicking on an item.
*   @param  none
*   @return a pointer to the QTableWidget table object
*/
QTableWidget *NQgridWidget::getTableWidget() { return table; }


void NQgridWidget::createActions()
{
//	fontAction = new QAction(tr("Font..."), this);
//	fontAction->setShortcut(Qt::CTRL | Qt::Key_F);
//	connect(fontAction, &QAction::triggered, this, &SpreadSheet::selectFont);

//	colorAction = new QAction(QPixmap(16, 16), tr("Background &Color..."), this);
//	connect(markRowAction, &QAction::triggered, this, &NQgridWidget::selectColor);

//	clearAction = new QAction(tr("Clear"), this);
//	clearAction->setShortcut(Qt::Key_Delete);
//	connect(clearAction, &QAction::triggered, this, &SpreadSheet::clear);

//	exitAction = new QAction(tr("E&xit"), this);
//	connect(exitAction, &QAction::triggered, qApp, &QCoreApplication::quit);

//	firstSeparator = new QAction(this);
//	firstSeparator->setSeparator(true);

//	secondSeparator = new QAction(this);
//	secondSeparator->setSeparator(true);
}

/*
void NQgridWidget::selectColor()
{
	QTableWidgetItem *item = table->currentItem();
	QColor col = item ? item->backgroundColor() : table->palette().base().color();
	col = QColorDialog::getColor(col, this);
	if (!col.isValid())
		return;

	QList<QTableWidgetItem*> selected = table->selectedItems();
	if (selected.count() == 0)
		return;

	foreach(QTableWidgetItem *i, selected) {
		if (i)
			i->setBackgroundColor(col);
	}

	updateColor(table->currentItem());
}
*/




void decode_position(const QString &pos, int *row, int *col)
{
	if (pos.isEmpty()) {
		*col = -1;
		*row = -1;
	}
	else {
		*col = pos.at(0).toLatin1() - 'A';
		*row = pos.right(pos.size() - 1).toInt() - 1;
	}
}

QString encode_position(int row, int col)
{
	return QString(col + 'A') + QString::number(row + 1);
}
