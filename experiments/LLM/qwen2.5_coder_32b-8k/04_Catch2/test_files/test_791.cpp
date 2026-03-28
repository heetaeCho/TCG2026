#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "./TestProjects/Catch2/src/catch2/reporters/catch_reporter_multi.hpp"

#include "./TestProjects/Catch2/src/catch2/interfaces/catch_interfaces_reporter.hpp"



using namespace Catch;

using ::testing::_;

using ::testing::Mock;



class MockIEventListener : public IEventListener {

public:

    MOCK_METHOD(void, benchmarkPreparing, (StringRef name), (override));

};



class MultiReporterTest_791 : public ::testing::Test {

protected:

    void SetUp() override {

        m_reporter = std::make_unique<MultiReporter>();

        m_mockListener = std::make_shared<MockIEventListener>();

        m_reporter->addListener(m_mockListener);

    }



    std::unique_ptr<MultiReporter> m_reporter;

    std::shared_ptr<MockIEventListener> m_mockListener;

};



TEST_F(MultiReporterTest_791, BenchmarkPreparing_DelegatesToListener_791) {

    StringRef benchmarkName("Benchmark1");

    EXPECT_CALL(*m_mockListener, benchmarkPreparing(benchmarkName)).Times(1);

    m_reporter->benchmarkPreparing(benchmarkName);

}



TEST_F(MultiReporterTest_791, BenchmarkPreparing_NoListenersDoesNothing_791) {

    m_reporter->addListener(nullptr);  // Add a nullptr to simulate no valid listeners

    StringRef benchmarkName("Benchmark2");

    EXPECT_CALL(*m_mockListener, benchmarkPreparing(benchmarkName)).Times(0);

    m_reporter->benchmarkPreparing(benchmarkName);

}



TEST_F(MultiReporterTest_791, BenchmarkPreparing_EmptyString_791) {

    StringRef benchmarkName("");

    EXPECT_CALL(*m_mockListener, benchmarkPreparing(benchmarkName)).Times(1);

    m_reporter->benchmarkPreparing(benchmarkName);

}
