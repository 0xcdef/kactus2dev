//-----------------------------------------------------------------------------
// File: ModuleParameterEditor.h
//-----------------------------------------------------------------------------
// Project: Kactus 2
// Author: Esko Pekkarinen
// Date: 19.02.2015
//
// Description:
// Editor for module parameters.
//-----------------------------------------------------------------------------

#ifndef MODULEPARAMETEREDITOR_H
#define MODULEPARAMETEREDITOR_H

#include <QGroupBox>
#include <QSortFilterProxyModel>

class Choice;
class ModuleParameter;
class ModuleParameterModel;
class ParameterFinder;
class ExpressionFormatter;

//-----------------------------------------------------------------------------
//! Editor for module parameters.
//-----------------------------------------------------------------------------
class ModuleParameterEditor : public QGroupBox
{
    Q_OBJECT
public:

    /*!
     *  The constructor.
     *
     *      @param [in] parameters              The selected module parameters.
     *      @param [in] componentChoices        The component choices.
     *      @param [in] parameterFinder         The selected parameter finder.
     *      @param [in] expressionFormatter     The selected expression formatter.
     *      @param [in] parent                  The owner of this editor.
     */
//     ModuleParameterEditor(QSharedPointer<QList<QSharedPointer<ModelParameter> > > parameters,
    ModuleParameterEditor(QSharedPointer<QList<QSharedPointer<ModuleParameter> > > parameters,
        QSharedPointer<QList<QSharedPointer<Choice> > > componentChoices,
        QSharedPointer<ParameterFinder> parameterFinder,
        QSharedPointer<ExpressionFormatter> expressionFormatter,
        QWidget* parent);

	//! The destructor.
	~ModuleParameterEditor();

    /*!
     *  Checks if the contents of the editor are valid.
     *
     *      @return True, if contents is valid, otherwise false.
     */
    bool isValid() const;

    /*!
     *  Refresh the contents of the editor.
     */
    void refresh();

signals:
    //! Emitted when contents of the editor change.
	void contentChanged();

	//! Prints an error message to the user.
	void errorMessage(const QString& msg) const;

	//! Prints a notification to user.
	void noticeMessage(const QString& msg) const;

    /*!
     *  Increase the amount of references to the parameter corresponding to the id.
     *
     *      @param [in] id      The id of the parameter being searched for.
     */
    void increaseReferences(QString id);

    /*!
     *  Decrease the amount of references to the parameter corresponding to the id.
     *
     *      @param [in] id      The id of the parameter being searched for.
     */
    void decreaseReferences(QString id);

    /*!
     *  Open the reference tree of the parameter with the id.
     *
     *      @param [in] id      The id of the parameter.
     */
    void openReferenceTree(QString const& id) const;

private:

	// Disable copying.
	ModuleParameterEditor(ModuleParameterEditor const& rhs);
	ModuleParameterEditor& operator=(ModuleParameterEditor const& rhs);
  
    //! The used sort filter proxy.
    QSortFilterProxyModel* proxy_;

    //! Used for editing model parameters.
    ModuleParameterModel* model_;
};

#endif // MODULEPARAMETEREDITOR_H