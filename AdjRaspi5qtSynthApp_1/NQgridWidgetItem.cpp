
/**
* @file		NQgridWidgetItem.cpp
*	@author		Nahum Budin
*	@date		24-Oct-2019
*	@version	1.0
*
*	@brief		A Qt based grid widget based on QTableWidget that provides
*				a spreadsheet like data display and entry.
*				Based on the spreadsheet example by Qt
*
*/

#include "NQgridWidgetItem.h"

NQgridWidgetItem::NQgridWidgetItem()
	: QTableWidgetItem(), isResolving(false)
{
}

NQgridWidgetItem::NQgridWidgetItem(const QString &text)
	: QTableWidgetItem(text), isResolving(false)
{
}

QTableWidgetItem *NQgridWidgetItem::clone() const
{
	NQgridWidgetItem *item = new NQgridWidgetItem();
	*item = *this;
	return item;
}

QVariant NQgridWidgetItem::data(int role) const
{
	if (role == Qt::EditRole || role == Qt::StatusTipRole)
		return formula();

	if (role == Qt::DisplayRole)
		return display();

	QString t = display().toString();
	bool isNumber = false;
	int number = t.toInt(&isNumber);

	if (role == Qt::ForegroundRole) {
		if (!isNumber)
			return QVariant::fromValue(QColor(Qt::black));
		else if (number < 0)
			return QVariant::fromValue(QColor(Qt::red));
		return QVariant::fromValue(QColor(Qt::blue));
	}

	if (role == Qt::TextAlignmentRole)
		if (!t.isEmpty() && (t.at(0).isNumber() || t.at(0) == '-'))
			return (int)(Qt::AlignRight | Qt::AlignVCenter);

	return QTableWidgetItem::data(role);
}

void NQgridWidgetItem::setData(int role, const QVariant &value)
{
	QTableWidgetItem::setData(role, value);
	if (tableWidget())
		tableWidget()->viewport()->update();
}

QVariant NQgridWidgetItem::display() const
{
	// avoid circular dependencies
	if (isResolving)
		return QVariant();

	isResolving = true;
	QVariant result = computeFormula(formula(), tableWidget(), this);
	isResolving = false;
	return result;
}

QVariant NQgridWidgetItem::computeFormula(const QString &formula,
	const QTableWidget *widget,
	const QTableWidgetItem *self)
{
	// check if the s tring is actually a formula or not
	QStringList list = formula.split(' ');
	if (list.isEmpty() || !widget)
		return formula; // it is a normal string

	QString op = list.value(0).toLower();

	int firstRow = -1;
	int firstCol = -1;
	int secondRow = -1;
	int secondCol = -1;

	if (list.count() > 1)
		decode_position(list.value(1), &firstRow, &firstCol);

	if (list.count() > 2)
		decode_position(list.value(2), &secondRow, &secondCol);

	const QTableWidgetItem *start = widget->item(firstRow, firstCol);
	const QTableWidgetItem *end = widget->item(secondRow, secondCol);

	int firstVal = start ? start->text().toInt() : 0;
	int secondVal = end ? end->text().toInt() : 0;

	QVariant result;
	if (op == "sum") {
		int sum = 0;
		for (int r = firstRow; r <= secondRow; ++r) {
			for (int c = firstCol; c <= secondCol; ++c) {
				const QTableWidgetItem *tableItem = widget->item(r, c);
				if (tableItem && tableItem != self)
					sum += tableItem->text().toInt();
			}
		}

		result = sum;
	}
	else if (op == "+") {
		result = (firstVal + secondVal);
	}
	else if (op == "-") {
		result = (firstVal - secondVal);
	}
	else if (op == "*") {
		result = (firstVal * secondVal);
	}
	else if (op == "/") {
		if (secondVal == 0)
			result = QString("nan");
		else
			result = (firstVal / secondVal);
	}
	else if (op == "=") {
		if (start)
			result = start->text();
	}
	else {
		result = formula;
	}

	return result;
}