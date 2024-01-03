#ifndef VIN_CPP
#define VIN_CPP

#include "Vin.hpp"

using namespace std;

Vin::Vin(int id, string rp, string cru, string nom, int millesime){
    identifiant = id;
    regionProd = rp;
    this->cru = cru;
    this->nom = nom;
    this->millesime = millesime;
}

int Vin::getIdentifiant(){return identifiant;}

string Vin::getRegionProd(){return regionProd;}

string Vin::getCru(){return cru;}

string Vin::getNom(){return nom;}

int Vin::getMillesime(){return millesime;}

VinGarde::VinGarde(int id, string rp,string cru,string nom,int millesime, string conservMin) : Vin(id, rp, cru, nom, millesime)
{
    this->conservMin = conservMin;
}

VinConso::VinConso(int id, string rp,string cru,string nom,int millesime, int annee) : Vin (id, rp, cru, nom, millesime)
{
    this->annee = annee;
}

void Vin::afficherResume(){
    cout<<nom<<":"<<endl;
    cout<<"Région de production: "<<regionProd<<endl;
    cout<<"Cru: "<<cru<<endl;
    cout<<"Millenisme: "<<millesime<<endl;
}


#endif

