#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "tags_int.cpp"



namespace Exiv2 {

    namespace Internal {

        class MockValue : public Value {

        public:

            MOCK_CONST_METHOD1(toInt64, int64_t(size_t index)) const;

            MOCK_CONST_METHOD0(count, size_t()) const;

        };

    }

}



using namespace Exiv2::Internal;



class Print0x9101Test_1399 : public ::testing::Test {

protected:

    MockValue mock_value;

};



TEST_F(Print0x9101Test_1399, EmptyValue_1399) {

    EXPECT_CALL(mock_value, count()).WillOnce(::testing::Return(0));



    std::ostringstream oss;

    print0x9101(oss, mock_value, nullptr);



    EXPECT_EQ("", oss.str());

}



TEST_F(Print0x9101Test_1399, SingleZeroValue_1399) {

    EXPECT_CALL(mock_value, count()).WillOnce(::testing::Return(1));

    EXPECT_CALL(mock_value, toInt64(0)).WillOnce(::testing::Return(0));



    std::ostringstream oss;

    print0x9101(oss, mock_value, nullptr);



    EXPECT_EQ("", oss.str());

}



TEST_F(Print0x9101Test_1399, SingleYValue_1399) {

    EXPECT_CALL(mock_value, count()).WillOnce(::testing::Return(1));

    EXPECT_CALL(mock_value, toInt64(0)).WillOnce(::testing::Return(1));



    std::ostringstream oss;

    print0x9101(oss, mock_value, nullptr);



    EXPECT_EQ("Y", oss.str());

}



TEST_F(Print0x9101Test_1399, MultipleValues_1399) {

    EXPECT_CALL(mock_value, count()).WillOnce(::testing::Return(6));

    EXPECT_CALL(mock_value, toInt64(0)).WillOnce(::testing::Return(2));

    EXPECT_CALL(mock_value, toInt64(1)).WillOnce(::testing::Return(3));

    EXPECT_CALL(mock_value, toInt64(2)).WillOnce(::testing::Return(4));

    EXPECT_CALL(mock_value, toInt64(3)).WillOnce(::testing::Return(5));

    EXPECT_CALL(mock_value, toInt64(4)).WillOnce(::testing::Return(6));

    EXPECT_CALL(mock_value, toInt64(5)).WillOnce(::testing::Return(0));



    std::ostringstream oss;

    print0x9101(oss, mock_value, nullptr);



    EXPECT_EQ("CbCrRGB", oss.str());

}



TEST_F(Print0x9101Test_1399, DefaultCaseValue_1399) {

    EXPECT_CALL(mock_value, count()).WillOnce(::testing::Return(2));

    EXPECT_CALL(mock_value, toInt64(0)).WillOnce(::testing::Return(7));

    EXPECT_CALL(mock_value, toInt64(1)).WillOnce(::testing::Return(8));



    std::ostringstream oss;

    print0x9101(oss, mock_value, nullptr);



    EXPECT_EQ("(7)(8)", oss.str());

}



TEST_F(Print0x9101Test_1399, MixedValues_1399) {

    EXPECT_CALL(mock_value, count()).WillOnce(::testing::Return(5));

    EXPECT_CALL(mock_value, toInt64(0)).WillOnce(::testing::Return(1));

    EXPECT_CALL(mock_value, toInt64(1)).WillOnce(::testing::Return(2));

    EXPECT_CALL(mock_value, toInt64(2)).WillOnce(::testing::Return(7));

    EXPECT_CALL(mock_value, toInt64(3)).WillOnce(::testing::Return(3));

    EXPECT_CALL(mock_value, toInt64(4)).WillOnce(::testing::Return(8));



    std::ostringstream oss;

    print0x9101(oss, mock_value, nullptr);



    EXPECT_EQ("YCb(7)Cr(8)", oss.str());

}
