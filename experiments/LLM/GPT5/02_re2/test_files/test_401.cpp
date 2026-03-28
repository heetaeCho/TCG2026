// File: flattened_prog_to_string_test.cc

#include <gtest/gtest.h>
#include <string>
#include <vector>
#include <cstdarg>
#include <cstdio>

// ---- Minimal shims & test doubles (only what's needed by the function under test) ----
namespace absl {
// Tiny printf-style formatter sufficient for these tests.
template <typename... Args>
std::string StrFormat(const char* fmt, Args... args) {
  // First, compute needed size
  int size = std::snprintf(nullptr, 0, fmt, args...);
  if (size <= 0) return std::string();
  std::string out(static_cast<size_t>(size), '\0');
  std::snprintf(out.data(), out.size() + 1, fmt, args...);
  return out;
}
}  // namespace absl

namespace re2 {

// Minimal interface-only doubles that the function touches.
class Prog {
 public:
  class Inst {
   public:
    Inst() = default;
    explicit Inst(std::string dump, bool last)
        : dump_(std::move(dump)), last_(last) {}
    // Only the methods used by FlattenedProgToString:
    int last() { return last_ ? 1 : 0; }
    std::string Dump() { return dump_; }

   private:
    std::string dump_;
    bool last_ = false;
  };

  explicit Prog(std::vector<Inst> insts) : insts_(std::move(insts)) {}

  int size() { return static_cast<int>(insts_.size()); }
  Inst* inst(int id) { return &insts_.at(static_cast<size_t>(id)); }

 private:
  std::vector<Inst> insts_;
};

}  // namespace re2

// ---- Include the implementation under test directly so we don't re-implement logic ----
// This file defines: static std::string re2::FlattenedProgToString(Prog*, int)
#include "re2/prog.cc"

// ------------------------------ Tests ------------------------------

using re2::Prog;

// Normal operation: mixes '+' and '.' endings and preserves indices.
TEST(FlattenedProgToStringTest_401, FormatsIndicesAndTerminators_401) {
  Prog p({
      Prog::Inst("A", /*last=*/false),
      Prog::Inst("B", /*last=*/false),
      Prog::Inst("C", /*last=*/true),
  });

  std::string out = re2::FlattenedProgToString(&p, /*start=*/0);

  // Expect:
  // 0+ A
  // 1+ B
  // 2. C
  std::string expected;
  expected += "0+ A\n";
  expected += "1+ B\n";
  expected += "2. C\n";
  EXPECT_EQ(out, expected);
}

// Boundary: start in the middle should skip the first entries entirely.
TEST(FlattenedProgToStringTest_401, StartsFromGivenIndex_401) {
  Prog p({
      Prog::Inst("X", /*last=*/false),
      Prog::Inst("Y", /*last=*/false),
      Prog::Inst("Z", /*last=*/true),
  });

  std::string out = re2::FlattenedProgToString(&p, /*start=*/1);

  std::string expected;
  expected += "1+ Y\n";
  expected += "2. Z\n";
  EXPECT_EQ(out, expected);
}

// Boundary: start == size() → empty output.
TEST(FlattenedProgToStringTest_401, EmptyWhenStartEqualsSize_401) {
  Prog p({
      Prog::Inst("only", /*last=*/true),
  });

  std::string out = re2::FlattenedProgToString(&p, /*start=*/p.size());
  EXPECT_TRUE(out.empty());
}

// Boundary: start > size() → empty output (loop never enters).
TEST(FlattenedProgToStringTest_401, EmptyWhenStartGreaterThanSize_401) {
  Prog p({
      Prog::Inst("a", /*last=*/false),
      Prog::Inst("b", /*last=*/true),
  });

  std::string out = re2::FlattenedProgToString(&p, /*start=*/p.size() + 5);
  EXPECT_TRUE(out.empty());
}

// All-final: when every inst is marked last(), every line should end with '.'.
TEST(FlattenedProgToStringTest_401, AllLastEndsWithDot_401) {
  Prog p({
      Prog::Inst("M1", /*last=*/true),
      Prog::Inst("M2", /*last=*/true),
  });

  std::string out = re2::FlattenedProgToString(&p, /*start=*/0);

  std::string expected;
  expected += "0. M1\n";
  expected += "1. M2\n";
  EXPECT_EQ(out, expected);
}
