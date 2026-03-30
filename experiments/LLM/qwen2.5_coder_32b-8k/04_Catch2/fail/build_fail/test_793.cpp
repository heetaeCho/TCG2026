#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "./TestProjects/Catch2/src/catch2/reporters/catch_reporter_multi.hpp"

#include "./TestProjects/Catch2/src/catch2/interfaces/catch_interfaces_reporter.hpp"



using namespace Catch;

using ::testing::MockFunction;



class MockEventListener : public IEventListener {

public:

    MOCK_METHOD(void, benchmarkEnded, (const BenchmarkStats<> &benchmarkStats), (override));

};



class MultiReporterTest_793 : public ::testing::Test {

protected:

    MultiReporter multiReporter;

    std::vector<IEventListenerPtr> listeners;

    MockEventListener mockListener;



    void SetUp() override {

        listeners.push_back(std::make_shared<MockEventListener>(mockListener));

        for (auto& listener : listeners) {

            multiReporter.addListener(std::move(listener));

        }

    }



    void TearDown() override {

        listeners.clear();

    }

};



TEST_F(MultiReporterTest_793, BenchmarkEndedForwardsToAllListeners_793) {

    BenchmarkStats<> benchmarkStats;

    EXPECT_CALL(mockListener, benchmarkEnded(::testing::_)).Times(1);

    multiReporter.benchmarkEnded(benchmarkStats);

}



TEST_F(MultiReporterTest_793, BenchmarkEndedNoListeners_793) {

    MultiReporter emptyMultiReporter; // No listeners added

    BenchmarkStats<> benchmarkStats;

    EXPECT_NO_THROW(emptyMultiReporter.benchmarkEnded(benchmarkStats));

}
