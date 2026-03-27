#include <gtest/gtest.h>

#include "ViewerPreferences.h"



class ViewerPreferencesTest : public ::testing::Test {

protected:

    ViewerPreferences* viewerPrefs;



    void SetUp() override {

        // Assuming Dict is a valid dictionary that can be constructed without specific values for this test.

        viewerPrefs = new ViewerPreferences(Dict());

    }



    void TearDown() override {

        delete viewerPrefs;

    }

};



TEST_F(ViewerPreferencesTest_1356, GetNumCopies_DefaultValue_1356) {

    EXPECT_EQ(viewerPrefs->getNumCopies(), 1);

}



TEST_F(ViewerPreferencesTest_1356, GetHideToolbar_DefaultValue_1356) {

    EXPECT_FALSE(viewerPrefs->getHideToolbar());

}



TEST_F(ViewerPreferencesTest_1356, GetHideMenubar_DefaultValue_1356) {

    EXPECT_FALSE(viewerPrefs->getHideMenubar());

}



TEST_F(ViewerPreferencesTest_1356, GetHideWindowUI_DefaultValue_1356) {

    EXPECT_FALSE(viewerPrefs->getHideWindowUI());

}



TEST_F(ViewerPreferencesTest_1356, GetFitWindow_DefaultValue_1356) {

    EXPECT_FALSE(viewerPrefs->getFitWindow());

}



TEST_F(ViewerPreferencesTest_1356, GetCenterWindow_DefaultValue_1356) {

    EXPECT_FALSE(viewerPrefs->getCenterWindow());

}



TEST_F(ViewerPreferencesTest_1356, GetDisplayDocTitle_DefaultValue_1356) {

    EXPECT_FALSE(viewerPrefs->getDisplayDocTitle());

}



TEST_F(ViewerPreferencesTest_1356, GetNonFullScreenPageMode_DefaultValue_1356) {

    EXPECT_EQ(viewerPrefs->getNonFullScreenPageMode(), nfpmUseNone);

}



TEST_F(ViewerPreferencesTest_1356, GetDirection_DefaultValue_1356) {

    EXPECT_EQ(viewerPrefs->getDirection(), directionL2R);

}



TEST_F(ViewerPreferencesTest_1356, GetPrintScaling_DefaultValue_1356) {

    EXPECT_EQ(viewerPrefs->getPrintScaling(), printScalingAppDefault);

}



TEST_F(ViewerPreferencesTest_1356, GetDuplex_DefaultValue_1356) {

    EXPECT_EQ(viewerPrefs->getDuplex(), duplexNone);

}



TEST_F(ViewerPreferencesTest_1356, GetPickTrayByPDFSize_DefaultValue_1356) {

    EXPECT_FALSE(viewerPrefs->getPickTrayByPDFSize());

}



TEST_F(ViewerPreferencesTest_1356, GetPrintPageRange_DefaultValue_1356) {

    EXPECT_TRUE(viewerPrefs->getPrintPageRange().empty());

}
