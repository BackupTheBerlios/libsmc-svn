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
#ifndef SMCMEDIALIBRARY_H
#define SMCMEDIALIBRARY_H

#include "fileinfo.h"

namespace smc {

/**
 * @brief Manage a media library
 * 
 * This class handles everything concerning a media library. This way you can have one object to represent one collection.
 * 
 * @author Felipe Sateler
*/
class MusicLibrary{
public:
	enum PlaylistFormat {M3U,PLS};
	
	///Constructor
	MusicLibrary();
	///Copy Constructor
	MusicLibrary(const MusicLibrary&);

	///Destructor
	~MusicLibrary();
	
	
	/** Loads a database file
	 * \param file The file to be loaded 
	*/
	void Load(const char* file);
	
	
	/** Saves the library to a database file.
	 * \param file The file to be saved. 
	 * If it exists, it's contents will be destroyed
	*/
	void Save(const char* file);
	
	
	/** Scans given directory and stores information about
	 * files found there.
	 * \param dir The directory to be scanned
	 * \param recurse Whether subdirectories should be scanned or not
	*/
	void Scan(const char* dir, const bool recurse=true);
	
	
	/** Get the internal array of information about the files
	 * @return Returns a reference to the list
	*/
	InfoList&	getFiles(void) const;
	PlaylistFormat	getPlaylistFormat(void) const;
	
	
protected:
	///Scans a directory and subdirectories
	InfoList&	RecurseDirectory(char* dir);
	///Scans a single directory, and doesn't recurse
	InfoList&	ScanDirectory(char* dir);
	
private:
	InfoList	mFiles;
	PlaylistFormat	mFormat;
	

};

}; // smc

#endif
