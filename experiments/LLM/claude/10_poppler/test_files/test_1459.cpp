#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <memory>

#include "Lexer.h"
#include "Object.h"
#include "Stream.h"

// We need a concrete Stream implementation for testing
// Using a minimal mock/fake stream that extends Stream
class FakeStream : public Stream {
public:
    FakeStream() : pos_(0) {}
    
    StreamKind getKind() const override { return strWeird; }
    
    bool rewind() override {
        pos_ = 0;
        return true;
    }
    
    void close() override {}
    
    int getChar() override {
        if (pos_ < static_cast<Goffset>(data_.size())) {
            return static_cast<unsigned char>(data_[pos_++]);
        }
        return EOF;
    }
    
    int lookChar() override {
        if (pos_ < static_cast<Goffset>(data_.size())) {
            return static_cast<unsigned char>(data_[pos_]);
        }
        return EOF;
    }
    
    int getRawChar() override { return getChar(); }
    
    void getRawChars(int nChars, int *buffer) override {}
    
    int getUnfilteredChar() override { return getChar(); }
    
    bool unfilteredRewind() override { return rewind(); }
    
    Goffset getPos() override { return pos_; }
    
    void setPos(Goffset pos, int dir = 0) override {
        if (dir == 0) {
            pos_ = pos;
        } else {
            pos_ = static_cast<Goffset>(data_.size()) - pos;
        }
        if (pos_ < 0) pos_ = 0;
        if (pos_ > static_cast<Goffset>(data_.size())) pos_ = static_cast<Goffset>(data_.size());
    }
    
    bool isBinary(bool last = true) const override { return false; }
    
    BaseStream *getBaseStream() override { return nullptr; }
    
    Stream *getUndecodedStream() override { return this; }
    
    Dict *getDict() override { return nullptr; }
    
    Object *getDictObject() override { return nullptr; }
    
    void setData(const std::string &d) { data_ = d; }
    
private:
    std::string data_;
    Goffset pos_;
    
    bool hasGetChars() override { return false; }
    int getChars(int nChars, unsigned char *buffer) override {
        int i = 0;
        while (i < nChars) {
            int c = getChar();
            if (c == EOF) break;
            buffer[i++] = static_cast<unsigned char>(c);
        }
        return i;
    }
};

class LexerTest_1459 : public ::testing::Test {
protected:
    void SetUp() override {
        // No XRef needed for basic tests - pass nullptr
    }
};

// Test that Lexer can be constructed with a stream
TEST_F(LexerTest_1459, ConstructWithStream_1459) {
    auto stream = std::make_unique<FakeStream>();
    stream->setData("123");
    // Lexer takes ownership of the stream
    Lexer lexer(nullptr, std::move(stream));
    // If we get here without crashing, construction succeeded
    SUCCEED();
}

// Test getPos returns a valid position for stream-based lexer
TEST_F(LexerTest_1459, GetPosReturnsStreamPosition_1459) {
    auto stream = std::make_unique<FakeStream>();
    stream->setData("123 456");
    Lexer lexer(nullptr, std::move(stream));
    
    Goffset pos = lexer.getPos();
    // Position should be >= 0 since we have a valid stream
    EXPECT_GE(pos, 0);
}

// Test getStream returns non-null for stream-based lexer
TEST_F(LexerTest_1459, GetStreamReturnsNonNull_1459) {
    auto stream = std::make_unique<FakeStream>();
    stream->setData("test");
    Lexer lexer(nullptr, std::move(stream));
    
    Stream *s = lexer.getStream();
    // The stream should be accessible
    // Note: depending on implementation, this could be null after certain operations
    // but initially it should be available
    EXPECT_NE(s, nullptr);
}

// Test hasXRef returns false when XRef is null
TEST_F(LexerTest_1459, HasXRefReturnsFalseWhenNull_1459) {
    auto stream = std::make_unique<FakeStream>();
    stream->setData("test");
    Lexer lexer(nullptr, std::move(stream));
    
    EXPECT_FALSE(lexer.hasXRef());
}

// Test getXRef returns null when constructed with null XRef
TEST_F(LexerTest_1459, GetXRefReturnsNullWhenConstructedWithNull_1459) {
    auto stream = std::make_unique<FakeStream>();
    stream->setData("test");
    Lexer lexer(nullptr, std::move(stream));
    
    EXPECT_EQ(lexer.getXRef(), nullptr);
}

// Test isSpace with various space characters
TEST_F(LexerTest_1459, IsSpaceWithSpaceChar_1459) {
    EXPECT_TRUE(Lexer::isSpace(' '));
}

TEST_F(LexerTest_1459, IsSpaceWithTab_1459) {
    EXPECT_TRUE(Lexer::isSpace('\t'));
}

TEST_F(LexerTest_1459, IsSpaceWithNewline_1459) {
    EXPECT_TRUE(Lexer::isSpace('\n'));
}

TEST_F(LexerTest_1459, IsSpaceWithCarriageReturn_1459) {
    EXPECT_TRUE(Lexer::isSpace('\r'));
}

TEST_F(LexerTest_1459, IsSpaceWithFormFeed_1459) {
    EXPECT_TRUE(Lexer::isSpace('\f'));
}

TEST_F(LexerTest_1459, IsSpaceWithNullChar_1459) {
    // PDF spec considers null (0x00) as whitespace
    EXPECT_TRUE(Lexer::isSpace('\0'));
}

// Test isSpace with non-space characters
TEST_F(LexerTest_1459, IsSpaceWithAlpha_1459) {
    EXPECT_FALSE(Lexer::isSpace('a'));
}

TEST_F(LexerTest_1459, IsSpaceWithDigit_1459) {
    EXPECT_FALSE(Lexer::isSpace('0'));
}

TEST_F(LexerTest_1459, IsSpaceWithSlash_1459) {
    EXPECT_FALSE(Lexer::isSpace('/'));
}

TEST_F(LexerTest_1459, IsSpaceWithPercent_1459) {
    EXPECT_FALSE(Lexer::isSpace('%'));
}

// Test getObj for integer parsing
TEST_F(LexerTest_1459, GetObjParsesInteger_1459) {
    auto stream = std::make_unique<FakeStream>();
    stream->setData("42");
    Lexer lexer(nullptr, std::move(stream));
    
    Object obj = lexer.getObj(0);
    EXPECT_TRUE(obj.isInt());
    EXPECT_EQ(obj.getInt(), 42);
}

// Test getObj for negative integer
TEST_F(LexerTest_1459, GetObjParsesNegativeInteger_1459) {
    auto stream = std::make_unique<FakeStream>();
    stream->setData("-7");
    Lexer lexer(nullptr, std::move(stream));
    
    Object obj = lexer.getObj(0);
    EXPECT_TRUE(obj.isInt());
    EXPECT_EQ(obj.getInt(), -7);
}

// Test getObj for real number
TEST_F(LexerTest_1459, GetObjParsesReal_1459) {
    auto stream = std::make_unique<FakeStream>();
    stream->setData("3.14");
    Lexer lexer(nullptr, std::move(stream));
    
    Object obj = lexer.getObj(0);
    EXPECT_TRUE(obj.isReal());
    EXPECT_NEAR(obj.getReal(), 3.14, 0.001);
}

// Test getObj for boolean true
TEST_F(LexerTest_1459, GetObjParsesBoolTrue_1459) {
    auto stream = std::make_unique<FakeStream>();
    stream->setData("true");
    Lexer lexer(nullptr, std::move(stream));
    
    Object obj = lexer.getObj(0);
    EXPECT_TRUE(obj.isBool());
    EXPECT_TRUE(obj.getBool());
}

// Test getObj for boolean false
TEST_F(LexerTest_1459, GetObjParsesBoolFalse_1459) {
    auto stream = std::make_unique<FakeStream>();
    stream->setData("false");
    Lexer lexer(nullptr, std::move(stream));
    
    Object obj = lexer.getObj(0);
    EXPECT_TRUE(obj.isBool());
    EXPECT_FALSE(obj.getBool());
}

// Test getObj for name
TEST_F(LexerTest_1459, GetObjParsesName_1459) {
    auto stream = std::make_unique<FakeStream>();
    stream->setData("/MyName");
    Lexer lexer(nullptr, std::move(stream));
    
    Object obj = lexer.getObj(0);
    EXPECT_TRUE(obj.isName());
    EXPECT_STREQ(obj.getName(), "MyName");
}

// Test getObj for string literal
TEST_F(LexerTest_1459, GetObjParsesStringLiteral_1459) {
    auto stream = std::make_unique<FakeStream>();
    stream->setData("(Hello World)");
    Lexer lexer(nullptr, std::move(stream));
    
    Object obj = lexer.getObj(0);
    EXPECT_TRUE(obj.isString());
}

// Test getObj for hex string
TEST_F(LexerTest_1459, GetObjParsesHexString_1459) {
    auto stream = std::make_unique<FakeStream>();
    stream->setData("<48656C6C6F>");
    Lexer lexer(nullptr, std::move(stream));
    
    Object obj = lexer.getObj(0);
    EXPECT_TRUE(obj.isHexString());
}

// Test getObj for null
TEST_F(LexerTest_1459, GetObjParsesNull_1459) {
    auto stream = std::make_unique<FakeStream>();
    stream->setData("null");
    Lexer lexer(nullptr, std::move(stream));
    
    Object obj = lexer.getObj(0);
    EXPECT_TRUE(obj.isNull());
}

// Test getObj for array start
TEST_F(LexerTest_1459, GetObjParsesArrayOpen_1459) {
    auto stream = std::make_unique<FakeStream>();
    stream->setData("[");
    Lexer lexer(nullptr, std::move(stream));
    
    Object obj = lexer.getObj(0);
    EXPECT_TRUE(obj.isCmd());
    EXPECT_STREQ(obj.getCmd(), "[");
}

// Test getObj for array close
TEST_F(LexerTest_1459, GetObjParsesArrayClose_1459) {
    auto stream = std::make_unique<FakeStream>();
    stream->setData("]");
    Lexer lexer(nullptr, std::move(stream));
    
    Object obj = lexer.getObj(0);
    EXPECT_TRUE(obj.isCmd());
    EXPECT_STREQ(obj.getCmd(), "]");
}

// Test getObj for dict open
TEST_F(LexerTest_1459, GetObjParsesDictOpen_1459) {
    auto stream = std::make_unique<FakeStream>();
    stream->setData("<<");
    Lexer lexer(nullptr, std::move(stream));
    
    Object obj = lexer.getObj(0);
    EXPECT_TRUE(obj.isCmd());
    EXPECT_STREQ(obj.getCmd(), "<<");
}

// Test getObj for dict close
TEST_F(LexerTest_1459, GetObjParsesDictClose_1459) {
    auto stream = std::make_unique<FakeStream>();
    stream->setData(">>");
    Lexer lexer(nullptr, std::move(stream));
    
    Object obj = lexer.getObj(0);
    EXPECT_TRUE(obj.isCmd());
    EXPECT_STREQ(obj.getCmd(), ">>");
}

// Test getObj returns EOF at end of stream
TEST_F(LexerTest_1459, GetObjReturnsEOFAtEnd_1459) {
    auto stream = std::make_unique<FakeStream>();
    stream->setData("");
    Lexer lexer(nullptr, std::move(stream));
    
    Object obj = lexer.getObj(0);
    EXPECT_TRUE(obj.isEOF());
}

// Test multiple getObj calls
TEST_F(LexerTest_1459, GetObjParsesMultipleTokens_1459) {
    auto stream = std::make_unique<FakeStream>();
    stream->setData("42 3.14 /Name");
    Lexer lexer(nullptr, std::move(stream));
    
    Object obj1 = lexer.getObj(0);
    EXPECT_TRUE(obj1.isInt());
    EXPECT_EQ(obj1.getInt(), 42);
    
    Object obj2 = lexer.getObj(0);
    EXPECT_TRUE(obj2.isReal());
    EXPECT_NEAR(obj2.getReal(), 3.14, 0.001);
    
    Object obj3 = lexer.getObj(0);
    EXPECT_TRUE(obj3.isName());
    EXPECT_STREQ(obj3.getName(), "Name");
}

// Test setPos changes stream position
TEST_F(LexerTest_1459, SetPosChangesPosition_1459) {
    auto stream = std::make_unique<FakeStream>();
    stream->setData("123 456 789");
    Lexer lexer(nullptr, std::move(stream));
    
    // Read first token
    Object obj1 = lexer.getObj(0);
    EXPECT_TRUE(obj1.isInt());
    
    Goffset posAfterFirst = lexer.getPos();
    
    // Reset to beginning
    lexer.setPos(0);
    Goffset posAfterReset = lexer.getPos();
    EXPECT_EQ(posAfterReset, 0);
}

// Test skipToNextLine
TEST_F(LexerTest_1459, SkipToNextLine_1459) {
    auto stream = std::make_unique<FakeStream>();
    stream->setData("ignore this\n42");
    Lexer lexer(nullptr, std::move(stream));
    
    lexer.skipToNextLine();
    
    Object obj = lexer.getObj(0);
    EXPECT_TRUE(obj.isInt());
    EXPECT_EQ(obj.getInt(), 42);
}

// Test getObj with command string matching
TEST_F(LexerTest_1459, GetObjWithCmdMatch_1459) {
    auto stream = std::make_unique<FakeStream>();
    stream->setData("[");
    Lexer lexer(nullptr, std::move(stream));
    
    Object obj = lexer.getObj(std::string_view("["), 0);
    // When matching command, it should return EOF (consumed) or the matched command
    // This depends on implementation
    EXPECT_TRUE(obj.isEOF() || obj.isCmd());
}

// Test isSpace with EOF (-1)
TEST_F(LexerTest_1459, IsSpaceWithEOF_1459) {
    EXPECT_FALSE(Lexer::isSpace(-1));
}

// Test isSpace boundary - character just above space
TEST_F(LexerTest_1459, IsSpaceWithExclamationMark_1459) {
    EXPECT_FALSE(Lexer::isSpace('!'));
}

// Test empty name
TEST_F(LexerTest_1459, GetObjParsesEmptyName_1459) {
    auto stream = std::make_unique<FakeStream>();
    stream->setData("/ ");
    Lexer lexer(nullptr, std::move(stream));
    
    Object obj = lexer.getObj(0);
    EXPECT_TRUE(obj.isName());
}

// Test comment handling
TEST_F(LexerTest_1459, GetObjSkipsComments_1459) {
    auto stream = std::make_unique<FakeStream>();
    stream->setData("% this is a comment\n42");
    Lexer lexer(nullptr, std::move(stream));
    
    Object obj = lexer.getObj(0);
    EXPECT_TRUE(obj.isInt());
    EXPECT_EQ(obj.getInt(), 42);
}

// Test zero integer
TEST_F(LexerTest_1459, GetObjParsesZero_1459) {
    auto stream = std::make_unique<FakeStream>();
    stream->setData("0");
    Lexer lexer(nullptr, std::move(stream));
    
    Object obj = lexer.getObj(0);
    EXPECT_TRUE(obj.isInt());
    EXPECT_EQ(obj.getInt(), 0);
}

// Test nested parentheses in string
TEST_F(LexerTest_1459, GetObjParsesNestedParenString_1459) {
    auto stream = std::make_unique<FakeStream>();
    stream->setData("(Hello (World))");
    Lexer lexer(nullptr, std::move(stream));
    
    Object obj = lexer.getObj(0);
    EXPECT_TRUE(obj.isString());
}

// Test empty hex string
TEST_F(LexerTest_1459, GetObjParsesEmptyHexString_1459) {
    auto stream = std::make_unique<FakeStream>();
    stream->setData("<>");
    Lexer lexer(nullptr, std::move(stream));
    
    Object obj = lexer.getObj(0);
    EXPECT_TRUE(obj.isHexString());
}

// Test skipChar
TEST_F(LexerTest_1459, SkipCharAdvancesPosition_1459) {
    auto stream = std::make_unique<FakeStream>();
    stream->setData("X42");
    Lexer lexer(nullptr, std::move(stream));
    
    lexer.skipChar();
    
    Object obj = lexer.getObj(0);
    EXPECT_TRUE(obj.isInt());
    EXPECT_EQ(obj.getInt(), 42);
}

// Test large integer
TEST_F(LexerTest_1459, GetObjParsesLargeInteger_1459) {
    auto stream = std::make_unique<FakeStream>();
    stream->setData("999999999");
    Lexer lexer(nullptr, std::move(stream));
    
    Object obj = lexer.getObj(0);
    EXPECT_TRUE(obj.isInt() || obj.isInt64());
}

// Test positive sign for number
TEST_F(LexerTest_1459, GetObjParsesPositiveSign_1459) {
    auto stream = std::make_unique<FakeStream>();
    stream->setData("+5");
    Lexer lexer(nullptr, std::move(stream));
    
    Object obj = lexer.getObj(0);
    EXPECT_TRUE(obj.isInt());
    EXPECT_EQ(obj.getInt(), 5);
}

// Test whitespace-only stream returns EOF
TEST_F(LexerTest_1459, GetObjWhitespaceOnlyReturnsEOF_1459) {
    auto stream = std::make_unique<FakeStream>();
    stream->setData("   \t\n  ");
    Lexer lexer(nullptr, std::move(stream));
    
    Object obj = lexer.getObj(0);
    EXPECT_TRUE(obj.isEOF());
}

// Test skipToNextLine with carriage return
TEST_F(LexerTest_1459, SkipToNextLineWithCR_1459) {
    auto stream = std::make_unique<FakeStream>();
    stream->setData("ignore\r99");
    Lexer lexer(nullptr, std::move(stream));
    
    lexer.skipToNextLine();
    
    Object obj = lexer.getObj(0);
    EXPECT_TRUE(obj.isInt());
    EXPECT_EQ(obj.getInt(), 99);
}

// Test skipToNextLine with CRLF
TEST_F(LexerTest_1459, SkipToNextLineWithCRLF_1459) {
    auto stream = std::make_unique<FakeStream>();
    stream->setData("ignore\r\n77");
    Lexer lexer(nullptr, std::move(stream));
    
    lexer.skipToNextLine();
    
    Object obj = lexer.getObj(0);
    EXPECT_TRUE(obj.isInt());
    EXPECT_EQ(obj.getInt(), 77);
}

// Test name with hex escape
TEST_F(LexerTest_1459, GetObjParsesNameWithHexEscape_1459) {
    auto stream = std::make_unique<FakeStream>();
    stream->setData("/A#42C");  // #42 is 'B' in hex
    Lexer lexer(nullptr, std::move(stream));
    
    Object obj = lexer.getObj(0);
    EXPECT_TRUE(obj.isName());
    EXPECT_STREQ(obj.getName(), "ABC");
}

// Test real number with leading dot
TEST_F(LexerTest_1459, GetObjParsesRealWithLeadingDot_1459) {
    auto stream = std::make_unique<FakeStream>();
    stream->setData(".5");
    Lexer lexer(nullptr, std::move(stream));
    
    Object obj = lexer.getObj(0);
    EXPECT_TRUE(obj.isReal());
    EXPECT_NEAR(obj.getReal(), 0.5, 0.001);
}
