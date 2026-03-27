#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include <sstream>

#include <iomanip>



// Mocking the Value class for the purposes of testing

class Value {

public:

    virtual ~Value() = default;

    virtual int32_t toRationalSecond() const = 0;

    virtual float toFloat() const = 0;

    virtual std::string toString() const = 0;

};



// Mock implementation of the Value class

class MockValue : public Value {

public:

    MOCK_CONST_METHOD0(toRationalSecond, int32_t());

    MOCK_CONST_METHOD0(toFloat, float());

    MOCK_CONST_METHOD0(toString, std::string());

};



namespace Exiv2 { namespace Internal {



std::ostream& print0x0006(std::ostream& os, const Value& value, const ExifData* exifData);



} } // namespace Exiv2::Internal



using ::testing::Return;

using ::testing::StrEq;



class Print0x0006Test_1385 : public ::testing::Test {

protected:

    std::ostringstream oss;

    MockValue mockValue;

};



TEST_F(Print0x0006Test_1385, NormalOperationWithNonZeroDenominator_1385) {

    EXPECT_CALL(mockValue, toRationalSecond()).WillOnce(Return(2));

    EXPECT_CALL(mockValue, toFloat()).WillOnce(Return(3.14159f));



    Exiv2::Internal::print0x0006(oss, mockValue, nullptr);

    EXPECT_EQ("3.1 m", oss.str());

}



TEST_F(Print0x0006Test_1385, NormalOperationWithDenominatorOne_1385) {

    EXPECT_CALL(mockValue, toRationalSecond()).WillOnce(Return(1));

    EXPECT_CALL(mockValue, toFloat()).WillOnce(Return(2.71f));



    Exiv2::Internal::print0x0006(oss, mockValue, nullptr);

    EXPECT_EQ("3 m", oss.str());

}



TEST_F(Print0x0006Test_1385, BoundaryConditionWithDenominatorZero_1385) {

    EXPECT_CALL(mockValue, toRationalSecond()).WillOnce(Return(0));

    EXPECT_CALL(mockValue, toString()).WillOnce(Return("(some_value)"));



    Exiv2::Internal::print0x0006(oss, mockValue, nullptr);

    EXPECT_EQ("(some_value)", oss.str());

}



TEST_F(Print0x0006Test_1385, ExceptionalCaseWithNegativeDenominator_1385) {

    EXPECT_CALL(mockValue, toRationalSecond()).WillOnce(Return(-1));

    EXPECT_CALL(mockValue, toFloat()).WillOnce(Return(1.41f));



    Exiv2::Internal::print0x0006(oss, mockValue, nullptr);

    EXPECT_EQ("1 m", oss.str());

}
