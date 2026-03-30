#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "exiv2/exif.hpp"

#include "exiv2/value.hpp"



using namespace Exiv2;

using namespace Exiv2::Internal;

using testing::_;

using testing::Return;



class MockValue : public Value {

public:

    MOCK_METHOD(size_t, count, (), (const));

    MOCK_METHOD(std::string, toString, (size_t n), (const));

};



TEST_F(PrintTagStringTest_179, NormalOperation_OneElement_179) {

    MockValue mockValue;

    ExifData exifData;



    EXPECT_CALL(mockValue, count()).WillOnce(Return(1));

    EXPECT_CALL(mockValue, toString(0)).WillOnce(Return("test"));



    std::ostringstream os;

    printTagString2(os, mockValue, &exifData);



    EXPECT_EQ(os.str(), "(test)");

}



TEST_F(PrintTagStringTest_179, NormalOperation_TwoElements_179) {

    MockValue mockValue;

    ExifData exifData;



    EXPECT_CALL(mockValue, count()).WillOnce(Return(2));

    EXPECT_CALL(mockValue, toString(0)).WillOnce(Return("test1"));

    EXPECT_CALL(mockValue, toString(1)).WillOnce(Return("test2"));



    std::ostringstream os;

    printTagString2(os, mockValue, &exifData);



    EXPECT_EQ(os.str(), "test1 test2");

}



TEST_F(PrintTagStringTest_179, BoundaryCondition_ZeroElements_179) {

    MockValue mockValue;

    ExifData exifData;



    EXPECT_CALL(mockValue, count()).WillOnce(Return(0));



    std::ostringstream os;

    printTagString2(os, mockValue, &exifData);



    EXPECT_EQ(os.str(), "()");

}



TEST_F(PrintTagStringTest_179, BoundaryCondition_OneElement_EmptyString_179) {

    MockValue mockValue;

    ExifData exifData;



    EXPECT_CALL(mockValue, count()).WillOnce(Return(1));

    EXPECT_CALL(mockValue, toString(0)).WillOnce(Return(""));



    std::ostringstream os;

    printTagString2(os, mockValue, &exifData);



    EXPECT_EQ(os.str(), "( )");

}



TEST_F(PrintTagStringTest_179, ExceptionalCase_LargeCount_ReturnsPartialResult_179) {

    MockValue mockValue;

    ExifData exifData;



    EXPECT_CALL(mockValue, count()).WillOnce(Return(LARGE_INT));

    EXPECT_CALL(mockValue, toString(0)).WillOnce(Return("test1"));

    EXPECT_CALL(mockValue, toString(1)).WillOnce(Return("test2"));



    std::ostringstream os;

    printTagString2(os, mockValue, &exifData);



    EXPECT_EQ(os.str(), "test1 test2");

}
