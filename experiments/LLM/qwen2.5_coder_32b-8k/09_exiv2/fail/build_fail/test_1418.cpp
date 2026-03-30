#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include <exiv2/exif.hpp>

#include <exiv2/value.hpp>

#include "tags_int.cpp"



using namespace testing;

using namespace Exiv2;

using namespace Exiv2::Internal;



class Print0xa409Test : public Test {

protected:

    std::ostringstream os;

    Value mockValue;

    const ExifData* metadata = nullptr;

};



TEST_F(Print0xa409Test, NormalOperation_1418) {

    EXPECT_CALL(mockValue, ok()).WillRepeatedly(Return(true));

    EXPECT_CALL(mockValue, toInt64(0)).WillOnce(Return(0)); // Assuming value represents "Normal"



    print0xa409(os, mockValue, metadata);



    EXPECT_EQ(os.str(), "Normal");

}



TEST_F(Print0xa409Test, BoundaryCondition_Low_1418) {

    EXPECT_CALL(mockValue, ok()).WillRepeatedly(Return(true));

    EXPECT_CALL(mockValue, toInt64(0)).WillOnce(Return(1)); // Assuming value represents "Low"



    print0xa409(os, mockValue, metadata);



    EXPECT_EQ(os.str(), "Low");

}



TEST_F(Print0xa409Test, BoundaryCondition_High_1418) {

    EXPECT_CALL(mockValue, ok()).WillRepeatedly(Return(true));

    EXPECT_CALL(mockValue, toInt64(0)).WillOnce(Return(2)); // Assuming value represents "High"



    print0xa409(os, mockValue, metadata);



    EXPECT_EQ(os.str(), "High");

}



TEST_F(Print0xa409Test, ErrorCase_InvalidValue_1418) {

    EXPECT_CALL(mockValue, ok()).WillRepeatedly(Return(true));

    EXPECT_CALL(mockValue, toInt64(0)).WillOnce(Return(3)); // Out of range value



    print0xa409(os, mockValue, metadata);



    EXPECT_EQ(os.str(), "Unknown saturation value 3");

}



TEST_F(Print0xa409Test, ErrorCase_ValueNotOk_1418) {

    EXPECT_CALL(mockValue, ok()).WillRepeatedly(Return(false));

    EXPECT_CALL(mockValue, toInt64(0)).Times(0); // Should not be called if Value is not OK



    print0xa409(os, mockValue, metadata);



    EXPECT_EQ(os.str(), "Invalid value");

}
