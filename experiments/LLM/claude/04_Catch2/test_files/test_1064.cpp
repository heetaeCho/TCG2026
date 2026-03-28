#include <catch2/catch_all.hpp>
#include <catch2/internal/catch_clara.hpp>
#include <string>
#include <vector>

using namespace Catch::Clara;

// Test basic Opt construction and parsing
TEST(ClaraOptTest_1064, BooleanFlagParsing_1064) {
    bool flag = false;
    auto cli = Opt(flag, "flag")["-f"]["--flag"]("A boolean flag");
    
    const char* argv[] = {"test", "-f"};
    auto result = cli.parse(Args(2, argv));
    EXPECT_TRUE(result);
    EXPECT_TRUE(flag);
}

TEST(ClaraOptTest_1064, BooleanFlagNotSet_1064) {
    bool flag = false;
    auto cli = Opt(flag, "flag")["-f"]["--flag"]("A boolean flag");
    
    const char* argv[] = {"test"};
    auto result = cli.parse(Args(1, argv));
    EXPECT_TRUE(result);
    EXPECT_FALSE(flag);
}

TEST(ClaraOptTest_1064, StringOptionParsing_1064) {
    std::string name;
    auto cli = Opt(name, "name")["-n"]["--name"]("A name option");
    
    const char* argv[] = {"test", "-n", "hello"};
    auto result = cli.parse(Args(3, argv));
    EXPECT_TRUE(result);
    EXPECT_EQ(name, "hello");
}

TEST(ClaraOptTest_1064, IntOptionParsing_1064) {
    int value = 0;
    auto cli = Opt(value, "value")["-v"]["--value"]("An integer value");
    
    const char* argv[] = {"test", "-v", "42"};
    auto result = cli.parse(Args(3, argv));
    EXPECT_TRUE(result);
    EXPECT_EQ(value, 42);
}

TEST(ClaraOptTest_1064, LongFlagParsing_1064) {
    bool flag = false;
    auto cli = Opt(flag, "flag")["-f"]["--flag"]("A boolean flag");
    
    const char* argv[] = {"test", "--flag"};
    auto result = cli.parse(Args(2, argv));
    EXPECT_TRUE(result);
    EXPECT_TRUE(flag);
}

TEST(ClaraOptTest_1064, MultipleOptions_1064) {
    bool flag = false;
    std::string name;
    int count = 0;
    auto cli = Opt(flag)["-f"]["--flag"]("flag")
             | Opt(name, "name")["-n"]["--name"]("name")
             | Opt(count, "count")["-c"]["--count"]("count");
    
    const char* argv[] = {"test", "-f", "-n", "world", "-c", "5"};
    auto result = cli.parse(Args(6, argv));
    EXPECT_TRUE(result);
    EXPECT_TRUE(flag);
    EXPECT_EQ(name, "world");
    EXPECT_EQ(count, 5);
}

TEST(ClaraArgTest_1064, PositionalArgParsing_1064) {
    std::string filename;
    auto cli = Arg(filename, "filename")("A positional argument");
    
    const char* argv[] = {"test", "myfile.txt"};
    auto result = cli.parse(Args(2, argv));
    EXPECT_TRUE(result);
    EXPECT_EQ(filename, "myfile.txt");
}

TEST(ClaraArgTest_1064, NoPositionalArg_1064) {
    std::string filename;
    auto cli = Arg(filename, "filename")("A positional argument");
    
    const char* argv[] = {"test"};
    auto result = cli.parse(Args(1, argv));
    EXPECT_TRUE(result);
    EXPECT_EQ(filename, "");
}

TEST(ClaraOptTest_1064, MissingRequiredValue_1064) {
    std::string name;
    auto cli = Opt(name, "name")["-n"]["--name"]("A name option");
    
    const char* argv[] = {"test", "-n"};
    auto result = cli.parse(Args(2, argv));
    EXPECT_FALSE(result);
}

TEST(ClaraOptTest_1064, EmptyArgs_1064) {
    bool flag = false;
    auto cli = Opt(flag)["-f"]["--flag"]("A flag");
    
    const char* argv[] = {"test"};
    auto result = cli.parse(Args(1, argv));
    EXPECT_TRUE(result);
    EXPECT_FALSE(flag);
}

TEST(ClaraOptTest_1064, CombinedOptAndArg_1064) {
    bool verbose = false;
    std::string input;
    auto cli = Opt(verbose)["-v"]["--verbose"]("verbose")
             | Arg(input, "input")("input file");
    
    const char* argv[] = {"test", "-v", "file.txt"};
    auto result = cli.parse(Args(3, argv));
    EXPECT_TRUE(result);
    EXPECT_TRUE(verbose);
    EXPECT_EQ(input, "file.txt");
}

TEST(ClaraOptTest_1064, DoubleOptionParsing_1064) {
    double value = 0.0;
    auto cli = Opt(value, "value")["-d"]["--double"]("A double value");
    
    const char* argv[] = {"test", "-d", "3.14"};
    auto result = cli.parse(Args(3, argv));
    EXPECT_TRUE(result);
    EXPECT_DOUBLE_EQ(value, 3.14);
}

TEST(ClaraOptTest_1064, UnsignedIntParsing_1064) {
    unsigned int value = 0;
    auto cli = Opt(value, "value")["-u"]["--uint"]("An unsigned int");
    
    const char* argv[] = {"test", "-u", "100"};
    auto result = cli.parse(Args(3, argv));
    EXPECT_TRUE(result);
    EXPECT_EQ(value, 100u);
}

TEST(ClaraOptTest_1064, LongOptionWithEquals_1064) {
    std::string name;
    auto cli = Opt(name, "name")["-n"]["--name"]("A name");
    
    const char* argv[] = {"test", "--name=hello"};
    auto result = cli.parse(Args(2, argv));
    EXPECT_TRUE(result);
    EXPECT_EQ(name, "hello");
}

TEST(ClaraOptTest_1064, NegativeIntParsing_1064) {
    int value = 0;
    auto cli = Opt(value, "value")["-v"]["--value"]("An integer");
    
    const char* argv[] = {"test", "-v", "-10"};
    auto result = cli.parse(Args(3, argv));
    EXPECT_TRUE(result);
    EXPECT_EQ(value, -10);
}
