//-----------------------------------------------------------------------------
// File: CommandLineSupport.h
//-----------------------------------------------------------------------------
// Project: Kactus 2
// Author: Esko Pekkarinen
// Date: 05.02.2018
//
// Description:
// Interface for enabling plugin run using the command line arguments.
//-----------------------------------------------------------------------------

#ifndef APISUPPORT_H
#define APISUPPORT_H

#include <QString>
#include <QStringList>
#include <QList>
#include <QSharedPointer>

class IPluginUtility;

//-----------------------------------------------------------------------------
//! Interface for enabling plugin run using the command line arguments.
//-----------------------------------------------------------------------------
class APISupport 
{
public:

	//! The destructor.
    virtual ~APISupport() {};

    /*!
     *  Gets the output format generated by the plugin.
     *
     *      @return The output file format generated by the plugin.
     */
    virtual QString getOutputFormat() const = 0;

    /*!
     * Runs the generation.
     *
     *     @param [in] utility              Utilities for enabling plugin execution.
     *     @param [in] component            The component to run the generation for.
     *     @param [in] design               The design to run the generation for.
     *     @param [in] designConfiguration  The design configuration to run the generation for.
     *     @param [in] viewName             The component view name to run the generation for.
     *     @param [in] outputDirectory      The output directory for the generation results.
     */
     virtual void runGenerator(IPluginUtility* utility,
        QSharedPointer<Component> component,
        QSharedPointer<Design> design,
        QSharedPointer<DesignConfiguration> designConfiguration,
        QString const& viewName,
        QString const& outputDirectory) = 0;
};

#endif // APISUPPORT_H
