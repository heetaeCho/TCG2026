#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "./TestProjects/ninja/src/util.cc"



using ::testing::_;

using ::testing::Return;



class ParseMountInfoTest_151 : public ::testing::Test {

protected:

    map<string, CGroupSubSys> subsystems;

};



TEST_F(ParseMountInfoTest_151, NormalOperationWithCgroup_151) {

    subsystems["cpu"] = {"0", "cpu", {}};

    subsystems["memory"] = {"1", "memory", {}};



    string mountinfoContent =

        "26 25 8:3 /mnt/cgroups/cpu cpu rw,nosuid,nodev,noexec,relatime shared:7 - cgroup cgroup rw,cpu\n"

        "27 25 8:4 /mnt/cgroups/memory memory rw,nosuid,nodev,noexec,relatime shared:8 - cgroup cgroup rw,memory\n";



    std::istringstream iss(mountinfoContent);

    testing::internal::CaptureStdout();

    std::streambuf* orig = std::cin.rdbuf(iss.rdbuf());



    map<string, string> result = ParseMountInfo(subsystems);



    std::cin.rdbuf(orig);

    std::string output = testing::internal::GetCapturedStdout();



    EXPECT_EQ(result["cpu"], "/mnt/cgroups/cpu");

    EXPECT_EQ(result["memory"], "/mnt/cgroups/memory");

}



TEST_F(ParseMountInfoTest_151, NormalOperationWithCgroup2_151) {

    subsystems[""] = {"0", "/", {}};



    string mountinfoContent =

        "28 25 8:5 /mnt/cgroups2 cgroup2 rw,nosuid,nodev,noexec,relatime shared:9 - cgroup2 cgroup2 rw\n";



    std::istringstream iss(mountinfoContent);

    testing::internal::CaptureStdout();

    std::streambuf* orig = std::cin.rdbuf(iss.rdbuf());



    map<string, string> result = ParseMountInfo(subsystems);



    std::cin.rdbuf(orig);

    std::string output = testing::internal::GetCapturedStdout();



    EXPECT_EQ(result["cgroup2"], "/mnt/cgroups2");

}



TEST_F(ParseMountInfoTest_151, BoundaryConditionEmptyMountinfo_151) {

    string mountinfoContent = "";



    std::istringstream iss(mountinfoContent);

    testing::internal::CaptureStdout();

    std::streambuf* orig = std::cin.rdbuf(iss.rdbuf());



    map<string, string> result = ParseMountInfo(subsystems);



    std::cin.rdbuf(orig);

    std::string output = testing::internal::GetCapturedStdout();



    EXPECT_TRUE(result.empty());

}



TEST_F(ParseMountInfoTest_151, BoundaryConditionNoMatchingSubsys_151) {

    subsystems["cpu"] = {"0", "cpu", {}};



    string mountinfoContent =

        "26 25 8:3 /mnt/cgroups/cpu cpu rw,nosuid,nodev,noexec,relatime shared:7 - cgroup cgroup rw,memory\n";



    std::istringstream iss(mountinfoContent);

    testing::internal::CaptureStdout();

    std::streambuf* orig = std::cin.rdbuf(iss.rdbuf());



    map<string, string> result = ParseMountInfo(subsystems);



    std::cin.rdbuf(orig);

    std::string output = testing::internal::GetCapturedStdout();



    EXPECT_TRUE(result.empty());

}



TEST_F(ParseMountInfoTest_151, ExceptionalCaseFileNotFound_151) {

    subsystems["cpu"] = {"0", "cpu", {}};



    // Simulate file not found by redirecting cin to an empty stream

    std::istringstream iss("");

    testing::internal::CaptureStdout();

    std::streambuf* orig = std::cin.rdbuf(iss.rdbuf());



    map<string, string> result = ParseMountInfo(subsystems);



    std::cin.rdbuf(orig);

    std::string output = testing::internal::GetCapturedStdout();



    EXPECT_TRUE(result.empty());

}
