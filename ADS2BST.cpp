#include <iostream>
#include <string>
#include <fstream>
#include <ctime>
#include <random>
#include <algorithm>
using namespace std;
struct BSTNode
{
    int index;
    string firstname, surname;
    BSTNode *left, *right;
};
BSTNode* bst_search(BSTNode *& root, int ix)
{
    if (root == NULL || root->index == ix)
       return root;
    if (root->index < ix)
       return bst_search(root->right, ix);
    return bst_search(root->left, ix);
}
BSTNode* bst_insert(BSTNode *& root, int ix, string f, string s)
{
    BSTNode * p = new BSTNode;
    p->left = p->right = 0;
    p->index = ix;
    p->surname = s;
    p->firstname = f;
    if (!root)
    {
        root = p;
    }
    else
    {
        if (ix > root->index)
            root->right = bst_insert(root->right, ix, f, s);
        else
            root->left = bst_insert(root->left, ix, f, s);
    }
    return root;
}
BSTNode* bst_new(int ix, string f, string s)
{
    BSTNode * p;
    p->index = ix;
    p->firstname = f;
    p->surname= s;
    p->left = p->right = NULL;
    return p;
}
BSTNode* bst_min(BSTNode *& root)
{
    BSTNode * p = root;
    while (p && p->left != NULL)
        p = p->left;
    return p;
}
BSTNode* bst_delete(BSTNode *& root, int ix)
{
    if (!root)
        return root;
    if (ix < root->index)
        root->left = bst_delete(root->left, ix);
    else if (ix > root->index)
        root->right = bst_delete(root->right, ix);
    else {
        if (root->left==NULL && root->right==NULL)
            return NULL;
        else
            if (root->left == NULL)
            {
                BSTNode * p = root->right;
                free(root);
                return p;
            }

        else
            if (root->right == NULL)
            {
                BSTNode * p = root->left;
                free(root);
                return p;
            }
        BSTNode * p = bst_min(root->right);
        root->index = p->index;
        root->firstname = p->firstname;
        root->surname = p->surname;
        root->right = bst_delete(root->right, p->index);
    }
    return root;
}
void bst_preorder(BSTNode *& root)
{
    if (!root)
        return;
    cout<<root->index<<" ";
    bst_preorder(root->left);
    bst_preorder(root->right);
}
void bst_inorder(BSTNode *& root)
{
    if (!root)
        return;
    bst_inorder(root->left);
    cout<<root->index<<" ";
    bst_inorder(root->right);
}
void bst_postorder(BSTNode *& root)
{
    if (!root)
        return;
    bst_postorder (root->left);
    bst_postorder(root->right);
    cout<<root->index<<" ";
}
void test(int n)
{
    BSTNode * root = 0;
    BSTNode * a;
    fstream dane("dane0.txt");
    fstream wynik("wynikb0.txt", ios::app);
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
        bst_insert(root, k, f, s);
    }
    koniec = clock();
    czas_trwania = (double)(koniec - poczatek) / CLOCKS_PER_SEC;
    cout<<"dodawanie "<<n<<" elementow \t"<<czas_trwania<<endl;
    wynik<<n<<" "<<czas_trwania;
    dane.close();
    shuffle(tab, tab + n, default_random_engine(0));
    poczatek = clock();
    for(int i = 0; i < n; i++)
        a = bst_search(root, tab[i]);
    koniec = clock();
    czas_trwania = (double)(koniec - poczatek) / CLOCKS_PER_SEC;
    cout<<"szukanie losowych elementow z "<<n<<" elementow \t"<<czas_trwania<<endl;
    wynik<<" "<<czas_trwania;
    poczatek = clock();
    for(int i = 0; i < n; i++)
        root = bst_delete(root, tab[i]);
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
