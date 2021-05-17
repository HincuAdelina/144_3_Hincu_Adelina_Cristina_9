# 144_3_Hincu_Adelina-Cristina_9

Tema 9 – Se dorește implementarea unei aplicații care sa permita gestionarea clienților și a proprietăților imobiliare în cadrul unei agenții imobiliare nou infiintate. Pentru fiecare locuință se cunoaște numele clientului care o închiriază, suprafata utila și discount-ul (0-10%). La apartamente se cunoaste etajul, iar la case se stie cati metri patrati are curtea, cate etaje are casa și care este suprafata utila pe fiecare etaj în parte. 
Evident, calculul chiriei se face diferit. Dacă la apartamente se considera doar formula data de prețul de închiriere pe metru pătrat * suprafata utila, avand grija sa se aplice discount unde este cazul, la casa, se adaugă, indiferent de discount, prețul pe metru pătrat de curte * suprafața acesteia.
Structura de date: set<pair<locuinta, tip>> unde tip = apartament sau casa

Cerința suplimentară: 
- Să se adauge toate campurile relevante pentru modelarea acestei probleme.
- Să se construiască clasa template Gestiune, continand structura de obiecte de tipul locuintelor implementate, alocat dinamic, unde indexul fiecărei locuințe este incrementat automat la adaugarea uneia noi, prin supraincarcarea operatorului +=. 
- Să se construiască o specializare pentru tipul Casa care sa stocheze numărul de case, fiecare cu chiria aferentă și afișează totalul obținut de agentia imobiliara de pe urma acestora. 

●	Cerințe comune tuturor temelor:

1.	utilizarea sabloanelor
2.	utilizarea STL
3.	utilizarea variabilelor, funcțiilor statice, constantelor și a unei functii const
4.	utilizarea conceptelor de RTTI raportat la templat-uri (ex: upcast & dynamic_cast)
5.	tratarea excepțiilor
6.	citirea informațiilor complete a n obiecte, memorarea și afișarea acestora


●	cerințe generale aplicate fiecărei teme din acest fișier:
- să se identifice și să se implementeze ierarhia de clase;
- clasele să conțină constructori, destructori, =, supraincarcare pe >> si << pentru citire si afisare;
- clasa de baza sa conțină funcție virtuala de afisare si citire, rescrisa în clasele derivate, iar operatorul de citire si afisare să fie implementat ca funcție prieten (în clasele derivate să se facă referire la implementarea acestuia în clasa de baza).
