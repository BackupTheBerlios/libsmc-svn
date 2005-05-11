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
 * This class handles everything concerning a media library.
 * This way you can have one object to represent one collection.
 * @todo Scan() actually re-scans everything. It should scan only new elements
 * @todo Scan() should accept filename patterns
 * @todo Implement ExportPlaylist()
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
	 * @param file The file to be loaded 
	*/
	void Load(const char* file);
	
	
	/** Saves the library to a database file.
	 * @param file The file to be saved. 
	 * If it exists, it's contents will be destroyed
	*/
	void Save(const char* file);
	
	
	/** Scans given directory and stores information about
	 * files found there.
	 * @param dir The directory to be scanned.
	 * @param recurse Whether subdirectories should be scanned or not
	*/
	void Scan(const char* dir, const bool recurse=true);
	
	
	/** Exports a playlist in given format
	 * @param file The destination file. If it already exists it's contents will be destroyed.
	 * @param format The format of the playlist. See enum PlaylistFormat for more details.
	 */
	void ExportPlaylist(const char* file,const PlaylistFormat format=M3U);
	
	
	/** Get the internal list of information about the files
	 * @return Returns a reference to the list
	*/
	InfoList&	getFiles(void) const;
	
	
	///Deletes all elements from the list
	void Clear();
	
	
protected:
	///Scans a single directory, doesn't recurse
	void ScanDirectory(const char* dir);
	
	/*
	 * The following functions are adaptations from Tamacom's PathConverter package,
	 * at http://tamacom.com/pathconvert.html
	 */
	
	///Converts from absolute to relative paths
	/**
	 * @param path absolute path
	 * @param base base directory (must be absolute path)
	 * @return resulting relative path
	 */
	Glib::ustring Abs2Rel(const Glib::ustring& path,const Glib::ustring& base);
	///Converts from relative to absolute paths
	/**
	 * @param path relative path
	 * @param base base directory (must be absolute path)
	 * @return resulting absolute path
	 */
	Glib::ustring Rel2Abs(Glib::ustring& path,Glib::ustring& base);
private:
	InfoList	mFiles;
	

};

}; // smc

#endif
