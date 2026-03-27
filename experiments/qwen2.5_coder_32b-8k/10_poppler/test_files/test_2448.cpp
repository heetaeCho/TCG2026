#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "poppler-page.h"

#include "poppler-private.h"

#include "CairoOutputDev.h"

#include "PDFRectangle.h"



using ::testing::_;

using ::testing::Return;

using ::testing::NotNull;



class MockCairoImage : public CairoImage {

public:

    MOCK_CONST_METHOD4(getRect, void(double*, double*, double*, double*));

};



class MockCairoImageOutputDev : public CairoImageOutputDev {

public:

    MOCK_CONST_METHOD0(getNumImages, int());

    MOCK_CONST_METHOD1(getImage, CairoImage*(int));

};



class MockPopplerPage : public PopplerPage {

public:

    MockPopplerPage() : PopplerPage(nullptr, 0, Object(), Ref(), std::make_unique<PageAttrs>()) {}

    MOCK_METHOD3(poppler_page_get_image_output_dev, CairoImageOutputDev*(MockPopplerPage*, void*, void*));

    MOCK_CONST_METHOD0(getCropBox, const PDFRectangle*());

};



TEST_F(PopplerPageTest_2448, NoImages_ReturnsEmptyList_2448) {

    MockPopplerPage mock_page;

    MockCairoImageOutputDev mock_output_dev;



    EXPECT_CALL(mock_page, poppler_page_get_image_output_dev(NotNull(), _, _))

        .WillOnce(Return(&mock_output_dev));

    EXPECT_CALL(mock_output_dev, getNumImages())

        .WillOnce(Return(0));



    GList *result = poppler_page_get_image_mapping(&mock_page);

    EXPECT_EQ(result, nullptr);



    g_list_free_full(result, (GDestroyNotify)poppler_image_mapping_free);

}



TEST_F(PopplerPageTest_2448, SingleImage_ReturnsOneMapping_2448) {

    MockPopplerPage mock_page;

    MockCairoImageOutputDev mock_output_dev;

    MockCairoImage mock_image;



    PDFRectangle crop_box(10, 10, 20, 20);

    EXPECT_CALL(mock_page, getCropBox())

        .WillRepeatedly(Return(&crop_box));



    EXPECT_CALL(mock_page, poppler_page_get_image_output_dev(NotNull(), _, _))

        .WillOnce(Return(&mock_output_dev));

    EXPECT_CALL(mock_output_dev, getNumImages())

        .WillOnce(Return(1));

    EXPECT_CALL(mock_output_dev, getImage(0))

        .WillOnce(Return(&mock_image));



    double x1 = 5.0, y1 = 5.0, x2 = 15.0, y2 = 15.0;

    EXPECT_CALL(mock_image, getRect(_, _, _, _))

        .WillOnce(DoAll(SetArgReferee<0>(x1), SetArgReferee<1>(y1),

                        SetArgReferee<2>(x2), SetArgReferee<3>(y2)));



    GList *result = poppler_page_get_image_mapping(&mock_page);

    EXPECT_EQ(g_list_length(result), 1);



    PopplerImageMapping *mapping = static_cast<PopplerImageMapping*>(g_list_nth_data(result, 0));

    EXPECT_EQ(mapping->image_id, 0);

    EXPECT_DOUBLE_EQ(mapping->area.x1, -5.0); // x1 -= crop_box.x1

    EXPECT_DOUBLE_EQ(mapping->area.y1, -5.0); // y1 -= crop_box.y1

    EXPECT_DOUBLE_EQ(mapping->area.x2, 5.0);  // x2 -= crop_box.x1

    EXPECT_DOUBLE_EQ(mapping->area.y2, 5.0);  // y2 -= crop_box.y1



    g_list_free_full(result, (GDestroyNotify)poppler_image_mapping_free);

}



TEST_F(PopplerPageTest_2448, MultipleImages_ReturnsMultipleMappings_2448) {

    MockPopplerPage mock_page;

    MockCairoImageOutputDev mock_output_dev;

    MockCairoImage mock_image1, mock_image2;



    PDFRectangle crop_box(10, 10, 30, 30);

    EXPECT_CALL(mock_page, getCropBox())

        .WillRepeatedly(Return(&crop_box));



    EXPECT_CALL(mock_page, poppler_page_get_image_output_dev(NotNull(), _, _))

        .WillOnce(Return(&mock_output_dev));

    EXPECT_CALL(mock_output_dev, getNumImages())

        .WillOnce(Return(2));

    EXPECT_CALL(mock_output_dev, getImage(0))

        .WillOnce(Return(&mock_image1));

    EXPECT_CALL(mock_output_dev, getImage(1))

        .WillOnce(Return(&mock_image2));



    double x1_1 = 5.0, y1_1 = 5.0, x2_1 = 15.0, y2_1 = 15.0;

    EXPECT_CALL(mock_image1, getRect(_, _, _, _))

        .WillOnce(DoAll(SetArgReferee<0>(x1_1), SetArgReferee<1>(y1_1),

                        SetArgReferee<2>(x2_1), SetArgReferee<3>(y2_1)));



    double x1_2 = 25.0, y1_2 = 25.0, x2_2 = 35.0, y2_2 = 35.0;

    EXPECT_CALL(mock_image2, getRect(_, _, _, _))

        .WillOnce(DoAll(SetArgReferee<0>(x1_2), SetArgReferee<1>(y1_2),

                        SetArgReferee<2>(x2_2), SetArgReferee<3>(y2_2)));



    GList *result = poppler_page_get_image_mapping(&mock_page);

    EXPECT_EQ(g_list_length(result), 2);



    PopplerImageMapping *mapping1 = static_cast<PopplerImageMapping*>(g_list_nth_data(result, 0));

    EXPECT_EQ(mapping1->image_id, 0);

    EXPECT_DOUBLE_EQ(mapping1->area.x1, -5.0); // x1 -= crop_box.x1

    EXPECT_DOUBLE_EQ(mapping1->area.y1, -5.0); // y1 -= crop_box.y1

    EXPECT_DOUBLE_EQ(mapping1->area.x2, 5.0);  // x2 -= crop_box.x1

    EXPECT_DOUBLE_EQ(mapping1->area.y2, 5.0);  // y2 -= crop_box.y1



    PopplerImageMapping *mapping2 = static_cast<PopplerImageMapping*>(g_list_nth_data(result, 1));

    EXPECT_EQ(mapping2->image_id, 1);

    EXPECT_DOUBLE_EQ(mapping2->area.x1, 15.0); // x1 -= crop_box.x1

    EXPECT_DOUBLE_EQ(mapping2->area.y1, 15.0); // y1 -= crop_box.y1

    EXPECT_DOUBLE_EQ(mapping2->area.x2, 25.0); // x2 -= crop_box.x1

    EXPECT_DOUBLE_EQ(mapping2->area.y2, 25.0); // y2 -= crop_box.y1



    g_list_free_full(result, (GDestroyNotify)poppler_image_mapping_free);

}



TEST_F(PopplerPageTest_2448, NullPage_ReturnsNull_2448) {

    GList *result = poppler_page_get_image_mapping(nullptr);

    EXPECT_EQ(result, nullptr);



    g_list_free_full(result, (GDestroyNotify)poppler_image_mapping_free);

}



TEST_F(PopplerPageTest_2448, ImageRectOutsideCropBox_CorrectlyAdjustedMapping_2448) {

    MockPopplerPage mock_page;

    MockCairoImageOutputDev mock_output_dev;

    MockCairoImage mock_image;



    PDFRectangle crop_box(10, 10, 30, 30);

    EXPECT_CALL(mock_page, getCropBox())

        .WillRepeatedly(Return(&crop_box));



    EXPECT_CALL(mock_page, poppler_page_get_image_output_dev(NotNull(), _, _))

        .WillOnce(Return(&mock_output_dev));

    EXPECT_CALL(mock_output_dev, getNumImages())

        .WillOnce(Return(1));

    EXPECT_CALL(mock_output_dev, getImage(0))

        .WillOnce(Return(&mock_image));



    double x1 = 5.0, y1 = 5.0, x2 = 40.0, y2 = 40.0;

    EXPECT_CALL(mock_image, getRect(_, _, _, _))

        .WillOnce(DoAll(SetArgReferee<0>(x1), SetArgReferee<1>(y1),

                        SetArgReferee<2>(x2), SetArgReferee<3>(y2)));



    GList *result = poppler_page_get_image_mapping(&mock_page);

    EXPECT_EQ(g_list_length(result), 1);



    PopplerImageMapping *mapping = static_cast<PopplerImageMapping*>(g_list_nth_data(result, 0));

    EXPECT_DOUBLE_EQ(mapping->area.x1, -5.0); // x1 -= crop_box.x1

    EXPECT_DOUBLE_EQ(mapping->area.y1, -5.0); // y1 -= crop_box.y1

    EXPECT_DOUBLE_EQ(mapping->area.x2, 30.0); // x2 -= crop_box.x1 (adjusted to crop box)

    EXPECT_DOUBLE_EQ(mapping->area.y2, 30.0); // y2 -= crop_box.y1 (adjusted to crop box)



    g_list_free_full(result, (GDestroyNotify)poppler_image_mapping_free);

}
