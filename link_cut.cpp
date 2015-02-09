#include <cstdio>

using namespace std;

struct Node
{   int sz, label; /* size, label */
    Node *p, *pp, *l, *r; /* parent, path-parent, left, right pointers */
    Node() { p = pp = l = r = 0; }
};

void update(Node *x)
{   x->sz = 1;
    if(x->l) x->sz += x->l->sz;
    if(x->r) x->sz += x->r->sz;
}

void rotr(Node *x)
{   Node *y, *z;
    y = x->p, z = y->p;
    if((y->l = x->r)) y->l->p = y;
    x->r = y, y->p = x;
    if((x->p = z))
    {   if(y == z->l) z->l = x;
        else z->r = x;
    }
    x->pp = y->pp;
    y->pp = 0;
    update(y);
}

void rotl(Node *x)
{   Node *y, *z;
    y = x->p, z = y->p;
    if((y->r = x->l)) y->r->p = y;
    x->l = y, y->p = x;
    if((x->p = z))
    {   if(y == z->l) z->l = x;
        else z->r = x;
    }
    x->pp = y->pp;
    y->pp = 0;
    update(y);
}

void splay(Node *x)
{   Node *y, *z;
    while(x->p)
    {   y = x->p;
        if(y->p == 0)
        {   if(x == y->l) rotr(x);
            else rotl(x);
        }
        else
        {   z = y->p;
            if(y == z->l)
            {   if(x == y->l) rotr(y), rotr(x);
                else rotl(x), rotr(x);
            }
            else
            {   if(x == y->r) rotl(y), rotl(x);
                else rotr(x), rotl(x);
            }
        }
    }
    update(x);
}

Node *access(Node *x)
{   splay(x);
    if(x->r)
    {   x->r->pp = x;
        x->r->p = 0;
        x->r = 0;
        update(x);
    }

    Node *last = x;
    while(x->pp)
    {   Node *y = x->pp;
        last = y;
        splay(y);
        if(y->r)
        {   y->r->pp = y;
            y->r->p = 0;
        }
        y->r = x;
        x->p = y;
        x->pp = 0;
        update(y);
        splay(x);
    }
    return last;
}

Node *root(Node *x)
{   access(x);
    while(x->l) x = x->l;
    splay(x);
    return x;
}

void cut(Node *x)
{   access(x);
    x->l->p = 0;
    x->l = 0;
    update(x);
}

void link(Node *x, Node *y)
{   access(x);
    access(y);
    x->l = y;
    y->p = x;
    update(x);
}

Node *lca(Node *x, Node *y)
{   access(x);
    return access(y);
}

int depth(Node *x)
{   access(x);
    return x->sz - 1;
}

class LinkCut
{   Node *x;

    public:
    LinkCut(int n)
    {   x = new Node[n];
        for(int i = 0; i < n; i++)
        {   x[i].label = i;
            update(&x[i]);
        }
    }

    virtual ~LinkCut()
    {   delete[] x;
    }

    void link(int u, int v)
    {   ::link(&x[u], &x[v]);
    }

    void cut(int u)
    {   ::cut(&x[u]);
    }

    int root(int u)
    {   return ::root(&x[u])->label;
    }

    int depth(int u)
    {   return ::depth(&x[u]);
    }

    int lca(int u, int v)
    {   return ::lca(&x[u], &x[v])->label;
    }
};

int main(void)
{   return 0;
}
