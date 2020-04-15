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
    return true;
}

bool Arpnoid::is_iface( const char *iface ) {
    struct ifreq req;
    strcpy( req.ifr_name, iface );

    if ( ioctl( _socket, SIOCGIFADDR, &req ) < 0 ) {
        ERROR( strerror(errno) );
    }
    return true;
}