#include <gtest/gtest.h>
#include <gmock/gmock.h>

// Include necessary headers from exiv2
#include "tiffcomposite_int.hpp"
#include "exiv2/types.hpp"
#include "exiv2/value.hpp"

using namespace Exiv2;
using namespace Exiv2::Internal;

// Since TiffImageEntry inherits from TiffDataEntryBase which inherits from TiffEntryBase
// and ultimately TiffComponent, we need to construct it properly.
// TiffImageEntry typically needs a tag and IfdId for construction.

class TiffImageEntryTest_391 : public ::testing::Test {
protected:
    void SetUp() override {
    }

    void TearDown() override {
    }
};

// Test doSize returns 0 when strips_ is empty (no setStrips called)
TEST_F(TiffImageEntryTest_391, DoSizeReturnsZeroWhenNoStrips_391) {
    // TiffImageEntry constructor typically takes tag and group
    // Tag 0x0111 is StripOffsets, group is IfdId
    TiffImageEntry entry(0x0111, IfdId::ifd0Id);
    
    // size() on TiffComponent should eventually call doSize()
    // When no strips are set, strips_.size() should be 0, so doSize returns 0
    EXPECT_EQ(entry.doSize(), 0u);
}

// Test doSize after setting strips with known size values
TEST_F(TiffImageEntryTest_391, DoSizeReturnsCorrectValueAfterSetStrips_391) {
    TiffImageEntry entry(0x0111, IfdId::ifd0Id);
    
    // Create a Value with strip sizes - using ULongValue
    auto pSize = Exiv2::Value::create(Exiv2::unsignedLong);
    
    // Add some strip size entries
    pSize->read("100");  // one strip of size 100
    
    // Create some dummy data
    const byte data[200] = {0};
    
    entry.setStrips(pSize.get(), data, sizeof(data), 0);
    
    // After setting 1 strip, doSize should return 1 * 4 = 4
    EXPECT_EQ(entry.doSize(), 4u);
}

// Test doSize with multiple strips
TEST_F(TiffImageEntryTest_391, DoSizeWithMultipleStrips_391) {
    TiffImageEntry entry(0x0111, IfdId::ifd0Id);
    
    auto pSize = Exiv2::Value::create(Exiv2::unsignedLong);
    
    // Add multiple strip size entries
    pSize->read("100 200 300");  // three strips
    
    // Create enough data to cover all strips
    std::vector<byte> data(600, 0);
    
    entry.setStrips(pSize.get(), data.data(), data.size(), 0);
    
    // After setting 3 strips, doSize should return 3 * 4 = 12
    EXPECT_EQ(entry.doSize(), 12u);
}

// Test doSize with null pSize value
TEST_F(TiffImageEntryTest_391, SetStripsWithNullSize_391) {
    TiffImageEntry entry(0x0111, IfdId::ifd0Id);
    
    const byte data[100] = {0};
    
    // Setting strips with null size - should handle gracefully
    entry.setStrips(nullptr, data, sizeof(data), 0);
    
    // With null size, strips should remain empty
    EXPECT_EQ(entry.doSize(), 0u);
}

// Test doSize with null data pointer
TEST_F(TiffImageEntryTest_391, SetStripsWithNullData_391) {
    TiffImageEntry entry(0x0111, IfdId::ifd0Id);
    
    auto pSize = Exiv2::Value::create(Exiv2::unsignedLong);
    pSize->read("100");
    
    // Setting strips with null data pointer
    entry.setStrips(pSize.get(), nullptr, 0, 0);
    
    // Behavior depends on implementation - strips may or may not be populated
    // Just verify it doesn't crash and returns a consistent value
    size_t result = entry.doSize();
    EXPECT_EQ(result % 4, 0u);  // Should always be multiple of 4
}

// Test doSize with zero sizeData
TEST_F(TiffImageEntryTest_391, SetStripsWithZeroSizeData_391) {
    TiffImageEntry entry(0x0111, IfdId::ifd0Id);
    
    auto pSize = Exiv2::Value::create(Exiv2::unsignedLong);
    pSize->read("100");
    
    const byte data[1] = {0};
    
    entry.setStrips(pSize.get(), data, 0, 0);
    
    size_t result = entry.doSize();
    EXPECT_EQ(result % 4, 0u);
}

// Test that doSize result is always a multiple of 4
TEST_F(TiffImageEntryTest_391, DoSizeAlwaysMultipleOfFour_391) {
    TiffImageEntry entry(0x0111, IfdId::ifd0Id);
    
    auto pSize = Exiv2::Value::create(Exiv2::unsignedLong);
    pSize->read("50 60 70 80 90");  // 5 strips
    
    std::vector<byte> data(500, 0);
    
    entry.setStrips(pSize.get(), data.data(), data.size(), 0);
    
    size_t result = entry.doSize();
    EXPECT_EQ(result, 20u);  // 5 * 4 = 20
    EXPECT_EQ(result % 4, 0u);
}

// Test with non-zero baseOffset
TEST_F(TiffImageEntryTest_391, SetStripsWithNonZeroBaseOffset_391) {
    TiffImageEntry entry(0x0111, IfdId::ifd0Id);
    
    auto pSize = Exiv2::Value::create(Exiv2::unsignedLong);
    pSize->read("100 200");
    
    std::vector<byte> data(400, 0);
    
    entry.setStrips(pSize.get(), data.data(), data.size(), 100);
    
    // doSize should still be based on number of strips * 4
    EXPECT_EQ(entry.doSize(), 8u);  // 2 * 4 = 8
}

// Test with single strip of size 0
TEST_F(TiffImageEntryTest_391, SetStripsWithZeroSizeStrip_391) {
    TiffImageEntry entry(0x0111, IfdId::ifd0Id);
    
    auto pSize = Exiv2::Value::create(Exiv2::unsignedLong);
    pSize->read("0");
    
    const byte data[1] = {0};
    
    entry.setStrips(pSize.get(), data, sizeof(data), 0);
    
    // Even with a zero-size strip, there's still 1 strip entry
    size_t result = entry.doSize();
    EXPECT_EQ(result, 4u);  // 1 * 4 = 4
}
