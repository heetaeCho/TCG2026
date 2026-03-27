#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "poppler-page.cc"

#include "CairoOutputDev.h"

#include "poppler-private.h"



using ::testing::_;

using ::testing::Return;



class MockPopplerPage {

public:

    MOCK_METHOD1(createGfx, std::unique_ptr<Gfx>(CairoImageOutputDev*, double, double, int, bool, bool, int, int, int, int, nullptr_t, nullptr_t));

    MOCK_METHOD1(display, void(Gfx*));



    std::shared_ptr<TextPage> text;

};



class MockGfx {

public:

    MOCK_METHOD0(get, Gfx*());

};



class PopplerPageTest_2447 : public ::testing::Test {

protected:

    MockPopplerPage mock_page;

    MockGfx mock_gfx;



    bool imgDrawDeviceCbk(int img_id, void *data) {

        return true; // Simple implementation for callback

    }



    void SetUp() override {

        EXPECT_CALL(mock_page, createGfx(_, 72.0, 72.0, 0, false, true, -1, -1, -1, -1, nullptr, nullptr))

            .WillOnce(::testing::Return(ByMove(std::unique_ptr<Gfx>(mock_gfx.get()))));

    }

};



TEST_F(PopplerPageTest_2447, PopplerPageGetImageOutputDev_NormalOperation_2447) {

    CairoImageOutputDev* image_dev = poppler_page_get_image_output_dev(&mock_page, imgDrawDeviceCbk, nullptr);

    EXPECT_NE(image_dev, nullptr);

    delete image_dev;

}



TEST_F(PopplerPageTest_2447, PopplerPageGetImageOutputDev_CallbackSet_2447) {

    bool (*callback)(int, void*) = imgDrawDeviceCbk;

    void* callback_data = nullptr;



    EXPECT_CALL(mock_page, createGfx(_, 72.0, 72.0, 0, false, true, -1, -1, -1, -1, nullptr, nullptr))

        .WillOnce(::testing::Return(ByMove(std::unique_ptr<Gfx>(mock_gfx.get()))));



    CairoImageOutputDev* image_dev = poppler_page_get_image_output_dev(&mock_page, callback, callback_data);

    EXPECT_NE(image_dev, nullptr);



    // Verify that the callback is set

    EXPECT_EQ(image_dev->imgDrawCbk, callback);

    EXPECT_EQ(image_dev->imgDrawCbkData, callback_data);



    delete image_dev;

}



TEST_F(PopplerPageTest_2447, PopplerPageGetImageOutputDev_NoCallback_2447) {

    CairoImageOutputDev* image_dev = poppler_page_get_image_output_dev(&mock_page, nullptr, nullptr);

    EXPECT_NE(image_dev, nullptr);



    // Verify that the callback is not set

    EXPECT_EQ(image_dev->imgDrawCbk, nullptr);

    EXPECT_EQ(image_dev->imgDrawCbkData, nullptr);



    delete image_dev;

}
