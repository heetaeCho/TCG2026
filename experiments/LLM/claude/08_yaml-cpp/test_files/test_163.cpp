#include <gtest/gtest.h>
#include <sstream>
#include <string>
#include "yaml-cpp/exceptions.h"
#include "stream.h"
#include "exp.h"

// Forward declaration of the function under test
namespace YAML {
const std::string ScanTagHandle(Stream& INPUT, bool& canBeHandle);
}

class ScanTagHandleTest_163 : public ::testing::Test {
protected:
    std::unique_ptr<YAML::Stream> makeStream(const std::string& input) {
        auto* ss = new std::istringstream(input);
        streams_.push_back(ss);
        return std::make_unique<YAML::Stream>(*ss);
    }

    std::vector<std::istringstream*> streams_;

    ~ScanTagHandleTest_163() override {
        for (auto* s : streams_) {
            delete s;
        }
    }
};

// Test with empty input - should return empty string
TEST_F(ScanTagHandleTest_163, EmptyInput_163) {
    auto stream = makeStream("");
    bool canBeHandle = false;
    std::string result = YAML::ScanTagHandle(*stream, canBeHandle);
    EXPECT_EQ(result, "");
    EXPECT_TRUE(canBeHandle);
}

// Test with just a tag character '!' - should return empty string and stop at '!'
TEST_F(ScanTagHandleTest_163, OnlyTagCharacter_163) {
    auto stream = makeStream("!");
    bool canBeHandle = false;
    std::string result = YAML::ScanTagHandle(*stream, canBeHandle);
    EXPECT_EQ(result, "");
    EXPECT_TRUE(canBeHandle);
    // The '!' should still be in the stream (we break, not consume it)
    EXPECT_EQ(stream->peek(), '!');
}

// Test with simple word characters followed by '!'
TEST_F(ScanTagHandleTest_163, SimpleWordFollowedByTag_163) {
    auto stream = makeStream("abc!");
    bool canBeHandle = true;
    std::string result = YAML::ScanTagHandle(*stream, canBeHandle);
    EXPECT_EQ(result, "abc");
    EXPECT_TRUE(canBeHandle);
    EXPECT_EQ(stream->peek(), '!');
}

// Test with simple word characters (no tag character at end)
TEST_F(ScanTagHandleTest_163, SimpleWordNoTag_163) {
    auto stream = makeStream("abc ");
    bool canBeHandle = true;
    std::string result = YAML::ScanTagHandle(*stream, canBeHandle);
    // Word chars are alphanumeric + '-', space is not a word char
    // When non-word char is encountered, canBeHandle becomes false
    // Then Exp::Tag() is tried; space likely doesn't match Tag either
    EXPECT_FALSE(result.empty() || result == "abc");
    // At minimum, "abc" should be consumed
}

// Test with alphanumeric word characters
TEST_F(ScanTagHandleTest_163, AlphanumericWord_163) {
    auto stream = makeStream("tag123!");
    bool canBeHandle = true;
    std::string result = YAML::ScanTagHandle(*stream, canBeHandle);
    EXPECT_EQ(result, "tag123");
    EXPECT_TRUE(canBeHandle);
}

// Test with hyphen in word (hyphens are typically valid word chars in YAML)
TEST_F(ScanTagHandleTest_163, WordWithHyphen_163) {
    auto stream = makeStream("my-tag!");
    bool canBeHandle = true;
    std::string result = YAML::ScanTagHandle(*stream, canBeHandle);
    EXPECT_EQ(result, "my-tag");
    EXPECT_TRUE(canBeHandle);
}

// Test that a non-word character after word chars causes canBeHandle to become false,
// and then encountering '!' throws ParserException
TEST_F(ScanTagHandleTest_163, NonWordThenTagThrows_163) {
    // A character like '#' is a valid tag URI char but not a word char.
    // If we have word chars, then a non-word (but valid tag) char, then '!',
    // it should throw because canBeHandle was true initially, became false,
    // and then '!' is encountered with canBeHandle == false.
    auto stream = makeStream("abc#def!");
    bool canBeHandle = true;
    EXPECT_THROW(YAML::ScanTagHandle(*stream, canBeHandle), YAML::ParserException);
}

// Test with URI-style tag characters (no word chars at start means canBeHandle stays true
// only if first char is a word char)
TEST_F(ScanTagHandleTest_163, TagURICharacters_163) {
    // '%' followed by hex digits is a valid tag URI escape
    // Starting with a non-word char means canBeHandle becomes false immediately
    auto stream = makeStream("%41 ");
    bool canBeHandle = true;
    std::string result = YAML::ScanTagHandle(*stream, canBeHandle);
    EXPECT_FALSE(canBeHandle);
    // Should have consumed the tag-valid characters
}

// Test with space immediately (nothing to scan)
TEST_F(ScanTagHandleTest_163, SpaceImmediately_163) {
    auto stream = makeStream(" abc");
    bool canBeHandle = true;
    std::string result = YAML::ScanTagHandle(*stream, canBeHandle);
    // Space is not a word char, canBeHandle becomes false
    // Space is not a tag char either, so we break
    EXPECT_EQ(result, "");
    EXPECT_FALSE(canBeHandle);
}

// Test canBeHandle is initially set to true by the function
TEST_F(ScanTagHandleTest_163, CanBeHandleInitializedTrue_163) {
    auto stream = makeStream("!");
    bool canBeHandle = false; // Start with false
    YAML::ScanTagHandle(*stream, canBeHandle);
    // The function sets canBeHandle = true at the beginning
    EXPECT_TRUE(canBeHandle);
}

// Test with only word characters and EOF
TEST_F(ScanTagHandleTest_163, WordCharsToEOF_163) {
    auto stream = makeStream("hello");
    bool canBeHandle = true;
    std::string result = YAML::ScanTagHandle(*stream, canBeHandle);
    EXPECT_EQ(result, "hello");
    EXPECT_TRUE(canBeHandle);
}

// Test with a single word character followed by '!'
TEST_F(ScanTagHandleTest_163, SingleCharHandle_163) {
    auto stream = makeStream("a!");
    bool canBeHandle = true;
    std::string result = YAML::ScanTagHandle(*stream, canBeHandle);
    EXPECT_EQ(result, "a");
    EXPECT_TRUE(canBeHandle);
}

// Test with digits
TEST_F(ScanTagHandleTest_163, DigitsOnly_163) {
    auto stream = makeStream("123!");
    bool canBeHandle = true;
    std::string result = YAML::ScanTagHandle(*stream, canBeHandle);
    EXPECT_EQ(result, "123");
    EXPECT_TRUE(canBeHandle);
}

// Test with a long word
TEST_F(ScanTagHandleTest_163, LongWord_163) {
    std::string longWord(100, 'a');
    auto stream = makeStream(longWord + "!");
    bool canBeHandle = true;
    std::string result = YAML::ScanTagHandle(*stream, canBeHandle);
    EXPECT_EQ(result, longWord);
    EXPECT_TRUE(canBeHandle);
}

// Test with tag URI characters that include valid URI chars like '/' and ':'
TEST_F(ScanTagHandleTest_163, URIWithSlashAndColon_163) {
    // Start with non-word makes canBeHandle false, then tag chars are consumed
    // But '/' is not a word char, so canBeHandle becomes false
    // Then if '!' is encountered, it should throw
    auto stream = makeStream("abc/def!");
    bool canBeHandle = true;
    EXPECT_THROW(YAML::ScanTagHandle(*stream, canBeHandle), YAML::ParserException);
}

// Test: pure tag-valid (non-word) characters ending at EOF (no '!' encountered)
TEST_F(ScanTagHandleTest_163, TagCharsEndAtEOF_163) {
    // After canBeHandle becomes false, Exp::Tag() chars are consumed until EOF
    // No '!' means no exception
    auto stream = makeStream("abc/def");
    bool canBeHandle = true;
    std::string result = YAML::ScanTagHandle(*stream, canBeHandle);
    EXPECT_FALSE(canBeHandle);
    // Should contain the consumed characters
    EXPECT_FALSE(result.empty());
}

// Test: pure tag-valid characters ending at space (no '!')
TEST_F(ScanTagHandleTest_163, TagCharsEndAtSpace_163) {
    auto stream = makeStream("abc/def ");
    bool canBeHandle = true;
    std::string result = YAML::ScanTagHandle(*stream, canBeHandle);
    EXPECT_FALSE(canBeHandle);
    EXPECT_FALSE(result.empty());
}
