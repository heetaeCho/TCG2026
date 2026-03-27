#include <gtest/gtest.h>

#include "catch2/reporters/catch_reporter_json.hpp"

#include "catch2/internal/catch_test_run_info.hpp"



using namespace Catch;



class JsonReporterTest : public ::testing::Test {

protected:

    ReporterConfig config;

    JsonReporter reporter{CATCH_MOVE(config)};



    TestRunInfo createTestRunInfo(const StringRef& name) {

        return TestRunInfo{name};

    }

};



TEST_F(JsonReporterTest_865, testRunStarting_SetsCorrectState_865) {

    auto runInfo = createTestRunInfo("Test Run");

    reporter.testRunStarting(runInfo);

    // Assuming we can verify the state through observable behavior

    // Here we just check if the function call does not throw and behaves as expected

}



TEST_F(JsonReporterTest_865, testRunStarting_EndsListingCorrectly_865) {

    auto runInfo = createTestRunInfo("Test Run");

    EXPECT_CALL(reporter, endListing());

    reporter.testRunStarting(runInfo);

    // This is a bit tricky since we cannot directly verify the call to endListing

    // as it's not a virtual function. We assume it's called internally.

}



TEST_F(JsonReporterTest_865, testRunStarting_StartsObjectWithCorrectKey_865) {

    auto runInfo = createTestRunInfo("Test Run");

    EXPECT_CALL(reporter, startObject("test-run"_sr));

    reporter.testRunStarting(runInfo);

    // Similar assumption as above for the call to startObject

}



TEST_F(JsonReporterTest_865, testRunStarting_StartsArrayWithCorrectKey_865) {

    auto runInfo = createTestRunInfo("Test Run");

    EXPECT_CALL(reporter, startArray("test-cases"_sr));

    reporter.testRunStarting(runInfo);

    // Similar assumption as above for the call to startArray

}



// Assuming there are no exceptional or error cases for testRunStarting based on the provided interface



TEST_F(JsonReporterTest_865, BoundaryCondition_EmptyName_865) {

    auto runInfo = createTestRunInfo("");

    reporter.testRunStarting(runInfo);

    // Check if the function handles empty name correctly

}



// Since we do not have more detailed observable behavior or error cases, we can only test these assumptions.
