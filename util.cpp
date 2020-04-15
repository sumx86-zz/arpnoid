#include "util.h"

string file_content( const char *file ) {
    if ( !file ) {
        throw runtime_error("File not specified");
    }
    ifstream filestream( file );
    if ( !filestream.is_open() ) {
        throw runtime_error("Error opening file!\n");
    }
    string line;
    string content;
    while ( std::getline( filestream, line ) ) {
        if ( !trim(line.c_str()).empty() ) {
            content += "\n" + line;
        }
    }
    return content;
}

string trim( const char *str ) {
    if ( !str ) {
        return "";
    }
    string newstr;
    while ( isspace( *str ) ) {
        str++;
    }
    newstr = string(str);
    return newstr;
}

vector<string> split( const string& str, const char delim ) {
    if ( str.empty()) {
        return {};
    }
    stringstream ss(str);
    string s;
    vector<string> tokens;

    while ( std::getline( ss, s, delim ) ) {
        if ( !s.empty() ) {
            tokens.push_back( s );
        }
    }
    return tokens;
}

bool is_ipv4( const char *ip ) {
    unsigned int ch_ip[4];
    int c = sscanf( ip, "%d.%d.%d.%d", &ch_ip[0], &ch_ip[1], &ch_ip[2], &ch_ip[3] );
    if ( c == EOF || c == -1 )
        return false;

    for ( int i = 0 ; i < 4 ; i++ ) {
        if ( ch_ip[i] > 255 || ch_ip[i] < 0 ) {
            return false;
        }
    }
    return true;
}