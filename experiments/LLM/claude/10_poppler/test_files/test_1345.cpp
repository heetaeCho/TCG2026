#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "poppler/ViewerPreferences.h"
#include "poppler/Dict.h"
#include "poppler/PDFDoc.h"
#include "poppler/GlobalParams.h"

#include <memory>
#include <string>
#include <cstring>

class ViewerPreferencesTest_1345 : public ::testing::Test {
protected:
    static void SetUpTestSuite() {
        if (!globalParams) {
            globalParams = std::make_unique<GlobalParams>();
        }
    }

    // Helper to create a Dict with specific viewer preference entries
    // We need an XRef for Dict, but we can pass nullptr for simple cases
    std::unique_ptr<Dict> createDict() {
        return std::make_unique<Dict>(static_cast<XRef*>(nullptr));
    }
};

TEST_F(ViewerPreferencesTest_1345, DefaultHideToolbarFalse_1345) {
    auto dict = createDict();
    ViewerPreferences vp(*dict);
    // Without setting HideToolbar, it should default to false
    EXPECT_FALSE(vp.getHideToolbar());
}

TEST_F(ViewerPreferencesTest_1345, DefaultHideMenubarFalse_1345) {
    auto dict = createDict();
    ViewerPreferences vp(*dict);
    EXPECT_FALSE(vp.getHideMenubar());
}

TEST_F(ViewerPreferencesTest_1345, DefaultHideWindowUIFalse_1345) {
    auto dict = createDict();
    ViewerPreferences vp(*dict);
    EXPECT_FALSE(vp.getHideWindowUI());
}

TEST_F(ViewerPreferencesTest_1345, DefaultFitWindowFalse_1345) {
    auto dict = createDict();
    ViewerPreferences vp(*dict);
    EXPECT_FALSE(vp.getFitWindow());
}

TEST_F(ViewerPreferencesTest_1345, DefaultCenterWindowFalse_1345) {
    auto dict = createDict();
    ViewerPreferences vp(*dict);
    EXPECT_FALSE(vp.getCenterWindow());
}

TEST_F(ViewerPreferencesTest_1345, DefaultDisplayDocTitleFalse_1345) {
    auto dict = createDict();
    ViewerPreferences vp(*dict);
    EXPECT_FALSE(vp.getDisplayDocTitle());
}

TEST_F(ViewerPreferencesTest_1345, DefaultPickTrayByPDFSizeFalse_1345) {
    auto dict = createDict();
    ViewerPreferences vp(*dict);
    EXPECT_FALSE(vp.getPickTrayByPDFSize());
}

TEST_F(ViewerPreferencesTest_1345, DefaultNumCopiesOne_1345) {
    auto dict = createDict();
    ViewerPreferences vp(*dict);
    EXPECT_EQ(vp.getNumCopies(), 1);
}

TEST_F(ViewerPreferencesTest_1345, DefaultPrintPageRangeEmpty_1345) {
    auto dict = createDict();
    ViewerPreferences vp(*dict);
    EXPECT_TRUE(vp.getPrintPageRange().empty());
}

TEST_F(ViewerPreferencesTest_1345, DefaultNonFullScreenPageMode_1345) {
    auto dict = createDict();
    ViewerPreferences vp(*dict);
    EXPECT_EQ(vp.getNonFullScreenPageMode(), ViewerPreferences::nfpmUseNone);
}

TEST_F(ViewerPreferencesTest_1345, DefaultDirection_1345) {
    auto dict = createDict();
    ViewerPreferences vp(*dict);
    EXPECT_EQ(vp.getDirection(), ViewerPreferences::directionL2R);
}

TEST_F(ViewerPreferencesTest_1345, DefaultPrintScaling_1345) {
    auto dict = createDict();
    ViewerPreferences vp(*dict);
    EXPECT_EQ(vp.getPrintScaling(), ViewerPreferences::printScalingAppDefault);
}

TEST_F(ViewerPreferencesTest_1345, DefaultDuplex_1345) {
    auto dict = createDict();
    ViewerPreferences vp(*dict);
    EXPECT_EQ(vp.getDuplex(), ViewerPreferences::duplexNone);
}

TEST_F(ViewerPreferencesTest_1345, HideToolbarTrue_1345) {
    auto dict = createDict();
    dict->add("HideToolbar", Object(true));
    ViewerPreferences vp(*dict);
    EXPECT_TRUE(vp.getHideToolbar());
}

TEST_F(ViewerPreferencesTest_1345, HideMenubarTrue_1345) {
    auto dict = createDict();
    dict->add("HideMenubar", Object(true));
    ViewerPreferences vp(*dict);
    EXPECT_TRUE(vp.getHideMenubar());
}

TEST_F(ViewerPreferencesTest_1345, HideWindowUITrue_1345) {
    auto dict = createDict();
    dict->add("HideWindowUI", Object(true));
    ViewerPreferences vp(*dict);
    EXPECT_TRUE(vp.getHideWindowUI());
}

TEST_F(ViewerPreferencesTest_1345, FitWindowTrue_1345) {
    auto dict = createDict();
    dict->add("FitWindow", Object(true));
    ViewerPreferences vp(*dict);
    EXPECT_TRUE(vp.getFitWindow());
}

TEST_F(ViewerPreferencesTest_1345, CenterWindowTrue_1345) {
    auto dict = createDict();
    dict->add("CenterWindow", Object(true));
    ViewerPreferences vp(*dict);
    EXPECT_TRUE(vp.getCenterWindow());
}

TEST_F(ViewerPreferencesTest_1345, DisplayDocTitleTrue_1345) {
    auto dict = createDict();
    dict->add("DisplayDocTitle", Object(true));
    ViewerPreferences vp(*dict);
    EXPECT_TRUE(vp.getDisplayDocTitle());
}

TEST_F(ViewerPreferencesTest_1345, PickTrayByPDFSizeTrue_1345) {
    auto dict = createDict();
    dict->add("PickTrayByPDFSize", Object(true));
    ViewerPreferences vp(*dict);
    EXPECT_TRUE(vp.getPickTrayByPDFSize());
}

TEST_F(ViewerPreferencesTest_1345, NumCopiesSet_1345) {
    auto dict = createDict();
    dict->add("NumCopies", Object(3));
    ViewerPreferences vp(*dict);
    EXPECT_EQ(vp.getNumCopies(), 3);
}

TEST_F(ViewerPreferencesTest_1345, DirectionR2L_1345) {
    auto dict = createDict();
    dict->add("Direction", Object(new GooString("R2L")));
    ViewerPreferences vp(*dict);
    EXPECT_EQ(vp.getDirection(), ViewerPreferences::directionR2L);
}

TEST_F(ViewerPreferencesTest_1345, NonFullScreenPageModeUseOutlines_1345) {
    auto dict = createDict();
    dict->add("NonFullScreenPageMode", Object(new GooString("UseOutlines")));
    ViewerPreferences vp(*dict);
    EXPECT_EQ(vp.getNonFullScreenPageMode(), ViewerPreferences::nfpmUseOutlines);
}

TEST_F(ViewerPreferencesTest_1345, NonFullScreenPageModeUseThumbs_1345) {
    auto dict = createDict();
    dict->add("NonFullScreenPageMode", Object(new GooString("UseThumbs")));
    ViewerPreferences vp(*dict);
    EXPECT_EQ(vp.getNonFullScreenPageMode(), ViewerPreferences::nfpmUseThumbs);
}

TEST_F(ViewerPreferencesTest_1345, NonFullScreenPageModeUseOC_1345) {
    auto dict = createDict();
    dict->add("NonFullScreenPageMode", Object(new GooString("UseOC")));
    ViewerPreferences vp(*dict);
    EXPECT_EQ(vp.getNonFullScreenPageMode(), ViewerPreferences::nfpmUseOC);
}

TEST_F(ViewerPreferencesTest_1345, PrintScalingNone_1345) {
    auto dict = createDict();
    dict->add("PrintScaling", Object(new GooString("None")));
    ViewerPreferences vp(*dict);
    EXPECT_EQ(vp.getPrintScaling(), ViewerPreferences::printScalingNone);
}

TEST_F(ViewerPreferencesTest_1345, DuplexSimplex_1345) {
    auto dict = createDict();
    dict->add("Duplex", Object(new GooString("Simplex")));
    ViewerPreferences vp(*dict);
    EXPECT_EQ(vp.getDuplex(), ViewerPreferences::duplexSimplex);
}

TEST_F(ViewerPreferencesTest_1345, DuplexFlipShortEdge_1345) {
    auto dict = createDict();
    dict->add("Duplex", Object(new GooString("DuplexFlipShortEdge")));
    ViewerPreferences vp(*dict);
    EXPECT_EQ(vp.getDuplex(), ViewerPreferences::duplexFlipShortEdge);
}

TEST_F(ViewerPreferencesTest_1345, DuplexFlipLongEdge_1345) {
    auto dict = createDict();
    dict->add("Duplex", Object(new GooString("DuplexFlipLongEdge")));
    ViewerPreferences vp(*dict);
    EXPECT_EQ(vp.getDuplex(), ViewerPreferences::duplexFlipLongEdge);
}

TEST_F(ViewerPreferencesTest_1345, HideToolbarFalseExplicit_1345) {
    auto dict = createDict();
    dict->add("HideToolbar", Object(false));
    ViewerPreferences vp(*dict);
    EXPECT_FALSE(vp.getHideToolbar());
}

TEST_F(ViewerPreferencesTest_1345, AllBooleanFieldsTrue_1345) {
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

TEST_F(ViewerPreferencesTest_1345, EmptyDictAllDefaults_1345) {
    auto dict = createDict();
    ViewerPreferences vp(*dict);
    EXPECT_FALSE(vp.getHideToolbar());
    EXPECT_FALSE(vp.getHideMenubar());
    EXPECT_FALSE(vp.getHideWindowUI());
    EXPECT_FALSE(vp.getFitWindow());
    EXPECT_FALSE(vp.getCenterWindow());
    EXPECT_FALSE(vp.getDisplayDocTitle());
    EXPECT_FALSE(vp.getPickTrayByPDFSize());
    EXPECT_EQ(vp.getNumCopies(), 1);
    EXPECT_EQ(vp.getNonFullScreenPageMode(), ViewerPreferences::nfpmUseNone);
    EXPECT_EQ(vp.getDirection(), ViewerPreferences::directionL2R);
    EXPECT_EQ(vp.getPrintScaling(), ViewerPreferences::printScalingAppDefault);
    EXPECT_EQ(vp.getDuplex(), ViewerPreferences::duplexNone);
    EXPECT_TRUE(vp.getPrintPageRange().empty());
}

TEST_F(ViewerPreferencesTest_1345, NumCopiesZero_1345) {
    auto dict = createDict();
    dict->add("NumCopies", Object(0));
    ViewerPreferences vp(*dict);
    // Zero copies may be treated differently; check observable result
    int nc = vp.getNumCopies();
    EXPECT_GE(nc, 0);
}

TEST_F(ViewerPreferencesTest_1345, NumCopiesNegative_1345) {
    auto dict = createDict();
    dict->add("NumCopies", Object(-1));
    ViewerPreferences vp(*dict);
    // Negative value should be handled gracefully
    int nc = vp.getNumCopies();
    // Default or clamped value expected
    EXPECT_GE(nc, 1);
}

TEST_F(ViewerPreferencesTest_1345, InvalidDirectionString_1345) {
    auto dict = createDict();
    dict->add("Direction", Object(new GooString("InvalidDirection")));
    ViewerPreferences vp(*dict);
    // Should fall back to default
    EXPECT_EQ(vp.getDirection(), ViewerPreferences::directionL2R);
}

TEST_F(ViewerPreferencesTest_1345, InvalidNonFullScreenPageModeString_1345) {
    auto dict = createDict();
    dict->add("NonFullScreenPageMode", Object(new GooString("InvalidMode")));
    ViewerPreferences vp(*dict);
    EXPECT_EQ(vp.getNonFullScreenPageMode(), ViewerPreferences::nfpmUseNone);
}

TEST_F(ViewerPreferencesTest_1345, InvalidPrintScalingString_1345) {
    auto dict = createDict();
    dict->add("PrintScaling", Object(new GooString("InvalidScaling")));
    ViewerPreferences vp(*dict);
    EXPECT_EQ(vp.getPrintScaling(), ViewerPreferences::printScalingAppDefault);
}

TEST_F(ViewerPreferencesTest_1345, InvalidDuplexString_1345) {
    auto dict = createDict();
    dict->add("Duplex", Object(new GooString("InvalidDuplex")));
    ViewerPreferences vp(*dict);
    EXPECT_EQ(vp.getDuplex(), ViewerPreferences::duplexNone);
}

TEST_F(ViewerPreferencesTest_1345, PrintPageRangeValid_1345) {
    auto dict = createDict();
    // PrintPageRange is an array of integers in pairs
    Array *arr = new Array(static_cast<XRef*>(nullptr));
    arr->add(Object(1));
    arr->add(Object(5));
    arr->add(Object(10));
    arr->add(Object(15));
    dict->add("PrintPageRange", Object(arr));
    ViewerPreferences vp(*dict);
    auto range = vp.getPrintPageRange();
    EXPECT_EQ(range.size(), 2u);
    if (range.size() >= 2) {
        EXPECT_EQ(range[0].first, 1);
        EXPECT_EQ(range[0].second, 5);
        EXPECT_EQ(range[1].first, 10);
        EXPECT_EQ(range[1].second, 15);
    }
}

TEST_F(ViewerPreferencesTest_1345, PrintPageRangeOddNumberOfEntries_1345) {
    auto dict = createDict();
    // Odd number of entries - incomplete pair
    Array *arr = new Array(static_cast<XRef*>(nullptr));
    arr->add(Object(1));
    arr->add(Object(5));
    arr->add(Object(10));
    dict->add("PrintPageRange", Object(arr));
    ViewerPreferences vp(*dict);
    auto range = vp.getPrintPageRange();
    // Should only include complete pairs
    EXPECT_EQ(range.size(), 1u);
}

TEST_F(ViewerPreferencesTest_1345, PrintPageRangeEmptyArray_1345) {
    auto dict = createDict();
    Array *arr = new Array(static_cast<XRef*>(nullptr));
    dict->add("PrintPageRange", Object(arr));
    ViewerPreferences vp(*dict);
    auto range = vp.getPrintPageRange();
    EXPECT_TRUE(range.empty());
}

TEST_F(ViewerPreferencesTest_1345, LargeNumCopies_1345) {
    auto dict = createDict();
    dict->add("NumCopies", Object(999));
    ViewerPreferences vp(*dict);
    EXPECT_EQ(vp.getNumCopies(), 999);
}
