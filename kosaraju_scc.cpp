#include<bits/stdc++.h>
using namespace std;
const int N = 1e5 + 5;
// solution of planets and kingdoms
vector<int>a1[N],a2[N];// one is normal graph and other is transposed graph
void dfs(int u,vector<int>&vis,stack<int>&st)
{
    vis[u] = 1;
    for(auto & x: a1[u])
    {
        if(!vis[x])dfs(x, vis, st);
    }
    st.push(u);
}
void dfs1(int u,int cnt, vector<int>&sol)
{
    sol[u] = cnt;
    for(auto &x: a2[u])
    {
        if(!sol[x])dfs1(x,cnt,sol);
    }
}
int main()
{
    int n;
    cin>>n;
    int m;
    cin>>m;
    for(int i = 0;i < m;i++){
        int a, b;
        cin>>a>>b;
        a1[a].push_back(b);
        a2[b].push_back(a);
    }    
    stack<int>st;
    vector<int>vis(n + 1);
    for(int i = 1;i<= n;i++)if(!vis[i])dfs(i, vis,st);
    int cnt = 1;
    for(int i = 1;i<= n;i++)vis[i] = 0;
    while(st.size())
    {
        int tp = st.top();
        if(vis[tp] == 0){
            dfs1(tp,cnt,vis);
            cnt++;
        }
        st.pop();
    }
    cout<<cnt-1<<'\n';
    for(int i = 1;i<= n;i++)cout<<vis[i]<<' ';
    cout<<'\n';
}
