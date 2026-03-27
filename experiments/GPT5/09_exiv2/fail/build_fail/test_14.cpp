#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "exiv2/slice.hpp"

namespace Exiv2 {
namespace Internal {

class PtrSliceStorageTest : public ::testing::Test {
protected:
    // Setup can go here if needed.
    // For now, no specific setup needed for this simple test case
};

TEST_F(PtrSliceStorageTest, UnsafeAt_ReturnsCorrectElement_14) {
    // Arrange
    int data[] = {1, 2, 3, 4, 5};
    PtrSliceStorage<int*> storage(data, 0, 5);

    // Act
    int& result = storage.unsafeAt(2); // Should return data[2] (which is 3)

    // Assert
    EXPECT_EQ(result, 3);
}

TEST_F(PtrSliceStorageTest, UnsafeAt_ThrowsOutOfBounds_14) {
    // Arrange
    int data[] = {1, 2, 3, 4, 5};
    PtrSliceStorage<int*> storage(data, 0, 5);

    // Act & Assert
    EXPECT_THROW(storage.unsafeAt(10), std::out_of_range);
}

TEST_F(PtrSliceStorageTest, UnsafeAt_EmptySlice_14) {
    // Arrange
    int data[] = {};
    PtrSliceStorage<int*> storage(data, 0, 0);

    // Act & Assert
    EXPECT_THROW(storage.unsafeAt(0), std::out_of_range);
}

TEST_F(PtrSliceStorageTest, UnsafeGetIteratorAt_ReturnsCorrectIterator_14) {
    // Arrange
    int data[] = {1, 2, 3, 4, 5};
    PtrSliceStorage<int*> storage(data, 0, 5);

    // Act
    auto iterator = storage.unsafeGetIteratorAt(3);

    // Assert
    EXPECT_EQ(*iterator, 4);
}

TEST_F(PtrSliceStorageTest, UnsafeGetIteratorAt_ThrowsOutOfBounds_14) {
    // Arrange
    int data[] = {1, 2, 3, 4, 5};
    PtrSliceStorage<int*> storage(data, 0, 5);

    // Act & Assert
    EXPECT_THROW(storage.unsafeGetIteratorAt(10), std::out_of_range);
}

}  // namespace Internal
}  // namespace Exiv2