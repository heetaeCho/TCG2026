#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "poppler-private.h"

#include "Page.h"

#include <cairo.h>



using namespace testing;



class PopplerPageTest_2438 : public ::testing::Test {

protected:

    MockFunction<bool(void*)> abortCheckCbk;

    MockFunction<bool(Annot*, void*)> annotDisplayDecideCbk;



    std::shared_ptr<Page> mock_page;

    PopplerPage poppler_page;



    virtual void SetUp() override {

        mock_page = std::make_shared<StrictMock<Page>>(nullptr, 0, Object(), Ref(), std::make_unique<PageAttrs>());

        poppler_page.page = mock_page;

    }

};



TEST_F(PopplerPageTest_2438, GetThumbnail_Success_2438) {

    unsigned char* data = new unsigned char[1];

    int width = 100, height = 100, rowstride = 100;



    EXPECT_CALL(*mock_page, loadThumb(_, _, _, _))

        .WillOnce(DoAll(SetArgReferee<0>(data),

                        SetArgReferee<1>(width),

                        SetArgReferee<2>(height),

                        SetArgReferee<3>(rowstride),

                        Return(true)));



    cairo_surface_t* surface = poppler_page_get_thumbnail(&poppler_page);

    EXPECT_NE(surface, nullptr);



    cairo_surface_destroy(surface);

    delete[] data;

}



TEST_F(PopplerPageTest_2438, GetThumbnail_NullPage_2438) {

    PopplerPage invalid_poppler_page;

    invalid_poppler_page.page = nullptr;



    cairo_surface_t* surface = poppler_page_get_thumbnail(&invalid_poppler_page);

    EXPECT_EQ(surface, nullptr);

}



TEST_F(PopplerPageTest_2438, GetThumbnail_LoadThumbFail_2438) {

    EXPECT_CALL(*mock_page, loadThumb(_, _, _, _))

        .WillOnce(Return(false));



    cairo_surface_t* surface = poppler_page_get_thumbnail(&poppler_page);

    EXPECT_EQ(surface, nullptr);

}



TEST_F(PopplerPageTest_2438, GetThumbnail_ZeroWidthHeight_2438) {

    unsigned char* data = new unsigned char[1];

    int width = 0, height = 0, rowstride = 0;



    EXPECT_CALL(*mock_page, loadThumb(_, _, _, _))

        .WillOnce(DoAll(SetArgReferee<0>(data),

                        SetArgReferee<1>(width),

                        SetArgReferee<2>(height),

                        SetArgReferee<3>(rowstride),

                        Return(true)));



    cairo_surface_t* surface = poppler_page_get_thumbnail(&poppler_page);

    EXPECT_EQ(surface, nullptr);



    delete[] data;

}



TEST_F(PopplerPageTest_2438, GetThumbnail_ZeroRowStride_2438) {

    unsigned char* data = new unsigned char[1];

    int width = 100, height = 100, rowstride = 0;



    EXPECT_CALL(*mock_page, loadThumb(_, _, _, _))

        .WillOnce(DoAll(SetArgReferee<0>(data),

                        SetArgReferee<1>(width),

                        SetArgReferee<2>(height),

                        SetArgReferee<3>(rowstride),

                        Return(true)));



    cairo_surface_t* surface = poppler_page_get_thumbnail(&poppler_page);

    EXPECT_EQ(surface, nullptr);



    delete[] data;

}
