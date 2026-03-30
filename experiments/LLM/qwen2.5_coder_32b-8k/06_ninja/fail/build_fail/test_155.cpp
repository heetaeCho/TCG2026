#include <gmock/gmock.h>

#include <gtest/gtest.h>



using ::testing::Return;

using ::testing::_;



// Mocking ParseSelfCGroup and ParseMountInfo functions

class MockSystemParser {

public:

    MOCK_CONST_METHOD0(ParseSelfCGroup, std::string());

    MOCK_CONST_METHOD1(ParseMountInfo, std::map<std::string, std::string>(const std::string&));

};



extern "C" {

    // Redirecting the actual calls to the mock object

    MockSystemParser* g_mockSystemParser = nullptr;



    std::string ParseSelfCGroup() {

        return g_mockSystemParser->ParseSelfCGroup();

    }



    std::map<std::string, std::string> ParseMountInfo(const std::string& subsystems) {

        return g_mockSystemParser->ParseMountInfo(subsystems);

    }

}



// Mocking ParseCgroupV1 and ParseCgroupV2 functions

int MockParseCgroupV1(const std::string& cgroupPath) {

    if (cgroupPath == "cpu_path") return 4;

    return -1;

}



int MockParseCgroupV2(const std::string& cgroupPath) {

    if (cgroupPath == "cgroup2_path") return 8;

    return -1;

}



extern "C" {

    int ParseCgroupV1(const std::string& cgroupPath) {

        return MockParseCgroupV1(cgroupPath);

    }



    int ParseCgroupV2(const std::string& cgroupPath) {

        return MockParseCgroupV2(cgroupPath);

    }

}



class ParseCPUFromCGroupTest_155 : public ::testing::Test {

protected:

    void SetUp() override {

        mockSystemParser = new MockSystemParser();

        g_mockSystemParser = mockSystemParser;

    }



    void TearDown() override {

        delete mockSystemParser;

        g_mockSystemParser = nullptr;

    }



    MockSystemParser* mockSystemParser;

};



TEST_F(ParseCPUFromCGroupTest_155, Cgroup2Exists_ReturnsParsedValue_155) {

    EXPECT_CALL(*mockSystemParser, ParseSelfCGroup()).WillOnce(Return("cgroup2_path"));

    std::map<std::string, std::string> cgroups = {{"cgroup2", "cgroup2_path"}};

    EXPECT_CALL(*mockSystemParser, ParseMountInfo(_)).WillOnce(Return(cgroups));



    int result = ParseCPUFromCGroup();

    EXPECT_EQ(result, 8);

}



TEST_F(ParseCPUFromCGroupTest_155, CPUExists_ReturnsParsedValue_155) {

    EXPECT_CALL(*mockSystemParser, ParseSelfCGroup()).WillOnce(Return("cpu_path"));

    std::map<std::string, std::string> cgroups = {{"cpu", "cpu_path"}};

    EXPECT_CALL(*mockSystemParser, ParseMountInfo(_)).WillOnce(Return(cgroups));



    int result = ParseCPUFromCGroup();

    EXPECT_EQ(result, 4);

}



TEST_F(ParseCPUFromCGroupTest_155, NeitherCgroup2NorCPUPresent_ReturnsNegativeOne_155) {

    EXPECT_CALL(*mockSystemParser, ParseSelfCGroup()).WillOnce(Return("some_path"));

    std::map<std::string, std::string> cgroups = {{"other", "other_path"}};

    EXPECT_CALL(*mockSystemParser, ParseMountInfo(_)).WillOnce(Return(cgroups));



    int result = ParseCPUFromCGroup();

    EXPECT_EQ(result, -1);

}



TEST_F(ParseCPUFromCGroupTest_155, EmptySubsystems_ReturnsNegativeOne_155) {

    EXPECT_CALL(*mockSystemParser, ParseSelfCGroup()).WillOnce(Return(""));

    std::map<std::string, std::string> cgroups = {};

    EXPECT_CALL(*mockSystemParser, ParseMountInfo(_)).WillOnce(Return(cgroups));



    int result = ParseCPUFromCGroup();

    EXPECT_EQ(result, -1);

}



TEST_F(ParseCPUFromCGroupTest_155, BothCgroup2AndCPUPresent_ReturnsCgroup2ParsedValue_155) {

    EXPECT_CALL(*mockSystemParser, ParseSelfCGroup()).WillOnce(Return("cgroup2_path cpu_path"));

    std::map<std::string, std::string> cgroups = {{"cgroup2", "cgroup2_path"}, {"cpu", "cpu_path"}};

    EXPECT_CALL(*mockSystemParser, ParseMountInfo(_)).WillOnce(Return(cgroups));



    int result = ParseCPUFromCGroup();

    EXPECT_EQ(result, 8);

}
