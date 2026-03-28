#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "tiffvisitor_int.hpp"

#include "tiffcomposite_int.hpp"



using namespace Exiv2::Internal;

using ::testing::NiceMock;



class MockTiffDataEntry : public TiffDataEntry {

public:

    MOCK_METHOD(void, setStrips, (const Value * pSize, const byte * pData, size_t sizeData, size_t baseOffset), (override));

    MOCK_METHOD(void, doAccept, (TiffVisitor & visitor), (override));

};



class TiffDecoderTest_1652 : public ::testing::Test {

protected:

    ExifData exifData;

    IptcData iptcData;

    XmpData xmpData;

    NiceMock<MockTiffDataEntry> mockTiffDataEntry;

    TiffDecoder decoder{exifData, iptcData, xmpData, nullptr, nullptr};

};



TEST_F(TiffDecoderTest_1652, VisitDataEntry_CallsDecodeTiffEntry_1652) {

    EXPECT_CALL(mockTiffDataEntry, doAccept(::testing::_)).WillOnce([](TiffVisitor& visitor) {

        // Simulate the call to decodeTiffEntry

        visitor.decodeTiffEntry(&mockTiffDataEntry);

    });



    decoder.visitDataEntry(&mockTiffDataEntry);

}



TEST_F(TiffDecoderTest_1652, VisitDataEntry_DoesNotThrowOnNormalOperation_1652) {

    EXPECT_CALL(mockTiffDataEntry, doAccept(::testing::_)).Times(1);



    ASSERT_NO_THROW(decoder.visitDataEntry(&mockTiffDataEntry));

}



TEST_F(TiffDecoderTest_1652, VisitDataEntry_VerifiesExternalInteraction_1652) {

    EXPECT_CALL(mockTiffDataEntry, doAccept(::testing::_))

        .WillOnce([](TiffVisitor& visitor) {

            // Simulate the call to decodeTiffEntry

            visitor.decodeTiffEntry(&mockTiffDataEntry);

        });



    decoder.visitDataEntry(&mockTiffDataEntry);

}
