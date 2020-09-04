//
//  uniquePeptideExtractor.hpp
//  uniquePeptideExtractor
//
//  Created by Aaron Maurais on 8/31/17.
//  Copyright © 2017 Aaron Maurais. All rights reserved.
//

#ifndef uniquePeptideExtractor_hpp
#define uniquePeptideExtractor_hpp

//deal with older c++ compilers
#if (__cplusplus == 199711L || __cplusplus == 1)
	#define nullptr NULL
#endif

//make sure this value is defined
#ifndef PATH_MAX
	#define PATH_MAX 1024
#endif

#define BIN_VERSION_NUM "2.0"

#include "utils.hpp"
#include "params.hpp"
#include "dtafilter.hpp"

#endif /* uniquePeptideExtractor_h */
