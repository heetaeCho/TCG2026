// File: ./TestProjects/re2/python/_re2_quote_meta_shim_test.cc

#include <gtest/gtest.h>
#include <pybind11/embed.h>   // py::scoped_interpreter
#include <pybind11/pytypes.h> // py::bytes, py::bytearray, py::str, py::cast
#include "re2/re2.h"

// Target under test
// ./TestProjects/re2/python/_re2.cc declares it in namespace re2_python
namespace re2_python {
  pybind11::bytes RE2QuoteMetaShim(pybind11::buffer buffer);
}

namespace py = pybind11;

class RE2QuoteMetaShimTest_60 : public ::testing::Test {
protected:
  // Keep the interpreter alive across all tests in this suite.
  static std::unique_ptr<py::scoped_interpreter> guard_;

  static void SetUpTestSuite() {
    // Start the Python interpreter exactly once for all tests here.
    guard_ = std::make_unique<py::scoped_interpreter>();
  }
  static void TearDownTestSuite() { guard_.reset(); }

  static std::string ToStdString(const py::bytes& b) {
    return py::cast<std::string>(b);
  }
};

std::unique_ptr<py::scoped_interpreter> RE2QuoteMetaShimTest_60::guard_;

// --- Tests ---

// Normal operation: plain ASCII with regex metacharacters.
TEST_F(RE2QuoteMetaShimTest_60, BasicBytesEscaping_60) {
  const std::string input = "a.b+c?^$()[]{}|\\";
  const std::string expected = re2::RE2::QuoteMeta(input);

  py::bytes py_in(input);
  py::bytes py_out = re2_python::RE2QuoteMetaShim(py_in);

  EXPECT_EQ(ToStdString(py_out), expected);
}

// Boundary: empty input should round-trip to empty output.
TEST_F(RE2QuoteMetaShimTest_60, EmptyInput_60) {
  const std::string input;
  const std::string expected = re2::RE2::QuoteMeta(input);

  py::bytes py_in(input);
  py::bytes py_out = re2_python::RE2QuoteMetaShim(py_in);

  EXPECT_EQ(ToStdString(py_out), expected);
  EXPECT_TRUE(ToStdString(py_out).empty());
}

// Unicode/UTF-8 input (still passed as bytes). Ensures shim handles UTF-8 bytes.
TEST_F(RE2QuoteMetaShimTest_60, Utf8BytesInput_60) {
  // Contains non-ASCII plus meta chars that should be quoted.
  const std::string input = u8"café(가격)+👍";
  const std::string expected = re2::RE2::QuoteMeta(input);

  py::bytes py_in(input);
  py::bytes py_out = re2_python::RE2QuoteMetaShim(py_in);

  EXPECT_EQ(ToStdString(py_out), expected);
}

// Accepts any buffer-protocol object: bytearray.
TEST_F(RE2QuoteMetaShimTest_60, ByteArrayInput_60) {
  const std::string input = "foo(bar)?";
  const std::string expected = re2::RE2::QuoteMeta(input);

  py::bytearray py_in(input);  // also supports buffer protocol
  py::bytes py_out = re2_python::RE2QuoteMetaShim(py_in);

  EXPECT_EQ(ToStdString(py_out), expected);
}

// Stress common regex sequence with backslashes, ensuring no crashes and correct delegation.
TEST_F(RE2QuoteMetaShimTest_60, BackslashesAndSeq_60) {
  const std::string input = R"(\d+\w?\s*[A-Z]{2,5})";
  const std::string expected = re2::RE2::QuoteMeta(input);

  py::bytes py_in(input);
  py::bytes py_out = re2_python::RE2QuoteMetaShim(py_in);

  EXPECT_EQ(ToStdString(py_out), expected);
}

// Error/exceptional case: passing a non-buffer object (e.g., Python str) should raise.
TEST_F(RE2QuoteMetaShimTest_60, NonBufferRaises_60) {
  // py::str does NOT provide the buffer protocol; constructing py::buffer from it will error.
  // The function expects a buffer; pybind11 will throw py::error_already_set.
  EXPECT_THROW(
      {
        py::str not_buffer("abc");
        // Call with a non-buffer object: should result in a Python TypeError propagated as error_already_set.
        (void)re2_python::RE2QuoteMetaShim(not_buffer);
      },
      py::error_already_set);
}
