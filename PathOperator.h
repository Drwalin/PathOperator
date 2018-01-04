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

#ifndef PATH_OPERATOR_H
#define PATH_OPERATOR_H

#include <cstdio>
#include <cstring>
#include <vector>
#include <string>
#include <fstream>

class PathOperator
{
private:
	
	std::vector < std::string > path;
	std::string tempFileName;
	char * tempBufer;
	
public:
	
	PathOperator& operator = ( const PathOperator& src );
	
	std::string GetLine( int id ) const;	// id >= 0
	void System( std::string temp ) const;
	
	int ChangeDirectory( std::string dir );
	
	std::vector<std::string> List( bool returnWithGlobalPath = false ) const;
	std::vector<std::string> ListFiles( bool returnWithGlobalPath = false ) const;
	std::vector<std::string> ListFolders( bool returnWithGlobalPath = false ) const;
	
	std::string GetCurrentPath() const;
	
	void SwitchDisk( std::string disk );
	
	PathOperator();
	~PathOperator();
};

#endif

