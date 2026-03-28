#include <gtest/gtest.h>

#include "ViewerPreferences.h"



class ViewerPreferencesTest_1346 : public ::testing::Test {

protected:

    ViewerPreferences* viewerPrefs;



    void SetUp() override {

        // Assuming Dict is a class that can be default constructed for testing purposes.

        // In real scenarios, you might need to provide a valid Dict object.

        viewerPrefs = new ViewerPreferences(Dict());

    }



    void TearDown() override {

        delete viewerPrefs;

    }

};



TEST_F(ViewerPreferencesTest_1346, GetHideMenubar_DefaultValue_1346) {

    EXPECT_FALSE(viewerPrefs->getHideMenubar());

}



TEST_F(ViewerPreferencesTest_1346, GetHideToolbar_DefaultValue_1346) {

    EXPECT_FALSE(viewerPrefs->getHideToolbar());

}



TEST_F(ViewerPreferencesTest_1346, GetHideWindowUI_DefaultValue_1346) {

    EXPECT_FALSE(viewerPrefs->getHideWindowUI());

}



TEST_F(ViewerPreferencesTest_1346, GetFitWindow_DefaultValue_1346) {

    EXPECT_FALSE(viewerPrefs->getFitWindow());

}



TEST_F(ViewerPreferencesTest_1346, GetCenterWindow_DefaultValue_1346) {

    EXPECT_FALSE(viewerPrefs->getCenterWindow());

}



TEST_F(ViewerPreferencesTest_1346, GetDisplayDocTitle_DefaultValue_1346) {

    EXPECT_FALSE(viewerPrefs->getDisplayDocTitle());

}



TEST_F(ViewerPreferencesTest_1346, GetNonFullScreenPageMode_DefaultValue_1346) {

    EXPECT_EQ(nfpmUseNone, viewerPrefs->getNonFullScreenPageMode());

}



TEST_F(ViewerPreferencesTest_1346, GetDirection_DefaultValue_1346) {

    EXPECT_EQ(directionL2R, viewerPrefs->getDirection());

}



TEST_F(ViewerPreferencesTest_1346, GetPrintScaling_DefaultValue_1346) {

    EXPECT_EQ(printScalingAppDefault, viewerPrefs->getPrintScaling());

}



TEST_F(ViewerPreferencesTest_1346, GetDuplex_DefaultValue_1346) {

    EXPECT_EQ(duplexNone, viewerPrefs->getDuplex());

}



TEST_F(ViewerPreferencesTest_1346, GetPickTrayByPDFSize_DefaultValue_1346) {

    EXPECT_FALSE(viewerPrefs->getPickTrayByPDFSize());

}



TEST_F(ViewerPreferencesTest_1346, GetNumCopies_DefaultValue_1346) {

    EXPECT_EQ(1, viewerPrefs->getNumCopies());

}



TEST_F(ViewerPreferencesTest_1346, GetPrintPageRange_DefaultValue_1346) {

    EXPECT_TRUE(viewerPrefs->getPrintPageRange().empty());

}
