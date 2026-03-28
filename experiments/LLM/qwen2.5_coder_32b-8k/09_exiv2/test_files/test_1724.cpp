#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "samsungmn_int.cpp"



namespace Exiv2 {

    class ValueMock : public Value {

    public:

        MOCK_METHOD(size_t, count, (), (const));

        MOCK_METHOD(TypeId, typeId, (), (const));

        MOCK_METHOD(int64_t, toInt64, (size_t) const, (const));

    };

}



using namespace Exiv2;

using namespace Exiv2::Internal;



class PrintValueMinus4Test_1724 : public ::testing::Test {

protected:

    ValueMock value_mock;

};



TEST_F(PrintValueMinus4Test_1724, NormalOperation_UShortCountOne_1724) {

    EXPECT_CALL(value_mock, count()).WillOnce(::testing::Return(1));

    EXPECT_CALL(value_mock, typeId()).WillOnce(::testing::Return(unsignedShort));

    EXPECT_CALL(value_mock, toInt64(0)).WillOnce(::testing::Return(10));



    std::ostringstream os;

    printValueMinus4(os, value_mock, nullptr);



    ASSERT_EQ(os.str(), "6");

}



TEST_F(PrintValueMinus4Test_1724, BoundaryCondition_CountZero_1724) {

    EXPECT_CALL(value_mock, count()).WillOnce(::testing::Return(0));

    EXPECT_CALL(value_mock, typeId()).WillOnce(::testing::Return(unsignedShort));



    std::ostringstream os;

    printValueMinus4(os, value_mock, nullptr);



    ASSERT_EQ(os.str(), "Exiv2::Value");

}



TEST_F(PrintValueMinus4Test_1724, BoundaryCondition_CountTwo_1724) {

    EXPECT_CALL(value_mock, count()).WillOnce(::testing::Return(2));

    EXPECT_CALL(value_mock, typeId()).WillOnce(::testing::Return(unsignedShort));



    std::ostringstream os;

    printValueMinus4(os, value_mock, nullptr);



    ASSERT_EQ(os.str(), "Exiv2::Value");

}



TEST_F(PrintValueMinus4Test_1724, ExceptionalCase_WrongTypeId_1724) {

    EXPECT_CALL(value_mock, count()).WillOnce(::testing::Return(1));

    EXPECT_CALL(value_mock, typeId()).WillOnce(::testing::Return(long));



    std::ostringstream os;

    printValueMinus4(os, value_mock, nullptr);



    ASSERT_EQ(os.str(), "Exiv2::Value");

}



TEST_F(PrintValueMinus4Test_1724, ExceptionalCase_NegativeValue_1724) {

    EXPECT_CALL(value_mock, count()).WillOnce(::testing::Return(1));

    EXPECT_CALL(value_mock, typeId()).WillOnce(::testing::Return(unsignedShort));

    EXPECT_CALL(value_mock, toInt64(0)).WillOnce(::testing::Return(-5));



    std::ostringstream os;

    printValueMinus4(os, value_mock, nullptr);



    ASSERT_EQ(os.str(), "-9");

}
