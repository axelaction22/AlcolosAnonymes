
#include<stdlib.h>
#include<vector>
#include "Vin.hpp"
#include "Cave.hpp"
#include "Fournisseur.hpp"
#include<iostream>
#include<fstream>

using namespace std;


void Save(vector<Vin> const vins,vector<Cave> const caves,vector<Fournisseur> const fournisseurs){
    //sauvegarde les trois objets principaux et leurs liens,dans l'emplacement d'ou est appelé l'executable
    string dirVin = "SavedWines.txt";
    string dirCaves = "SavedWines.txt";
    string dirFournisseurs = "SavedWines.txt";
    fstream fileVin;
    fstream fileCave;
    fstream fileFournisseur;
    
    fileVin.open(dirVin,ios::out);
    fileCave.open(dirCaves,ios::out);
    fileFournisseur.open(dirFournisseurs,ios::out);



    for(Vin v : vins){
        Vin* vptr = &v;
        fileVin << vptr->getSaveFormat();
    }

    fileVin.close();
    fileCave.close();
    fileFournisseur.close();
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

    cave1->afficherResume();
    cave1->afficherListeVente();
    cave1->afficherListeVins();
    vins.push_back(*Vin1);
    vins.push_back(*Vin2);
    Save(vins,caves,fournisseurs);
}

