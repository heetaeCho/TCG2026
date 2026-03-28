// SPDX-License-Identifier: GPL-2.0-or-later
// File: test_taglist_1365.cpp
//
// Unit tests for Exiv2::Internal::taglist(std::ostream&, IfdId)
//
// Constraints note:
// - Treat implementation as a black box.
// - Verify only observable behavior via ostream output and lack of exceptions.

#include <gtest/gtest.h>

#include <sstream>
#include <string>
#include <vector>

#include "exiv2/tags.hpp"  // IfdId (and related types) live in Exiv2 headers.

namespace {

// Calls taglist and returns resulting stream contents.
static std::string RunTaglistToString(Exiv2::IfdId ifdId, const std::string& prefix = {}) {
  std::ostringstream os;
  os << prefix;
  Exiv2::Internal::taglist(os, ifdId);
  return os.str();
}

// Convenience to test a handful of "likely" IFD ids without assuming any specific one exists.
// (We only assert generic invariants when output is non-empty.)
static std::vector<Exiv2::IfdId> SomeIfdIdsToProbe() {
  std::vector<Exiv2::IfdId> ids;
  for (int i = -2; i <= 25; ++i) {
    ids.push_back(static_cast<Exiv2::IfdId>(i));
  }
  ids.push_back(static_cast<Exiv2::IfdId>(9999));
  return ids;
}

}  // namespace

TEST(TaglistTest_1365, DoesNotModifyExistingStreamPrefix_1365) {
  const auto id = static_cast<Exiv2::IfdId>(0);
  const std::string prefix = "PREFIX\n";

  const std::string out = RunTaglistToString(id, prefix);

  ASSERT_GE(out.size(), prefix.size());
  EXPECT_EQ(out.substr(0, prefix.size()), prefix);
}

TEST(TaglistTest_1365, EmptyOutputOrEndsWithNewline_1365) {
  // Observable invariant from implementation: it prints each entry followed by "\n".
  // If nothing is printed, output remains empty.
  for (auto id : SomeIfdIdsToProbe()) {
    const std::string out = RunTaglistToString(id);

    if (!out.empty()) {
      EXPECT_EQ(out.back(), '\n') << "Output should end with a newline when non-empty.";
    } else {
      SUCCEED() << "No tag list for this IfdId; empty output is acceptable.";
    }
  }
}

TEST(TaglistTest_1365, DeterministicForSameIfdId_1365) {
  // For a pure "listing" function, repeated calls with same input should produce identical output.
  // (We don't assume non-empty output, only determinism.)
  const auto id = static_cast<Exiv2::IfdId>(0);

  const std::string out1 = RunTaglistToString(id);
  const std::string out2 = RunTaglistToString(id);

  EXPECT_EQ(out1, out2);
}

TEST(TaglistTest_1365, InvalidIfdIdDoesNotThrowAndProducesNoOutput_1365) {
  // Boundary / error-ish cases: unknown IfdId values should result in no output
  // if tagList(ifdId) is null. We verify only what is observable and safe.
  // If Exiv2 ever changes to provide fallback lists, this test remains valid on "no throw";
  // the "no output" expectation is limited to clearly out-of-range values.
  const auto invalid1 = static_cast<Exiv2::IfdId>(-1);
  const auto invalid2 = static_cast<Exiv2::IfdId>(9999);

  {
    std::ostringstream os;
    EXPECT_NO_THROW(Exiv2::Internal::taglist(os, invalid1));
    EXPECT_TRUE(os.str().empty());
  }
  {
    std::ostringstream os;
    EXPECT_NO_THROW(Exiv2::Internal::taglist(os, invalid2));
    EXPECT_TRUE(os.str().empty());
  }
}

TEST(TaglistTest_1365, DoesNotThrowWhenStreamIsInFailState_1365) {
  // Boundary: writing to a stream with failbit set should be a no-op but must not crash/throw.
  const auto id = static_cast<Exiv2::IfdId>(0);

  std::ostringstream os;
  os.setstate(std::ios::failbit);

  EXPECT_NO_THROW(Exiv2::Internal::taglist(os, id));
  EXPECT_TRUE(os.str().empty());
}