#include <iostream>
#include<string.h>
using namespace std;

class IOInterface
{
public:
    // virtualizarea citirii
    virtual istream& citire(istream& is) = 0;
    virtual ostream& afisare(ostream& os) const = 0;
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
            is>>this->CNP;
            cout<<"Introduceti varsta: ";
            is>>this->varsta;
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
        Persoana(string nume, string prenume, string CNP, int varsta);
        Persoana();
        Persoana(const Persoana &p);
        Persoana& operator=(const Persoana& persoana);
        friend ostream & operator<<(ostream &out, const Persoana& p);
        friend istream & operator>>(istream &in, Persoana& p);
        ~Persoana();
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
        is>>this->nrProprietatiDetinute;
        cout<<"Introduceti incasarile totale: ";
        is>>this->IncasariTotale;
        return is;
    }

    ostream& afisare(ostream& os) const
    {
        Persoana::afisare(os);
        os<<"Numarul proprietatilor detinute: "<<this->nrProprietatiDetinute<<endl;
        os<<"Incasarile totale: "<<this->IncasariTotale<<endl;
        return os;
    }
    Proprietar(string nume, string prenume, string CNP, int varsta, int nrProprietatiDetinute, int IncasariTotale);
    Proprietar();
    Proprietar(const Proprietar &p);
    Proprietar& operator=(const Proprietar& proprietar);
    friend ostream & operator<<(ostream &out, const Proprietar& p);
    friend istream & operator>>(istream &in, Proprietar& p);
    ~Proprietar();
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
    if(this != &p) {

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
        is>>this->suprafata;
        cout<<"Introduceti adresa: ";
        is>>this->adresa;
        cout<<"Introduceti numarul de camere: ";
        is>>this->nrCamere;
        cout<<"Introduceti localizarea: ";
        is>>this->localizare;
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

    Cladire(int suprafata, string adresa, int nrCamere, string localizare, string numeProprietar);
    Cladire();
    Cladire(const Cladire &c);
    Cladire& operator=(const Cladire& cladire);
    friend ostream & operator<<(ostream &out, const Cladire& c);
    friend istream & operator>>(istream &in, Cladire& c);
    ~Cladire();
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
    string numePensiune;
    int pretInchiriere;
    string disponibilitate;
    string rating;

public:
    istream& citire(istream& is)
    {
        Cladire::citire(is);
        cout<<"Introduceti numele pensiunii: ";
        is>>this->numePensiune;
        cout<<"Introduceti pretul de inchiriere: ";
        is>>this->pretInchiriere;
        cout<<"Introduceti disponibilitatea: ";
        is>>this->disponibilitate;
        cout<<"Introduceti rating-ul: ";
        is>>this->rating;
        return is;
    }

    ostream& afisare(ostream& os) const
    {
        Cladire::afisare(os);
        os<<"Numele pensiunii: "<<this->numePensiune<<endl;
        os<<"Pret de inchiriere: "<<this->pretInchiriere<<endl;
        os<<"Disponibilitate: "<<this->disponibilitate<<endl;
        os<<"Rating: "<<this->rating<<endl;
        return os;
    }

    Pensiune(int suprafata, string adresa, int nrCamere, string localizare, string numeProprietar,
             string numePensiune, int pretInchiriere, string disponibilitate, string rating);
    Pensiune();
    Pensiune(const Pensiune &p);
    Pensiune& operator=(const Pensiune& pensiune);
    friend ostream & operator<<(ostream &out, const Pensiune& p);
    friend istream & operator>>(istream &in, Pensiune& p);
    ~Pensiune();
    void setDisponibilitate(string disponibilitate);
    void setPretInchiriere(int pretInchiriere);
    string getDisponibilitate();
    int getPretInchiriere();
};
Pensiune::Pensiune(int suprafata, string adresa, int nrCamere, string localizare, string numeProprietar,
                   string numePensiune, int pretInchiriere, string disponibilitate, string rating)
                   :Cladire(suprafata,adresa,nrCamere,localizare,numeProprietar)
{
    this->numePensiune=numePensiune;
    this->pretInchiriere=pretInchiriere;
    this->disponibilitate=disponibilitate;
    this->rating=rating;
}
Pensiune::Pensiune(): Cladire()
{
    this->numePensiune="-";
    this->pretInchiriere=0;
    this->disponibilitate="-";
}
Pensiune::Pensiune(const Pensiune &p): Cladire()
{
    this->numePensiune=p.numePensiune;
    this->pretInchiriere=p.pretInchiriere;
    this->disponibilitate=p.disponibilitate;
    this->rating=p.rating;
}
Pensiune& Pensiune::operator=(const Pensiune& p)
{
    if (this!=&p)
    {
        Cladire::operator=(p);
        this->numePensiune=p.numePensiune;
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
Pensiune::~Pensiune()
{
    this->numePensiune="-";
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
        is>>this->pretCamera;
        cout<<"Introduceti disponibilitatea: ";
        is>>this->disponibilitate;
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

    Hotel(int suprafata, string adresa, int nrCamere, string localizare, string numeProprietar,
          string numeHotel, int pretCamera, string disponibilitate, string rating);
    Hotel();
    Hotel(const Hotel &p);
    Hotel& operator=(const Hotel& hotel);
    friend ostream & operator<<(ostream &out, const Hotel& h);
    friend istream & operator>>(istream &in, Hotel& h);
    ~Hotel();
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


void InchirierePensiune(Proprietar &prop, Pensiune &pens)
{
    if (pens.getDisponibilitate()=="disponibil")
    {
        prop.setIncasariTotale(pens.getPretInchiriere());
        pens.setDisponibilitate("indisponibil");
    }
    else
        cout<<"Pensiunea nu este disponibila";
}
void InchiriereCameraHotel(Proprietar &prop, Hotel &hot)
{
    if (hot.getDisponibilitate()=="disponibil")
    {
        prop.setIncasariTotale(hot.getPretCamera());
        hot.setDisponibilitate("indisponibil");
    }
    else
        cout<<"Hotelul nu este disponibil";
}

int main()
{
    Persoana *pers=new Persoana[100];
    Proprietar *prop=new Proprietar[100];
    Pensiune *pens=new Pensiune[100];
    Hotel *hot=new Hotel[100];
    int n_persoana=0,n_pensiune=0,n_hotel=0,n_proprietar=0;
    char optiune;
    while(true)
    {
        cout<<"Comenzi(apasa x pentru a iesi)"<<endl;
        cout<<"1.Pensiune"<<endl;
        cout<<"2.Hotel"<<endl;
        cout<<"3.Proprietar"<<endl;

        cin>>optiune;

        if (optiune=='1')
        {
            char optiune_pensiune;
            cout<<"Comenzi(apasa x pentru a iesi)"<<endl;
            cout<<"1.Adauga pensiune"<<endl;
            cout<<"2.Elimina ultima pensiune adaugata"<<endl;
            cout<<"3.Modifica pensiune"<<endl;
            cout<<"4.Afiseaza pensiune"<<endl;
            cout<<"5.Rezerva pensiune"<<endl;

            cin>>optiune_pensiune;

            if (optiune_pensiune=='1')
            {
                Pensiune *aux=new Pensiune;
                cin>>*aux;
                pens[n_pensiune++]=*aux;
            }
            else
                if (optiune_pensiune=='2')
                    n_pensiune--;
                else
                    if (optiune_pensiune=='3')
                    {
                        cout<<"Scrieti indexul pensiunii pe care doriti sa o modificati"<<endl;
                        int index;
                        cin>>index;
                        if (index<n_pensiune)
                        {
                            Pensiune *aux=new Pensiune;
                            cin.get();
                            cin>>*aux;
                            pens[index]=*aux;
                        }
                        else
                            cout<<"Pensiunea ceruta de dumneavoastra a fost eliminata"<<endl;
                    }
                    else
                        if (optiune_pensiune=='4')
                        {
                           cout<<"Scrieti indexul pensiunii pe care doriti sa o vizualizati"<<endl;
                           int index;
                           cin>>index;
                           if (index<n_pensiune)
                               cout<<pens[index]<<endl;
                           else
                               cout<<"Pensiunea ceruta de dumneavoastra a fost eliminata"<<endl;
                        }
                        else
                            if (optiune_pensiune=='5')
                            {
                                cout<<"Scrieti indexul proprietarului si indexul pensiunii pe care doriti sa o inchiriati"<<endl;
                                int index_prop,index_pens;
                                cin>>index_prop>>index_pens;
                                InchirierePensiune(prop[index_prop],pens[index_pens]);
                            }
                            else
                                break;
        }
        else
            if (optiune=='2')
            {
                char optiune_hotel;
                cout<<"Comenzi(apasa x pentru a iesi)"<<endl;
                cout<<"1.Adauga hotel"<<endl;
                cout<<"2.Elimina ultimul hotel adaugat"<<endl;
                cout<<"3.Modifica hotel"<<endl;
                cout<<"4.Afiseaza hotel"<<endl;
                cout<<"5.Rezerva camera de hotel"<<endl;

                cin>>optiune_hotel;

                if (optiune_hotel=='1')
                {
                    Hotel *aux=new Hotel;
                    cin>>*aux;
                    hot[n_hotel++]=*aux;
                }
                else
                    if (optiune_hotel=='2')
                        n_hotel--;
                    else
                        if (optiune_hotel=='3')
                        {
                            cout<<"Scrieti indexul hotelului pe care doriti sa il modificati"<<endl;
                            int index;
                            cin>>index;
                            if (index<n_hotel)
                            {
                                Hotel *aux=new Hotel;
                                cin.get();
                                cin>>*aux;
                                hot[index]=*aux;
                            }
                            else
                                cout<<"Hotelul cerut de dumneavoastra a fost eliminat"<<endl;
                        }
                        else
                            if (optiune_hotel=='4')
                            {
                                cout<<"Scrieti indexul hotelului pe care doriti sa il vizualizati"<<endl;
                                int index;
                                cin>>index;
                                if (index<n_hotel)
                                    cout<<hot[index]<<endl;
                                else
                                    cout<<"Hotelul cerut de dumneavoastra a fost eliminat"<<endl;
                            }
                            else
                                if (optiune_hotel=='5')
                                {
                                    cout<<"Scrieti indexul proprietarului si indexul hotelului unde doriti sa va cazati"<<endl;
                                    int index_prop,index_hot;
                                    cin>>index_prop>>index_hot;
                                    InchiriereCameraHotel(prop[index_prop],hot[index_hot]);
                                }
                                else
                                    break;
            }
            else
                if (optiune=='3')
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
                        Proprietar *aux=new Proprietar;
                        cin>>*aux;
                        prop[n_proprietar++]=*aux;
                    }
                    else
                        if (optiune_proprietar=='2')
                            n_proprietar--;
                        else
                            if (optiune_proprietar=='3')
                            {
                                cout<<"Scrieti indexul proprietarului pe care doriti sa il modificati"<<endl;
                                int index;
                                cin>>index;
                                if (index<n_proprietar)
                                {
                                    Proprietar *aux=new Proprietar;
                                    cin.get();
                                    cin>>*aux;
                                    prop[index]=*aux;
                                }
                                else
                                    cout<<"Proprietarul cerut de dumneavoastra a fost eliminat"<<endl;
                            }
                            else
                                if (optiune_proprietar=='4')
                                {
                                    cout<<"Scrieti indexul proprietarului pe care doriti sa il vizualizati"<<endl;
                                    int index;
                                    cin>>index;
                                    if (index<n_proprietar)
                                        cout<<prop[index]<<endl;
                                    else
                                        cout<<"Proprietarul cerut de dumneavoastra a fost eliminat"<<endl;
                                }
                                else
                                    break;
                }
    }
    return 0;
}
