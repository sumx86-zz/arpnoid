#ifndef __ARPNOID_UTIL_HH
#define __ARPNOID_UTIL_HH 1

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

using namespace std;

bool is_ipv4( const char *ip );
string trim( const char *str );
string file_content( const char *file );
vector<string> split( const string& str, const char delim );

#endif