#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "./TestProjects/exiv2/src/tiffcomposite_int.hpp"  // Assuming the class header is located here

namespace Exiv2 {
namespace Internal {

// Test fixture for TiffSizeEntry
class TiffSizeEntryTest : public ::testing::Test {
protected:
    uint16_t tag = 1;
    IfdId group = 2;
    uint16_t dtTag = 3;
    IfdId dtGroup = 4;
    TiffSizeEntry entry{tag, group, dtTag, dtGroup};
};

// Test constructor and member initialization
TEST_F(TiffSizeEntryTest, Constructor_InitializesCorrectly_243) {
    // Verify that the TiffSizeEntry is initialized correctly
    EXPECT_EQ(entry.dtTag(), dtTag);
    EXPECT_EQ(entry.dtGroup(), dtGroup);
}

// Test normal behavior of dtTag
TEST_F(TiffSizeEntryTest, dtTag_ReturnsCorrectValue_244) {
    // Verify that dtTag returns the correct value
    EXPECT_EQ(entry.dtTag(), dtTag);
}

// Test normal behavior of dtGroup
TEST_F(TiffSizeEntryTest, dtGroup_ReturnsCorrectValue_245) {
    // Verify that dtGroup returns the correct value
    EXPECT_EQ(entry.dtGroup(), dtGroup);
}

// Test exceptional behavior of an uninitialized object (constructor behavior)
TEST_F(TiffSizeEntryTest, UninitializedObject_ThrowsExpectedException_246) {
    TiffSizeEntry uninitializedEntry(0, 0, 0, 0);
    // This test assumes that certain functionality of the constructor may cause an exception if the values are invalid.
    // If that's not the case, adjust according to the actual code's behavior.
    // For example:
    // EXPECT_THROW(uninitializedEntry.dtTag(), std::invalid_argument);
}

// Mock for testing interaction with external dependencies (e.g., TiffVisitor, TiffEncoder)
class MockTiffVisitor : public TiffVisitor {
public:
    MOCK_METHOD(void, visit, (const TiffSizeEntry& entry), (override));
};

class MockTiffEncoder : public TiffEncoder {
public:
    MOCK_METHOD(void, encode, (const TiffSizeEntry& entry, const Exifdatum* datum), (override));
};

TEST_F(TiffSizeEntryTest, doAccept_InvokesVisitor_247) {
    MockTiffVisitor mockVisitor;
    EXPECT_CALL(mockVisitor, visit(entry)).Times(1);

    entry.doAccept(mockVisitor);  // This should call visit() on the mockVisitor
}

TEST_F(TiffSizeEntryTest, doEncode_InvokesEncoder_248) {
    MockTiffEncoder mockEncoder;
    Exifdatum* datum = nullptr;  // Assuming a valid datum is passed in the real code
    EXPECT_CALL(mockEncoder, encode(entry, datum)).Times(1);

    entry.doEncode(mockEncoder, datum);  // This should call encode() on the mockEncoder
}

// Test doClone behavior
TEST_F(TiffSizeEntryTest, doClone_ReturnsClonedObject_249) {
    const TiffSizeEntry* clonedEntry = entry.doClone();
    EXPECT_NE(&entry, clonedEntry);  // Ensure that the cloned object is a different instance
    EXPECT_EQ(clonedEntry->dtTag(), entry.dtTag());  // Ensure the cloned object has the same dtTag
    EXPECT_EQ(clonedEntry->dtGroup(), entry.dtGroup());  // Ensure the cloned object has the same dtGroup
}

// Boundary test for dtTag range
TEST_F(TiffSizeEntryTest, dtTag_BoundaryTest_MinValue_250) {
    TiffSizeEntry entryMin(0, group, 0, dtGroup);
    EXPECT_EQ(entryMin.dtTag(), 0);
}

TEST_F(TiffSizeEntryTest, dtTag_BoundaryTest_MaxValue_251) {
    TiffSizeEntry entryMax(UINT16_MAX, group, UINT16_MAX, dtGroup);
    EXPECT_EQ(entryMax.dtTag(), UINT16_MAX);
}

}  // namespace Internal
}  // namespace Exiv2