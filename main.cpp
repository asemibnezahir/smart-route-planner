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
        int routecount=0;

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
        int roadExists(int sourceIndex,int destinationIndex)
        {
            for(int i=0;i<graph[sourceIndex].size();i++)
            {
                if(graph[sourceIndex][i].first==destinationIndex)
                    return i;
            }
            return -1;
        }
        void DFSHelper(int cityIndex,vector<bool>&visited)
        {
            visited[cityIndex]=true;
            cout<<cities[cityIndex]<<" ->";
            for(int i=0;i<graph[cityIndex].size();i++)
            {
                int neibourCityIndex=graph[cityIndex][i].first;
                if(visited[neibourCityIndex]==false)
                    DFSHelper(neibourCityIndex,visited);
            }
        }
        void routeFinderHelper(int currentIndex,int destinationIndex,vector<bool>&visited,vector<int>&currentPath)
        {
            visited[currentIndex]=true;
            currentPath.push_back(currentIndex);
            if(currentIndex==destinationIndex)
            {
                routecount++;
                cout<<"Route-"<<routecount<<": ";
                for(int i=0;i<currentPath.size();i++)
                {
                    cout<<cities[currentPath[i]];
                    if(i!=currentPath.size()-1)
                        cout<<" -> ";
                    else
                        cout<<endl;
                }
                currentPath.pop_back();
                visited[currentIndex]=false;
                return;
            }
            for(int i=0;i<graph[currentIndex].size();i++)
            {
                int neighbour=graph[currentIndex][i].first;
                if(!visited[neighbour])
                    routeFinderHelper(neighbour,destinationIndex,visited,currentPath);
            }
            currentPath.pop_back();
            visited[currentIndex]=false;
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
            cout<<"Feature coming soon..."<<endl;
            /*string city;
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
            */
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
            if(roadExists(sourceIndex,destinationIndex)!=-1)
            {
                cout<<"Road Already Exists. Not need to add again...."<<endl;
                return;
            }
            graph[sourceIndex].push_back({destinationIndex,distance});
            graph[destinationIndex].push_back({sourceIndex,distance});
            cout<<"Road added successfully!"<< endl;
        }
        void showRoads()
        {
            for(int i=0;i<graph.size();i++)
            {
                cout<<cities[i]<<":"<<endl;
                for(int j=0;j<graph[i].size();j++)
                {
                    if(graph[i][j].first>i)
                        cout<<cities[i]<<" <--> "<<cities[graph[i][j].first]<<" ("<<graph[i][j].second<<" km)"<<endl;
                }
            }
        }
        void removeRoad()
        {
            string source,destination;
            cout<<"Enter Source City: ";
            getline(cin>>ws,source);
            cout<<"Enter Destination City: ";
            getline(cin>>ws,destination);
            int sourceIndex=cityExists(source);
            int destinationIndex=cityExists(destination);
            if(sourceIndex==-1&&destinationIndex==-1)
            {
                cout<<"Both cities do not exist!!"<<endl;
                return;
            }
            else if(sourceIndex==-1)
            {
                cout<<"Source City do not exist!!"<<endl;
                return;
            }
            else if(destinationIndex==-1)
            {
                cout<<"Destination City do not exist!!"<<endl;
                return;
            }
            if(sourceIndex==destinationIndex)
            {
                cout<<"Source and Destination cannot be the same!!"<<endl;
                return;
            }
            int roadInd1=roadExists(sourceIndex,destinationIndex);
            int roadInd2=roadExists(destinationIndex,sourceIndex);

            if(roadInd1==-1||roadInd2==-1)
            {
                cout<<"Road Doesnot Exists."<<endl;
                return;
            }
            graph[sourceIndex].erase(graph[sourceIndex].begin()+roadInd1);
            graph[destinationIndex].erase(graph[destinationIndex].begin()+roadInd2);
            cout<<"Road removed successfully!"<<endl;
        }
        void exploreCities()
        {
            string city;
            cout<<"Enter Starting City: ";
            getline(cin>>ws,city);
            int startIndex=cityExists(city);
            if(startIndex==-1)
            {
                cout<<"City does not exist!!"<<endl;
                return;
            }
            vector<bool> visited(cities.size(),false);
            cout<<"Exploring From :"<<city<<endl;
            DFSHelper(startIndex,visited);
            cout<<endl;

        }
        void routeFinder()
        {
            string source,destination;
            cout<<"Enter Source City: ";
            getline(cin>>ws,source);
            cout<<"Enter Destination City: ";
            getline(cin>>ws,destination);
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
            routecount=0;
            vector<bool>visited(graph.size(),false);
            vector<int>currentPath;
            routeFinderHelper(sourceIndex,destinationIndex,visited,currentPath);
            if(routecount==0)
                cout<<"No route found between "<<source<<" and "<<destination<<"."<<endl;
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
        cout<<"2. Remove City\n";
        cout<<"3. Add Route\n";
        cout<<"4. Remove Route\n";
        cout<<"5. Show Cities\n";
        cout<<"6. Show Routes\n";
        cout<<"7. Explore Cities\n";
        cout<<"8. Find All Routes\n";
        cout<<"9. Find Shortest Route\n";
        cout<<"10. Developer Information\n";
        cout<<"11. Exit\n";

        cout<<"\nEnter your choice: ";
        cin>>choice;

        switch(choice)
        {
            case 1:
                planner.addCity();
                break;

            case 2:
                planner.removeCity();
                break;

            case 3:
                planner.addRoad();
                break;

            case 4:
                planner.removeRoad();
                break;

            case 5:
                planner.showCities();
                break;

            case 6:
                planner.showRoads();
                break;

            case 7:
                planner.exploreCities();
                break;

            case 8:
                planner.routeFinder();
                break;

            case 9:
                cout << "\nThank you for using Smart Route Planner!\n";
                break;

            case 10:
                cout << "\nThank you for using Smart Route Planner!\n";
                break;

            case 11: exit(0);

            default:
                cout << "\nInvalid Choice! Please try again.\n";
        }
    }
}