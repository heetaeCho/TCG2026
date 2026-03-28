#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "ViewerPreferences.h"
#include "Dict.h"
#include "PDFDoc.h"
#include "GlobalParams.h"

#include <memory>
#include <string>

class ViewerPreferencesTest_1346 : public ::testing::Test {
protected:
    void SetUp() override {
        if (!globalParams) {
            globalParams = std::make_unique<GlobalParams>();
        }
    }

    // Helper to create a Dict with specific viewer preference entries
    std::unique_ptr<Dict> createPrefDict(XRef *xref) {
        return std::make_unique<Dict>(xref);
    }
};

// Test with an empty dictionary - all defaults should apply
TEST_F(ViewerPreferencesTest_1346, DefaultValues_EmptyDict_1346) {
    Dict emptyDict(nullptr);
    ViewerPreferences vp(emptyDict);

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

// Test getHideMenubar returns false by default
TEST_F(ViewerPreferencesTest_1346, HideMenubarDefaultFalse_1346) {
    Dict emptyDict(nullptr);
    ViewerPreferences vp(emptyDict);

    EXPECT_FALSE(vp.getHideMenubar());
}

// Test getHideToolbar returns false by default
TEST_F(ViewerPreferencesTest_1346, HideToolbarDefaultFalse_1346) {
    Dict emptyDict(nullptr);
    ViewerPreferences vp(emptyDict);

    EXPECT_FALSE(vp.getHideToolbar());
}

// Test getHideWindowUI returns false by default
TEST_F(ViewerPreferencesTest_1346, HideWindowUIDefaultFalse_1346) {
    Dict emptyDict(nullptr);
    ViewerPreferences vp(emptyDict);

    EXPECT_FALSE(vp.getHideWindowUI());
}

// Test getFitWindow returns false by default
TEST_F(ViewerPreferencesTest_1346, FitWindowDefaultFalse_1346) {
    Dict emptyDict(nullptr);
    ViewerPreferences vp(emptyDict);

    EXPECT_FALSE(vp.getFitWindow());
}

// Test getCenterWindow returns false by default
TEST_F(ViewerPreferencesTest_1346, CenterWindowDefaultFalse_1346) {
    Dict emptyDict(nullptr);
    ViewerPreferences vp(emptyDict);

    EXPECT_FALSE(vp.getCenterWindow());
}

// Test getDisplayDocTitle returns false by default
TEST_F(ViewerPreferencesTest_1346, DisplayDocTitleDefaultFalse_1346) {
    Dict emptyDict(nullptr);
    ViewerPreferences vp(emptyDict);

    EXPECT_FALSE(vp.getDisplayDocTitle());
}

// Test getPickTrayByPDFSize returns false by default
TEST_F(ViewerPreferencesTest_1346, PickTrayByPDFSizeDefaultFalse_1346) {
    Dict emptyDict(nullptr);
    ViewerPreferences vp(emptyDict);

    EXPECT_FALSE(vp.getPickTrayByPDFSize());
}

// Test getNumCopies returns 1 by default
TEST_F(ViewerPreferencesTest_1346, NumCopiesDefault1_1346) {
    Dict emptyDict(nullptr);
    ViewerPreferences vp(emptyDict);

    EXPECT_EQ(vp.getNumCopies(), 1);
}

// Test getPrintPageRange returns empty vector by default
TEST_F(ViewerPreferencesTest_1346, PrintPageRangeDefaultEmpty_1346) {
    Dict emptyDict(nullptr);
    ViewerPreferences vp(emptyDict);

    std::vector<std::pair<int, int>> range = vp.getPrintPageRange();
    EXPECT_TRUE(range.empty());
}

// Test NonFullScreenPageMode default
TEST_F(ViewerPreferencesTest_1346, NonFullScreenPageModeDefault_1346) {
    Dict emptyDict(nullptr);
    ViewerPreferences vp(emptyDict);

    EXPECT_EQ(vp.getNonFullScreenPageMode(), ViewerPreferences::nfpmUseNone);
}

// Test Direction default
TEST_F(ViewerPreferencesTest_1346, DirectionDefault_1346) {
    Dict emptyDict(nullptr);
    ViewerPreferences vp(emptyDict);

    EXPECT_EQ(vp.getDirection(), ViewerPreferences::directionL2R);
}

// Test PrintScaling default
TEST_F(ViewerPreferencesTest_1346, PrintScalingDefault_1346) {
    Dict emptyDict(nullptr);
    ViewerPreferences vp(emptyDict);

    EXPECT_EQ(vp.getPrintScaling(), ViewerPreferences::printScalingAppDefault);
}

// Test Duplex default
TEST_F(ViewerPreferencesTest_1346, DuplexDefault_1346) {
    Dict emptyDict(nullptr);
    ViewerPreferences vp(emptyDict);

    EXPECT_EQ(vp.getDuplex(), ViewerPreferences::duplexNone);
}

// Test with a Dict that has HideToolbar set to true
TEST_F(ViewerPreferencesTest_1346, HideToolbarTrue_1346) {
    Dict prefDict(nullptr);
    prefDict.add("HideToolbar", Object(true));
    ViewerPreferences vp(prefDict);

    EXPECT_TRUE(vp.getHideToolbar());
}

// Test with a Dict that has HideMenubar set to true
TEST_F(ViewerPreferencesTest_1346, HideMenubarTrue_1346) {
    Dict prefDict(nullptr);
    prefDict.add("HideMenubar", Object(true));
    ViewerPreferences vp(prefDict);

    EXPECT_TRUE(vp.getHideMenubar());
}

// Test with a Dict that has HideWindowUI set to true
TEST_F(ViewerPreferencesTest_1346, HideWindowUITrue_1346) {
    Dict prefDict(nullptr);
    prefDict.add("HideWindowUI", Object(true));
    ViewerPreferences vp(prefDict);

    EXPECT_TRUE(vp.getHideWindowUI());
}

// Test with a Dict that has FitWindow set to true
TEST_F(ViewerPreferencesTest_1346, FitWindowTrue_1346) {
    Dict prefDict(nullptr);
    prefDict.add("FitWindow", Object(true));
    ViewerPreferences vp(prefDict);

    EXPECT_TRUE(vp.getFitWindow());
}

// Test with a Dict that has CenterWindow set to true
TEST_F(ViewerPreferencesTest_1346, CenterWindowTrue_1346) {
    Dict prefDict(nullptr);
    prefDict.add("CenterWindow", Object(true));
    ViewerPreferences vp(prefDict);

    EXPECT_TRUE(vp.getCenterWindow());
}

// Test with a Dict that has DisplayDocTitle set to true
TEST_F(ViewerPreferencesTest_1346, DisplayDocTitleTrue_1346) {
    Dict prefDict(nullptr);
    prefDict.add("DisplayDocTitle", Object(true));
    ViewerPreferences vp(prefDict);

    EXPECT_TRUE(vp.getDisplayDocTitle());
}

// Test with a Dict that has PickTrayByPDFSize set to true
TEST_F(ViewerPreferencesTest_1346, PickTrayByPDFSizeTrue_1346) {
    Dict prefDict(nullptr);
    prefDict.add("PickTrayByPDFSize", Object(true));
    ViewerPreferences vp(prefDict);

    EXPECT_TRUE(vp.getPickTrayByPDFSize());
}

// Test with a Dict that has NumCopies set to a specific value
TEST_F(ViewerPreferencesTest_1346, NumCopiesSpecificValue_1346) {
    Dict prefDict(nullptr);
    prefDict.add("NumCopies", Object(5));
    ViewerPreferences vp(prefDict);

    EXPECT_EQ(vp.getNumCopies(), 5);
}

// Test Direction set to R2L
TEST_F(ViewerPreferencesTest_1346, DirectionR2L_1346) {
    Dict prefDict(nullptr);
    prefDict.add("Direction", Object(objName, "R2L"));
    ViewerPreferences vp(prefDict);

    EXPECT_EQ(vp.getDirection(), ViewerPreferences::directionR2L);
}

// Test PrintScaling set to None
TEST_F(ViewerPreferencesTest_1346, PrintScalingNone_1346) {
    Dict prefDict(nullptr);
    prefDict.add("PrintScaling", Object(objName, "None"));
    ViewerPreferences vp(prefDict);

    EXPECT_EQ(vp.getPrintScaling(), ViewerPreferences::printScalingNone);
}

// Test NonFullScreenPageMode UseOutlines
TEST_F(ViewerPreferencesTest_1346, NonFullScreenPageModeUseOutlines_1346) {
    Dict prefDict(nullptr);
    prefDict.add("NonFullScreenPageMode", Object(objName, "UseOutlines"));
    ViewerPreferences vp(prefDict);

    EXPECT_EQ(vp.getNonFullScreenPageMode(), ViewerPreferences::nfpmUseOutlines);
}

// Test NonFullScreenPageMode UseThumbs
TEST_F(ViewerPreferencesTest_1346, NonFullScreenPageModeUseThumbs_1346) {
    Dict prefDict(nullptr);
    prefDict.add("NonFullScreenPageMode", Object(objName, "UseThumbs"));
    ViewerPreferences vp(prefDict);

    EXPECT_EQ(vp.getNonFullScreenPageMode(), ViewerPreferences::nfpmUseThumbs);
}

// Test NonFullScreenPageMode UseOC
TEST_F(ViewerPreferencesTest_1346, NonFullScreenPageModeUseOC_1346) {
    Dict prefDict(nullptr);
    prefDict.add("NonFullScreenPageMode", Object(objName, "UseOC"));
    ViewerPreferences vp(prefDict);

    EXPECT_EQ(vp.getNonFullScreenPageMode(), ViewerPreferences::nfpmUseOC);
}

// Test Duplex DuplexFlipShortEdge
TEST_F(ViewerPreferencesTest_1346, DuplexFlipShortEdge_1346) {
    Dict prefDict(nullptr);
    prefDict.add("Duplex", Object(objName, "DuplexFlipShortEdge"));
    ViewerPreferences vp(prefDict);

    EXPECT_EQ(vp.getDuplex(), ViewerPreferences::duplexFlipShortEdge);
}

// Test Duplex DuplexFlipLongEdge
TEST_F(ViewerPreferencesTest_1346, DuplexFlipLongEdge_1346) {
    Dict prefDict(nullptr);
    prefDict.add("Duplex", Object(objName, "DuplexFlipLongEdge"));
    ViewerPreferences vp(prefDict);

    EXPECT_EQ(vp.getDuplex(), ViewerPreferences::duplexFlipLongEdge);
}

// Test Duplex Simplex
TEST_F(ViewerPreferencesTest_1346, DuplexSimplex_1346) {
    Dict prefDict(nullptr);
    prefDict.add("Duplex", Object(objName, "Simplex"));
    ViewerPreferences vp(prefDict);

    EXPECT_EQ(vp.getDuplex(), ViewerPreferences::duplexSimplex);
}

// Test all boolean preferences set to false explicitly
TEST_F(ViewerPreferencesTest_1346, AllBooleansFalseExplicit_1346) {
    Dict prefDict(nullptr);
    prefDict.add("HideToolbar", Object(false));
    prefDict.add("HideMenubar", Object(false));
    prefDict.add("HideWindowUI", Object(false));
    prefDict.add("FitWindow", Object(false));
    prefDict.add("CenterWindow", Object(false));
    prefDict.add("DisplayDocTitle", Object(false));
    prefDict.add("PickTrayByPDFSize", Object(false));
    ViewerPreferences vp(prefDict);

    EXPECT_FALSE(vp.getHideToolbar());
    EXPECT_FALSE(vp.getHideMenubar());
    EXPECT_FALSE(vp.getHideWindowUI());
    EXPECT_FALSE(vp.getFitWindow());
    EXPECT_FALSE(vp.getCenterWindow());
    EXPECT_FALSE(vp.getDisplayDocTitle());
    EXPECT_FALSE(vp.getPickTrayByPDFSize());
}

// Test all boolean preferences set to true
TEST_F(ViewerPreferencesTest_1346, AllBooleansTrue_1346) {
    Dict prefDict(nullptr);
    prefDict.add("HideToolbar", Object(true));
    prefDict.add("HideMenubar", Object(true));
    prefDict.add("HideWindowUI", Object(true));
    prefDict.add("FitWindow", Object(true));
    prefDict.add("CenterWindow", Object(true));
    prefDict.add("DisplayDocTitle", Object(true));
    prefDict.add("PickTrayByPDFSize", Object(true));
    ViewerPreferences vp(prefDict);

    EXPECT_TRUE(vp.getHideToolbar());
    EXPECT_TRUE(vp.getHideMenubar());
    EXPECT_TRUE(vp.getHideWindowUI());
    EXPECT_TRUE(vp.getFitWindow());
    EXPECT_TRUE(vp.getCenterWindow());
    EXPECT_TRUE(vp.getDisplayDocTitle());
    EXPECT_TRUE(vp.getPickTrayByPDFSize());
}

// Test with PrintPageRange array
TEST_F(ViewerPreferencesTest_1346, PrintPageRangeWithEntries_1346) {
    Dict prefDict(nullptr);
    Array *arr = new Array(nullptr);
    arr->add(Object(1));
    arr->add(Object(5));
    arr->add(Object(10));
    arr->add(Object(15));
    prefDict.add("PrintPageRange", Object(arr));
    ViewerPreferences vp(prefDict);

    std::vector<std::pair<int, int>> range = vp.getPrintPageRange();
    ASSERT_EQ(range.size(), 2u);
    EXPECT_EQ(range[0].first, 1);
    EXPECT_EQ(range[0].second, 5);
    EXPECT_EQ(range[1].first, 10);
    EXPECT_EQ(range[1].second, 15);
}

// Test NumCopies boundary: value of 0
TEST_F(ViewerPreferencesTest_1346, NumCopiesZero_1346) {
    Dict prefDict(nullptr);
    prefDict.add("NumCopies", Object(0));
    ViewerPreferences vp(prefDict);

    // Behavior for 0 copies depends on implementation; just verify it doesn't crash
    int copies = vp.getNumCopies();
    (void)copies;
}

// Test NumCopies with large value
TEST_F(ViewerPreferencesTest_1346, NumCopiesLargeValue_1346) {
    Dict prefDict(nullptr);
    prefDict.add("NumCopies", Object(1000));
    ViewerPreferences vp(prefDict);

    EXPECT_EQ(vp.getNumCopies(), 1000);
}
