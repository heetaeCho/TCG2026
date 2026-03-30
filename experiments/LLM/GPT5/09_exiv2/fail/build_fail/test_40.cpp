#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "exiv2/exif.hpp"

using namespace Exiv2;
using ::testing::_;
using ::testing::Return;

class ExifDataTest_40 : public ::testing::Test {
protected:
    ExifData exifData;
};

// Normal Operation Tests

TEST_F(ExifDataTest_40, EndReturnsIterator_40) {
    // Testing that the `end()` method returns a valid iterator
    ASSERT_NE(exifData.end(), exifData.begin());
}

TEST_F(ExifDataTest_40, CountReturnsCorrectNumber_40) {
    // Adding 2 entries to the ExifData
    ExifKey key1("Key1");
    ExifKey key2("Key2");
    Exifdatum datum1(key1, nullptr);
    Exifdatum datum2(key2, nullptr);
    
    exifData.add(datum1);
    exifData.add(datum2);

    // Verify count function returns the correct count of added items
    ASSERT_EQ(exifData.count(), 2);
}

// Boundary Condition Tests

TEST_F(ExifDataTest_40, EmptyReturnsTrue_40) {
    // Verify empty returns true when no items are added
    ASSERT_TRUE(exifData.empty());
}

TEST_F(ExifDataTest_40, EmptyReturnsFalseAfterAdd_40) {
    ExifKey key("Key1");
    Exifdatum datum(key, nullptr);
    
    exifData.add(datum);
    
    // Verify empty returns false after adding an item
    ASSERT_FALSE(exifData.empty());
}

// Exceptional/Error Cases

TEST_F(ExifDataTest_40, EraseOnEmptyDataReturnsEnd_40) {
    // Trying to erase from an empty ExifData
    auto it = exifData.erase(exifData.begin());
    
    // Verify that the iterator returned is the end iterator
    ASSERT_EQ(it, exifData.end());
}

TEST_F(ExifDataTest_40, EraseInvalidIterator_40) {
    ExifKey key("Key1");
    Exifdatum datum(key, nullptr);
    
    exifData.add(datum);
    
    // Trying to erase invalid iterator (outside of range)
    auto it = exifData.erase(exifData.end());
    
    // Verify iterator doesn't go out of bounds
    ASSERT_EQ(it, exifData.end());
}

// Mock external interactions (e.g., callbacks)

class MockExifKey : public ExifKey {
public:
    MOCK_METHOD(std::string, keyName, (), (const, override));
};

TEST_F(ExifDataTest_40, AddExifDatumWithMockKey_40) {
    MockExifKey mockKey;
    EXPECT_CALL(mockKey, keyName()).WillOnce(Return("MockedKey"));

    Exifdatum datum(mockKey, nullptr);
    exifData.add(datum);
    
    // Check if key was added correctly (via mock call)
    ASSERT_EQ(exifData.count(), 1);
}