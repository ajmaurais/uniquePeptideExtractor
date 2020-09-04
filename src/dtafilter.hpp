//
//  Header.hpp
//  uniquePeptideExtractor
//
//  Created by Aaron Maurais on 9/23/16.
//  Copyright © 2016 Aaron Maurais. All rights reserved.
//

#include <iostream>
#include <vector>
#include <fstream>
#include <cassert>
#include <cstdlib>
#include <string>
#include <sys/stat.h>
#include <sstream>
#include <algorithm>
#include <cstring>
#include "utils.hpp"

using namespace std;

//this string is used to determine if a DTAFilter file is valid. If the DTASelect version is
//different the string can be changed, but compatibility with this program is not guaranteed.
string const DTAFILTER_HEADER_LINE = "DTASelect v2.0.39";

char const DELIM = '\t';

/******** class definitions and member functions *******/

class DTAfilter;
class Protein;

class Protein{
	friend class DTAfilter;
private:
	string locus;
	
	int sequenceCount,
		spectrumCount;
	
	string	sequenceCoverage,
		length,
		MW,
		pI,
		validationStatus,
		desciptiveName;
	
	int numElements;
	
	bool getUnique(ifstream&, string&, vector<string>&);
	void clear();
	
public:
	Protein();
	
	bool initialize(string);
	string getHeaderLine() const;
};

class DTAfilter{
private:
	//stores each line of filter file corresponding to unique peptides
	vector<string> lines;
	
	bool headerLineFound;
public:
	//constructor
	DTAfilter();
	
	//modifers
	bool readIn(string);
	
	//properties
	bool writeOut(string) const;
};

/****** functions ******/

/* dtafilter.cpp */
bool isColumnHeaderLine(const std::string&);
int parsePeptideSC(string);


