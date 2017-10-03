//-----------------------------------------------------------------------------
// File: ComponentParameterReferenceTree.h
//-----------------------------------------------------------------------------
// Project: Kactus2
// Author: Mikko Teuho
// Date: 28.09.2018
//
// Description:
// Tree widget for displaying references to a parameter within a component.
//-----------------------------------------------------------------------------

#ifndef COMPONENTPARAMETERREFERENCETREE_H
#define COMPONENTPARAMETERREFERENCETREE_H

#include <editors/ComponentEditor/common/ExpressionFormatter.h>
#include <editors/ComponentEditor/parameterReferenceTree/ParameterReferenceTree.h>

#include <QSharedPointer>

class Component;
class ModuleParameter;
class FileSet;
class FileBuilder;
class File;
class BuildCommand;
class AddressSpace;
class Segment;
class ComponentInstantiation;
class DesignConfigurationInstantiation;
class DesignInstantiation;
class Port;
class MemoryMapBase;
class MemoryMap;
class MemoryRemap;
class AddressBlock;
class RegisterBase;
class Register;
class Field;
class BusInterface;
class MirroredSlaveInterface;
class MasterInterface;
class RemapState;
class RemapPort;

//-----------------------------------------------------------------------------
//! Tree widget for displaying references to a parameter within a component.
//-----------------------------------------------------------------------------
class ComponentParameterReferenceTree : public ParameterReferenceTree
{
    Q_OBJECT
public:

    /*!
     *   The constructor.
     *
     *      @param [in] component               The component whose references to display.
     *      @param [in] expressionFormatter     Formatter for expressions.
     *      @param [in] parent                  The parent widget.
     */
    ComponentParameterReferenceTree(QSharedPointer<Component> component,
        QSharedPointer<ExpressionFormatter> expressionFormatter, QWidget *parent = 0);

	/*!
     *  The destructor.
     */
    ~ComponentParameterReferenceTree();

private:
    
	// Disable copying.
    ComponentParameterReferenceTree(ComponentParameterReferenceTree const& rhs);
    ComponentParameterReferenceTree& operator=(ComponentParameterReferenceTree const& rhs);

    /*!
     *  Setup the reference tree.
     */
    void setupTree();

    /*!
     *  Check if a reference exists in component file sets.
     *
     *      @return True, if a reference is found, false otherwise.
     */
    bool referenceExistsInFileSets() const;

    /*!
     *  Check if a reference exists in a single file set.
     *
     *      @param [in] fileSet     The selected file set.
     *
     *      @return True, if a reference is found, false otherwise.
     */
    bool fileSetHasReference(QSharedPointer<FileSet> fileSet) const;

    /*!
     *  Check if a reference exists in file builders.
     *
     *      @param [in] fileBuilders    The selected list of file builders.
     *
     *      @return True, if a reference is found, false otherwise.
     */
    bool referenceExistsInFileBuilders(QSharedPointer<QList<QSharedPointer<FileBuilder> > > fileBuilders) const;

    /*!
     *  Check if a reference exists in a single file builder.
     *
     *      @param [in] fileBuilder     The selected file builder.
     *
     *      @return True, if a reference is found, false otherwise.
     */
    bool fileBuilderHasReference(QSharedPointer<FileBuilder> fileBuilder) const;

    /*!
     *  Check if a reference exists in files.
     *
     *      @param [in] fileList    The list of selected files.
     *
     *      @return True, if a reference exists in the files, false otherwise.
     */
    bool referenceExistsInFiles(QSharedPointer<QList<QSharedPointer<File> > > fileList) const;

    /*!
     *  Check if a reference exists in a single file.
     *
     *      @param [in] file    The selected file.
     *
     *      @return True, if a reference exists in a single file, false otherwise.
     */
    bool fileHasReference(QSharedPointer<File> file) const;

    /*!
     *  Check if a reference exits in a build command.
     *
     *      @param [in] fileBuildCommand    The selected build command.
     *
     *      @return True, if a reference exists in the build command, false otherwise.
     */
    bool buildCommandHasReference(QSharedPointer<BuildCommand> fileBuildCommand) const;

    /*!
     *  Create references for file sets.
     */
    void createReferencesForFileSets();

    /*!
     *  Create references for file builders.
     *
     *      @param [in] fileBuilders    The selected file builders.
     *      @param [in] parentItem      The parent item of the file builders item.
     */
    void createReferencesForFileBuilders(QSharedPointer<QList<QSharedPointer<FileBuilder> > > fileBuilders,
        QTreeWidgetItem* parentItem);

    /*!
     *  Create references for a single file builder.
     *
     *      @param [in] fileBuilder     The selected file builder.
     *      @param [in] parentItem      The parent item.
     */
    void createReferencesForSingleFileBuilder(QSharedPointer<FileBuilder> fileBuilder, QTreeWidgetItem* parentItem);

    /*!
     *  Create references from the selected files.
     *
     *      @param [in] fileList    A list of files with possible references.
     *      @param [in] parentItem  The parent item.
     */
    void createReferencesForFiles(QSharedPointer<QList<QSharedPointer<File> > > fileList,
        QTreeWidgetItem* parentItem);

    /*!
     *  Create references for a single file.
     *
     *      @param [in] selectedFile    The selected file.
     *      @param [in] parentItem      The parent item.
     */
    void createReferencesForSingleFile(QSharedPointer<File> selectedFile, QTreeWidgetItem* parentItem);

    /*!
     *  Check if a reference exists in components model parameters.
     *
     *      @return True, if there is a reference in model parameters to this parameter, false otherwise.
     */
    bool referenceExistsInModuleParameters(QSharedPointer<QList<QSharedPointer<ModuleParameter> > > parameters)
        const;

    /*!
     *  Create the references for model parameters.
     *
     *      @param [in] parameters  The model parameters to create references for.
     *      @param [in] parentItem  The parent item for references.
     */
    void createReferencesForModuleParameters(QSharedPointer<QList<QSharedPointer<ModuleParameter> > > parameters,
        QTreeWidgetItem* parentItem);

    /*!
     *  Check if a reference exists in address spaces.
     *
     *      @return True, if there is a reference to this parameter, false otherwise.
     */
    bool referenceExistsInAddressSpaces() const;
    
    /*!
     *  Check if a reference exists in an address space.
     *
     *      @param[in] addressSpace    The address space to search for.
     *
     *      @return True, if there is a reference in the address space to this parameter, otherwise false.
     */
    bool referenceExistsInSingleAddressSpace(QSharedPointer<AddressSpace> addressSpace) const;
        
    /*!
     *  Check if a reference exists in an address space segments.
     *
     *      @param[in] addressSpace    The address space whose segments to search for.
     *
     *      @return True, if there is a reference in the segments to this parameter, otherwise false.
     */
    bool referenceExistsInSegments(QSharedPointer<AddressSpace> addressSpace) const;
            
    /*!
     *  Check if a reference exists in a segment.
     *
     *      @param[in] segment      The segment to search for.
     *
     *      @return True, if there is a reference in the segment to this parameter, otherwise false.
     */
    bool referenceExistsInSingleSegment(QSharedPointer<Segment> segment) const;

    /*!
     *  Check if a reference exists in instantiations.
     *
     *      @return True, if there is a reference in the instantiations to this parameter, otherwise false.
     */
    bool referenceExistsInInstantiations() const;

    /*!
     *  Check if a reference exists in component instantiations.
     *
     *      @return True, if a reference is found, false otherwise.
     */
    bool referenceExistsInComponentInstantiations() const;

    /*!
     *  Check if a reference exists in a single component instantiation.
     *
     *      @param [in] instantiation   The selected component instantiation.
     *
     *      @return True, if a reference is found, false otherwise.
     */
    bool referenceExistsInSingleComponentInstantiation(QSharedPointer<ComponentInstantiation> instantiation) const;

    /*!
     *  Check if a reference exists in a design configuration instantiations.
     *
     *      @return True, if a reference is found, false otherwise.
     */
    bool referenceExistsInDesignConfigurationInstantiations() const;

    /*!
     *  Check if a reference exists in a single design configuration instantiation.
     *
     *      @param [in] instantiation   The selected design configuration instantiation.
     *
     *      @return True, if a reference is found, false otherwise.
     */
    bool referenceExistsInSingleDesignConfigurationInstantiation(
        QSharedPointer<DesignConfigurationInstantiation> instantiation) const;

    /*!
     *  Check if a reference exists in design instantiations.
     *
     *      @return True, if there is a reference to this parameter in the design instantiations , otherwise false.
     */
    bool referenceExistsInDesignInstantiations() const;

    /*!
     *  Check if a reference exists in a single design instantiation.
     *
     *      @param [in] instantiation   The selected design instantiation.
     *
     *      @return True, if there is a reference to this parameter in the design instantiation, otherwise false.
     */
    bool referenceExistsInSingleDesignInstantiation(QSharedPointer<DesignInstantiation> instantiation) const;

    /*!
     *  Create references for instantiations.
     */
    void createReferencesForInstantiations();

    /*!
     *  Create references for component instantiations.
     *
     *      @param [in] topInstantiationsItem   The parent tree item.
     */
    void createReferencesForComponentInstantiations(QTreeWidgetItem* topInstantiationsItem);

    /*!
     *  Create references for design configuration instantiations.
     *
     *      @param [in] topInstantiationsItem   The parent tree item.
     */
    void createReferencesForDesignConfigurationInstantiations(QTreeWidgetItem* topInstantiationsItem);

    /*!
     *  Create references for design instantiations.
     *
     *      @param [in] topInstantiationsItem   The parent tree item.
     */
    void createReferencesForDesignInstantiations(QTreeWidgetItem* topInstantiationsItem);

    /*!
     *  Check if a reference exists in ports.
     *
     *      @return True, if there is a reference to this parameter, false otherwise.
     */
    bool referenceExistsInPorts();

    /*!
     *  Check if a single port has a reference to this parameter.
     *
     *      @param [in] port    The port being studied.
     *
     *      @return True, if there is a reference to this parameter, false otherwise.
     */
    bool portHasreference(QSharedPointer<Port> port);

    /*!
     *  Create the references for ports.
     */
    void createReferencesForPorts();

    /*!
     *  Check if a reference exist in memory maps.
     *
     *      @return True, if there is a reference to this parameter, false otherwise.
     */
    bool referenceExistsInMemoryMaps();

    /*!
     *  Check if a reference exists in a single memory map.
     *
     *      @param [in] memoryMap   The memory map whose references are being looked at.
     *
     *      @return True, if there is a reference to this parameter, false otherwise.
     */
    bool referenceExistsInSingleMemoryMap(QSharedPointer<MemoryMap> memoryMap);

    /*!
     *  Check if a reference exists in the default memory remap (memory map).
     *
     *      @param [in] memoryMap   The memory map being examined.
     *
     *      @return True, if a reference exists in this memory map, false otherwise.
     */
    bool referenceExistsInDefaultMemoryRemap(QSharedPointer<MemoryMapBase> memoryMap) const;

    /*!
     *  Check if a reference exists in a single memory remap of a memory map.
     *
     *      @param [in] memoryRemap     The memory remap being examined.
     *
     *      @return True, if a reference exists in this memory remap, false otherwise.
     */
    bool referenceExistsInSingleMemoryRemap(QSharedPointer<MemoryRemap> memoryRemap);

    /*!
     *  Check if a reference exists in an address block.
     *
     *      @param [in] addressBlock    The address block whose references are being looked at.
     *
     *      @return True, if there is a reference to this parameter, false otherwise.
     */
    bool referenceExistsInAddressBlock(QSharedPointer<AddressBlock> addressBlock) const;

    /*!
     *  Checks if a reference exists in an address blocks values.
     *
     *      @param [in] addressBlock    The address block whose references are being looked at.
     *
     *      @return True, if there is a reference to this parameter, false otherwise.
     */
    bool referenceExistsInAddressBlockValues(QSharedPointer<AddressBlock> addressBlock) const;

    /*!
     *  Check if a reference exists in a list of base registers.
     *
     *      @param [in] registerList    The selected register list.
     *
     *      @return True, if a reference exists in the give list, false otherwise.
     */
    bool referenceExistsInRegisters(QSharedPointer<QList<QSharedPointer<RegisterBase> > > registerList) const;

    /*!
     *  Check if a register has a reference.
     *
     *      @param [in] targetRegister      The register being studied.
     *
     *      @return True, if there is a reference to this parameter, false otherwise.
     */
    bool registerHasReference(QSharedPointer<Register> targetRegister) const;

    /*!
     *  Check if any of the register fields has a reference.
     *
     *      @param [in] targetRegister      The register, whose fields are being checked.
     */
    bool referenceExistsInRegisterFields(QSharedPointer<Register> targetRegister) const;

    /*!
     *  Check if a single field has a reference.
     *
     *      @param [in] targetField         The target field.
     */
    bool registerFieldHasReference(QSharedPointer<Field> targetField) const;

    /*!
     *  Create the references for address spaces.
     */
    void createReferencesForAddressSpaces();

    /*!
     *  Create the references for a single address space.
     *
     *      @param [in] addressSpace    The address space to create references for.
     *      @param [in] parent          The parent tree item of the new address space item.
     */
    void createItemsForAddressSpace(QSharedPointer<AddressSpace> addressSpace, QTreeWidgetItem* parent);
    
    /*!
     *  Create the references for segments within an address space.
     *
     *      @param [in] addressSpace    The address space to create references for.
     *      @param [in] parent          The parent tree item of the new segment items.
     */
    void createReferencesForSegments(QSharedPointer<AddressSpace> addressSpace, QTreeWidgetItem* parent);
        
    /*!
     *  Create the references a segment within an address space.
     *
     *      @param [in] segment    The segment to create references for.
     *      @param [in] parent     The parent tree item of the segment items.
     */
    void createItemsForSegment(QSharedPointer<Segment> segment, QTreeWidgetItem* parent);

    /*!
     *  Create the references for memory maps.
     */
    void createReferencesForMemoryMaps();

    /*!
     *  Create the references for a single abstract memory map.
     *
     *      @param [in] memoryMap           The memory map / memory remap.
     *      @param [in] topMemoryMapItem    The parent tree item of the new memory map tree item.
     */
    void createReferencesForSingleMemoryMap(QSharedPointer<MemoryMapBase> memoryMap,
        QTreeWidgetItem* memoryRemapItem);

    /*!
     *  Create the references for a single address block.
     *
     *      @param [in] addressBlock                The address block.
     *      @param [in] middleAddressBlocksItem     The parent tree item of the new address block tree item.
     */
    void createReferencesForSingleAddressBlock(QSharedPointer<AddressBlock> addressBlock,
        QTreeWidgetItem* middleAddressBlocksItem);

    /*!
     *  Create the references for a single register.
     *
     *      @param [in] targetRegister  The register.
     *      @param [in] parentItem      The parent tree item of the new register tree item.
     */
    void createReferencesForSingleRegister(QSharedPointer<Register> targetRegister, QTreeWidgetItem* parentItem);

    /*!
     *  Check if a reference exists in bus interfaces.
     *
     *      @return True, if a reference exists in a bus interface, false otherwise.
     */
    bool referenceExistsInBusInterfaces() const;

    /*!
     *  Create references for bus interfaces.
     */
    void createReferencesForBusInterfaces();

    /*!
     *  Check if a reference exists in a single bus interface.
     *
     *      @param [in] busInterface    Pointer to the bus interface.
     */
    bool referenceExistsInSingleBusInterface(QSharedPointer<BusInterface> busInterface) const;

    /*!
     *  Check if a reference exists in mirrored slave.
     *
     *      @param [in] mirrorSlave     Pointer to the mirrored slave interface.
     */
    bool referenceExistsInMirroredSlave(QSharedPointer<MirroredSlaveInterface> mirrorSlave) const;

    /*!
     *  Check if a reference exists in a master interface.
     *
     *      @param [in] masterInterface     Pointer to the master interface.
     */
    bool referenceExistsInMasterInterface(QSharedPointer<MasterInterface> masterInterface) const;

    /*!
     *  Check if a reference exists in mirrored slaves remap address.
     *
     *      @param [in] mirrorSlave     Pointer to the mirrored slave interface.
     */
    bool mirroredSlaveRemapAddressHasReference(QSharedPointer<MirroredSlaveInterface> mirrorSlave) const;

    /*!
     *  Check if a reference exists in mirrored slaves range.
     *
     *      @param [in] mirrorSlave     Pointer to the mirrored slave interface.
     */
    bool mirroredSlaveRangeHasReference(QSharedPointer<MirroredSlaveInterface> mirrorSlave) const;

    /*!
     *  Check if a reference exists in remap states.
     *
     *      @return True, if a reference exists in remap states, false otherwise.
     */
    bool referenceExistsInRemapStates() const;

    /*!
     *  Check if a reference exists in a single remap state.
     *
     *      @param [in] remapState  Pointer to the remap state.
     *
     *      @return True, if a reference exists in a single remap state, false otherwise.
     */
    bool referenceExistsInSingleRemapState(QSharedPointer<RemapState> remapState) const;

    /*!
     *  Check if a reference exists in a single remap port.
     *
     *      @param [in] remapPort   Pointer to the remap port.
     *
     *      @return True, if a reference exists in a single remap port, flase otherwise.
     */
    bool referenceExistsInSingleRemapPort(QSharedPointer<RemapPort> remapPort) const;

    /*!
     *  Create references for remap states.
     */
    void createReferencesForRemapStates();

    /*!
     *  Create tree items for a port that is referencing this parameter.
     *
     *      @param [in] port        The referencing port.
     *      @param [in] parent      The parent of the upcoming item.
     */
    void createItemsForPort(QSharedPointer<Port> port, QTreeWidgetItem* parent);

    /*!
     *  Create tree items for an address block that is referencing this parameter.
     *
     *      @param [in] targetAddressBlock  The referencing address block.
     *      @param [in] parent              The parent for the upcoming item.
     */
    void createItemsForAddressBlock(QSharedPointer<AddressBlock> targetAddressBlock, QTreeWidgetItem* parent);

    /*!
     *  Create tree items for a register that is referencing this parameter.
     *
     *      @param [in] targetRegister  The referencing register.
     *      @param [in] parent          The parent of the upcoming item.
     */
    void createItemsForRegister(QSharedPointer<Register> targetRegister, QTreeWidgetItem* parent);

    /*!
     *  Create tree items for a register field that is referencing this parameter.
     *
     *      @param [in] targetField     The referencing register field.
     *      @param [in] parent          The parent of the new item.
     */
    void createItemsForField(QSharedPointer<Field> targetField, QTreeWidgetItem* parent);

    //-----------------------------------------------------------------------------
    // Data.
    //-----------------------------------------------------------------------------

    //! The component in which this id is situated.
    QSharedPointer<Component> component_;
};

#endif // COMPONENTPARAMETERREFERENCETREE_H
