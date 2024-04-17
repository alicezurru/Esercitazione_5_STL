#pragma once

#include <iostream>
#include "PolygonalMesh.hpp"

using namespace std;

namespace MeshLibrary{
bool importCell0Ds(const string& fileName, PolygonalMesh& mesh);
bool importCell1Ds(const string& fileName, PolygonalMesh& mesh,double tol1D);

bool importCell2Ds(const string& fileName, PolygonalMesh& mesh,double tol1D);

bool importMesh(const string& path, PolygonalMesh& mesh,double tol1D, double tol2D);
}

//per settare la tolleranza
double setTol1D();
double setTol2D(const double tol1D);
