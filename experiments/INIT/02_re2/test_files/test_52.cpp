// File: bytes_to_char_len_test_52.cc
#include <gtest/gtest.h>
#include <pybind11/embed.h>
#include <pybind11/pytypes.h>

namespace py = pybind11;

// Forward declaration to avoid relying on private headers.
// Linker will resolve against the production object/library.
namespace re2_python {
  ssize_t BytesToCharLen(py::buffer buffer, ssize_t pos, ssize_t endpos);
}

class BytesToCharLenTest_52 : public ::testing::Test {
protected:
  // Initialize the Python interpreter once for all tests in this suite.
  static void SetUpTestSuite() {
    guard_ = new py::scoped_interpreter();
  }
  static void TearDownTestSuite() {
    delete guard_;
    guard_ = nullptr;
  }

  // Helper to create a py::buffer from a std::string.
  static py::buffer AsBuffer(const std::string& s) {
    // Python 'bytes' implements the buffer protocol; py::buffer can wrap it.
    py::bytes pyb(s);
    py::buffer buf(pyb);
    return buf;
  }

  static py::scoped_interpreter* guard_;
};

py::scoped_interpreter* BytesToCharLenTest_52::guard_ = nullptr;

// --- Tests ---

// Empty slice should yield 0 regardless of content.
TEST_F(BytesToCharLenTest_52, ReturnsZeroForEmptyRange_52) {
  const std::string s = "hello";
  auto buf = AsBuffer(s);
  EXPECT_EQ(re2_python::BytesToCharLen(buf, /*pos=*/0, /*endpos=*/0), 0);
  EXPECT_EQ(re2_python::BytesToCharLen(buf, /*pos=*/3, /*endpos=*/3), 0);
}

// Pure ASCII: each byte is one character (observable: length equals bytes in range).
TEST_F(BytesToCharLenTest_52, CountsAsciiBytesAsChars_52) {
  const std::string s = "abcdef";
  auto buf = AsBuffer(s);
  EXPECT_EQ(re2_python::BytesToCharLen(buf, 0, static_cast<ssize_t>(s.size())), 6);
  EXPECT_EQ(re2_python::BytesToCharLen(buf, 1, 4), 3); // "bcd"
}

// Subrange at boundaries in ASCII input.
TEST_F(BytesToCharLenTest_52, CountsSliceAscii_52) {
  const std::string s = "XYZ";
  auto buf = AsBuffer(s);
  EXPECT_EQ(re2_python::BytesToCharLen(buf, 0, 1), 1); // "X"
  EXPECT_EQ(re2_python::BytesToCharLen(buf, 2, 3), 1); // "Z"
}

// UTF-8 Korean (each code point is multiple bytes). Expect code-point count.
TEST_F(BytesToCharLenTest_52, CountsUtf8Korean_52) {
  // "안녕" -> 2 Unicode characters; in UTF-8 typically 3 bytes each (total 6 bytes).
  const std::string s = u8"안녕";
  ASSERT_EQ(s.size(), 6u) << "Test assumes typical UTF-8 byte length for '안녕'.";
  auto buf = AsBuffer(s);

  // Whole buffer: expect 2 characters.
  EXPECT_EQ(re2_python::BytesToCharLen(buf, 0, static_cast<ssize_t>(s.size())), 2);

  // First character only (first 3 bytes).
  EXPECT_EQ(re2_python::BytesToCharLen(buf, 0, 3), 1);

  // Second character only (last 3 bytes).
  EXPECT_EQ(re2_python::BytesToCharLen(buf, 3, 6), 1);
}

// Emoji (4-byte UTF-8 code point) is counted as one character.
TEST_F(BytesToCharLenTest_52, CountsEmojiAsSingleChar_52) {
  const std::string s = u8"😀"; // U+1F600, typically 4 bytes in UTF-8
  ASSERT_EQ(s.size(), 4u) << "Test assumes typical UTF-8 byte length for '😀'.";
  auto buf = AsBuffer(s);
  EXPECT_EQ(re2_python::BytesToCharLen(buf, 0, 4), 1);
}

// Mixed ASCII + UTF-8: verify counting across different byte widths.
TEST_F(BytesToCharLenTest_52, MixedAsciiAndUtf8_52) {
  const std::string s = std::string("A") + u8"😀" + "B"; // bytes: 1 + 4 + 1 = 6
  ASSERT_EQ(s.size(), 6u);
  auto buf = AsBuffer(s);

  // Whole buffer: 3 code points.
  EXPECT_EQ(re2_python::BytesToCharLen(buf, 0, 6), 3);

  // Middle slice over the emoji only.
  EXPECT_EQ(re2_python::BytesToCharLen(buf, 1, 5), 1);

  // Slices over ASCII ends.
  EXPECT_EQ(re2_python::BytesToCharLen(buf, 0, 1), 1); // "A"
  EXPECT_EQ(re2_python::BytesToCharLen(buf, 5, 6), 1); // "B"
}

// Start==end at buffer end: still zero.
TEST_F(BytesToCharLenTest_52, StartEqualsEndAtBufferEnd_52) {
  const std::string s = u8"가나"; // 2 code points
  auto buf = AsBuffer(s);
  const ssize_t n = static_cast<ssize_t>(s.size());
  EXPECT_EQ(re2_python::BytesToCharLen(buf, n, n), 0);
}

// Full-buffer sanity across multi-language string.
TEST_F(BytesToCharLenTest_52, WholeBuffer_52) {
  const std::string s = std::string("Hi") + u8"안녕" + u8"😀";
  // "Hi" (2) + "안녕" (2) + "😀" (1) => 5 code points
  auto buf = AsBuffer(s);
  EXPECT_EQ(re2_python::BytesToCharLen(buf, 0, static_cast<ssize_t>(s.size())), 5);
}
