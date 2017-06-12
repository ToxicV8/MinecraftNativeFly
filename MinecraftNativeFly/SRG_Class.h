#pragma once
#include <string>
#include <sstream>
#include <vector>

class SRG_Class
{
public:

    SRG_Class( const std::string& line )
    {
        std::istringstream istream( line );

        std::vector<std::string> fields;

        std::string str;
        while( getline( istream, str, ' ' ) ) {
            fields.push_back( str );
        }

        if( fields.size() < 3 ) {
            throw std::exception( "Invalid Class. Not enough fields" );
        }

        if( fields[ 0 ] != "CL:" ) {
            throw std::exception( "Invalid Class. Type is not CL" );
        }

        class_name_obf = fields[ 1 ];

        class_name_deobf = fields[ 2 ];
    }

    SRG_Class() = default;

    // Obfuscated
    std::string class_name_obf;

    // Deobfuscated
    std::string class_name_deobf;
};