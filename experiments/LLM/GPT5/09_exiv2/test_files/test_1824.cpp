#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <cstring>

// Assuming Exiv2::Photoshop and required headers are already included
namespace Exiv2 {
    // Mock class to mimic the `Photoshop` class interface
    class PhotoshopMock {
    public:
        MOCK_METHOD(bool, isIrb, (const byte* pPsData), (const));
    };
}

// TEST CASE 1: Normal Operation - Check if function returns true for valid IRB data
TEST_F(PhotoshopTest_1824, ValidIrbData_1824) {
    const byte validIrb[] = {0x01, 0x23, 0x45, 0x67}; // example valid IRB data
    EXPECT_TRUE(Exiv2::Photoshop::isIrb(validIrb)); // Replace with actual check
}

// TEST CASE 2: Normal Operation - Check if function returns false for null input
TEST_F(PhotoshopTest_1825, NullDataPointer_1825) {
    EXPECT_FALSE(Exiv2::Photoshop::isIrb(nullptr)); // Check for null input
}

// TEST CASE 3: Normal Operation - Check if function returns false for data that does not match known IRB identifiers
TEST_F(PhotoshopTest_1826, InvalidIrbData_1826) {
    const byte invalidIrb[] = {0xFF, 0xFF, 0xFF, 0xFF}; // example invalid IRB data
    EXPECT_FALSE(Exiv2::Photoshop::isIrb(invalidIrb)); // Should not match any valid IRB identifier
}

// TEST CASE 4: Boundary Condition - Check with empty array (0 length)
TEST_F(PhotoshopTest_1827, EmptyArray_1827) {
    const byte emptyData[] = {}; // empty array
    EXPECT_FALSE(Exiv2::Photoshop::isIrb(emptyData)); // Should return false for an empty array
}

// TEST CASE 5: Boundary Condition - Check with small but valid IRB data
TEST_F(PhotoshopTest_1828, SmallValidData_1828) {
    const byte validSmallIrb[] = {0x01, 0x23, 0x45, 0x67}; // same valid IRB data
    EXPECT_TRUE(Exiv2::Photoshop::isIrb(validSmallIrb)); // Check if small data matches valid IRB
}

// TEST CASE 6: Exceptional Case - Check for non-zero pointer but no IRB match
TEST_F(PhotoshopTest_1829, NonMatchingData_1829) {
    const byte nonMatchingData[] = {0xDE, 0xAD, 0xBE, 0xEF}; // Some non-matching data
    EXPECT_FALSE(Exiv2::Photoshop::isIrb(nonMatchingData)); // Should return false since the data does not match any IRB identifier
}