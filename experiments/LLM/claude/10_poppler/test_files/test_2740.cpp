#include <gtest/gtest.h>
#include <cstring>
#include <string>
#include "parseargs.h"
#include "goo/GooString.h"

class ParseArgsTest_2740 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test argFlag: setting a boolean flag
TEST_F(ParseArgsTest_2740, FlagArgSetsBoolean_2740) {
    bool flagVal = false;
    const ArgDesc argTable[] = {
        { "-flag", argFlag, &flagVal, 0, "a flag" },
        { nullptr, argFlag, nullptr, 0, nullptr }
    };

    char arg0[] = "prog";
    char arg1[] = "-flag";
    char *argv[] = { arg0, arg1, nullptr };
    int argc = 2;

    bool ok = parseArgs(argTable, &argc, argv);
    EXPECT_TRUE(ok);
    EXPECT_TRUE(flagVal);
    EXPECT_EQ(argc, 1);
}

// Test argInt: parsing an integer argument
TEST_F(ParseArgsTest_2740, IntArgParsesInteger_2740) {
    int intVal = 0;
    const ArgDesc argTable[] = {
        { "-num", argInt, &intVal, 0, "an integer" },
        { nullptr, argFlag, nullptr, 0, nullptr }
    };

    char arg0[] = "prog";
    char arg1[] = "-num";
    char arg2[] = "42";
    char *argv[] = { arg0, arg1, arg2, nullptr };
    int argc = 3;

    bool ok = parseArgs(argTable, &argc, argv);
    EXPECT_TRUE(ok);
    EXPECT_EQ(intVal, 42);
    EXPECT_EQ(argc, 1);
}

// Test argInt: negative integer
TEST_F(ParseArgsTest_2740, IntArgParsesNegativeInteger_2740) {
    int intVal = 0;
    const ArgDesc argTable[] = {
        { "-num", argInt, &intVal, 0, "an integer" },
        { nullptr, argFlag, nullptr, 0, nullptr }
    };

    char arg0[] = "prog";
    char arg1[] = "-num";
    char arg2[] = "-10";
    char *argv[] = { arg0, arg1, arg2, nullptr };
    int argc = 3;

    bool ok = parseArgs(argTable, &argc, argv);
    EXPECT_TRUE(ok);
    EXPECT_EQ(intVal, -10);
    EXPECT_EQ(argc, 1);
}

// Test argInt: missing value after int arg
TEST_F(ParseArgsTest_2740, IntArgMissingValue_2740) {
    int intVal = 99;
    const ArgDesc argTable[] = {
        { "-num", argInt, &intVal, 0, "an integer" },
        { nullptr, argFlag, nullptr, 0, nullptr }
    };

    char arg0[] = "prog";
    char arg1[] = "-num";
    char *argv[] = { arg0, arg1, nullptr };
    int argc = 2;

    bool ok = parseArgs(argTable, &argc, argv);
    EXPECT_FALSE(ok);
    // Value should remain unchanged since parsing failed
    EXPECT_EQ(intVal, 99);
}

// Test argInt: non-integer value after int arg
TEST_F(ParseArgsTest_2740, IntArgNonIntegerValue_2740) {
    int intVal = 99;
    const ArgDesc argTable[] = {
        { "-num", argInt, &intVal, 0, "an integer" },
        { nullptr, argFlag, nullptr, 0, nullptr }
    };

    char arg0[] = "prog";
    char arg1[] = "-num";
    char arg2[] = "abc";
    char *argv[] = { arg0, arg1, arg2, nullptr };
    int argc = 3;

    bool ok = parseArgs(argTable, &argc, argv);
    EXPECT_FALSE(ok);
}

// Test argFP: parsing a floating point argument
TEST_F(ParseArgsTest_2740, FPArgParsesDouble_2740) {
    double fpVal = 0.0;
    const ArgDesc argTable[] = {
        { "-fp", argFP, &fpVal, 0, "a float" },
        { nullptr, argFlag, nullptr, 0, nullptr }
    };

    char arg0[] = "prog";
    char arg1[] = "-fp";
    char arg2[] = "3.14";
    char *argv[] = { arg0, arg1, arg2, nullptr };
    int argc = 3;

    bool ok = parseArgs(argTable, &argc, argv);
    EXPECT_TRUE(ok);
    EXPECT_DOUBLE_EQ(fpVal, 3.14);
    EXPECT_EQ(argc, 1);
}

// Test argFP: missing value
TEST_F(ParseArgsTest_2740, FPArgMissingValue_2740) {
    double fpVal = 1.0;
    const ArgDesc argTable[] = {
        { "-fp", argFP, &fpVal, 0, "a float" },
        { nullptr, argFlag, nullptr, 0, nullptr }
    };

    char arg0[] = "prog";
    char arg1[] = "-fp";
    char *argv[] = { arg0, arg1, nullptr };
    int argc = 2;

    bool ok = parseArgs(argTable, &argc, argv);
    EXPECT_FALSE(ok);
}

// Test argFP: non-FP value
TEST_F(ParseArgsTest_2740, FPArgNonFPValue_2740) {
    double fpVal = 1.0;
    const ArgDesc argTable[] = {
        { "-fp", argFP, &fpVal, 0, "a float" },
        { nullptr, argFlag, nullptr, 0, nullptr }
    };

    char arg0[] = "prog";
    char arg1[] = "-fp";
    char arg2[] = "notanumber";
    char *argv[] = { arg0, arg1, arg2, nullptr };
    int argc = 3;

    bool ok = parseArgs(argTable, &argc, argv);
    EXPECT_FALSE(ok);
}

// Test argString: parsing a string argument
TEST_F(ParseArgsTest_2740, StringArgParsesString_2740) {
    char strVal[256] = "";
    const ArgDesc argTable[] = {
        { "-str", argString, strVal, 256, "a string" },
        { nullptr, argFlag, nullptr, 0, nullptr }
    };

    char arg0[] = "prog";
    char arg1[] = "-str";
    char arg2[] = "hello";
    char *argv[] = { arg0, arg1, arg2, nullptr };
    int argc = 3;

    bool ok = parseArgs(argTable, &argc, argv);
    EXPECT_TRUE(ok);
    EXPECT_STREQ(strVal, "hello");
    EXPECT_EQ(argc, 1);
}

// Test argString: missing value
TEST_F(ParseArgsTest_2740, StringArgMissingValue_2740) {
    char strVal[256] = "original";
    const ArgDesc argTable[] = {
        { "-str", argString, strVal, 256, "a string" },
        { nullptr, argFlag, nullptr, 0, nullptr }
    };

    char arg0[] = "prog";
    char arg1[] = "-str";
    char *argv[] = { arg0, arg1, nullptr };
    int argc = 2;

    bool ok = parseArgs(argTable, &argc, argv);
    EXPECT_FALSE(ok);
}

// Test argString: truncation when string is too long
TEST_F(ParseArgsTest_2740, StringArgTruncatesLongString_2740) {
    char strVal[8] = "";
    const ArgDesc argTable[] = {
        { "-str", argString, strVal, 8, "a string" },
        { nullptr, argFlag, nullptr, 0, nullptr }
    };

    char arg0[] = "prog";
    char arg1[] = "-str";
    char arg2[] = "verylongstring";
    char *argv[] = { arg0, arg1, arg2, nullptr };
    int argc = 3;

    bool ok = parseArgs(argTable, &argc, argv);
    EXPECT_TRUE(ok);
    EXPECT_EQ(strlen(strVal), 7u);
    // Should be null-terminated at position size-1
    EXPECT_EQ(strVal[7], '\0');
}

// Test argGooString: parsing a GooString argument
TEST_F(ParseArgsTest_2740, GooStringArgParsesString_2740) {
    GooString gooVal;
    const ArgDesc argTable[] = {
        { "-goo", argGooString, &gooVal, 0, "a goo string" },
        { nullptr, argFlag, nullptr, 0, nullptr }
    };

    char arg0[] = "prog";
    char arg1[] = "-goo";
    char arg2[] = "world";
    char *argv[] = { arg0, arg1, arg2, nullptr };
    int argc = 3;

    bool ok = parseArgs(argTable, &argc, argv);
    EXPECT_TRUE(ok);
    EXPECT_EQ(gooVal.toStr(), std::string("world"));
    EXPECT_EQ(argc, 1);
}

// Test argGooString: missing value
TEST_F(ParseArgsTest_2740, GooStringArgMissingValue_2740) {
    GooString gooVal("original");
    const ArgDesc argTable[] = {
        { "-goo", argGooString, &gooVal, 0, "a goo string" },
        { nullptr, argFlag, nullptr, 0, nullptr }
    };

    char arg0[] = "prog";
    char arg1[] = "-goo";
    char *argv[] = { arg0, arg1, nullptr };
    int argc = 2;

    bool ok = parseArgs(argTable, &argc, argv);
    EXPECT_FALSE(ok);
}

// Test multiple args combined
TEST_F(ParseArgsTest_2740, MultipleArgsCombined_2740) {
    bool flagVal = false;
    int intVal = 0;
    double fpVal = 0.0;
    char strVal[256] = "";

    const ArgDesc argTable[] = {
        { "-flag", argFlag, &flagVal, 0, "a flag" },
        { "-num", argInt, &intVal, 0, "an integer" },
        { "-fp", argFP, &fpVal, 0, "a float" },
        { "-str", argString, strVal, 256, "a string" },
        { nullptr, argFlag, nullptr, 0, nullptr }
    };

    char arg0[] = "prog";
    char arg1[] = "-flag";
    char arg2[] = "-num";
    char arg3[] = "100";
    char arg4[] = "-fp";
    char arg5[] = "2.718";
    char arg6[] = "-str";
    char arg7[] = "test";
    char *argv[] = { arg0, arg1, arg2, arg3, arg4, arg5, arg6, arg7, nullptr };
    int argc = 8;

    bool ok = parseArgs(argTable, &argc, argv);
    EXPECT_TRUE(ok);
    EXPECT_TRUE(flagVal);
    EXPECT_EQ(intVal, 100);
    EXPECT_DOUBLE_EQ(fpVal, 2.718);
    EXPECT_STREQ(strVal, "test");
    EXPECT_EQ(argc, 1);
}

// Test no args parsed (only program name)
TEST_F(ParseArgsTest_2740, NoArgsParsed_2740) {
    bool flagVal = false;
    const ArgDesc argTable[] = {
        { "-flag", argFlag, &flagVal, 0, "a flag" },
        { nullptr, argFlag, nullptr, 0, nullptr }
    };

    char arg0[] = "prog";
    char *argv[] = { arg0, nullptr };
    int argc = 1;

    bool ok = parseArgs(argTable, &argc, argv);
    EXPECT_TRUE(ok);
    EXPECT_FALSE(flagVal);
    EXPECT_EQ(argc, 1);
}

// Test unknown arg is left in argv
TEST_F(ParseArgsTest_2740, UnknownArgLeftInArgv_2740) {
    bool flagVal = false;
    const ArgDesc argTable[] = {
        { "-flag", argFlag, &flagVal, 0, "a flag" },
        { nullptr, argFlag, nullptr, 0, nullptr }
    };

    char arg0[] = "prog";
    char arg1[] = "-unknown";
    char arg2[] = "file.txt";
    char *argv[] = { arg0, arg1, arg2, nullptr };
    int argc = 3;

    bool ok = parseArgs(argTable, &argc, argv);
    // Unknown args should remain
    EXPECT_TRUE(ok);
    EXPECT_FALSE(flagVal);
}

// Test non-option args remain after parsing
TEST_F(ParseArgsTest_2740, NonOptionArgsRemain_2740) {
    bool flagVal = false;
    const ArgDesc argTable[] = {
        { "-flag", argFlag, &flagVal, 0, "a flag" },
        { nullptr, argFlag, nullptr, 0, nullptr }
    };

    char arg0[] = "prog";
    char arg1[] = "-flag";
    char arg2[] = "file.txt";
    char *argv[] = { arg0, arg1, arg2, nullptr };
    int argc = 3;

    bool ok = parseArgs(argTable, &argc, argv);
    EXPECT_TRUE(ok);
    EXPECT_TRUE(flagVal);
    // "file.txt" should remain
    EXPECT_EQ(argc, 2);
    EXPECT_STREQ(argv[1], "file.txt");
}

// Test argInt with zero
TEST_F(ParseArgsTest_2740, IntArgParsesZero_2740) {
    int intVal = 99;
    const ArgDesc argTable[] = {
        { "-num", argInt, &intVal, 0, "an integer" },
        { nullptr, argFlag, nullptr, 0, nullptr }
    };

    char arg0[] = "prog";
    char arg1[] = "-num";
    char arg2[] = "0";
    char *argv[] = { arg0, arg1, arg2, nullptr };
    int argc = 3;

    bool ok = parseArgs(argTable, &argc, argv);
    EXPECT_TRUE(ok);
    EXPECT_EQ(intVal, 0);
}

// Test argFP with negative value
TEST_F(ParseArgsTest_2740, FPArgParsesNegativeDouble_2740) {
    double fpVal = 0.0;
    const ArgDesc argTable[] = {
        { "-fp", argFP, &fpVal, 0, "a float" },
        { nullptr, argFlag, nullptr, 0, nullptr }
    };

    char arg0[] = "prog";
    char arg1[] = "-fp";
    char arg2[] = "-1.5";
    char *argv[] = { arg0, arg1, arg2, nullptr };
    int argc = 3;

    bool ok = parseArgs(argTable, &argc, argv);
    EXPECT_TRUE(ok);
    EXPECT_DOUBLE_EQ(fpVal, -1.5);
}

// Test argFP with integer-like FP value
TEST_F(ParseArgsTest_2740, FPArgParsesIntegerAsFP_2740) {
    double fpVal = 0.0;
    const ArgDesc argTable[] = {
        { "-fp", argFP, &fpVal, 0, "a float" },
        { nullptr, argFlag, nullptr, 0, nullptr }
    };

    char arg0[] = "prog";
    char arg1[] = "-fp";
    char arg2[] = "5";
    char *argv[] = { arg0, arg1, arg2, nullptr };
    int argc = 3;

    bool ok = parseArgs(argTable, &argc, argv);
    EXPECT_TRUE(ok);
    EXPECT_DOUBLE_EQ(fpVal, 5.0);
}

// Test argString with empty string
TEST_F(ParseArgsTest_2740, StringArgEmptyString_2740) {
    char strVal[256] = "notempty";
    const ArgDesc argTable[] = {
        { "-str", argString, strVal, 256, "a string" },
        { nullptr, argFlag, nullptr, 0, nullptr }
    };

    char arg0[] = "prog";
    char arg1[] = "-str";
    char arg2[] = "";
    char *argv[] = { arg0, arg1, arg2, nullptr };
    int argc = 3;

    bool ok = parseArgs(argTable, &argc, argv);
    EXPECT_TRUE(ok);
    EXPECT_STREQ(strVal, "");
}

// Test argString with size 1 (only null terminator fits)
TEST_F(ParseArgsTest_2740, StringArgSizeOne_2740) {
    char strVal[1] = {};
    const ArgDesc argTable[] = {
        { "-str", argString, strVal, 1, "a string" },
        { nullptr, argFlag, nullptr, 0, nullptr }
    };

    char arg0[] = "prog";
    char arg1[] = "-str";
    char arg2[] = "hello";
    char *argv[] = { arg0, arg1, arg2, nullptr };
    int argc = 3;

    bool ok = parseArgs(argTable, &argc, argv);
    EXPECT_TRUE(ok);
    EXPECT_EQ(strVal[0], '\0');
}
