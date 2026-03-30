#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include <iostream>

#include <sstream>

#include "tags_int.cpp"  // Assuming this is how we include the partial implementation



namespace Exiv2 {

    class Value {

    public:

        virtual ~Value() = default;

        virtual bool ok() const = 0;

        virtual Rational toRational() const = 0;

    };



    struct Rational {

        int first;

        int second;

    };



    struct URational {

        float first;

        int second;

    };



    class MockValue : public Value {

    public:

        MOCK_CONST_METHOD0(ok, bool());

        MOCK_CONST_METHOD0(toRational, Rational());

    };



    URational exposureTime(float value) {

        // This is a mock implementation for the sake of testing.

        // In real scenarios, this function should be part of the codebase or mocked as well.

        return {value, 1};

    }



    namespace Internal {

        std::ostream& print0x9201(std::ostream& os, const Value& value, const ExifData* exifData);

    }

}



using namespace Exiv2;

using namespace Exiv2::Internal;



class Print0x9201Test_1400 : public ::testing::Test {

protected:

    MockValue mockValue;

};



TEST_F(Print0x9201Test_1400, NormalOperation_1400) {

    EXPECT_CALL(mockValue, ok()).WillOnce(::testing::Return(true));

    EXPECT_CALL(mockValue, toRational()).WillOnce(::testing::Return(Rational{1, 2}));



    std::ostringstream os;

    print0x9201(os, mockValue, nullptr);



    EXPECT_EQ("0.5 s", os.str());

}



TEST_F(Print0x9201Test_1400, BoundaryCondition_ZeroDenominator_1400) {

    EXPECT_CALL(mockValue, ok()).WillOnce(::testing::Return(true));

    EXPECT_CALL(mockValue, toRational()).WillOnce(::testing::Return(Rational{1, 0}));



    std::ostringstream os;

    print0x9201(os, mockValue, nullptr);



    EXPECT_EQ("(1/0) s", os.str());

}



TEST_F(Print0x9201Test_1400, BoundaryCondition_NegativeNumerator_1400) {

    EXPECT_CALL(mockValue, ok()).WillOnce(::testing::Return(true));

    EXPECT_CALL(mockValue, toRational()).WillOnce(::testing::Return(Rational{-1, 2}));



    std::ostringstream os;

    print0x9201(os, mockValue, nullptr);



    EXPECT_EQ("-0.5 s", os.str());

}



TEST_F(Print0x9201Test_1400, BoundaryCondition_NegativeDenominator_1400) {

    EXPECT_CALL(mockValue, ok()).WillOnce(::testing::Return(true));

    EXPECT_CALL(mockValue, toRational()).WillOnce(::testing::Return(Rational{1, -2}));



    std::ostringstream os;

    print0x9201(os, mockValue, nullptr);



    EXPECT_EQ("-0.5 s", os.str());

}



TEST_F(Print0x9201Test_1400, ErrorCase_ValueNotOk_1400) {

    EXPECT_CALL(mockValue, ok()).WillOnce(::testing::Return(false));



    std::ostringstream os;

    print0x9201(os, mockValue, nullptr);



    EXPECT_EQ("(Exiv2::Internal::MockValue object) s", os.str());

}
