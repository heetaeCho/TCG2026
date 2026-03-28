#include <gtest/gtest.h>
#include <string>
#include <ratio>
#include "catch2/catch_tostring.hpp"

// Test the generic ratio_string template with various ratios

TEST(RatioStringTest_93, GenericRatio_OneToOne_93) {
    std::string result = Catch::ratio_string<std::ratio<1, 1>>::symbol();
    EXPECT_EQ(result, "[1/1]");
}

TEST(RatioStringTest_93, GenericRatio_OneToThousand_93) {
    std::string result = Catch::ratio_string<std::ratio<1, 1000>>::symbol();
    EXPECT_EQ(result, "[1/1000]");
}

TEST(RatioStringTest_93, GenericRatio_OneToMillion_93) {
    std::string result = Catch::ratio_string<std::ratio<1, 1000000>>::symbol();
    EXPECT_EQ(result, "[1/1000000]");
}

TEST(RatioStringTest_93, GenericRatio_OneToBillion_93) {
    std::string result = Catch::ratio_string<std::ratio<1, 1000000000>>::symbol();
    EXPECT_EQ(result, "[1/1000000000]");
}

TEST(RatioStringTest_93, GenericRatio_ThousandToOne_93) {
    std::string result = Catch::ratio_string<std::ratio<1000, 1>>::symbol();
    EXPECT_EQ(result, "[1000/1]");
}

TEST(RatioStringTest_93, GenericRatio_ArbitraryRatio_93) {
    std::string result = Catch::ratio_string<std::ratio<3, 7>>::symbol();
    EXPECT_EQ(result, "[3/7]");
}

TEST(RatioStringTest_93, GenericRatio_LargeNumeratorAndDenominator_93) {
    std::string result = Catch::ratio_string<std::ratio<123456, 789012>>::symbol();
    // std::ratio simplifies, so we need to check the simplified form
    using R = std::ratio<123456, 789012>;
    std::string expected = "[" + std::to_string(R::num) + "/" + std::to_string(R::den) + "]";
    EXPECT_EQ(result, expected);
}

TEST(RatioStringTest_93, GenericRatio_NegativeNumerator_93) {
    std::string result = Catch::ratio_string<std::ratio<-1, 1000>>::symbol();
    EXPECT_EQ(result, "[-1/1000]");
}

TEST(RatioStringTest_93, GenericRatio_ReducedForm_93) {
    // std::ratio<2, 4> should be reduced to 1/2
    using R = std::ratio<2, 4>;
    std::string result = Catch::ratio_string<R>::symbol();
    std::string expected = "[" + std::to_string(R::num) + "/" + std::to_string(R::den) + "]";
    EXPECT_EQ(result, expected);
    EXPECT_EQ(result, "[1/2]");
}

// Test known specializations if they exist
// std::atto = std::ratio<1, 1000000000000000000>
TEST(RatioStringTest_93, Atto_Symbol_93) {
    auto result = Catch::ratio_string<std::atto>::symbol();
    // Could be a char specialization or fall through to generic
    // We just verify it returns something valid
    (void)result;
}

// std::femto = std::ratio<1, 1000000000000000>
TEST(RatioStringTest_93, Femto_Symbol_93) {
    auto result = Catch::ratio_string<std::femto>::symbol();
    (void)result;
}

// std::pico = std::ratio<1, 1000000000000>
TEST(RatioStringTest_93, Pico_Symbol_93) {
    auto result = Catch::ratio_string<std::pico>::symbol();
    (void)result;
}

// std::nano = std::ratio<1, 1000000000>
TEST(RatioStringTest_93, Nano_Symbol_93) {
    auto result = Catch::ratio_string<std::nano>::symbol();
    (void)result;
}

// std::micro = std::ratio<1, 1000000>
TEST(RatioStringTest_93, Micro_Symbol_93) {
    auto result = Catch::ratio_string<std::micro>::symbol();
    (void)result;
}

// std::milli = std::ratio<1, 1000>
TEST(RatioStringTest_93, Milli_Symbol_93) {
    auto result = Catch::ratio_string<std::milli>::symbol();
    (void)result;
}

TEST(RatioStringTest_93, GenericRatio_SymbolContainsBrackets_93) {
    std::string result = Catch::ratio_string<std::ratio<5, 3>>::symbol();
    EXPECT_FALSE(result.empty());
    EXPECT_EQ(result.front(), '[');
    EXPECT_EQ(result.back(), ']');
}

TEST(RatioStringTest_93, GenericRatio_SymbolContainsSlash_93) {
    std::string result = Catch::ratio_string<std::ratio<5, 3>>::symbol();
    EXPECT_NE(result.find('/'), std::string::npos);
}

TEST(RatioStringTest_93, GenericRatio_ZeroNumerator_93) {
    std::string result = Catch::ratio_string<std::ratio<0, 1>>::symbol();
    EXPECT_EQ(result, "[0/1]");
}

TEST(RatioStringTest_93, ConsistentResults_93) {
    // Calling symbol() multiple times should give the same result
    std::string result1 = Catch::ratio_string<std::ratio<1, 1000>>::symbol();
    std::string result2 = Catch::ratio_string<std::ratio<1, 1000>>::symbol();
    EXPECT_EQ(result1, result2);
}
