#pragma once
#include <string>
#include <sstream>
#include <vector>

class SRG_Field
{
public:

    SRG_Field( const std::string& line )
    {
        std::istringstream istream( line );

        std::vector<std::string> fields;

        std::string str;
        while( getline( istream, str, ' ' ) ) {
            fields.push_back( str );
        }

        if( fields.size() < 3 ) {
            throw std::exception( "Invalid Field. Not enough fields" );
        }

        if( fields[ 0 ] != "FD:" ) {
            throw std::exception( "Invalid Field. Type is not FD" );
        }

        field_name_obf = fields[ 1 ];

        field_name_deobf = fields[ 2 ];
    }

    SRG_Field() = default;

    // Obfuscated
    std::string field_name_obf;

    // Deobfuscated
    std::string field_name_deobf;
};