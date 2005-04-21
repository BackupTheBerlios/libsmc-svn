/***************************************************************************
 *   Copyright (C) 2004 by Felipe Sateler                                  *
 *   fsatelerp@hotmail.com                                                 *
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
#ifndef SMCFILEINFO_H
#define SMCFILEINFO_H

#include <glibmm.h>

namespace smc{

/**
 * @brief Manage file meta-data
 * 
 * Manages a single file. It can parse a given file, or can be set by hand.
 * @author Felipe Sateler
*/
class FileInfo {
public:
	///Constructor
	FileInfo();
	///Destructor
	~FileInfo();
	
	/** @brief Element used for comparison
	 * 
	 * What element should the '<' and '>' operators use when comparing.
	 * 
	 */
	enum SortCriteria{
		PATH,
		TITLE,
		ARTIST,
		ALBUM,
		COMMENT,
		GENRE,
		TRACK,
		LENGTH,
		BITRATE,
		SAMPLERATE,
		CHANNELS,
		YEAR
	};
	
	// FileInfo interface
	/** @brief Parse a file
	 * 
	 * Parses a file to extract it's meta data.
	 * If the file can't be parsed, no information will be stored.
	 * @param file The file to be parsed.
	*/
	void Parse(const Glib::ustring file);
	/** @brief Set contents by hand
	 *
	 * Sets the information for a given file.
	 * Useful when extracting information from a database instead of a file.
	 * @param _path The complete path of the file
	 * @param _title The title of the song
	 * @param _artist The artist or performer
	 * @param _album The album
	 * @param _comment Comment about the file
	 * @param _genre The genre of the song
	 * @param _track Track number
	 * @param _length The length of the song, in seconds
	 * @param _bitrate The bitrate, in kbps
	 * @param _samplerate Sample rate of the song, in Hertz
	 * @param _channels Number of channels that the song has
	 * @param _year The year
	*/
	void set(const Glib::ustring& _path,const Glib::ustring& _title,const Glib::ustring& _artist,
		const Glib::ustring& _album,const Glib::ustring& _comment,const Glib::ustring& _genre,
		const int _track,const int _length, const int _bitrate,const int _samplerate,
		const int _channels,const unsigned _year);
	
	/** @brief Get information 
	 * 
	 * Returns a string with any info required
	 * @param fmt format descriptor (like printf)
	 * Recognized format tags (other characters are just printed):
	 * %p Performer/Artist
	 * %t Song title
	 * %f File path 
	 * %n Track number
	 * %a Album
	 * %l Song length (in seconds)
	 * %i Comment
	 * %g Genre
	 * %b Bitrate
	 * %y Year
	 * %s Sample rate
	 * %c Channels
	 * %% a single '%'
	 */
	Glib::ustring getInfo(const char* fmt) const;
	
	Glib::ustring getPath() const;
	Glib::ustring getTitle() const;
	Glib::ustring getArtist() const;
	Glib::ustring getAlbum() const;
	Glib::ustring getComment() const;
	Glib::ustring getGenre() const;
	int getTrack() const;
	int getLength() const;
	int getBitrate() const;
	int getSampleRate() const;
	int getChannels() const;
	unsigned getYear() const;
	
	private:
	// FileInfo variables
	Glib::ustring mPath;		// File Path
	Glib::ustring mTitle;		// Song name
	Glib::ustring mArtist;		// Artist name
	Glib::ustring mAlbum;	// Album name
	Glib::ustring mComment;	// NULL if not present
	Glib::ustring mGenre;		// NULL if not present
	int mTrack;		// Track number
	int mBitrate;		// For VBRs it is either the average or nominal bitrate
	int mLength;		// In seconds
	int mSample;		// Sample Rate in Hz
	int mChannels;	// Number of audio channels
	unsigned mYear;	// 0 if no year set
	SortCriteria mCriteria;
	
	public:
	// FileInfo operators (and related)
	///Compares 2 objects, using SortCriteria
	bool operator<(const FileInfo& r) const;
	///Set compare criteria
	void setSort(const SortCriteria);
	
	
};
typedef std::vector<FileInfo> InfoVector;
typedef std::list<FileInfo> InfoList;
} // smc

#endif	/* SMCFILEINFO_H */
