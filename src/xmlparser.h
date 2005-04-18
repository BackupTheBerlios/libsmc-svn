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
#ifndef SMCXMLPARSER_H
#define SMCXMLPARSER_H

#include <libxml++/parsers/saxparser.h>
#include <glibmm/ustring.h>
#include "fileinfo.h"

namespace smc {

/**
 * SAX XML parser for loading the database file into memory. Read the libXML++ documentation for details.
 * @author Felipe Sateler
*/
class XmlParser : public xmlpp::SaxParser
{
public:
	XmlParser(InfoList*);
	~XmlParser();
protected:
	virtual void on_start_element (const Glib::ustring &name, const AttributeList &attributes);
	virtual void on_end_element (const Glib::ustring &name);
	virtual void on_warning (const Glib::ustring &text);
	virtual void on_error (const Glib::ustring &text);
	virtual void on_fatal_error (const Glib::ustring &text);
	virtual void on_cdata_block (const Glib::ustring &text);


private:
	Glib::ustring mLastElement;
	InfoList *mInfo;
	FileInfo temp;
	bool mVersionOk;

	Glib::ustring mPath;		/// File Path
	Glib::ustring mSong;		/// Song name
	Glib::ustring mArtist;		/// Artist name
	Glib::ustring mAlbum;	/// Album name
	Glib::ustring mComment;	/// NULL if not present
	Glib::ustring mGenre;		/// NULL if not present
	int mTrack;		/// Track number
	int mBitrate;		/// For VBRs it is either the average or nominal bitrate
	int mLength;		/// In seconds
	int mSample;		/// Sample Rate in Hz
	int mChannels;	/// Number of audio channels
	unsigned mYear;	/// 0 if no year set

};

};

#endif
