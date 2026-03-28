#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <string>
#include "exiv2/image.hpp"

using namespace Exiv2;

class ImageTest : public ::testing::Test {
protected:
    // Setup method for Image instance
    ImageTest() : image_(ImageType::Unknown, 0, std::make_unique<BasicIo>()) {}

    Image image_;
};

// Normal operation test for setting byte order
TEST_F(ImageTest, SetByteOrder_Normal_1088) {
    ByteOrder byteOrder = ByteOrder::bigEndian;
    image_.setByteOrder(byteOrder);

    EXPECT_EQ(image_.byteOrder(), byteOrder);
}

// Boundary test: Setting the byte order to invalid value
TEST_F(ImageTest, SetByteOrder_Invalid_1089) {
    ByteOrder byteOrder = ByteOrder::invalidByteOrder;
    image_.setByteOrder(byteOrder);

    EXPECT_EQ(image_.byteOrder(), ByteOrder::invalidByteOrder);
}

// Exceptional case: Verify that setting and getting byte order works correctly under various cases
TEST_F(ImageTest, SetByteOrder_Exceptional_1090) {
    try {
        ByteOrder byteOrder = static_cast<ByteOrder>(-1);  // Invalid value for ByteOrder
        image_.setByteOrder(byteOrder);
        FAIL() << "Expected std::invalid_argument exception.";
    } catch (const std::invalid_argument& e) {
        EXPECT_STREQ(e.what(), "Invalid byte order");
    } catch (...) {
        FAIL() << "Expected std::invalid_argument exception.";
    }
}

// Verification of external interactions: Check if external mock function is called correctly when byteOrder is set
TEST_F(ImageTest, SetByteOrder_ExternalInteraction_1091) {
    // Assuming a mock for external handler that interacts with byteOrder, e.g., setting configuration.
    MockExternalHandler mockHandler;
    EXPECT_CALL(mockHandler, handleByteOrderChange(ByteOrder::bigEndian))
        .Times(1);

    image_.setByteOrder(ByteOrder::bigEndian);
}