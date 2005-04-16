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
#include "exception.h"
#include <execinfo.h>


namespace smc {

Exception::Exception(ErrorType Error,const Glib::ustring& Msg): mMsg(Msg){
	mError=Error;
	// With 50 elements we should be able to trace all the stack
	void * Array[50];
	int Size = backtrace(Array, 50);
	char ** Symbols = backtrace_symbols(Array, Size);

	for (int i = 0; i < Size; i++)
	{
		mStackTrace.push_back(Symbols[i]);
	}

	free(Symbols);
}


Exception::~Exception()
{
}

std::vector<Glib::ustring> & Exception::getStackTrace() {
	return mStackTrace;
}

Exception::ErrorType Exception::getType() const{
	return mError;
}

};
