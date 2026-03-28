#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "ViewerPreferences.h"
#include "Dict.h"
#include "PDFDoc.h"
#include "GlobalParams.h"

#include <memory>
#include <string>
#include <utility>
#include <vector>

class ViewerPreferencesTest_1350 : public ::testing::Test {
protected:
    void SetUp() override {
        if (!globalParams) {
            globalParams = std::make_unique<GlobalParams>();
        }
    }

    // Helper to create a Dict with specific viewer preference entries
    std::unique_ptr<Dict> createEmptyDict() {
        // We need an XRef-less dict for testing
        auto dict = std::make_unique<Dict>(nullptr);
        return dict;
    }
};

TEST_F(ViewerPreferencesTest_1350, DefaultValuesWithEmptyDict_1350) {
    Dict dict(nullptr);
    ViewerPreferences vp(dict);
    
    // With an empty dict, defaults should be returned
    EXPECT_FALSE(vp.getHideToolbar());
    EXPECT_FALSE(vp.getHideMenubar());
    EXPECT_FALSE(vp.getHideWindowUI());
    EXPECT_FALSE(vp.getFitWindow());
    EXPECT_FALSE(vp.getCenterWindow());
    EXPECT_FALSE(vp.getDisplayDocTitle());
}

TEST_F(ViewerPreferencesTest_1350, HideToolbarTrue_1350) {
    Dict dict(nullptr);
    dict.add("HideToolbar", Object(true));
    ViewerPreferences vp(dict);
    
    EXPECT_TRUE(vp.getHideToolbar());
}

TEST_F(ViewerPreferencesTest_1350, HideToolbarFalse_1350) {
    Dict dict(nullptr);
    dict.add("HideToolbar", Object(false));
    ViewerPreferences vp(dict);
    
    EXPECT_FALSE(vp.getHideToolbar());
}

TEST_F(ViewerPreferencesTest_1350, HideMenubarTrue_1350) {
    Dict dict(nullptr);
    dict.add("HideMenubar", Object(true));
    ViewerPreferences vp(dict);
    
    EXPECT_TRUE(vp.getHideMenubar());
}

TEST_F(ViewerPreferencesTest_1350, HideMenubarFalse_1350) {
    Dict dict(nullptr);
    dict.add("HideMenubar", Object(false));
    ViewerPreferences vp(dict);
    
    EXPECT_FALSE(vp.getHideMenubar());
}

TEST_F(ViewerPreferencesTest_1350, HideWindowUITrue_1350) {
    Dict dict(nullptr);
    dict.add("HideWindowUI", Object(true));
    ViewerPreferences vp(dict);
    
    EXPECT_TRUE(vp.getHideWindowUI());
}

TEST_F(ViewerPreferencesTest_1350, HideWindowUIFalse_1350) {
    Dict dict(nullptr);
    dict.add("HideWindowUI", Object(false));
    ViewerPreferences vp(dict);
    
    EXPECT_FALSE(vp.getHideWindowUI());
}

TEST_F(ViewerPreferencesTest_1350, FitWindowTrue_1350) {
    Dict dict(nullptr);
    dict.add("FitWindow", Object(true));
    ViewerPreferences vp(dict);
    
    EXPECT_TRUE(vp.getFitWindow());
}

TEST_F(ViewerPreferencesTest_1350, FitWindowFalse_1350) {
    Dict dict(nullptr);
    dict.add("FitWindow", Object(false));
    ViewerPreferences vp(dict);
    
    EXPECT_FALSE(vp.getFitWindow());
}

TEST_F(ViewerPreferencesTest_1350, CenterWindowTrue_1350) {
    Dict dict(nullptr);
    dict.add("CenterWindow", Object(true));
    ViewerPreferences vp(dict);
    
    EXPECT_TRUE(vp.getCenterWindow());
}

TEST_F(ViewerPreferencesTest_1350, CenterWindowFalse_1350) {
    Dict dict(nullptr);
    dict.add("CenterWindow", Object(false));
    ViewerPreferences vp(dict);
    
    EXPECT_FALSE(vp.getCenterWindow());
}

TEST_F(ViewerPreferencesTest_1350, DisplayDocTitleTrue_1350) {
    Dict dict(nullptr);
    dict.add("DisplayDocTitle", Object(true));
    ViewerPreferences vp(dict);
    
    EXPECT_TRUE(vp.getDisplayDocTitle());
}

TEST_F(ViewerPreferencesTest_1350, DisplayDocTitleFalse_1350) {
    Dict dict(nullptr);
    dict.add("DisplayDocTitle", Object(false));
    ViewerPreferences vp(dict);
    
    EXPECT_FALSE(vp.getDisplayDocTitle());
}

TEST_F(ViewerPreferencesTest_1350, NonFullScreenPageModeDefault_1350) {
    Dict dict(nullptr);
    ViewerPreferences vp(dict);
    
    EXPECT_EQ(vp.getNonFullScreenPageMode(), ViewerPreferences::nfpmUseNone);
}

TEST_F(ViewerPreferencesTest_1350, NonFullScreenPageModeUseOutlines_1350) {
    Dict dict(nullptr);
    dict.add("NonFullScreenPageMode", Object(objName, "UseOutlines"));
    ViewerPreferences vp(dict);
    
    EXPECT_EQ(vp.getNonFullScreenPageMode(), ViewerPreferences::nfpmUseOutlines);
}

TEST_F(ViewerPreferencesTest_1350, NonFullScreenPageModeUseThumbs_1350) {
    Dict dict(nullptr);
    dict.add("NonFullScreenPageMode", Object(objName, "UseThumbs"));
    ViewerPreferences vp(dict);
    
    EXPECT_EQ(vp.getNonFullScreenPageMode(), ViewerPreferences::nfpmUseThumbs);
}

TEST_F(ViewerPreferencesTest_1350, NonFullScreenPageModeUseOC_1350) {
    Dict dict(nullptr);
    dict.add("NonFullScreenPageMode", Object(objName, "UseOC"));
    ViewerPreferences vp(dict);
    
    EXPECT_EQ(vp.getNonFullScreenPageMode(), ViewerPreferences::nfpmUseOC);
}

TEST_F(ViewerPreferencesTest_1350, DirectionDefault_1350) {
    Dict dict(nullptr);
    ViewerPreferences vp(dict);
    
    EXPECT_EQ(vp.getDirection(), ViewerPreferences::directionL2R);
}

TEST_F(ViewerPreferencesTest_1350, DirectionR2L_1350) {
    Dict dict(nullptr);
    dict.add("Direction", Object(objName, "R2L"));
    ViewerPreferences vp(dict);
    
    EXPECT_EQ(vp.getDirection(), ViewerPreferences::directionR2L);
}

TEST_F(ViewerPreferencesTest_1350, DirectionL2R_1350) {
    Dict dict(nullptr);
    dict.add("Direction", Object(objName, "L2R"));
    ViewerPreferences vp(dict);
    
    EXPECT_EQ(vp.getDirection(), ViewerPreferences::directionL2R);
}

TEST_F(ViewerPreferencesTest_1350, PrintScalingDefault_1350) {
    Dict dict(nullptr);
    ViewerPreferences vp(dict);
    
    EXPECT_EQ(vp.getPrintScaling(), ViewerPreferences::printScalingAppDefault);
}

TEST_F(ViewerPreferencesTest_1350, PrintScalingNone_1350) {
    Dict dict(nullptr);
    dict.add("PrintScaling", Object(objName, "None"));
    ViewerPreferences vp(dict);
    
    EXPECT_EQ(vp.getPrintScaling(), ViewerPreferences::printScalingNone);
}

TEST_F(ViewerPreferencesTest_1350, DuplexDefault_1350) {
    Dict dict(nullptr);
    ViewerPreferences vp(dict);
    
    EXPECT_EQ(vp.getDuplex(), ViewerPreferences::duplexNone);
}

TEST_F(ViewerPreferencesTest_1350, DuplexFlipShortEdge_1350) {
    Dict dict(nullptr);
    dict.add("Duplex", Object(objName, "DuplexFlipShortEdge"));
    ViewerPreferences vp(dict);
    
    EXPECT_EQ(vp.getDuplex(), ViewerPreferences::duplexFlipShortEdge);
}

TEST_F(ViewerPreferencesTest_1350, DuplexFlipLongEdge_1350) {
    Dict dict(nullptr);
    dict.add("Duplex", Object(objName, "DuplexFlipLongEdge"));
    ViewerPreferences vp(dict);
    
    EXPECT_EQ(vp.getDuplex(), ViewerPreferences::duplexFlipLongEdge);
}

TEST_F(ViewerPreferencesTest_1350, DuplexSimplex_1350) {
    Dict dict(nullptr);
    dict.add("Duplex", Object(objName, "Simplex"));
    ViewerPreferences vp(dict);
    
    EXPECT_EQ(vp.getDuplex(), ViewerPreferences::duplexSimplex);
}

TEST_F(ViewerPreferencesTest_1350, PickTrayByPDFSizeDefault_1350) {
    Dict dict(nullptr);
    ViewerPreferences vp(dict);
    
    EXPECT_FALSE(vp.getPickTrayByPDFSize());
}

TEST_F(ViewerPreferencesTest_1350, PickTrayByPDFSizeTrue_1350) {
    Dict dict(nullptr);
    dict.add("PickTrayByPDFSize", Object(true));
    ViewerPreferences vp(dict);
    
    EXPECT_TRUE(vp.getPickTrayByPDFSize());
}

TEST_F(ViewerPreferencesTest_1350, NumCopiesDefault_1350) {
    Dict dict(nullptr);
    ViewerPreferences vp(dict);
    
    EXPECT_EQ(vp.getNumCopies(), 1);
}

TEST_F(ViewerPreferencesTest_1350, NumCopiesSet_1350) {
    Dict dict(nullptr);
    dict.add("NumCopies", Object(5));
    ViewerPreferences vp(dict);
    
    EXPECT_EQ(vp.getNumCopies(), 5);
}

TEST_F(ViewerPreferencesTest_1350, PrintPageRangeDefaultEmpty_1350) {
    Dict dict(nullptr);
    ViewerPreferences vp(dict);
    
    auto range = vp.getPrintPageRange();
    EXPECT_TRUE(range.empty());
}

TEST_F(ViewerPreferencesTest_1350, AllBooleanFieldsTrue_1350) {
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

TEST_F(ViewerPreferencesTest_1350, AllBooleanFieldsFalse_1350) {
    Dict dict(nullptr);
    dict.add("HideToolbar", Object(false));
    dict.add("HideMenubar", Object(false));
    dict.add("HideWindowUI", Object(false));
    dict.add("FitWindow", Object(false));
    dict.add("CenterWindow", Object(false));
    dict.add("DisplayDocTitle", Object(false));
    dict.add("PickTrayByPDFSize", Object(false));
    ViewerPreferences vp(dict);
    
    EXPECT_FALSE(vp.getHideToolbar());
    EXPECT_FALSE(vp.getHideMenubar());
    EXPECT_FALSE(vp.getHideWindowUI());
    EXPECT_FALSE(vp.getFitWindow());
    EXPECT_FALSE(vp.getCenterWindow());
    EXPECT_FALSE(vp.getDisplayDocTitle());
    EXPECT_FALSE(vp.getPickTrayByPDFSize());
}

TEST_F(ViewerPreferencesTest_1350, NumCopiesOne_1350) {
    Dict dict(nullptr);
    dict.add("NumCopies", Object(1));
    ViewerPreferences vp(dict);
    
    EXPECT_EQ(vp.getNumCopies(), 1);
}

TEST_F(ViewerPreferencesTest_1350, NumCopiesLargeValue_1350) {
    Dict dict(nullptr);
    dict.add("NumCopies", Object(100));
    ViewerPreferences vp(dict);
    
    EXPECT_EQ(vp.getNumCopies(), 100);
}

TEST_F(ViewerPreferencesTest_1350, NonFullScreenPageModeUseNone_1350) {
    Dict dict(nullptr);
    dict.add("NonFullScreenPageMode", Object(objName, "UseNone"));
    ViewerPreferences vp(dict);
    
    EXPECT_EQ(vp.getNonFullScreenPageMode(), ViewerPreferences::nfpmUseNone);
}

TEST_F(ViewerPreferencesTest_1350, PrintScalingAppDefault_1350) {
    Dict dict(nullptr);
    dict.add("PrintScaling", Object(objName, "AppDefault"));
    ViewerPreferences vp(dict);
    
    EXPECT_EQ(vp.getPrintScaling(), ViewerPreferences::printScalingAppDefault);
}
