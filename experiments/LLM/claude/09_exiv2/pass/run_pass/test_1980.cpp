#include <gtest/gtest.h>
#include <climits>
#include <string>
#include <stdexcept>

// Include necessary XMP headers
// We need to replicate the minimal environment to test GatherInt

// Forward declarations and type definitions from the XMP SDK
typedef const char* XMP_StringPtr;
typedef int32_t XMP_Int32;

// XMP_Throw macro - in the actual SDK this throws an exception
// We need to define a compatible exception class
class XMP_Error {
public:
    XMP_Error(int id, const char* errMsg) : id_(id), errMsg_(errMsg) {}
    int GetID() const { return id_; }
    const char* GetErrMsg() const { return errMsg_; }
private:
    int id_;
    const char* errMsg_;
};

#define XMP_Throw(msg, id) throw XMP_Error(id, msg)

// Error codes
enum {
    kXMPErr_Unknown = 0,
    kXMPErr_BadParam = 4,
};

// Copy the GatherInt function from the source
static XMP_Int32 GatherInt(XMP_StringPtr strValue, size_t* _pos, const char* errMsg) {
    size_t pos = *_pos;
    XMP_Int32 value = 0;

    const XMP_Int32 tens_upperbound = std::numeric_limits<XMP_Int32>::max() / 10;
    const XMP_Int32 ones_upperbound = std::numeric_limits<XMP_Int32>::max() % 10;

    for (char ch = strValue[pos]; ('0' <= ch) && (ch <= '9'); ++pos, ch = strValue[pos]) {
        const XMP_Int32 digit = ch - '0';
        if (value >= tens_upperbound) {
            if (value > tens_upperbound || digit > ones_upperbound) {
                XMP_Throw(errMsg, kXMPErr_BadParam);
            }
        }
        value = (value * 10) + digit;
    }

    if (pos == *_pos) XMP_Throw(errMsg, kXMPErr_BadParam);
    *_pos = pos;
    return value;
}

// Test fixture
class GatherIntTest_1980 : public ::testing::Test {
protected:
    const char* errMsg = "test error message";
};

// ==================== Normal Operation Tests ====================

TEST_F(GatherIntTest_1980, ParsesSingleDigit_1980) {
    size_t pos = 0;
    XMP_Int32 result = GatherInt("5", &pos, errMsg);
    EXPECT_EQ(result, 5);
    EXPECT_EQ(pos, 1u);
}

TEST_F(GatherIntTest_1980, ParsesMultipleDigits_1980) {
    size_t pos = 0;
    XMP_Int32 result = GatherInt("12345", &pos, errMsg);
    EXPECT_EQ(result, 12345);
    EXPECT_EQ(pos, 5u);
}

TEST_F(GatherIntTest_1980, ParsesZero_1980) {
    size_t pos = 0;
    XMP_Int32 result = GatherInt("0", &pos, errMsg);
    EXPECT_EQ(result, 0);
    EXPECT_EQ(pos, 1u);
}

TEST_F(GatherIntTest_1980, ParsesDigitsWithTrailingNonDigit_1980) {
    size_t pos = 0;
    XMP_Int32 result = GatherInt("123abc", &pos, errMsg);
    EXPECT_EQ(result, 123);
    EXPECT_EQ(pos, 3u);
}

TEST_F(GatherIntTest_1980, ParsesFromMiddleOfString_1980) {
    size_t pos = 3;
    XMP_Int32 result = GatherInt("abc456def", &pos, errMsg);
    EXPECT_EQ(result, 456);
    EXPECT_EQ(pos, 6u);
}

TEST_F(GatherIntTest_1980, ParsesDigitZeroAtStart_1980) {
    size_t pos = 0;
    XMP_Int32 result = GatherInt("007", &pos, errMsg);
    EXPECT_EQ(result, 7);
    EXPECT_EQ(pos, 3u);
}

TEST_F(GatherIntTest_1980, ParsesAllDigitChars_1980) {
    size_t pos = 0;
    XMP_Int32 result = GatherInt("1234567890", &pos, errMsg);
    EXPECT_EQ(result, 1234567890);
    EXPECT_EQ(pos, 10u);
}

TEST_F(GatherIntTest_1980, StopsAtSpace_1980) {
    size_t pos = 0;
    XMP_Int32 result = GatherInt("42 rest", &pos, errMsg);
    EXPECT_EQ(result, 42);
    EXPECT_EQ(pos, 2u);
}

TEST_F(GatherIntTest_1980, StopsAtHyphen_1980) {
    size_t pos = 0;
    XMP_Int32 result = GatherInt("2023-01-15", &pos, errMsg);
    EXPECT_EQ(result, 2023);
    EXPECT_EQ(pos, 4u);
}

TEST_F(GatherIntTest_1980, ParsesAfterHyphenStop_1980) {
    // Simulate parsing a date: parse year, skip '-', parse month
    size_t pos = 0;
    const char* dateStr = "2023-01-15";
    XMP_Int32 year = GatherInt(dateStr, &pos, errMsg);
    EXPECT_EQ(year, 2023);
    EXPECT_EQ(pos, 4u);

    pos++; // skip '-'
    XMP_Int32 month = GatherInt(dateStr, &pos, errMsg);
    EXPECT_EQ(month, 1);
    EXPECT_EQ(pos, 7u);

    pos++; // skip '-'
    XMP_Int32 day = GatherInt(dateStr, &pos, errMsg);
    EXPECT_EQ(day, 15);
    EXPECT_EQ(pos, 10u);
}

TEST_F(GatherIntTest_1980, ParsesSingleDigitFromOffset_1980) {
    size_t pos = 5;
    XMP_Int32 result = GatherInt("hello9world", &pos, errMsg);
    EXPECT_EQ(result, 9);
    EXPECT_EQ(pos, 6u);
}

// ==================== Boundary Condition Tests ====================

TEST_F(GatherIntTest_1980, ParsesMaxInt32Value_1980) {
    // INT32_MAX = 2147483647
    size_t pos = 0;
    XMP_Int32 result = GatherInt("2147483647", &pos, errMsg);
    EXPECT_EQ(result, 2147483647);
    EXPECT_EQ(pos, 10u);
}

TEST_F(GatherIntTest_1980, ParsesJustBelowMaxInt32_1980) {
    // 2147483646
    size_t pos = 0;
    XMP_Int32 result = GatherInt("2147483646", &pos, errMsg);
    EXPECT_EQ(result, 2147483646);
    EXPECT_EQ(pos, 10u);
}

TEST_F(GatherIntTest_1980, ParsesLeadingZeros_1980) {
    size_t pos = 0;
    XMP_Int32 result = GatherInt("00000001", &pos, errMsg);
    EXPECT_EQ(result, 1);
    EXPECT_EQ(pos, 8u);
}

TEST_F(GatherIntTest_1980, ParsesMultipleZeros_1980) {
    size_t pos = 0;
    XMP_Int32 result = GatherInt("000", &pos, errMsg);
    EXPECT_EQ(result, 0);
    EXPECT_EQ(pos, 3u);
}

TEST_F(GatherIntTest_1980, StopsAtNullTerminator_1980) {
    size_t pos = 0;
    XMP_Int32 result = GatherInt("99", &pos, errMsg);
    EXPECT_EQ(result, 99);
    EXPECT_EQ(pos, 2u);
}

// ==================== Error/Exception Tests ====================

TEST_F(GatherIntTest_1980, ThrowsOnEmptyString_1980) {
    size_t pos = 0;
    try {
        GatherInt("", &pos, errMsg);
        FAIL() << "Expected XMP_Error to be thrown";
    } catch (const XMP_Error& e) {
        EXPECT_EQ(e.GetID(), kXMPErr_BadParam);
        EXPECT_EQ(pos, 0u); // pos should not have changed
    }
}

TEST_F(GatherIntTest_1980, ThrowsOnNonDigitAtStart_1980) {
    size_t pos = 0;
    try {
        GatherInt("abc", &pos, errMsg);
        FAIL() << "Expected XMP_Error to be thrown";
    } catch (const XMP_Error& e) {
        EXPECT_EQ(e.GetID(), kXMPErr_BadParam);
        EXPECT_EQ(pos, 0u);
    }
}

TEST_F(GatherIntTest_1980, ThrowsOnNonDigitAtOffset_1980) {
    size_t pos = 3;
    try {
        GatherInt("abcdef", &pos, errMsg);
        FAIL() << "Expected XMP_Error to be thrown";
    } catch (const XMP_Error& e) {
        EXPECT_EQ(e.GetID(), kXMPErr_BadParam);
        EXPECT_EQ(pos, 3u);
    }
}

TEST_F(GatherIntTest_1980, ThrowsOnOverflowBeyondMaxInt32_1980) {
    // 2147483648 = INT32_MAX + 1
    size_t pos = 0;
    try {
        GatherInt("2147483648", &pos, errMsg);
        FAIL() << "Expected XMP_Error to be thrown";
    } catch (const XMP_Error& e) {
        EXPECT_EQ(e.GetID(), kXMPErr_BadParam);
    }
}

TEST_F(GatherIntTest_1980, ThrowsOnLargeOverflow_1980) {
    // Very large number
    size_t pos = 0;
    try {
        GatherInt("99999999999", &pos, errMsg);
        FAIL() << "Expected XMP_Error to be thrown";
    } catch (const XMP_Error& e) {
        EXPECT_EQ(e.GetID(), kXMPErr_BadParam);
    }
}

TEST_F(GatherIntTest_1980, ThrowsOnOverflowWithTensUpperbound_1980) {
    // A number where value == tens_upperbound but digit > ones_upperbound
    // tens_upperbound = 214748364, ones_upperbound = 7
    // So "2147483649" should overflow (last digit 9 > 7)
    size_t pos = 0;
    try {
        GatherInt("2147483649", &pos, errMsg);
        FAIL() << "Expected XMP_Error to be thrown";
    } catch (const XMP_Error& e) {
        EXPECT_EQ(e.GetID(), kXMPErr_BadParam);
    }
}

TEST_F(GatherIntTest_1980, ThrowsOnSpaceOnly_1980) {
    size_t pos = 0;
    try {
        GatherInt(" ", &pos, errMsg);
        FAIL() << "Expected XMP_Error to be thrown";
    } catch (const XMP_Error& e) {
        EXPECT_EQ(e.GetID(), kXMPErr_BadParam);
    }
}

TEST_F(GatherIntTest_1980, ThrowsOnNegativeSign_1980) {
    // GatherInt doesn't handle negative numbers - '-' is not a digit
    size_t pos = 0;
    try {
        GatherInt("-123", &pos, errMsg);
        FAIL() << "Expected XMP_Error to be thrown";
    } catch (const XMP_Error& e) {
        EXPECT_EQ(e.GetID(), kXMPErr_BadParam);
    }
}

TEST_F(GatherIntTest_1980, ThrowsOnPlusSign_1980) {
    size_t pos = 0;
    try {
        GatherInt("+123", &pos, errMsg);
        FAIL() << "Expected XMP_Error to be thrown";
    } catch (const XMP_Error& e) {
        EXPECT_EQ(e.GetID(), kXMPErr_BadParam);
    }
}

TEST_F(GatherIntTest_1980, ErrorMessagePreserved_1980) {
    size_t pos = 0;
    const char* customMsg = "custom error for test";
    try {
        GatherInt("abc", &pos, customMsg);
        FAIL() << "Expected XMP_Error to be thrown";
    } catch (const XMP_Error& e) {
        EXPECT_STREQ(e.GetErrMsg(), customMsg);
    }
}

TEST_F(GatherIntTest_1980, ThrowsOnOverflowTensExceeded_1980) {
    // Number where the accumulated value exceeds tens_upperbound before last digit
    // 3000000000 > 2147483647
    size_t pos = 0;
    try {
        GatherInt("3000000000", &pos, errMsg);
        FAIL() << "Expected XMP_Error to be thrown";
    } catch (const XMP_Error& e) {
        EXPECT_EQ(e.GetID(), kXMPErr_BadParam);
    }
}

// ==================== Position Update Tests ====================

TEST_F(GatherIntTest_1980, PositionUpdatedCorrectly_1980) {
    size_t pos = 2;
    // "ab123cd" - starting at pos 2 should parse "123"
    XMP_Int32 result = GatherInt("ab123cd", &pos, errMsg);
    EXPECT_EQ(result, 123);
    EXPECT_EQ(pos, 5u);
}

TEST_F(GatherIntTest_1980, PositionNotChangedOnError_1980) {
    size_t pos = 0;
    size_t originalPos = pos;
    try {
        GatherInt("abc", &pos, errMsg);
        FAIL();
    } catch (const XMP_Error&) {
        EXPECT_EQ(pos, originalPos);
    }
}

TEST_F(GatherIntTest_1980, ConsecutiveParsingWorks_1980) {
    // Parse "12:34:56" as time-like
    const char* timeStr = "12:34:56";
    size_t pos = 0;

    XMP_Int32 hours = GatherInt(timeStr, &pos, errMsg);
    EXPECT_EQ(hours, 12);
    EXPECT_EQ(pos, 2u);

    pos++; // skip ':'
    XMP_Int32 minutes = GatherInt(timeStr, &pos, errMsg);
    EXPECT_EQ(minutes, 34);
    EXPECT_EQ(pos, 5u);

    pos++; // skip ':'
    XMP_Int32 seconds = GatherInt(timeStr, &pos, errMsg);
    EXPECT_EQ(seconds, 56);
    EXPECT_EQ(pos, 8u);
}

// ==================== Edge Case with Digit Characters ====================

TEST_F(GatherIntTest_1980, StopsAtDotCharacter_1980) {
    size_t pos = 0;
    XMP_Int32 result = GatherInt("3.14", &pos, errMsg);
    EXPECT_EQ(result, 3);
    EXPECT_EQ(pos, 1u);
}

TEST_F(GatherIntTest_1980, ParsesDigit0_1980) {
    size_t pos = 0;
    XMP_Int32 result = GatherInt("0", &pos, errMsg);
    EXPECT_EQ(result, 0);
    EXPECT_EQ(pos, 1u);
}

TEST_F(GatherIntTest_1980, ParsesDigit9_1980) {
    size_t pos = 0;
    XMP_Int32 result = GatherInt("9", &pos, errMsg);
    EXPECT_EQ(result, 9);
    EXPECT_EQ(pos, 1u);
}

TEST_F(GatherIntTest_1980, StopsBeforeCharJustBelowZero_1980) {
    // Character '/' is ASCII 47, just below '0' (ASCII 48)
    size_t pos = 0;
    try {
        GatherInt("/", &pos, errMsg);
        FAIL() << "Expected XMP_Error";
    } catch (const XMP_Error& e) {
        EXPECT_EQ(e.GetID(), kXMPErr_BadParam);
    }
}

TEST_F(GatherIntTest_1980, StopsBeforeCharJustAboveNine_1980) {
    // Character ':' is ASCII 58, just above '9' (ASCII 57)
    size_t pos = 0;
    try {
        GatherInt(":", &pos, errMsg);
        FAIL() << "Expected XMP_Error";
    } catch (const XMP_Error& e) {
        EXPECT_EQ(e.GetID(), kXMPErr_BadParam);
    }
}
