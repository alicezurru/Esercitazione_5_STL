#include "Utils.hpp"
#include "PolygonalMesh.hpp"
#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

namespace MeshLibrary {
bool importMesh(const string& path, PolygonalMesh& mesh)
{
    if (!importCell0Ds(path+ "./Cell0Ds.csv", mesh))
        return false;
    else{//controllo sui marker
        cout<<"Cells0D:"<<endl;
        for(auto& el: mesh.VerticesMarker) //per ogni elemento della mappa dove l'elemento è la tupla chiave valore
        {
            cout<<"key: "<< el.first<<endl; //first è la chiave
            for(auto& id: el.second) //nella lista (second)
                cout<<id<< " ";
            cout <<endl;

        }
    }

    if (!importCell1Ds(path+ "./Cell1Ds.csv", mesh))
        return false;
    else{//controllo sui marker
        cout<<"Cells1D:"<<endl;
        for(auto& el: mesh.EdgesMarker)
        {
            cout<<"key: "<< el.first<<endl; //first è la chiave
            for(auto& id: el.second) //nella lista (second)
                cout<<id<< " ";
            cout <<endl;

        }

    }

    if (!importCell2Ds(path+ "./Cell2Ds.csv", mesh))
        return false;
    else{//per controllo che numero di lati e vertici coincidano
        for(unsigned int i=0;i<mesh.NumberofCell2Ds;i++){
            cout<< "id:"<<mesh.IdCell2Ds[i]<<" Vertici:"<<(mesh.VerticesCell2Ds[i]).size()<<" Lati:"<<(mesh.EdgesCell2Ds[i]).size()<<endl;
        }
    }
    return true;
}


bool importCell0Ds(const string& fileName, PolygonalMesh& mesh){
    ifstream file(fileName);
    if(file.fail())
        return false;
    string header;
    getline(file, header); //buttiamo la prima riga

    list<string> lines;
    string line;
    while(getline(file,line))
    {
        lines.push_back(line); //va avanti finchè non fallisce: quando raggiungo la fine del file
    } //leggo tutte le righe e le metto in una lista
    file.close();

    mesh.NumberofCell0Ds= lines.size(); //il numero di righe del file corrisponde al numero di vertici
    mesh.CoordinatesCell0Ds.reserve(mesh.NumberofCell0Ds); //modifico la capacità per allocare la giusta memoria
    mesh.IdCell0Ds.reserve(mesh.NumberofCell0Ds);
    mesh.MarkerCell0Ds.reserve(mesh.NumberofCell0Ds);


    for(const string& line:lines) //per ogni riga nella lista
    {
        istringstream convert(line);
        unsigned int id;
        unsigned int marker;
        char c; //per i ;
        Vector2d coordinates;
        convert>>id>>c>>marker>>c>>coordinates(0)>>c>>coordinates(1);

        mesh.IdCell0Ds.push_back(id); //popolo i vettori
        mesh.MarkerCell0Ds.push_back(marker);
        mesh.CoordinatesCell0Ds.push_back(coordinates);

        if (marker!=0){
            auto ret=mesh.VerticesMarker.insert({marker,{id}});
            //prova a inserire la nuova chiave corrispondente alla lista che contiene solo il mio id
            //se non trova già la chiave la inserisce nuova
            //se ritorna false vuol dire che la chiave è gia presente
            if(!ret.second) //se la chiave già esisteva devo aggiungere alla lista
                mesh.VerticesMarker[marker].push_back(id);
        }
    }
        return true;

}

bool importCell1Ds(const string& fileName, PolygonalMesh& mesh){
    ifstream file(fileName);
    if(file.fail())
        return false;
    string header;
    getline(file, header); //buttiamo la prima riga

    list<string> lines;
    string line;
    while(getline(file,line))
    {
        lines.push_back(line);
    }
    file.close();

    mesh.NumberofCell1Ds= lines.size(); //il numero di righe del file corrisponde al numero di lati
    mesh.VerticesCell1Ds.reserve(mesh.NumberofCell1Ds); //modifico la capacità per allocare la giusta memoria
    mesh.IdCell1Ds.reserve(mesh.NumberofCell1Ds);
    mesh.MarkerCell1Ds.reserve(mesh.NumberofCell1Ds);


    for(const string& line:lines) //per ogni riga nella lista
    {
        istringstream convert(line);
        unsigned int id;
        unsigned int marker;
        char c;
        array<unsigned int,2> vertices;
        convert>>id>>c>>marker>>c>>vertices[0]>>c>>vertices[1];

        mesh.IdCell1Ds.push_back(id);
        mesh.MarkerCell1Ds.push_back(marker);
        mesh.VerticesCell1Ds.push_back(vertices);

        if (marker!=0){
            auto ret=mesh.VerticesMarker.insert({marker,{id}});
            if(!ret.second) //se la chiave già esisteva devo aggiungere alla lista
                mesh.EdgesMarker[marker].push_back(id); //aggiunge
        }

        }

    return true;


}

bool importCell2Ds(const string& fileName, PolygonalMesh& mesh){
    ifstream file(fileName);
    if(file.fail())
        return false;
    string header;
    getline(file, header); //buttiamo la prima riga

    list<string> lines;
    string line;
    while(getline(file,line))
    {
        lines.push_back(line);
    }
    file.close();

    mesh.NumberofCell2Ds= lines.size(); //il numero di righe del file corrisponde al numero di vertici
    mesh.VerticesCell2Ds.reserve(mesh.NumberofCell2Ds); //modifico la capacità per allocare la giusta memoria
    mesh.EdgesCell2Ds.reserve(mesh.NumberofCell2Ds);
    mesh.IdCell2Ds.reserve(mesh.NumberofCell2Ds);


    for(const string& line:lines) //per ogni riga nella lista
    {
        istringstream convert(line);
        unsigned int id;
        char c;
        unsigned int nVertices;
        unsigned int nEdges;
        unsigned int marker;
        vector<unsigned int> vertices;
        vector<unsigned int> edges;
        convert>>id>>c>>marker>>c>>nVertices;

        vertices.reserve(nVertices);
        for(unsigned int i=0;i<nVertices;i++) {
            unsigned int v;
            convert>>c>>v;
            vertices.push_back(v);
        }

        convert>>c>>nEdges;
        edges.reserve(nEdges);
        for(unsigned int i=0;i<nEdges;i++) {
            unsigned int v;
            convert>>c>>v;
            edges.push_back(v);
        }

        mesh.IdCell2Ds.push_back(id); //popolo i vettori
        mesh.VerticesCell2Ds.push_back(vertices);
        mesh.EdgesCell2Ds.push_back(edges);


    }

    return true;


}

double setTol1D() {
    double tolUtente;
    cout<<"Inserire tolleranza per la distanza tra punti: "<<endl;
    cin>>tolUtente;
    double tol= max(10*numeric_limits<double>::epsilon(), tolUtente);
    cout<<"Tolleranza: "<<tol<<endl;
    return tol;
}

double setTol2D(const double tol1D) {
    double tolUtente;
    cout<<"Inserire tolleranza per l'area dei poligoni: "<<endl;
    cin>>tolUtente;
    double tol= max(10*numeric_limits<double>::epsilon(), tolUtente);
    tol=max(tol, pow(tol1D,2)*sqrt(3)/4); //aggiungo la minima area di un triangolo equilatero
    cout<<"Tolleranza: "<<tol<<endl;
    return tol;
}

void testEdges(PolygonalMesh& mesh, const double tol1D){
    for(auto& id: mesh.IdCell1Ds){
        unsigned int idStart= (mesh.VerticesCell1Ds[id])[0];
        unsigned int idEnd= (mesh.VerticesCell1Ds[id])[1];

        if (sqrt(pow((mesh.CoordinatesCell0Ds[idStart])[0]-(mesh.CoordinatesCell0Ds[idEnd])[0],2)+//guardo se la distanza tra i punti è minore della tolleranza
                 pow((mesh.CoordinatesCell0Ds[idStart])[1]-(mesh.CoordinatesCell0Ds[idEnd])[1],2))<tol1D){
            cerr<<"ERROR: "<<id<<" has zero length"<<endl;
        }
    }
}

void testPolygons(PolygonalMesh& mesh, const double tol2D){
    for(auto& id:mesh.IdCell2Ds){
        vector<unsigned int> idV = mesh.VerticesCell2Ds[id];
        //calcolo l'area del poligono (0.5*sum(0>n-1)(x(i)y(i+1)-x(i+1)y(i))
        double A=0.0;
        for (unsigned int i=0;i<idV.size()-1;i++){
            A=A+NormCrossPr(mesh.CoordinatesCell0Ds[idV[i]],mesh.CoordinatesCell0Ds[idV[i+1]]);
        }
        //aggiungo l'ultimo con il primo
        A=A+NormCrossPr(mesh.CoordinatesCell0Ds[idV[0]],mesh.CoordinatesCell0Ds[idV[idV.size()-1]]);
        A=0.5*A;
        if (A<tol2D){
            cerr<<"ERROR: "<<id<<" has zero area"<<endl;
        }
    }

}


double NormCrossPr(Vector2d& v1, Vector2d& v2){
    return abs(v1[0]*v2[1]-v1[1]*v2[0]);
}
}
