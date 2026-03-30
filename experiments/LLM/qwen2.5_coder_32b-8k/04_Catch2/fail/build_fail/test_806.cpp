#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "./TestProjects/Catch2/src/catch2/reporters/catch_reporter_multi.hpp"

#include "./TestProjects/Catch2/src/catch2/interfaces/catch_interfaces_reporter.hpp"



using namespace Catch;

using ::testing::_;

using ::testing::InvokeWithoutArgs;



class MockIEventListener : public IEventListener {

public:

    MOCK_METHOD(void, listReporters, (const std::vector<ReporterDescription>& descriptions), (override));

};



class MultiReporterTest_806 : public ::testing::Test {

protected:

    MultiReporter multiReporter;

    NiceMock<MockIEventListener> mockListener1;

    NiceMock<MockIEventListener> mockListener2;



    void SetUp() override {

        multiReporter.addListener(IEventListenerPtr(&mockListener1, [](auto*){}));

        multiReporter.addListener(IEventListenerPtr(&mockListener2, [](auto*){}));

    }

};



TEST_F(MultiReporterTest_806, ListReporters_CallsAllListeners_806) {

    std::vector<ReporterDescription> descriptions;

    

    EXPECT_CALL(mockListener1, listReporters(descriptions)).Times(1);

    EXPECT_CALL(mockListener2, listReporters(descriptions)).Times(1);



    multiReporter.listReporters(descriptions);

}



TEST_F(MultiReporterTest_806, ListReporters_EmptyListeners_NoCrash_806) {

    MultiReporter emptyReporter;

    std::vector<ReporterDescription> descriptions;



    EXPECT_NO_THROW(emptyReporter.listReporters(descriptions));

}



TEST_F(MultiReporterTest_806, ListReporters_MultipleCalls_AllListenersCalledEachTime_806) {

    std::vector<ReporterDescription> descriptions1;

    std::vector<ReporterDescription> descriptions2;



    EXPECT_CALL(mockListener1, listReporters(descriptions1)).Times(1);

    EXPECT_CALL(mockListener2, listReporters(descriptions1)).Times(1);



    multiReporter.listReporters(descriptions1);



    EXPECT_CALL(mockListener1, listReporters(descriptions2)).Times(1);

    EXPECT_CALL(mockListener2, listReporters(descriptions2)).Times(1);



    multiReporter.listReporters(descriptions2);

}
