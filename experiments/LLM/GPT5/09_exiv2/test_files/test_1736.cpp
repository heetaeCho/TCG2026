#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "exiv2/image.hpp"
#include "exiv2/basicio.hpp"
#include "exiv2/tiffimage.hpp"

namespace Exiv2 {

class MockBasicIo : public BasicIo {
public:
    MOCK_METHOD(bool, good, (), (const, override));
    MOCK_METHOD(size_t, read, (uint8_t* buffer, size_t size), (override));
    MOCK_METHOD(size_t, write, (const uint8_t* buffer, size_t size), (override));
    MOCK_METHOD(off_t, seek, (off_t offset, int whence), (override));
};

}  // namespace Exiv2

// Test case for normal operation of newTiffInstance
TEST_F(TiffImageTest_1736, newTiffInstance_ReturnsValidInstance_WhenGoodIo) {
    auto mockIo = std::make_unique<MockBasicIo>();
    EXPECT_CALL(*mockIo, good()).WillOnce(testing::Return(true));

    auto image = Exiv2::newTiffInstance(std::move(mockIo), false);

    EXPECT_NE(image, nullptr);  // The image should not be nullptr
}

// Test case for newTiffInstance when the Io is not good
TEST_F(TiffImageTest_1736, newTiffInstance_ReturnsNull_WhenBadIo) {
    auto mockIo = std::make_unique<MockBasicIo>();
    EXPECT_CALL(*mockIo, good()).WillOnce(testing::Return(false));

    auto image = Exiv2::newTiffInstance(std::move(mockIo), false);

    EXPECT_EQ(image, nullptr);  // The image should be nullptr
}

// Test case for creating a new instance with create set to true
TEST_F(TiffImageTest_1736, newTiffInstance_CreatesNewInstance_WhenCreateFlagIsTrue) {
    auto mockIo = std::make_unique<MockBasicIo>();
    EXPECT_CALL(*mockIo, good()).WillOnce(testing::Return(true));

    auto image = Exiv2::newTiffInstance(std::move(mockIo), true);

    EXPECT_NE(image, nullptr);  // The image should not be nullptr
}

// Test case for boundary condition: passing nullptr as BasicIo
TEST_F(TiffImageTest_1736, newTiffInstance_ReturnsNull_WhenIoIsNull) {
    auto image = Exiv2::newTiffInstance(nullptr, false);

    EXPECT_EQ(image, nullptr);  // The image should be nullptr
}

// Test case for verifying behavior with different Io state (good and bad)
TEST_F(TiffImageTest_1736, newTiffInstance_ReturnsValidOrNullBasedOnIoState) {
    // Good IO case
    auto mockIoGood = std::make_unique<MockBasicIo>();
    EXPECT_CALL(*mockIoGood, good()).WillOnce(testing::Return(true));

    auto imageGood = Exiv2::newTiffInstance(std::move(mockIoGood), false);
    EXPECT_NE(imageGood, nullptr);  // The image should not be nullptr

    // Bad IO case
    auto mockIoBad = std::make_unique<MockBasicIo>();
    EXPECT_CALL(*mockIoBad, good()).WillOnce(testing::Return(false));

    auto imageBad = Exiv2::newTiffInstance(std::move(mockIoBad), false);
    EXPECT_EQ(imageBad, nullptr);  // The image should be nullptr
}