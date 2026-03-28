// File: sonarqube_reporter_getdescription_tests_569.cpp

#include <gtest/gtest.h>
#include <string>
#include "catch2/reporters/catch_reporter_sonarqube.hpp"

// Sanity: the function should not throw when called.
TEST(SonarQubeReporter_GetDescription_569, NoThrow_569) {
    EXPECT_NO_THROW({
        auto desc = Catch::SonarQubeReporter::getDescription();
        (void)desc; // suppress unused warning
    });
}

// The returned description must exactly match the documented string.
TEST(SonarQubeReporter_GetDescription_569, ReturnsExpectedText_569) {
    const std::string expected =
        "Reports test results in the Generic Test Data SonarQube XML format";
    const std::string actual = Catch::SonarQubeReporter::getDescription();
    EXPECT_EQ(actual, expected);
}

// The description should be non-empty and stable across repeated calls.
TEST(SonarQubeReporter_GetDescription_569, NonEmptyAndStable_569) {
    const std::string first  = Catch::SonarQubeReporter::getDescription();
    const std::string second = Catch::SonarQubeReporter::getDescription();

    EXPECT_FALSE(first.empty());
    EXPECT_EQ(first, second);
}

// (Compile-time) The return type should be std::string.
// This aligns with the public signature and prevents accidental changes.
TEST(SonarQubeReporter_GetDescription_569, ReturnTypeIsStdString_569) {
    const auto desc = Catch::SonarQubeReporter::getDescription();
    // If the return type changes, this will fail to compile or assert false.
    bool isStdString = std::is_same<decltype(desc), const std::string>::value
                       || std::is_same<decltype(desc), std::string>::value;
    EXPECT_TRUE(isStdString);
}
