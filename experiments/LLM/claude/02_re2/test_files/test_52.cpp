#include <gtest/gtest.h>
#include <pybind11/pybind11.h>
#include <pybind11/buffer_info.h>
#include <string>
#include <vector>

namespace py = pybind11;

// Forward declaration of the function under test
namespace re2_python {
ssize_t BytesToCharLen(py::buffer buffer, ssize_t pos, ssize_t endpos);
}

// Helper to create a py::bytes object from a std::string
// We need a Python interpreter to use pybind11 objects
class BytesToCharLenTest_52 : public ::testing::Test {
protected:
    static void SetUpTestSuite() {
        // Initialize Python interpreter if not already initialized
        if (!Py_IsInitialized()) {
            py::initialize_interpreter();
        }
    }

    static void TearDownTestSuite() {
        // Don't finalize - let it live for the whole test run
    }
};

TEST_F(BytesToCharLenTest_52, EmptyBuffer_52) {
    py::bytes data("");
    ssize_t result = re2_python::BytesToCharLen(data, 0, 0);
    EXPECT_EQ(result, 0);
}

TEST_F(BytesToCharLenTest_52, SingleAsciiChar_52) {
    py::bytes data("a");
    ssize_t result = re2_python::BytesToCharLen(data, 0, 1);
    EXPECT_EQ(result, 1);
}

TEST_F(BytesToCharLenTest_52, MultipleAsciiChars_52) {
    py::bytes data("hello");
    ssize_t result = re2_python::BytesToCharLen(data, 0, 5);
    EXPECT_EQ(result, 5);
}

TEST_F(BytesToCharLenTest_52, AsciiSubstring_52) {
    py::bytes data("hello");
    ssize_t result = re2_python::BytesToCharLen(data, 1, 4);
    EXPECT_EQ(result, 3);
}

TEST_F(BytesToCharLenTest_52, PosEqualsEndpos_52) {
    py::bytes data("hello");
    ssize_t result = re2_python::BytesToCharLen(data, 2, 2);
    EXPECT_EQ(result, 0);
}

TEST_F(BytesToCharLenTest_52, TwoByteUtf8Char_52) {
    // "é" is 0xC3 0xA9 in UTF-8 (2 bytes)
    std::string s = "\xC3\xA9";
    py::bytes data(s);
    ssize_t result = re2_python::BytesToCharLen(data, 0, 2);
    EXPECT_EQ(result, 1);
}

TEST_F(BytesToCharLenTest_52, ThreeByteUtf8Char_52) {
    // "€" is 0xE2 0x82 0xAC in UTF-8 (3 bytes)
    std::string s = "\xE2\x82\xAC";
    py::bytes data(s);
    ssize_t result = re2_python::BytesToCharLen(data, 0, 3);
    EXPECT_EQ(result, 1);
}

TEST_F(BytesToCharLenTest_52, FourByteUtf8Char_52) {
    // U+1F600 (😀) is 0xF0 0x9F 0x98 0x80 in UTF-8 (4 bytes)
    std::string s = "\xF0\x9F\x98\x80";
    py::bytes data(s);
    ssize_t result = re2_python::BytesToCharLen(data, 0, 4);
    EXPECT_EQ(result, 1);
}

TEST_F(BytesToCharLenTest_52, MixedAsciiAndMultibyte_52) {
    // "aé€" = 'a' (1 byte) + 'é' (2 bytes) + '€' (3 bytes) = 6 bytes, 3 chars
    std::string s = "a\xC3\xA9\xE2\x82\xAC";
    py::bytes data(s);
    ssize_t result = re2_python::BytesToCharLen(data, 0, 6);
    EXPECT_EQ(result, 3);
}

TEST_F(BytesToCharLenTest_52, SubstringOfMultibyte_52) {
    // "aé€" = 'a' (1 byte) + 'é' (2 bytes) + '€' (3 bytes) = 6 bytes
    // pos=1, endpos=3 => covers the 'é' character (bytes 1-2)
    std::string s = "a\xC3\xA9\xE2\x82\xAC";
    py::bytes data(s);
    ssize_t result = re2_python::BytesToCharLen(data, 1, 3);
    EXPECT_EQ(result, 1);
}

TEST_F(BytesToCharLenTest_52, MultipleMultibyteChars_52) {
    // Two 2-byte chars: "éè" = \xC3\xA9\xC3\xA8 (4 bytes, 2 chars)
    std::string s = "\xC3\xA9\xC3\xA8";
    py::bytes data(s);
    ssize_t result = re2_python::BytesToCharLen(data, 0, 4);
    EXPECT_EQ(result, 2);
}

TEST_F(BytesToCharLenTest_52, StartFromMiddleOfBuffer_52) {
    py::bytes data("abcde");
    ssize_t result = re2_python::BytesToCharLen(data, 3, 5);
    EXPECT_EQ(result, 2);
}

TEST_F(BytesToCharLenTest_52, SingleByteRange_52) {
    py::bytes data("abcde");
    ssize_t result = re2_python::BytesToCharLen(data, 2, 3);
    EXPECT_EQ(result, 1);
}

TEST_F(BytesToCharLenTest_52, FullAsciiRange_52) {
    std::string s(256, 'x');
    py::bytes data(s);
    ssize_t result = re2_python::BytesToCharLen(data, 0, 256);
    EXPECT_EQ(result, 256);
}
