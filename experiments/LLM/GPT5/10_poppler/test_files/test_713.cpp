// TEST_ID: 713
// File: Page_getRotate_test_713.cpp

#include <gtest/gtest.h>

#include "Page.h"

// Poppler core types used to build minimal page/attrs dictionaries.
#include "Object.h"
#include "Dict.h"
#include "Array.h"
#include "XRef.h"

using namespace std;

namespace {

Object makeIntObj(int v)
{
    Object o;
    o.initInt(v);
    return o;
}

Object makeRealObj(double v)
{
    Object o;
    o.initReal(v);
    return o;
}

Object makeBoxArrayObj(XRef *xref, double x1, double y1, double x2, double y2)
{
    auto *arr = new Array(xref);
    arr->add(makeRealObj(x1));
    arr->add(makeRealObj(y1));
    arr->add(makeRealObj(x2));
    arr->add(makeRealObj(y2));

    Object o;
    o.initArray(arr);
    return o;
}

// Create a minimal Dict suitable for PageAttrs construction.
// We always provide /MediaBox because many PDF attribute readers expect it.
// /Rotate is optional and can be provided by tests.
unique_ptr<Dict> makeAttrsDictWithMediaBoxAndOptionalRotate(XRef *xref, const optional<int> rotate)
{
    auto dict = std::make_unique<Dict>(xref);

    // Minimal valid MediaBox: [0 0 612 792] (US Letter in points), but any rectangle works.
    dict->add("MediaBox", makeBoxArrayObj(xref, 0, 0, 612, 792));

    if (rotate.has_value()) {
        dict->add("Rotate", makeIntObj(*rotate));
    }

    return dict;
}

// Build a Page object where getRotate() is observable.
// We construct PageAttrs first, record its public getRotate() result, then move it into Page.
// This tests that Page::getRotate forwards to PageAttrs::getRotate without peeking into internals.
struct PageAndExpectedRotate {
    unique_ptr<Page> page;
    int expectedRotate;
};

PageAndExpectedRotate makePageWithAttrsDict(unique_ptr<Dict> attrsDict)
{
    // PageAttrs reads from the provided dict (and optionally inherits from parent attrs; we pass nullptr).
    auto attrs = std::make_unique<PageAttrs>(nullptr, attrsDict.get());
    const int expected = attrs->getRotate();

    // Minimal page dictionary object. For this test, we keep it empty; Page::getRotate should not depend on it.
    // (We still provide a dict object to satisfy typical Page construction expectations.)
    auto pageDict = std::make_unique<Dict>(nullptr);
    Object pageDictObj;
    pageDictObj.initDict(pageDict.release());

    Ref pageRef;
    pageRef.num = 1;
    pageRef.gen = 0;

    // docA is unused for getRotate() forwarding in the public interface; we pass nullptr.
    auto page = std::make_unique<Page>(nullptr, /*numA=*/1, std::move(pageDictObj), pageRef, std::move(attrs));
    return {std::move(page), expected};
}

class PageTest_713 : public ::testing::Test {
protected:
    // For these tests, we can keep xref null; Dict/Array accept nullptr in many poppler builds.
    // If your build requires a valid XRef, wire it here.
    XRef *xref = nullptr;
};

} // namespace

TEST_F(PageTest_713, GetRotate_ForwardsAttrsRotate_WhenRotateIs0_713)
{
    auto attrsDict = makeAttrsDictWithMediaBoxAndOptionalRotate(xref, 0);
    auto built = makePageWithAttrsDict(std::move(attrsDict));

    ASSERT_NE(built.page, nullptr);
    EXPECT_EQ(built.page->getRotate(), built.expectedRotate);
}

TEST_F(PageTest_713, GetRotate_ForwardsAttrsRotate_WhenRotateIs90_713)
{
    auto attrsDict = makeAttrsDictWithMediaBoxAndOptionalRotate(xref, 90);
    auto built = makePageWithAttrsDict(std::move(attrsDict));

    ASSERT_NE(built.page, nullptr);
    EXPECT_EQ(built.page->getRotate(), built.expectedRotate);
}

TEST_F(PageTest_713, GetRotate_ForwardsAttrsRotate_WhenRotateIs270_713)
{
    auto attrsDict = makeAttrsDictWithMediaBoxAndOptionalRotate(xref, 270);
    auto built = makePageWithAttrsDict(std::move(attrsDict));

    ASSERT_NE(built.page, nullptr);
    EXPECT_EQ(built.page->getRotate(), built.expectedRotate);
}

TEST_F(PageTest_713, GetRotate_ForwardsAttrsRotate_WhenRotateKeyMissing_Boundary_713)
{
    auto attrsDict = makeAttrsDictWithMediaBoxAndOptionalRotate(xref, std::nullopt);
    auto built = makePageWithAttrsDict(std::move(attrsDict));

    ASSERT_NE(built.page, nullptr);
    // We do not assume a specific default; we only verify the forwarding behavior.
    EXPECT_EQ(built.page->getRotate(), built.expectedRotate);
}

TEST_F(PageTest_713, GetRotate_ForwardsAttrsRotate_WhenRotateIsNonStandardValue_Boundary_713)
{
    // Non-standard PDF rotate value (commonly rotations are multiples of 90).
    // We do not assume normalization rules; only verify forwarding to PageAttrs::getRotate().
    auto attrsDict = makeAttrsDictWithMediaBoxAndOptionalRotate(xref, 45);
    auto built = makePageWithAttrsDict(std::move(attrsDict));

    ASSERT_NE(built.page, nullptr);
    EXPECT_EQ(built.page->getRotate(), built.expectedRotate);
}

TEST_F(PageTest_713, GetRotate_IsStableAcrossMultipleCalls_Normal_713)
{
    auto attrsDict = makeAttrsDictWithMediaBoxAndOptionalRotate(xref, 180);
    auto built = makePageWithAttrsDict(std::move(attrsDict));

    ASSERT_NE(built.page, nullptr);

    const int r1 = built.page->getRotate();
    const int r2 = built.page->getRotate();
    const int r3 = built.page->getRotate();

    EXPECT_EQ(r1, built.expectedRotate);
    EXPECT_EQ(r2, built.expectedRotate);
    EXPECT_EQ(r3, built.expectedRotate);
}