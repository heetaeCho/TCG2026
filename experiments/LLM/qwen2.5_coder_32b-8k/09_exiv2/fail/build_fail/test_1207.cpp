#include <gtest/gtest.h>

#include "exiv2/preview.hpp"



using namespace Exiv2;



class PreviewImageTest : public ::testing::Test {

protected:

    DataBuf testData = {new byte[5]{1, 2, 3, 4, 5}, 5};

    PreviewProperties testProps;

    PreviewImage image = PreviewImage(testProps, std::move(testData));

};



TEST_F(PreviewImageTest_1207, CopyReturnsCorrectData_1207) {

    DataBuf copiedData = image.copy();

    ASSERT_EQ(copiedData.pData[0], 1);

    ASSERT_EQ(copiedData.pData[1], 2);

    ASSERT_EQ(copiedData.pData[2], 3);

    ASSERT_EQ(copiedData.pData[3], 4);

    ASSERT_EQ(copiedData.pData[4], 5);

    ASSERT_EQ(copiedData.size, image.size());

}



TEST_F(PreviewImageTest_1207, SizeReturnsCorrectValue_1207) {

    EXPECT_EQ(image.size(), 5u);

}



TEST_F(PreviewImageTest_1207, CopyDoesNotModifyOriginalData_1207) {

    DataBuf copiedData = image.copy();

    copiedData.pData[0] = 99;

    EXPECT_EQ(image.pData()[0], 1);

}



TEST_F(PreviewImageTest_1207, BoundaryConditionEmptyData_1207) {

    PreviewProperties emptyProps;

    DataBuf emptyData = {nullptr, 0};

    PreviewImage emptyImage(emptyProps, std::move(emptyData));

    EXPECT_EQ(emptyImage.size(), 0u);

}



TEST_F(PreviewImageTest_1207, CopyOfEmptyImageDataIsValid_1207) {

    PreviewProperties emptyProps;

    DataBuf emptyData = {nullptr, 0};

    PreviewImage emptyImage(emptyProps, std::move(emptyData));

    DataBuf copiedData = emptyImage.copy();

    EXPECT_EQ(copiedData.pData, nullptr);

    EXPECT_EQ(copiedData.size, 0u);

}
