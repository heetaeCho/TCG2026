// SPDX-License-Identifier: GPL-2.0-or-later
// File: LinkRendition_getScreenAnnot_311_test.cpp
//
// Unit tests for LinkRendition::getScreenAnnot() based strictly on the public interface.
//
// The TEST_ID is 311

#include <gtest/gtest.h>

#include "./TestProjects/poppler/poppler/Link.h"

// Poppler typically provides Object/Ref in these headers; include defensively.
#include "./TestProjects/poppler/poppler/Object.h"

#include <type_traits>
#include <utility>

namespace {

// Try to initialize an Object to null across Poppler versions without relying on internals.
template <typename T>
auto MakeNullObjectImpl(int) -> decltype(std::declval<T &>().initNull(), T{}) {
    T o;
    o.initNull();
    return o;
}

template <typename T>
auto MakeNullObjectImpl(long) -> decltype(std::declval<T &>().setToNull(), T{}) {
    T o;
    o.setToNull();
    return o;
}

template <typename T>
T MakeNullObjectImpl(...) {
    // Best-effort fallback: default-constructed Object is commonly a null/empty object.
    return T{};
}

static Object MakeNullObject() { return MakeNullObjectImpl<Object>(0); }

// Compare Refs without assuming operator== exists.
static void ExpectRefEq(const Ref &a, const Ref &b) {
    EXPECT_EQ(a.num, b.num);
    EXPECT_EQ(a.gen, b.gen);
}

static Ref MakeZeroRef() {
    Ref r{};
    // Common Poppler Ref layout uses num/gen; value-initialization usually sets to 0.
    // Keep this helper to avoid repeating assumptions in tests.
    return r;
}

} // namespace

class LinkRenditionTest_311 : public ::testing::Test {};

TEST_F(LinkRenditionTest_311, GetScreenAnnot_ReturnTypeIsRef_311) {
    static_assert(std::is_same<decltype(std::declval<const LinkRendition &>().getScreenAnnot()), Ref>::value,
                  "LinkRendition::getScreenAnnot() must return Ref by value");
}

TEST_F(LinkRenditionTest_311, GetScreenAnnot_IsStableAcrossMultipleCalls_311) {
    // Construct using a "null" Object in a version-tolerant way.
    const Object obj = MakeNullObject();
    const LinkRendition lr(&obj);

    const Ref r1 = lr.getScreenAnnot();
    const Ref r2 = lr.getScreenAnnot();

    ExpectRefEq(r1, r2);
}

TEST_F(LinkRenditionTest_311, GetScreenAnnot_ConstAndNonConstAccessMatch_311) {
    const Object obj = MakeNullObject();
    LinkRendition lr(&obj);

    const Ref r_nonconst = lr.getScreenAnnot();

    const LinkRendition &clr = lr;
    const Ref r_const = clr.getScreenAnnot();

    ExpectRefEq(r_nonconst, r_const);
}

TEST_F(LinkRenditionTest_311, GetScreenAnnot_OnNullObjectDoesNotChangeFromDefaultOverTime_311) {
    const Object obj = MakeNullObject();
    const LinkRendition lr(&obj);

    // This test does not assume what the value *should* be (e.g., {0,0});
    // it only checks the value is deterministic and does not mutate.
    const Ref r0 = lr.getScreenAnnot();
    const Ref r1 = lr.getScreenAnnot();
    const Ref r2 = lr.getScreenAnnot();

    ExpectRefEq(r0, r1);
    ExpectRefEq(r1, r2);

    // If Poppler uses a zero ref to represent "no screen annot", this should hold;
    // if not, it still passes as long as it is deterministic.
    const Ref zr = MakeZeroRef();
    (void)zr; // keep helper referenced without asserting semantics.
}