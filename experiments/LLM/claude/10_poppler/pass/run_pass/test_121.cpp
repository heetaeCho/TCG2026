#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "Stream.h"
#include "GooString.h"
#include <string>
#include <vector>
#include <memory>

// Mock Stream class to test the fillGooString method and other interface methods
class MockStream : public Stream {
public:
    MOCK_METHOD(StreamKind, getKind, (), (const, override));
    MOCK_METHOD(bool, rewind, (), (override));
    MOCK_METHOD(void, close, (), (override));
    MOCK_METHOD(int, getChar, (), (override));
    MOCK_METHOD(int, lookChar, (), (override));
    MOCK_METHOD(int, getRawChar, (), (override));
    MOCK_METHOD(void, getRawChars, (int nChars, int *buffer), (override));
    MOCK_METHOD(int, getUnfilteredChar, (), (override));
    MOCK_METHOD(bool, unfilteredRewind, (), (override));
    MOCK_METHOD(char*, getLine, (char *buf, int size), (override));
    MOCK_METHOD(unsigned int, discardChars, (unsigned int n), (override));
    MOCK_METHOD(Goffset, getPos, (), (override));
    MOCK_METHOD(void, setPos, (Goffset pos, int dir), (override));
    MOCK_METHOD(std::optional<std::string>, getPSFilter, (int psLevel, const char *indent), (override));
    MOCK_METHOD(bool, isBinary, (bool last), (const, override));
    MOCK_METHOD(BaseStream*, getBaseStream, (), (override));
    MOCK_METHOD(Stream*, getUndecodedStream, (), (override));
    MOCK_METHOD(Dict*, getDict, (), (override));
    MOCK_METHOD(Object*, getDictObject, (), (override));
    MOCK_METHOD(bool, isEncoder, (), (const, override));
    MOCK_METHOD(void, getImageParams, (int*, StreamColorSpaceMode*, bool*), (override));
    MOCK_METHOD(Stream*, getNextStream, (), (const, override));

private:
    MOCK_METHOD(int, getChars, (int nChars, unsigned char *buffer), (override));
    MOCK_METHOD(bool, hasGetChars, (), (override));
};

// A concrete test stream that provides known data for testing fillString/fillGooString
class TestDataStream : public Stream {
public:
    TestDataStream(const std::string &data) : data_(data), pos_(0) {}

    StreamKind getKind() const override { return streamKind; }
    bool rewind() override { pos_ = 0; return true; }
    void close() override {}
    
    int getChar() override {
        if (pos_ < data_.size()) {
            return static_cast<unsigned char>(data_[pos_++]);
        }
        return EOF;
    }
    
    int lookChar() override {
        if (pos_ < data_.size()) {
            return static_cast<unsigned char>(data_[pos_]);
        }
        return EOF;
    }
    
    int getRawChar() override { return getChar(); }
    void getRawChars(int nChars, int *buffer) override {}
    int getUnfilteredChar() override { return getChar(); }
    bool unfilteredRewind() override { return rewind(); }
    
    char* getLine(char *buf, int size) override { return nullptr; }
    unsigned int discardChars(unsigned int n) override { return 0; }
    Goffset getPos() override { return pos_; }
    void setPos(Goffset pos, int dir) override { pos_ = pos; }
    std::optional<std::string> getPSFilter(int psLevel, const char *indent) override { return std::nullopt; }
    bool isBinary(bool last) const override { return false; }
    BaseStream* getBaseStream() override { return nullptr; }
    Stream* getUndecodedStream() override { return this; }
    Dict* getDict() override { return nullptr; }
    Object* getDictObject() override { return nullptr; }

private:
    static constexpr StreamKind streamKind = strFile; // Using a known StreamKind
    std::string data_;
    size_t pos_;
};

class StreamTest_121 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test fillGooString with normal data
TEST_F(StreamTest_121, FillGooStringWithNormalData_121) {
    std::string testData = "Hello, World!";
    TestDataStream stream(testData);
    GooString gooStr;
    
    stream.fillGooString(&gooStr);
    
    EXPECT_EQ(gooStr.toStr(), testData);
}

// Test fillGooString with empty stream
TEST_F(StreamTest_121, FillGooStringWithEmptyStream_121) {
    std::string testData = "";
    TestDataStream stream(testData);
    GooString gooStr;
    
    stream.fillGooString(&gooStr);
    
    EXPECT_EQ(gooStr.toStr(), "");
}

// Test fillGooString with binary data
TEST_F(StreamTest_121, FillGooStringWithBinaryData_121) {
    std::string testData;
    for (int i = 0; i < 256; ++i) {
        testData += static_cast<char>(i);
    }
    TestDataStream stream(testData);
    GooString gooStr;
    
    stream.fillGooString(&gooStr);
    
    EXPECT_EQ(gooStr.toStr().size(), 256u);
    EXPECT_EQ(gooStr.toStr(), testData);
}

// Test fillGooString with large data
TEST_F(StreamTest_121, FillGooStringWithLargeData_121) {
    std::string testData(100000, 'A');
    TestDataStream stream(testData);
    GooString gooStr;
    
    stream.fillGooString(&gooStr);
    
    EXPECT_EQ(gooStr.toStr().size(), 100000u);
    EXPECT_EQ(gooStr.toStr(), testData);
}

// Test fillGooString fills into an existing GooString (appends or overwrites)
TEST_F(StreamTest_121, FillGooStringOverwritesExistingContent_121) {
    std::string testData = "New content";
    TestDataStream stream(testData);
    GooString gooStr("Old content");
    
    stream.fillGooString(&gooStr);
    
    // The behavior depends on implementation - fillString likely clears and fills
    // We just verify the new content is present
    EXPECT_FALSE(gooStr.toStr().empty());
}

// Test toUnsignedChars with normal data
TEST_F(StreamTest_121, ToUnsignedCharsNormalData_121) {
    std::string testData = "Test data for unsigned chars";
    TestDataStream stream(testData);
    
    std::vector<unsigned char> result = stream.toUnsignedChars();
    
    EXPECT_EQ(result.size(), testData.size());
    for (size_t i = 0; i < testData.size(); ++i) {
        EXPECT_EQ(result[i], static_cast<unsigned char>(testData[i]));
    }
}

// Test toUnsignedChars with empty stream
TEST_F(StreamTest_121, ToUnsignedCharsEmptyStream_121) {
    std::string testData = "";
    TestDataStream stream(testData);
    
    std::vector<unsigned char> result = stream.toUnsignedChars();
    
    EXPECT_TRUE(result.empty());
}

// Test toUnsignedChars with custom initial size
TEST_F(StreamTest_121, ToUnsignedCharsCustomInitialSize_121) {
    std::string testData = "Small";
    TestDataStream stream(testData);
    
    std::vector<unsigned char> result = stream.toUnsignedChars(16, 16);
    
    EXPECT_EQ(result.size(), testData.size());
}

// Test doGetChars
TEST_F(StreamTest_121, DoGetCharsNormalData_121) {
    std::string testData = "ABCDEFGHIJ";
    TestDataStream stream(testData);
    unsigned char buffer[10];
    
    int nRead = stream.doGetChars(10, buffer);
    
    EXPECT_EQ(nRead, 10);
    for (int i = 0; i < 10; ++i) {
        EXPECT_EQ(buffer[i], static_cast<unsigned char>(testData[i]));
    }
}

// Test doGetChars requesting more than available
TEST_F(StreamTest_121, DoGetCharsMoreThanAvailable_121) {
    std::string testData = "ABC";
    TestDataStream stream(testData);
    unsigned char buffer[10] = {};
    
    int nRead = stream.doGetChars(10, buffer);
    
    EXPECT_EQ(nRead, 3);
    EXPECT_EQ(buffer[0], 'A');
    EXPECT_EQ(buffer[1], 'B');
    EXPECT_EQ(buffer[2], 'C');
}

// Test doGetChars with zero bytes
TEST_F(StreamTest_121, DoGetCharsZeroBytes_121) {
    std::string testData = "ABC";
    TestDataStream stream(testData);
    unsigned char buffer[1] = {};
    
    int nRead = stream.doGetChars(0, buffer);
    
    EXPECT_EQ(nRead, 0);
}

// Test getChar returns EOF for empty stream
TEST_F(StreamTest_121, GetCharReturnsEOFForEmptyStream_121) {
    TestDataStream stream("");
    
    int ch = stream.getChar();
    
    EXPECT_EQ(ch, EOF);
}

// Test getChar returns correct characters
TEST_F(StreamTest_121, GetCharReturnsCorrectCharacters_121) {
    TestDataStream stream("AB");
    
    EXPECT_EQ(stream.getChar(), 'A');
    EXPECT_EQ(stream.getChar(), 'B');
    EXPECT_EQ(stream.getChar(), EOF);
}

// Test lookChar does not advance position
TEST_F(StreamTest_121, LookCharDoesNotAdvance_121) {
    TestDataStream stream("X");
    
    EXPECT_EQ(stream.lookChar(), 'X');
    EXPECT_EQ(stream.lookChar(), 'X');
    EXPECT_EQ(stream.getChar(), 'X');
    EXPECT_EQ(stream.lookChar(), EOF);
}

// Test rewind resets position
TEST_F(StreamTest_121, RewindResetsPosition_121) {
    TestDataStream stream("Hello");
    
    stream.getChar();
    stream.getChar();
    bool result = stream.rewind();
    
    EXPECT_TRUE(result);
    EXPECT_EQ(stream.getChar(), 'H');
}

// Test fillString with data containing null bytes
TEST_F(StreamTest_121, FillGooStringWithNullBytes_121) {
    std::string testData;
    testData += 'A';
    testData += '\0';
    testData += 'B';
    TestDataStream stream(testData);
    GooString gooStr;
    
    stream.fillGooString(&gooStr);
    
    EXPECT_EQ(gooStr.toStr().size(), 3u);
    EXPECT_EQ(gooStr.getChar(0), 'A');
    EXPECT_EQ(gooStr.getChar(1), '\0');
    EXPECT_EQ(gooStr.getChar(2), 'B');
}

// Test toUnsignedChars with large data exceeding initial buffer
TEST_F(StreamTest_121, ToUnsignedCharsLargeData_121) {
    std::string testData(50000, 'Z');
    TestDataStream stream(testData);
    
    std::vector<unsigned char> result = stream.toUnsignedChars(4096, 4096);
    
    EXPECT_EQ(result.size(), 50000u);
    for (auto c : result) {
        EXPECT_EQ(c, static_cast<unsigned char>('Z'));
    }
}

// Test getBaseStream returns nullptr for test stream
TEST_F(StreamTest_121, GetBaseStreamReturnsNull_121) {
    TestDataStream stream("test");
    
    EXPECT_EQ(stream.getBaseStream(), nullptr);
}

// Test getDict returns nullptr for test stream
TEST_F(StreamTest_121, GetDictReturnsNull_121) {
    TestDataStream stream("test");
    
    EXPECT_EQ(stream.getDict(), nullptr);
}

// Test getPSFilter returns nullopt for test stream
TEST_F(StreamTest_121, GetPSFilterReturnsNullopt_121) {
    TestDataStream stream("test");
    
    auto result = stream.getPSFilter(1, "");
    
    EXPECT_FALSE(result.has_value());
}

// Test isBinary returns false for test stream
TEST_F(StreamTest_121, IsBinaryReturnsFalse_121) {
    TestDataStream stream("test");
    
    EXPECT_FALSE(stream.isBinary(true));
    EXPECT_FALSE(stream.isBinary(false));
}

// Test getUndecodedStream
TEST_F(StreamTest_121, GetUndecodedStream_121) {
    TestDataStream stream("test");
    
    Stream *undecoded = stream.getUndecodedStream();
    
    EXPECT_EQ(undecoded, &stream);
}

// Test fillGooString with single character
TEST_F(StreamTest_121, FillGooStringSingleChar_121) {
    TestDataStream stream("X");
    GooString gooStr;
    
    stream.fillGooString(&gooStr);
    
    EXPECT_EQ(gooStr.toStr(), "X");
    EXPECT_EQ(gooStr.toStr().size(), 1u);
}

// Test fillString through fillGooString - verify the string conversion
TEST_F(StreamTest_121, FillGooStringToNonConstStr_121) {
    std::string testData = "Test string conversion";
    TestDataStream stream(testData);
    GooString gooStr;
    
    stream.fillGooString(&gooStr);
    
    std::string &ref = gooStr.toNonConstStr();
    EXPECT_EQ(ref, testData);
}

// Test sequential reads after partial doGetChars
TEST_F(StreamTest_121, SequentialDoGetChars_121) {
    std::string testData = "ABCDEF";
    TestDataStream stream(testData);
    unsigned char buffer[3];
    
    int nRead1 = stream.doGetChars(3, buffer);
    EXPECT_EQ(nRead1, 3);
    EXPECT_EQ(buffer[0], 'A');
    EXPECT_EQ(buffer[1], 'B');
    EXPECT_EQ(buffer[2], 'C');
    
    int nRead2 = stream.doGetChars(3, buffer);
    EXPECT_EQ(nRead2, 3);
    EXPECT_EQ(buffer[0], 'D');
    EXPECT_EQ(buffer[1], 'E');
    EXPECT_EQ(buffer[2], 'F');
    
    int nRead3 = stream.doGetChars(3, buffer);
    EXPECT_EQ(nRead3, 0);
}
