
#include<stdlib.h>
#include<vector>
#include "Vin.hpp"
#include "Cave.hpp"
#include "Fournisseur.hpp"
#include<iostream>
#include <algorithm>
#include <limits>


#include<fstream>

using namespace std;

void Load(vector<VinGarde>* vinsGarde, vector<VinConso>* vinsConso, vector<Cave>* caves, vector<Fournisseur>* fournisseurs){
    //etape 1, vider les listes existantes
    for(Fournisseur f : *fournisseurs){
        while(f.getListeOffre().size()>0){
            f.deleteOffre(f.getListeOffre().at(0),*caves);
        }
        while(f.getListeReduction().size() > 0){
            f.deleteReduction(f.getListeReduction().at(0));
        }
    }
    while(fournisseurs->size() > 0){
        fournisseurs->erase(fournisseurs->begin());
    }

    for(Cave c : *caves){
        while(c.getListeVin().size() > 0){
            c.RetirerVin(c.getListeVin().at(0));
        }
    }
    while(caves->size() > 0){
        caves->erase(caves->begin());
    }
    while(vinsConso->size() > 0){
        vinsConso->erase(vinsConso->begin());
    }
    while(vinsGarde->size() > 0){
        vinsGarde->erase(vinsGarde->begin());
    }
    
    
    
    
    
    //etape 2 reconstruire les listes sauvegardées
    string dirVin = "SavedWines.txt";
    string dirCaves = "SavedCaves.txt";
    string dirFournisseurs = "SavedFournisseurs.txt";
    



    //Chargement des vins
    ifstream file(dirVin);
    string line;
    while(getline(file,line)){
        if(line.substr(0,0) == "G"){
            
            size_t semicolon = line.find(";");//emplacemet du ; trouvé
            int identifiant  = stoi(line.substr(2,2));//ne bougera jamais

            semicolon = line.find(";",4);
            string regionProd = line.substr(semicolon,line.find(";")-1);

            semicolon = line.find(";",semicolon+1);
            string cru = line.substr(semicolon,line.find(";")-1);

            semicolon = line.find(";",semicolon+1);
            string nom = line.substr(semicolon,line.find(";")-1);

            semicolon = line.find(";",semicolon+1);
            int millesime = stoi(line.substr(semicolon,line.find(";")-1));

            semicolon = line.find(";",semicolon+1);
            string conservMin = line.substr(semicolon,line.find(";")-1);

            vinsGarde->push_back(VinGarde(identifiant,regionProd,cru,nom,millesime,conservMin));
        }
       
    }




    
}

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

void menu(vector<Cave>& caves,vector<Vin>& vins,vector<Fournisseur>& fournisseurs);
void menuListeCave(vector<Cave>& caves);
void menuListeVin(vector<Vin>& vins, vector<Cave>& caves);
void menuListeFournisseur(vector<Fournisseur>& fournisseurs);
void AjouterVin(Cave *cave,vector<Vin>& vins);
void RetirerVin(Cave *cave);
int main(){
    vector<VinGarde> vinsGarde;
    vector<VinConso> vinsConso;
    vector<Cave> caves;
    vector<Fournisseur> fournisseurs;
    // Ces listes contiennent toutes les instances d'objets, tout objet en connaissant un autre doit recuperer un pointeur vers celui-ci 
    /*
    Cave *cave1 = new Cave(01,"Cave Bordeaux","bordeaux, duh");
    Cave *cave2 = new Cave(02,"Cave Champagne","champagne");
    VinGarde* Vin1 = new VinGarde(1,"Bordeaux","AOP","Chateau Quelquechose",2003,"3 years");
    VinConso* Vin2 = new VinConso(2,"Champagne","AOP","Chateau Truc",2016,2025);
    cave1->ajouterVin(Vin1, 50.0);
    cave1->ajouterVin(Vin2, 35.0);
    cave1->RetirerVin(Vin1);
    menu(caves,vinsGarde,vinsConso,fournisseurs);

    vinsGarde.push_back(*Vin1);
    vinsConso.push_back(*Vin2);
    caves.push_back(*cave1);
    */

    Load(&vinsGarde,&vinsConso,&caves,&fournisseurs);
    vinsConso.at(0).afficherResume();
    vinsGarde.at(0).afficherResume();
    /*
    delete Vin1;
    delete Vin2;
    delete cave1;
    delete cave2;
    */
}

void menu(vector<Cave>& caves,vector<VinGarde>& vinsGarde,vector<VinConso>& vinsConso,vector<Fournisseur>& fournisseurs){
    int reponse;
   
    while(true){
        cout<<"Bienvenue dans le menu de la cave à vin, que souhaitez vous faire :"<<endl;
        cout<<"Afficher le menu Caves: 1"<<endl;
        cout<<"Afficher le menu vins: 2"<<endl;
        cout<<"Afficher liste des fournisseurs: 3"<<endl;
        cin>>reponse;
        switch (reponse)
        {
            case 1:
                menuListeCave(caves,vinsGarde,vinsConso);
                break;
            case 2:
                menuListeVin(vinsGarde,vinsConso,caves,fournisseurs);
                break;
            case 3:
                menuListeFournisseur(fournisseurs);
            default:
                cout<<"Erreur veuillez recommencer"<<endl;
                break;
        }
    }
   
}






void menuListeCave(vector<Cave>& caves,vector<VinGarde>& vinsGarde,vector<VinConso>& vinsConso) {
    
    int reponse=-1;
    while(reponse!=0){
        cout<<endl;
        cout<<endl;
        cout<<"Que souhaitez vous faire: "<<endl;
        cout<<"Revenir au menu précédent: 0"<<endl;
        cout<<"Ajouter une cave: 1"<<endl;
        cout<<"Supprimer une cave: 2"<<endl;
        cout<<"Afficher l'ensemble des caves: 3"<<endl;
        cout<<"Détail sur une cave: 4"<<endl;//Programmer ajout/retrait Vin/Vente + possibilité afficher liste 
        cin>>reponse;
        
        switch (reponse)
        {
        case 1://CREATION CAVE
        {
            int NouveauIdentifiant;
            string NouveauNom;
            string NouvelleAdresse;
            cout<<"Tapez l'identifiant de la nouvelle Cave:"<<endl;
            cin>>NouveauIdentifiant;
            cout<<"Tapez le nom de la nouvelle Cave:"<<endl;
            cin>>NouveauNom;
            cout<<"Tapez l'adresse de la nouvelle Cave:"<<endl;
            cin>>NouvelleAdresse;
            auto it = std::find_if(caves.begin(), caves.end(), [NouveauIdentifiant,NouveauNom](Cave& cave) {
            return cave.getIdentifiant() == NouveauIdentifiant || cave.getNom()==NouveauNom;
            });
            if (it != caves.end()) {
                //Cave déjà existant
            cout<<"Une cave possède déjà le même nom ou identfiant."<<endl;
            } else {
                // Cave non trouvée
                Cave NouvelleCave=Cave(NouveauIdentifiant,NouveauNom,NouvelleAdresse);
                caves.push_back(NouvelleCave);
                cout<<"La Cave a été crée avec succés."<<endl;
                cout<<endl;  
            
            }
            menuListeCave(caves);       
            break;
        }
        case 2:
        {//DESTRUCTION CAVE
            string nom;
            cout<<"Tapez le nom de la Cave à supprimer:"<<endl;
            cin>>nom;
            auto it = std::find_if(caves.begin(), caves.end(), [nom](Cave& cave) {
            return cave.getNom() == nom;
            });
            if (it != caves.end()) {
                // Cave trouvée
                delete &*it;
                cout << "La Cave: '" << nom << "' a été supprimé" <<endl;
            } else {
                // Cave non trouvée
                cout << "La Cave: '" << nom << "' n'a pas été trouvée." <<endl;
            }
            break;
            
        }
        case 3:
        {
        cout << "Liste des Caves: " << endl;
        for (const Cave& cave : caves) {
            cave.afficherResume();
            cout << endl;
        }
        break;
        }
        case 4:
        {
            cout<<"Sur quelle cave voulez avoir des détails?"<<endl;
            string nomRecherche;
            cout<<"Tapez le nom de la Cave à rechercher:"<<endl;
            cin>>nomRecherche;

            auto it = find_if(caves.begin(), caves.end(), [nomRecherche](Cave& cave) {
            return cave.getNom() == nomRecherche;
            });
            if (it != caves.end()) {
                // Cave trouvée
                it->afficherResume();
                it->afficherListeVins();
                it->afficherListeVente();

                reponse=-1;
                while(reponse!=0){
                    cout<<"Que voulez-vous faire:"<<endl;
                    cout<<"Revenir au menu précédent : 0"<<endl;
                    cout<<"Ajouter un vin : 1"<<endl;
                    cout<<"Retirer un vin: 2"<<endl;
                    cin>>reponse;
                    switch (reponse)
                    {
                    case 1:{
                        AjouterVin(&*it,vinsGarde,vinsConso);
                        break;
                    }
                    case 2:{
                        RetirerVin(&*it);
                    }
                    default:
                        cout<<"Erreur Veuillez réssayer";
                        break;
                    }
                }
            
            } else {
                // Cave non trouvée
                cout << "La Cave: '" << nomRecherche << "n'a pas été trouvée." <<endl;
            }
            break; 
        }
        default:
        {
            cout<<"Erreur Veuillez Recommencer"<<endl;
        }
    
    }
    }
    
}

void AjouterVin(Cave *cave,vector<VinGarde>& vinsGarde,vector<VinConso>& vinsConso){
    string nomVin;                   
    int millesime;
    float prix;
    int reponse=-1;

    cout<<"Taper le nom du vin à rajouter"<<endl;
    cin>>nomVin;
    cout<<"Taper le millesime du vin à rajouter"<<endl;
    cin>>millesime;
    cout<<"1:Vin de Garde"<<endl;
    cout<<"2:Vin à Consommer"<<endl;
    cin>>reponse;
    if (reponse==1){
        auto vin = find_if(vinsGarde.begin(), vinsGarde.end(), [nomVin,millesime](Vin& vin) {
        return vin.getNom() == nomVin && vin.getMillesime()==millesime;
        });
        if (vin!=vinsGarde.end()){
            cout<<"Vin trouvé, veuillez lui donner un prix :"<<endl;
            cin>>prix;
            cave->ajouterVin(&*vin,prix);
            cout<<"Le vin a été ajouté avec succés"<<endl;
        }else{
            cout<<"Le vin n'existe pas dans la liste de vins"<<endl;
        }
    }else if(reponse==2){
        auto vin = find_if(vinsConso.begin(), vinsConso.end(), [nomVin,millesime](Vin& vin) {
        return vin.getNom() == nomVin && vin.getMillesime()==millesime;
        });
        if (vin!=vinsConso.end()){
            cout<<"Vin trouvé, veuillez lui donner un prix :"<<endl;
            cin>>prix;
            cave->ajouterVin(&*vin,prix);
            cout<<"Le vin a été ajouté avec succés"<<endl;
        }else{
            cout<<"Le vin n'existe pas dans la liste de vins"<<endl;
        }
    }else{
        cout<<"Erreur retour au menu précédent"<<endl;
    }
    
}

void RetirerVin(Cave *cave){
    string nomVin;                 
    int millesime;
    cout<<"Taper le nom du vin à enlever"<<endl;
    cin>>nomVin;
    cout<<"Taper le millesime du vin à enlever"<<endl;
    cin>>millesime;
    for(int i=0;i<cave->getNombreVin();i++){
            if(cave->getVin(i)->getNom()==nomVin && cave->getVin(i)->getMillesime()){
                cave->RetirerVin(cave->getVin(i));
                cout<<"Le vin a été supprimé avec succés"<<endl;
                return;
            }
        
        }
    cout<<"Aucun vin trouvé."<<endl;
    
}




void menuListeVin(vector<VinGarde>& vinsGarde,vector<VinConso>& vinsConso,vector<Cave>& caves,vector<Fournisseur>& fournisseurs ){
    int reponse=-1;
    cout<<endl;
    cout<<endl;
    cout<<"Que souhaitez vous faire: "<<endl;
    cout<<"Revenir au menu précédent: 0"<<endl;
    cout<<"Ajouter un Vin: 1"<<endl;
    cout<<"Supprimer un vin: 2"<<endl;
    cout<<"Afficher l'ensemble des vins: 3"<<endl;//Programmer ajout/retrait Vin/Vente + possibilité afficher liste 
    cout<<"Détail sur un Vin et son meilleur Prix: 4"<<endl;
    cin>>reponse;
    while (reponse!=0)
    {
    switch (reponse)
        {
        case 1://AJOUTER VIN
        {
            int nouveauIdentifiant;
            string nouvelleRegion;
            string nouveauCru;
            string nouveauNom;
            int nouveauMillenisme;
            reponse=-1;
            cout<<"Tapez l'identifiant du nouveau Vin:"<<endl;
            cin>>nouveauIdentifiant;
            cout<<"Tapez la region de Production du nouveau Vin"<<endl;
            cin>>nouvelleRegion;
            cout<<"Tapez le Cru du nouveau Vin"<<endl;
            cin>>nouveauCru;
            cout<<"Tapez le Nom du nouveau Vin:"<<endl;
            cin>>nouveauNom;
            cout<<"Tapez le Millenisme du nouveau Vin:"<<endl;
            cin>>nouveauMillenisme;
            cout<<"Vin de Garde: 1"<<endl;
            cout<<"Vin de Consomation: 2"<<endl;
            cin>>reponse;
            if (reponse==1){
                auto it = std::find_if(vinsGarde.begin(), vinsGarde.end(), [nouveauNom,nouveauMillenisme](Vin& vin) {
                return vin.getNom() == nouveauNom && vin.getMillesime()==nouveauMillenisme;
                });
                if (it != vinsGarde.end()) {
                    // Vin déjà existant
                cout<<"le vin existe déjà."<<endl;
                } else {
                    // Vin non trouvée
                    string conservation;
                    cout<<"Veuillez donner sa durée de conservation :"<<endl;
                    cin>>conservation;
                    VinGarde NouveauVin=VinGarde(nouveauIdentifiant,nouvelleRegion,nouveauCru,nouveauNom,nouveauMillenisme,conservation);
                    vinsGarde.push_back(NouveauVin);
                    cout<<"Le vin a été crée avec succés."<<endl;
                    cout<<endl;  
                }    
                break;
            }else if (reponse==2){
                auto it = std::find_if(vinsConso.begin(), vinsConso.end(), [nouveauNom,nouveauMillenisme](Vin& vin) {
                return vin.getNom() == nouveauNom && vin.getMillesime()==nouveauMillenisme;
                });
                if (it != vinsConso.end()) {
                    // Vin déjà existant
                cout<<"le vin existe déjà."<<endl;
                } else {
                    // Vin non trouvée
                    int consomation;
                    cout<<"Veuillez donner son année de consomation :"<<endl;
                    cin>>consomation;
                    VinConso NouveauVin=VinConso(nouveauIdentifiant,nouvelleRegion,nouveauCru,nouveauNom,nouveauMillenisme,consomation);
                    vinsConso.push_back(NouveauVin);
                    cout<<"Le vin a été crée avec succés."<<endl;
                    cout<<endl;  
                }    
                break;
            }else{
                cout<<"Erreur retour au menu précédent";
            }
        break;
        }
        case 2://ENLEVER VIN
        {
            string nom;
            int millesime;
            cout<<"Tapez le nom du vin à supprimer:"<<endl;
            cin>>nom;
            cout<<"Tapez le millenisme du vin à supprimer:"<<endl;
            cin>>nom;
            auto it = std::find_if(vinsConso.begin(), vinsConso.end(), [nom,millesime](Vin& vin) {
            return vin.getNom() == nom && vin.getMillesime()==millesime;
            });
            if (it != vinsConso.end()) {
                // vin trouvée
                delete &*it;
                cout<<"Suppression effectué"<<endl;
            }else{
                auto it = std::find_if(vinsGarde.begin(), vinsGarde.end(), [nom,millesime](Vin& vin) {
                return vin.getNom() == nom && vin.getMillesime()==millesime;
                });
                if (it != vinsGarde.end()) {
                    // vin trouvée
                    delete &*it;
                    cout<<"Suppression effectué"<<endl;
                }else{
                    cout<<"le Vin n'existe pas"<<endl;
                }
            }
        break;
        }
        case 3://LISTE VIN
        {
            cout << "Liste des Vins de Garde: " << endl;
            for (Vin& vin : vinsGarde) {
                vin.afficherResume();
                for (Fournisseur& fournisseur : fournisseurs) {
                    fournisseur.afficherOffresvin(&vin);
                }
                cout << endl;
            }
            cout << "Liste des Vins de Consomation: " << endl;
            for (Vin& vin : vinsConso) {
                vin.afficherResume();
                for (Fournisseur& fournisseur : fournisseurs) {
                    fournisseur.afficherOffresvin(&vin);
                }
                cout << endl;
            }
        }
        case 4:
        {   
            string nomRecherche;
            int MillenismeRecherche;
            cout<<"Sur quel Vin voulez avoir des détails?"<<endl;
            cout<<"Tapez le nom du Vin à rechercher:"<<endl;
            cin>>nomRecherche;
            cout<<"Tapez le Millenisme du Vin à rechercher:"<<endl;
            cin>>MillenismeRecherche;

            auto it = find_if(vinsGarde.begin(), vinsGarde.end(), [nomRecherche,MillenismeRecherche](Vin& vin) {
            return vin.getNom() == nomRecherche && vin.getMillesime()==MillenismeRecherche;
            });
            if (it != vinsGarde.end()) {
                // Vin trouvée
                it->afficherResume();
                float meilleurPrix = std::numeric_limits<float>::max();
                Vente* venteVinMeilleurPrix = nullptr;

                for (Cave &cave : caves) {
                    for(int i=0;i<cave.getNombreVente();i++){
                        Vin* vinComparatif=cave.getVente(i)->getVin();
                        float prixComparatif=cave.getVente(i)->getPrixVente();
                        if (vinComparatif->getNom()==nomRecherche && vinComparatif->getMillesime()==MillenismeRecherche && prixComparatif< meilleurPrix){
                            meilleurPrix = prixComparatif;
                            venteVinMeilleurPrix = cave.getVente(i);
                        }
                    }
                }
                if (venteVinMeilleurPrix != nullptr) {
                    cout<<"La meilleure offre de ce Vin est:"<<endl;
                    venteVinMeilleurPrix->afficherResume();
                } else {
                    cout << "Aucun vin nommé " << nomRecherche << " n'a été trouvé." <<endl;
                }
            }else {
                auto it = find_if(vinsConso.begin(), vinsConso.end(), [nomRecherche,MillenismeRecherche](Vin& vin) {
                return vin.getNom() == nomRecherche && vin.getMillesime()==MillenismeRecherche;
                });
                if (it != vinsConso.end()) {
                    // Vin trouvée
                    it->afficherResume();
                    float meilleurPrix = std::numeric_limits<float>::max();
                    Vente* venteVinMeilleurPrix = nullptr;

                    for (Cave &cave : caves) {
                        for(int i=0;i<cave.getNombreVente();i++){
                            Vin* vinComparatif=cave.getVente(i)->getVin();
                            float prixComparatif=cave.getVente(i)->getPrixVente();
                            if (vinComparatif->getNom()==nomRecherche && vinComparatif->getMillesime()==MillenismeRecherche && prixComparatif< meilleurPrix){
                                meilleurPrix = prixComparatif;
                                venteVinMeilleurPrix = cave.getVente(i);
                            }
                        }
                    }
                    if (venteVinMeilleurPrix != nullptr) {
                        cout<<"La meilleure offre de ce Vin est:"<<endl;
                        venteVinMeilleurPrix->afficherResume();
                    } else {
                        cout << "Aucun vin nommé " << nomRecherche << " n'a été trouvé." <<endl;
                    }

                    // Cave non trouvée
                    cout << "La Cave: '" << nomRecherche << "n'a pas été trouvée." <<endl;
            }
            break;
        }
        }
        default:
            break;
        }

    }

    
}





void menuListeFournisseur(vector<Fournisseur>& fournisseurs){
    int reponse=-1;
    while(reponse!=0){
        cout<<endl;
        cout<<endl;
        cout<<"Que souhaitez vous faire: "<<endl;
        cout<<"Revenir au menu précédent: 0"<<endl;
        cout<<"Ajouter un Fournisseur: 1"<<endl;
        cout<<"Supprimer un Fournisseur: 2"<<endl;
        cout<<"Afficher l'ensemble des Fournisseurs: 3"<<endl;//Programmer ajout/retrait Vin/Vente + possibilité afficher liste 
        cout<<"Détail sur un Fournisseur: 4"<<endl;
        cin>>reponse;

        switch (reponse)
        {
        case 1:{//NOUVEAU FOURNISSEUR
            int nouveauIdentifiant;
            string nouveauNom;
            string nouvelleAdresse;
            cout<<"Tapez l'identifiant du nouveau Fournisseur:"<<endl;
            cin>>nouveauIdentifiant;
            cout<<"Tapez le Nom du nouveau Fournisseur:"<<endl;
            cin>>nouveauNom;
            cout<<"Tapez l'adresse du nouveau Fournisseur:"<<endl;
            cin>>nouvelleAdresse;
            
            auto it = std::find_if(fournisseurs.begin(), fournisseurs.end(), [nouveauIdentifiant,nouveauNom](Fournisseur& fournisseur) {
            return fournisseur.getNom() == nouveauNom || fournisseur.getIdentifiant()==nouveauIdentifiant;
            });
            if (it != fournisseurs.end()) {
                // Vin déjà existant
            cout<<"le vin existe déjà."<<endl;
            it->afficherResume();
            } else {
                // Cave non trouvée
                Fournisseur Nouveaufournisseur=Fournisseur(nouveauIdentifiant,nouveauNom,nouvelleAdresse);
                fournisseurs.push_back(Nouveaufournisseur);
                cout<<"Le fournisseur a été crée avec succés."<<endl;
                cout<<endl;  
            }
            menuListeFournisseur(fournisseurs);       
            break;  
        }
        case 2:
        {//SUPPRIMER FOURNISSEUR
            string nom;
            int millesime;
            cout<<"Tapez le nom du fournisseur à supprimer:"<<endl;
            cin>>nom;
            auto it = std::find_if(fournisseurs.begin(), fournisseurs.end(), [nom](Fournisseur& fournisseur) {
            return fournisseur.getNom() == nom ;
            });
            if (it != fournisseurs.end()) {
                // Fourniseur trouvée
                delete &*it;
            } else {
                // Fournisseur non trouvée
                cout << "La Cave: '" << nom << "' n'a pas été trouvée." <<endl;
            }

        }
        case 3:{//LISTES DES FOURNISSEURS
            cout << "Liste des Fournisseurs: " << endl;
            for (const Fournisseur& fournisseur : fournisseurs) {
            fournisseur.afficherResume();
            cout << endl;
        }
        case 4:
        {//DETAILS FOURNISSEURS
            cout<<"Sur quel Fournisseur voulez avoir des détails?"<<endl;
            string nomRecherche;
            cout<<"Tapez le nom du Fournisseur à rechercher:"<<endl;
            cin>>nomRecherche;

            auto it = find_if(fournisseurs.begin(), fournisseurs.end(), [nomRecherche](Fournisseur& fournisseur) {
            return fournisseur.getNom() == nomRecherche;
            });
            if (it != fournisseurs.end()) {
                // fournisseur trouvée
                it->afficherResume();
                it->afficherListeOffres();
                it->afficherListeReductions();
            
            } else {
                // fournisseur non trouvée
                cout << "Le Fournisseur: '" << nomRecherche << "n'a pas été trouvée." <<endl;
            }
        }
            break;
        
        default:
            break;
        }
    }
    }
   

}
