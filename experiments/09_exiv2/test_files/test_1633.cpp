#include <gtest/gtest.h>

#include <gmock/gmock.h>



// Assuming necessary headers are included for TiffFinder and TiffImageEntry



namespace Exiv2 { namespace Internal {



class MockTiffImageEntry : public TiffImageEntry {

public:

    MOCK_METHOD(void, setStrips, (const Value* pSize, const byte* pData, size_t sizeData, size_t baseOffset), (override));

    MOCK_METHOD(void, doAccept, (TiffVisitor& visitor), (override));

};



TEST_F(TiffFinderTest_1633, VisitImageEntryCallsFindObject_1633) {

    MockTiffImageEntry mockEntry;

    TiffFinder finder(0x1234, ifdIdMain);



    EXPECT_CALL(mockEntry, doAccept(::testing::_)).WillOnce([&](TiffVisitor& visitor) {

        visitor.findObject(&mockEntry);

    });



    finder.visitImageEntry(&mockEntry);

}



TEST_F(TiffFinderTest_1633, VisitImageEntryWithNullPointerDoesNotCrash_1633) {

    TiffFinder finder(0x1234, ifdIdMain);



    EXPECT_NO_THROW(finder.visitImageEntry(nullptr));

}



// Assuming TiffComponent and related classes are properly defined

TEST_F(TiffFinderTest_1633, VisitImageEntrySetsResult_1633) {

    MockTiffImageEntry mockEntry;

    TiffFinder finder(0x1234, ifdIdMain);



    EXPECT_CALL(mockEntry, doAccept(::testing::_)).WillOnce([&](TiffVisitor& visitor) {

        visitor.findObject(&mockEntry);

    });



    finder.visitImageEntry(&mockEntry);

    ASSERT_EQ(finder.result(), &mockEntry);

}



}} // namespace Exiv2::Internal
