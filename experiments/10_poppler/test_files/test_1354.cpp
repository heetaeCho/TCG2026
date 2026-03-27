#include <gtest/gtest.h>

#include "ViewerPreferences.h"

#include <vector>



// Test Fixture for ViewerPreferences

class ViewerPreferencesTest_1354 : public ::testing::Test {

protected:

    ViewerPreferences* viewerPrefs;



    void SetUp() override {

        // Assuming Dict is a valid type in the context, we need to create an instance of it.

        // Since the actual implementation details are unknown, we will mock or use a default constructed object.

        viewerPrefs = new ViewerPreferences(/* Mock or default Dict */);

    }



    void TearDown() override {

        delete viewerPrefs;

    }

};



// Test case for normal operation: getDuplex returns expected value

TEST_F(ViewerPreferencesTest_1354, GetDuplex_ReturnsDefault_1354) {

    EXPECT_EQ(viewerPrefs->getDuplex(), duplexNone);

}



// Additional test cases based on other public methods



// Normal operation: getHideToolbar returns false by default

TEST_F(ViewerPreferencesTest_1354, GetHideToolbar_ReturnsFalseByDefault_1354) {

    EXPECT_FALSE(viewerPrefs->getHideToolbar());

}



// Normal operation: getHideMenubar returns false by default

TEST_F(ViewerPreferencesTest_1354, GetHideMenubar_ReturnsFalseByDefault_1354) {

    EXPECT_FALSE(viewerPrefs->getHideMenubar());

}



// Normal operation: getHideWindowUI returns false by default

TEST_F(ViewerPreferencesTest_1354, GetHideWindowUI_ReturnsFalseByDefault_1354) {

    EXPECT_FALSE(viewerPrefs->getHideWindowUI());

}



// Normal operation: getFitWindow returns false by default

TEST_F(ViewerPreferencesTest_1354, GetFitWindow_ReturnsFalseByDefault_1354) {

    EXPECT_FALSE(viewerPrefs->getFitWindow());

}



// Normal operation: getCenterWindow returns false by default

TEST_F(ViewerPreferencesTest_1354, GetCenterWindow_ReturnsFalseByDefault_1354) {

    EXPECT_FALSE(viewerPrefs->getCenterWindow());

}



// Normal operation: getDisplayDocTitle returns false by default

TEST_F(ViewerPreferencesTest_1354, GetDisplayDocTitle_ReturnsFalseByDefault_1354) {

    EXPECT_FALSE(viewerPrefs->getDisplayDocTitle());

}



// Normal operation: getNonFullScreenPageMode returns nfpmUseNone by default

TEST_F(ViewerPreferencesTest_1354, GetNonFullScreenPageMode_ReturnsNfpmUseNone_1354) {

    EXPECT_EQ(viewerPrefs->getNonFullScreenPageMode(), nfpmUseNone);

}



// Normal operation: getDirection returns directionL2R by default

TEST_F(ViewerPreferencesTest_1354, GetDirection_ReturnsDirectionL2R_1354) {

    EXPECT_EQ(viewerPrefs->getDirection(), directionL2R);

}



// Normal operation: getPrintScaling returns printScalingAppDefault by default

TEST_F(ViewerPreferencesTest_1354, GetPrintScaling_ReturnsPrintScalingAppDefault_1354) {

    EXPECT_EQ(viewerPrefs->getPrintScaling(), printScalingAppDefault);

}



// Normal operation: getPickTrayByPDFSize returns false by default

TEST_F(ViewerPreferencesTest_1354, GetPickTrayByPDFSize_ReturnsFalseByDefault_1354) {

    EXPECT_FALSE(viewerPrefs->getPickTrayByPDFSize());

}



// Normal operation: getNumCopies returns 1 by default

TEST_F(ViewerPreferencesTest_1354, GetNumCopies_ReturnsOne_1354) {

    EXPECT_EQ(viewerPrefs->getNumCopies(), 1);

}



// Normal operation: getPrintPageRange returns empty vector by default

TEST_F(ViewerPreferencesTest_1354, GetPrintPageRange_ReturnsEmptyVector_1354) {

    EXPECT_TRUE(viewerPrefs->getPrintPageRange().empty());

}
