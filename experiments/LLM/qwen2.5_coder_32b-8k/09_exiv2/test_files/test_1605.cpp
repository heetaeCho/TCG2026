#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "sonymn_int.cpp"



namespace Exiv2 { namespace Internal {



class SonyMakerNoteTest : public ::testing::Test {

protected:

    SonyMakerNote sonyMakerNote;

    std::ostringstream os;

};



TEST_F(SonyMakerNoteTest_1605, PrintColorCompensationFilter_NormalOperation_PositiveValue_1605) {

    Value value;

    value.makeArray(unsignedLong);

    value[0] = 42;



    sonyMakerNote.printColorCompensationFilter(os, value, nullptr);



    EXPECT_EQ(os.str(), "G/M: M42");

}



TEST_F(SonyMakerNoteTest_1605, PrintColorCompensationFilter_NormalOperation_NegativeValue_1605) {

    Value value;

    value.makeArray(unsignedLong);

    value[0] = static_cast<uint32_t>(-42);



    sonyMakerNote.printColorCompensationFilter(os, value, nullptr);



    EXPECT_EQ(os.str(), "G/M: G42");

}



TEST_F(SonyMakerNoteTest_1605, PrintColorCompensationFilter_NormalOperation_ZeroValue_1605) {

    Value value;

    value.makeArray(unsignedLong);

    value[0] = 0;



    sonyMakerNote.printColorCompensationFilter(os, value, nullptr);



    EXPECT_EQ(os.str(), "G/M: 0");

}



TEST_F(SonyMakerNoteTest_1605, PrintColorCompensationFilter_BoundaryCondition_ValueCountNotOne_1605) {

    Value value;

    value.makeArray(unsignedLong);

    value[0] = 42;

    value[1] = 84;



    sonyMakerNote.printColorCompensationFilter(os, value, nullptr);



    EXPECT_EQ(os.str(), "(Exiv2::Value*)");

}



TEST_F(SonyMakerNoteTest_1605, PrintColorCompensationFilter_BoundaryCondition_ValueTypeNotUnsignedLong_1605) {

    Value value;

    value.makeArray(short);

    value[0] = 42;



    sonyMakerNote.printColorCompensationFilter(os, value, nullptr);



    EXPECT_EQ(os.str(), "(Exiv2::Value*)");

}



} } // namespace Exiv2::Internal
