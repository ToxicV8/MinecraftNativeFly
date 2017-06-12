#pragma once
#include <string>
#include <fstream>
#include <vector>

class CSV_Field
{
public:

    CSV_Field( const std::string& line )
    {
        std::istringstream istream( line );

        std::vector<std::string> fields;

        std::string str;
        while( getline( istream, str, ',' ) ) {
            fields.push_back( str );
        }

        searge = fields[ 0 ];
        name = fields[ 1 ];
        side = std::stoi( fields[ 2 ] );
    }

    CSV_Field() = default;

    std::string searge;
    std::string name;
    int side;
};

class CSV_Method
{
public:

    CSV_Method( const std::string& line )
    {
        std::istringstream istream( line );

        std::vector<std::string> fields;

        std::string str;
        while( getline( istream, str, ',' ) ) {
            fields.push_back( str );
        }

        searge = fields[ 0 ];
        name = fields[ 1 ];
        side = std::stoi( fields[ 2 ] );
    }

    CSV_Method() = default;

    std::string searge;
    std::string name;
    int side;
};

class CSV_Definitions
{
public:
    CSV_Definitions() = default;

    static CSV_Definitions parse_files( std::string methods_path, std::string fields_path )
    {
        CSV_Definitions definitions;
        
        // The buffer
        std::string line;

        std::ifstream methods_stream( methods_path );

        if( methods_stream ) {
            // Header
            getline( methods_stream, line );

            while( getline( methods_stream, line ) ) {
                definitions.methods.push_back( CSV_Method( line ) );
            }
        }

        methods_stream.close();

        std::ifstream fields_stream( fields_path );

        if( fields_stream ) {
            // Header
            getline( fields_stream, line );

            while( getline( fields_stream, line ) ) {
                definitions.fields.push_back( CSV_Field( line ) );
            }
        }

        fields_stream.close();

        return definitions;
    }

    std::vector<CSV_Field> fields;
    std::vector<CSV_Method> methods;
};