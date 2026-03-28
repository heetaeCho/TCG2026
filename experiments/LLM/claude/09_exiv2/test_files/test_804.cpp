#include <gtest/gtest.h>
#include <string>
#include <cstring>

// Minimal type definitions to match Exiv2 conventions
namespace Exiv2 {

using byte = unsigned char;

enum ByteOrder {
    invalidByteOrder,
    littleEndian,
    bigEndian
};

class StringValueBase {
public:
    int read(const byte* buf, size_t len, ByteOrder /*byteOrder*/) {
        if (buf)
            value_ = std::string(reinterpret_cast<const char*>(buf), len);
        return 0;
    }

    // Expose value_ for testing purposes (assumed accessible in the actual codebase)
    std::string value_;
};

} // namespace Exiv2

using namespace Exiv2;

class StringValueBaseTest_804 : public ::testing::Test {
protected:
    StringValueBase svb;
};

// Test that reading a normal ASCII string works correctly
TEST_F(StringValueBaseTest_804, ReadNormalString_804) {
    const std::string input = "Hello, World!";
    const byte* buf = reinterpret_cast<const byte*>(input.c_str());
    int result = svb.read(buf, input.size(), littleEndian);
    EXPECT_EQ(result, 0);
    EXPECT_EQ(svb.value_, "Hello, World!");
}

// Test that reading with zero length produces an empty string
TEST_F(StringValueBaseTest_804, ReadZeroLength_804) {
    const std::string input = "Hello";
    const byte* buf = reinterpret_cast<const byte*>(input.c_str());
    int result = svb.read(buf, 0, littleEndian);
    EXPECT_EQ(result, 0);
    EXPECT_EQ(svb.value_, "");
}

// Test that reading with a null buffer does not modify value_
TEST_F(StringValueBaseTest_804, ReadNullBuffer_804) {
    svb.value_ = "pre-existing";
    int result = svb.read(nullptr, 10, bigEndian);
    EXPECT_EQ(result, 0);
    // When buf is null, value_ should remain unchanged
    EXPECT_EQ(svb.value_, "pre-existing");
}

// Test that reading replaces the previous value
TEST_F(StringValueBaseTest_804, ReadReplacesExistingValue_804) {
    const std::string first = "First";
    const byte* buf1 = reinterpret_cast<const byte*>(first.c_str());
    svb.read(buf1, first.size(), littleEndian);
    EXPECT_EQ(svb.value_, "First");

    const std::string second = "Second";
    const byte* buf2 = reinterpret_cast<const byte*>(second.c_str());
    int result = svb.read(buf2, second.size(), bigEndian);
    EXPECT_EQ(result, 0);
    EXPECT_EQ(svb.value_, "Second");
}

// Test that reading a single character string works
TEST_F(StringValueBaseTest_804, ReadSingleCharacter_804) {
    const byte buf[] = {'X'};
    int result = svb.read(buf, 1, littleEndian);
    EXPECT_EQ(result, 0);
    EXPECT_EQ(svb.value_, "X");
}

// Test that reading binary data with embedded null bytes preserves them
TEST_F(StringValueBaseTest_804, ReadBinaryDataWithNullBytes_804) {
    const byte buf[] = {'A', 0, 'B', 0, 'C'};
    int result = svb.read(buf, 5, littleEndian);
    EXPECT_EQ(result, 0);
    EXPECT_EQ(svb.value_.size(), 5u);
    EXPECT_EQ(svb.value_[0], 'A');
    EXPECT_EQ(svb.value_[1], '\0');
    EXPECT_EQ(svb.value_[2], 'B');
    EXPECT_EQ(svb.value_[3], '\0');
    EXPECT_EQ(svb.value_[4], 'C');
}

// Test that byte order parameter doesn't affect the result (it's ignored)
TEST_F(StringValueBaseTest_804, ByteOrderDoesNotAffectResult_804) {
    const std::string input = "TestData";
    const byte* buf = reinterpret_cast<const byte*>(input.c_str());

    StringValueBase svb1, svb2, svb3;
    svb1.read(buf, input.size(), littleEndian);
    svb2.read(buf, input.size(), bigEndian);
    svb3.read(buf, input.size(), invalidByteOrder);

    EXPECT_EQ(svb1.value_, svb2.value_);
    EXPECT_EQ(svb2.value_, svb3.value_);
    EXPECT_EQ(svb1.value_, "TestData");
}

// Test that return value is always 0
TEST_F(StringValueBaseTest_804, AlwaysReturnsZero_804) {
    const std::string input = "test";
    const byte* buf = reinterpret_cast<const byte*>(input.c_str());

    EXPECT_EQ(svb.read(buf, input.size(), littleEndian), 0);
    EXPECT_EQ(svb.read(nullptr, 0, bigEndian), 0);
    EXPECT_EQ(svb.read(buf, 0, invalidByteOrder), 0);
}

// Test reading a partial length from the buffer
TEST_F(StringValueBaseTest_804, ReadPartialLength_804) {
    const std::string input = "Hello, World!";
    const byte* buf = reinterpret_cast<const byte*>(input.c_str());
    int result = svb.read(buf, 5, littleEndian);
    EXPECT_EQ(result, 0);
    EXPECT_EQ(svb.value_, "Hello");
}

// Test reading a large buffer
TEST_F(StringValueBaseTest_804, ReadLargeBuffer_804) {
    std::string large(10000, 'A');
    const byte* buf = reinterpret_cast<const byte*>(large.c_str());
    int result = svb.read(buf, large.size(), littleEndian);
    EXPECT_EQ(result, 0);
    EXPECT_EQ(svb.value_.size(), 10000u);
    EXPECT_EQ(svb.value_, large);
}

// Test reading all byte values (0-255)
TEST_F(StringValueBaseTest_804, ReadAllByteValues_804) {
    byte buf[256];
    for (int i = 0; i < 256; ++i) {
        buf[i] = static_cast<byte>(i);
    }
    int result = svb.read(buf, 256, littleEndian);
    EXPECT_EQ(result, 0);
    EXPECT_EQ(svb.value_.size(), 256u);
    for (int i = 0; i < 256; ++i) {
        EXPECT_EQ(static_cast<byte>(svb.value_[i]), static_cast<byte>(i));
    }
}

// Test that null buffer with zero length still returns 0 and doesn't crash
TEST_F(StringValueBaseTest_804, NullBufferZeroLength_804) {
    svb.value_ = "original";
    int result = svb.read(nullptr, 0, littleEndian);
    EXPECT_EQ(result, 0);
    EXPECT_EQ(svb.value_, "original");
}
