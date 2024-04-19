#pragma once

#include <iostream>
#include "PolygonalMesh.hpp"

using namespace std;

namespace MeshLibrary{
bool importCell0Ds(const string& fileName, PolygonalMesh& mesh);
bool importCell1Ds(const string& fileName, PolygonalMesh& mesh);

bool importCell2Ds(const string& fileName, PolygonalMesh& mesh);

bool importMesh(const string& path, PolygonalMesh& mesh);


//per settare la tolleranza
double setTol1D();
double setTol2D(const double tol1D);
//test
void testEdges(PolygonalMesh& mesh, const double tol1D);
void testPolygons(PolygonalMesh& mesh, const double tol2D);

double NormCrossPr(Vector2d& v1, Vector2d& v2);
}
