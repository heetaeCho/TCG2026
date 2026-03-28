// TEST_ID = 305
// File: link_movie_getannotref_ut_305.cpp

#include <gtest/gtest.h>

#include "poppler/Link.h"
#include "poppler/Object.h"
#include "poppler/Ref.h"

namespace {

// Helper: create an "empty / null-like" Object without assuming internals.
// Many Poppler Object implementations default-construct to a null object.
static Object MakeDefaultObject()
{
    Object obj;
    return obj;
}

class LinkMovieTest_305 : public ::testing::Test {
protected:
    Object obj_ = MakeDefaultObject();
};

} // namespace

TEST_F(LinkMovieTest_305, GetAnnotRef_ReturnsNonNullPointer_305)
{
    LinkMovie lm(&obj_);

    const Ref *refPtr = lm.getAnnotRef();
    ASSERT_NE(refPtr, nullptr);
}

TEST_F(LinkMovieTest_305, GetAnnotRef_ReturnsStablePointerAcrossCalls_305)
{
    LinkMovie lm(&obj_);

    const Ref *p1 = lm.getAnnotRef();
    const Ref *p2 = lm.getAnnotRef();
    const Ref *p3 = lm.getAnnotRef();

    ASSERT_NE(p1, nullptr);
    EXPECT_EQ(p1, p2);
    EXPECT_EQ(p2, p3);
}

TEST_F(LinkMovieTest_305, GetAnnotRef_CanBeCalledOnConstInstance_305)
{
    LinkMovie lm(&obj_);
    const LinkMovie &clm = lm;

    const Ref *p1 = clm.getAnnotRef();
    const Ref *p2 = clm.getAnnotRef();

    ASSERT_NE(p1, nullptr);
    EXPECT_EQ(p1, p2);
}

TEST_F(LinkMovieTest_305, GetAnnotRef_CallIsSafeRegardlessOfIsOk_305)
{
    // Boundary / error-style scenario: constructed from a default Object.
    // We do NOT assume whether this makes the action "ok" or not; we only
    // verify the getter is callable and returns a non-null pointer.
    LinkMovie lm(&obj_);

    (void)lm.isOk(); // observable query; result not asserted (black-box)
    const Ref *p = lm.getAnnotRef();
    ASSERT_NE(p, nullptr);
}

TEST_F(LinkMovieTest_305, GetAnnotRef_DoesNotDependOnHasAnnotRefQuery_305)
{
    LinkMovie lm(&obj_);

    // We don't assume the value of hasAnnotRef(); we just ensure calling it
    // does not affect getAnnotRef() pointer stability (observable behavior).
    const Ref *before = lm.getAnnotRef();
    ASSERT_NE(before, nullptr);

    (void)lm.hasAnnotRef();

    const Ref *after = lm.getAnnotRef();
    ASSERT_NE(after, nullptr);
    EXPECT_EQ(before, after);
}