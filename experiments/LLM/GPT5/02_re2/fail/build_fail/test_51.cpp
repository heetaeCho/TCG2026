// File: char_len_to_bytes_test_51.cc

#include <gtest/gtest.h>
#include <pybind11/embed.h>
#include <pybind11/pybind11.h>

namespace py = pybind11;

// Forward declaration of the function under test.
// We only rely on its signature (black-box).
namespace re2_python {
  ssize_t CharLenToBytes(py::buffer buffer, ssize_t pos, ssize_t len);
}

// Test fixture: own a Python interpreter for py::buffer creation.
class CharLenToBytesTest_51 : public ::testing::Test {
protected:
  static void SetUpTestSuite() {
    // Start Python once for the entire suite.
    guard_ = new py::scoped_interpreter{};
  }
  static void TearDownTestSuite() {
    delete guard_;
    guard_ = nullptr;
  }

  // Utility: make a py::buffer from raw bytes.
  static py::buffer MakeBuffer(const std::string& bytes) {
    py::bytes pyb(bytes);
    return py::buffer(pyb);
  }

private:
  static py::scoped_interpreter* guard_;
};

py::scoped_interpreter* CharLenToBytesTest_51::guard_ = nullptr;

// ---------- Tests ----------

// Normal operation: ASCII text, count exactly 'len' characters from start.
TEST_F(CharLenToBytesTest_51, ReturnsBytesForExactAsciiLen_51) {
  const std::string s = "hello world"; // 11 bytes, all ASCII
  auto buf = MakeBuffer(s);

  // Ask for 5 characters from pos=0 -> expect 5 bytes.
  ssize_t bytes = re2_python::CharLenToBytes(buf, /*pos=*/0, /*len=*/5);
  EXPECT_EQ(bytes, 5);
}

// Boundary: len exceeds remaining characters -> must stop at end.
TEST_F(CharLenToBytesTest_51, StopsAtEndWhenLenTooLarge_51) {
  const std::string s = "abcde"; // 5 bytes, all ASCII
  auto buf = MakeBuffer(s);

  // From pos=0, ask for 10 characters -> should only advance 5 bytes.
  ssize_t bytes = re2_python::CharLenToBytes(buf, /*pos=*/0, /*len=*/10);
  EXPECT_EQ(bytes, 5);
}

// Boundary: starting from a non-zero position, still should not go past end.
TEST_F(CharLenToBytesTest_51, RespectsEndFromMiddlePosition_51) {
  const std::string s = "abcdef"; // 6 bytes
  auto buf = MakeBuffer(s);

  // From pos=2 ("cdef"), ask for 10 chars -> only 4 bytes remain.
  ssize_t bytes = re2_python::CharLenToBytes(buf, /*pos=*/2, /*len=*/10);
  EXPECT_EQ(bytes, 4);
}

// Edge: len == 0 should advance 0 bytes regardless of pos.
TEST_F(CharLenToBytesTest_51, ZeroLenAdvancesZeroBytes_51) {
  const std::string s = "sample";
  auto buf = MakeBuffer(s);

  ssize_t bytes = re2_python::CharLenToBytes(buf, /*pos=*/3, /*len=*/0);
  EXPECT_EQ(bytes, 0);
}

// Boundary: pos at end (== size) should immediately return 0.
TEST_F(CharLenToBytesTest_51, PositionAtEndReturnsZero_51) {
  const std::string s = "xyz";
  auto buf = MakeBuffer(s);

  // pos == size is a valid, empty range.
  ssize_t bytes = re2_python::CharLenToBytes(buf, /*pos=*/static_cast<ssize_t>(s.size()), /*len=*/3);
  EXPECT_EQ(bytes, 0);
}

// Sanity: small consecutive calls with varying pos/len behave consistently.
TEST_F(CharLenToBytesTest_51, ConsecutiveQueriesConsistent_51) {
  const std::string s = "abcdefghij"; // 10 bytes
  auto buf = MakeBuffer(s);

  // First 3 chars from start -> 3 bytes.
  EXPECT_EQ(re2_python::CharLenToBytes(buf, 0, 3), 3);

  // Next 4 chars from pos=3 -> 4 bytes.
  EXPECT_EQ(re2_python::CharLenToBytes(buf, 3, 4), 4);

  // From pos=7, ask for 10 -> only 3 bytes remain.
  EXPECT_EQ(re2_python::CharLenToBytes(buf, 7, 10), 3);
}
