// File: ./TestProjects/tests/re2_python_RE2PossibleMatchRangeShim_test.cc

#include <gtest/gtest.h>
#include <memory>

#include "re2/re2.h"

// pybind11
#include <pybind11/pybind11.h>
#include <pybind11/embed.h>   // for scoped_interpreter
#include <pybind11/pytypes.h> // for py::bytes

// SUT header (shim lives in _re2.cc; declare here to use in tests)
namespace re2_python {
  // Declaration matching the provided partial code
  std::tuple<bool, pybind11::bytes, pybind11::bytes>
  RE2PossibleMatchRangeShim(const re2::RE2& self, int maxlen);
}

namespace py = pybind11;
using re2::RE2;

class RE2PossibleMatchRangeShimTest_58 : public ::testing::Test {
protected:
  // Hold a Python interpreter for all tests (needed for py::bytes)
  static std::unique_ptr<py::scoped_interpreter> guard_;

  static void SetUpTestSuite() {
    guard_ = std::make_unique<py::scoped_interpreter>();
  }
  static void TearDownTestSuite() {
    guard_.reset();
  }

  // Helper: assert that shim mirrors RE2::PossibleMatchRange for given (pattern,maxlen)
  static void ExpectShimMirrorsRE2(const std::string& pattern, int maxlen) {
    RE2 re(pattern);

    std::string expected_min, expected_max;
    bool expected_ok = re.PossibleMatchRange(&expected_min, &expected_max, maxlen);

    auto [ok, py_min, py_max] = re2_python::RE2PossibleMatchRangeShim(re, maxlen);

    // Compare the boolean first
    EXPECT_EQ(ok, expected_ok);

    // Convert py::bytes -> std::string for comparison
    std::string got_min = static_cast<std::string>(py_min);
    std::string got_max = static_cast<std::string>(py_max);

    EXPECT_EQ(got_min, expected_min);
    EXPECT_EQ(got_max, expected_max);

    // Also ensure outputs respect maxlen bound (observable via returned strings)
    EXPECT_LE(got_min.size(), static_cast<size_t>(std::max(0, maxlen)));
    EXPECT_LE(got_max.size(), static_cast<size_t>(std::max(0, maxlen)));
  }
};

std::unique_ptr<py::scoped_interpreter> RE2PossibleMatchRangeShimTest_58::guard_;

// ---- Tests ----

TEST_F(RE2PossibleMatchRangeShimTest_58, LiteralPattern_ReturnsSameAsRE2_58) {
  // A simple literal is a safe black-box case; we only assert equality with RE2.
  ExpectShimMirrorsRE2("abc", /*maxlen=*/16);
}

TEST_F(RE2PossibleMatchRangeShimTest_58, CharacterClass_DelegatesExactly_58) {
  // Character class; again, no assumptions beyond equal-to-RE2.
  ExpectShimMirrorsRE2("[a-c]", /*maxlen=*/8);
}

TEST_F(RE2PossibleMatchRangeShimTest_58, MaxLen_IsRespectedAndForwarded_58) {
  // Same pattern, two different maxlen values to confirm the shim forwards maxlen.
  // First call (shorter maxlen)
  ExpectShimMirrorsRE2("abcdef", /*maxlen=*/3);
  // Second call (longer maxlen)
  ExpectShimMirrorsRE2("abcdef", /*maxlen=*/10);
}

TEST_F(RE2PossibleMatchRangeShimTest_58, AnchoredPattern_BooleanAndRangeMatchRE2_58) {
  // Many anchored patterns cause RE2::PossibleMatchRange to return false.
  // We don't assume that — we compare the shim output to RE2’s public API.
  ExpectShimMirrorsRE2("^abc$", /*maxlen=*/10);
}

TEST_F(RE2PossibleMatchRangeShimTest_58, UTF8Pattern_MirrorsRE2WithBytes_58) {
  // Multibyte UTF-8; ensure the shim’s py::bytes round-trips identical to RE2 output.
  ExpectShimMirrorsRE2(u8"한글", /*maxlen=*/10);
}

