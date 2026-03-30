#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "tiffvisitor_int.hpp"

#include "tiffcomposite_int.hpp"



using namespace Exiv2::Internal;

using ::testing::_;



// Test fixture for TiffFinder tests

class TiffFinderTest : public testing::Test {

protected:

    std::unique_ptr<TiffSubIfd> sub_ifd_;

    TiffFinder tiff_finder_;



    TiffFinderTest() 

        : sub_ifd_(std::make_unique<TiffSubIfd>(0x1234, IfdId::ifd0, IfdId::subIfd1)),

          tiff_finder_(0x1234, IfdId::ifd0) {

    }

};



TEST_F(TiffFinderTest_1636, VisitSubIfd_CallsFindObject_1636) {

    EXPECT_CALL(*sub_ifd_, doAccept(_)).WillOnce([&](TiffVisitor& visitor) {

        visitor.findObject(sub_ifd_.get());

    });



    tiff_finder_.visitSubIfd(sub_ifd_.get());



    EXPECT_EQ(tiff_finder_.result(), sub_ifd_.get());

}



TEST_F(TiffFinderTest_1636, Init_ChangesTagAndGroup_1636) {

    uint16_t new_tag = 0x5678;

    IfdId new_group = IfdId::ifdExif;



    tiff_finder_.init(new_tag, new_group);



    // Assuming internal state can be checked through result after visiting

    EXPECT_CALL(*sub_ifd_, doAccept(_)).WillOnce([&](TiffVisitor& visitor) {

        visitor.findObject(sub_ifd_.get());

    });



    sub_ifd_->doAccept(tiff_finder_);



    EXPECT_EQ(tiff_finder_.result(), nullptr); // Since the tag and group don't match

}



TEST_F(TiffFinderTest_1636, VisitSubIfd_MatchingTagAndGroup_ReturnsSubIfd_1636) {

    tiff_finder_.init(0x1234, IfdId::ifd0);



    EXPECT_CALL(*sub_ifd_, doAccept(_)).WillOnce([&](TiffVisitor& visitor) {

        visitor.findObject(sub_ifd_.get());

    });



    tiff_finder_.visitSubIfd(sub_ifd_.get());



    EXPECT_EQ(tiff_finder_.result(), sub_ifd_.get());

}



TEST_F(TiffFinderTest_1636, VisitSubIfd_NonMatchingTag_ReturnsNull_1636) {

    tiff_finder_.init(0x5678, IfdId::ifd0);



    EXPECT_CALL(*sub_ifd_, doAccept(_)).WillOnce([&](TiffVisitor& visitor) {

        visitor.findObject(sub_ifd_.get());

    });



    tiff_finder_.visitSubIfd(sub_ifd_.get());



    EXPECT_EQ(tiff_finder_.result(), nullptr);

}



TEST_F(TiffFinderTest_1636, VisitSubIfd_NonMatchingGroup_ReturnsNull_1636) {

    tiff_finder_.init(0x1234, IfdId::ifdExif);



    EXPECT_CALL(*sub_ifd_, doAccept(_)).WillOnce([&](TiffVisitor& visitor) {

        visitor.findObject(sub_ifd_.get());

    });



    tiff_finder_.visitSubIfd(sub_ifd_.get());



    EXPECT_EQ(tiff_finder_.result(), nullptr);

}
