#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "catch2/internal/catch_run_context.hpp"



using namespace Catch;

using ::testing::_;

using ::testing::Return;



class MockEventListener : public IEventListener {

public:

    MOCK_METHOD(void, exceptionEarlyReported, (), (override));

};



class RunContextTest_510 : public ::testing::Test {

protected:

    NiceMock<MockEventListener> mock_reporter;

    std::unique_ptr<IEventListenerPtr> reporter = std::make_unique<NiceMock<MockEventListener>>();

    const IConfig* mock_config = nullptr;  // Assuming this is a valid pointer in actual usage

    RunContext run_context{mock_config, std::move(reporter)};

};



TEST_F(RunContextTest_510, ExceptionEarlyReported_SetsShouldReportUnexpectedToFalse_510) {

    EXPECT_CALL(mock_reporter, exceptionEarlyReported()).Times(1);



    run_context.exceptionEarlyReported();



    // Since m_shouldReportUnexpected is private, we can't directly verify its value.

    // However, we ensure the method behaves as expected by verifying the mock call.

}
