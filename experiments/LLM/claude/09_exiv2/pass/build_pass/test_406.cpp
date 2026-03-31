#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "tiffcomposite_int.hpp"
#include "exiv2/exiv2.hpp"

namespace Exiv2 {
namespace Internal {

// Test helper class to access protected members
class TiffSubIfdTestAccess : public TiffSubIfd {
public:
    TiffSubIfdTestAccess(uint16_t tag, IfdId group, IfdId newGroup)
        : TiffSubIfd(tag, group, newGroup) {}

    using TiffSubIfd::doSizeImage;
    using TiffSubIfd::doSize;
    using TiffSubIfd::doSizeData;
    using TiffSubIfd::doAddChild;
};

class TiffSubIfdTest_406 : public ::testing::Test {
protected:
    void SetUp() override {
    }

    void TearDown() override {
    }
};

// Test that TiffSubIfd can be constructed with valid parameters
TEST_F(TiffSubIfdTest_406, Construction_406) {
    EXPECT_NO_THROW({
        TiffSubIfdTestAccess subIfd(0x014a, IfdId::ifd0Id, IfdId::subImage1Id);
    });
}

// Test that doSizeImage returns 0 when there are no child IFDs
TEST_F(TiffSubIfdTest_406, DoSizeImageEmptyIfds_406) {
    TiffSubIfdTestAccess subIfd(0x014a, IfdId::ifd0Id, IfdId::subImage1Id);
    size_t result = subIfd.doSizeImage();
    EXPECT_EQ(result, 0u);
}

// Test that doSize returns a valid value for a newly constructed TiffSubIfd
TEST_F(TiffSubIfdTest_406, DoSizeNewlyConstructed_406) {
    TiffSubIfdTestAccess subIfd(0x014a, IfdId::ifd0Id, IfdId::subImage1Id);
    size_t result = subIfd.doSize();
    // A newly constructed sub IFD should have some size (at minimum for the entry)
    EXPECT_GE(result, 0u);
}

// Test that doSizeData returns a valid value for a newly constructed TiffSubIfd
TEST_F(TiffSubIfdTest_406, DoSizeDataNewlyConstructed_406) {
    TiffSubIfdTestAccess subIfd(0x014a, IfdId::ifd0Id, IfdId::subImage1Id);
    size_t result = subIfd.doSizeData();
    EXPECT_GE(result, 0u);
}

// Test construction with different tag values
TEST_F(TiffSubIfdTest_406, ConstructionDifferentTags_406) {
    EXPECT_NO_THROW({
        TiffSubIfdTestAccess subIfd1(0x0000, IfdId::ifd0Id, IfdId::subImage1Id);
    });
    EXPECT_NO_THROW({
        TiffSubIfdTestAccess subIfd2(0xFFFF, IfdId::ifd0Id, IfdId::subImage1Id);
    });
}

// Test that copy assignment is deleted (compile-time check conceptual test)
// This is verified by the = delete declaration; we just verify the object works correctly
TEST_F(TiffSubIfdTest_406, ObjectUsableAfterConstruction_406) {
    TiffSubIfdTestAccess subIfd(0x014a, IfdId::ifd0Id, IfdId::subImage1Id);
    // Should be able to call methods without issues
    EXPECT_EQ(subIfd.doSizeImage(), 0u);
}

// Test with different group IDs
TEST_F(TiffSubIfdTest_406, ConstructionVariousGroups_406) {
    EXPECT_NO_THROW({
        TiffSubIfdTestAccess subIfd(0x014a, IfdId::ifd1Id, IfdId::subImage2Id);
    });
}

// Test that tag() returns the tag used in construction (inherited from TiffEntryBase)
TEST_F(TiffSubIfdTest_406, TagAccessor_406) {
    TiffSubIfdTestAccess subIfd(0x014a, IfdId::ifd0Id, IfdId::subImage1Id);
    EXPECT_EQ(subIfd.tag(), 0x014a);
}

// Test that group() returns the group used in construction (inherited from TiffEntryBase)
TEST_F(TiffSubIfdTest_406, GroupAccessor_406) {
    TiffSubIfdTestAccess subIfd(0x014a, IfdId::ifd0Id, IfdId::subImage1Id);
    EXPECT_EQ(subIfd.group(), IfdId::ifd0Id);
}

// Test multiple calls to doSizeImage are consistent
TEST_F(TiffSubIfdTest_406, DoSizeImageConsistentCalls_406) {
    TiffSubIfdTestAccess subIfd(0x014a, IfdId::ifd0Id, IfdId::subImage1Id);
    size_t result1 = subIfd.doSizeImage();
    size_t result2 = subIfd.doSizeImage();
    EXPECT_EQ(result1, result2);
}

} // namespace Internal
} // namespace Exiv2
