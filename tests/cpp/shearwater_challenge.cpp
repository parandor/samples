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
        double final_cost = 0.0;
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

            log_q(pq, waypoints);
            std::cout << "PRE current idx: " << current.idx << ", pq size: " << pq.size() << std::endl;
            if (current.idx == n - 1)
            {
                std::cout << "POST current idx: " << current.idx << ", pq size: " << pq.size() << std::endl;

                optimal_path = current.path;
                final_cost = current.cost;
                cout << " Optimized path:";
                for (int waypoint_index : optimal_path)
                {
                    cout << " (" << waypoints[waypoint_index].x << "," << waypoints[waypoint_index].y << ")";
                }
                cout << endl;
                break;
            }

            for (int i = 0; i < n; ++i)
            {
                if (!visited[i])
                {
                    double time_to_next = distance(waypoints[current.idx].x, waypoints[current.idx].y, waypoints[i].x, waypoints[i].y) / SPEED + 10;
                    double new_cost = current.cost + time_to_next;
                    cout << "current cost: " << current.cost << ", time to next waypoint: " << time_to_next << endl;
                    // std::cout << "wp: " << waypoints[i].x << "," << waypoints[i].y << ", pen: " << waypoints[i].penalty << std::endl;
                    // double skipped_cost = skipped_waypoints_cost(current, waypoints, i);
                    // new_cost += skipped_cost;
                    // cout << "SKIPPED COST: " << skipped_cost << ", " << waypoints[i].x << "," << waypoints[i].y << endl;

                    if (!dp.count(i) || new_cost < dp[i])
                    {
                        dp[i] = new_cost;
                        // cout << "new cost: " << new_cost << ", dp: " << dp[i] << ", " << waypoints[i].x << "," << waypoints[i].y << ", skipped cost: " << skipped_cost;
                        vector<int> new_path = current.path;
                        new_path.push_back(i);
                        // cout << " New path:";
                        // for (int waypoint_index : new_path)
                        // {
                        //     cout << " (" << waypoints[waypoint_index].x << "," << waypoints[waypoint_index].y << ")";
                        // }
                        // cout << endl;

                        pq.push({waypoints[i].x, waypoints[i].y, i, new_cost /*+ heuristic(waypoints[i].x, waypoints[i].y, 100, 100)*/, new_path});
                        // log_q(pq, waypoints);
                    }
                }
            }
        }

        return calculateTotalTime(waypoints, final_cost);
    }

    double skipped_waypoints_cost(const State &current, const vector<Waypoint> &waypoints, const int &j)
    {
        double cumulative_penalty = 0.0;
        // Iterate through all waypoints
        for (int i = 0; i < waypoints.size(); ++i)
        {
            // Check if the current waypoint is not visited
            if (find(current.path.begin(), current.path.end(), i) == current.path.end() && i != j)
            {
                cout << "SKIPPING: x: " << waypoints[i].x << ", y: " << waypoints[i].y << ", penalty: " << waypoints[i].penalty << endl;
                // If the waypoint is not visited, add its penalty to the cumulative penalty
                cumulative_penalty += waypoints[i].penalty;
            }
        }

        return cumulative_penalty;
    }

    void log_q(priority_queue<State, vector<State>, function<bool(State, State)>> &pq, const vector<Waypoint> &waypoints)
    {
        // Log the contents of the priority queue
        cout << "Priority Queue contents after pushing new state:" << endl;
        priority_queue<State, vector<State>, function<bool(State, State)>> temp_pq = pq;
        while (!temp_pq.empty())
        {
            State temp_state = temp_pq.top();
            temp_pq.pop();
            cout << "x: " << temp_state.x << ", y: " << temp_state.y << ", idx: " << temp_state.idx << ", cost: " << temp_state.cost << ", path:";
            for (int waypoint_index : temp_state.path)
            {
                cout << " (" << waypoints[waypoint_index].x << "," << waypoints[waypoint_index].y << ")";
            }
            cout << endl;
        }
    }

private:
    constexpr static float SPEED = 2.0; // Assuming UAV moves at 2 m/s
    double distance(int x1, int y1, int x2, int y2)
    {
        return sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2));
    }

    vector<int> getSkippedWaypoints(const vector<int> &optimal_path, int num_waypoints)
    {
        vector<int> skipped_waypoints;
        for (int i = 0; i < num_waypoints; ++i)
        {
            if (find(optimal_path.begin(), optimal_path.end(), i) == optimal_path.end())
            {
                skipped_waypoints.push_back(i);
            }
        }
        return skipped_waypoints;
    }

    double calculateTotalTime(const vector<Waypoint> &waypoints, const double &cost)
    {
        double total_time = 0.0;
        int current_x = 0, current_y = 0;
        // auto skipped = getSkippedWaypoints(path, waypoints.size());
        // auto skipped_time = 0.0;
        // for (int i = 0; i < skipped.size(); ++i)
        // {
        //     skipped_time += waypoints[skipped[i]].penalty;
        //     // std::cout << "skipped: " << waypoints[skipped[i]].x << "," << waypoints[skipped[i]].y << std::endl;
        // }
        // std::cout << "skipped time total: " << skipped_time << std::endl;

        // for (int i = 0; i < path.size(); ++i)
        // {
        //     std::cout << "Optimized path: x: " << waypoints[path[i]].x << ", y: " << waypoints[path[i]].y << std::endl;
        // }

        // for (int i = 0; i < path.size(); ++i)
        // {
        //     std::cout << "x: " << waypoints[path[i]].x << ", y: " << waypoints[path[i]].y << std::endl;
        //     total_time += distance(current_x, current_y, waypoints[path[i]].x, waypoints[path[i]].y) / SPEED;
        //     total_time += 10; // Stop for 10 seconds at each waypoint
        //     std::cout << "total time: " << total_time << std::endl;
        //     current_x = waypoints[path[i]].x;
        //     current_y = waypoints[path[i]].y;
        // }
        total_time = cost;

        total_time += 10;

        return total_time;
    }

    double heuristic(int x1, int y1, int x2, int y2)
    {
        return distance(x1, y1, x2, y2) / SPEED + 10;
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
        std::cout << "file: " << filePath << std::endl;
        while (input >> numWaypoints && numWaypoints != 0)
        {
            std::vector<Waypoint> waypoints;
            waypoints.push_back({0, 0, 0});
            for (int j = 0; j < numWaypoints; ++j)
            {
                Waypoint wp;
                input >> wp.x >> wp.y >> wp.penalty;
                // std::cout << "x: " << wp.x << ", y: " << wp.y << ", pen: " << wp.penalty << std::endl;
                waypoints.push_back(wp);
            }
            waypoints.push_back({100, 100, 0});
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