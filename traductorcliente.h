#ifndef TRADUCTORSERVIDOR_H
#define TRADUCTORSERVIDOR_H
#include "rapidjson/document.h"
#include "rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"
#include <string>
using namespace std;
using namespace rapidjson;


class TraductorCliente{
public:
    TraductorCliente();
    string SerializarInformacionIteracion3(string obstaculos1 ,string rutaA,string rutaB,bool finalizacion);
    void  DeserializarInformacionIteracion3(string json,string *obstaculos1 ,string *rutaA,string *rutaB,bool *finalizacion);
    string SerializarInformacion(string obstaculos1 ,int atributosGladiador1[9],int atributosGladiador2[9],string rutaA,string rutaB,bool finalizacion,int AvanceGenetico,string muerte1,string muerte2);
    void DeserializarInfoDeSimulacion(string json,string *obstaculos,int atributosGladiador1[10], int atributosGladiador2[10],bool *finalizacion,float *Prom1, float *Prom2, string *rutaA,string *rutaB,string *muerte1,string *muerte2, int* ganador);

};

#endif // TRADUCTORSERVIDOR_H
