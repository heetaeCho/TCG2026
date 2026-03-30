// File: set_match_test_62.cc
#include <gtest/gtest.h>
#include <re2/re2.h>
#include <re2/set.h>
#include <algorithm>
#include <vector>
#include <string>

#include <pybind11/embed.h>
#include <pybind11/pybind11.h>
#include <pybind11/pytypes.h>

namespace py = pybind11;

// --- Class under test (header declarations assumed available in build) ---
namespace re2_python {
class Set {
 public:
  Set(RE2::Anchor anchor, const RE2::Options& options);
  Set(const Set&) = delete;
  Set& operator=(const Set&) = delete;
  ~Set() = default;

  int Add(py::buffer buffer);
  bool Compile();
  std::vector<int> Match(py::buffer buffer) const;
};
}  // namespace re2_python

class SetMatchTest_62 : public ::testing::Test {
 protected:
  // Keep interpreter alive across all tests in this suite
  static std::unique_ptr<py::scoped_interpreter> guard_;

  static void SetUpTestSuite() {
    if (!guard_) {
      guard_ = std::make_unique<py::scoped_interpreter>();
    }
  }
  static void TearDownTestSuite() {
    // Keep interpreter for the whole test binary lifetime to avoid finalize issues.
    // Do not reset guard_ here.
  }

  // Helper: construct a py::buffer from std::string via bytearray
  static py::buffer MakeBufferFromString(const std::string& s) {
    py::bytes py_b(s);
    py::object ba = py::bytearray(py_b); // supports buffer protocol and is mutable
    return py::buffer(ba);
  }

  // Helper: construct a py::buffer as memoryview over a bytearray
  static py::buffer MakeMemoryViewBuffer(const std::string& s) {
    py::bytes py_b(s);
    py::object ba = py::bytearray(py_b);
    py::object mv = py::module_::import("builtins").attr("memoryview")(ba);
    return py::buffer(mv);
  }

  static re2_python::Set MakeDefaultSet() {
    RE2::Options opts;
    // Use defaults; do not assume internal behavior beyond public API.
    return re2_python::Set(RE2::UNANCHORED, opts);
  }
};

std::unique_ptr<py::scoped_interpreter> SetMatchTest_62::guard_;

// --- Tests ---

// Normal operation: multiple patterns, multiple matches by index order
TEST_F(SetMatchTest_62, MultiplePatterns_MultipleMatches_ReturnsIndices_62) {
  auto set = MakeDefaultSet();

  // Add patterns; indices should reflect add order.
  ASSERT_GE(set.Add(MakeBufferFromString("cat")), 0);
  ASSERT_GE(set.Add(MakeBufferFromString("dog")), 0);
  ASSERT_GE(set.Add(MakeBufferFromString("bird")), 0);

  ASSERT_TRUE(set.Compile());

  auto matches = set.Match(MakeBufferFromString("a cat and a dog walked by"));

  // Expect "cat" (0) and "dog" (1) present, "bird"(2) absent.
  std::sort(matches.begin(), matches.end());
  std::vector<int> expected{0, 1};
  EXPECT_EQ(matches, expected);
}

// Boundary: empty set (no patterns) compiled should yield no matches
TEST_F(SetMatchTest_62, EmptySet_NoPatterns_YieldsEmptyMatches_62) {
  auto set = MakeDefaultSet();
  ASSERT_TRUE(set.Compile());

  auto matches = set.Match(MakeBufferFromString("anything here"));
  EXPECT_TRUE(matches.empty());
}

// Boundary: empty input text with non-empty patterns should return no matches
// (We avoid patterns like ".*" to keep observable behavior straightforward.)
TEST_F(SetMatchTest_62, EmptyInputText_NoMatch_62) {
  auto set = MakeDefaultSet();
  ASSERT_GE(set.Add(MakeBufferFromString("a+")), 0);
  ASSERT_GE(set.Add(MakeBufferFromString("b+")), 0);
  ASSERT_TRUE(set.Compile());

  auto matches = set.Match(MakeBufferFromString(""));
  EXPECT_TRUE(matches.empty());
}

// Normal operation with UTF-8 input: ensure the buffer path handles multibyte text
TEST_F(SetMatchTest_62, UTF8Input_KoreanWord_MatchFound_62) {
  auto set = MakeDefaultSet();

  // Add a UTF-8 literal pattern (Korean "고양이" = "cat").
  ASSERT_GE(set.Add(MakeBufferFromString(u8"고양이")), 0);
  ASSERT_GE(set.Add(MakeBufferFromString("dog")), 0);
  ASSERT_TRUE(set.Compile());

  auto matches = set.Match(MakeBufferFromString(u8"나는 고양이와 개를 좋아해요"));
  // Expect pattern at index 0 to match.
  ASSERT_FALSE(matches.empty());
  // Since we don't rely on order beyond indices, just check presence of 0.
  EXPECT_NE(std::find(matches.begin(), matches.end(), 0), matches.end());
}

// Buffer types: memoryview over bytearray should be accepted and produce same result
TEST_F(SetMatchTest_62, AcceptsMemoryViewBuffer_62) {
  auto set = MakeDefaultSet();

  ASSERT_GE(set.Add(MakeBufferFromString("alpha")), 0);
  ASSERT_GE(set.Add(MakeBufferFromString("beta")), 0);
  ASSERT_TRUE(set.Compile());

  auto matches_mv = set.Match(MakeMemoryViewBuffer("beta then alpha"));
  std::sort(matches_mv.begin(), matches_mv.end());

  std::vector<int> expected{0, 1}; // "alpha" index 0, "beta" index 1
  EXPECT_EQ(matches_mv, expected);
}

// Idempotence wrt duplicates in text: indices returned reflect presence, not count
// (observable via returned unique indices regardless of multiple occurrences)
TEST_F(SetMatchTest_62, MultipleOccurrences_ReturnsUniqueIndices_62) {
  auto set = MakeDefaultSet();

  ASSERT_GE(set.Add(MakeBufferFromString("ha")), 0);
  ASSERT_TRUE(set.Compile());

  auto matches = set.Match(MakeBufferFromString("hahaha")); // multiple "ha"
  // We only expect index {0} once as presence indicator.
  ASSERT_EQ(matches.size(), 1u);
  EXPECT_EQ(matches[0], 0);
}
