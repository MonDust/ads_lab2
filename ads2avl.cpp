#include<bits/stdc++.h>
#include <string>
using namespace std;
struct AVLNode
{
    int index;
    string firstname, surname;
    AVLNode *left;
    AVLNode *right;
    int height;
};

int height(AVLNode *N)
{
    if (N == 0)
        return 0;
    return N->height;
}
int maxi(int a, int b)
{
    return (a > b)? a : b;
}
AVLNode* newNode(int ix, string f, string s)
{
    AVLNode* node = new AVLNode();
    node->index = ix;
    node->firstname = f;
    node->surname = s;
    node->left = NULL;
    node->right = NULL;
    node->height = 1;
    return(node);
}
AVLNode *rightRotate(AVLNode *y)
{
    AVLNode *x = y->left;
    AVLNode *T2 = x->right;
    x->right = y;
    y->left = T2;
    y->height = maxi(height(y->left), height(y->right)) + 1;
    x->height = maxi(height(x->left), height(x->right)) + 1;
    return x;
}
AVLNode *leftRotate(AVLNode *x)
{
    AVLNode *y = x->right;
    AVLNode *T2 = y->left;
    y->left = x;
    x->right = T2;
    x->height = maxi(height(x->left), height(x->right)) + 1;
    y->height = maxi(height(y->left), height(y->right)) + 1;
    return y;
}
int getBalance(AVLNode *N)
{
    if (N == NULL)
        return 0;
    return height(N->left) - height(N->right);
}
AVLNode* avl_insert(AVLNode* node, int index, string f, string s)
{
    if (node == NULL)
        return(newNode(index, f, s));
    if (index < node->index)
        node->left = avl_insert(node->left, index, f, s);
    else if (index > node->index)
        node->right = avl_insert(node->right, index, f, s);
    else
        return node;
    node->height = 1 + maxi(height(node->left), height(node->right));
    int balance = getBalance(node);
    if (balance > 1 && index < node->left->index)
        return rightRotate(node);
    if (balance < -1 && index > node->right->index)
        return leftRotate(node);
    if (balance > 1 && index > node->left->index)
    {
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }
    if (balance < -1 && index < node->right->index)
    {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }
    return node;
}
AVLNode* avl_search(AVLNode * root, int ix)
{
    if (root == NULL || root->index == ix)
       return root;
    if (root->index < ix)
       return avl_search(root->right, ix);
    return avl_search(root->left, ix);
}

void avl_inorder(AVLNode *root)
{
    if (!root)
        return;
    avl_inorder(root->left);
    cout<<root->index<<" ";
    avl_inorder(root->right);
}
AVLNode * minValueAVLNode(AVLNode* Node)
{
    AVLNode* current = Node;
    while (current->left != NULL)
        current = current->left;
    return current;
}
AVLNode* deleteAVLNode(AVLNode* root, int index)
{
    if (root == NULL)
        return root;
    if ( index < root->index )
        root->left = deleteAVLNode(root->left, index);
    else if( index > root->index )
        root->right = deleteAVLNode(root->right, index);
    else
    {
        if( (root->left == NULL) || (root->right == NULL) )
        {
            AVLNode *temp = root->left ? root->left : root->right;
            if (temp == NULL)
            {
                temp = root;
                root = NULL;
            }
            else
            *root = *temp;
            free(temp);
        }
        else
        {
            AVLNode* temp = minValueAVLNode(root->right);
            root->index = temp->index;
            root->firstname = temp->firstname;
            root->surname = temp->surname;
            root->right = deleteAVLNode(root->right, temp->index);
        }
    }
    if (root == NULL)
        return root;
    root->height = 1 + maxi(height(root->left), height(root->right));
    int balance = getBalance(root);
    if (balance > 1 && getBalance(root->left) >= 0)
        return rightRotate(root);
    if (balance > 1 && getBalance(root->left) < 0)
    {
        root->left = leftRotate(root->left);
        return rightRotate(root);
    }
    if (balance < -1 && getBalance(root->right) <= 0)
        return leftRotate(root);
    if (balance < -1 && getBalance(root->right) > 0)
    {
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }
    return root;
}
void test(int n)
{
    AVLNode * root = 0;
    AVLNode * a;
    fstream dane("dane0.txt");
    fstream wynik("wynika0.txt", ios::app);
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
        root = avl_insert(root, k, f, s);
    }
    koniec = clock();
    czas_trwania = (double)(koniec - poczatek) / CLOCKS_PER_SEC;
    cout<<"dodawanie "<<n<<" elementow \t"<<czas_trwania<<endl;
    wynik<<n<<" "<<czas_trwania;
    dane.close();
    shuffle(tab, tab + n, default_random_engine(0));
    poczatek = clock();
    for(int i = 0; i < n; i++)
        a = avl_search(root, tab[i]);
    koniec = clock();
    czas_trwania = (double)(koniec - poczatek) / CLOCKS_PER_SEC;
    cout<<"szukanie losowych elementow z "<<n<<" elementow \t"<<czas_trwania<<endl;
    wynik<<" "<<czas_trwania;
    poczatek = clock();
    for(int i = 0; i < n; i++)
        root = deleteAVLNode(root, tab[i]);
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
