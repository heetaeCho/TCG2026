#include <gtest/gtest.h>

#include "TestProjects/poppler/poppler/ViewerPreferences.h"



class ViewerPreferencesTest_1347 : public ::testing::Test {

protected:

    Dict prefDict;  // Assuming Dict is a valid class or type used in the actual codebase

    ViewerPreferences viewerPrefs;



    ViewerPreferencesTest_1347() : viewerPrefs(prefDict) {}

};



TEST_F(ViewerPreferencesTest_1347, GetHideWindowUINormalOperation_1347) {

    // Assuming hideWindowUI is initialized to false by default in the constructor

    EXPECT_FALSE(viewerPrefs.getHideWindowUI());

}



// Boundary conditions for boolean values are not applicable as they only have two states.

// Exceptional or error cases are not observable through the provided interface.



TEST_F(ViewerPreferencesTest_1347, GetHideToolbarNormalOperation_1347) {

    // Assuming hideToolbar is initialized to false by default in the constructor

    EXPECT_FALSE(viewerPrefs.getHideToolbar());

}



TEST_F(ViewerPreferencesTest_1347, GetHideMenubarNormalOperation_1347) {

    // Assuming hideMenubar is initialized to false by default in the constructor

    EXPECT_FALSE(viewerPrefs.getHideMenubar());

}



TEST_F(ViewerPreferencesTest_1347, GetFitWindowNormalOperation_1347) {

    // Assuming fitWindow is initialized to false by default in the constructor

    EXPECT_FALSE(viewerPrefs.getFitWindow());

}



TEST_F(ViewerPreferencesTest_1347, GetCenterWindowNormalOperation_1347) {

    // Assuming centerWindow is initialized to false by default in the constructor

    EXPECT_FALSE(viewerPrefs.getCenterWindow());

}



TEST_F(ViewerPreferencesTest_1347, GetDisplayDocTitleNormalOperation_1347) {

    // Assuming displayDocTitle is initialized to false by default in the constructor

    EXPECT_FALSE(viewerPrefs.getDisplayDocTitle());

}



TEST_F(ViewerPreferencesTest_1347, GetNonFullScreenPageModeNormalOperation_1347) {

    // Assuming nonFullScreenPageMode is initialized to nfpmUseNone by default in the constructor

    EXPECT_EQ(viewerPrefs.getNonFullScreenPageMode(), nfpmUseNone);

}



TEST_F(ViewerPreferencesTest_1347, GetDirectionNormalOperation_1347) {

    // Assuming direction is initialized to directionL2R by default in the constructor

    EXPECT_EQ(viewerPrefs.getDirection(), directionL2R);

}



TEST_F(ViewerPreferencesTest_1347, GetPrintScalingNormalOperation_1347) {

    // Assuming printScaling is initialized to printScalingAppDefault by default in the constructor

    EXPECT_EQ(viewerPrefs.getPrintScaling(), printScalingAppDefault);

}



TEST_F(ViewerPreferencesTest_1347, GetDuplexNormalOperation_1347) {

    // Assuming duplex is initialized to duplexNone by default in the constructor

    EXPECT_EQ(viewerPrefs.getDuplex(), duplexNone);

}



TEST_F(ViewerPreferencesTest_1347, GetPickTrayByPDFSizeNormalOperation_1347) {

    // Assuming pickTrayByPDFSize is initialized to false by default in the constructor

    EXPECT_FALSE(viewerPrefs.getPickTrayByPDFSize());

}



TEST_F(ViewerPreferencesTest_1347, GetNumCopiesNormalOperation_1347) {

    // Assuming numCopies is initialized to 1 by default in the constructor

    EXPECT_EQ(viewerPrefs.getNumCopies(), 1);

}



TEST_F(ViewerPreferencesTest_1347, GetPrintPageRangeNormalOperation_1347) {

    // Assuming printPageRange is initialized to an empty vector by default in the constructor

    EXPECT_TRUE(viewerPrefs.getPrintPageRange().empty());

}
