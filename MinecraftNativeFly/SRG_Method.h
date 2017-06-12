#pragma once
#include <string>
#include <sstream>
#include <vector>

class SRG_Method
{
public:
    
    SRG_Method( const std::string& line )
    {
        std::istringstream istream( line );

        std::vector<std::string> fields;

        std::string str;
        while( getline( istream, str, ' ' ) ) {
            fields.push_back( str );
        }

        if( fields.size() < 5 ) {
            throw std::exception( "Invalid Method. Not enough fields" );
        }

        if( fields[ 0 ] != "MD:" ) {
            throw std::exception( "Invalid Method. Type is not MD" );
        }

        function_name_obf = fields[ 1 ];
        function_signature_obf = fields[ 2 ];

        function_name_deobf = fields[ 3 ];
        function_signature_deobf = fields[ 4 ];
    }

    SRG_Method() = default;

    // Obfuscated
    std::string function_name_obf;
    std::string function_signature_obf;

    // Deobfuscated
    std::string function_name_deobf;
    std::string function_signature_deobf;
};