/***************************************************************************
 *   Copyright (C) 2005 by Itay 'z9u2K' Duvdevani                          *
 *   itay AT z9u2kHomelinuxCom                                             *
 *   (replace uppercase letters with '.' and lowercase letter)             *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
 ***************************************************************************/

#ifndef __LOG_H__
#define __LOG_H__

#include <string>
#include <map>

#include "Exception.h"

#define LOG_LOCATION(loggingClass, loggingMethod) \
    Log::LogLocation(loggingClass, loggingMethod, __FILE__, __LINE__)

/**
 * Singleton logger.
 * 
 * @author z9u2k
 */
class Log {
public:

    /* --- Inner Types --- */
    
    /**
     * Supported Log levels
     */
    enum LogLevel {
        ALL, DEBUG, INFO, WARNING,
        ERROR, FATAL, BUG, NONE
    };

    /**
     * TODO: JavaDocs
     */
    struct LogLocation {
    public:

        LogLocation(std::string loggingClass,
                    std::string loggingMethod,
                    std::string loggingFile,
                    int loggingLine) {
            this->loggingClass = loggingClass;
            this->loggingMethod = loggingMethod;
            this->loggingFile = loggingFile;
            this->loggingLine = loggingLine;
        }
        
        std::string loggingClass;
        std::string loggingMethod;
        std::string loggingFile;
        int loggingLine;
    };

    /* --- Public Static Methods --- */

    /**
     * Initializes the logger with a specifi log level.
     *
     * @param level Log level to initilize logger with.
     */
    static void create(LogLevel level);

    /**
     * Releases the logger;
     */
    static void release();

    /**
     * Logs a message at the bug level.
     *
     * @param msg Message.
     */
    static void bug(LogLocation location, const std::string &msg);

    /**
     * Logs a message at the fatal level.
     *
     * @param msg Message.
     */
    static void fatal(LogLocation location, const std::string &msg);

    /**
     * Logs a message at the error level.
     *
     * @param msg Message.
     */
    static void error(LogLocation location, const std::string &msg);

    /**
     * Logs a message at the warning level.
     *
     * @param msg Message.
     */
    static void warning(LogLocation location, const std::string &msg);

    /**
     * Logs a message at the info level.
     *
     * @param msg Message.
     */
    static void info(LogLocation location, const std::string &msg);

    /**
     * Logs a message at the debug level.
     *
     * @param msg Message.
     */
    static void debug(LogLocation location, const std::string &msg);

    /**
     * Translate the string to log level.
     *
     * @param level String representation of a log-level. String is case
     *        insensitive and must be one of:
     *        <ul>
     *        <li>none</li>
     *        <li>bug</li>
     *        <li>fatal</li>
     *        <li>error</li>
     *        <li>warning</li>
     *        <li>info</li>
     *        <li>debug</li>
     *        <li>all</li>
     *        </ul>
     * @return Log-level corresponding the given string.
     * @throws FormatException When the given string is unknown
     */
    static LogLevel levelFromString(std::string level);

    /* --- Exceptions --- */

    /**
     * Thrown when the string given to <code>levelFromString</code> is
     * unknown.
     */
    NewException(FormatException);

private:

    /**
     * Fills the map of log-levels.
     */
    static void initLogLevels();

    /* --- Private Methods --- */

    /**
     * Logs <code>msg</code> with a specific log level.
     *
     * @param level Log level this message is logged at
     * @param msg Messages
     */
    void log(LogLocation location, LogLevel level, const std::string &msg);

    /* --- Singleton --- */

    /**
     * Private constructor.
     *
     * @param level Log level this logger is at
     */
    Log(LogLevel level);

    /* --- Data Members --- */

    /** Current log level */
    LogLevel logLevel;

    /** Maps between log levels and their names */
    static std::map<LogLevel, std::string> levelNames;

    /* --- Singeton instance --- */

    /** Thie singleton instance */
    static Log *instance;
};

#endif
