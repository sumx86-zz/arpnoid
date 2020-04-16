#include "util.h"
#include "arpnoid.h"

void usage( const char *prog ) {
    std::cout << "Usage: " << prog << " -i IFACE -f FILE" << "\n";
    std::exit(2);
}

void __die( const string& buf ) {
    std::cout << buf << "\n";
    std::exit(2);
}

int main( int argc, char **argv )
{
    int opt;
    const char *iface = nullptr;
    const char *file = nullptr;

    while ( (opt = getopt( argc, argv, "i:f:" )) != -1 ) {
        switch ( opt ) {
            case 'f':
                file = optarg;
                break;
            case 'i':
                iface = optarg;
                break;
            default:
                usage( argv[0] );
        }
    }

    if ( !iface || !file ) {
        usage( argv[0] );
    }

    vector<string> endpoints = split_str( file_content( file ), '\n' );
    if ( endpoints.size() <= 0 ) {
        __die( "File is empty!\n" );
    }
    std::shared_ptr<Arpnoid> arpnoid = Arpnoid::instance();
    if ( !arpnoid->init( iface ) ) {
        __die( arpnoid->errbuf );
    }
    if ( !arpnoid->cache( endpoints ) ) {
        __die( arpnoid->errbuf );
    }
    return 0;
}