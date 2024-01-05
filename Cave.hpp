/*
    Represente une cave a vin avec un stock de vins
    
*/
#ifndef CAVE_HPP
#define CAVE_HPP

#include<vector>
#include<string>
using namespace std;

#include<vector>
#include"Vin.hpp"
#include"Fournisseur.hpp"
class Fournisseur;
class Offre;
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
        ~Cave();
        bool ajouterVin(Vin* vin, float prix);//ajouter un vin a la vente
        void RetirerVin(Vin* vin);
        std::vector<Vin*> getListeVin();
        Vin* getVin(int i);
        bool ajouterVente(Vente* vente);///ajoute une vente que propose la cave
        int getNombreVin();
        Vente* getVente(int i);
        int getNombreVente();
        void prendreOffre(Offre* const offre);
        void retirerOffre(Offre* const offre);
        std::string getNom();
        int getIdentifiant();
        void afficherResume() const;
        void afficherListeVins() const;
        void afficherListeVente() const;
        std::string getSaveFormat(std::vector<VinGarde> const vinsGarde,std::vector<VinConso> const vinsConso,std::vector<Fournisseur> fournisseurs);

};
// Classe d'association avec vin, prix de vente par vin
class Vente{
    private : 
        Cave* vendeur;
        Vin* vin;
        float prixVente;
        std::vector<Offre*> listeOffre;
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
        std::vector<Offre*> getListeOffre();
        void afficherResume () const ;
        void afficherListeOffre();
};



#endif