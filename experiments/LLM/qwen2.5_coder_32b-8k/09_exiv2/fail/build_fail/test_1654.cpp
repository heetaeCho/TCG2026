#include <gtest/gtest.h>

#include <gmock/gmock.h>



// Mock dependencies

class MockTiffSizeEntry : public Exiv2::Internal::TiffSizeEntry {

public:

    MOCK_METHOD(void, doAccept, (Exiv2::Internal::TiffVisitor& visitor), (override));

};



TEST_F(TiffDecoderTest_1654, VisitSizeEntry_CallsDecodeTiffEntry_1654) {

    MockTiffSizeEntry mockSizeEntry(0x0112, Exiv2::ifdExif, 0x0112, Exiv2::ifdExif);

    Exiv2::Internal::TiffDecoder decoder(/* mock ExifData */, /* mock IptcData */, /* mock XmpData */, nullptr, nullptr);



    EXPECT_CALL(mockSizeEntry, doAccept(::testing::_))

        .WillOnce([this] (Exiv2::Internal::TiffVisitor& visitor) {

            visitor.decodeTiffEntry(&mockSizeEntry);

        });



    decoder.visitSizeEntry(&mockSizeEntry);

}
