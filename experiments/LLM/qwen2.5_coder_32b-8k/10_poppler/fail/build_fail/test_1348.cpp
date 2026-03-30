#include <gtest/gtest.h>

#include "TestProjects/poppler/poppler/ViewerPreferences.h"



class ViewerPreferencesTest_1348 : public ::testing::Test {

protected:

    ViewerPreferences* viewerPrefs;



    void SetUp() override {

        // Assuming Dict is a placeholder and can be default constructed for testing

        viewerPrefs = new ViewerPreferences(Dict());

    }



    void TearDown() override {

        delete viewerPrefs;

    }

};



TEST_F(ViewerPreferencesTest_1348, GetFitWindow_DefaultValue_False_1348) {

    EXPECT_FALSE(viewerPrefs->getFitWindow());

}



TEST_F(ViewerPreferencesTest_1348, GetHideToolbar_DefaultValue_False_1348) {

    EXPECT_FALSE(viewerPrefs->getHideToolbar());

}



TEST_F(ViewerPreferencesTest_1348, GetHideMenubar_DefaultValue_False_1348) {

    EXPECT_FALSE(viewerPrefs->getHideMenubar());

}



TEST_F(ViewerPreferencesTest_1348, GetHideWindowUI_DefaultValue_False_1348) {

    EXPECT_FALSE(viewerPrefs->getHideWindowUI());

}



TEST_F(ViewerPreferencesTest_1348, GetCenterWindow_DefaultValue_False_1348) {

    EXPECT_FALSE(viewerPrefs->getCenterWindow());

}



TEST_F(ViewerPreferencesTest_1348, GetDisplayDocTitle_DefaultValue_True_1348) {

    EXPECT_TRUE(viewerPrefs->getDisplayDocTitle());

}



TEST_F(ViewerPreferencesTest_1348, GetNonFullScreenPageMode_DefaultValue_UseNone_1348) {

    EXPECT_EQ(viewerPrefs->getNonFullScreenPageMode(), nfpmUseNone);

}



TEST_F(ViewerPreferencesTest_1348, GetDirection_DefaultValue_L2R_1348) {

    EXPECT_EQ(viewerPrefs->getDirection(), directionL2R);

}



TEST_F(ViewerPreferencesTest_1348, GetPrintScaling_DefaultValue_AppDefault_1348) {

    EXPECT_EQ(viewerPrefs->getPrintScaling(), printScalingAppDefault);

}



TEST_F(ViewerPreferencesTest_1348, GetDuplex_DefaultValue_None_1348) {

    EXPECT_EQ(viewerPrefs->getDuplex(), duplexNone);

}



TEST_F(ViewerPreferencesTest_1348, GetPickTrayByPDFSize_DefaultValue_False_1348) {

    EXPECT_FALSE(viewerPrefs->getPickTrayByPDFSize());

}



TEST_F(ViewerPreferencesTest_1348, GetNumCopies_DefaultValue_One_1348) {

    EXPECT_EQ(viewerPrefs->getNumCopies(), 1);

}



TEST_F(ViewerPreferencesTest_1348, GetPrintPageRange_DefaultValue_Empty_1348) {

    EXPECT_TRUE(viewerPrefs->getPrintPageRange().empty());

}
