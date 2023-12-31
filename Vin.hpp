/* 
    Represente les types de vin
    Vin : classe generale
    VinGarde : vin a garder X année avant conso
    VinConso : vin a consommer avant X
*/

#ifndef VIN_HPP
#define VIN_HPP

#include <iostream>
#include<stdio.h>
#include<string>
#include<vector>



class Vin {
    protected :
        int identifiant;
        std::string regionProd;
        std::string cru;
        std::string nom;
        int millesime; //annee de recolte
        Vin(int id, std::string rp,std::string cru,std::string nom,int millesime);

    public :
        ~Vin();
        int getIdentifiant();
        std::string getRegionProd();
        std::string getCru();
        std::string getNom();
        int getMillesime();
        void afficherResume();
        virtual std::string getSaveFormat();
};


class VinGarde : public Vin{
    private :
        std::string conservMin;
    public : 
        VinGarde(int id, std::string rp,std::string cru, std::string nom,int millesime, std::string conservMin);
        
        std::string getSaveFormat() override;
};
class VinConso : public Vin{
    private :
        int annee;//annee de consommation maximum
    public : 
        VinConso(int id, std::string rp,std::string cru,std::string nom,int millesime, int annee);
        std::string getSaveFormat() override;

};




#endif