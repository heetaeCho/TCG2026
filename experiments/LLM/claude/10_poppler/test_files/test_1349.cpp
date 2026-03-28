#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "ViewerPreferences.h"
#include "Dict.h"
#include "PDFDoc.h"
#include "GlobalParams.h"

#include <memory>
#include <string>

class ViewerPreferencesTest_1349 : public ::testing::Test {
protected:
    void SetUp() override {
        if (!globalParams) {
            globalParams = std::make_unique<GlobalParams>();
        }
    }

    // Helper to create a Dict with specific viewer preference entries
    // We need an XRef for Dict, so we use a minimal approach
    std::unique_ptr<Dict> createDict(XRef *xref) {
        return std::make_unique<Dict>(xref);
    }
};

// Test with empty dictionary - all defaults should apply
TEST_F(ViewerPreferencesTest_1349, DefaultValues_EmptyDict_1349) {
    Dict dict(nullptr);
    ViewerPreferences vp(dict);

    EXPECT_FALSE(vp.getHideToolbar());
    EXPECT_FALSE(vp.getHideMenubar());
    EXPECT_FALSE(vp.getHideWindowUI());
    EXPECT_FALSE(vp.getFitWindow());
    EXPECT_FALSE(vp.getCenterWindow());
    EXPECT_FALSE(vp.getDisplayDocTitle());
    EXPECT_EQ(vp.getNumCopies(), 1);
    EXPECT_FALSE(vp.getPickTrayByPDFSize());
    EXPECT_TRUE(vp.getPrintPageRange().empty());
}

// Test NonFullScreenPageMode default
TEST_F(ViewerPreferencesTest_1349, DefaultNonFullScreenPageMode_1349) {
    Dict dict(nullptr);
    ViewerPreferences vp(dict);

    EXPECT_EQ(vp.getNonFullScreenPageMode(), ViewerPreferences::nfpmUseNone);
}

// Test Direction default
TEST_F(ViewerPreferencesTest_1349, DefaultDirection_1349) {
    Dict dict(nullptr);
    ViewerPreferences vp(dict);

    EXPECT_EQ(vp.getDirection(), ViewerPreferences::directionL2R);
}

// Test PrintScaling default
TEST_F(ViewerPreferencesTest_1349, DefaultPrintScaling_1349) {
    Dict dict(nullptr);
    ViewerPreferences vp(dict);

    EXPECT_EQ(vp.getPrintScaling(), ViewerPreferences::printScalingAppDefault);
}

// Test Duplex default
TEST_F(ViewerPreferencesTest_1349, DefaultDuplex_1349) {
    Dict dict(nullptr);
    ViewerPreferences vp(dict);

    EXPECT_EQ(vp.getDuplex(), ViewerPreferences::duplexNone);
}

// Test with HideToolbar set to true
TEST_F(ViewerPreferencesTest_1349, HideToolbarTrue_1349) {
    Dict dict(nullptr);
    dict.add("HideToolbar", Object(true));
    ViewerPreferences vp(dict);

    EXPECT_TRUE(vp.getHideToolbar());
}

// Test with HideMenubar set to true
TEST_F(ViewerPreferencesTest_1349, HideMenubarTrue_1349) {
    Dict dict(nullptr);
    dict.add("HideMenubar", Object(true));
    ViewerPreferences vp(dict);

    EXPECT_TRUE(vp.getHideMenubar());
}

// Test with HideWindowUI set to true
TEST_F(ViewerPreferencesTest_1349, HideWindowUITrue_1349) {
    Dict dict(nullptr);
    dict.add("HideWindowUI", Object(true));
    ViewerPreferences vp(dict);

    EXPECT_TRUE(vp.getHideWindowUI());
}

// Test with FitWindow set to true
TEST_F(ViewerPreferencesTest_1349, FitWindowTrue_1349) {
    Dict dict(nullptr);
    dict.add("FitWindow", Object(true));
    ViewerPreferences vp(dict);

    EXPECT_TRUE(vp.getFitWindow());
}

// Test with CenterWindow set to true
TEST_F(ViewerPreferencesTest_1349, CenterWindowTrue_1349) {
    Dict dict(nullptr);
    dict.add("CenterWindow", Object(true));
    ViewerPreferences vp(dict);

    EXPECT_TRUE(vp.getCenterWindow());
}

// Test with DisplayDocTitle set to true
TEST_F(ViewerPreferencesTest_1349, DisplayDocTitleTrue_1349) {
    Dict dict(nullptr);
    dict.add("DisplayDocTitle", Object(true));
    ViewerPreferences vp(dict);

    EXPECT_TRUE(vp.getDisplayDocTitle());
}

// Test with CenterWindow set to false explicitly
TEST_F(ViewerPreferencesTest_1349, CenterWindowFalse_1349) {
    Dict dict(nullptr);
    dict.add("CenterWindow", Object(false));
    ViewerPreferences vp(dict);

    EXPECT_FALSE(vp.getCenterWindow());
}

// Test with NumCopies set
TEST_F(ViewerPreferencesTest_1349, NumCopiesSet_1349) {
    Dict dict(nullptr);
    dict.add("NumCopies", Object(5));
    ViewerPreferences vp(dict);

    EXPECT_EQ(vp.getNumCopies(), 5);
}

// Test with NumCopies = 1 (default)
TEST_F(ViewerPreferencesTest_1349, NumCopiesDefault_1349) {
    Dict dict(nullptr);
    ViewerPreferences vp(dict);

    EXPECT_EQ(vp.getNumCopies(), 1);
}

// Test with Direction R2L
TEST_F(ViewerPreferencesTest_1349, DirectionR2L_1349) {
    Dict dict(nullptr);
    dict.add("Direction", Object(objName, "R2L"));
    ViewerPreferences vp(dict);

    EXPECT_EQ(vp.getDirection(), ViewerPreferences::directionR2L);
}

// Test with Direction L2R explicit
TEST_F(ViewerPreferencesTest_1349, DirectionL2LExplicit_1349) {
    Dict dict(nullptr);
    dict.add("Direction", Object(objName, "L2R"));
    ViewerPreferences vp(dict);

    EXPECT_EQ(vp.getDirection(), ViewerPreferences::directionL2R);
}

// Test with PrintScaling None
TEST_F(ViewerPreferencesTest_1349, PrintScalingNone_1349) {
    Dict dict(nullptr);
    dict.add("PrintScaling", Object(objName, "None"));
    ViewerPreferences vp(dict);

    EXPECT_EQ(vp.getPrintScaling(), ViewerPreferences::printScalingNone);
}

// Test with Duplex Simplex
TEST_F(ViewerPreferencesTest_1349, DuplexSimplex_1349) {
    Dict dict(nullptr);
    dict.add("Duplex", Object(objName, "Simplex"));
    ViewerPreferences vp(dict);

    EXPECT_EQ(vp.getDuplex(), ViewerPreferences::duplexSimplex);
}

// Test with Duplex DuplexFlipShortEdge
TEST_F(ViewerPreferencesTest_1349, DuplexFlipShortEdge_1349) {
    Dict dict(nullptr);
    dict.add("Duplex", Object(objName, "DuplexFlipShortEdge"));
    ViewerPreferences vp(dict);

    EXPECT_EQ(vp.getDuplex(), ViewerPreferences::duplexFlipShortEdge);
}

// Test with Duplex DuplexFlipLongEdge
TEST_F(ViewerPreferencesTest_1349, DuplexFlipLongEdge_1349) {
    Dict dict(nullptr);
    dict.add("Duplex", Object(objName, "DuplexFlipLongEdge"));
    ViewerPreferences vp(dict);

    EXPECT_EQ(vp.getDuplex(), ViewerPreferences::duplexFlipLongEdge);
}

// Test with PickTrayByPDFSize set to true
TEST_F(ViewerPreferencesTest_1349, PickTrayByPDFSizeTrue_1349) {
    Dict dict(nullptr);
    dict.add("PickTrayByPDFSize", Object(true));
    ViewerPreferences vp(dict);

    EXPECT_TRUE(vp.getPickTrayByPDFSize());
}

// Test NonFullScreenPageMode UseOutlines
TEST_F(ViewerPreferencesTest_1349, NonFullScreenPageModeUseOutlines_1349) {
    Dict dict(nullptr);
    dict.add("NonFullScreenPageMode", Object(objName, "UseOutlines"));
    ViewerPreferences vp(dict);

    EXPECT_EQ(vp.getNonFullScreenPageMode(), ViewerPreferences::nfpmUseOutlines);
}

// Test NonFullScreenPageMode UseThumbs
TEST_F(ViewerPreferencesTest_1349, NonFullScreenPageModeUseThumbs_1349) {
    Dict dict(nullptr);
    dict.add("NonFullScreenPageMode", Object(objName, "UseThumbs"));
    ViewerPreferences vp(dict);

    EXPECT_EQ(vp.getNonFullScreenPageMode(), ViewerPreferences::nfpmUseThumbs);
}

// Test NonFullScreenPageMode UseOC
TEST_F(ViewerPreferencesTest_1349, NonFullScreenPageModeUseOC_1349) {
    Dict dict(nullptr);
    dict.add("NonFullScreenPageMode", Object(objName, "UseOC"));
    ViewerPreferences vp(dict);

    EXPECT_EQ(vp.getNonFullScreenPageMode(), ViewerPreferences::nfpmUseOC);
}

// Test all boolean values set to true simultaneously
TEST_F(ViewerPreferencesTest_1349, AllBooleanTrue_1349) {
    Dict dict(nullptr);
    dict.add("HideToolbar", Object(true));
    dict.add("HideMenubar", Object(true));
    dict.add("HideWindowUI", Object(true));
    dict.add("FitWindow", Object(true));
    dict.add("CenterWindow", Object(true));
    dict.add("DisplayDocTitle", Object(true));
    dict.add("PickTrayByPDFSize", Object(true));
    ViewerPreferences vp(dict);

    EXPECT_TRUE(vp.getHideToolbar());
    EXPECT_TRUE(vp.getHideMenubar());
    EXPECT_TRUE(vp.getHideWindowUI());
    EXPECT_TRUE(vp.getFitWindow());
    EXPECT_TRUE(vp.getCenterWindow());
    EXPECT_TRUE(vp.getDisplayDocTitle());
    EXPECT_TRUE(vp.getPickTrayByPDFSize());
}

// Test PrintPageRange empty by default
TEST_F(ViewerPreferencesTest_1349, PrintPageRangeEmptyByDefault_1349) {
    Dict dict(nullptr);
    ViewerPreferences vp(dict);

    std::vector<std::pair<int, int>> range = vp.getPrintPageRange();
    EXPECT_TRUE(range.empty());
}

// Test consistency - calling getters multiple times returns same value
TEST_F(ViewerPreferencesTest_1349, GetterConsistency_1349) {
    Dict dict(nullptr);
    dict.add("CenterWindow", Object(true));
    dict.add("NumCopies", Object(3));
    ViewerPreferences vp(dict);

    EXPECT_EQ(vp.getCenterWindow(), vp.getCenterWindow());
    EXPECT_EQ(vp.getNumCopies(), vp.getNumCopies());
    EXPECT_EQ(vp.getDirection(), vp.getDirection());
    EXPECT_EQ(vp.getPrintScaling(), vp.getPrintScaling());
    EXPECT_EQ(vp.getDuplex(), vp.getDuplex());
}
