#include "filteritem.h"
#include "filterview.h"

ConditionItem::ConditionItem(const cvar::Field &field, Operator::Type op, const QVariant &value)
    :QTreeWidgetItem(FilterView::ConditionType), mField(field), mOperator(op), mValue(value)
{
    updateItem();


}

void ConditionItem::setField(const cvar::Field &f)
{
    mField = f;
    updateItem();
}

void ConditionItem::setOperator(Operator::Type op)
{
    mOperator = op;
    updateItem();
}

void ConditionItem::setValue(const QVariant &value)
{
    mValue = value;
    updateItem();
}

const cvar::Field& ConditionItem::field() const
{
    return mField;
}

QString ConditionItem::operatorName() const
{
    return Operator::symbol(mOperator);
}

Operator::Type ConditionItem::currentOperator() const
{
    return mOperator;
}

QVariant ConditionItem::value() const
{
    return mValue;
}

QString ConditionItem::expression() const
{
    return QString("%1 %2 %3").arg(mField.expression(), Operator::symbol(mOperator), mValue.toString());
}

void ConditionItem::updateItem()
{
    setText(0, field().name());
    setText(1, operatorName());
    setText(2, value().toString());

    setToolTip(0, mField.description());


}
