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

class RBT
{
    Node *root;
    Node *q;
public :
    RBT()
    {
        q=NULL;
        root=NULL;
    }
    void insert ( int & );
    void insertfix ( Node * );
    void leftrotate ( Node * );
    void rightrotate ( Node * );
    void remove ( int & );
    void interval ( int &, int &,Node *);
    void succesorr ( int & );
    void predecesorr ( int & );
    Node* successor ( Node *);
    void delfix ( Node * );
    void disp ();
    void display ( Node *);
    void search ( int & );
    Node* get ();
};
Node * RBT::get ()
{
    return root;
}
void RBT::insert ( int &z )
{
    int i=0;
    Node *nod1,*nod2;
    Node *nod3=new Node;
    nod3->data=z;
    nod3->left=NULL;
    nod3->right=NULL;
    nod3->color='r';
    nod1=root;
    nod2=NULL;
    if ( root==NULL )
    {
        root=nod3;
        nod3->parent=NULL;
    }
    else
    {
        while ( nod1!=NULL )
        {
            nod2=nod1;
            if ( nod1->data<nod3->data )
                nod1=nod1->right;
            else
                nod1=nod1->left;
        }
        nod3->parent=nod2;
        if ( nod2->data<nod3->data )
            nod2->right=nod3;
        else
            nod2->left=nod3;
    }
    insertfix ( nod3 );
}
void RBT::insertfix ( Node *t )
{
    Node *u;
    if ( root==t )
    {
        t->color='b';
        return;
    }
    while ( t->parent!=NULL and t->parent->color=='r' )
    {
        Node *g=t->parent->parent;
        if ( g->left==t->parent )
        {
            if ( g->right!=NULL )
            {
                u=g->right;
                if ( u->color=='r' )
                {
                    t->parent->color='b';
                    u->color='b';
                    g->color='r';
                    t=g;
                }
            }
            else
            {
                if ( t->parent->right==t )
                {
                    t=t->parent;
                    leftrotate ( t );
                }
                t->parent->color='b';
                g->color='r';
                rightrotate ( g );
            }
        }
        else
        {
            if ( g->left!=NULL )
            {
                u=g->left;
                if ( u->color=='r' )
                {
                    t->parent->color='b';
                    u->color='b';
                    g->color='r';
                    t=g;
                }
            }
            else
            {
                if ( t->parent->left==t )
                {
                    t=t->parent;
                    rightrotate ( t );
                }
                t->parent->color='b';
                g->color='r';
                leftrotate ( g );
            }
        }
        root->color='b';
    }
}

void RBT::remove ( int &x )
{

    Node *p;
    nod=root;
    Node *y=NULL;
    Node *q=NULL;
    int ok=0;
    while ( nod!=NULL and  ok==0 )
    {
        if ( nod->data==x )
            ok=1;
        if ( ok==0 )
        {
            if ( nod->data<x )
                nod=nod->right;
            else
                nod=nod->left;
        }
    }
    if ( ok!=0 )
    {
        if ( nod->left==NULL or nod->right==NULL )
            y=nod;
        else
            y=successor(nod);
        if ( y->left!=NULL )
            q=y->left;
        else
        {
            if ( y->right!=NULL )
                q=y->right;
            else
                q=NULL;
        }
        if ( q!=NULL )
            q->parent=y->parent;
        if ( y->parent==NULL )
            root=q;
        else
        {
            if ( y==y->parent->left )
                y->parent->left=q;
            else
                y->parent->right=q;
        }
        if(y!=nod)
        {
            nod->color=y->color;
            nod->data=y->data;
        }
        if(y->color=='b')
            delfix ( q );
    }
}

void RBT::delfix ( Node *nod )
{
    Node *s;
    while ( nod!=root and nod->color=='b' )
    {
        if ( nod->parent->left==nod )
        {
            s=nod->parent->right;
            if ( s->color=='r' )
            {
                s->color='b';
                nod->parent->color='r';
                leftrotate ( nod->parent );
                s=nod->parent->right;
            }
            if ( s->right->color=='b' and  s->left->color=='b' )
            {
                s->color='r';
                nod=nod->parent;
            }
            else
            {
                if ( s->right->color=='b' )
                {
                    s->left->color=='b';
                    s->color='r';
                    rightrotate ( s );
                    s=nod->parent->right;
                }
                s->color=nod->parent->color;
                nod->parent->color='b';
                s->right->color='b';
                leftrotate ( nod->parent );
                nod=root;
            }
        }
        else
        {
            s=nod->parent->left;
            if( s->color=='r' )
            {
                s->color='b';
                nod->parent->color='r';
                rightrotate ( nod->parent );
                s=nod->parent->left;
            }
            if ( s->left->color=='b' and s->right->color=='b' )
            {
                s->color='r';
                nod=nod->parent;
            }
            else
            {
                if ( s->left->color=='b' )
                {
                    s->right->color='b';
                    s->color='r';
                    leftrotate(s);
                    s=nod->parent->left;
                }
                s->color=nod->parent->color;
                nod->parent->color='b';
                s->left->color='b';
                rightrotate ( nod->parent );
                nod=root;
            }
        }
        nod->color='b';
        root->color='b';
    }
}

void RBT::leftrotate ( Node *nod )
{
    if ( nod->right==NULL )
        return ;
    else
    {
        Node *y=nod->right;
        if ( y->left!=NULL )
        {
            nod->right=y->left;
            y->left->parent=nod;
        }
        else
            nod->right=NULL;
        if ( nod->parent!=NULL )
            y->parent=nod->parent;
        if ( nod->parent==NULL )
            root=y;
        else
        {
            if ( nod==nod->parent->left )
                nod->parent->left=y;
            else
                nod->parent->right=y;
        }
        y->left=nod;
        nod->parent=y;
    }
}
void RBT::rightrotate ( Node *nod )
{
    if ( nod->left==NULL )
        return ;
    else
    {
        Node *y=nod->left;
        if ( y->right!=NULL )
        {
            nod->left=y->right;
            y->right->parent=nod;
        }
        else
            nod->left=NULL;
        if(nod->parent!=NULL)
            y->parent=nod->parent;
        if ( nod->parent==NULL )
            root=y;
        else
        {
            if ( nod==nod->parent->left )
                nod->parent->left=y;
            else
                nod->parent->right=y;
        }
        y->right=nod;
        nod->parent=y;
    }
}

Node* RBT::successor ( Node *nod ) ///returneaza succesorul
{
    Node *y=NULL;
    if ( nod->left!=NULL )
    {
        y=nod->left;
        while ( y->right!=NULL )
            y=y->right;
    }
    else
    {
        y=nod->right;
        while ( y->left!=NULL )
            y=y->left;
    }
    return y;
}

void  RBT::succesorr ( int &data ) ///afisez succesorul
{
    int cnt=0;
    Node *x=root;
    while ( x!= NULL )
        if ( x->data>=data )
        {
            cnt=x->data;
            if ( cnt==data )
                break;
            x=x->left;
        }
        else
            x=x->right;
    g<<cnt<<endl;
}

void RBT::interval ( int &st, int &dr, Node *nod )
{
    if ( st<=nod->data )
        if( nod->left!=NULL )
            interval(st,dr,nod->left);
    if ( st<=nod->data and dr>=nod->data )
        g<<nod->data<<" ";
    if ( dr>=nod->data )
        if ( nod->right!=NULL )
            interval(st,dr,nod->right);
}

void RBT::nodredecesorr ( int &data ) ///afisez nodredecesorul
{
    int cnt=0;
    Node *x=root;
    while ( x!= NULL )
        if ( x->data<=data )
        {
            cnt=x->data;
            if ( cnt==data )
                break;
            x=x->right;
        }
        else
            x=x->left;
    g<<cnt<<endl;
}
void RBT::search ( int &x )
{
    Node *nod=root;
    int ok=0;
    while ( nod!=NULL&& ok==0 )
    {
        if ( nod->data==x )
            ok=1;
        if ( ok==0 )
        {
            if ( nod->data<x )
                nod=nod->right;
            else
                nod=nod->left;
        }
    }
   if ( ok==0 ) g<<"0";
   else g<<"1";
   g<<endl;
}
int n,op,NR,data1,data2;
RBT P;
int main()
{
    f>>n;
    for ( int i=1; i<=n; i++ )
    {
        f>>op;
        if ( op==1 )
        {
            f>>NR;
            P.insert(NR);
        }
        else if ( op==2 )
        {
            f>>NR;
            P.remove(NR);
        }
        else if ( op==3 )
        {
            f>>NR;
            P.search(NR);
        }
        else if ( op==4 )
        {
            f>>NR;
            P.predecesorr(NR);
        }
        else if ( op==5 )
        {
            f>>NR;
            P.succesorr(NR);
        }
        else if ( op==6 )
        {
            f>>data1>>data2;
            P.interval(data1,data2,P.get());
            g<<endl;
        }
    }
    return 0;
}
