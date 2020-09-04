//
//  params.hpp
//  uniquePeptideExtractor
//
//  Created by Aaron Maurais on 8/31/17.
//  Copyright © 2017 Aaron Maurais. All rights reserved.
//

#ifndef params_hpp
#define params_hpp

#include <iostream>
#include <vector>
#include "utils.hpp"

using namespace std;

namespace params{
	
	/******************************/
	/* namespace scoped constants */
	/******************************/
	
	const string INVALID_ARG = " is an invalid option! Exiting...\nUse uniqueSC -h for help.";
	
	//default file locations
	const string SHARE_DIR = std::string(PROG_SHARE_DIR);
	const string PROG_HELP_FILE_FNAME = SHARE_DIR + "/helpFile.man";
	const string PROG_USAGE_FNAME = SHARE_DIR + "/usage.txt";
	
	/**********************/
	/* class definitions */
	/*********************/
	
	class Params;
	
	class Params{
	private:
		bool rewrite;
		bool wdSpecified;
		bool force;
		string wd;
		vector<string> ifnames;
		vector<string> ofnames;
		size_t numFiles;
		
		void usage() const;
		void makeOfnames();
		
	public:
		//constructor
		Params()
		{
			rewrite = false;
			wdSpecified = false;
			numFiles = 0;
		}
		~Params() {}
		
		//modifiers
		bool getArgs(int, const char* const[]);
		
		//properties
		string get_wd() const{
			return wd;
		}
		bool get_wdSpecified() const{
			return wdSpecified;
		}
		bool get_force() const{
			return force;
		}
		size_t get_numFiles() const{
			return numFiles;
		}
		string get_ofname(size_t index) const{
			return ofnames[index];
		}
		string get_ifname(size_t index) const{
			return ifnames[index];
		}
	};
}// end of namespace

#endif /* params_hpp */
