#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "catch2/reporters/catch_reporter_multi.hpp"

#include "catch2/interfaces/catch_interfaces_reporter.hpp"



using namespace Catch;

using namespace testing;



class MockEventListener : public IEventListener {

public:

    MOCK_METHOD(void, listTests, (const std::vector<TestCaseHandle>& tests), (override));

};



class MultiReporterTest_808 : public Test {

protected:

    MultiReporter reporter;

    NiceMock<MockEventListener> mockListener1;

    NiceMock<MockEventListener> mockListener2;



    void SetUp() override {

        reporter.addListener(IEventListenerPtr(&mockListener1, [](IEventListener*){}));

        reporter.addReporter(IEventListenerPtr(&mockListener2, [](IEventListener*){}));

    }

};



TEST_F(MultiReporterTest_808, ListTests_CallsAllListeners_NormalOperation_808) {

    std::vector<TestCaseHandle> tests;

    EXPECT_CALL(mockListener1, listTests(tests)).Times(1);

    EXPECT_CALL(mockListener2, listTests(tests)).Times(1);



    reporter.listTests(tests);

}



TEST_F(MultiReporterTest_808, ListTests_CallsAllListeners_EmptyTests_808) {

    std::vector<TestCaseHandle> emptyTests;

    EXPECT_CALL(mockListener1, listTests(emptyTests)).Times(1);

    EXPECT_CALL(mockListener2, listTests(emptyTests)).Times(1);



    reporter.listTests(emptyTests);

}



TEST_F(MultiReporterTest_808, ListTests_CallsAllListeners_SingleTest_808) {

    std::vector<TestCaseHandle> singleTest{TestCaseHandle()};

    EXPECT_CALL(mockListener1, listTests(singleTest)).Times(1);

    EXPECT_CALL(mockListener2, listTests(singleTest)).Times(1);



    reporter.listTests(singleTest);

}



TEST_F(MultiReporterTest_808, ListTests_CallsAllListeners_MultipleTests_808) {

    std::vector<TestCaseHandle> multipleTests{TestCaseHandle(), TestCaseHandle()};

    EXPECT_CALL(mockListener1, listTests(multipleTests)).Times(1);

    EXPECT_CALL(mockListener2, listTests(multipleTests)).Times(1);



    reporter.listTests(multipleTests);

}
