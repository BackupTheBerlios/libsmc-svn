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
#include "musiclibrary.h"
#include "xmlparser.h"
#include "fileinfo.h"
#include "exception.h"

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include <libxml++/document.h>
#include <libxml++/nodes/node.h>
#include <dirent.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>

namespace smc {

MusicLibrary::MusicLibrary() : mFiles()
{
}

MusicLibrary::MusicLibrary(const MusicLibrary& ref) : mFiles(ref.mFiles)
{
}


MusicLibrary::~MusicLibrary()
{
}

void MusicLibrary::Save(const char* file){

	xmlpp::Document doc;
	xmlpp::Element *root,*entry,*child;
	InfoList::const_iterator end=mFiles.end(),it=mFiles.begin();


	root=doc.create_root_node("SMCDB");
	root->set_attribute("version","1.0");

	for( ;it!=end ; it++){
		entry=root->add_child("SongEntry");
	
		child=entry->add_child("Path");
		child->add_child_text((*it).getPath());
	
		child=entry->add_child("Artist");
		child->add_child_text((*it).getArtist());
	
		child=entry->add_child("Title");
		child->add_child_text((*it).getTitle());
	
		child=entry->add_child("Album");
		child->add_child_text((*it).getAlbum());
	
		child=entry->add_child("Comment");
		child->add_child_text((*it).getComment());
	
		child=entry->add_child("Genre");
		child->add_child_text((*it).getGenre());
	
		child=entry->add_child("Track");
		child->add_child_text((*it).getInfo("%n"));
	
		child=entry->add_child("Length");
		child->add_child_text((*it).getInfo("%l"));
	
		child=entry->add_child("Bitrate");
		child->add_child_text((*it).getInfo("%b"));
	
		child=entry->add_child("SampleRate");
		child->add_child_text((*it).getInfo("%s"));
	
		child=entry->add_child("Channels");
		child->add_child_text((*it).getInfo("%c"));

		child=entry->add_child("Year");
		child->add_child_text((*it).getInfo("%y"));

	}

	doc.write_to_file(file,"UTF-8");

}

void MusicLibrary::Load(const char* file){
	XmlParser Parser(&mFiles);
	Parser.parse_file(file);
}

void MusicLibrary::ExportPlaylist( const char * file, const PlaylistFormat format ){
	
	switch( format ){
	case M3U:
		int size=mFiles.size();
		for( int i=0;i<size ;i++ ){
			
		}
		break;
	}
}


///Removes anything that is not a directory
static int ScanSelector(const dirent *dir){
	// Has to be a directory, but not itself or parent
	if(dir->d_type==DT_DIR){
		if( (!strcmp(dir->d_name,".") || !strcmp(dir->d_name,"..")) )
			return 0;
		else
			return 1;
	} 
	else
		return 0;
}

void MusicLibrary::Scan(const char* dir,const bool recurse){
	if(!recurse)
		ScanDirectory(dir);
	else{
		dirent** Dirs;
		int count=scandir(dir,&Dirs,ScanSelector,alphasort);
		
		if(count<0)
			throw Exception(Exception::BAD_DIR,dir);

		unsigned StrSize;
		char Path[4096]; //Names larger than this are unlikely to be found
		strcpy(Path,dir);
		StrSize=strlen(dir);
		for(int i=0;i<count;i++){
			switch( Dirs[i]->d_type ){
			// We only want directories to recurse
			case DT_DIR:
				strcat(Path+StrSize,"/");
				strcat(Path+StrSize+1,Dirs[i]->d_name);
				ScanDirectory(Path);
				break;
			}
		}

	}
}
///Removes '.' and '..' entries
static int ScanDirectorySelector(const dirent *dir){
	// Is a directory, and either itself or parent (. or ..)
	if(dir->d_type==DT_DIR && 
		  (!strcmp(dir->d_name,".") || 
		  !strcmp(dir->d_name,"..")) )
		return 0;
	else
		return 1;
}

void MusicLibrary::ScanDirectory(const char* dir){
	FileInfo Temp;
	dirent** Files;
	int count;
	Glib::ustring Path(dir);
	
	
	count=scandir(dir, &Files, ScanDirectorySelector, alphasort);
	
	if(count<0)
		throw Exception(Exception::BAD_DIR,Path);			
	
	for( int i=0; i<count ; i++){
		switch( Files[i]->d_type ){
		/*
			* We only want regular files to parse. Directories aren't recursed, nor symlinks followed
			*/
		case DT_REG:
			// We scan everything for now
			/*ext=strrchr(files[i]->d_name,'.')+1;	// Finds backwards
			if(!ext)
				continue;
			for(unsigned j=0;j<extensions.size();j++){
				if(extensions[j]==ext){
					info.parse((path+"/")+files[i]->d_name);
					all.push_back(info);
					break;
				}
			}
			*/
			Temp.Parse((Path+"/")+Files[i]->d_name);
			mFiles.push_back(Temp);
			break;
		}
		
	}
}

void MusicLibrary::Clear(){
	mFiles.clear();
}



Glib::ustring MusicLibrary::Abs2Rel(const Glib::ustring path,const Glib::ustring _base){
	
	// We can't handle non absolute paths
	if( path[0]!='/' || _base[0]!='/')
		throw new Exception(BAD_PATH);

	Glib::ustring base(_base);

	if(base[base.length()-1]!='/')
		base+='/';
	
	// First we see what parts we have in common
	int i;
	for(i=0;i<base.length();i++){
		if( base[i]!=path[i] )
			break;
	}

	if(i==base.length())
		return path.substr(i);

	// Now we scroll back until we find a '/'
	i=base.rfind('/',i);
	
	
	// Now we construct the path
	// What we do eliminate i characters from path
	// and then we add as many '..' as necessary
	Glib::ustring result=path.substr(i+1);
	while( (i=base.find('/',i+1))!=string::npos ){
		result="../"+result;
	}
	
	return result;
	
}

Glib::ustring&  MusicLibrary::Rel2Abs(const Glib::ustring path,const Glib::ustring base){
	// Too lazy to think of a more "correct" algorithm
	if( path[0]=='/' || base[0]!='/' )
		throw new Exception(BAD_PATH);
	
	if(base[base.length()-1]=='/')
		return base+path;
	else
		return base+'/'+path;
}


};//smc
