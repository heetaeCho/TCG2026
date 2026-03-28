// File: re2_named_groups_shim_test_55.cc

#include <gtest/gtest.h>
#include <map>
#include <string>
#include <utility>
#include <vector>

#include <pybind11/pybind11.h>
#include <pybind11/embed.h>

#include "re2/re2.h"

// Declaration of the shim under test (implemented in _re2.cc).
namespace py = pybind11;
namespace re2_python {
  std::vector<std::pair<py::bytes, int>> RE2NamedCapturingGroupsShim(const RE2& self);
}

// Test fixture: initializes a Python interpreter for py::bytes usage.
class RE2NamedGroupsShimTest_55 : public ::testing::Test {
protected:
  static std::unique_ptr<py::scoped_interpreter> guard_;

  static void SetUpTestSuite() {
    // Start Python (required to create/compare py::bytes)
    guard_ = std::make_unique<py::scoped_interpreter>();
  }

  static void TearDownTestSuite() {
    guard_.reset();
  }

  // Helper: convert the shim's return value to a std::map<std::string,int>
  // so tests don't depend on vector ordering.
  static std::map<std::string, int> AsNameIndexMap(
      const std::vector<std::pair<py::bytes, int>>& v) {
    // Must hold the GIL while interacting with py::objects.
    py::gil_scoped_acquire gil{};
    std::map<std::string, int> out;
    for (const auto& p : v) {
      // py::bytes -> std::string (byte-preserving)
      std::string name = py::cast<std::string>(p.first);
      out.emplace(name, p.second);
    }
    return out;
  }
};

std::unique_ptr<py::scoped_interpreter> RE2NamedGroupsShimTest_55::guard_;

// --- Tests ---

// No named groups -> empty result.
TEST_F(RE2NamedGroupsShimTest_55, ReturnsEmptyVectorWhenNoNamedGroups_55) {
  RE2 re(R"((\w+)-(\d+))");  // two unnamed captures
  ASSERT_TRUE(re.ok());

  auto result = re2_python::RE2NamedCapturingGroupsShim(re);
  EXPECT_TRUE(result.empty());
}

// Two named groups -> both appear with correct indices.
TEST_F(RE2NamedGroupsShimTest_55, ReturnsNamesAndIndicesForTwoGroups_55) {
  RE2 re(R"((?P<first>\w+)-(?P<second>\d+))");
  ASSERT_TRUE(re.ok());

  auto result = re2_python::RE2NamedCapturingGroupsShim(re);
  auto m = AsNameIndexMap(result);

  // Expect exactly two entries.
  ASSERT_EQ(m.size(), 2u);

  // Indices should correspond to their capture group positions (1-based).
  // Observable via the public API contract of NamedCapturingGroups().
  EXPECT_EQ(m["first"], 1);
  EXPECT_EQ(m["second"], 2);

  // Sanity: indices are within the reported number of capturing groups.
  EXPECT_LE(m["first"], re.NumberOfCapturingGroups());
  EXPECT_LE(m["second"], re.NumberOfCapturingGroups());
}

// Mixing unnamed and named captures: indices must reflect actual capture order.
TEST_F(RE2NamedGroupsShimTest_55, HandlesMixOfUnnamedAndNamedGroups_55) {
  // Group layout:
  //  (1) unnamed       -> (\w+)
  //  (2) named "bar"   -> (?P<bar>[A-Z]+)
  //  noncapturing      -> (?:skip)
  //  (3) named "num"   -> (?P<num>\d+)
  RE2 re(R"((\w+)-(?P<bar>[A-Z]+)-(?:skip)-(?P<num>\d+))");
  ASSERT_TRUE(re.ok());

  auto result = re2_python::RE2NamedCapturingGroupsShim(re);
  auto m = AsNameIndexMap(result);

  ASSERT_EQ(m.size(), 2u);
  EXPECT_EQ(m["bar"], 2);
  EXPECT_EQ(m["num"], 3);
  EXPECT_LE(m["bar"], re.NumberOfCapturingGroups());
  EXPECT_LE(m["num"], re.NumberOfCapturingGroups());
}

// Verifies that names are returned as *bytes* with exact contents (ASCII-safe).
TEST_F(RE2NamedGroupsShimTest_55, BytesNameContentIsExact_55) {
  RE2 re(R"((?Palpha>\w+)_(?P<beta>\d+))");  // note: "alpha" without angle? corrected below
  // The above line has a typo for a Python-style group; correct pattern:
  RE2 re_fix(R"((?P<alpha>\w+)_(?P<beta>\d+))");
  ASSERT_TRUE(re_fix.ok());

  auto result = re2_python::RE2NamedCapturingGroupsShim(re_fix);

  // Collect names as std::strings from py::bytes to verify exact byte content.
  py::gil_scoped_acquire gil{};
  std::vector<std::string> names;
  names.reserve(result.size());
  for (const auto& p : result) {
    names.push_back(py::cast<std::string>(p.first));
  }

  // Order is not guaranteed by the API; check set membership.
  // (std::map is ordered by key, but we avoid asserting order here.)
  ASSERT_EQ(names.size(), 2u);
  EXPECT_TRUE(std::find(names.begin(), names.end(), "alpha") != names.end());
  EXPECT_TRUE(std::find(names.begin(), names.end(), "beta")  != names.end());
}
