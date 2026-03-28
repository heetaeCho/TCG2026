#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "ViewerPreferences.h"
#include "Dict.h"
#include "PDFDoc.h"
#include "GlobalParams.h"

#include <memory>
#include <string>

class ViewerPreferencesTest_1351 : public ::testing::Test {
protected:
    void SetUp() override {
        if (!globalParams) {
            globalParams = std::make_unique<GlobalParams>();
        }
    }

    // Helper to create a Dict with specific entries
    // We need an XRef for Dict, so we use a minimal approach
    std::unique_ptr<Dict> createDict() {
        return std::make_unique<Dict>(static_cast<XRef*>(nullptr));
    }
};

TEST_F(ViewerPreferencesTest_1351, DefaultNonFullScreenPageMode_1351) {
    auto dict = createDict();
    ViewerPreferences vp(*dict);
    EXPECT_EQ(vp.getNonFullScreenPageMode(), ViewerPreferences::nfpmUseNone);
}

TEST_F(ViewerPreferencesTest_1351, DefaultDirection_1351) {
    auto dict = createDict();
    ViewerPreferences vp(*dict);
    EXPECT_EQ(vp.getDirection(), ViewerPreferences::directionL2R);
}

TEST_F(ViewerPreferencesTest_1351, DefaultPrintScaling_1351) {
    auto dict = createDict();
    ViewerPreferences vp(*dict);
    EXPECT_EQ(vp.getPrintScaling(), ViewerPreferences::printScalingAppDefault);
}

TEST_F(ViewerPreferencesTest_1351, DefaultDuplex_1351) {
    auto dict = createDict();
    ViewerPreferences vp(*dict);
    EXPECT_EQ(vp.getDuplex(), ViewerPreferences::duplexNone);
}

TEST_F(ViewerPreferencesTest_1351, DefaultNumCopies_1351) {
    auto dict = createDict();
    ViewerPreferences vp(*dict);
    EXPECT_EQ(vp.getNumCopies(), 1);
}

TEST_F(ViewerPreferencesTest_1351, DefaultHideToolbar_1351) {
    auto dict = createDict();
    ViewerPreferences vp(*dict);
    EXPECT_FALSE(vp.getHideToolbar());
}

TEST_F(ViewerPreferencesTest_1351, DefaultHideMenubar_1351) {
    auto dict = createDict();
    ViewerPreferences vp(*dict);
    EXPECT_FALSE(vp.getHideMenubar());
}

TEST_F(ViewerPreferencesTest_1351, DefaultHideWindowUI_1351) {
    auto dict = createDict();
    ViewerPreferences vp(*dict);
    EXPECT_FALSE(vp.getHideWindowUI());
}

TEST_F(ViewerPreferencesTest_1351, DefaultFitWindow_1351) {
    auto dict = createDict();
    ViewerPreferences vp(*dict);
    EXPECT_FALSE(vp.getFitWindow());
}

TEST_F(ViewerPreferencesTest_1351, DefaultCenterWindow_1351) {
    auto dict = createDict();
    ViewerPreferences vp(*dict);
    EXPECT_FALSE(vp.getCenterWindow());
}

TEST_F(ViewerPreferencesTest_1351, DefaultDisplayDocTitle_1351) {
    auto dict = createDict();
    ViewerPreferences vp(*dict);
    EXPECT_FALSE(vp.getDisplayDocTitle());
}

TEST_F(ViewerPreferencesTest_1351, DefaultPickTrayByPDFSize_1351) {
    auto dict = createDict();
    ViewerPreferences vp(*dict);
    EXPECT_FALSE(vp.getPickTrayByPDFSize());
}

TEST_F(ViewerPreferencesTest_1351, DefaultPrintPageRange_1351) {
    auto dict = createDict();
    ViewerPreferences vp(*dict);
    auto range = vp.getPrintPageRange();
    EXPECT_TRUE(range.empty());
}

TEST_F(ViewerPreferencesTest_1351, HideToolbarTrue_1351) {
    auto dict = createDict();
    dict->add("HideToolbar", Object(true));
    ViewerPreferences vp(*dict);
    EXPECT_TRUE(vp.getHideToolbar());
}

TEST_F(ViewerPreferencesTest_1351, HideMenubarTrue_1351) {
    auto dict = createDict();
    dict->add("HideMenubar", Object(true));
    ViewerPreferences vp(*dict);
    EXPECT_TRUE(vp.getHideMenubar());
}

TEST_F(ViewerPreferencesTest_1351, HideWindowUITrue_1351) {
    auto dict = createDict();
    dict->add("HideWindowUI", Object(true));
    ViewerPreferences vp(*dict);
    EXPECT_TRUE(vp.getHideWindowUI());
}

TEST_F(ViewerPreferencesTest_1351, FitWindowTrue_1351) {
    auto dict = createDict();
    dict->add("FitWindow", Object(true));
    ViewerPreferences vp(*dict);
    EXPECT_TRUE(vp.getFitWindow());
}

TEST_F(ViewerPreferencesTest_1351, CenterWindowTrue_1351) {
    auto dict = createDict();
    dict->add("CenterWindow", Object(true));
    ViewerPreferences vp(*dict);
    EXPECT_TRUE(vp.getCenterWindow());
}

TEST_F(ViewerPreferencesTest_1351, DisplayDocTitleTrue_1351) {
    auto dict = createDict();
    dict->add("DisplayDocTitle", Object(true));
    ViewerPreferences vp(*dict);
    EXPECT_TRUE(vp.getDisplayDocTitle());
}

TEST_F(ViewerPreferencesTest_1351, PickTrayByPDFSizeTrue_1351) {
    auto dict = createDict();
    dict->add("PickTrayByPDFSize", Object(true));
    ViewerPreferences vp(*dict);
    EXPECT_TRUE(vp.getPickTrayByPDFSize());
}

TEST_F(ViewerPreferencesTest_1351, NonFullScreenPageModeUseOutlines_1351) {
    auto dict = createDict();
    dict->add("NonFullScreenPageMode", Object(new GooString("UseOutlines")));
    ViewerPreferences vp(*dict);
    EXPECT_EQ(vp.getNonFullScreenPageMode(), ViewerPreferences::nfpmUseOutlines);
}

TEST_F(ViewerPreferencesTest_1351, NonFullScreenPageModeUseThumbs_1351) {
    auto dict = createDict();
    dict->add("NonFullScreenPageMode", Object(new GooString("UseThumbs")));
    ViewerPreferences vp(*dict);
    EXPECT_EQ(vp.getNonFullScreenPageMode(), ViewerPreferences::nfpmUseThumbs);
}

TEST_F(ViewerPreferencesTest_1351, NonFullScreenPageModeUseOC_1351) {
    auto dict = createDict();
    dict->add("NonFullScreenPageMode", Object(new GooString("UseOC")));
    ViewerPreferences vp(*dict);
    EXPECT_EQ(vp.getNonFullScreenPageMode(), ViewerPreferences::nfpmUseOC);
}

TEST_F(ViewerPreferencesTest_1351, DirectionR2L_1351) {
    auto dict = createDict();
    dict->add("Direction", Object(new GooString("R2L")));
    ViewerPreferences vp(*dict);
    EXPECT_EQ(vp.getDirection(), ViewerPreferences::directionR2L);
}

TEST_F(ViewerPreferencesTest_1351, PrintScalingNone_1351) {
    auto dict = createDict();
    dict->add("PrintScaling", Object(new GooString("None")));
    ViewerPreferences vp(*dict);
    EXPECT_EQ(vp.getPrintScaling(), ViewerPreferences::printScalingNone);
}

TEST_F(ViewerPreferencesTest_1351, DuplexSimplex_1351) {
    auto dict = createDict();
    dict->add("Duplex", Object(new GooString("Simplex")));
    ViewerPreferences vp(*dict);
    EXPECT_EQ(vp.getDuplex(), ViewerPreferences::duplexSimplex);
}

TEST_F(ViewerPreferencesTest_1351, DuplexFlipShortEdge_1351) {
    auto dict = createDict();
    dict->add("Duplex", Object(new GooString("DuplexFlipShortEdge")));
    ViewerPreferences vp(*dict);
    EXPECT_EQ(vp.getDuplex(), ViewerPreferences::duplexFlipShortEdge);
}

TEST_F(ViewerPreferencesTest_1351, DuplexFlipLongEdge_1351) {
    auto dict = createDict();
    dict->add("Duplex", Object(new GooString("DuplexFlipLongEdge")));
    ViewerPreferences vp(*dict);
    EXPECT_EQ(vp.getDuplex(), ViewerPreferences::duplexFlipLongEdge);
}

TEST_F(ViewerPreferencesTest_1351, NumCopiesCustom_1351) {
    auto dict = createDict();
    dict->add("NumCopies", Object(5));
    ViewerPreferences vp(*dict);
    EXPECT_EQ(vp.getNumCopies(), 5);
}

TEST_F(ViewerPreferencesTest_1351, HideToolbarFalse_1351) {
    auto dict = createDict();
    dict->add("HideToolbar", Object(false));
    ViewerPreferences vp(*dict);
    EXPECT_FALSE(vp.getHideToolbar());
}

TEST_F(ViewerPreferencesTest_1351, AllBooleanOptionsSet_1351) {
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

TEST_F(ViewerPreferencesTest_1351, NumCopiesOne_1351) {
    auto dict = createDict();
    dict->add("NumCopies", Object(1));
    ViewerPreferences vp(*dict);
    EXPECT_EQ(vp.getNumCopies(), 1);
}

TEST_F(ViewerPreferencesTest_1351, NonFullScreenPageModeUseNone_1351) {
    auto dict = createDict();
    dict->add("NonFullScreenPageMode", Object(new GooString("UseNone")));
    ViewerPreferences vp(*dict);
    EXPECT_EQ(vp.getNonFullScreenPageMode(), ViewerPreferences::nfpmUseNone);
}

TEST_F(ViewerPreferencesTest_1351, DirectionL2R_1351) {
    auto dict = createDict();
    dict->add("Direction", Object(new GooString("L2R")));
    ViewerPreferences vp(*dict);
    EXPECT_EQ(vp.getDirection(), ViewerPreferences::directionL2R);
}

TEST_F(ViewerPreferencesTest_1351, PrintScalingAppDefault_1351) {
    auto dict = createDict();
    dict->add("PrintScaling", Object(new GooString("AppDefault")));
    ViewerPreferences vp(*dict);
    EXPECT_EQ(vp.getPrintScaling(), ViewerPreferences::printScalingAppDefault);
}
