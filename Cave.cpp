#ifndef CAVE_CPP
#define CAVE_CPP


#include "Cave.hpp"
#include<vector>
#include<algorithm>
#include<iterator>
#include<iostream>
using namespace std;

Cave::Cave(int identifier, string nom, string adresse){
    this->identifier = identifier;
    this->nom = nom;
    this->adresse = adresse;
}
/// @brief ajoute un vin a une cave et crée l'association Vente avec le prix de vente.
/// @param vin 
/// @param p
/// @returns true si succes et false si vin deja present 
bool Cave::ajouterVin(Vin *vin, float prix){
    //Si on ne trouve pas le vin dans la liste, on le rajoute
    if(find(listeVins.begin(),listeVins.end(),vin) == listeVins.end()){
        listeVins.push_back(vin);
        Vente* v = new Vente(this, vin, prix);
        listeVente.push_back(v);
        return true;
    }
    return false;
    
}
void Cave::RetirerVin(Vin* vin){
    if(find(listeVins.begin(),listeVins.end(),vin)!=listeVins.end()){
        listeVins.erase(find(listeVins.begin(),listeVins.end(),vin));//effacer le vin de la listeVins
    }
    //effacer les ventes associées au Vin;
    vector<vector<Vente*>::iterator> toRemove;
    vector<Vente*>::iterator it;
    for(it = listeVente.begin();it<listeVente.begin();it++){
        if((*it)->getVin() == vin){
            toRemove.push_back(it);
        }
    }
    for(vector<Vente*>::iterator it : toRemove){
        listeVente.erase(it);
    }
}
Vin* Cave::getVin(int i){
    return listeVins.at(i);
}
Vente* Cave::getVente(int i){return listeVente.at(i);}
void Cave::prendreOffre(Offre* const offre){
    for (Vente* vente : listeVente){
        if(vente->getVin() == offre->getVin()){
            vente->prendreOffre(offre);
        }
    }
}
void Cave::retirerOffre(Offre* const offre){
    for(Vente* vente : listeVente){
        vente->retirerOffre(offre);
    }
}

void Cave::afficherResume(){
    cout<<"Nom: "<<nom<<endl;
    cout<<"Adresse: "<<adresse<<endl;
}
//Affiche un rapide résumer des Vins- Pourra avoir de chaque vin via la fonction afficherdetail() dans vin
void Cave::afficherListeVins(){
    cout<<"Liste des Vins: "<<endl;
    for (Vin* vin : listeVins) {
        if (vin != nullptr) { // Vérifie que le pointeur n'est pas nul avant de l'utiliser
            vin->afficherResume();
            cout<<endl;
        }
}
}
//Affiche un rapide résumer des ventes - Pourra avoir de chaque vente via la fonction afficherdetail() dans vente
void Cave::afficherListeVente(){
    cout<<"Liste des Ventes: "<<endl;
    for (Vente* vente : listeVente) {
        if (vente != nullptr) { // Vérifie que le pointeur n'est pas nul avant de l'utiliser
           vente->afficherResume();
           cout<<endl;
        }
}
}

//Vente : 
Vente:: Vente(Cave* c, Vin* v, float prix){
    vendeur = c;
    vin = v;
    prixVente = prix;
}
Cave*   Vente::getVendeur(){return vendeur;}
void    Vente::setVendeur(Cave* c){vendeur = c;}
Vin*    Vente::getVin(){return vin;}
void    Vente::setVin(Vin* v){vin = v;}
float   Vente::getPrixVente(){return prixVente;}
void    Vente::setPrixVente(float p){prixVente = p;}

void Vente::prendreOffre(Offre* const offre){
    if(find(listeOffre.begin(),listeOffre.end(),offre) == listeOffre.end()){
        listeOffre.push_back(offre);
    }
}
void Vente::retirerOffre(Offre* const offre){
    if(*find(listeOffre.begin(),listeOffre.end(),offre) != offre){
        return;
    }

    listeOffre.erase(find(listeOffre.begin(),listeOffre.end(),offre));
}

void Vente::afficherResume(){
    cout<<"Cave :"<<endl;
    vendeur->afficherResume();
    cout<<"Vin :"<<endl;
    vin->afficherResume();
    cout<<"Prix :"<<prixVente<<endl;
    cout<<endl;
}

void Vente::afficherListeOffre(){
    cout<<"Liste des Ventes: "<<endl;
    for (Offre* offre : listeOffre) {
        if (offre != nullptr) { // Vérifie que le pointeur n'est pas nul avant de l'utiliser
            offre->afficherResume();
            cout<<endl;
        }
    }
}


#endif

