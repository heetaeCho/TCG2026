// File: filter_match_test_65.cc
#include <gtest/gtest.h>
#include <algorithm>
#include <set>
#include <string>
#include <vector>

#include <pybind11/embed.h>
#include <pybind11/pybind11.h>
#include <pybind11/numpy.h>

#include "re2/re2.h"

// Include header that declares re2_python::Filter (adjust include path as needed)
#include "TestProjects/re2/python/_re2.cc"  // or the appropriate header that declares Filter

namespace py = pybind11;
using re2_python::Filter;

class FilterMatchTest_65 : public ::testing::Test {
protected:
  // Start/stop embedded Python once for all tests in this binary.
  static void SetUpTestSuite() {
    guard_ = new py::scoped_interpreter();
  }
  static void TearDownTestSuite() {
    delete guard_;
    guard_ = nullptr;
  }

  // Helper to make a py::buffer from a std::string without assuming internals.
  static py::buffer MakeBuffer(const std::string& s) {
    // bytes objects implement the Python buffer protocol; wrap explicitly as py::buffer.
    return py::buffer(py::bytes(s));
  }

  // Sort a vector<int> in-place to assert independent of order (observable-safe).
  static void Sort(std::vector<int>& v) { std::sort(v.begin(), v.end()); }

  static py::scoped_interpreter* guard_;
};

py::scoped_interpreter* FilterMatchTest_65::guard_ = nullptr;

// ───────────────────────────────────────────────────────────────────────────────
// Error case: Match before Compile
// ───────────────────────────────────────────────────────────────────────────────
TEST_F(FilterMatchTest_65, MatchBeforeCompileThrows_65) {
  Filter f;
  auto buf = MakeBuffer("hello");

  // Expect a Python exception raised through pybind11 when Match is called pre-Compile.
  try {
    (void)f.Match(buf, /*potential=*/false);
    FAIL() << "Expected a Python exception when Match() is called before Compile()";
  } catch (const py::error_already_set& e) {
    // Check the message contains the API-visible failure text.
    std::string msg = e.what();
    // The exact formatting may include a Python traceback, so use substring check.
    EXPECT_NE(msg.find("Match() called before compiling"), std::string::npos)
        << "Unexpected exception message: " << msg;
  } catch (...) {
    FAIL() << "Expected py::error_already_set when calling Match() before Compile()";
  }
}

// ───────────────────────────────────────────────────────────────────────────────
// Normal operation: multiple patterns, definitive matches (potential=false)
// ───────────────────────────────────────────────────────────────────────────────
TEST_F(FilterMatchTest_65, ReturnsIdsOfMatchingPatterns_65) {
  Filter f;

  RE2::Options opts;  // Use default options via public API.
  const int id_foo = f.Add(MakeBuffer("foo"), opts);
  const int id_ba_dot = f.Add(MakeBuffer("ba."), opts); // matches "bar", "baz", etc.

  ASSERT_TRUE(f Compile()) << "Compile() should succeed after adding patterns";

  auto buf = MakeBuffer("xx bar yy foo zz");
  auto matches = f.Match(buf, /*potential=*/false);

  // We assert that both patterns match somewhere in the text.
  // Avoid relying on order: sort and compare as sets.
  Sort(matches);
  std::vector<int> expected{std::min(id_foo, id_ba_dot), std::max(id_foo, id_ba_dot)};
  Sort(expected);
  // They must be exactly the two we added (definitive matches).
  // If implementation returns unique IDs, sizes should match.
  // If duplicates were possible, we would de-duplicate before comparing; however,
  // the observable, public-facing expectation is unique pattern IDs.
  EXPECT_EQ(matches, expected);
}

// ───────────────────────────────────────────────────────────────────────────────
// Relationship: potentials should be a superset (or equal) of definitive matches
// ───────────────────────────────────────────────────────────────────────────────
TEST_F(FilterMatchTest_65, PotentialsIncludeAllDefinitiveMatches_65) {
  Filter f;

  RE2::Options opts;
  (void)f.Add(MakeBuffer("foo"), opts);
  (void)f.Add(MakeBuffer("ba."), opts);
  (void)f.Add(MakeBuffer("qu+x"), opts);  // might or might not match; adds variety

  ASSERT_TRUE(f.Compile());

  auto buf = MakeBuffer("bar foo");
  auto definitive = f.Match(buf, /*potential=*/false);
  auto potentials = f.Match(buf, /*potential=*/true);

  // Convert to sets for subset check.
  std::set<int> set_def(definitive.begin(), definitive.end());
  std::set<int> set_pot(potentials.begin(), potentials.end());

  // All definitive matches must appear among potentials.
  for (int id : set_def) {
    EXPECT_TRUE(set_pot.count(id) > 0) << "Definitive match id " << id
                                       << " not found in potentials";
  }
}

// ───────────────────────────────────────────────────────────────────────────────
// Boundary: empty input should yield no matches (without empty-patterns added)
// ───────────────────────────────────────────────────────────────────────────────
TEST_F(FilterMatchTest_65, EmptyInputYieldsNoMatches_65) {
  Filter f;

  RE2::Options opts;
  (void)f.Add(MakeBuffer("foo"), opts);
  (void)f.Add(MakeBuffer("bar"), opts);

  ASSERT_TRUE(f.Compile());

  auto buf = MakeBuffer("");  // empty input
  auto matches = f.Match(buf, /*potential=*/false);

  EXPECT_TRUE(matches.empty());
}

// ───────────────────────────────────────────────────────────────────────────────
// Boundary: compile with zero patterns, then match → should not throw and be empty
// ───────────────────────────────────────────────────────────────────────────────
TEST_F(FilterMatchTest_65, CompileWithNoPatterns_ThenMatchIsEmpty_65) {
  Filter f;

  // No Add() calls here.
  ASSERT_TRUE(f.Compile()) << "Compile() should handle zero patterns via public API";

  auto buf = MakeBuffer("some text");
  auto matches = f.Match(buf, /*potential=*/false);

  EXPECT_TRUE(matches.empty());
}
