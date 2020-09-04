//
//  main.cpp
//  uniquePeptideExtractor
//
//  Created by Aaron Maurais on 9/23/16.
//  Copyright © 2016 Aaron Maurais. All rights reserved.
//
/*************************************************************************************
 
 uniquePeptideExtractor reads in a DTASelect-filter.txt file and removes all peptides
 which are not unique to a single loccus and poteins which do not have at least one 
 unique peptide.  The shortened filter file is written to a new filter file called
 DTASelect-filter_unique.txt in the current working dirrectory
 
*************************************************************************************/

#include "uniquePeptideExtractor.hpp"

using namespace std;

int main(int argc, char* argv[])
{
	//get args
	params::Params pars;
	if(!pars.getArgs(argc, argv))
		return -1;
	
	cout << endl << "uniquePeptideExtractor v" << BIN_VERSION_NUM << endl;
	
	for(size_t i = 0; i < pars.get_numFiles(); i++)
	{
		DTAfilter filterFile;
		string ifname = pars.get_ifname(i);
		string ofname = pars.get_ofname(i);
		
		if(!filterFile.readIn(ifname))
		{
			cout << endl << "Failed to read " << ifname << "!" << endl;
			if(pars.get_force())
				continue;
			else return -1;
		}
		
		if(!filterFile.writeOut(ofname))
		{
			cout << endl << "Failed to write " << ofname << "!" << endl;
			return -1;
		}
		
		if(!pars.get_wdSpecified())
		{
			ifname = utils::baseName(ifname);
			ofname = utils::baseName(ofname);
		}
		cout << endl << "Non uniqe peptides removed from " << ifname << ".\nResults written to: " << ofname << endl;
	}
	
	cout << "Done!" << endl;
	return 0;
}
