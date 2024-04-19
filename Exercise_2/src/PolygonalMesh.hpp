#pragma once
#include <vector>
#include <iostream>
#include <Eigen/Eigen>

using namespace Eigen;
using namespace std;

namespace MeshLibrary{
struct PolygonalMesh {

    //Cell0D
    unsigned int NumberofCell0Ds;
    vector<unsigned int> IdCell0Ds={};
    vector<Vector2d> CoordinatesCell0Ds; //uso eigen perchè potrei aver bisogno di operazioni matematiche
    vector<unsigned int> MarkerCell0Ds = {};

    //Cell1D
    unsigned int NumberofCell1Ds;
    vector<unsigned int> IdCell1Ds={};
    vector<array<unsigned int,2>> VerticesCell1Ds = {};//uso un array perchè so gia la dimensione (2)
    //mentre non so quanti ne ho in totale (quindi vector)
    vector<unsigned int> MarkerCell1Ds = {};

    //Cell2D
    unsigned int NumberofCell2Ds;
    vector<unsigned int> IdCell2Ds={};
    vector<vector<unsigned int>> VerticesCell2Ds= {}; //vertici
    vector<vector<unsigned int>> EdgesCell2Ds= {}; //lati
    //non so la dimensione del vector visto che potrei avere poligoni di numero di lati diversi

    //salvo per ogni marker una lista di id con il marker corrispondente
    map<unsigned int, list<unsigned int>> VerticesMarker; //lista perchè non ho bisogno di accesso randomico in base alla posizione
    map<unsigned int, list<unsigned int>> EdgesMarker; //li separo perchè gli Id sono univoci solo in ogni tipo di cella


};
}
