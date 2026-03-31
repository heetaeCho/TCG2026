#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "tiffvisitor_int.hpp"
#include "tiffcomposite_int.hpp"
#include "tiffimage_int.hpp"

using namespace Exiv2;
using namespace Exiv2::Internal;

// Test fixture for TiffCopier tests
class TiffCopierTest_1646 : public ::testing::Test {
protected:
    void SetUp() override {
    }

    void TearDown() override {
    }
};

// Test that TiffCopier can be constructed with valid parameters
TEST_F(TiffCopierTest_1646, ConstructWithValidParams_1646) {
    TiffDirectory root(0, IfdId::ifd0Id);
    PrimaryGroups primaryGroups;
    
    EXPECT_NO_THROW({
        TiffCopier copier(&root, 0, nullptr, primaryGroups);
    });
}

// Test that TiffCopier can be constructed with nullptr root
TEST_F(TiffCopierTest_1646, ConstructWithNullRoot_1646) {
    PrimaryGroups primaryGroups;
    
    EXPECT_NO_THROW({
        TiffCopier copier(nullptr, 0, nullptr, primaryGroups);
    });
}

// Test that TiffCopier can be constructed with empty PrimaryGroups
TEST_F(TiffCopierTest_1646, ConstructWithEmptyPrimaryGroups_1646) {
    TiffDirectory root(0, IfdId::ifd0Id);
    PrimaryGroups primaryGroups;
    
    EXPECT_NO_THROW({
        TiffCopier copier(&root, 0, nullptr, std::move(primaryGroups));
    });
}

// Test visitSubIfd with a valid TiffSubIfd object
TEST_F(TiffCopierTest_1646, VisitSubIfdCallsCopyObject_1646) {
    TiffDirectory root(0, IfdId::ifd0Id);
    PrimaryGroups primaryGroups;
    TiffCopier copier(&root, 0, nullptr, primaryGroups);
    
    TiffSubIfd subIfd(0x014a, IfdId::ifd0Id, IfdId::subImage1Id);
    
    // visitSubIfd should call copyObject internally - this should not crash
    EXPECT_NO_THROW({
        copier.visitSubIfd(&subIfd);
    });
}

// Test visitDirectory does not throw
TEST_F(TiffCopierTest_1646, VisitDirectoryNoThrow_1646) {
    TiffDirectory root(0, IfdId::ifd0Id);
    PrimaryGroups primaryGroups;
    TiffCopier copier(&root, 0, nullptr, primaryGroups);
    
    TiffDirectory dir(0, IfdId::ifd0Id);
    
    EXPECT_NO_THROW({
        copier.visitDirectory(&dir);
    });
}

// Test visitEntry with a valid TiffEntry object
TEST_F(TiffCopierTest_1646, VisitEntryNoThrow_1646) {
    TiffDirectory root(0, IfdId::ifd0Id);
    PrimaryGroups primaryGroups;
    TiffCopier copier(&root, 0, nullptr, primaryGroups);
    
    TiffEntry entry(0x0100, IfdId::ifd0Id);
    
    EXPECT_NO_THROW({
        copier.visitEntry(&entry);
    });
}

// Test visitBinaryElement with a valid object
TEST_F(TiffCopierTest_1646, VisitBinaryElementNoThrow_1646) {
    TiffDirectory root(0, IfdId::ifd0Id);
    PrimaryGroups primaryGroups;
    TiffCopier copier(&root, 0, nullptr, primaryGroups);
    
    TiffBinaryElement elem(0x0001, IfdId::ifd0Id);
    
    EXPECT_NO_THROW({
        copier.visitBinaryElement(&elem);
    });
}

// Test that visitSubIfd with different tag values works
TEST_F(TiffCopierTest_1646, VisitSubIfdDifferentTags_1646) {
    TiffDirectory root(0, IfdId::ifd0Id);
    PrimaryGroups primaryGroups;
    TiffCopier copier(&root, 0, nullptr, primaryGroups);
    
    TiffSubIfd subIfd1(0x014a, IfdId::ifd0Id, IfdId::subImage1Id);
    TiffSubIfd subIfd2(0x8769, IfdId::ifd0Id, IfdId::exifId);
    
    EXPECT_NO_THROW({
        copier.visitSubIfd(&subIfd1);
        copier.visitSubIfd(&subIfd2);
    });
}

// Test constructing TiffCopier with non-zero root value
TEST_F(TiffCopierTest_1646, ConstructWithNonZeroRoot_1646) {
    TiffDirectory root(0, IfdId::ifd0Id);
    PrimaryGroups primaryGroups;
    
    EXPECT_NO_THROW({
        TiffCopier copier(&root, 42, nullptr, primaryGroups);
    });
}

// Test that multiple visit calls on same copier don't cause issues
TEST_F(TiffCopierTest_1646, MultipleVisitCallsOnSameCopier_1646) {
    TiffDirectory root(0, IfdId::ifd0Id);
    PrimaryGroups primaryGroups;
    TiffCopier copier(&root, 0, nullptr, primaryGroups);
    
    TiffSubIfd subIfd(0x014a, IfdId::ifd0Id, IfdId::subImage1Id);
    TiffEntry entry(0x0100, IfdId::ifd0Id);
    TiffDirectory dir(0, IfdId::ifd1Id);
    
    EXPECT_NO_THROW({
        copier.visitDirectory(&dir);
        copier.visitSubIfd(&subIfd);
        copier.visitEntry(&entry);
    });
}

// Test copyObject with a TiffSubIfd as TiffComponent
TEST_F(TiffCopierTest_1646, CopyObjectWithSubIfd_1646) {
    TiffDirectory root(0, IfdId::ifd0Id);
    PrimaryGroups primaryGroups;
    TiffCopier copier(&root, 0, nullptr, primaryGroups);
    
    TiffSubIfd subIfd(0x014a, IfdId::ifd0Id, IfdId::subImage1Id);
    
    EXPECT_NO_THROW({
        copier.copyObject(&subIfd);
    });
}
