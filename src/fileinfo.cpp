/***************************************************************************
 *   Copyright (C) 2004 by Felipe Sateler                                  *
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
#include "fileinfo.h"
#include "exception.h"
#include "musiclibrary.h"
#include <tag.h>
#include <fileref.h>
#include <tstring.h>
#include <sstream>
#include <assert.h>
#include <glibmm/ustring.h>


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
	// File doesn't exist
	if(!access(file.c_str(),F_OK))
		throw new Exception(Exception::BAD_FILE,file);
	
	TagLib::FileRef ref(file.c_str());
	
	//Get current working directory
	char* wd=getcwd(NULL,-1);
	Glib::ustring cwd(wd);
	free(wd);
	
	if(ref.isNull()){
		
		mPath=MusicLibrary::Rel2Abs(file,cwd);
		mTrack=0;
		mYear=0;
		mTitle=" ";
		mArtist=" ";
		mAlbum=" ";
		mComment=" ";
		mGenre=" ";
	}
	
	TagLib::Tag* tag=ref.tag();
	if(tag){
		mPath=MusicLibrary::Rel2Abs(file,cwd);
		mTrack=tag->track();
		mYear=tag->year();
		mTitle=tag->title().to8Bit(true);
		mArtist=tag->artist().to8Bit(true);
		mAlbum=tag->album().to8Bit(true);
		mComment=tag->comment().to8Bit(true);
		mGenre=tag->genre().to8Bit(true);
	}
	else {
		mPath=MusicLibrary::Rel2Abs(file,cwd);
		mTrack=0;
		mYear=0;
		mTitle=" ";
		mArtist=" ";
		mAlbum=" ";
		mComment=" ";
		mGenre=" ";
	}
	
	
	TagLib::AudioProperties* ap=ref.audioProperties();
	if(ap){
		mLength=ap->length();
		mBitrate=ap->bitrate();
		mSample=ap->sampleRate();
		mChannels=ap->channels();
	}
	else
		mLength=mBitrate=mSample=mChannels=0;
}

void FileInfo::set(const Glib::ustring& _path,const Glib::ustring& _title,const Glib::ustring& _artist,
	const Glib::ustring& _album,const Glib::ustring& _comment,const Glib::ustring& _genre,
	const int _track,const int _length, const int _bitrate,const int _samplerate,
	const int _channels,const unsigned _year){
	mPath=_path;
	mTitle=_title;
	mArtist=_artist;
	mAlbum=_album;
	mComment=_comment;
	mGenre=_genre;
	mTrack=_track;
	mLength=_length;
	mBitrate=_bitrate;
	mSample=_samplerate;
	mChannels=_channels;
	mYear=_year;
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
				result<<mArtist;
				break;
			case 't':
				result<<mTitle;
				break;
			case 'a':
				result<<mAlbum;
				break;
			case 'f':
				result<<mPath;
				break;
			case 'n':
				result<<mTrack;
				break;
			case '%':
				result<<'%';
				break;
			case 'l':
				result<<mLength;
				break;
			case 'c':
				result<<mChannels;
				break;
			case 'g':
				result<<mGenre;
				break;
			case 's':
				result<<mSample;
				break;
			case 'i':
				result<<mComment;
				break;
			case 'b':
				result<<mBitrate;
				break;
			case 'y':
				result<<mYear;
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
	assert(mCriteria>=PATH && mCriteria<=YEAR);
	bool result=false;
	switch(mCriteria){
	case PATH:
		result=mPath<r.mPath;
		break;
	case TITLE:
		result=mTitle<r.mTitle;
		break;
	case ARTIST:
		result=mArtist<r.mArtist;
		break;
	case ALBUM:
		result=mAlbum<r.mAlbum;
		break;
	case COMMENT:
		result=mComment<r.mComment;
		break;
	case GENRE:
		result=mGenre<r.mGenre;
		break;
	case TRACK:
		result=mTrack<r.mTrack;
		break;
	case LENGTH:
		result=mLength<r.mLength;
		break;
	case BITRATE:
		result=mBitrate<r.mBitrate;
		break;
	case SAMPLERATE:
		result=mSample<r.mSample;
		break;
	case CHANNELS:
		result=mChannels<r.mChannels;
		break;
	case YEAR:
		result=mYear<r.mYear;
		break;
	}
	return result;
}

Glib::ustring FileInfo::getPath() const{
	return mPath;
}

Glib::ustring FileInfo::getTitle() const{
	return mTitle;
}

Glib::ustring FileInfo::getArtist() const{
	return mArtist;
}

Glib::ustring FileInfo::getAlbum() const{
	return mAlbum;
}

Glib::ustring FileInfo::getComment() const{
	return mComment;
}

Glib::ustring FileInfo::getGenre() const{
	return mGenre;
}

int FileInfo::getTrack() const{
	return mTrack;
}

int FileInfo::getLength() const{
	return mLength;
}

int FileInfo::getBitrate() const{
	return mBitrate;
}

int FileInfo::getSampleRate() const{
	return mSample;
}

int FileInfo::getChannels() const{
	return mChannels;
}

unsigned FileInfo::getYear() const{
	return mYear;
}

void smc::FileInfo::setSort(const SortCriteria criteria){
	mCriteria=criteria;
} 

} //smc
