#include <gtest/gtest.h>
#include <memory>

// Include the necessary headers from the exiv2 project
#include "tiffcomposite_int.hpp"
#include "exiv2/exiv2.hpp"

namespace Exiv2 {
namespace Internal {

// Helper class to access protected doClone method for testing
class TiffEntryTestAccess : public TiffEntry {
public:
    using TiffEntry::TiffEntry;
    
    TiffEntry* callDoClone() const {
        return doClone();
    }
};

class TiffEntryTest_286 : public ::testing::Test {
protected:
    void SetUp() override {
    }

    void TearDown() override {
    }
};

// Test that doClone returns a non-null pointer
TEST_F(TiffEntryTest_286, DoCloneReturnsNonNull_286) {
    // Create a TiffEntry with some tag and group
    TiffEntry entry(0x0100, IfdId::ifd0Id);
    TiffEntry* clone = entry.clone();
    ASSERT_NE(clone, nullptr);
    delete clone;
}

// Test that doClone returns a different object (not the same pointer)
TEST_F(TiffEntryTest_286, DoCloneReturnsDifferentObject_286) {
    TiffEntry entry(0x0100, IfdId::ifd0Id);
    TiffEntry* clone = entry.clone();
    ASSERT_NE(clone, nullptr);
    EXPECT_NE(static_cast<void*>(clone), static_cast<void*>(&entry));
    delete clone;
}

// Test that cloned object preserves tag value
TEST_F(TiffEntryTest_286, DoClonePreservesTag_286) {
    const uint16_t testTag = 0x0110;
    TiffEntry entry(testTag, IfdId::ifd0Id);
    TiffEntry* clone = entry.clone();
    ASSERT_NE(clone, nullptr);
    EXPECT_EQ(clone->tag(), testTag);
    delete clone;
}

// Test that cloned object preserves group
TEST_F(TiffEntryTest_286, DoClonePreservesGroup_286) {
    TiffEntry entry(0x0100, IfdId::ifd1Id);
    TiffEntry* clone = entry.clone();
    ASSERT_NE(clone, nullptr);
    EXPECT_EQ(clone->group(), IfdId::ifd1Id);
    delete clone;
}

// Test cloning with different tag values (boundary: tag = 0)
TEST_F(TiffEntryTest_286, DoCloneWithZeroTag_286) {
    TiffEntry entry(0x0000, IfdId::ifd0Id);
    TiffEntry* clone = entry.clone();
    ASSERT_NE(clone, nullptr);
    EXPECT_EQ(clone->tag(), 0x0000);
    delete clone;
}

// Test cloning with maximum tag value
TEST_F(TiffEntryTest_286, DoCloneWithMaxTag_286) {
    TiffEntry entry(0xFFFF, IfdId::ifd0Id);
    TiffEntry* clone = entry.clone();
    ASSERT_NE(clone, nullptr);
    EXPECT_EQ(clone->tag(), 0xFFFF);
    delete clone;
}

// Test that multiple clones are independent
TEST_F(TiffEntryTest_286, MultipleDoCloneReturnsIndependentObjects_286) {
    TiffEntry entry(0x0100, IfdId::ifd0Id);
    TiffEntry* clone1 = entry.clone();
    TiffEntry* clone2 = entry.clone();
    ASSERT_NE(clone1, nullptr);
    ASSERT_NE(clone2, nullptr);
    EXPECT_NE(clone1, clone2);
    EXPECT_EQ(clone1->tag(), clone2->tag());
    EXPECT_EQ(clone1->group(), clone2->group());
    delete clone1;
    delete clone2;
}

// Test cloning with exifIfd group
TEST_F(TiffEntryTest_286, DoCloneWithExifIfdGroup_286) {
    TiffEntry entry(0x829A, IfdId::exifId);
    TiffEntry* clone = entry.clone();
    ASSERT_NE(clone, nullptr);
    EXPECT_EQ(clone->tag(), 0x829A);
    EXPECT_EQ(clone->group(), IfdId::exifId);
    delete clone;
}

}  // namespace Internal
}  // namespace Exiv2
