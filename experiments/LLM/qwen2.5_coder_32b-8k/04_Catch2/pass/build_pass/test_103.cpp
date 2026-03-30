#include <gtest/gtest.h>

#include <chrono>

#include "catch_tostring.hpp"

#include "catch_reusable_string_stream.hpp"



using namespace Catch;



// Test fixture for StringMaker tests

class StringMakerTest_103 : public ::testing::Test {

protected:

    ReusableStringStream rss;

};



// Test normal operation with std::chrono::duration<std::chrono::hours>

TEST_F(StringMakerTest_103, ConvertChronoHours_NormalOperation_103) {

    auto duration = std::chrono::hours(5);

    std::string result = StringMaker<decltype(duration)>::convert(duration);

    EXPECT_EQ(result, "5 h");

}



// Test boundary condition with zero hours

TEST_F(StringMakerTest_103, ConvertChronoHours_ZeroDuration_103) {

    auto duration = std::chrono::hours(0);

    std::string result = StringMaker<decltype(duration)>::convert(duration);

    EXPECT_EQ(result, "0 h");

}



// Test boundary condition with maximum hours

TEST_F(StringMakerTest_103, ConvertChronoHours_MaxDuration_103) {

    auto duration = std::chrono::hours(std::numeric_limits<int64_t>::max());

    std::string result = StringMaker<decltype(duration)>::convert(duration);

    EXPECT_EQ(result, std::to_string(std::numeric_limits<int64_t>::max()) + " h");

}



// Test boundary condition with minimum hours

TEST_F(StringMakerTest_103, ConvertChronoHours_MinDuration_103) {

    auto duration = std::chrono::hours(std::numeric_limits<int64_t>::min());

    std::string result = StringMaker<decltype(duration)>::convert(duration);

    EXPECT_EQ(result, std::to_string(std::numeric_limits<int64_t>::min()) + " h");

}
