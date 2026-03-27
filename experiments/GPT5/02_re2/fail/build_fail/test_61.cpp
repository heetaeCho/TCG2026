// File: set_add_test_61.cc
#include <gtest/gtest.h>
#include <re2/re2.h>
#include <pybind11/embed.h>   // for py::scoped_interpreter
#include <pybind11/pybind11.h>
#include <pybind11/pytypes.h>

namespace py = pybind11;

// Forward-declare the class under test as provided
namespace re2_python {
class Set {
 public:
  Set(RE2::Anchor anchor, const RE2::Options& options);
  Set(const Set&) = delete;
  ~Set() = default;
  Set& operator=(const Set&) = delete;

  int Add(py::buffer buffer);
  bool Compile();
  std::vector<int> Match(py::buffer buffer) const;
};
}  // namespace re2_python

class SetAddTest_61 : public ::testing::Test {
 protected:
  // Initialize the Python interpreter once for all tests.
  static void SetUpTestSuite() {
    interpreter_ = new py::scoped_interpreter{};
  }
  static void TearDownTestSuite() {
    delete interpreter_;
    interpreter_ = nullptr;
  }

  // Fresh Set for each test (black-box use only).
  void SetUp() override {
    RE2::Options opts;
    set_ = std::make_unique<re2_python::Set>(RE2::UNANCHORED, opts);
  }

  std::unique_ptr<re2_python::Set> set_;
  static py::scoped_interpreter* interpreter_;
};

py::scoped_interpreter* SetAddTest_61::interpreter_ = nullptr;

// Normal case: adding valid patterns returns non-negative, increasing indices.
TEST_F(SetAddTest_61, AddValidPatterns_ReturnIncrementingIndices_61) {
  py::bytes p1("foo");
  py::bytes p2("bar");
  int i1 = set_->Add(p1);
  int i2 = set_->Add(p2);

  EXPECT_GE(i1, 0);
  EXPECT_GE(i2, 0);
  // For RE2::Set, indices should be assigned in insertion order.
  EXPECT_LT(i1, i2);
}

// Boundary: empty pattern ("") is a valid regex that matches the empty string.
// Expect a non-negative index.
TEST_F(SetAddTest_61, AddEmptyPattern_ReturnsNonNegativeIndex_61) {
  py::bytes empty_pattern("");
  int idx = set_->Add(empty_pattern);
  EXPECT_GE(idx, 0);
}

// Error case: syntactically invalid regex should cause RE2::Set::Add to fail (-1).
TEST_F(SetAddTest_61, AddInvalidRegex_ReturnsMinusOne_61) {
  // Unbalanced parenthesis is a classic invalid regex.
  py::bytes invalid("(");
  int idx = set_->Add(invalid);
  EXPECT_EQ(idx, -1);
}

// Boundary/compat: accept any buffer-protocol object (bytearray).
// Expect non-negative index for a valid pattern in bytearray.
TEST_F(SetAddTest_61, AddFromByteArray_BufferProtocolAccepted_61) {
  py::object bytearray_obj = py::bytearray("ab.*cd", 6);
  // py::bytearray satisfies the buffer protocol; Add should accept it.
  int idx = set_->Add(bytearray_obj);
  EXPECT_GE(idx, 0);
}

// Unicode pattern in bytes (UTF-8). As long as it’s a valid regex string,
// Add should return a non-negative index.
TEST_F(SetAddTest_61, AddUnicodeUTF8Pattern_ReturnsNonNegativeIndex_61) {
  // Pattern uses a Unicode literal (e.g., Korean characters) alongside regex meta.
  // Using a simple literal to avoid depending on locale/escapes.
  const char* utf8_pat = u8"헬로(월드)?";
  py::bytes p(utf8_pat);
  int idx = set_->Add(p);
  EXPECT_GE(idx, 0);
}
