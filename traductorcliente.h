#ifndef TRADUCTORSERVIDOR_H
#define TRADUCTORSERVIDOR_H
#include "rapidjson/document.h"
#include "rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"
#include <string>
using namespace std;
using namespace rapidjson;


class TraductorCliente
{
public:
    TraductorCliente();
    string SerializarInformacion(string obstaculos1 ,int atributosGladiador1[9],int atributosGladiador2[9],string rutaA,string rutaB,bool finalizacion,int AvanceGenetico);
    void DeserializarInfoDeSimulacion(string json ,string *obstaculos,int atributosGladiador1[9],int atributosGladiador2[9],bool *finalizacion,int *AvanceGenetico,string *rutaA,string *rutaB);

};

#endif // TRADUCTORSERVIDOR_H
