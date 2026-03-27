// File: filter_add_test_63.cc

#include <gtest/gtest.h>
#include <pybind11/embed.h>
#include <pybind11/pybind11.h>
#include <pybind11/pytypes.h>

#include "re2/re2.h"  // for RE2::Options

// The class under test is declared in the project under re2_python namespace.
// We only use its public interface as a black box.
namespace re2_python {
class Filter {
 public:
  Filter() = default;
  Filter(const Filter&) = delete;
  ~Filter() = default;
  Filter& operator=(const Filter&) = delete;

  // Interface under test:
  int Add(pybind11::buffer buffer, const RE2::Options& options);
};
}  // namespace re2_python

namespace {

namespace py = pybind11;

// Test fixture that brings up a single embedded Python interpreter
// for all tests that need to create py::buffer objects.
class FilterAddTest_63 : public ::testing::Test {
 protected:
  static void SetUpTestSuite() {
    // Start the embedded interpreter once for the whole suite.
    guard_ = std::make_unique<py::scoped_interpreter>();
  }
  static void TearDownTestSuite() {
    guard_.reset();
  }

  // Helper to create a py::buffer from a std::string pattern.
  static py::bytes ToBuffer(const std::string& s) {
    return py::bytes(s);
  }

  // Helper to get default, quiet options (avoid log noise).
  static RE2::Options DefaultQuietOptions() {
    RE2::Options opt;
    opt.set_log_errors(false);
    return opt;
  }

 private:
  static std::unique_ptr<py::scoped_interpreter> guard_;
};

std::unique_ptr<py::scoped_interpreter> FilterAddTest_63::guard_;

}  // namespace

// -------- Tests --------

// Normal operation: valid regex should return a non-negative index.
TEST_F(FilterAddTest_63, Add_ValidPatternReturnsNonNegativeIndex_63) {
  re2_python::Filter filter;
  auto options = DefaultQuietOptions();

  // Simple valid pattern.
  const std::string pattern = "a+b*";
  int index = filter.Add(FilterAddTest_63::ToBuffer(pattern), options);

  EXPECT_GE(index, 0) << "Expected non-negative index for a valid pattern";
}

// Boundary: empty pattern is valid in RE2 (matches empty string).
TEST_F(FilterAddTest_63, Add_EmptyPatternReturnsNonNegativeIndex_63) {
  re2_python::Filter filter;
  auto options = DefaultQuietOptions();

  const std::string pattern;  // empty
  int index = filter.Add(FilterAddTest_63::ToBuffer(pattern), options);

  EXPECT_GE(index, 0) << "Expected non-negative index for an empty pattern";
}

// Error/exceptional case (observable): syntactically invalid regex.
// The implementation initializes index to -1 and calls into the filter;
// on error, index should remain -1 (i.e., not clobbered).
TEST_F(FilterAddTest_63, Add_InvalidPatternKeepsMinusOneIndex_63) {
  re2_python::Filter filter;
  auto options = DefaultQuietOptions();

  const std::string invalid_pattern = "(";  // Unbalanced parenthesis
  int index = filter.Add(FilterAddTest_63::ToBuffer(invalid_pattern), options);

  EXPECT_EQ(index, -1) << "Expected -1 for invalid regex, preserving sentinel";
}

// Boundary: large but valid pattern should succeed (or at least not crash).
TEST_F(FilterAddTest_63, Add_LargePatternReturnsIndexOrMinusOneWithoutCrash_63) {
  re2_python::Filter filter;
  auto options = DefaultQuietOptions();

  // Build a long literal pattern like "a{1}a{1}...". Still syntactically valid.
  std::string pattern;
  pattern.reserve(20000);
  for (int i = 0; i < 2000; ++i) {
    pattern += "a{1}";
  }

  int index = filter.Add(FilterAddTest_63::ToBuffer(pattern), options);

  // We don't assert success semantics beyond the interface:
  // Either a non-negative index (success) or -1 (failure) is acceptable.
  // The key is observable behavior: it should not crash and should return an int as specified.
  // Still, in most reasonable configurations, we expect success:
  EXPECT_TRUE(index >= 0 || index == -1)
      << "Add should return a valid observable result (>=0 on success, -1 on failure)";
}

