//-----------------------------------------------------------------------------
// File: AdHocTiedValueCommand.cpp
//-----------------------------------------------------------------------------
// Project: Kactus2
// Author: Mikko Teuho
// Date: 03.05.2017
//
// Description:
// Parent undo command for ad hoc tied value commands.
//-----------------------------------------------------------------------------

#include "AdHocTiedValueCommand.h"

#include <IPXACTmodels/Design/Design.h>

#include <editors/HWDesign/AdHocItem.h>
#include <editors/HWDesign/HWDesignDiagram.h>
#include <editors/HWDesign/HWComponentItem.h>

//-----------------------------------------------------------------------------
// Function: AdHocTiedValueCommand::AdHocTiedValueCommand()
//-----------------------------------------------------------------------------
AdHocTiedValueCommand::AdHocTiedValueCommand(AdHocItem* portItem,
    QSharedPointer<AdHocConnection> tiedValueConnection, HWDesignDiagram* designDiagram):
tiedValueConnection_(tiedValueConnection),
containingDesign_(designDiagram->getDesign()),
referencedPort_()
{
    if (!tiedValueConnection_)
    {
        tiedValueConnection_ = createConnectionForTiedValue(portItem);
    }
    else
    {
        setupReferencedPort(portItem->name().toStdString());
    }
}

//-----------------------------------------------------------------------------
// Function: AdHocTiedValueCommand::createConnectionForTiedValue()
//-----------------------------------------------------------------------------
QSharedPointer<AdHocConnection> AdHocTiedValueCommand::createConnectionForTiedValue(AdHocItem* portItem)
{
    std::string connectionName = createNameForTiedValueConnection(portItem);

    QSharedPointer<AdHocConnection> connection (new AdHocConnection(connectionName));

    QSharedPointer<PortReference> portReference (new PortReference(portItem->name().toStdString()));

    ComponentItem* containingComponent = portItem->encompassingComp();
    if (containingComponent)
    {
        portReference->setComponentRef(containingComponent->name());
        connection->getInternalPortReferences()->append(portReference);
    }
    else
    {
        connection->getExternalPortReferences()->append(portReference);
    }

    referencedPort_ = portReference;

    return connection;
}

//-----------------------------------------------------------------------------
// Function: AdHocTiedValueCommand::createNameForTiedValueConnection()
//-----------------------------------------------------------------------------
std::string AdHocTiedValueCommand::createNameForTiedValueConnection(AdHocItem* portItem) const
{
    ComponentItem* containingComponent = portItem->encompassingComp();

    auto instanceName = std::string();

    if (containingComponent)
    {
        instanceName = containingComponent->name();
        instanceName.append("_");
    }

    std::string portName = portItem->name().toStdString();

    return instanceName + portName + "_to_tiedValue";
}

//-----------------------------------------------------------------------------
// Function: AdHocTiedValueCommand::~AdHocTiedValueCommand()
//-----------------------------------------------------------------------------
AdHocTiedValueCommand::~AdHocTiedValueCommand()
{

}

//-----------------------------------------------------------------------------
// Function: AdHocTiedValueCommand::getTiedValueConnection()
//-----------------------------------------------------------------------------
QSharedPointer<AdHocConnection> AdHocTiedValueCommand::getTiedValueConnection() const
{
    return tiedValueConnection_;
}

//-----------------------------------------------------------------------------
// Function: AdHocTiedValueCommand::setupReferencedPort()
//-----------------------------------------------------------------------------
void AdHocTiedValueCommand::setupReferencedPort(std::string const& portName)
{
    for (QSharedPointer<PortReference> externalPort : *tiedValueConnection_->getExternalPortReferences())
    {
        if (externalPort->getPortRef().compare(portName) == 0)
        {
            referencedPort_ = externalPort;
            return;
        }
    }

    for (QSharedPointer<PortReference> internalPort : *tiedValueConnection_->getInternalPortReferences())
    {
        if (internalPort->getPortRef().compare(portName) == 0)
        {
            referencedPort_ = internalPort;
            return;
        }
    }
}

//-----------------------------------------------------------------------------
// Function: AdHocTiedValueCommand::getReferencedPort()
//-----------------------------------------------------------------------------
QSharedPointer<PortReference> AdHocTiedValueCommand::getReferencedPort() const
{
    return referencedPort_;
}

//-----------------------------------------------------------------------------
// Function: AdHocTiedValueCommand::addOrRemoveConnection()
//-----------------------------------------------------------------------------
void AdHocTiedValueCommand::addOrRemoveTiedValueConnection()
{
    QSharedPointer<PartSelect> portPartSelect = referencedPort_->getPartSelect();

    if (containingDesign_->getAdHocConnections()->contains(tiedValueConnection_) &&
        tiedValueConnection_->getTiedValue().empty() && (!portPartSelect ||
        (portPartSelect && portPartSelect->getLeftRange().isEmpty() && portPartSelect->getRightRange().isEmpty())))
    {
        containingDesign_->getAdHocConnections()->removeAll(tiedValueConnection_);
    }
    else if (!containingDesign_->getAdHocConnections()->contains(tiedValueConnection_))
    {
        containingDesign_->getAdHocConnections()->append(tiedValueConnection_);
    }
}
