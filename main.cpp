#include <iostream>
#include<string.h>
#include<fstream>
#include<vector>
using namespace std;

ifstream fin("Date.in");

/***************************************/
class Locuinta
{
protected:
    char *nume;
    double S_utila;
    double pret_metru;
    int discount;

public:
    Locuinta();

    Locuinta(char* n, double S, double p, int d);

    ~Locuinta();

    Locuinta(const Locuinta& c);

    Locuinta& operator=(const Locuinta& c);

    virtual double calcul_pret_chirie()=0;

    virtual void afisare()=0;

    virtual void citire(istream & in);

    virtual void citire_f(ifstream & fin);

    virtual void afis(ostream & out);

    friend istream & operator>>(istream& in, Locuinta& ob);

    friend ifstream & operator>>(ifstream& fin, Locuinta& ob);

    friend ostream & operator<<(ostream& out, Locuinta& ob);

    char* get_nume()
    {return nume;}
};

Locuinta::Locuinta()
{
    nume=NULL;
    S_utila=0.0;
    pret_metru=0.0;
    discount=0;
}

Locuinta::Locuinta(char* n, double S, double p, int d)
{
    nume=new char[strlen(n)+1];
    strcpy(nume,n);
    S_utila=S;
    pret_metru=p;
    discount=d;
}

Locuinta::~Locuinta()
{    delete[]nume;}

Locuinta::Locuinta(const Locuinta& c)
{
    nume=new char[strlen(c.nume)+1];
    strcpy(nume,c.nume);
    S_utila=c.S_utila;
    pret_metru=c.pret_metru;
    discount=c.discount;
}

Locuinta& Locuinta::operator=(const Locuinta& c)
{
    if(this==&c)
        return *this;

    delete []nume;
    nume=new char[strlen(c.nume)+1];
    strcpy(nume,c.nume);
    S_utila=c.S_utila;
    pret_metru=c.pret_metru;
    discount=c.discount;

    return (*this);
}

void Locuinta::citire(istream& in)
{
    char sir[100];
    cout<<"\nDati numele chiriasului: \n";
    in>>sir;
    nume=new char[strlen(sir)+1];
    strcpy(nume,sir);
    cout<<"Dati suprafata utila: \n";
    in>>S_utila;
    cout<<"Dati pret/metru_2 - suprafata utila: \n";
    in>>pret_metru;
    cout<<"Dati discountul: \n";
    in>>discount;
}

void Locuinta::citire_f(ifstream & fin)
{
    char sir[100];
    fin>>sir;
    nume=new char[strlen(sir)+1];
    strcpy(nume,sir);
    fin>>S_utila;
    fin>>pret_metru;
    fin>>discount;
}

void Locuinta::afis(ostream& out)
{out<<"Numele chiriasului: "<<nume<<"\nSuprafata utila: "<<S_utila<<"\nPret/metru_2: "<<pret_metru<<"\nDiscount :"<<discount;}

istream& operator>>(istream& in, Locuinta& ob)
{
    ob.citire(in);
    return in;
}

ifstream& operator>>(ifstream& fin, Locuinta& ob)
{
    ob.citire_f(fin);
    return fin;
}

ostream& operator<<(ostream& out, Locuinta& ob)
{
    ob.afis(out);
    return out;
}
/***************************************/
class Casa:public Locuinta
{
    double S_curte;
    int nr_etaje;
    double pret_curte;
    double *v;

public:
    Casa();

    Casa(char *N, double S, unsigned int d, double p, double Sc, int n_et,double pret_c, double * vec);

    ~Casa();

    Casa(const Casa& c);

    Casa& operator=(const Casa& c);

    double calcul_pret_chirie();

    void afisare();

    void citire(istream& in);

    void citire_f(ifstream& fin);

    void afis(ostream& out);

    friend istream& operator>>(istream& in, Casa& ob);

    friend ifstream& operator>>(ifstream& fin, Casa& ob);

    friend ostream& operator<<(ostream& out, Casa& ob);

};

Casa::Casa()
        :Locuinta()
{
    S_curte=0.0;
    nr_etaje=0;
    v=new double[nr_etaje];
    pret_curte=0;
    for(int i=0;i<nr_etaje;i++)
        v[i]=0.0;
}

Casa::Casa(char *N, double S, unsigned int d, double p, double Sc, int n_et, double pret_c, double *vec)
          :Locuinta(N,S,d,p)
{
    S_curte=Sc;
    nr_etaje=n_et;
    v=new double[nr_etaje];
    pret_curte=pret_c;
    for(int i=0;i<nr_etaje;i++)
        v[i]=vec[i];
}

Casa::~Casa()
{    delete[]v;}

Casa::Casa(const Casa& c)
           :Locuinta(c)
{
    S_curte=c.S_curte;
    nr_etaje=c.nr_etaje;
    v=new double[nr_etaje];
    v=c.v;
}

Casa& Casa::operator=(const Casa& c)
{
    if(this!=&c)
    {
        Locuinta::operator=(c);
        delete []v;
        S_curte=c.S_curte;
        nr_etaje=c.nr_etaje;
        v=new double[nr_etaje];
        v=c.v;
        return (*this);
    }
    else
        return (*this);
}

double Casa::calcul_pret_chirie()
{
    double p,S=0;
    p=pret_metru-(pret_metru*discount)/100.0;

    int i;
    for(i=0;i<nr_etaje;i++)
        S+=v[i];
    S+=S_utila;
    return S*p+S_curte*pret_curte;
}

istream& operator>>(istream& in, Casa& ob)
{
    ob.citire(in);
    return in;
}

ifstream& operator>>(ifstream& fin, Casa& ob)
{
    ob.citire_f(fin);
    return fin;
}

ostream& operator<<(ostream& out, Casa& ob)
{
    ob.afis(out);
    return out;
}

void Casa::afisare()
{
    cout<<"Casa: \n";
    cout<<"Nume: "<<nume<<"\n"<<"Suprafata utila este: "<<S_utila<<"\n"<<"Discountul este: "<<discount<<"\n";
    cout<<"Pret/m_2 : "<<pret_metru<<"\n"<<"Suprafata curtii este: "<<S_curte<<"\n"<<"Pret/m_2 pentru curte: "<<pret_curte<<"\n";
    cout<<"Numarul de etaje este: "<<nr_etaje<<"\n";
    cout<<"Suprafata pe fiecare etaj: \n";

    for(int i=0;i<nr_etaje;i++)
    {   if(i==0)
        cout<<"Parter: "<<" "<<v[i]<<endl;
        else
            cout<<"Etaj "<<i<<": "<<v[i]<<endl;
    }
}

void Casa::citire(istream& in)
{
    Locuinta::citire(in);

    cout<<"Dati suprafata curtii: \n";
    in>>S_curte;
    cout<<"Dati numarul de etaje: \n";
    in>>nr_etaje;
    cout<<"Dati pret/m_2 curte: \n";
    in>>pret_curte;
    cout<<"Dati suprafata utila de pe fiecare etaj:\n";
    v=new double[nr_etaje];
    for(int i=0;i<nr_etaje;i++)
    {
        if(i==0)
        cout<<"Parter:";
        else
        cout<<"Etaj "<<i<<" :";
        in>>v[i];
        cout<<"\n";
    }
}

void Casa::citire_f(ifstream& fin)
{
    Locuinta::citire_f(fin);

    fin>>S_curte;
    fin>>pret_curte;
    fin>>nr_etaje;
    v=new double[nr_etaje];
    for(int i=0;i<nr_etaje;i++)
        fin>>v[i];
}

void Casa::afis(ostream& out)
{
    Locuinta::afis(out);

    cout<<"Casa: \n";
    cout<<"Suprafata curtii este: "<<S_curte<<"\n";
    cout<<"Pret/m_2 pentru curte: "<<pret_curte<<"\n"<<"Numarul de etaje este: "<<nr_etaje<<"\n";
    cout<<"Suprafata pe fiecare etaj: \n";
    for(int i=0;i<nr_etaje;i++)
    {   if(i==0)
        cout<<"Parter: "<<" "<<v[i]<<endl;
        else
            cout<<"Etaj "<<i<<": "<<v[i]<<endl;
    }
}
/***************************************/
class Apartament:public Locuinta
{
    int etaj;
public:
    Apartament();

    Apartament(char *N, double S, unsigned int d, double p, int et);

    ~Apartament(){};

    Apartament(const Apartament& c);

    Apartament& operator=(const Apartament& c);

    double calcul_pret_chirie();

    void afisare();

    void citire(istream& in);

    void citire_f(ifstream& fin);

    friend istream& operator>>(istream& in, Apartament& ob);

    friend ifstream & operator>>(ifstream& fin, Apartament& ob);

    void afis(ostream& out);
};

Apartament::Apartament()
        :Locuinta()
{
    etaj=0;
}

Apartament::Apartament(char *N, double S, unsigned int d, double p, int et)
        :Locuinta(N,S,d,p)
{
    etaj=et;
}

Apartament::Apartament(const Apartament& c)
        :Locuinta(c)
{
    etaj=c.etaj;
}

Apartament& Apartament::operator=(const Apartament& c)
{
    if(this!=&c)
    {
        Locuinta::operator=(c);
        etaj=c.etaj;
        return (*this);
    }
    else
        return (*this);
}

void Apartament::afisare()
{
    cout<<"Apartament: \n"<<"Nume: "<<nume<<"\n"<<"Suprafata utila este: "<<S_utila<<"\n";
    cout<<"Discountul este: "<<discount<<"\n"<<"Pret/m_2 : "<<pret_metru<<"\n"<<"Etajul: "<<etaj<<"\n\n";
}

double Apartament::calcul_pret_chirie()
{
    pret_metru=pret_metru-(pret_metru*discount)/100.0;
    return S_utila*pret_metru;
}

void Apartament::citire(istream& in)
{
    Locuinta::citire(in);
    cout<<"Dati etajul unde se afla apartamentul: \n";
    in>>etaj;
}

void Apartament::citire_f(ifstream& fin)
{
    Locuinta::citire_f(fin);
    fin>>etaj;
}

istream& operator>>(istream& in, Apartament& ob)
{
    ob.citire(in);
    return in;
}

ifstream& operator>>(ifstream& fin, Apartament& ob)
{
    ob.citire_f(fin);
    return fin;
}

void Apartament::afis(ostream& out)
{
    Locuinta::afis(out);
    cout<<"\nApartament: ";
    cout<<"\nEtaj: "<<etaj;cout<<endl;
}

/********************/

template<class T>
class Gestiune
{
    vector <Locuinta*> L;
    vector <double> G;
    static unsigned int nrgestiuni;

public:
    Gestiune(){};

    Gestiune(vector <Locuinta *> Loc, vector <double> Gest);

    ~Gestiune();

    Gestiune(const Gestiune<T>& g);

    Gestiune& operator=(const Gestiune& g);

    void operator+=(T& ob);

    void afisare();

    int get_size()const;

    Locuinta* get_locuitor(int i)const;

    double get_chirie(int i)const;

    static void showStatic()
    {
        cout<<"Numarul de gestiuni este dat static: "<<nrgestiuni<<"\n";
    }

};
template <class T> unsigned int Gestiune<T>::nrgestiuni=0;

template <class T> Gestiune<T>::Gestiune(vector <Locuinta *> Loc, vector <double> Gest)
{

    unsigned int i;
    for(i=0;i<Loc.size();i++)
    {
         nrgestiuni++;
         L.push_back(Loc[i]);
         G.push_back(Gest[i]);
    }
}

template <class T> Gestiune<T>::~Gestiune()
{L.clear(); G.clear();}

template <class T> Gestiune<T>::Gestiune(const Gestiune<T>& g)
{
    if(g.get_size()==0)
        return;

    for(int i=0;i<g.get_size();i++)
    {
         L.push_back(g.get_locuitor(i));
         G.push_back(g.get_chirie(i));
    }
}

template <class T> Gestiune<T>& Gestiune<T>::operator=(const Gestiune<T>& g)
{
    if(this==&g)
        return (*this);
    L.clear();
    G.clear();
    for(int i=0;i<g.get_size();i++)
    {
        L.push_back(g.get_locuitor(i));
        G.push_back(g.get_chirie(i));
    }
    return (*this);
}

template <class T> void Gestiune<T>::operator+= (T& ob)
{
    nrgestiuni++;
    L.push_back(ob);
    G.push_back(ob->calcul_pret_chirie());
}

template <class T> void Gestiune<T>::afisare()
{
    unsigned int i;
    for(i=0;i<L.size();i++)
    {
       cout<<L[i]->get_nume();
       cout<<"\nChiria lunara este: "<<G[i];
       cout<<endl;
    }
}

template <class T> Locuinta* Gestiune<T>::get_locuitor(int i)const
{return L[i];}

template <class T> double Gestiune<T>::get_chirie(int i)const
{return G[i];}

template <class T> int Gestiune<T>::get_size()const
{return L.size();}

/***************************************/
template<>
class Gestiune <char *>
{
    vector <char *> L;
    static unsigned int nr_gestiuni;

public:
    Gestiune(){};

    Gestiune(vector <char *> Num);

    ~Gestiune();

    Gestiune(const Gestiune& g);

    Gestiune& operator=(const Gestiune& g);

    void operator+=(char* ob);

    void afisare();

    unsigned int get_size()const
    {return L.size();}

    unsigned int lung_sir(int i)const
    {return strlen(L[i]);}

    char* get_nume(int i)const
    {return L[i];}

    void Showstatic()Real-Estate-Agency
    {cout<<"\nNumarul de gestiuni pentr char* este dat static:  "<<nr_gestiuni<<"\n";}
};

unsigned int Gestiune<char *>::nr_gestiuni=0;

Gestiune<char *>::~Gestiune()
{L.clear();}

Gestiune<char *>::Gestiune(vector<char *> Num)
{
    unsigned int i;
    for(i=0;i<Num.size();i++)
    {
        L.push_back(Num[i]);
        nr_gestiuni++;
    }
}

Gestiune<char *>::Gestiune(const Gestiune<char *>& g)
{
    if(g.get_size()==0)
        return ;
    unsigned int i;
    for(i=0;i<g.get_size();i++)
     L.push_back(g.get_nume(i));
}

Gestiune<char *>& Gestiune<char *>::operator=(const Gestiune<char *>& g)
{
    if(this==&g)
        return (*this);

    L.clear();
    for(unsigned int i=0;i<g.get_size();i++)
     L.push_back(g.get_nume(i));

    return (*this);
}

void Gestiune<char *>::operator+=(char* ob)
{
    nr_gestiuni++;
    L.push_back(ob);
}

void Gestiune<char *>::afisare()
{
    for(unsigned int i=0;i<L.size();i++)
        cout<<L[i]<<" ";
}

/**********************************/
int main()
{
    unsigned int optiune;
    do
    {   cout<<"\nOptiuni:\n";
        cout<<"1. Clasa Casa\n";
        cout<<"2. Clasa Apartament\n";
        cout<<"3. Clasa Gestiune\n";
        cout<<"4. Clasa Gestiune specializare char*\n";
        cin>>optiune;

        switch(optiune)
        {

        case 1:
            {
                cout<<"Verificare pentru clasa Casa\n";
                Casa c;
                cin>>c;
                cout<<c;
                break;
            }
        case 2:
            {
                cout<<"Verificare pentru apartament\n";

                Apartament s;
                cin>>s;
                cout<<s;

                cout<<"Constructorul cu parametri:\n";
                char nume[10]="Popescu";
                Apartament u(nume,190.89,4,12.89,6);
                u.afisare();
                cout<<"Chiria pentru "<<u.get_nume()<<" este: "<<u.calcul_pret_chirie()<<"\n";

                cout<<"Constructorul de copiere:\n";
                Apartament z(u);
                z.afisare();

                Apartament r; r=s;
                r.afisare();
                break;
            }
        case 3:
            {
                cout<<"Verificare clasa Gestiune:\n";
                char nume[10]="Denis";
                Locuinta *y=new Apartament(nume,134.78,5,17.9,1);
                Locuinta *r=new Apartament ;
                fin>>(*r);

                Locuinta *u=new Apartament;
                fin>>(*u);

                Locuinta *g=new Casa;
                fin>>(*g);

                Locuinta *h=new Casa;
                fin>>(*h);

                Locuinta *m=new Apartament;
                Locuinta *n=new Apartament;
                fin>>(*n);
                fin>>(*m);

                vector<Locuinta *> L;
                L.push_back(r); L.push_back(u); L.push_back(g); L.push_back(h);

                vector<double> chirii;

                chirii.push_back(r->calcul_pret_chirie()); chirii.push_back(u->calcul_pret_chirie());
                chirii.push_back(g->calcul_pret_chirie()); chirii.push_back(h->calcul_pret_chirie());

                Gestiune <Locuinta *> F(L,chirii);//verificare constructor cu parametri
                F+=y; F+=m; F+=n;

                F.afisare();

                cout<<"\nOperatorul egal:\n";
                Gestiune <Locuinta *> H;
                H=F;
                H.afisare();
                F.showStatic();
                break;
            }
        case 4:
            {
                cout<<"Verificare clasa Gestiune pentru specializarea char*:\n";

                vector<char *> x;
                char sir[100][100]={"Rares","Ionica","Mircea","Vladimir","Lavinia"};

                x.push_back(sir[0]);

                Gestiune<char *> J(x);//verificare constructor cu parametri

                J+=sir[1]; J+=sir[2]; J+=sir[3]; J+=sir[4];
                J.afisare();
                J.Showstatic();
                break;
            }
        }

    }
    while(optiune<5);
    return 0;
}
