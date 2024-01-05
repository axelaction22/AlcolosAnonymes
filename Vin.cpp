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

Vin::~Vin(){}
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
string Vin::getSaveFormat(){
    return "wrong function!";
}
/// @brief chaine de caractere representant les donnés d'un VinGarde, pour sauvegarde.
string VinGarde::getSaveFormat(){
    string s = "";
    s += "G;";
    s += to_string(identifiant) + ";"; // std::to_string to convert in to string 
    s += regionProd  + ";";
    s += cru  + ";";
    s += nom  + ";";
    s += to_string(millesime) + ";";
    s += conservMin + "\n";
    return s;
}

/// @brief chaine de caractere representant les donnés d'un VinGarde, pour sauvegarde.
string VinConso::getSaveFormat(){
    string s = "";
    s += "C;";
    s += to_string(identifiant) + ";"; // std::to_string to convert in to string 
    s += regionProd  + ";";
    s += cru  + ";";
    s += nom  + ";";
    s += to_string(millesime) + ";";
    s += to_string(annee) + "\n";
    return s;

}

#endif

