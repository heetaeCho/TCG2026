#include <gtest/gtest.h>

#include "./TestProjects/Catch2/src/catch2/catch_tostring.hpp"



class CatchStrnlenTest : public ::testing::Test {

protected:

    using StrLenFunc = std::size_t (*)(const char*, std::size_t);

    StrLenFunc catch_strnlen_func;



    CatchStrnlenTest() : catch_strnlen_func(Catch::Detail::catch_strnlen) {}

};



TEST_F(CatchStrnlenTest, NormalOperation_73) {

    const char* testString = "HelloWorld";

    std::size_t maxLength = 20;

    EXPECT_EQ(catch_strnlen_func(testString, maxLength), strlen(testString));

}



TEST_F(CatchStrnlenTest, EmptyString_73) {

    const char* emptyString = "";

    std::size_t maxLength = 10;

    EXPECT_EQ(catch_strnlen_func(emptyString, maxLength), 0);

}



TEST_F(CatchStrnlenTest, MaxLengthZero_73) {

    const char* testString = "NonEmpty";

    std::size_t maxLength = 0;

    EXPECT_EQ(catch_strnlen_func(testString, maxLength), 0);

}



TEST_F(CatchStrnlenTest, LengthLessThanMax_73) {

    const char* testString = "Short";

    std::size_t maxLength = 10;

    EXPECT_EQ(catch_strnlen_func(testString, maxLength), strlen(testString));

}



TEST_F(CatchStrnlenTest, LengthEqualsMaxNoNullTerminator_73) {

    const char testArray[] = {'N', 'o', 'T', 'e', 'r', 'm'};

    std::size_t maxLength = sizeof(testArray);

    EXPECT_EQ(catch_strnlen_func(testArray, maxLength), maxLength);

}



TEST_F(CatchStrnlenTest, LengthGreaterThanMax_73) {

    const char* testString = "ThisIsAVeryLongString";

    std::size_t maxLength = 5;

    EXPECT_EQ(catch_strnlen_func(testString, maxLength), maxLength);

}
