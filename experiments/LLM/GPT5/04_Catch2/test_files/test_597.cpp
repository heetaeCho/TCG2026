// File: tests/parse_enums_tests_597.cpp

#include <gtest/gtest.h>
#include <vector>
#include <string>

// Include the public interfaces used by the function under test.
#include "Catch2/src/catch2/internal/catch_stringref.hpp"

// Forward-declare the function under test (kept as a black box).
namespace Catch {
namespace Detail {
    std::vector<Catch::StringRef> parseEnums(Catch::StringRef enums);
} // namespace Detail
} // namespace Catch

using Catch::StringRef;

class ParseEnumsTest_597 : public ::testing::Test {};

// [Normal operation] Simple comma-separated identifiers
TEST_F(ParseEnumsTest_597, SplitsSimpleCommaSeparated_597) {
    StringRef input("A,B,C");
    auto out = Catch::Detail::parseEnums(input);

    ASSERT_EQ(out.size(), 3u);
    EXPECT_EQ(std::string(out[0]), "A");
    EXPECT_EQ(std::string(out[1]), "B");
    EXPECT_EQ(std::string(out[2]), "C");
}

// [Boundary] Empty input yields no entries
TEST_F(ParseEnumsTest_597, EmptyInputYieldsEmptyVector_597) {
    StringRef input("");
    auto out = Catch::Detail::parseEnums(input);
    EXPECT_TRUE(out.empty());
}

// [Normal + Trimming] Surrounding and inner whitespace is trimmed
TEST_F(ParseEnumsTest_597, TrimsWhitespaceAroundNames_597) {
    StringRef input("  A ,\tB  ,  C\t");
    auto out = Catch::Detail::parseEnums(input);

    ASSERT_EQ(out.size(), 3u);
    EXPECT_EQ(std::string(out[0]), "A");
    EXPECT_EQ(std::string(out[1]), "B");
    EXPECT_EQ(std::string(out[2]), "C");
}

// [Observable behavior via interface] Values with explicit assignments keep just the instance name
// (e.g., "A = 1" -> "A"), as exposed by parseEnums's return values.
TEST_F(ParseEnumsTest_597, ExtractsNameBeforeEquals_597) {
    StringRef input("A=1, B = 2, C=   -3");
    auto out = Catch::Detail::parseEnums(input);

    ASSERT_EQ(out.size(), 3u);
    EXPECT_EQ(std::string(out[0]), "A");
    EXPECT_EQ(std::string(out[1]), "B");
    EXPECT_EQ(std::string(out[2]), "C");
}

// [Observable behavior via interface] Scoped names return the instance identifier
// (e.g., "Ns::Red" -> "Red") in the parsed output.
TEST_F(ParseEnumsTest_597, ExtractsScopedInstanceName_597) {
    StringRef input("Colors::Red,  Shades::Blue, ::Global::Green");
    auto out = Catch::Detail::parseEnums(input);

    ASSERT_EQ(out.size(), 3u);
    EXPECT_EQ(std::string(out[0]), "Red");
    EXPECT_EQ(std::string(out[1]), "Blue");
    EXPECT_EQ(std::string(out[2]), "Green");
}

// [Boundary] Single value (no comma) returns a single-element vector
TEST_F(ParseEnumsTest_597, SingleValueProducesSingleElement_597) {
    StringRef input("OnlyOne");
    auto out = Catch::Detail::parseEnums(input);

    ASSERT_EQ(out.size(), 1u);
    EXPECT_EQ(std::string(out[0]), "OnlyOne");
}

// [Normal] Order is preserved as provided in the input
TEST_F(ParseEnumsTest_597, PreservesOrderOfItems_597) {
    StringRef input("First,Second,Third,Fourth");
    auto out = Catch::Detail::parseEnums(input);

    std::vector<std::string> got;
    got.reserve(out.size());
    for (auto const& s : out) got.emplace_back(static_cast<std::string>(s));

    std::vector<std::string> expected = {"First","Second","Third","Fourth"};
    EXPECT_EQ(got, expected);
}
