#include <gtest/gtest.h>

#include <string>



namespace re2 {

    static void AppendCCRange(std::string* t, Rune lo, Rune hi);

}



using namespace re2;



// Test fixture for AppendCCRange function

class AppendCCRangeTest_229 : public ::testing::Test {

protected:

    std::string result;

};



// Normal operation: lo < hi

TEST_F(AppendCCRangeTest_229, AppendsRangeCorrectly_229) {

    Rune lo = 97; // 'a'

    Rune hi = 102; // 'f'

    AppendCCRange(&result, lo, hi);

    EXPECT_EQ(result, "a-f");

}



// Normal operation: lo == hi

TEST_F(AppendCCRangeTest_229, AppendsSingleChar_229) {

    Rune lo = 65; // 'A'

    Rune hi = 65; // 'A'

    AppendCCRange(&result, lo, hi);

    EXPECT_EQ(result, "A");

}



// Boundary condition: lo > hi

TEST_F(AppendCCRangeTest_229, NoAppendWhenLoGreaterThanHi_229) {

    Rune lo = 102; // 'f'

    Rune hi = 97; // 'a'

    AppendCCRange(&result, lo, hi);

    EXPECT_EQ(result, "");

}



// Edge case: lo and hi are at the boundary of printable ASCII

TEST_F(AppendCCRangeTest_229, AppendsBoundaryValues_229) {

    Rune lo = 32; // ' '

    Rune hi = 126; // '~'

    AppendCCRange(&result, lo, hi);

    EXPECT_EQ(result, " -~");

}



// Edge case: lo and hi are non-printable ASCII

TEST_F(AppendCCRangeTest_229, AppendsNonPrintableValues_229) {

    Rune lo = 0; // NUL

    Rune hi = 31; // Unit Separator

    AppendCCRange(&result, lo, hi);

    EXPECT_EQ(result.size(), 6); // "\x00-\x1f" should be 6 characters long in string representation

}
