#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "tiffvisitor_int.hpp"

#include "xmp_exiv2.hpp"

#include "error.hpp"



using namespace Exiv2;

using namespace Exiv2::Internal;



class TiffDecoderTest_1658 : public ::testing::Test {

protected:

    TiffDecoderTest_1658() 

        : xmpData_(XmpData()), iptcData_(IptcData()),

          findDecoderFct_(nullptr), pRoot_(nullptr),

          tiffDecoder_(exifData_, iptcData_, xmpData_, pRoot_, findDecoderFct_) {}



    ExifData exifData_;

    IptcData iptcData_;

    XmpData xmpData_;

    FindDecoderFct findDecoderFct_;

    TiffComponent* pRoot_;

    TiffDecoder tiffDecoder_;

};



TEST_F(TiffDecoderTest_1658, DecodeXmp_NoData_1658) {

    // Arrange

    auto mockTiffEntry = std::make_unique<TiffEntryBase>(0x02bc, IfdId::ifd0Id, TiffType::undefined);

    const TiffEntryBase* object = mockTiffEntry.get();



    // Act

    tiffDecoder_.decodeXmp(object);



    // Assert

    EXPECT_TRUE(xmpData_.empty());

}



TEST_F(TiffDecoderTest_1658, DecodeXmp_ValidXmpPacket_1658) {

    // Arrange

    std::string xmpPacket = "<?xpacket begin='' id='W5M0MpCehiHzreS3GCS4sg=='?>\n<x:xmpmeta xmlns:x='adobe:ns:meta/' x:xmptk='XMP Core 6.6.0-Flavour 120647, cairogcc Mac OS X-clang 12.0.0 (clang-1200.0.32.29)'>\n</x:xmpmeta>\n<?xpacket end='r'?>";

    auto mockTiffEntry = std::make_unique<TiffEntryBase>(0x02bc, IfdId::ifd0Id, TiffType::undefined);

    mockTiffEntry->setData(reinterpret_cast<byte*>(const_cast<char*>(xmpPacket.data())), xmpPacket.size(), nullptr);

    const TiffEntryBase* object = mockTiffEntry.get();



    // Act

    tiffDecoder_.decodeXmp(object);



    // Assert

    EXPECT_FALSE(xmpData_.empty());

}



TEST_F(TiffDecoderTest_1658, DecodeXmp_InvalidXmpPacket_1658) {

    // Arrange

    std::string invalidXmpPacket = "This is not an XMP packet";

    auto mockTiffEntry = std::make_unique<TiffEntryBase>(0x02bc, IfdId::ifd0Id, TiffType::undefined);

    mockTiffEntry->setData(reinterpret_cast<byte*>(const_cast<char*>(invalidXmpPacket.data())), invalidXmpPacket.size(), nullptr);

    const TiffEntryBase* object = mockTiffEntry.get();



    // Act

    tiffDecoder_.decodeXmp(object);



    // Assert

    EXPECT_TRUE(xmpData_.empty());

}



TEST_F(TiffDecoderTest_1658, DecodeXmp_XmpPacketWithLeadingChars_1658) {

    // Arrange

    std::string xmpPacket = "Some leading characters<?xpacket begin='' id='W5M0MpCehiHzreS3GCS4sg=='?>\n<x:xmpmeta xmlns:x='adobe:ns:meta/' x:xmptk='XMP Core 6.6.0-Flavour 120647, cairogcc Mac OS X-clang 12.0.0 (clang-1200.0.32.29)'>\n</x:xmpmeta>\n<?xpacket end='r'?>";

    auto mockTiffEntry = std::make_unique<TiffEntryBase>(0x02bc, IfdId::ifd0Id, TiffType::undefined);

    mockTiffEntry->setData(reinterpret_cast<byte*>(const_cast<char*>(xmpPacket.data())), xmpPacket.size(), nullptr);

    const TiffEntryBase* object = mockTiffEntry.get();



    // Act

    tiffDecoder_.decodeXmp(object);



    // Assert

    EXPECT_FALSE(xmpData_.empty());

}



TEST_F(TiffDecoderTest_1658, DecodeXmp_XmpPacketWithNoStartTag_1658) {

    // Arrange

    std::string xmpPacket = "<x:xmpmeta xmlns:x='adobe:ns:meta/' x:xmptk='XMP Core 6.6.0-Flavour 120647, cairogcc Mac OS X-clang 12.0.0 (clang-1200.0.32.29)'>\n</x:xmpmeta>\n<?xpacket end='r'?>";

    auto mockTiffEntry = std::make_unique<TiffEntryBase>(0x02bc, IfdId::ifd0Id, TiffType::undefined);

    mockTiffEntry->setData(reinterpret_cast<byte*>(const_cast<char*>(xmpPacket.data())), xmpPacket.size(), nullptr);

    const TiffEntryBase* object = mockTiffEntry.get();



    // Act

    tiffDecoder_.decodeXmp(object);



    // Assert

    EXPECT_FALSE(xmpData_.empty());

}



TEST_F(TiffDecoderTest_1658, DecodeXmp_XmpPacketWithNoEndTag_1658) {

    // Arrange

    std::string xmpPacket = "<?xpacket begin='' id='W5M0MpCehiHzreS3GCS4sg=='?>\n<x:xmpmeta xmlns:x='adobe:ns:meta/' x:xmptk='XMP Core 6.6.0-Flavour 120647, cairogcc Mac OS X-clang 12.0.0 (clang-1200.0.32.29)'>\n</x:xmpmeta>";

    auto mockTiffEntry = std::make_unique<TiffEntryBase>(0x02bc, IfdId::ifd0Id, TiffType::undefined);

    mockTiffEntry->setData(reinterpret_cast<byte*>(const_cast<char*>(xmpPacket.data())), xmpPacket.size(), nullptr);

    const TiffEntryBase* object = mockTiffEntry.get();



    // Act

    tiffDecoder_.decodeXmp(object);



    // Assert

    EXPECT_FALSE(xmpData_.empty());

}



TEST_F(TiffDecoderTest_1658, DecodeXmp_XmpPacketWithEmptyString_1658) {

    // Arrange

    std::string xmpPacket = "";

    auto mockTiffEntry = std::make_unique<TiffEntryBase>(0x02bc, IfdId::ifd0Id, TiffType::undefined);

    mockTiffEntry->setData(reinterpret_cast<byte*>(const_cast<char*>(xmpPacket.data())), xmpPacket.size(), nullptr);

    const TiffEntryBase* object = mockTiffEntry.get();



    // Act

    tiffDecoder_.decodeXmp(object);



    // Assert

    EXPECT_TRUE(xmpData_.empty());

}



TEST_F(TiffDecoderTest_1658, DecodeXmp_XmpPacketWithGarbageData_1658) {

    // Arrange

    std::string xmpPacket = "garbage data garbage data";

    auto mockTiffEntry = std::make_unique<TiffEntryBase>(0x02bc, IfdId::ifd0Id, TiffType::undefined);

    mockTiffEntry->setData(reinterpret_cast<byte*>(const_cast<char*>(xmpPacket.data())), xmpPacket.size(), nullptr);

    const TiffEntryBase* object = mockTiffEntry.get();



    // Act

    tiffDecoder_.decodeXmp(object);



    // Assert

    EXPECT_TRUE(xmpData_.empty());

}



TEST_F(TiffDecoderTest_1658, DecodeXmp_XmpPacketWithLargeLeadingChars_1658) {

    // Arrange

    std::string leadingChars(1024, 'A');

    std::string xmpPacket = leadingChars + "<?xpacket begin='' id='W5M0MpCehiHzreS3GCS4sg=='?>\n<x:xmpmeta xmlns:x='adobe:ns:meta/' x:xmptk='XMP Core 6.6.0-Flavour 120647, cairogcc Mac OS X-clang 12.0.0 (clang-1200.0.32.29)'>\n</x:xmpmeta>\n<?xpacket end='r'?>";

    auto mockTiffEntry = std::make_unique<TiffEntryBase>(0x02bc, IfdId::ifd0Id, TiffType::undefined);

    mockTiffEntry->setData(reinterpret_cast<byte*>(const_cast<char*>(xmpPacket.data())), xmpPacket.size(), nullptr);

    const TiffEntryBase* object = mockTiffEntry.get();



    // Act

    tiffDecoder_.decodeXmp(object);



    // Assert

    EXPECT_FALSE(xmpData_.empty());

}
