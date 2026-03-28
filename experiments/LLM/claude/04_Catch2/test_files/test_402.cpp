#include "catch2/internal/catch_clara.hpp"
#include "catch2/catch_all.hpp"
#include <gtest/gtest.h>
#include <string>

// Use the Clara namespace
using namespace Catch::Clara;

class ComposableParserImplTest_402 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test that composing two Opt parsers via operator| produces a valid Parser
TEST_F(ComposableParserImplTest_402, ComposeTwoOpts_402) {
    bool flagA = false;
    bool flagB = false;

    auto optA = Opt(flagA)["-a"]["--flag-a"]("Flag A");
    auto optB = Opt(flagB)["-b"]["--flag-b"]("Flag B");

    auto composed = optA | optB;

    // Parse with -a flag
    const char* argv[] = {"test", "-a", "-b"};
    auto result = composed.parse(Detail::Args(3, argv));

    EXPECT_TRUE(static_cast<bool>(result));
    EXPECT_TRUE(flagA);
    EXPECT_TRUE(flagB);
}

// Test composing an Opt with an Arg
TEST_F(ComposableParserImplTest_402, ComposeOptAndArg_402) {
    bool flag = false;
    std::string name;

    auto opt = Opt(flag)["-f"]["--flag"]("A flag");
    auto arg = Arg(name, "name")("A positional argument");

    auto composed = opt | arg;

    const char* argv[] = {"test", "-f", "hello"};
    auto result = composed.parse(Detail::Args(3, argv));

    EXPECT_TRUE(static_cast<bool>(result));
    EXPECT_TRUE(flag);
    EXPECT_EQ(name, "hello");
}

// Test composing multiple opts with chained operator|
TEST_F(ComposableParserImplTest_402, ChainMultipleOpts_402) {
    bool flagA = false;
    bool flagB = false;
    bool flagC = false;

    auto optA = Opt(flagA)["-a"]("Flag A");
    auto optB = Opt(flagB)["-b"]("Flag B");
    auto optC = Opt(flagC)["-c"]("Flag C");

    auto composed = optA | optB | optC;

    const char* argv[] = {"test", "-a", "-c"};
    auto result = composed.parse(Detail::Args(3, argv));

    EXPECT_TRUE(static_cast<bool>(result));
    EXPECT_TRUE(flagA);
    EXPECT_FALSE(flagB);
    EXPECT_TRUE(flagC);
}

// Test that composing parsers and parsing with no arguments works
TEST_F(ComposableParserImplTest_402, ComposeWithNoArguments_402) {
    bool flag = false;

    auto opt = Opt(flag)["-f"]("A flag");
    auto opt2 = Opt(flag)["-g"]("Another flag");

    auto composed = opt | opt2;

    const char* argv[] = {"test"};
    auto result = composed.parse(Detail::Args(1, argv));

    EXPECT_TRUE(static_cast<bool>(result));
    EXPECT_FALSE(flag);
}

// Test composing parser with string value options
TEST_F(ComposableParserImplTest_402, ComposeWithStringValueOpts_402) {
    std::string valA;
    std::string valB;

    auto optA = Opt(valA, "valA")["-a"]("Value A");
    auto optB = Opt(valB, "valB")["-b"]("Value B");

    auto composed = optA | optB;

    const char* argv[] = {"test", "-a", "alpha", "-b", "beta"};
    auto result = composed.parse(Detail::Args(5, argv));

    EXPECT_TRUE(static_cast<bool>(result));
    EXPECT_EQ(valA, "alpha");
    EXPECT_EQ(valB, "beta");
}

// Test composing with integer value options
TEST_F(ComposableParserImplTest_402, ComposeWithIntValueOpts_402) {
    int count = 0;
    bool verbose = false;

    auto optCount = Opt(count, "count")["-n"]["--count"]("A count");
    auto optVerbose = Opt(verbose)["-v"]["--verbose"]("Verbose mode");

    auto composed = optCount | optVerbose;

    const char* argv[] = {"test", "-n", "42", "-v"};
    auto result = composed.parse(Detail::Args(4, argv));

    EXPECT_TRUE(static_cast<bool>(result));
    EXPECT_EQ(count, 42);
    EXPECT_TRUE(verbose);
}

// Test that unknown arguments handled appropriately
TEST_F(ComposableParserImplTest_402, ComposeWithUnknownArg_402) {
    bool flag = false;

    auto opt = Opt(flag)["-f"]("A flag");
    auto opt2 = Opt(flag)["-g"]("Another flag");

    auto composed = opt | opt2;

    const char* argv[] = {"test", "--unknown"};
    auto result = composed.parse(Detail::Args(2, argv));

    // Unknown arguments may or may not cause failure depending on configuration
    // but the parse should complete without crashing
    EXPECT_FALSE(flag);
}
