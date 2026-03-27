#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "exiv2/slice.hpp"

namespace Exiv2 { namespace Internal {

class ContainerStorageTest : public ::testing::Test {
protected:
    // Mocking a container for testing
    std::vector<int> testData = {1, 2, 3, 4, 5};
    ContainerStorage<std::vector<int>> containerStorage = ContainerStorage<std::vector<int>>(testData, 0, testData.size());
};

// Test for normal operation
TEST_F(ContainerStorageTest, UnsafeAtReturnsCorrectElement_12) {
    // Testing that the function `unsafeAt` returns the correct element for a given index
    EXPECT_EQ(containerStorage.unsafeAt(0), 1);
    EXPECT_EQ(containerStorage.unsafeAt(2), 3);
    EXPECT_EQ(containerStorage.unsafeAt(4), 5);
}

// Test for boundary conditions (checking first and last index)
TEST_F(ContainerStorageTest, UnsafeAtBoundaryConditions_12) {
    // Test first index
    EXPECT_EQ(containerStorage.unsafeAt(0), 1);
    
    // Test last index
    EXPECT_EQ(containerStorage.unsafeAt(4), 5);
    
    // Out of range behavior (should not compile as no out-of-bounds check exists in `unsafeAt`)
    // EXPECT_THROW(containerStorage.unsafeAt(5), std::out_of_range);
}

// Test for exceptional cases (trying to access an invalid index)
// Note: As mentioned, unsafeAt does not have internal bounds checking, so this part would generally require modifications
TEST_F(ContainerStorageTest, UnsafeAtOutOfBounds_12) {
    // There should be no exception, unsafeAt will return whatever is at that index in the data structure
    // Since unsafeAt does not throw, we will assert that an out-of-bounds index will not crash the program
    EXPECT_EQ(containerStorage.unsafeAt(10), 0); // This is expected behavior, no exception, returns default value
}

// Test for verification of interaction
TEST_F(ContainerStorageTest, UnsafeGetIteratorAtReturnsIterator_12) {
    // Mocking a scenario for checking unsafeGetIteratorAt if necessary
    auto iterator = containerStorage.unsafeGetIteratorAt(2);
    EXPECT_EQ(*iterator, 3); // It should return the element at index 2, which is 3
}

} }  // namespace Exiv2::Internal