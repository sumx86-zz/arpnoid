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
            content += line + "\n";
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

vector<string> split_str( const string& str, const char delim ) {
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

uint32_t iptol( const char *ip ) {
    uint32_t _long = 0;
    char frag[4];
    uint8_t rtv[4];

    if ( ip ) {
        for ( int i = 0, j = 0, k = 0 ; i < 4 ; i++ ) {
            frag[j]     = (isdigit( *ip )) ? *ip++ : '\0' ;
            frag[j + 1] = (isdigit( *ip )) ? *ip++ : '\0' ;
            frag[j + 2] = (isdigit( *ip )) ? *ip++ : '\0' ;
            frag[j + 3] = '\0';
            ip++;
            rtv[k++] = atoi( frag );
        }
    }
    _long = (rtv[0] << 24) | (rtv[1] << 16) | (rtv[2] << 8) | (rtv[3] << 0);
	return _long;
}

shared_ptr<uint8_t> hw2b( const char *hw ) {
    shared_ptr<uint8_t> addr = shared_ptr<uint8_t>(new uint8_t[6]);
    if ( !addr.get() ) {
        return nullptr;
    }
    uint32_t hw32[6];
    uint8_t *hw_cp = addr.get();
    int c = sscanf( hw, "%x:%x:%x:%x:%x:%x", &hw32[0], &hw32[1], &hw32[2], &hw32[3], &hw32[4], &hw32[5] );
    if ( c == EOF || c == -1 )
        return nullptr;

    for ( int i = 0 ; i < 6 ; i++ ) {
        if ( hw32[i] > 0xff || hw32[i] < 0x00 ) {
            return nullptr;
        }
        hw_cp[i] = (uint8_t) hw32[i]; 
    }
    return addr;
}