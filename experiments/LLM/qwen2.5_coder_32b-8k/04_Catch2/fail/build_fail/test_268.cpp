#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "./TestProjects/Catch2/src/catch2/catch_tostring.hpp"



using namespace Catch;



TEST(StringMaker_byte_Test_268, ConvertZeroByte_268) {

    EXPECT_EQ(StringMaker<std::byte>::convert(static_cast<std::byte>(0)), "0");

}



TEST(StringMaker_byte_Test_268, ConvertMaxByte_268) {

    EXPECT_EQ(StringMaker<std::byte>::convert(static_cast<std::byte>(255)), "255");

}



TEST(StringMaker_byte_Test_268, ConvertMidRangeByte_268) {

    EXPECT_EQ(StringMaker<std::byte>::convert(static_cast<std::byte>(128)), "128");

}



// Assuming the behavior for negative bytes is undefined or not applicable since std::byte is unsigned

```


