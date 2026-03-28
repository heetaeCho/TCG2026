#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "exiv2/exif.hpp"

#include "exiv2/value.hpp"



using namespace Exiv2;

using namespace testing;



class Print0x0009Test_1387 : public Test {

protected:

    std::ostringstream os;

    Value value;

    const ExifData* metadata = nullptr;



    void SetUp() override {

        // Setup if necessary

    }

};



TEST_F(Print0x0009Test_1387, NormalOperation_A_1387) {

    EXPECT_CALL(value, ok()).WillRepeatedly(Return(true));

    value.setDataArea(reinterpret_cast<const byte*>("A"), 1);

    Internal::print0x0009(os, value, metadata);

    EXPECT_EQ(os.str(), "Measurement in progress");

}



TEST_F(Print0x0009Test_1387, NormalOperation_V_1387) {

    EXPECT_CALL(value, ok()).WillRepeatedly(Return(true));

    value.setDataArea(reinterpret_cast<const byte*>("V"), 1);

    Internal::print0x0009(os, value, metadata);

    EXPECT_EQ(os.str(), "Measurement interrupted");

}



TEST_F(Print0x0009Test_1387, BoundaryCondition_EmptyData_1387) {

    EXPECT_CALL(value, ok()).WillRepeatedly(Return(true));

    value.setDataArea(reinterpret_cast<const byte*>(""), 0);

    Internal::print0x0009(os, value, metadata);

    EXPECT_EQ(os.str(), "");

}



TEST_F(Print0x0009Test_1387, BoundaryCondition_UnknownCharacter_1387) {

    EXPECT_CALL(value, ok()).WillRepeatedly(Return(true));

    value.setDataArea(reinterpret_cast<const byte*>("X"), 1);

    Internal::print0x0009(os, value, metadata);

    EXPECT_EQ(os.str(), "");

}



TEST_F(Print0x0009Test_1387, ExceptionalCase_ValueNotOk_1387) {

    EXPECT_CALL(value, ok()).WillRepeatedly(Return(false));

    Internal::print0x0009(os, value, metadata);

    EXPECT_EQ(os.str(), "");

}
