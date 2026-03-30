#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include <sstream>

#include <exiv2/exiv2.hpp>



using namespace Exiv2;

using namespace Exiv2::Internal;



class Nikon1MakerNoteTest_455 : public ::testing::Test {

protected:

    Nikon1MakerNote makerNote_;

};



TEST_F(Nikon1MakerNoteTest_455, Print0x0088_ValidFocusAreaAndPoint_455) {

    Value value;

    value.typeId_ = ValueType::uint32;

    value.data_.push_back(0); // focusArea

    value.data_.push_back(2); // focusPoint

    value.size_ = 2;



    std::ostringstream os;

    makerNote_.print0x0088(os, value, nullptr);



    EXPECT_EQ("Center; Center", os.str());

}



TEST_F(Nikon1MakerNoteTest_455, Print0x0088_ValidFocusAreaAndPointWithGuess_455) {

    Value value;

    value.typeId_ = ValueType::uint32;

    value.data_.push_back(0); // focusArea

    value.data_.push_back(9); // focusPoint (out of range but within guessable range)

    value.size_ = 2;



    std::ostringstream os;

    makerNote_.print0x0088(os, value, nullptr);



    EXPECT_EQ("Center; 9 guess Bottom-right", os.str());

}



TEST_F(Nikon1MakerNoteTest_455, Print0x0088_OutOfRangeFocusArea_455) {

    Value value;

    value.typeId_ = ValueType::uint32;

    value.data_.push_back(100); // focusArea (out of range)

    value.size_ = 1;



    std::ostringstream os;

    makerNote_.print0x0088(os, value, nullptr);



    EXPECT_EQ("Invalid value", os.str());

}



TEST_F(Nikon1MakerNoteTest_455, Print0x0088_ValidFocusPointsUsed_455) {

    Value value;

    value.typeId_ = ValueType::uint32;

    value.data_.push_back(0); // focusArea

    value.data_.push_back(2); // focusPoint

    value.data_.push_back(1 | 2 | 4); // focusPointsUsed1 (bits 0, 1, and 2)

    value.data_.push_back(8); // focusPointsUsed2 (bit 3)

    value.size_ = 4;



    std::ostringstream os;

    makerNote_.print0x0088(os, value, nullptr);



    EXPECT_EQ("Center; Center; [Center Right Bottom-left Top]", os.str());

}



TEST_F(Nikon1MakerNoteTest_455, Print0x0088_ZeroFocusPointsUsed_455) {

    Value value;

    value.typeId_ = ValueType::uint32;

    value.data_.push_back(0); // focusArea

    value.data_.push_back(2); // focusPoint

    value.data_.push_back(0); // focusPointsUsed1 (no bits set)

    value.data_.push_back(0); // focusPointsUsed2 (no bits set)

    value.size_ = 4;



    std::ostringstream os;

    makerNote_.print0x0088(os, value, nullptr);



    EXPECT_EQ("Center; Center", os.str());

}



TEST_F(Nikon1MakerNoteTest_455, Print0x0088_EmptyValue_455) {

    Value value;

    value.typeId_ = ValueType::uint32;

    value.size_ = 0;



    std::ostringstream os;

    makerNote_.print0x0088(os, value, nullptr);



    EXPECT_EQ("()", os.str());

}



TEST_F(Nikon1MakerNoteTest_455, Print0x0088_SingleValue_455) {

    Value value;

    value.typeId_ = ValueType::uint32;

    value.data_.push_back(0); // focusArea

    value.size_ = 1;



    std::ostringstream os;

    makerNote_.print0x0088(os, value, nullptr);



    EXPECT_EQ("Center", os.str());

}



TEST_F(Nikon1MakerNoteTest_455, Print0x0088_TwoValuesWithSecondOutOfRange_455) {

    Value value;

    value.typeId_ = ValueType::uint32;

    value.data_.push_back(0); // focusArea

    value.data_.push_back(6); // focusPoint (out of range)

    value.size_ = 2;



    std::ostringstream os;

    makerNote_.print0x0088(os, value, nullptr);



    EXPECT_EQ("Center; 6", os.str());

}
