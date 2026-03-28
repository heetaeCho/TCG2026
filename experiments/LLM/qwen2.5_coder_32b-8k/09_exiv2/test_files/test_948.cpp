#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "./TestProjects/exiv2/src/canonmn_int.cpp"



namespace Exiv2 {

    class ErrorMock : public Error {

    public:

        using Error::Error;

        MOCK_METHOD(void, raise, (), (const override));

    };

}



using namespace Exiv2::Internal;



TEST(string_to_float_948, NormalOperation_PositiveNumber_948) {

    EXPECT_FLOAT_EQ(string_to_float("123.456"), 123.456f);

}



TEST(string_to_float_948, NormalOperation_NegativeNumber_948) {

    EXPECT_FLOAT_EQ(string_to_float("-123.456"), -123.456f);

}



TEST(string_to_float_948, NormalOperation_Zero_948) {

    EXPECT_FLOAT_EQ(string_to_float("0"), 0.0f);

}



TEST(string_to_float_948, BoundaryCondition_MaxFloat_948) {

    EXPECT_FLOAT_EQ(string_to_float(std::to_string(std::numeric_limits<float>::max())), std::numeric_limits<float>::max());

}



TEST(string_to_float_948, BoundaryCondition_MinFloat_948) {

    EXPECT_FLOAT_EQ(string_to_float(std::to_string(-std::numeric_limits<float>::max())), -std::numeric_limits<float>::max());

}



TEST(string_to_float_948, ExceptionalCase_EmptyString_948) {

    EXPECT_THROW({

        try {

            string_to_float("");

        } catch (const Error& e) {

            EXPECT_EQ(e.code(), ErrorCode::kerErrorMessage);

            throw;

        }

    }, Error);

}



TEST(string_to_float_948, ExceptionalCase_NonNumericString_948) {

    EXPECT_THROW({

        try {

            string_to_float("abc");

        } catch (const Error& e) {

            EXPECT_EQ(e.code(), ErrorCode::kerErrorMessage);

            throw;

        }

    }, Error);

}



TEST(string_to_float_948, ExceptionalCase_InvalidNumberFormat_948) {

    EXPECT_THROW({

        try {

            string_to_float("123.abc");

        } catch (const Error& e) {

            EXPECT_EQ(e.code(), ErrorCode::kerErrorMessage);

            throw;

        }

    }, Error);

}
