#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "ViewerPreferences.h"
#include "Dict.h"
#include "PDFDoc.h"
#include "GlobalParams.h"

#include <memory>
#include <string>

class ViewerPreferencesTest_1353 : public ::testing::Test {
protected:
    void SetUp() override {
        if (!globalParams) {
            globalParams = std::make_unique<GlobalParams>();
        }
    }

    // Helper to create a Dict with specific entries
    // We need an XRef for Dict, but we can pass nullptr for simple cases
    std::unique_ptr<Dict> createDict() {
        return std::make_unique<Dict>(static_cast<XRef *>(nullptr));
    }
};

TEST_F(ViewerPreferencesTest_1353, DefaultPrintScaling_1353)
{
    auto dict = createDict();
    ViewerPreferences vp(*dict);
    // Default printScaling should be printScalingAppDefault
    EXPECT_EQ(vp.getPrintScaling(), ViewerPreferences::printScalingAppDefault);
}

TEST_F(ViewerPreferencesTest_1353, DefaultHideToolbar_1353)
{
    auto dict = createDict();
    ViewerPreferences vp(*dict);
    EXPECT_FALSE(vp.getHideToolbar());
}

TEST_F(ViewerPreferencesTest_1353, DefaultHideMenubar_1353)
{
    auto dict = createDict();
    ViewerPreferences vp(*dict);
    EXPECT_FALSE(vp.getHideMenubar());
}

TEST_F(ViewerPreferencesTest_1353, DefaultHideWindowUI_1353)
{
    auto dict = createDict();
    ViewerPreferences vp(*dict);
    EXPECT_FALSE(vp.getHideWindowUI());
}

TEST_F(ViewerPreferencesTest_1353, DefaultFitWindow_1353)
{
    auto dict = createDict();
    ViewerPreferences vp(*dict);
    EXPECT_FALSE(vp.getFitWindow());
}

TEST_F(ViewerPreferencesTest_1353, DefaultCenterWindow_1353)
{
    auto dict = createDict();
    ViewerPreferences vp(*dict);
    EXPECT_FALSE(vp.getCenterWindow());
}

TEST_F(ViewerPreferencesTest_1353, DefaultDisplayDocTitle_1353)
{
    auto dict = createDict();
    ViewerPreferences vp(*dict);
    EXPECT_FALSE(vp.getDisplayDocTitle());
}

TEST_F(ViewerPreferencesTest_1353, DefaultNonFullScreenPageMode_1353)
{
    auto dict = createDict();
    ViewerPreferences vp(*dict);
    EXPECT_EQ(vp.getNonFullScreenPageMode(), ViewerPreferences::nfpmUseNone);
}

TEST_F(ViewerPreferencesTest_1353, DefaultDirection_1353)
{
    auto dict = createDict();
    ViewerPreferences vp(*dict);
    EXPECT_EQ(vp.getDirection(), ViewerPreferences::directionL2R);
}

TEST_F(ViewerPreferencesTest_1353, DefaultDuplex_1353)
{
    auto dict = createDict();
    ViewerPreferences vp(*dict);
    EXPECT_EQ(vp.getDuplex(), ViewerPreferences::duplexNone);
}

TEST_F(ViewerPreferencesTest_1353, DefaultPickTrayByPDFSize_1353)
{
    auto dict = createDict();
    ViewerPreferences vp(*dict);
    EXPECT_FALSE(vp.getPickTrayByPDFSize());
}

TEST_F(ViewerPreferencesTest_1353, DefaultNumCopies_1353)
{
    auto dict = createDict();
    ViewerPreferences vp(*dict);
    EXPECT_EQ(vp.getNumCopies(), 1);
}

TEST_F(ViewerPreferencesTest_1353, DefaultPrintPageRangeEmpty_1353)
{
    auto dict = createDict();
    ViewerPreferences vp(*dict);
    auto range = vp.getPrintPageRange();
    EXPECT_TRUE(range.empty());
}

TEST_F(ViewerPreferencesTest_1353, HideToolbarTrue_1353)
{
    auto dict = createDict();
    dict->add("HideToolbar", Object(true));
    ViewerPreferences vp(*dict);
    EXPECT_TRUE(vp.getHideToolbar());
}

TEST_F(ViewerPreferencesTest_1353, HideToolbarFalse_1353)
{
    auto dict = createDict();
    dict->add("HideToolbar", Object(false));
    ViewerPreferences vp(*dict);
    EXPECT_FALSE(vp.getHideToolbar());
}

TEST_F(ViewerPreferencesTest_1353, HideMenubarTrue_1353)
{
    auto dict = createDict();
    dict->add("HideMenubar", Object(true));
    ViewerPreferences vp(*dict);
    EXPECT_TRUE(vp.getHideMenubar());
}

TEST_F(ViewerPreferencesTest_1353, HideWindowUITrue_1353)
{
    auto dict = createDict();
    dict->add("HideWindowUI", Object(true));
    ViewerPreferences vp(*dict);
    EXPECT_TRUE(vp.getHideWindowUI());
}

TEST_F(ViewerPreferencesTest_1353, FitWindowTrue_1353)
{
    auto dict = createDict();
    dict->add("FitWindow", Object(true));
    ViewerPreferences vp(*dict);
    EXPECT_TRUE(vp.getFitWindow());
}

TEST_F(ViewerPreferencesTest_1353, CenterWindowTrue_1353)
{
    auto dict = createDict();
    dict->add("CenterWindow", Object(true));
    ViewerPreferences vp(*dict);
    EXPECT_TRUE(vp.getCenterWindow());
}

TEST_F(ViewerPreferencesTest_1353, DisplayDocTitleTrue_1353)
{
    auto dict = createDict();
    dict->add("DisplayDocTitle", Object(true));
    ViewerPreferences vp(*dict);
    EXPECT_TRUE(vp.getDisplayDocTitle());
}

TEST_F(ViewerPreferencesTest_1353, PrintScalingNone_1353)
{
    auto dict = createDict();
    dict->add("PrintScaling", Object(new GooString("None")));
    ViewerPreferences vp(*dict);
    EXPECT_EQ(vp.getPrintScaling(), ViewerPreferences::printScalingNone);
}

TEST_F(ViewerPreferencesTest_1353, PrintScalingAppDefault_1353)
{
    auto dict = createDict();
    dict->add("PrintScaling", Object(new GooString("AppDefault")));
    ViewerPreferences vp(*dict);
    EXPECT_EQ(vp.getPrintScaling(), ViewerPreferences::printScalingAppDefault);
}

TEST_F(ViewerPreferencesTest_1353, DirectionR2L_1353)
{
    auto dict = createDict();
    dict->add("Direction", Object(new GooString("R2L")));
    ViewerPreferences vp(*dict);
    EXPECT_EQ(vp.getDirection(), ViewerPreferences::directionR2L);
}

TEST_F(ViewerPreferencesTest_1353, DirectionL2R_1353)
{
    auto dict = createDict();
    dict->add("Direction", Object(new GooString("L2R")));
    ViewerPreferences vp(*dict);
    EXPECT_EQ(vp.getDirection(), ViewerPreferences::directionL2R);
}

TEST_F(ViewerPreferencesTest_1353, NonFullScreenPageModeUseOC_1353)
{
    auto dict = createDict();
    dict->add("NonFullScreenPageMode", Object(new GooString("UseOC")));
    ViewerPreferences vp(*dict);
    EXPECT_EQ(vp.getNonFullScreenPageMode(), ViewerPreferences::nfpmUseOC);
}

TEST_F(ViewerPreferencesTest_1353, NonFullScreenPageModeUseOutlines_1353)
{
    auto dict = createDict();
    dict->add("NonFullScreenPageMode", Object(new GooString("UseOutlines")));
    ViewerPreferences vp(*dict);
    EXPECT_EQ(vp.getNonFullScreenPageMode(), ViewerPreferences::nfpmUseOutlines);
}

TEST_F(ViewerPreferencesTest_1353, NonFullScreenPageModeUseThumbs_1353)
{
    auto dict = createDict();
    dict->add("NonFullScreenPageMode", Object(new GooString("UseThumbs")));
    ViewerPreferences vp(*dict);
    EXPECT_EQ(vp.getNonFullScreenPageMode(), ViewerPreferences::nfpmUseThumbs);
}

TEST_F(ViewerPreferencesTest_1353, DuplexSimplex_1353)
{
    auto dict = createDict();
    dict->add("Duplex", Object(new GooString("Simplex")));
    ViewerPreferences vp(*dict);
    EXPECT_EQ(vp.getDuplex(), ViewerPreferences::duplexSimplex);
}

TEST_F(ViewerPreferencesTest_1353, DuplexDuplexFlipShortEdge_1353)
{
    auto dict = createDict();
    dict->add("Duplex", Object(new GooString("DuplexFlipShortEdge")));
    ViewerPreferences vp(*dict);
    EXPECT_EQ(vp.getDuplex(), ViewerPreferences::duplexFlipShortEdge);
}

TEST_F(ViewerPreferencesTest_1353, DuplexDuplexFlipLongEdge_1353)
{
    auto dict = createDict();
    dict->add("Duplex", Object(new GooString("DuplexFlipLongEdge")));
    ViewerPreferences vp(*dict);
    EXPECT_EQ(vp.getDuplex(), ViewerPreferences::duplexFlipLongEdge);
}

TEST_F(ViewerPreferencesTest_1353, PickTrayByPDFSizeTrue_1353)
{
    auto dict = createDict();
    dict->add("PickTrayByPDFSize", Object(true));
    ViewerPreferences vp(*dict);
    EXPECT_TRUE(vp.getPickTrayByPDFSize());
}

TEST_F(ViewerPreferencesTest_1353, NumCopiesSet_1353)
{
    auto dict = createDict();
    dict->add("NumCopies", Object(5));
    ViewerPreferences vp(*dict);
    EXPECT_EQ(vp.getNumCopies(), 5);
}

TEST_F(ViewerPreferencesTest_1353, NumCopiesOne_1353)
{
    auto dict = createDict();
    dict->add("NumCopies", Object(1));
    ViewerPreferences vp(*dict);
    EXPECT_EQ(vp.getNumCopies(), 1);
}

TEST_F(ViewerPreferencesTest_1353, AllBooleanFieldsSetTrue_1353)
{
    auto dict = createDict();
    dict->add("HideToolbar", Object(true));
    dict->add("HideMenubar", Object(true));
    dict->add("HideWindowUI", Object(true));
    dict->add("FitWindow", Object(true));
    dict->add("CenterWindow", Object(true));
    dict->add("DisplayDocTitle", Object(true));
    dict->add("PickTrayByPDFSize", Object(true));
    ViewerPreferences vp(*dict);
    EXPECT_TRUE(vp.getHideToolbar());
    EXPECT_TRUE(vp.getHideMenubar());
    EXPECT_TRUE(vp.getHideWindowUI());
    EXPECT_TRUE(vp.getFitWindow());
    EXPECT_TRUE(vp.getCenterWindow());
    EXPECT_TRUE(vp.getDisplayDocTitle());
    EXPECT_TRUE(vp.getPickTrayByPDFSize());
}

TEST_F(ViewerPreferencesTest_1353, InvalidPrintScalingDefaultsToAppDefault_1353)
{
    auto dict = createDict();
    dict->add("PrintScaling", Object(new GooString("InvalidValue")));
    ViewerPreferences vp(*dict);
    // Invalid value should likely default to appDefault
    EXPECT_EQ(vp.getPrintScaling(), ViewerPreferences::printScalingAppDefault);
}

TEST_F(ViewerPreferencesTest_1353, InvalidDirectionDefaultsToL2R_1353)
{
    auto dict = createDict();
    dict->add("Direction", Object(new GooString("InvalidDir")));
    ViewerPreferences vp(*dict);
    EXPECT_EQ(vp.getDirection(), ViewerPreferences::directionL2R);
}

TEST_F(ViewerPreferencesTest_1353, PrintPageRangeWithEntries_1353)
{
    auto dict = createDict();
    auto arr = std::make_unique<Array>(static_cast<XRef *>(nullptr));
    arr->add(Object(1));
    arr->add(Object(3));
    arr->add(Object(5));
    arr->add(Object(10));
    dict->add("PrintPageRange", Object(arr.release()));
    ViewerPreferences vp(*dict);
    auto range = vp.getPrintPageRange();
    ASSERT_EQ(range.size(), 2u);
    EXPECT_EQ(range[0].first, 1);
    EXPECT_EQ(range[0].second, 3);
    EXPECT_EQ(range[1].first, 5);
    EXPECT_EQ(range[1].second, 10);
}

TEST_F(ViewerPreferencesTest_1353, EmptyPrintPageRange_1353)
{
    auto dict = createDict();
    auto arr = std::make_unique<Array>(static_cast<XRef *>(nullptr));
    dict->add("PrintPageRange", Object(arr.release()));
    ViewerPreferences vp(*dict);
    auto range = vp.getPrintPageRange();
    EXPECT_TRUE(range.empty());
}
