#include "graph.h"
class Menu
{

private:
    Graph graph1;

public:
    void AddPlace()
    {
        int x, y;
        string name;
        system("cls");
        cout << "=== ADD PLACE ===" << endl;
        cout << "Codinates: ";
        cin >> x >> y;
        cout << "Name: ";
        fflush(stdin);
        getline(cin, name);
        if (graph1.getVertex(name) != -1)
        {
            cout << "Place already existed.";
            system("pause");
            return;
        }
        graph1.addVertex(x, y, name);
    };
    void AddWay()
    {
        int option;
        string s1, s2, name, distance;
        do
        {
            cout << "=== ADD WAY ===" << endl;
            cout << "1. Add two-way street" << endl;
            cout << "2. Add one-way street" << endl;
            cout << "0. Back" << endl;
            cin >> option;
            system("cls");
            switch (option)
            {
            case 1:
                cout << "=== ADD TWO-WAY STREET ===" << endl;
                cout << "Way between 2 place" << endl;
                cout << "from: ";
                fflush(stdin);
                getline(cin, s1);
                cout << "to: ";
                fflush(stdin);
                getline(cin, s2);
                if (graph1.getVertex(s1) == -1 || graph1.getVertex(s2) == -1)
                {
                    cout << "Place not found" << endl;
                    break;
                }
                cout << "Name of the way: ";
                fflush(stdin);
                getline(cin, name);
                if (graph1.getEdge(name).first != -1)
                {
                    cout << "Way already existed." << endl;
                    break;
                }
                cout << "Distance: ";
                cin >> distance;
                graph1.addTwoWayEdge(s1,s2,name,distance);
                break;
            case 2:
                cout << "=== ADD ONE-WAY STREET ===" << endl;
                cout << "Way between 2 place" << endl;
                cout << "from: ";
                fflush(stdin);
                getline(cin, s1);
                cout << "to: ";
                fflush(stdin);
                getline(cin, s2);
                if (graph1.getVertex(s1) == -1 || graph1.getVertex(s2) == -1)
                {
                    cout << "Place not found"<< endl;
                    break;
                }
                cout << "Name of the way: ";
                fflush(stdin);
                getline(cin, name);
                if (graph1.getEdge(name).first != -1)
                {
                    cout << "Way already existed." << endl;
                    break;
                }
                cout << "Distance: ";
                cin >> distance;
                graph1.addOneWayEdge(s1,s2,name,distance);
                break;
            default:
                break;
            }
        } while (option != 0);
    };
    void Remove()
    {
        string p, w;
        int option;
        do
        {
            cout << "=== REMOVE ===" << endl;
            cout << "1. Revome a place" << endl;
            cout << "2. Remove a way" << endl;
            cout << "3. Remove all" << endl;
            cout << "0. Back" << endl;
            cin >> option;
            system("cls");
            switch (option)
            {
            case 1:
                cout << "=== REMOVE A PLACE ===" << endl;
                cout << "Enter place: ";
                fflush(stdin);
                getline(cin, p);
                if (graph1.getVertex(p) == -1) 
                {
                    cout << "Place not found" << endl;
                    break;
                }
                graph1.removeVertex(p);
                system("pause");
                break;
            case 2:
                cout << "=== REMOVE A WAY ===" << endl;
                cout << "Enter name of the way: ";
                fflush(stdin);
                getline(cin, w);
                if (graph1.getEdge(w).first == -1)
                {
                    cout << "Way not found" << endl;
                    break;
                }
                graph1.removeEdge(w);
                system("pause");
                break;
            case 3:
                cout << "=== REMOVE ALL ===" << endl;
                graph1.removeAll();
                break;
            default:
                break;
            }
        } while (option != 0);
    };
    void Print()
    {
        system("cls");
        graph1.printList();
        system("pause");
    };
    void Hightlight()
    {
        system("cls");
        string begin, end;
        cout << "=== FIND SHORTEST WAY ===" << endl;
        cout << "from: ";
        fflush(stdin);
        getline(cin, begin);
        cout << " to: ";
        fflush(stdin);
        getline(cin, end);
        if (graph1.getVertex(begin) == -1 || graph1.getVertex(end) == -1)
        {
            cout << "Place not found"<< endl;
            system("pause");
            return;
        }
        vector<int> path = graph1.getShortestWay(begin, end);
        graph1.highlightWay(path);
        system("pause");
        graph1.unhighlightWay(path);
    };
    void run(){
        int option;
        do {
        system("cls");
        cout << "==== MAPS ====" << endl;
        cout << "1. Add place" << endl;
        cout << "2. Add way" << endl;
        cout << "3. Remove" << endl;
        cout << "4. Print adjacency list" << endl;
        cout << "5. Find shortest way" << endl;
        cout << "0. Exit" << endl;
        cin >> option;
        switch (option)
        {
        case 1:
            AddPlace();
            break;
        case 2:
            AddWay();
            break;
        case 3:
            Remove();
            break;
        case 4:
            Print();
            break;
        case 5:
            Hightlight();
            break;
        default:
            break;
        }
    } while (option!=0);
    }
};
