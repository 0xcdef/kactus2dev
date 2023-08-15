//-----------------------------------------------------------------------------
// File: SingleModeEditor.cpp
//-----------------------------------------------------------------------------
// Project: Kactus2
// Author: Esko Pekkarinen
// Date: 08.08.2023
//
// Description:
// Editor to edit a single mode in a component.
//-----------------------------------------------------------------------------

#include "SingleModeEditor.h"

#include <IPXACTmodels/Component/Component.h>
#include <IPXACTmodels/Component/Mode.h>

#include <KactusAPI/include/LibraryInterface.h>

#include <editors/ComponentEditor/memoryMaps/ExpressionProxyModel.h>
#include <editors/ComponentEditor/parameters/ComponentParameterModel.h>
#include <editors/ComponentEditor/common/ParameterCompleter.h>

#include <QScrollArea>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLabel>

//-----------------------------------------------------------------------------
// Function: SingleModeEditor::SingleModeEditor()
//-----------------------------------------------------------------------------
SingleModeEditor::SingleModeEditor(QSharedPointer<Component> component,
    QSharedPointer<Mode> mode,
    LibraryInterface* libHandler,
    ExpressionSet expressions,
    QWidget* parent) :
    ItemEditor(component, libHandler, parent),
    mode_(mode),
    nameEditor_(mode, component->getRevision(), this, tr("Mode name and description")),
    conditionEditor_(this),
    portSliceEditor_(component, mode, libHandler, expressions, this)
{
    connect(&nameEditor_, SIGNAL(contentChanged()), this, SIGNAL(contentChanged()), Qt::UniqueConnection);
    connect(&portSliceEditor_, SIGNAL(contentChanged()), this, SIGNAL(contentChanged()), Qt::UniqueConnection);

    setupLayout();
}

//-----------------------------------------------------------------------------
// Function: SingleModeEditor::refresh()
//-----------------------------------------------------------------------------
void SingleModeEditor::refresh()
{
    nameEditor_.refresh();
}

//-----------------------------------------------------------------------------
// Function: SingleModeEditor::setupLayout()
//-----------------------------------------------------------------------------
void SingleModeEditor::setupLayout()
{
    auto scrollArea = new QScrollArea(this);
    scrollArea->setWidgetResizable(true);
    scrollArea->setFrameShape(QFrame::NoFrame);

    auto scrollLayout = new QHBoxLayout(this);
    scrollLayout->addWidget(scrollArea);
    scrollLayout->setContentsMargins(0, 0, 0, 0);

    auto topWidget = new QWidget(scrollArea);
    topWidget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    scrollArea->setWidget(topWidget);

    auto conditionGroup = new QGroupBox(tr("Mode condition"), this);
    conditionGroup->setFlat(true);

    auto conditionLayout = new QHBoxLayout(conditionGroup);
    conditionLayout->addWidget(new QLabel(tr("Condition:"), this));
    conditionLayout->addWidget(&conditionEditor_, 1);

    auto portsGroup = new QGroupBox(tr("Condition ports"), this);
    portsGroup->setFlat(true);

    auto portLayout = new QHBoxLayout(portsGroup);
    portLayout->addWidget(&portSliceEditor_);

    auto fieldsGroup = new QGroupBox(tr("Condition fields"), this);
    fieldsGroup->setFlat(true);

    auto topLayout = new QGridLayout(topWidget);
    topLayout->addWidget(&nameEditor_, 0, 0, 1, 1);
    topLayout->addWidget(conditionGroup, 1, 0, 1, 1);
    topLayout->addWidget(portsGroup, 2, 0, 1, 1);
    topLayout->addWidget(fieldsGroup, 3, 0, 1, 1);
}

//-----------------------------------------------------------------------------
// Function: SingleModeEditor::showEvent()
//-----------------------------------------------------------------------------
void SingleModeEditor::showEvent(QShowEvent * event)
{
    QWidget::showEvent(event);

    emit helpUrlRequested("componenteditor/mode2022.html");
}