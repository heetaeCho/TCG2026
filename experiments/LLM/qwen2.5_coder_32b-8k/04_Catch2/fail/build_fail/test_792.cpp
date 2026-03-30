#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "catch2/reporters/catch_reporter_multi.hpp"

#include "catch2/interfaces/catch_interfaces_reporter.hpp"



using namespace Catch;

using ::testing::_;

using ::testing::NiceMock;



class MockEventListener : public IEventListener {

public:

    MOCK_METHOD(void, benchmarkStarting, (const BenchmarkInfo &benchmarkInfo), (override));

};



class MultiReporterTest_792 : public ::testing::Test {

protected:

    MultiReporter multiReporter;

    NiceMock<MockEventListener> mockListener1;

    NiceMock<MockEventListener> mockListener2;



    void SetUp() override {

        multiReporter.addListener(IEventListenerPtr(new MockEventListener(mockListener1)));

        multiReporter.addListener(IEventListenerPtr(new MockEventListener(mockListener2)));

    }

};



TEST_F(MultiReporterTest_792, BenchmarkStarting_DelegatesToAllListeners_792) {

    BenchmarkInfo benchmarkInfo;

    benchmarkInfo.estimatedDuration = 0.5;

    benchmarkInfo.iterations = 100;

    benchmarkInfo.samples = 3;

    benchmarkInfo.resamples = 2;

    benchmarkInfo.clockResolution = 0.001;

    benchmarkInfo.clockCost = 0.0001;



    EXPECT_CALL(mockListener1, benchmarkStarting(_)).WillOnce(::testing::SetArgReferee<0>(benchmarkInfo));

    EXPECT_CALL(mockListener2, benchmarkStarting(_)).WillOnce(::testing::SetArgReferee<0>(benchmarkInfo));



    multiReporter.benchmarkStarting(benchmarkInfo);

}



TEST_F(MultiReporterTest_792, BenchmarkStarting_NoListeners_DoesNotCrash_792) {

    MultiReporter emptyMultiReporter;

    BenchmarkInfo benchmarkInfo;



    EXPECT_NO_THROW(emptyMultiReporter.benchmarkStarting(benchmarkInfo));

}
