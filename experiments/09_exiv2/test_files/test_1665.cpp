#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "tiffvisitor_int.hpp"

#include "tiffcomposite_int.hpp"



using namespace Exiv2::Internal;

using ::testing::_;



class TiffDecoderTest : public ::testing::Test {

protected:

    TiffDecoderTest()

        : exifData_(),

          iptcData_(),

          xmpData_(),

          pRoot_(nullptr),

          findDecoderFct_([](IfdId, uint16_t) { return nullptr; }),

          decoder_(exifData_, iptcData_, xmpData_, pRoot_, findDecoderFct_)

    {

        tiffBinaryElement_ = new TiffBinaryElement();

    }



    ~TiffDecoderTest() override {

        delete tiffBinaryElement_;

    }



    ExifData exifData_;

    IptcData iptcData_;

    XmpData xmpData_;

    TiffComponent* pRoot_;

    FindDecoderFct findDecoderFct_;

    TiffDecoder decoder_;

    TiffBinaryElement* tiffBinaryElement_;

};



TEST_F(TiffDecoderTest_1665, VisitBinaryElementCallsDecodeTiffEntry_1665) {

    EXPECT_CALL(*tiffBinaryElement_, doAccept(_)).WillOnce([&](TiffVisitor& visitor) {

        visitor.decodeTiffEntry(tiffBinaryElement_);

    });



    decoder_.visitBinaryElement(tiffBinaryElement_);

}



TEST_F(TiffDecoderTest_1665, VisitBinaryElementWithNullElementDoesNotCrash_1665) {

    TiffBinaryElement* nullElement = nullptr;

    EXPECT_NO_THROW(decoder_.visitBinaryElement(nullElement));

}
