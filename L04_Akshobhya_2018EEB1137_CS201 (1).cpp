#include <iostream>
#include<stdlib.h>
#include<time.h>
#include<bits/stdc++.h>
#include <sys/time.h>
using namespace std;
typedef long long int ll;
#define inf 1000000007
#define nil 8134845466
#define endl "\n"

class node {
public:
    ll data;
    node* next=NULL;
};

class Queue
{

      public:
          node *head,*End;
            ll top;
             Queue()
               {
                    top=-1;
               }

             void enque(ll x)
              {
                  if (top < 0 )
                  {
                     head =new node;
                     head->next=NULL;
                     head->data=x;
                     End = head;
                     top ++;
                   }
             else
                  {
                        node* temp = new node;
                        temp->data = x;
                        temp->next = NULL;
                        End->next = temp;
                        End = End->next;
                        top++;
                   }
                }
            ll Size()
            {
                return top + 1;
            }
             void display()
               {
                  node *temp;
                  temp=head;
                  if (top < 0)
                    {
                        cout <<" Queue under flow"<<endl;
                        return;
                     }
                  while(temp != NULL)
                     {
                        cout <<temp->data<< " ";
                        temp=temp->next;
                     }
                     cout<<endl;
               }
              ll Deque()
                {
                   node *temp;
                   temp=head;
                   ll data;
                   if( top < 0 )
                    {
                       cout <<"Queue under flow"<<endl;
                       return -1;
                    }
                    top--;
                    data = head->data;
                   head = head->next;
                   free(temp);
                   return data;
                 }
};

class List
{

    public:
        ll top;
    node*head;
    node*it;
        List()
        {
            top = 0;
        }

        void add(ll x)
        {
            if (top == 0 )
                  {
                     head =new node;
                     head->next=NULL;
                     head->data=x;
                     it = head;
                     top ++;
                   }
             else
                  {
                      node*temp = head;
                      if(temp->next==NULL)
                      {
                          if(head->data<x)
                          {
                              node*t = new node;
                              t->data = x;
                              t->next = NULL;
                              head->next = t;
                              top++;
                          }
                          else if(x<head->data)
                        {
                            node*t = new node;
                            t->data = x;
                            t->next = head;
                            head = t;
                            it  = head;
                            top++;
                        }
                      }

                      else
                    {
                        node*prev = temp;
                        while(temp->next!=NULL&&temp->data<x)
                        {
                            prev = temp;
                            temp = temp->next;
                        }
                        if(temp->data>x)
                        {
                            node*f = new node;
                            f->data = x;
                            temp = prev->next;
                            prev->next = f;
                            f->next = temp;
                            top++;
                        }
                        else if(temp->next==NULL&&temp->data<x)
                        {
                            node*f = new node;
                            f->data = x;
                            f->next = NULL;
                            temp->next = f;
                            top++;
                        }
                    }
                  }
        }

        ll Deque()
                {
                   node *temp;
                   temp=head;
                   ll data;
                   if( top < 0 )
                    {
                       cout <<"Queue under flow"<<endl;
                       return -1;
                    }
                    top--;
                    data = head->data;
                   head = head->next;
                   free(temp);
                   return data;
                 }
        ll Size()
        {
            return top;
        }
        void display()
        {

            if (top == 0)
            {
                cout <<"List under flow"<<endl;
                return;
            }
            node *temp;
            temp = head;
            while(temp != NULL)
            {
                cout <<temp->data<< " ";
                temp=temp->next;
            }
            cout<<endl;
        }
};

class vertex
{
    public:
        ll data;
        List lis;
        List in;
        ll color;
        ll distance;
        ll discoveryTime;
        ll finishTime ;
        ll parent ;
};

class graph
{
    public:
        ll vertices;
        vertex* adj;
        graph(ll v)
        {
            vertices = v;
            adj = new vertex[v];
            for(ll i =0;i<v;i++)
            {
                adj[i].data = i + 1;
            }
        }
        void addEdge(ll a,ll b)
        {
            adj[a-1].lis.add(b);
            adj[b-1].in.add(a);
        }
      void display()
        {
            for(ll j=0;j<vertices;j++)
            {
                cout<<j+1<< " : ";
                adj[j].lis.display();
            }
            cout<<endl;
        }
        void indisplay()
        {
            for(ll j=0;j<vertices;j++)
            {
                cout<<j+1<< " : ";
                adj[j].in.display();
            }
            cout<<endl;
        }
};

void BFS(graph g,ll s,bool*modified)
{
    g.adj[s-1].color = 0;
    Queue q;
    q.enque(s);
    while(q.Size()!=0)
    {
        ll u = q.Deque();
        node*temp = g.adj[u-1].lis.head;
        for(ll i=0;i<g.adj[u-1].lis.Size();i++)
        {
            if(g.adj[temp->data - 1].color==-1)
            {
                g.adj[temp->data-1].color = 0;
                q.enque(g.adj[temp->data-1].data);
            }
            temp = temp->next;
        }
        g.adj[u-1].color = 1;
        modified[u-1] = true;
    }
}

void DFS_visit(graph g,ll s,ll**a,ll*pred,ll*k,ll*order,ll*time)
{
    node*head = g.adj[s-1].lis.head;
    g.adj[s-1].color  = 1;
    g.adj[s-1].discoveryTime = *time;
    *time = *time + 1;
    node*temp = head;
    bool flag = false;
    g.adj[s-1].color = 1;
    while(head!=NULL&&g.adj[s-1].lis.Size()!=0)
    {
        if(a[s-1][head->data-1] == 0 && pred[head->data-1] == nil)
        {
            pred[head->data-1] = s;
            if(g.adj[head->data-1].color==1)
                flag = true;
            DFS_visit(g,head->data,a,pred,k, order,time);
        }
        head = head->next;
    }

    order[*k] = s;
    *k = *k + 1;
    g.adj[s-1].finishTime = *time;
    *time = *time + 1;
    return;
}

void DFS_(graph g,ll s,ll**a,ll**old,ll*distance,ll*pred)
{
    node*head = g.adj[s-1].lis.head;
    g.adj[s-1].color  = 1;
    node*temp = head;
    g.adj[s-1].color = 1;
    while(head!=NULL&&g.adj[s-1].lis.Size()!=0)
    {
        if(old[s-1][head->data-1] == 0)
        {
            if(pred[head->data-1] == s)
                {
                    distance[head->data-1] = distance[s-1] + a[s-1][head->data-1];
                }
                if(g.adj[head->data-1].color == 0)
            DFS_(g,head->data,a,old,distance,pred);
        }
        head = head->next;
    }
    return;
}

void visitGraph(graph g,ll r,ll**a,ll**old,ll*distance,ll*pred)
{
    for(ll i=0;i<g.vertices;i++)
        g.adj[i].color = 0;
    DFS_(g,r,a,old,distance,pred);

}


void visitGraphForward(graph g,ll r,ll**a,ll*pred,ll*order)
{
    ll time = 0;
    for(ll i=0;i<g.vertices;i++)
    {
        pred[i] = nil;
    }
    pred[r-1] = r;
    ll k =0;
    for(ll i=0;i<g.vertices;i++)order[i] = nil;
    for(ll i=0;i<g.vertices;i++)
        g.adj[i].color = 0;
    DFS_visit(g,r,a,pred,&k,order,&time);
    for(ll i=0;i<g.vertices;i++)
    {
        if(pred[i]==nil)
        {
            DFS_visit(g,i+1,a,pred,&k,order,&time);
        }
    }
    ll maxIndex;
    ll maxVal = -inf;
    for(ll i =0;i<g.vertices;i++)
    {
        if(maxVal<g.adj[i].finishTime)
        {
            maxVal = g.adj[i].finishTime;
            maxIndex = i+1;
        }
    }

    order[g.vertices-1] = maxIndex;
}

void reverseDFS_visit(graph g, ll s,ll*succ,ll*h,ll**a,ll*S,ll*order)
{
    node*ptr = g.adj[s-1].in.head;
    while(ptr!=NULL&&g.adj[s-1].in.Size()!=0)
    {
        if(succ[ptr->data-1]==nil&&a[ptr->data-1][s-1]==0)
        {
            succ[ptr->data-1] = s;
            reverseDFS_visit(g,ptr->data,succ,h,a,S,order);
        }
        ptr = ptr->next;
    }
    S[*h] = s;
    *h  = *h + 1;

}

void visitGraphBackward(graph g, ll*succ,ll*order,ll**a,ll*h,ll*S)
{

    *h =0;
    for(ll i = 0;i<g.vertices;i++)
    {
        succ[i] = nil;
    }

    succ[order[g.vertices-1]-1] = order[g.vertices-1];
    for(ll i= 0;i<g.vertices;i++)S[i] = nil;
    reverseDFS_visit(g,order[g.vertices-1],succ,h,a,S,order);
}

void updateCost(graph g, ll*S,ll*h,ll*alpha,bool*flag,ll**a)
{
    ll x,y;
    for(ll u = 0;u<*h;u++)
    {
        node*ptr = g.adj[S[u]-1].in.head;
        while(ptr!=NULL&&g.adj[S[u]-1].in.Size()!=0)
        {
            if(!flag[ptr->data-1])
                {
                    x = a[ptr->data-1][S[u]-1];
                    a[ptr->data-1][S[u]-1] = a[ptr->data-1][S[u]-1] - *alpha;
                    y = a[ptr->data-1][S[u]-1];
                }
            ptr = ptr->next;
        }
    }
}

void findArc(graph g, ll*S, ll*h, bool*flag,ll*alpha,ll**a)
{;
    for(ll i=0;i<g.vertices;i++)flag[i] = false;
    for (ll i = 0; i < *h; i++)
    {
        if(S[i]!=nil)
        flag[S[i]-1] = true;
    }

    *alpha = inf;
    for(ll u = 0;u<*h;u++)
    {
        node*ptr = g.adj[S[u]-1].in.head;
        while(ptr!=NULL&&g.adj[S[u]-1].in.Size()!=0)
        {
            if(!flag[ptr->data-1]&&a[ptr->data-1][S[u]-1]<*alpha)
                *alpha = a[ptr->data-1][S[u]-1];

            ptr = ptr->next;
        }
    }
}

void ford(graph g, ll r,ll**oo,ll*pred,ll*distance)
{
    ll**a = new ll*[g.vertices];
    for(ll i = 0;i<g.vertices;i++)
        distance[i] = 0;
    for(ll i=0;i<g.vertices;i++)
        a[i] = new ll[g.vertices];

    for(ll i=0;i< g.vertices;i++)
        for(ll j=0;j<g.vertices;j++)
            a[i][j] = oo[i][j];

    ll alpha = inf;
    ll h =0;

    ll*order =  new ll[g.vertices];
    ll*succ = new ll[g.vertices];
    ll*S = new ll[g.vertices];
    bool* flag = new bool[g.vertices];
    for(ll i=0;i<g.vertices;i++)
    {
        pred[i] = nil;
        order[i]  = nil;
        succ[i] = nil;
        flag[i] = false;
        S[i] = nil;
    }

    visitGraphForward(g,r,a,pred,order);
    ll kk = 0;
    do
    {
       visitGraphBackward(g,succ,order,a,&h,S);
       findArc(g,S,&h,flag,&alpha,a);
       updateCost(g,S,&h,&alpha,flag,a);
       visitGraphForward(g,r,a,pred,order);
    } while (order[g.vertices-1]!=r);


    visitGraph(g,r,oo,a,distance,pred);
     kk = 0;

      for(ll i=0;i<g.vertices;i++)
      {
          if(i!=r-1)
            kk = kk + oo[pred[i]-1][i];
      }

      cout<<kk<<" ";

}

int main()
{
    ios::sync_with_stdio(false);cin.tie(NULL);
    struct timeval start, end; 
  
    // start timer. 
    gettimeofday(&start, NULL); 
    
    
    ll t;cin>>t;

    while(t--)
    {
        ll n,s,m;
        cin>>n>>s>>m;
        ll**aa = new ll*[n];
        for(ll i=0;i<n;i++)
            aa[i] = new ll[n];

        for(ll i= 0;i<n;i++)
            for(ll j=0;j<n;j++)
                aa[i][j] = inf;

        graph g(n);
        for(ll i = 0;i<g.vertices;i++)
        {
            g.adj[i].color = -1;
            g.adj[i].distance = inf;
            g.adj[i].discoveryTime = inf;
            g.adj[i].finishTime = inf;  
            g.adj[i].parent = -1;
        }

        ll u[n],v[n],w[n],how[n];
            for(ll i=0;i<n;i++)how[i]= 0;

            bool gotSource= false;

        for(ll i=0;i<m;i++)
        {
            cin>>u[i]>>v[i]>>w[i];
            if(how[u[i]-1]==0)
                how[u[i]-1] = 1;
            if(how[v[i]-1] ==0)
                how[v[i]-1] =1;

            g.addEdge(u[i],v[i]);
            aa[u[i]-1][v[i]-1] = w[i];
            if(u[i]==s)
                    gotSource = true;

        }


        if(gotSource)
        {
            ll nodes = 0;
            for(ll i =0;i<n;i++)
            {
                if(how[i] == 1)
                {
                    nodes++;
                }
            }

        bool*modified = new bool[n];
        for(ll i=0;i<n;i++)modified[i] = false;
       
        BFS(g,s,modified);


        ll count = 0;

         for(ll i=0;i<g.vertices;i++)
        {
            if(modified[i]==true)
            {
                count++;
            }
        }

        ll**weight = new ll*[count];
        for(ll i=0;i<count;i++)
        weight[i] = new ll[count];
        for(ll k=0;k<count;k++)for(ll j=0;j<count;j++)weight[k][j] = inf;

            graph G(count);
            for(ll i = 0;i<G.vertices;i++)
        {
            G.adj[i].color = -1;
            G.adj[i].distance = inf;
            G.adj[i].discoveryTime = inf;
            G.adj[i].finishTime = inf;  
            G.adj[i].parent = -1;
        }
            
        
        if(count!=n)
        {
                ll*convert = new ll[n];
            ll check  = 0;
            ll valueToBeStored = 1;

            for(ll i=0;i<g.vertices;i++)
            {
                if(modified[i])
                {
                    convert[i] = check+1;
                    check++;
                }
                else
                {
                    convert[i] = -1;
                }
            }

            for(ll i=0;i<g.vertices;i++)
            {
                if(modified[i])
                {
                    if(i==s-1)
                    {
                        s = convert[i];
                    }
                    
                    node*ptr = g.adj[i].lis.head;
                    while(ptr!=NULL)
                    {
                        G.addEdge(   convert[i], convert[ptr->data-1] );
                        weight[convert[i]-1][convert[ptr->data-1]-1] =  aa[i][ptr->data-1];
                        ptr = ptr->next;
                    }


                }
            }
        }
        else
        {
            G = g;
            for(ll i = 0;i<n;i++)
            {
                for(ll j =0;j<n;j++)
                    weight[i][j] = aa[i][j];
            }
        }
        ll*pred = new ll [G.vertices];
        ll*distance = new ll[G.vertices];
      
        

        ford(G,s,weight,pred,distance);

        pred[s-1] = 0;
        ll j = 0;
        for(ll i= 0;i<g.vertices;i++)
        {
            if(modified[i])
                {
                    cout<<distance[j]<<" ";
                    j++;
                }
            else
                cout<<-1<<" ";
        }
      cout<<"# ";
      j = 0;
        for(ll i= 0;i<g.vertices;i++)
        {
            if(modified[i])
                {
                    cout<<pred[j]<<" ";
                    j++;
                }
            else
                cout<<-1<<" ";
        }



    }
    else
        {
            cout<<0<<" ";
            for(ll i= 0;i<g.vertices;i++)
            {
                if(i==s-1)
                    cout<<0<<" ";
                else
                    cout<<-1<<" ";
            }
            cout<<"# ";
            for(ll i =0;i<g.vertices;i++)
            {
                if(i==s-1)
                    cout<<0<<" ";
                else
                    cout<<-1<<" ";
            }
        }
        cout<<endl;

    }
    
    
gettimeofday(&end, NULL); 
  
    // Calculating total time taken by the program. 
    double time_taken; 
  
    time_taken = (end.tv_sec - start.tv_sec) * 1e6; 
    time_taken = (time_taken + (end.tv_usec -  
                              start.tv_usec)) * 1e-6; 
  
    cout << fixed 
         << time_taken << setprecision(6); ///printing time 
    cout <<endl; 
}
