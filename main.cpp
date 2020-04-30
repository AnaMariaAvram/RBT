#include <bits/stdc++.h>
#include <iostream>
using namespace std;
ifstream f("abce.in");
ofstream g("abce.out");

struct Node
{
    int data;
    Node *parent;
    Node *left;
    Node *right;
    int color;

};

class RBtree
{
    Node *root;
    Node *q;
public :
    RBtree()
    {
        q=NULL;
        root=NULL;
    }
    void insert(int &);
    void insertfix(Node *);
    void leftrotate(Node *);
    void rightrotate(Node *);
    void remove(int &);
    void interval(int &, int &,Node *);
    void succesorr( int &);
    void predecesorr(int &);
    Node* successor(Node *);
    void delfix(Node *);
    void disp();
    void display( Node *);
    void search(int &);
    Node* get();
};
Node * RBtree::get()
{
    return root;
}
void RBtree::insert(int &z)
{
    int i=0;
    Node *p,*q;
    Node *t=new Node;
    t->data=z;
    t->left=NULL;
    t->right=NULL;
    t->color='r';
    p=root;
    q=NULL;
    if(root==NULL)
    {
        root=t;
        t->parent=NULL;
    }
    else
    {
        while(p!=NULL)
        {
            q=p;
            if(p->data<t->data)
                p=p->right;
            else
                p=p->left;
        }
        t->parent=q;
        if(q->data<t->data)
            q->right=t;
        else
            q->left=t;
    }
    insertfix(t);
}
void RBtree::insertfix(Node *t)
{
    Node *u;
    if(root==t)
    {
        t->color='b';
        return;
    }
    while(t->parent!=NULL&&t->parent->color=='r')
    {
        Node *g=t->parent->parent;
        if(g->left==t->parent)
        {
            if(g->right!=NULL)
            {
                u=g->right;
                if(u->color=='r')
                {
                    t->parent->color='b';
                    u->color='b';
                    g->color='r';
                    t=g;
                }
            }
            else
            {
                if(t->parent->right==t)
                {
                    t=t->parent;
                    leftrotate(t);
                }
                t->parent->color='b';
                g->color='r';
                rightrotate(g);
            }
        }
        else
        {
            if(g->left!=NULL)
            {
                u=g->left;
                if(u->color=='r')
                {
                    t->parent->color='b';
                    u->color='b';
                    g->color='r';
                    t=g;
                }
            }
            else
            {
                if(t->parent->left==t)
                {
                    t=t->parent;
                    rightrotate(t);
                }
                t->parent->color='b';
                g->color='r';
                leftrotate(g);
            }
        }
        root->color='b';
    }
}

void RBtree::remove(int &x)
{

    Node *p;
    p=root;
    Node *y=NULL;
    Node *q=NULL;
    int found=0;
    while(p!=NULL&&found==0)
    {
        if(p->data==x)
            found=1;
        if(found==0)
        {
            if(p->data<x)
                p=p->right;
            else
                p=p->left;
        }
    }
    if(found)
    {
        if(p->left==NULL||p->right==NULL)
            y=p;
        else
            y=successor(p);
        if(y->left!=NULL)
            q=y->left;
        else
        {
            if(y->right!=NULL)
                q=y->right;
            else
                q=NULL;
        }
        if(q!=NULL)
            q->parent=y->parent;
        if(y->parent==NULL)
            root=q;
        else
        {
            if(y==y->parent->left)
                y->parent->left=q;
            else
                y->parent->right=q;
        }
        if(y!=p)
        {
            p->color=y->color;
            p->data=y->data;
        }
        if(y->color=='b')
            delfix(q);
    }
}

void RBtree::delfix(Node *p)
{
    Node *s;
    while(p!=root&&p->color=='b')
    {
        if(p->parent->left==p)
        {
            s=p->parent->right;
            if(s->color=='r')
            {
                s->color='b';
                p->parent->color='r';
                leftrotate(p->parent);
                s=p->parent->right;
            }
            if(s->right->color=='b'&&s->left->color=='b')
            {
                s->color='r';
                p=p->parent;
            }
            else
            {
                if(s->right->color=='b')
                {
                    s->left->color=='b';
                    s->color='r';
                    rightrotate(s);
                    s=p->parent->right;
                }
                s->color=p->parent->color;
                p->parent->color='b';
                s->right->color='b';
                leftrotate(p->parent);
                p=root;
            }
        }
        else
        {
            s=p->parent->left;
            if(s->color=='r')
            {
                s->color='b';
                p->parent->color='r';
                rightrotate(p->parent);
                s=p->parent->left;
            }
            if(s->left->color=='b'&&s->right->color=='b')
            {
                s->color='r';
                p=p->parent;
            }
            else
            {
                if(s->left->color=='b')
                {
                    s->right->color='b';
                    s->color='r';
                    leftrotate(s);
                    s=p->parent->left;
                }
                s->color=p->parent->color;
                p->parent->color='b';
                s->left->color='b';
                rightrotate(p->parent);
                p=root;
            }
        }
        p->color='b';
        root->color='b';
    }
}

void RBtree::leftrotate(Node *p)
{
    if(p->right==NULL)
        return ;
    else
    {
        Node *y=p->right;
        if(y->left!=NULL)
        {
            p->right=y->left;
            y->left->parent=p;
        }
        else
            p->right=NULL;
        if(p->parent!=NULL)
            y->parent=p->parent;
        if(p->parent==NULL)
            root=y;
        else
        {
            if(p==p->parent->left)
                p->parent->left=y;
            else
                p->parent->right=y;
        }
        y->left=p;
        p->parent=y;
    }
}
void RBtree::rightrotate(Node *p)
{
    if(p->left==NULL)
        return ;
    else
    {
        Node *y=p->left;
        if(y->right!=NULL)
        {
            p->left=y->right;
            y->right->parent=p;
        }
        else
            p->left=NULL;
        if(p->parent!=NULL)
            y->parent=p->parent;
        if(p->parent==NULL)
            root=y;
        else
        {
            if(p==p->parent->left)
                p->parent->left=y;
            else
                p->parent->right=y;
        }
        y->right=p;
        p->parent=y;
    }
}

Node* RBtree::successor(Node *p)
{
    Node *y=NULL;
    if(p->left!=NULL)
    {
        y=p->left;
        while(y->right!=NULL)
            y=y->right;
    }
    else
    {
        y=p->right;
        while(y->left!=NULL)
            y=y->left;
    }
    return y;
}



void  RBtree::succesorr(int &data)
{
    int cnt=0;
    Node *x=root;
    while (x!= NULL)
        if (x->data>=data)
        {
            cnt=x->data;
            if (cnt==data)
                break;
            x=x->left;
        }
        else
            x=x->right;
    g<<cnt<<endl;
}

void RBtree::interval(int &st, int &dr, Node *p)
{
    if (st<=p->data)
        if(p->left!=NULL)
            interval(st,dr,p->left);
    if (st<=p->data and dr>=p->data)
        g<<p->data<<" ";
    if (dr>=p->data)
        if (p->right!=NULL)
            interval(st,dr,p->right);
}

void RBtree::predecesorr(int &data)
{
    int cnt=0;
    Node *x=root;
    while (x!= NULL)
        if (x->data<=data)
        {
            cnt=x->data;
            if (cnt==data)
                break;
            x=x->right;
        }
        else
            x=x->left;
    g<<cnt<<endl;
}
void RBtree::search(int &x)
{
    Node *p=root;
    int found=0;
    while(p!=NULL&& found==0)
    {
        if(p->data==x)
            found=1;
        if(found==0)
        {
            if(p->data<x)
                p=p->right;
            else
                p=p->left;
        }
    }
   if(found==0) g<<"0";
   else g<<"1";
   g<<endl;
}
int n,op,NR,data1,data2;
RBtree P;
int main()
{
    f>>n;
    for(int i=1; i<=n; i++)
    {
        f>>op;
        if( op==1 )
        {
            f>>NR;
            P.insert(NR);
        }
        else if( op==2 )
        {
            f>>NR;
            P.remove(NR);
        }
        else if( op==3 )
        {
            f>>NR;
            P.search(NR);
        }
        else if( op==4 )
        {
            f>>NR;
            P.predecesorr(NR);
        }
        else if( op==5 )
        {
            f>>NR;
            P.succesorr(NR);
        }
        else if( op==6 )
        {
            f>>data1>>data2;
            P.interval(data1,data2,P.get());
            g<<endl;
        }
    }
    return 0;
}
