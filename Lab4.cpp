#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <iomanip>

using namespace std;

class IRezervare {
public:
    virtual int calculeazaDurata() const = 0;
    virtual double calculeazaPret() const = 0;
    virtual void afiseaza() const = 0;
    virtual ~IRezervare() {}
};

class Rezervare : public IRezervare {
protected:
    string numeClient;
    string dataOra;
    int nrPersoane;

public:
    Rezervare(string nume, string data, int persoane)
        : numeClient(nume), dataOra(data), nrPersoane(persoane) {}

    string getNumeClient() const { return numeClient; }
    string getDataOra() const { return dataOra; }
    int getNrPersoane() const { return nrPersoane; }

    virtual int calculeazaDurata() const override {
        return 2;
    }

    virtual double calculeazaPret() const override = 0;
    virtual void afiseaza() const override = 0;
    virtual ~Rezervare() {}
};

class RezervareZilnica : public Rezervare {
public:
    RezervareZilnica(string nume, string data, int persoane)
        : Rezervare(nume, data, persoane) {}

    double calculeazaPret() const override {
        if (nrPersoane <= 2) {
            return 50.0;
        } else {
            return 50.0 + (nrPersoane - 2) * 20.0;
        }
    }

    void afiseaza() const override {
        cout << "Rezervare Zilnica";
    }
};

class RezervareEvenimentSpecial : public Rezervare {
private:
    int durataEveniment;

public:
    RezervareEvenimentSpecial(string nume, string data, int persoane, int durata = 3)
        : Rezervare(nume, data, persoane), durataEveniment(durata) {}

    int calculeazaDurata() const override {
        return durataEveniment;
    }

    double calculeazaPret() const override {
        double pretBaza = 200.0;
        if (durataEveniment > 2) {
            pretBaza += (durataEveniment - 2) * 30.0;
        }
        return pretBaza;
    }

    void afiseaza() const override {
        cout << "Rezervare Eveniment Special";
    }
};

class RezervareGrupMare : public Rezervare {
public:
    RezervareGrupMare(string nume, string data, int persoane)
        : Rezervare(nume, data, persoane) {}

    double calculeazaPret() const override {
        if (nrPersoane <= 20) {
            return 500.0;
        } else {
            return 500.0 + (nrPersoane - 20) * 10.0;
        }
    }

    void afiseaza() const override {
        cout << "Rezervare Grup Mare";
    }
};

class RezervareVIP : public Rezervare {
public:
    RezervareVIP(string nume, string data, int persoane)
        : Rezervare(nume, data, persoane) {}

    int calculeazaDurata() const override {
        return 4;
    }

    double calculeazaPret() const override {
        double pret = nrPersoane * 100.0;
        if (nrPersoane > 5) {
            pret = pret * 0.9;
        }
        return pret;
    }

    void afiseaza() const override {
        cout << "Rezervare VIP";
    }
};

int main() {
    cout << "SISTEM GESTIONARE REZERVARI RESTAURANT" << endl;
    cout << "----------------------------------------" << endl;

    vector<Rezervare*> rezervari;

    rezervari.push_back(new RezervareZilnica("Tudor Popescu", "2025-02-27 19:00", 4));
    rezervari.push_back(new RezervareEvenimentSpecial("Ana Maria", "2025-03-15 18:00", 10));
    rezervari.push_back(new RezervareGrupMare("Ion Ionescu", "2025-04-20 20:00", 25));
    rezervari.push_back(new RezervareZilnica("Maria Popescu", "2025-05-10 13:00", 2));
    rezervari.push_back(new RezervareEvenimentSpecial("Costel Georgescu", "2025-06-05 19:30", 15, 4));
    rezervari.push_back(new RezervareGrupMare("Elena Vasilescu", "2025-07-12 21:00", 30));
    rezervari.push_back(new RezervareVIP("Andreea Dumitrescu", "2025-08-01 20:00", 6));
    rezervari.push_back(new RezervareZilnica("George Marinescu", "2025-09-03 14:00", 3));

    double totalIncasari = 0;
    int index = 1;

    for (auto* rezervare : rezervari) {
        cout << "\nRezervarea #" << index++ << endl;
        rezervare->afiseaza();
        cout << endl;
        cout << "Client: " << rezervare->getNumeClient() << endl;
        cout << "Data si ora: " << rezervare->getDataOra() << endl;
        cout << "Numar persoane: " << rezervare->getNrPersoane() << endl;
        cout << "Durata: " << rezervare->calculeazaDurata() << " ore" << endl;
        cout << "Pret total: " << fixed << setprecision(2) << rezervare->calculeazaPret() << " lei" << endl;
        cout << "----------------------------------------" << endl;

        totalIncasari += rezervare->calculeazaPret();
    }

    cout << "\nTOTAL REZERVARI: " << rezervari.size() << endl;
    cout << "TOTAL INCASARI: " << fixed << setprecision(2) << totalIncasari << " lei" << endl;

    for (auto* rezervare : rezervari) {
        delete rezervare;
    }
    rezervari.clear();

    return 0;
}
