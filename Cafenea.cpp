#include <iostream>
#include <string>
#include <vector>
using namespace std;

class Cafenea {
private:
    string nume;
    string adresa;
    int anDeschidere;
    double suprafata;
    int numarLocuri;
    double incasariZilnice;
    double incasariTotale;
    int numarAngajati;
    bool esteDeschisa;
    vector<string> produseMeniu;

public:
    Cafenea() {
        nume = "Necunoscuta";
        adresa = "Necunoscuta";
        anDeschidere = 2024;
        suprafata = 0;
        numarLocuri = 0;
        incasariZilnice = 0;
        incasariTotale = 0;
        numarAngajati = 0;
        esteDeschisa = false;
    }
    
    Cafenea(string nume, string adresa, int an, double suprafata, int locuri) {
        this->nume = nume;
        this->adresa = adresa;
        this->anDeschidere = an;
        this->suprafata = suprafata;
        this->numarLocuri = locuri;
        this->incasariZilnice = 0;
        this->incasariTotale = 0;
        this->numarAngajati = 2;
        this->esteDeschisa = true;
    }
    
    Cafenea(const Cafenea& other) {
        this->nume = other.nume + " (Copie)";
        this->adresa = other.adresa;
        this->anDeschidere = 2024;
        this->suprafata = other.suprafata;
        this->numarLocuri = other.numarLocuri;
        this->incasariZilnice = 0;
        this->incasariTotale = 0;
        this->numarAngajati = other.numarAngajati;
        this->esteDeschisa = true;
    }
    
    ~Cafenea() {
        cout << "Cafeneaua " << nume << " a fost inchisa definitiv." << endl;
    }
    
    string getNume() { return nume; }
    string getAdresa() { return adresa; }
    int getAnDeschidere() { return anDeschidere; }
    double getSuprafata() { return suprafata; }
    int getNumarLocuri() { return numarLocuri; }
    double getIncasariTotale() { return incasariTotale + incasariZilnice; }
    int getNumarAngajati() { return numarAngajati; }
    bool getStatus() { return esteDeschisa; }
    
    void setNume(string numeNou) {
        if(!numeNou.empty()) {
            nume = numeNou;
        }
    }
    
    void setAdresa(string adresaNoua) {
        if(!adresaNoua.empty()) {
            adresa = adresaNoua;
        }
    }
    
    void deschide() {
        esteDeschisa = true;
        cout << nume << " este acum deschisa." << endl;
    }
    
    void inchide() {
        esteDeschisa = false;
        incasariTotale += incasariZilnice;
        incasariZilnice = 0;
        cout << nume << " s-a inchis." << endl;
    }
    
    void vindeProdus(string produs, double pret) {
        if(!esteDeschisa) {
            cout << "Cafeneaua este inchisa!" << endl;
            return;
        }
        incasariZilnice += pret;
        produseMeniu.push_back(produs);
        cout << "Vandut: " << produs << " - " << pret << " lei" << endl;
    }
    
    void angajeaza(int numar) {
        numarAngajati += numar;
        cout << "Angajati " << numar << " persoane. Total: " << numarAngajati << endl;
    }
    
    void concediaza(int numar) {
        if(numarAngajati - numar >= 1) {
            numarAngajati -= numar;
            cout << "Concediati " << numar << " persoane. Total: " << numarAngajati << endl;
        } else {
            cout << "Nu se poate concedia. Minim un angajat." << endl;
        }
    }
    
    void afiseazaInformatii() {
        cout << "\n=== " << nume << " ===" << endl;
        cout << "Adresa: " << adresa << endl;
        cout << "Deschis din: " << anDeschidere << endl;
        cout << "Suprafata: " << suprafata << " mp" << endl;
        cout << "Locuri: " << numarLocuri << endl;
        cout << "Angajati: " << numarAngajati << endl;
        cout << "Status: " << (esteDeschisa ? "Deschisa" : "Inchisa") << endl;
        cout << "Incasari azi: " << incasariZilnice << " lei" << endl;
        cout << "Incasari totale: " << incasariTotale + incasariZilnice << " lei" << endl;
        cout << "Produse vandute azi: " << produseMeniu.size() << endl;
    }
    
    bool operator>(Cafenea& other) {
        return (this->incasariTotale + this->incasariZilnice) > 
               (other.incasariTotale + other.incasariZilnice);
    }
};

int main() {
    cout << "=== GESTIONARE CAFENELE 'LA CATALIN' ===" << endl;
    
    Cafenea cafenea1;
    cafenea1.afiseazaInformatii();
    
    Cafenea cafenea2("La Catalin - Centru", "Stefan cel Mare 123", 2020, 85, 30);
    cafenea2.afiseazaInformatii();
    
    Cafenea cafenea3 = cafenea2;
    cafenea3.setNume("La Catalin - Franciza Botanica");
    cafenea3.setAdresa("Dacia 50");
    cafenea3.afiseazaInformatii();
    
    cout << "\n=== OPERATIUNI ZILNICE ===" << endl;
    cafenea2.vindeProdus("Cappuccino", 25);
    cafenea2.vindeProdus("Espresso", 15);
    cafenea2.vindeProdus("Croissant", 20);
    
    cafenea2.angajeaza(2);
    cafenea2.concediaza(1);
    
    cafenea2.inchide();
    cafenea2.afiseazaInformatii();
    
    cafenea2.deschide();
    cafenea2.vindeProdus("Latte", 28);
    
    cout << "\n=== COMPARARE CAFENELE ===" << endl;
    if(cafenea2 > cafenea3) {
        cout << cafenea2.getNume() << " are incasari mai mari." << endl;
    } else {
        cout << cafenea3.getNume() << " are incasari mai mari." << endl;
    }
    
    cout << "\n=== GESTIONARE RETELE ===" << endl;
    vector<Cafenea> retea;
    retea.push_back(cafenea1);
    retea.push_back(cafenea2);
    retea.push_back(cafenea3);
    
    for(int i = 0; i < retea.size(); i++) {
        cout << i+1 << ". " << retea[i].getNume() << " - " 
             << retea[i].getAdresa() << " - " 
             << retea[i].getIncasariTotale() << " lei" << endl;
    }
    
    cout << "\n=== PROGRAM TERMINAT ===" << endl;
    
    return 0;
}
