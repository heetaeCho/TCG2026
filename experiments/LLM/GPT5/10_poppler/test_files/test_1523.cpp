#include <gtest/gtest.h>

extern uint32_t decodeUtf8(uint32_t *state, uint32_t *codep, char byte);
extern const uint32_t UTF8_ACCEPT;
extern const uint8_t decodeUtf8Table[364];

class DecodeUtf8Test_1523 : public ::testing::Test {
protected:
    uint32_t state;
    uint32_t codep;
};

TEST_F(DecodeUtf8Test_1523, DecodeValidUtf8Sequence_1523) {
    state = UTF8_ACCEPT;
    codep = 0;

    // Valid UTF-8 byte sequence for 'A' (0x41)
    EXPECT_EQ(decodeUtf8(&state, &codep, 0x41), UTF8_ACCEPT);
    EXPECT_EQ(codep, 0x41);
}

TEST_F(DecodeUtf8Test_1523, DecodeMultiByteUtf8Sequence_1524) {
    state = UTF8_ACCEPT;
    codep = 0;

    // Valid UTF-8 sequence for '€' (0x20AC) in two bytes: 0xE2, 0x82, 0xAC
    EXPECT_EQ(decodeUtf8(&state, &codep, 0xE2), 1); // First byte
    EXPECT_EQ(decodeUtf8(&state, &codep, 0x82), 2); // Second byte
    EXPECT_EQ(decodeUtf8(&state, &codep, 0xAC), UTF8_ACCEPT); // Third byte
    EXPECT_EQ(codep, 0x20AC);
}

TEST_F(DecodeUtf8Test_1523, BoundaryTestSingleByte_1525) {
    state = UTF8_ACCEPT;
    codep = 0;

    // Boundary test: Single byte UTF-8 value (0x00)
    EXPECT_EQ(decodeUtf8(&state, &codep, 0x00), UTF8_ACCEPT);
    EXPECT_EQ(codep, 0x00);
}

TEST_F(DecodeUtf8Test_1523, BoundaryTestHighestSingleByte_1526) {
    state = UTF8_ACCEPT;
    codep = 0;

    // Boundary test: Highest single byte UTF-8 value (0x7F)
    EXPECT_EQ(decodeUtf8(&state, &codep, 0x7F), UTF8_ACCEPT);
    EXPECT_EQ(codep, 0x7F);
}

TEST_F(DecodeUtf8Test_1523, ErrorCaseInvalidContinuationByte_1527) {
    state = UTF8_ACCEPT;
    codep = 0;

    // Error case: Invalid continuation byte (0x80), should not start a valid UTF-8 character.
    EXPECT_NE(decodeUtf8(&state, &codep, 0x80), UTF8_ACCEPT);
}

TEST_F(DecodeUtf8Test_1523, ErrorCaseInvalidLeadByte_1528) {
    state = UTF8_ACCEPT;
    codep = 0;

    // Error case: Invalid lead byte (0xF5), which is outside of the valid UTF-8 range.
    EXPECT_NE(decodeUtf8(&state, &codep, 0xF5), UTF8_ACCEPT);
}

TEST_F(DecodeUtf8Test_1523, DecodeAfterInvalidByte_1529) {
    state = UTF8_ACCEPT;
    codep = 0;

    // First invalid byte
    EXPECT_NE(decodeUtf8(&state, &codep, 0xF5), UTF8_ACCEPT);
    // Next byte (valid continuation after invalid lead byte)
    EXPECT_EQ(decodeUtf8(&state, &codep, 0x80), UTF8_ACCEPT);
    EXPECT_EQ(codep, 0x80);  // Continuation byte should still be invalid.
}

TEST_F(DecodeUtf8Test_1523, ExternalInteractionTest_1530) {
    // Mock or verify external interactions if any in the function signature or the decoding process.
    // This can include tests that validate how `decodeUtf8` interacts with other parts of the system,
    // such as handlers or callbacks passed in external to this function (though this case isn't clear from the given code).
    // No external interaction is specified for this simple test function.

    // For now, this is left as a placeholder for further expansion.
}