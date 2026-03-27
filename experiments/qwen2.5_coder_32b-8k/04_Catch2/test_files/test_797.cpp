#include <gmock/gmock.h>

#include <gtest/gtest.h>

#include "catch2/reporters/catch_reporter_multi.hpp"

#include "catch2/interfaces/catch_interfaces_reporter.hpp"



using namespace Catch;

using ::testing::_;

using ::testing::NiceMock;



class MockEventListener : public IEventListener {

public:

    MOCK_METHOD(void, testCasePartialStarting, (const TestCaseInfo& testInfo, uint64_t partNumber), (override));

};



class MultiReporterTest_797 : public ::testing::Test {

protected:

    MultiReporter multiReporter;

    NiceMock<MockEventListener> mockListener1;

    NiceMock<MockEventListener> mockListener2;



    void SetUp() override {

        multiReporter.addListener(IEventListenerPtr(new NiceMock<MockEventListener>(mockListener1)));

        multiReporter.addListener(IEventListenerPtr(new NiceMock<MockEventListener>(mockListener2)));

    }

};



TEST_F(MultiReporterTest_797, TestCasePartialStarting_ForwardsToAllListeners_797) {

    TestCaseInfo testInfo("ClassName", NameAndTags("TestCaseName"), SourceLineInfo(__FILE__, __LINE__));

    uint64_t partNumber = 1;



    EXPECT_CALL(mockListener1, testCasePartialStarting(testInfo, partNumber));

    EXPECT_CALL(mockListener2, testCasePartialStarting(testInfo, partNumber));



    multiReporter.testCasePartialStarting(testInfo, partNumber);

}



TEST_F(MultiReporterTest_797, TestCasePartialStarting_NoListeners_NoCrash_797) {

    MultiReporter emptyMultiReporter; // No listeners added

    TestCaseInfo testInfo("ClassName", NameAndTags("TestCaseName"), SourceLineInfo(__FILE__, __LINE__));

    uint64_t partNumber = 1;



    EXPECT_NO_THROW(emptyMultiReporter.testCasePartialStarting(testInfo, partNumber));

}



TEST_F(MultiReporterTest_797, TestCasePartialStarting_PartNumberZero_ValidBoundary_797) {

    TestCaseInfo testInfo("ClassName", NameAndTags("TestCaseName"), SourceLineInfo(__FILE__, __LINE__));

    uint64_t partNumber = 0;



    EXPECT_CALL(mockListener1, testCasePartialStarting(testInfo, partNumber));

    EXPECT_CALL(mockListener2, testCasePartialStarting(testInfo, partNumber));



    multiReporter.testCasePartialStarting(testInfo, partNumber);

}



TEST_F(MultiReporterTest_797, TestCasePartialStarting_PartNumberLarge_ValidBoundary_797) {

    TestCaseInfo testInfo("ClassName", NameAndTags("TestCaseName"), SourceLineInfo(__FILE__, __LINE__));

    uint64_t partNumber = UINT64_MAX;



    EXPECT_CALL(mockListener1, testCasePartialStarting(testInfo, partNumber));

    EXPECT_CALL(mockListener2, testCasePartialStarting(testInfo, partNumber));



    multiReporter.testCasePartialStarting(testInfo, partNumber);

}



TEST_F(MultiReporterTest_797, TestCasePartialStarting_EmptyClassName_ValidBoundary_797) {

    TestCaseInfo testInfo("", NameAndTags("TestCaseName"), SourceLineInfo(__FILE__, __LINE__));

    uint64_t partNumber = 1;



    EXPECT_CALL(mockListener1, testCasePartialStarting(testInfo, partNumber));

    EXPECT_CALL(mockListener2, testCasePartialStarting(testInfo, partNumber));



    multiReporter.testCasePartialStarting(testInfo, partNumber);

}



TEST_F(MultiReporterTest_797, TestCasePartialStarting_EmptyTestCaseName_ValidBoundary_797) {

    TestCaseInfo testInfo("ClassName", NameAndTags(""), SourceLineInfo(__FILE__, __LINE__));

    uint64_t partNumber = 1;



    EXPECT_CALL(mockListener1, testCasePartialStarting(testInfo, partNumber));

    EXPECT_CALL(mockListener2, testCasePartialStarting(testInfo, partNumber));



    multiReporter.testCasePartialStarting(testInfo, partNumber);

}
