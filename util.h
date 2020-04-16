#ifndef __ARPNOID_UTIL_HH
#define __ARPNOID_UTIL_HH 1

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <memory>

using namespace std;

bool is_ipv4( const char *ip );
string trim( const char *str );
string file_content( const char *file );
vector<string> split_str( const string& str, const char delim );
shared_ptr<uint8_t> ip2b( const char *ip );
shared_ptr<uint8_t> hw2b( const char *hw );

#endif