#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "catch2/internal/catch_clara.hpp"

using namespace Catch;
using namespace Catch::Clara;
using namespace Catch::Clara::Detail;

// A concrete implementation of ParserBase for testing purposes
class MockParserBase : public ParserBase {
public:
    // We need to override the virtual parse method
    MOCK_METHOD(InternalParseResult, parse, (const std::string& exeName, TokenStream tokens), (override, const));
    MOCK_METHOD(size_t, cardinality, (), (override, const));
};

// Test fixture
class ParserBaseTest_656 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test that Args correctly stores the exe name from argc/argv
TEST_F(ParserBaseTest_656, ArgsConstructorFromArgcArgv_656) {
    const char* argv[] = {"myapp", "--flag", "value"};
    int argc = 3;
    Args args(argc, argv);
    
    EXPECT_EQ(static_cast<std::string>(args.exeName()), "myapp");
}

// Test that Args correctly stores the exe name from initializer list
TEST_F(ParserBaseTest_656, ArgsConstructorFromInitializerList_656) {
    Args args({"myapp", "--option", "val"});
    
    EXPECT_EQ(static_cast<std::string>(args.exeName()), "myapp");
}

// Test that Args with single element (just exe name) works
TEST_F(ParserBaseTest_656, ArgsWithOnlyExeName_656) {
    const char* argv[] = {"myapp"};
    int argc = 1;
    Args args(argc, argv);
    
    EXPECT_EQ(static_cast<std::string>(args.exeName()), "myapp");
}

// Test that Args initializer list with single element works
TEST_F(ParserBaseTest_656, ArgsInitializerListSingleElement_656) {
    Args args({"program"});
    
    EXPECT_EQ(static_cast<std::string>(args.exeName()), "program");
}

// Test that parse(Args) calls the virtual parse with correct exeName
TEST_F(ParserBaseTest_656, ParseArgsCallsVirtualParseWithExeName_656) {
    MockParserBase parser;
    
    // We expect the virtual parse to be called with the exe name from Args
    EXPECT_CALL(parser, parse(::testing::Eq(std::string("testapp")), ::testing::_))
        .Times(1)
        .WillOnce(::testing::Return(InternalParseResult::ok(ParseState(ParseResultType::Matched, TokenStream()))));
    
    Args args({"testapp", "--verbose"});
    auto result = parser.parse(args);
}

// Test that parse(Args) passes the exe name correctly with argc/argv constructor
TEST_F(ParserBaseTest_656, ParseArgsFromArgcArgvCallsVirtualParse_656) {
    MockParserBase parser;
    
    const char* argv[] = {"myprogram", "--help"};
    int argc = 2;
    Args args(argc, argv);
    
    EXPECT_CALL(parser, parse(::testing::Eq(std::string("myprogram")), ::testing::_))
        .Times(1)
        .WillOnce(::testing::Return(InternalParseResult::ok(ParseState(ParseResultType::Matched, TokenStream()))));
    
    auto result = parser.parse(args);
}

// Test with empty exe name
TEST_F(ParserBaseTest_656, ParseArgsWithEmptyExeName_656) {
    MockParserBase parser;
    
    const char* argv[] = {"", "--flag"};
    int argc = 2;
    Args args(argc, argv);
    
    EXPECT_CALL(parser, parse(::testing::Eq(std::string("")), ::testing::_))
        .Times(1)
        .WillOnce(::testing::Return(InternalParseResult::ok(ParseState(ParseResultType::Matched, TokenStream()))));
    
    auto result = parser.parse(args);
}

// Test that default cardinality returns expected value
TEST_F(ParserBaseTest_656, DefaultCardinality_656) {
    MockParserBase parser;
    
    EXPECT_CALL(parser, cardinality())
        .Times(1)
        .WillOnce(::testing::Return(1));
    
    EXPECT_EQ(parser.cardinality(), 1);
}

// Test that validate returns success by default (base class behavior)
TEST_F(ParserBaseTest_656, ValidateReturnsOk_656) {
    // Create a non-mock derived class that doesn't override validate
    class SimpleParser : public ParserBase {
    public:
        InternalParseResult parse(const std::string&, TokenStream) const override {
            return InternalParseResult::ok(ParseState(ParseResultType::Matched, TokenStream()));
        }
    };
    
    SimpleParser parser;
    auto result = parser.validate();
    EXPECT_TRUE(static_cast<bool>(result));
}

// Test parse with multiple arguments
TEST_F(ParserBaseTest_656, ParseArgsWithMultipleArguments_656) {
    MockParserBase parser;
    
    Args args({"app", "-a", "-b", "-c", "value1", "value2"});
    
    EXPECT_CALL(parser, parse(::testing::Eq(std::string("app")), ::testing::_))
        .Times(1)
        .WillOnce(::testing::Return(InternalParseResult::ok(ParseState(ParseResultType::Matched, TokenStream()))));
    
    auto result = parser.parse(args);
}

// Test parse with no additional arguments beyond exe name
TEST_F(ParserBaseTest_656, ParseArgsWithNoAdditionalArgs_656) {
    MockParserBase parser;
    
    Args args({"standalone"});
    
    EXPECT_CALL(parser, parse(::testing::Eq(std::string("standalone")), ::testing::_))
        .Times(1)
        .WillOnce(::testing::Return(InternalParseResult::ok(ParseState(ParseResultType::Matched, TokenStream()))));
    
    auto result = parser.parse(args);
}

// Test that the exe name with path is preserved
TEST_F(ParserBaseTest_656, ParseArgsExeNameWithPath_656) {
    MockParserBase parser;
    
    const char* argv[] = {"/usr/local/bin/myapp", "--config", "file.cfg"};
    int argc = 3;
    Args args(argc, argv);
    
    EXPECT_CALL(parser, parse(::testing::Eq(std::string("/usr/local/bin/myapp")), ::testing::_))
        .Times(1)
        .WillOnce(::testing::Return(InternalParseResult::ok(ParseState(ParseResultType::Matched, TokenStream()))));
    
    auto result = parser.parse(args);
}
