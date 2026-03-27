#include <gtest/gtest.h>

#include "catch2/reporters/catch_reporter_sonarqube.hpp"

#include "catch2/interfaces/catch_interfaces_reporter.hpp"

#include "catch2/internal/catch_unique_ptr.hpp"



using namespace Catch;



class SonarQubeReporterTest_1085 : public ::testing::Test {

protected:

    ReporterConfig createMockConfig() {

        auto stream = Detail::make_unique<IStream>(nullptr);

        return ReporterConfig(nullptr, CATCH_MOVE(stream), ColourMode::None, {});

    }



    SonarQubeReporter reporter;

    

    SonarQubeReporterTest_1085() : reporter(createMockConfig()) {}

};



TEST_F(SonarQubeReporterTest_1085, ConstructorInitializesPreferences_1085) {

    EXPECT_FALSE(reporter.getPreferences().shouldRedirectStdOut);

    EXPECT_FALSE(reporter.getPreferences().shouldReportAllAssertions);

}



TEST_F(SonarQubeReporterTest_1085, ConstructorSetsShouldStoreSuccesfulAssertionsToFalse_1085) {

    EXPECT_FALSE(reporter.m_shouldStoreSuccesfulAssertions);

}
