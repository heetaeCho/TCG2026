// File: tests/xmlformatting_or_operator_test.cpp
#include <gtest/gtest.h>
#include <cstdint>

// Include the header under test (use the path from your tree)
#include "Catch2/src/catch2/internal/catch_xmlwriter.hpp"

using Catch::XmlFormatting;

// Small helper to construct flags without assuming any named enumerators.
static inline XmlFormatting F(std::uint8_t v) {
    return static_cast<XmlFormatting>(v);
}
static inline std::uint8_t U(XmlFormatting f) {
    return static_cast<std::uint8_t>(f);
}

// ---- Basic combinations ----

TEST(XmlFormattingTest_15, OrBasicCombination_15) {
    // 0x01 | 0x02 -> 0x03
    auto a = F(0x01);
    auto b = F(0x02);
    auto r = a | b;
    EXPECT_EQ(U(r), static_cast<std::uint8_t>(0x03));
}

TEST(XmlFormattingTest_15, OrWithZeroIsIdentity_15) {
    auto zero = F(0x00);
    auto x    = F(0xAC);
    EXPECT_EQ(U(zero | x), U(x));
    EXPECT_EQ(U(x | zero), U(x));
}

TEST(XmlFormattingTest_15, OrWithOverlapKeepsSetBits_15) {
    // 0x03 | 0x01 -> 0x03
    auto a = F(0x03);
    auto b = F(0x01);
    EXPECT_EQ(U(a | b), static_cast<std::uint8_t>(0x03));
}

// ---- Algebraic properties (on observable results) ----

TEST(XmlFormattingTest_15, OrIsCommutative_15) {
    auto a = F(0x12);
    auto b = F(0x80);
    EXPECT_EQ(U(a | b), U(b | a));
}

TEST(XmlFormattingTest_15, OrIsAssociative_15) {
    auto a = F(0x01);
    auto b = F(0x04);
    auto c = F(0x10);
    auto left  = U((a | b) | c);
    auto right = U(a | (b | c));
    EXPECT_EQ(left, right);
}

TEST(XmlFormattingTest_15, OrIsIdempotent_15) {
    auto a = F(0x5A);
    EXPECT_EQ(U(a | a), U(a));
}

// ---- Boundary / edge values within uint8_t domain ----

TEST(XmlFormattingTest_15, OrWithHighBit_15) {
    auto a = F(0x80);
    auto b = F(0x7F);
    EXPECT_EQ(U(a | b), static_cast<std::uint8_t>(0xFF));
}

TEST(XmlFormattingTest_15, OrAllZeros_15) {
    auto a = F(0x00);
    auto b = F(0x00);
    EXPECT_EQ(U(a | b), static_cast<std::uint8_t>(0x00));
}

TEST(XmlFormattingTest_15, OrChainedMultipleFlags_15) {
    auto a = F(0x01);
    auto b = F(0x02);
    auto c = F(0x08);
    auto d = F(0x20);
    auto r = a | b | c | d;
    EXPECT_EQ(U(r), static_cast<std::uint8_t>(0x2B)); // 0b0010'1011
}

// ---- Constexpr usability (compile-time friendly) ----

// These static_asserts validate the function can be used in constant expressions
// and that the observable result equals the uint8_t OR of inputs.
static constexpr XmlFormatting kA_15 = static_cast<XmlFormatting>(0x11);
static constexpr XmlFormatting kB_15 = static_cast<XmlFormatting>(0x0A);
static constexpr XmlFormatting kR_15 = kA_15 | kB_15;
static_assert(static_cast<std::uint8_t>(kR_15) == static_cast<std::uint8_t>(0x1B),
              "XmlFormatting operator| should behave like uint8_t bitwise OR (constexpr).");

