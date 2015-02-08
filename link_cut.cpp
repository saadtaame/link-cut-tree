#include <cstdio>
#include <cassert>

struct Node
{   int sz, label; /* size, label */
    Node *p, *l, *r; /* parent, left, right pointers */
    Node() { p = l = r = 0; }
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
    update(x->r);
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
    update(x->l);
}

bool splay_root(Node *x)
{   return (x->p == 0) || (x != x->p->l && x != x->p->r);
}

void splay(Node *x)
{   Node *y, *z;
    while(splay_root(x) == false)
    {   y = x->p;
        if(splay_root(y))
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

void access(Node *x)
{   Node *r = 0;
    for(Node *y = x; y; y = y->p)
    {   splay(y);
        y->r = r;
        update(y);
        r = y;
    }
    splay(x);
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
    assert(x->r == 0);
}

void link(Node *x, Node *y)
{   access(x);
    access(y);
    x->l = y;
    y->p = x;
    update(x);
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
};

int main(void)
{   return 0;
}
