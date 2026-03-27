#include <gtest/gtest.h>

#include <Catch2/reporters/catch_reporter_json.hpp>

#include <Catch2/catch_test_case_info.hpp>



using namespace Catch;

using namespace Catch::JsonReporter;



class JsonReporterTest : public ::testing::Test {

protected:

    ReporterConfig config;

    JsonReporter reporter{CATCH_MOVE(config)};

    TestCaseInfo tcInfo{"TestClass", {"testName"}, SourceLineInfo("filename.cpp", 42)};

};



TEST_F(JsonReporterTest_868, testCaseStarting_CreatesJsonStructure_868) {

    std::ostringstream oss;

    reporter.m_objectWriters.emplace(oss);

    reporter.testCaseStarting(tcInfo);



    EXPECT_FALSE(reporter.m_objectWriters.empty());

}



TEST_F(JsonReporterTest_868, testCaseStarting_WritesNameAndSourceInfo_868) {

    std::ostringstream oss;

    reporter.m_objectWriters.emplace(oss);

    reporter.testCaseStarting(tcInfo);



    std::string output = oss.str();

    EXPECT_NE(output.find("\"name\":\"testName\""), std::string::npos);

    EXPECT_NE(output.find("\"filename\":\"filename.cpp\",\"line\":42"), std::string::npos);

}



TEST_F(JsonReporterTest_868, testCaseStarting_WritesTags_868) {

    tcInfo.tags.push_back(Tag{"tag1"});

    tcInfo.tags.push_back(Tag{"tag2"});



    std::ostringstream oss;

    reporter.m_objectWriters.emplace(oss);

    reporter.testCaseStarting(tcInfo);



    std::string output = oss.str();

    EXPECT_NE(output.find("\"tags\":[\"tag1\",\"tag2\"]"), std::string::npos);

}



TEST_F(JsonReporterTest_868, testCaseStarting_WritesProperties_868) {

    tcInfo.properties = TestCaseProperties::None;



    std::ostringstream oss;

    reporter.m_objectWriters.emplace(oss);

    reporter.testCaseStarting(tcInfo);



    std::string output = oss.str();

    EXPECT_NE(output.find("\"properties\":[]"), std::string::npos);

}



TEST_F(JsonReporterTest_868, testCaseStarting_StartsRunsArray_868) {

    std::ostringstream oss;

    reporter.m_objectWriters.emplace(oss);

    reporter.testCaseStarting(tcInfo);



    std::string output = oss.str();

    EXPECT_NE(output.find("\"runs\":["), std::string::npos);

}



TEST_F(JsonReporterTest_868, testCaseStarting_HandlesEmptyName_868) {

    TestCaseInfo tcInfoWithNoName{"TestClass", {"", "tag1"}, SourceLineInfo("filename.cpp", 42)};

    std::ostringstream oss;

    reporter.m_objectWriters.emplace(oss);

    reporter.testCaseStarting(tcInfoWithNoName);



    std::string output = oss.str();

    EXPECT_NE(output.find("\"name\":\"\""), std::string::npos);

}
