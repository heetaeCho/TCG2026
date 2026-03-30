// SPDX-License-Identifier: GPL-2.0-or-later
// File: test_xmptextvalue_touint32_840.cpp
//
// Unit tests for:
//   Exiv2::XmpTextValue::toUint32(size_t) const
//
// Constraints respected:
// - Treat implementation as black box (no logic re-implementation).
// - Only use observable behavior through the public interface.
// - No private state access.

#include <gtest/gtest.h>
#include <cstdint>
#include <limits>

#include "value.hpp"  // Exiv2::XmpTextValue

namespace {

// TEST_ID = 840
class XmpTextValueTest_840 : public ::testing::Test {};

}  // namespace

// Note:
// We only have the signature for toUint32(size_t) and do not have any public setter exposed here.
// Therefore, these tests focus on *interface-level contracts* that are observable without
// constructing internal text state. In particular, we validate behavior with default construction,
// argument boundary behavior (n ignored), const-ness, and repeatability.
// If your codebase exposes a public way to set the text content (e.g., via Value::read, setValue,
// operator=, or factory helpers), add additional tests to cover parsing outcomes.

TEST_F(XmpTextValueTest_840, DefaultConstructed_ReturnsSomeUint32AndIsStable_840) {
  const Exiv2::XmpTextValue v;

  const uint32_t a = v.toUint32(0);
  const uint32_t b = v.toUint32(0);

  // Observable behavior: returns a uint32_t and should be stable for same object/state.
  EXPECT_EQ(a, b);
}

TEST_F(XmpTextValueTest_840, IgnoresIndexArgument_BoundaryValuesProduceSameResult_840) {
  const Exiv2::XmpTextValue v;

  const uint32_t a = v.toUint32(0);
  const uint32_t b = v.toUint32(1);
  const uint32_t c = v.toUint32(std::numeric_limits<size_t>::max());

  // Signature comment says size_t /*n*/ is unused; validate that different n doesn't change output.
  EXPECT_EQ(a, b);
  EXPECT_EQ(a, c);
}

TEST_F(XmpTextValueTest_840, CanCallOnConstReference_NoMutationObserved_840) {
  Exiv2::XmpTextValue v;
  const Exiv2::XmpTextValue& cv = v;

  const uint32_t before = cv.toUint32(0);
  const uint32_t after = cv.toUint32(0);

  // Observable behavior: method is const; repeated calls should not mutate visible output.
  EXPECT_EQ(before, after);
}

TEST_F(XmpTextValueTest_840, MultipleCallsWithDifferentArguments_AreAllStable_840) {
  const Exiv2::XmpTextValue v;

  const uint32_t r0 = v.toUint32(0);
  const uint32_t r1 = v.toUint32(123);
  const uint32_t r2 = v.toUint32(std::numeric_limits<size_t>::max());
  const uint32_t r3 = v.toUint32(0);

  // All should match if argument is ignored and state doesn't change.
  EXPECT_EQ(r0, r1);
  EXPECT_EQ(r0, r2);
  EXPECT_EQ(r0, r3);
}