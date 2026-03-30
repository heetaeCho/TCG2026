#include <gtest/gtest.h>



// Assuming Unicode is defined as a type alias for unsigned int or similar.

using Unicode = unsigned int;



extern char getType(Unicode c);



class UnicodeTypeTableTest_1868 : public ::testing::Test {

protected:

    // No additional setup needed for this test suite.

};



TEST_F(UnicodeTypeTableTest_1868, GetType_Returns_X_For_OutOfRangeValue_1868) {

    Unicode out_of_range_value = 0x110000; // Just past the last valid Unicode value

    EXPECT_EQ(getType(out_of_range_value), 'X');

}



TEST_F(UnicodeTypeTableTest_1868, GetType_Returns_X_For_Part2_Start_Value_1868) {

    Unicode unicode_part2_start = UNICODE_PART2_START;

    EXPECT_EQ(getType(unicode_part2_start), 'X');

}



TEST_F(UnicodeTypeTableTest_1868, GetType_Returns_Valid_Type_For_Last_Char_Part1_1868) {

    Unicode last_char_part1 = UNICODE_LAST_CHAR_PART1;

    char expected_type = typeTable[(last_char_part1 >> 8) & 0xff].vector[last_char_part1 & 0xff];

    EXPECT_EQ(getType(last_char_part1), expected_type);

}



TEST_F(UnicodeTypeTableTest_1868, GetType_Returns_L_For_Hangul_L_Base_1868) {

    Unicode hangul_l_base = HANGUL_L_BASE;

    EXPECT_EQ(getType(hangul_l_base), 'L');

}



TEST_F(UnicodeTypeTableTest_1868, GetType_Returns_Valid_Type_For_First_Part2_Value_1868) {

    Unicode first_part2_value = UNICODE_PART2_START + 1;

    char expected_type = typeTable[(first_part2_value >> 8) & 0xff].vector[first_part2_value & 0xff];

    EXPECT_EQ(getType(first_part2_value), expected_type);

}



TEST_F(UnicodeTypeTableTest_1868, GetType_Returns_X_For_Part1_End_Value_1868) {

    Unicode part1_end_value = UNICODE_LAST_CHAR_PART1 + 1;

    char expected_type = typeTable[(part1_end_value >> 8) & 0xff].type; // Expecting 'X' as it's not a valid Part1 character

    EXPECT_EQ(getType(part1_end_value), expected_type);

}



TEST_F(UnicodeTypeTableTest_1868, GetType_Returns_Valid_Type_For_Hangul_S_Base_1868) {

    Unicode hangul_s_base = HANGUL_S_BASE;

    char expected_type = typeTable[(hangul_s_base >> 8) & 0xff].vector[hangul_s_base & 0xff];

    EXPECT_EQ(getType(hangul_s_base), expected_type);

}



TEST_F(UnicodeTypeTableTest_1868, GetType_Returns_Valid_Type_For_Small_Value_1868) {

    Unicode small_value = 0x20; // A small ASCII value

    char expected_type = typeTable[(small_value >> 8) & 0xff].vector[small_value & 0xff];

    EXPECT_EQ(getType(small_value), expected_type);

}
