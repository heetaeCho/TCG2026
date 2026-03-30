#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "./TestProjects/exiv2/src/tiffcomposite_int.hpp"

#include "./TestProjects/exiv2/src/tiffvisitor_int.hpp"



using namespace Exiv2::Internal;



class TiffDecoderTest_1656 : public ::testing::Test {

protected:

    TiffDecoderTest_1656()

        : exifData_{},

          iptcData_{},

          xmpData_{},

          pRoot_{nullptr},

          findDecoderFct_{[](const std::string&) -> TiffDecoder* { return nullptr; }},

          tiffDecoder_{exifData_, iptcData_, xmpData_, pRoot_, findDecoderFct_},

          tiffMnEntry_{1, IfdId::rootIFD, IfdId::mnExif} {}



    ExifData exifData_;

    IptcData iptcData_;

    XmpData xmpData_;

    TiffComponent* pRoot_;

    FindDecoderFct findDecoderFct_;

    TiffDecoder tiffDecoder_;

    TiffMnEntry tiffMnEntry_;

};



TEST_F(TiffDecoderTest_1656, VisitMnEntryCallsDecodeTiffEntry_1656) {

    EXPECT_CALL(tiffMnEntry_, doAccept(::testing::_))

        .WillOnce([](TiffVisitor& visitor) { static_cast<TiffDecoder*>(&visitor)->decodeTiffEntry(&tiffMnEntry_); });



    tiffDecoder_.visitMnEntry(&tiffMnEntry_);

}



TEST_F(TiffDecoderTest_1656, VisitMnEntryWithNullPointer_1656) {

    EXPECT_THROW(tiffDecoder_.visitMnEntry(nullptr), std::exception);

}
