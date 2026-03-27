#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "./TestProjects/Catch2/src/catch2/interfaces/catch_interfaces_reporter.hpp"

#include "./TestProjects/Catch2/src/catch2/reporters/catch_reporter_multi.hpp"



using namespace Catch;

using ::testing::MockFunction;



class MockEventListener : public IEventListener {

public:

    MOCK_METHOD(void, noMatchingTestCases, (StringRef unmatchedSpec), (override));

};



class MultiReporterTest_788 : public ::testing::Test {

protected:

    MultiReporter multiReporter;

    std::vector<IEventListenerPtr> listeners;

    NiceMock<MockEventListener> mockListener1;

    NiceMock<MockEventListener> mockListener2;



    void SetUp() override {

        listeners.push_back(IEventListenerPtr(new MockEventListener(mockListener1)));

        listeners.push_back(IEventListenerPtr(new MockEventListener(mockListener2)));



        for (auto& listener : listeners) {

            multiReporter.addListener(std::move(listener));

        }

    }

};



TEST_F(MultiReporterTest_788, NoMatchingTestCases_CallsAllListeners_788) {

    StringRef unmatchedSpec("unmatched_spec");



    EXPECT_CALL(mockListener1, noMatchingTestCases(unmatchedSpec)).Times(1);

    EXPECT_CALL(mockListener2, noMatchingTestCases(unmatchedSpec)).Times(1);



    multiReporter.noMatchingTestCases(unmatchedSpec);

}



TEST_F(MultiReporterTest_788, NoMatchingTestCases_EmptyString_788) {

    StringRef unmatchedSpec("");



    EXPECT_CALL(mockListener1, noMatchingTestCases(unmatchedSpec)).Times(1);

    EXPECT_CALL(mockListener2, noMatchingTestCases(unmatchedSpec)).Times(1);



    multiReporter.noMatchingTestCases(unmatchedSpec);

}



TEST_F(MultiReporterTest_788, NoMatchingTestCases_LongString_788) {

    std::string longString(1000, 'a');

    StringRef unmatchedSpec(longString.c_str());



    EXPECT_CALL(mockListener1, noMatchingTestCases(unmatchedSpec)).Times(1);

    EXPECT_CALL(mockListener2, noMatchingTestCases(unmatchedSpec)).Times(1);



    multiReporter.noMatchingTestCases(unmatchedSpec);

}
