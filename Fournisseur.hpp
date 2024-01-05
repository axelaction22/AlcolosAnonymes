#ifndef FOURNISSEUR_HPP
#define FOURNISSEUR_HPP
#include<stdlib.h>
#include"Vin.hpp"
#include"Cave.hpp"

using namespace std;
class Fournisseur;
class Cave;

class Offre{// un fournisseur offre des vins a un prix
    private :   
        Vin* vin;
        float prix;
        Fournisseur* fournisseur;
    public : 
        Offre(Vin* v, float price, Fournisseur* f);
        Vin* getVin();
        float getPrix();
        Fournisseur* getFournisseur();
        void afficherResume();
};

class Reduction{
    private :
        float percentage;
        int BouteillesMin;
        int BouteillesMax;
    public :
        Reduction(float per,int min, int max);
        void afficherResume();
};

class Fournisseur{
    private :
        std::string identifiant;
        std::string nom;
        std::string adresse;
        std::vector<Offre*> offres;
        std::vector<Reduction*> reductionsOffertes;
    public :
        Fournisseur(std::string identifiant, std::string nom, std::string adresse);
        Offre* CreerOffre(Vin* v, float price);
        void deleteOffre(Offre* offre,vector<Cave> const listeCave);
        Reduction* creerReduction(int min, int max, float percent);
        void deleteReduction(Reduction* reduc);
        void afficherResume();
        void afficherListeOffres();
        void afficherListeReductions();
        bool operator==(const Fournisseur& f) const ;
        std::string getSaveFormat();
};

#endif