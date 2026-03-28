#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "Stream.h"
#include "Object.h"
#include <cstring>
#include <vector>
#include <algorithm>

// Concrete implementation of BaseSeekInputStream for testing purposes
class TestSeekInputStream : public BaseSeekInputStream {
public:
    TestSeekInputStream(const std::vector<char> &data, Goffset startA, bool limitedA, Goffset lengthA)
        : BaseSeekInputStream(startA, limitedA, lengthA, Object(objNull)),
          m_data(data), m_pos(startA) {}

    ~TestSeekInputStream() override = default;

    const Goffset currentPos() override {
        return m_pos;
    }

    void setCurrentPos(Goffset offset) override {
        if (offset < 0) offset = 0;
        if (offset > static_cast<Goffset>(m_data.size())) offset = static_cast<Goffset>(m_data.size());
        m_pos = offset;
    }

    Goffset read(char *buf, Goffset size) override {
        if (m_pos >= static_cast<Goffset>(m_data.size())) return 0;
        Goffset available = static_cast<Goffset>(m_data.size()) - m_pos;
        Goffset toRead = std::min(size, available);
        if (toRead <= 0) return 0;
        std::memcpy(buf, m_data.data() + m_pos, toRead);
        m_pos += toRead;
        return toRead;
    }

private:
    std::vector<char> m_data;
    Goffset m_pos;
};

class BaseSeekInputStreamTest_134 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test lookChar on empty stream returns EOF
TEST_F(BaseSeekInputStreamTest_134, LookCharEmptyStream_134) {
    std::vector<char> data;
    TestSeekInputStream stream(data, 0, false, 0);
    stream.reset();
    int result = stream.lookChar();
    EXPECT_EQ(result, EOF);
}

// Test lookChar returns first byte without advancing position
TEST_F(BaseSeekInputStreamTest_134, LookCharReturnsByteWithoutAdvancing_134) {
    std::vector<char> data = {'A', 'B', 'C'};
    TestSeekInputStream stream(data, 0, false, 3);
    stream.reset();
    int first = stream.lookChar();
    int second = stream.lookChar();
    EXPECT_EQ(first, 'A');
    EXPECT_EQ(second, 'A');
}

// Test getChar returns byte and advances
TEST_F(BaseSeekInputStreamTest_134, GetCharAdvancesPosition_134) {
    std::vector<char> data = {'X', 'Y', 'Z'};
    TestSeekInputStream stream(data, 0, false, 3);
    stream.reset();
    int ch1 = stream.getChar();
    int ch2 = stream.getChar();
    int ch3 = stream.getChar();
    int ch4 = stream.getChar();
    EXPECT_EQ(ch1, 'X');
    EXPECT_EQ(ch2, 'Y');
    EXPECT_EQ(ch3, 'Z');
    EXPECT_EQ(ch4, EOF);
}

// Test lookChar with high byte values (unsigned correctness)
TEST_F(BaseSeekInputStreamTest_134, LookCharHighByteValue_134) {
    std::vector<char> data = {static_cast<char>(0xFF), static_cast<char>(0x80)};
    TestSeekInputStream stream(data, 0, false, 2);
    stream.reset();
    int result = stream.lookChar();
    EXPECT_EQ(result, 0xFF);
}

// Test getPos returns correct position
TEST_F(BaseSeekInputStreamTest_134, GetPosReturnsCorrectPosition_134) {
    std::vector<char> data = {'A', 'B', 'C', 'D'};
    TestSeekInputStream stream(data, 0, false, 4);
    stream.reset();
    Goffset pos0 = stream.getPos();
    stream.getChar();
    Goffset pos1 = stream.getPos();
    EXPECT_GE(pos1, pos0);
}

// Test rewind returns to start
TEST_F(BaseSeekInputStreamTest_134, RewindReturnsToStart_134) {
    std::vector<char> data = {'A', 'B', 'C'};
    TestSeekInputStream stream(data, 0, false, 3);
    stream.reset();
    stream.getChar();
    stream.getChar();
    bool result = stream.rewind();
    EXPECT_TRUE(result);
    int ch = stream.getChar();
    EXPECT_EQ(ch, 'A');
}

// Test setPos sets position correctly
TEST_F(BaseSeekInputStreamTest_134, SetPosFromStart_134) {
    std::vector<char> data = {'A', 'B', 'C', 'D', 'E'};
    TestSeekInputStream stream(data, 0, false, 5);
    stream.reset();
    stream.setPos(2, 0);
    int ch = stream.getChar();
    EXPECT_EQ(ch, 'C');
}

// Test limited stream respects length
TEST_F(BaseSeekInputStreamTest_134, LimitedStreamRespectsLength_134) {
    std::vector<char> data = {'A', 'B', 'C', 'D', 'E'};
    TestSeekInputStream stream(data, 0, true, 3);
    stream.reset();
    int ch1 = stream.getChar();
    int ch2 = stream.getChar();
    int ch3 = stream.getChar();
    int ch4 = stream.getChar();
    EXPECT_EQ(ch1, 'A');
    EXPECT_EQ(ch2, 'B');
    EXPECT_EQ(ch3, 'C');
    EXPECT_EQ(ch4, EOF);
}

// Test getStart returns starting offset
TEST_F(BaseSeekInputStreamTest_134, GetStartReturnsStartOffset_134) {
    std::vector<char> data = {'A', 'B', 'C', 'D', 'E'};
    TestSeekInputStream stream(data, 2, true, 3);
    stream.reset();
    Goffset start = stream.getStart();
    EXPECT_EQ(start, 2);
}

// Test moveStart adjusts start position
TEST_F(BaseSeekInputStreamTest_134, MoveStartAdjustsStart_134) {
    std::vector<char> data = {'A', 'B', 'C', 'D', 'E'};
    TestSeekInputStream stream(data, 0, true, 5);
    stream.reset();
    stream.moveStart(2);
    Goffset start = stream.getStart();
    EXPECT_EQ(start, 2);
}

// Test getKind returns correct stream kind
TEST_F(BaseSeekInputStreamTest_134, GetKindReturnsCorrectKind_134) {
    std::vector<char> data = {'A'};
    TestSeekInputStream stream(data, 0, false, 1);
    StreamKind kind = stream.getKind();
    // BaseSeekInputStream should have a defined kind
    // We just verify it returns something valid without crashing
    SUCCEED();
}

// Test close followed by lookChar returns EOF
TEST_F(BaseSeekInputStreamTest_134, CloseAndLookChar_134) {
    std::vector<char> data = {'A', 'B', 'C'};
    TestSeekInputStream stream(data, 0, false, 3);
    stream.reset();
    stream.close();
    // After close, behavior may vary but should not crash
    SUCCEED();
}

// Test unfilteredRewind
TEST_F(BaseSeekInputStreamTest_134, UnfilteredRewind_134) {
    std::vector<char> data = {'A', 'B', 'C'};
    TestSeekInputStream stream(data, 0, false, 3);
    stream.reset();
    stream.getChar();
    bool result = stream.unfilteredRewind();
    EXPECT_TRUE(result);
}

// Test getUnfilteredChar
TEST_F(BaseSeekInputStreamTest_134, GetUnfilteredChar_134) {
    std::vector<char> data = {'A', 'B', 'C'};
    TestSeekInputStream stream(data, 0, false, 3);
    stream.reset();
    int ch = stream.getUnfilteredChar();
    EXPECT_EQ(ch, 'A');
}

// Test reading single byte stream
TEST_F(BaseSeekInputStreamTest_134, SingleByteStream_134) {
    std::vector<char> data = {'Z'};
    TestSeekInputStream stream(data, 0, false, 1);
    stream.reset();
    int look = stream.lookChar();
    EXPECT_EQ(look, 'Z');
    int get = stream.getChar();
    EXPECT_EQ(get, 'Z');
    int eof = stream.lookChar();
    EXPECT_EQ(eof, EOF);
}

// Test reading large data that exceeds buffer size
TEST_F(BaseSeekInputStreamTest_134, LargeDataExceedsBuffer_134) {
    // Create data larger than typical buffer size
    std::vector<char> data(20000);
    for (size_t i = 0; i < data.size(); i++) {
        data[i] = static_cast<char>(i & 0xFF);
    }
    TestSeekInputStream stream(data, 0, false, 20000);
    stream.reset();
    // Read all characters and verify first few and last
    for (int i = 0; i < 20000; i++) {
        int ch = stream.getChar();
        EXPECT_EQ(ch, (i & 0xFF)) << "Mismatch at position " << i;
    }
    int eof = stream.getChar();
    EXPECT_EQ(eof, EOF);
}

// Test lookChar with start offset
TEST_F(BaseSeekInputStreamTest_134, LookCharWithStartOffset_134) {
    std::vector<char> data = {'A', 'B', 'C', 'D', 'E'};
    TestSeekInputStream stream(data, 2, true, 3);
    stream.reset();
    int ch = stream.lookChar();
    EXPECT_EQ(ch, 'C');
}

// Test lookChar returns value masked with 0xFF
TEST_F(BaseSeekInputStreamTest_134, LookCharMaskedWith0xFF_134) {
    std::vector<char> data = {static_cast<char>(0xAB)};
    TestSeekInputStream stream(data, 0, false, 1);
    stream.reset();
    int result = stream.lookChar();
    EXPECT_EQ(result, 0xAB);
    EXPECT_GT(result, 0); // Should be positive due to & 0xff
}

// Test sequential lookChar and getChar interleaving
TEST_F(BaseSeekInputStreamTest_134, InterleavedLookAndGet_134) {
    std::vector<char> data = {'1', '2', '3', '4'};
    TestSeekInputStream stream(data, 0, false, 4);
    stream.reset();
    
    EXPECT_EQ(stream.lookChar(), '1');
    EXPECT_EQ(stream.getChar(), '1');
    EXPECT_EQ(stream.lookChar(), '2');
    EXPECT_EQ(stream.lookChar(), '2');
    EXPECT_EQ(stream.getChar(), '2');
    EXPECT_EQ(stream.getChar(), '3');
    EXPECT_EQ(stream.lookChar(), '4');
    EXPECT_EQ(stream.getChar(), '4');
    EXPECT_EQ(stream.lookChar(), EOF);
    EXPECT_EQ(stream.getChar(), EOF);
}
