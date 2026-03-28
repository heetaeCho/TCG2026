#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "poppler/ViewerPreferences.h"
#include "poppler/Dict.h"
#include "poppler/PDFDoc.h"
#include "poppler/GlobalParams.h"

#include <memory>
#include <string>
#include <vector>
#include <utility>

class ViewerPreferencesTest_1355 : public ::testing::Test {
protected:
    static void SetUpTestSuite() {
        if (!globalParams) {
            globalParams = std::make_unique<GlobalParams>();
        }
    }

    // Helper to create a Dict with specific viewer preference entries
    // We need an XRef for Dict, but we can use nullptr in some versions
    // or create a minimal setup
};

// Test with a minimal/empty preferences dictionary
TEST_F(ViewerPreferencesTest_1355, DefaultValuesFromEmptyDict_1355) {
    // Create an empty Dict - the ViewerPreferences should use defaults
    auto xref = (XRef*)nullptr;
    Dict dict(xref);
    
    ViewerPreferences vp(dict);
    
    // Default values based on PDF spec defaults
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

// Test HideToolbar set to true
TEST_F(ViewerPreferencesTest_1355, HideToolbarTrue_1355) {
    auto xref = (XRef*)nullptr;
    Dict dict(xref);
    dict.add("HideToolbar", Object(true));
    
    ViewerPreferences vp(dict);
    EXPECT_TRUE(vp.getHideToolbar());
}

// Test HideToolbar set to false
TEST_F(ViewerPreferencesTest_1355, HideToolbarFalse_1355) {
    auto xref = (XRef*)nullptr;
    Dict dict(xref);
    dict.add("HideToolbar", Object(false));
    
    ViewerPreferences vp(dict);
    EXPECT_FALSE(vp.getHideToolbar());
}

// Test HideMenubar set to true
TEST_F(ViewerPreferencesTest_1355, HideMenubarTrue_1355) {
    auto xref = (XRef*)nullptr;
    Dict dict(xref);
    dict.add("HideMenubar", Object(true));
    
    ViewerPreferences vp(dict);
    EXPECT_TRUE(vp.getHideMenubar());
}

// Test HideWindowUI set to true
TEST_F(ViewerPreferencesTest_1355, HideWindowUITrue_1355) {
    auto xref = (XRef*)nullptr;
    Dict dict(xref);
    dict.add("HideWindowUI", Object(true));
    
    ViewerPreferences vp(dict);
    EXPECT_TRUE(vp.getHideWindowUI());
}

// Test FitWindow set to true
TEST_F(ViewerPreferencesTest_1355, FitWindowTrue_1355) {
    auto xref = (XRef*)nullptr;
    Dict dict(xref);
    dict.add("FitWindow", Object(true));
    
    ViewerPreferences vp(dict);
    EXPECT_TRUE(vp.getFitWindow());
}

// Test CenterWindow set to true
TEST_F(ViewerPreferencesTest_1355, CenterWindowTrue_1355) {
    auto xref = (XRef*)nullptr;
    Dict dict(xref);
    dict.add("CenterWindow", Object(true));
    
    ViewerPreferences vp(dict);
    EXPECT_TRUE(vp.getCenterWindow());
}

// Test DisplayDocTitle set to true
TEST_F(ViewerPreferencesTest_1355, DisplayDocTitleTrue_1355) {
    auto xref = (XRef*)nullptr;
    Dict dict(xref);
    dict.add("DisplayDocTitle", Object(true));
    
    ViewerPreferences vp(dict);
    EXPECT_TRUE(vp.getDisplayDocTitle());
}

// Test PickTrayByPDFSize set to true
TEST_F(ViewerPreferencesTest_1355, PickTrayByPDFSizeTrue_1355) {
    auto xref = (XRef*)nullptr;
    Dict dict(xref);
    dict.add("PickTrayByPDFSize", Object(true));
    
    ViewerPreferences vp(dict);
    EXPECT_TRUE(vp.getPickTrayByPDFSize());
}

// Test PickTrayByPDFSize set to false
TEST_F(ViewerPreferencesTest_1355, PickTrayByPDFSizeFalse_1355) {
    auto xref = (XRef*)nullptr;
    Dict dict(xref);
    dict.add("PickTrayByPDFSize", Object(false));
    
    ViewerPreferences vp(dict);
    EXPECT_FALSE(vp.getPickTrayByPDFSize());
}

// Test NumCopies
TEST_F(ViewerPreferencesTest_1355, NumCopiesSet_1355) {
    auto xref = (XRef*)nullptr;
    Dict dict(xref);
    dict.add("NumCopies", Object(5));
    
    ViewerPreferences vp(dict);
    EXPECT_EQ(vp.getNumCopies(), 5);
}

// Test NumCopies default
TEST_F(ViewerPreferencesTest_1355, NumCopiesDefault_1355) {
    auto xref = (XRef*)nullptr;
    Dict dict(xref);
    
    ViewerPreferences vp(dict);
    EXPECT_EQ(vp.getNumCopies(), 1);
}

// Test Direction L2R
TEST_F(ViewerPreferencesTest_1355, DirectionL2R_1355) {
    auto xref = (XRef*)nullptr;
    Dict dict(xref);
    dict.add("Direction", Object(objName, "L2R"));
    
    ViewerPreferences vp(dict);
    EXPECT_EQ(vp.getDirection(), ViewerPreferences::directionL2R);
}

// Test Direction R2L
TEST_F(ViewerPreferencesTest_1355, DirectionR2L_1355) {
    auto xref = (XRef*)nullptr;
    Dict dict(xref);
    dict.add("Direction", Object(objName, "R2L"));
    
    ViewerPreferences vp(dict);
    EXPECT_EQ(vp.getDirection(), ViewerPreferences::directionR2L);
}

// Test NonFullScreenPageMode UseNone (default)
TEST_F(ViewerPreferencesTest_1355, NonFullScreenPageModeDefault_1355) {
    auto xref = (XRef*)nullptr;
    Dict dict(xref);
    
    ViewerPreferences vp(dict);
    EXPECT_EQ(vp.getNonFullScreenPageMode(), ViewerPreferences::nfpmUseNone);
}

// Test NonFullScreenPageMode UseOutlines
TEST_F(ViewerPreferencesTest_1355, NonFullScreenPageModeUseOutlines_1355) {
    auto xref = (XRef*)nullptr;
    Dict dict(xref);
    dict.add("NonFullScreenPageMode", Object(objName, "UseOutlines"));
    
    ViewerPreferences vp(dict);
    EXPECT_EQ(vp.getNonFullScreenPageMode(), ViewerPreferences::nfpmUseOutlines);
}

// Test NonFullScreenPageMode UseThumbs
TEST_F(ViewerPreferencesTest_1355, NonFullScreenPageModeUseThumbs_1355) {
    auto xref = (XRef*)nullptr;
    Dict dict(xref);
    dict.add("NonFullScreenPageMode", Object(objName, "UseThumbs"));
    
    ViewerPreferences vp(dict);
    EXPECT_EQ(vp.getNonFullScreenPageMode(), ViewerPreferences::nfpmUseThumbs);
}

// Test NonFullScreenPageMode UseOC
TEST_F(ViewerPreferencesTest_1355, NonFullScreenPageModeUseOC_1355) {
    auto xref = (XRef*)nullptr;
    Dict dict(xref);
    dict.add("NonFullScreenPageMode", Object(objName, "UseOC"));
    
    ViewerPreferences vp(dict);
    EXPECT_EQ(vp.getNonFullScreenPageMode(), ViewerPreferences::nfpmUseOC);
}

// Test PrintScaling None
TEST_F(ViewerPreferencesTest_1355, PrintScalingNone_1355) {
    auto xref = (XRef*)nullptr;
    Dict dict(xref);
    dict.add("PrintScaling", Object(objName, "None"));
    
    ViewerPreferences vp(dict);
    EXPECT_EQ(vp.getPrintScaling(), ViewerPreferences::printScalingNone);
}

// Test PrintScaling AppDefault
TEST_F(ViewerPreferencesTest_1355, PrintScalingAppDefault_1355) {
    auto xref = (XRef*)nullptr;
    Dict dict(xref);
    dict.add("PrintScaling", Object(objName, "AppDefault"));
    
    ViewerPreferences vp(dict);
    EXPECT_EQ(vp.getPrintScaling(), ViewerPreferences::printScalingAppDefault);
}

// Test PrintScaling default value
TEST_F(ViewerPreferencesTest_1355, PrintScalingDefault_1355) {
    auto xref = (XRef*)nullptr;
    Dict dict(xref);
    
    ViewerPreferences vp(dict);
    EXPECT_EQ(vp.getPrintScaling(), ViewerPreferences::printScalingAppDefault);
}

// Test Duplex None (default)
TEST_F(ViewerPreferencesTest_1355, DuplexDefault_1355) {
    auto xref = (XRef*)nullptr;
    Dict dict(xref);
    
    ViewerPreferences vp(dict);
    EXPECT_EQ(vp.getDuplex(), ViewerPreferences::duplexNone);
}

// Test Duplex Simplex
TEST_F(ViewerPreferencesTest_1355, DuplexSimplex_1355) {
    auto xref = (XRef*)nullptr;
    Dict dict(xref);
    dict.add("Duplex", Object(objName, "Simplex"));
    
    ViewerPreferences vp(dict);
    EXPECT_EQ(vp.getDuplex(), ViewerPreferences::duplexSimplex);
}

// Test Duplex DuplexFlipShortEdge
TEST_F(ViewerPreferencesTest_1355, DuplexFlipShortEdge_1355) {
    auto xref = (XRef*)nullptr;
    Dict dict(xref);
    dict.add("Duplex", Object(objName, "DuplexFlipShortEdge"));
    
    ViewerPreferences vp(dict);
    EXPECT_EQ(vp.getDuplex(), ViewerPreferences::duplexFlipShortEdge);
}

// Test Duplex DuplexFlipLongEdge
TEST_F(ViewerPreferencesTest_1355, DuplexFlipLongEdge_1355) {
    auto xref = (XRef*)nullptr;
    Dict dict(xref);
    dict.add("Duplex", Object(objName, "DuplexFlipLongEdge"));
    
    ViewerPreferences vp(dict);
    EXPECT_EQ(vp.getDuplex(), ViewerPreferences::duplexFlipLongEdge);
}

// Test PrintPageRange empty by default
TEST_F(ViewerPreferencesTest_1355, PrintPageRangeEmptyDefault_1355) {
    auto xref = (XRef*)nullptr;
    Dict dict(xref);
    
    ViewerPreferences vp(dict);
    auto range = vp.getPrintPageRange();
    EXPECT_TRUE(range.empty());
}

// Test multiple boolean preferences set simultaneously
TEST_F(ViewerPreferencesTest_1355, MultipleBooleanPreferences_1355) {
    auto xref = (XRef*)nullptr;
    Dict dict(xref);
    dict.add("HideToolbar", Object(true));
    dict.add("HideMenubar", Object(true));
    dict.add("FitWindow", Object(true));
    dict.add("CenterWindow", Object(false));
    dict.add("DisplayDocTitle", Object(true));
    
    ViewerPreferences vp(dict);
    EXPECT_TRUE(vp.getHideToolbar());
    EXPECT_TRUE(vp.getHideMenubar());
    EXPECT_FALSE(vp.getHideWindowUI());
    EXPECT_TRUE(vp.getFitWindow());
    EXPECT_FALSE(vp.getCenterWindow());
    EXPECT_TRUE(vp.getDisplayDocTitle());
}

// Test NumCopies boundary - value of 1
TEST_F(ViewerPreferencesTest_1355, NumCopiesBoundaryOne_1355) {
    auto xref = (XRef*)nullptr;
    Dict dict(xref);
    dict.add("NumCopies", Object(1));
    
    ViewerPreferences vp(dict);
    EXPECT_EQ(vp.getNumCopies(), 1);
}

// Test all preferences set together
TEST_F(ViewerPreferencesTest_1355, AllPreferencesSet_1355) {
    auto xref = (XRef*)nullptr;
    Dict dict(xref);
    dict.add("HideToolbar", Object(true));
    dict.add("HideMenubar", Object(true));
    dict.add("HideWindowUI", Object(true));
    dict.add("FitWindow", Object(true));
    dict.add("CenterWindow", Object(true));
    dict.add("DisplayDocTitle", Object(true));
    dict.add("PickTrayByPDFSize", Object(true));
    dict.add("NumCopies", Object(3));
    dict.add("Direction", Object(objName, "R2L"));
    dict.add("PrintScaling", Object(objName, "None"));
    dict.add("Duplex", Object(objName, "Simplex"));
    
    ViewerPreferences vp(dict);
    EXPECT_TRUE(vp.getHideToolbar());
    EXPECT_TRUE(vp.getHideMenubar());
    EXPECT_TRUE(vp.getHideWindowUI());
    EXPECT_TRUE(vp.getFitWindow());
    EXPECT_TRUE(vp.getCenterWindow());
    EXPECT_TRUE(vp.getDisplayDocTitle());
    EXPECT_TRUE(vp.getPickTrayByPDFSize());
    EXPECT_EQ(vp.getNumCopies(), 3);
    EXPECT_EQ(vp.getDirection(), ViewerPreferences::directionR2L);
    EXPECT_EQ(vp.getPrintScaling(), ViewerPreferences::printScalingNone);
    EXPECT_EQ(vp.getDuplex(), ViewerPreferences::duplexSimplex);
}

// Test PrintPageRange with valid entries
TEST_F(ViewerPreferencesTest_1355, PrintPageRangeWithEntries_1355) {
    auto xref = (XRef*)nullptr;
    Dict dict(xref);
    
    // PrintPageRange is an array of pairs of integers
    Array *arr = new Array(xref);
    arr->add(Object(1));
    arr->add(Object(5));
    arr->add(Object(10));
    arr->add(Object(15));
    dict.add("PrintPageRange", Object(arr));
    
    ViewerPreferences vp(dict);
    auto range = vp.getPrintPageRange();
    EXPECT_EQ(range.size(), 2u);
    if (range.size() >= 2) {
        EXPECT_EQ(range[0].first, 1);
        EXPECT_EQ(range[0].second, 5);
        EXPECT_EQ(range[1].first, 10);
        EXPECT_EQ(range[1].second, 15);
    }
}

// Test Direction default
TEST_F(ViewerPreferencesTest_1355, DirectionDefault_1355) {
    auto xref = (XRef*)nullptr;
    Dict dict(xref);
    
    ViewerPreferences vp(dict);
    EXPECT_EQ(vp.getDirection(), ViewerPreferences::directionL2R);
}
