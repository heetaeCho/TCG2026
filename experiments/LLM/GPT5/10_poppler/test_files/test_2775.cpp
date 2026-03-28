// poppler-page-transition-data-test_2775.cc
#include <gtest/gtest.h>

#include "Object.h"

// PageTransitionData is defined in the .cc (per provided snippet). Include the implementation
// to make the class visible to this test TU.
#include "poppler-page-transition.cc"

namespace Poppler {

class PageTransitionDataTest_2775 : public ::testing::Test {
protected:
    // Helper to build a few representative Objects to pass as transition sources.
    static Object MakeNullObj()
    {
        return Object::null();
    }
    static Object MakeErrorObj()
    {
        return Object::error();
    }
    static Object MakeIntObj(int v)
    {
        return Object(v);
    }
};

TEST_F(PageTransitionDataTest_2775, CtorWithNullObjectCreatesPt_2775)
{
    Object trans = MakeNullObj();
    PageTransitionData ptd(&trans);

    // Observable behavior: public pointer exists.
    EXPECT_NE(ptd.pt, nullptr);
}

TEST_F(PageTransitionDataTest_2775, CtorWithErrorObjectCreatesPt_2775)
{
    Object trans = MakeErrorObj();
    PageTransitionData ptd(&trans);

    EXPECT_NE(ptd.pt, nullptr);
}

TEST_F(PageTransitionDataTest_2775, CtorWithNonDictNonNullObjectCreatesPt_2775)
{
    // Boundary-ish: give a non-dict type (int). We don't assume how it is interpreted,
    // only that construction is safe and yields an allocated transition object.
    Object trans = MakeIntObj(123);
    PageTransitionData ptd(&trans);

    EXPECT_NE(ptd.pt, nullptr);
}

TEST_F(PageTransitionDataTest_2775, CopyCtorProducesUsableObject_2775)
{
    Object trans = MakeNullObj();
    PageTransitionData original(&trans);

    PageTransitionData copy(original);

    EXPECT_NE(original.pt, nullptr);
    EXPECT_NE(copy.pt, nullptr);

    // Do NOT assume deep vs shallow copy semantics; only require both are usable.
}

TEST_F(PageTransitionDataTest_2775, DestructionDoesNotCrash_2775)
{
    Object trans = MakeNullObj();

    // Exercise ctor + dtor path explicitly.
    auto *ptd = new PageTransitionData(&trans);
    ASSERT_NE(ptd->pt, nullptr);
    delete ptd;
}

TEST_F(PageTransitionDataTest_2775, CtorWithNullptrDeathOrCrash_2775)
{
    // Exceptional/error case: passing nullptr is invalid for many APIs.
    // We don't infer implementation details; we only assert that the program
    // either terminates (assert/abort) under death-test, or we skip if unsupported.
#if GTEST_HAS_DEATH_TEST
    EXPECT_DEATH_IF_SUPPORTED(
        {
            PageTransitionData ptd(nullptr);
            (void)ptd;
        },
        "");
#else
    GTEST_SKIP() << "Death tests are not supported on this platform/configuration.";
#endif
}

} // namespace Poppler