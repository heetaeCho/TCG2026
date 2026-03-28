#include <gtest/gtest.h>
#include <pybind11/pybind11.h>
#include <pybind11/embed.h>

namespace py = pybind11;

namespace re2_python {
ssize_t CharLenToBytes(py::buffer buffer, ssize_t pos, ssize_t len);
}

class CharLenToBytesTest_51 : public ::testing::Test {
protected:
    static void SetUpTestSuite() {
        if (!Py_IsInitialized()) {
            py::initialize_interpreter();
        }
    }

    static void TearDownTestSuite() {
        // Don't finalize - let it clean up naturally
    }

    py::bytes MakeBuffer(const std::string& s) {
        return py::bytes(s);
    }
};

// Test with pure ASCII string, requesting all characters
TEST_F(CharLenToBytesTest_51, AsciiFullString_51) {
    py::bytes buf = MakeBuffer("hello");
    ssize_t result = re2_python::CharLenToBytes(buf, 0, 5);
    EXPECT_EQ(result, 5);
}

// Test with ASCII string, requesting subset of characters
TEST_F(CharLenToBytesTest_51, AsciiSubset_51) {
    py::bytes buf = MakeBuffer("hello");
    ssize_t result = re2_python::CharLenToBytes(buf, 0, 3);
    EXPECT_EQ(result, 3);
}

// Test with zero length returns zero bytes
TEST_F(CharLenToBytesTest_51, ZeroLen_51) {
    py::bytes buf = MakeBuffer("hello");
    ssize_t result = re2_python::CharLenToBytes(buf, 0, 0);
    EXPECT_EQ(result, 0);
}

// Test with pos offset in ASCII
TEST_F(CharLenToBytesTest_51, AsciiWithOffset_51) {
    py::bytes buf = MakeBuffer("hello");
    ssize_t result = re2_python::CharLenToBytes(buf, 2, 2);
    EXPECT_EQ(result, 2);
}

// Test with UTF-8 multi-byte characters (2-byte: e.g., "ñ" = \xc3\xb1)
TEST_F(CharLenToBytesTest_51, Utf8TwoByteChars_51) {
    // "ññ" = \xc3\xb1\xc3\xb1 (4 bytes, 2 characters)
    std::string s = "\xc3\xb1\xc3\xb1";
    py::bytes buf = MakeBuffer(s);
    ssize_t result = re2_python::CharLenToBytes(buf, 0, 2);
    EXPECT_EQ(result, 4);
}

// Test single UTF-8 two-byte character
TEST_F(CharLenToBytesTest_51, Utf8SingleTwoByteChar_51) {
    std::string s = "\xc3\xb1\xc3\xb1";
    py::bytes buf = MakeBuffer(s);
    ssize_t result = re2_python::CharLenToBytes(buf, 0, 1);
    EXPECT_EQ(result, 2);
}

// Test with 3-byte UTF-8 characters (e.g., "あ" = \xe3\x81\x82)
TEST_F(CharLenToBytesTest_51, Utf8ThreeByteChars_51) {
    std::string s = "\xe3\x81\x82\xe3\x81\x84"; // "あい"
    py::bytes buf = MakeBuffer(s);
    ssize_t result = re2_python::CharLenToBytes(buf, 0, 2);
    EXPECT_EQ(result, 6);
}

// Test requesting more characters than available (should stop at end)
TEST_F(CharLenToBytesTest_51, LenExceedsAvailable_51) {
    py::bytes buf = MakeBuffer("hi");
    ssize_t result = re2_python::CharLenToBytes(buf, 0, 100);
    EXPECT_EQ(result, 2);
}

// Test with pos at end of buffer, len > 0
TEST_F(CharLenToBytesTest_51, PosAtEnd_51) {
    py::bytes buf = MakeBuffer("hi");
    ssize_t result = re2_python::CharLenToBytes(buf, 2, 1);
    EXPECT_EQ(result, 0);
}

// Test empty buffer
TEST_F(CharLenToBytesTest_51, EmptyBuffer_51) {
    py::bytes buf = MakeBuffer("");
    ssize_t result = re2_python::CharLenToBytes(buf, 0, 0);
    EXPECT_EQ(result, 0);
}

// Test mixed ASCII and multi-byte with offset
TEST_F(CharLenToBytesTest_51, MixedAsciiAndUtf8WithOffset_51) {
    // "añb" = a(1) + ñ(2) + b(1) = 4 bytes
    std::string s = "a\xc3\xb1" "b";
    py::bytes buf = MakeBuffer(s);
    // Start at pos=1 (byte offset of ñ), read 1 character
    ssize_t result = re2_python::CharLenToBytes(buf, 1, 1);
    EXPECT_EQ(result, 2);
}

// Test 4-byte UTF-8 character (e.g., U+1F600 = \xf0\x9f\x98\x80)
TEST_F(CharLenToBytesTest_51, Utf8FourByteChar_51) {
    std::string s = "\xf0\x9f\x98\x80"; // 😀
    py::bytes buf = MakeBuffer(s);
    ssize_t result = re2_python::CharLenToBytes(buf, 0, 1);
    EXPECT_EQ(result, 4);
}
