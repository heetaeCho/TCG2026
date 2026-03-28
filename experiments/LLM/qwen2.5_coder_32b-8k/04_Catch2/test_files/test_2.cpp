#include <gtest/gtest.h>

#include "catch2/internal/catch_reusable_string_stream.hpp"



class ReusableStringStreamTest : public ::testing::Test {

protected:

    Catch::ReusableStringStream stream;

};



TEST_F(ReusableStringStreamTest_2, GetReturnsOstreamReference_2) {

    EXPECT_NO_THROW(stream.get());

}



TEST_F(ReusableStringStreamTest_2, StrDefaultIsEmpty_2) {

    EXPECT_EQ(stream.str(), "");

}



TEST_F(ReusableStringStreamTest_2, StrSetAndGet_2) {

    stream.str("Hello, World!");

    EXPECT_EQ(stream.str(), "Hello, World!");

}



TEST_F(ReusableStringStreamTest_2, OperatorLeftShiftSetsString_2) {

    stream << "Hello, World!";

    EXPECT_EQ(stream.str(), "Hello, World!");

}



TEST_F(ReusableStringStreamTest_2, MultipleOperatorLeftShiftConcatenatesStrings_2) {

    stream << "Hello, ";

    stream << "World!";

    EXPECT_EQ(stream.str(), "Hello, World!");

}



TEST_F(ReusableStringStreamTest_2, ResetStrAfterSetAndGet_2) {

    stream.str("Initial");

    stream.str("");

    EXPECT_EQ(stream.str(), "");

}
