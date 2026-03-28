#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "ViewerPreferences.h"
#include "Dict.h"
#include "PDFDoc.h"
#include "GlobalParams.h"

#include <memory>
#include <string>

class ViewerPreferencesTest_1348 : public ::testing::Test {
protected:
    void SetUp() override {
        if (!globalParams) {
            globalParams = std::make_unique<GlobalParams>();
        }
    }

    // Helper to create a Dict with given key-value pairs
    // We need an XRef for Dict, but we can pass nullptr for simple cases
    std::unique_ptr<Dict> createDict() {
        return std::make_unique<Dict>(nullptr);
    }
};

TEST_F(ViewerPreferencesTest_1348, DefaultValues_EmptyDict_1348) {
    auto dict = createDict();
    ViewerPreferences vp(*dict);

    // With an empty dict, defaults should apply
    EXPECT_FALSE(vp.getHideToolbar());
    EXPECT_FALSE(vp.getHideMenubar());
    EXPECT_FALSE(vp.getHideWindowUI());
    EXPECT_FALSE(vp.getFitWindow());
    EXPECT_FALSE(vp.getCenterWindow());
    EXPECT_FALSE(vp.getDisplayDocTitle());
    EXPECT_FALSE(vp.getPickTrayByPDFSize());
    EXPECT_EQ(vp.getNumCopies(), 1);
    EXPECT_TRUE(vp.getPrintPageRange().empty());
}

TEST_F(ViewerPreferencesTest_1348, HideToolbarTrue_1348) {
    auto dict = createDict();
    dict->add("HideToolbar", Object(true));
    ViewerPreferences vp(*dict);

    EXPECT_TRUE(vp.getHideToolbar());
}

TEST_F(ViewerPreferencesTest_1348, HideToolbarFalse_1348) {
    auto dict = createDict();
    dict->add("HideToolbar", Object(false));
    ViewerPreferences vp(*dict);

    EXPECT_FALSE(vp.getHideToolbar());
}

TEST_F(ViewerPreferencesTest_1348, HideMenubarTrue_1348) {
    auto dict = createDict();
    dict->add("HideMenubar", Object(true));
    ViewerPreferences vp(*dict);

    EXPECT_TRUE(vp.getHideMenubar());
}

TEST_F(ViewerPreferencesTest_1348, HideMenubarFalse_1348) {
    auto dict = createDict();
    dict->add("HideMenubar", Object(false));
    ViewerPreferences vp(*dict);

    EXPECT_FALSE(vp.getHideMenubar());
}

TEST_F(ViewerPreferencesTest_1348, HideWindowUITrue_1348) {
    auto dict = createDict();
    dict->add("HideWindowUI", Object(true));
    ViewerPreferences vp(*dict);

    EXPECT_TRUE(vp.getHideWindowUI());
}

TEST_F(ViewerPreferencesTest_1348, HideWindowUIFalse_1348) {
    auto dict = createDict();
    dict->add("HideWindowUI", Object(false));
    ViewerPreferences vp(*dict);

    EXPECT_FALSE(vp.getHideWindowUI());
}

TEST_F(ViewerPreferencesTest_1348, FitWindowTrue_1348) {
    auto dict = createDict();
    dict->add("FitWindow", Object(true));
    ViewerPreferences vp(*dict);

    EXPECT_TRUE(vp.getFitWindow());
}

TEST_F(ViewerPreferencesTest_1348, FitWindowFalse_1348) {
    auto dict = createDict();
    dict->add("FitWindow", Object(false));
    ViewerPreferences vp(*dict);

    EXPECT_FALSE(vp.getFitWindow());
}

TEST_F(ViewerPreferencesTest_1348, CenterWindowTrue_1348) {
    auto dict = createDict();
    dict->add("CenterWindow", Object(true));
    ViewerPreferences vp(*dict);

    EXPECT_TRUE(vp.getCenterWindow());
}

TEST_F(ViewerPreferencesTest_1348, CenterWindowFalse_1348) {
    auto dict = createDict();
    dict->add("CenterWindow", Object(false));
    ViewerPreferences vp(*dict);

    EXPECT_FALSE(vp.getCenterWindow());
}

TEST_F(ViewerPreferencesTest_1348, DisplayDocTitleTrue_1348) {
    auto dict = createDict();
    dict->add("DisplayDocTitle", Object(true));
    ViewerPreferences vp(*dict);

    EXPECT_TRUE(vp.getDisplayDocTitle());
}

TEST_F(ViewerPreferencesTest_1348, DisplayDocTitleFalse_1348) {
    auto dict = createDict();
    dict->add("DisplayDocTitle", Object(false));
    ViewerPreferences vp(*dict);

    EXPECT_FALSE(vp.getDisplayDocTitle());
}

TEST_F(ViewerPreferencesTest_1348, DirectionDefault_1348) {
    auto dict = createDict();
    ViewerPreferences vp(*dict);

    EXPECT_EQ(vp.getDirection(), ViewerPreferences::directionL2R);
}

TEST_F(ViewerPreferencesTest_1348, DirectionL2R_1348) {
    auto dict = createDict();
    dict->add("Direction", Object(objName, "L2R"));
    ViewerPreferences vp(*dict);

    EXPECT_EQ(vp.getDirection(), ViewerPreferences::directionL2R);
}

TEST_F(ViewerPreferencesTest_1348, DirectionR2L_1348) {
    auto dict = createDict();
    dict->add("Direction", Object(objName, "R2L"));
    ViewerPreferences vp(*dict);

    EXPECT_EQ(vp.getDirection(), ViewerPreferences::directionR2L);
}

TEST_F(ViewerPreferencesTest_1348, PrintScalingDefault_1348) {
    auto dict = createDict();
    ViewerPreferences vp(*dict);

    EXPECT_EQ(vp.getPrintScaling(), ViewerPreferences::printScalingAppDefault);
}

TEST_F(ViewerPreferencesTest_1348, PrintScalingNone_1348) {
    auto dict = createDict();
    dict->add("PrintScaling", Object(objName, "None"));
    ViewerPreferences vp(*dict);

    EXPECT_EQ(vp.getPrintScaling(), ViewerPreferences::printScalingNone);
}

TEST_F(ViewerPreferencesTest_1348, DuplexDefault_1348) {
    auto dict = createDict();
    ViewerPreferences vp(*dict);

    EXPECT_EQ(vp.getDuplex(), ViewerPreferences::duplexNone);
}

TEST_F(ViewerPreferencesTest_1348, DuplexSimplex_1348) {
    auto dict = createDict();
    dict->add("Duplex", Object(objName, "Simplex"));
    ViewerPreferences vp(*dict);

    EXPECT_EQ(vp.getDuplex(), ViewerPreferences::duplexSimplex);
}

TEST_F(ViewerPreferencesTest_1348, DuplexFlipShortEdge_1348) {
    auto dict = createDict();
    dict->add("Duplex", Object(objName, "DuplexFlipShortEdge"));
    ViewerPreferences vp(*dict);

    EXPECT_EQ(vp.getDuplex(), ViewerPreferences::duplexFlipShortEdge);
}

TEST_F(ViewerPreferencesTest_1348, DuplexFlipLongEdge_1348) {
    auto dict = createDict();
    dict->add("Duplex", Object(objName, "DuplexFlipLongEdge"));
    ViewerPreferences vp(*dict);

    EXPECT_EQ(vp.getDuplex(), ViewerPreferences::duplexFlipLongEdge);
}

TEST_F(ViewerPreferencesTest_1348, PickTrayByPDFSizeTrue_1348) {
    auto dict = createDict();
    dict->add("PickTrayByPDFSize", Object(true));
    ViewerPreferences vp(*dict);

    EXPECT_TRUE(vp.getPickTrayByPDFSize());
}

TEST_F(ViewerPreferencesTest_1348, PickTrayByPDFSizeFalse_1348) {
    auto dict = createDict();
    dict->add("PickTrayByPDFSize", Object(false));
    ViewerPreferences vp(*dict);

    EXPECT_FALSE(vp.getPickTrayByPDFSize());
}

TEST_F(ViewerPreferencesTest_1348, NumCopiesDefault_1348) {
    auto dict = createDict();
    ViewerPreferences vp(*dict);

    EXPECT_EQ(vp.getNumCopies(), 1);
}

TEST_F(ViewerPreferencesTest_1348, NumCopiesSet_1348) {
    auto dict = createDict();
    dict->add("NumCopies", Object(5));
    ViewerPreferences vp(*dict);

    EXPECT_EQ(vp.getNumCopies(), 5);
}

TEST_F(ViewerPreferencesTest_1348, NonFullScreenPageModeDefault_1348) {
    auto dict = createDict();
    ViewerPreferences vp(*dict);

    EXPECT_EQ(vp.getNonFullScreenPageMode(), ViewerPreferences::nfpmUseNone);
}

TEST_F(ViewerPreferencesTest_1348, NonFullScreenPageModeUseOutlines_1348) {
    auto dict = createDict();
    dict->add("NonFullScreenPageMode", Object(objName, "UseOutlines"));
    ViewerPreferences vp(*dict);

    EXPECT_EQ(vp.getNonFullScreenPageMode(), ViewerPreferences::nfpmUseOutlines);
}

TEST_F(ViewerPreferencesTest_1348, NonFullScreenPageModeUseThumbs_1348) {
    auto dict = createDict();
    dict->add("NonFullScreenPageMode", Object(objName, "UseThumbs"));
    ViewerPreferences vp(*dict);

    EXPECT_EQ(vp.getNonFullScreenPageMode(), ViewerPreferences::nfpmUseThumbs);
}

TEST_F(ViewerPreferencesTest_1348, NonFullScreenPageModeUseOC_1348) {
    auto dict = createDict();
    dict->add("NonFullScreenPageMode", Object(objName, "UseOC"));
    ViewerPreferences vp(*dict);

    EXPECT_EQ(vp.getNonFullScreenPageMode(), ViewerPreferences::nfpmUseOC);
}

TEST_F(ViewerPreferencesTest_1348, PrintPageRangeEmpty_1348) {
    auto dict = createDict();
    ViewerPreferences vp(*dict);

    auto range = vp.getPrintPageRange();
    EXPECT_TRUE(range.empty());
}

TEST_F(ViewerPreferencesTest_1348, AllBooleansTrueSimultaneously_1348) {
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

TEST_F(ViewerPreferencesTest_1348, AllBooleansFalseSimultaneously_1348) {
    auto dict = createDict();
    dict->add("HideToolbar", Object(false));
    dict->add("HideMenubar", Object(false));
    dict->add("HideWindowUI", Object(false));
    dict->add("FitWindow", Object(false));
    dict->add("CenterWindow", Object(false));
    dict->add("DisplayDocTitle", Object(false));
    dict->add("PickTrayByPDFSize", Object(false));
    ViewerPreferences vp(*dict);

    EXPECT_FALSE(vp.getHideToolbar());
    EXPECT_FALSE(vp.getHideMenubar());
    EXPECT_FALSE(vp.getHideWindowUI());
    EXPECT_FALSE(vp.getFitWindow());
    EXPECT_FALSE(vp.getCenterWindow());
    EXPECT_FALSE(vp.getDisplayDocTitle());
    EXPECT_FALSE(vp.getPickTrayByPDFSize());
}

TEST_F(ViewerPreferencesTest_1348, NumCopiesBoundaryOne_1348) {
    auto dict = createDict();
    dict->add("NumCopies", Object(1));
    ViewerPreferences vp(*dict);

    EXPECT_EQ(vp.getNumCopies(), 1);
}

TEST_F(ViewerPreferencesTest_1348, NumCopiesLargeValue_1348) {
    auto dict = createDict();
    dict->add("NumCopies", Object(999));
    ViewerPreferences vp(*dict);

    EXPECT_EQ(vp.getNumCopies(), 999);
}

TEST_F(ViewerPreferencesTest_1348, PrintPageRangeWithEntries_1348) {
    auto dict = createDict();
    // PrintPageRange is an array of pairs of integers
    auto arr = std::make_unique<Array>(nullptr);
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

TEST_F(ViewerPreferencesTest_1348, PrintPageRangeSinglePair_1348) {
    auto dict = createDict();
    auto arr = std::make_unique<Array>(nullptr);
    arr->add(Object(3));
    arr->add(Object(7));
    dict->add("PrintPageRange", Object(arr.release()));
    ViewerPreferences vp(*dict);

    auto range = vp.getPrintPageRange();
    ASSERT_EQ(range.size(), 1u);
    EXPECT_EQ(range[0].first, 3);
    EXPECT_EQ(range[0].second, 7);
}
