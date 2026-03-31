#include <gtest/gtest.h>
#include <vector>
#include <string>
#include <stdexcept>

// Include the header under test
#include "exiv2/slice.hpp"

// Test fixture for ContainerStorage
class ContainerStorageTest_12 : public ::testing::Test {
protected:
    void SetUp() override {
        intVec = {10, 20, 30, 40, 50};
        strVec = {"alpha", "beta", "gamma", "delta"};
    }

    std::vector<int> intVec;
    std::vector<std::string> strVec;
};

// Test that unsafeAt returns the correct element at index 0
TEST_F(ContainerStorageTest_12, UnsafeAtReturnsFirstElement_12) {
    Exiv2::Internal::ContainerStorage<std::vector<int>> storage(intVec, 0, intVec.size());
    EXPECT_EQ(storage.unsafeAt(0), 10);
}

// Test that unsafeAt returns the correct element at a middle index
TEST_F(ContainerStorageTest_12, UnsafeAtReturnsMiddleElement_12) {
    Exiv2::Internal::ContainerStorage<std::vector<int>> storage(intVec, 0, intVec.size());
    EXPECT_EQ(storage.unsafeAt(2), 30);
}

// Test that unsafeAt returns the correct element at the last valid index
TEST_F(ContainerStorageTest_12, UnsafeAtReturnsLastElement_12) {
    Exiv2::Internal::ContainerStorage<std::vector<int>> storage(intVec, 0, intVec.size());
    EXPECT_EQ(storage.unsafeAt(4), 50);
}

// Test that unsafeAt throws std::out_of_range for an out-of-bounds index
TEST_F(ContainerStorageTest_12, UnsafeAtThrowsOnOutOfBounds_12) {
    Exiv2::Internal::ContainerStorage<std::vector<int>> storage(intVec, 0, intVec.size());
    EXPECT_THROW(storage.unsafeAt(5), std::out_of_range);
}

// Test that unsafeAt throws for a very large index
TEST_F(ContainerStorageTest_12, UnsafeAtThrowsOnVeryLargeIndex_12) {
    Exiv2::Internal::ContainerStorage<std::vector<int>> storage(intVec, 0, intVec.size());
    EXPECT_THROW(storage.unsafeAt(1000), std::out_of_range);
}

// Test unsafeAt with string vector
TEST_F(ContainerStorageTest_12, UnsafeAtWorksWithStringVector_12) {
    Exiv2::Internal::ContainerStorage<std::vector<std::string>> storage(strVec, 0, strVec.size());
    EXPECT_EQ(storage.unsafeAt(0), "alpha");
    EXPECT_EQ(storage.unsafeAt(1), "beta");
    EXPECT_EQ(storage.unsafeAt(2), "gamma");
    EXPECT_EQ(storage.unsafeAt(3), "delta");
}

// Test that unsafeAt reflects changes to the underlying container
TEST_F(ContainerStorageTest_12, UnsafeAtReflectsContainerModifications_12) {
    Exiv2::Internal::ContainerStorage<std::vector<int>> storage(intVec, 0, intVec.size());
    intVec[2] = 999;
    EXPECT_EQ(storage.unsafeAt(2), 999);
}

// Test const correctness - unsafeAt on const storage
TEST_F(ContainerStorageTest_12, UnsafeAtWorksOnConstStorage_12) {
    const Exiv2::Internal::ContainerStorage<std::vector<int>> storage(intVec, 0, intVec.size());
    EXPECT_EQ(storage.unsafeAt(0), 10);
    EXPECT_EQ(storage.unsafeAt(4), 50);
}

// Test with empty container - any access should throw
TEST_F(ContainerStorageTest_12, UnsafeAtThrowsOnEmptyContainer_12) {
    std::vector<int> emptyVec;
    Exiv2::Internal::ContainerStorage<std::vector<int>> storage(emptyVec, 0, 0);
    EXPECT_THROW(storage.unsafeAt(0), std::out_of_range);
}

// Test with single element container
TEST_F(ContainerStorageTest_12, UnsafeAtSingleElementContainer_12) {
    std::vector<int> singleVec = {42};
    Exiv2::Internal::ContainerStorage<std::vector<int>> storage(singleVec, 0, singleVec.size());
    EXPECT_EQ(storage.unsafeAt(0), 42);
    EXPECT_THROW(storage.unsafeAt(1), std::out_of_range);
}

// Test that storage holds a reference to the original container
TEST_F(ContainerStorageTest_12, StorageHoldsReferenceToOriginal_12) {
    Exiv2::Internal::ContainerStorage<std::vector<int>> storage(intVec, 0, intVec.size());
    EXPECT_EQ(storage.unsafeAt(0), 10);
    intVec[0] = 100;
    EXPECT_EQ(storage.unsafeAt(0), 100);
}

// Test construction with non-zero begin parameter
TEST_F(ContainerStorageTest_12, ConstructionWithNonZeroBegin_12) {
    Exiv2::Internal::ContainerStorage<std::vector<int>> storage(intVec, 2, intVec.size());
    // unsafeAt accesses data_.at(index), so index 0 should still be the first element of the vector
    EXPECT_EQ(storage.unsafeAt(0), 10);
}

// Test unsafeAt iterates through all elements correctly
TEST_F(ContainerStorageTest_12, UnsafeAtAllElements_12) {
    Exiv2::Internal::ContainerStorage<std::vector<int>> storage(intVec, 0, intVec.size());
    for (size_t i = 0; i < intVec.size(); ++i) {
        EXPECT_EQ(storage.unsafeAt(i), intVec[i]);
    }
}
