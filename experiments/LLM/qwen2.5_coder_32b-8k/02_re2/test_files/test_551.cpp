#include <gtest/gtest.h>

#include <string>



// Assuming CharClass::iterator and Rune are defined somewhere in re2 namespace

namespace re2 {

    class CharClass {

    public:

        typedef int* iterator; // Placeholder for actual iterator type

    };

    using Rune = int; // Placeholder for actual Rune type



    static std::string RuneToStringLatin1(Rune r);

}



// Test fixture for the RuneToStringLatin1 function

class RuneToStringLatin1Test_551 : public ::testing::Test {

protected:

    re2::Rune testRune;

};



// Normal operation: Test with a standard ASCII character

TEST_F(RuneToStringLatin1Test_551, StandardAsciiCharacter_551) {

    testRune = 'A'; // ASCII value 65

    std::string result = re2::RuneToStringLatin1(testRune);

    EXPECT_EQ(result, "A");

}



// Boundary condition: Test with the minimum ASCII character (NUL)

TEST_F(RuneToStringLatin1Test_551, MinimumAsciiCharacter_551) {

    testRune = 0; // NUL

    std::string result = re2::RuneToStringLatin1(testRune);

    EXPECT_EQ(result, "\0");

}



// Boundary condition: Test with the maximum ASCII character (DEL)

TEST_F(RuneToStringLatin1Test_551, MaximumAsciiCharacter_551) {

    testRune = 127; // DEL

    std::string result = re2::RuneToStringLatin1(testRune);

    EXPECT_EQ(result, "\x7F");

}



// Exceptional case: Test with a value outside the ASCII range (should still work as it masks to 8 bits)

TEST_F(RuneToStringLatin1Test_551, OutsideAsciiRange_551) {

    testRune = 256; // Should mask to 0

    std::string result = re2::RuneToStringLatin1(testRune);

    EXPECT_EQ(result, "\0");

}



// Exceptional case: Test with a negative value (should still work as it masks to 8 bits)

TEST_F(RuneToStringLatin1Test_551, NegativeValue_551) {

    testRune = -1; // Should mask to 255

    std::string result = re2::RuneToStringLatin1(testRune);

    EXPECT_EQ(result, "\xFF");

}
