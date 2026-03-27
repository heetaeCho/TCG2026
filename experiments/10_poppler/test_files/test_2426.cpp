#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "poppler-page.h"

#include "Page.h"



using namespace testing;



// Mock class for Page to control its behavior during tests

class MockPage : public poppler::Page {

public:

    MOCK_METHOD(int, getRotate, (), (const));

    MOCK_METHOD(double, getCropWidth, (), (const));

    MOCK_METHOD(double, getCropHeight, (), (const));



    // Constructor delegation

    using Page::Page;

};



// Test fixture class for PopplerPage tests

class PopplerPageTest : public ::testing::Test {

protected:

    void SetUp() override {

        page = new MockPage(nullptr, 0, Object(), Ref(), std::make_unique<PageAttrs>());

        poppler_page = g_new0(PopplerPage, 1);

        poppler_page->page = page;

    }



    void TearDown() override {

        g_free(poppler_page);

        delete page;

    }



    MockPage* page;

    PopplerPage* poppler_page;

};



// Test normal operation with no rotation

TEST_F(PopplerPageTest, GetSizeNoRotation_2426) {

    EXPECT_CALL(*page, getRotate()).WillOnce(Return(0));

    EXPECT_CALL(*page, getCropWidth()).WillOnce(Return(1920.0));

    EXPECT_CALL(*page, getCropHeight()).WillOnce(Return(1080.0));



    double width = 0.0, height = 0.0;

    poppler_page_get_size(poppler_page, &width, &height);



    ASSERT_EQ(width, 1920.0);

    ASSERT_EQ(height, 1080.0);

}



// Test normal operation with 90 degree rotation

TEST_F(PopplerPageTest, GetSizeRotation90_2426) {

    EXPECT_CALL(*page, getRotate()).WillOnce(Return(90));

    EXPECT_CALL(*page, getCropWidth()).WillOnce(Return(1920.0));

    EXPECT_CALL(*page, getCropHeight()).WillOnce(Return(1080.0));



    double width = 0.0, height = 0.0;

    poppler_page_get_size(poppler_page, &width, &height);



    ASSERT_EQ(width, 1080.0);

    ASSERT_EQ(height, 1920.0);

}



// Test normal operation with 270 degree rotation

TEST_F(PopplerPageTest, GetSizeRotation270_2426) {

    EXPECT_CALL(*page, getRotate()).WillOnce(Return(270));

    EXPECT_CALL(*page, getCropWidth()).WillOnce(Return(1920.0));

    EXPECT_CALL(*page, getCropHeight()).WillOnce(Return(1080.0));



    double width = 0.0, height = 0.0;

    poppler_page_get_size(poppler_page, &width, &height);



    ASSERT_EQ(width, 1080.0);

    ASSERT_EQ(height, 1920.0);

}



// Test normal operation with other rotation values

TEST_F(PopplerPageTest, GetSizeOtherRotation_2426) {

    EXPECT_CALL(*page, getRotate()).WillOnce(Return(180));

    EXPECT_CALL(*page, getCropWidth()).WillOnce(Return(1920.0));

    EXPECT_CALL(*page, getCropHeight()).WillOnce(Return(1080.0));



    double width = 0.0, height = 0.0;

    poppler_page_get_size(poppler_page, &width, &height);



    ASSERT_EQ(width, 1920.0);

    ASSERT_EQ(height, 1080.0);

}



// Test boundary condition with zero dimensions

TEST_F(PopplerPageTest, GetSizeZeroDimensions_2426) {

    EXPECT_CALL(*page, getRotate()).WillOnce(Return(0));

    EXPECT_CALL(*page, getCropWidth()).WillOnce(Return(0.0));

    EXPECT_CALL(*page, getCropHeight()).WillOnce(Return(0.0));



    double width = 1.0, height = 1.0;

    poppler_page_get_size(poppler_page, &width, &height);



    ASSERT_EQ(width, 0.0);

    ASSERT_EQ(height, 0.0);

}



// Test behavior when width pointer is nullptr

TEST_F(PopplerPageTest, GetSizeWidthNull_2426) {

    EXPECT_CALL(*page, getRotate()).WillOnce(Return(0));

    EXPECT_CALL(*page, getCropHeight()).WillOnce(Return(1080.0));



    double height = 0.0;

    poppler_page_get_size(poppler_page, nullptr, &height);



    ASSERT_EQ(height, 1080.0);

}



// Test behavior when height pointer is nullptr

TEST_F(PopplerPageTest, GetSizeHeightNull_2426) {

    EXPECT_CALL(*page, getRotate()).WillOnce(Return(0));

    EXPECT_CALL(*page, getCropWidth()).WillOnce(Return(1920.0));



    double width = 0.0;

    poppler_page_get_size(poppler_page, &width, nullptr);



    ASSERT_EQ(width, 1920.0);

}



// Test behavior when both pointers are nullptr

TEST_F(PopplerPageTest, GetSizeBothNull_2426) {

    EXPECT_CALL(*page, getRotate()).WillOnce(Return(0));



    poppler_page_get_size(poppler_page, nullptr, nullptr);



    // No assertions needed as the function should just return without error

}
