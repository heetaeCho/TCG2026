#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "tags_int.cpp"  // Assuming this is how we include the implementation



namespace Exiv2 {

    class ValueMock : public Value {

    public:

        MOCK_METHOD(Rational, toRational, (), (const override));

    };

}



using namespace Exiv2;

using namespace Exiv2::Internal;



class Print0x829dTest_1396 : public ::testing::Test {

protected:

    std::ostringstream os;

    testing::StrictMock<ValueMock> valueMock;

    const ExifData* exifDataPtr = nullptr;  // Assuming no interaction with this

};



TEST_F(Print0x829dTest_1396, NormalOperation_NonZeroDenominator_1396) {

    EXPECT_CALL(valueMock, toRational()).WillOnce(::testing::Return(Rational{45, 10}));

    print0x829d(os, valueMock, exifDataPtr);

    EXPECT_EQ(os.str(), "F4.5");

}



TEST_F(Print0x829dTest_1396, NormalOperation_ZeroDenominator_1396) {

    EXPECT_CALL(valueMock, toRational()).WillOnce(::testing::Return(Rational{45, 0}));

    print0x829d(os, valueMock, exifDataPtr);

    EXPECT_EQ(os.str(), "(value)");

}



TEST_F(Print0x829dTest_1396, BoundaryCondition_MaxIntegers_1396) {

    EXPECT_CALL(valueMock, toRational()).WillOnce(::testing::Return(Rational{INT_MAX, 1}));

    print0x829d(os, valueMock, exifDataPtr);

    EXPECT_EQ(os.str(), "F2.1475e+09");

}



TEST_F(Print0x829dTest_1396, BoundaryCondition_MinIntegers_1396) {

    EXPECT_CALL(valueMock, toRational()).WillOnce(::testing::Return(Rational{INT_MIN, 1}));

    print0x829d(os, valueMock, exifDataPtr);

    EXPECT_EQ(os.str(), "F-2.1475e+09");

}



TEST_F(Print0x829dTest_1396, BoundaryCondition_ZeroNumerator_1396) {

    EXPECT_CALL(valueMock, toRational()).WillOnce(::testing::Return(Rational{0, 1}));

    print0x829d(os, valueMock, exifDataPtr);

    EXPECT_EQ(os.str(), "F0");

}



TEST_F(Print0x829dTest_1396, ExceptionalCase_NegativeDenominator_1396) {

    EXPECT_CALL(valueMock, toRational()).WillOnce(::testing::Return(Rational{45, -10}));

    print0x829d(os, valueMock, exifDataPtr);

    EXPECT_EQ(os.str(), "F-4.5");

}
