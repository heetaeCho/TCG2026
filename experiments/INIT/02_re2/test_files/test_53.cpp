// File: RE2InitShim_test_53.cc

#include <gtest/gtest.h>
#include "re2/re2.h"

// pybind11
#include <pybind11/embed.h>
#include <pybind11/pytypes.h>
#include <pybind11/pybind11.h>
#include <pybind11/pybuffer.h>

namespace py = pybind11;

// Declaration under test (from _re2.cc)
namespace re2_python {
  std::unique_ptr<RE2> RE2InitShim(py::buffer buffer, const RE2::Options& options);
}

// Test fixture to manage the Python interpreter lifetime safely.
class RE2InitShimTest_53 : public ::testing::Test {
protected:
  // Start/stop the embedded interpreter once per test.
  py::scoped_interpreter guard_;

  // Helper: make a py::buffer from a Python object that supports the buffer protocol.
  static py::buffer AsBuffer(const py::object& o) {
    return py::buffer(o);
  }

  // Convenience: build Options with case sensitivity set as requested.
  static RE2::Options MakeOptions(bool case_sensitive) {
    RE2::Options opt;
    opt.set_case_sensitive(case_sensitive);
    return opt;
  }
};

// ---- Normal operation: bytes pattern + default (case-sensitive) options ----
TEST_F(RE2InitShimTest_53, BytesCaseSensitive_MatchesExact_53) {
  // Arrange
  py::bytes pattern("abc");
  auto buf = AsBuffer(pattern);
  RE2::Options opts = MakeOptions(/*case_sensitive=*/true);

  // Act
  std::unique_ptr<RE2> re = re2_python::RE2InitShim(buf, opts);

  // Assert: object is created and behaves with case sensitivity.
  ASSERT_NE(re, nullptr);
  EXPECT_TRUE(RE2::FullMatch("abc", *re));
  EXPECT_FALSE(RE2::FullMatch("ABC", *re));
}

// ---- Option pass-through: case-insensitive should match uppercase input ----
TEST_F(RE2InitShimTest_53, CaseInsensitiveOption_AppliedToEngine_53) {
  // Arrange
  py::bytes pattern("abc");
  auto buf = AsBuffer(pattern);
  RE2::Options opts = MakeOptions(/*case_sensitive=*/false);

  // Act
  std::unique_ptr<RE2> re = re2_python::RE2InitShim(buf, opts);

  // Assert
  ASSERT_NE(re, nullptr);
  // With case-insensitive option, uppercase input should match.
  EXPECT_TRUE(RE2::FullMatch("ABC", *re));
  // Still should match the original case too.
  EXPECT_TRUE(RE2::FullMatch("abc", *re));
}

// ---- Boundary condition: empty pattern ----
// RE2’s empty pattern typically only full-matches the empty string.
TEST_F(RE2InitShimTest_53, EmptyPattern_OnlyMatchesEmptyString_53) {
  // Arrange
  py::bytes pattern("");
  auto buf = AsBuffer(pattern);
  RE2::Options opts = MakeOptions(/*case_sensitive=*/true);

  // Act
  std::unique_ptr<RE2> re = re2_python::RE2InitShim(buf, opts);

  // Assert
  ASSERT_NE(re, nullptr);
  EXPECT_TRUE(RE2::FullMatch("", *re));
  EXPECT_FALSE(RE2::FullMatch("x", *re));
}

// ---- Normal operation with another buffer provider: bytearray ----
TEST_F(RE2InitShimTest_53, AcceptsAnyBufferProvider_PyByteArray_53) {
  // Arrange: Python bytearray also supports the buffer protocol.
  py::object bytearray_obj = py::reinterpret_steal<py::object>(
      PyByteArray_FromStringAndSize("a.c", 3));  // pattern: "a.c"
  auto buf = AsBuffer(bytearray_obj);
  RE2::Options opts = MakeOptions(/*case_sensitive=*/true);

  // Act
  std::unique_ptr<RE2> re = re2_python::RE2InitShim(buf, opts);

  // Assert
  ASSERT_NE(re, nullptr);
  EXPECT_TRUE(RE2::FullMatch("a_c", *re));  // '.' should match single char
  EXPECT_FALSE(RE2::FullMatch("ac", *re));  // missing middle char
}

// ---- UTF-8 pattern passes through and works (observable via match) ----
TEST_F(RE2InitShimTest_53, UTF8Pattern_MatchesUTF8Text_53) {
  // Arrange: UTF-8 pattern "café" (with accent)
  py::bytes pattern(u8"café");
  auto buf = AsBuffer(pattern);
  RE2::Options opts = MakeOptions(/*case_sensitive=*/true);

  // Act
  std::unique_ptr<RE2> re = re2_python::RE2InitShim(buf, opts);

  // Assert
  ASSERT_NE(re, nullptr);
  EXPECT_TRUE(RE2::FullMatch(u8"café", *re));
  EXPECT_FALSE(RE2::FullMatch(u8"CAFÉ", *re));  // case-sensitive by default
}

// ---- Case-insensitive with UTF-8 pattern ----
TEST_F(RE2InitShimTest_53, UTF8Pattern_CaseInsensitive_53) {
  // Arrange: same UTF-8 pattern but case-insensitive option.
  py::bytes pattern(u8"café");
  auto buf = AsBuffer(pattern);
  RE2::Options opts = MakeOptions(/*case_sensitive=*/false);

  // Act
  std::unique_ptr<RE2> re = re2_python::RE2InitShim(buf, opts);

  // Assert
  ASSERT_NE(re, nullptr);
  // Depending on Unicode case-folding support, 'CAFÉ' should match when case-insensitive.
  // If the engine's behavior differs, this still remains a black-box check via the public API.
  EXPECT_TRUE(RE2::FullMatch(u8"CAFÉ", *re));
}

