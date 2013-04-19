/* 
 *	Created on: 15.2.2013
 *	Author:		Antti Kamppi
 * File name:	memorymapheadergenerator.h
 * Project:	Kactus 2
*/

#ifndef ALTERABSPGENERATOR_H
#define ALTERABSPGENERATOR_H

#include "alterabspgenerator_global.h"

#include <PluginSystem/IGeneratorPlugin.h>
#include <models/librarycomponent.h>

#include <QObject>
#include <QSharedPointer>
#include <QString>
#include <QIcon>

class IPluginUtility;

/*! \brief The plugin to generate C-headers of component memory maps.
 *
 */
class ALTERABSPGENERATOR_EXPORT AlteraBSPGenerator : public QObject, public IGeneratorPlugin {

	Q_OBJECT
	Q_PLUGIN_METADATA(IID "kactus2.plugins.AlteraBSPGenerator" FILE "alteraBSPGenerator.json")

	Q_INTERFACES(IPlugin)
	Q_INTERFACES(IGeneratorPlugin)

public:

	/*! \brief The constructor
	 *
	 * Method: 		AlteraBSPGenerator
	 * Full name:	AlteraBSPGenerator::AlteraBSPGenerator
	 * Access:		public 
	 *
	*/
	AlteraBSPGenerator();
	
	//! \brief The destructor
	virtual ~AlteraBSPGenerator();

	//! \brief Returns the name of the plugin.
    virtual QString const& getName() const;

	//! \brief Returns the version of the plugin.
    virtual QString const& getVersion() const;

	//! \brief Returns the description of the plugin.
    virtual QString const& getDescription() const;

	//! \brief Returns the icon for the generator.
    /*!
     *  Returns the settings widget.
     */
    virtual PluginSettingsWidget* getSettingsWidget();

    /*!
     *  Returns the icon for the generator.
     */
    virtual QIcon getIcon() const;

    /*! \brief Checks whether the generator supports generation for the given library component.
     *
     * Method: 		checkGeneratorSupport
     * Full name:	MemoryMapHeaderGenerator::checkGeneratorSupport
     * Access:		virtual public 
     *
     * \param libComp The library component for which to check support.
     * \param libDesConf The design configuration object if the generator is run on a hierarchical component.
     * \param libDes The design object if the generator is run on a hierarchical component.
     *
     * \return True, if the generator supports the given component. Otherwise false.
    */
	 virtual bool checkGeneratorSupport(QSharedPointer<LibraryComponent const> libComp,
		 QSharedPointer<LibraryComponent const> libDesConf = QSharedPointer<LibraryComponent const>(),
		 QSharedPointer<LibraryComponent const> libDes = QSharedPointer<LibraryComponent const>()) const;

    /*! \brief Runs the generator.
     *
     * Method: 		runGenerator
     * Full name:	MemoryMapHeaderGenerator::runGenerator
     * Access:		virtual public 
     *
     * \param utility The plugin utility interface.
     * \param libComp The component for which the generator is run.
     * \param libDesConf The design configuration object if the generator is run on a hierarchical component.
     * \param libDes The design object if the generator is run on a hierarchical component.
     *
    */
	 virtual void runGenerator(IPluginUtility* utility, 
		 QSharedPointer<LibraryComponent> libComp, 
		 QSharedPointer<LibraryComponent> libDesConf = QSharedPointer<LibraryComponent>(), 
		 QSharedPointer<LibraryComponent> libDes = QSharedPointer<LibraryComponent>());

private:

	//! \brief No copying
	AlteraBSPGenerator(const AlteraBSPGenerator& other);

	//! \brief No assignment
	AlteraBSPGenerator& operator=(const AlteraBSPGenerator& other);

	//! The plugin utility.
	IPluginUtility* utility_;
};

#endif // ALTERABSPGENERATOR_H