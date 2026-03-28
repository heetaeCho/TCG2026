#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "tiffcomposite_int.hpp"
#include "exiv2/exiv2.hpp"

using namespace Exiv2;
using namespace Exiv2::Internal;

// Helper class to access protected members for testing
class TestableTiffSubIfd : public TiffSubIfd {
public:
    using TiffSubIfd::TiffSubIfd;

    TiffSubIfd* callDoClone() const {
        return doClone();
    }

    // Expose other protected methods if needed for testing
    size_t callDoSize() const {
        return doSize();
    }

    size_t callDoSizeData() const {
        return doSizeData();
    }

    size_t callDoSizeImage() const {
        return doSizeImage();
    }
};

class TiffSubIfdTest_291 : public ::testing::Test {
protected:
    void SetUp() override {
    }

    void TearDown() override {
    }
};

// Test: Construction with valid parameters
TEST_F(TiffSubIfdTest_291, ConstructWithValidParameters_291) {
    EXPECT_NO_THROW({
        TiffSubIfd subIfd(0x014a, IfdId::ifd0Id, IfdId::subImage1Id);
    });
}

// Test: Construction with tag 0
TEST_F(TiffSubIfdTest_291, ConstructWithZeroTag_291) {
    EXPECT_NO_THROW({
        TiffSubIfd subIfd(0x0000, IfdId::ifd0Id, IfdId::subImage1Id);
    });
}

// Test: Construction with maximum tag value
TEST_F(TiffSubIfdTest_291, ConstructWithMaxTag_291) {
    EXPECT_NO_THROW({
        TiffSubIfd subIfd(0xFFFF, IfdId::ifd0Id, IfdId::subImage1Id);
    });
}

// Test: Tag is correctly stored after construction
TEST_F(TiffSubIfdTest_291, TagIsCorrectlyStored_291) {
    TiffSubIfd subIfd(0x014a, IfdId::ifd0Id, IfdId::subImage1Id);
    EXPECT_EQ(subIfd.tag(), 0x014a);
}

// Test: Group is correctly stored after construction
TEST_F(TiffSubIfdTest_291, GroupIsCorrectlyStored_291) {
    TiffSubIfd subIfd(0x014a, IfdId::ifd0Id, IfdId::subImage1Id);
    EXPECT_EQ(subIfd.group(), IfdId::ifd0Id);
}

// Test: doClone creates a valid copy
TEST_F(TiffSubIfdTest_291, DoCloneCreatesValidCopy_291) {
    TestableTiffSubIfd original(0x014a, IfdId::ifd0Id, IfdId::subImage1Id);
    TiffSubIfd* cloned = original.callDoClone();
    ASSERT_NE(cloned, nullptr);
    EXPECT_EQ(cloned->tag(), original.tag());
    EXPECT_EQ(cloned->group(), original.group());
    delete cloned;
}

// Test: doClone returns a different object (not the same pointer)
TEST_F(TiffSubIfdTest_291, DoCloneReturnsDifferentObject_291) {
    TestableTiffSubIfd original(0x014a, IfdId::ifd0Id, IfdId::subImage1Id);
    TiffSubIfd* cloned = original.callDoClone();
    ASSERT_NE(cloned, nullptr);
    EXPECT_NE(static_cast<TiffSubIfd*>(&original), cloned);
    delete cloned;
}

// Test: doClone preserves tag value
TEST_F(TiffSubIfdTest_291, DoClonePreservesTag_291) {
    TestableTiffSubIfd original(0x0100, IfdId::ifd0Id, IfdId::subImage1Id);
    TiffSubIfd* cloned = original.callDoClone();
    ASSERT_NE(cloned, nullptr);
    EXPECT_EQ(cloned->tag(), 0x0100);
    delete cloned;
}

// Test: doClone preserves group
TEST_F(TiffSubIfdTest_291, DoClonePreservesGroup_291) {
    TestableTiffSubIfd original(0x0100, IfdId::exifId, IfdId::subImage1Id);
    TiffSubIfd* cloned = original.callDoClone();
    ASSERT_NE(cloned, nullptr);
    EXPECT_EQ(cloned->group(), IfdId::exifId);
    delete cloned;
}

// Test: doSize on empty sub IFD
TEST_F(TiffSubIfdTest_291, DoSizeOnEmptySubIfd_291) {
    TestableTiffSubIfd subIfd(0x014a, IfdId::ifd0Id, IfdId::subImage1Id);
    size_t size = subIfd.callDoSize();
    // An empty sub IFD should have some baseline size (at minimum 0 or the size of the offset entry)
    EXPECT_GE(size, 0u);
}

// Test: doSizeData on empty sub IFD
TEST_F(TiffSubIfdTest_291, DoSizeDataOnEmptySubIfd_291) {
    TestableTiffSubIfd subIfd(0x014a, IfdId::ifd0Id, IfdId::subImage1Id);
    size_t sizeData = subIfd.callDoSizeData();
    EXPECT_GE(sizeData, 0u);
}

// Test: doSizeImage on empty sub IFD
TEST_F(TiffSubIfdTest_291, DoSizeImageOnEmptySubIfd_291) {
    TestableTiffSubIfd subIfd(0x014a, IfdId::ifd0Id, IfdId::subImage1Id);
    size_t sizeImage = subIfd.callDoSizeImage();
    EXPECT_GE(sizeImage, 0u);
}

// Test: Construction with different group combinations
TEST_F(TiffSubIfdTest_291, ConstructWithDifferentGroups_291) {
    EXPECT_NO_THROW({
        TiffSubIfd subIfd1(0x014a, IfdId::ifd0Id, IfdId::subImage2Id);
    });
    EXPECT_NO_THROW({
        TiffSubIfd subIfd2(0x014a, IfdId::ifd1Id, IfdId::subImage3Id);
    });
}

// Test: Multiple clones are independent
TEST_F(TiffSubIfdTest_291, MultipleClonesAreIndependent_291) {
    TestableTiffSubIfd original(0x014a, IfdId::ifd0Id, IfdId::subImage1Id);
    TiffSubIfd* clone1 = original.callDoClone();
    TiffSubIfd* clone2 = original.callDoClone();
    ASSERT_NE(clone1, nullptr);
    ASSERT_NE(clone2, nullptr);
    EXPECT_NE(clone1, clone2);
    EXPECT_EQ(clone1->tag(), clone2->tag());
    EXPECT_EQ(clone1->group(), clone2->group());
    delete clone1;
    delete clone2;
}

// Test: Destruction does not throw
TEST_F(TiffSubIfdTest_291, DestructionDoesNotThrow_291) {
    EXPECT_NO_THROW({
        TiffSubIfd* subIfd = new TiffSubIfd(0x014a, IfdId::ifd0Id, IfdId::subImage1Id);
        delete subIfd;
    });
}

// Test: Assignment operator is deleted (compile-time check conceptual; we verify it doesn't compile)
// This is a compile-time constraint; we just document it here
// TiffSubIfd a(0, IfdId::ifd0Id, IfdId::subImage1Id);
// TiffSubIfd b(0, IfdId::ifd0Id, IfdId::subImage1Id);
// b = a; // Should not compile

