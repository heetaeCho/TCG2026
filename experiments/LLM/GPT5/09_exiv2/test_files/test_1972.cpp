#include <gtest/gtest.h>
#include <cstring>
#include "XMPMeta-Parse.cpp"  // Include the relevant code file

// Test suite for CountControlEscape function
class CountControlEscapeTest : public ::testing::Test {
protected:
    // Helper function to call CountControlEscape with specific inputs
    int callCountControlEscape(const XMP_Uns8* escStart, const XMP_Uns8* bufEnd) {
        return CountControlEscape(escStart, bufEnd);
    }
};

// Test for normal operation when a valid escape sequence is provided
TEST_F(CountControlEscapeTest, ValidHexadecimalEscapeSequence_1972) {
    // Valid escape sequence: &#xA; (Hexadecimal escape)
    const XMP_Uns8 testInput[] = "This is a test &#xA; with escape.";
    const XMP_Uns8* escStart = reinterpret_cast<const XMP_Uns8*>(strstr(reinterpret_cast<const char*>(testInput), "&#xA;"));
    const XMP_Uns8* bufEnd = testInput + sizeof(testInput) - 1;

    // Expect the function to detect the escape sequence and return the correct length
    EXPECT_EQ(callCountControlEscape(escStart, bufEnd), 6);  // "&#xA;" length
}

// Test for invalid escape sequence (not starting with "&#x")
TEST_F(CountControlEscapeTest, InvalidEscapeSequence_NoHexPrefix_1973) {
    // Invalid escape sequence: &A;
    const XMP_Uns8 testInput[] = "Invalid &A; sequence";
    const XMP_Uns8* escStart = reinterpret_cast<const XMP_Uns8*>(strstr(reinterpret_cast<const char*>(testInput), "&A;"));
    const XMP_Uns8* bufEnd = testInput + sizeof(testInput) - 1;

    // The sequence does not start with "&#x", should return 0
    EXPECT_EQ(callCountControlEscape(escStart, bufEnd), 0);
}

// Test for escape sequence with only a partial escape (not ending with ";")
TEST_F(CountControlEscapeTest, PartialEscapeSequence_NoSemicolon_1974) {
    // Partial escape sequence: &#xA (missing ';')
    const XMP_Uns8 testInput[] = "Invalid &#xA sequence";
    const XMP_Uns8* escStart = reinterpret_cast<const XMP_Uns8*>(strstr(reinterpret_cast<const char*>(testInput), "&#xA"));
    const XMP_Uns8* bufEnd = testInput + sizeof(testInput) - 1;

    // Should return -1 for incomplete escape sequence
    EXPECT_EQ(callCountControlEscape(escStart, bufEnd), -1);
}

// Test for escape sequence with an invalid character in the hex value
TEST_F(CountControlEscapeTest, InvalidHexCharacter_1975) {
    // Invalid escape sequence: &#xG; (G is not a valid hex character)
    const XMP_Uns8 testInput[] = "Invalid &#xG; sequence";
    const XMP_Uns8* escStart = reinterpret_cast<const XMP_Uns8*>(strstr(reinterpret_cast<const char*>(testInput), "&#xG"));
    const XMP_Uns8* bufEnd = testInput + sizeof(testInput) - 1;

    // The escape sequence is invalid due to 'G', expect 0
    EXPECT_EQ(callCountControlEscape(escStart, bufEnd), 0);
}

// Test for boundary condition where the escape sequence is at the very end of the buffer
TEST_F(CountControlEscapeTest, EscapeAtEndOfBuffer_1976) {
    // Escape sequence at the very end of the buffer: &#xA;
    const XMP_Uns8 testInput[] = "Test sequence&#xA;";
    const XMP_Uns8* escStart = reinterpret_cast<const XMP_Uns8*>(strstr(reinterpret_cast<const char*>(testInput), "&#xA;"));
    const XMP_Uns8* bufEnd = testInput + sizeof(testInput) - 1;

    // Expect it to be detected at the end of the buffer
    EXPECT_EQ(callCountControlEscape(escStart, bufEnd), 6);
}

// Test for escape sequence with a valid but prohibited escape value
TEST_F(CountControlEscapeTest, ProhibitedEscapeValue_1977) {
    // Escape sequence: &#x9; (Tab, which is prohibited)
    const XMP_Uns8 testInput[] = "Invalid escape &#x9; here";
    const XMP_Uns8* escStart = reinterpret_cast<const XMP_Uns8*>(strstr(reinterpret_cast<const char*>(testInput), "&#x9"));
    const XMP_Uns8* bufEnd = testInput + sizeof(testInput) - 1;

    // Should return 0 since Tab (0x9) is a prohibited escape value
    EXPECT_EQ(callCountControlEscape(escStart, bufEnd), 0);
}