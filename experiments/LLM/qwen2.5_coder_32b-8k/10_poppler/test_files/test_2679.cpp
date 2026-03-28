#include <gtest/gtest.h>

#include <string_view>



// Assuming the trim function is part of a namespace or a class.

// For this example, we will assume it's in a utility namespace.

namespace utils {

    static std::string_view trim(std::string_view input) { 

        size_t first = input.find_first_not_of(" \t"); 

        if (first == std::string_view::npos) { 

            return {}; 

        } 

        size_t last = input.find_last_not_of(" \t"); 

        return input.substr(first, last - first + 1); 

    }

}



// Test suite for the trim function

class TrimFunctionTest_2679 : public ::testing::Test {

protected:

    // You can add any setup code here if needed

};



TEST_F(TrimFunctionTest_2679, NormalOperation_2679) {

    std::string_view input = "   Hello, World!   ";

    std::string_view expected_output = "Hello, World!";

    EXPECT_EQ(utils::trim(input), expected_output);

}



TEST_F(TrimFunctionTest_2679, LeadingSpaces_2679) {

    std::string_view input = "   Hello, World!";

    std::string_view expected_output = "Hello, World!";

    EXPECT_EQ(utils::trim(input), expected_output);

}



TEST_F(TrimFunctionTest_2679, TrailingSpaces_2679) {

    std::string_view input = "Hello, World!   ";

    std::string_view expected_output = "Hello, World!";

    EXPECT_EQ(utils::trim(input), expected_output);

}



TEST_F(TrimFunctionTest_2679, LeadingAndTrailingTabs_2679) {

    std::string_view input = "\t\tHello, World!\t";

    std::string_view expected_output = "Hello, World!";

    EXPECT_EQ(utils::trim(input), expected_output);

}



TEST_F(TrimFunctionTest_2679, NoSpaces_2679) {

    std::string_view input = "Hello, World!";

    std::string_view expected_output = "Hello, World!";

    EXPECT_EQ(utils::trim(input), expected_output);

}



TEST_F(TrimFunctionTest_2679, OnlySpaces_2679) {

    std::string_view input = "       ";

    std::string_view expected_output = "";

    EXPECT_EQ(utils::trim(input), expected_output);

}



TEST_F(TrimFunctionTest_2679, EmptyString_2679) {

    std::string_view input = "";

    std::string_view expected_output = "";

    EXPECT_EQ(utils::trim(input), expected_output);

}
