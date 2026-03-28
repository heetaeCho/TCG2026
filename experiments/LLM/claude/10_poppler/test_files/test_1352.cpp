#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "ViewerPreferences.h"
#include "Dict.h"
#include "PDFDoc.h"
#include "GlobalParams.h"

#include <memory>
#include <string>
#include <vector>
#include <utility>

class ViewerPreferencesTest_1352 : public ::testing::Test {
protected:
    void SetUp() override {
        if (!globalParams) {
            globalParams = std::make_unique<GlobalParams>();
        }
    }

    // Helper to create a Dict with specific entries
    // We need an XRef for Dict, but we can pass nullptr for simple cases
    std::unique_ptr<Dict> createDict() {
        return std::make_unique<Dict>(nullptr);
    }
};

// Test default direction value (L2R) when no Direction entry in dict
TEST_F(ViewerPreferencesTest_1352, DefaultDirection_1352) {
    Dict dict(nullptr);
    ViewerPreferences vp(dict);
    EXPECT_EQ(vp.getDirection(), ViewerPreferences::directionL2R);
}

// Test default values for boolean preferences with empty dict
TEST_F(ViewerPreferencesTest_1352, DefaultHideToolbar_1352) {
    Dict dict(nullptr);
    ViewerPreferences vp(dict);
    EXPECT_FALSE(vp.getHideToolbar());
}

TEST_F(ViewerPreferencesTest_1352, DefaultHideMenubar_1352) {
    Dict dict(nullptr);
    ViewerPreferences vp(dict);
    EXPECT_FALSE(vp.getHideMenubar());
}

TEST_F(ViewerPreferencesTest_1352, DefaultHideWindowUI_1352) {
    Dict dict(nullptr);
    ViewerPreferences vp(dict);
    EXPECT_FALSE(vp.getHideWindowUI());
}

TEST_F(ViewerPreferencesTest_1352, DefaultFitWindow_1352) {
    Dict dict(nullptr);
    ViewerPreferences vp(dict);
    EXPECT_FALSE(vp.getFitWindow());
}

TEST_F(ViewerPreferencesTest_1352, DefaultCenterWindow_1352) {
    Dict dict(nullptr);
    ViewerPreferences vp(dict);
    EXPECT_FALSE(vp.getCenterWindow());
}

TEST_F(ViewerPreferencesTest_1352, DefaultDisplayDocTitle_1352) {
    Dict dict(nullptr);
    ViewerPreferences vp(dict);
    EXPECT_FALSE(vp.getDisplayDocTitle());
}

TEST_F(ViewerPreferencesTest_1352, DefaultNonFullScreenPageMode_1352) {
    Dict dict(nullptr);
    ViewerPreferences vp(dict);
    EXPECT_EQ(vp.getNonFullScreenPageMode(), ViewerPreferences::nfpmUseNone);
}

TEST_F(ViewerPreferencesTest_1352, DefaultPrintScaling_1352) {
    Dict dict(nullptr);
    ViewerPreferences vp(dict);
    EXPECT_EQ(vp.getPrintScaling(), ViewerPreferences::printScalingAppDefault);
}

TEST_F(ViewerPreferencesTest_1352, DefaultDuplex_1352) {
    Dict dict(nullptr);
    ViewerPreferences vp(dict);
    EXPECT_EQ(vp.getDuplex(), ViewerPreferences::duplexNone);
}

TEST_F(ViewerPreferencesTest_1352, DefaultPickTrayByPDFSize_1352) {
    Dict dict(nullptr);
    ViewerPreferences vp(dict);
    EXPECT_FALSE(vp.getPickTrayByPDFSize());
}

TEST_F(ViewerPreferencesTest_1352, DefaultNumCopies_1352) {
    Dict dict(nullptr);
    ViewerPreferences vp(dict);
    EXPECT_EQ(vp.getNumCopies(), 1);
}

TEST_F(ViewerPreferencesTest_1352, DefaultPrintPageRange_1352) {
    Dict dict(nullptr);
    ViewerPreferences vp(dict);
    std::vector<std::pair<int, int>> range = vp.getPrintPageRange();
    EXPECT_TRUE(range.empty());
}

// Test with HideToolbar set to true
TEST_F(ViewerPreferencesTest_1352, HideToolbarTrue_1352) {
    Dict dict(nullptr);
    dict.add("HideToolbar", Object(true));
    ViewerPreferences vp(dict);
    EXPECT_TRUE(vp.getHideToolbar());
}

// Test with HideMenubar set to true
TEST_F(ViewerPreferencesTest_1352, HideMenubarTrue_1352) {
    Dict dict(nullptr);
    dict.add("HideMenubar", Object(true));
    ViewerPreferences vp(dict);
    EXPECT_TRUE(vp.getHideMenubar());
}

// Test with HideWindowUI set to true
TEST_F(ViewerPreferencesTest_1352, HideWindowUITrue_1352) {
    Dict dict(nullptr);
    dict.add("HideWindowUI", Object(true));
    ViewerPreferences vp(dict);
    EXPECT_TRUE(vp.getHideWindowUI());
}

// Test with FitWindow set to true
TEST_F(ViewerPreferencesTest_1352, FitWindowTrue_1352) {
    Dict dict(nullptr);
    dict.add("FitWindow", Object(true));
    ViewerPreferences vp(dict);
    EXPECT_TRUE(vp.getFitWindow());
}

// Test with CenterWindow set to true
TEST_F(ViewerPreferencesTest_1352, CenterWindowTrue_1352) {
    Dict dict(nullptr);
    dict.add("CenterWindow", Object(true));
    ViewerPreferences vp(dict);
    EXPECT_TRUE(vp.getCenterWindow());
}

// Test with DisplayDocTitle set to true
TEST_F(ViewerPreferencesTest_1352, DisplayDocTitleTrue_1352) {
    Dict dict(nullptr);
    dict.add("DisplayDocTitle", Object(true));
    ViewerPreferences vp(dict);
    EXPECT_TRUE(vp.getDisplayDocTitle());
}

// Test Direction R2L
TEST_F(ViewerPreferencesTest_1352, DirectionR2L_1352) {
    Dict dict(nullptr);
    dict.add("Direction", Object(objName, "R2L"));
    ViewerPreferences vp(dict);
    EXPECT_EQ(vp.getDirection(), ViewerPreferences::directionR2L);
}

// Test Direction L2R explicitly
TEST_F(ViewerPreferencesTest_1352, DirectionL2LExplicit_1352) {
    Dict dict(nullptr);
    dict.add("Direction", Object(objName, "L2R"));
    ViewerPreferences vp(dict);
    EXPECT_EQ(vp.getDirection(), ViewerPreferences::directionL2R);
}

// Test NonFullScreenPageMode UseOutlines
TEST_F(ViewerPreferencesTest_1352, NonFullScreenPageModeUseOutlines_1352) {
    Dict dict(nullptr);
    dict.add("NonFullScreenPageMode", Object(objName, "UseOutlines"));
    ViewerPreferences vp(dict);
    EXPECT_EQ(vp.getNonFullScreenPageMode(), ViewerPreferences::nfpmUseOutlines);
}

// Test NonFullScreenPageMode UseThumbs
TEST_F(ViewerPreferencesTest_1352, NonFullScreenPageModeUseThumbs_1352) {
    Dict dict(nullptr);
    dict.add("NonFullScreenPageMode", Object(objName, "UseThumbs"));
    ViewerPreferences vp(dict);
    EXPECT_EQ(vp.getNonFullScreenPageMode(), ViewerPreferences::nfpmUseThumbs);
}

// Test NonFullScreenPageMode UseOC
TEST_F(ViewerPreferencesTest_1352, NonFullScreenPageModeUseOC_1352) {
    Dict dict(nullptr);
    dict.add("NonFullScreenPageMode", Object(objName, "UseOC"));
    ViewerPreferences vp(dict);
    EXPECT_EQ(vp.getNonFullScreenPageMode(), ViewerPreferences::nfpmUseOC);
}

// Test PrintScaling None
TEST_F(ViewerPreferencesTest_1352, PrintScalingNone_1352) {
    Dict dict(nullptr);
    dict.add("PrintScaling", Object(objName, "None"));
    ViewerPreferences vp(dict);
    EXPECT_EQ(vp.getPrintScaling(), ViewerPreferences::printScalingNone);
}

// Test Duplex Simplex
TEST_F(ViewerPreferencesTest_1352, DuplexSimplex_1352) {
    Dict dict(nullptr);
    dict.add("Duplex", Object(objName, "Simplex"));
    ViewerPreferences vp(dict);
    EXPECT_EQ(vp.getDuplex(), ViewerPreferences::duplexSimplex);
}

// Test Duplex DuplexFlipShortEdge
TEST_F(ViewerPreferencesTest_1352, DuplexFlipShortEdge_1352) {
    Dict dict(nullptr);
    dict.add("Duplex", Object(objName, "DuplexFlipShortEdge"));
    ViewerPreferences vp(dict);
    EXPECT_EQ(vp.getDuplex(), ViewerPreferences::duplexFlipShortEdge);
}

// Test Duplex DuplexFlipLongEdge
TEST_F(ViewerPreferencesTest_1352, DuplexFlipLongEdge_1352) {
    Dict dict(nullptr);
    dict.add("Duplex", Object(objName, "DuplexFlipLongEdge"));
    ViewerPreferences vp(dict);
    EXPECT_EQ(vp.getDuplex(), ViewerPreferences::duplexFlipLongEdge);
}

// Test PickTrayByPDFSize true
TEST_F(ViewerPreferencesTest_1352, PickTrayByPDFSizeTrue_1352) {
    Dict dict(nullptr);
    dict.add("PickTrayByPDFSize", Object(true));
    ViewerPreferences vp(dict);
    EXPECT_TRUE(vp.getPickTrayByPDFSize());
}

// Test NumCopies with specific value
TEST_F(ViewerPreferencesTest_1352, NumCopiesSpecificValue_1352) {
    Dict dict(nullptr);
    dict.add("NumCopies", Object(5));
    ViewerPreferences vp(dict);
    EXPECT_EQ(vp.getNumCopies(), 5);
}

// Test that boolean false is handled correctly
TEST_F(ViewerPreferencesTest_1352, HideToolbarFalse_1352) {
    Dict dict(nullptr);
    dict.add("HideToolbar", Object(false));
    ViewerPreferences vp(dict);
    EXPECT_FALSE(vp.getHideToolbar());
}

// Test with invalid Direction name - should default
TEST_F(ViewerPreferencesTest_1352, DirectionInvalidName_1352) {
    Dict dict(nullptr);
    dict.add("Direction", Object(objName, "InvalidDirection"));
    ViewerPreferences vp(dict);
    // Should remain at default
    EXPECT_EQ(vp.getDirection(), ViewerPreferences::directionL2R);
}

// Test NumCopies with value 1 (boundary)
TEST_F(ViewerPreferencesTest_1352, NumCopiesBoundaryOne_1352) {
    Dict dict(nullptr);
    dict.add("NumCopies", Object(1));
    ViewerPreferences vp(dict);
    EXPECT_EQ(vp.getNumCopies(), 1);
}

// Test multiple preferences set simultaneously
TEST_F(ViewerPreferencesTest_1352, MultiplePreferences_1352) {
    Dict dict(nullptr);
    dict.add("HideToolbar", Object(true));
    dict.add("HideMenubar", Object(true));
    dict.add("FitWindow", Object(true));
    dict.add("Direction", Object(objName, "R2L"));
    dict.add("NumCopies", Object(3));
    ViewerPreferences vp(dict);
    EXPECT_TRUE(vp.getHideToolbar());
    EXPECT_TRUE(vp.getHideMenubar());
    EXPECT_TRUE(vp.getFitWindow());
    EXPECT_FALSE(vp.getHideWindowUI());
    EXPECT_EQ(vp.getDirection(), ViewerPreferences::directionR2L);
    EXPECT_EQ(vp.getNumCopies(), 3);
}
