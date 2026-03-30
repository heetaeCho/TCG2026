// File: re2_error_shim_test_54.cc

#include <gtest/gtest.h>
#include <string>
#include <vector>

#include <pybind11/embed.h>   // for pybind11::scoped_interpreter
#include <pybind11/pybind11.h>
#include <pybind11/pytypes.h>

#include "re2/re2.h"

namespace py = pybind11;
using re2::RE2;

// Declaration of the shim under test (defined in ./TestProjects/re2/python/_re2.cc)
namespace re2_python {
  py::bytes RE2ErrorShim(const RE2& self);
}

namespace {

class RE2ErrorShimTest_54 : public ::testing::Test {};

// --- Tests ---

// [Normal] Valid simple pattern should have no error; shim returns empty bytes.
TEST_F(RE2ErrorShimTest_54, ValidPattern_EmptyError_54) {
  RE2 re("a+");
  ASSERT_TRUE(re.ok()) << "Precondition: valid pattern should be ok()";
  auto b = re2_python::RE2ErrorShim(re);
  // py::bytes is convertible to std::string
  std::string shim_err = static_cast<std::string>(b);
  EXPECT_TRUE(re.error().empty());
  EXPECT_EQ(shim_err, re.error());
}

// [Boundary] Empty pattern is valid in RE2; expect empty error via shim.
TEST_F(RE2ErrorShimTest_54, EmptyPattern_EmptyError_54) {
  RE2 re("");
  ASSERT_TRUE(re.ok()) << "Precondition: empty pattern is valid in RE2";
  auto b = re2_python::RE2ErrorShim(re);
  std::string shim_err = static_cast<std::string>(b);
  EXPECT_TRUE(re.error().empty());
  EXPECT_EQ(shim_err, re.error());
}

// [Exceptional/Error] Obviously invalid pattern should set a non-empty error;
// shim must propagate exactly the same bytes as RE2::error().
TEST_F(RE2ErrorShimTest_54, InvalidPattern_PropagatesError_54) {
  RE2 re("(");  // unmatched parenthesis -> invalid
  ASSERT_FALSE(re.ok()) << "Precondition: invalid pattern should not be ok()";
  auto b = re2_python::RE2ErrorShim(re);
  std::string shim_err = static_cast<std::string>(b);
  // We do NOT assert a specific error message string (black-box testing),
  // only that the shim exactly mirrors RE2::error().
  EXPECT_EQ(shim_err, re.error());
  EXPECT_FALSE(shim_err.empty()) << "Expect some error message to be present";
}

// [Consistency] The shim should always equal RE2::error() regardless of pattern validity.
TEST_F(RE2ErrorShimTest_54, ShimAlwaysMatchesRE2Error_54) {
  std::vector<std::string> patterns = {
      "abc.*def",  // valid
      "",          // boundary: empty
      "(",         // invalid
      "[a-z]+",    // valid
  };

  for (const auto& pat : patterns) {
    SCOPED_TRACE(::testing::Message() << "Pattern: '" << pat << "'");
    RE2 re(pat);
    auto b = re2_python::RE2ErrorShim(re);
    std::string shim_err = static_cast<std::string>(b);
    EXPECT_EQ(shim_err, re.error());
  }
}

}  // namespace

// Provide a custom main to ensure the Python interpreter is initialized
// before any test constructs/uses py::bytes.
int main(int argc, char** argv) {
  py::scoped_interpreter guard{};
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
