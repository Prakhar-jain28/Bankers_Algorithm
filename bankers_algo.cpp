#include <bits/stdc++.h>
using namespace std;

#define ll long long int
#define ld long double
#define all(a) (a).begin(), (a).end()
#define pb push_back
#define imax INT_MAX
#define imin INT_MIN
#define floop(n) for (int i = 0; i < n; i++)

const ll mod = 1e9 + 7;

class Bankers_algorithm
{
    int iProcesses;
    int iResources;
    vector<vector<int>> iAllocated;
    vector<vector<int>> iMax;
    vector<vector<int>> iNeed;
    vector<bool> bFlag;
    vector<int> iAvailable;

public:
    Bankers_algorithm(const vector<vector<int>> &iAllocated1, const vector<vector<int>> &iMax1, const vector<int> &iAvailable1)
    {
        iProcesses = iAllocated1.size();
        iResources = iAllocated1[0].size();
        for (int i = 0; i < iProcesses; i++)
        {
            vector<int> temp;
            for (int j = 0; j < iResources; j++)
            {
                temp.push_back(iAllocated1[i][j]);
            }
            iAllocated.push_back(temp);
        }
        for (int i = 0; i < iProcesses; i++)
        {
            vector<int> temp;
            for (int j = 0; j < iResources; j++)
            {
                temp.push_back(iMax1[i][j]);
            }
            iMax.push_back(temp);
        }
        for (int i = 0; i < iResources; i++)
        {
            iAvailable.push_back(iAvailable1[i]);
        }
        // Adding values to Need matrix
        for (int i = 0; i < iProcesses; i++)
        {
            vector<int> temp;
            for (int j = 0; j < iResources; j++)
            {
                temp.push_back((iMax1[i][j] - iAllocated1[i][j]));
            }
            iNeed.push_back(temp);
        }
        for (int i = 0; i < iProcesses; i++)
        {
            bFlag.push_back(0);
        }
    }
    bool bCheckState(int idx);
    void execution();
    void update(int idx);
};

void Bankers_algorithm::update(int idx)
{
    for (int i = 0; i < iResources; i++)
    {
        iAvailable[i] += iAllocated[idx][i];
    }
}

void Bankers_algorithm::execution()
{
    int iCompleted = 0, idx = 0;
    while (iCompleted != iProcesses)
    {
        if (idx == iProcesses)
        {
            idx = 0;
        }
        if (bCheckState(idx) && !bFlag[idx])
        {
            // If in safe state then update values
            cout << "Process P" << idx << " is in Safe State, Executing: P" << idx << endl;
            bFlag[idx] = 1;
            update(idx);
            iCompleted++;
            idx++;
            continue;
        }
        else if (!bFlag[idx])
        {
            // Pretend
            cout << "Process P" << idx << " is in Unsafe State" << endl;
        }
        idx++;
    }
}

bool Bankers_algorithm::bCheckState(int idx)
{
    for (int i = 0; i < iResources; i++)
    {
        if (iAvailable[i] < iNeed[idx][i])
        {
            return 0;
        }
    }
    return 1;
}

int32_t main()
{
    int iProcessses;
    cout << "Enter Number Of Processes: ";
    cin >> iProcessses;
    int iResources;
    cout << "Enter Number of Resources: ";
    cin >> iResources;

    vector<vector<int>> iAllocated;
    vector<vector<int>> iMax;
    vector<int> iAvailable;

    cout << "Enter the allocated Resources to each process: ";
    for (int i = 0; i < iProcessses; i++)
    {
        vector<int> temp;
        for (int j = 0; j < iResources; j++)
        {
            int x;
            cin >> x;
            temp.push_back(x);
        }
        iAllocated.push_back(temp);
    }
    cout << "Enter the Maximum resources a process require: ";
    for (int i = 0; i < iProcessses; i++)
    {
        vector<int> temp;
        for (int j = 0; j < iResources; j++)
        {
            int x;
            cin >> x;
            temp.push_back(x);
        }
        iMax.push_back(temp);
    }
    cout << "Enter the Available resources : ";
    for (int i = 0; i < iResources; i++)
    {
        int temp;
        cin >> temp;
        iAvailable.push_back(temp);
    }

    Bankers_algorithm obj1(iAllocated, iMax, iAvailable);
    obj1.execution();

    return 0;
}
