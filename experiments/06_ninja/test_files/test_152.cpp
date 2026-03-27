#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include <fstream>

#include "util.h"



using namespace testing;

using namespace std;



class ParseSelfCGroupTest_152 : public ::testing::Test {

protected:

    void SetUp() override {

        // Redirect cin to capture input if needed

        test_cgroup_file = "/tmp/test_cgroup_152";

        ofstream file(test_cgroup_file);

        file.close();

        orig_cgroup_file = "./TestProjects/ninja/src/util.cc";

        ::testing::internal::CaptureStdout();

    }



    void TearDown() override {

        // Restore original state if needed

        remove(test_cgroup_file.c_str());

        ::testing::internal::GetCapturedStdout(); // Clear captured stdout

    }



    string test_cgroup_file;

    string orig_cgroup_file;

};



TEST_F(ParseSelfCGroupTest_152, EmptyFileReturnsEmptyMap_152) {

    map<string, CGroupSubSys> result = ParseSelfCGroup();

    EXPECT_TRUE(result.empty());

}



TEST_F(ParseSelfCGroupTest_152, SingleValidLineCreatesOneEntry_152) {

    ofstream file(test_cgroup_file);

    file << "0::/user.slice/user-1000.slice/session-3.scope\n";

    file.close();

    

    map<string, CGroupSubSys> result = ParseSelfCGroup();

    EXPECT_EQ(result.size(), 1);

}



TEST_F(ParseSelfCGroupTest_152, MultipleValidLinesCreateMultipleEntries_152) {

    ofstream file(test_cgroup_file);

    file << "0::/user.slice/user-1000.slice/session-3.scope\n";

    file << "1:name=systemd:/\n";

    file.close();

    

    map<string, CGroupSubSys> result = ParseSelfCGroup();

    EXPECT_EQ(result.size(), 2);

}



TEST_F(ParseSelfCGroupTest_152, InvalidLineIgnored_152) {

    ofstream file(test_cgroup_file);

    file << "invalid line\n";

    file.close();

    

    map<string, CGroupSubSys> result = ParseSelfCGroup();

    EXPECT_TRUE(result.empty());

}



TEST_F(ParseSelfCGroupTest_152, FileNotExistsReturnsEmptyMap_152) {

    remove(test_cgroup_file.c_str());

    

    map<string, CGroupSubSys> result = ParseSelfCGroup();

    EXPECT_TRUE(result.empty());

}

```


