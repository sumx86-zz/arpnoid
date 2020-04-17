#include "arpnoid.h"

std::shared_ptr<Arpnoid> Arpnoid::_instance = nullptr;

Arpnoid::Arpnoid( void ){}

Arpnoid::~Arpnoid(){}

std::shared_ptr<Arpnoid> Arpnoid::instance( void ) {
    if ( !_instance.get() ) {
        _instance = std::shared_ptr<Arpnoid>(new Arpnoid());
    }
    return _instance;
}

bool Arpnoid::init( const char *iface ) {
    if ( (_socket = socket(AF_INET, SOCK_STREAM, 0x00)) < 0 ) {
        ERROR( strerror(errno) );
    }
    if ( !is_iface( iface ) ) {
        return false;
    }
    _iface = iface;
    return true;
}

bool Arpnoid::is_iface( const char *iface ) {
    struct ifreq *req = if_list();
    if ( !req ) {
        return false;
    }
    register int i = 0;
    while ( strlen( req[i].ifr_name ) > 0 ) {
        if ( strcmp( iface, req[i++].ifr_name ) == 0 ) {
            return true;
        }
    }
    return false;
}

/* list all interfaces */
struct ifreq * Arpnoid::if_list( void ) {
    struct ifconf conf;
    static struct ifreq req[10];

    conf.ifc_len = sizeof( req );
    conf.ifc_req = req;

    if ( ioctl( _socket, SIOCGIFCONF, &conf ) < 0 ) {
        ERROR2( strerror(errno) );
    }
    return req;
}

bool Arpnoid::insert_entry( struct arpreq *req, const char *ip, const char *hw ) {
    uint8_t hww[6];
    if ( !hw2b( hw, hww ) ) {
        return false;
    }
    memcpy( req->arp_ha.sa_data, hww, 0x06 );
    struct sockaddr_in *sin = (struct sockaddr_in *) &req->arp_pa;
    sin->sin_family      = AF_INET;
    sin->sin_addr.s_addr = htonl( iptol( ip ) );

    if ( ioctl( _socket, SIOCSARP, req ) < 0 )
        ERROR( strerror(errno) );
    return true;
}

bool Arpnoid::cache( vector<string> endpoints ) {
    struct arpreq req;
    memset( &req, '\x00', sizeof(req) );
    strcpy( req.arp_dev, _iface );

    req.arp_flags = ATF_COM | ATF_PERM;
    req.arp_ha.sa_family = AF_UNSPEC;

    for ( vector<string>::iterator it = endpoints.begin() ; it != endpoints.end() ; it++ ) {
        auto entry = split_str( *it, '-' );
        if ( !insert_entry( &req, entry[0].c_str(), entry[1].c_str() ) ) {
            return false;
        }
    }
    return true;
}