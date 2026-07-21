// Header Files
#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <queue>
#include <climits>
#include <algorithm>
#include <iomanip>
#include <cstdlib>
#include <limits>
#include <windows.h>

using namespace std;

void clearScreen()
{
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}
void pauseScreen()
{
    cout<<"\nPress Enter to continue...";
    cin.ignore(numeric_limits<streamsize>::max(),'\n');
    cin.get();
}
void setColor(int color)
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),color);
}

class RoutePlanner
{
    private:
        vector<string> cities; // Member Variable
        vector<vector<pair<int,int>>> graph;
        int routeCount=0;

        string toLowerCase(string text)
        {
            for (int i=0;i<text.size();i++)
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
                routeCount++;
                cout<<"Route-"<<routeCount<<": ";
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
            setColor(14);
            string city;
            cout<<"Enter city name: ";
            getline(cin>>ws,city);
            if(cityExists(city)!=-1)
            {
                setColor(12);
                cout<<"City already exists!! Add another....."<<endl;
                setColor(7);
                return;
            }
            cities.push_back(city);
            graph.push_back(vector<pair<int,int>>());
            setColor(10);
            cout<<city<<" added successfully!"<<endl;
            setColor(7);
        }
        void showCities()
        {
            if(cities.empty())
            {
                setColor(12);
                cout<<"No Cities Available!! Add some first..."<<endl;
                setColor(7);
                return;
            }
            setColor(11);
            cout<<"\n----- Available Cities -----"<<endl;
            setColor(7);
            for(int i=0;i<cities.size();i++)
                cout<<"  "<<i+1<<". "<<cities[i]<<endl;
        }
        void removeCity()
        {
            setColor(14);
            string city;
            cout<<"Enter city name: ";
            getline(cin>>ws,city);
            int Ind=cityExists(city);
            if(Ind==-1)
            {
                setColor(12);
                cout<<"City Name does not Exists here....."<<endl;
                setColor(7);
                return;
            }
            cities.erase(cities.begin()+Ind);
            graph.erase(graph.begin()+Ind);
            for(int i=0;i<graph.size();i++)
            {
                for(int j=0;j<graph[i].size();j++)
                {
                    if(graph[i][j].first==Ind)
                    {
                        graph[i].erase(graph[i].begin()+j);
                        j--;
                        continue;
                    }
                    if(graph[i][j].first>Ind)
                        graph[i][j].first--;
                }
            }
            setColor(10);
            cout<<city<<" removed successfully!"<< endl;
            setColor(7);
        }
        void addRoad()
        {
            setColor(14);
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
                setColor(12);
                cout<<"Distance Must be greater than zero"<<endl;
                setColor(7);
                return;
            }
            int sourceIndex=cityExists(source);
            int destinationIndex=cityExists(destination);
            setColor(12);
            if(sourceIndex==-1&&destinationIndex==-1)
            {
                cout<<"Both cities do not exist!! Add them first...."<<endl;
                setColor(7);
                return;
            }
            else if(sourceIndex==-1)
            {
                cout<<"Source City do not exist!! Add it first...."<<endl;
                setColor(7);
                return;
            }
            else if(destinationIndex==-1)
            {
                cout<<"Destination City do not exist!! Add it first...."<<endl;
                setColor(7);
                return;
            }
            if(sourceIndex==destinationIndex)
            {
                cout<<"Source and Destination cannot be the same!!"<<endl;
                setColor(7);
                return;
            }
            if(roadExists(sourceIndex,destinationIndex)!=-1)
            {
                cout<<"Road Already Exists. Not need to add again...."<<endl;
                setColor(7);
                return;
            }
            graph[sourceIndex].push_back({destinationIndex,distance});
            graph[destinationIndex].push_back({sourceIndex,distance});
            setColor(10);
            cout<<"Road added successfully!"<<endl;
            setColor(7);
        }
        void showRoads()
        {
            if(cities.empty())
            {
                setColor(12);
                cout<<"No Roads Available!! Add some cities first..."<<endl;
                setColor(7);
                return;
            }
            setColor(14);
            for(int i=0;i<graph.size();i++)
            {
                setColor(11);
                cout<<cities[i]<<":"<<endl;
                setColor(7);
                routeCount=0;
                for(int j=0;j<graph[i].size();j++)
                {
                    routeCount++;
                    if(graph[i][j].first>i)
                        cout<<routeCount<<". "<<cities[i]<<" <-->"<<cities[graph[i][j].first]<<" ("<<graph[i][j].second<<" km)"<<endl;
                }
            }
            setColor(7);
        }
        void removeRoad()
        {
            setColor(14);
            string source,destination;
            cout<<"Enter Source City: ";
            getline(cin>>ws,source);
            cout<<"Enter Destination City: ";
            getline(cin>>ws,destination);
            int sourceIndex=cityExists(source);
            int destinationIndex=cityExists(destination);
            setColor(12);
            if(sourceIndex==-1&&destinationIndex==-1)
            {
                cout<<"Both cities do not exist!!"<<endl;
                setColor(7);
                return;
            }
            else if(sourceIndex==-1)
            {
                cout<<"Source City do not exist!!"<<endl;
                setColor(7);
                return;
            }
            else if(destinationIndex==-1)
            {
                cout<<"Destination City do not exist!!"<<endl;
                setColor(7);
                return;
            }
            if(sourceIndex==destinationIndex)
            {
                cout<<"Source and Destination cannot be the same!!"<<endl;
                setColor(7);
                return;
            }
            int roadInd1=roadExists(sourceIndex,destinationIndex);
            int roadInd2=roadExists(destinationIndex,sourceIndex);

            if(roadInd1==-1||roadInd2==-1)
            {
                cout<<"Road Doesnot Exists."<<endl;
                setColor(7);
                return;
            }
            graph[sourceIndex].erase(graph[sourceIndex].begin()+roadInd1);
            graph[destinationIndex].erase(graph[destinationIndex].begin()+roadInd2);
            setColor(10);
            cout<<"Road removed successfully!"<<endl;
            setColor(7);
        }
        void exploreCities()
        {
            setColor(14);
            string city;
            cout<<"Enter Starting City: ";
            getline(cin>>ws,city);
            int startIndex=cityExists(city);
            if(startIndex==-1)
            {
                setColor(12);
                cout<<"City does not exist!!"<<endl;
                setColor(7);
                return;
            }
            vector<bool> visited(cities.size(),false);
            setColor(14);
            cout<<"Exploring From :"<<city<<endl;
            setColor(7);
            DFSHelper(startIndex,visited);
            cout<<endl;
        }
        void routeFinder()
        {
            setColor(14);
            string source,destination;
            cout<<"Enter Source City: ";
            getline(cin>>ws,source);
            cout<<"Enter Destination City: ";
            getline(cin>>ws,destination);
            int sourceIndex=cityExists(source);
            int destinationIndex=cityExists(destination);
            setColor(12);
            if(sourceIndex==-1&&destinationIndex==-1)
            {
                cout<<"Both cities do not exist!! Add them first...."<<endl;
                setColor(7);
                return;
            }
            else if(sourceIndex==-1)
            {
                cout<<"Source City do not exist!! Add it first...."<<endl;
                setColor(7);
                return;
            }
            else if(destinationIndex==-1)
            {
                cout<<"Destination City do not exist!! Add it first...."<<endl;
                setColor(7);
                return;
            }
            if (sourceIndex==destinationIndex)
            {
                cout<<"Source and Destination cannot be the same!!"<<endl;
                setColor(7);
                return;
            }
            setColor(7);
            routeCount=0;
            vector<bool> visited(graph.size(),false);
            vector<int> currentPath;
            routeFinderHelper(sourceIndex,destinationIndex,visited,currentPath);
            setColor(12);
            if(routeCount==0)
                cout<<"No route found between "<<source<<" and "<< destination<<"."<<endl;
            setColor(7);
        }
        void shortestRoute()
        {
            setColor(14);
            string source,destination;
            cout<<"Enter Source City: ";
            getline(cin>>ws,source);
            cout<<"Enter Destination City: ";
            getline(cin>>ws,destination);
            int sourceIndex=cityExists(source);
            int destinationIndex=cityExists(destination);
            setColor(12);
            if(sourceIndex==-1&&destinationIndex==-1)
            {
                cout<<"Both cities do not exist!! Add them first...."<<endl;
                setColor(7);
                return;
            }
            else if(sourceIndex==-1)
            {
                cout<<"Source City do not exist!! Add it first...."<<endl;
                setColor(7);
                return;
            }
            else if(destinationIndex==-1)
            {
                cout<<"Destination City do not exist!! Add it first...."<<endl;
                setColor(7);
                return;
            }
            if(sourceIndex==destinationIndex)
            {
                cout<<"Source and Destination cannot be the same!!" << endl;
                setColor(7);
                return;
            }
            setColor(7);
            vector<int> distance(cities.size(),INT_MAX);
            vector<int> parent(cities.size(),-1);
            priority_queue<pair<int,int>,vector<pair<int,int>>,greater<pair<int,int>>> pq;
            distance[sourceIndex]=0;
            pq.push({0,sourceIndex});
            while(!pq.empty())
            {
                int currentDistance=pq.top().first;
                int currentCityIndex=pq.top().second;
                pq.pop();
                if(currentDistance>distance[currentCityIndex])
                    continue;
                for(int i=0;i<graph[currentCityIndex].size();i++)
                {
                    int neighbor=graph[currentCityIndex][i].first;
                    int roadDistance=graph[currentCityIndex][i].second;
                    int newDistance=currentDistance + roadDistance;
                    if(newDistance<distance[neighbor])
                    {
                        distance[neighbor]=newDistance;
                        parent[neighbor]=currentCityIndex;
                        pq.push({newDistance,neighbor});
                    }
                }
            }
            if(distance[destinationIndex]==INT_MAX)
            {
                setColor(12);
                cout<<"No Paths Found to "<<cities[destinationIndex]<<endl;
                setColor(7);
                return;
            }
            vector<int> path;
            int current=destinationIndex;
            while(current!=-1)
            {
                path.push_back(current);
                current=parent[current];
            }
            reverse(path.begin(),path.end());
            for(int i=0;i<path.size();i++)
            {
                cout<<cities[path[i]];
                if(i!=path.size()-1)
                    cout<<" -> ";
                else
                    cout<<endl;
            }
            setColor(11);
            cout<<"Total Distance: "<<distance[destinationIndex]<<" Km"<<endl;
            setColor(7);
        }
        void teamInfo()
        {
            setColor(13);
            cout<<"\n==============================================\n";
            cout<<"          TEAM INFORMATION\n";
            cout<<"==============================================\n";
            cout<<"Team Name    : RouteMasters\n";
            cout<<"Project Name : Smart Route Planner\n";
            cout<<"Total Members: 5\n";
            cout<<"==============================================\n\n";
            cout<<left<<setw(5)<<"SL"<<setw(30)<<"Name"<<setw(15)<<"Student ID"<<endl;
            cout<<"----------------------------------------------\n";
            cout<<left<<setw(5)<<"1"<<setw(30)<<"Md Rahat Mahamud"<<setw(15)<<"252-15-234"<<endl;
            cout<<left<<setw(5)<<"2"<<setw(30)<<"Asem Ibne Zahir"<<setw(15)<<"252-15-199"<<endl;
            cout<<left<<setw(5)<<"3"<<setw(30)<<"MD Shahriar Alam Ohe"<<setw(15)<<"252-15-197"<<endl;
            cout<<left<<setw(5)<<"4"<<setw(30)<<"Md Ashak Billah Tanzim"<<setw(15)<<"252-15-796"<<endl;
            cout<<left<<setw(5)<<"5"<<setw(30)<<"Md Adip Hasan"<<setw(15)<<"252-15-082"<<endl;
            cout<<"==============================================\n";
            setColor(7);
        }
};

RoutePlanner planner;

int main()
{
    int choice;
    while(true)
    {
        clearScreen();
        setColor(11);
        cout<<"\n=========================================\n";
        cout<<"      SMART ROUTE PLANNER SYSTEM\n";
        cout<<"=========================================\n";
        setColor(14);

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
        setColor(7);

        switch(choice)
        {
            case 1:
                clearScreen();
                planner.addCity();
                pauseScreen();
                break;

            case 2:
                clearScreen();
                planner.removeCity();
                pauseScreen();
                break;

            case 3:
                clearScreen();
                planner.addRoad();
                pauseScreen();
                break;

            case 4:
                clearScreen();
                planner.removeRoad();
                pauseScreen();
                break;

            case 5:
                clearScreen();
                planner.showCities();
                pauseScreen();
                break;

            case 6:
                clearScreen();
                planner.showRoads();
                pauseScreen();
                break;

            case 7:
                clearScreen();
                planner.exploreCities();
                pauseScreen();
                break;

            case 8:
                clearScreen();
                planner.routeFinder();
                pauseScreen();
                break;

            case 9:
                clearScreen();
                planner.shortestRoute();
                pauseScreen();
                break;

            case 10:
                clearScreen();
                planner.teamInfo();
                pauseScreen();
                break;

            case 11:
                clearScreen();
                setColor(11);
                cout<<"\n=========================================\n";
                cout<<" Thank you for using Smart Route Planner!\n";
                cout<<"        Have a Safe Journey!\n";
                cout<<"=========================================\n";
                exit(0);
            default:
                cout<<"\nInvalid Choice!\n";
                pauseScreen();
        }
    }
}