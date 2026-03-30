#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include <catch2/reporters/catch_reporter_json.hpp>

#include <vector>



using namespace Catch;

using ::testing::_;

using ::testing::MockFunction;



class JsonReporterTest : public ::testing::Test {

protected:

    JsonReporter jsonReporter{ReporterConfig{}};

    std::ostringstream oss;

    std::vector<TestCaseHandle> testCases;



    void SetUp() override {

        // Initialize any necessary objects or mocks here

    }

};



TEST_F(JsonReporterTest_876, ListTests_EmptyList_DoesNotWriteAnything_876) {

    jsonReporter.listTests({});

    EXPECT_EQ(oss.str(), "");

}



TEST_F(JsonReporterTest_876, ListTests_SingleTestCase_WritesCorrectJson_876) {

    TestCaseInfo testCaseInfo{"TestClass", NameAndTags{"TestName"}, SourceLineInfo{"file.cpp", 1}};

    TestCaseHandle testCaseHandle{&testCaseInfo, nullptr};

    testCases.push_back(testCaseHandle);



    jsonReporter.listTests(testCases);

    std::string expectedOutput = R"({"tests":[{"name":"TestName","class-name":"TestClass","tags":[],"filename":"file.cpp","line":1}]})";

    EXPECT_EQ(oss.str(), expectedOutput);

}



TEST_F(JsonReporterTest_876, ListTests_MultipleTestsWithTags_WritesCorrectJson_876) {

    TestCaseInfo testCaseInfo1{"TestClass1", NameAndTags{"TestName1"}, SourceLineInfo{"file1.cpp", 10}};

    TestCaseInfo testCaseInfo2{"TestClass2", NameAndTags{"TestName2"}, SourceLineInfo{"file2.cpp", 20}};



    Tag tag1{"tag1"};

    Tag tag2{"tag2"};

    testCaseInfo1.tags.push_back(tag1);

    testCaseInfo2.tags.push_back(tag2);



    TestCaseHandle testCaseHandle1{&testCaseInfo1, nullptr};

    TestCaseHandle testCaseHandle2{&testCaseInfo2, nullptr};

    testCases.push_back(testCaseHandle1);

    testCases.push_back(testCaseHandle2);



    jsonReporter.listTests(testCases);

    std::string expectedOutput = R"({"tests":[{"name":"TestName1","class-name":"TestClass1","tags":["tag1"],"filename":"file1.cpp","line":10},{"name":"TestName2","class-name":"TestClass2","tags":["tag2"],"filename":"file2.cpp","line":20}]})";

    EXPECT_EQ(oss.str(), expectedOutput);

}



TEST_F(JsonReporterTest_876, ListTests_TestWithEmptyClassName_WritesCorrectJson_876) {

    TestCaseInfo testCaseInfo{"", NameAndTags{"TestName"}, SourceLineInfo{"file.cpp", 1}};

    TestCaseHandle testCaseHandle{&testCaseInfo, nullptr};

    testCases.push_back(testCaseHandle);



    jsonReporter.listTests(testCases);

    std::string expectedOutput = R"({"tests":[{"name":"TestName","class-name":"","tags":[],"filename":"file.cpp","line":1}]})";

    EXPECT_EQ(oss.str(), expectedOutput);

}



TEST_F(JsonReporterTest_876, ListTests_TestWithNoTags_WritesCorrectJson_876) {

    TestCaseInfo testCaseInfo{"TestClass", NameAndTags{"TestName"}, SourceLineInfo{"file.cpp", 1}};

    TestCaseHandle testCaseHandle{&testCaseInfo, nullptr};

    testCases.push_back(testCaseHandle);



    jsonReporter.listTests(testCases);

    std::string expectedOutput = R"({"tests":[{"name":"TestName","class-name":"TestClass","tags":[],"filename":"file.cpp","line":1}]})";

    EXPECT_EQ(oss.str(), expectedOutput);

}
