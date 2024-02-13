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

        while (true) // Loop until all waypoints have been visited
        {
            if (pq.empty())
            {
                break;
            }

            State current = pq.top();
            pq.pop();

            if (visited[current.idx])
            {
                continue;
            }

            visited[current.idx] = true;

            if (current.idx == n - 1) // Check if the ending waypoint has been visited
            {
                optimal_path = current.path;
                break;
            }

            for (int i = 0; i < n; ++i)
            {
                if (!visited[i])
                {
                    // printPath(current.path, waypoints);
                    // cout << "Next wp: " << waypoints[i].x << ", " << waypoints[i].y << endl;
                    double time_to_next = distance(waypoints[current.idx].x, waypoints[current.idx].y, waypoints[i].x, waypoints[i].y) / SPEED + 10;
                    double backtrack_cost = getBackTrackPenalty(waypoints, current.idx, i, i - 2);
                    double skipped_cost = getSkippedTimeMod(current.path, waypoints, i);
                    double new_cost = current.cost + time_to_next + skipped_cost - backtrack_cost;
                    // cout << "New cost: " << new_cost << ", cur cost: " << current.cost << ", next cost: " << time_to_next << ", skip cost: " << skipped_cost << ", dp.count[i]: " << dp.count(i) << ", i: " << i << endl;
                    if (dp.count(i))
                    {
                        // cout << "dp[i]: " << dp[i] << ", newcost: " << new_cost << std::endl;
                    }
                    if (!dp.count(i) || new_cost < dp[i])
                    {
                        /// cout << "dp valid for index: " << i << endl;
                        // cout << "New cost: " << new_cost << ", cur cost: " << current.cost << ", next cost: " << time_to_next << ", skip cost: " << skipped_cost << endl;
                        dp[i] = new_cost;
                        vector<int> new_path = current.path;
                        new_path.push_back(i);
                        // printPath(new_path, waypoints);
                        pq.push({waypoints[i].x, waypoints[i].y, i, new_cost, new_path});
                        // log_q(pq, waypoints);
                    }
                }
            }
        }

        return calculateTotalTime(waypoints, optimal_path);
    }

    void printPath(const vector<int> &path, const vector<Waypoint> &waypoints)
    {
        cout << " PATH:";
        for (int waypoint_index : path)
        {
            cout << " (" << waypoints[waypoint_index].x << "," << waypoints[waypoint_index].y << ")";
        }
        cout << endl;
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

    double getBackTrackPenalty(const vector<Waypoint> &waypoints, const int current, const int next, const int previous)
    {
        if (current < 0 || current >= waypoints.size() || next < 0 || next >= waypoints.size() || previous < 0 || previous >= waypoints.size())
        {
            return 0.0;
        }
        double dist_current = distance(0, 0, waypoints[current].x, waypoints[current].y);
        double dist_next = distance(0, 0, waypoints[next].x, waypoints[next].y);
        double dist_previous = distance(0, 0, waypoints[previous].x, waypoints[previous].y);
        if (dist_next <= dist_current && dist_next >= 0.0)
        {
            return waypoints[next].penalty;
        }
        return 0.0;
    }

    double getSkippedTimeMod(const vector<int> &optimal_path, const vector<Waypoint> &waypoints, const int &next_index)
    {
        double skipped_time = 0.0;
        // printPath(optimal_path, waypoints);
        for (int i = 0; i < waypoints.size(); ++i)
        {
            if (i > next_index)
            {
                continue;
            }
            if (find(optimal_path.begin(), optimal_path.end(), i) == optimal_path.end())
            {
                // cout << "waypoint skipped: " << waypoints[i].x << ", " << waypoints[i].y << ", " << waypoints[i].penalty << endl;
                skipped_time += waypoints[i].penalty;
            }
        }
        return skipped_time - waypoints[next_index].penalty;
    }

    double getSkippedTime(const vector<int> &optimal_path, const vector<Waypoint> &waypoints)
    {
        double skipped_time = 0.0;
        for (int i = 0; i < waypoints.size(); ++i)
        {            
            if (find(optimal_path.begin(), optimal_path.end(), i) == optimal_path.end())
            {
                skipped_time += waypoints[i].penalty;
            }
        }
        return skipped_time;
    }

    double calculateTotalTime(const vector<Waypoint> &waypoints, const vector<int> &path)
    {
        double total_time = 0.0;
        int current_x = 0, current_y = 0;
        auto skipped_time = getSkippedTime(path, waypoints);
        //cout << "final skippedtime: " << skipped_time << endl;

        for (int i = 0; i < path.size(); ++i)
        {
            total_time += distance(current_x, current_y, waypoints[path[i]].x, waypoints[path[i]].y) / SPEED + 10;
            current_x = waypoints[path[i]].x;
            current_y = waypoints[path[i]].y;
        }
        total_time -= 10; // 100,100 is double counted, so deduct 10 seconds

        return total_time + skipped_time;
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