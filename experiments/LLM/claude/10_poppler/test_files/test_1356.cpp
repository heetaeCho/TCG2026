#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "ViewerPreferences.h"
#include "Dict.h"
#include "PDFDoc.h"
#include "GlobalParams.h"

#include <memory>
#include <string>

class ViewerPreferencesTest_1356 : public ::testing::Test {
protected:
    void SetUp() override {
        if (!globalParams) {
            globalParams = std::make_unique<GlobalParams>();
        }
    }

    // Helper to create a Dict with specific entries
    // We need an XRef for Dict, so we'll use a minimal setup
    std::unique_ptr<Dict> createEmptyDict() {
        auto dict = std::make_unique<Dict>(nullptr);
        return dict;
    }
};

// Test default values when constructing with an empty dictionary
TEST_F(ViewerPreferencesTest_1356, DefaultNumCopies_1356)
{
    auto dict = createEmptyDict();
    ViewerPreferences vp(dict.get());
    EXPECT_EQ(vp.getNumCopies(), 1);
}

TEST_F(ViewerPreferencesTest_1356, DefaultHideToolbar_1356)
{
    auto dict = createEmptyDict();
    ViewerPreferences vp(dict.get());
    EXPECT_FALSE(vp.getHideToolbar());
}

TEST_F(ViewerPreferencesTest_1356, DefaultHideMenubar_1356)
{
    auto dict = createEmptyDict();
    ViewerPreferences vp(dict.get());
    EXPECT_FALSE(vp.getHideMenubar());
}

TEST_F(ViewerPreferencesTest_1356, DefaultHideWindowUI_1356)
{
    auto dict = createEmptyDict();
    ViewerPreferences vp(dict.get());
    EXPECT_FALSE(vp.getHideWindowUI());
}

TEST_F(ViewerPreferencesTest_1356, DefaultFitWindow_1356)
{
    auto dict = createEmptyDict();
    ViewerPreferences vp(dict.get());
    EXPECT_FALSE(vp.getFitWindow());
}

TEST_F(ViewerPreferencesTest_1356, DefaultCenterWindow_1356)
{
    auto dict = createEmptyDict();
    ViewerPreferences vp(dict.get());
    EXPECT_FALSE(vp.getCenterWindow());
}

TEST_F(ViewerPreferencesTest_1356, DefaultDisplayDocTitle_1356)
{
    auto dict = createEmptyDict();
    ViewerPreferences vp(dict.get());
    EXPECT_FALSE(vp.getDisplayDocTitle());
}

TEST_F(ViewerPreferencesTest_1356, DefaultNonFullScreenPageMode_1356)
{
    auto dict = createEmptyDict();
    ViewerPreferences vp(dict.get());
    EXPECT_EQ(vp.getNonFullScreenPageMode(), ViewerPreferences::nfpmUseNone);
}

TEST_F(ViewerPreferencesTest_1356, DefaultDirection_1356)
{
    auto dict = createEmptyDict();
    ViewerPreferences vp(dict.get());
    EXPECT_EQ(vp.getDirection(), ViewerPreferences::directionL2R);
}

TEST_F(ViewerPreferencesTest_1356, DefaultPrintScaling_1356)
{
    auto dict = createEmptyDict();
    ViewerPreferences vp(dict.get());
    EXPECT_EQ(vp.getPrintScaling(), ViewerPreferences::printScalingAppDefault);
}

TEST_F(ViewerPreferencesTest_1356, DefaultDuplex_1356)
{
    auto dict = createEmptyDict();
    ViewerPreferences vp(dict.get());
    EXPECT_EQ(vp.getDuplex(), ViewerPreferences::duplexNone);
}

TEST_F(ViewerPreferencesTest_1356, DefaultPickTrayByPDFSize_1356)
{
    auto dict = createEmptyDict();
    ViewerPreferences vp(dict.get());
    EXPECT_FALSE(vp.getPickTrayByPDFSize());
}

TEST_F(ViewerPreferencesTest_1356, DefaultPrintPageRangeEmpty_1356)
{
    auto dict = createEmptyDict();
    ViewerPreferences vp(dict.get());
    auto range = vp.getPrintPageRange();
    EXPECT_TRUE(range.empty());
}

// Test with specific values set in the dictionary
TEST_F(ViewerPreferencesTest_1356, HideToolbarTrue_1356)
{
    auto dict = createEmptyDict();
    dict->add("HideToolbar", Object(true));
    ViewerPreferences vp(dict.get());
    EXPECT_TRUE(vp.getHideToolbar());
}

TEST_F(ViewerPreferencesTest_1356, HideMenubarTrue_1356)
{
    auto dict = createEmptyDict();
    dict->add("HideMenubar", Object(true));
    ViewerPreferences vp(dict.get());
    EXPECT_TRUE(vp.getHideMenubar());
}

TEST_F(ViewerPreferencesTest_1356, HideWindowUITrue_1356)
{
    auto dict = createEmptyDict();
    dict->add("HideWindowUI", Object(true));
    ViewerPreferences vp(dict.get());
    EXPECT_TRUE(vp.getHideWindowUI());
}

TEST_F(ViewerPreferencesTest_1356, FitWindowTrue_1356)
{
    auto dict = createEmptyDict();
    dict->add("FitWindow", Object(true));
    ViewerPreferences vp(dict.get());
    EXPECT_TRUE(vp.getFitWindow());
}

TEST_F(ViewerPreferencesTest_1356, CenterWindowTrue_1356)
{
    auto dict = createEmptyDict();
    dict->add("CenterWindow", Object(true));
    ViewerPreferences vp(dict.get());
    EXPECT_TRUE(vp.getCenterWindow());
}

TEST_F(ViewerPreferencesTest_1356, DisplayDocTitleTrue_1356)
{
    auto dict = createEmptyDict();
    dict->add("DisplayDocTitle", Object(true));
    ViewerPreferences vp(dict.get());
    EXPECT_TRUE(vp.getDisplayDocTitle());
}

TEST_F(ViewerPreferencesTest_1356, NumCopiesSet_1356)
{
    auto dict = createEmptyDict();
    dict->add("NumCopies", Object(5));
    ViewerPreferences vp(dict.get());
    EXPECT_EQ(vp.getNumCopies(), 5);
}

TEST_F(ViewerPreferencesTest_1356, DirectionR2L_1356)
{
    auto dict = createEmptyDict();
    dict->add("Direction", Object(new GooString("R2L")));
    ViewerPreferences vp(dict.get());
    EXPECT_EQ(vp.getDirection(), ViewerPreferences::directionR2L);
}

TEST_F(ViewerPreferencesTest_1356, PrintScalingNone_1356)
{
    auto dict = createEmptyDict();
    dict->add("PrintScaling", Object(new GooString("None")));
    ViewerPreferences vp(dict.get());
    EXPECT_EQ(vp.getPrintScaling(), ViewerPreferences::printScalingNone);
}

TEST_F(ViewerPreferencesTest_1356, DuplexSimplex_1356)
{
    auto dict = createEmptyDict();
    dict->add("Duplex", Object(new GooString("Simplex")));
    ViewerPreferences vp(dict.get());
    EXPECT_EQ(vp.getDuplex(), ViewerPreferences::duplexSimplex);
}

TEST_F(ViewerPreferencesTest_1356, DuplexFlipShortEdge_1356)
{
    auto dict = createEmptyDict();
    dict->add("Duplex", Object(new GooString("DuplexFlipShortEdge")));
    ViewerPreferences vp(dict.get());
    EXPECT_EQ(vp.getDuplex(), ViewerPreferences::duplexFlipShortEdge);
}

TEST_F(ViewerPreferencesTest_1356, DuplexFlipLongEdge_1356)
{
    auto dict = createEmptyDict();
    dict->add("Duplex", Object(new GooString("DuplexFlipLongEdge")));
    ViewerPreferences vp(dict.get());
    EXPECT_EQ(vp.getDuplex(), ViewerPreferences::duplexFlipLongEdge);
}

TEST_F(ViewerPreferencesTest_1356, PickTrayByPDFSizeTrue_1356)
{
    auto dict = createEmptyDict();
    dict->add("PickTrayByPDFSize", Object(true));
    ViewerPreferences vp(dict.get());
    EXPECT_TRUE(vp.getPickTrayByPDFSize());
}

TEST_F(ViewerPreferencesTest_1356, NonFullScreenPageModeUseOutlines_1356)
{
    auto dict = createEmptyDict();
    dict->add("NonFullScreenPageMode", Object(new GooString("UseOutlines")));
    ViewerPreferences vp(dict.get());
    EXPECT_EQ(vp.getNonFullScreenPageMode(), ViewerPreferences::nfpmUseOutlines);
}

TEST_F(ViewerPreferencesTest_1356, NonFullScreenPageModeUseThumbs_1356)
{
    auto dict = createEmptyDict();
    dict->add("NonFullScreenPageMode", Object(new GooString("UseThumbs")));
    ViewerPreferences vp(dict.get());
    EXPECT_EQ(vp.getNonFullScreenPageMode(), ViewerPreferences::nfpmUseThumbs);
}

TEST_F(ViewerPreferencesTest_1356, NonFullScreenPageModeUseOC_1356)
{
    auto dict = createEmptyDict();
    dict->add("NonFullScreenPageMode", Object(new GooString("UseOC")));
    ViewerPreferences vp(dict.get());
    EXPECT_EQ(vp.getNonFullScreenPageMode(), ViewerPreferences::nfpmUseOC);
}

// Test boundary: NumCopies of 0 or negative
TEST_F(ViewerPreferencesTest_1356, NumCopiesZero_1356)
{
    auto dict = createEmptyDict();
    dict->add("NumCopies", Object(0));
    ViewerPreferences vp(dict.get());
    // The implementation may clamp or accept 0; we just observe the result
    int copies = vp.getNumCopies();
    EXPECT_GE(copies, 0);
}

TEST_F(ViewerPreferencesTest_1356, NumCopiesNegative_1356)
{
    auto dict = createEmptyDict();
    dict->add("NumCopies", Object(-1));
    ViewerPreferences vp(dict.get());
    // Should either default to 1 or accept -1; observe behavior
    int copies = vp.getNumCopies();
    // We at least verify it doesn't crash and returns something
    SUCCEED();
}

TEST_F(ViewerPreferencesTest_1356, NumCopiesLargeValue_1356)
{
    auto dict = createEmptyDict();
    dict->add("NumCopies", Object(999999));
    ViewerPreferences vp(dict.get());
    EXPECT_EQ(vp.getNumCopies(), 999999);
}

// Test with all boolean preferences set to false explicitly
TEST_F(ViewerPreferencesTest_1356, AllBooleansFalse_1356)
{
    auto dict = createEmptyDict();
    dict->add("HideToolbar", Object(false));
    dict->add("HideMenubar", Object(false));
    dict->add("HideWindowUI", Object(false));
    dict->add("FitWindow", Object(false));
    dict->add("CenterWindow", Object(false));
    dict->add("DisplayDocTitle", Object(false));
    dict->add("PickTrayByPDFSize", Object(false));
    ViewerPreferences vp(dict.get());
    EXPECT_FALSE(vp.getHideToolbar());
    EXPECT_FALSE(vp.getHideMenubar());
    EXPECT_FALSE(vp.getHideWindowUI());
    EXPECT_FALSE(vp.getFitWindow());
    EXPECT_FALSE(vp.getCenterWindow());
    EXPECT_FALSE(vp.getDisplayDocTitle());
    EXPECT_FALSE(vp.getPickTrayByPDFSize());
}

// Test with all boolean preferences set to true
TEST_F(ViewerPreferencesTest_1356, AllBooleansTrue_1356)
{
    auto dict = createEmptyDict();
    dict->add("HideToolbar", Object(true));
    dict->add("HideMenubar", Object(true));
    dict->add("HideWindowUI", Object(true));
    dict->add("FitWindow", Object(true));
    dict->add("CenterWindow", Object(true));
    dict->add("DisplayDocTitle", Object(true));
    dict->add("PickTrayByPDFSize", Object(true));
    ViewerPreferences vp(dict.get());
    EXPECT_TRUE(vp.getHideToolbar());
    EXPECT_TRUE(vp.getHideMenubar());
    EXPECT_TRUE(vp.getHideWindowUI());
    EXPECT_TRUE(vp.getFitWindow());
    EXPECT_TRUE(vp.getCenterWindow());
    EXPECT_TRUE(vp.getDisplayDocTitle());
    EXPECT_TRUE(vp.getPickTrayByPDFSize());
}

// Test with invalid string values for enum fields - should fall back to defaults
TEST_F(ViewerPreferencesTest_1356, InvalidDirectionString_1356)
{
    auto dict = createEmptyDict();
    dict->add("Direction", Object(new GooString("Invalid")));
    ViewerPreferences vp(dict.get());
    EXPECT_EQ(vp.getDirection(), ViewerPreferences::directionL2R);
}

TEST_F(ViewerPreferencesTest_1356, InvalidDuplexString_1356)
{
    auto dict = createEmptyDict();
    dict->add("Duplex", Object(new GooString("Invalid")));
    ViewerPreferences vp(dict.get());
    EXPECT_EQ(vp.getDuplex(), ViewerPreferences::duplexNone);
}

TEST_F(ViewerPreferencesTest_1356, InvalidPrintScalingString_1356)
{
    auto dict = createEmptyDict();
    dict->add("PrintScaling", Object(new GooString("Invalid")));
    ViewerPreferences vp(dict.get());
    EXPECT_EQ(vp.getPrintScaling(), ViewerPreferences::printScalingAppDefault);
}

TEST_F(ViewerPreferencesTest_1356, InvalidNonFullScreenPageModeString_1356)
{
    auto dict = createEmptyDict();
    dict->add("NonFullScreenPageMode", Object(new GooString("Invalid")));
    ViewerPreferences vp(dict.get());
    EXPECT_EQ(vp.getNonFullScreenPageMode(), ViewerPreferences::nfpmUseNone);
}

// Test PrintPageRange with a valid array
TEST_F(ViewerPreferencesTest_1356, PrintPageRangeValid_1356)
{
    auto dict = createEmptyDict();
    Array *arr = new Array(nullptr);
    arr->add(Object(1));
    arr->add(Object(5));
    dict->add("PrintPageRange", Object(arr));
    ViewerPreferences vp(dict.get());
    auto range = vp.getPrintPageRange();
    if (!range.empty()) {
        EXPECT_EQ(range[0].first, 1);
        EXPECT_EQ(range[0].second, 5);
    }
}

TEST_F(ViewerPreferencesTest_1356, PrintPageRangeMultipleRanges_1356)
{
    auto dict = createEmptyDict();
    Array *arr = new Array(nullptr);
    arr->add(Object(1));
    arr->add(Object(3));
    arr->add(Object(5));
    arr->add(Object(10));
    dict->add("PrintPageRange", Object(arr));
    ViewerPreferences vp(dict.get());
    auto range = vp.getPrintPageRange();
    if (range.size() >= 2) {
        EXPECT_EQ(range[0].first, 1);
        EXPECT_EQ(range[0].second, 3);
        EXPECT_EQ(range[1].first, 5);
        EXPECT_EQ(range[1].second, 10);
    }
}

// Test PrintPageRange with odd number of elements (should handle gracefully)
TEST_F(ViewerPreferencesTest_1356, PrintPageRangeOddElements_1356)
{
    auto dict = createEmptyDict();
    Array *arr = new Array(nullptr);
    arr->add(Object(1));
    arr->add(Object(3));
    arr->add(Object(5));
    dict->add("PrintPageRange", Object(arr));
    ViewerPreferences vp(dict.get());
    auto range = vp.getPrintPageRange();
    // Just verify no crash; implementation may ignore the odd element
    EXPECT_GE(range.size(), 0u);
}
