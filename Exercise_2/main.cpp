#include <iostream>
#include "Utils.hpp"
#include "PolygonalMesh.hpp"

using namespace std;
using namespace MeshLibrary;


int main()
{
    double tol1D=setTol1D(); //chiedo all'inizio la tolleranza
    double tol2D=setTol2D(tol1D);
    PolygonalMesh mesh;
    string path="./PolygonalMesh"; //nome della cartella
    if(!importMesh(path,mesh))
        return 1; //se qualcosa va storto
    testEdges(mesh,tol1D);
    testPolygons(mesh,tol2D);

    return 0;
}
