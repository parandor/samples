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
                    double time_to_next = distance(waypoints[current.idx].x, waypoints[current.idx].y, waypoints[i].x, waypoints[i].y) / SPEED + 10;
                    double backtrack_cost = getBackTrackPenalty(waypoints, current.idx, i, i - 2);
                    double skipped_cost = getSkippedTimeMod(current.path, waypoints, i);
                    double new_cost = current.cost + time_to_next + skipped_cost - backtrack_cost;
                    if (!dp.count(i) || new_cost < dp[i])
                    {
                        dp[i] = new_cost;
                        vector<int> new_path = current.path;
                        new_path.push_back(i);
                        pq.push({waypoints[i].x, waypoints[i].y, i, new_cost, new_path});
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
        for (int i = 0; i < waypoints.size(); ++i)
        {
            if (i > next_index)
            {
                continue;
            }
            if (find(optimal_path.begin(), optimal_path.end(), i) == optimal_path.end())
            {
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

        for (int i = 0; i < path.size(); ++i)
        {
            total_time += distance(current_x, current_y, waypoints[path[i]].x, waypoints[path[i]].y) / SPEED + 10;
            current_x = waypoints[path[i]].x;
            current_y = waypoints[path[i]].y;
        }
        total_time -= 10; // 100,100 is double counted, so deduct 10 seconds

        return total_time + skipped_time;
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

    struct WaypointData
    {
        std::vector<Waypoint> waypoints;
        float expected_lowest_time = 0.0;
    };

    struct TestInfo
    {
        fs::path filePath;
        std::vector<WaypointData> testCases;
    };

    std::vector<TestInfo> testInfos;

private:
    static void replaceString(std::string &str, const std::string &target, const std::string &replacement)
    {
        size_t startPos = 0;
        while ((startPos = str.find(target, startPos)) != std::string::npos)
        {
            str.replace(startPos, target.length(), replacement);
            startPos += replacement.length();
        }
    }

    void ReadTestCases(std::ifstream &input, const fs::path &filePath)
    {
        int numWaypoints;
        TestInfo info;
        info.filePath = filePath;
        std::cout << "file: " << filePath << std::endl;
        while (input >> numWaypoints && numWaypoints != 0)
        {
            WaypointData data;
            data.waypoints.push_back({0, 0, 0});
            for (int j = 0; j < numWaypoints; ++j)
            {
                Waypoint wp;
                input >> wp.x >> wp.y >> wp.penalty;
                data.waypoints.push_back(wp);
            }
            data.waypoints.push_back({100, 100, 0});
            info.testCases.push_back(data);
        }

        std::string sample_output = filePath;
        WaypointTest::replaceString(sample_output, "sample_input", "sample_output");

        std::ifstream output(sample_output);
        if (output.is_open())
        {
            int i = 0;
            while (output >> info.testCases[i].expected_lowest_time)
            {
                i++;
            }
            output.close();
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
        for (const auto &data : info.testCases)
        {
            for (const auto &wp : data.waypoints)
            {
                EXPECT_GE(wp.x, 0);
                EXPECT_GE(wp.y, 0);
                EXPECT_GE(wp.penalty, 0);
                // Add more specific tests if needed
            }
        }
    }
}

template <typename T>
T roundDifference(T &difference)
{
    const T threshold = 0.001; // Threshold for considering difference as zero
    if (std::abs(difference) < threshold)
    {
        difference = 0.000;
    }
    return difference;
}

TEST_F(WaypointTest, LowestTimeTest)
{
    Optimizer optimizer;
    for (const auto &info : testInfos)
    {
        for (const auto &data : info.testCases)
        {
            double lowestTime = optimizer.findLowestTime(data.waypoints);
            double diff = abs(lowestTime - data.expected_lowest_time);
            double rounded = roundDifference(diff);
            std::string result = ((int)rounded) == 0 ? "PASS" : "FAIL";
            std::cout << "For file " << info.filePath << ": optimized lowest time: " << lowestTime << " sec, expected: "
                      << data.expected_lowest_time << " sec. Diff (sec): " << rounded << ", " << result << std::endl;
        }
    }
}

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}