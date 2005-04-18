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
#include "xmlparser.h"
#include "exception.h"
#include <iostream>

namespace smc {

XmlParser::XmlParser(InfoList* _info)
	: xmlpp::SaxParser(){
	mInfo=_info;
	mVersionOk=false;
}


XmlParser::~XmlParser(){
}

void XmlParser::on_start_element (const Glib::ustring &name, const AttributeList &attributes){
	
	Glib::ustring Version;
	
	// Check version
	if(name=="SMCDB"){
		AttributeList::const_iterator end=attributes.end(),it=attributes.begin();
		for(;it!=end;it++){
			if((*it).name=="version"){
				Version=(*it).value;
				break;
			}
		}
		// Unsupported version, or no version
		if( Version!="1.0")	
			throw Exception(Exception::BAD_VERSION);
		mVersionOk=true;
	}
	else{	
		if(!mVersionOk)
			// No SMCDB tag read
			throw Exception(Exception::BAD_FILE);
	}
	

	mLastElement=name;
}

void XmlParser::on_end_element (const Glib::ustring &name){
	if(name=="SongEntry"){
		temp.set(mPath,mSong,mArtist,mAlbum,mComment,mGenre,mTrack,mLength,mBitrate,mSample,mChannels,mYear);
		mInfo->push_back(temp);
	
		mPath.clear();
		mSong.clear();
		mArtist.clear();
		mAlbum.clear();
		mComment.clear();
		mGenre.clear();
		mTrack=mBitrate=mLength=mSample=mChannels=mYear=0;
	}
	mLastElement.clear();
}

void XmlParser::on_warning (const Glib::ustring &text){
//	throw "XML Warning: "+text;
}

void XmlParser::on_error (const Glib::ustring &text){
	throw Exception(Exception::BAD_FILE,text);
}

void XmlParser::on_fatal_error (const Glib::ustring &text){
	throw Exception(Exception::BAD_FILE,text);
}

void XmlParser::on_cdata_block (const Glib::ustring &text){
	
	if(text=="" || text.empty())
		return;

	if(mLastElement=="Path"){
		mPath=text;
	}
	else if(mLastElement=="Artist"){
		mArtist=text;
	}
	else if(mLastElement=="Title"){
		mSong=text;
	}
	else if(mLastElement=="Album"){
		mAlbum=text;
	}
	else if(mLastElement=="Comment"){
		mComment=text;
	}
	else if(mLastElement=="Genre"){
		mGenre=text;
	}
	else if(mLastElement=="Track"){
		mTrack=atoi(text.c_str());
	}
	else if(mLastElement=="Length"){
		mLength=atoi(text.c_str());
	}
	else if(mLastElement=="Bitrate"){
		mBitrate=atoi(text.c_str());
	}
	else if(mLastElement=="SampleRate"){
		mSample=atoi(text.c_str());
	}
	else if(mLastElement=="Channels"){
		mChannels=atoi(text.c_str());
	}
	else if(mLastElement=="Year"){
		mYear=atoi(text.c_str());
	}
}

};
