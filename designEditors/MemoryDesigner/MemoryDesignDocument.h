//-----------------------------------------------------------------------------
// File: MemoryDesignDocument.h
//-----------------------------------------------------------------------------
// Project: Kactus2
// Author: Mikko Teuho
// Date: 06.07.2016
//
// Description:
// Declares the memory design tab document class.
//-----------------------------------------------------------------------------

#ifndef MEMORYDESIGNDOCUMENT_H
#define MEMORYDESIGNDOCUMENT_H

#include <common/widgets/tabDocument/TabDocument.h>

#include <QGraphicsView>

class MemoryDesignerDiagram;
class VLNV;
class LibraryInterface;
class Design;
class Component;

//-----------------------------------------------------------------------------
//! Declares the memory design tab document class.
//-----------------------------------------------------------------------------
class MemoryDesignDocument : public TabDocument
{
    Q_OBJECT

public:
   
    /*!
     *  The constructor.
     *
     *      @param [in] library     The library interface.
     *      @param [in] parent      The parent.
     */
    MemoryDesignDocument(LibraryInterface* library, QWidget* parent = 0);

    /*!
     *  The destructor.
     */
    virtual ~MemoryDesignDocument();

    /*!
     *  Reload the current memory design.
     */
    virtual void refresh();

    /*!
     *  Set the memory design.
     *
     *      @param [in] componentVLNV   VLNV of the component.
     *      @param [in] viewName        The selected component view.
     *
     *      @return True, if the memory design was opened successfully, false otherwise.
     */
    bool setDesign(VLNV const& componentVLNV, QString const& viewName);

    /*!
     *  Get the supported draw modes.
     *
     *      @return The supported draw modes.
     */
    virtual unsigned int getSupportedDrawModes() const;

    /*!
     *  Get the VLNV that can be used to identify the document.
	 * 
	 *      @return The VLNV that identifies the document.
	 */
	virtual VLNV getIdentifyingVLNV() const;

    /*!
     *  Get the document VLNV.
     *
     *      @return The VLNV of the containing document.
     */
    virtual VLNV getDocumentVLNV() const;

    /*!
     *  Changes the state of a visibility control.
     *
     *      @param [in] name   The name of the visibility control.
     *      @param [in] state  The new state for the visibility control.
     */
    virtual void setVisibilityControlState(QString const& name, bool state);

    /*!
     *  Sets the zoom level of the design.
     *
     *      @param [in] level The zoom level in percents.
     */
    virtual void setZoomLevel(int level);

    /*!
     *  Fits the whole design in view.
     */
    virtual void fitInView();

    /*!
     *  Centers the current view to a point.
     *
     *      @param [in] centerPoint   The point to center to.
     */
    void centerViewTo(QPointF const& centerPoint);

    /*!
     *  Sets the protection state of the document.
     *
     *      @param [in] locked True for locked state; false for unlocked.
     */
    virtual void setProtection(bool locked);

    /*!
     *  Change the condensing of memory graphics items.
     *
     *      @param [in] condenseItems   Value for condensing memory graphics items.
     */
    void setCondenseMemoryItems(bool condenseItems);

    /*!
     *  Check whether the memory graphics items are condensed or not.
     *
     *      @return True, if the memory graphics items are condensed, otherwise false.
     */
    bool memoryItemsAreCondensed() const;

    /*!
     *  Change the filtering of chained address space memory connections.
     *
     *      @param [in] filterChains    Value for filtering chained address space memory connections.
     */
    void filterAddressSpaceChains(bool filterChains);

    /*!
     *  Check whether the chained address space memory connections are filtered or not.
     *
     *      @return True, if the chained connections are filtered, otherwise false.
     */
    bool addressSpaceChainsAreFiltered() const;

    /*!
     *  Check whether the address space segments are filtered or not.
     *
     *      @return True, if address space segments are filtered, otherwise false.
     */
    bool addressSpaceSegmentsAreFilterted() const;

    /*!
     *  Check whether the address blocks are filtered or not.
     *
     *      @return True, if address blocks are filtered, otherwise false.
     */
    bool addressBlocksAreFiltered() const;

    /*!
     *  Check whether the address block registers are filtered or not.
     *
     *      @return True, if address block registers are filtered, otherwise false.
     */
    bool addressBlockRegistersAreFiltered() const;

public slots:

    /*!
     *  Filter the address space segments.
     *
     *      @param [in] filterSegments  Value for filtering the segments.
     */
    void filterAddressSpaceSegments(bool filterSegments);

    /*!
     *  Filter the address blocks.
     *
     *      @param [in] filterBlocks    Value for filtering the address blocks.
     */
    void filterAddressBlocks(bool filterBlocks);

    /*!
     *  Filter the address block registers.
     *
     *      @param [in] filterRegisters     Value for filtering the registers.
     */
    void filterAddressBlockRegisters(bool filterRegisters);

    //! Called when the vertical scrollbar is scrolled.
    void onVerticalScroll(int y);

signals:

    //! Signaled when the zoom level has changed.
    void zoomChanged();

    //! Signaled when all items are deselected.
    void clearItemSelection();

protected:
    
    /*!
     *  Show the document.
     *
     *      @param [in] event   The selected show event.
     */
    void showEvent(QShowEvent* event);

private:
    // Disable copying.
    MemoryDesignDocument(MemoryDesignDocument const& rhs);
    MemoryDesignDocument& operator=(MemoryDesignDocument const& rhs);

    /*!
     *  Get the design from the selected view.
     *
     *      @param [in] component   Component whose views are used.
     *      @param [in] viewName    The name of the selected view.
     */
    QSharedPointer<Design> getDesignFromView(QSharedPointer<Component> component, QString const& viewName);

    //-----------------------------------------------------------------------------
    // Data.
    //-----------------------------------------------------------------------------

    //! The graphics view for showing the diagram.
    QGraphicsView* view_;

    //! The memory design diagram.
    MemoryDesignerDiagram* diagram_;

    //! The used library interface.
    LibraryInterface* libraryHandler_;

    //! VLNV identifying the design.
    VLNV identifyingVLNV_;

    //! The name of the view used to construct the memory design diagram.
    QString designViewName_;
};

//-----------------------------------------------------------------------------

#endif // MEMORYDESIGNDOCUMENT_H