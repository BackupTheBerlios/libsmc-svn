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
#ifdef HAVE_CONFIG_H
#include <config.h>
#endif
#include <libxml++/document.h>
#include <libxml++/nodes/node.h>

namespace smc {

MusicLibrary::MusicLibrary() : mFiles(),mFormat(M3U)
{
}

MusicLibrary::MusicLibrary(const MusicLibrary& ref) : mFiles(ref.mFiles),mFormat(ref.mFormat)
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


}; //smc
