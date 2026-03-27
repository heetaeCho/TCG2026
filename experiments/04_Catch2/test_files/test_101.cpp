#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include <catch2/catch_tostring.hpp>

#include <chrono>



using namespace Catch;

using ::testing::Return;



TEST(convert_duration_test_101, NormalOperation_101) {

    std::chrono::duration<int64_t> duration(5);

    EXPECT_EQ(StringMaker<std::chrono::duration<int64_t>>::convert(duration), "5 s");

}



TEST(convert_duration_test_101, BoundaryCondition_Zero_101) {

    std::chrono::duration<int64_t> duration(0);

    EXPECT_EQ(StringMaker<std::chrono::duration<int64_t>>::convert(duration), "0 s");

}



TEST(convert_duration_test_101, BoundaryCondition_Max_101) {

    std::chrono::duration<int64_t> duration(std::numeric_limits<int64_t>::max());

    std::string expected = std::to_string(std::numeric_limits<int64_t>::max()) + " s";

    EXPECT_EQ(StringMaker<std::chrono::duration<int64_t>>::convert(duration), expected);

}



TEST(convert_duration_test_101, BoundaryCondition_Min_101) {

    std::chrono::duration<int64_t> duration(std::numeric_limits<int64_t>::min());

    std::string expected = std::to_string(std::numeric_limits<int64_t>::min()) + " s";

    EXPECT_EQ(StringMaker<std::chrono::duration<int64_t>>::convert(duration), expected);

}



TEST(convert_duration_test_101, NegativeValue_101) {

    std::chrono::duration<int64_t> duration(-3);

    EXPECT_EQ(StringMaker<std::chrono::duration<int64_t>>::convert(duration), "-3 s");

}
