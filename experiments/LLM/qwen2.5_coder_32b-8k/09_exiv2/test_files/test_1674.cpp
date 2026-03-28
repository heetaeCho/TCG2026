#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "exiv2/exif.hpp"

#include "TestProjects/exiv2/src/tiffvisitor_int.hpp"

#include "TestProjects/exiv2/src/tiffcomposite_int.hpp"



using namespace Exiv2;

using namespace Exiv2::Internal;



class TiffEncoderTest : public ::testing::Test {

protected:

    ExifData exifData_;

    IptcData iptcData_;

    XmpData xmpData_;

    std::unique_ptr<TiffComponent> pRootDir_ = std::make_unique<TiffComponent>(0, ifdExif);

    TiffEncoder encoder_{exifData_, iptcData_, xmpData_, pRootDir_.get(), false, PrimaryGroups{}, nullptr, nullptr};

};



TEST_F(TiffEncoderTest, VisitMnEntry_NormalOperation_NoMakernote_1674) {

    TiffMnEntry mnEntry(0x927C, ifdExif, ifdMakernoteCanon);

    encoder_.visitMnEntry(&mnEntry);

    // No observable change expected since mn_ is nullptr and del_ is true.

}



TEST_F(TiffEncoderTest, VisitMnEntry_MakernotePresent_DeleteEnabled_EntryRemoved_1674) {

    TiffMnEntry mnEntry(0x927C, ifdExif, ifdMakernoteCanon);

    mnEntry.mn_ = std::make_unique<TiffIfdMakernote>();

    ExifKey key(mnEntry.tag(), mnEntry.groupName());

    exifData_.add(key, nullptr);



    EXPECT_EQ(exifData_.count(), 1);

    encoder_.visitMnEntry(&mnEntry);

    EXPECT_EQ(exifData_.count(), 0); // Entry should be removed since del_ is true.

}



TEST_F(TiffEncoderTest, VisitMnEntry_MakernotePresent_DeleteDisabled_NoChange_1674) {

    TiffMnEntry mnEntry(0x927C, ifdExif, ifdMakernoteCanon);

    mnEntry.mn_ = std::make_unique<TiffIfdMakernote>();

    encoder_.del_ = false; // Disable deletion

    ExifKey key(mnEntry.tag(), mnEntry.groupName());

    exifData_.add(key, nullptr);



    EXPECT_EQ(exifData_.count(), 1);

    encoder_.visitMnEntry(&mnEntry);

    EXPECT_EQ(exifData_.count(), 1); // Entry should not be removed since del_ is false.

}



TEST_F(TiffEncoderTest, VisitMnEntry_NoMakernote_DeleteDisabled_NoChange_1674) {

    TiffMnEntry mnEntry(0x927C, ifdExif, ifdMakernoteCanon);

    encoder_.del_ = false; // Disable deletion

    EXPECT_EQ(exifData_.count(), 0);

    encoder_.visitMnEntry(&mnEntry);

    EXPECT_EQ(exifData_.count(), 0); // No observable change expected since mn_ is nullptr.

}



TEST_F(TiffEncoderTest, VisitMnEntry_BoundaryCondition_EmptyExifData_NoChange_1674) {

    TiffMnEntry mnEntry(0x927C, ifdExif, ifdMakernoteCanon);

    mnEntry.mn_ = std::make_unique<TiffIfdMakernote>();

    EXPECT_EQ(exifData_.count(), 0);

    encoder_.visitMnEntry(&mnEntry);

    EXPECT_EQ(exifData_.count(), 0); // No observable change expected since ExifData is empty.

}



TEST_F(TiffEncoderTest, VisitMnEntry_BoundaryCondition_MaxTagValue_NoChange_1674) {

    TiffMnEntry mnEntry(0xFFFF, ifdExif, ifdMakernoteCanon);

    encoder_.visitMnEntry(&mnEntry);

    // No observable change expected since no specific behavior is defined for max tag value.

}



TEST_F(TiffEncoderTest, VisitMnEntry_ExceptionalCase_InvalidTag_NoChange_1674) {

    TiffMnEntry mnEntry(0xFFFF + 1, ifdExif, ifdMakernoteCanon); // Invalid tag

    encoder_.visitMnEntry(&mnEntry);

    // No observable change expected since invalid tags should be handled gracefully.

}



TEST_F(TiffEncoderTest, VisitMnEntry_ExceptionalCase_InvalidGroup_NoChange_1674) {

    TiffMnEntry mnEntry(0x927C, static_cast<IfdId>(-1), ifdMakernoteCanon); // Invalid group

    encoder_.visitMnEntry(&mnEntry);

    // No observable change expected since invalid groups should be handled gracefully.

}
