#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "tiffvisitor_int.hpp"
#include "tiffcomposite_int.hpp"
#include "tiffimage_int.hpp"

#include <memory>
#include <vector>

using namespace Exiv2::Internal;

class TiffCopierTest_1644 : public ::testing::Test {
protected:
    void SetUp() override {
    }

    void TearDown() override {
    }
};

// Test that TiffCopier can be constructed with valid parameters
TEST_F(TiffCopierTest_1644, ConstructWithValidParams_1644) {
    // Create a minimal TiffDirectory as root
    TiffDirectory root(0, IfdId::ifd0Id);
    PrimaryGroups primaryGroups;

    // TiffCopier construction should not throw
    EXPECT_NO_THROW({
        TiffCopier copier(&root, 0, nullptr, primaryGroups);
    });
}

// Test that visitImageEntry can be called with a TiffImageEntry object
TEST_F(TiffCopierTest_1644, VisitImageEntryWithValidObject_1644) {
    TiffDirectory root(0, IfdId::ifd0Id);
    PrimaryGroups primaryGroups;
    TiffCopier copier(&root, 0, nullptr, primaryGroups);

    // Create a TiffImageEntry - tag 0x0111 (StripOffsets) is commonly used
    TiffImageEntry imageEntry(0x0111, IfdId::ifd0Id);

    // visitImageEntry should not crash when called with a valid object
    EXPECT_NO_THROW(copier.visitImageEntry(&imageEntry));
}

// Test that visitImageEntry delegates to copyObject (observable by not crashing)
TEST_F(TiffCopierTest_1644, VisitImageEntryCopyObject_1644) {
    TiffDirectory root(0, IfdId::ifd0Id);
    PrimaryGroups primaryGroups;
    TiffCopier copier(&root, 0, nullptr, primaryGroups);

    TiffImageEntry imageEntry(0x0117, IfdId::ifd0Id); // StripByteCounts tag

    // Should successfully copy without errors
    EXPECT_NO_THROW(copier.visitImageEntry(&imageEntry));
}

// Test visitEntry with a TiffEntry
TEST_F(TiffCopierTest_1644, VisitEntryWithValidObject_1644) {
    TiffDirectory root(0, IfdId::ifd0Id);
    PrimaryGroups primaryGroups;
    TiffCopier copier(&root, 0, nullptr, primaryGroups);

    TiffEntry entry(0x0100, IfdId::ifd0Id); // ImageWidth tag

    EXPECT_NO_THROW(copier.visitEntry(&entry));
}

// Test visitDataEntry with a TiffDataEntry
TEST_F(TiffCopierTest_1644, VisitDataEntryWithValidObject_1644) {
    TiffDirectory root(0, IfdId::ifd0Id);
    PrimaryGroups primaryGroups;
    TiffCopier copier(&root, 0, nullptr, primaryGroups);

    TiffDataEntry dataEntry(0x0201, IfdId::ifd0Id);

    EXPECT_NO_THROW(copier.visitDataEntry(&dataEntry));
}

// Test visitSizeEntry with a TiffSizeEntry
TEST_F(TiffCopierTest_1644, VisitSizeEntryWithValidObject_1644) {
    TiffDirectory root(0, IfdId::ifd0Id);
    PrimaryGroups primaryGroups;
    TiffCopier copier(&root, 0, nullptr, primaryGroups);

    TiffSizeEntry sizeEntry(0x0202, IfdId::ifd0Id);

    EXPECT_NO_THROW(copier.visitSizeEntry(&sizeEntry));
}

// Test visitDirectory with a TiffDirectory
TEST_F(TiffCopierTest_1644, VisitDirectoryWithValidObject_1644) {
    TiffDirectory root(0, IfdId::ifd0Id);
    PrimaryGroups primaryGroups;
    TiffCopier copier(&root, 0, nullptr, primaryGroups);

    TiffDirectory dir(0, IfdId::ifd1Id);

    EXPECT_NO_THROW(copier.visitDirectory(&dir));
}

// Test visitBinaryElement with a TiffBinaryElement
TEST_F(TiffCopierTest_1644, VisitBinaryElementWithValidObject_1644) {
    TiffDirectory root(0, IfdId::ifd0Id);
    PrimaryGroups primaryGroups;
    TiffCopier copier(&root, 0, nullptr, primaryGroups);

    TiffBinaryElement binaryElement(0x0001, IfdId::ifd0Id);

    EXPECT_NO_THROW(copier.visitBinaryElement(&binaryElement));
}

// Test multiple visitImageEntry calls on the same copier
TEST_F(TiffCopierTest_1644, MultipleVisitImageEntryCalls_1644) {
    TiffDirectory root(0, IfdId::ifd0Id);
    PrimaryGroups primaryGroups;
    TiffCopier copier(&root, 0, nullptr, primaryGroups);

    TiffImageEntry imageEntry1(0x0111, IfdId::ifd0Id);
    TiffImageEntry imageEntry2(0x0117, IfdId::ifd0Id);

    EXPECT_NO_THROW(copier.visitImageEntry(&imageEntry1));
    EXPECT_NO_THROW(copier.visitImageEntry(&imageEntry2));
}

// Test constructing TiffCopier with non-empty PrimaryGroups
TEST_F(TiffCopierTest_1644, ConstructWithNonEmptyPrimaryGroups_1644) {
    TiffDirectory root(0, IfdId::ifd0Id);
    PrimaryGroups primaryGroups;
    primaryGroups.push_back(IfdId::ifd0Id);
    primaryGroups.push_back(IfdId::ifd1Id);

    EXPECT_NO_THROW({
        TiffCopier copier(&root, 0, nullptr, primaryGroups);
    });
}

// Test visitImageEntry with different tag values
TEST_F(TiffCopierTest_1644, VisitImageEntryDifferentTags_1644) {
    TiffDirectory root(0, IfdId::ifd0Id);
    PrimaryGroups primaryGroups;
    TiffCopier copier(&root, 0, nullptr, primaryGroups);

    // Use tag 0 as a boundary value
    TiffImageEntry imageEntry(0x0000, IfdId::ifd0Id);

    EXPECT_NO_THROW(copier.visitImageEntry(&imageEntry));
}
