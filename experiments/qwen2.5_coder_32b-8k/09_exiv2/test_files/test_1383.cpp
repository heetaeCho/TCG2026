#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include <sstream>

#include "tags_int.hpp"  // Assuming the header file for Exiv2::Internal::print0x0000 is tags_int.hpp



using namespace testing;

using namespace Exiv2::Internal;



class Print0x0000Test_1383 : public Test {

protected:

    std::ostringstream os;

    Value mockValue;

};



TEST_F(Print0x0000Test_1383, NormalOperation_UIntegers_1383) {

    EXPECT_CALL(mockValue, size()).WillRepeatedly(Return(4));

    EXPECT_CALL(mockValue, typeId()).WillRepeatedly(Return(unsignedByte));



    EXPECT_CALL(mockValue, toInt64(0)).WillOnce(Return(192));

    EXPECT_CALL(mockValue, toInt64(1)).WillOnce(Return(168));

    EXPECT_CALL(mockValue, toInt64(2)).WillOnce(Return(0));

    EXPECT_CALL(mockValue, toInt64(3)).WillOnce(Return(1));



    print0x0000(os, mockValue, nullptr);



    EXPECT_EQ("192.168.0.1", os.str());

}



TEST_F(Print0x0000Test_1383, BoundaryCondition_SizeNot4_1383) {

    EXPECT_CALL(mockValue, size()).WillRepeatedly(Return(5));

    EXPECT_CALL(mockValue, typeId()).WillRepeatedly(Return(unsignedByte));



    print0x0000(os, mockValue, nullptr);



    // Assuming Value::operator<< is defined to handle this case

    EXPECT_EQ("Exiv2::Value", os.str());

}



TEST_F(Print0x0000Test_1383, BoundaryCondition_TypeNotUnsignedByte_1383) {

    EXPECT_CALL(mockValue, size()).WillRepeatedly(Return(4));

    EXPECT_CALL(mockValue, typeId()).WillRepeatedly(Return(short));



    print0x0000(os, mockValue, nullptr);



    // Assuming Value::operator<< is defined to handle this case

    EXPECT_EQ("Exiv2::Value", os.str());

}



TEST_F(Print0x0000Test_1383, ExceptionalCase_ValueOperatorThrows_1383) {

    EXPECT_CALL(mockValue, size()).WillRepeatedly(Return(4));

    EXPECT_CALL(mockValue, typeId()).WillRepeatedly(Return(unsignedByte));



    EXPECT_CALL(mockValue, toInt64(_)).WillOnce(Throw(std::runtime_error("Error")));



    print0x0000(os, mockValue, nullptr);



    // Assuming Value::operator<< is defined to handle this case

    EXPECT_EQ("Exiv2::Value", os.str());

}

```


