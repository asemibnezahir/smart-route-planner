//Header Files
#include <iostream>
#include<vector>
#include<string>
#include<unordered_map>

using namespace std;

class RoutePlanner
{
    private:
        vector<string> cities; //Member Variable
        unordered_map<string,int>cityIndex;
        vector<vector<pair<int,int>>>graph;

        string toLowerCase(string text)
        {
            for(int i=0;i<text.size();i++)
            {
                text[i]=tolower(text[i]);
            }
            return text;
        }
        int cityExists(string city)
        {
            string lowCity=toLowerCase(city);
            for(int i=0;i<cities.size();i++)
            {
                if(toLowerCase(cities[i])==lowCity)
                    return i;
            }
            return -1;
        }
    public:
        void addCity()
        {
            string city;
            cout<<"Enter city name: ";
            getline(cin>>ws,city);
            if(cityExists(city)!=-1)
            {
                cout<<"City already exists!! Add another....."<<endl;
                return;
            }
            cities.push_back(city);
            cityIndex[toLowerCase(city)]=cities.size()-1;
            graph.push_back(vector<pair<int,int>>());
            cout<<city<<" added successfully!"<<endl;
        }
        void showCities()
        {
            if(cities.empty())
            {
                cout<<"No Cities Available!! Add some first..."<<endl;
                return;
            }
            cout<<"\n----- Available Cities -----"<<endl;
            for(int i=0;i<cities.size();i++)
            {
                cout<<"  "<<i+1<<". "<<cities[i]<<endl;
            }
        }
        void removeCity()
        {
            string city;
            cout<<"Enter city name: ";
            getline(cin>>ws,city);
            int Ind=cityExists(city);
            if(Ind==-1)
            {
                cout<<"City Name does not Exists here....."<<endl;
                return;
            }
            cities.erase(cities.begin()+Ind);
            cityIndex.erase(toLowerCase(city));
            cout<<city<<" removed successfully!"<< endl;
        }
        void addRoad()
        {
            string source,destination;
            int distance;
            cout<<"Enter Source City: ";
            getline(cin>>ws,source);
            cout<<"Enter Destination City: ";
            getline(cin>>ws,destination);
            cout<<"Enter City Distance: ";
            cin>>distance;
            if(distance<1)
            {
                cout<<"Distance Must be greater than zero"<<endl;
                return;
            }
            int sourceIndex=cityExists(source);
            int destinationIndex=cityExists(destination);
            if(sourceIndex==-1&&destinationIndex==-1)
            {
                cout<<"Both cities do not exist!! Add them first...."<<endl;
                return;
            }
            else if(sourceIndex==-1)
            {
                cout<<"Source City do not exist!! Add it first...."<<endl;
                return;
            }
            else if(destinationIndex==-1)
            {
                cout<<"Destination City do not exist!! Add it first...."<<endl;
                return;
            }
            if(sourceIndex==destinationIndex)
            {
                cout<<"Source and Destination cannot be the same!!"<<endl;
                return;
            }
            graph[sourceIndex].push_back({destinationIndex,distance});
            graph[destinationIndex].push_back({sourceIndex,distance});
        }
};

RoutePlanner planner;


int main()
{
    int choice;
    while(true)
    {
        cout<<"\n=========================================\n";
        cout<<"      SMART ROUTE PLANNER SYSTEM\n";
        cout<<"=========================================\n";

        cout<<"1. Add City\n";
        cout<<"2. Add Route\n";
        cout<<"3. Show Cities\n";
        cout<<"4. Show Routes\n";
        cout<<"5. Find All Routes (DFS)\n";
        cout<<"6. Find Shortest Route (Dijkstra)\n";
        cout<<"7. Compare Algorithms\n";
        cout<<"8. Exit\n";

        cout<<"\nEnter your choice: ";
        cin>>choice;

        switch(choice)
        {
            case 1:
                planner.addCity();
                break;

            case 2:
                planner.showCities();
                break;

            case 3:
                planner.removeCity();
                break;

            case 4:
                cout << "\n[Show Routes Selected]\n";
                break;

            case 5:
                cout << "\n[DFS Selected]\n";
                break;

            case 6:
                cout << "\n[Dijkstra Selected]\n";
                break;

            case 7:
                cout << "\n[Comparison Mode Selected]\n";
                break;

            case 8:
                cout << "\nThank you for using Smart Route Planner!\n";
                return 0;

            default:
                cout << "\nInvalid Choice! Please try again.\n";
        }
    }
}