#ifndef ARDUINO_H
#define ARDUINO_H
#include <QSerialPort>
#include <iostream>
using namespace std;

class arduino
{
public:
    arduino();
    void escribir(string mensaje);
    static arduino & getInstance(){
        static arduino instance;
        return instance;
    }
    void leer();
private:
    QSerialPort *arduinos;
    static const quint16 arduino_uno_vendor_id = 9025;
    static const quint16 arduino_UNO = 66;
    static const quint16 arduino_MEGA = 67;
    QString arduino_puerto;
    bool arduino_esta_disponible;
    void buscaYconectaArduino();
};

#endif // ARDUINO_H
