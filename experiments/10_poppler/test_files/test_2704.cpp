#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "TestProjects/poppler/utils/HtmlOutputDev.h"



using namespace testing;



class HtmlPageTest : public Test {

protected:

    HtmlPage page;

    HtmlPageTest() : page(false) {}

};



TEST_F(HtmlPageTest_2704, GetNumImagesInitiallyZero_2704) {

    EXPECT_EQ(page.getNumImages(), 0);

}



TEST_F(HtmlPageTest_2704, AddImageIncreasesCount_2704) {

    page.addImage("image1.png", nullptr);

    EXPECT_EQ(page.getNumImages(), 1);



    page.addImage("image2.png", nullptr);

    EXPECT_EQ(page.getNumImages(), 2);

}



TEST_F(HtmlPageTest_2704, AddMultipleSameImageIncreasesCount_2704) {

    page.addImage("same_image.png", nullptr);

    page.addImage("same_image.png", nullptr);



    EXPECT_EQ(page.getNumImages(), 2);

}



TEST_F(HtmlPageTest_2704, ClearResetsImageCount_2704) {

    page.addImage("image1.png", nullptr);

    page.clear();

    EXPECT_EQ(page.getNumImages(), 0);

}
