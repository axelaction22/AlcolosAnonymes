
#include<stdlib.h>
#include<vector>
#include "Vin.hpp"
#include "Cave.hpp"
#include "Fournisseur.hpp"
#include<iostream>
using namespace std;

Vin createVinConso(int id, string rp,string cru,string nom,int millesime){
    Vin v = Vin(id, rp, cru, nom, millesime);
    return v;
}


int main(){
    vector<Vin> vins;
    vector<Cave> caves;
    vector<Fournisseur> fournisseurs;
    // Ces listes contiennent toutes les instances d'objets, tout objet en connaissant un autre doit recuperer un pointeur vers celui-ci 

    Cave *cave1 = new Cave(01,"Cave Bordeaux","bordeaux, duh");
    Cave *cave2 = new Cave(02,"Cave Champagne","champagne");
    VinGarde* Vin1 = new VinGarde(1,"Bordeaux","AOP","Chateau Quelquechose",2003,"3 years");
    VinConso* Vin2 = new VinConso(2,"Champagne","AOP","Chateau Truc",2016,2025);
    cave1->ajouterVin(Vin1, 50.0);
    cave1->ajouterVin(Vin2, 35.0);
    cave1->RetirerVin(Vin1);

    cave1->toString();
    cave1->afficherListeVente();
    cave1->afficherListeVins();
}

