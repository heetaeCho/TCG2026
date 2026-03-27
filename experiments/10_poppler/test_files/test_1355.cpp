#include <gtest/gtest.h>

#include "TestProjects/poppler/poppler/ViewerPreferences.h"



class ViewerPreferencesTest : public ::testing::Test {

protected:

    ViewerPreferences* viewerPrefs;



    void SetUp() override {

        // Assuming a mock or a valid Dict for initialization

        Dict prefDict;  // This should be properly constructed as per the actual implementation needs.

        viewerPrefs = new ViewerPreferences(prefDict);

    }



    void TearDown() override {

        delete viewerPrefs;

    }

};



TEST_F(ViewerPreferencesTest_1355, GetPickTrayByPDFSize_DefaultValue_1355) {

    // Assuming default value is false if not set in Dict

    EXPECT_FALSE(viewerPrefs->getPickTrayByPDFSize());

}



TEST_F(ViewerPreferencesTest_1355, GetHideToolbar_DefaultValue_1355) {

    // Assuming default value is false if not set in Dict

    EXPECT_FALSE(viewerPrefs->getHideToolbar());

}



TEST_F(ViewerPreferencesTest_1355, GetHideMenubar_DefaultValue_1355) {

    // Assuming default value is false if not set in Dict

    EXPECT_FALSE(viewerPrefs->getHideMenubar());

}



TEST_F(ViewerPreferencesTest_1355, GetHideWindowUI_DefaultValue_1355) {

    // Assuming default value is false if not set in Dict

    EXPECT_FALSE(viewerPrefs->getHideWindowUI());

}



TEST_F(ViewerPreferencesTest_1355, GetFitWindow_DefaultValue_1355) {

    // Assuming default value is false if not set in Dict

    EXPECT_FALSE(viewerPrefs->getFitWindow());

}



TEST_F(ViewerPreferencesTest_1355, GetCenterWindow_DefaultValue_1355) {

    // Assuming default value is false if not set in Dict

    EXPECT_FALSE(viewerPrefs->getCenterWindow());

}



TEST_F(ViewerPreferencesTest_1355, GetDisplayDocTitle_DefaultValue_1355) {

    // Assuming default value is false if not set in Dict

    EXPECT_FALSE(viewerPrefs->getDisplayDocTitle());

}



TEST_F(ViewerPreferencesTest_1355, GetNonFullScreenPageMode_DefaultValue_1355) {

    EXPECT_EQ(viewerPrefs->getNonFullScreenPageMode(), nfpmUseNone);

}



TEST_F(ViewerPreferencesTest_1355, GetDirection_DefaultValue_1355) {

    EXPECT_EQ(viewerPrefs->getDirection(), directionL2R);

}



TEST_F(ViewerPreferencesTest_1355, GetPrintScaling_DefaultValue_1355) {

    EXPECT_EQ(viewerPrefs->getPrintScaling(), printScalingAppDefault);

}



TEST_F(ViewerPreferencesTest_1355, GetDuplex_DefaultValue_1355) {

    EXPECT_EQ(viewerPrefs->getDuplex(), duplexNone);

}



TEST_F(ViewerPreferencesTest_1355, GetNumCopies_DefaultValue_1355) {

    EXPECT_EQ(viewerPrefs->getNumCopies(), 1);

}



TEST_F(ViewerPreferencesTest_1355, GetPrintPageRange_DefaultValue_1355) {

    EXPECT_TRUE(viewerPrefs->getPrintPageRange().empty());

}
