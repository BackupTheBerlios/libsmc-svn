/***************************************************************************
 *   Copyright (C) 2005 by Felipe Sateler                                  *
 *   fsateler@gmail.com                                                    *
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
#ifndef SMCEXCEPTION_H
#define SMCEXCEPTION_H

#include <glibmm/ustring.h>
#include <vector>

namespace smc {

/** @brief Exception thrown by libsmc
 * 
 * Exception handling for the SMC library. If the library throws this,
 * then it couldn't (or it shouldn't) handle the error.
 * It will build a stack trace 
 * to aid the developer in finding were the error is.
 * 
 * @author Felipe Sateler
*/
class Exception{
public:
	/** Describes the different possible errors */
	enum ErrorType{
		UNKNOWN,	///< Unknown error. Not currently used
		BAD_FILE,	///< A bad file was read
		BAD_VERSION,	///< The database version is wrong
		BAD_DIR		///< A bad directory was read
	};
	
	/** @brief Constructor
	 * 
	 * Creates an Exception object. It also builds a stack trace so as to know who threw it.
	 * @param Type The error type. Check enum ErrorType to see possible values
	 * @param text Additional text the thrower might want to add.
	 */
	Exception(ErrorType Type,const Glib::ustring& text);
	/// @overload
	Exception(ErrorType Type);
	
	~Exception();
	/** Returns an array of Glib::ustring's containing the symbols got during backtrace */
	std::vector<Glib::ustring>& getStackTrace();
	///Returns the type of error thrown (See ErrorType for more details)
	ErrorType getType() const;
	///Returns the message that the thrower added to the exception.
	Glib::ustring& getMessage();
	
private:
	ErrorType mError;
	Glib::ustring mMsg;
	std::vector<Glib::ustring> mStackTrace;

};

};

#endif
