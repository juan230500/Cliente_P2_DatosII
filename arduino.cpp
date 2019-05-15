#include "arduino.h"
#include <QSerialPort>
#include <QSerialPortInfo>
#include <QTimer>
#include <QDebug>
#include <iostream>
#include <unistd.h>
using namespace std;
arduino::arduino()
{
    buscaYconectaArduino();
}
void arduino:: escribir(string mensaje){
    sleep(5);
    arduinos->write(mensaje.c_str());
}
void arduino:: leer(){
    QByteArray datoLeido = arduinos->readAll();
   // int DatoEntero = datoLeido.toHex().toInt(0,16);
    qDebug() << datoLeido << "LEER";
}
void arduino::buscaYconectaArduino(){
    //Parte # 1, declaración inicial de las variables
    arduino_esta_disponible = false;
    arduino_puerto = "";
    arduinos = new QSerialPort;
    QString nombreDispositivoSerial = "";
    int nombreProductID = 0;

    //Parte # 2,buscar puertos con los identificadores de Arduino
    qDebug() << "Puertos disponibles: " << QSerialPortInfo::availablePorts().length();
    foreach (const QSerialPortInfo &serialPortInfo, QSerialPortInfo::availablePorts()) {
        qDebug() << "Identificador del fabricante (VENDOR ID): " << serialPortInfo.hasVendorIdentifier();
        if(serialPortInfo.hasVendorIdentifier()){
            qDebug() << "PUERTO  " << serialPortInfo.portName();
            qDebug() << "ID Vendedor " << serialPortInfo.vendorIdentifier();
            qDebug() << "ID Producto: " << serialPortInfo.productIdentifier();

            if(serialPortInfo.productIdentifier() == arduino_UNO || serialPortInfo.productIdentifier() == arduino_MEGA){
                arduino_esta_disponible = true;
                nombreDispositivoSerial = serialPortInfo.portName();
                nombreProductID = serialPortInfo.productIdentifier();
            }
        }
    }
    //Parte # 3, conexión del puerto encontrado con Arduino
    if(arduino_esta_disponible){
        arduino_puerto = nombreDispositivoSerial;
        arduinos->setPortName(arduino_puerto);
        arduinos->open(QIODevice::ReadWrite);
        arduinos->setDataBits(QSerialPort::Data8);
        arduinos ->setBaudRate(QSerialPort::Baud9600);
        arduinos->setParity(QSerialPort::NoParity);
        arduinos->setStopBits(QSerialPort::OneStop);
        arduinos->setFlowControl(QSerialPort::NoFlowControl);
        qDebug() << "Producto: " << nombreProductID;
        if(nombreProductID == 67) {
            qDebug()<<"Arduino UNO R3 conectado";
        }
        else if(nombreProductID == 66) {
            qDebug()<<"Arduino Mega conectado";}
        else{
         qDebug()<<"Error 3";
        }
    }
    else{
        qDebug()<<"No hay arduino";
    }
}
