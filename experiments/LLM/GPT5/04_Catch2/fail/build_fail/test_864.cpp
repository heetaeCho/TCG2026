// File: tests/json_reporter_get_description_864.cpp

#include <gtest/gtest.h>

// We include the provided partial implementation directly to use the exact interface/behavior
// under test, treating it as a black box per the constraints.
#include "Catch2/src/catch2/reporters/catch_reporter_json.cpp"

class JsonReporterGetDescriptionTest_864 : public ::testing::Test {
protected:
    Catch::JsonReporter reporter; // default-constructible per provided partial code
};

// Normal operation: exact expected message
TEST_F(JsonReporterGetDescriptionTest_864, ReturnsExactMessage_864) {
    const std::string expected =
        "Outputs listings as JSON. Test listing is Work-in-Progress!";
    EXPECT_EQ(reporter.getDescription(), expected);
}

// Boundary-ish observable checks: non-empty and contains a key term
TEST_F(JsonReporterGetDescriptionTest_864, NotEmptyAndContainsJSON_864) {
    const std::string desc = reporter.getDescription();
    EXPECT_FALSE(desc.empty());
    EXPECT_NE(desc.find("JSON"), std::string::npos) << "Description should mention JSON";
}

// Idempotence: multiple calls return the same value
TEST_F(JsonReporterGetDescriptionTest_864, ConsistentAcrossMultipleCalls_864) {
    const std::string first = reporter.getDescription();
    const std::string second = reporter.getDescription();
    EXPECT_EQ(first, second);
}

// Multiple instances behave the same (no hidden instance-dependent variation observable via the interface)
TEST_F(JsonReporterGetDescriptionTest_864, SameAcrossInstances_864) {
    Catch::JsonReporter another;
    EXPECT_EQ(reporter.getDescription(), another.getDescription());
}
