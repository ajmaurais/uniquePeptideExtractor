//
//  utils.cpp
//  costom general utils library
//
//  Created by Aaron Maurais on 8/31/17.
//  Copyright © 2017 Aaron Maurais. All rights reserved.
//

#ifndef utils_hpp
#define utils_hpp

#include <cassert>
#include <sstream>
#include <sys/stat.h>
#include <string>
#include <cstring>
#include <stdlib.h>
#include <stdexcept>
#include <sys/types.h>
#include <dirent.h>
#include <unistd.h>
#include <ctime>
#include <vector>
#include <fstream>
#include <algorithm>

#ifndef PATH_MAX
	#define PATH_MAX 1024
#endif
namespace utils{
	
	using namespace std;
	
	/******************************/
	/* namespace scoped constants */
	/*****************************/
	
	string const WHITESPACE = " \f\n\r\t\v";
	string const COMMENT_SYMBOL = "#";
	enum newline_type {lf, crlf, cr, unknown};
	char const DEFAULT_LINE_DELIM = '\n';
	size_t const DEFAULT_BEGIN_LINE = 0;
	bool const IGNORE_HIDDEN_FILES = true;
	
	/******************************/
	/*     class definitions     */
	/*****************************/
	
	class File;
	
	class File{
	private:
		char* buffer;
		char delim;
		newline_type delimType;
		string fname;
		size_t beginLine;
		stringstream ss;
		unsigned long slen;
	public:
		File(){
			buffer = nullptr;
			slen = 0;
		}
		File(string str){
			buffer = nullptr;
			fname = str;
			slen = 0;
		}
		~File(){}
		
		//modifers
		bool read(string);
		bool read();
		string getLine();
		string getLine_skip();
		string getLine_trim();
		string getLine_skip_trim();
		string getLine_trim_skip();
		
		//properties
		bool end(){
			return (ss.tellg() >= slen);
		}
		string getFname() const{
			return fname;
		}
		char getDelim() const{
			return delim;
		}
		newline_type getNewLineType() const{
			return delimType;
		}
	};
	
	/*************/
	/* functions */
	/*************/
	
	//file utils
	char getDelim(newline_type);
	newline_type detectLineEnding_killStream(ifstream&);
	newline_type detectLineEnding(ifstream&);
	bool dirExists(const char*);
	bool dirExists(string);
	bool fileExists(const char*);
	bool fileExists(string);
	string pwd();
	string absPath(string);
	string absPath(const char*);
	bool ls(const char*, vector<string>&);
	bool ls(const char*, vector<string>&, string);
	bool mkdir(string);
	bool mkdir(const char*);
	void systemCommand(string command);

    template<class _Tp>
    _Tp baseName(const _Tp& path, const _Tp& delims = "/\\")
    {
        return path.substr(path.find_last_of(delims) + 1);
    }
    template<class _Tp>
    _Tp removeExtension(const _Tp& filename)
    {
        typename _Tp::size_type const p(filename.find_last_of('.'));
        return p > 0 && p != _Tp::npos ? filename.substr(0, p) : filename;
    }
    template<class _Tp>
    _Tp getExtension(const _Tp& filename)
    {
        typename _Tp::size_type const p(filename.find_last_of('.'));
        return p > 0 && p != _Tp::npos ? filename.substr(p) : filename;
    }

	//type conversions

    //converts num to string because to_string does not work with stl 98
    template <typename _Tp>
    string toString(_Tp num)
    {
        string str;
        stringstream convert;

        convert << num;
        convert >> str;

        return str;
    }

    int toInt(string);
	double toDouble(string);
	bool isInteger(string);
	
	//string utils
	bool strContains(string, string);
	bool strContains(char, string);
	bool startsWith(string whithinStr, string findStr);
	bool endsWith(string whithinStr, string findStr);
	void split (const string&, const char, vector<string>&);
	string trimTraling(const string&);
	string trimLeading(const string&);
	string trim(const string&);
	bool isCommentLine(string);
	string removeSubstr(string, string);
	string removeChars(char, string);
	string toLower(string);
	string repeat(string, size_t);
	void getLineTrim(istream& is, string& line,
							char delim = DEFAULT_LINE_DELIM, size_t beginLine = DEFAULT_BEGIN_LINE);
	void getLine(istream& is, string& line,
						char delim = DEFAULT_LINE_DELIM, size_t beginLine = DEFAULT_BEGIN_LINE);
	
	//other
	bool isFlag(const char*);
	bool isArg(const char*);
	string ascTime();
	template <typename _Tp, size_t N> _Tp* begin(_Tp(&arr)[N]) {
		return &arr[0];
	}
	template <typename _Tp, size_t N> _Tp* end(_Tp(&arr)[N]) {
		return &arr[0]+N;
	}
}

#endif /* utils_hpp */
