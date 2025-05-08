#include <iostream>
#include <vector>
#include <queue>
#include <cmath>
#include <unordered_map>
#include <algorithm>

using namespace std;

struct Point
{
    int x, y;

    Point() : x(0), y(0) {}
    Point(int x, int y) : x(x), y(y) {}

    bool operator==(const Point &other) const
    {
        return x == other.x && y == other.y;
    }
};

struct PointHash
{
    size_t operator()(const Point &p) const
    {
        return hash<int>()(p.x) ^ hash<int>()(p.y);
    }
};

struct Node
{
    Point point;
    int gCost;
    int hCost;
    int fCost() const { return gCost + hCost; }

    Node(Point p, int g, int h) : point(p), gCost(g), hCost(h) {}

    bool operator<(const Node &other) const
    {
        return fCost() > other.fCost();
    }
};

vector<Point> directions = {Point(-1, 0), Point(1, 0), Point(0, -1), Point(0, 1)};

bool isValid(Point p, const vector<vector<int>> &grid)
{
    return p.x >= 0 && p.x < grid.size() && p.y >= 0 && p.y < grid[0].size() && grid[p.x][p.y] == 0;
}

int heuristic(Point a, Point b)
{
    return abs(a.x - b.x) + abs(a.y - b.y);
}

vector<Point> aStar(Point start, Point target, vector<vector<int>> &grid)
{
    priority_queue<Node> openSet;
    unordered_map<Point, Point, PointHash> cameFrom;
    unordered_map<Point, int, PointHash> gScore;

    openSet.emplace(start, 0, heuristic(start, target));
    gScore[start] = 0;

    while (!openSet.empty())
    {
        Node current = openSet.top();
        openSet.pop();

        if (current.point == target)
        {
            vector<Point> path;
            Point p = target;
            while (cameFrom.find(p) != cameFrom.end())
            {
                path.push_back(p);
                p = cameFrom[p];
            }

            path.push_back(start);
            reverse(path.begin(), path.end());
            return path;
        }

        for (auto dir : directions)
        {
            Point neighbor(current.point.x + dir.x, current.point.y + dir.y);

            if (!isValid(neighbor, grid))
                continue;

            int tentativeGScore = gScore[current.point] + 1;
            if (gScore.find(neighbor) == gScore.end() || tentativeGScore < gScore[neighbor])
            {
                int gCost = tentativeGScore;
                gScore[neighbor] = gCost;
                int hCost = heuristic(neighbor, target);
                openSet.emplace(neighbor, tentativeGScore, hCost);
                cameFrom[neighbor] = current.point;

                cout << "\nPoint: (" << neighbor.x << ", " << neighbor.y << ") ";
                cout << "\th(Point): " << hCost << "\tg(Point): " << gCost << "\tf(Point): " << (gCost + hCost) << endl;
            }
        }
    }

    return {};
}

int main()
{
    // Example grid
    vector<vector<int>> grid = {
        {0, 0, 0, 1, 0},
        {1, 1, 0, 1, 0},
        {0, 0, 0, 0, 0},
        {0, 1, 1, 1, 0},
        {0, 0, 0, 0, 0}};
    bool b1 = true;

    while (b1)
    {
        pair<int, int> a, b;
        cout << "\n Enter Starting point :";
        cin >> a.first >> a.second;

        cout << "\n Enter Target point :";
        cin >> b.first >> b.second;

        Point start(a.first, a.second);
        Point target(b.first, b.second);
        vector<Point> path = aStar(start, target, grid);

        if (!path.empty())
        {
            cout << "\n\t#----------Path found....Here is the ROUTE----------#\n";
            size_t i = 0;

            while (i < path.size() - 1)
            {
                if (i == 0)
                    cout << "\nStarting Point : (" << path[i].x << ", " << path[i].y << ") \n";

                cout << "\nCurrent Point : (" << path[i].x << ", " << path[i].y << ")";

                pair<int, int> curr(path[i].x, path[i].y);
                i++;

                if (path[i].x > curr.first)
                    cout << "\tGo Downward!!";
                else if (path[i].y > curr.second)
                    cout << "\tGo Forward!!";
            }
            cout << "\nTarget Reached!!!" << endl;
            cout << "\tTarget : (" << path[i].x << ", " << path[i].y << ")" << endl;
        }

        else
            cout << "No path found!\n";

        cout << "\n Do you want to check another root ? (Y/N)";
        cin >> b1;
    }

    return 0;
}