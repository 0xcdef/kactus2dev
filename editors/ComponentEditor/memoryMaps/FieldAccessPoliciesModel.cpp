//-----------------------------------------------------------------------------
// File: FieldAccessPoliciesModel.h
//-----------------------------------------------------------------------------
// Project: Kactus 2
// Author: Anton Hagqvist
// Date: 8.8.2023
//
// Description:
// Model to manage the field access policies of a field.
//-----------------------------------------------------------------------------

#include "FieldAccessPoliciesModel.h"
#include "FieldAccessPolicyColumns.h"

#include <common/KactusColors.h>

//-----------------------------------------------------------------------------
// Function: FieldAccessPoliciesModel::FieldAccessPoliciesModel()
//-----------------------------------------------------------------------------
FieldAccessPoliciesModel::FieldAccessPoliciesModel(QString const& fieldName, 
    QSharedPointer<ParameterFinder> parameterFinder, FieldInterface* fieldInterface, QObject* parent):
ReferencingTableModel(parameterFinder, parent),
ParameterizableTable(parameterFinder),
fieldInterface_(fieldInterface),
fieldName_(fieldName.toStdString())
{

}

//-----------------------------------------------------------------------------
// Function: FieldAccessPoliciesModel::rowCount()
//-----------------------------------------------------------------------------
int FieldAccessPoliciesModel::rowCount(const QModelIndex& parent /*= QModelIndex()*/) const
{
    if (parent.isValid())
    {
        return 0;
    }

    return fieldInterface_->getAccessPolicyCount(fieldName_);
}

//-----------------------------------------------------------------------------
// Function: FieldAccessPoliciesModel::columnCount()
//-----------------------------------------------------------------------------
int FieldAccessPoliciesModel::columnCount(const QModelIndex& parent /*= QModelIndex()*/) const
{
    if (parent.isValid())
    {
        return 0;
    }

    return FieldAccessPolicyColumns::COUNT;
}

//-----------------------------------------------------------------------------
// Function: FieldAccessPoliciesModel::flags()
//-----------------------------------------------------------------------------
Qt::ItemFlags FieldAccessPoliciesModel::flags(const QModelIndex& index) const
{
    if (!index.isValid())
    {
        return Qt::NoItemFlags;
    }

    // Disable editing until editor is made.
    else if (index.column() == FieldAccessPolicyColumns::TYPE_DEFINITION)
    {
        return Qt::NoItemFlags;
    }

    // Disable write constraint min/max, when that option is not set.
    else if ((index.column() == FieldAccessPolicyColumns::WRITE_CONSTRAINT_MAXIMUM ||
        index.column() == FieldAccessPolicyColumns::WRITE_CONSTRAINT_MINIMUM) &&
        QString::fromStdString(fieldInterface_->getWriteConstraint(
            fieldName_, index.row())) != QStringLiteral("Set minimum and maximum limits"))
    {
        return Qt::NoItemFlags;
    }

    else if (index.column() == FieldAccessPolicyColumns::TEST_CONSTRAINT &&
        fieldInterface_->getTestableBool(fieldName_, index.row()) == false)
    {
        return Qt::NoItemFlags;
    }

    return Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemIsEditable;
}

//-----------------------------------------------------------------------------
// Function: FieldAccessPoliciesModel::headerData()
//-----------------------------------------------------------------------------
QVariant FieldAccessPoliciesModel::headerData(int section, Qt::Orientation orientation, int role /*= Qt::DisplayRole*/) const
{
    if (orientation != Qt::Horizontal)
    {
        return QVariant();
    }
    if (Qt::DisplayRole == role)
    {
        if (section == FieldAccessPolicyColumns::MODE)
        {
            return QStringLiteral("Mode(s)");
        }
        else if (section == FieldAccessPolicyColumns::TYPE_DEFINITION)
        {
            return QStringLiteral("Type definition");
        }
        else if (section == FieldAccessPolicyColumns::ACCESS)
        {
            return QStringLiteral("Access");
        }
        else if (section == FieldAccessPolicyColumns::MODIFIED_WRITE)
        {
            return QStringLiteral("Modified write\nvalue");
        }
        else if (section == FieldAccessPolicyColumns::WRITE_VALUE_CONSTRAINT)
        {
            return QStringLiteral("Write value\nconstraint");
        }
        else if (section == FieldAccessPolicyColumns::READ_ACTION)
        {
            return QStringLiteral("Read action");
        }
        else if (section == FieldAccessPolicyColumns::READ_RESPONSE)
        {
            return QStringLiteral("Read response") + getExpressionSymbol();
        }
        else if (section == FieldAccessPolicyColumns::TESTABLE)
        {
            return QStringLiteral("Testable");
        }
        else if (section == FieldAccessPolicyColumns::TEST_CONSTRAINT)
        {
            return QStringLiteral("Test constraint");
        }
        else if (section == FieldAccessPolicyColumns::RESERVED)
        {
            return QStringLiteral("Reserved") + getExpressionSymbol();
        }
        else if (section == FieldAccessPolicyColumns::WRITE_CONSTRAINT_MINIMUM)
        {
            return QStringLiteral("Write constraint\nminimum") + getExpressionSymbol();
        }
        else if (section == FieldAccessPolicyColumns::WRITE_CONSTRAINT_MAXIMUM)
        {
            return QStringLiteral("Write constraint\nmaximum") + getExpressionSymbol();
        }
    }

    return QVariant();
}

//-----------------------------------------------------------------------------
// Function: FieldAccessPoliciesModel::data()
//-----------------------------------------------------------------------------
QVariant FieldAccessPoliciesModel::data(const QModelIndex& index, int role /*= Qt::DisplayRole*/) const
{
    if (role == Qt::DisplayRole)
    {
        if (isValidExpressionColumn(index))
        {
            return formattedExpressionForIndex(index);
        }
        
        return valueForIndex(index);
    }

    else if (role == Qt::BackgroundRole)
    {
        if (index.flags() == Qt::NoItemFlags)
        {
            return KactusColors::DISABLED_FIELD;
        }

        return KactusColors::REGULAR_FIELD;
    }

    else if (role == Qt::ToolTipRole)
    {
        return valueForIndex(index);
    }

    else if (role == Qt::ForegroundRole)
    {
        return blackForValidOrRedForInvalidIndex(index);
    }

    else if (role == Qt::EditRole)
    {
        if (isValidExpressionColumn(index))
        {
            return expressionForIndex(index);
        }
    }

    else if (role == Qt::UserRole)
    {
        // Data for mode ref editor.
        if (index.column() == FieldAccessPolicyColumns::MODE)
        {
            auto const& modeRefsList = fieldInterface_->getModeRefs(fieldName_, index.row());

            QList<QPair<QString, int> > modeRefs;
            for (auto const& [reference, priority] : modeRefsList)
            {
                modeRefs.append(QPair<QString, int>({ QString::fromStdString(reference), priority }));
            }

            QVariant modeRefsVariant;
            modeRefsVariant.setValue(modeRefs);
            return modeRefsVariant;
        }
    }

    return QVariant();
}

//-----------------------------------------------------------------------------
// Function: FieldAccessPoliciesModel::setData()
//-----------------------------------------------------------------------------
bool FieldAccessPoliciesModel::setData(const QModelIndex& index, const QVariant& value, int role /*= Qt::EditRole*/)
{
    if (!index.isValid() || index.row() < 0 || 
        index.row() >= fieldInterface_->getAccessPolicyCount(fieldName_) ||
        !(flags(index) & Qt::ItemIsEditable) || role != Qt::EditRole)
    {
        return false;
    }

    if (index.column() == FieldAccessPolicyColumns::MODE)
    {
        auto modeRefs = value.value<QList<QPair<QString, int> > >();

        std::vector<std::pair<std::string, int> > modeRefsStdType;
        for (auto const& [reference, priority] : modeRefs)
        {
            modeRefsStdType.emplace_back(reference.toStdString(), priority);
        }

        fieldInterface_->setModeRefs(fieldName_, index.row(), modeRefsStdType);
    }

    else if (index.column() == FieldAccessPolicyColumns::ACCESS)
    {
        fieldInterface_->setAccess(fieldName_, value.toString().toStdString(), index.row());
    }

    else if (index.column() == FieldAccessPolicyColumns::MODIFIED_WRITE)
    {
        fieldInterface_->setModifiedWrite(fieldName_, value.toString().toStdString(), index.row());
    }

    else if (index.column() == FieldAccessPolicyColumns::READ_ACTION)
    {
        fieldInterface_->setReadAction(fieldName_, value.toString().toStdString(), index.row());
    }

    else if (index.column() == FieldAccessPolicyColumns::READ_RESPONSE)
    {
        fieldInterface_->setReadResponse(fieldName_, index.row(), value.toString().toStdString());
    }

    else if (index.column() == FieldAccessPolicyColumns::TESTABLE)
    {
        fieldInterface_->setTestable(fieldName_, value.toString().toStdString(), index.row());
    }

    else if (index.column() == FieldAccessPolicyColumns::TEST_CONSTRAINT)
    {
        fieldInterface_->setTestConstraint(fieldName_, value.toString().toStdString(), index.row());
    }

    else if (index.column() == FieldAccessPolicyColumns::RESERVED)
    {
        fieldInterface_->setReserved(fieldName_, value.toString().toStdString(), index.row());
    }

    else if (index.column() == FieldAccessPolicyColumns::WRITE_VALUE_CONSTRAINT)
    {
        auto oldValue = fieldInterface_->getWriteConstraint(fieldName_, index.row());
        auto newValue = value.toString().toStdString();

        // To prevent clearing the min/max fields after clicking out of editor, even when selection isn't changed.
        if (oldValue != newValue)
        {
            fieldInterface_->setWriteConstraint(fieldName_, value.toString().toStdString(), index.row());
        }
    }

    else if (index.column() == FieldAccessPolicyColumns::WRITE_CONSTRAINT_MINIMUM)
    {
        fieldInterface_->setWriteConstraintMinimum(fieldName_, value.toString().toStdString(), index.row());
    }

    else if (index.column() == FieldAccessPolicyColumns::WRITE_CONSTRAINT_MAXIMUM)
    {
        fieldInterface_->setWriteConstraintMaximum(fieldName_, value.toString().toStdString(), index.row());
    }

    emit dataChanged(index, index);
    return true;
}

//-----------------------------------------------------------------------------
// Function: FieldAccessPoliciesModel::onAddRow()
//-----------------------------------------------------------------------------
void FieldAccessPoliciesModel::onAddRow(QModelIndex const& index)
{
    int lastRow = fieldInterface_->getAccessPolicyCount(fieldName_);

    beginInsertRows(QModelIndex(), lastRow, lastRow);
    fieldInterface_->addFieldAccessPolicy(fieldName_);
    endInsertRows();

    emit invalidateFilter();
    emit contentChanged();
}

//-----------------------------------------------------------------------------
// Function: FieldAccessPoliciesModel::onRemoveItem()
//-----------------------------------------------------------------------------
void FieldAccessPoliciesModel::onRemoveItem(QModelIndex const& index)
{
    if (!index.isValid() || index.row() < 0 ||
        index.row() >= fieldInterface_->getAccessPolicyCount(fieldName_))
    {
        return;
    }

    beginRemoveRows(QModelIndex(), index.row(), index.row());
    fieldInterface_->removeFieldAccessPolicy(fieldName_, index.row());
    endRemoveRows();

    emit invalidateFilter();
    emit contentChanged();
}

//-----------------------------------------------------------------------------
// Function: FieldAccessPoliciesModel::getAllReferencesToIdInItemOnRow()
//-----------------------------------------------------------------------------
int FieldAccessPoliciesModel::getAllReferencesToIdInItemOnRow(const int& row, QString const& valueID) const
{
    return fieldInterface_->getAllReferencesToIdInFieldAccessPolicy(fieldName_, row, valueID.toStdString());
}

//-----------------------------------------------------------------------------
// Function: FieldAccessPoliciesModel::isValidExpressionColumn()
//-----------------------------------------------------------------------------
bool FieldAccessPoliciesModel::isValidExpressionColumn(QModelIndex const& index) const
{
    int column = index.column();
    return column == FieldAccessPolicyColumns::READ_RESPONSE ||
        column == FieldAccessPolicyColumns::RESERVED ||
        column == FieldAccessPolicyColumns::WRITE_CONSTRAINT_MAXIMUM ||
        column == FieldAccessPolicyColumns::WRITE_CONSTRAINT_MINIMUM;
}

//-----------------------------------------------------------------------------
// Function: FieldAccessPoliciesModel::expressionOrValueForIndex()
//-----------------------------------------------------------------------------
QVariant FieldAccessPoliciesModel::expressionOrValueForIndex(QModelIndex const& index) const
{
    if (isValidExpressionColumn(index))
    {
        return expressionForIndex(index);
    }

    return valueForIndex(index);
}

//-----------------------------------------------------------------------------
// Function: FieldAccessPoliciesModel::validateIndex()
//-----------------------------------------------------------------------------
bool FieldAccessPoliciesModel::validateIndex(QModelIndex const& index) const
{
    if (int column = index.column(); 
        column == FieldAccessPolicyColumns::MODE)
    {
        return fieldInterface_->hasValidAccessPolicyModeRefs(fieldName_, index.row());
    }
    
    else if (column == FieldAccessPolicyColumns::ACCESS)
    {
        return fieldInterface_->hasValidAccess(fieldName_, index.row());
    }
    
    else if (column == FieldAccessPolicyColumns::READ_RESPONSE)
    {
        return fieldInterface_->hasValidReadResponse(fieldName_, index.row());
    }
    
    else if (column == FieldAccessPolicyColumns::RESERVED)
    {
        return fieldInterface_->hasValidReserved(fieldName_, index.row());
    }

    else if (column == FieldAccessPolicyColumns::WRITE_VALUE_CONSTRAINT ||
        column == FieldAccessPolicyColumns::WRITE_CONSTRAINT_MINIMUM ||
        column == FieldAccessPolicyColumns::WRITE_CONSTRAINT_MAXIMUM)
    {
        return fieldInterface_->hasValidWriteValueConstraint(fieldName_, index.row());
    }

    return true;
}

//-----------------------------------------------------------------------------
// Function: FieldAccessPoliciesModel::valueForIndex()
//-----------------------------------------------------------------------------
QVariant FieldAccessPoliciesModel::valueForIndex(QModelIndex const& index) const
{
    if (index.column() == FieldAccessPolicyColumns::ACCESS)
    {
        return QString::fromStdString(fieldInterface_->getAccessString(fieldName_, index.row()));
    }

    else if (index.column() == FieldAccessPolicyColumns::MODE)
    {
        auto const& modeRefsList = fieldInterface_->getModeRefs(fieldName_, index.row());
        QStringList list;
        for (auto const& [reference, priority] : modeRefsList)
        {
            list.append(QString::fromStdString(reference));
        }

        return list.join(", ");
    }

    else if (index.column() == FieldAccessPolicyColumns::MODIFIED_WRITE)
    {
        return QString::fromStdString(fieldInterface_->getModifiedWriteString(fieldName_, index.row()));
    }

    else if (index.column() == FieldAccessPolicyColumns::READ_ACTION)
    {
        return QString::fromStdString(fieldInterface_->getReadActionString(fieldName_, index.row()));
    }

    else if (index.column() == FieldAccessPolicyColumns::READ_RESPONSE)
    {
        return QString::fromStdString(fieldInterface_->getReadResponseValue(fieldName_, index.row()));
    }

    else if (index.column() == FieldAccessPolicyColumns::TESTABLE)
    {
        return QString::fromStdString(fieldInterface_->getTestableValue(fieldName_, index.row()));
    }

    else if (index.column() == FieldAccessPolicyColumns::TEST_CONSTRAINT)
    {
        return QString::fromStdString(fieldInterface_->getTestConstraintString(fieldName_, index.row()));
    }

    else if (index.column() == FieldAccessPolicyColumns::RESERVED)
    {
        return QString::fromStdString(fieldInterface_->getReservedValue(fieldName_, index.row()));
    }

    else if (index.column() == FieldAccessPolicyColumns::WRITE_VALUE_CONSTRAINT)
    {
        return QString::fromStdString(fieldInterface_->getWriteConstraint(fieldName_, index.row()));
    }

    else if (index.column() == FieldAccessPolicyColumns::WRITE_CONSTRAINT_MINIMUM)
    {
        return QString::fromStdString(fieldInterface_->getWriteConstraintMinimumValue(fieldName_, index.row()));
    }

    else if (index.column() == FieldAccessPolicyColumns::WRITE_CONSTRAINT_MAXIMUM)
    {
        return QString::fromStdString(fieldInterface_->getWriteConstraintMaximumValue(fieldName_, index.row()));
    }

    return QVariant();
}

//-----------------------------------------------------------------------------
// Function: FieldAccessPoliciesModel::expressionForIndex()
//-----------------------------------------------------------------------------
QVariant FieldAccessPoliciesModel::expressionForIndex(QModelIndex const& index) const
{
    if (index.column() == FieldAccessPolicyColumns::READ_RESPONSE)
    {
        return QString::fromStdString(fieldInterface_->getReadResponseExpression(fieldName_, index.row()));
    }

    else if (index.column() == FieldAccessPolicyColumns::RESERVED)
    {
        return QString::fromStdString(fieldInterface_->getReservedExpression(fieldName_, index.row()));
    }
    
    else if (index.column() == FieldAccessPolicyColumns::WRITE_CONSTRAINT_MAXIMUM)
    {
        return QString::fromStdString(fieldInterface_->getWriteConstraintMaximumExpression(fieldName_, index.row()));
    }

    else if (index.column() == FieldAccessPolicyColumns::WRITE_CONSTRAINT_MINIMUM)
    {
        return QString::fromStdString(fieldInterface_->getWriteConstraintMinimumExpression(fieldName_, index.row()));
    }

    return QVariant();
}

//-----------------------------------------------------------------------------
// Function: FieldAccessPoliciesModel::formattedExpressionForIndex()
//-----------------------------------------------------------------------------
QVariant FieldAccessPoliciesModel::formattedExpressionForIndex(QModelIndex const& index) const
{
    if (index.column() == FieldAccessPolicyColumns::READ_RESPONSE)
    {
        return QString::fromStdString(fieldInterface_->getReadResponseFormattedExpression(fieldName_, index.row()));
    }

    else if (index.column() == FieldAccessPolicyColumns::RESERVED)
    {
        return QString::fromStdString(fieldInterface_->getReservedFormattedExpression(fieldName_, index.row()));
    }

    else if (index.column() == FieldAccessPolicyColumns::WRITE_CONSTRAINT_MAXIMUM)
    {
        return QString::fromStdString(fieldInterface_->getWriteConstraintMaximumFormattedExpression(fieldName_, index.row()));
    }

    else if (index.column() == FieldAccessPolicyColumns::WRITE_CONSTRAINT_MINIMUM)
    {
        return QString::fromStdString(fieldInterface_->getWriteConstraintMinimumFormattedExpression(fieldName_, index.row()));
    }

    return QVariant();
}

