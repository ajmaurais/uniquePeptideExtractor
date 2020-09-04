//
//  dtafilter.cpp
//  uniquePeptideExtractor
//
//  Created by Aaron Maurais on 9/23/16.
//  Copyright © 2016 Aaron Maurais. All rights reserved.
//

#include "dtafilter.hpp"

Protein::Protein()
{
	numElements = 9;
}

void Protein::clear()
{
	locus.clear();
	sequenceCount = 0;
	spectrumCount = 0;
	sequenceCoverage.clear();
	length.clear();
	MW.clear();
	pI.clear();
	desciptiveName.clear();
}

//parse proten header line and extract desired data
bool Protein::initialize(string line)
{
	clear();
	//split line by tabs
	vector<string> elems;
	utils::split(line, '\t', elems);
	
	//tell readIn function to skip line if it is header line
	if(isColumnHeaderLine(elems))
		return false;
	
	//extract protein information
	locus = elems[0];
	sequenceCount = utils::toInt(elems[1]);
	spectrumCount = utils::toInt(elems[2]);
	sequenceCoverage = elems[3];
	length = elems[4];
	MW = elems[5];
	pI = elems[6];
	validationStatus = elems[7];
	desciptiveName = elems[8];
	
	return true;
}

bool Protein::getUnique(ifstream& inF, string& line, vector<string>& peptides)
{
	assert(inF && peptides.empty());
	int allPeptides = sequenceCount;
	sequenceCount = 0;
	spectrumCount = 0;
	int i = 0;
	
	do{
		getline(inF, line);
		if(line[0] == '*')
		{
			peptides.push_back(line);
			sequenceCount++;
			spectrumCount += parsePeptideSC(line);
		}
		i++;
		if(utils::strContains('%', line))
		   return false;
	} while (i < allPeptides);
	return true;
}

string Protein::getHeaderLine() const
{
	string line;
	
	line = locus + DELIM;
	line += utils::toString(sequenceCount) + DELIM;
	line += utils::toString(spectrumCount) + DELIM;
	line += sequenceCoverage + DELIM;
	line += length + DELIM;
	line += MW + DELIM;
	line += pI + DELIM;
	line += validationStatus + DELIM;
	line += desciptiveName;
	
	return line;
}

DTAfilter::DTAfilter()
{
	vector<string> temp;
	lines = temp;
	headerLineFound = false;
}

//loop through protein headder and peptide lines in DTA filter file and add data to Proteins
bool DTAfilter::readIn(string fname)
{
	ifstream inF(fname.c_str());
	
	if(!inF)
		return false;
	
	bool getNewLine = true;
	string line;
	Protein newProtein;
	vector<string> peptides;
	
	while(!inF.eof())
	{
		if(getNewLine)
			getline(inF, line);
		getNewLine = true;
		if(line == DTAFILTER_HEADER_LINE)
			headerLineFound = true;
		if(utils::strContains('%', line))
		{
			if(!headerLineFound)
			{
				cout << endl << utils::baseName(fname) << " is not a valid DTAfilter file!" << endl;
				return false;
			}
			newProtein.clear();
			if(newProtein.initialize(line))
			{
				peptides.clear();
				getNewLine = newProtein.getUnique(inF, line, peptides);
				if(newProtein.sequenceCount > 0)
				{
				   lines.push_back(newProtein.getHeaderLine());
				   lines.insert(lines.end(), peptides.begin(), peptides.end());
				}
			}
			else lines.push_back(line);
		}
		else lines.push_back(line);
	}
	
	return true;
}

bool DTAfilter::writeOut(string fname) const
{
	ofstream outF(fname.c_str());
	
	if(!outF)
		return false;
	
	long len = lines.size();
	
	for(long i = 0; i < len; i++)
		outF << lines[i] << '\n';
	
	return true;
}

//check if line containing % is a collumn header line instead of a protein header line
bool isColumnHeaderLine(const vector<string>& elems)
{
	for (int i = 0; i < COLUMN_HEADER_LINE_ELEMENTS_LENGTH; i++)
		if(COLUMN_HEADER_LINE_ELEMENTS[i] != elems[i])
			return false;
	
	return true;
}

//return number of spectral counts for a peptide from a line in DTA filter file
int parsePeptideSC(string line)
{
	//split line by tabs
	vector<string> elems;
	utils::split(line, '\t', elems);
	assert(elems.size() > 11);
	
	//return SC for peptide as int
	return utils::toInt(elems[11]);
}

