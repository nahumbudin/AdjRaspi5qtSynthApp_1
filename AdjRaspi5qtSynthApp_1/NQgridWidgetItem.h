/**
* @file		NQgridWidgetItem.h
*	@author		Nahum Budin
*	@date		24-Oct-2019
*	@version	1.0
*
*	@brief		A Qt based grid widget based on QTableWidget that provides
*				a spreadsheet like data display and entry.
*				Based on the spreadsheet example by Qt
*
*/

#ifndef _NQ_GRID_WIDG
#define _NQ_GRID_WIDG

#include "NQgridWidget.h"

#include <QTableWidgetItem>

class NQgridWidgetItem : public QTableWidgetItem
{
public:
	NQgridWidgetItem();
	NQgridWidgetItem(const QString &text);

	QTableWidgetItem *clone() const override;

	QVariant data(int role) const override;
	void setData(int role, const QVariant &value) override;
	QVariant display() const;

	inline QString formula() const
	{
		return QTableWidgetItem::data(Qt::DisplayRole).toString();
	}

	static QVariant computeFormula(const QString &formula,
		const QTableWidget *widget,
		const QTableWidgetItem *self = 0);

private:
	mutable bool isResolving;
};


void decode_position(const QString &pos, int *row, int *col);
QString encode_position(int row, int col);

#endif 



