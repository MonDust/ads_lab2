#include <bits/stdc++.h>
using namespace std;
struct l_Node
{
    int index;
    string firstname, surname;
    l_Node* next;
};
void l_insert(l_Node** head_ref, l_Node* new_node)
{
    l_Node* p;
    if (*head_ref == NULL || (*head_ref)->index >= new_node->index)
    {
        new_node->next = *head_ref;
        *head_ref = new_node;
    }
    else
    {
        p = *head_ref;
        while (p->next != NULL && p->next->index < new_node->index)
            p = p->next;
        new_node->next = p->next;
        p->next = new_node;
    }
}
l_Node* l_new(int ix, string f, string s)
{
    l_Node* p = new l_Node();
    p->index = ix;
    p->firstname = f;
    p->surname = s;
    p->next = NULL;
    return p;
}
void l_print(l_Node* head)
{
    l_Node* p = head;
    while (p != NULL) {
        cout << p->index << " ";
        p = p->next;
    }
}
bool l_search(l_Node* head, int x)
{
    l_Node* current = head;
    while (current != NULL)
    {
        if (current->index == x)
            return true;
        current = current->next;
    }
    return false;
}

void l_delete(l_Node** head_ref, int key)
{
    l_Node* p = *head_ref;
    l_Node* prev = NULL;
    if (p != NULL && p->index == key)
    {
        *head_ref = p->next;
        delete p;
        return;
    }
      else
    {
    while (p != NULL && p->index != key)
    {
        prev = p;
        p = p->next;
    }
    if (p == NULL)
        return;
    prev->next = p->next;
    delete p;
    }
}
void test(int n)
{
    l_Node* head = NULL;
    fstream dane("dane0.txt");
    fstream wynik("wynikl6.txt", ios::app);
    int k;
    string s, f;
    int tab[n];
    clock_t poczatek, koniec;
    double czas_trwania;
    poczatek = clock();
    for(int i = 0; i < n; i++ )
    {
        dane>>k;
        dane>>f;
        dane>>s;
        tab[i] = k;
        l_insert(&head, l_new(k, f, s));
    }
    koniec = clock();
    czas_trwania = (double)(koniec - poczatek) / CLOCKS_PER_SEC;
    cout<<"dodawanie "<<n<<" elementow \t"<<czas_trwania<<endl;
    wynik<<n<<" "<<czas_trwania;
    dane.close();
    shuffle(tab, tab + n, default_random_engine(0));
    poczatek = clock();
    for(int i = 0; i < n; i++)
        l_search(head, tab[i]);
    koniec = clock();
    czas_trwania = (double)(koniec - poczatek) / CLOCKS_PER_SEC;
    cout<<"szukanie losowych elementow z "<<n<<" elementow \t"<<czas_trwania<<endl;
    wynik<<" "<<czas_trwania;
    poczatek = clock();
    for(int i = 0; i < n; i++)
        l_delete(&head, tab[i]);
    koniec = clock();
    czas_trwania = (double)(koniec - poczatek) / CLOCKS_PER_SEC;
    cout<<"usuwanie wszystkich z "<<n<<" elementow \t"<<czas_trwania<<endl;
    wynik<<" "<<czas_trwania<<endl;
    wynik.close();
}
int main()
{
    for(int i = 1000; i<100001; i+=9900)
        test(i);
    return 0;
}
