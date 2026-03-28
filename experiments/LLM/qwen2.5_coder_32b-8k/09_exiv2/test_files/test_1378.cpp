#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include <sstream>

#include "tags_int.cpp"  // Assuming this file contains the definition of printFloat



namespace Exiv2 {

    class ValueMock : public Value {

    public:

        MOCK_METHOD(Rational, toRational, (), const);

        MOCK_METHOD(float, toFloat, (), const);

        MOCK_METHOD(std::ostream&, write, (std::ostream& os), const);

        MOCK_METHOD(std::string, toString, (), const);

    };

}



using namespace Exiv2;

using namespace Exiv2::Internal;

using ::testing::Return;



class PrintFloatTest_1378 : public ::testing::Test {

protected:

    std::ostringstream oss;

    ValueMock valueMock;

};



TEST_F(PrintFloatTest_1378, NonZeroDenominatorOutputsFloatValue_1378) {

    EXPECT_CALL(valueMock, toRational()).WillOnce(Return(Rational(3, 2)));

    EXPECT_CALL(valueMock, toFloat()).WillOnce(Return(1.5f));



    printFloat(oss, valueMock, nullptr);

    EXPECT_EQ(oss.str(), "1.5");

}



TEST_F(PrintFloatTest_1378, ZeroDenominatorOutputsValueInParentheses_1378) {

    EXPECT_CALL(valueMock, toRational()).WillOnce(Return(Rational(3, 0)));

    EXPECT_CALL(valueMock, toString()).WillOnce(Return("Rational(3/0)"));



    printFloat(oss, valueMock, nullptr);

    EXPECT_EQ(oss.str(), "(Rational(3/0))");

}



TEST_F(PrintFloatTest_1378, NegativeValueWithNonZeroDenominatorOutputsNegativeFloat_1378) {

    EXPECT_CALL(valueMock, toRational()).WillOnce(Return(Rational(-3, 2)));

    EXPECT_CALL(valueMock, toFloat()).WillOnce(Return(-1.5f));



    printFloat(oss, valueMock, nullptr);

    EXPECT_EQ(oss.str(), "-1.5");

}



TEST_F(PrintFloatTest_1378, NegativeValueWithZeroDenominatorOutputsNegativeValueInParentheses_1378) {

    EXPECT_CALL(valueMock, toRational()).WillOnce(Return(Rational(-3, 0)));

    EXPECT_CALL(valueMock, toString()).WillOnce(Return("Rational(-3/0)"));



    printFloat(oss, valueMock, nullptr);

    EXPECT_EQ(oss.str(), "(Rational(-3/0))");

}
