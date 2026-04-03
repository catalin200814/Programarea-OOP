#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <iomanip>
#include <memory>

using namespace std;

class Vehicle {
protected:
    string Vehicul;
    string NumIn;
    string OraIntrare;
    string OraIesire;
    int TimpTotal;
    int ore;
    int minute;
    double Tarif;
    
public:
    Vehicle(string tip, string numar, string intrare, string iesire) {
        Vehicul = tip;
        NumIn = numar;
        OraIntrare = intrare;
        OraIesire = iesire;
        TimpTotal = 0;
        ore = 0;
        minute = 0;
        Tarif = 0;
    }
    
    virtual ~Vehicle() {}
    
    void TimpParcat() {
        int OreIntrare = stoi(OraIntrare.substr(0, 2)) * 3600;
        int MinuteIntrare = stoi(OraIntrare.substr(3, 2)) * 60;
        int OreIesire = stoi(OraIesire.substr(0, 2)) * 3600;
        int MinuteIesire = stoi(OraIesire.substr(3, 2)) * 60;
        
        int Intrare = OreIntrare + MinuteIntrare;
        int Iesire = OreIesire + MinuteIesire;
        TimpTotal = Iesire - Intrare;
        ore = TimpTotal / 3600;
        minute = (TimpTotal % 3600) / 60;
    }
    
    virtual void CalculTarif() = 0;
    
    double getTarif() {
        return Tarif;
    }
    
    void Afisare() {
        cout << "Tip vehicul: " << Vehicul << endl;
        cout << "Numar de inmatriculare: " << NumIn << endl;
        cout << "Ora intrarii: " << OraIntrare << endl;
        cout << "Ora iesirii: " << OraIesire << endl;
        cout << "Timp parcat: " << ore << ":" << minute << endl;
        cout << "Tarif: " << Tarif << " lei" << endl;
        cout << endl;
    }
};

class Masina : public Vehicle {
public:
    Masina(string numar, string intrare, string iesire) 
        : Vehicle("Masina", numar, intrare, iesire) {}
    
    void CalculTarif() override {
        TimpParcat();
        double oreCuZecimale = ore + minute / 60.0;
        Tarif = oreCuZecimale * 5;
    }
};

class Motocicleta : public Vehicle {
public:
    Motocicleta(string numar, string intrare, string iesire) 
        : Vehicle("Motocicleta", numar, intrare, iesire) {}
    
    void CalculTarif() override {
        TimpParcat();
        double oreCuZecimale = ore + minute / 60.0;
        Tarif = oreCuZecimale * 3;
    }
};

class Camion : public Vehicle {
public:
    Camion(string numar, string intrare, string iesire) 
        : Vehicle("Camion", numar, intrare, iesire) {}
    
    void CalculTarif() override {
        TimpParcat();
        double oreCuZecimale = ore + minute / 60.0;
        Tarif = oreCuZecimale * 10;
    }
};

class Bicicleta : public Vehicle {
public:
    Bicicleta(string numar, string intrare, string iesire) 
        : Vehicle("Bicicleta", numar, intrare, iesire) {}
    
    void CalculTarif() override {
        TimpParcat();
        double oreCuZecimale = ore + minute / 60.0;
        
        if (oreCuZecimale <= 2) {
            Tarif = 0;
        } else {
            Tarif = (oreCuZecimale - 2) * 2;
        }
    }
};

int main() {
    vector<Vehicle*> vehicule;
    
    ifstream fisier("Vehicule.txt");
    
    if (!fisier.is_open()) {
        cout << "Eroare: Nu s-a putut deschide fisierul Vehicule.txt!" << endl;
        return 1;
    }
    
    string linie;
    while (getline(fisier, linie)) {
        if (linie.empty()) continue;
        
        stringstream ss(linie);
        string tip, numar, intrare, iesire;
        
        ss >> tip >> numar >> intrare >> iesire;
        
        if (tip == "Masina") {
            vehicule.push_back(new Masina(numar, intrare, iesire));
        } else if (tip == "Motocicleta") {
            vehicule.push_back(new Motocicleta(numar, intrare, iesire));
        } else if (tip == "Camion") {
            vehicule.push_back(new Camion(numar, intrare, iesire));
        } else if (tip == "Bicicleta") {
            vehicule.push_back(new Bicicleta(numar, intrare, iesire));
        }
    }
    
    fisier.close();
    
    cout << "\n================================================" << endl;
    cout << "     SISTEM DE GESTIONARE A PARCĂRII" << endl;
    cout << "================================================" << endl;
    cout << endl;
    
    double totalIncasari = 0;
    
    for (auto vehicul : vehicule) {
        vehicul->CalculTarif();
        vehicul->Afisare();
        totalIncasari += vehicul->getTarif();
    }
    
    cout << "================================================" << endl;
    cout << "TOTAL ÎNCASĂRI: " << fixed << setprecision(2) << totalIncasari << " lei" << endl;
    cout << "================================================" << endl;
    
    for (auto vehicul : vehicule) {
        delete vehicul;
    }
    
    return 0;
}
