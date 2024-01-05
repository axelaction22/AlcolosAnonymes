#ifndef FOURNISSEUR_CPP
#define FOURNISSEUR_CPP

#include "Fournisseur.hpp"
#include<algorithm>
#include<string>
#include<vector>

using namespace std;

//Fournisseur, etablissemant vendant des vins, fournissant des Offres de Vin et pouvant appliquer des Reductions

Fournisseur::Fournisseur(int identifiant, string nom, string adresse){
    this->identifiant = identifiant;
    this->nom         = nom;
    this->adresse     = adresse;
}
Offre* Fournisseur::CreerOffre(Vin* v, float price){
    Offre* offre = new Offre(v,price,this);
    offres.push_back(offre);
    return offre;
}
void Fournisseur::deleteOffre(Offre* offre,vector<Cave> const listeCave){
    //Supprimer l'offre des ventes associées
    for(Cave cave : listeCave){
        cave.retirerOffre(offre);
    }
    offres.erase(find(offres.begin(),offres.end(),offre));
    delete offre;
}
Reduction* Fournisseur::creerReduction(int min, int max, float percent){
    Reduction* reduc = new Reduction(percent,min,max);
    reductionsOffertes.push_back(reduc);
    return reduc;
}
void Fournisseur::deleteReduction(Reduction* reduc){
    reductionsOffertes.erase(find(reductionsOffertes.begin(),reductionsOffertes.end(),reduc));
}
void Fournisseur::afficherResume(){
    cout<<"Nom du Fournisseur :"<<nom<<endl;
    cout<<"Adresse :"<<adresse<<endl;
}
void Fournisseur::afficherListeOffres(){
    cout<<"Liste des Offres du Fournisseur : "<<nom<<endl;
    for (Offre* offre : offres) {
        if (offre != nullptr) { // Vérifie que le pointeur n'est pas nul avant de l'utiliser
           offre->afficherResume();
        }
    }
}
void Fournisseur::afficherListeReductions(){
    cout<<"Liste des Reductions du Fournisseur : "<<nom<<endl;
    for (Reduction* reduction : reductionsOffertes) {
        if (reduction != nullptr) { // Vérifie que le pointeur n'est pas nul avant de l'utiliser
           reduction->afficherResume();
           cout<<endl;
        }
    }
}

bool Fournisseur::operator==(const Fournisseur& f) const {
            return (
                identifiant == f.identifiant &&
                nom == f.nom &&
                adresse == f.adresse &&
                equal(offres.begin(),offres.end(),f.offres.begin()) &&
                equal(reductionsOffertes.begin(),reductionsOffertes.end(),f.reductionsOffertes.begin())
            );
        }

string Fournisseur::getSaveFormat(vector<VinGarde> vinsGardes,vector<VinConso> vinsConsos){
    string s = "";
    s += to_string(identifiant) + "\n";
    s += nom + "\n";
    s += adresse + "\n[\n";
    for(Offre* offre : offres){//sauvegarde du code de Vin + prix
        for(int i=0;i<vinsGardes.size();i++){
            if(offre->getVin()->getNom() == vinsGardes.at(i).getNom()){
                s += "G" + to_string(i) + "\n";
                s += to_string(offre->getPrix())+"\n";
            }
            if(offre->getVin()->getNom() == vinsConsos.at(i).getNom()){
                s += "C" + to_string(i) + "\n";
                s += to_string(offre->getPrix())+"\n";
            }
        }
    } s += "]\n[\n";//Fin des offres du fournisseur, debut des reducs
    for(Reduction* reduc : reductionsOffertes){
        s +=  to_string(reduc->getBouteillesMin())+ "\n";
        s +=  to_string(reduc->getBouteillesMax())+ "\n";
        s +=  to_string(reduc->getPercentage())   + "\n";
    } 
}








//Offre

Offre::Offre(Vin* v, float price, Fournisseur* f){
    vin = v;
    prix = price;
    fournisseur = f;
}

float Offre::getPrix(){return prix;}

Vin*         Offre::getVin() { return vin; }
Fournisseur* Offre::getFournisseur(){return fournisseur;}

void Offre::afficherResume(){
    cout<<"Vin: "<<vin->getNom()<<endl;
    cout<<"Prix de l'offre: "<<prix<<endl;
    cout<<"Fournisseur: "<<fournisseur<<endl;
}

//Reduction
Reduction::Reduction(float per, int min, int max){
    percentage = per;
    BouteillesMax = max;
    BouteillesMin = min;
}
void Reduction::afficherResume(){
    cout<<"La reduction est de :"<<percentage<<endl;
    cout<<"Nombre de bouteilles minimun :"<<BouteillesMin<<endl;
    cout<<"Nombre de bouteilles maximun :"<<BouteillesMax<<endl;
}
float Reduction::getPercentage() const {
    return percentage;
}
int Reduction::getBouteillesMax() const {
    return BouteillesMax;
}
int Reduction::getBouteillesMin() const {
    return BouteillesMin;
}

#endif