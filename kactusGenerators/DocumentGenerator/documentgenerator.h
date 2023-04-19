//-----------------------------------------------------------------------------
// File: DocumentGenerator.h
//-----------------------------------------------------------------------------
// Project: Kactus2
// Author: Antti Kamppi
// Date: 19.09.2011
//
// Description:
// Generates documentation for a component and its associated items.
//-----------------------------------------------------------------------------

#ifndef DOCUMENTGENERATOR_H
#define DOCUMENTGENERATOR_H

#include <kactusGenerators/DocumentGenerator/GeneralDocumentGenerator.h>
#include <kactusGenerators/DocumentGenerator/DocumentationWriter.h>

#include <KactusAPI/include/ExpressionFormatterFactory.h>
#include <KactusAPI/include/ExpressionFormatter.h>

#include <editors/common/DesignWidgetFactory.h>

#include <KactusAPI/include/LibraryInterface.h>

#include <IPXACTmodels/common/VLNV.h>
#include <IPXACTmodels/Component/Component.h>

#include <QTextStream>
#include <QList>
#include <QSharedPointer>
#include <QStringList>
#include <QWidget>

class AddressBlock;
class Register;
class Field;
class ViewDocumentGenerator;

//-----------------------------------------------------------------------------
//! Generates documentation for a component and its associated items.
//-----------------------------------------------------------------------------
class DocumentGenerator : public GeneralDocumentGenerator
{
    Q_OBJECT

public:

    /*!
     *  The constructor.
     *
     *      @param [in] handler                     Library, where the components reside.
     *      @param [in] vlnv                        VLNV of the component or design.
     *      @param [in] designWidgetFactory         Factory for making design widgets.
     *      @param [in] expressionFormatterFactory  Factory for making expression formatters.
     *      @param [in] parent                      The parent widget of the generator.
     */
    DocumentGenerator(LibraryInterface* handler, const VLNV& vlnv, DesignWidgetFactory* designWidgetFactory,
        ExpressionFormatterFactory* expressionFormatterFactory, QWidget* parent);

    /*!
     *  The constructor for child generators.
     *
     *      @param [in] handler                     Library, where the components reside.
     *      @param [in] vlnv                        VLNV of the component or design.
     *      @param [in] objects                     The vlnvs that have been gone through already.
     *      @param [in] expressionFormatterFactory  The factory for making expression formatters.
     *      @param [in] viewDocumentationGenerator  Generates documentation for views and instantiations.
     *      @param [in] parent                      The parent generator.
     */
    DocumentGenerator(LibraryInterface* handler, const VLNV& vlnv, QList<VLNV>& objects,
        ExpressionFormatterFactory* expressionFormatterFactory, ViewDocumentGenerator* viewDocumentationGenerator,
        DocumentGenerator* parent);
    
    /*!
     *  The destructor
     */
    virtual ~DocumentGenerator();
    
    enum DocumentFormat
    {
        HTML,
        MD
    };

    /*!
     *  Set the document format
     *
     *      @param [in] 
     */
    void setFormat(DocumentFormat format);

    /*!
     *  Write the documentation to the selected stream.
     *
     *      @param [in] stream          The stream where to write.
     *      @param [in] targetPath      The path where the document will be placed.
     */
    void writeDocumentation(QTextStream& stream, QString targetPath);

    /*!
     *  Write the html header.
     *
     *      @param [in] stream  The text stream to write the table of contents into.
     */
    void writeHeader(QTextStream& stream);

    /*!
     *  Write the table of contents for the component.
     *
     *      @param [in] componentNumber     The number for this component.
     *      @param [in] stream              The text stream to write the table of contents into.
     */
    void writeTableOfContents(QTextStream& stream);

    /*!
     *  Write the documentation for the given component.
     *
     *      @param [in] stream          The text stream to write the documentation into.
     *      @param [in] targetPath      File path to the file to be written.
     *      @param [in] filesToInclude  List of file names that contain pictures needed to display the document.
     */
    void writeDocumentation(QTextStream& stream, const QString& targetPath, QStringList& filesToInclude);

    void writeKactusAttributes(QTextStream& stream, int& subHeaderNumber);

    /*!
     *  Write the parameters and kactus2 parameters of the component.
     *
     *      @param [in] stream              The text stream to write the documentation into.
     *      @param [in] subHeaderNumber     The number that defines the sub-header.
     */
    void writeParameters(QTextStream& stream, int& subHeaderNumber);

    /*!
     *  Write the memory maps of the component.
     *
     *      @param [in] stream              The text stream to write the documentation into.
     *      @param [in] subHeaderNumber     The number that defines the sub header.
     */
    void writeMemoryMaps(QTextStream& stream, int& subHeaderNumber);

    /*!
     *  Write the address blocks of the memory map.
     *
     *      @param [in] addressBlocks       The list of the address blocks.
     *      @param [in] stream              The text stream to write the documentation into.
     *      @param [in] subHeaderNumber     The number that defines the sub header.
     *      @param [in] memoryMapNumber     The number for the memory map, whose address blocks are written.
     */
    void writeAddressBlocks(QList <QSharedPointer <AddressBlock> > addressBlocks, QTextStream& stream,
        int& subHeaderNumber, int& memoryMapNumber);

    /*!
     *  Write the registers of the address block.
     *
     *      @param [in] registers           The list of registers.
     *      @param [in] stream              The text stream to write the documentation into.
     *      @param [in] subHeaderNumber     The number that defines the sub header.
     *      @param [in] memoryMapNumber     The number that defines the memory map.
     *      @param [in] addressBlockNumber  The number that defines the address block.
     */
    void writeRegisters(QList <QSharedPointer <Register> > registers, QTextStream& stream, int& subHeaderNumber,
        int& memoryMapNumber, int& addressBlockNumber);

    /*!
     *  Write the fields of the register.
     *
     *      @param [in] currentRegister     The register, whose fields are to be written.
     *      @param [in] stream              The text stream to write the documentation into.
     */
    void writeFields(QSharedPointer <Register> currentRegister, QTextStream& stream);

    /*!
     *  Write the ports of the component.
     *
     *      @param [in] stream              The text stream to write the documentation into.
     *      @param [in] subHeaderNumber     The number that defines the sub header.
     */
    void writePorts(QTextStream& stream, int& subHeaderNumber);

    /*!
     *  Write the interfaces of the component.
     *
     *      @param [in] stream              The text stream to write the documentation into.
     *      @param [in] subHeaderNumber     The number that defines the sub header.
     */
    void writeInterfaces(QTextStream& stream, int& subHeaderNumber);

    /*!
     *  Write the file sets of the component.
     *
     *      @param [in] stream              The text stream to write the documentation into.
     *      @param [in] subHeaderNumber     The number that defines the sub header.
     */
    void writeFileSets(QTextStream& stream, int& subHeaderNumber);

    /*!
     *  Write the end of the document.
     *
     *      @param [in] stream  The text stream to write the documentation into.
     */
    void writeEndOfDocument(QTextStream& stream);

private:
    //! No copying. No assignment
    DocumentGenerator(const DocumentGenerator& other);
    DocumentGenerator& operator=(const DocumentGenerator& other);

    /*!
     *  Get the expression formatter factory.
     *
     *      @return The factory used for creating expression formatters.
     */
    ExpressionFormatterFactory* getExpressionFormatterFactory() const;

    /*!
     *  Create an expression formatter using the parameters of the contained component.
     *
     *      @return The created expression formatter.
     */
    ExpressionFormatter* createExpressionFormatter() const;

    /*!
     *  Write the header to the given stream.
     *
     *      @param [in] headerNumber    The number of the sub-header.
     *      @param [in] stream          The stream to write into.
     *      @param [in] text            The textual part of the header.
     *      @param [in] headerID        The id-tag for the header element.
     */
    void writeSubHeader(unsigned const int& headerNumber, QTextStream& stream, const QString& text, const QString& headerID);

    /*!
     *  Get the information for the reset values of the selected field.
     *
     *      @param [in] field   The selected field.
     */
    QString getFieldResetInfo(QSharedPointer<Field> field) const;

    /*!
     *  Write the port table for the selected ports.
     *
     *      @param [in] stream  The stream to write into.
     *      @param [in] title   The title of the port table.
     *      @param [in] ports   The selected ports.
     */
    void writePortTable(QTextStream& stream, QString const& title, QList <QSharedPointer <Port> > ports);

    /*!
     *  Write the details of a file
     *
     *      @param [in] file    Pointer to the file.
     *      @param [in] stream  The text stream to write into.
     */
    void writeFile(QSharedPointer<File> file, QTextStream& stream);

    /*!
     *  Parse the child items for the document generator.
     *
     *      @param [in] objects     List of objects that have already been parsed so there won't be duplicate
     *                              components in the generated document.
     */
    void parseChildItems(QList<VLNV>& objects);

    /*!
     *  Create a picture for the component.
     *
     *      @param [in] pictureList     List of file names to add the path of the created picture to.
     */
    void createComponentPicture(QStringList& pictureList);

    //-----------------------------------------------------------------------------
    // Data.
    //-----------------------------------------------------------------------------
    
    //! Pointer to the instance that manages the library.
    LibraryInterface* libraryHandler_;

    //! Pointer to the component whose documentation this generator writes.
    QSharedPointer<Component> component_;

    //! The running number that used for writing the numbered headers.
    unsigned int componentNumber_;

    //! The file path to the documentation file being written.
    QString targetPath_;

    //! The factory for creating expression formatters.
    ExpressionFormatterFactory* expressionFormatterFactory_;
    
    //! List contains pointers to the document generators under this generator.
    QList<QSharedPointer<DocumentGenerator> > childInstances_;

    //! Pointer to the instance that owns the top document generator.
    QWidget* parentWidget_;

    //! The expression formatter, used to change parameter IDs into names.
    ExpressionFormatter* expressionFormatter_;

    //! Document generator for component views.
    ViewDocumentGenerator* viewDocumentationGenerator_;

    DocumentationWriter* writer_;
};

#endif // DOCUMENTGENERATOR_H
