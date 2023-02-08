#include "draw.h"
using namespace std;

const int maxn = 1000;

class Graph
{
protected:
    vector<Vertex> vList;
    vector<pair<int, pair<int, string>>> adj[maxn]; 
    int numberofVertex;
public:
    Graph()
    {
        numberofVertex = 0;
        initwindow(900, 700, "Visualization"); 
        setbkcolor(WHITE);                     
        cleardevice();
        setcolor(BLACK);
        drawxyAxis();   
    }
    ~Graph() = default;
    void addVertex(int x, int y, string placeName)
    { 
        
        numberofVertex++;
        Vertex temp = {x, y, placeName};
        vList.push_back(temp);

        drawVertex(x, y, stringToChars(placeName));
    }
    void addOneWayEdge(string name1, string name2, string streetName, string cost)
    {
        int intCost = stoi(cost);
        int index1 = getVertex(name1);
        int index2 = getVertex(name2);  
        adj[index1].push_back({index2, {intCost, streetName}});
        drawOneWayEdge(vList[index1], vList[index2], stringToChars(streetName), stringToChars(cost));
    
    }
    void addTwoWayEdge(string name1, string name2, string streetName, string cost)
    {
        int intCost = stoi(cost);
        int index1 = getVertex(name1);
        int index2 = getVertex(name2);
        adj[index1].push_back({index2, {intCost, streetName}});
        adj[index2].push_back({index1, {intCost, streetName}});
        drawTwoWayEdge(vList[index1], vList[index2], stringToChars(streetName), stringToChars(cost));
        
    }
    void removeEdge(string streetName)
    {
        pair<int,int> info = getEdge(streetName);
        for (int i = 0;i < adj[info.first].size(); i++){
            if (adj[info.first][i].first == info.second )
            { 
              
                adj[info.first].erase(adj[info.first].begin()+i);
            }
        }
        for (int i = 0;i < adj[info.second].size(); i++){
            if (adj[info.second][i].first == info.first ) adj[info.second].erase(adj[info.second].begin()+i);
        }
        deleteOneWayEdge(vList[info.first],vList[info.second]);
        outtextxy(vList[info.first].x-4-radius,vList[info.first].y+10+radius+3, stringToChars(vList[info.first].name));
        outtextxy(vList[info.second].x-4-radius,vList[info.second].y+10+radius+3, stringToChars(vList[info.second].name));
    }
    void removeVertex(string placeName)
    {
        int index = getVertex(placeName);
        while( !adj[index].empty() ) 
        {
            int temp = adj[index].back().first;
            deleteOneWayEdge(vList[index],vList[temp]);
            adj[index].pop_back();
        }
        for (int i = 0; i < numberofVertex; i++ )
        {
            if (adj[i].empty()) continue;
            for (int j = 0; j < adj[i].size(); j++) 
            {
                if (adj[i][j].first == index)
                {
                    deleteOneWayEdge(vList[i],vList[index]);
                    adj[i].erase(adj[i].begin()+j);
                }
            }
        }
        deleteVertex(vList[index]);
    }
    void removeAll()
    {    
        for (int i = 0;i < numberofVertex;i++) {
            adj[i].clear();
        }
        while (!vList.empty()) vList.pop_back();
        cleardevice();
        drawxyAxis();
        numberofVertex = 0;
    };
    vector<int> getShortestWay(string name1, string name2)
    {
        int previous[maxn];
        int s = getVertex(name1);
        int t = getVertex(name2);
        vector<long long> d(numberofVertex + 1, INF); 
        d[s] = 0;
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> Q;
        Q.push({0, s});
        while (!Q.empty())
        {
            pair<int, int> top = Q.top();
            Q.pop();
            int u = top.second;
            int length = top.first;
            if (length > d[u])
                continue;
            for (auto it : adj[u])
            {
                int v = it.first;
                int w = it.second.first; 
                if (d[v] > d[u] + w)
                {
                    d[v] = d[u] + w;
                    Q.push({d[v], v});
                    previous[v] = u;
                }
            }
        }
        cout << "Shortest distance : " << d[t] << endl;
        vector<int> path;
        while (1)
        {
            path.push_back(t);
            if (t == s)
                break;
            t = previous[t];
        }
        reverse(path.begin(), path.end());
        return path;
    };
    void highlightWay(vector<int> path)
    {
        for (int i=0; i<path.size(); i++) {
            
            if(i == path.size()-1)
            continue;
            highlightEdge(vList[path[i]],vList[path[i+1]]);
            string wayName;
            for (int j = 0 ;j < adj[path[i]].size();j++)
            {
                if (adj[path[i]][j].first == path[i+1]) wayName = adj[path[i]][j].second.second;
            }
            outtextxy((vList[path[i]].x+vList[path[i+1]].x)/2-20,(vList[path[i]].y+vList[path[i+1]].y)/2+20, stringToChars(wayName));
            outtextxy(vList[path[i]].x-4-radius,vList[path[i]].y+10+radius+3, stringToChars(vList[path[i]].name));
            int cost = getCost(vList[path[i]].name,vList[path[i+1]].name);
            string costStr = to_string(cost);
            const char* costChar = costStr.c_str();
            outtextxy((vList[path[i]].x+vList[path[i+1]].x)/2+10,(vList[path[i]].y+vList[path[i+1]].y)/2-5, costChar);
        }
    }
    void unhighlightWay(vector<int> path)
    {
        for (int i=0; i<path.size(); i++) {
            if(i == path.size()-1) continue;
            unHighlightEdge(vList[path[i]],vList[path[i+1]]);
            string wayName;
            for (int j = 0 ;j < adj[path[i]].size();j++)
            {
                if (adj[path[i]][j].first == path[i+1]) wayName = adj[path[i]][j].second.second;
            }
            outtextxy((vList[path[i]].x+vList[path[i+1]].x)/2-20,(vList[path[i]].y+vList[path[i+1]].y)/2+20, stringToChars(wayName));
            outtextxy(vList[path[i]].x-4-radius,vList[path[i]].y+10+radius+3, stringToChars(vList[path[i]].name));
            int cost = getCost(vList[path[i]].name,vList[path[i+1]].name);
            string costStr = to_string(cost);
            const char* costChar = costStr.c_str();
            outtextxy((vList[path[i]].x+vList[path[i+1]].x)/2+10,(vList[path[i]].y+vList[path[i+1]].y)/2-5, costChar);
        }
    }
    void printList()
    {
        for (int i = 0; i < numberofVertex; i++)
        {   
            if (adj[i].empty()) continue;
            cout << vList[i].name << ":"
                 << " ";
            for (auto x : adj[i])
            {
                cout << "{" << vList[x.first].name << ",{" << x.second.first << "," << x.second.second << "},";
            }
            cout << endl;
        }
    }
    int getVertex(string name)
    {
        string temp;
        for (int i = 0; i < numberofVertex; i++)
        {
            string temp = vList[i].name;
            if (temp == name)
                return i;
        }
        return -1;
    }
    int getCost(string name1, string name2)
    {
        int index1 = getVertex(name1);
        int index2 = getVertex(name2);
        for (auto x : adj[index1])
        {
            if (index2 == x.first)
                return x.second.first;
        }
    };
    pair<int, int> getEdge(string name)
    {
        for (int i = 0; i < numberofVertex; i++)
        {
            for (auto x : adj[i])
            {
                if (x.second.second == name)
                    return {i, x.first};
            }
        }
        return {-1,-1};
    }
};