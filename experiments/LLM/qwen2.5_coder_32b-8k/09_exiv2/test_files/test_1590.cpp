#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include <sstream>

#include <cstdint>

#include "TestProjects/exiv2/src/sonymn_int.cpp"



using namespace Exiv2::Internal;

using ::testing::_;

using ::testing::Ref;



class SonyMakerNoteTest_1590 : public ::testing::Test {

protected:

    SonyMakerNote sonyMakerNote;

};



TEST_F(SonyMakerNoteTest_1590, PrintMultiBurstSize_NormalOperation_1590) {

    Value value;

    value.typeId_ = unsignedShort;

    value.data_.push_back(1);

    ExifData exifData;



    std::ostringstream oss;

    sonyMakerNote.printMultiBurstSize(oss, value, &exifData);



    EXPECT_EQ("1", oss.str());

}



TEST_F(SonyMakerNoteTest_1590, PrintMultiBurstSize_ValueCountNotOne_1590) {

    Value value;

    value.typeId_ = unsignedShort;

    value.data_.push_back(1);

    value.data_.push_back(2); // More than one element

    ExifData exifData;



    std::ostringstream oss;

    sonyMakerNote.printMultiBurstSize(oss, value, &exifData);



    EXPECT_EQ("(1 2)", oss.str());

}



TEST_F(SonyMakerNoteTest_1590, PrintMultiBurstSize_ValueTypeNotUnsignedShort_1590) {

    Value value;

    value.typeId_ = tiffLong; // Different type

    value.data_.push_back(1);

    ExifData exifData;



    std::ostringstream oss;

    sonyMakerNote.printMultiBurstSize(oss, value, &exifData);



    EXPECT_EQ("(1)", oss.str());

}



TEST_F(SonyMakerNoteTest_1590, PrintMultiBurstSize_ExifDataNullptr_1590) {

    Value value;

    value.typeId_ = unsignedShort;

    value.data_.push_back(1);



    std::ostringstream oss;

    sonyMakerNote.printMultiBurstSize(oss, value, nullptr); // Nullptr ExifData



    EXPECT_EQ("1", oss.str());

}



TEST_F(SonyMakerNoteTest_1590, PrintMultiBurstSize_BoundaryConditionZero_1590) {

    Value value;

    value.typeId_ = unsignedShort;

    value.data_.push_back(0);

    ExifData exifData;



    std::ostringstream oss;

    sonyMakerNote.printMultiBurstSize(oss, value, &exifData);



    EXPECT_EQ("0", oss.str());

}



TEST_F(SonyMakerNoteTest_1590, PrintMultiBurstSize_BoundaryConditionMaxUnsignedShort_1590) {

    Value value;

    value.typeId_ = unsignedShort;

    value.data_.push_back(65535);

    ExifData exifData;



    std::ostringstream oss;

    sonyMakerNote.printMultiBurstSize(oss, value, &exifData);



    EXPECT_EQ("65535", oss.str());

}
