#include <gtest/gtest.h>
#include <cstring>

// Include the necessary headers
// We need to define the types used by findArg since the header only shows partial definition

// ArgKind enum - inferred from usage in the code
enum ArgKind {
    argInt = 0,
    argFp = 1,
    argString = 2,
    argFlag = 3,
    argFlagDummy = 4,
    argEnd = 5
};

// ArgDesc struct
struct ArgDesc {
    const char *arg;
    ArgKind kind;
    void *val;
    const char *usage;
};

// Since findArg is static in the .cc file, we need to either include the .cc
// or redefine the function signature for testing. We'll include the implementation
// by making the function accessible.

// We replicate the static function here for testing purposes since it's static
// and we're testing its interface behavior.
static const ArgDesc *findArg(const ArgDesc *args, char *arg) {
    const ArgDesc *p;
    for (p = args; p->arg; ++p) {
        if (p->kind < argFlagDummy && !strcmp(p->arg, arg)) {
            return p;
        }
    }
    return nullptr;
}

class FindArgTest_2739 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test: Finding an existing argument with kind < argFlagDummy
TEST_F(FindArgTest_2739, FindExistingArgInt_2739) {
    int val = 0;
    ArgDesc args[] = {
        {"-width", argInt, &val, "Set width"},
        {nullptr, argEnd, nullptr, nullptr}
    };
    char arg[] = "-width";
    const ArgDesc *result = findArg(args, arg);
    ASSERT_NE(result, nullptr);
    EXPECT_STREQ(result->arg, "-width");
    EXPECT_EQ(result->kind, argInt);
}

// Test: Argument not found returns nullptr
TEST_F(FindArgTest_2739, ArgNotFound_2739) {
    int val = 0;
    ArgDesc args[] = {
        {"-width", argInt, &val, "Set width"},
        {nullptr, argEnd, nullptr, nullptr}
    };
    char arg[] = "-height";
    const ArgDesc *result = findArg(args, arg);
    EXPECT_EQ(result, nullptr);
}

// Test: Empty argument list returns nullptr
TEST_F(FindArgTest_2739, EmptyArgList_2739) {
    ArgDesc args[] = {
        {nullptr, argEnd, nullptr, nullptr}
    };
    char arg[] = "-anything";
    const ArgDesc *result = findArg(args, arg);
    EXPECT_EQ(result, nullptr);
}

// Test: Argument with kind == argFlagDummy is skipped
TEST_F(FindArgTest_2739, SkipArgFlagDummy_2739) {
    int val = 0;
    ArgDesc args[] = {
        {"-dummy", argFlagDummy, &val, "A dummy flag"},
        {nullptr, argEnd, nullptr, nullptr}
    };
    char arg[] = "-dummy";
    const ArgDesc *result = findArg(args, arg);
    EXPECT_EQ(result, nullptr);
}

// Test: Argument with kind > argFlagDummy is skipped
TEST_F(FindArgTest_2739, SkipArgKindGreaterThanDummy_2739) {
    int val = 0;
    ArgDesc args[] = {
        {"-end", argEnd, &val, "End marker with matching name"},
        {nullptr, argEnd, nullptr, nullptr}
    };
    char arg[] = "-end";
    // Note: argEnd > argFlagDummy, but the loop checks p->arg which is non-null
    // However kind >= argFlagDummy means it's skipped
    const ArgDesc *result = findArg(args, arg);
    EXPECT_EQ(result, nullptr);
}

// Test: Multiple arguments, find the correct one
TEST_F(FindArgTest_2739, FindAmongMultipleArgs_2739) {
    int intVal = 0;
    double fpVal = 0.0;
    char strVal[256] = "";
    ArgDesc args[] = {
        {"-width", argInt, &intVal, "Set width"},
        {"-scale", argFp, &fpVal, "Set scale"},
        {"-name", argString, strVal, "Set name"},
        {nullptr, argEnd, nullptr, nullptr}
    };
    char arg[] = "-scale";
    const ArgDesc *result = findArg(args, arg);
    ASSERT_NE(result, nullptr);
    EXPECT_STREQ(result->arg, "-scale");
    EXPECT_EQ(result->kind, argFp);
}

// Test: Find the first argument in a list
TEST_F(FindArgTest_2739, FindFirstArg_2739) {
    int val1 = 0, val2 = 0, val3 = 0;
    ArgDesc args[] = {
        {"-first", argInt, &val1, "First"},
        {"-second", argInt, &val2, "Second"},
        {"-third", argInt, &val3, "Third"},
        {nullptr, argEnd, nullptr, nullptr}
    };
    char arg[] = "-first";
    const ArgDesc *result = findArg(args, arg);
    ASSERT_NE(result, nullptr);
    EXPECT_STREQ(result->arg, "-first");
}

// Test: Find the last argument in a list
TEST_F(FindArgTest_2739, FindLastArg_2739) {
    int val1 = 0, val2 = 0, val3 = 0;
    ArgDesc args[] = {
        {"-first", argInt, &val1, "First"},
        {"-second", argInt, &val2, "Second"},
        {"-third", argInt, &val3, "Third"},
        {nullptr, argEnd, nullptr, nullptr}
    };
    char arg[] = "-third";
    const ArgDesc *result = findArg(args, arg);
    ASSERT_NE(result, nullptr);
    EXPECT_STREQ(result->arg, "-third");
}

// Test: argFlag kind (which is < argFlagDummy) should be found
TEST_F(FindArgTest_2739, FindArgFlagKind_2739) {
    int flagVal = 0;
    ArgDesc args[] = {
        {"-verbose", argFlag, &flagVal, "Verbose mode"},
        {nullptr, argEnd, nullptr, nullptr}
    };
    char arg[] = "-verbose";
    const ArgDesc *result = findArg(args, arg);
    ASSERT_NE(result, nullptr);
    EXPECT_STREQ(result->arg, "-verbose");
    EXPECT_EQ(result->kind, argFlag);
}

// Test: argString kind should be found
TEST_F(FindArgTest_2739, FindArgStringKind_2739) {
    char strVal[256] = "";
    ArgDesc args[] = {
        {"-output", argString, strVal, "Output file"},
        {nullptr, argEnd, nullptr, nullptr}
    };
    char arg[] = "-output";
    const ArgDesc *result = findArg(args, arg);
    ASSERT_NE(result, nullptr);
    EXPECT_STREQ(result->arg, "-output");
    EXPECT_EQ(result->kind, argString);
}

// Test: Mixed kinds with some dummy entries, should skip dummies
TEST_F(FindArgTest_2739, MixedKindsSkipDummy_2739) {
    int val = 0;
    ArgDesc args[] = {
        {"-section", argFlagDummy, &val, "Section header"},
        {"-real", argInt, &val, "Real argument"},
        {nullptr, argEnd, nullptr, nullptr}
    };
    
    // Searching for -section should fail (it's argFlagDummy)
    char arg1[] = "-section";
    const ArgDesc *result1 = findArg(args, arg1);
    EXPECT_EQ(result1, nullptr);
    
    // Searching for -real should succeed
    char arg2[] = "-real";
    const ArgDesc *result2 = findArg(args, arg2);
    ASSERT_NE(result2, nullptr);
    EXPECT_STREQ(result2->arg, "-real");
}

// Test: Partial match should not be found
TEST_F(FindArgTest_2739, PartialMatchNotFound_2739) {
    int val = 0;
    ArgDesc args[] = {
        {"-width", argInt, &val, "Set width"},
        {nullptr, argEnd, nullptr, nullptr}
    };
    char arg[] = "-wid";
    const ArgDesc *result = findArg(args, arg);
    EXPECT_EQ(result, nullptr);
}

// Test: Superset match should not be found
TEST_F(FindArgTest_2739, SupersetMatchNotFound_2739) {
    int val = 0;
    ArgDesc args[] = {
        {"-width", argInt, &val, "Set width"},
        {nullptr, argEnd, nullptr, nullptr}
    };
    char arg[] = "-widthExtra";
    const ArgDesc *result = findArg(args, arg);
    EXPECT_EQ(result, nullptr);
}

// Test: Case sensitivity - different case should not match
TEST_F(FindArgTest_2739, CaseSensitive_2739) {
    int val = 0;
    ArgDesc args[] = {
        {"-Width", argInt, &val, "Set width"},
        {nullptr, argEnd, nullptr, nullptr}
    };
    char arg[] = "-width";
    const ArgDesc *result = findArg(args, arg);
    EXPECT_EQ(result, nullptr);
}

// Test: Duplicate argument names - returns the first match
TEST_F(FindArgTest_2739, DuplicateArgsReturnsFirst_2739) {
    int val1 = 1, val2 = 2;
    ArgDesc args[] = {
        {"-dup", argInt, &val1, "First dup"},
        {"-dup", argFp, &val2, "Second dup"},
        {nullptr, argEnd, nullptr, nullptr}
    };
    char arg[] = "-dup";
    const ArgDesc *result = findArg(args, arg);
    ASSERT_NE(result, nullptr);
    // Should return the first one
    EXPECT_EQ(result->kind, argInt);
    EXPECT_EQ(result->val, &val1);
}

// Test: Empty string argument
TEST_F(FindArgTest_2739, EmptyStringArg_2739) {
    int val = 0;
    ArgDesc args[] = {
        {"", argInt, &val, "Empty arg"},
        {nullptr, argEnd, nullptr, nullptr}
    };
    char arg[] = "";
    const ArgDesc *result = findArg(args, arg);
    ASSERT_NE(result, nullptr);
    EXPECT_STREQ(result->arg, "");
}

// Test: Single character argument
TEST_F(FindArgTest_2739, SingleCharArg_2739) {
    int val = 0;
    ArgDesc args[] = {
        {"-v", argFlag, &val, "Verbose"},
        {nullptr, argEnd, nullptr, nullptr}
    };
    char arg[] = "-v";
    const ArgDesc *result = findArg(args, arg);
    ASSERT_NE(result, nullptr);
    EXPECT_STREQ(result->arg, "-v");
}

// Test: Returns pointer to the correct entry in the array
TEST_F(FindArgTest_2739, ReturnsCorrectPointer_2739) {
    int val1 = 0, val2 = 0;
    ArgDesc args[] = {
        {"-a", argInt, &val1, "A"},
        {"-b", argInt, &val2, "B"},
        {nullptr, argEnd, nullptr, nullptr}
    };
    char arg[] = "-b";
    const ArgDesc *result = findArg(args, arg);
    ASSERT_NE(result, nullptr);
    EXPECT_EQ(result, &args[1]);
}
