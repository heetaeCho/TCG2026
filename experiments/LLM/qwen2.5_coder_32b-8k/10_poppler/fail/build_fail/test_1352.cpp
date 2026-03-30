#include <gtest/gtest.h>

#include "ViewerPreferences.h"

#include <vector>



class ViewerPreferencesTest_1352 : public ::testing::Test {

protected:

    Dict mockDict; // Assuming Dict is a class used in the constructor of ViewerPreferences

    ViewerPreferences* viewerPrefs;



    void SetUp() override {

        viewerPrefs = new ViewerPreferences(mockDict);

    }



    void TearDown() override {

        delete viewerPrefs;

    }

};



TEST_F(ViewerPreferencesTest_1352, GetHideToolbar_ReturnsDefaultValue_1352) {

    EXPECT_EQ(viewerPrefs->getHideToolbar(), false);

}



TEST_F(ViewerPreferencesTest_1352, GetHideMenubar_ReturnsDefaultValue_1352) {

    EXPECT_EQ(viewerPrefs->getHideMenubar(), false);

}



TEST_F(ViewerPreferencesTest_1352, GetHideWindowUI_ReturnsDefaultValue_1352) {

    EXPECT_EQ(viewerPrefs->getHideWindowUI(), false);

}



TEST_F(ViewerPreferencesTest_1352, GetFitWindow_ReturnsDefaultValue_1352) {

    EXPECT_EQ(viewerPrefs->getFitWindow(), false);

}



TEST_F(ViewerPreferencesTest_1352, GetCenterWindow_ReturnsDefaultValue_1352) {

    EXPECT_EQ(viewerPrefs->getCenterWindow(), false);

}



TEST_F(ViewerPreferencesTest_1352, GetDisplayDocTitle_ReturnsDefaultValue_1352) {

    EXPECT_EQ(viewerPrefs->getDisplayDocTitle(), false);

}



TEST_F(ViewerPreferencesTest_1352, GetNonFullScreenPageMode_ReturnsDefaultValue_1352) {

    EXPECT_EQ(viewerPrefs->getNonFullScreenPageMode(), nfpmUseNone);

}



TEST_F(ViewerPreferencesTest_1352, GetDirection_ReturnsDefaultValue_1352) {

    EXPECT_EQ(viewerPrefs->getDirection(), directionL2R);

}



TEST_F(ViewerPreferencesTest_1352, GetPrintScaling_ReturnsDefaultValue_1352) {

    EXPECT_EQ(viewerPrefs->getPrintScaling(), printScalingAppDefault);

}



TEST_F(ViewerPreferencesTest_1352, GetDuplex_ReturnsDefaultValue_1352) {

    EXPECT_EQ(viewerPrefs->getDuplex(), duplexNone);

}



TEST_F(ViewerPreferencesTest_1352, GetPickTrayByPDFSize_ReturnsDefaultValue_1352) {

    EXPECT_EQ(viewerPrefs->getPickTrayByPDFSize(), false);

}



TEST_F(ViewerPreferencesTest_1352, GetNumCopies_ReturnsDefaultValue_1352) {

    EXPECT_EQ(viewerPrefs->getNumCopies(), 1);

}



TEST_F(ViewerPreferencesTest_1352, GetPrintPageRange_ReturnsDefaultValue_1352) {

    EXPECT_TRUE(viewerPrefs->getPrintPageRange().empty());

}
