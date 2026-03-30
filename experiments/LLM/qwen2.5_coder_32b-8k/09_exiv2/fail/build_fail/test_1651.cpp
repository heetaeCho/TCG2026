#include <gtest/gtest.h>

#include "tiffvisitor_int.hpp"

#include "tiffcomposite_int.hpp"



namespace Exiv2 {

namespace Internal {



class MockTiffEntry : public TiffEntry {

public:

    MOCK_METHOD(void, doAccept, (TiffVisitor& visitor), override);

};



class TiffDecoderTest_1651 : public ::testing::Test {

protected:

    TiffDecoderTest_1651()

        : exifData_(), iptcData_(), xmpData_(), pRoot_(nullptr), findDecoderFct_(nullptr),

          decoder_(exifData_, iptcData_, xmpData_, pRoot_, findDecoderFct_) {}



    ExifData exifData_;

    IptcData iptcData_;

    XmpData xmpData_;

    TiffComponent* pRoot_;

    FindDecoderFct findDecoderFct_;

    TiffDecoder decoder_;

};



TEST_F(TiffDecoderTest_1651, VisitEntryCallsDecodeTiffEntry_1651) {

    auto mockEntry = std::make_unique<MockTiffEntry>();

    EXPECT_CALL(*mockEntry, doAccept(::testing::_)).WillOnce([this](TiffVisitor& visitor) {

        visitor.decodeTiffEntry(mockEntry.get());

    });



    decoder_.visitEntry(mockEntry.get());

}



TEST_F(TiffDecoderTest_1651, VisitEntryWithNullPointer_1651) {

    TiffEntry* nullEntry = nullptr;

    EXPECT_NO_THROW(decoder_.visitEntry(nullEntry));

}



// Assuming there are no specific boundary conditions for the visitEntry method,

// as it primarily deals with a single pointer argument.



}  // namespace Internal

}  // namespace Exiv2
