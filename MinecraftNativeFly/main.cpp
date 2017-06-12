#include <Windows.h>
#include <jni.h>
#include <iostream>
#include "SRG_File.h"
#include "SRG_Utilities.h"
#include "CSV_Definitions.h"
#include "CSV_Utilities.h"

SRG_File srg_file;
CSV_Definitions csv_definitions;

jobject minecraft;
jobject player;

JavaVM* jvm;
JNIEnv* jenv;

jobject getMinecraft()
{
    static jclass mcClass = jenv->FindClass( SRG_Utilities::get_obfuscated_class_name( "net/minecraft/client/Minecraft", srg_file ).c_str() );
    static SRG_Method method = SRG_Utilities::get_method_by_name( "net/minecraft/client/Minecraft", CSV_Utilities::get_method_searge_name_by_name( "getMinecraft", csv_definitions ), srg_file );
    static std::string method_name = method.function_name_obf.substr( method.function_name_obf.find_last_of( '/' ) + 1 );
    static jmethodID smid = jenv->GetStaticMethodID( mcClass, method_name.c_str(), method.function_signature_obf.c_str() );

    return jenv->CallStaticObjectMethod( mcClass, smid );
}

jstring getVersion()
{
    static SRG_Method method = SRG_Utilities::get_method_by_name( "net/minecraft/client/Minecraft", CSV_Utilities::get_method_searge_name_by_name( "getVersion", csv_definitions ), srg_file );
    static std::string method_name = method.function_name_obf.substr( method.function_name_obf.find_last_of( '/' ) + 1 );
    static jmethodID smid = jenv->GetMethodID( jenv->FindClass( SRG_Utilities::get_obfuscated_class_name( "net/minecraft/client/Minecraft", srg_file ).c_str() ), method_name.c_str(), method.function_signature_obf.c_str() );

    return jstring( jenv->CallObjectMethod( minecraft, smid ) );
}

jobject getLocalPlayer()
{
    static std::string name = SRG_Utilities::get_obfuscated_field_name( "net/minecraft/client/Minecraft", CSV_Utilities::get_field_searge_name_by_name( "player", csv_definitions ), srg_file );
    static jfieldID fid = jenv->GetFieldID( jenv->GetObjectClass( minecraft ), name.c_str(), ( "L" + SRG_Utilities::get_obfuscated_class_name( "net/minecraft/client/entity/EntityPlayerSP", srg_file ) + ";" ).c_str() );

    return jenv->GetObjectField( minecraft, fid );
}

int getPlayerPermissionLevel( jobject player_object )
{
    static std::string field_name = SRG_Utilities::get_obfuscated_field_name( "net/minecraft/client/entity/EntityPlayerSP", CSV_Utilities::get_field_searge_name_by_name( "permissionLevel", csv_definitions ), srg_file );
    static jfieldID fid = jenv->GetFieldID( jenv->GetObjectClass( player ), field_name.c_str(), "I" );

    return jenv->GetIntField( player_object, fid );
}

jobject getPlayerCapabilities( jobject player_object )
{
    static std::string field_name = SRG_Utilities::get_obfuscated_field_name( "net/minecraft/entity/player/EntityPlayer", CSV_Utilities::get_field_searge_name_by_name( "capabilities", csv_definitions ), srg_file );
    static jfieldID fid = jenv->GetFieldID( jenv->FindClass( SRG_Utilities::get_obfuscated_class_name( "net/minecraft/entity/player/EntityPlayer", srg_file ).c_str() ), field_name.c_str(), ( "L" + SRG_Utilities::get_obfuscated_class_name( "net/minecraft/entity/player/PlayerCapabilities", srg_file ) + ";" ).c_str() );

    return jenv->GetObjectField( player_object, fid );
}

int getDisplayWidth( jobject mc )
{
    static std::string name = SRG_Utilities::get_obfuscated_field_name( "net/minecraft/client/Minecraft", CSV_Utilities::get_field_searge_name_by_name( "displayWidth", csv_definitions ), srg_file );
    static jfieldID fid = jenv->GetFieldID( jenv->GetObjectClass( mc ), name.c_str(), "I" );

    return jenv->GetIntField( mc, fid );
}

void EnableFly()
{

    jobject capabilities = getPlayerCapabilities( player );

    static std::string name = SRG_Utilities::get_obfuscated_field_name( "net/minecraft/entity/player/PlayerCapabilities", CSV_Utilities::get_field_searge_name_by_name( "isFlying", csv_definitions ), srg_file );
    static jfieldID fid = jenv->GetFieldID( jenv->GetObjectClass( capabilities ), name.c_str(), "Z" );

    jenv->SetBooleanField( capabilities, fid, true );
}

void initialize_framework()
{
    srg_file = SRG_File::parse_file( "joined.srg" );
    csv_definitions = CSV_Definitions::parse_files( "methods.csv", "fields.csv" );

    JNI_GetCreatedJavaVMs( &jvm, 1, nullptr );

    jvm->AttachCurrentThread( reinterpret_cast<void**>( &jenv ), nullptr );

    if( jenv ) {

        minecraft = getMinecraft();
        minecraft = jenv->NewGlobalRef( minecraft );

        player = getLocalPlayer();
        player = jenv->NewGlobalRef( player );
        
        jstring str = getVersion();

        const char* version = jenv->GetStringUTFChars( str, 0 );

        std::cout << "Minecraft Version: " << version << '\n';

        jenv->ReleaseStringUTFChars( str, version );

        while( true ) {
            if( player )
                EnableFly();
            else
                player = jenv->NewGlobalRef( getLocalPlayer() );
        }
    }

    if( jenv->ExceptionCheck() ) {
        jenv->ExceptionDescribe();
    }

    jvm->DetachCurrentThread();
}


bool __stdcall DllMain( void* handle, unsigned long reason, void* reserved )
{
    if( reason == DLL_PROCESS_ATTACH ) {

        AllocConsole();
        freopen( "CONOUT$", "w", stdout );
        SetConsoleTextAttribute( GetStdHandle( STD_OUTPUT_HANDLE ), FOREGROUND_INTENSITY | FOREGROUND_GREEN );

        CreateThread( nullptr, 0, reinterpret_cast<LPTHREAD_START_ROUTINE>( initialize_framework ), nullptr, 0, nullptr );
    }

    return true;
}