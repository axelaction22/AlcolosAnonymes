#ifndef FOURNISSEUR_CPP
#define FOURNISSEUR_CPP

#include "Fournisseur.hpp"
#include<algorithm>

//Fournisseur, etablissemant vendant des vins, fournissant des Offres de Vin et pouvant appliquer des Reductions

Fournisseur::Fournisseur(string identifiant, string nom, string adresse){
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








//Offre

Offre::Offre(Vin* v, float price, Fournisseur* f){
    vin = v;
    prix = price;
    fournisseur = f;
}

float Offre::getPrix(){return prix;}

Vin*         Offre::getVin() { return vin; }
Fournisseur* Offre::getFournisseur(){return fournisseur;}

//Reduction
Reduction::Reduction(float per, int min, int max){
    percentage = per;
    BouteillesMax = max;
    BouteillesMin = min;
}



#endif