//-----------------------------------------------------------------------------
// File: SubspaceMapReader.cpp
//-----------------------------------------------------------------------------
// Project: Kactus 2
// Author: Mikko Teuho
// Date: 21.01.2022
//
// Description:
// Reader for ipxact:subspaceMap element.
//-----------------------------------------------------------------------------

#include "SubspaceMapReader.h"

#include <IPXACTmodels/common/NameGroupReader.h>
#include <IPXACTmodels/Component/SubSpaceMap.h>

//-----------------------------------------------------------------------------
// Function: SubspaceMapReader::createMemoryBlockFrom()
//-----------------------------------------------------------------------------
IPXACTMODELS_EXPORT QSharedPointer<SubSpaceMap> SubspaceMapReader::createSubspaceMapFrom(QDomNode const& subspaceMapNode, Document::Revision docRevision)
{
    QSharedPointer<SubSpaceMap> newSubspaceMap(new SubSpaceMap());

    Details::parseAttributes(subspaceMapNode, newSubspaceMap);

    MemoryBlockBaseReader::parseNameGroup(subspaceMapNode, newSubspaceMap);

    MemoryBlockBaseReader::parsePresence(subspaceMapNode, newSubspaceMap);

    MemoryBlockBaseReader::parseBaseAddress(subspaceMapNode, newSubspaceMap);

    MemoryBlockBaseReader::parseParameters(subspaceMapNode, newSubspaceMap, docRevision);

    CommonItemsReader::parseVendorExtensions(subspaceMapNode, newSubspaceMap);

    return newSubspaceMap;
}

//-----------------------------------------------------------------------------
// Function: SubspaceMapReader::Details::parseAttributes()
//-----------------------------------------------------------------------------
void SubspaceMapReader::Details::parseAttributes(QDomNode const& subspaceMapNode,
    QSharedPointer<SubSpaceMap> newSubspaceMap)
{
    QDomNamedNodeMap attributes = subspaceMapNode.attributes();
    for (int j = 0; j < attributes.size(); ++j)
    {
        QString attributeName = attributes.item(j).nodeName();
        QString attributeValue = attributes.item(j).nodeValue();

        if (attributeName == QStringLiteral("masterRef"))
        {
            newSubspaceMap->setMasterReference(attributeValue);
        }
        else if (attributeName == QStringLiteral("segmentRef"))
        {
            newSubspaceMap->setSegmentReference(attributeValue);
        }
    }

}
