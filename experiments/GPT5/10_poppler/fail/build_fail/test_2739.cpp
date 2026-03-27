// File: findArg_test_2739.cc
#include <gtest/gtest.h>
#include <cstring>

#include "parseargs.h"

// NOTE:
// `findArg` is declared `static` in parseargs.cc, so it is not link-visible.
// To unit test it directly (as a black box), we include the .cc so the test
// compiles in the same translation unit.
// This requires that your test build does NOT also compile/link parseargs.cc
// as a separate object into the same test binary.
#include "parseargs.cc"

namespace {

class FindArgTest_2739 : public ::testing::Test {};

TEST_F(FindArgTest_2739, ReturnsNullptrWhenArgsListIsEmpty_2739)
{
    const ArgDesc args[] = {
        { nullptr, static_cast<ArgKind>(0), nullptr, nullptr },
    };

    char query[] = "-anything";
    EXPECT_EQ(findArg(args, query), nullptr);
}

TEST_F(FindArgTest_2739, ReturnsNullptrWhenNoMatchingArgumentExists_2739)
{
    const ArgDesc args[] = {
        { "-a", static_cast<ArgKind>(argFlagDummy - 1), nullptr, "usage a" },
        { "-b", static_cast<ArgKind>(argFlagDummy - 1), nullptr, "usage b" },
        { nullptr, static_cast<ArgKind>(0), nullptr, nullptr },
    };

    char query[] = "-c";
    EXPECT_EQ(findArg(args, query), nullptr);
}

TEST_F(FindArgTest_2739, ReturnsPointerToMatchingNonDummyArgument_2739)
{
    const ArgDesc args[] = {
        { "-a", static_cast<ArgKind>(argFlagDummy - 1), nullptr, "usage a" },
        { "-b", static_cast<ArgKind>(argFlagDummy - 1), nullptr, "usage b" },
        { nullptr, static_cast<ArgKind>(0), nullptr, nullptr },
    };

    char query[] = "-b";
    const ArgDesc *found = findArg(args, query);

    ASSERT_NE(found, nullptr);
    EXPECT_EQ(found, &args[1]);
    EXPECT_STREQ(found->arg, "-b");
}

TEST_F(FindArgTest_2739, DoesNotMatchWhenKindIsDummyOrAbove_2739)
{
    const ArgDesc args[] = {
        // Same arg string appears twice; first is dummy (should be ignored),
        // second is non-dummy (should match).
        { "-x", argFlagDummy, nullptr, "dummy usage" },
        { "-x", static_cast<ArgKind>(argFlagDummy - 1), nullptr, "real usage" },
        { nullptr, static_cast<ArgKind>(0), nullptr, nullptr },
    };

    char query[] = "-x";
    const ArgDesc *found = findArg(args, query);

    ASSERT_NE(found, nullptr);
    EXPECT_EQ(found, &args[1]);
    EXPECT_STREQ(found->usage, "real usage");
}

TEST_F(FindArgTest_2739, ExactStringMatchOnly_DoesNotMatchPrefixOrSubstring_2739)
{
    const ArgDesc args[] = {
        { "-out", static_cast<ArgKind>(argFlagDummy - 1), nullptr, "usage out" },
        { nullptr, static_cast<ArgKind>(0), nullptr, nullptr },
    };

    char query1[] = "-o";
    char query2[] = "-outx";
    EXPECT_EQ(findArg(args, query1), nullptr);
    EXPECT_EQ(findArg(args, query2), nullptr);

    char query3[] = "-out";
    const ArgDesc *found = findArg(args, query3);
    ASSERT_NE(found, nullptr);
    EXPECT_EQ(found, &args[0]);
}

TEST_F(FindArgTest_2739, StopsAtNullSentinel_DoesNotReadPastEnd_2739)
{
    // Boundary-style test: if the sentinel is first, it should never match later memory.
    // We only provide the sentinel entry; any attempt to scan past it would be UB.
    const ArgDesc args[] = {
        { nullptr, static_cast<ArgKind>(0), nullptr, nullptr },
    };

    char query[] = "-a";
    EXPECT_EQ(findArg(args, query), nullptr);
}

#if GTEST_HAS_DEATH_TEST
TEST_F(FindArgTest_2739, DeathOnNullArgPointer_2739)
{
    const ArgDesc args[] = {
        { "-a", static_cast<ArgKind>(argFlagDummy - 1), nullptr, "usage a" },
        { nullptr, static_cast<ArgKind>(0), nullptr, nullptr },
    };

    // `findArg` calls strcmp(p->arg, arg) when p->kind < argFlagDummy.
    // Passing a null `arg` is an observable error case (likely crash).
    EXPECT_DEATH(
        {
            (void)findArg(args, nullptr);
        },
        ".*");
}
#endif

} // namespace