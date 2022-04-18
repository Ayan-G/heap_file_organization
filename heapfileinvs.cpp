#include <bits/stdc++.h>

using namespace std;

class record{
public:
    int ssize;
    int prim_key;
    record(int ,int );
    virtual ~record();
};

record::record(int s,int p)
{
    ssize=s;
    prim_key=p;
}

record::~record()
{

}

class page{
public:
    page(int);
    int countt;
    page *nextpage;
    page *prevpage;
    int freespace;
    vector<record>arr;
    bool insert_rc(record);
    virtual ~page();

};
page::page(int freespc1)
{
    freespace=freespc1-16;
    countt=0;
    nextpage=nullptr;
    prevpage=nullptr;
}

bool page::insert_rc(record rr)
{
    if((4+ rr.ssize)<=freespace)
    {
        arr.push_back(rr);
        countt++;
        freespace-=(4+rr.ssize);
        return true;
    }
    else return false;
}
page::~page()
{

}

class heapfile{
public:
    int freespace;
    page *head;
    page *tail;
    int num_pages;
    heapfile(int );
    virtual ~heapfile();
    bool insert_rec(int ,int);
    void search_rec(int );
    void display_status();
};

heapfile::heapfile(int freespc)
{
    freespace=freespc;
    head=nullptr;
    tail=nullptr;
    num_pages=0;
}

bool heapfile::insert_rec(int sz,int pk)
{
    record rr(sz,pk);
    if(head==nullptr)
    {
        head=new page(freespace);
        tail=head;
        num_pages=1;
        return(tail->insert_rc(rr));
    }
    page* curr=head;
    while(curr!=nullptr)
    {
        if(curr->insert_rc(rr))
            return true;
        curr=curr->nextpage;
    }
    page *pg=new page(freespace);
    tail->nextpage=pg;
    pg->prevpage=tail;
    tail=pg;
    num_pages++;
    return(tail->insert_rc(rr));

    //basically if it returns false then page size is not big enough to accomodate record that big
}

void heapfile::search_rec(int key)
{
    int pg=0;
    page* curr=head;
    while(curr!=nullptr)
    {
        //we have got the page now we will search the record in the page
        for(int i=0;i<curr->countt;i++)
        {
            if(curr->arr[i].prim_key==key)
            {
                cout<<pg<<" "<<i<<endl;
                return ;
            }

        }
        pg++;
        curr=curr->nextpage;
    }
    cout<<"-1 -1"<<endl;
    return ;
}

void heapfile::display_status()
{
    cout<<num_pages<<" ";
    page* curr=head;
    while(curr!=nullptr)
    {
        cout<<curr->countt<<" ";
        curr=curr->nextpage;
    }
    cout<<endl;
}
heapfile::~heapfile()
{

}

int main()
{
    bool flag=true;
    int xx,yy,zz;
    cin>>xx;
    heapfile h(xx);
    while(flag)
    {
        cin>>xx;
        switch (xx)
        {
        case 1:
            cin>>yy>>zz;
            h.insert_rec(yy,zz);
            break;
        case 2:
            h.display_status();
            break;
        case 3:
            cin>>zz;
            h.search_rec(zz);
            break;
        case 4:
            flag=false;
            break;
        default:
            cout<<"Enter the correct choice"<<endl;
            break;

        }
    }
    return 0;
}
