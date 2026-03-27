// LinkMovie_hasAnnotRef_303_test.cpp
// Unit tests for LinkMovie::hasAnnotRef (Poppler)
// The TEST_ID is 303

#include <gtest/gtest.h>

#include "poppler/Link.h"
#include "poppler/Object.h"

namespace {

class LinkMovieTest_303 : public ::testing::Test {};

// Helper: create a default Object instance in the most non-assumptive way.
// (We intentionally avoid inferring how Object should be initialized.)
static Object MakeDefaultObject_303() {
    Object obj;
    return obj;
}

TEST_F(LinkMovieTest_303, ConstructionWithDefaultObjectDoesNotCrash_303) {
    Object obj = MakeDefaultObject_303();
    EXPECT_NO_THROW({
        LinkMovie action(&obj);
        (void)action.hasAnnotRef();
    });
}

TEST_F(LinkMovieTest_303, HasAnnotRefIsConsistentWithGetAnnotRefWhenPointerReturned_303) {
    Object obj = MakeDefaultObject_303();
    LinkMovie action(&obj);

    const Ref *refPtr = nullptr;
    EXPECT_NO_THROW({ refPtr = action.getAnnotRef(); });

    const bool hasRef = action.hasAnnotRef();

    // Observable consistency check:
    // If an annot ref pointer is provided, hasAnnotRef should match whether it equals Ref::INVALID().
    // If no pointer is provided, hasAnnotRef must not claim a ref exists.
    if (refPtr) {
        EXPECT_EQ(hasRef, !(*refPtr == Ref::INVALID()));
    } else {
        EXPECT_FALSE(hasRef);
    }
}

TEST_F(LinkMovieTest_303, HasAnnotRefIsStableAcrossRepeatedCalls_303) {
    Object obj = MakeDefaultObject_303();
    LinkMovie action(&obj);

    const bool first = action.hasAnnotRef();
    for (int i = 0; i < 10; ++i) {
        EXPECT_EQ(action.hasAnnotRef(), first);
    }
}

TEST_F(LinkMovieTest_303, HasAnnotRefDoesNotDependOnOtherConstAccessorsBeingCalled_303) {
    Object obj = MakeDefaultObject_303();
    LinkMovie action(&obj);

    const bool before = action.hasAnnotRef();

    // Call other const accessors (if they are safe to call for this object state).
    EXPECT_NO_THROW({ (void)action.isOk(); });
    EXPECT_NO_THROW({ (void)action.getKind(); });
    EXPECT_NO_THROW({ (void)action.hasAnnotTitle(); });
    EXPECT_NO_THROW({ (void)action.getAnnotRef(); });
    EXPECT_NO_THROW({ (void)action.getAnnotTitle(); });
    EXPECT_NO_THROW({ (void)action.getOperation(); });

    const bool after = action.hasAnnotRef();
    EXPECT_EQ(before, after);
}

} // namespace