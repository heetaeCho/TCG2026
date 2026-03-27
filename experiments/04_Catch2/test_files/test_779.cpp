#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "./TestProjects/Catch2/src/catch2/reporters/catch_reporter_common_base.hpp"

#include "./TestProjects/Catch2/src/catch2/interfaces/catch_interfaces_config.hpp"



using namespace Catch;



class MockConfig : public IConfig {

public:

    MOCK_CONST_METHOD0(hasTestFilters, bool());

    MOCK_CONST_METHOD0(verbosity, Verbosity());

};



class ReporterBaseTest_779 : public ::testing::Test {

protected:

    testing::StrictMock<MockConfig> mock_config;

    ReporterConfig reporter_config{&mock_config};

    ReporterBase reporter_base{std::move(reporter_config)};

    std::vector<TestCaseHandle> test_cases;

};



TEST_F(ReporterBaseTest_779, ListTests_CallsDefaultListTests_WithNoFiltersAndLowVerbosity_779) {

    EXPECT_CALL(mock_config, hasTestFilters()).WillOnce(testing::Return(false));

    EXPECT_CALL(mock_config, verbosity()).WillOnce(testing::Return(Verbosity::Quiet));



    reporter_base.listTests(test_cases);

}



TEST_F(ReporterBaseTest_779, ListTests_CallsDefaultListTests_WithFiltersAndHighVerbosity_779) {

    EXPECT_CALL(mock_config, hasTestFilters()).WillOnce(testing::Return(true));

    EXPECT_CALL(mock_config, verbosity()).WillOnce(testing::Return(Verbosity::Verbose));



    reporter_base.listTests(test_cases);

}



TEST_F(ReporterBaseTest_779, ListTests_CallsDefaultListTests_WithNoFiltersAndHighVerbosity_779) {

    EXPECT_CALL(mock_config, hasTestFilters()).WillOnce(testing::Return(false));

    EXPECT_CALL(mock_config, verbosity()).WillOnce(testing::Return(Verbosity::Verbose));



    reporter_base.listTests(test_cases);

}



TEST_F(ReporterBaseTest_779, ListTests_CallsDefaultListTests_WithFiltersAndLowVerbosity_779) {

    EXPECT_CALL(mock_config, hasTestFilters()).WillOnce(testing::Return(true));

    EXPECT_CALL(mock_config, verbosity()).WillOnce(testing::Return(Verbosity::Quiet));



    reporter_base.listTests(test_cases);

}
