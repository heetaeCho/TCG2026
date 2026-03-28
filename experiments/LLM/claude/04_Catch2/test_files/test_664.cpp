#include <catch2/internal/catch_clara.hpp>
#include <catch2/catch_test_macros.hpp>

#include <gtest/gtest.h>
#include <string>
#include <vector>

using namespace Catch::Clara;
using namespace Catch::Clara::Detail;

class OptParseTest_664 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test: A flag option that matches a token sets the flag to true
TEST_F(OptParseTest_664, FlagOptionMatchesSetsFlag_664) {
    bool flag = false;
    auto opt = Opt(flag)["-f"]["--flag"]
        .description("A test flag");

    std::vector<std::string> args = {"--flag"};
    // Build token stream from args
    auto result = opt.parse("", TokenStream(Detail::Args(args.size(), args)));
    EXPECT_TRUE(result);
    EXPECT_TRUE(flag);
}

// Test: A flag option that doesn't match returns NoMatch
TEST_F(OptParseTest_664, FlagOptionNoMatch_664) {
    bool flag = false;
    auto opt = Opt(flag)["-f"]["--flag"]
        .description("A test flag");

    std::vector<std::string> args = {"--other"};
    auto result = opt.parse("", TokenStream(Detail::Args(args.size(), args)));
    EXPECT_TRUE(result);
    EXPECT_FALSE(flag);
}

// Test: A value option that matches consumes the next argument
TEST_F(OptParseTest_664, ValueOptionMatchesConsumesArgument_664) {
    std::string value;
    auto opt = Opt(value, "value")["-v"]["--value"]
        .description("A test value");

    std::vector<std::string> args = {"--value", "hello"};
    auto result = opt.parse("", TokenStream(Detail::Args(args.size(), args)));
    EXPECT_TRUE(result);
    EXPECT_EQ(value, "hello");
}

// Test: A value option without following argument returns error
TEST_F(OptParseTest_664, ValueOptionMissingArgument_664) {
    std::string value;
    auto opt = Opt(value, "value")["-v"]["--value"]
        .description("A test value");

    std::vector<std::string> args = {"--value"};
    auto result = opt.parse("", TokenStream(Detail::Args(args.size(), args)));
    EXPECT_FALSE(result);
}

// Test: Empty token stream returns NoMatch
TEST_F(OptParseTest_664, EmptyTokenStreamReturnsNoMatch_664) {
    bool flag = false;
    auto opt = Opt(flag)["-f"]["--flag"]
        .description("A test flag");

    std::vector<std::string> args = {};
    auto result = opt.parse("", TokenStream(Detail::Args(args.size(), args)));
    EXPECT_TRUE(result);
    EXPECT_FALSE(flag);
}

// Test: Short flag option matches
TEST_F(OptParseTest_664, ShortFlagOptionMatches_664) {
    bool flag = false;
    auto opt = Opt(flag)["-f"]["--flag"]
        .description("A test flag");

    std::vector<std::string> args = {"-f"};
    auto result = opt.parse("", TokenStream(Detail::Args(args.size(), args)));
    EXPECT_TRUE(result);
    EXPECT_TRUE(flag);
}

// Test: Short value option matches and consumes argument
TEST_F(OptParseTest_664, ShortValueOptionMatches_664) {
    std::string value;
    auto opt = Opt(value, "value")["-v"]["--value"]
        .description("A test value");

    std::vector<std::string> args = {"-v", "world"};
    auto result = opt.parse("", TokenStream(Detail::Args(args.size(), args)));
    EXPECT_TRUE(result);
    EXPECT_EQ(value, "world");
}

// Test: Integer value option parses correctly
TEST_F(OptParseTest_664, IntValueOptionParsesCorrectly_664) {
    int value = 0;
    auto opt = Opt(value, "number")["-n"]["--number"]
        .description("A numeric value");

    std::vector<std::string> args = {"--number", "42"};
    auto result = opt.parse("", TokenStream(Detail::Args(args.size(), args)));
    EXPECT_TRUE(result);
    EXPECT_EQ(value, 42);
}

// Test: Flag initially false stays false when no match
TEST_F(OptParseTest_664, FlagStaysFalseOnNoMatch_664) {
    bool flag = false;
    auto opt = Opt(flag)["-f"]["--flag"]
        .description("A test flag");

    std::vector<std::string> args = {"--notflag"};
    auto result = opt.parse("", TokenStream(Detail::Args(args.size(), args)));
    EXPECT_TRUE(result);
    EXPECT_FALSE(flag);
}

// Test: Multiple option names, second name matches
TEST_F(OptParseTest_664, MultipleOptionNamesSecondMatches_664) {
    bool flag = false;
    auto opt = Opt(flag)["-f"]["--flag"]["--flag2"]
        .description("Multi-name flag");

    std::vector<std::string> args = {"--flag2"};
    auto result = opt.parse("", TokenStream(Detail::Args(args.size(), args)));
    EXPECT_TRUE(result);
    EXPECT_TRUE(flag);
}
