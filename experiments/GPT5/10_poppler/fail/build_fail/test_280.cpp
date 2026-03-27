// TEST_ID: 280
// Unit tests for LinkDest::getChangeTop()
// File: ./TestProjects/poppler/poppler/Link.h

#include <gtest/gtest.h>

#include "Link.h"
#include "Array.h"
#include "Object.h"

namespace {

Array makeDestArrayXYZ(Object &&page, Object &&left, Object &&top, Object &&zoom)
{
    Array a(nullptr);
    a.add(std::move(page));
    a.add(Object(objName, "XYZ"));
    a.add(std::move(left));
    a.add(std::move(top));
    a.add(std::move(zoom));
    return a;
}

} // namespace

class LinkDestTest_280 : public ::testing::Test
{
};

// Normal operation (when isOk() is true) + basic accessor behavior.
TEST_F(LinkDestTest_280, GetChangeTop_RepeatedCallsAreStable_WhenOk_280)
{
    Array a = makeDestArrayXYZ(Object(1), Object(10.0), Object(20.0), Object(1.25));
    LinkDest d(&a);

    ASSERT_TRUE(d.isOk());

    const bool v1 = d.getChangeTop();
    const bool v2 = d.getChangeTop();
    EXPECT_EQ(v1, v2);

    // Calling other getters should not affect the value (observable stability).
    (void)d.getKind();
    (void)d.getLeft();
    (void)d.getTop();
    (void)d.getZoom();

    const bool v3 = d.getChangeTop();
    EXPECT_EQ(v1, v3);
}

// Boundary-ish: allow unusual numeric values; regardless of ok-ness, calling accessor must be safe and stable.
TEST_F(LinkDestTest_280, GetChangeTop_HandlesExtremeTopValue_280)
{
    Array a = makeDestArrayXYZ(Object(1), Object(0.0), Object(1e300), Object(0.0));
    LinkDest d(&a);

    const bool v1 = d.getChangeTop();
    const bool v2 = d.getChangeTop();
    EXPECT_EQ(v1, v2);
}

// Boundary-ish: null / omitted-like input. Do not assume semantics; just ensure callable and stable.
TEST_F(LinkDestTest_280, GetChangeTop_WithNullTop_IsCallableAndStable_280)
{
    Array a = makeDestArrayXYZ(Object(1), Object(10.0), Object(objNull), Object(1.0));
    LinkDest d(&a);

    const bool v1 = d.getChangeTop();
    const bool v2 = d.getChangeTop();
    EXPECT_EQ(v1, v2);

    // If it did parse successfully, basic accessors should also be callable.
    if (d.isOk()) {
        (void)d.getKind();
        (void)d.getTop();
    }
}

// Exceptional/error case: empty array (likely invalid). Accessor should still be callable without relying on internals.
TEST_F(LinkDestTest_280, GetChangeTop_OnInvalidEmptyArray_IsCallableAndStable_280)
{
    Array a(nullptr); // empty
    LinkDest d(&a);

    const bool v1 = d.getChangeTop();
    const bool v2 = d.getChangeTop();
    EXPECT_EQ(v1, v2);
}

// Const-correctness / external observable behavior: callable through const ref and value stable across copies.
TEST_F(LinkDestTest_280, GetChangeTop_CallableOnConstRef_AndPreservedOnCopy_280)
{
    Array a = makeDestArrayXYZ(Object(1), Object(5.0), Object(6.0), Object(2.0));
    LinkDest d(&a);

    const LinkDest &cd = d;
    const bool v1 = cd.getChangeTop();
    const bool v2 = cd.getChangeTop();
    EXPECT_EQ(v1, v2);

    // Copy (if supported by the class) should preserve observable getter result.
    LinkDest copy = d;
    EXPECT_EQ(copy.getChangeTop(), v1);
    EXPECT_EQ(copy.isOk(), d.isOk());
    if (d.isOk()) {
        EXPECT_EQ(copy.getKind(), d.getKind());
    }
}