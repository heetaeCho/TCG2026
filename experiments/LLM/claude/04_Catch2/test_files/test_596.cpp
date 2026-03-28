#include <gtest/gtest.h>
#include <sstream>
#include <string>
#include <cstdint>

#include "catch2/internal/catch_string_manip.hpp"

class PluraliseTest_596 : public ::testing::Test {
protected:
    std::ostringstream oss;
};

// Normal operation: count of 0 should produce plural form (with 's')
TEST_F(PluraliseTest_596, ZeroCountProducesPluralForm_596) {
    oss << Catch::pluralise(0, "test"_catch_sr);
    EXPECT_EQ(oss.str(), "0 tests");
}

// Normal operation: count of 1 should produce singular form (no 's')
TEST_F(PluraliseTest_596, OneCountProducesSingularForm_596) {
    oss << Catch::pluralise(1, "test"_catch_sr);
    EXPECT_EQ(oss.str(), "1 test");
}

// Normal operation: count of 2 should produce plural form (with 's')
TEST_F(PluraliseTest_596, TwoCountProducesPluralForm_596) {
    oss << Catch::pluralise(2, "test"_catch_sr);
    EXPECT_EQ(oss.str(), "2 tests");
}

// Normal operation: larger count should produce plural form
TEST_F(PluraliseTest_596, LargeCountProducesPluralForm_596) {
    oss << Catch::pluralise(100, "case"_catch_sr);
    EXPECT_EQ(oss.str(), "100 cases");
}

// Normal operation: different label
TEST_F(PluraliseTest_596, DifferentLabelSingular_596) {
    oss << Catch::pluralise(1, "assertion"_catch_sr);
    EXPECT_EQ(oss.str(), "1 assertion");
}

// Normal operation: different label plural
TEST_F(PluraliseTest_596, DifferentLabelPlural_596) {
    oss << Catch::pluralise(5, "assertion"_catch_sr);
    EXPECT_EQ(oss.str(), "5 assertions");
}

// Boundary: maximum uint64_t value should produce plural form
TEST_F(PluraliseTest_596, MaxUint64ProducesPluralForm_596) {
    std::uint64_t maxVal = UINT64_MAX;
    oss << Catch::pluralise(maxVal, "item"_catch_sr);
    std::string expected = std::to_string(maxVal) + " items";
    EXPECT_EQ(oss.str(), expected);
}

// Verify that operator<< returns the stream reference (chaining)
TEST_F(PluraliseTest_596, OperatorReturnsStreamReference_596) {
    std::ostream& result = (oss << Catch::pluralise(3, "thing"_catch_sr));
    EXPECT_EQ(&result, &oss);
}

// Chaining multiple pluralise outputs
TEST_F(PluraliseTest_596, ChainingMultipleOutputs_596) {
    oss << Catch::pluralise(1, "test"_catch_sr) << " and " << Catch::pluralise(2, "assertion"_catch_sr);
    EXPECT_EQ(oss.str(), "1 test and 2 assertions");
}

// Empty label with singular count
TEST_F(PluraliseTest_596, EmptyLabelSingular_596) {
    oss << Catch::pluralise(1, ""_catch_sr);
    EXPECT_EQ(oss.str(), "1 ");
}

// Empty label with plural count
TEST_F(PluraliseTest_596, EmptyLabelPlural_596) {
    oss << Catch::pluralise(0, ""_catch_sr);
    EXPECT_EQ(oss.str(), "0 s");
}

// Count of exactly 1 boundary - verify no trailing 's'
TEST_F(PluraliseTest_596, ExactlyOneNoTrailingS_596) {
    oss << Catch::pluralise(1, "failure"_catch_sr);
    std::string result = oss.str();
    EXPECT_EQ(result, "1 failure");
    // Ensure it does NOT end with 's'
    EXPECT_NE(result.back(), 's');
}

// Count of 2 boundary - verify trailing 's'
TEST_F(PluraliseTest_596, ExactlyTwoHasTrailingS_596) {
    oss << Catch::pluralise(2, "failure"_catch_sr);
    std::string result = oss.str();
    EXPECT_EQ(result, "2 failures");
    EXPECT_EQ(result.back(), 's');
}
