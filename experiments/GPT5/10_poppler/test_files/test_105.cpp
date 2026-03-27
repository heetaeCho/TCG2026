// Object_getRefNum_105_test.cpp
#include <gtest/gtest.h>

#include <climits>
#include <type_traits>
#include <utility>

#include "poppler/Object.h"

// Helper: detect whether Object is constructible from Ref in this build.
template <typename = void>
struct HasRefCtor : std::false_type {};
template <>
struct HasRefCtor<std::void_t<decltype(Object(std::declval<Ref>()))>> : std::true_type {};

static Object MakeRefObjectOrSkip(int num, int gen)
{
    if constexpr (HasRefCtor<>::value) {
        Ref r;
        r.num = num;
        r.gen = gen;
        return Object(r);
    } else {
        GTEST_SKIP() << "This build of poppler::Object does not appear to expose a public Object(Ref) constructor.";
        return Object::null(); // unreachable after skip, but keeps compilers happy
    }
}

class ObjectGetRefNumTest_105 : public ::testing::Test
{
};

TEST_F(ObjectGetRefNumTest_105, ReturnsNumForValidRef_105)
{
    Object o = MakeRefObjectOrSkip(123, 0);
    EXPECT_EQ(o.getRefNum(), 123);
}

TEST_F(ObjectGetRefNumTest_105, BoundaryNumZero_105)
{
    Object o = MakeRefObjectOrSkip(0, 0);
    EXPECT_EQ(o.getRefNum(), 0);
}

TEST_F(ObjectGetRefNumTest_105, BoundaryNumIntMax_105)
{
    Object o = MakeRefObjectOrSkip(INT_MAX, 1);
    EXPECT_EQ(o.getRefNum(), INT_MAX);
}

TEST_F(ObjectGetRefNumTest_105, MovePreservesRefNum_105)
{
    Object src = MakeRefObjectOrSkip(77, 9);
    Object moved(std::move(src));
    EXPECT_EQ(moved.getRefNum(), 77);
}

TEST_F(ObjectGetRefNumTest_105, DiesWhenCalledOnNonRefType_105)
{
#if defined(NDEBUG)
    GTEST_SKIP() << "Type checks may be compiled out in release (NDEBUG) builds.";
#else
    // Use a definitely-non-ref object.
    Object notRef(42);

#if GTEST_HAS_DEATH_TEST
    EXPECT_DEATH_IF_SUPPORTED(
        {
            (void)notRef.getRefNum();
        },
        "");
#else
    GTEST_SKIP() << "Death tests are not supported in this test environment.";
#endif
#endif
}