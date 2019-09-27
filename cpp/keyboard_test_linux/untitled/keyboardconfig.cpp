#include "keyboardconfig.h"
#include <QFile>
#include <QDomDocument>
#include <QDomElement>

#include "exception.h"

bool operator < ( const KbdDescription& a, const KbdDescription& b ) {
    return a.dev_name < b.dev_name;
}
bool operator > ( const KbdDescription& a, const KbdDescription& b ) {
    return a.dev_name > b.dev_name;
}

KeyboardConfig::KeyboardConfig() {}

void KeyboardConfig::read( const QString& file_name ) {
    QFile   cfg_file( file_name );

    if ( !cfg_file.exists() )
        throw Exception( E_FILE_NOT_EXISTS( file_name ) );

    if ( !cfg_file.open( QIODevice::ReadOnly ) )
        throw Exception( E_CANNOT_OPEN_FILE( file_name ) );

    QDomDocument    doc;
    QString         xml_parse_err_msg;
    int             err_line, err_column;

    bool parsed = doc.setContent(
        cfg_file.readAll(),
        &xml_parse_err_msg,
        &err_line,
        &err_column
    );
    if ( !parsed )
        throw Exception(
            E_XML_FILE_PARSE( file_name,  err_line, err_column, xml_parse_err_msg )
        );

    read( doc );
}

void KeyboardConfig::read( const QDomDocument& doc ){
    QDomNodeList keyboards = doc.elementsByTagName( "keyboard" );
    int n_keyboard = keyboards.count();
    for ( int i = 0; i < n_keyboard; ++i ) {
        QDomElement e_kbd = keyboards.at( i ).toElement();
        read( e_kbd );
    }
}

void KeyboardConfig::read( const QDomElement& e ){
    QString dev_path = e.attribute( "dev_path" ),
            type = e.attribute( "type", "functional" );

    if ( dev_path.isEmpty() )
        throw Exception( E_XML_STRUCT_KBD_DEV_PATH );

    Code2KeyMap codes2keys;

    if ( type == "qwerty" ) {
        QDomNodeList keys = e.elementsByTagName( "key" );
        int n_keys = keys.count();

        for( int i = 0; i < n_keys; ++i ) {
            QDomElement e_key = keys.at( i ).toElement();

            Code2Key code2key = Code2Key(
                e_key.attribute( "code" ),
                e_key.attribute( "symbol" )
            );
            codes2keys.insert( code2key );
        }
        kbd_info_map_.insert(
            KeyboardInfo(
                { dev_path, KbdDescription::K_QWERTY },
                codes2keys
            )
        );
    } else if ( type == "functional" ) {
        kbd_info_map_.insert(
            KeyboardInfo(
                { dev_path, KbdDescription::K_FUNCTIONAL },
                codes2keys
            )
        );
    }
}

const Code2KeyMap* KeyboardConfig::getLayoutForKbd( const QString& kbd_dev_name ) const {
    KeyboardInfoMap::const_iterator kbd_it = kbd_info_map_.find( { kbd_dev_name, -1 } );
    if ( kbd_it == kbd_info_map_.end() )
        return 0;

    return &( kbd_it->second );
}

Code2Key KeyboardConfig::getCode2Key( const QString& kbd_dev_name, const QString& code ) const {
    KeyboardInfoMap::const_iterator kbd_it = kbd_info_map_.find( { kbd_dev_name, -1 } );
    if ( kbd_it == kbd_info_map_.end() )
        return Code2Key();

    Code2KeyMap::const_iterator c2k_it = kbd_it->second.find( code );
    return ( c2k_it == kbd_it->second.end() )
        ? Code2Key()
        : Code2Key( c2k_it->first, c2k_it->second );
}
