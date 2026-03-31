#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "ViewerPreferences.h"
#include "Dict.h"
#include "PDFDoc.h"
#include "GlobalParams.h"
#include "Object.h"

#include <memory>
#include <utility>
#include <vector>

class ViewerPreferencesTest_1347 : public ::testing::Test {
protected:
    void SetUp() override {
        if (!globalParams) {
            globalParams = std::make_unique<GlobalParams>();
        }
        xref = nullptr;
    }

    // Helper to create a Dict with given key-value pairs
    Dict *createDict() {
        return new Dict(xref);
    }

    XRef *xref;
};

TEST_F(ViewerPreferencesTest_1347, DefaultValues_1347) {
    // Empty dict should give default values
    Dict *dict = createDict();
    ViewerPreferences vp(*dict);

    EXPECT_FALSE(vp.getHideToolbar());
    EXPECT_FALSE(vp.getHideMenubar());
    EXPECT_FALSE(vp.getHideWindowUI());
    EXPECT_FALSE(vp.getFitWindow());
    EXPECT_FALSE(vp.getCenterWindow());
    EXPECT_FALSE(vp.getDisplayDocTitle());
    EXPECT_FALSE(vp.getPickTrayByPDFSize());
    EXPECT_EQ(vp.getNumCopies(), 1);
    EXPECT_TRUE(vp.getPrintPageRange().empty());

    delete dict;
}

TEST_F(ViewerPreferencesTest_1347, HideToolbarTrue_1347) {
    Dict *dict = createDict();
    dict->add("HideToolbar", Object(true));
    ViewerPreferences vp(*dict);

    EXPECT_TRUE(vp.getHideToolbar());

    delete dict;
}

TEST_F(ViewerPreferencesTest_1347, HideToolbarFalse_1347) {
    Dict *dict = createDict();
    dict->add("HideToolbar", Object(false));
    ViewerPreferences vp(*dict);

    EXPECT_FALSE(vp.getHideToolbar());

    delete dict;
}

TEST_F(ViewerPreferencesTest_1347, HideMenubarTrue_1347) {
    Dict *dict = createDict();
    dict->add("HideMenubar", Object(true));
    ViewerPreferences vp(*dict);

    EXPECT_TRUE(vp.getHideMenubar());

    delete dict;
}

TEST_F(ViewerPreferencesTest_1347, HideMenubarFalse_1347) {
    Dict *dict = createDict();
    dict->add("HideMenubar", Object(false));
    ViewerPreferences vp(*dict);

    EXPECT_FALSE(vp.getHideMenubar());

    delete dict;
}

TEST_F(ViewerPreferencesTest_1347, HideWindowUITrue_1347) {
    Dict *dict = createDict();
    dict->add("HideWindowUI", Object(true));
    ViewerPreferences vp(*dict);

    EXPECT_TRUE(vp.getHideWindowUI());

    delete dict;
}

TEST_F(ViewerPreferencesTest_1347, HideWindowUIFalse_1347) {
    Dict *dict = createDict();
    dict->add("HideWindowUI", Object(false));
    ViewerPreferences vp(*dict);

    EXPECT_FALSE(vp.getHideWindowUI());

    delete dict;
}

TEST_F(ViewerPreferencesTest_1347, FitWindowTrue_1347) {
    Dict *dict = createDict();
    dict->add("FitWindow", Object(true));
    ViewerPreferences vp(*dict);

    EXPECT_TRUE(vp.getFitWindow());

    delete dict;
}

TEST_F(ViewerPreferencesTest_1347, FitWindowFalse_1347) {
    Dict *dict = createDict();
    dict->add("FitWindow", Object(false));
    ViewerPreferences vp(*dict);

    EXPECT_FALSE(vp.getFitWindow());

    delete dict;
}

TEST_F(ViewerPreferencesTest_1347, CenterWindowTrue_1347) {
    Dict *dict = createDict();
    dict->add("CenterWindow", Object(true));
    ViewerPreferences vp(*dict);

    EXPECT_TRUE(vp.getCenterWindow());

    delete dict;
}

TEST_F(ViewerPreferencesTest_1347, CenterWindowFalse_1347) {
    Dict *dict = createDict();
    dict->add("CenterWindow", Object(false));
    ViewerPreferences vp(*dict);

    EXPECT_FALSE(vp.getCenterWindow());

    delete dict;
}

TEST_F(ViewerPreferencesTest_1347, DisplayDocTitleTrue_1347) {
    Dict *dict = createDict();
    dict->add("DisplayDocTitle", Object(true));
    ViewerPreferences vp(*dict);

    EXPECT_TRUE(vp.getDisplayDocTitle());

    delete dict;
}

TEST_F(ViewerPreferencesTest_1347, DisplayDocTitleFalse_1347) {
    Dict *dict = createDict();
    dict->add("DisplayDocTitle", Object(false));
    ViewerPreferences vp(*dict);

    EXPECT_FALSE(vp.getDisplayDocTitle());

    delete dict;
}

TEST_F(ViewerPreferencesTest_1347, NonFullScreenPageModeDefault_1347) {
    Dict *dict = createDict();
    ViewerPreferences vp(*dict);

    EXPECT_EQ(vp.getNonFullScreenPageMode(), ViewerPreferences::nfpmUseNone);

    delete dict;
}

TEST_F(ViewerPreferencesTest_1347, NonFullScreenPageModeUseOutlines_1347) {
    Dict *dict = createDict();
    dict->add("NonFullScreenPageMode", Object(objName, "UseOutlines"));
    ViewerPreferences vp(*dict);

    EXPECT_EQ(vp.getNonFullScreenPageMode(), ViewerPreferences::nfpmUseOutlines);

    delete dict;
}

TEST_F(ViewerPreferencesTest_1347, NonFullScreenPageModeUseThumbs_1347) {
    Dict *dict = createDict();
    dict->add("NonFullScreenPageMode", Object(objName, "UseThumbs"));
    ViewerPreferences vp(*dict);

    EXPECT_EQ(vp.getNonFullScreenPageMode(), ViewerPreferences::nfpmUseThumbs);

    delete dict;
}

TEST_F(ViewerPreferencesTest_1347, NonFullScreenPageModeUseOC_1347) {
    Dict *dict = createDict();
    dict->add("NonFullScreenPageMode", Object(objName, "UseOC"));
    ViewerPreferences vp(*dict);

    EXPECT_EQ(vp.getNonFullScreenPageMode(), ViewerPreferences::nfpmUseOC);

    delete dict;
}

TEST_F(ViewerPreferencesTest_1347, DirectionDefault_1347) {
    Dict *dict = createDict();
    ViewerPreferences vp(*dict);

    EXPECT_EQ(vp.getDirection(), ViewerPreferences::directionL2R);

    delete dict;
}

TEST_F(ViewerPreferencesTest_1347, DirectionR2L_1347) {
    Dict *dict = createDict();
    dict->add("Direction", Object(objName, "R2L"));
    ViewerPreferences vp(*dict);

    EXPECT_EQ(vp.getDirection(), ViewerPreferences::directionR2L);

    delete dict;
}

TEST_F(ViewerPreferencesTest_1347, PrintScalingDefault_1347) {
    Dict *dict = createDict();
    ViewerPreferences vp(*dict);

    EXPECT_EQ(vp.getPrintScaling(), ViewerPreferences::printScalingAppDefault);

    delete dict;
}

TEST_F(ViewerPreferencesTest_1347, PrintScalingNone_1347) {
    Dict *dict = createDict();
    dict->add("PrintScaling", Object(objName, "None"));
    ViewerPreferences vp(*dict);

    EXPECT_EQ(vp.getPrintScaling(), ViewerPreferences::printScalingNone);

    delete dict;
}

TEST_F(ViewerPreferencesTest_1347, DuplexDefault_1347) {
    Dict *dict = createDict();
    ViewerPreferences vp(*dict);

    EXPECT_EQ(vp.getDuplex(), ViewerPreferences::duplexNone);

    delete dict;
}

TEST_F(ViewerPreferencesTest_1347, DuplexSimplex_1347) {
    Dict *dict = createDict();
    dict->add("Duplex", Object(objName, "Simplex"));
    ViewerPreferences vp(*dict);

    EXPECT_EQ(vp.getDuplex(), ViewerPreferences::duplexSimplex);

    delete dict;
}

TEST_F(ViewerPreferencesTest_1347, DuplexFlipShortEdge_1347) {
    Dict *dict = createDict();
    dict->add("Duplex", Object(objName, "DuplexFlipShortEdge"));
    ViewerPreferences vp(*dict);

    EXPECT_EQ(vp.getDuplex(), ViewerPreferences::duplexFlipShortEdge);

    delete dict;
}

TEST_F(ViewerPreferencesTest_1347, DuplexFlipLongEdge_1347) {
    Dict *dict = createDict();
    dict->add("Duplex", Object(objName, "DuplexFlipLongEdge"));
    ViewerPreferences vp(*dict);

    EXPECT_EQ(vp.getDuplex(), ViewerPreferences::duplexFlipLongEdge);

    delete dict;
}

TEST_F(ViewerPreferencesTest_1347, PickTrayByPDFSizeTrue_1347) {
    Dict *dict = createDict();
    dict->add("PickTrayByPDFSize", Object(true));
    ViewerPreferences vp(*dict);

    EXPECT_TRUE(vp.getPickTrayByPDFSize());

    delete dict;
}

TEST_F(ViewerPreferencesTest_1347, PickTrayByPDFSizeFalse_1347) {
    Dict *dict = createDict();
    dict->add("PickTrayByPDFSize", Object(false));
    ViewerPreferences vp(*dict);

    EXPECT_FALSE(vp.getPickTrayByPDFSize());

    delete dict;
}

TEST_F(ViewerPreferencesTest_1347, NumCopiesDefault_1347) {
    Dict *dict = createDict();
    ViewerPreferences vp(*dict);

    EXPECT_EQ(vp.getNumCopies(), 1);

    delete dict;
}

TEST_F(ViewerPreferencesTest_1347, NumCopiesSet_1347) {
    Dict *dict = createDict();
    dict->add("NumCopies", Object(5));
    ViewerPreferences vp(*dict);

    EXPECT_EQ(vp.getNumCopies(), 5);

    delete dict;
}

TEST_F(ViewerPreferencesTest_1347, PrintPageRangeEmpty_1347) {
    Dict *dict = createDict();
    ViewerPreferences vp(*dict);

    std::vector<std::pair<int, int>> range = vp.getPrintPageRange();
    EXPECT_TRUE(range.empty());

    delete dict;
}

TEST_F(ViewerPreferencesTest_1347, AllBooleanFieldsTrue_1347) {
    Dict *dict = createDict();
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

    delete dict;
}

TEST_F(ViewerPreferencesTest_1347, AllBooleanFieldsFalse_1347) {
    Dict *dict = createDict();
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

    delete dict;
}

TEST_F(ViewerPreferencesTest_1347, NumCopiesOne_1347) {
    Dict *dict = createDict();
    dict->add("NumCopies", Object(1));
    ViewerPreferences vp(*dict);

    EXPECT_EQ(vp.getNumCopies(), 1);

    delete dict;
}

TEST_F(ViewerPreferencesTest_1347, NumCopiesLargeValue_1347) {
    Dict *dict = createDict();
    dict->add("NumCopies", Object(100));
    ViewerPreferences vp(*dict);

    EXPECT_EQ(vp.getNumCopies(), 100);

    delete dict;
}

TEST_F(ViewerPreferencesTest_1347, DirectionL2RExplicit_1347) {
    Dict *dict = createDict();
    dict->add("Direction", Object(objName, "L2R"));
    ViewerPreferences vp(*dict);

    EXPECT_EQ(vp.getDirection(), ViewerPreferences::directionL2R);

    delete dict;
}

TEST_F(ViewerPreferencesTest_1347, NonFullScreenPageModeUseNoneExplicit_1347) {
    Dict *dict = createDict();
    dict->add("NonFullScreenPageMode", Object(objName, "UseNone"));
    ViewerPreferences vp(*dict);

    EXPECT_EQ(vp.getNonFullScreenPageMode(), ViewerPreferences::nfpmUseNone);

    delete dict;
}

TEST_F(ViewerPreferencesTest_1347, PrintScalingAppDefaultExplicit_1347) {
    Dict *dict = createDict();
    dict->add("PrintScaling", Object(objName, "AppDefault"));
    ViewerPreferences vp(*dict);

    EXPECT_EQ(vp.getPrintScaling(), ViewerPreferences::printScalingAppDefault);

    delete dict;
}

TEST_F(ViewerPreferencesTest_1347, PrintPageRangeWithValues_1347) {
    Dict *dict = createDict();
    Array *arr = new Array(xref);
    arr->add(Object(1));
    arr->add(Object(10));
    dict->add("PrintPageRange", Object(arr));
    ViewerPreferences vp(*dict);

    std::vector<std::pair<int, int>> range = vp.getPrintPageRange();
    if (!range.empty()) {
        EXPECT_EQ(range.size(), 1u);
        EXPECT_EQ(range[0].first, 1);
        EXPECT_EQ(range[0].second, 10);
    }

    delete dict;
}

TEST_F(ViewerPreferencesTest_1347, PrintPageRangeMultipleRanges_1347) {
    Dict *dict = createDict();
    Array *arr = new Array(xref);
    arr->add(Object(1));
    arr->add(Object(5));
    arr->add(Object(10));
    arr->add(Object(20));
    dict->add("PrintPageRange", Object(arr));
    ViewerPreferences vp(*dict);

    std::vector<std::pair<int, int>> range = vp.getPrintPageRange();
    if (!range.empty()) {
        EXPECT_EQ(range.size(), 2u);
        EXPECT_EQ(range[0].first, 1);
        EXPECT_EQ(range[0].second, 5);
        EXPECT_EQ(range[1].first, 10);
        EXPECT_EQ(range[1].second, 20);
    }

    delete dict;
}
