#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "poppler-page.cc"

#include "Page.h"



class MockPage : public Page {

public:

    MOCK_METHOD(Object, getThumb, (), (const, override));

};



class PopplerPageTest_2440 : public ::testing::Test {

protected:

    std::shared_ptr<MockPage> mock_page;

    PopplerPage poppler_page;



    void SetUp() override {

        mock_page = std::make_shared<MockPage>();

        poppler_page.page = mock_page.get();

    }

};



TEST_F(PopplerPageTest_2440, GetThumbnailSize_ReturnsFalseWhenThumbIsNotStream_2440) {

    Object thumb;

    EXPECT_CALL(*mock_page, getThumb()).WillOnce(testing::Return(thumb));



    int width = 0;

    int height = 0;

    gboolean result = poppler_page_get_thumbnail_size(&poppler_page, &width, &height);



    EXPECT_FALSE(result);

    EXPECT_EQ(width, 0);

    EXPECT_EQ(height, 0);

}



TEST_F(PopplerPageTest_2440, GetThumbnailSize_ReturnsFalseWhenDictLookupFails_2440) {

    Object thumb;

    thumb.initStream(nullptr, nullptr);

    EXPECT_CALL(*mock_page, getThumb()).WillOnce(testing::Return(thumb));



    int width = 0;

    int height = 0;

    gboolean result = poppler_page_get_thumbnail_size(&poppler_page, &width, &height);



    EXPECT_FALSE(result);

    EXPECT_EQ(width, 0);

    EXPECT_EQ(height, 0);

}



TEST_F(PopplerPageTest_2440, GetThumbnailSize_ReturnsTrueWithValidDimensions_2440) {

    Object thumb;

    Dict dict;

    dict.dictSet("Width", Object(100));

    dict.dictSet("Height", Object(200));



    thumb.initStream(nullptr, &dict);

    EXPECT_CALL(*mock_page, getThumb()).WillOnce(testing::Return(thumb));



    int width = 0;

    int height = 0;

    gboolean result = poppler_page_get_thumbnail_size(&poppler_page, &width, &height);



    EXPECT_TRUE(result);

    EXPECT_EQ(width, 100);

    EXPECT_EQ(height, 200);

}



TEST_F(PopplerPageTest_2440, GetThumbnailSize_ReturnsFalseWhenWidthLookupFails_2440) {

    Object thumb;

    Dict dict;

    dict.dictSet("Height", Object(200));



    thumb.initStream(nullptr, &dict);

    EXPECT_CALL(*mock_page, getThumb()).WillOnce(testing::Return(thumb));



    int width = 0;

    int height = 0;

    gboolean result = poppler_page_get_thumbnail_size(&poppler_page, &width, &height);



    EXPECT_FALSE(result);

    EXPECT_EQ(width, 0);

    EXPECT_EQ(height, 0);

}



TEST_F(PopplerPageTest_2440, GetThumbnailSize_ReturnsFalseWhenHeightLookupFails_2440) {

    Object thumb;

    Dict dict;

    dict.dictSet("Width", Object(100));



    thumb.initStream(nullptr, &dict);

    EXPECT_CALL(*mock_page, getThumb()).WillOnce(testing::Return(thumb));



    int width = 0;

    int height = 0;

    gboolean result = poppler_page_get_thumbnail_size(&poppler_page, &width, &height);



    EXPECT_FALSE(result);

    EXPECT_EQ(width, 0);

    EXPECT_EQ(height, 0);

}



TEST_F(PopplerPageTest_2440, GetThumbnailSize_ReturnsFalseWhenNullWidthPointerPassed_2440) {

    Object thumb;

    thumb.initStream(nullptr, nullptr);

    EXPECT_CALL(*mock_page, getThumb()).WillOnce(testing::Return(thumb));



    int height = 0;

    gboolean result = poppler_page_get_thumbnail_size(&poppler_page, nullptr, &height);



    EXPECT_FALSE(result);

}



TEST_F(PopplerPageTest_2440, GetThumbnailSize_ReturnsFalseWhenNullHeightPointerPassed_2440) {

    Object thumb;

    thumb.initStream(nullptr, nullptr);

    EXPECT_CALL(*mock_page, getThumb()).WillOnce(testing::Return(thumb));



    int width = 0;

    gboolean result = poppler_page_get_thumbnail_size(&poppler_page, &width, nullptr);



    EXPECT_FALSE(result);

}



TEST_F(PopplerPageTest_2440, GetThumbnailSize_ReturnsFalseWhenNullPagePointerPassed_2440) {

    Object thumb;

    thumb.initStream(nullptr, nullptr);

    EXPECT_CALL(*mock_page, getThumb()).WillOnce(testing::Return(thumb));



    int width = 0;

    int height = 0;

    gboolean result = poppler_page_get_thumbnail_size(nullptr, &width, &height);



    EXPECT_FALSE(result);

}
