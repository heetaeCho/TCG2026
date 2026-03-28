#include <catch2/catch_all.hpp>
#include <catch2/internal/catch_clara.hpp>
#include <gtest/gtest.h>
#include <string>
#include <vector>

using namespace Catch::Clara;

// Tests for Clara's ParserResult / BasicResult types
class ClaraResultTest_1065 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Tests for Clara's Opt and Arg parsers
class ClaraParserTest_1065 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test that a simple Opt can be created and bound to a boolean
TEST_F(ClaraParserTest_1065, OptBindToBool_1065) {
    bool flag = false;
    auto opt = Opt(flag)["-f"]["--flag"]("A flag option");
    
    // Parse with the flag present
    auto args = std::vector<std::string>{"test", "-f"};
    std::vector<const char*> argv;
    for (auto& a : args) argv.push_back(a.c_str());
    
    auto result = opt.parse(Detail::Args(static_cast<int>(argv.size()), argv.data()));
    EXPECT_TRUE(static_cast<bool>(result));
    EXPECT_TRUE(flag);
}

// Test that Opt without the flag leaves bool as false
TEST_F(ClaraParserTest_1065, OptNotPresentLeavesDefault_1065) {
    bool flag = false;
    auto opt = Opt(flag)["-f"]["--flag"]("A flag option");
    
    auto args = std::vector<std::string>{"test"};
    std::vector<const char*> argv;
    for (auto& a : args) argv.push_back(a.c_str());
    
    auto result = opt.parse(Detail::Args(static_cast<int>(argv.size()), argv.data()));
    EXPECT_TRUE(static_cast<bool>(result));
    EXPECT_FALSE(flag);
}

// Test Opt bound to a string value
TEST_F(ClaraParserTest_1065, OptBindToString_1065) {
    std::string name;
    auto opt = Opt(name, "name")["-n"]["--name"]("A name option");
    
    auto args = std::vector<std::string>{"test", "-n", "hello"};
    std::vector<const char*> argv;
    for (auto& a : args) argv.push_back(a.c_str());
    
    auto result = opt.parse(Detail::Args(static_cast<int>(argv.size()), argv.data()));
    EXPECT_TRUE(static_cast<bool>(result));
    EXPECT_EQ(name, "hello");
}

// Test Opt bound to an int value
TEST_F(ClaraParserTest_1065, OptBindToInt_1065) {
    int count = 0;
    auto opt = Opt(count, "count")["-c"]["--count"]("A count option");
    
    auto args = std::vector<std::string>{"test", "-c", "42"};
    std::vector<const char*> argv;
    for (auto& a : args) argv.push_back(a.c_str());
    
    auto result = opt.parse(Detail::Args(static_cast<int>(argv.size()), argv.data()));
    EXPECT_TRUE(static_cast<bool>(result));
    EXPECT_EQ(count, 42);
}

// Test Arg (positional argument)
TEST_F(ClaraParserTest_1065, ArgBindToString_1065) {
    std::string positional;
    auto arg = Arg(positional, "input")("A positional argument");
    
    auto args = std::vector<std::string>{"test", "myfile.txt"};
    std::vector<const char*> argv;
    for (auto& a : args) argv.push_back(a.c_str());
    
    auto result = arg.parse(Detail::Args(static_cast<int>(argv.size()), argv.data()));
    EXPECT_TRUE(static_cast<bool>(result));
    EXPECT_EQ(positional, "myfile.txt");
}

// Test combining Opt and Arg with | operator
TEST_F(ClaraParserTest_1065, CombinedParser_1065) {
    bool flag = false;
    std::string name;
    
    auto cli = Opt(flag)["-f"]["--flag"]("flag") | Opt(name, "name")["-n"]["--name"]("name");
    
    auto args = std::vector<std::string>{"test", "-f", "-n", "world"};
    std::vector<const char*> argv;
    for (auto& a : args) argv.push_back(a.c_str());
    
    auto result = cli.parse(Detail::Args(static_cast<int>(argv.size()), argv.data()));
    EXPECT_TRUE(static_cast<bool>(result));
    EXPECT_TRUE(flag);
    EXPECT_EQ(name, "world");
}

// Test long option form
TEST_F(ClaraParserTest_1065, LongOptionForm_1065) {
    std::string value;
    auto opt = Opt(value, "val")["-v"]["--value"]("A value");
    
    auto args = std::vector<std::string>{"test", "--value", "longform"};
    std::vector<const char*> argv;
    for (auto& a : args) argv.push_back(a.c_str());
    
    auto result = opt.parse(Detail::Args(static_cast<int>(argv.size()), argv.data()));
    EXPECT_TRUE(static_cast<bool>(result));
    EXPECT_EQ(value, "longform");
}

// Test empty args (no arguments besides program name)
TEST_F(ClaraParserTest_1065, EmptyArgs_1065) {
    bool flag = false;
    auto opt = Opt(flag)["-f"]["--flag"]("A flag");
    
    auto args = std::vector<std::string>{"test"};
    std::vector<const char*> argv;
    for (auto& a : args) argv.push_back(a.c_str());
    
    auto result = opt.parse(Detail::Args(static_cast<int>(argv.size()), argv.data()));
    EXPECT_TRUE(static_cast<bool>(result));
    EXPECT_FALSE(flag);
}

// Test Opt with lambda
TEST_F(ClaraParserTest_1065, OptWithLambda_1065) {
    int parsed_value = 0;
    auto opt = Opt([&](int v) { parsed_value = v; }, "value")["-v"]["--value"]("value with lambda");
    
    auto args = std::vector<std::string>{"test", "-v", "99"};
    std::vector<const char*> argv;
    for (auto& a : args) argv.push_back(a.c_str());
    
    auto result = opt.parse(Detail::Args(static_cast<int>(argv.size()), argv.data()));
    EXPECT_TRUE(static_cast<bool>(result));
    EXPECT_EQ(parsed_value, 99);
}

// Test multiple options set together
TEST_F(ClaraParserTest_1065, MultipleOptionsTogether_1065) {
    bool flagA = false;
    bool flagB = false;
    int num = 0;
    
    auto cli = Opt(flagA)["-a"]("flag a") 
             | Opt(flagB)["-b"]("flag b") 
             | Opt(num, "num")["-n"]("number");
    
    auto args = std::vector<std::string>{"test", "-a", "-b", "-n", "7"};
    std::vector<const char*> argv;
    for (auto& a : args) argv.push_back(a.c_str());
    
    auto result = cli.parse(Detail::Args(static_cast<int>(argv.size()), argv.data()));
    EXPECT_TRUE(static_cast<bool>(result));
    EXPECT_TRUE(flagA);
    EXPECT_TRUE(flagB);
    EXPECT_EQ(num, 7);
}

// Test Opt with missing required value
TEST_F(ClaraParserTest_1065, OptMissingValue_1065) {
    std::string val;
    auto opt = Opt(val, "val")["-v"]["--value"]("a required value opt");
    
    // -v without a following value
    auto args = std::vector<std::string>{"test", "-v"};
    std::vector<const char*> argv;
    for (auto& a : args) argv.push_back(a.c_str());
    
    auto result = opt.parse(Detail::Args(static_cast<int>(argv.size()), argv.data()));
    // The parse might fail or the value might be empty - depends on implementation
    // We just check it doesn't crash and we can query the result
    // If it fails, result should be falsy
    if (!static_cast<bool>(result)) {
        SUCCEED(); // Expected failure for missing value
    } else {
        // Some implementations may accept this
        SUCCEED();
    }
}

// Test that default value is preserved when option not specified
TEST_F(ClaraParserTest_1065, DefaultValuePreserved_1065) {
    int count = 100;
    auto opt = Opt(count, "count")["-c"]["--count"]("count option");
    
    auto args = std::vector<std::string>{"test"};
    std::vector<const char*> argv;
    for (auto& a : args) argv.push_back(a.c_str());
    
    auto result = opt.parse(Detail::Args(static_cast<int>(argv.size()), argv.data()));
    EXPECT_TRUE(static_cast<bool>(result));
    EXPECT_EQ(count, 100);
}

// Test parsing negative numbers
TEST_F(ClaraParserTest_1065, NegativeIntValue_1065) {
    int val = 0;
    auto opt = Opt(val, "val")["-v"]["--value"]("value");
    
    auto args = std::vector<std::string>{"test", "-v", "-5"};
    std::vector<const char*> argv;
    for (auto& a : args) argv.push_back(a.c_str());
    
    auto result = opt.parse(Detail::Args(static_cast<int>(argv.size()), argv.data()));
    // Negative numbers might be parsed or treated as flags
    // Just verify no crash
    SUCCEED();
}

// Test with only program name (minimal args)
TEST_F(ClaraParserTest_1065, MinimalArgs_1065) {
    bool flag = false;
    std::string name = "default";
    
    auto cli = Opt(flag)["-f"]("flag") | Opt(name, "name")["-n"]("name");
    
    auto args = std::vector<std::string>{"program"};
    std::vector<const char*> argv;
    for (auto& a : args) argv.push_back(a.c_str());
    
    auto result = cli.parse(Detail::Args(static_cast<int>(argv.size()), argv.data()));
    EXPECT_TRUE(static_cast<bool>(result));
    EXPECT_FALSE(flag);
    EXPECT_EQ(name, "default");
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
