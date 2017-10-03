//-----------------------------------------------------------------------------
// File: DesignWidgetFactoryImplementation.h
//-----------------------------------------------------------------------------
// Project: Kactus2
// Author: Mikko Teuho
// Date: 11.02.2015
//
// Description:
// Class for design widget factory.
//-----------------------------------------------------------------------------

#include "DesignWidgetFactoryImplementation.h"

#include <designEditors/HWDesign/HWDesignWidget.h>

//-----------------------------------------------------------------------------
// Function: DesignWidgetFactoryImplementation::DesignWidgetFactoryImplementation()
//-----------------------------------------------------------------------------
DesignWidgetFactoryImplementation::DesignWidgetFactoryImplementation(LibraryInterface* libInterface,
    QSharedPointer<MultipleParameterFinder> designParameterReferenceFinder):
libInterface_(libInterface),
designParameterReferenceFinder_(designParameterReferenceFinder)
{

}

//-----------------------------------------------------------------------------
// Function: DesignWidgetFactoryImplementation::~DesignWidgetFactoryImplementation()
//-----------------------------------------------------------------------------
DesignWidgetFactoryImplementation::~DesignWidgetFactoryImplementation()
{

}

//-----------------------------------------------------------------------------
// Function: DesignWidgetFactoryImplementation::makeHWDesignWidget()
//-----------------------------------------------------------------------------
DesignWidget* DesignWidgetFactoryImplementation::makeHWDesignWidget(QWidget* parent /* = 0 */)
{
    DesignWidget* hwDesignWidget (new HWDesignWidget(libInterface_, designParameterReferenceFinder_, parent));

    return hwDesignWidget;
}
