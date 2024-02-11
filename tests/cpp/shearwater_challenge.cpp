#include <gtest/gtest.h>
#include <fstream>
#include <vector>
#include <filesystem>
#include <cmath>

#include <iostream>
#include <vector>
#include <queue>
#include <cmath>
#include <unordered_map>

using namespace std;

struct Waypoint {
    int x;
    int y;
    int penalty;
};

struct State {
    int x;
    int y;
    int idx;
    double cost;
    vector<int> path;
};

double distance(int x1, int y1, int x2, int y2) {
    return sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2));
}

double calculateTotalTime(const vector<Waypoint>& waypoints, const vector<int>& path) {
    double total_time = 0.0;
    int current_x = 0, current_y = 0;

    for (int i = 0; i < path.size(); ++i) {
        total_time += distance(current_x, current_y, waypoints[path[i]].x, waypoints[path[i]].y) / 2.0; // Assuming UAV moves at 2 m/s
        total_time += 10; // Stop for 10 seconds at each waypoint
        current_x = waypoints[path[i]].x;
        current_y = waypoints[path[i]].y;
        if (i < path.size() - 1) {
            total_time += waypoints[path[i]].penalty; // Add penalty for skipping the current waypoint
        }
    }

    // Add penalty for the final waypoint
    total_time += waypoints[path.back()].penalty;

    return total_time;
}

double heuristic(int x1, int y1, int x2, int y2) {
    return distance(x1, y1, x2, y2);
}

double findLowestTime(const vector<Waypoint>& waypoints) {
    int n = waypoints.size();
    vector<int> optimal_path;
    vector<bool> visited(n, false);

    priority_queue<State, vector<State>, function<bool(State, State)>> pq(
        [](const State& a, const State& b) {
            return a.cost > b.cost;
        }
    );

    unordered_map<int, double> dp; // Memoization for dynamic programming

    pq.push({0, 0, 0, 0.0, {0}});

    while (!pq.empty()) {
        State current = pq.top();
        pq.pop();

        if (visited[current.idx]) {
            continue;
        }

        visited[current.idx] = true;

        if (current.idx == n - 1) {
            optimal_path = current.path;
            break;
        }

        for (int i = 0; i < n; ++i) {
            if (!visited[i]) {
                double new_cost = current.cost + distance(waypoints[current.idx].x, waypoints[current.idx].y, waypoints[i].x, waypoints[i].y) / 2.0 + 10;
                new_cost += waypoints[i].penalty;
                if (!dp.count(i) || new_cost < dp[i]) {
                    dp[i] = new_cost;
                    vector<int> new_path = current.path;
                    new_path.push_back(i);
                    pq.push({waypoints[i].x, waypoints[i].y, i, new_cost + heuristic(waypoints[i].x, waypoints[i].y, 100, 100), new_path});
                }
            }
        }
    }

    return calculateTotalTime(waypoints, optimal_path);
}

int main() {
    vector<Waypoint> waypoints = {{25, 25, 5}, {50, 50, 10}, {75, 75, 7}, {100, 100, 15}};
    // Waypoints are represented as (x, y, penalty)

    double lowest_time = findLowestTime(waypoints);
    cout << "Lowest possible time: " << lowest_time << " seconds" << endl;

    return 0;
}


using namespace std;
namespace fs = std::filesystem;

// Structure to represent a waypoint
struct Waypoint
{
    float x, y;  // Coordinates of the waypoint as floats
    int penalty; // Penalty for missing delivery
};

// Structure to represent a solution
struct Solution
{
    float time;  // Time to deliver all packages
    int penalty; // Total penalty incurred
};

class Solver
{
    constexpr static int SPEED = 2; // m/s
public:
    Solution solve(vector<Waypoint> &waypoints)
    {
        int n = waypoints.size();
        vector<Solution> dp(n);

        dp[0].time = sqrt(waypoints[0].x * waypoints[0].x + waypoints[0].y * waypoints[0].y) / SPEED + 10;
        dp[0].penalty = waypoints[0].penalty;

        for (int i = 1; i < n; ++i)
        {
            float distance = sqrt((waypoints[i].x - waypoints[i - 1].x) * (waypoints[i].x - waypoints[i - 1].x) + (waypoints[i].y - waypoints[i - 1].y) * (waypoints[i].y - waypoints[i - 1].y));
            dp[i].time = dp[i - 1].time + distance / SPEED + 10;
            dp[i].penalty = dp[i - 1].penalty + waypoints[i].penalty;

            // Check if skipping the current waypoint leads to a better solution
            if (i >= 2)
            {
                dp[i].time = min(dp[i].time, dp[i - 2].time + distance / SPEED + 10);
                dp[i].penalty = min(dp[i].penalty, dp[i - 2].penalty);
            }
        }

        // Adding the time to reach the final point
        float last_distance = sqrt(waypoints[n - 1].x * waypoints[n - 1].x + waypoints[n - 1].y * waypoints[n - 1].y);
        dp[n - 1].time += last_distance / SPEED + 10;

        // Formatting time to three decimal places
        dp[n - 1].time = round(dp[n - 1].time * 1000) / 1000;

        return dp[n - 1];
    }
};

// Class to represent a test case
class TestCase
{
public:
    int numWaypoints;
    vector<Waypoint> waypoints;

    // Function to load the test case from a file
    void loadTestCase(const string &filename)
    {
        ifstream inFile(filename);
        inFile >> numWaypoints;
        if (numWaypoints == 0)
            return;

        waypoints.resize(numWaypoints);
        for (int i = 0; i < numWaypoints; ++i)
        {
            inFile >> waypoints[i].x >> waypoints[i].y >> waypoints[i].penalty;
        }
        inFile.close();
    }

    // Function to print all waypoints to the console
    void printWaypoints()
    {
        cout << "Waypoints:\n";
        for (const auto &waypoint : waypoints)
        {
            cout << "Coordinates: (" << waypoint.x << ", " << waypoint.y << "), Penalty: " << waypoint.penalty << endl;
        }
    }
};

// Fixture for testing loading of test cases
class LoadTestCaseTest : public ::testing::TestWithParam<string>
{
protected:
    string directory;
    TestCase testCase;

    void SetUp() override
    {
        directory = GetParam();
    }

    void TearDown() override
    {
    }
};

// Test case to check loading of test cases
TEST_P(LoadTestCaseTest, LoadTestCaseTest)
{
    Solver solver;
    string filename;
    for (const auto &entry : fs::directory_iterator(directory))
    {
        if (entry.is_regular_file() && entry.path().filename().string().find("sample_input") == 0)
        {
            filename = entry.path().string();
            std::cout << "filename: " << filename << std::endl;
            testCase.loadTestCase(filename);
            ASSERT_GT(testCase.numWaypoints, 0); // Check that the number of waypoints is greater than 0
            //testCase.printWaypoints();
            Solution result = solver.solve(testCase.waypoints);
            cout << "Time: " << result.time << ", Penalty: " << result.penalty << endl;
        }
    }
}

// Generate test cases for the specified directory
INSTANTIATE_TEST_CASE_P(LoadTestCases, LoadTestCaseTest, ::testing::Values(fs::current_path() / fs::path("../../data/shearwater_challenge")));

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
