#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "catch2/reporters/catch_reporter_common_base.hpp"

#include "catch2/interfaces/catch_interfaces_config.hpp"



using namespace Catch;

using ::testing::NiceMock;



class MockConfig : public IConfig {

public:

    MOCK_CONST_METHOD0(verbosity, Verbosity());

};



class ReporterBaseTest_777 : public ::testing::Test {

protected:

    NiceMock<MockConfig> mockConfig;

    std::vector<ReporterDescription> reporterDescriptions;

    ReporterBase reporter{ReporterConfig{&mockConfig, std::make_unique<std::ostringstream>(), ColourMode::None}};

};



TEST_F(ReporterBaseTest_777, ListReportersWithEmptyList_777) {

    EXPECT_CALL(mockConfig, verbosity()).Times(1);

    reporter.listReporters(reporterDescriptions);

}



TEST_F(ReporterBaseTest_777, ListReportersWithNonEmptyList_777) {

    reporterDescriptions.push_back(ReporterDescription{"name", "description"});

    EXPECT_CALL(mockConfig, verbosity()).Times(1);

    reporter.listReporters(reporterDescriptions);

}
