#include <iostream>
#include<string>
#include <vector>
#include <set>

using namespace std;

class Locuinta
{
protected:
    string nume;
    double suprafata;
    double discount;
    double pret;
    int index_locuinta;
    static int s_nr_locuinte;
public:
    Locuinta(): suprafata(0), discount(0),pret(0) {nume=""; index_locuinta = ++s_nr_locuinte;}
    Locuinta(string nume, double suprafata, double discount, double pret)   //constructor parametrizat
    {
        this->nume = nume;
        this->suprafata = suprafata;
        if(discount>=0 && discount<=10)
            this->discount = discount;
        else                                //daca discountul nu este intre 0% si 10%, acesta va fi 0
        {
            this->discount=0;
            cout<<"Discountul trebuie sa fie inte 0% si 10%";
        }
        this->pret = pret;
        Locuinta::fct_s_nr_locuinte();
        index_locuinta = s_nr_locuinte;
    }
    Locuinta(Locuinta &locuinta)      //constructor de copiere
        : nume(locuinta.nume), suprafata(locuinta.suprafata), discount(locuinta.discount), pret(locuinta.pret), index_locuinta(locuinta.index_locuinta) {}
    virtual ~Locuinta(){index_locuinta--;}
    static void fct_s_nr_locuinte() //metoda statica care incrementeaza indexul locuintelor create in timpul rularii programului
    {
        s_nr_locuinte++;
    }
    static int getNrLocuinte() {return s_nr_locuinte;} //metoda care returneaza numarul de locuinte din program
    friend std::istream& operator >>(std::istream& in,  Locuinta& locuinta);
    friend std::ostream& operator <<(std::ostream& out, const Locuinta& locuinta);
    Locuinta& operator=(const Locuinta& locuinta)//operator de atribuire
    {
        nume = locuinta.nume;
        suprafata = locuinta.suprafata;
        discount = locuinta.discount;
        index_locuinta = locuinta.index_locuinta;
        return *this;
    }
    virtual ostream& Afisare(ostream& out) const  //metoda virtuala de afisare
    {
        out<<"Index locuinta: "<<index_locuinta<<"\nNume client: "<<nume<<"\nSuprafata: "<<suprafata<<"\nDiscount: "<<discount<<"\nPret pe metru patrat: "<<pret<<endl;
        return out;
    }
    virtual istream& Citire(istream &in) //metoda virtuala de citire
    {
        cout<<"Nume client: ";
        in>>nume;
        try  //treatarea exceptiilor
        {
            cout<<"Suprafata: ";
            in>>suprafata;
            if(suprafata<=0)
                throw suprafata;
        }
        catch(double s)
        {
            cout<<"Suprafata trebuie sa fie pozitiva! \n";
            in>>suprafata;
        }
        try
        {
            cout<<"Discount: ";
            in>>discount;
            if(discount<0||discount>10)
                throw discount;
        }
        catch(double d)
        {
            cout<<"Discountul trebuie sa fie inte 0 si 10! \n";
            in>>discount;
        }
        try
        {
            cout<<"Pretul pe metru patrat: ";
            in>>pret;
            if(pret<0)
                throw pret;
        }
        catch(double p)
        {
            cout<<"Pretul trebuie sa fie pozitiv! \n";
            in>>pret;
        }

    index_locuinta = s_nr_locuinte;
    return in;
    }
};
int Locuinta::s_nr_locuinte = 0;

std::istream& operator >>(std::istream& in,  Locuinta& locuinta)
{
    return locuinta.Citire(in);
}
std::ostream& operator <<(std::ostream& out, const Locuinta& locuinta)
{
    return locuinta.Afisare(out);
}

class Apartament: public Locuinta
{
    int etaj;
public:
    Apartament(): Locuinta(), etaj(0){}
    Apartament(string nume, double suprafata, double discount, double pret, int etaj)//constructor parametrizat
        :Locuinta(nume, suprafata, discount, pret), etaj(etaj){}
    Apartament(Apartament &ap)      //constructor de copiere
        : Locuinta(ap.nume, ap.suprafata, ap.discount, ap.pret), etaj(ap.etaj) {}
    ~Apartament(){}
    double Chirie() //metoda de calcul al chiriei
    {
        double pret_intreg = pret * suprafata;  //pretul fara discount
        double chirie = pret_intreg - (discount / 100) * pret_intreg; //pretul cu discount
        return chirie;
    }
    ostream& Afisare(ostream& out) const //metoda de afisare
    {
        Locuinta::Afisare(out);
        out<<"Etaj: "<<etaj<<endl;
        return out;
    }
    istream& Citire(istream &in) //metoda de citire
    {
        Locuinta::Citire(in);
        try       //tratarea exceptiilor
        {
            cout<<"Etaj: ";
            in>>etaj;
            if(etaj<0)
                throw etaj;
        }
        catch(int e)
        {
            cout<<"Etajul trebuie sa fie pozitiv! \n";
            in>>etaj;
        }
        cout<<endl;
        return in;
    }

    friend std::istream& operator >>(std::istream& in,  Apartament& ap);
    friend std::ostream& operator <<(std::ostream& out, const Apartament& ap);
    Apartament& operator=(const Apartament& ap) //operator de atribuire
    {
        nume = ap.nume;
        suprafata = ap.suprafata;
        discount = ap.discount;
        pret = ap.pret;
        index_locuinta = ap.index_locuinta;
        etaj = ap.etaj;

        return *this;
    }
};


std::istream& operator >>(std::istream& in,  Apartament& ap)
{
    return ap.Citire(in);
}
std::ostream& operator <<(std::ostream& out, const Apartament& ap)
{
    return ap.Afisare(out);
}


class Casa: public Locuinta
{
    double suprafataCurte;
    double pretCurte;
    int nrEtaje;
    vector <double> suprafataEtaje;
public:
    Casa(): Locuinta(), suprafataCurte(0),pretCurte(0), nrEtaje(0){}
    Casa(string nume, double suprafata, double discount, double suprafataCurte, double pretCurte, int nrEtaje)  //constructor parametrizat
        :Locuinta(nume, suprafata, discount, pret), suprafataCurte(suprafataCurte), pretCurte(pretCurte), nrEtaje(nrEtaje)
        {
            double s;
            for(int i=0; i<nrEtaje; i++)
            {
                cout<<"Suprafata pe etajul "<<i<<endl;
                cin>>s;
                suprafataEtaje.push_back(s);
            }
        }
    Casa(Casa &casa)      //constructor de copiere
        : Locuinta(casa.nume, casa.suprafata, casa.discount, casa.pret), suprafataCurte(casa.suprafataCurte),
        pretCurte(casa.pretCurte), nrEtaje(nrEtaje), suprafataEtaje(suprafataEtaje){}
    ~Casa(){}
    double Chirie() //metoda pentru calculul chiriei
    {
        double pret_intreg = pret * suprafata; //pretul fara discount si fara pretul chiriei curtii
        double chirie_curte = suprafataCurte * pretCurte; // pretul chiriei curtii
        double chirie = pret_intreg - (discount / 100) * pret_intreg + chirie_curte; //nu se aplica discountul la chiria pe curte
        return chirie;
    }
    ostream& Afisare(ostream& out) const //metoda pentru afisare
    {
        Locuinta::Afisare(out);
        out<<"Suprafata curte: "<<suprafataCurte<<endl;
        out<<"Pret pe metru patrat de curte: "<<pretCurte<<endl;
        out<<"Numar etaje: "<<nrEtaje<<endl;
        for(int i=0; i<nrEtaje; i++)
            {
                out<<"Suprafata pe etajul "<<i<<" este "<<suprafataEtaje[i]<<endl;
            }
        return out;
    }
    istream &Citire(istream& in) //metoda pentru citire
    {
        Locuinta::Citire(in);
        try         //tratarea exceptiilor
        {
            cout<<"Suprafata curte: ";
            in>>suprafataCurte;
            if(suprafataCurte<0)
                throw suprafataCurte;
        }
        catch(double sc)
        {
            cout<<"Suprafata trebuie sa fie pozitiva! \n";
             in>>suprafataCurte;
        }
        try
        {
            cout<<"Pret pe metru patrat de curte: ";
            in>>pretCurte;
            if(pretCurte<0)
                throw pretCurte;
        }
        catch(double pc)
        {
            cout<<"Pretul trebuie sa fie pozitiv! \n";
           in>>pretCurte;
        }
        try
        {
            cout<<"Numar etaje: ";
            in>>nrEtaje;
            if(nrEtaje<0)
                throw nrEtaje;
        }
        catch(int nre)
        {
            cout<<"Numarul de etaje trebuie sa fie pozitiv! \n";
            in>>nrEtaje;
        }
        suprafataEtaje.resize(nrEtaje);
        double s=0;
        try //verifica daca suma suprafetelor este egala cu suprafata casei
        {
            s=0;
            for(int i=0; i<nrEtaje; i++)
            {
                cout<<"Suprafata pe etajul "<<i<<endl;
                in>>suprafataEtaje[i];
                s = s+suprafataEtaje[i];
            }
            if(s!=this->suprafata)
                throw s;
        }catch(double spe)
        {
            cout<<"Suma suprafetelor pe etaje trebuie sa fie egale cu suprafata casei! "<<endl;
            for(int i=0; i<nrEtaje; i++)
            {
                cout<<"Suprafata pe etajul "<<i<<endl;
                in>>suprafataEtaje[i];
            }
        }
        cout<<endl;
        return in;
    }
    friend std::istream& operator >>(std::istream& in,  Casa& casa);
    friend std::ostream& operator <<(std::ostream& out, const Casa& casa);
    Casa& operator=(const Casa& casa) //operator de atribuire
    {
        nume = casa.nume;
        suprafata = casa.suprafata;
        discount = casa.discount;
        pret = casa.pret;
        suprafataCurte = casa.suprafataCurte;
        pretCurte = casa.pretCurte;
        nrEtaje = casa.nrEtaje;
        suprafataEtaje = casa.suprafataEtaje;

        return *this;
    }
};

std::istream& operator >>(std::istream& in,  Casa& casa)
{
    return casa.Citire(in);
}
std::ostream& operator <<(std::ostream& out, const Casa& casa)
{
    return casa.Afisare(out);
}


template <class T>
class Gestiune
{
    int m_nr_locuinte;
    set<pair<Locuinta*,char>> m_locuinte; //pereche de <locuinta*, tip>
public:
    Gestiune(){m_nr_locuinte=0;}
    Gestiune(int nr_locuinte,set<pair<Locuinta*,char>> locuinte)//constructor parametrizat
    {
        m_nr_locuinte = nr_locuinte;
        m_locuinte = locuinte;
    }
    Gestiune(Gestiune<T>& gestiune) //constructor de copiere
    {
        this->m_nr_locuinte = gestiune.m_nr_locuinte;
        this->m_locuinte = gestiune.m_locuinte;
    }
    ~Gestiune()
    {
        m_nr_locuinte = 0;
        m_locuinte.clear();
    }
    Gestiune& operator=(Gestiune<T>& gestiune)//operator de atribuire
    {
        this->m_nr_locuinte = gestiune.m_nr_locuinte;
        this->m_locuinte = gestiune.m_locuinte;
        return *this;
    }
    friend istream& operator>>(istream& in, Gestiune<T>& gestiune)
    {
        cout<<"Numar locuinte: ";
        in>>gestiune.m_nr_locuinte;
        char tip;
        Locuinta* locuinta;
        for(int i=0; i<gestiune.m_nr_locuinte; i++)
        {
            cout<<"Alegeti:\nA - Apartament\nC - Casa:\n";
            cin>>tip;
            if(tip == 'A')
            {   locuinta = new Apartament;
                in>>dynamic_cast<Apartament&>(*locuinta);
                gestiune.m_locuinte.insert(make_pair(&*locuinta,tip));
            }
            else if(tip=='C')
            {
                locuinta = new Casa;
                in>>dynamic_cast<Casa&>(*locuinta);
                gestiune.m_locuinte.insert(make_pair(&*locuinta,tip));
            }
            else
                cout<<"Nu exista acest tip!\n";
        }
        return in;
    }
    friend ostream& operator<<(ostream& out, Gestiune<T>& gestiune)
    {
        out<<"Numarul de locuinte: ";
        out<<gestiune.m_nr_locuinte;
        out<<"\nLOCUINTELE: \n";
        for(auto it=gestiune.m_locuinte.begin();it!=gestiune.m_locuinte.end();it++)
        {
            out<<it->second<<"\n";
            out<<*(it->first)<<"\n";
        }
        return out;
    }
    friend Gestiune& operator+=(Gestiune<T>& gestiune, pair<Locuinta*,char> &p) //adauga o pereche <locuinta,tip> in gestiune
    {
        gestiune.m_nr_locuinte++;
        cout<<"Alegeti:\nA - Apartament\nC - Casa:\n";
        cin>>p.second;
        char tip = p.second;
        if(tip == 'A')
        {   p.first = new Apartament;
            cin>>dynamic_cast<Apartament&>(*p.first);
            gestiune.m_locuinte.insert(p);
        }
        else if(tip=='C')
        {
            p.first = new Casa;
            cin>>dynamic_cast<Casa&>(*p.first);
            gestiune.m_locuinte.insert(p);
        }
        else
            cout<<"Nu exista acest tip!\n";

        return gestiune;
    }
};

template<>
class Gestiune<Casa>
{
    int m_nr_case;
    vector <Casa*> m_case;
    vector <double> m_chirii;
public:
    Gestiune(){m_nr_case=0;m_case.resize(0);m_chirii.resize(0);}
    Gestiune(int nr_case,vector <Casa*> Case ) //constructor parametrizat
    {
        m_nr_case = nr_case;
        m_case = Case;
        for(int i=0; i<Case.size(); i++)    //se adauga chiriile in vectorul de chirii
        {
            double chirie = Case[i]->Chirie();
            m_chirii.push_back(chirie);
        }
    }
    Gestiune(Gestiune<Casa>& gestiune) //constructor de copiere
    {
        this->m_nr_case = gestiune.m_nr_case;
        this->m_case = gestiune.m_case;
        this->m_chirii = gestiune.m_chirii;
    }
    ~Gestiune()
    {
        m_nr_case = 0;
        m_case.clear();
        m_chirii.clear();
    }
    Gestiune& operator=(Gestiune<Casa>& gestiune)//operator de atribuire
    {
        this->m_nr_case = gestiune.m_nr_case;
        this->m_case = gestiune.m_case;
        this->m_chirii = gestiune.m_chirii;
        return *this;
    }
    void total_chirii() //metoda pentru afisarea sumei obtinute din chiriile pe gestiunea de case
    {
        double total=0;
        for(int i=0; i<m_case.size(); i++)
        {
            total+=m_chirii[i];
        }
        cout<<"Totalul obtinut de agentia imobiliara de pe urma chiriilor: "<<total<<endl;  // afisare total chirii

    }
    friend istream& operator>>(istream& in, Gestiune<Casa>& gestiune)
    {
        cout<<"Numar case: ";
        in>>gestiune.m_nr_case;
        gestiune.m_case.resize(gestiune.m_nr_case);
        for(int i=0; i<gestiune.m_nr_case; i++)
        {
            gestiune.m_case[i] = new Casa;
            in>>*gestiune.m_case[i];
            gestiune.m_chirii.push_back(gestiune.m_case[i]->Chirie()); //se adauga chiriile in vectorul de chirii
        }
        return in;
    }
    friend ostream& operator<<(ostream& out, Gestiune<Casa>& gestiune)
    {
        out<<"Numarul de case: ";
        out<<gestiune.m_nr_case;
        out<<"\nCASELE: \n";
        //double suma_chirii=0;
        for(int i=0; i<gestiune.m_case.size(); i++)
        {
            out<<*gestiune.m_case[i];
            out<<"Chiria: "<<gestiune.m_chirii[i]<< "\n\n";
            //suma_chirii+=gestiune.m_chirii[i];
        }
        //out<<"Totalul obtinut de agentia imobiliara de pe urma chiriilor: "<<suma_chirii<<endl;  // afisare total chirii
        return out;
    }
    friend Gestiune& operator+=(Gestiune<Casa>& gestiune, int nr) //gestiune += 3 reprezinta adaugarea a 3 case in gestiune
    {
        gestiune.m_nr_case += nr;
        for(int i=gestiune.m_nr_case-nr; i<gestiune.m_nr_case; i++)//pentru a parcurge doar ultimele nr pozitii
        {
            Casa* casa = new Casa;
            cin>>*casa;
            gestiune.m_case.push_back(casa);
            gestiune.m_chirii.push_back(gestiune.m_case[i]->Chirie()); //se adauga chiriile in vectorul de chirii
        }
        return gestiune;
    }

};

void OptiuniMeniu()
{
    cout<< "0. Oprire." <<endl;
    cout<< "1. Cititi o gestiune." <<endl;
    cout<< "2. Afisati gestiunea." <<endl;
    cout<< "3. Adaugati o pereche <locuinta,tip> in gestiune." <<endl;
    cout<< "4. Cititi o gestiune de case." <<endl;
    cout<< "5. Afisati gestiunea de case." <<endl;
    cout<< "6. Adaugati case in gestiunea de case." <<endl;
    cout<< "7. Afisati totalul obtinut de agentia imobiliara de pe urma chiriilor din gestiunea de case." <<endl;
    cout<< endl;
}

void MeniuInteractiv()
{
    cout<< "Alegeti o optiune: " <<endl;
    OptiuniMeniu();
    int optiune = 0;
    int stop = 0;

    Gestiune<pair<Locuinta*,char>> gestiune;
    Gestiune<Casa> gestiune_case ;

    cin>>optiune;
    while(optiune != stop)
    {
        if(optiune == 1)
        {
            cin>>gestiune;
        }
        else if(optiune == 2)
        {
            cout<<gestiune;
        }
        else if(optiune == 3)
        {
            pair<Locuinta*,char> pereche;
            gestiune += pereche;
        }
        else if(optiune==4)
        {
            cin>>gestiune_case;
        }
        else if(optiune == 5)
        {
            cout<<gestiune_case;
        }
        else if(optiune == 6)
        {
            int nr;
            cout<<"Numarul de case pe care doriti sa le adaugati: ";
            cin>>nr;
            gestiune_case += nr;
        }
        else if(optiune == 7)
        {
            gestiune_case.total_chirii();
        }
        else
            cout<<"Optiunea nu exista!"<<endl;
        OptiuniMeniu();
        cin>>optiune;
    }
}
int main()
{
    MeniuInteractiv();
    return 0;
}
