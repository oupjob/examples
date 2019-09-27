#ifndef KEYBOARDCONFIG_H
#define KEYBOARDCONFIG_H

#include <map>

#include <QDomDocument>
#include <QString>
#include <exception>

typedef std::pair<QString, QString>         Code2Key;
typedef std::map<QString, QString>          Code2KeyMap;

struct KbdDescription {
    enum KbdType { K_QWERTY, K_FUNCTIONAL };

    QString         dev_name;
    int             type;
};

bool operator < ( const KbdDescription& a, const KbdDescription& b );
bool operator > ( const KbdDescription& a, const KbdDescription& b );

typedef std::pair<KbdDescription, Code2KeyMap>     KeyboardInfo;
typedef std::map<KbdDescription, Code2KeyMap>      KeyboardInfoMap;
//      map( kbd_dev_path -> map ( code -> key ) )

class KeyboardConfig
{
public:

    KeyboardInfoMap         kbd_info_map_;

    const Code2KeyMap* getLayoutForKbd( const QString& kbd_dev_name ) const;
    Code2Key getCode2Key( const QString& kbd_dev_name, const QString& code ) const;

    KeyboardConfig();
    void read( const QString& file_name = "" );
    void read( const QDomDocument& doc );
    void read( const QDomElement& e );
};

#endif // KEYBOARDCONFIG_H
