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
        initwindow(900, 700, "Visualization"); // khởi tạo cửa sổ
        setbkcolor(WHITE);                     // set backgroundcolor là white
        cleardevice();
        setcolor(BLACK);
        // settextstyle(0,0,2); 
        drawxyAxis();   
    }
    ~Graph() = default;
    void addVertex(int x, int y, string placeName)
    { // đỉnh: tọa độ x, y, tên điểm
        // Thêm vertex đấy vào trong vector để lưu
        numberofVertex++;
        Vertex temp = {x, y, placeName};
        vList.push_back(temp);
        // B2 : vẽ lên màn hình
        drawVertex(x, y, stringToChars(placeName));
    }
    void addOneWayEdge(string name1, string name2, string streetName, string cost)
    {
        // đường 1 chiều: điểm đầu, điểm cuối, tên đường, khoảng cách
        //    Thêm đường đấy vào trong danh sách kề array adj.
        int intCost = stoi(cost);
        int index1 = getVertex(name1);
        int index2 = getVertex(name2);  
        //    adj[index1] : là 1 cái vector chứa các thông tin của các đỉnh kề với đỉnh index1  dưới dạng {index của đỉnh,{khoảng cách, tên đường}};
        adj[index1].push_back({index2, {intCost, streetName}});
        //    Vẽ lên màn hình
        drawOneWayEdge(vList[index1], vList[index2], stringToChars(streetName), stringToChars(cost));
    
    }
    void addTwoWayEdge(string name1, string name2, string streetName, string cost)
    {
        // đường 2 chiều: điểm đầu, điểm cuối, tên đường, khoảng cách
        int intCost = stoi(cost);
        int index1 = getVertex(name1);
        int index2 = getVertex(name2);
         //    adj[index1] : là 1 cái vector chứa các thông tin của các đỉnh kề với đỉnh index1  dưới dạng {index của đỉnh,{khoảng cách, tên đường}};
        adj[index1].push_back({index2, {intCost, streetName}});
        adj[index2].push_back({index1, {intCost, streetName}});
        //    Vẽ lên màn hình
        drawTwoWayEdge(vList[index1], vList[index2], stringToChars(streetName), stringToChars(cost));
        
    }
    void removeEdge(string streetName)
    {
        // xóa 1 đường : xóa trong danh sách kề : tốt nhất là xóa theo kiểu đường 2 chiều
        pair<int,int> info = getEdge(streetName);
        for (int i = 0;i < adj[info.first].size();i++){
            if (adj[info.first].at(i).first == info.second ) adj[info.first].erase(adj[info.first].begin()+i);
        }
        for (int i = 0;i < adj[info.second].size();i++){
            if (adj[info.second].at(i).first == info.first ) adj[info.second].erase(adj[info.first].begin()+i);
        }
        // xóa trên màn hìn
        deleteOneWayEdge(vList[info.first],vList[info.second]);
        outtextxy(vList[info.first].x-4-radius,vList[info.first].y+10+radius+3, stringToChars(vList[info.first].name));
        outtextxy(vList[info.second].x-4-radius,vList[info.second].y+10+radius+3, stringToChars(vList[info.second].name));
    }
    void removeVertex(string placeName)
    {
        // xóa 1 đỉnh : xóa hết các đỉnh trong vector kề của đỉnh này trong list, xóa hết đỉnh này ở mọi vector kề khác
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
        // xóa hết màn hình , vẽ lại trục tọa độ
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