#include <gtest/gtest.h>
#include <cstring>
#include <cstdlib>

// Include the header for parseargs
#include "parseargs.h"

// We need the full ArgDesc struct and parseArgs function declaration
// Based on the partial code, we can see parseArgs signature and ArgDesc usage

// Helper function to create argv-style arrays
class ParseArgsTest_2737 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}

    // Helper to create a modifiable argv array from string literals
    void makeArgv(const std::vector<std::string>& strs) {
        argStorage = strs;
        argvPtrs.clear();
        for (auto& s : argStorage) {
            argvPtrs.push_back(const_cast<char*>(s.c_str()));
        }
        argvPtrs.push_back(nullptr);
        testArgc = static_cast<int>(strs.size());
        testArgv = argvPtrs.data();
    }

    std::vector<std::string> argStorage;
    std::vector<char*> argvPtrs;
    int testArgc;
    char** testArgv;
};

// Test: No arguments besides program name
TEST_F(ParseArgsTest_2737, NoArguments_2737) {
    int intVal = 0;
    ArgDesc args[] = {
        { "-n", argInt, &intVal, 0, "an integer" },
        { nullptr }
    };

    makeArgv({"program"});
    bool result = parseArgs(args, &testArgc, testArgv);
    EXPECT_TRUE(result);
    EXPECT_EQ(testArgc, 1);
    EXPECT_EQ(intVal, 0);
}

// Test: Parse a single integer argument
TEST_F(ParseArgsTest_2737, SingleIntArg_2737) {
    int intVal = 0;
    ArgDesc args[] = {
        { "-n", argInt, &intVal, 0, "an integer" },
        { nullptr }
    };

    makeArgv({"program", "-n", "42"});
    bool result = parseArgs(args, &testArgc, testArgv);
    EXPECT_TRUE(result);
    EXPECT_EQ(intVal, 42);
}

// Test: Parse a string argument
TEST_F(ParseArgsTest_2737, SingleStringArg_2737) {
    char stringVal[256] = "";
    ArgDesc args[] = {
        { "-s", argString, stringVal, sizeof(stringVal), "a string" },
        { nullptr }
    };

    makeArgv({"program", "-s", "hello"});
    bool result = parseArgs(args, &testArgc, testArgv);
    EXPECT_TRUE(result);
    EXPECT_STREQ(stringVal, "hello");
}

// Test: Parse a flag/boolean argument
TEST_F(ParseArgsTest_2737, FlagArg_2737) {
    bool flagVal = false;
    ArgDesc args[] = {
        { "-f", argFlag, &flagVal, 0, "a flag" },
        { nullptr }
    };

    makeArgv({"program", "-f"});
    bool result = parseArgs(args, &testArgc, testArgv);
    EXPECT_TRUE(result);
    EXPECT_TRUE(flagVal);
}

// Test: Double dash stops argument parsing
TEST_F(ParseArgsTest_2737, DoubleDashStopsParsing_2737) {
    int intVal = 0;
    ArgDesc args[] = {
        { "-n", argInt, &intVal, 0, "an integer" },
        { nullptr }
    };

    makeArgv({"program", "--", "-n", "42"});
    bool result = parseArgs(args, &testArgc, testArgv);
    EXPECT_TRUE(result);
    EXPECT_EQ(intVal, 0);
    // After --, the remaining args should be shifted and -- removed
}

// Test: Unknown argument is left in argv
TEST_F(ParseArgsTest_2737, UnknownArgLeftInArgv_2737) {
    int intVal = 0;
    ArgDesc args[] = {
        { "-n", argInt, &intVal, 0, "an integer" },
        { nullptr }
    };

    makeArgv({"program", "-x", "foo"});
    bool result = parseArgs(args, &testArgc, testArgv);
    EXPECT_TRUE(result);
    // Unknown args should remain
    EXPECT_EQ(testArgc, 3);
}

// Test: Parse a double/floating point argument
TEST_F(ParseArgsTest_2737, SingleFPArg_2737) {
    double fpVal = 0.0;
    ArgDesc args[] = {
        { "-d", argFP, &fpVal, 0, "a double" },
        { nullptr }
    };

    makeArgv({"program", "-d", "3.14"});
    bool result = parseArgs(args, &testArgc, testArgv);
    EXPECT_TRUE(result);
    EXPECT_NEAR(fpVal, 3.14, 0.001);
}

// Test: Multiple arguments parsed together
TEST_F(ParseArgsTest_2737, MultipleArgs_2737) {
    int intVal = 0;
    bool flagVal = false;
    double fpVal = 0.0;
    ArgDesc args[] = {
        { "-n", argInt, &intVal, 0, "an integer" },
        { "-f", argFlag, &flagVal, 0, "a flag" },
        { "-d", argFP, &fpVal, 0, "a double" },
        { nullptr }
    };

    makeArgv({"program", "-n", "10", "-f", "-d", "2.5"});
    bool result = parseArgs(args, &testArgc, testArgv);
    EXPECT_TRUE(result);
    EXPECT_EQ(intVal, 10);
    EXPECT_TRUE(flagVal);
    EXPECT_NEAR(fpVal, 2.5, 0.001);
}

// Test: Integer argument missing value
TEST_F(ParseArgsTest_2737, IntArgMissingValue_2737) {
    int intVal = 0;
    ArgDesc args[] = {
        { "-n", argInt, &intVal, 0, "an integer" },
        { nullptr }
    };

    makeArgv({"program", "-n"});
    bool result = parseArgs(args, &testArgc, testArgv);
    // Should return false because -n requires a value but none is provided
    EXPECT_FALSE(result);
}

// Test: String argument missing value
TEST_F(ParseArgsTest_2737, StringArgMissingValue_2737) {
    char stringVal[256] = "";
    ArgDesc args[] = {
        { "-s", argString, stringVal, sizeof(stringVal), "a string" },
        { nullptr }
    };

    makeArgv({"program", "-s"});
    bool result = parseArgs(args, &testArgc, testArgv);
    EXPECT_FALSE(result);
}

// Test: FP argument missing value
TEST_F(ParseArgsTest_2737, FPArgMissingValue_2737) {
    double fpVal = 0.0;
    ArgDesc args[] = {
        { "-d", argFP, &fpVal, 0, "a double" },
        { nullptr }
    };

    makeArgv({"program", "-d"});
    bool result = parseArgs(args, &testArgc, testArgv);
    EXPECT_FALSE(result);
}

// Test: Empty args list (no defined args)
TEST_F(ParseArgsTest_2737, EmptyArgDescList_2737) {
    ArgDesc args[] = {
        { nullptr }
    };

    makeArgv({"program", "-x"});
    bool result = parseArgs(args, &testArgc, testArgv);
    EXPECT_TRUE(result);
    // -x is unknown, should remain
    EXPECT_EQ(testArgc, 2);
}

// Test: Negative integer argument
TEST_F(ParseArgsTest_2737, NegativeIntArg_2737) {
    int intVal = 0;
    ArgDesc args[] = {
        { "-n", argInt, &intVal, 0, "an integer" },
        { nullptr }
    };

    makeArgv({"program", "-n", "-5"});
    bool result = parseArgs(args, &testArgc, testArgv);
    // This might or might not work depending on implementation
    // -5 could be interpreted as a flag. We just check behavior.
    // If the implementation treats -5 as the integer value:
    if (result) {
        EXPECT_EQ(intVal, -5);
    }
}

// Test: Known args are removed from argv
TEST_F(ParseArgsTest_2737, KnownArgsRemovedFromArgv_2737) {
    int intVal = 0;
    ArgDesc args[] = {
        { "-n", argInt, &intVal, 0, "an integer" },
        { nullptr }
    };

    makeArgv({"program", "-n", "42", "file.txt"});
    bool result = parseArgs(args, &testArgc, testArgv);
    EXPECT_TRUE(result);
    EXPECT_EQ(intVal, 42);
    // After parsing, argc should be reduced and "file.txt" should remain
    EXPECT_EQ(testArgc, 2);
    EXPECT_STREQ(testArgv[0], "program");
    EXPECT_STREQ(testArgv[1], "file.txt");
}

// Test: Multiple known and unknown args intermixed
TEST_F(ParseArgsTest_2737, MixedKnownAndUnknownArgs_2737) {
    int intVal = 0;
    bool flagVal = false;
    ArgDesc args[] = {
        { "-n", argInt, &intVal, 0, "an integer" },
        { "-f", argFlag, &flagVal, 0, "a flag" },
        { nullptr }
    };

    makeArgv({"program", "unknown1", "-n", "7", "unknown2", "-f"});
    bool result = parseArgs(args, &testArgc, testArgv);
    EXPECT_TRUE(result);
    EXPECT_EQ(intVal, 7);
    EXPECT_TRUE(flagVal);
    // Unknown args should remain: program, unknown1, unknown2
    EXPECT_EQ(testArgc, 3);
}

// Test: Double dash with no subsequent args
TEST_F(ParseArgsTest_2737, DoubleDashNoFollowingArgs_2737) {
    int intVal = 0;
    ArgDesc args[] = {
        { "-n", argInt, &intVal, 0, "an integer" },
        { nullptr }
    };

    makeArgv({"program", "--"});
    bool result = parseArgs(args, &testArgc, testArgv);
    EXPECT_TRUE(result);
    EXPECT_EQ(testArgc, 1);
}

// Test: Same argument specified twice - second value overwrites
TEST_F(ParseArgsTest_2737, DuplicateArg_2737) {
    int intVal = 0;
    ArgDesc args[] = {
        { "-n", argInt, &intVal, 0, "an integer" },
        { nullptr }
    };

    makeArgv({"program", "-n", "10", "-n", "20"});
    bool result = parseArgs(args, &testArgc, testArgv);
    EXPECT_TRUE(result);
    EXPECT_EQ(intVal, 20);
}

// Test: Zero integer value
TEST_F(ParseArgsTest_2737, ZeroIntArg_2737) {
    int intVal = 99;
    ArgDesc args[] = {
        { "-n", argInt, &intVal, 0, "an integer" },
        { nullptr }
    };

    makeArgv({"program", "-n", "0"});
    bool result = parseArgs(args, &testArgc, testArgv);
    EXPECT_TRUE(result);
    EXPECT_EQ(intVal, 0);
}

// Test: Only program name, no other args
TEST_F(ParseArgsTest_2737, OnlyProgramName_2737) {
    ArgDesc args[] = {
        { nullptr }
    };

    makeArgv({"program"});
    bool result = parseArgs(args, &testArgc, testArgv);
    EXPECT_TRUE(result);
    EXPECT_EQ(testArgc, 1);
}
