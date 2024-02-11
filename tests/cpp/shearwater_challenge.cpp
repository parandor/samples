#include <gtest/gtest.h>
#include <cmath>
#include <iostream>
#include <filesystem>
#include <fstream>
#include <vector>
#include <queue>
#include <unordered_map>

using namespace std;
namespace fs = std::filesystem;

struct Waypoint
{
    int x;
    int y;
    int penalty;
};

struct State
{
    int x;
    int y;
    int idx;
    double cost;
    vector<int> path;
};

class Optimizer
{
public:
    double findLowestTime(const vector<Waypoint> &waypoints)
    {
        int n = waypoints.size();
        vector<int> optimal_path;
        vector<bool> visited(n, false);

        priority_queue<State, vector<State>, function<bool(State, State)>> pq(
            [](const State &a, const State &b)
            {
                return a.cost > b.cost;
            });

        unordered_map<int, double> dp; // Memoization for dynamic programming

        pq.push({0, 0, 0, 0.0, {0}});

        while (!pq.empty())
        {
            State current = pq.top();
            pq.pop();

            if (visited[current.idx])
            {
                continue;
            }

            visited[current.idx] = true;

            if (current.idx == n - 1)
            {
                optimal_path = current.path;
                break;
            }

            for (int i = 0; i < n; ++i)
            {
                if (!visited[i])
                {
                    double new_cost = current.cost + distance(waypoints[current.idx].x, waypoints[current.idx].y, waypoints[i].x, waypoints[i].y) / SPEED + 10;
                    new_cost += waypoints[i].penalty;
                    if (!dp.count(i) || new_cost < dp[i])
                    {
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

private:
    constexpr static float SPEED = 2.0; // Assuming UAV moves at 2 m/s
    double distance(int x1, int y1, int x2, int y2)
    {
        return sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2));
    }

    double calculateTotalTime(const vector<Waypoint> &waypoints, const vector<int> &path)
    {
        double total_time = 0.0;
        int current_x = 0, current_y = 0;

        for (int i = 0; i < path.size(); ++i)
        {
            total_time += distance(current_x, current_y, waypoints[path[i]].x, waypoints[path[i]].y) / SPEED;
            total_time += 10; // Stop for 10 seconds at each waypoint
            current_x = waypoints[path[i]].x;
            current_y = waypoints[path[i]].y;
            if (i < path.size() - 1)
            {
                total_time += waypoints[path[i]].penalty; // Add penalty for skipping the current waypoint
            }
        }

        // Add penalty for the final waypoint
        total_time += waypoints[path.back()].penalty;

        return total_time;
    }

    double heuristic(int x1, int y1, int x2, int y2)
    {
        return distance(x1, y1, x2, y2);
    }
};

class WaypointTest : public ::testing::Test
{
protected:
    void SetUp() override
    {
        fs::path directoryPath = fs::current_path() / "../../data/shearwater_challenge/";
        // Iterate through files in the directory
        for (const auto &entry : fs::directory_iterator(directoryPath))
        {
            // Check if the file starts with "sample_input"
            if (entry.is_regular_file() && entry.path().filename().string().find("sample_input") == 0)
            {
                std::ifstream input(entry.path());
                if (input.is_open())
                {
                    ReadTestCases(input, entry.path());
                    input.close();
                }
            }
        }
    }

    // Add member variables here if needed

    struct TestInfo
    {
        fs::path filePath;
        std::vector<std::vector<Waypoint>> testCases;
    };

    std::vector<TestInfo> testInfos;

private:
    void ReadTestCases(std::ifstream &input, const fs::path &filePath)
    {
        int numWaypoints;
        TestInfo info;
        info.filePath = filePath;
        while (input >> numWaypoints && numWaypoints != 0)
        {
            std::vector<Waypoint> waypoints;
            for (int j = 0; j < numWaypoints; ++j)
            {
                Waypoint wp;
                input >> wp.x >> wp.y >> wp.penalty;
                waypoints.push_back(wp);
            }
            info.testCases.push_back(waypoints);
        }
        testInfos.push_back(info);
    }
};

TEST_F(WaypointTest, TestCaseCount)
{
    // Ensure that the correct number of test cases are read
    for (const auto &info : testInfos)
    {
        EXPECT_EQ(3, info.testCases.size());
    }
}

TEST_F(WaypointTest, WaypointValidity)
{
    // Add your tests to validate waypoints here
    // For example, you can check if the waypoints are within valid ranges
    for (const auto &info : testInfos)
    {
        for (const auto &waypoints : info.testCases)
        {
            for (const auto &wp : waypoints)
            {
                EXPECT_GE(wp.x, 0);
                EXPECT_GE(wp.y, 0);
                EXPECT_GE(wp.penalty, 0);
                // Add more specific tests if needed
            }
        }
    }
}

TEST_F(WaypointTest, LowestTimeTest)
{
    Optimizer optimizer;
    for (const auto &info : testInfos)
    {
        for (const auto &waypoints : info.testCases)
        {
            double lowestTime = optimizer.findLowestTime(waypoints);
            // Add your assertions here to validate the lowest time
            // For demonstration, let's just print it
            std::cout << "Lowest time for test case in file " << info.filePath << ": " << lowestTime << std::endl;
        }
    }
}

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}