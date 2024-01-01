/*
    Represente une cave a vin avec un stock de vins
    
*/
#ifndef CAVE_HPP
#define CAVE_HPP

#include<vector>
#include<string>

#include"Vin.hpp"
#include"Fournisseur.hpp"

class Vente;
//represente une cave vendant des vins;
class Cave{
    private :       
        int identifier; 
        std::string nom;
        std::string adresse;
        std::vector<Vin*> listeVins;
        std::vector<Vente*> listeVente;
    public :
        Cave(int identifier, std::string nom, std::string adresse);
        bool ajouterVin(Vin* vin, float prix);//ajouter un vin a la vente
        void RetirerVin(Vin *vin);
        Vin *getVin(int i);
        Vente* getVente(int i);
        void prendreOffre(Offre* const offre);
        void retirerOffre(Offre* const offre);

};
// Classe d'association avec vin, prix de vente par vin
class Vente{
    private : 
        Cave* vendeur;
        Vin* vin;
        float prixVente;
        vector<Offre*> listeOffre;
    public : 
        Vente(Cave* c, Vin* v, float prix);
        float getPrixVente();
        void setPrixVente(float p);
        Vin* getVin();
        void setVin(Vin* v);
        Cave* getVendeur();
        void setVendeur(Cave* c);
        void prendreOffre(Offre* const offre);
        void retirerOffre(Offre* const offre);
};



#endif