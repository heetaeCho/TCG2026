#include <gtest/gtest.h>

#include "TestProjects/poppler/poppler/ViewerPreferences.h"



class ViewerPreferencesTest : public ::testing::Test {

protected:

    Dict prefDict; // Assuming Dict is a valid class used in the constructor

    ViewerPreferences* viewerPrefs;



    void SetUp() override {

        viewerPrefs = new ViewerPreferences(prefDict);

    }



    void TearDown() override {

        delete viewerPrefs;

    }

};



TEST_F(ViewerPreferencesTest_1351, GetNonFullScreenPageMode_DefaultValue_1351) {

    EXPECT_EQ(viewerPrefs->getNonFullScreenPageMode(), nfpmUseNone);

}



TEST_F(ViewerPreferencesTest_1351, GetHideToolbar_DefaultValue_1351) {

    EXPECT_FALSE(viewerPrefs->getHideToolbar());

}



TEST_F(ViewerPreferencesTest_1351, GetHideMenubar_DefaultValue_1351) {

    EXPECT_FALSE(viewerPrefs->getHideMenubar());

}



TEST_F(ViewerPreferencesTest_1351, GetHideWindowUI_DefaultValue_1351) {

    EXPECT_FALSE(viewerPrefs->getHideWindowUI());

}



TEST_F(ViewerPreferencesTest_1351, GetFitWindow_DefaultValue_1351) {

    EXPECT_FALSE(viewerPrefs->getFitWindow());

}



TEST_F(ViewerPreferencesTest_1351, GetCenterWindow_DefaultValue_1351) {

    EXPECT_FALSE(viewerPrefs->getCenterWindow());

}



TEST_F(ViewerPreferencesTest_1351, GetDisplayDocTitle_DefaultValue_1351) {

    EXPECT_FALSE(viewerPrefs->getDisplayDocTitle());

}



TEST_F(ViewerPreferencesTest_1351, GetDirection_DefaultValue_1351) {

    EXPECT_EQ(viewerPrefs->getDirection(), directionL2R);

}



TEST_F(ViewerPreferencesTest_1351, GetPrintScaling_DefaultValue_1351) {

    EXPECT_EQ(viewerPrefs->getPrintScaling(), printScalingAppDefault);

}



TEST_F(ViewerPreferencesTest_1351, GetDuplex_DefaultValue_1351) {

    EXPECT_EQ(viewerPrefs->getDuplex(), duplexNone);

}



TEST_F(ViewerPreferencesTest_1351, GetPickTrayByPDFSize_DefaultValue_1351) {

    EXPECT_FALSE(viewerPrefs->getPickTrayByPDFSize());

}



TEST_F(ViewerPreferencesTest_1351, GetNumCopies_DefaultValue_1351) {

    EXPECT_EQ(viewerPrefs->getNumCopies(), 1);

}



TEST_F(ViewerPreferencesTest_1351, GetPrintPageRange_DefaultValue_1351) {

    EXPECT_TRUE(viewerPrefs->getPrintPageRange().empty());

}
