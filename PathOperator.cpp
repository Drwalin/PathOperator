/*
	Copyright (C) 2017 Marek Zalewski
	
	This software is provided 'as-is', without any express or implied
	warranty. In no event will the authors be held liable for any damages
	arising from the use of this software.
	
	Permission is granted to anyone to use this software for any purpose,
	including commercial applications, and to alter it and redistribute it
	freely, subject to the following restrictions:

	1.	The origin of this software must not be misrepresented; you must not
		claim that you wrote the original software. If you use this software
		in a product, an acknowledgment in the product documentation is required.
	2.	Altered source versions must be plainly marked as such, and must not be
		misrepresented as being the original software.
	3.	This notice may not be removed or altered from any source distribution.
*/

#ifndef PATH_OPERATOR_CPP
#define PATH_OPERATOR_CPP

#include "PathOperator.h"

void PathOperator::System( std::string temp ) const
{
	system( temp.c_str() );
}

std::string PathOperator::GetLine( int id ) const
{
	tempBufer[0] = 0;
	std::ifstream file( tempFileName.c_str() );
	if( file.good() );
	{
		int i;
		for( i = 0; i <= id; ++i )
		{
			if( !file.getline( tempBufer, 1023 ) )
				return std::string("");
		}
		file.close();
	}
	return std::string(tempBufer);
}

int PathOperator::ChangeDirectory( std::string dir )
{
	if( dir == ".." )
	{
		if( path.size() > 1 )
			path.resize( path.size() - 1 );
	}
	else if( dir != "." )
	{
		path.push_back( dir );
	}
}

std::vector<std::string> PathOperator::List( bool returnWithGlobalPath ) const
{
	std::vector < std::string > dst;
	System( std::string( std::string("dir ") + GetCurrentPath() + " > " + tempFileName ) );
	
	std::string line;
	
	int i;
	for( i = 7;; ++i )
	{
		line = GetLine( i );
		if( line[0] == ' ' )
			break;
		
		dst.push_back( ( returnWithGlobalPath ? GetCurrentPath() : std::string("") ) + std::string(line.c_str()+36) );
	}
	
	return dst;
}

std::vector<std::string> PathOperator::ListFiles( bool returnWithGlobalPath ) const
{
	std::vector < std::string > dst;
	System( std::string( std::string("dir ") + GetCurrentPath() + " > " + tempFileName ) );
	
	std::string line;
	
	int i;
	for( i = 7;; ++i )
	{
		line = GetLine( i );
		if( line[0] == ' ' )
			break;
		
		if( line[24] == ' ' )
		{
			dst.push_back( ( returnWithGlobalPath ? GetCurrentPath() : std::string("") ) + std::string(line.c_str()+36) );
		}
	}
	
	return dst;
}

std::vector<std::string> PathOperator::ListFolders( bool returnWithGlobalPath ) const
{
	std::vector < std::string > dst;
	System( std::string( std::string("dir ") + GetCurrentPath() + " > " + tempFileName ) );
	
	std::string line;
	
	int i;
	for( i = 7;; ++i )
	{
		line = GetLine( i );
		if( line[0] == ' ' )
			break;
		
		if( line[24] != ' ' )
		{
			dst.push_back( ( returnWithGlobalPath ? GetCurrentPath() : std::string("") ) + std::string(line.c_str()+36) );
		}
	}
	
	return dst;
}

std::string PathOperator::GetCurrentPath() const
{
	std::string dst;
	int i;
	for( i = 0; i < path.size(); ++i )
		dst += path[i] + "\\";
	return dst;
}

void PathOperator::SwitchDisk( std::string disk )
{
	path.resize( 1 );
	path[0] = disk + ":";
}

PathOperator::PathOperator()
{
	tempBufer = new char[1024];
	memset( tempBufer, 0, 1024 );
	tempFileName = "temp.system.com.tmp";
	path.push_back( std::string( "C:" ) );
	System( std::string("dir > ") + tempFileName );
	
	std::string line = GetLine( 3 );
	int i;
	{
		bool ff = false;
		for( i = 0; i < line.size(); ++i )
		{
			if( ff )
			{
				if( line[i] == ' ' )
				{
					++i;
					break;
				}
			}
			else
			{
				if( line[i] != ' ' )
					ff = true;
			}
		}
	}
	
	tempFileName = std::string( line.c_str()+i ) + "\\" + tempFileName;
}

PathOperator::~PathOperator()
{
	delete[] tempBufer;
}

#endif

