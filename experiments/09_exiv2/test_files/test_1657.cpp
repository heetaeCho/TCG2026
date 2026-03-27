#include <gtest/gtest.h>

#include "exiv2/types.hpp"

#include "exiv2/exif.hpp"

#include "./TestProjects/exiv2/src/tiffcomposite_int.hpp"

#include "./TestProjects/exiv2/src/tiffvisitor_int.hpp"



using namespace Exiv2;

using namespace Exiv2::Internal;



class TiffDecoderTest_1657 : public ::testing::Test {

protected:

    TiffDecoderTest_1657()

        : exifData_(),

          iptcData_(),

          xmpData_(),

          pRoot_(nullptr),

          findDecoderFct_(nullptr),

          tiffDecoder_(exifData_, iptcData_, xmpData_, pRoot_, findDecoderFct_)

    {

        // Setup any common objects or state here

    }



    ExifData exifData_;

    IptcData iptcData_;

    XmpData xmpData_;

    TiffComponent* pRoot_;

    FindDecoderFct findDecoderFct_;

    TiffDecoder tiffDecoder_;

};



TEST_F(TiffDecoderTest_1657, VisitIfdMakernote_NormalOperation_LittleEndian_1657) {

    std::unique_ptr<MnHeader> pHeader = nullptr;

    TiffIfdMakernote tiffIfdMakernote(0x927C, ifdExif, ifdMakerNotes, std::move(pHeader), false);

    tiffIfdMakernote.setByteOrder(littleEndian);



    uint32_t offset = 12345;

    tiffIfdMakernote.setImageByteOrder(littleEndian);

    tiffIfdMakernote.setBaseOffset(offset - 8); // Simulate base offset setup

    tiffIfdMakernote.mnOffset_ = offset;



    tiffDecoder_.visitIfdMakernote(&tiffIfdMakernote);



    EXPECT_EQ(exifData_["Exif.MakerNote.Offset"].toString(), "12345");

    EXPECT_EQ(exifData_["Exif.MakerNote.ByteOrder"].toString(), "II");

}



TEST_F(TiffDecoderTest_1657, VisitIfdMakernote_NormalOperation_BigEndian_1657) {

    std::unique_ptr<MnHeader> pHeader = nullptr;

    TiffIfdMakernote tiffIfdMakernote(0x927C, ifdExif, ifdMakerNotes, std::move(pHeader), false);

    tiffIfdMakernote.setByteOrder(bigEndian);



    uint32_t offset = 12345;

    tiffIfdMakernote.setImageByteOrder(bigEndian);

    tiffIfdMakernote.setBaseOffset(offset - 8); // Simulate base offset setup

    tiffIfdMakernote.mnOffset_ = offset;



    tiffDecoder_.visitIfdMakernote(&tiffIfdMakernote);



    EXPECT_EQ(exifData_["Exif.MakerNote.Offset"].toString(), "12345");

    EXPECT_EQ(exifData_["Exif.MakerNote.ByteOrder"].toString(), "MM");

}



TEST_F(TiffDecoderTest_1657, VisitIfdMakernote_BoundaryCondition_ZeroOffset_1657) {

    std::unique_ptr<MnHeader> pHeader = nullptr;

    TiffIfdMakernote tiffIfdMakernote(0x927C, ifdExif, ifdMakerNotes, std::move(pHeader), false);

    tiffIfdMakernote.setByteOrder(littleEndian);



    uint32_t offset = 0;

    tiffIfdMakernote.setImageByteOrder(littleEndian);

    tiffIfdMakernote.setBaseOffset(offset); // Simulate base offset setup

    tiffIfdMakernote.mnOffset_ = offset;



    tiffDecoder_.visitIfdMakernote(&tiffIfdMakernote);



    EXPECT_EQ(exifData_["Exif.MakerNote.Offset"].toString(), "0");

    EXPECT_EQ(exifData_["Exif.MakerNote.ByteOrder"].toString(), "II");

}



TEST_F(TiffDecoderTest_1657, VisitIfdMakernote_ErrorCase_InvalidByteOrder_1657) {

    std::unique_ptr<MnHeader> pHeader = nullptr;

    TiffIfdMakernote tiffIfdMakernote(0x927C, ifdExif, ifdMakerNotes, std::move(pHeader), false);

    tiffIfdMakernote.setByteOrder(invalidByteOrder);



    uint32_t offset = 12345;

    tiffIfdMakernote.setImageByteOrder(littleEndian);

    tiffIfdMakernote.setBaseOffset(offset - 8); // Simulate base offset setup

    tiffIfdMakernote.mnOffset_ = offset;



    tiffDecoder_.visitIfdMakernote(&tiffIfdMakernote);



    EXPECT_EQ(exifData_["Exif.MakerNote.Offset"].toString(), "12345");

    EXPECT_EQ(exifData_.findKey(ExifKey("Exif.MakerNote.ByteOrder")), exifData_.end());

}
