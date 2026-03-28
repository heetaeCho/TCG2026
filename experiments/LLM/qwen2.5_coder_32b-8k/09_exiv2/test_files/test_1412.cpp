#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "exiv2/exif.hpp"

#include "exiv2/value.hpp"

#include "./TestProjects/exiv2/src/tags_int.cpp"



using namespace Exiv2;

using namespace Exiv2::Internal;

using testing::_;

using testing::Ref;



class Print0xa402Test_1412 : public ::testing::Test {

protected:

    Value mockValue;

    ExifData mockMetadata;

};



TEST_F(Print0xa402Test_1412, NormalOperation_Auto_1412) {

    EXPECT_CALL(mockValue, toInt64(0)).WillOnce(testing::Return(0));

    std::ostringstream os;

    print0xa402(os, mockValue, &mockMetadata);

    EXPECT_EQ("Auto", os.str());

}



TEST_F(Print0xa402Test_1412, NormalOperation_Manual_1412) {

    EXPECT_CALL(mockValue, toInt64(0)).WillOnce(testing::Return(1));

    std::ostringstream os;

    print0xa402(os, mockValue, &mockMetadata);

    EXPECT_EQ("Manual", os.str());

}



TEST_F(Print0xa402Test_1412, NormalOperation_AutoBracket_1412) {

    EXPECT_CALL(mockValue, toInt64(0)).WillOnce(testing::Return(2));

    std::ostringstream os;

    print0xa402(os, mockValue, &mockMetadata);

    EXPECT_EQ("Auto bracket", os.str());

}



TEST_F(Print0xa402Test_1412, BoundaryCondition_OutOfRange_1412) {

    EXPECT_CALL(mockValue, toInt64(0)).WillOnce(testing::Return(3));

    std::ostringstream os;

    print0xa402(os, mockValue, &mockMetadata);

    EXPECT_EQ("Unknown", os.str());

}



TEST_F(Print0xa402Test_1412, BoundaryCondition_Negative_1412) {

    EXPECT_CALL(mockValue, toInt64(0)).WillOnce(testing::Return(-1));

    std::ostringstream os;

    print0xa402(os, mockValue, &mockMetadata);

    EXPECT_EQ("Unknown", os.str());

}



TEST_F(Print0xa402Test_1412, ExceptionalCase_ValueNotOk_1412) {

    mockValue.ok_ = false;

    std::ostringstream os;

    print0xa402(os, mockValue, &mockMetadata);

    EXPECT_EQ("", os.str());

}
