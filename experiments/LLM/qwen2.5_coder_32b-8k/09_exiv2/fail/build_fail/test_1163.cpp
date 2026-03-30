#include <gtest/gtest.h>

#include "./TestProjects/exiv2/src/tiffimage_int.hpp"

#include "./TestProjects/exiv2/src/tiffcomposite_int.hpp"



using namespace Exiv2::Internal;



class TiffMappingTest_1163 : public ::testing::Test {

protected:

    TiffMapping tiff_mapping;

};



TEST_F(TiffMappingTest_1163, DefaultDecoderWhenNotFound_1163) {

    std::string_view make = "UnknownMake";

    uint32_t extendedTag = 0x1234;

    IfdId group = IfdId::IFD0;



    DecoderFct decoderFct = tiff_mapping.findDecoder(make, extendedTag, group);



    EXPECT_EQ(decoderFct, &TiffDecoder::decodeStdTiffEntry);

}



TEST_F(TiffMappingTest_1163, KnownDecoderFound_1163) {

    std::string_view make = "KnownMake";

    uint32_t extendedTag = 0x5678;

    IfdId group = IfdId::IFD0;



    // Assuming the tiffMappingInfo_ is populated with this entry

    TiffMappingInfo knownEntry{.make_ = make, .decoderFct_ = reinterpret_cast<DecoderFct>(0xDEADBEEF)};

    Exiv2::find(tiffMappingInfo_, TiffMappingInfo::Key{make, extendedTag, group}) = &knownEntry;



    DecoderFct decoderFct = tiff_mapping.findDecoder(make, extendedTag, group);



    EXPECT_EQ(decoderFct, knownEntry.decoderFct_);

}



TEST_F(TiffMappingTest_1163, BoundaryCondition_EmptyMake_1163) {

    std::string_view make = "";

    uint32_t extendedTag = 0x1234;

    IfdId group = IfdId::IFD0;



    DecoderFct decoderFct = tiff_mapping.findDecoder(make, extendedTag, group);



    EXPECT_EQ(decoderFct, &TiffDecoder::decodeStdTiffEntry);

}



TEST_F(TiffMappingTest_1163, BoundaryCondition_MaxExtendedTag_1163) {

    std::string_view make = "KnownMake";

    uint32_t extendedTag = UINT32_MAX;

    IfdId group = IfdId::IFD0;



    DecoderFct decoderFct = tiff_mapping.findDecoder(make, extendedTag, group);



    EXPECT_EQ(decoderFct, &TiffDecoder::decodeStdTiffEntry);

}



TEST_F(TiffMappingTest_1163, BoundaryCondition_MinIfdGroup_1163) {

    std::string_view make = "KnownMake";

    uint32_t extendedTag = 0x1234;

    IfdId group = static_cast<IfdId>(0);



    DecoderFct decoderFct = tiff_mapping.findDecoder(make, extendedTag, group);



    EXPECT_EQ(decoderFct, &TiffDecoder::decodeStdTiffEntry);

}
