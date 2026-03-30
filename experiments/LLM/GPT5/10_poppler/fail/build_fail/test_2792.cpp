// HtmlImage_test_2792.cc
#include <gtest/gtest.h>

#include <string>
#include <type_traits>
#include <utility>

// These headers are expected to exist in the real Poppler codebase.
#include "GfxState.h"

// HtmlImage is implemented in utils/HtmlOutputDev.cc in the codebase.
// In Poppler's test style, it's common to include the .cc to access
// file-local helpers/types. This keeps the class under test as the real one.
#include "utils/HtmlOutputDev.cc"

namespace {

static std::unique_ptr<GfxState> MakeState_2792()
{
    // PDFRectangle is a Poppler type used by GfxState's ctor.
    // It is typically declared in core headers included transitively in the build.
    //
    // We intentionally keep this minimal: we only need a valid-looking page box
    // to be able to construct a GfxState for HtmlImage's constructor.
    PDFRectangle pageBox;
    pageBox.x1 = 0;
    pageBox.y1 = 0;
    pageBox.x2 = 612; // 8.5in * 72dpi
    pageBox.y2 = 792; // 11in  * 72dpi

    return std::make_unique<GfxState>(72.0, 72.0, &pageBox, /*rotateA=*/0, /*upsideDown=*/false);
}

class HtmlImageTest_2792 : public ::testing::Test {
protected:
    std::unique_ptr<GfxState> state_ = MakeState_2792();
};

} // namespace

TEST_F(HtmlImageTest_2792, StoresProvidedFileName_2792)
{
    std::string name = "image-001.png";
    HtmlImage img(std::move(name), state_.get());

    EXPECT_EQ(img.fName, "image-001.png");
}

TEST_F(HtmlImageTest_2792, AcceptsEmptyFileName_2792)
{
    std::string name;
    ASSERT_TRUE(name.empty());

    HtmlImage img(std::move(name), state_.get());
    EXPECT_TRUE(img.fName.empty());
}

TEST_F(HtmlImageTest_2792, PreservesEmbeddedNullCharacters_2792)
{
    std::string name("ab\0cd", 5);
    ASSERT_EQ(name.size(), 5u);

    HtmlImage img(std::move(name), state_.get());

    EXPECT_EQ(img.fName.size(), 5u);
    EXPECT_EQ(img.fName[0], 'a');
    EXPECT_EQ(img.fName[1], 'b');
    EXPECT_EQ(img.fName[2], '\0');
    EXPECT_EQ(img.fName[3], 'c');
    EXPECT_EQ(img.fName[4], 'd');
}

TEST_F(HtmlImageTest_2792, HandlesLongFileName_2792)
{
    std::string name(4096, 'x');
    ASSERT_EQ(name.size(), 4096u);

    EXPECT_NO_THROW({
        HtmlImage img(std::move(name), state_.get());
        EXPECT_EQ(img.fName.size(), 4096u);
        EXPECT_EQ(img.fName.front(), 'x');
        EXPECT_EQ(img.fName.back(), 'x');
    });
}

TEST_F(HtmlImageTest_2792, MultipleInstancesKeepIndependentNames_2792)
{
    HtmlImage img1(std::string("a.png"), state_.get());
    HtmlImage img2(std::string("b.png"), state_.get());

    EXPECT_EQ(img1.fName, "a.png");
    EXPECT_EQ(img2.fName, "b.png");
}

TEST_F(HtmlImageTest_2792, TypeTraits_DeletedCopyAndAssignment_2792)
{
    static_assert(!std::is_copy_constructible<HtmlImage>::value,
                  "HtmlImage copy construction must be deleted");
    static_assert(!std::is_copy_assignable<HtmlImage>::value,
                  "HtmlImage copy assignment must be deleted");
}

TEST_F(HtmlImageTest_2792, TypeTraits_ConstructibleFromRvalueStringOnly_2792)
{
    // Constructor takes std::string&& per interface.
    static_assert(std::is_constructible<HtmlImage, std::string&&, GfxState*>::value,
                  "HtmlImage must be constructible from (std::string&&, GfxState*)");
    static_assert(!std::is_constructible<HtmlImage, const std::string&, GfxState*>::value,
                  "HtmlImage must not be constructible from (const std::string&, GfxState*)");
    static_assert(!std::is_constructible<HtmlImage, std::string&, GfxState*>::value,
                  "HtmlImage must not be constructible from (std::string&, GfxState*)");
}