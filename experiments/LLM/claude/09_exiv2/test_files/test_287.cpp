#include <gtest/gtest.h>
#include <gmock/gmock.h>

// Include necessary exiv2 headers
#include "tiffcomposite_int.hpp"
#include "exiv2/exiv2.hpp"

using namespace Exiv2;
using namespace Exiv2::Internal;

class TiffDataEntryTest_287 : public ::testing::Test {
protected:
    void SetUp() override {
    }

    void TearDown() override {
    }
};

// Test that doClone returns a non-null pointer (clone of the object)
TEST_F(TiffDataEntryTest_287, DoCloneReturnsNonNull_287) {
    // TiffDataEntry inherits from TiffDataEntryBase which likely needs a tag and group
    // Based on exiv2 conventions, construct with a tag and group id
    TiffDataEntry entry(0x0111, IfdId::ifd0Id);
    TiffDataEntry* clone = entry.doClone();
    ASSERT_NE(clone, nullptr);
    delete clone;
}

// Test that clone is a different object than original
TEST_F(TiffDataEntryTest_287, DoCloneReturnsDifferentObject_287) {
    TiffDataEntry entry(0x0111, IfdId::ifd0Id);
    TiffDataEntry* clone = entry.doClone();
    ASSERT_NE(clone, nullptr);
    EXPECT_NE(clone, &entry);
    delete clone;
}

// Test setStrips with null pSize parameter
TEST_F(TiffDataEntryTest_287, SetStripsWithNullSize_287) {
    TiffDataEntry entry(0x0111, IfdId::ifd0Id);
    const byte data[] = {0x01, 0x02, 0x03, 0x04};
    // Should handle null pSize gracefully
    EXPECT_NO_THROW(entry.setStrips(nullptr, data, sizeof(data), 0));
}

// Test setStrips with null data pointer
TEST_F(TiffDataEntryTest_287, SetStripsWithNullData_287) {
    TiffDataEntry entry(0x0111, IfdId::ifd0Id);
    EXPECT_NO_THROW(entry.setStrips(nullptr, nullptr, 0, 0));
}

// Test setStrips with zero size data
TEST_F(TiffDataEntryTest_287, SetStripsWithZeroSizeData_287) {
    TiffDataEntry entry(0x0111, IfdId::ifd0Id);
    const byte data[] = {0x00};
    EXPECT_NO_THROW(entry.setStrips(nullptr, data, 0, 0));
}

// Test setStrips with valid data and size value
TEST_F(TiffDataEntryTest_287, SetStripsWithValidData_287) {
    TiffDataEntry entry(0x0111, IfdId::ifd0Id);
    const byte data[] = {0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08};

    // Create a Value object to represent strip sizes
    auto pSize = Value::create(unsignedLong);
    pSize->read("4");

    EXPECT_NO_THROW(entry.setStrips(pSize.get(), data, sizeof(data), 0));
}

// Test doSizeData after default construction (no data set)
TEST_F(TiffDataEntryTest_287, DoCloneAfterSetStrips_287) {
    TiffDataEntry entry(0x0111, IfdId::ifd0Id);
    const byte data[] = {0x01, 0x02, 0x03, 0x04};

    auto pSize = Value::create(unsignedLong);
    pSize->read("4");

    entry.setStrips(pSize.get(), data, sizeof(data), 0);

    TiffDataEntry* clone = entry.doClone();
    ASSERT_NE(clone, nullptr);
    delete clone;
}

// Test setStrips with non-zero base offset
TEST_F(TiffDataEntryTest_287, SetStripsWithBaseOffset_287) {
    TiffDataEntry entry(0x0111, IfdId::ifd0Id);
    const byte data[] = {0x01, 0x02, 0x03, 0x04, 0x05, 0x06};

    auto pSize = Value::create(unsignedLong);
    pSize->read("3");

    EXPECT_NO_THROW(entry.setStrips(pSize.get(), data, sizeof(data), 100));
}

// Test construction with different tag values
TEST_F(TiffDataEntryTest_287, ConstructionWithDifferentTags_287) {
    TiffDataEntry entry1(0x0111, IfdId::ifd0Id);  // StripOffsets
    TiffDataEntry entry2(0x0201, IfdId::ifd0Id);  // JPEGInterchangeFormat
    
    TiffDataEntry* clone1 = entry1.doClone();
    TiffDataEntry* clone2 = entry2.doClone();
    
    ASSERT_NE(clone1, nullptr);
    ASSERT_NE(clone2, nullptr);
    
    delete clone1;
    delete clone2;
}
