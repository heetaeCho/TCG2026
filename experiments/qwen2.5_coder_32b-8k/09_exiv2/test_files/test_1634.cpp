#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "tiffvisitor_int.hpp"



using namespace Exiv2::Internal;

using testing::NiceMock;

using testing::_;



class MockTiffSizeEntry : public TiffSizeEntry {

public:

    MOCK_METHOD(void, doAccept, (TiffVisitor & visitor), override);

    MOCK_METHOD(void, doEncode, (TiffEncoder & encoder, const Exifdatum * datum), override);

    MOCK_METHOD(const TiffSizeEntry *, doClone, (), const, override);



    MockTiffSizeEntry(uint16_t tag, IfdId group, uint16_t dtTag, IfdId dtGroup)

        : TiffSizeEntry(tag, group, dtTag, dtGroup) {}

};



class TiffFinderTest_1634 : public testing::Test {

protected:

    TiffFinder finder{0x0112, ifdExif};

    std::unique_ptr<MockTiffSizeEntry> mockSizeEntry = std::make_unique<MockTiffSizeEntry>(0x0112, ifdExif, 5, ifdExif);

};



TEST_F(TiffFinderTest_1634, VisitSizeEntryCallsFindObject_1634) {

    EXPECT_CALL(*mockSizeEntry, doAccept(_)).Times(1);



    finder.visitSizeEntry(mockSizeEntry.get());

}



TEST_F(TiffFinderTest_1634, VisitSizeEntryWithNullPointerDoesNotCrash_1634) {

    EXPECT_NO_THROW(finder.visitSizeEntry(nullptr));

}
