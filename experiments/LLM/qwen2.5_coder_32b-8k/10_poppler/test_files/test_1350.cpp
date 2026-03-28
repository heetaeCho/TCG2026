#include <gtest/gtest.h>

#include "ViewerPreferences.h"



class ViewerPreferencesTest_1350 : public ::testing::Test {

protected:

    // Assuming a mock or setup for Dict if needed, but treating it as black box.

    ViewerPreferences* viewerPrefs;



    void SetUp() override {

        // Create an instance with default or dummy data since internal logic is not to be inferred

        viewerPrefs = new ViewerPreferences(Dict());

    }



    void TearDown() override {

        delete viewerPrefs;

    }

};



TEST_F(ViewerPreferencesTest_1350, GetDisplayDocTitle_DefaultValue_1350) {

    // Assuming default value for displayDocTitle is false if not specified in Dict

    EXPECT_FALSE(viewerPrefs->getDisplayDocTitle());

}



TEST_F(ViewerPreferencesTest_1350, GetHideToolbar_DefaultValue_1350) {

    // Assuming default value for hideToolbar is false if not specified in Dict

    EXPECT_FALSE(viewerPrefs->getHideToolbar());

}



TEST_F(ViewerPreferencesTest_1350, GetHideMenubar_DefaultValue_1350) {

    // Assuming default value for hideMenubar is false if not specified in Dict

    EXPECT_FALSE(viewerPrefs->getHideMenubar());

}



TEST_F(ViewerPreferencesTest_1350, GetHideWindowUI_DefaultValue_1350) {

    // Assuming default value for hideWindowUI is false if not specified in Dict

    EXPECT_FALSE(viewerPrefs->getHideWindowUI());

}



TEST_F(ViewerPreferencesTest_1350, GetFitWindow_DefaultValue_1350) {

    // Assuming default value for fitWindow is false if not specified in Dict

    EXPECT_FALSE(viewerPrefs->getFitWindow());

}



TEST_F(ViewerPreferencesTest_1350, GetCenterWindow_DefaultValue_1350) {

    // Assuming default value for centerWindow is false if not specified in Dict

    EXPECT_FALSE(viewerPrefs->getCenterWindow());

}



TEST_F(ViewerPreferencesTest_1350, GetNonFullScreenPageMode_DefaultValue_1350) {

    // Assuming default value for nonFullScreenPageMode is nfpmUseNone if not specified in Dict

    EXPECT_EQ(viewerPrefs->getNonFullScreenPageMode(), nfpmUseNone);

}



TEST_F(ViewerPreferencesTest_1350, GetDirection_DefaultValue_1350) {

    // Assuming default value for direction is directionL2R if not specified in Dict

    EXPECT_EQ(viewerPrefs->getDirection(), directionL2R);

}



TEST_F(ViewerPreferencesTest_1350, GetPrintScaling_DefaultValue_1350) {

    // Assuming default value for printScaling is printScalingAppDefault if not specified in Dict

    EXPECT_EQ(viewerPrefs->getPrintScaling(), printScalingAppDefault);

}



TEST_F(ViewerPreferencesTest_1350, GetDuplex_DefaultValue_1350) {

    // Assuming default value for duplex is duplexNone if not specified in Dict

    EXPECT_EQ(viewerPrefs->getDuplex(), duplexNone);

}



TEST_F(ViewerPreferencesTest_1350, GetPickTrayByPDFSize_DefaultValue_1350) {

    // Assuming default value for pickTrayByPDFSize is false if not specified in Dict

    EXPECT_FALSE(viewerPrefs->getPickTrayByPDFSize());

}



TEST_F(ViewerPreferencesTest_1350, GetNumCopies_DefaultValue_1350) {

    // Assuming default value for numCopies is 1 if not specified in Dict

    EXPECT_EQ(viewerPrefs->getNumCopies(), 1);

}



TEST_F(ViewerPreferencesTest_1350, GetPrintPageRange_DefaultValue_1350) {

    // Assuming default value for printPageRange is empty vector if not specified in Dict

    EXPECT_TRUE(viewerPrefs->getPrintPageRange().empty());

}
