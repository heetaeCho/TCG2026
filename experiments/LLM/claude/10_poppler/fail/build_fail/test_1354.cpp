#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "ViewerPreferences.h"
#include "Dict.h"
#include "PDFDoc.h"
#include "GlobalParams.h"

#include <memory>
#include <string>

class ViewerPreferencesTest_1354 : public ::testing::Test {
protected:
    void SetUp() override {
        if (!globalParams) {
            globalParams = std::make_unique<GlobalParams>();
        }
    }

    // Helper to create a Dict with specific entries
    // We need an XRef for Dict, but we can pass nullptr for simple cases
    std::unique_ptr<Dict> createEmptyDict() {
        return std::make_unique<Dict>(static_cast<XRef*>(nullptr));
    }
};

TEST_F(ViewerPreferencesTest_1354, DefaultDuplex_1354) {
    auto dict = createEmptyDict();
    ViewerPreferences vp(*dict);
    // With an empty dict, duplex should default to duplexNone
    EXPECT_EQ(vp.getDuplex(), ViewerPreferences::duplexNone);
}

TEST_F(ViewerPreferencesTest_1354, DefaultHideToolbar_1354) {
    auto dict = createEmptyDict();
    ViewerPreferences vp(*dict);
    EXPECT_FALSE(vp.getHideToolbar());
}

TEST_F(ViewerPreferencesTest_1354, DefaultHideMenubar_1354) {
    auto dict = createEmptyDict();
    ViewerPreferences vp(*dict);
    EXPECT_FALSE(vp.getHideMenubar());
}

TEST_F(ViewerPreferencesTest_1354, DefaultHideWindowUI_1354) {
    auto dict = createEmptyDict();
    ViewerPreferences vp(*dict);
    EXPECT_FALSE(vp.getHideWindowUI());
}

TEST_F(ViewerPreferencesTest_1354, DefaultFitWindow_1354) {
    auto dict = createEmptyDict();
    ViewerPreferences vp(*dict);
    EXPECT_FALSE(vp.getFitWindow());
}

TEST_F(ViewerPreferencesTest_1354, DefaultCenterWindow_1354) {
    auto dict = createEmptyDict();
    ViewerPreferences vp(*dict);
    EXPECT_FALSE(vp.getCenterWindow());
}

TEST_F(ViewerPreferencesTest_1354, DefaultDisplayDocTitle_1354) {
    auto dict = createEmptyDict();
    ViewerPreferences vp(*dict);
    EXPECT_FALSE(vp.getDisplayDocTitle());
}

TEST_F(ViewerPreferencesTest_1354, DefaultNonFullScreenPageMode_1354) {
    auto dict = createEmptyDict();
    ViewerPreferences vp(*dict);
    EXPECT_EQ(vp.getNonFullScreenPageMode(), ViewerPreferences::nfpmUseNone);
}

TEST_F(ViewerPreferencesTest_1354, DefaultDirection_1354) {
    auto dict = createEmptyDict();
    ViewerPreferences vp(*dict);
    EXPECT_EQ(vp.getDirection(), ViewerPreferences::directionL2R);
}

TEST_F(ViewerPreferencesTest_1354, DefaultPrintScaling_1354) {
    auto dict = createEmptyDict();
    ViewerPreferences vp(*dict);
    EXPECT_EQ(vp.getPrintScaling(), ViewerPreferences::printScalingAppDefault);
}

TEST_F(ViewerPreferencesTest_1354, DefaultPickTrayByPDFSize_1354) {
    auto dict = createEmptyDict();
    ViewerPreferences vp(*dict);
    EXPECT_FALSE(vp.getPickTrayByPDFSize());
}

TEST_F(ViewerPreferencesTest_1354, DefaultNumCopies_1354) {
    auto dict = createEmptyDict();
    ViewerPreferences vp(*dict);
    EXPECT_EQ(vp.getNumCopies(), 1);
}

TEST_F(ViewerPreferencesTest_1354, DefaultPrintPageRange_1354) {
    auto dict = createEmptyDict();
    ViewerPreferences vp(*dict);
    auto range = vp.getPrintPageRange();
    EXPECT_TRUE(range.empty());
}

TEST_F(ViewerPreferencesTest_1354, HideToolbarTrue_1354) {
    auto dict = createEmptyDict();
    dict->add("HideToolbar", Object(true));
    ViewerPreferences vp(*dict);
    EXPECT_TRUE(vp.getHideToolbar());
}

TEST_F(ViewerPreferencesTest_1354, HideToolbarFalse_1354) {
    auto dict = createEmptyDict();
    dict->add("HideToolbar", Object(false));
    ViewerPreferences vp(*dict);
    EXPECT_FALSE(vp.getHideToolbar());
}

TEST_F(ViewerPreferencesTest_1354, HideMenubarTrue_1354) {
    auto dict = createEmptyDict();
    dict->add("HideMenubar", Object(true));
    ViewerPreferences vp(*dict);
    EXPECT_TRUE(vp.getHideMenubar());
}

TEST_F(ViewerPreferencesTest_1354, HideWindowUITrue_1354) {
    auto dict = createEmptyDict();
    dict->add("HideWindowUI", Object(true));
    ViewerPreferences vp(*dict);
    EXPECT_TRUE(vp.getHideWindowUI());
}

TEST_F(ViewerPreferencesTest_1354, FitWindowTrue_1354) {
    auto dict = createEmptyDict();
    dict->add("FitWindow", Object(true));
    ViewerPreferences vp(*dict);
    EXPECT_TRUE(vp.getFitWindow());
}

TEST_F(ViewerPreferencesTest_1354, CenterWindowTrue_1354) {
    auto dict = createEmptyDict();
    dict->add("CenterWindow", Object(true));
    ViewerPreferences vp(*dict);
    EXPECT_TRUE(vp.getCenterWindow());
}

TEST_F(ViewerPreferencesTest_1354, DisplayDocTitleTrue_1354) {
    auto dict = createEmptyDict();
    dict->add("DisplayDocTitle", Object(true));
    ViewerPreferences vp(*dict);
    EXPECT_TRUE(vp.getDisplayDocTitle());
}

TEST_F(ViewerPreferencesTest_1354, DirectionR2L_1354) {
    auto dict = createEmptyDict();
    dict->add("Direction", Object(objName, "R2L"));
    ViewerPreferences vp(*dict);
    EXPECT_EQ(vp.getDirection(), ViewerPreferences::directionR2L);
}

TEST_F(ViewerPreferencesTest_1354, DirectionL2R_1354) {
    auto dict = createEmptyDict();
    dict->add("Direction", Object(objName, "L2R"));
    ViewerPreferences vp(*dict);
    EXPECT_EQ(vp.getDirection(), ViewerPreferences::directionL2R);
}

TEST_F(ViewerPreferencesTest_1354, PrintScalingNone_1354) {
    auto dict = createEmptyDict();
    dict->add("PrintScaling", Object(objName, "None"));
    ViewerPreferences vp(*dict);
    EXPECT_EQ(vp.getPrintScaling(), ViewerPreferences::printScalingNone);
}

TEST_F(ViewerPreferencesTest_1354, PrintScalingAppDefault_1354) {
    auto dict = createEmptyDict();
    dict->add("PrintScaling", Object(objName, "AppDefault"));
    ViewerPreferences vp(*dict);
    EXPECT_EQ(vp.getPrintScaling(), ViewerPreferences::printScalingAppDefault);
}

TEST_F(ViewerPreferencesTest_1354, DuplexSimplex_1354) {
    auto dict = createEmptyDict();
    dict->add("Duplex", Object(objName, "Simplex"));
    ViewerPreferences vp(*dict);
    EXPECT_EQ(vp.getDuplex(), ViewerPreferences::duplexSimplex);
}

TEST_F(ViewerPreferencesTest_1354, DuplexFlipShortEdge_1354) {
    auto dict = createEmptyDict();
    dict->add("Duplex", Object(objName, "DuplexFlipShortEdge"));
    ViewerPreferences vp(*dict);
    EXPECT_EQ(vp.getDuplex(), ViewerPreferences::duplexFlipShortEdge);
}

TEST_F(ViewerPreferencesTest_1354, DuplexFlipLongEdge_1354) {
    auto dict = createEmptyDict();
    dict->add("Duplex", Object(objName, "DuplexFlipLongEdge"));
    ViewerPreferences vp(*dict);
    EXPECT_EQ(vp.getDuplex(), ViewerPreferences::duplexFlipLongEdge);
}

TEST_F(ViewerPreferencesTest_1354, PickTrayByPDFSizeTrue_1354) {
    auto dict = createEmptyDict();
    dict->add("PickTrayByPDFSize", Object(true));
    ViewerPreferences vp(*dict);
    EXPECT_TRUE(vp.getPickTrayByPDFSize());
}

TEST_F(ViewerPreferencesTest_1354, NumCopiesSet_1354) {
    auto dict = createEmptyDict();
    dict->add("NumCopies", Object(5));
    ViewerPreferences vp(*dict);
    EXPECT_EQ(vp.getNumCopies(), 5);
}

TEST_F(ViewerPreferencesTest_1354, NumCopiesOne_1354) {
    auto dict = createEmptyDict();
    dict->add("NumCopies", Object(1));
    ViewerPreferences vp(*dict);
    EXPECT_EQ(vp.getNumCopies(), 1);
}

TEST_F(ViewerPreferencesTest_1354, NonFullScreenPageModeUseOutlines_1354) {
    auto dict = createEmptyDict();
    dict->add("NonFullScreenPageMode", Object(objName, "UseOutlines"));
    ViewerPreferences vp(*dict);
    EXPECT_EQ(vp.getNonFullScreenPageMode(), ViewerPreferences::nfpmUseOutlines);
}

TEST_F(ViewerPreferencesTest_1354, NonFullScreenPageModeUseThumbs_1354) {
    auto dict = createEmptyDict();
    dict->add("NonFullScreenPageMode", Object(objName, "UseThumbs"));
    ViewerPreferences vp(*dict);
    EXPECT_EQ(vp.getNonFullScreenPageMode(), ViewerPreferences::nfpmUseThumbs);
}

TEST_F(ViewerPreferencesTest_1354, NonFullScreenPageModeUseOC_1354) {
    auto dict = createEmptyDict();
    dict->add("NonFullScreenPageMode", Object(objName, "UseOC"));
    ViewerPreferences vp(*dict);
    EXPECT_EQ(vp.getNonFullScreenPageMode(), ViewerPreferences::nfpmUseOC);
}

TEST_F(ViewerPreferencesTest_1354, NonFullScreenPageModeUseNone_1354) {
    auto dict = createEmptyDict();
    dict->add("NonFullScreenPageMode", Object(objName, "UseNone"));
    ViewerPreferences vp(*dict);
    EXPECT_EQ(vp.getNonFullScreenPageMode(), ViewerPreferences::nfpmUseNone);
}

TEST_F(ViewerPreferencesTest_1354, InvalidDirectionDefaultsToL2R_1354) {
    auto dict = createEmptyDict();
    dict->add("Direction", Object(objName, "InvalidDirection"));
    ViewerPreferences vp(*dict);
    EXPECT_EQ(vp.getDirection(), ViewerPreferences::directionL2R);
}

TEST_F(ViewerPreferencesTest_1354, InvalidDuplexDefaultsToNone_1354) {
    auto dict = createEmptyDict();
    dict->add("Duplex", Object(objName, "InvalidDuplex"));
    ViewerPreferences vp(*dict);
    EXPECT_EQ(vp.getDuplex(), ViewerPreferences::duplexNone);
}

TEST_F(ViewerPreferencesTest_1354, AllPropertiesSetTogether_1354) {
    auto dict = createEmptyDict();
    dict->add("HideToolbar", Object(true));
    dict->add("HideMenubar", Object(true));
    dict->add("HideWindowUI", Object(true));
    dict->add("FitWindow", Object(true));
    dict->add("CenterWindow", Object(true));
    dict->add("DisplayDocTitle", Object(true));
    dict->add("Direction", Object(objName, "R2L"));
    dict->add("PrintScaling", Object(objName, "None"));
    dict->add("Duplex", Object(objName, "Simplex"));
    dict->add("PickTrayByPDFSize", Object(true));
    dict->add("NumCopies", Object(3));

    ViewerPreferences vp(*dict);

    EXPECT_TRUE(vp.getHideToolbar());
    EXPECT_TRUE(vp.getHideMenubar());
    EXPECT_TRUE(vp.getHideWindowUI());
    EXPECT_TRUE(vp.getFitWindow());
    EXPECT_TRUE(vp.getCenterWindow());
    EXPECT_TRUE(vp.getDisplayDocTitle());
    EXPECT_EQ(vp.getDirection(), ViewerPreferences::directionR2L);
    EXPECT_EQ(vp.getPrintScaling(), ViewerPreferences::printScalingNone);
    EXPECT_EQ(vp.getDuplex(), ViewerPreferences::duplexSimplex);
    EXPECT_TRUE(vp.getPickTrayByPDFSize());
    EXPECT_EQ(vp.getNumCopies(), 3);
}

TEST_F(ViewerPreferencesTest_1354, PrintPageRangeWithEntries_1354) {
    auto dict = createEmptyDict();
    auto arr = std::make_unique<Array>(static_cast<XRef*>(nullptr));
    arr->add(Object(1));
    arr->add(Object(5));
    arr->add(Object(10));
    arr->add(Object(15));
    dict->add("PrintPageRange", Object(arr.release()));

    ViewerPreferences vp(*dict);
    auto range = vp.getPrintPageRange();
    ASSERT_EQ(range.size(), 2u);
    EXPECT_EQ(range[0].first, 1);
    EXPECT_EQ(range[0].second, 5);
    EXPECT_EQ(range[1].first, 10);
    EXPECT_EQ(range[1].second, 15);
}

TEST_F(ViewerPreferencesTest_1354, PrintPageRangeEmpty_1354) {
    auto dict = createEmptyDict();
    auto arr = std::make_unique<Array>(static_cast<XRef*>(nullptr));
    dict->add("PrintPageRange", Object(arr.release()));

    ViewerPreferences vp(*dict);
    auto range = vp.getPrintPageRange();
    EXPECT_TRUE(range.empty());
}

TEST_F(ViewerPreferencesTest_1354, PrintPageRangeSinglePair_1354) {
    auto dict = createEmptyDict();
    auto arr = std::make_unique<Array>(static_cast<XRef*>(nullptr));
    arr->add(Object(3));
    arr->add(Object(7));
    dict->add("PrintPageRange", Object(arr.release()));

    ViewerPreferences vp(*dict);
    auto range = vp.getPrintPageRange();
    ASSERT_EQ(range.size(), 1u);
    EXPECT_EQ(range[0].first, 3);
    EXPECT_EQ(range[0].second, 7);
}
