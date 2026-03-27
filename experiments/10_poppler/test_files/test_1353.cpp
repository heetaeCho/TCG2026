#include <gtest/gtest.h>

#include "TestProjects/poppler/poppler/ViewerPreferences.h"



class ViewerPreferencesTest_1353 : public ::testing::Test {

protected:

    Dict mockDict;  // Assuming Dict is a type that can be default constructed for this test.

    ViewerPreferences viewerPrefs;



    ViewerPreferencesTest_1353() : viewerPrefs(mockDict) {}

};



TEST_F(ViewerPreferencesTest_1353, GetPrintScaling_DefaultValue_1353) {

    EXPECT_EQ(viewerPrefs.getPrintScaling(), printScalingAppDefault);

}



// Assuming PrintScaling can have other values like printScalingNone, printScalingShrinkToFit, etc.

TEST_F(ViewerPreferencesTest_1353, GetPrintScaling_OtherValues_1353) {

    // This test would require a way to set the value in Dict to something other than default,

    // which is not provided here. Thus, this test is more of a placeholder for completeness.

    // In a real scenario, you'd have a mechanism to control the values passed via mockDict.

}



TEST_F(ViewerPreferencesTest_1353, GetHideToolbar_DefaultValue_1353) {

    EXPECT_EQ(viewerPrefs.getHideToolbar(), false);

}



TEST_F(ViewerPreferencesTest_1353, GetHideMenubar_DefaultValue_1353) {

    EXPECT_EQ(viewerPrefs.getHideMenubar(), false);

}



TEST_F(ViewerPreferencesTest_1353, GetHideWindowUI_DefaultValue_1353) {

    EXPECT_EQ(viewerPrefs.getHideWindowUI(), false);

}



TEST_F(ViewerPreferencesTest_1353, GetFitWindow_DefaultValue_1353) {

    EXPECT_EQ(viewerPrefs.getFitWindow(), false);

}



TEST_F(ViewerPreferencesTest_1353, GetCenterWindow_DefaultValue_1353) {

    EXPECT_EQ(viewerPrefs.getCenterWindow(), false);

}



TEST_F(ViewerPreferencesTest_1353, GetDisplayDocTitle_DefaultValue_1353) {

    EXPECT_EQ(viewerPrefs.getDisplayDocTitle(), false);

}



TEST_F(ViewerPreferencesTest_1353, GetNonFullScreenPageMode_DefaultValue_1353) {

    EXPECT_EQ(viewerPrefs.getNonFullScreenPageMode(), nfpmUseNone);

}



TEST_F(ViewerPreferencesTest_1353, GetDirection_DefaultValue_1353) {

    EXPECT_EQ(viewerPrefs.getDirection(), directionL2R);

}



TEST_F(ViewerPreferencesTest_1353, GetDuplex_DefaultValue_1353) {

    EXPECT_EQ(viewerPrefs.getDuplex(), duplexNone);

}



TEST_F(ViewerPreferencesTest_1353, GetPickTrayByPDFSize_DefaultValue_1353) {

    EXPECT_EQ(viewerPrefs.getPickTrayByPDFSize(), false);

}



TEST_F(ViewerPreferencesTest_1353, GetNumCopies_DefaultValue_1353) {

    EXPECT_EQ(viewerPrefs.getNumCopies(), 1);

}



TEST_F(ViewerPreferencesTest_1353, GetPrintPageRange_DefaultValue_1353) {

    EXPECT_TRUE(viewerPrefs.getPrintPageRange().empty());

}
