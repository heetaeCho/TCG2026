#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "samsungmn_int.cpp"

#include <sstream>



using namespace Exiv2::Internal;

using ::testing::_;



// Mock class for Value

class MockValue : public Exiv2::Value {

public:

    MOCK_CONST_METHOD0(count, long());

    MOCK_CONST_METHOD0(typeId, Exiv2::TypeId());

    MOCK_CONST_METHOD0(toFloat, float());

};



TEST(printCameraTemperatureTest_1721, NormalOperation_SingleSignedRational_1721) {

    MockValue mockValue;

    std::ostringstream oss;



    EXPECT_CALL(mockValue, count()).WillOnce(::testing::Return(1));

    EXPECT_CALL(mockValue, typeId()).WillOnce(::testing::Return(signedRational));

    EXPECT_CALL(mockValue, toFloat()).WillOnce(::testing::Return(25.0f));



    printCameraTemperature(oss, mockValue, nullptr);



    EXPECT_EQ("25 C", oss.str());

}



TEST(printCameraTemperatureTest_1721, BoundaryCondition_ZeroCount_1721) {

    MockValue mockValue;

    std::ostringstream oss;



    EXPECT_CALL(mockValue, count()).WillOnce(::testing::Return(0));



    printCameraTemperature(oss, mockValue, nullptr);



    // Since count is not 1, it should return the value as is.

    EXPECT_EQ("", oss.str());

}



TEST(printCameraTemperatureTest_1721, BoundaryCondition_MultipleCount_1721) {

    MockValue mockValue;

    std::ostringstream oss;



    EXPECT_CALL(mockValue, count()).WillOnce(::testing::Return(2));



    printCameraTemperature(oss, mockValue, nullptr);



    // Since count is not 1, it should return the value as is.

    EXPECT_EQ("", oss.str());

}



TEST(printCameraTemperatureTest_1721, ExceptionalCase_WrongTypeId_1721) {

    MockValue mockValue;

    std::ostringstream oss;



    EXPECT_CALL(mockValue, count()).WillOnce(::testing::Return(1));

    EXPECT_CALL(mockValue, typeId()).WillOnce(::testing::Return(unsignedShort));



    printCameraTemperature(oss, mockValue, nullptr);



    // Since type is not signedRational, it should return the value as is.

    EXPECT_EQ("", oss.str());

}



TEST(printCameraTemperatureTest_1721, ExternalInteraction_ValueToString_1721) {

    MockValue mockValue;

    std::ostringstream oss;



    EXPECT_CALL(mockValue, count()).WillOnce(::testing::Return(1));

    EXPECT_CALL(mockValue, typeId()).WillOnce(::testing::Return(signedRational));

    EXPECT_CALL(mockValue, toFloat()).WillOnce(::testing::Return(30.5f));



    printCameraTemperature(oss, mockValue, nullptr);



    EXPECT_EQ("30.5 C", oss.str());

}
