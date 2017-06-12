#pragma once
#include <vector>
#include <string>
#include <fstream>

#include "SRG_Method.h"
#include "SRG_Field.h"
#include "SRG_Class.h"
#include "SRG_Package.h"


class SRG_File
{
public:

    SRG_File() = default;

    void dump( std::ostream& stream )
    {
        // Classes
        stream << "----------------------------------- Classes ------------------------------------\n";

        for( std::vector<SRG_Class>::const_iterator iter = classes.cbegin(); iter != classes.cend(); ++iter ) {
            stream << "Obfuscated Class Name: " << iter->class_name_obf << '\n';
            stream << "Deobfuscated Class Name: " << iter->class_name_deobf << '\n';
            stream << "--------------------------------------------------------------------------------\n";
        }


        stream << "------------------------------------ Fields ------------------------------------\n";

        for( std::vector<SRG_Field>::const_iterator iter = fields.cbegin(); iter != fields.cend(); ++iter ) {
            stream << "Obfuscated Field Name: " << iter->field_name_obf << '\n';
            stream << "Deobfuscated Field Name: " << iter->field_name_deobf << '\n';
            stream << "--------------------------------------------------------------------------------\n";
        }

        stream << "----------------------------------- Methods ------------------------------------\n";

        for( std::vector<SRG_Method>::const_iterator iter = methods.cbegin(); iter != methods.cend(); ++iter ) {
            stream << "Obfuscated Method Name: " << iter->function_name_obf << '\n';
            stream << "Obfuscated Signature: " << iter->function_signature_obf << '\n';
            stream << "Deobfuscated Method Name: " << iter->function_name_deobf << '\n';
            stream << "Deobfuscated Signature: " << iter->function_signature_deobf << '\n';
            stream << "--------------------------------------------------------------------------------\n";
        }

        stream << "----------------------------------- Packages -----------------------------------\n";

        for( std::vector<SRG_Package>::const_iterator iter = packages.cbegin(); iter != packages.cend(); ++iter ) {
            stream << "Obfuscated Package Name: " << iter->package_name_obf << '\n';
            stream << "Deobfuscated Package Name: " << iter->package_name_deobf << '\n';
            stream << "--------------------------------------------------------------------------------\n";
        }
    }

    static SRG_File parse( std::istream& stream )
    {
        SRG_File parsed_file;
        std::string str;

        while( getline( stream, str ) ) {
            if( str.find( "MD:" ) == 0 ) {
                parsed_file.methods.push_back( SRG_Method( str ) );
            }
            else if( str.find( "FD:" ) == 0 ) {
                parsed_file.fields.push_back( SRG_Field( str ) );
            }
            else if( str.find( "PK:" ) == 0 ) {
                parsed_file.packages.push_back( SRG_Package( str ) );
            }
            else if( str.find( "CL:" ) == 0 ) {
                parsed_file.classes.push_back( SRG_Class( str ) );
            }
        }

        return parsed_file;
    }

    static SRG_File parse_file( const std::string& path )
    {
        SRG_File parsed_file;

        std::fstream srg_stream( path );

        std::string str;

        while( getline( srg_stream, str ) ) {
            if( str.find( "MD:" ) == 0 ) {
                parsed_file.methods.push_back( SRG_Method( str ) );
            }
            else if( str.find( "FD:" ) == 0 ) {
                parsed_file.fields.push_back( SRG_Field( str ) );
            }
            else if( str.find( "PK:" ) == 0 ) {
                parsed_file.packages.push_back( SRG_Package( str ) );
            }
            else if( str.find( "CL:" ) == 0 ) {
                parsed_file.classes.push_back( SRG_Class( str ) );
            }
        }

        srg_stream.close();

        return parsed_file;
    }

    std::vector<SRG_Class> classes;
    std::vector<SRG_Field> fields;
    std::vector<SRG_Method> methods;
    std::vector<SRG_Package> packages;
};