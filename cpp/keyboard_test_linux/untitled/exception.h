#ifndef EXCEPTION_H
#define EXCEPTION_H

#include <exception>
#include <QString>

#define E_FILE_NOT_EXISTS( file )\
QObject::tr( "Файл %1 не существует" ).arg( file )

#define E_CANNOT_OPEN_FILE( file )\
QObject::tr( "Невозможно открыть файл: %1" ).arg( file )

#define E_XML_FILE_PARSE( file, line, col, msg )\
QObject::tr( "Неверная конфигурация файла: %1, строка: %2, позиция: %3\n Сообщение парсера: %4" )\
    .arg( file ).arg( line ).arg( col ).arg( msg )

#define E_XML_STRUCT_KBD_DEV_PATH \
QObject::tr( "Не задан файл устройства клавиатуры" )

#define E_OPEN_KBD_DEV_FILE( path )\
QObject::tr( "Не удалось открыть файл устройства клавиатуры:\n%1" ).arg( path )

class Exception : public std::exception
{
private:
    QString     message_;

public:
    Exception( const QString& message ) throw () : message_( message ) {}
    virtual ~Exception() throw() {}

    const QString& message() { return message_; }
};

#endif // EXCEPTION_H
