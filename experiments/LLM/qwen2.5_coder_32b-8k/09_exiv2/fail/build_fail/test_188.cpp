#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "exiv2/exif.hpp"

#include "exiv2/value.hpp"

#include "TestProjects/exiv2/src/pentaxmn_int.cpp"



using namespace Exiv2;

using namespace Exiv2::Internal;

using ::testing::_;

using ::testing::Return;



class PrintCombiTagTest_188 : public ::testing::Test {

protected:

    TagDetails tagDetailsArray[1] = {{"Label", 0x01020304}};

};



TEST_F(PrintCombiTagTest_188, NormalOperation_188) {

    Value value;

    EXPECT_CALL(value, count()).WillRepeatedly(Return(4));

    EXPECT_CALL(value, toInt64(0)).WillOnce(Return(1));

    EXPECT_CALL(value, toInt64(1)).WillOnce(Return(2));

    EXPECT_CALL(value, toInt64(2)).WillOnce(Return(3));

    EXPECT_CALL(value, toInt64(3)).WillOnce(Return(4));



    std::ostringstream os;

    printCombiTag<1>(os, value, nullptr);



    EXPECT_EQ(os.str(), "Label");

}



TEST_F(PrintCombiTagTest_188, BoundaryCondition_CountZero_188) {

    Value value;

    EXPECT_CALL(value, count()).WillOnce(Return(0));



    std::ostringstream os;

    printCombiTag<1>(os, value, nullptr);



    EXPECT_EQ(os.str(), "Unknown (0x)");

}



TEST_F(PrintCombiTagTest_188, BoundaryCondition_CountOne_188) {

    Value value;

    EXPECT_CALL(value, count()).WillRepeatedly(Return(1));

    EXPECT_CALL(value, toInt64(0)).WillOnce(Return(1));



    std::ostringstream os;

    printCombiTag<1>(os, value, nullptr);



    EXPECT_EQ(os.str(), "Label");

}



TEST_F(PrintCombiTagTest_188, BoundaryCondition_CountFour_188) {

    Value value;

    EXPECT_CALL(value, count()).WillRepeatedly(Return(4));

    EXPECT_CALL(value, toInt64(0)).WillOnce(Return(1));

    EXPECT_CALL(value, toInt64(1)).WillOnce(Return(2));

    EXPECT_CALL(value, toInt64(2)).WillOnce(Return(3));

    EXPECT_CALL(value, toInt64(3)).WillOnce(Return(4));



    std::ostringstream os;

    printCombiTag<1>(os, value, nullptr);



    EXPECT_EQ(os.str(), "Label");

}



TEST_F(PrintCombiTagTest_188, BoundaryCondition_CountFive_188) {

    Value value;

    EXPECT_CALL(value, count()).WillOnce(Return(5));



    std::ostringstream os;

    printCombiTag<1>(os, value, nullptr);



    EXPECT_EQ(os.str(), "Unknown (0x)");

}



TEST_F(PrintCombiTagTest_188, ExceptionalCase_ValueNegative_188) {

    Value value;

    EXPECT_CALL(value, count()).WillRepeatedly(Return(4));

    EXPECT_CALL(value, toInt64(0)).WillOnce(Return(-1));



    std::ostringstream os;

    printCombiTag<1>(os, value, nullptr);



    EXPECT_EQ(os.str(), "Unknown (0x)");

}



TEST_F(PrintCombiTagTest_188, ExceptionalCase_ValueAbove255_188) {

    Value value;

    EXPECT_CALL(value, count()).WillRepeatedly(Return(4));

    EXPECT_CALL(value, toInt64(0)).WillOnce(Return(256));



    std::ostringstream os;

    printCombiTag<1>(os, value, nullptr);



    EXPECT_EQ(os.str(), "Unknown (0x)");

}
