// ProcessedReporterSpec_operator_not_equal_tests_423.cpp
#include <gtest/gtest.h>
#include <map>
#include <string>

// Include the provided interface
#include "catch2/catch_config.hpp"

using Catch::ProcessedReporterSpec;

class ProcessedReporterSpecTest_423 : public ::testing::Test {};

// Verifies that for two default-constructed specs, != is the logical negation of ==
TEST_F(ProcessedReporterSpecTest_423, DefaultConstructed_NegatesEquality_423) {
    ProcessedReporterSpec a;
    ProcessedReporterSpec b;

    EXPECT_EQ((a != b), !(a == b));
}

// Verifies the relationship holds for reflexive comparison (same instance)
TEST_F(ProcessedReporterSpecTest_423, Reflexive_NegatesEquality_423) {
    ProcessedReporterSpec a;

    EXPECT_EQ((a != a), !(a == a));
}

// Verifies the relationship for two objects with the same observable values
TEST_F(ProcessedReporterSpecTest_423, SameValues_NegatesEquality_423) {
    ProcessedReporterSpec a;
    a.outputFilename = "report.txt";
    a.customOptions = {{"key1", "val1"}, {"key2", "val2"}};

    ProcessedReporterSpec b;
    b.outputFilename = "report.txt";
    b.customOptions = {{"key1", "val1"}, {"key2", "val2"}};

    EXPECT_EQ((a != b), !(a == b));
}

// Verifies the relationship when a single observable field differs
TEST_F(ProcessedReporterSpecTest_423, DifferentOutputFilename_NegatesEquality_423) {
    ProcessedReporterSpec a;
    a.outputFilename = "out-A.txt";

    ProcessedReporterSpec b;
    b.outputFilename = "out-B.txt";

    EXPECT_EQ((a != b), !(a == b));
}

// Verifies the relationship when custom options differ
TEST_F(ProcessedReporterSpecTest_423, DifferentCustomOptions_NegatesEquality_423) {
    ProcessedReporterSpec a;
    a.customOptions = {{"format", "json"}, {"level", "debug"}};

    ProcessedReporterSpec b;
    b.customOptions = {{"format", "xml"}, {"level", "debug"}};

    EXPECT_EQ((a != b), !(a == b));
}

// Verifies the relationship across larger/edge string values and multiple options
TEST_F(ProcessedReporterSpecTest_423, LargeStringsAndMultipleOptions_NegatesEquality_423) {
    std::string longName(4096, 'x'); // long but reasonable string

    ProcessedReporterSpec a;
    a.outputFilename = longName;
    a.customOptions = {
        {"alpha", "1"}, {"beta", "2"}, {"gamma", "3"},
        {"delta", ""},  {"epsilon", std::string(1024, 'e')}
    };

    ProcessedReporterSpec b;
    b.outputFilename = longName; // same filename
    b.customOptions = {
        {"alpha", "1"}, {"beta", "2"}, {"gamma", "3"},
        {"delta", ""},  {"epsilon", std::string(1024, 'e')}
    };

    // First check with identical values
    EXPECT_EQ((a != b), !(a == b));

    // Mutate one observable field to exercise the other branch as well
    b.customOptions["beta"] = "22";
    EXPECT_EQ((a != b), !(a == b));
}
