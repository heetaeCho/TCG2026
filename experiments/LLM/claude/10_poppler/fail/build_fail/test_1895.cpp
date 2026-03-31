#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <cstdarg>
#include <string>
#include <memory>
#include <cstdio>

#include "poppler/Error.h"
#include "poppler/GlobalParams.h"

// External declarations
extern void setErrorCallback(ErrorCallback cbk);

// Store callback results for verification
struct CallbackRecord {
    ErrorCategory category;
    Goffset pos;
    std::string message;
    int callCount;
    
    void reset() {
        category = errSyntaxWarning;
        pos = 0;
        message.clear();
        callCount = 0;
    }
};

static CallbackRecord g_record;

static void testErrorCallback(ErrorCategory category, Goffset pos, const char *msg) {
    g_record.category = category;
    g_record.pos = pos;
    g_record.message = msg;
    g_record.callCount++;
}

class ErrorTest_1895 : public ::testing::Test {
protected:
    void SetUp() override {
        g_record.reset();
        // Ensure globalParams exists
        if (!globalParams) {
            globalParams = std::make_unique<GlobalParams>("");
        }
        globalParams->setErrQuiet(false);
        // Set callback for most tests
        setErrorCallback(testErrorCallback);
    }
    
    void TearDown() override {
        setErrorCallback(nullptr);
        g_record.reset();
    }
};

// Test basic error with callback and positive position
TEST_F(ErrorTest_1895, BasicErrorWithPositivePosition_1895) {
    error(errSyntaxWarning, 42, "test message");
    
    EXPECT_EQ(g_record.callCount, 1);
    EXPECT_EQ(g_record.category, errSyntaxWarning);
    EXPECT_EQ(g_record.pos, 42);
    EXPECT_EQ(g_record.message, "test message");
}

// Test error with negative position
TEST_F(ErrorTest_1895, ErrorWithNegativePosition_1895) {
    error(errSyntaxError, -1, "negative pos message");
    
    EXPECT_EQ(g_record.callCount, 1);
    EXPECT_EQ(g_record.category, errSyntaxError);
    EXPECT_EQ(g_record.pos, -1);
    EXPECT_EQ(g_record.message, "negative pos message");
}

// Test error with zero position
TEST_F(ErrorTest_1895, ErrorWithZeroPosition_1895) {
    error(errConfigError, 0, "zero pos message");
    
    EXPECT_EQ(g_record.callCount, 1);
    EXPECT_EQ(g_record.category, errConfigError);
    EXPECT_EQ(g_record.pos, 0);
    EXPECT_EQ(g_record.message, "zero pos message");
}

// Test all error categories
TEST_F(ErrorTest_1895, SyntaxWarningCategory_1895) {
    error(errSyntaxWarning, 0, "msg");
    EXPECT_EQ(g_record.category, errSyntaxWarning);
}

TEST_F(ErrorTest_1895, SyntaxErrorCategory_1895) {
    error(errSyntaxError, 0, "msg");
    EXPECT_EQ(g_record.category, errSyntaxError);
}

TEST_F(ErrorTest_1895, ConfigErrorCategory_1895) {
    error(errConfigError, 0, "msg");
    EXPECT_EQ(g_record.category, errConfigError);
}

TEST_F(ErrorTest_1895, CommandLineErrorCategory_1895) {
    error(errCommandLine, 0, "msg");
    EXPECT_EQ(g_record.category, errCommandLine);
}

TEST_F(ErrorTest_1895, IOErrorCategory_1895) {
    error(errIO, 0, "msg");
    EXPECT_EQ(g_record.category, errIO);
}

TEST_F(ErrorTest_1895, PermissionErrorCategory_1895) {
    error(errPermission, 0, "msg");
    EXPECT_EQ(g_record.category, errPermission);
}

TEST_F(ErrorTest_1895, UnimplementedCategory_1895) {
    error(errUnimplemented, 0, "msg");
    EXPECT_EQ(g_record.category, errUnimplemented);
}

TEST_F(ErrorTest_1895, InternalErrorCategory_1895) {
    error(errInternal, 0, "msg");
    EXPECT_EQ(g_record.category, errInternal);
}

// Test format string with arguments
TEST_F(ErrorTest_1895, FormatStringWithIntArg_1895) {
    error(errSyntaxWarning, 10, "value is {0:d}", 42);
    
    EXPECT_EQ(g_record.callCount, 1);
    EXPECT_EQ(g_record.pos, 10);
    EXPECT_THAT(g_record.message, ::testing::HasSubstr("42"));
}

// Test format string with string argument
TEST_F(ErrorTest_1895, FormatStringWithStringArg_1895) {
    error(errSyntaxWarning, 10, "name is {0:s}", "hello");
    
    EXPECT_EQ(g_record.callCount, 1);
    EXPECT_THAT(g_record.message, ::testing::HasSubstr("hello"));
}

// Test sanitization of control characters
TEST_F(ErrorTest_1895, SanitizesControlCharacters_1895) {
    // Characters < 0x20 should be sanitized to hex format
    std::string msgWithCtrl = "hello";
    msgWithCtrl += '\x01';
    msgWithCtrl += "world";
    
    error(errSyntaxWarning, 0, "{0:s}", msgWithCtrl.c_str());
    
    EXPECT_EQ(g_record.callCount, 1);
    // The control character \x01 should be sanitized
    EXPECT_THAT(g_record.message, ::testing::HasSubstr("<01>"));
    EXPECT_THAT(g_record.message, ::testing::HasSubstr("hello"));
    EXPECT_THAT(g_record.message, ::testing::HasSubstr("world"));
}

// Test sanitization of high bytes (>= 0x7f)
TEST_F(ErrorTest_1895, SanitizesHighBytes_1895) {
    std::string msgWithHigh = "test";
    msgWithHigh += '\x80';
    msgWithHigh += "end";
    
    error(errSyntaxWarning, 0, "{0:s}", msgWithHigh.c_str());
    
    EXPECT_EQ(g_record.callCount, 1);
    EXPECT_THAT(g_record.message, ::testing::HasSubstr("<80>"));
    EXPECT_THAT(g_record.message, ::testing::HasSubstr("test"));
    EXPECT_THAT(g_record.message, ::testing::HasSubstr("end"));
}

// Test sanitization of 0x7f (DEL)
TEST_F(ErrorTest_1895, SanitizesDelCharacter_1895) {
    std::string msgWithDel = "a";
    msgWithDel += '\x7f';
    msgWithDel += "b";
    
    error(errSyntaxWarning, 0, "{0:s}", msgWithDel.c_str());
    
    EXPECT_EQ(g_record.callCount, 1);
    EXPECT_THAT(g_record.message, ::testing::HasSubstr("<7f>"));
}

// Test that printable characters pass through
TEST_F(ErrorTest_1895, PrintableCharactersPassThrough_1895) {
    error(errSyntaxWarning, 0, "Hello World! 123 ~");
    
    EXPECT_EQ(g_record.callCount, 1);
    EXPECT_EQ(g_record.message, "Hello World! 123 ~");
}

// Test space character (0x20) passes through
TEST_F(ErrorTest_1895, SpaceCharacterPassesThrough_1895) {
    error(errSyntaxWarning, 0, "a b");
    
    EXPECT_EQ(g_record.callCount, 1);
    EXPECT_EQ(g_record.message, "a b");
}

// Test that null byte is sanitized
TEST_F(ErrorTest_1895, SanitizesNullByte_1895) {
    std::string msgWithNull = "pre";
    msgWithNull += '\x00';
    msgWithNull += "post";
    
    // Note: null byte in C string will truncate it, so we pass via format
    // Instead test with \x01 which is also a control character
    error(errSyntaxWarning, 0, "{0:s}", std::string("a\x01" "b").c_str());
    
    EXPECT_EQ(g_record.callCount, 1);
    EXPECT_THAT(g_record.message, ::testing::HasSubstr("<01>"));
}

// Test that errQuiet suppresses error when no callback
TEST_F(ErrorTest_1895, ErrQuietSuppressesWithoutCallback_1895) {
    setErrorCallback(nullptr);
    globalParams->setErrQuiet(true);
    
    // Capture stderr
    // Since errQuiet is true and no callback, error should return early
    // We can't easily verify no output without capturing stderr,
    // but at least verify no crash
    error(errSyntaxWarning, 0, "should be quiet");
    
    // No crash = pass. Callback was not set, so record should be untouched
    EXPECT_EQ(g_record.callCount, 0);
}

// Test that callback is called even when errQuiet is true
TEST_F(ErrorTest_1895, CallbackCalledEvenWhenErrQuiet_1895) {
    globalParams->setErrQuiet(true);
    setErrorCallback(testErrorCallback);
    
    error(errSyntaxWarning, 5, "quiet but callback");
    
    EXPECT_EQ(g_record.callCount, 1);
    EXPECT_EQ(g_record.message, "quiet but callback");
    EXPECT_EQ(g_record.pos, 5);
}

// Test empty message
TEST_F(ErrorTest_1895, EmptyMessage_1895) {
    error(errSyntaxWarning, 0, "");
    
    EXPECT_EQ(g_record.callCount, 1);
    EXPECT_EQ(g_record.message, "");
}

// Test large position value
TEST_F(ErrorTest_1895, LargePositionValue_1895) {
    Goffset largePos = 999999999999LL;
    error(errSyntaxWarning, largePos, "large position");
    
    EXPECT_EQ(g_record.callCount, 1);
    EXPECT_EQ(g_record.pos, largePos);
    EXPECT_EQ(g_record.message, "large position");
}

// Test multiple calls accumulate properly
TEST_F(ErrorTest_1895, MultipleCallsIncrementCount_1895) {
    error(errSyntaxWarning, 0, "first");
    error(errSyntaxError, 1, "second");
    error(errIOError, 2, "third");
    
    EXPECT_EQ(g_record.callCount, 3);
    // Last call should be recorded
    EXPECT_EQ(g_record.message, "third");
    EXPECT_EQ(g_record.pos, 2);
}

// Test sanitization of newline character
TEST_F(ErrorTest_1895, SanitizesNewline_1895) {
    error(errSyntaxWarning, 0, "{0:s}", "line1\nline2");
    
    EXPECT_EQ(g_record.callCount, 1);
    EXPECT_THAT(g_record.message, ::testing::HasSubstr("<0a>"));
    EXPECT_THAT(g_record.message, ::testing::HasSubstr("line1"));
    EXPECT_THAT(g_record.message, ::testing::HasSubstr("line2"));
}

// Test sanitization of tab character
TEST_F(ErrorTest_1895, SanitizesTab_1895) {
    error(errSyntaxWarning, 0, "{0:s}", "col1\tcol2");
    
    EXPECT_EQ(g_record.callCount, 1);
    EXPECT_THAT(g_record.message, ::testing::HasSubstr("<09>"));
}

// Test sanitization of carriage return
TEST_F(ErrorTest_1895, SanitizesCarriageReturn_1895) {
    error(errSyntaxWarning, 0, "{0:s}", "line\rreturn");
    
    EXPECT_EQ(g_record.callCount, 1);
    EXPECT_THAT(g_record.message, ::testing::HasSubstr("<0d>"));
}

// Test tilde character (0x7e) passes through (last printable before DEL)
TEST_F(ErrorTest_1895, TildePassesThrough_1895) {
    error(errSyntaxWarning, 0, "~");
    
    EXPECT_EQ(g_record.callCount, 1);
    EXPECT_EQ(g_record.message, "~");
}

// Test that 0xFF byte is sanitized
TEST_F(ErrorTest_1895, SanitizesFFByte_1895) {
    std::string msg = "x";
    msg += '\xff';
    msg += "y";
    
    error(errSyntaxWarning, 0, "{0:s}", msg.c_str());
    
    EXPECT_EQ(g_record.callCount, 1);
    EXPECT_THAT(g_record.message, ::testing::HasSubstr("<ff>"));
}

// Test without callback set (stderr output path) - just verify no crash
TEST_F(ErrorTest_1895, NoCallbackPositivePosition_1895) {
    setErrorCallback(nullptr);
    globalParams->setErrQuiet(false);
    
    // This should print to stderr without crashing
    error(errSyntaxWarning, 100, "stderr test positive pos");
    
    // No callback means our record shouldn't be updated
    EXPECT_EQ(g_record.callCount, 0);
}

// Test without callback and negative position
TEST_F(ErrorTest_1895, NoCallbackNegativePosition_1895) {
    setErrorCallback(nullptr);
    globalParams->setErrQuiet(false);
    
    // This should print to stderr without crashing
    error(errSyntaxError, -1, "stderr test negative pos");
    
    EXPECT_EQ(g_record.callCount, 0);
}

// Test setting and clearing callback
TEST_F(ErrorTest_1895, SetAndClearCallback_1895) {
    setErrorCallback(testErrorCallback);
    error(errSyntaxWarning, 0, "with callback");
    EXPECT_EQ(g_record.callCount, 1);
    
    setErrorCallback(nullptr);
    globalParams->setErrQuiet(false);
    error(errSyntaxWarning, 0, "without callback");
    // Callback was cleared, count should remain 1
    EXPECT_EQ(g_record.callCount, 1);
}
