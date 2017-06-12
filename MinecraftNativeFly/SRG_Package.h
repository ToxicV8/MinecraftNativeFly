#pragma once
#include <string>
#include <sstream>
#include <vector>

class SRG_Package
{
public:

    SRG_Package( const std::string& line )
    {
        std::istringstream istream( line );

        std::vector<std::string> fields;

        std::string str;
        while( getline( istream, str, ' ' ) ) {
            fields.push_back( str );
        }

        if( fields.size() < 3 ) {
            throw std::exception( "Invalid Package. Not enough fields" );
        }

        if( fields[ 0 ] != "PK:" ) {
            throw std::exception( "Invalid Package. Type is not PK" );
        }

        package_name_obf = fields[ 1 ];

        package_name_deobf = fields[ 2 ];
    }

    SRG_Package() = default;

    // Obfuscated
    std::string package_name_obf;

    // Deobfuscated
    std::string package_name_deobf;
};