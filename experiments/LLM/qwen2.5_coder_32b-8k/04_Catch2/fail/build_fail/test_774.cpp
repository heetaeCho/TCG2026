#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "catch2/reporters/catch_reporter_console.hpp"

#include "catch2/interfaces/catch_interfaces_config.hpp"

#include "catch2/internal/catch_unique_ptr.hpp"



using namespace Catch;



class MockConfig : public IConfig {

public:

    MOCK_CONST_METHOD0(testSpec, TestSpec const&());

    MOCK_CONST_METHOD0(rngSeed, uint32_t());

};



class ConsoleReporterTest : public ::testing::Test {

protected:

    MockConfig mock_config;

    ReporterConfig reporter_config{&mock_config, Detail::unique_ptr<IStream>(nullptr)};

    ConsoleReporter console_reporter{CATCH_MOVE(reporter_config)};



    void SetUp() override {

        // Setup default behavior for mocks if needed

    }

};



TEST_F(ConsoleReporterTest_774, TestRunStarting_NoFilters_774) {

    TestRunInfo test_run_info{"Sample Test Run"};

    EXPECT_CALL(mock_config, rngSeed()).WillOnce(::testing::Return(12345));

    console_reporter.testRunStarting(test_run_info);



    // Verify the output stream contains the correct seed information

    std::string expected_output = "Randomness seeded to: 12345\n";

    EXPECT_EQ(console_reporter.m_stream.str(), expected_output);

}



TEST_F(ConsoleReporterTest_774, TestRunStarting_WithFilters_774) {

    TestRunInfo test_run_info{"Sample Test Run"};

    TestSpec test_spec;

    ON_CALL(mock_config, hasTestFilters()).WillByDefault(::testing::Return(true));

    EXPECT_CALL(mock_config, testSpec()).WillOnce(::testing::ReturnRef(test_spec));

    EXPECT_CALL(mock_config, rngSeed()).WillOnce(::testing::Return(12345));

    console_reporter.testRunStarting(test_run_info);



    // Verify the output stream contains filter information and seed information

    std::string expected_output = "Filters: \nRandomness seeded to: 12345\n";

    EXPECT_EQ(console_reporter.m_stream.str(), expected_output);

}



TEST_F(ConsoleReporterTest_774, TestRunStarting_BoundaryCondition_EmptyName_774) {

    TestRunInfo test_run_info{""};

    EXPECT_CALL(mock_config, rngSeed()).WillOnce(::testing::Return(12345));

    console_reporter.testRunStarting(test_run_info);



    // Verify the output stream contains the correct seed information

    std::string expected_output = "Randomness seeded to: 12345\n";

    EXPECT_EQ(console_reporter.m_stream.str(), expected_output);

}
