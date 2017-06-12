#pragma once
#include "CSV_Definitions.h"

class CSV_Utilities
{
public:

    static std::vector<std::string> get_method_searge_name_by_name( const std::string& name, CSV_Definitions& definitions )
    {
        std::vector<std::string> searges;

        for( std::vector<CSV_Method>::const_iterator iter = definitions.methods.cbegin(); iter != definitions.methods.cend(); ++iter ) {
            if( iter->name == name )
                searges.push_back( iter->searge );
        }

        return searges;
    }

    static std::vector<std::string> get_field_searge_name_by_name( const std::string& name, CSV_Definitions& definitions )
    {
        std::vector<std::string> searges;

        for( std::vector<CSV_Field>::const_iterator iter = definitions.fields.cbegin(); iter != definitions.fields.cend(); ++iter ) {
            if( iter->name == name )
                searges.push_back( iter->searge );
        }

        return searges;
    }
};