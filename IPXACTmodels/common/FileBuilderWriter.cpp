//-----------------------------------------------------------------------------
// File: FileBuilderWriter.cpp
//-----------------------------------------------------------------------------
// Project: Kactus 2
// Author: Mikko Teuho
// Date: 22.09.2015
//
// Description:
// Writer class for fileBuilder element.
//-----------------------------------------------------------------------------

#include "FileBuilderWriter.h"
#include "FileBuilder.h"
#include "FileType.h"

#include <IPXACTmodels/Component/FileWriter.h>

//-----------------------------------------------------------------------------
// Function: FileBuilderWriter::writeDefaultFileBuilder()
//-----------------------------------------------------------------------------
void FileBuilderWriter::writeDefaultFileBuilder(QXmlStreamWriter& writer, QSharedPointer<FileBuilder> fileBuilder,
    Document::Revision docRevision)
{
    writer.writeStartElement(QStringLiteral("ipxact:defaultFileBuilder"));

    FileWriter::writeFileType(writer, fileBuilder->getFileType(), docRevision);

    Details::writeBuildModel(writer, fileBuilder);

    if (docRevision == Document::Revision::Std14)
    {
        CommonItemsWriter::writeVendorExtensions(writer, fileBuilder);
    }

    writer.writeEndElement(); // ipxact:defaultFileBuilder
}


//-----------------------------------------------------------------------------
// Function: FileBuilderWriter::writeBuildCommand()
//-----------------------------------------------------------------------------
void FileBuilderWriter::Details::writeBuildModel(QXmlStreamWriter& writer, QSharedPointer<FileBuilder> fileBuilder)
{
    writer.writeTextElement(QStringLiteral("ipxact:command"), fileBuilder->getCommand());

    if (!fileBuilder->getFlags().isEmpty())
    {
        writer.writeTextElement(QStringLiteral("ipxact:flags"), fileBuilder->getFlags());
    }
    if (!fileBuilder->getReplaceDefaultFlags().isEmpty())
    {
        writer.writeTextElement(QStringLiteral("ipxact:replaceDefaultFlags"), fileBuilder->getReplaceDefaultFlags());
    }
}