#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "tiffcomposite_int.hpp"
#include "tiffvisitor_int.hpp"

namespace Exiv2 {
namespace Internal {

class MockTiffVisitor : public TiffVisitor {
public:
    MOCK_METHOD(void, visitImageEntry, (TiffImageEntry*), (override));
};

class TiffImageEntryTest : public ::testing::Test {
protected:
    TiffImageEntry imageEntry;
    MockTiffVisitor visitor;
};

// TEST_ID is 340
TEST_F(TiffImageEntryTest, AcceptsVisitor_340) {
    // Arrange: Prepare the mock for the visitImageEntry function
    EXPECT_CALL(visitor, visitImageEntry(&imageEntry)).Times(1);

    // Act: Call doAccept with the mock visitor
    imageEntry.doAccept(visitor);

    // Assert: Verify that the visitor's visitImageEntry method was called
}

// TEST_ID is 341
TEST_F(TiffImageEntryTest, SetStrips_340) {
    // Arrange
    const Value* pSize = nullptr;
    const byte* pData = nullptr;
    size_t sizeData = 0;
    size_t baseOffset = 0;
    
    // No expectations, just verify no crash or errors during this method call
    EXPECT_NO_THROW(imageEntry.setStrips(pSize, pData, sizeData, baseOffset));
}

// TEST_ID is 342
TEST_F(TiffImageEntryTest, DoEncode_340) {
    // Arrange
    TiffEncoder encoder;
    const Exifdatum* datum = nullptr;

    // No expectations, just verify no crash or errors during this method call
    EXPECT_NO_THROW(imageEntry.doEncode(encoder, datum));
}

// TEST_ID is 343
TEST_F(TiffImageEntryTest, DoWrite_340) {
    // Arrange
    IoWrapper ioWrapper;
    ByteOrder byteOrder = ByteOrder::LittleEndian;
    size_t offset = 0;
    size_t valueIdx = 0;
    size_t dataIdx = 0;
    size_t imageIdx = 0;

    // No expectations, just verify no crash or errors during this method call
    EXPECT_NO_THROW(imageEntry.doWrite(ioWrapper, byteOrder, offset, valueIdx, dataIdx, imageIdx));
}

// TEST_ID is 344
TEST_F(TiffImageEntryTest, DoSize_340) {
    // Arrange & Act
    size_t result = imageEntry.doSize();

    // Assert
    EXPECT_GT(result, 0); // Assuming non-zero size
}

// TEST_ID is 345
TEST_F(TiffImageEntryTest, DoSizeData_340) {
    // Arrange & Act
    size_t result = imageEntry.doSizeData();

    // Assert
    EXPECT_GT(result, 0); // Assuming non-zero size
}

// TEST_ID is 346
TEST_F(TiffImageEntryTest, DoSizeImage_340) {
    // Arrange & Act
    size_t result = imageEntry.doSizeImage();

    // Assert
    EXPECT_GT(result, 0); // Assuming non-zero size
}

} // namespace Internal
} // namespace Exiv2