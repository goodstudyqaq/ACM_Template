const int maxv = 55;
const int inf = 0x3f3f3f3f;
struct Edge
{
    int from, to, cap, flow;
    Edge(int u, int v, int c, int f) :from(u), to(v), cap(c), flow(f) {}
    Edge() {}
};
struct Dinic
{
    int n, m, s, t;
    vector<Edge>edges;
    vector<int>G[maxv + 50];
    bool vis[maxv + 50];
    int d[maxv + 50];
    int cur[maxv + 50];

    void AddEdge(int from, int to, int cap)
    {
        edges.push_back(Edge(from, to, cap, 0));
        edges.push_back(Edge(to, from, 0, 0));
        m = edges.size();
        G[from].push_back(m - 2);
        G[to].push_back(m - 1);
    }

    void init(int n)
    {
        for (int i = 0;i <= n;i++)G[i].clear();
        edges.clear();
    }

    bool BFS()
    {
        memset(vis, 0, sizeof(vis));
        queue<int>Q;
        Q.push(s);
        d[s] = 0;
        vis[s] = 1;
        while (!Q.empty())
        {
            int x = Q.front();Q.pop();
            for (int i = 0;i < G[x].size();i++)
            {
                Edge&e = edges[G[x][i]];
                if (!vis[e.to] && e.cap > e.flow)
                {
                    vis[e.to] = 1;
                    d[e.to] = d[x] + 1;
                    Q.push(e.to);
                }
            }
        }
        return vis[t];
    }

    int DFS(int x, int a)
    {
        if (x == t || a == 0)return a;
        int flow = 0, f;
        for (int &i = cur[x];i < G[x].size();i++)
        {
            Edge&e = edges[G[x][i]];
            if (d[x] + 1 == d[e.to] && (f = DFS(e.to, min(a, e.cap - e.flow)))>0)
            {
                e.flow += f;
                edges[G[x][i] ^ 1].flow -= f;
                flow += f;
                a -= f;
                if (a == 0)break;
            }
        }
        return flow;
    }
    int Maxflow(int s, int t)
    {
        //cout << edges.size() << endl;
        this->s = s;this->t = t;
        int flow = 0;
        while (BFS())
        {
            memset(cur, 0, sizeof(cur));
            flow += DFS(s, inf);
        }
        return flow;
    }

}ans;
