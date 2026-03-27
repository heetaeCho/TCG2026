#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "catch_reporter_multi.hpp"

#include "catch_interfaces_reporter.hpp"



using namespace Catch;

using testing::_;

using testing::MockFunction;



class MockEventListener : public IEventListener {

public:

    MOCK_METHOD(void, testCaseStarting, (const TestCaseInfo & testInfo), (override));

};



class MultiReporterTest_796 : public ::testing::Test {

protected:

    MultiReporter multiReporter;

    std::vector<IEventListenerPtr> listeners;

    NiceMock<MockEventListener> mockListener;



    void SetUp() override {

        listeners.push_back(IEventListenerPtr(&mockListener, [](IEventListener*){}));

        for (auto& listener : listeners) {

            multiReporter.addListener(std::move(listener));

        }

    }

};



TEST_F(MultiReporterTest_796, TestCaseStarting_CallsAllListeners_796) {

    TestCaseInfo testInfo("ClassName", NameAndTags("TestName", ""), SourceLineInfo("", 0));



    EXPECT_CALL(mockListener, testCaseStarting(_)).Times(1);



    multiReporter.testCaseStarting(testInfo);

}



TEST_F(MultiReporterTest_796, NoListeners_NoCrash_796) {

    MultiReporter emptyMultiReporter;

    TestCaseInfo testInfo("ClassName", NameAndTags("TestName", ""), SourceLineInfo("", 0));



    EXPECT_NO_THROW(emptyMultiReporter.testCaseStarting(testInfo));

}



TEST_F(MultiReporterTest_796, MultipleListeners_AllCalled_796) {

    MultiReporter multiReporterWithMultipleListeners;

    NiceMock<MockEventListener> mockListener1;

    NiceMock<MockEventListener> mockListener2;



    auto listenerPtr1 = IEventListenerPtr(&mockListener1, [](IEventListener*){});

    auto listenerPtr2 = IEventListenerPtr(&mockListener2, [](IEventListener*){});



    multiReporterWithMultipleListeners.addListener(std::move(listenerPtr1));

    multiReporterWithMultipleListeners.addListener(std::move(listenerPtr2));



    TestCaseInfo testInfo("ClassName", NameAndTags("TestName", ""), SourceLineInfo("", 0));



    EXPECT_CALL(mockListener1, testCaseStarting(_)).Times(1);

    EXPECT_CALL(mockListener2, testCaseStarting(_)).Times(1);



    multiReporterWithMultipleListeners.testCaseStarting(testInfo);

}
