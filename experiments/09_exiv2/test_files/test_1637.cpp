#include <gtest/gtest.h>

#include <gmock/gmock.h>



// Mocking TiffMnEntry for testing purposes

class MockTiffMnEntry : public Exiv2::Internal::TiffMnEntry {

public:

    MOCK_METHOD(void, doAccept, (Exiv2::Internal::TiffVisitor& visitor), (override));

};



namespace Exiv2 { namespace Internal {



// Test fixture for TiffFinder

class TiffFinderTest_1637 : public ::testing::Test {

protected:

    MockTiffMnEntry mock_tiff_mn_entry;

    TiffFinder tiff_finder{0, ifdIdExif};

};



TEST_F(TiffFinderTest_1637, VisitMnEntry_CallsDoAccept_1637) {

    EXPECT_CALL(mock_tiff_mn_entry, doAccept(::testing::_)).Times(1);

    tiff_finder.visitMnEntry(&mock_tiff_mn_entry);

}



} } // namespace Exiv2::Internal
