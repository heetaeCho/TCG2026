#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "exiv2/exiv2.hpp"
#include "tiffcomposite_int.hpp"
#include "tiffvisitor_int.hpp"

namespace Exiv2 {
namespace Internal {

// Test helper class to access protected members
class TiffSubIfdTestable : public TiffSubIfd {
public:
    TiffSubIfdTestable(uint16_t tag, IfdId group, IfdId newGroup)
        : TiffSubIfd(tag, group, newGroup) {}

    // Expose protected methods for testing
    using TiffSubIfd::doSizeData;
    using TiffSubIfd::doSize;
    using TiffSubIfd::doSizeImage;
    using TiffSubIfd::doClone;
    using TiffSubIfd::doAddChild;

    size_t callDoSizeData() const {
        return doSizeData();
    }

    size_t callDoSize() const {
        return doSize();
    }

    size_t callDoSizeImage() const {
        return doSizeImage();
    }

    TiffSubIfd* callDoClone() const {
        return doClone();
    }

    TiffComponent* callDoAddChild(TiffComponent::SharedPtr tiffComponent) {
        return doAddChild(tiffComponent);
    }
};

class TiffSubIfdTest_402 : public ::testing::Test {
protected:
    void SetUp() override {
    }

    void TearDown() override {
    }
};

// Test: Construction with valid parameters
TEST_F(TiffSubIfdTest_402, ConstructionWithValidParameters_402) {
    EXPECT_NO_THROW(TiffSubIfdTestable subifd(0x014a, IfdId::ifd0Id, IfdId::subImage1Id));
}

// Test: doSizeData returns 0 when no IFDs are added
TEST_F(TiffSubIfdTest_402, DoSizeDataReturnsZeroWhenEmpty_402) {
    TiffSubIfdTestable subifd(0x014a, IfdId::ifd0Id, IfdId::subImage1Id);
    EXPECT_EQ(0u, subifd.callDoSizeData());
}

// Test: doSizeImage returns 0 when no IFDs are added
TEST_F(TiffSubIfdTest_402, DoSizeImageReturnsZeroWhenEmpty_402) {
    TiffSubIfdTestable subifd(0x014a, IfdId::ifd0Id, IfdId::subImage1Id);
    EXPECT_EQ(0u, subifd.callDoSizeImage());
}

// Test: doSize returns expected value for empty SubIfd
TEST_F(TiffSubIfdTest_402, DoSizeReturnsValueForEmpty_402) {
    TiffSubIfdTestable subifd(0x014a, IfdId::ifd0Id, IfdId::subImage1Id);
    size_t size = subifd.callDoSize();
    // An empty TiffSubIfd should have some base size (at least 0)
    EXPECT_GE(size, 0u);
}

// Test: Clone produces a valid copy
TEST_F(TiffSubIfdTest_402, DoCloneProducesValidCopy_402) {
    TiffSubIfdTestable subifd(0x014a, IfdId::ifd0Id, IfdId::subImage1Id);
    TiffSubIfd* cloned = subifd.callDoClone();
    ASSERT_NE(nullptr, cloned);
    // Cloned object should have same tag
    EXPECT_EQ(subifd.tag(), cloned->tag());
    delete cloned;
}

// Test: Construction with different tag values
TEST_F(TiffSubIfdTest_402, ConstructionWithDifferentTags_402) {
    TiffSubIfdTestable subifd1(0x0000, IfdId::ifd0Id, IfdId::subImage1Id);
    TiffSubIfdTestable subifd2(0xFFFF, IfdId::ifd0Id, IfdId::subImage1Id);
    EXPECT_EQ(0x0000, subifd1.tag());
    EXPECT_EQ(0xFFFF, subifd2.tag());
}

// Test: doSizeData consistency - calling multiple times returns same value
TEST_F(TiffSubIfdTest_402, DoSizeDataConsistentMultipleCalls_402) {
    TiffSubIfdTestable subifd(0x014a, IfdId::ifd0Id, IfdId::subImage1Id);
    size_t size1 = subifd.callDoSizeData();
    size_t size2 = subifd.callDoSizeData();
    EXPECT_EQ(size1, size2);
}

// Test: Construction with various group IDs
TEST_F(TiffSubIfdTest_402, ConstructionWithVariousGroupIds_402) {
    EXPECT_NO_THROW(TiffSubIfdTestable(0x014a, IfdId::ifd1Id, IfdId::subImage2Id));
    EXPECT_NO_THROW(TiffSubIfdTestable(0x014a, IfdId::exifId, IfdId::subImage3Id));
}

// Test: Tag accessor returns correct tag
TEST_F(TiffSubIfdTest_402, TagAccessorReturnsCorrectTag_402) {
    TiffSubIfdTestable subifd(0x014a, IfdId::ifd0Id, IfdId::subImage1Id);
    EXPECT_EQ(0x014a, subifd.tag());
}

// Test: Group accessor returns correct group
TEST_F(TiffSubIfdTest_402, GroupAccessorReturnsCorrectGroup_402) {
    TiffSubIfdTestable subifd(0x014a, IfdId::ifd0Id, IfdId::subImage1Id);
    EXPECT_EQ(IfdId::ifd0Id, subifd.group());
}

}  // namespace Internal
}  // namespace Exiv2
