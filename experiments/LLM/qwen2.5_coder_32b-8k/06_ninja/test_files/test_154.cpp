#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include <string>

#include <fstream>



// Assuming ParseCgroupV2 is declared in a header file named util.h

#include "util.h"



using namespace std;



class ParseCgroupV2Test_154 : public ::testing::Test {

protected:

    void SetUp() override {

        // Create a temporary directory for test files

        temp_dir = testing::TempDir();

        path = temp_dir + "/test_cgroup";

        fs::create_directories(path);

    }



    void TearDown() override {

        // Remove the temporary directory and its contents

        fs::remove_all(path);

    }



    string CreateTestFile(const string& content) {

        string file_path = path + "/cpu.max";

        ofstream cpu_max(file_path);

        if (cpu_max.is_open()) {

            cpu_max << content;

            cpu_max.close();

        }

        return file_path;

    }



    std::string temp_dir;

    std::string path;

};



TEST_F(ParseCgroupV2Test_154, ValidQuotaAndPeriod_154) {

    CreateTestFile("1000 500");

    EXPECT_EQ(ParseCgroupV2(path), 2);

}



TEST_F(ParseCgroupV2Test_154, MaxQuotaNoLimit_154) {

    CreateTestFile("max 500");

    EXPECT_EQ(ParseCgroupV2(path), -1);

}



TEST_F(ParseCgroupV2Test_154, InvalidFilePath_154) {

    string invalid_path = "/nonexistent/cpu.max";

    EXPECT_EQ(ParseCgroupV2(invalid_path.substr(0, invalid_path.size() - 3)), -1);

}



TEST_F(ParseCgroupV2Test_154, EmptyFileContent_154) {

    CreateTestFile("");

    EXPECT_EQ(ParseCgroupV2(path), -1);

}



TEST_F(ParseCgroupV2Test_154, MissingPeriod_154) {

    CreateTestFile("1000");

    EXPECT_EQ(ParseCgroupV2(path), -1);

}



TEST_F(ParseCgroupV2Test_154, NonNumericQuota_154) {

    CreateTestFile("abc 500");

    EXPECT_EQ(ParseCgroupV2(path), -1);

}



TEST_F(ParseCgroupV2Test_154, NonNumericPeriod_154) {

    CreateTestFile("1000 xyz");

    EXPECT_EQ(ParseCgroupV2(path), -1);

}



TEST_F(ParseCgroupV2Test_154, QuotaZero_154) {

    CreateTestFile("0 500");

    EXPECT_EQ(ParseCgroupV2(path), -1);

}



TEST_F(ParseCgroupV2Test_154, PeriodZero_154) {

    CreateTestFile("1000 0");

    EXPECT_EQ(ParseCgroupV2(path), -1);

}



TEST_F(ParseCgroupV2Test_154, LargeNumbersNoOverflow_154) {

    CreateTestFile("9223372036854775807 9223372036854775807");

    EXPECT_EQ(ParseCgroupV2(path), 1);

}



TEST_F(ParseCgroupV2Test_154, LargeNumbersWithPeriodOne_154) {

    CreateTestFile("9223372036854775807 1");

    EXPECT_EQ(ParseCgroupV2(path), -1); // This will cause ERANGE for quota

}
