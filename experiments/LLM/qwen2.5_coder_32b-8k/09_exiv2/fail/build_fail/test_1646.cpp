#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "tiffvisitor_int.hpp"

#include "tiffcomposite_int.hpp"



using namespace Exiv2::Internal;

using ::testing::StrictMock;



class MockTiffSubIfd : public TiffSubIfd {

public:

    MockTiffSubIfd(uint16_t tag, IfdId group, IfdId newGroup) : TiffSubIfd(tag, group, newGroup) {}

};



class TiffCopierTest_1646 : public ::testing::Test {

protected:

    StrictMock<MockTiffSubIfd> mockSubIfd;

    TiffCopier tiffCopier{nullptr, 0, nullptr, {}};



    TiffCopierTest_1646() : mockSubIfd(0x0025, ifdExif, ifdExif) {}

};



TEST_F(TiffCopierTest_1646, VisitSubIfdCallsCopyObject_1646) {

    EXPECT_CALL(mockSubIfd, doAccept(::testing::_))

        .WillOnce([](TiffVisitor& visitor){ visitor.copyObject(&mockSubIfd); });



    tiffCopier.visitSubIfd(&mockSubIfd);

}



TEST_F(TiffCopierTest_1646, VisitSubIfdWithNullPointer_1646) {

    EXPECT_NO_THROW(tiffCopier.visitSubIfd(nullptr));

}
