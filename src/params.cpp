//
//  params.cpp
//  uniquePeptideExtractor
//
//  Created by Aaron Maurais on 8/31/17.
//  Copyright © 2017 Aaron Maurais. All rights reserved.
//

#include "params.hpp"

bool params::Params::getArgs(int argc, const char* const argv[])
{
	//get wd
	wd = utils::pwd();
	assert(utils::dirExists(wd));
	
	for(int i = 1; i < argc; i++)
	{
		if(!strcmp(argv[i], "-h") || !strcmp(argv[i], "--help"))
		{
			utils::systemCommand("man " + PROG_HELP_FILE_FNAME);
			return false;
		}
		if(!strcmp(argv[i], "-d") || !strcmp(argv[i], "--dir"))
		{
			if(!utils::isArg(argv[++i]))
			{
				usage();
				return false;
			}
			wdSpecified = true;
			wd = utils::absPath(argv[i]);
			if(!utils::dirExists(wd))
			{
				cerr << "Specified direectory does not exist." << endl;
				return false;
			}
			continue;
		}
		if(!strcmp(argv[i], "-f"))
		{
			force = true;
			continue;
		}
		if(!strcmp(argv[i], "-rw"))
		{
			rewrite = true;
			continue;
		}
		else if(utils::isFlag(argv[i]))
		{
			cerr << argv[i] << INVALID_ARG << endl;
			usage();
			return false;
		}
		else if(utils::isArg(argv[i]))
		{
			for(;i < argc; i++)
			{
				if(utils::isFlag(argv[i]))
				{
					usage();
					return false;
				}
				ifnames.push_back(argv[i]);
			}//end of for
			if(ifnames.size() <= 0)
			{
				usage();
				return false;
			}
			numFiles = ifnames.size();
		}//end of else if
	}//end of for
	
	//fix args
	if(wd[wd.length() - 1] != '/')
		wd += "/";
	makeOfnames();
	
	return true;
}//end of fxn

void params::Params::makeOfnames()
{
	assert(ifnames.size() > 0);
	vector<string>::iterator it;
	
	//convert all file references to absolute
	for(it = ifnames.begin(); it != ifnames.end(); ++it)
	{
		if(wdSpecified)
			*it = wd + *it;
		else *it = utils::absPath(*it);
	}
	
	//generate ofnames
	if(rewrite)
		ofnames = ifnames;
	else {
		for(it = ifnames.begin(); it != ifnames.end(); ++it)
			ofnames.push_back(utils::removeExtension(*it) + "_unique" + utils::getExtension(*it));
	}
}

void params::Params::usage() const
{
	utils::File file(PROG_USAGE_FNAME);
	assert(file.read());
	
	while(!file.end())
		cerr << file.getLine() << endl;
}
