// File: filter_compile_tests_64.cc
#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <pybind11/embed.h>   // py::scoped_interpreter
#include <pybind11/pytypes.h> // py::bytes
// Include the headers that declare re2_python::Filter and re2::RE2::Options
// Adjust include paths as needed by your project layout.
#include "TestProjects/re2/python/_re2.cc"   // or the proper header that declares Filter
#include "TestProjects/re2/re2/re2.h"

namespace py = pybind11;
using ::testing::Contains;
using ::testing::IsEmpty;
using ::testing::UnorderedElementsAre;

class FilterCompileTest_64 : public ::testing::Test {
protected:
  // Start a Python interpreter so we can construct py::bytes for py::buffer params.
  py::scoped_interpreter guard_;
};

// --- Normal operation: no patterns added ---
TEST_F(FilterCompileTest_64, CompileWithNoPatternsReturnsAndMatchesNothing_64) {
  re2_python::Filter f;

  // Compiling with no patterns should succeed (observable: returns bool).
  // We don't assume internal behavior beyond the return and that later Match is empty.
  ASSERT_TRUE(f.Compile());

  // Match on arbitrary text should yield no indices.
  auto out = f.Match(py::bytes("anything"), /*potential=*/false);
  EXPECT_THAT(out, IsEmpty());
}

// --- Normal operation: single literal match, case-insensitive behavior ---
TEST_F(FilterCompileTest_64, SingleLiteralCaseInsensitiveMatch_64) {
  re2_python::Filter f;

  re2::RE2::Options add_opts;  // Interface requires options at Add-time; we don't rely on internal use here.
  // Add a pattern in uppercase; Compile() forces literal(true) and case_sensitive(false).
  const int idx = f.Add(py::bytes("HELLO"), add_opts);
  // Index should be non-negative (we check by observing it appears in Match result later).
  ASSERT_GE(idx, 0);

  ASSERT_TRUE(f.Compile());

  // Because Compile() sets case-insensitive, lowercase text should still match.
  auto matched = f.Match(py::bytes("say hello to re2"), /*potential=*/false);
  EXPECT_THAT(matched, Contains(idx));
}

// --- Literal behavior: metacharacters should NOT act as regex ---
TEST_F(FilterCompileTest_64, LiteralDotDoesNotWildcard_64) {
  re2_python::Filter f;

  re2::RE2::Options add_opts;
  const int idx_dot = f.Add(py::bytes("a.c"), add_opts);
  ASSERT_GE(idx_dot, 0);

  ASSERT_TRUE(f.Compile());

  // With literal(true), "a.c" should match only the exact substring "a.c"
  auto exact_hit = f.Match(py::bytes("xx a.c yy"), /*potential=*/false);
  EXPECT_THAT(exact_hit, Contains(idx_dot));

  // And should NOT match "abc" (dot is literal, not a wildcard).
  auto no_hit = f.Match(py::bytes("xx abc yy"), /*potential=*/false);
  EXPECT_THAT(no_hit, ::testing::Not(Contains(idx_dot)));
}

// --- Multiple patterns: both should be reported by Match() ---
TEST_F(FilterCompileTest_64, MultiplePatternsBothReported_64) {
  re2_python::Filter f;

  re2::RE2::Options add_opts;
  const int idx_cat = f.Add(py::bytes("cat"), add_opts);
  const int idx_dog = f.Add(py::bytes("dog"), add_opts);
  ASSERT_GE(idx_cat, 0);
  ASSERT_GE(idx_dog, 0);

  ASSERT_TRUE(f.Compile());

  auto hits = f.Match(py::bytes("hot dog with cat"), /*potential=*/false);
  // Order of returned indices is an observable detail of the implementation; to avoid
  // over-constraining, just assert presence of both indices (unordered).
  EXPECT_THAT(hits, UnorderedElementsAre(idx_cat, idx_dog));
}

// --- Case-insensitive ensures mixed-case matches ---
TEST_F(FilterCompileTest_64, CaseInsensitiveMixedCase_64) {
  re2_python::Filter f;

  re2::RE2::Options add_opts;
  const int idx = f.Add(py::bytes("ReGeX"), add_opts);
  ASSERT_GE(idx, 0);

  ASSERT_TRUE(f.Compile());

  // Mixed case in text should still match due to case_sensitive(false) set in Compile().
  auto hit1 = f.Match(py::bytes("using regex engines"), /*potential=*/false);
  EXPECT_THAT(hit1, Contains(idx));

  auto hit2 = f.Match(py::bytes("REGEX all-caps"), /*potential=*/false);
  EXPECT_THAT(hit2, Contains(idx));
}

// --- Boundary: empty haystack behavior (should be no matches for non-empty pattern) ---
TEST_F(FilterCompileTest_64, EmptyHaystackNoMatchForNonEmptyPattern_64) {
  re2_python::Filter f;

  re2::RE2::Options add_opts;
  const int idx = f.Add(py::bytes("nonempty"), add_opts);
  ASSERT_GE(idx, 0);

  ASSERT_TRUE(f.Compile());

  auto hits = f.Match(py::bytes(""), /*potential=*/false);
  EXPECT_THAT(hits, IsEmpty());
}
