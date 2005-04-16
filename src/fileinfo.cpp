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
#include "fileinfo.h"
#include <tag.h>
#include <fileref.h>
#include <tstring.h>
#include <iostream>
#include <sstream>
#include <stdio.h>


using namespace std;

namespace smc{

FileInfo::FileInfo()
{
	// Nothing here yet
}


FileInfo::~FileInfo()
{
	// Nothing to do here
}

void FileInfo::Parse(Glib::ustring file)
{
	TagLib::FileRef ref(file.c_str());
	
	if(ref.isNull()){
		path=file;
		track=0;
		year=0;
		song=" ";
		artist=" ";
		album=" ";
		comment=" ";
		genre=" ";
	}
	
	TagLib::Tag* tag=ref.tag();
	if(tag){
		path=file;
		track=tag->track();
		year=tag->year();
		song=tag->title().to8Bit(true);
		artist=tag->artist().to8Bit(true);
		album=tag->album().to8Bit(true);
		comment=tag->comment().to8Bit(true);
		genre=tag->genre().to8Bit(true);
	}
	else {
		path=file;
		track=0;
		year=0;
		song=" ";
		artist=" ";
		album=" ";
		comment=" ";
		genre=" ";
	}
	
	
	TagLib::AudioProperties* ap=ref.audioProperties();
	if(ap){
		length=ap->length();
		bitrate=ap->bitrate();
		sample=ap->sampleRate();
		channels=ap->channels();
	}
	else
		length=bitrate=sample=channels=0;
}

void FileInfo::set(const Glib::ustring& _path,const Glib::ustring& _title,const Glib::ustring& _artist,
	const Glib::ustring& _album,const Glib::ustring& _comment,const Glib::ustring& _genre,
	const int _track,const int _length, const int _bitrate,const int _samplerate,
	const int _channels,const unsigned _year){
	path=_path;
	song=_title;
	artist=_artist;
	album=_album;
	comment=_comment;
	genre=_genre;
	track=_track;
	length=_length;
	bitrate=_bitrate;
	sample=_samplerate;
	channels=_channels;
	year=_year;
}




Glib::ustring FileInfo::getInfo(const char* fmt) const{
	int i;
	const int size=strlen(fmt);
	stringstream result;
	
	for(i=0;i<size;i++){
		if(fmt[i]=='%'){
			i++;
			switch( fmt[i] ){
			case 'p':
				result<<artist;
				break;
			case 't':
				result<<song;
				break;
			case 'a':
				result<<album;
				break;
			case 'f':
				result<<path;
				break;
			case 'n':
				result<<track;
				break;
			case '%':
				result<<'%';
				break;
			case 'l':
				result<<length;
				break;
			case 'c':
				result<<channels;
				break;
			case 'g':
				result<<genre;
				break;
			case 's':
				result<<sample;
				break;
			case 'i':
				result<<comment;
				break;
			case 'b':
				result<<bitrate;
				break;
			case 'y':
				result<<year;
				break;
			//default:
				// Just ignore it
			}
		}
		else
			result<<fmt[i];
	}
	
	return result.str();
}

bool FileInfo::operator <(const FileInfo& r) const{
	return path<r.path;
}

Glib::ustring FileInfo::getPath() const{
	return path;
}

Glib::ustring FileInfo::getTitle() const{
	return song;
}

Glib::ustring FileInfo::getArtist() const{
	return artist;
}

Glib::ustring FileInfo::getAlbum() const{
	return album;
}

Glib::ustring FileInfo::getComment() const{
	return comment;
}

Glib::ustring FileInfo::getGenre() const{
	return genre;
}

int FileInfo::getTrack() const{
	return track;
}

int FileInfo::getLength() const{
	return length;
}

int FileInfo::getBitrate() const{
	return bitrate;
}

int FileInfo::getSampleRate() const{
	return sample;
}

int FileInfo::getChannels() const{
	return channels;
}

unsigned FileInfo::getYear() const{
	return year;
}

} //smc
