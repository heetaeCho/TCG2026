#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <string>
#include <vector>
#include <cstring>

// Include necessary headers
// We need to set up the types and the function under test

// Forward declarations and type definitions matching the codebase
typedef unsigned char XMP_Uns8;
typedef unsigned int XMP_OptionBits;

#ifndef XMP_Assert
#define XMP_Assert(c) ((void)0)
#endif

// Minimal XML_Node and related types for compilation
enum { kRootNode = 0 };

struct XML_Node {
    XML_Node(int, const char*, int) {}
};

typedef XML_Node* XML_NodePtr;
typedef std::vector<XML_NodePtr> XML_NodeVector;

// Mock XMLParserAdapter
class XMLParserAdapter {
public:
    XML_Node tree;
    XML_NodeVector parseStack;
    XML_NodePtr rootNode;
    size_t rootCount;
    XMP_OptionBits charEncoding;
    size_t pendingCount;
    unsigned char pendingInput[16];

    XMLParserAdapter()
        : tree(0, "", kRootNode), rootNode(0), rootCount(0),
          charEncoding((XMP_OptionBits)(-1)), pendingCount(0) {}

    virtual void ParseBuffer(const void* buffer, size_t length, bool last) = 0;
    virtual ~XMLParserAdapter() {}
};

class MockXMLParserAdapter : public XMLParserAdapter {
public:
    MOCK_METHOD(void, ParseBuffer, (const void* buffer, size_t length, bool last), (override));
};

// Constants used by ProcessUTF8Portion
static const char kTab = 0x09;
static const char kLF  = 0x0A;
static const char kCR  = 0x0D;

// The kReplaceLatin1 table
static const char* kReplaceLatin1[128] = {
    "\342\202\254", " ", "\342\200\232", "\306\222",
    "\342\200\236", "\342\200\246", "\342\200\240", "\342\200\241",
    "\313\206", "\342\200\260", "\305\240", "\342\200\271",
    "\305\222", " ", "\305\275", " ",
    " ", "\342\200\230", "\342\200\231", "\342\200\234",
    "\342\200\235", "\342\200\242", "\342\200\223", "\342\200\224",
    "\313\234", "\342\204\242", "\305\241", "\342\200\272",
    "\305\223", " ", "\305\276", "\305\270",
    "\302\240", "\302\241", "\302\242", "\302\243",
    "\302\244", "\302\245", "\302\246", "\302\247",
    "\302\250", "\302\251", "\302\252", "\302\253",
    "\302\254", "\302\255", "\302\256", "\302\257",
    "\302\260", "\302\261", "\302\262", "\302\263",
    "\302\264", "\302\265", "\302\266", "\302\267",
    "\302\270", "\302\271", "\302\272", "\302\273",
    "\302\274", "\302\275", "\302\276", "\302\277",
    "\303\200", "\303\201", "\303\202", "\303\203",
    "\303\204", "\303\205", "\303\206", "\303\207",
    "\303\210", "\303\211", "\303\212", "\303\213",
    "\303\214", "\303\215", "\303\216", "\303\217",
    "\303\220", "\303\221", "\303\222", "\303\223",
    "\303\224", "\303\225", "\303\226", "\303\227",
    "\303\230", "\303\231", "\303\232", "\303\233",
    "\303\234", "\303\235", "\303\236", "\303\237",
    "\303\240", "\303\241", "\303\242", "\303\243",
    "\303\244", "\303\245", "\303\246", "\303\247",
    "\303\250", "\303\251", "\303\252", "\303\253",
    "\303\254", "\303\255", "\303\256", "\303\257",
    "\303\260", "\303\261", "\303\262", "\303\263",
    "\303\264", "\303\265", "\303\266", "\303\267",
    "\303\270", "\303\271", "\303\272", "\303\273",
    "\303\274", "\303\275", "\303\276", "\303\277"
};

// Helper functions that ProcessUTF8Portion calls
// CountUTF8: returns length of UTF-8 sequence, negative if incomplete, 0 if invalid
static int CountUTF8(const XMP_Uns8* spanEnd, const XMP_Uns8* bufEnd) {
    if (spanEnd >= bufEnd) return 0;
    XMP_Uns8 byte = *spanEnd;
    int expectedLen = 0;
    if ((byte & 0xE0) == 0xC0) expectedLen = 2;
    else if ((byte & 0xF0) == 0xE0) expectedLen = 3;
    else if ((byte & 0xF8) == 0xF0) expectedLen = 4;
    else return 0; // invalid leading byte for multi-byte UTF-8

    if (spanEnd + expectedLen > bufEnd) return -1; // incomplete

    for (int i = 1; i < expectedLen; ++i) {
        if ((spanEnd[i] & 0xC0) != 0x80) return 0; // invalid continuation
    }
    return expectedLen;
}

// CountControlEscape: check for &#xNN; escape of control characters
// Returns positive length if valid escape found, negative if potentially incomplete, 0 if not an escape
static int CountControlEscape(const XMP_Uns8* spanEnd, const XMP_Uns8* bufEnd) {
    // Minimal implementation for testing: looks for &#xNN; pattern
    size_t remaining = bufEnd - spanEnd;
    if (remaining < 2) return -1;

    if (spanEnd[1] != '#') return 0;

    // Look for the pattern &#xNN;
    if (remaining < 3) return -1;
    if (spanEnd[2] != 'x' && spanEnd[2] != 'X') {
        // Could be decimal &#NN;
        // Look for semicolon
        for (size_t i = 2; i < remaining; ++i) {
            if (spanEnd[i] == ';') {
                // Check if the value is a control character (< 0x20)
                int val = 0;
                for (size_t j = 2; j < i; ++j) {
                    if (spanEnd[j] < '0' || spanEnd[j] > '9') return 0;
                    val = val * 10 + (spanEnd[j] - '0');
                }
                if (val < 0x20 && val != kTab && val != kLF && val != kCR) {
                    return (int)(i + 1);
                }
                return 0;
            }
        }
        return -1; // incomplete
    }

    for (size_t i = 3; i < remaining; ++i) {
        if (spanEnd[i] == ';') {
            int val = 0;
            for (size_t j = 3; j < i; ++j) {
                char c = spanEnd[j];
                if (c >= '0' && c <= '9') val = val * 16 + (c - '0');
                else if (c >= 'a' && c <= 'f') val = val * 16 + (c - 'a' + 10);
                else if (c >= 'A' && c <= 'F') val = val * 16 + (c - 'A' + 10);
                else return 0;
            }
            if (val < 0x20 && val != kTab && val != kLF && val != kCR) {
                return (int)(i + 1);
            }
            return 0;
        }
    }
    return -1; // incomplete
}

// Now declare ProcessUTF8Portion - since it's a static function in the .cpp file,
// we need to include it or redefine. Since we're testing the interface, we include 
// the implementation directly.

#define Trace_ParsingHackery 0

static size_t ProcessUTF8Portion(
    XMLParserAdapter* xmlParser,
    const XMP_Uns8* buffer,
    size_t length,
    bool last)
{
    const XMP_Uns8* bufEnd = buffer + length;
    const XMP_Uns8* spanEnd;
    std::string copy;

    for (spanEnd = buffer; spanEnd < bufEnd; ++spanEnd) {
        if ((0x20 <= *spanEnd) && (*spanEnd <= 0x7E) && (*spanEnd != '&')) {
            copy.push_back(*spanEnd);
            continue;
        }

        if (*spanEnd >= 0x80) {
            int uniLen = CountUTF8(spanEnd, bufEnd);
            if (uniLen > 0) {
                copy.append((const char*)spanEnd, uniLen);
                spanEnd += uniLen - 1;
            } else if ((uniLen < 0) && (!last)) {
                xmlParser->ParseBuffer(copy.c_str(), copy.size(), false);
                return (spanEnd - buffer);
            } else {
                const char* replacement = kReplaceLatin1[*spanEnd - 0x80];
                copy.append(replacement);
            }
        } else if ((*spanEnd < 0x20) || (*spanEnd == 0x7F)) {
            if ((*spanEnd == kTab) || (*spanEnd == kLF) || (*spanEnd == kCR)) {
                copy.push_back(*spanEnd);
                continue;
            }
            copy.push_back(' ');
        } else {
            XMP_Assert(*spanEnd == '&');
            int escLen = CountControlEscape(spanEnd, bufEnd);
            if (escLen < 0) {
                if (last) {
                    copy.push_back('&');
                    continue;
                }
                xmlParser->ParseBuffer(copy.c_str(), copy.size(), false);
                return (spanEnd - buffer);
            } else if (escLen > 0) {
                copy.push_back(' ');
                spanEnd = spanEnd + escLen - 1;
            } else {
                copy.push_back('&');
            }
        }
    }

    XMP_Assert(spanEnd == bufEnd);
    copy.push_back(' ');
    xmlParser->ParseBuffer(copy.c_str(), copy.size(), true);
    return length;
}

// ============================================================================
// Test Fixture
// ============================================================================

class ProcessUTF8PortionTest_1973 : public ::testing::Test {
protected:
    MockXMLParserAdapter mockParser;
};

// Test: Regular ASCII text is passed through and ParseBuffer called with last=true
TEST_F(ProcessUTF8PortionTest_1973, RegularASCII_1973) {
    const char* input = "Hello World";
    size_t len = strlen(input);

    EXPECT_CALL(mockParser, ParseBuffer(::testing::_, ::testing::_, true))
        .Times(1);

    size_t result = ProcessUTF8Portion(&mockParser, (const XMP_Uns8*)input, len, true);
    EXPECT_EQ(result, len);
}

// Test: Empty buffer
TEST_F(ProcessUTF8PortionTest_1973, EmptyBuffer_1973) {
    const XMP_Uns8 buffer[] = {};

    EXPECT_CALL(mockParser, ParseBuffer(::testing::_, ::testing::_, true))
        .Times(1);

    size_t result = ProcessUTF8Portion(&mockParser, buffer, 0, true);
    EXPECT_EQ(result, 0u);
}

// Test: Tab, LF, CR are preserved
TEST_F(ProcessUTF8PortionTest_1973, WhitespaceCharactersPreserved_1973) {
    XMP_Uns8 input[] = { 0x09, 0x0A, 0x0D }; // tab, LF, CR
    size_t len = sizeof(input);

    std::string captured;
    EXPECT_CALL(mockParser, ParseBuffer(::testing::_, ::testing::_, true))
        .WillOnce([&captured](const void* buf, size_t length, bool) {
            captured = std::string((const char*)buf, length);
        });

    size_t result = ProcessUTF8Portion(&mockParser, input, len, true);
    EXPECT_EQ(result, len);
    // The captured string should contain tab, LF, CR plus trailing space
    EXPECT_EQ(captured.size(), 4u);
    EXPECT_EQ(captured[0], '\t');
    EXPECT_EQ(captured[1], '\n');
    EXPECT_EQ(captured[2], '\r');
    EXPECT_EQ(captured[3], ' '); // trailing space appended
}

// Test: Control characters (not tab/LF/CR) are replaced with space
TEST_F(ProcessUTF8PortionTest_1973, ControlCharacterReplacedWithSpace_1973) {
    XMP_Uns8 input[] = { 0x01 }; // SOH control character
    size_t len = sizeof(input);

    std::string captured;
    EXPECT_CALL(mockParser, ParseBuffer(::testing::_, ::testing::_, true))
        .WillOnce([&captured](const void* buf, size_t length, bool) {
            captured = std::string((const char*)buf, length);
        });

    size_t result = ProcessUTF8Portion(&mockParser, input, len, true);
    EXPECT_EQ(result, len);
    // Should be space (replacement) + space (trailing)
    EXPECT_EQ(captured, "  ");
}

// Test: DEL character (0x7F) is replaced with space
TEST_F(ProcessUTF8PortionTest_1973, DELCharacterReplacedWithSpace_1973) {
    XMP_Uns8 input[] = { 0x7F };
    size_t len = sizeof(input);

    std::string captured;
    EXPECT_CALL(mockParser, ParseBuffer(::testing::_, ::testing::_, true))
        .WillOnce([&captured](const void* buf, size_t length, bool) {
            captured = std::string((const char*)buf, length);
        });

    size_t result = ProcessUTF8Portion(&mockParser, input, len, true);
    EXPECT_EQ(result, len);
    EXPECT_EQ(captured, "  "); // space replacement + trailing space
}

// Test: Valid 2-byte UTF-8 sequence passes through
TEST_F(ProcessUTF8PortionTest_1973, ValidTwoByteUTF8_1973) {
    XMP_Uns8 input[] = { 0xC3, 0xA9 }; // é in UTF-8
    size_t len = sizeof(input);

    std::string captured;
    EXPECT_CALL(mockParser, ParseBuffer(::testing::_, ::testing::_, true))
        .WillOnce([&captured](const void* buf, size_t length, bool) {
            captured = std::string((const char*)buf, length);
        });

    size_t result = ProcessUTF8Portion(&mockParser, input, len, true);
    EXPECT_EQ(result, len);
    // Should contain the 2-byte UTF-8 sequence + trailing space
    EXPECT_EQ(captured.size(), 3u);
    EXPECT_EQ((unsigned char)captured[0], 0xC3);
    EXPECT_EQ((unsigned char)captured[1], 0xA9);
    EXPECT_EQ(captured[2], ' ');
}

// Test: Valid 3-byte UTF-8 sequence passes through
TEST_F(ProcessUTF8PortionTest_1973, ValidThreeByteUTF8_1973) {
    XMP_Uns8 input[] = { 0xE2, 0x82, 0xAC }; // € in UTF-8
    size_t len = sizeof(input);

    std::string captured;
    EXPECT_CALL(mockParser, ParseBuffer(::testing::_, ::testing::_, true))
        .WillOnce([&captured](const void* buf, size_t length, bool) {
            captured = std::string((const char*)buf, length);
        });

    size_t result = ProcessUTF8Portion(&mockParser, input, len, true);
    EXPECT_EQ(result, len);
    EXPECT_EQ(captured.size(), 4u);
    EXPECT_EQ((unsigned char)captured[0], 0xE2);
    EXPECT_EQ((unsigned char)captured[1], 0x82);
    EXPECT_EQ((unsigned char)captured[2], 0xAC);
    EXPECT_EQ(captured[3], ' ');
}

// Test: Incomplete UTF-8 sequence with last=false returns early
TEST_F(ProcessUTF8PortionTest_1973, IncompleteUTF8NotLast_1973) {
    // 0xC3 starts a 2-byte sequence but we only have 1 byte
    XMP_Uns8 input[] = { 'A', 0xC3 };
    size_t len = sizeof(input);

    EXPECT_CALL(mockParser, ParseBuffer(::testing::_, ::testing::_, false))
        .Times(1);

    size_t result = ProcessUTF8Portion(&mockParser, input, len, false);
    // Should return the position of the incomplete UTF-8 byte
    EXPECT_EQ(result, 1u);
}

// Test: Incomplete UTF-8 with last=true uses Latin1 replacement
TEST_F(ProcessUTF8PortionTest_1973, IncompleteUTF8Last_1973) {
    // 0xC3 starts a 2-byte sequence but we only have 1 byte, and it's the last buffer
    XMP_Uns8 input[] = { 0xC3 };
    size_t len = sizeof(input);

    std::string captured;
    EXPECT_CALL(mockParser, ParseBuffer(::testing::_, ::testing::_, true))
        .WillOnce([&captured](const void* buf, size_t length, bool) {
            captured = std::string((const char*)buf, length);
        });

    size_t result = ProcessUTF8Portion(&mockParser, input, len, true);
    EXPECT_EQ(result, len);
    // 0xC3 - 0x80 = 0x43 = 67, kReplaceLatin1[67] = "\303\203" (Ã)
    // Should contain the Latin1 replacement + trailing space
    EXPECT_GT(captured.size(), 1u); // at least replacement + trailing space
}

// Test: Ampersand not part of escape is passed through as-is
TEST_F(ProcessUTF8PortionTest_1973, AmpersandNotEscape_1973) {
    const char* input = "&abc";
    size_t len = strlen(input);

    std::string captured;
    EXPECT_CALL(mockParser, ParseBuffer(::testing::_, ::testing::_, true))
        .WillOnce([&captured](const void* buf, size_t length, bool) {
            captured = std::string((const char*)buf, length);
        });

    size_t result = ProcessUTF8Portion(&mockParser, (const XMP_Uns8*)input, len, true);
    EXPECT_EQ(result, len);
    // & should be kept as-is since it's not a control escape
    EXPECT_NE(captured.find('&'), std::string::npos);
}

// Test: Latin1 byte 0x80 gets replaced with Euro sign UTF-8
TEST_F(ProcessUTF8PortionTest_1973, Latin1_0x80_ReplacementEuro_1973) {
    // 0x80 is not a valid UTF-8 leading byte, so CountUTF8 returns 0
    // and it's treated as Latin1 replacement
    // But wait, 0x80 has (byte & 0xC0) == 0x80, which is a continuation byte
    // CountUTF8 should return 0 for invalid leading byte
    XMP_Uns8 input[] = { 0x80 };
    size_t len = sizeof(input);

    std::string captured;
    EXPECT_CALL(mockParser, ParseBuffer(::testing::_, ::testing::_, true))
        .WillOnce([&captured](const void* buf, size_t length, bool) {
            captured = std::string((const char*)buf, length);
        });

    size_t result = ProcessUTF8Portion(&mockParser, input, len, true);
    EXPECT_EQ(result, len);
    // kReplaceLatin1[0] = "\342\202\254" (€ in UTF-8) + trailing space
    std::string expected;
    expected += "\342\202\254";
    expected += ' ';
    EXPECT_EQ(captured, expected);
}

// Test: Mixed content - ASCII + control + UTF8
TEST_F(ProcessUTF8PortionTest_1973, MixedContent_1973) {
    XMP_Uns8 input[] = { 'H', 'i', 0x01, 0x09, '!' };
    size_t len = sizeof(input);

    std::string captured;
    EXPECT_CALL(mockParser, ParseBuffer(::testing::_, ::testing::_, true))
        .WillOnce([&captured](const void* buf, size_t length, bool) {
            captured = std::string((const char*)buf, length);
        });

    size_t result = ProcessUTF8Portion(&mockParser, input, len, true);
    EXPECT_EQ(result, len);
    // Expected: "Hi" + space (for 0x01) + tab (0x09) + "!" + trailing space
    EXPECT_EQ(captured, "Hi \t! ");
}

// Test: Return value equals length for complete processing
TEST_F(ProcessUTF8PortionTest_1973, ReturnValueFullLength_1973) {
    const char* input = "complete";
    size_t len = strlen(input);

    EXPECT_CALL(mockParser, ParseBuffer(::testing::_, ::testing::_, true))
        .Times(1);

    size_t result = ProcessUTF8Portion(&mockParser, (const XMP_Uns8*)input, len, true);
    EXPECT_EQ(result, len);
}

// Test: ParseBuffer called with last=true when entire buffer is processed
TEST_F(ProcessUTF8PortionTest_1973, ParseBufferCalledWithLastTrue_1973) {
    const char* input = "test";
    size_t len = strlen(input);

    EXPECT_CALL(mockParser, ParseBuffer(::testing::_, ::testing::_, true))
        .Times(1);

    ProcessUTF8Portion(&mockParser, (const XMP_Uns8*)input, len, true);
}

// Test: ParseBuffer called with last=false on early return
TEST_F(ProcessUTF8PortionTest_1973, ParseBufferCalledWithLastFalseOnEarlyReturn_1973) {
    // Incomplete UTF-8 at end, not last buffer
    XMP_Uns8 input[] = { 'A', 'B', 0xE2, 0x82 }; // incomplete 3-byte UTF-8
    size_t len = sizeof(input);

    EXPECT_CALL(mockParser, ParseBuffer(::testing::_, ::testing::_, false))
        .Times(1);

    size_t result = ProcessUTF8Portion(&mockParser, input, len, false);
    EXPECT_EQ(result, 2u); // returns position of incomplete sequence
}

// Test: Ampersand at end of buffer with last=false causes early return
TEST_F(ProcessUTF8PortionTest_1973, AmpersandAtEndNotLast_1973) {
    XMP_Uns8 input[] = { 'X', '&' };
    size_t len = sizeof(input);

    EXPECT_CALL(mockParser, ParseBuffer(::testing::_, ::testing::_, false))
        .Times(1);

    size_t result = ProcessUTF8Portion(&mockParser, input, len, false);
    EXPECT_EQ(result, 1u); // returns position of '&'
}

// Test: Ampersand at end of buffer with last=true is absorbed
TEST_F(ProcessUTF8PortionTest_1973, AmpersandAtEndLast_1973) {
    XMP_Uns8 input[] = { 'X', '&' };
    size_t len = sizeof(input);

    std::string captured;
    EXPECT_CALL(mockParser, ParseBuffer(::testing::_, ::testing::_, true))
        .WillOnce([&captured](const void* buf, size_t length, bool) {
            captured = std::string((const char*)buf, length);
        });

    size_t result = ProcessUTF8Portion(&mockParser, input, len, true);
    EXPECT_EQ(result, len);
    EXPECT_EQ(captured, "X& ");
}

// Test: All printable ASCII characters (except &) pass through
TEST_F(ProcessUTF8PortionTest_1973, AllPrintableASCII_1973) {
    std::vector<XMP_Uns8> input;
    for (int i = 0x20; i <= 0x7E; ++i) {
        if (i != '&') input.push_back((XMP_Uns8)i);
    }

    std::string captured;
    EXPECT_CALL(mockParser, ParseBuffer(::testing::_, ::testing::_, true))
        .WillOnce([&captured](const void* buf, size_t length, bool) {
            captured = std::string((const char*)buf, length);
        });

    size_t result = ProcessUTF8Portion(&mockParser, input.data(), input.size(), true);
    EXPECT_EQ(result, input.size());
    // captured should be all those chars + trailing space
    EXPECT_EQ(captured.size(), input.size() + 1);
    for (size_t i = 0; i < input.size(); ++i) {
        EXPECT_EQ((unsigned char)captured[i], input[i]);
    }
    EXPECT_EQ(captured.back(), ' ');
}

// Test: Single byte buffer with regular ASCII
TEST_F(ProcessUTF8PortionTest_1973, SingleByteASCII_1973) {
    XMP_Uns8 input[] = { 'Z' };

    std::string captured;
    EXPECT_CALL(mockParser, ParseBuffer(::testing::_, ::testing::_, true))
        .WillOnce([&captured](const void* buf, size_t length, bool) {
            captured = std::string((const char*)buf, length);
        });

    size_t result = ProcessUTF8Portion(&mockParser, input, 1, true);
    EXPECT_EQ(result, 1u);
    EXPECT_EQ(captured, "Z ");
}

// Test: Multiple control characters all become spaces
TEST_F(ProcessUTF8PortionTest_1973, MultipleControlChars_1973) {
    XMP_Uns8 input[] = { 0x00, 0x01, 0x02, 0x03, 0x04 };
    size_t len = sizeof(input);

    std::string captured;
    EXPECT_CALL(mockParser, ParseBuffer(::testing::_, ::testing::_, true))
        .WillOnce([&captured](const void* buf, size_t length, bool) {
            captured = std::string((const char*)buf, length);
        });

    size_t result = ProcessUTF8Portion(&mockParser, input, len, true);
    EXPECT_EQ(result, len);
    // 5 control chars -> 5 spaces + 1 trailing space
    EXPECT_EQ(captured, "      ");
}

// Test: Valid 4-byte UTF-8 sequence
TEST_F(ProcessUTF8PortionTest_1973, ValidFourByteUTF8_1973) {
    XMP_Uns8 input[] = { 0xF0, 0x9F, 0x98, 0x80 }; // 😀
    size_t len = sizeof(input);

    std::string captured;
    EXPECT_CALL(mockParser, ParseBuffer(::testing::_, ::testing::_, true))
        .WillOnce([&captured](const void* buf, size_t length, bool) {
            captured = std::string((const char*)buf, length);
        });

    size_t result = ProcessUTF8Portion(&mockParser, input, len, true);
    EXPECT_EQ(result, len);
    EXPECT_EQ(captured.size(), 5u); // 4-byte sequence + trailing space
    EXPECT_EQ((unsigned char)captured[0], 0xF0);
    EXPECT_EQ((unsigned char)captured[1], 0x9F);
    EXPECT_EQ((unsigned char)captured[2], 0x98);
    EXPECT_EQ((unsigned char)captured[3], 0x80);
    EXPECT_EQ(captured[4], ' ');
}

// Test: Latin1 byte 0xFF gets replaced
TEST_F(ProcessUTF8PortionTest_1973, Latin1_0xFF_Replacement_1973) {
    XMP_Uns8 input[] = { 0xFF };
    size_t len = sizeof(input);

    std::string captured;
    EXPECT_CALL(mockParser, ParseBuffer(::testing::_, ::testing::_, true))
        .WillOnce([&captured](const void* buf, size_t length, bool) {
            captured = std::string((const char*)buf, length);
        });

    size_t result = ProcessUTF8Portion(&mockParser, input, len, true);
    EXPECT_EQ(result, len);
    // kReplaceLatin1[127] = "\303\277" (ÿ in UTF-8) + trailing space
    std::string expected;
    expected += "\303\277";
    expected += ' ';
    EXPECT_EQ(captured, expected);
}

// Test: Control escape &#x01; is replaced with space
TEST_F(ProcessUTF8PortionTest_1973, ControlEscapeReplaced_1973) {
    const char* input = "&#x01;";
    size_t len = strlen(input);

    std::string captured;
    EXPECT_CALL(mockParser, ParseBuffer(::testing::_, ::testing::_, true))
        .WillOnce([&captured](const void* buf, size_t length, bool) {
            captured = std::string((const char*)buf, length);
        });

    size_t result = ProcessUTF8Portion(&mockParser, (const XMP_Uns8*)input, len, true);
    EXPECT_EQ(result, len);
    // The control escape should be replaced with a space, then trailing space
    EXPECT_EQ(captured, "  ");
}

// Test: Normal ampersand entity (not control) passes through as &
TEST_F(ProcessUTF8PortionTest_1973, NormalAmpersandEntity_1973) {
    const char* input = "&amp;";
    size_t len = strlen(input);

    std::string captured;
    EXPECT_CALL(mockParser, ParseBuffer(::testing::_, ::testing::_, true))
        .WillOnce([&captured](const void* buf, size_t length, bool) {
            captured = std::string((const char*)buf, length);
        });

    size_t result = ProcessUTF8Portion(&mockParser, (const XMP_Uns8*)input, len, true);
    EXPECT_EQ(result, len);
    // CountControlEscape returns 0 for &amp; so & is kept, then "amp;" are regular ASCII
    EXPECT_EQ(captured, "&amp; ");
}

// Test: Trailing space is always appended when full buffer is consumed
TEST_F(ProcessUTF8PortionTest_1973, TrailingSpaceAppended_1973) {
    XMP_Uns8 input[] = { 'A' };

    std::string captured;
    EXPECT_CALL(mockParser, ParseBuffer(::testing::_, ::testing::_, true))
        .WillOnce([&captured](const void* buf, size_t length, bool) {
            captured = std::string((const char*)buf, length);
        });

    ProcessUTF8Portion(&mockParser, input, 1, true);
    EXPECT_EQ(captured.back(), ' ');
}

// Test: last=false with complete content still processes everything
TEST_F(ProcessUTF8PortionTest_1973, LastFalseCompleteContent_1973) {
    const char* input = "Hello";
    size_t len = strlen(input);

    EXPECT_CALL(mockParser, ParseBuffer(::testing::_, ::testing::_, true))
        .Times(1);

    size_t result = ProcessUTF8Portion(&mockParser, (const XMP_Uns8*)input, len, false);
    EXPECT_EQ(result, len);
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
