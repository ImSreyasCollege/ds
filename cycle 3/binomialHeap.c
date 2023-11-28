#include<stdio.h>
#include<malloc.h>

struct node 
{
    int n;
    int degree;
    struct node* parent;
    struct node* child;
    struct node* sibling;
};

struct node* make_bin_heap();
int bin_link(struct node*, struct node*);
struct node* create_node(int);
struct node* bin_heap_union(struct node*, struct node*);
struct node* bin_heap_insert(struct node*, struct node*);
struct node* bin_heap_merge(struct node*, struct node*);
struct node* bin_heap_extract_min(struct node*);
int revert_list(struct node*);
int display(struct node*);
struct node* find_node(struct node*, int);
int bin_heap_decrease_key(struct node*, int, int);
int bin_heap_delete(struct node*, int);
int count = 1;

struct node* make_bin_heap() 
{
    struct node* np;
    np = NULL;
    return np;
}

struct node * H = NULL;
struct node *Hr = NULL;
 
int bin_link(struct node* y, struct node* z) 
{
    y->parent = z;
    y->sibling = z->child;
    z->child = y;
    z->degree = z->degree + 1;
}

struct node* create_node(int k) 
{
    struct node* p;
    p = (struct node*) malloc(sizeof(struct node));
    p->n = k;
    return p;
}

struct node* bin_heap_union(struct node* H1, struct node* H2) 
{
    struct node* prev_x;
    struct node* next_x;
    struct node* x;
    struct node* H = make_bin_heap();
    H = bin_heap_merge(H1, H2);
    if (H == NULL)
        return H;
    prev_x = NULL;
    x = H;
    next_x = x->sibling;
    while (next_x != NULL) 
    {
        if ((x->degree != next_x->degree) || ((next_x->sibling != NULL)
                && (next_x->sibling)->degree == x->degree)) 
                {
            prev_x = x;
            x = next_x;
        	} 
        else 
        {
            if (x->n <= next_x->n) 
            {
                x->sibling = next_x->sibling;
                bin_link(next_x, x);
            } 
            else 
            {
                if (prev_x == NULL)
                    H = next_x;
                else
                    prev_x->sibling = next_x;
                bin_link(x, next_x);
                x = next_x;
            }
        }
        next_x = x->sibling;
    }
    return H;
}
 
struct node* bin_heap_insert(struct node* H, struct node* x) 
{
    struct node* H1 = make_bin_heap();
    x->parent = NULL;
    x->child = NULL;
    x->sibling = NULL;
    x->degree = 0;
    H1 = x;
    H = bin_heap_union(H, H1);
    return H;
}

struct node* bin_heap_merge(struct node* H1, struct node* H2) 
{
    struct node* H = make_bin_heap();
    struct node* y;
    struct node* z;
    struct node* a;
    struct node* b;
    y = H1;
    z = H2;
    if (y != NULL) 
    {
        if (z != NULL && y->degree <= z->degree)
            H = y;
        else if (z != NULL && y->degree > z->degree)
            /* need some modifications here;the first and the else conditions
            can be merged together!!!! */
            H = z;
        else
            H = y;
    } else
        H = z;
    while (y != NULL && z != NULL) 
    {
        if (y->degree < z->degree) 
        {
            y = y->sibling;
        } 
        else if (y->degree == z->degree) 
        {
            a = y->sibling;
            y->sibling = z;
            y = a;
        } else 
        {
            b = z->sibling;
            z->sibling = y;
            z = b;
        }
    }
    return H;
}

int display(struct node* H) 
{
    struct node* p;
    if (H == NULL) 
    {
        printf("\nheap empty");
        return 0;
    }
    printf("\nthe root nodes are:-\n");
    p = H;
    while (p != NULL) 
    {
        printf("%d", p->n);
        if (p->sibling != NULL)
            printf("-->");
        p = p->sibling;
    }
    printf("\n");
}

struct node* bin_heap_extract_min(struct node* H1) 
{
    int min;
    struct node* t = NULL;
    struct node* x = H1;
    struct node *Hr;
    struct node* p;
    Hr = NULL;
    if (x == NULL) 
    {
        printf("\nnothing to extract");
        return x;
    }
    p = x;
    while (p->sibling != NULL) 
    {
        if ((p->sibling)->n < min) 
        {
            min = (p->sibling)->n;
            t = p;
            x = p->sibling;
        }
        p = p->sibling;
    }
    if (t == NULL && x->sibling == NULL)
        H1 = NULL;
    else if (t == NULL)
        H1 = x->sibling;
    else if (t->sibling == NULL)
        t = NULL;
    else
        t->sibling = x->sibling;
    if (x->child != NULL) 
    {
        revert_list(x->child);
        (x->child)->sibling = NULL;
    }
    H = bin_heap_union(H1, Hr);
    return x;
}
 
int revert_list(struct node* y) 
{
    if (y->sibling != NULL) 
    {
        revert_list(y->sibling);
        (y->sibling)->sibling = y;
    } else 
    {
        Hr = y;
    }
}

struct node* find_node(struct node* H, int k) 
{
    struct node* x = H;
    struct node* p = NULL;
        if (x->n == k) 
        {
        p = x;
        return p;
    }
    if (x->child != NULL && p == NULL) 
    {
        p = find_node(x->child, k);
    }
 
    if (x->sibling != NULL && p == NULL) 
    {
        p = find_node(x->sibling, k);
    }
    return p;
}
 
int bin_heap_decrease_key(struct node* H, int i, int k) 
{
    int temp;
    struct node* p;
    struct node* y;
    struct node* z;
    p = find_node(H, i);
    if (p == NULL) 
    {
        printf("\ninvalid choice of key to be reduced");
        return 0;
    }
    if (k > p->n) 
    {
        printf("\nsorry!the new key is greater than current one");
        return 0;
    }
    p->n = k;
    y = p;
    z = p->parent;
    while (z != NULL && y->n < z->n) 
    {
        temp = y->n;
        y->n = z->n;
        z->n = temp;
        y = z;
        z = z->parent;
    }
    printf("\nkey reduced successfully!");
}

int bin_heap_delete(struct node* H, int k) 
{
    struct node* np;
    if (H == NULL) 
    {
        printf("\nheap empty");
        return 0;
    }
 
    bin_heap_decrease_key(H, k, -1000);
    np = bin_heap_extract_min(H);
    if (np != NULL)
        printf("\nnode deleted successfully");
}
 
int main() 
{
    int i, n, m, l;
    struct node* p;
    struct node* np;
    char ch;
    printf("\nenter the number of elements:");
    scanf("%d", &n);
    printf("\nenter the elements:\n");
    for (i = 1; i <= n; i++) 
    {
        scanf("%d", &m);
        np = create_node(m);
        H = bin_heap_insert(H, np);
    }
    display(H);
    do 
    {
        printf("\nmenu:-\n");
        printf(
                "\n1)insert an element\n2)extract the minimum key node\n3)decrease a node key\n4)delete a node\n5)quit\n");
        scanf("%d", &l);
        switch (l) 
        {
        case 1:
            do 
            {
                printf("\nenter the element to be inserted:");
                scanf("%d", &m);
                p = create_node(m);
                H = bin_heap_insert(H, p);
                printf("\nnow the heap is:\n");
                display(H);
                printf("\ninsert more(y/y)= \n");
                fflush(stdin);
                scanf("%c", &ch);
            } while (ch == 'y' || ch == 'y');
            break;
        case 2:
            do 
            {
                printf("\nextracting the minimum key node");
                p = bin_heap_extract_min(H);
                if (p != NULL)
                    printf("\nthe extracted node is %d", p->n);
                printf("\nnow the heap is:\n");
                display(H);
                printf("\nextract more(y/y)\n");
                fflush(stdin);
                scanf("%c", &ch);
            } while (ch == 'y' || ch == 'y');
            break;
        case 3:
            do 
            {
                printf("\nenter the key of the node to be decreased:");
                scanf("%d", &m);
                printf("\nenter the new key : ");
                scanf("%d", &l);
                bin_heap_decrease_key(H, m, l);
                printf("\nnow the heap is:\n");
                display(H);
                printf("\ndecrease more(y/y)\n");
                fflush(stdin);
                scanf("%c", &ch);
            } while (ch == 'y' || ch == 'y');
            break;
        case 4:
            do 
            {
                printf("\nenter the key to be deleted: ");
                scanf("%d", &m);
                bin_heap_delete(H, m);
                printf("\ndelete more(y/y)\n");
                fflush(stdin);
                scanf("%c", &ch);
            } while (ch == 'y' || ch == 'y');
            break;
        case 5:
            printf("\nexiting....\n");
            break;
        default:
            printf("\ninvalid entry...try again....\n");
	}
    } while (l != 5);
}