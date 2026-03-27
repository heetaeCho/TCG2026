#include <gtest/gtest.h>

#include "tiffvisitor_int.hpp"

#include "tiffcomposite_int.hpp"



namespace Exiv2 {

namespace Internal {



class MockTiffImageEntry : public TiffImageEntry {

public:

    MOCK_METHOD(void, doAccept, (TiffVisitor& visitor), (override));

};



TEST_F(TiffDecoderTest_1653, VisitImageEntryCallsDoAccept_1653) {

    NiceMock<MockTiffImageEntry> mockEntry;

    TiffDecoder decoder({}, {}, {}, nullptr, nullptr);



    EXPECT_CALL(mockEntry, doAccept(testing::Ref(decoder)));



    decoder.visitImageEntry(&mockEntry);

}



TEST_F(TiffDecoderTest_1653, VisitImageEntryWithNullPointer_1653) {

    TiffDecoder decoder({}, {}, {}, nullptr, nullptr);



    EXPECT_NO_THROW(decoder.visitImageEntry(nullptr));

}



}  // namespace Internal

}  // namespace Exiv2
