#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "catch2/reporters/catch_reporter_multi.hpp"

#include "catch2/interfaces/catch_interfaces_reporter.hpp"

#include "catch2/catch_test_case_info.hpp"



using namespace Catch;

using ::testing::MockFunction;



class MockEventListener : public IEventListener {

public:

    MOCK_METHOD(void, skipTest, (const TestCaseInfo & testInfo), (override));

};



class MultiReporterTest_805 : public ::testing::Test {

protected:

    MultiReporter multiReporter;

    std::vector<IEventListenerPtr> listeners;

    NiceMock<MockEventListener> mockListener;



    void SetUp() override {

        listeners.push_back(IEventListenerPtr{new NiceMock<MockEventListener>(nullptr)});

        multiReporter.addListener(std::move(listeners[0]));

    }

};



TEST_F(MultiReporterTest_805, SkipTest_CallsSkipTestOnAllListeners_805) {

    TestCaseInfo testInfo("ClassName", NameAndTags{"Name", ""}, SourceLineInfo{"file.cpp", 42});

    

    EXPECT_CALL(mockListener, skipTest(testInfo)).Times(1);

    multiReporter.skipTest(testInfo);

}



TEST_F(MultiReporterTest_805, SkipTest_NoListeners_NoCrash_805) {

    TestCaseInfo testInfo("ClassName", NameAndTags{"Name", ""}, SourceLineInfo{"file.cpp", 42});

    

    multiReporter = MultiReporter(); // Clear listeners

    multiReporter.skipTest(testInfo);

}



TEST_F(MultiReporterTest_805, SkipTest_MultipleListeners_AllCalled_805) {

    NiceMock<MockEventListener> mockListener2;

    multiReporter.addListener(IEventListenerPtr{new NiceMock<MockEventListener>(nullptr)});

    

    TestCaseInfo testInfo("ClassName", NameAndTags{"Name", ""}, SourceLineInfo{"file.cpp", 42});

    

    EXPECT_CALL(mockListener, skipTest(testInfo)).Times(1);

    EXPECT_CALL(mockListener2, skipTest(testInfo)).Times(1);

    multiReporter.skipTest(testInfo);

}
