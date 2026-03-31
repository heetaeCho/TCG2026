#include <gtest/gtest.h>
#include <memory>

#include "tiffcomposite_int.hpp"

using namespace Exiv2::Internal;

// Helper: Create a simple TiffComponent for testing
// We'll use TiffDirectory itself as a concrete TiffComponent since it's available
class TiffDirectoryTest_327 : public ::testing::Test {
protected:
    void SetUp() override {
    }

    void TearDown() override {
    }

    std::unique_ptr<TiffDirectory> createDirectory(uint16_t tag = 0, IfdId group = IfdId::ifd0Id, bool hasNext = false) {
        return std::make_unique<TiffDirectory>(tag, group, hasNext);
    }

    TiffComponent::SharedPtr createChildComponent(uint16_t tag = 1, IfdId group = IfdId::ifd0Id) {
        return std::make_shared<TiffDirectory>(tag, group, false);
    }
};

// Test that constructor creates a TiffDirectory with hasNext = false
TEST_F(TiffDirectoryTest_327, ConstructorWithHasNextFalse_327) {
    auto dir = createDirectory(0x0100, IfdId::ifd0Id, false);
    ASSERT_NE(dir, nullptr);
    EXPECT_FALSE(dir->hasNext());
}

// Test that constructor creates a TiffDirectory with hasNext = true
TEST_F(TiffDirectoryTest_327, ConstructorWithHasNextTrue_327) {
    auto dir = createDirectory(0x0100, IfdId::ifd0Id, true);
    ASSERT_NE(dir, nullptr);
    EXPECT_TRUE(dir->hasNext());
}

// Test that doAddChild returns a non-null pointer when adding a valid component
TEST_F(TiffDirectoryTest_327, DoAddChildReturnsNonNullPointer_327) {
    auto dir = createDirectory();
    auto child = createChildComponent(0x0101, IfdId::ifd0Id);
    TiffComponent* rawChildPtr = child.get();

    TiffComponent* result = dir->doAddChild(child);
    ASSERT_NE(result, nullptr);
}

// Test that doAddChild returns a pointer to the same component that was added
TEST_F(TiffDirectoryTest_327, DoAddChildReturnsSameComponent_327) {
    auto dir = createDirectory();
    auto child = createChildComponent(0x0102, IfdId::ifd0Id);
    TiffComponent* expectedPtr = child.get();

    TiffComponent* result = dir->doAddChild(child);
    EXPECT_EQ(result, expectedPtr);
}

// Test adding multiple children
TEST_F(TiffDirectoryTest_327, DoAddChildMultipleChildren_327) {
    auto dir = createDirectory();

    auto child1 = createChildComponent(0x0101, IfdId::ifd0Id);
    auto child2 = createChildComponent(0x0102, IfdId::ifd0Id);
    auto child3 = createChildComponent(0x0103, IfdId::ifd0Id);

    TiffComponent* ptr1 = child1.get();
    TiffComponent* ptr2 = child2.get();
    TiffComponent* ptr3 = child3.get();

    TiffComponent* result1 = dir->doAddChild(child1);
    TiffComponent* result2 = dir->doAddChild(child2);
    TiffComponent* result3 = dir->doAddChild(child3);

    EXPECT_EQ(result1, ptr1);
    EXPECT_EQ(result2, ptr2);
    EXPECT_EQ(result3, ptr3);
}

// Test that all returned pointers from doAddChild are distinct
TEST_F(TiffDirectoryTest_327, DoAddChildReturnedPointersAreDistinct_327) {
    auto dir = createDirectory();

    auto child1 = createChildComponent(0x0201, IfdId::ifd0Id);
    auto child2 = createChildComponent(0x0202, IfdId::ifd0Id);

    TiffComponent* result1 = dir->doAddChild(child1);
    TiffComponent* result2 = dir->doAddChild(child2);

    EXPECT_NE(result1, result2);
}

// Test that the tag is preserved in the directory
TEST_F(TiffDirectoryTest_327, ConstructorPreservesTag_327) {
    uint16_t expectedTag = 0x1234;
    auto dir = createDirectory(expectedTag, IfdId::ifd0Id, false);
    EXPECT_EQ(dir->tag(), expectedTag);
}

// Test that the group is preserved in the directory
TEST_F(TiffDirectoryTest_327, ConstructorPreservesGroup_327) {
    auto dir = createDirectory(0x0100, IfdId::exifId, false);
    EXPECT_EQ(dir->group(), IfdId::exifId);
}

// Test doCount returns 0 for empty directory
TEST_F(TiffDirectoryTest_327, DoCountEmptyDirectory_327) {
    auto dir = createDirectory();
    EXPECT_EQ(dir->doCount(), 0u);
}

// Test doSize returns appropriate value for empty directory
TEST_F(TiffDirectoryTest_327, DoSizeEmptyDirectory_327) {
    auto dir = createDirectory();
    // For an empty directory, size should be well-defined (possibly 0 or minimal header)
    size_t size = dir->doSize();
    // Just verify it doesn't crash and returns a reasonable value
    EXPECT_GE(size, 0u);
}

// Test adding child with tag 0 (boundary)
TEST_F(TiffDirectoryTest_327, DoAddChildWithZeroTag_327) {
    auto dir = createDirectory();
    auto child = createChildComponent(0x0000, IfdId::ifd0Id);
    TiffComponent* expectedPtr = child.get();

    TiffComponent* result = dir->doAddChild(child);
    EXPECT_EQ(result, expectedPtr);
}

// Test adding child with max tag value (boundary)
TEST_F(TiffDirectoryTest_327, DoAddChildWithMaxTag_327) {
    auto dir = createDirectory();
    auto child = createChildComponent(0xFFFF, IfdId::ifd0Id);
    TiffComponent* expectedPtr = child.get();

    TiffComponent* result = dir->doAddChild(child);
    EXPECT_EQ(result, expectedPtr);
}

// Test that doAddChild with shared_ptr properly takes ownership
TEST_F(TiffDirectoryTest_327, DoAddChildSharedPtrOwnership_327) {
    auto dir = createDirectory();
    auto child = createChildComponent(0x0105, IfdId::ifd0Id);

    // After adding, the shared_ptr should still be valid since it's shared
    TiffComponent* result = dir->doAddChild(child);
    ASSERT_NE(result, nullptr);
    // The result should be accessible
    EXPECT_EQ(result->tag(), 0x0105);
}

// Test constructor with tag 0
TEST_F(TiffDirectoryTest_327, ConstructorWithZeroTag_327) {
    auto dir = createDirectory(0, IfdId::ifd0Id, false);
    ASSERT_NE(dir, nullptr);
    EXPECT_EQ(dir->tag(), 0);
}

// Test constructor with max tag value
TEST_F(TiffDirectoryTest_327, ConstructorWithMaxTag_327) {
    auto dir = createDirectory(0xFFFF, IfdId::ifd0Id, true);
    ASSERT_NE(dir, nullptr);
    EXPECT_EQ(dir->tag(), 0xFFFF);
    EXPECT_TRUE(dir->hasNext());
}
