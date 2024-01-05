
#include<stdlib.h>
#include<vector>
#include "Vin.hpp"
#include "Cave.hpp"
#include "Fournisseur.hpp"
#include<iostream>
#include<fstream>

using namespace std;


void Save(vector<VinGarde> const vinsGarde, vector<VinConso> const  vinsConso,vector<Cave> const caves,vector<Fournisseur> const fournisseurs){
    //sauvegarde les trois objets principaux et leurs liens,dans l'emplacement d'ou est appelé l'executable
    string dirVin = "SavedWines.txt";
    string dirCaves = "SavedCaves.txt";
    string dirFournisseurs = "SavedFournisseurs.txt";
    fstream fileVin;
    fstream fileCave;
    fstream fileFournisseur;
    
    fileVin.open(dirVin,ios::out);
    fileCave.open(dirCaves,ios::out);
    fileFournisseur.open(dirFournisseurs,ios::out);

    //important l'ordre de sauvegarde et de chargement est Vin >> Fournisseur >> Cave
    //du au besoin d'information des classes precedentes.
    //(techniquement pas obligatoire pour sauvegarde mais definitivement pour chargement)

    for(VinGarde vg : vinsGarde){
        fileVin << vg.getSaveFormat();
    }
    for(VinConso vc : vinsConso){
        fileVin << vc.getSaveFormat();
    }
    for(Fournisseur f : fournisseurs){
        fileFournisseur << f.getSaveFormat(vinsGarde,vinsConso);
    }
    for(Cave c : caves){
        fileCave << c.getSaveFormat(vinsGarde,vinsConso,fournisseurs);
    }

    fileVin.close();
    fileCave.close();
    fileFournisseur.close();
}



int main(){
    vector<VinGarde> vinsGarde;
    vector<VinConso> vinsConso;
    vector<Cave> caves;
    vector<Fournisseur> fournisseurs;
    // Ces listes contiennent toutes les instances d'objets, tout objet en connaissant un autre doit recuperer un pointeur vers celui-ci 

    Cave *cave1 = new Cave(01,"Cave Bordeaux","bordeaux, duh");
    Cave *cave2 = new Cave(02,"Cave Champagne","champagne");
    VinGarde* Vin1 = new VinGarde(1,"Bordeaux","AOP","Chateau Quelquechose",2003,"3 years");
    VinConso* Vin2 = new VinConso(2,"Champagne","AOP","Chateau Truc",2016,2025);
    cave1->ajouterVin(Vin1, 50.0);
    cave1->ajouterVin(Vin2, 35.0);
    

    cave1->afficherResume();
    cave1->afficherListeVente();
    cave1->afficherListeVins();
    vinsGarde.push_back(*Vin1);
    vinsConso.push_back(*Vin2);
    caves.push_back(*cave1);
    Save(vinsGarde,vinsConso,caves,fournisseurs);
    delete Vin1;
    delete Vin2;
    delete cave1;
    delete cave2;
}

