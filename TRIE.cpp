#include <iostream>
#include <string>

using namespace std;
#define ALFABET 26

typedef struct Wezel
{
    char klucz;
    Wezel* wezly[ALFABET];
    string tlumaczenie;
} Wezel;

Wezel* StworzWezel(char litera)
{
    Wezel* tmpWezel = new Wezel;
    tmpWezel->klucz = litera;
    tmpWezel->tlumaczenie = "-";
    for (int i = 0; i < ALFABET; i++) tmpWezel->wezly[i] = nullptr;
    return tmpWezel;
}
void DodajDoDrzewa(Wezel* wezel, const string& s, const string& t)
{
    for (unsigned int i = 0; i < s.size(); i++)
    {
        if (wezel->wezly[(int)(s[i] - 'a')] != nullptr && wezel->wezly[(int)(s[i] - 'a')]->klucz == s[i]) wezel = wezel->wezly[(int)(s[i] - 'a')];
        else
        {
            wezel->wezly[(int)(s[i] - 'a')] = StworzWezel(s[i]);
            wezel = wezel->wezly[(int)(s[i] - 'a')];
        }
    }
    wezel->tlumaczenie = t;
}
void SzukajTlumaczenia(Wezel* wezel, string s)
{
    for (unsigned int i = 0; i < s.size(); i++)
    {
        bool znalezione = 0;
        for (int j = 0; j < ALFABET; j++) // sprawdzamy czy mamy utworzonego node'a o podanym kluczu
        {
            if (wezel->wezly[j] != nullptr && wezel->wezly[j]->klucz == s[i])
            {
                wezel = wezel->wezly[j];
                znalezione = 1;
                break;
            }
        }
        if (znalezione == 0)
        {
            cout << "-\n";
            return;
        }
    }
    cout << wezel->tlumaczenie << "\n";
}
void WypiszTlumaczenia(Wezel* wezel)
{
    if (wezel->tlumaczenie != "-")  cout << wezel->tlumaczenie << "\n";

    for (int j = 0; j < ALFABET; j++)
    {
        if (wezel->wezly[j] != nullptr) WypiszTlumaczenia(wezel->wezly[j]);
    }

    return;
}
void TlumaczeniaSlowZaczynajacychSieNa(Wezel* wezel, const string& s)
{
    for (unsigned int i = 0; i < s.size(); i++)
    {
        bool znalezione = 0;
        for (int j = 0; j < ALFABET; j++)
        {
            if (wezel->wezly[j] != nullptr && wezel->wezly[j]->klucz == s[i])
            {
                wezel = wezel->wezly[j];
                znalezione = 1;
                break;
            }
        }
        if (znalezione == 0)
        {
            cout << "-\n";
            return;
        }
    }
    // dochodzimy do slowa ktore zawiera na poczatku s
    // wypisujemy tlumaczenia wezlow pod spodem
    WypiszTlumaczenia(wezel);
}
void UsunDrzewo(Wezel* wezel)
{
    for (int i = 0; i < ALFABET; i++)
    {
        if (wezel->wezly[i] != nullptr) UsunDrzewo(wezel->wezly[i]);
    }
    delete wezel;
}
int main()
{
    char input = ' ';
    string s;
    string t;

    Wezel* slownik = StworzWezel(' ');

    while (cin >> input)
    {
        if (input == '+')
        {
            cin >> s >> t;
            DodajDoDrzewa(slownik, s, t);
        }
        else if (input == '?')
        {
            cin >> s;
            SzukajTlumaczenia(slownik, s);
        }
        else if (input == '*')
        {
            cin >> s;
            TlumaczeniaSlowZaczynajacychSieNa(slownik, s);
        }
        else if (input == 'q') break;
    }
    UsunDrzewo(slownik);
}