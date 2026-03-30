#include <gtest/gtest.h>

#include "exiv2/value.hpp"



using namespace Exiv2;



class AsciiValueTest_813 : public ::testing::Test {

protected:

    AsciiValue asciiValue;

};



TEST_F(AsciiValueTest_813, ReadNonEmptyBuffer_813) {

    std::string input = "Hello";

    int result = asciiValue.read(input);

    EXPECT_EQ(result, 0);

}



TEST_F(AsciiValueTest_813, ReadEmptyBuffer_813) {

    std::string input = "";

    int result = asciiValue.read(input);

    EXPECT_EQ(result, 0);

}



TEST_F(AsciiValueTest_813, ReadBufferWithNullTerminator_813) {

    std::string input = "Hello\0";

    int result = asciiValue.read(input);

    EXPECT_EQ(result, 0);

}



TEST_F(AsciiValueTest_813, ReadBufferWithoutNullTerminator_813) {

    std::string input = "Hello";

    int result = asciiValue.read(input);

    EXPECT_EQ(result, 0);

    EXPECT_EQ(asciiValue.value_.back(), '\0');

}



TEST_F(AsciiValueTest_813, ReadVeryLongBuffer_813) {

    std::string input(LARGE_INT, 'a'); // Assuming LARGE_INT is a macro defining a large number

    int result = asciiValue.read(input);

    EXPECT_EQ(result, 0);

    EXPECT_EQ(asciiValue.value_.back(), '\0');

}
