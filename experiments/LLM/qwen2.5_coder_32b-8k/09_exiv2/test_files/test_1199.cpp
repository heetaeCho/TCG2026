#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "exiv2/bmffimage.hpp"

#include "exiv2/types.hpp"

#include <sstream>



using namespace Exiv2;

using ::testing::_;

using ::testing::Return;



class BmffImageTest : public ::testing::Test {

protected:

    std::unique_ptr<BasicIo> ioMock = std::make_unique<BasicIo>();

    BmffImage bmffImage{std::move(ioMock), false, 10};

    DataBuf data{8};

    std::ostringstream out;



    void SetUp() override {

        // Initialize data buffer with some values

        for (size_t i = 0; i < data.size(); ++i) {

            data.write_uint8(i, static_cast<uint8_t>(i));

        }

    }

};



TEST_F(BmffImageTest_1199, ParseCr3Preview_NormalOperation_1199) {

    bmffImage.parseCr3Preview(data, out, false, 0, 1, 2, 4);

    const auto& previews = bmffImage.nativePreviews();

    ASSERT_EQ(previews.size(), 1u);

    EXPECT_EQ(previews[0].width_, 257); // 1 * 256 + 2

    EXPECT_EQ(previews[0].height_, 513); // 2 * 256 + 1

    EXPECT_EQ(previews[0].size_, 1028); // 4 * 256 + 512 + 12

    EXPECT_EQ(previews[0].filter_, "");

    EXPECT_EQ(previews[0].mimeType_, "image/jpeg");

}



TEST_F(BmffImageTest_1199, ParseCr3Preview_Version1MimeType_1199) {

    bmffImage.parseCr3Preview(data, out, false, 1, 1, 2, 4);

    const auto& previews = bmffImage.nativePreviews();

    ASSERT_EQ(previews.size(), 1u);

    EXPECT_EQ(previews[0].mimeType_, "application/octet-stream");

}



TEST_F(BmffImageTest_1199, ParseCr3Preview_TraceEnabled_1199) {

    bmffImage.parseCr3Preview(data, out, true, 0, 1, 2, 4);

    EXPECT_EQ(out.str(), "width,height,size = 257,513,1028");

}



TEST_F(BmffImageTest_1199, ParseCr3Preview_RelativePositionBoundary_1199) {

    bmffImage.parseCr3Preview(data, out, false, 0, 1, 2, std::numeric_limits<size_t>::max());

    const auto& previews = bmffImage.nativePreviews();

    ASSERT_EQ(previews.size(), 1u);

    EXPECT_EQ(previews[0].position_, std::numeric_limits<size_t>::max() + ioMock->tell());

}



TEST_F(BmffImageTest_1199, ParseCr3Preview_DataBufferTooSmall_1199) {

    DataBuf smallData{2};

    EXPECT_THROW(bmffImage.parseCr3Preview(smallData, out, false, 0, 1, 2, 4), Error);

}



TEST_F(BmffImageTest_1199, ParseCr3Preview_RelativePositionOverflow_1199) {

    ON_CALL(*ioMock, tell()).WillByDefault(Return(std::numeric_limits<size_t>::max()));

    EXPECT_THROW(bmffImage.parseCr3Preview(data, out, false, 0, 1, 2, 4), Error);

}
