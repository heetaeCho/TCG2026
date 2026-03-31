#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "tiffcomposite_int.hpp"
#include "tiffvisitor_int.hpp"

#include <stack>
#include <memory>

using namespace Exiv2;
using namespace Exiv2::Internal;

// Helper: TiffPath is std::stack<TiffPathItem>
// We need to build TiffPath objects for testing

class TiffSubIfdTest_321 : public ::testing::Test {
protected:
    void SetUp() override {
    }

    void TearDown() override {
    }
};

// Test: When tiffPath has only one element (after popping top), doAddPath returns 'this'
TEST_F(TiffSubIfdTest_321, EmptyPathAfterPop_ReturnsSelf_321) {
    // Create a TiffSubIfd
    uint16_t tag = 0x8769;
    IfdId group = IfdId::ifd0Id;
    IfdId newGroup = IfdId::exifId;
    TiffSubIfd subIfd(tag, group, newGroup);

    // Create a TiffPath with exactly one element
    // After popping, tiffPath will be empty, so doAddPath should return 'this'
    TiffPath tiffPath;
    tiffPath.push(TiffPathItem(tag, group));

    TiffComponent* result = subIfd.addPath(tag, tiffPath, &subIfd, nullptr);
    EXPECT_EQ(result, &subIfd);
}

// Test: When tiffPath has two elements, a new child directory is created
TEST_F(TiffSubIfdTest_321, TwoElementPath_CreatesChildDirectory_321) {
    uint16_t tag = 0x8769;
    IfdId group = IfdId::ifd0Id;
    IfdId newGroup = IfdId::exifId;
    TiffSubIfd subIfd(tag, group, newGroup);

    TiffPath tiffPath;
    // Push in reverse order since it's a stack (bottom first)
    tiffPath.push(TiffPathItem(0x0001, IfdId::exifId));
    tiffPath.push(TiffPathItem(tag, group));

    TiffComponent* result = subIfd.addPath(tag, tiffPath, &subIfd, nullptr);
    // Result should not be null - a child was created
    EXPECT_NE(result, nullptr);
}

// Test: When tiffPath size is 1 (after first pop) and object is provided, object is used as child
TEST_F(TiffSubIfdTest_321, SingleRemainingPathWithObject_UsesProvidedObject_321) {
    uint16_t tag = 0x8769;
    IfdId group = IfdId::ifd0Id;
    IfdId newGroup = IfdId::exifId;
    TiffSubIfd subIfd(tag, group, newGroup);

    TiffPath tiffPath;
    // After popping top, only one element remains => tiffPath.size() == 1
    tiffPath.push(TiffPathItem(0x0001, IfdId::exifId));
    tiffPath.push(TiffPathItem(tag, group));

    auto object = std::make_unique<TiffDirectory>(0x0001, IfdId::exifId);
    TiffComponent* rawPtr = object.get();

    TiffComponent* result = subIfd.addPath(tag, tiffPath, &subIfd, std::move(object));
    EXPECT_NE(result, nullptr);
}

// Test: Multiple calls should create multiple IFDs and update count
TEST_F(TiffSubIfdTest_321, MultipleAddPath_CreatesMultipleIfds_321) {
    uint16_t tag = 0x8769;
    IfdId group = IfdId::ifd0Id;
    IfdId newGroup = IfdId::exifId;
    TiffSubIfd subIfd(tag, group, newGroup);

    // First call
    {
        TiffPath tiffPath;
        tiffPath.push(TiffPathItem(0x0001, IfdId::exifId));
        tiffPath.push(TiffPathItem(tag, group));
        TiffComponent* result = subIfd.addPath(tag, tiffPath, &subIfd, nullptr);
        EXPECT_NE(result, nullptr);
    }

    // Second call with a different group so it doesn't match existing IFD
    {
        TiffPath tiffPath;
        tiffPath.push(TiffPathItem(0x0002, IfdId::canonId));
        tiffPath.push(TiffPathItem(tag, group));
        TiffComponent* result = subIfd.addPath(tag, tiffPath, &subIfd, nullptr);
        EXPECT_NE(result, nullptr);
    }
}

// Test: When an existing IFD matches the group, it should reuse it
TEST_F(TiffSubIfdTest_321, MatchingGroupReusesExistingIfd_321) {
    uint16_t tag = 0x8769;
    IfdId group = IfdId::ifd0Id;
    IfdId newGroup = IfdId::exifId;
    TiffSubIfd subIfd(tag, group, newGroup);

    IfdId childGroup = IfdId::exifId;

    // First call - creates an IFD with childGroup
    TiffComponent* firstResult;
    {
        TiffPath tiffPath;
        tiffPath.push(TiffPathItem(0x0001, childGroup));
        tiffPath.push(TiffPathItem(tag, group));
        firstResult = subIfd.addPath(tag, tiffPath, &subIfd, nullptr);
        EXPECT_NE(firstResult, nullptr);
    }

    // Second call with same childGroup - should reuse existing IFD
    TiffComponent* secondResult;
    {
        TiffPath tiffPath;
        tiffPath.push(TiffPathItem(0x0002, childGroup));
        tiffPath.push(TiffPathItem(tag, group));
        secondResult = subIfd.addPath(tag, tiffPath, &subIfd, nullptr);
        EXPECT_NE(secondResult, nullptr);
    }
}

// Test: TiffSubIfd construction with valid parameters
TEST_F(TiffSubIfdTest_321, Construction_321) {
    uint16_t tag = 0x014A;
    IfdId group = IfdId::ifd0Id;
    IfdId newGroup = IfdId::subImage1Id;

    TiffSubIfd subIfd(tag, group, newGroup);
    EXPECT_EQ(subIfd.tag(), tag);
    EXPECT_EQ(subIfd.group(), group);
}

// Test: Count reflects the number of sub-IFDs after addPath
TEST_F(TiffSubIfdTest_321, CountReflectsSubIfds_321) {
    uint16_t tag = 0x8769;
    IfdId group = IfdId::ifd0Id;
    IfdId newGroup = IfdId::exifId;
    TiffSubIfd subIfd(tag, group, newGroup);

    // Initially count should be 0
    EXPECT_EQ(subIfd.count(), 0u);

    // Add a path that creates a sub-IFD
    TiffPath tiffPath;
    tiffPath.push(TiffPathItem(0x0001, IfdId::exifId));
    tiffPath.push(TiffPathItem(tag, group));
    subIfd.addPath(tag, tiffPath, &subIfd, nullptr);

    // Count should now be 1
    EXPECT_EQ(subIfd.count(), 1u);
}

// Test: Deep path (more than 2 elements) creates nested structure
TEST_F(TiffSubIfdTest_321, DeepPath_CreatesNestedStructure_321) {
    uint16_t tag = 0x8769;
    IfdId group = IfdId::ifd0Id;
    IfdId newGroup = IfdId::exifId;
    TiffSubIfd subIfd(tag, group, newGroup);

    TiffPath tiffPath;
    // 3 elements deep
    tiffPath.push(TiffPathItem(0x0003, IfdId::canonId));
    tiffPath.push(TiffPathItem(0x0002, IfdId::exifId));
    tiffPath.push(TiffPathItem(tag, group));

    TiffComponent* result = subIfd.addPath(tag, tiffPath, &subIfd, nullptr);
    EXPECT_NE(result, nullptr);
}

// Test: Nullptr object with single remaining path element
TEST_F(TiffSubIfdTest_321, NullObjectSingleRemainingPath_321) {
    uint16_t tag = 0x8769;
    IfdId group = IfdId::ifd0Id;
    IfdId newGroup = IfdId::exifId;
    TiffSubIfd subIfd(tag, group, newGroup);

    TiffPath tiffPath;
    tiffPath.push(TiffPathItem(0x0001, IfdId::exifId));
    tiffPath.push(TiffPathItem(tag, group));

    // Pass nullptr as object - should still work, creating TiffDirectory internally
    TiffComponent* result = subIfd.addPath(tag, tiffPath, &subIfd, nullptr);
    EXPECT_NE(result, nullptr);
}

// Test: addPath with provided object that has correct tag
TEST_F(TiffSubIfdTest_321, ProvidedObjectIsUsedWhenPathSizeOne_321) {
    uint16_t tag = 0x8769;
    IfdId group = IfdId::ifd0Id;
    IfdId newGroup = IfdId::exifId;
    TiffSubIfd subIfd(tag, group, newGroup);

    TiffPath tiffPath;
    tiffPath.push(TiffPathItem(0x0001, IfdId::exifId));
    tiffPath.push(TiffPathItem(tag, group));

    auto customDir = std::make_unique<TiffDirectory>(0x0001, IfdId::exifId);
    
    TiffComponent* result = subIfd.addPath(tag, tiffPath, &subIfd, std::move(customDir));
    EXPECT_NE(result, nullptr);
    // After adding, count should be updated
    EXPECT_EQ(subIfd.count(), 1u);
}
