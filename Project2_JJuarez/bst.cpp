#include<iostream>
#include <algorithm>
#include <string>
#include <cctype>
using namespace std;

//binary tree with data as words, and counter as occurrences of that word
//two display functions were made, one for an INDEX giving the corresponding letter as index for the word, and one for regular display.

class BST
{
    struct node
    {
        string data;
        int counter;
        node* left;
        node* right;
    };
    
    node* root;
    string indexvar;
    node* makeEmpty(node* t)
    {
        if(t == NULL)
            return NULL;
        {
            makeEmpty(t->left);
            makeEmpty(t->right);
            delete t;
        }
        return NULL;
    }
    
    node* insert(string x,int counter, node* t)
    {
        if(t == NULL)
        {
            t = new node;
            t->data = x;
            t->counter = counter;
            t->left = t->right = NULL;
        }
        else if(x < t->data)
            t->left = insert(x,counter, t->left);
        else if(x > t->data)
            t->right = insert(x,counter, t->right);
        return t;
    }
    
    node* findMin(node* t)
    {
        if(t == NULL)
            return NULL;
        else if(t->left == NULL)
            return t;
        else
            return findMin(t->left);
    }
    
    node* findMax(node* t)
    {
        if(t == NULL)
            return NULL;
        else if(t->right == NULL)
            return t;
        else
            return findMax(t->right);
    }
    
    node* remove(string x, node* t)
    {
        node* temp;
        if(t == NULL)
            return NULL;
        else if(x < t->data)
            t->left = remove(x, t->left);
        else if(x > t->data)
            t->right = remove(x, t->right);
        else if(t->left && t->right)
        {
            temp = findMin(t->right);
            t->data = temp->data;
            t->right = remove(t->data, t->right);
        }
        else
        {
            temp = t;
            if(t->left == NULL)
                t = t->right;
            else if(t->right == NULL)
                t = t->left;
            delete temp;
        }
        
        return t;
    }
    void wordUsedTooOften(node* t)
     {
         if(t==NULL)
         {
             cout<<""<<endl;
         }
         else
         {
             cout << "Words used too often: " << endl;
             inorder(t);
         }
     
     }
    
    void inorder(node* t)
    {
        if(t == NULL)
        return;
        inorder(t->left);
        cout << t->data << " |occurrences: "<< t->counter << endl; ;
        inorder(t->right);
    }
    
    void inorderIndex(node* t)
    {
        if(t == NULL)
        {
            return;
        }
        inorderIndex(t->left);
        if(t->data[0]!=indexvar[0])
        {
            cout << endl << (char)(toupper(t->data[0])) << endl;
            indexvar = t->data[0];
        }
        cout << t->data << " |occurrences: "<< t->counter << endl; ;
        inorderIndex(t->right);
    }
    bool empty(node* t)
    {
        if(t == NULL)
        {
            return true;
        }
        else
            return false;
    }
    
    node* find(node* t, string x)
    {
        if(t == NULL)
        {
            cout << "No such word found."<<endl;;
            return NULL;
        }
        else if(x < t->data)
        {
            return find(t->left, x);
        }
        else if(x > t->data)
        {
            return find(t->right, x);
        }
        else
        {
            cout << "'" << t->data << "'" << " found " << t->counter << " times." << endl;
            return t;
        }
    }
    
public:
    BST()
    {
        root = NULL;
    }
    
    ~BST()
    {
        root = makeEmpty(root);
    }
    
    void insert(string x,int counter)
    {
        root = insert(x,counter, root);
    }
    
    void remove(string x)
    {
        root = remove(x, root);
    }
    
    void displayIndex()
    {
        indexvar = "!";
        inorderIndex(root);
        cout << endl;
    }
    void display()
    {
        inorder(root);
        cout << endl;
    }
    void displayOften()
    {
        wordUsedTooOften(root);
        cout << endl;
    }
    
    void search(string x)
    {
        node* temp = root;
        temp = find(root, x);
    }
    bool isEmpty()
    {
        return empty(root);
    }
    
};
