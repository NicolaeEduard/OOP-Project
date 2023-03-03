#include <iostream>
#include<string.h>
#include<math.h>
using namespace std;

class Persoana
{
private:
    char *nume;
    char InitialaTata;
    char *unitatiInchiriatePrecedent;
    double buget;
    static int contorID;
    const int idPersoana;
    int *sumeCheltuite;
    int nrProprietari;
public:
    Persoana(char *nume, char InitialaTata, char *unitatiInchiriatePrecedent, double buget, int *sumeCheltuite, int nrProprietari);
    Persoana();
    Persoana(char *nume, char InitialaTata);
    Persoana(Persoana &p);
    Persoana& operator=(const Persoana& persoana);
    friend ostream & operator<<(ostream &out, const Persoana& p);
    friend istream & operator>>(istream &in, Persoana& p);
    ~Persoana();
    const Persoana operator++();//pre-inc
    const Persoana operator++(int);//post-inc
    bool operator==(const Persoana& p);
    bool operator>=(const Persoana& p);
    Persoana operator+(int f);//p+i
    friend Persoana operator+(int f, Persoana p);//i+p
    Persoana operator*(double f);//p*d
    friend Persoana operator*(double f, Persoana p);//d*p
    int operator[](int index);

    void setNume(char *nume);
    void setInitialaTata(char InitialaTata);
    void setUnitatiInchiriatePrecedent(char *unitatiInchiriatePrecedent);
    void setBuget(double buget);
    void setContorID(int contorID);
    void setNrProprietari(int nrProprietari);
    void setSumeCheltuite(int *sumeCheltuite, int nrProprietari);

    char *getNume();
    char getInitialaTata();
    char *getUnitatiInchiriatePrecedent();
    double getBuget();
    int getContorID();
    int getIDPersoana();
    int *getSumeCheltuite();
    int getNrProprietari();

    //functionalitati

};
int Persoana::contorID=0;
Persoana::Persoana(char *nume, char InitialaTata, char *unitatiInchiriatePrecedent, double buget, int *sumeCheltuite, int nrProprietari):idPersoana(contorID++)
{
    this->nume=new char[strlen(nume)+1];
    strcpy(this->nume,nume);
    this->InitialaTata=InitialaTata;
    this->unitatiInchiriatePrecedent=new char[strlen(unitatiInchiriatePrecedent)+1];
    strcpy(this->unitatiInchiriatePrecedent,unitatiInchiriatePrecedent);
    this->buget=buget;
    this->nrProprietari=nrProprietari;
    this->sumeCheltuite=new int[nrProprietari];
    for (int i=0; i<nrProprietari; i++)
        this->sumeCheltuite[i]=sumeCheltuite[i];
}
Persoana::Persoana():idPersoana(contorID++)
{
    this->nume=new char[strlen("Anonim")+1];
    strcpy(this->nume,"Anonim");
    this->InitialaTata='-';
    this->unitatiInchiriatePrecedent=new char[strlen("Anonim")+1];
    strcpy(this->unitatiInchiriatePrecedent,"Anonim");
    this->buget=0;
    this->nrProprietari=0;
    this->sumeCheltuite=NULL;
}
Persoana::Persoana(char *nume, char InitialaTata):idPersoana(contorID++)
{
    this->nume=new char[strlen(nume)+1];
    strcpy(this->nume,nume);
    this->InitialaTata=InitialaTata;
    this->unitatiInchiriatePrecedent=new char[strlen("Anonim")+1];
    strcpy(this->unitatiInchiriatePrecedent,"Anonim");
    this->buget=0;
    this->nrProprietari=0;
    this->sumeCheltuite=NULL;
}
Persoana::Persoana(Persoana &p):idPersoana(contorID++)
{
    this->nume=new char[strlen(p.nume)+1];
    strcpy(this->nume,p.nume);
    this->InitialaTata=p.InitialaTata;
    this->unitatiInchiriatePrecedent=new char[strlen(p.unitatiInchiriatePrecedent)+1];
    strcpy(this->unitatiInchiriatePrecedent,p.unitatiInchiriatePrecedent);
    this->buget=p.buget;
    this->nrProprietari=p.nrProprietari;
    this->sumeCheltuite=new int[p.nrProprietari];
    for (int i=0; i<this->nrProprietari; i++)
        this->sumeCheltuite[i]=p.sumeCheltuite[i];
}
Persoana& Persoana::operator=(const Persoana& p)
{
    if (this!=&p)
    {
        if (this->nume!=NULL)
            delete[] this->nume;
        this->nume=new char[strlen(p.nume)+1];
        strcpy(this->nume,p.nume);
        this->InitialaTata=p.InitialaTata;
        if (this->unitatiInchiriatePrecedent!=NULL)
            delete[] this->unitatiInchiriatePrecedent;
        this->unitatiInchiriatePrecedent=new char[strlen(p.unitatiInchiriatePrecedent)+1];
        strcpy(this->unitatiInchiriatePrecedent,p.unitatiInchiriatePrecedent);
        this->buget=p.buget;
        this->nrProprietari=p.nrProprietari;
        if (this->sumeCheltuite!=NULL)
            delete[] this->sumeCheltuite;
        this->sumeCheltuite=new int[p.nrProprietari];
        for (int i=0; i<this->nrProprietari; i++)
            this->sumeCheltuite[i]=p.sumeCheltuite[i];
    }
}
ostream & operator<<(ostream & out, const Persoana& p)
{
    out<<"Numele persoanei este: "<<p.nume<<endl;
    out<<"Initiala prenumelui tatalui este: "<<p.InitialaTata<<endl;
    out<<"Unitati inchiriate precedent: "<<p.unitatiInchiriatePrecedent<<endl;
    out<<"Bugetul persoanei este: "<<p.buget<<endl;
    out<<"Numarul de proprietari cu care a interactionat: "<<p.nrProprietari<<endl;
    out<<"Sumele cheltuite in tranzactiile cu proprietarii: "<<endl;
    for (int i=0; i<p.nrProprietari; i++)
        out<<p.sumeCheltuite<<" ";
    out<<endl;
    out<<"ID-ul persoanei este: "<<p.idPersoana;
    return out;
}
istream &operator>>(istream &in, Persoana& p)
{
    char sir[100];
    if (p.nume)
        delete[] p.nume;
    if (p.sumeCheltuite)
        delete[] p.sumeCheltuite;
    if (p.unitatiInchiriatePrecedent)
        delete[] p.unitatiInchiriatePrecedent;

    cout<<"Introduceti numele persoanei: ";
    in.get(sir,100);
    p.nume=new char[strlen(sir)+1];
    strcpy(p.nume,sir);
    in.get();
    cout<<"Introduceti initiala prenumelui tatalui: ";
    in>>p.InitialaTata;
    cout<<"Introduceti numarul de proprietari cu care a interactionat: ";
    in>>p.nrProprietari;
    cout<<"Introduceti sumele cheltuite in tranzactiile cu proprietarii: ";
    p.sumeCheltuite=new int[p.nrProprietari];
    for (int i=0; i<p.nrProprietari; i++)
        in>>p.sumeCheltuite[i];
    cout<<"Introduceti numele unitatilor inchiriate precedent: ";
    in.get();
    in.get(sir,100);
    p.unitatiInchiriatePrecedent=new char[strlen(sir)+1];
    in.get();
    cout<<"Introduceti bugetul persoanei: ";
    in>>p.buget;
}
Persoana::~Persoana()
{
    if (this->nume!=NULL)
        delete[] this->nume;
    if (this->sumeCheltuite!=NULL)
        delete[] this->sumeCheltuite;
    if (this->unitatiInchiriatePrecedent!=NULL)
        delete[] this->unitatiInchiriatePrecedent;
    this->buget=0;
    this->InitialaTata='-';
    this->nrProprietari=0;
}
const Persoana Persoana::operator++()//pre-inc
{
    this->nrProprietari++;
    return *this;
}
const Persoana Persoana::operator++(int)//post-inc
{
    Persoana aux(*this);
    this->nrProprietari++;
    return aux;
}
bool Persoana::operator==(const Persoana& p)
{
    if (this->InitialaTata==p.InitialaTata && strcmp(this->nume,p.nume)==0)
        return true;
    return false;
}
bool Persoana::operator>=(const Persoana& p)
{
    if (strcmp(this->nume,p.nume)>0)
        return true;
    else if (strcmp(this->nume,p.nume)==0 && this->InitialaTata>p.InitialaTata)
        return true;
    return false;
}
Persoana Persoana::operator+(int d)     //Persoana+int
{
    Persoana aux(*this);
    aux.nrProprietari=aux.nrProprietari+d;
    return aux;
}
Persoana operator+(int d,Persoana p)    //int+Persoana
{
    Persoana aux(p);
    aux.nrProprietari=aux.nrProprietari+d;
    return aux;
}
Persoana Persoana::operator*(double d)     //Persoana*double
{
    Persoana aux(*this);
    aux.buget=aux.buget*d;
    return aux;
}
Persoana operator*(double d, Persoana p)  //double*Persoana
{
    Persoana aux(p);
    aux.buget=aux.buget*d;
    return aux;
}
int Persoana::operator[](int indice)
{
    if (indice>nrProprietari)
        return '-';
    return this->sumeCheltuite[indice];
}
void Persoana::setNume(char *nume)
{
    if (this->nume)
        delete[] this->nume;
    this->nume=new char[strlen(nume)+1];
    strcpy(this->nume,nume);
}
void Persoana::setInitialaTata(char InitialaTata)
{
    this->InitialaTata=InitialaTata;
}
void Persoana::setUnitatiInchiriatePrecedent(char *unitatiInchiriatePrecedent)
{
    if (this->unitatiInchiriatePrecedent)
        delete[] this->unitatiInchiriatePrecedent;
    this->unitatiInchiriatePrecedent=new char[strlen(unitatiInchiriatePrecedent)+1];
    strcpy(this->unitatiInchiriatePrecedent,unitatiInchiriatePrecedent);
}
void Persoana::setBuget(double buget)
{
    this->buget=buget;
}
void Persoana::setContorID(int contorID)
{
    this->contorID=contorID;
}
void Persoana::setNrProprietari(int nrProprietari)
{
    this->nrProprietari=nrProprietari;
}
void Persoana::setSumeCheltuite(int *sumeCheltuite, int nrProprietari)
{
    for (int i=0; i<nrProprietari; i++)
        this->sumeCheltuite[i]=sumeCheltuite[i];
}
char *Persoana::getNume()
{
    return this->nume;
}
char Persoana::getInitialaTata()
{
    return this->InitialaTata;
}
char *Persoana::getUnitatiInchiriatePrecedent()
{
    return this->unitatiInchiriatePrecedent;
}
double Persoana::getBuget()
{
    return this->buget;
}
int Persoana::getIDPersoana()
{
    return this->idPersoana;
}
int Persoana::getContorID()
{
    return this->contorID;
}
int *Persoana::getSumeCheltuite()
{
    return this->sumeCheltuite;
}
int Persoana::getNrProprietari()
{
    return this->nrProprietari;
}
class Pensiune
{
private:
    char *numePensiune;
    char *numeProprietar;
    long nrCamereOcupate;
    float pretCamera;
    bool disponibilitate;
    char rating;
public:
    Pensiune(char *numePensiune, char *numeProprietar, long nrCamereOcupate, float pretCamera, bool disponibilitate, char rating);
    Pensiune();
    Pensiune(char *numePensiune, char *numeProprietar);
    Pensiune(Pensiune &p);
    Pensiune& operator=(const Pensiune& pensiune);
    friend ostream & operator<<(ostream &out, const Pensiune& p);
    friend istream & operator>>(istream &in, Pensiune& p);
    ~Pensiune();
    const Pensiune operator++();//pre-inc
    const Pensiune operator++(int);//post-inc
    bool operator==(const Pensiune& p);
    bool operator<=(const Pensiune& p);
    Pensiune operator+(long f);//Pensiune+float
    friend Pensiune operator+(long f, Pensiune p);//float+Pensiune
    Pensiune operator*(float f);//Pensiune*float
    friend Pensiune operator*(float f, Pensiune p);//float*Pensiune
    char operator[](int index);

    void setNumePensiune(char *numePensiune);
    void setNumeProprietar(char *numeProprietar);
    void setNrCamereOcupate(long nrCamereOcupate);
    void setPretCamera(float pretCamera);
    void setDisponibilitate(bool disponibilitate);
    void setRating(char rating);

    char *getNumePensiune();
    char *getNumeProprietar();
    long getNrCamereOcupate();
    float getPretCamera();
    bool getDisponibilitate();
    char getRating();
};
Pensiune::Pensiune(char *numePensiune, char *numeProprietar, long nrCamereOcupate, float pretCamera, bool disponibilitate, char rating)
{
    this->numePensiune=new char[strlen(numePensiune)+1];
    strcpy(this->numePensiune,numePensiune);
    this->numeProprietar=new char[strlen(numeProprietar)+1];
    strcpy(this->numeProprietar,numeProprietar);
    this->nrCamereOcupate=nrCamereOcupate;
    this->pretCamera=pretCamera;
    this->disponibilitate=disponibilitate;
    this->rating=rating;
}
Pensiune::Pensiune()
{
    this->numePensiune=new char[strlen("Necunoscut")+1];
    strcpy(this->numePensiune,"Necunoscut");
    this->numeProprietar=new char[strlen("Necunoscut")+1];
    strcpy(this->numeProprietar,"Necunoscut");
    this->nrCamereOcupate=0;
    this->pretCamera=0;
    this->disponibilitate=false;
    this->rating='-';
}
Pensiune::Pensiune(char *numePensiune, char *numeProprietar)
{
    this->numePensiune=new char[strlen(numePensiune)+1];
    strcpy(this->numePensiune,numePensiune);
    this->numeProprietar=new char[strlen(numeProprietar)+1];
    strcpy(this->numeProprietar,numeProprietar);
    this->nrCamereOcupate=0;
    this->pretCamera=0;
    this->disponibilitate=false;
    this->rating='-';
}
Pensiune::Pensiune(Pensiune &p)
{
    this->numePensiune=new char[strlen(p.numePensiune)+1];
    strcpy(this->numePensiune,p.numePensiune);
    this->numeProprietar=new char[strlen(p.numeProprietar)+1];
    strcpy(this->numeProprietar,p.numeProprietar);
    this->nrCamereOcupate=p.nrCamereOcupate;
    this->pretCamera=p.pretCamera;
    this->disponibilitate=p.disponibilitate;
    this->rating=p.rating;
}
Pensiune& Pensiune::operator=(const Pensiune& p)
{
    if (this!=&p)
    {
        if (this->numePensiune!=NULL)
            delete[] this->numePensiune;
        if (this->numeProprietar!=NULL)
            delete[] this->numeProprietar;
        this->numePensiune=new char[strlen(p.numePensiune)+1];
        strcpy(this->numePensiune,p.numePensiune);
        this->numeProprietar=new char[strlen(p.numeProprietar)+1];
        strcpy(this->numeProprietar,p.numeProprietar);
        this->pretCamera=p.pretCamera;
        this->nrCamereOcupate=p.nrCamereOcupate;
        this->disponibilitate=p.disponibilitate;
        this->rating=p.rating;
    }
}
ostream & operator<<(ostream & out, const Pensiune& p)
{
    out<<"Numele pensiunii este: "<<p.numePensiune<<endl;
    out<<"Numele proprietarului este: "<<p.numeProprietar<<endl;
    out<<"Pretul unei camere este: "<<p.pretCamera<<endl;
    out<<"Numarul de camere ocupate este: "<<p.nrCamereOcupate<<endl;
    out<<"Este pensiunea disponibila?: "<<endl;
    if (p.disponibilitate==true)
        out<<"Da"<<endl;
    else
        out<<"Nu"<<endl;
    out<<"Rating-ul pensiunii este: "<<p.rating;
    return out;
}
istream &operator>>(istream &in, Pensiune& p)
{
    char sir[100];
    if (p.numePensiune)
        delete[] p.numePensiune;
    if (p.numeProprietar)
        delete[] p.numeProprietar;

    cout<<"Introduceti numele pensiunii: ";
    in.get(sir,100);
    p.numePensiune=new char[strlen(sir)+1];
    strcpy(p.numePensiune,sir);
    in.get();
    cout<<"Introduceti numele proprietarului pensiunii: ";
    in.get(sir,100);
    p.numeProprietar=new char[strlen(sir)+1];
    strcpy(p.numeProprietar,sir);
    in.get();
    cout<<"Introduceti pretul unei camere: ";
    in>>p.pretCamera;
    cout<<"Introduceti numarul de camere ocupate: ";
    in>>p.nrCamereOcupate;
    cout<<"Introduceti disponibilitatea inchirierii pensiunii: ";
    int aux;
    in>>aux;
    if (aux==1)
        p.disponibilitate=true;
    else
        p.disponibilitate=false;
    cout<<"Introduceti rating-ul pensiunii: ";
    in>>p.rating;
}
Pensiune::~Pensiune()
{
    if (this->numePensiune!=NULL)
        delete[] this->numePensiune;
    if (this->numeProprietar!=NULL)
        delete[] this->numeProprietar;
    this->pretCamera=0;
    this->nrCamereOcupate=0;
    this->disponibilitate=false;
    this->rating='-';
}
const Pensiune Pensiune::operator++()//pre-inc
{
    this->nrCamereOcupate++;
    return *this;
}
const Pensiune Pensiune::operator++(int)//post-inc
{
    Pensiune aux(*this);
    this->nrCamereOcupate++;
    return aux;
}
bool Pensiune::operator==(const Pensiune& p)
{
    if (strcmp(this->numeProprietar,p.numeProprietar)==0 && strcmp(this->numePensiune,p.numePensiune)==0)
        return true;
    return false;
}
bool Pensiune::operator<=(const Pensiune& p)
{
    if (strcmp(this->numePensiune,p.numePensiune)<0)
        return true;
    else if (strcmp(this->numePensiune,p.numePensiune)==0 && strcmp(this->numeProprietar,p.numeProprietar)<0)
        return true;
    return false;
}
Pensiune Pensiune::operator+(long d)     //Pensiune+long
{
    Pensiune aux(*this);
    aux.nrCamereOcupate=aux.nrCamereOcupate+d;
    return aux;
}
Pensiune operator+(long d,Pensiune p)    //long+Pensiune
{
    Pensiune aux(p);
    aux.nrCamereOcupate=aux.nrCamereOcupate+d;
    return aux;
}
Pensiune Pensiune::operator*(float d)     //Pensiune*float
{
    Pensiune aux(*this);
    aux.pretCamera=aux.pretCamera*d;
    return aux;
}
Pensiune operator*(float d, Pensiune p)  //float*Pensiune
{
    Pensiune aux(p);
    aux.pretCamera=aux.pretCamera*d;
    return aux;
}
char Pensiune::operator[](int indice)
{
    if (indice>strlen(numePensiune))
        return '-';
    return this->numePensiune[indice];
}
void Pensiune::setNumePensiune(char *numePensiune)
{
    if (this->numePensiune)
        delete[] this->numePensiune;
    this->numePensiune=new char[strlen(numePensiune)+1];
    strcpy(this->numePensiune,numePensiune);
}
void Pensiune::setNumeProprietar(char *numeProprietar)
{
    if (this->numeProprietar)
        delete[] this->numeProprietar;
    this->numeProprietar=new char[strlen(numeProprietar)+1];
    strcpy(this->numeProprietar,numeProprietar);
}
void Pensiune::setNrCamereOcupate(long nrCamereOcupate)
{
    this->nrCamereOcupate=nrCamereOcupate;
}
void Pensiune::setPretCamera(float pretCamera)
{
    this->pretCamera=pretCamera;
}
void Pensiune::setDisponibilitate(bool disponibilitate)
{
    this->disponibilitate=disponibilitate;
}
void Pensiune::setRating(char rating)
{
    this->rating=rating;
}
char *Pensiune::getNumePensiune()
{
    return this->numePensiune;
}
char *Pensiune::getNumeProprietar()
{
    return this->numeProprietar;
}
long Pensiune::getNrCamereOcupate()
{
    return this->nrCamereOcupate;
}
float Pensiune::getPretCamera()
{
    return this->pretCamera;
}
bool Pensiune::getDisponibilitate()
{
    return this->disponibilitate;
}
char Pensiune::getRating()
{
    return this->rating;
}

class Hotel
{
private:
    char *numeHotel;
    char *numeProprietar;
    int pretCamera;
    double pretFacilitati;
    bool disponibilitate;
    char rating;
public:
    Hotel(char *numeHotel, char *numeProprietar, int pretCamera, double pretFacilitati, bool disponibilitate, char rating);
    Hotel();
    Hotel(char *numePensiune, char *numeProprietar);
    Hotel(Hotel &p);
    Hotel& operator=(const Hotel& hotel);
    friend ostream & operator<<(ostream &out, const Hotel& h);
    friend istream & operator>>(istream &in, Hotel& h);
    ~Hotel();
    const Hotel operator++();//pre-inc
    const Hotel operator++(int);//post-inc
    bool operator==(const Hotel& h);
    bool operator<=(const Hotel& h);
    Hotel operator+(double d);//Hotel+double
    friend Hotel operator+(double d, Hotel h);//double+Hotel
    Hotel operator*(double f);//Hotel*double
    friend Hotel operator*(double f, Hotel h);//double*Hotel
    char operator[](int index);

    void setNumeHotel(char *numeHotel);
    void setNumeProprietar(char *numeProprietar);
    void setPretCamera(int pretCamera);
    void setPretFacilitati(double pretFacilitati);
    void setDisponibilitate(bool disponibilitate);
    void setRating(char rating);

    char *getNumeHotel();
    char *getNumeProprietar();
    int getPretCamera();
    double getPretFacilitati();
    bool getDisponibilitate();
    char getRating();
};
Hotel::Hotel(char *numeHotel, char *numeProprietar, int pretCamera, double pretFacilitati, bool disponibilitate, char rating)
{
    this->numeHotel=new char[strlen(numeHotel)+1];
    strcpy(this->numeHotel,numeHotel);
    this->numeProprietar=new char[strlen(numeProprietar)+1];
    strcpy(this->numeProprietar,numeProprietar);
    this->pretFacilitati=pretFacilitati;
    this->pretCamera=pretCamera;
    this->disponibilitate=disponibilitate;
    this->rating=rating;
}
Hotel::Hotel()
{
    this->numeHotel=new char[strlen("Necunoscut")+1];
    strcpy(this->numeHotel,"Necunoscut");
    this->numeProprietar=new char[strlen("Necunoscut")+1];
    strcpy(this->numeProprietar,"Necunoscut");
    this->pretFacilitati=0.0;
    this->pretCamera=0;
    this->disponibilitate=false;
    this->rating='-';
}
Hotel::Hotel(char *numeHotel, char *numeProprietar)
{
    this->numeHotel=new char[strlen(numeHotel)+1];
    strcpy(this->numeHotel,numeHotel);
    this->numeProprietar=new char[strlen(numeProprietar)+1];
    strcpy(this->numeProprietar,numeProprietar);
    this->pretFacilitati=0.0;
    this->pretCamera=0;
    this->disponibilitate=false;
    this->rating='-';
}
Hotel::Hotel(Hotel &h)
{
    this->numeHotel=new char[strlen(h.numeHotel)+1];
    strcpy(this->numeHotel,h.numeHotel);
    this->numeProprietar=new char[strlen(h.numeProprietar)+1];
    strcpy(this->numeProprietar,h.numeProprietar);
    this->pretFacilitati=h.pretFacilitati;
    this->pretCamera=h.pretCamera;
    this->disponibilitate=h.disponibilitate;
    this->rating=h.rating;
}
Hotel& Hotel::operator=(const Hotel& h)
{
    if (this!=&h)
    {
        if (this->numeHotel!=NULL)
            delete[] this->numeHotel;
        this->numeHotel=new char[strlen(h.numeHotel)+1];
        strcpy(this->numeHotel,h.numeHotel);
        if (this->numeProprietar!=NULL)
            delete[] this->numeProprietar;
        this->numeProprietar=new char[strlen(h.numeProprietar)+1];
        strcpy(this->numeProprietar,h.numeProprietar);
        this->pretCamera=h.pretCamera;
        this->pretFacilitati=h.pretFacilitati;
        this->disponibilitate=h.disponibilitate;
        this->rating=h.rating;
    }
}
ostream & operator<<(ostream & out, const Hotel& h)
{
    out<<"Numele hotelului este: "<<h.numeHotel<<endl;
    out<<"Numele proprietarului este: "<<h.numeProprietar<<endl;
    out<<"Pretul unei camere este: "<<h.pretCamera<<endl;
    out<<"Pretul facilitatilor este: "<<h.pretFacilitati<<endl;
    out<<"Este hotelul disponibil?: "<<endl;
    if (h.disponibilitate==true)
        out<<"Da"<<endl;
    else
        out<<"Nu"<<endl;
    out<<"Rating-ul hotelului este: "<<h.rating;
    return out;
}
istream &operator>>(istream &in, Hotel& h)
{
    char sir[100];
    if (h.numeHotel)
        delete[] h.numeHotel;
    if (h.numeProprietar)
        delete[] h.numeProprietar;

    cout<<"Introduceti numele hotelului: ";
    in.get(sir,100);
    h.numeHotel=new char[strlen(sir)+1];
    strcpy(h.numeHotel,sir);
    in.get();
    cout<<"Introduceti numele proprietarului hotelului: ";
    in.get(sir,100);
    h.numeProprietar=new char[strlen(sir)+1];
    strcpy(h.numeProprietar,sir);
    in.get();
    cout<<"Introduceti pretul unei camere: ";
    in>>h.pretCamera;
    cout<<"Introduceti pretul facilitatilor: ";
    in>>h.pretFacilitati;
    cout<<"Introduceti disponibilitatea hotelului: ";
    int aux;
    in>>aux;
    if (aux==1)
        h.disponibilitate=true;
    else
        h.disponibilitate=false;
    cout<<"Introduceti rating-ul hotelului: ";
    in>>h.rating;
}
Hotel::~Hotel()
{
    if (this->numeHotel!=NULL)
        delete[] this->numeHotel;
    if (this->numeProprietar!=NULL)
        delete[] this->numeProprietar;
    this->pretCamera=0;
    this->pretFacilitati=0;
    this->disponibilitate=false;
    this->rating='-';
}
const Hotel Hotel::operator++()//pre-inc
{
    this->pretCamera++;
    return *this;
}
const Hotel Hotel::operator++(int)//post-inc
{
    Hotel aux(*this);
    this->pretCamera++;
    return aux;
}
bool Hotel::operator==(const Hotel& h)
{
    if (strcmp(this->numeProprietar,h.numeProprietar)==0 && strcmp(this->numeHotel,h.numeHotel)==0)
        return true;
    return false;
}
bool Hotel::operator<=(const Hotel& h)
{
    if (strcmp(this->numeHotel,h.numeHotel)<0)
        return true;
    else if (strcmp(this->numeHotel,h.numeHotel)==0 && strcmp(this->numeProprietar,h.numeProprietar)<0)
        return true;
    return false;
}
Hotel Hotel::operator+(double d)     //Hotel+double
{
    Hotel aux(*this);
    aux.pretFacilitati=aux.pretFacilitati+d;
    return aux;
}
Hotel operator+(double d,Hotel p)    //double+Hotel
{
    Hotel aux(p);
    aux.pretFacilitati=aux.pretFacilitati+d;
    return aux;
}
Hotel Hotel::operator*(double d)     //*double
{
    Hotel aux(*this);
    aux.pretFacilitati=aux.pretFacilitati*d;
    return aux;
}
Hotel operator*(double d, Hotel p)  //double*Persoana
{
    Hotel aux(p);
    aux.pretFacilitati=aux.pretFacilitati*d;
    return aux;
}
char Hotel::operator[](int indice)
{
    if (indice>strlen(numeHotel))
        return '-';
    return this->numeHotel[indice];
}
void Hotel::setNumeHotel(char *numeHotel)
{
    if (this->numeHotel)
        delete[] this->numeHotel;
    this->numeHotel=new char[strlen(numeHotel)+1];
    strcpy(this->numeHotel,numeHotel);
}
void Hotel::setNumeProprietar(char *numeProprietar)
{
    if (this->numeProprietar)
        delete[] this->numeProprietar;
    this->numeProprietar=new char[strlen(numeProprietar)+1];
    strcpy(this->numeProprietar,numeProprietar);
}
void Hotel::setPretCamera(int pretCamera)
{
    this->pretCamera=pretCamera;
}
void Hotel::setPretFacilitati(double pretFacilitati)
{
    this->pretFacilitati=pretFacilitati;
}
void Hotel::setDisponibilitate(bool disponibilitate)
{
    this->disponibilitate=disponibilitate;
}
void Hotel::setRating(char rating)
{
    this->rating=rating;
}
char *Hotel::getNumeHotel()
{
    return this->numeHotel;
}
char *Hotel::getNumeProprietar()
{
    return this->numeProprietar;
}
int Hotel::getPretCamera()
{
    return this->pretCamera;
}
double Hotel::getPretFacilitati()
{
    return this->pretFacilitati;
}
bool Hotel::getDisponibilitate()
{
    return this->disponibilitate;
}
char Hotel::getRating()
{
    return this->rating;
}

class Proprietar
{
private:
    char *nume;
    char *ProprietatiDetinute;
    float* incasariPrecedente;
    int nrPersoane;
    int nrProprietatiDetinute;
    double varsta;
public:
    Proprietar(char *nume, char *ProprietatiDetinute, float *incasariPrecedente, int nrProprietatiDetinute, double varsta, int nrPersoane);
    Proprietar();
    Proprietar(char *nume, char *ProprietatiDetinute);
    Proprietar(Proprietar &p);
    Proprietar& operator=(const Proprietar& proprietar);
    friend ostream & operator<<(ostream &out, const Proprietar& p);
    friend istream & operator>>(istream &in, Proprietar& p);
    ~Proprietar();
    const Proprietar operator++();
    const Proprietar operator++(int);
    bool operator==(const Proprietar& p);
    bool operator<=(const Proprietar& p);
    Proprietar operator+(int f);//Proprietar+int
    friend Proprietar operator+(int f, Proprietar p);//int+Proprietar
    Proprietar operator*(int f);//Proprietar*int
    friend Proprietar operator*(int f, Proprietar p);//int*Proprietar
    float operator[](int index);

    void setNume(char *nume);
    void setProprietatiDetinute(char *ProprietatiDetinute);
    void setNrPersoane(int nrPersoane);
    void setIncasariPrecedente(float *incasariPrecedente, int nrPersoane);
    void setNrProprietatiDetinute(int nrProprietatiDetinute);
    void setVarsta(double varsta);

    char *getNume();
    char *getProprietatiDetinute();
    float *getIncasariPrecedente();
    int getNrPersoane();
    int getNrProprietatiDetinute();
    double getVarsta();
};
Proprietar::Proprietar(char *nume, char *ProprietatiDetinute, float *incasariPrecedente, int nrProprietatiDetinute, double varsta, int nrPersoane)
{
    this->nume=new char[strlen(nume)+1];
    strcpy(this->nume,nume);
    this->ProprietatiDetinute=new char[strlen(ProprietatiDetinute)+1];
    strcpy(this->ProprietatiDetinute,ProprietatiDetinute);
    this->nrProprietatiDetinute=nrProprietatiDetinute;
    this->varsta=varsta;
    this->nrPersoane=nrPersoane;
    this->incasariPrecedente=new float[nrPersoane];
    for (int i=0; i<nrPersoane; i++)
        this->incasariPrecedente[i]=incasariPrecedente[i];
}
Proprietar::Proprietar()
{
    this->nume=new char[strlen("Necunoscut")+1];
    strcpy(this->nume,"Necunoscut");
    this->ProprietatiDetinute=new char[strlen("Necunoscut")+1];
    strcpy(this->ProprietatiDetinute,"Necunoscut");
    this->varsta=0;
    this->nrPersoane=0;
    this->nrProprietatiDetinute=0;
    this->incasariPrecedente=NULL;
}
Proprietar::Proprietar(char *nume, char *ProprietatiDetinute)
{
    this->nume=new char[strlen(nume)+1];
    strcpy(this->nume,nume);
    this->ProprietatiDetinute=new char[strlen(ProprietatiDetinute)+1];
    strcpy(this->ProprietatiDetinute,ProprietatiDetinute);
    this->varsta=0;
    this->nrPersoane=0;
    this->nrProprietatiDetinute=0;
    this->incasariPrecedente=NULL;
}
Proprietar::Proprietar(Proprietar &p)
{
    this->nume=new char[strlen(p.nume)+1];
    strcpy(this->nume,p.nume);
    this->ProprietatiDetinute=new char[strlen(p.ProprietatiDetinute)+1];
    strcpy(this->ProprietatiDetinute,p.ProprietatiDetinute);
    this->nrProprietatiDetinute=p.nrProprietatiDetinute;
    this->varsta=p.varsta;
    this->nrPersoane=p.nrPersoane;
    this->incasariPrecedente=new float[p.nrPersoane];
    for (int i=0; i<p.nrPersoane; i++)
        this->incasariPrecedente[i]=p.incasariPrecedente[i];
}
Proprietar& Proprietar::operator=(const Proprietar& p)
{
    if (this!=&p)
    {
        if (this->nume!=NULL)
            delete[] this->nume;
        if (this->ProprietatiDetinute!=NULL)
            delete[] this->ProprietatiDetinute;
        if (this->incasariPrecedente!=NULL)
            delete[] this->incasariPrecedente;
        this->nume=new char[strlen(p.nume)+1];
        strcpy(this->nume,p.nume);
        this->ProprietatiDetinute=new char[strlen(p.ProprietatiDetinute)+1];
        strcpy(this->ProprietatiDetinute,p.ProprietatiDetinute);
        this->nrProprietatiDetinute=p.nrProprietatiDetinute;
        this->varsta=p.varsta;
        this->nrPersoane=p.nrPersoane;
        this->incasariPrecedente=new float[p.nrPersoane];
        for (int i=0; i<this->nrPersoane; i++)
            this->incasariPrecedente[i]=p.incasariPrecedente[i];
    }
}
ostream & operator<<(ostream & out, const Proprietar& p)
{
    out<<"Numele proprietarului este: "<<p.nume<<endl;
    out<<"Proprietatile detinute de catre proprietar sunt: "<<p.ProprietatiDetinute<<endl;
    out<<"Numarul proprietatilor detinute de catre proprietar este: "<<p.nrProprietatiDetinute<<endl;
    out<<"Varsta proprietarului este: "<<p.varsta<<endl;
    out<<"Numarul de persoane cu care proprietarul a facut tranzactii: "<<p.nrPersoane<<endl;
    out<<"Incasarile proprietarului: "<<endl;
    for (int i=0; i<p.nrPersoane; i++)
        out<<p.incasariPrecedente<<" ";
    out<<endl;
    return out;
}
istream &operator>>(istream &in, Proprietar& p)
{
    char sir[100];
    if (p.nume)
        delete[] p.nume;
    if (p.ProprietatiDetinute)
        delete[] p.ProprietatiDetinute;
    if (p.incasariPrecedente)
        delete[] p.incasariPrecedente;

    cout<<"Introduceti numele proprietarului: ";
    in.get(sir,100);
    p.nume=new char[strlen(sir)+1];
    strcpy(p.nume,sir);
    in.get();
    cout<<"Introduceti varsta proprietarului: ";
    in>>p.varsta;
    cout<<"Introduceti numarul de proprietati detinute: ";
    in>>p.nrProprietatiDetinute;
    cout<<"Introduceti numele proprietatilor detinute de proprietar: ";
    in.get();
    in.get(sir,100);
    p.nume=new char[strlen(sir)+1];
    strcpy(p.ProprietatiDetinute,sir);
    in.get();
    cout<<"Introduceti numarul de persoane cu care a interactionat: ";
    in>>p.nrPersoane;
    cout<<"Introduceti sumele incasate in tranzactiile cu clientii: ";
    in.get();
    p.incasariPrecedente=new float[p.nrPersoane];
    for (int i=0; i<p.nrPersoane; i++)
        in>>p.incasariPrecedente[i];
}
Proprietar::~Proprietar()
{
    if (this->nume!=NULL)
        delete[] this->nume;
    if (this->ProprietatiDetinute!=NULL)
        delete[] this->ProprietatiDetinute;
    if (this->incasariPrecedente!=NULL)
        delete[] this->incasariPrecedente;
    this->varsta=0;
    this->nrProprietatiDetinute=0;
    this->nrPersoane=0;
}
const Proprietar Proprietar::operator++()//pre-inc
{
    this->nrPersoane++;
    return *this;
}
const Proprietar Proprietar::operator++(int)//post-inc
{
    Proprietar aux(*this);
    this->nrPersoane++;
    return aux;
}
bool Proprietar::operator==(const Proprietar& p)
{
    if (this->varsta==p.varsta && strcmp(this->nume,p.nume)==0)
        return true;
    return false;
}
bool Proprietar::operator<=(const Proprietar& p)
{
    if (strcmp(this->nume,p.nume)<0)
        return true;
    else if (strcmp(this->nume,p.nume)==0 && this->varsta<p.varsta)
        return true;
    return false;
}
Proprietar Proprietar::operator+(int d)     //Proprietar+int
{
    Proprietar aux(*this);
    aux.nrPersoane=aux.nrPersoane+d;
    return aux;
}
Proprietar operator+(int d,Proprietar p)    //int+Proprietar
{
    Proprietar aux(p);
    aux.nrPersoane=aux.nrPersoane+d;
    return aux;
}
Proprietar Proprietar::operator*(int d)     //Proprietar*int
{
    Proprietar aux(*this);
    aux.nrPersoane=aux.nrPersoane*d;
    return aux;
}
Proprietar operator*(int d, Proprietar p)  //int*Proprietar
{
    Proprietar aux(p);
    aux.nrPersoane=aux.nrPersoane*d;
    return aux;
}
float Proprietar::operator[](int indice)
{
    if (indice>nrPersoane)
        return '-';
    return this->incasariPrecedente[indice];
}
void Proprietar::setNume(char *nume)
{
    if (this->nume)
        delete[] this->nume;
    this->nume=new char[strlen(nume)+1];
    strcpy(this->nume,nume);
}
void Proprietar::setProprietatiDetinute(char *ProprietatiDetinute)
{
    if (this->ProprietatiDetinute)
        delete[] this->ProprietatiDetinute;
    this->ProprietatiDetinute=new char[strlen(ProprietatiDetinute)+1];
    strcpy(this->ProprietatiDetinute,ProprietatiDetinute);
}
void Proprietar::setNrPersoane(int nrPersoane)
{
    this->nrPersoane=nrPersoane;
}
void Proprietar::setIncasariPrecedente(float *incasariPrecedente, int nrPersoane)
{
    for (int i=0; i<nrPersoane; i++)
        this->incasariPrecedente[i]=incasariPrecedente[i];
}
void Proprietar::setNrProprietatiDetinute(int nrProprietatiDetinute)
{
    this->nrProprietatiDetinute=nrProprietatiDetinute;
}
void Proprietar::setVarsta(double varsta)
{
    this->varsta=varsta;
}
char *Proprietar::getNume()
{
    return this->nume;
}
char *Proprietar::getProprietatiDetinute()
{
    return this->ProprietatiDetinute;
}
float *Proprietar::getIncasariPrecedente()
{
    return this->incasariPrecedente;
}
int Proprietar::getNrProprietatiDetinute()
{
    return this->nrProprietatiDetinute;
}
int Proprietar::getNrPersoane()
{
    return this->nrPersoane;
}
double Proprietar::getVarsta()
{
    return this->getVarsta();
}

int main()
{
    Persoana *pers=new Persoana[100];
    Pensiune *pens=new Pensiune[100];
    Hotel *hot=new Hotel[100];
    Proprietar *prop=new Proprietar[100];
    int n_persoana=0,n_pensiune=0,n_hotel=0,n_proprietar=0;
    char optiune;
    while(true)
    {
        cout<<"Comenzi(scrie x pentru a iesi):"<<endl;
        cout<<"1.Persoana."<<endl;
        cout<<"2.Pensiune."<<endl;
        cout<<"3.Hotel."<<endl;
        cout<<"4.Proprietar."<<endl;

        cin>>optiune;
        if (optiune=='1')
        {
            cout<<"1.Afiseaza datele unei persoane."<<endl;
            cout<<"2.Adauga o persoana."<<endl;
            cout<<"3.Elimina ultima persoana adaugata."<<endl;
            cout<<"4.Modifica datele unei persoane."<<endl;

            char opt_pers;
            cin>>opt_pers;

            if (opt_pers=='1')
            {
                cout<<"Dati indexul persoanei pe care o cautati:"<<endl;
                int index;
                cin>>index;
                if (index<n_persoana)
                    cout<<pers[index]<<endl;
                else
                    cout<<"Persoana ceruta de dumneavoastra a fost eliminata"<<endl;
            }
            else
                if (opt_pers=='2')
                {
                    Persoana p;
                    cin.get();
                    cin>>p;
                    pers[n_persoana++]=p;
                }
                else
                    if (opt_pers=='3')
                        n_persoana--;
                    else
                    {
                        cout<<"Scrieti indexul persoanei pe care doriti sa o modificati"<<endl;
                        int index;
                        cin>>index;
                        Persoana p;
                        cin.get();
                        cin>>p;
                        pers[index]=p;
                    }
        }
        else
            if (optiune=='2')
            {
                cout<<"1.Afiseaza datele unei pensiuni."<<endl;
                cout<<"2.Adauga o pensiune."<<endl;
                cout<<"3.Elimina ultima pensiune adaugata."<<endl;
                cout<<"4.Modifica datele unei pensiuni."<<endl;

                char opt_pens;
                cin>>opt_pens;

                if (opt_pens=='1')
                {
                    cout<<"Dati indexul pensiunii pe care o cautati:"<<endl;
                    int index;
                    cin>>index;
                    if (index<n_pensiune)
                        cout<<pens[index]<<endl;
                    else
                        cout<<"Pensiunea ceruta de dumneavoastra a fost eliminata"<<endl;
                }
                else
                    if (opt_pens=='2')
                    {
                        Pensiune p;
                        cin.get();
                        cin>>p;
                        pens[n_pensiune++]=p;
                    }
                    else
                        if (opt_pens=='3')
                            n_pensiune--;
                        else
                        {
                            cout<<"Scrieti indexul pensiunii pe care doriti sa o modificati"<<endl;
                            int index;
                            cin>>index;
                            Pensiune p;
                            cin.get();
                            cin>>p;
                            pens[index]=p;
                        }
            }
            else
                if (optiune=='3')
                {
                    cout<<"1.Afiseaza datele unui hotel."<<endl;
                    cout<<"2.Adauga un hotel."<<endl;
                    cout<<"3.Elimina ultimul hotel adaugat."<<endl;
                    cout<<"4.Modifica datele unui hotel."<<endl;

                    char opt_hotel;
                    cin>>opt_hotel;

                    if (opt_hotel=='1')
                    {
                        cout<<"Dati indexul hotelului pe care il cautati:"<<endl;
                        int index;
                        cin>>index;
                        if (index<n_hotel)
                            cout<<hot[index]<<endl;
                        else
                            cout<<"Hotelul cerut de dumneavoastra a fost eliminat"<<endl;
                    }
                    else
                        if (opt_hotel=='2')
                        {
                            Hotel h;
                            cin.get();
                            cin>>h;
                            hot[n_hotel++]=h;
                        }
                        else
                            if (opt_hotel=='3')
                                n_hotel--;
                            else
                            {
                                cout<<"Scrieti indexul hotelului pe care doriti sa il modificati"<<endl;
                                int index;
                                cin>>index;
                                Hotel h;
                                cin.get();
                                cin>>h;
                                hot[index]=h;
                            }
                }
                else
                    if (optiune=='4')
                    {
                        cout<<"1.Afiseaza datele unui proprietar."<<endl;
                        cout<<"2.Adauga un proprietar."<<endl;
                        cout<<"3.Elimina ultimul proprietar adaugat."<<endl;
                        cout<<"4.Modifica datele unui proprietar."<<endl;

                        char opt_prop;
                        cin>>opt_prop;

                        if (opt_prop=='1')
                        {
                            cout<<"Dati indexul proprietarului pe care il cautati:"<<endl;
                            int index;
                            cin>>index;
                            if (index<n_proprietar)
                                cout<<prop[index]<<endl;
                            else
                                cout<<"Proprietarul cerut de dumneavoastra a fost eliminat"<<endl;
                        }
                        else
                            if (opt_prop=='2')
                            {
                                Proprietar p;
                                cin.get();
                                cin>>p;
                                prop[n_proprietar++]=p;
                            }
                            else
                                if (opt_prop=='3')
                                    n_proprietar--;
                                else
                                {
                                    cout<<"Scrieti indexul proprietarului pe care doriti sa il modificati"<<endl;
                                    int index;
                                    cin>>index;
                                    Proprietar p;
                                    cin.get();
                                    cin>>p;
                                    prop[index]=p;
                                }
                    }
                    else
                        break;

    }
    return 0;
}
