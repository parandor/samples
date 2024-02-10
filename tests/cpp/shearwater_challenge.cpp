#include <gtest/gtest.h>
#include <fstream>
#include <vector>
#include <filesystem>
#include <cmath>

using namespace std;
namespace fs = std::filesystem;

// Structure to represent a waypoint
struct Waypoint
{
    int x, y;    // Coordinates of the waypoint
    int penalty; // Penalty for missing delivery
};

// Structure to represent a solution
struct Solution {
    float time; // Time to deliver all packages
    int penalty; // Total penalty incurred
};

class Solver {
public:
    Solution solve(vector<Waypoint>& waypoints) {
        int n = waypoints.size();
        vector<Solution> dp(n);

        dp[0].time = sqrt(waypoints[0].x * waypoints[0].x + waypoints[0].y * waypoints[0].y) / 2 + 10;
        dp[0].penalty = waypoints[0].penalty;

        for (int i = 1; i < n; ++i) {
            int distance = sqrt((waypoints[i].x - waypoints[i - 1].x) * (waypoints[i].x - waypoints[i - 1].x)
                                + (waypoints[i].y - waypoints[i - 1].y) * (waypoints[i].y - waypoints[i - 1].y));
            dp[i].time = dp[i - 1].time + distance / 2 + 10;
            dp[i].penalty = dp[i - 1].penalty + waypoints[i].penalty;

            // Check if skipping the current waypoint leads to a better solution
            if (i >= 2) {
                dp[i].time = min(dp[i].time, dp[i - 2].time + distance / 2 + 10);
                dp[i].penalty = min(dp[i].penalty, dp[i - 2].penalty);
            }
        }

        // Adding the time to reach the final point
        int last_distance = sqrt(waypoints[n - 1].x * waypoints[n - 1].x + waypoints[n - 1].y * waypoints[n - 1].y);
        dp[n - 1].time += last_distance / 2;

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
            // testCase.printWaypoints();
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
