#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include <poppler-page.h>

#include <CairoOutputDev.h>



using ::testing::_;

using ::testing::Return;

using ::testing::MockFunction;



class PopplerPageTest : public ::testing::Test {

protected:

    struct _PopplerPage page;

};



TEST_F(PopplerPageTest, GetImageWithValidId_2450) {

    // Arrange

    MockFunction<bool(int img_id, void* data)> mock_cbk;

    CairoImageOutputDev* out = new CairoImageOutputDev();

    out->setImageDrawDecideCbk([](int, void*) { return true; }, nullptr);

    out->saveImage(new CairoImage());

    EXPECT_CALL(mock_cbk, Call(0, _)).WillOnce(Return(true));



    // Act

    cairo_surface_t* image = poppler_page_get_image(&page, 0);



    // Assert

    ASSERT_NE(image, nullptr);

    cairo_surface_destroy(image);

    delete out;

}



TEST_F(PopplerPageTest, GetImageWithInvalidId_2450) {

    // Arrange

    MockFunction<bool(int img_id, void* data)> mock_cbk;

    CairoImageOutputDev* out = new CairoImageOutputDev();

    out->setImageDrawDecideCbk([](int, void*) { return true; }, nullptr);

    EXPECT_CALL(mock_cbk, Call(1, _)).WillOnce(Return(false));



    // Act

    cairo_surface_t* image = poppler_page_get_image(&page, 1);



    // Assert

    ASSERT_EQ(image, nullptr);

    delete out;

}



TEST_F(PopplerPageTest, GetImageWithNullPage_2450) {

    // Arrange



    // Act

    cairo_surface_t* image = poppler_page_get_image(nullptr, 0);



    // Assert

    ASSERT_EQ(image, nullptr);

}



TEST_F(PopplerPageTest, GetImageWithNoImages_2450) {

    // Arrange

    MockFunction<bool(int img_id, void* data)> mock_cbk;

    CairoImageOutputDev* out = new CairoImageOutputDev();

    out->setImageDrawDecideCbk([](int, void*) { return true; }, nullptr);

    EXPECT_CALL(mock_cbk, Call(0, _)).WillOnce(Return(false));



    // Act

    cairo_surface_t* image = poppler_page_get_image(&page, 0);



    // Assert

    ASSERT_EQ(image, nullptr);

    delete out;

}
