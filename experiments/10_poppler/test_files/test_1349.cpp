#include <gtest/gtest.h>

#include "TestProjects/poppler/poppler/ViewerPreferences.h"

#include <vector>



using namespace testing;



TEST_F(ViewerPreferencesTest_1349, GetCenterWindow_ReturnsTrue_1349) {

    // Arrange

    Dict mockDict;  // Assuming Dict is a valid type used in the actual implementation.

    ViewerPreferences viewerPrefs(mockDict);



    // Act & Assert

    EXPECT_TRUE(viewerPrefs.getCenterWindow());

}



TEST_F(ViewerPreferencesTest_1349, GetCenterWindow_ReturnsFalse_1349) {

    // Arrange

    Dict mockDict;  // Assuming Dict is a valid type used in the actual implementation.

    ViewerPreferences viewerPrefs(mockDict);



    // Act & Assert

    EXPECT_FALSE(viewerPrefs.getCenterWindow());

}



TEST_F(ViewerPreferencesTest_1349, GetHideToolbar_ReturnsTrue_1349) {

    // Arrange

    Dict mockDict;  // Assuming Dict is a valid type used in the actual implementation.

    ViewerPreferences viewerPrefs(mockDict);



    // Act & Assert

    EXPECT_TRUE(viewerPrefs.getHideToolbar());

}



TEST_F(ViewerPreferencesTest_1349, GetHideToolbar_ReturnsFalse_1349) {

    // Arrange

    Dict mockDict;  // Assuming Dict is a valid type used in the actual implementation.

    ViewerPreferences viewerPrefs(mockDict);



    // Act & Assert

    EXPECT_FALSE(viewerPrefs.getHideToolbar());

}



TEST_F(ViewerPreferencesTest_1349, GetHideMenubar_ReturnsTrue_1349) {

    // Arrange

    Dict mockDict;  // Assuming Dict is a valid type used in the actual implementation.

    ViewerPreferences viewerPrefs(mockDict);



    // Act & Assert

    EXPECT_TRUE(viewerPrefs.getHideMenubar());

}



TEST_F(ViewerPreferencesTest_1349, GetHideMenubar_ReturnsFalse_1349) {

    // Arrange

    Dict mockDict;  // Assuming Dict is a valid type used in the actual implementation.

    ViewerPreferences viewerPrefs(mockDict);



    // Act & Assert

    EXPECT_FALSE(viewerPrefs.getHideMenubar());

}



TEST_F(ViewerPreferencesTest_1349, GetHideWindowUI_ReturnsTrue_1349) {

    // Arrange

    Dict mockDict;  // Assuming Dict is a valid type used in the actual implementation.

    ViewerPreferences viewerPrefs(mockDict);



    // Act & Assert

    EXPECT_TRUE(viewerPrefs.getHideWindowUI());

}



TEST_F(ViewerPreferencesTest_1349, GetHideWindowUI_ReturnsFalse_1349) {

    // Arrange

    Dict mockDict;  // Assuming Dict is a valid type used in the actual implementation.

    ViewerPreferences viewerPrefs(mockDict);



    // Act & Assert

    EXPECT_FALSE(viewerPrefs.getHideWindowUI());

}



TEST_F(ViewerPreferencesTest_1349, GetFitWindow_ReturnsTrue_1349) {

    // Arrange

    Dict mockDict;  // Assuming Dict is a valid type used in the actual implementation.

    ViewerPreferences viewerPrefs(mockDict);



    // Act & Assert

    EXPECT_TRUE(viewerPrefs.getFitWindow());

}



TEST_F(ViewerPreferencesTest_1349, GetFitWindow_ReturnsFalse_1349) {

    // Arrange

    Dict mockDict;  // Assuming Dict is a valid type used in the actual implementation.

    ViewerPreferences viewerPrefs(mockDict);



    // Act & Assert

    EXPECT_FALSE(viewerPrefs.getFitWindow());

}



TEST_F(ViewerPreferencesTest_1349, GetDisplayDocTitle_ReturnsTrue_1349) {

    // Arrange

    Dict mockDict;  // Assuming Dict is a valid type used in the actual implementation.

    ViewerPreferences viewerPrefs(mockDict);



    // Act & Assert

    EXPECT_TRUE(viewerPrefs.getDisplayDocTitle());

}



TEST_F(ViewerPreferencesTest_1349, GetDisplayDocTitle_ReturnsFalse_1349) {

    // Arrange

    Dict mockDict;  // Assuming Dict is a valid type used in the actual implementation.

    ViewerPreferences viewerPrefs(mockDict);



    // Act & Assert

    EXPECT_FALSE(viewerPrefs.getDisplayDocTitle());

}



TEST_F(ViewerPreferencesTest_1349, GetNonFullScreenPageMode_ReturnsDefault_1349) {

    // Arrange

    Dict mockDict;  // Assuming Dict is a valid type used in the actual implementation.

    ViewerPreferences viewerPrefs(mockDict);



    // Act & Assert

    EXPECT_EQ(viewerPrefs.getNonFullScreenPageMode(), nfpmUseNone);

}



TEST_F(ViewerPreferencesTest_1349, GetDirection_ReturnsDefault_1349) {

    // Arrange

    Dict mockDict;  // Assuming Dict is a valid type used in the actual implementation.

    ViewerPreferences viewerPrefs(mockDict);



    // Act & Assert

    EXPECT_EQ(viewerPrefs.getDirection(), directionL2R);

}



TEST_F(ViewerPreferencesTest_1349, GetPrintScaling_ReturnsDefault_1349) {

    // Arrange

    Dict mockDict;  // Assuming Dict is a valid type used in the actual implementation.

    ViewerPreferences viewerPrefs(mockDict);



    // Act & Assert

    EXPECT_EQ(viewerPrefs.getPrintScaling(), printScalingAppDefault);

}



TEST_F(ViewerPreferencesTest_1349, GetDuplex_ReturnsDefault_1349) {

    // Arrange

    Dict mockDict;  // Assuming Dict is a valid type used in the actual implementation.

    ViewerPreferences viewerPrefs(mockDict);



    // Act & Assert

    EXPECT_EQ(viewerPrefs.getDuplex(), duplexNone);

}



TEST_F(ViewerPreferencesTest_1349, GetPickTrayByPDFSize_ReturnsTrue_1349) {

    // Arrange

    Dict mockDict;  // Assuming Dict is a valid type used in the actual implementation.

    ViewerPreferences viewerPrefs(mockDict);



    // Act & Assert

    EXPECT_TRUE(viewerPrefs.getPickTrayByPDFSize());

}



TEST_F(ViewerPreferencesTest_1349, GetPickTrayByPDFSize_ReturnsFalse_1349) {

    // Arrange

    Dict mockDict;  // Assuming Dict is a valid type used in the actual implementation.

    ViewerPreferences viewerPrefs(mockDict);



    // Act & Assert

    EXPECT_FALSE(viewerPrefs.getPickTrayByPDFSize());

}



TEST_F(ViewerPreferencesTest_1349, GetNumCopies_ReturnsDefault_1349) {

    // Arrange

    Dict mockDict;  // Assuming Dict is a valid type used in the actual implementation.

    ViewerPreferences viewerPrefs(mockDict);



    // Act & Assert

    EXPECT_EQ(viewerPrefs.getNumCopies(), 1);

}



TEST_F(ViewerPreferencesTest_1349, GetPrintPageRange_ReturnsEmptyVector_1349) {

    // Arrange

    Dict mockDict;  // Assuming Dict is a valid type used in the actual implementation.

    ViewerPreferences viewerPrefs(mockDict);



    // Act & Assert

    EXPECT_TRUE(viewerPrefs.getPrintPageRange().empty());

}
