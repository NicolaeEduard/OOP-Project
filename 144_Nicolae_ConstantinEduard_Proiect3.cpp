#include <iostream>

#include<fstream>
#include<typeinfo>
#include<vector>
#include<list>
#include<exception>
#include<string.h>
#include<math.h>
#include<stdlib.h>
using namespace std;

class Nu_este_int: public exception
{
    virtual const char* what() const throw()
    {
        return "Nu este int";
    }
};
class Nu_este_CNP: public exception
{
    virtual const char* what() const throw()
    {
        return "Nu ati introdus un CNP valid";
    }
};
class Nu_este_disponibilitate: public exception
{
    virtual const char* what() const throw()
    {
        return "Nu ati introdus o disponibilitate valida";
    }
};
class Nu_este_localizare: public exception
{
    virtual const char* what() const throw()
    {
        return "Nu ati introdus o localizare valida";
    }
};
class Eroare_index:public exception
{
    virtual const char* what() const throw()
    {
        return "index prea mare";
    }
};


class IOInterface
{
public:
    // virtualizarea citirii
    virtual istream& citire(istream& is) = 0;
    virtual ostream& afisare(ostream& os) const = 0;
    virtual ifstream& citireFisier(ifstream& is) = 0;
    virtual ofstream& afisareFisier(ofstream& os) const = 0;
};


class Persoana: public IOInterface
{
protected:
    string nume;
    string prenume;
    string CNP;
    int varsta;
public:
    istream& citire(istream& is)
    {
        cout<<"Introduceti numele: ";
        is>>this->nume;
        cout<<"Introduceti prenumele: ";
        is>>this->prenume;
        cout<<"Introduceti CNP-ul: ";
        char sir[100];
        int sem=1;
        is.get();
        while(sem)
        {
            is.get(sir,100);
            is.get();
            try
            {
                int ok=1;
                if (strlen(sir)!=13)
                    ok=0;
                else
                    for (int i=0; i<strlen(sir); i++)
                        if (!isdigit(sir[i]))
                            ok=0;
                if (ok==0)
                    throw Nu_este_CNP();
                sem=0;
            }
            catch (exception &e)
            {
                if (strcmp(e.what(),"Nu ati introdus un CNP valid")==0)
                    cout<<"Nu ati introdus un CNP valid, incercati din nou"<<endl;
                else
                    cout<<"Alta eroare"<<endl;
            }
        }
        this->CNP=sir;
        cout<<"Introduceti varsta: ";
        sem=1;
        is.get();
        while(sem)
        {
            is.get(sir,100);
            is.get();
            try
            {
                for (int i=0; i<strlen(sir); i++)
                    if (!isdigit(sir[i]))
                        throw Nu_este_int();
                sem=0;
            }
            catch (exception &e)
            {
                if (strcmp(e.what(),"Nu este int")==0)
                    cout<<"Nu ati introdus o valoare corecta, introduceti una valida"<<endl;
                else
                    cout<<"Alta eroare"<<endl;
            }
        }
        this->varsta=atoi(sir);
        return is;
    }

    ostream& afisare(ostream& os) const
    {
        os<<"Nume: "<<this->nume<<endl;
        os<<"Prenume: "<<this->prenume<<endl;
        os<<"CNP: "<<this->CNP<<endl;
        os<<"Varsta: "<<this->varsta<<endl;
        return os;
    }
    ifstream &citireFisier(ifstream &is)
    {
        is>>this->nume;
        is>>this->prenume;
        is>>this->CNP;
        is>>this->varsta;
        return is;
    }
    ofstream &afisareFisier(ofstream &os) const
    {
        os<<this->nume<<endl;
        os<<this->prenume<<endl;
        os<<this->CNP<<endl;
        os<<this->varsta;
        return os;
    }

    Persoana(string nume, string prenume, string CNP, int varsta);
    Persoana();
    Persoana(const Persoana &p);
    Persoana& operator=(const Persoana& persoana);
    friend ostream & operator<<(ostream &out, const Persoana& p);
    friend istream & operator>>(istream &in, Persoana& p);
    friend ofstream &operator<<(ofstream &out, const Persoana&p);
    friend ifstream &operator>>(ifstream &in, Persoana &p);
    virtual ~Persoana();
};

Persoana::Persoana(string nume, string prenume, string CNP, int varsta)
{
    this->nume=nume;
    this->prenume=prenume;
    this->CNP=CNP;
    this->varsta=varsta;
}
Persoana::Persoana()
{
    this->nume="Anonim";
    this->prenume="Anonim";
    this->CNP="Anonim";
    this->varsta=0;
}
Persoana::Persoana(const Persoana &p)
{
    this->nume=p.nume;
    this->prenume=p.prenume;
    this->CNP=p.CNP;
    this->varsta=p.varsta;
}
Persoana& Persoana::operator=(const Persoana& p)
{
    if (this!=&p)
    {
        this->nume=p.nume;
        this->prenume=p.prenume;
        this->CNP=p.CNP;
        this->varsta=p.varsta;
    }
    return *this;
}
ostream & operator<<(ostream & os, const Persoana& p)
{
    return p.afisare(os);
}
istream &operator>>(istream &is, Persoana& p)
{
    return p.citire(is);
}
ofstream &operator<<(ofstream &os, const Persoana& p)
{
    return p.afisareFisier(os);
}
ifstream &operator>>(ifstream &is, Persoana &p)
{
    return p.citireFisier(is);
}
Persoana::~Persoana()
{
    this->nume="-";
    this->prenume="-";
    this->CNP="-";
    this->varsta=0;
}

class Proprietar: public Persoana
{
private:
    int nrProprietatiDetinute;
    int IncasariTotale;
public:
    istream& citire(istream& is)
    {
        Persoana::citire(is);
        cout<<"Introduceti numarul proprietatilor detinute: ";
        char sir[100];
        int sem=1;
        is.get();
        while(sem)
        {
            is.get(sir,100);
            is.get();
            try
            {
                for (int i=0; i<strlen(sir); i++)
                    if (!isdigit(sir[i]))
                        throw Nu_este_int();
                sem=0;
            }
            catch (exception &e)
            {
                if (strcmp(e.what(),"Nu este int")==0)
                    cout<<"Nu ati introdus o valoare corecta, introduceti una valida"<<endl;
                else
                    cout<<"Alta eroare"<<endl;
            }
        }
        this->nrProprietatiDetinute=atoi(sir);
        cout<<"Introduceti incasarile totale: ";
        sem=1;
        is.get();
        while(sem)
        {
            is.get(sir,100);
            is.get();
            try
            {
                for (int i=0; i<strlen(sir); i++)
                    if (!isdigit(sir[i]))
                        throw Nu_este_int();
                sem=0;
            }
            catch (exception &e)
            {
                if (strcmp(e.what(),"Nu este int")==0)
                    cout<<"Nu ati introdus o valoare corecta, introduceti una valida"<<endl;
                else
                    cout<<"Alta eroare"<<endl;
            }
        }
        this->IncasariTotale=atoi(sir);
        return is;
    }

    ostream& afisare(ostream& os) const
    {
        Persoana::afisare(os);
        os<<"Numarul proprietatilor detinute: "<<this->nrProprietatiDetinute<<endl;
        os<<"Incasarile totale: "<<this->IncasariTotale<<endl;
        return os;
    }
    ifstream &citireFisier(ifstream &is)
    {
        Persoana::citireFisier(is);
        is>>this->nrProprietatiDetinute;
        is>>this->IncasariTotale;
        return is;
    }
    ofstream &afisareFisier(ofstream &os) const
    {
        Persoana::afisareFisier(os);
        os<<this->nrProprietatiDetinute<<endl;
        os<<this->IncasariTotale<<endl;
        return os;
    }
    Proprietar(string nume, string prenume, string CNP, int varsta, int nrProprietatiDetinute, int IncasariTotale);
    Proprietar();
    Proprietar(const Proprietar &p);
    Proprietar& operator=(const Proprietar& proprietar);
    friend ostream & operator<<(ostream &out, const Proprietar& p);
    friend istream & operator>>(istream &in, Proprietar& p);
    friend ofstream &operator<<(ofstream &out, const Proprietar& p);
    friend ifstream &operator>>(ifstream &in, const Proprietar &p);
    virtual ~Proprietar();
    void setIncasariTotale(int IncasariTotale);
    int getIncasariTotale();
    Proprietar operator+(int f);//Proprietar+int
    friend Proprietar operator+(int f, Proprietar p);//int+Proprietar
};
Proprietar::Proprietar(string nume, string prenume, string CNP, int varsta,
                       int nrProprietatiDetinute, int IncasariTotale) //constructor cu toti parametrii
    :Persoana(nume,prenume,CNP,varsta)
{
    this->nrProprietatiDetinute=nrProprietatiDetinute;
    this->IncasariTotale=IncasariTotale;
}
Proprietar::Proprietar(): Persoana() //constructor fara parametrii
{
    this->nrProprietatiDetinute=0;
    this->IncasariTotale=0;
}
Proprietar::Proprietar(const Proprietar &p): Persoana(p) //copy-constructor
{
    this->nrProprietatiDetinute=p.nrProprietatiDetinute;
    this->IncasariTotale=p.IncasariTotale;
}
Proprietar& Proprietar::operator=(const Proprietar& p) //supraincarcarea operatorului egal
{
    if(this != &p)
    {

        // call explicit la operatorul = al clasei Produs
        Persoana::operator =(p);
        this->nrProprietatiDetinute=p.nrProprietatiDetinute;
        this->IncasariTotale=p.IncasariTotale;
    }
    return *this;
}
ostream & operator<<(ostream & os, const Proprietar& p) //supraincarcarea operatorului <<
{
    return p.afisare(os);
}
istream &operator>>(istream &is, Proprietar& p) //supraincarcarea operatorului >>
{
    return p.citire(is);
}
ofstream &operator<<(ofstream &os, const Proprietar &p)
{
    return p.afisareFisier(os);
}
ifstream &operator>>(ifstream &is, Proprietar &p)
{
    return p.citireFisier(is);
}
Proprietar Proprietar::operator+(int d)     //Proprietar+int
{
    Proprietar aux(*this);
    aux.IncasariTotale=aux.IncasariTotale+d;
    return aux;
}
Proprietar operator+(int d,Proprietar p)    //int+Proprietar
{
    Proprietar aux(p);
    aux.IncasariTotale=aux.IncasariTotale+d;
    return aux;
}
Proprietar::~Proprietar() //destructor
{
    this->nrProprietatiDetinute=0;
    this->IncasariTotale=0;
}
void Proprietar::setIncasariTotale(int IncasariTotale)
{
    this->IncasariTotale=IncasariTotale;
}
int Proprietar::getIncasariTotale()
{
    return this->IncasariTotale;
}

class Cladire: public IOInterface
{
protected:
    int suprafata;
    string adresa;
    int nrCamere;
    string localizare; //urban sau rural
    string numeProprietar;

public:
    istream& citire(istream& is)
    {
        cout<<"Introduceti suprafata: ";
        char sir[100];
        int sem=1;
        is.get();
        while(sem)
        {
            is.get(sir,100);
            is.get();
            try
            {
                for (int i=0; i<strlen(sir); i++)
                    if (!isdigit(sir[i]))
                        throw Nu_este_int();
                sem=0;
            }
            catch (exception &e)
            {
                if (strcmp(e.what(),"Nu este int")==0)
                    cout<<"Nu ati introdus o valoare corecta, introduceti una valida"<<endl;
                else
                    cout<<"Alta eroare"<<endl;
            }
        }
        this->suprafata=atoi(sir);
        cout<<"Introduceti adresa: ";
        is>>this->adresa;
        cout<<"Introduceti numarul de camere: ";
        sem=1;
        is.get();
        while(sem)
        {
            is.get(sir,100);
            is.get();
            try
            {
                for (int i=0; i<strlen(sir); i++)
                    if (!isdigit(sir[i]))
                        throw Nu_este_int();
                sem=0;
            }
            catch (exception &e)
            {
                if (strcmp(e.what(),"Nu este int")==0)
                    cout<<"Nu ati introdus o valoare corecta, introduceti una valida"<<endl;
                else
                    cout<<"Alta eroare"<<endl;
            }
        }
        this->nrCamere=atoi(sir);
        cout<<"Introduceti localizarea: ";
        sem=1;
        is.get();
        while (sem)
        {
            is.get(sir,100);
            is.get();
            try
            {
                int ok=1;
                if (strcmp(sir,"rural")==0 || strcmp(sir,"urban")==0)
                    ok=0;
                if (ok==1)
                    throw Nu_este_localizare();
                sem=0;
            }
            catch (exception &e)
            {
                if (strcmp(e.what(),"Nu ati introdus o localizare valida")==0)
                    cout<<"Nu ati introdus o localizare valida, incercati din nou"<<endl;
                else
                    cout<<"Alta eroare"<<endl;
            }
        }
        this->localizare=sir;
        cout<<"Introduceti numele proprietarului: ";
        is>>this->numeProprietar;
        return is;
    }

    ostream& afisare(ostream& os) const
    {
        os<<"Suprafata: "<<this->suprafata<<endl;
        os<<"Adresa: "<<this->adresa<<endl;
        os<<"Numarul de camere: "<<this->nrCamere<<endl;
        os<<"Localizare: "<<this->localizare<<endl;
        os<<"Nume proprietar: "<<this->numeProprietar<<endl;
        return os;
    }
    ifstream &citireFisier(ifstream &is)
    {
        is>>this->suprafata;
        is>>this->adresa;
        is>>this->nrCamere;
        is>>this->localizare;
        is>>this->numeProprietar;
        return is;
    }
    ofstream &afisareFisier(ofstream &os) const
    {
        os<<this->suprafata<<endl;
        os<<this->adresa<<endl;
        os<<this->nrCamere<<endl;
        os<<this->localizare<<endl;
        os<<this->numeProprietar<<endl;
        return os;
    }

    Cladire(int suprafata, string adresa, int nrCamere, string localizare, string numeProprietar);
    Cladire();
    Cladire(const Cladire &c);
    Cladire& operator=(const Cladire& cladire);
    friend ostream & operator<<(ostream &out, const Cladire& c);
    friend istream & operator>>(istream &in, Cladire& c);
    friend ofstream &operator<<(ofstream &out, const Cladire &c);
    friend ifstream &operator>>(ifstream &in, Cladire &c);
    virtual ~Cladire();
};

Cladire::Cladire(int suprafata, string adresa, int nrCamere, string localizare, string numeProprietar)
{
    this->suprafata=suprafata;
    this->adresa=adresa;
    this->nrCamere=nrCamere;
    this->localizare=localizare;
    this->numeProprietar=numeProprietar;
}
Cladire::Cladire()
{
    this->suprafata=0;
    this->adresa="Necunoscut";
    this->nrCamere=0;
    this->localizare="Necunoscut";
    this->numeProprietar="Anonim";
}
Cladire::Cladire(const Cladire&c)
{
    this->suprafata=c.suprafata;
    this->adresa=c.adresa;
    this->nrCamere=c.nrCamere;
    this->localizare=c.localizare;
    this->numeProprietar=c.numeProprietar;
}
Cladire& Cladire::operator=(const Cladire& c)
{
    if (this!=&c)
    {
        this->suprafata=c.suprafata;
        this->adresa=c.adresa;
        this->nrCamere=c.nrCamere;
        this->localizare=c.localizare;
        this->numeProprietar=c.numeProprietar;
    }
    return *this;
}
ostream& operator<<(ostream& os, const Cladire& c)
{
    return c.afisare(os);
}
istream &operator>>(istream &is, Cladire& c)
{
    return c.citire(is);
}
ofstream &operator<<(ofstream &os, const Cladire &c)
{
    return c.afisareFisier(os);
}
ifstream &operator>>(ifstream &is, Cladire &c)
{
    return c.citireFisier(is);
}
Cladire::~Cladire()
{
    this->suprafata=0;
    this->adresa="-";
    this->nrCamere=0;
    this->localizare="-";
    this->numeProprietar="-";
}

class Pensiune: public Cladire
{
private:
    string nume;
    int pretInchiriere;
    string disponibilitate;
    string rating;

public:
    istream& citire(istream& is)
    {
        Cladire::citire(is);
        cout<<"Introduceti numele unitatii: ";
        is>>this->nume;
        cout<<"Introduceti pretul de inchiriere: ";
        char sir[100];
        int sem=1;
        is.get();
        while(sem)
        {
            is.get(sir,100);
            is.get();
            try
            {
                for (int i=0; i<strlen(sir); i++)
                    if (!isdigit(sir[i]))
                        throw Nu_este_int();
                sem=0;
            }
            catch (exception &e)
            {
                if (strcmp(e.what(),"Nu este int")==0)
                    cout<<"Nu ati introdus o valoare corecta, introduceti una valida"<<endl;
                else
                    cout<<"Alta eroare"<<endl;
            }
        }
        this->pretInchiriere=atoi(sir);
        cout<<"Introduceti disponibilitatea: ";
        sem=1;
        is.get();
        while (sem)
        {
            is.get(sir,100);
            is.get();
            try
            {
                int ok=1;
                if (strcmp(sir,"disponibil")==0 || strcmp(sir,"indisponibil")==0)
                    ok=0;
                if (ok==1)
                    throw Nu_este_disponibilitate();
                sem=0;
            }
            catch (exception &e)
            {
                if (strcmp(e.what(),"Nu ati introdus o disponibilitate valida")==0)
                    cout<<"Nu ati introdus o disponibilitate valida, incercati din nou"<<endl;
                else
                    cout<<"Alta eroare"<<endl;
            }
        }
        this->disponibilitate=sir;
        cout<<"Introduceti rating-ul: ";
        is>>this->rating;
        return is;
    }

    ostream& afisare(ostream& os) const
    {
        Cladire::afisare(os);
        os<<"Numele unitatii: "<<this->nume<<endl;
        os<<"Pret de inchiriere: "<<this->pretInchiriere<<endl;
        os<<"Disponibilitate: "<<this->disponibilitate<<endl;
        os<<"Rating: "<<this->rating<<endl;
        return os;
    }

    ifstream &citireFisier(ifstream &is)
    {
        Cladire::citireFisier(is);
        is>>this->nume;
        is>>this->pretInchiriere;
        is>>this->disponibilitate;
        is>>this->rating;
        return is;
    }

    ofstream &afisareFisier(ofstream &os) const
    {
        Cladire::afisareFisier(os);
        os<<this->nume<<endl;
        os<<this->pretInchiriere<<endl;
        os<<this->disponibilitate<<endl;
        os<<this->rating<<endl;
        return os;
    }
    Pensiune(int suprafata, string adresa, int nrCamere, string localizare, string numeProprietar,
             string nume, int pretInchiriere, string disponibilitate, string rating);
    Pensiune();
    Pensiune(const Pensiune &p);
    Pensiune& operator=(const Pensiune& pensiune);
    friend ostream & operator<<(ostream &out, const Pensiune& p);
    friend istream & operator>>(istream &in, Pensiune& p);
    friend ofstream &operator<<(ofstream &out, const Pensiune &p);
    friend ifstream &operator>>(ifstream &in, Pensiune &p);
    virtual ~Pensiune();
    void setDisponibilitate(string disponibilitate);
    void setPretInchiriere(int pretInchiriere);
    string getDisponibilitate();
    int getPretInchiriere();
};
Pensiune::Pensiune(int suprafata, string adresa, int nrCamere, string localizare, string numeProprietar,
                   string nume, int pretInchiriere, string disponibilitate, string rating)
    :Cladire(suprafata,adresa,nrCamere,localizare,numeProprietar)
{
    this->nume=nume;
    this->pretInchiriere=pretInchiriere;
    this->disponibilitate=disponibilitate;
    this->rating=rating;
}
Pensiune::Pensiune(): Cladire()
{
    this->nume="-";
    this->pretInchiriere=0;
    this->disponibilitate="-";
}
Pensiune::Pensiune(const Pensiune &p): Cladire()
{
    this->nume=p.nume;
    this->pretInchiriere=p.pretInchiriere;
    this->disponibilitate=p.disponibilitate;
    this->rating=p.rating;
}
Pensiune& Pensiune::operator=(const Pensiune& p)
{
    if (this!=&p)
    {
        Cladire::operator=(p);
        this->nume=p.nume;
        this->pretInchiriere=p.pretInchiriere;
        this->disponibilitate=p.disponibilitate;
        this->rating=p.rating;
    }
    return *this;
}
ostream & operator<<(ostream & os, const Pensiune& p)
{
    return p.afisare(os);
}
istream &operator>>(istream &is, Pensiune& p)
{
    return p.citire(is);
}
ofstream &operator<<(ofstream &os, const Pensiune &p)
{
    return p.afisareFisier(os);
}
ifstream &operator>>(ifstream &is, Pensiune &p)
{
    return p.citireFisier(is);
}
Pensiune::~Pensiune()
{
    this->nume="-";
    this->pretInchiriere=0;
    this->disponibilitate="-";
    this->rating="-";
}
void Pensiune::setDisponibilitate(string disponibilitate)
{
    this->disponibilitate=disponibilitate;
}
void Pensiune::setPretInchiriere(int pretInchiriere)
{
    this->pretInchiriere=pretInchiriere;
}
string Pensiune::getDisponibilitate()
{
    return this->disponibilitate;
}
int Pensiune::getPretInchiriere()
{
    return this->pretInchiriere;
}

class Cabana: public Pensiune
{
private:
    int altitudine;

public:
    istream& citire(istream& is)
    {
        Pensiune::citire(is);
        cout<<"Introduceti altitudinea: ";
        char sir[100];
        int sem=1;
        is.get();
        while(sem)
        {
            is.get(sir,100);
            is.get();
            try
            {
                for (int i=0; i<strlen(sir); i++)
                    if (!isdigit(sir[i]))
                        throw Nu_este_int();
                sem=0;
            }
            catch (exception &e)
            {
                if (strcmp(e.what(),"Nu este int")==0)
                    cout<<"Nu ati introdus o valoare corecta, introduceti una valida"<<endl;
                else
                    cout<<"Alta eroare"<<endl;
            }
        }
        this->altitudine=atoi(sir);
        return is;
    }

    ostream& afisare(ostream& os) const
    {
        Pensiune::afisare(os);
        os<<"Altitudine: "<<this->altitudine<<endl;
        return os;
    }
    ifstream &citireFisier(ifstream &is)
    {
        Pensiune::citireFisier(is);
        is>>this->altitudine;
        return is;
    }
    ofstream &afisareFisier(ofstream &os) const
    {
        Pensiune::afisareFisier(os);
        os<<this->altitudine<<endl;
        return os;
    }
    Cabana(int suprafata, string adresa, int nrCamere, string localizare, string numeProprietar,
           string nume, int pretInchiriere, string disponibilitate, string rating,
           int altitudine);
    Cabana();
    Cabana(const Cabana &c);
    Cabana& operator=(const Cabana& cabana);
    friend ostream & operator<<(ostream &out, const Cabana& c);
    friend istream & operator>>(istream &in, Cabana& c);
    friend ofstream &operator<<(ofstream &out, const Cabana &c);
    friend ifstream &operator>>(ifstream &in, Cabana &c);
    virtual ~Cabana();
};

Cabana::Cabana(int suprafata, string adresa, int nrCamere, string localizare, string numeProprietar,
               string nume, int pretInchiriere, string disponibilitate, string rating,
               int altitudine)
    :Pensiune(suprafata,adresa,nrCamere,localizare,numeProprietar,nume,pretInchiriere,disponibilitate,rating)
{
    this->altitudine=altitudine;
}
Cabana::Cabana(): Pensiune()
{
    this->altitudine=0;
}
Cabana::Cabana(const Cabana &c): Pensiune()
{
    this->altitudine=c.altitudine;
}
Cabana& Cabana::operator=(const Cabana& c)
{
    if (this!=&c)
    {
        Pensiune::operator=(c);
        this->altitudine=c.altitudine;
    }
    return *this;
}
ostream & operator<<(ostream & os, const Cabana& c)
{
    return c.afisare(os);
}
istream &operator>>(istream &is, Cabana& c)
{
    return c.citire(is);
}
ofstream &operator<<(ofstream &os, const Cabana &c)
{
    return c.afisareFisier(os);
}
ifstream &operator>>(ifstream &is, Cabana &c)
{
    return c.citireFisier(is);
}
Cabana::~Cabana()
{
    this->altitudine=0;
}

class Hotel: public Cladire
{
private:
    string numeHotel;
    int pretCamera;
    string disponibilitate;
    string rating;
public:
    istream& citire(istream& is)
    {
        Cladire::citire(is);
        cout<<"Introduceti numele hotelului: ";
        is>>this->numeHotel;
        cout<<"Introduceti pretul unei camere: ";
        char sir[100];
        int sem=1;
        is.get();
        while(sem)
        {
            is.get(sir,100);
            is.get();
            try
            {
                for (int i=0; i<strlen(sir); i++)
                    if (!isdigit(sir[i]))
                        throw Nu_este_int();
                sem=0;
            }
            catch (exception &e)
            {
                if (strcmp(e.what(),"Nu este int")==0)
                    cout<<"Nu ati introdus o valoare corecta, introduceti una valida"<<endl;
                else
                    cout<<"Alta eroare"<<endl;
            }
        }
        this->pretCamera=atoi(sir);
        cout<<"Introduceti disponibilitatea: ";
        sem=1;
        is.get();
        while (sem)
        {
            is.get(sir,100);
            is.get();
            try
            {
                int ok=1;
                if (strcmp(sir,"disponibil")==0 || strcmp(sir,"indisponibil")==0)
                    ok=0;
                if (ok==1)
                    throw Nu_este_disponibilitate();
                sem=0;
            }
            catch (exception &e)
            {
                if (strcmp(e.what(),"Nu ati introdus o disponibilitate valida")==0)
                    cout<<"Nu ati introdus o disponibilitate valida, incercati din nou"<<endl;
                else
                    cout<<"Alta eroare"<<endl;
            }
        }
        this->disponibilitate=sir;
        cout<<"Introduceti rating-ul: ";
        is>>this->rating;
        return is;
    }

    ostream& afisare(ostream& os) const
    {
        Cladire::afisare(os);
        os<<"Numele hotelului: "<<this->numeHotel<<endl;
        os<<"Pret camera: "<<this->pretCamera<<endl;
        os<<"Disponibilitate: "<<this->disponibilitate<<endl;
        os<<"Rating: "<<this->rating<<endl;
        return os;
    }
    ifstream &citireFisier(ifstream &is)
    {
        Cladire::citireFisier(is);
        is>>this->numeHotel;
        is>>this->pretCamera;
        is>>this->disponibilitate;
        is>>this->rating;
        return is;
    }
    ofstream &afisareFisier(ofstream &os) const
    {
        Cladire::afisareFisier(os);
        os<<this->numeHotel<<endl;
        os<<this->pretCamera<<endl;
        os<<this->disponibilitate<<endl;
        os<<this->rating<<endl;
        return os;
    }
    Hotel(int suprafata, string adresa, int nrCamere, string localizare, string numeProprietar,
          string numeHotel, int pretCamera, string disponibilitate, string rating);
    Hotel();
    Hotel(const Hotel &p);
    Hotel& operator=(const Hotel& hotel);
    friend ostream & operator<<(ostream &out, const Hotel& h);
    friend istream & operator>>(istream &in, Hotel& h);
    friend ofstream &operator<<(ofstream &out, const Hotel &h);
    friend ifstream &operator>>(ifstream &in, Hotel &h);
    virtual ~Hotel();
    void setDisponibilitate(string disponibilitate);
    void setPretCamera(int pretCamera);
    string getDisponibilitate();
    int getPretCamera();
};
Hotel::Hotel(int suprafata, string adresa, int nrCamere, string localizare, string numeProprietar,
             string numeHotel, int pretCamera, string disponibilitate, string rating)
    :Cladire(suprafata,adresa,nrCamere,localizare,numeProprietar)
{
    this->numeHotel=numeHotel;
    this->pretCamera=pretCamera;
    this->disponibilitate=disponibilitate;
    this->rating=rating;
}
Hotel::Hotel(): Cladire()
{
    this->numeHotel="-";
    this->pretCamera=0;
    this->disponibilitate="-";
    this->rating="-";
}
Hotel::Hotel(const Hotel &h): Cladire()
{
    this->numeHotel=h.numeHotel;
    this->pretCamera=h.pretCamera;
    this->disponibilitate=h.disponibilitate;
    this->rating=h.rating;
}
Hotel& Hotel::operator=(const Hotel& h)
{
    if (this!=&h)
    {
        Cladire::operator=(h);
        this->numeHotel=h.numeHotel;
        this->pretCamera=h.pretCamera;
        this->disponibilitate=h.disponibilitate;
        this->rating=h.rating;
    }
    return *this;
}
ostream & operator<<(ostream & os, const Hotel& h)
{
    return h.afisare(os);
}
istream &operator>>(istream &is, Hotel& h)
{
    return h.citire(is);
}
ofstream &operator<<(ofstream &os, const Hotel &h)
{
    return h.afisareFisier(os);
}
ifstream &operator>>(ifstream &is, Hotel &h)
{
    return h.citireFisier(is);
}
Hotel::~Hotel()
{
    this->numeHotel="-";
    this->pretCamera=0;
    this->disponibilitate="-";
    this->rating="-";
}
void Hotel::setDisponibilitate(string disponibilitate)
{
    this->disponibilitate=disponibilitate;
}
void Hotel::setPretCamera(int pretCamera)
{
    this->pretCamera=pretCamera;
}
string Hotel::getDisponibilitate()
{
    return this->disponibilitate;
}
int Hotel::getPretCamera()
{
    return this->pretCamera;
}


class Singletone
{
private:
    static Singletone *obiect;
    int nrAccesari;
    Singletone()
    {
        this->nrAccesari=0;
    }
    Singletone(int nrAccesari)
    {
        this->nrAccesari=nrAccesari;
    }
    Singletone(const Singletone&)
    {
    }
    Singletone &operator=(const Singletone&)
    {
        return *this;
    }
    ~Singletone()
    {
        this->nrAccesari=0;
    }
public:
    static Singletone* getInstance()
    {
        if(!obiect)
            obiect=new Singletone();


        return obiect;
    }

    void setNrAccesari(int nrAccesari)
    {
        this->nrAccesari=nrAccesari;
    }
    int getNrAccesari()
    {
        return this->nrAccesari;
    }
    //functie meniu
    void InchirierePensiune(Proprietar &prop, Pensiune &pens)
    {
        if (pens.getDisponibilitate()=="disponibil")
        {
            prop.setIncasariTotale(pens.getPretInchiriere());
            pens.setDisponibilitate("indisponibil");
        }
        else
            cout<<"Pensiunea nu este disponibila"<<endl;
    }
    void InchiriereCabana(Proprietar &prop, Cabana &cab)
    {
        if (cab.getDisponibilitate()=="disponibil")
        {
            prop.setIncasariTotale(cab.getPretInchiriere());
            cab.setDisponibilitate("indisponibil");
        }
        else
            cout<<"Cabana nu este disponibila"<<endl;
    }
    void InchiriereCameraHotel(Proprietar &prop, Hotel &hot)
    {
        if (hot.getDisponibilitate()=="disponibil")
        {
            prop.setIncasariTotale(hot.getPretCamera());
            hot.setDisponibilitate("indisponibil");
        }
        else
            cout<<"Hotelul nu este disponibil"<<endl;
    }
    void InchiriereCladire(Persoana *&p, Cladire *c)
    {
        if (typeid(*p)!=typeid(Proprietar))
        {
            cout<<"Persoana aceasta nu este proprietar"<<endl;
            return;
        }
        if (typeid(*c)==typeid(Cladire))
        {
            cout<<"Aceasta cladire nu se poate inchiria"<<endl;
            return;
        }
        Proprietar *prop;
        try
        {
            prop=dynamic_cast<Proprietar *> (p);
        }
        catch(...)
        {
            cout<<"A aparut o eroare"<<endl;
            return;
        }
        Pensiune *pens;
        Hotel *hot;
        Cabana *cab;
        if (typeid(*c)==typeid(Pensiune))
        {
            pens=dynamic_cast<Pensiune *> (c);
            InchirierePensiune(*prop,*pens);
        }
        else if (typeid(*c)==typeid(Hotel))
        {
            hot=dynamic_cast<Hotel *> (c);
            InchiriereCameraHotel(*prop,*hot);
        }
        else if (typeid(*c)==typeid(Cabana))
        {
            cab=dynamic_cast<Cabana *> (c);
            InchiriereCabana(*prop,*cab);
        }
        else
        {
            cout<<"A aparut o eroare"<<endl;
            return;
        }
    }

    void meniu()
    {
        vector<Persoana*> pers;
        list<Cladire*> cld;
        this->nrAccesari=0;
        char optiune;
        while(true)
        {
            cout<<"Comenzi(apasa x pentru a iesi)"<<endl;
            cout<<"1.Pensiune"<<endl;
            cout<<"2.Hotel"<<endl;
            cout<<"3.Cabana"<<endl;
            cout<<"4.Proprietar"<<endl;

            cin>>optiune;
            this->nrAccesari++;

            if (optiune=='1')
            {
                char optiune_pensiune;
                cout<<"Comenzi(apasa x pentru a iesi)"<<endl;
                cout<<"1.Adauga pensiune"<<endl;
                cout<<"2.Elimina pensiune"<<endl;
                cout<<"3.Modifica pensiune"<<endl;
                cout<<"4.Afiseaza pensiune"<<endl;
                cout<<"5.Rezerva pensiune"<<endl;

                cin>>optiune_pensiune;

                if (optiune_pensiune=='1')
                {
                    Cladire *aux=new Pensiune;
                    cin>>*aux;
                    cld.push_back(aux);
                }
                else if (optiune_pensiune=='2')
                     {
                         cout<<"Scrieti indexul pensiunii pe care doriti sa o eliminati"<<endl;
                         int index;
                         cin>>index;
                         try
                         {
                            if (index>cld.size())
                                throw Eroare_index();
                            list<Cladire*>::iterator i;
                            for (i=cld.begin(); i!=cld.end() && index; i++)
                                index--;
                            cld.remove(*i);
                         }
                         catch(exception &e)
                         {
                             if (strcmp(e.what(),"index prea mare")==0)
                                cout<<"Pensiunea cautata de dumneavoastra nu exista"<<endl;
                             else
                                cout<<"Alta eroare"<<endl;
                        }
                     }
                     else if (optiune_pensiune=='3')
                          {
                             cout<<"Scrieti indexul pensiunii pe care doriti sa o modificati"<<endl;
                             int index;
                             cin>>index;
                             try
                             {
                                 if (index>cld.size())
                                    throw Eroare_index();
                                 Cladire *aux=new Pensiune;
                                 cin.get();
                                 cin>>*aux;
                                 list<Cladire*>::iterator i;
                                 for (i=cld.begin(); i!=cld.end() && index; i++)
                                     index--;
                                 (*i)=aux;
                             }
                             catch (exception &e)
                             {
                                 if (strcmp(e.what(),"index prea mare")==0)
                                    cout<<"Pensiunea ceruta de dumneavoastra nu exista"<<endl;
                                else
                                    cout<<"Alta eroare"<<endl;
                             }
                          }
                          else if (optiune_pensiune=='4')
                               {
                                    cout<<"Scrieti indexul pensiunii pe care doriti sa o vizualizati"<<endl;
                                    int index;
                                    cin>>index;
                                    try
                                    {
                                        if (index>cld.size())
                                            throw Eroare_index();
                                        list<Cladire*>::iterator i;
                                        for (i=cld.begin(); i!=cld.end() && index; i++)
                                            index--;
                                        cout<<*(*i);
                                    }
                                    catch (exception &e)
                                    {
                                        if (strcmp(e.what(),"index prea mare")==0)
                                            cout<<"Pensiunea cautata de dumneavoastra nu exista"<<endl;
                                        else
                                            cout<<"Alta eroare"<<endl;
                                    }
                                }
                                else if (optiune_pensiune=='5')
                                     {
                                         cout<<"Scrieti indexul proprietarului si indexul pensiunii pe care doriti sa o inchiriati"<<endl;
                                         int index_prop,index_pens;
                                         cin>>index_prop>>index_pens;
                                         try
                                         {
                                             if (index_pens>cld.size())
                                                throw Eroare_index();
                                         }
                                         catch (exception &e)
                                         {
                                             if (strcmp(e.what(),"index prea mare")==0)
                                                cout<<"Pensiunea cautata de dumneavoastra nu exista"<<endl;
                                             else
                                                cout<<"Alta eroare"<<endl;
                                         }
                                         try
                                         {
                                             if (index_prop>pers.size())
                                                throw Eroare_index();
                                         }
                                         catch (exception &e)
                                         {
                                             if (strcmp(e.what(),"index prea mare")==0)
                                                cout<<"Proprietarul cautat de dumneavoastra nu exista"<<endl;
                                             else
                                                cout<<"Alta eroare"<<endl;
                                         }
                                         list<Cladire*>::iterator i;
                                         for (i=cld.begin(); i!=cld.end() && index_pens; i++)
                                             index_pens--;
                                         InchiriereCladire(pers[index_prop],*i);
                                     }
                                     else
                                         break;
            }
            else if (optiune=='2')
                 {
                    char optiune_hotel;
                    cout<<"Comenzi(apasa x pentru a iesi)"<<endl;
                    cout<<"1.Adauga hotel"<<endl;
                    cout<<"2.Elimina hotel"<<endl;
                    cout<<"3.Modifica hotel"<<endl;
                    cout<<"4.Afiseaza hotel"<<endl;
                    cout<<"5.Rezerva camera de hotel"<<endl;

                    cin>>optiune_hotel;

                    if (optiune_hotel=='1')
                    {
                        Cladire *aux=new Hotel;
                        cin>>*aux;
                        cld.push_back(aux);
                    }
                    else if (optiune_hotel=='2')
                         {
                            cout<<"Scrieti indexul hotelului pe care doriti sa il eliminati"<<endl;
                            int index;
                            cin>>index;
                            try
                            {
                                if (index>cld.size())
                                    throw Eroare_index();
                                list<Cladire*>::iterator i;
                                for (i=cld.begin(); i!=cld.end() && index; i++)
                                    index--;
                                cld.remove(*i);
                            }
                            catch (exception &e)
                            {
                                if (strcmp(e.what(),"index prea mare")==0)
                                    cout<<"Hotelul cautat de dumneavoastra nu exista"<<endl;
                                else
                                    cout<<"Alta eroare"<<endl;
                            }
                         }
                         else if (optiune_hotel=='3')
                              {
                                    cout<<"Scrieti indexul hotelului pe care doriti sa il modificati"<<endl;
                                    int index;
                                    cin>>index;
                                    try
                                    {
                                        if (index>cld.size())
                                            throw Eroare_index();
                                        Cladire *aux=new Hotel;
                                        cin.get();
                                        cin>>*aux;
                                        list<Cladire*>::iterator i;
                                        for (i=cld.begin(); i!=cld.end() && index; i++)
                                            index--;
                                        (*i)=aux;
                                    }
                                    catch (exception &e)
                                    {
                                        if (strcmp(e.what(),"index prea mare")==0)
                                            cout<<"Hotelul cerut de dumneavoastra nu exista"<<endl;
                                        else
                                            cout<<"Alta eroare"<<endl;
                                    }
                             }
                             else if (optiune_hotel=='4')
                                  {
                                        cout<<"Scrieti indexul hotelului pe care doriti sa il vizualizati"<<endl;
                                        int index;
                                        cin>>index;
                                        try
                                        {
                                            if (index>cld.size())
                                                throw Eroare_index();
                                            list<Cladire*>::iterator i;
                                            for (i=cld.begin(); i!=cld.end() && index; i++)
                                                index--;
                                            cout<<*(*i);
                                        }
                                        catch (exception &e)
                                        {
                                            if (strcmp(e.what(),"index prea mare")==0)
                                                cout<<"Hotelul cautat de dumneavoastra nu exista"<<endl;
                                            else
                                                cout<<"Alta eroare"<<endl;
                                        }
                                  }
                                  else if (optiune_hotel=='5')
                                       {
                                            cout<<"Scrieti indexul proprietarului si indexul hotelului unde doriti sa va cazati"<<endl;
                                            int index_prop,index_hot;
                                            cin>>index_prop>>index_hot;
                                            try
                                            {
                                                if (index_hot>cld.size())
                                                    throw Eroare_index();
                                            }
                                            catch (exception &e)
                                            {
                                                if (strcmp(e.what(),"index prea mare")==0)
                                                    cout<<"Hotelul cautat de dumneavoastra nu exista"<<endl;
                                                else
                                                    cout<<"Alta eroare"<<endl;
                                            }
                                            try
                                            {
                                                if (index_prop>pers.size())
                                                    throw Eroare_index();
                                            }
                                            catch (exception &e)
                                            {
                                                if (strcmp(e.what(),"index prea mare")==0)
                                                    cout<<"Proprietarul cautat de dumneavostra nu exista"<<endl;
                                                else
                                                    cout<<"Alta eroare"<<endl;
                                            }
                                            list<Cladire*>::iterator i;
                                            for (i=cld.begin(); i!=cld.end() && index_hot; i++)
                                                index_hot--;
                                            InchiriereCladire(pers[index_prop],*i);
                                       }
                                       else
                                            break;
                    }
                    else if (optiune=='3')
                         {
                            char optiune_cabana;
                            cout<<"Comenzi(apasa x pentru a iesi)"<<endl;
                            cout<<"1.Adauga cabana"<<endl;
                            cout<<"2.Elimina cabana"<<endl;
                            cout<<"3.Modifica cabana"<<endl;
                            cout<<"4.Afiseaza cabana"<<endl;
                            cout<<"5.Rezerva cabana"<<endl;

                            cin>>optiune_cabana;
                            if (optiune_cabana=='1')
                            {
                                Cladire *aux=new Hotel;
                                cin>>*aux;
                                cld.push_back(aux);
                            }
                            else if (optiune_cabana=='2')
                                 {
                                    cout<<"Scrieti indexul cabanei pe care doriti sa o eliminati"<<endl;
                                    int index;
                                    cin>>index;
                                    try
                                    {
                                        if (index>cld.size())
                                            throw Eroare_index();
                                        list<Cladire*>::iterator i;
                                        for (i=cld.begin(); i!=cld.end() && index; i++)
                                            index--;
                                        cld.remove(*i);
                                    }
                                    catch (exception &e)
                                    {
                                        if (strcmp(e.what(),"index prea mare")==0)
                                            cout<<"Cabana cautata de dumneavoastra nu exista"<<endl;
                                        else
                                            cout<<"Alta eroare"<<endl;
                                    }
                                 }
                                 else if (optiune_cabana=='3')
                                      {
                                          cout<<"Scrieti indexul cabanei pe care doriti sa o modificati"<<endl;
                                          int index;
                                          cin>>index;
                                          try
                                          {
                                                if (index>cld.size())
                                                    throw Eroare_index();
                                                Cladire *aux=new Cabana;
                                                cin.get();
                                                cin>>*aux;
                                                list<Cladire*>::iterator i;
                                                for (i=cld.begin(); i!=cld.end() && index; i++)
                                                    index--;
                                                (*i)=aux;
                                          }
                                          catch (exception &e)
                                          {
                                              if (strcmp(e.what(),"index prea mare")==0)
                                                cout<<"Cabana cautata de dumneavoastra nu exista"<<endl;
                                              else
                                                cout<<"Alta eroare"<<endl;
                                          }
                                      }
                                      else if (optiune_cabana=='4')
                                           {
                                                cout<<"Scrieti indexul cabanei pe care doriti sa o vizualizati"<<endl;
                                                int index;
                                                cin>>index;
                                                try
                                                {
                                                    if (index>cld.size())
                                                        throw Eroare_index();
                                                    list<Cladire*>::iterator i;
                                                    for (i=cld.begin(); i!=cld.end() && index; i++)
                                                        index--;
                                                    cout<<*(*i);
                                                }
                                                catch (exception &e)
                                                {
                                                    if (strcmp(e.what(),"index prea mare")==0)
                                                        cout<<"Cabana cautata de dumneavoastra nu exista"<<endl;
                                                    else
                                                        cout<<"Alta eroare"<<endl;
                                                }
                                           }
                                           else if (optiune_cabana=='5')
                                                {
                                                    cout<<"Scrieti indexul proprietarului si indexul cabanei unde doriti sa va cazati"<<endl;
                                                    int index_prop,index_cab;
                                                    cin>>index_prop>>index_cab;
                                                    try
                                                    {
                                                        if (index_cab>cld.size())
                                                            throw Eroare_index();
                                                    }
                                                    catch (exception &e)
                                                    {
                                                        if (strcmp(e.what(),"index prea mare")==0)
                                                            cout<<"Cabana cautata de dumneavoastra nu exista"<<endl;
                                                        else
                                                            cout<<"Alta eroare"<<endl;
                                                    }
                                                    try
                                                    {
                                                        if (index_prop>pers.size())
                                                            throw Eroare_index();
                                                    }
                                                    catch (exception &e)
                                                    {
                                                        if (strcmp(e.what(),"index prea mare")==0)
                                                            cout<<"Proprietarul cautat de dumneavoastra nu exista"<<endl;
                                                        else
                                                            cout<<"Alta eroare"<<endl;
                                                    }
                                                    list<Cladire*>::iterator i;
                                                    for (i=cld.begin(); i!=cld.end() && index_cab; i++)
                                                        index_cab--;
                                                    InchiriereCladire(pers[index_prop],*i);
                                                }
                          }
                          else if (optiune=='4')
                               {
                                    char optiune_proprietar;
                                    cout<<"Comenzi(apasa x pentru a iesi)"<<endl;
                                    cout<<"1.Adauga proprietar"<<endl;
                                    cout<<"2.Elimina ultimul proprietar adaugat"<<endl;
                                    cout<<"3.Modifica proprietar"<<endl;
                                    cout<<"4.Afiseaza proprietar"<<endl;

                                    cin>>optiune_proprietar;

                                    if (optiune_proprietar=='1')
                                    {
                                        Persoana *aux=new Proprietar;
                                        cin>>*aux;
                                        pers.push_back(aux);
                                    }
                                    else
                                        if (optiune_proprietar=='2')
                                            pers.pop_back();
                                        else
                                            if (optiune_proprietar=='3')
                                            {
                                                cout<<"Scrieti indexul proprietarului pe care doriti sa il modificati"<<endl;
                                                int index;
                                                cin>>index;
                                                try
                                                {
                                                    if (index>pers.size())
                                                        throw Eroare_index();
                                                    Persoana *aux=new Proprietar;
                                                    cin.get();
                                                    cin>>*aux;
                                                    pers[index]=aux;
                                                }
                                                catch (exception &e)
                                                {
                                                    if (strcmp(e.what(),"index prea mare")==0)
                                                        cout<<"Proprietarul cautat de dumneavoastra nu exista"<<endl;
                                                    else
                                                        cout<<"Alta eroare"<<endl;
                                                }
                                            }
                                            else
                                                if (optiune_proprietar=='4')
                                                {
                                                    cout<<"Scrieti indexul proprietarului pe care doriti sa il vizualizati"<<endl;
                                                    int index;
                                                    cin>>index;
                                                    try
                                                    {
                                                        if (index>pers.size())
                                                            throw Eroare_index();
                                                    }
                                                    catch (exception &e)
                                                    {
                                                        if (strcmp(e.what(),"index prea mare")==0)
                                                            cout<<"Proprietarul cautat de dumneavoastra nu exista"<<endl;
                                                        else
                                                            cout<<"Alta eroare"<<endl;
                                                    }
                                                    cout<<pers[index];
                                                }
                               }
                               else
                                    break;
        }
    }
};
Singletone* Singletone::obiect=0;


int main()
{
    Singletone *s=s->getInstance();
    s->meniu();
    return 0;
}
