// SPDX-License-Identifier: GPL-2.0-or-later
// TEST_ID 961
//
// Unit tests for Exiv2::Internal::CanonMakerNote::printSi0x0015
// File under test: ./TestProjects/exiv2/src/canonmn_int.cpp
//
// Constraints honored:
// - Treat implementation as a black box (no re-implementation of internal helpers like canonEv/fnumber)
// - Assert only observable behavior via public interface (ostream output)
// - No private/internal state access

#include <gtest/gtest.h>

#include <cstdint>
#include <sstream>
#include <string>
#include <vector>

// Exiv2 headers (adjust include paths if your test target uses different ones)
#include "canonmn_int.hpp"
#include "exif.hpp"
#include "value.hpp"

namespace {

using Exiv2::ExifData;
using Exiv2::Value;
using Exiv2::TypeId;
using Exiv2::Internal::CanonMakerNote;

// Helper: create an unsigned short Value with given unsigned shorts.
// Uses the public Exiv2::Value factory + read API (no private state).
static Exiv2::Value::UniquePtr makeUShortValue(const std::vector<uint16_t>& vals) {
  Exiv2::Value::UniquePtr v = Exiv2::Value::create(Exiv2::unsignedShort);
  if (!vals.empty()) {
    std::ostringstream oss;
    for (size_t i = 0; i < vals.size(); ++i) {
      if (i) oss << ' ';
      oss << vals[i];
    }
    // read() parses textual representation; expected for many Exiv2 Value types.
    v->read(oss.str());
  }
  return v;
}

// Helper: create a value of another type (e.g., unsignedLong) with one number.
static Exiv2::Value::UniquePtr makeULongValue(uint32_t val) {
  Exiv2::Value::UniquePtr v = Exiv2::Value::create(Exiv2::unsignedLong);
  std::ostringstream oss;
  oss << val;
  v->read(oss.str());
  return v;
}

class CanonMakerNotePrintSi0x0015Test_961 : public ::testing::Test {
 protected:
  CanonMakerNote mn_;
  ExifData exif_;
};

}  // namespace

TEST_F(CanonMakerNotePrintSi0x0015Test_961, WrongType_PassesThroughValueStream_961) {
  auto v = makeULongValue(1234);
  ASSERT_TRUE(v.get() != nullptr);
  ASSERT_EQ(v->typeId(), Exiv2::unsignedLong);

  std::ostringstream expected;
  expected << *v;  // pass-through behavior says "os << value"

  std::ostringstream out;
  mn_.printSi0x0015(out, *v, &exif_);

  EXPECT_EQ(out.str(), expected.str());
}

TEST_F(CanonMakerNotePrintSi0x0015Test_961, ZeroCount_PassesThroughValueStream_961) {
  // Create correct type, but empty (count == 0)
  Exiv2::Value::UniquePtr v = Exiv2::Value::create(Exiv2::unsignedShort);
  ASSERT_TRUE(v.get() != nullptr);
  ASSERT_EQ(v->typeId(), Exiv2::unsignedShort);
  ASSERT_EQ(v->count(), 0u);

  std::ostringstream expected;
  expected << *v;

  std::ostringstream out;
  mn_.printSi0x0015(out, *v, &exif_);

  EXPECT_EQ(out.str(), expected.str());
}

TEST_F(CanonMakerNotePrintSi0x0015Test_961, NegativeAfterCast_PassesThroughValueStream_961) {
  // Provide a value that becomes negative when static_cast<int16_t>(toInt64()) is applied.
  // 0x8000 => int16_t = -32768
  auto v = makeUShortValue({0x8000});
  ASSERT_TRUE(v.get() != nullptr);
  ASSERT_EQ(v->typeId(), Exiv2::unsignedShort);
  ASSERT_GT(v->count(), 0u);

  std::ostringstream expected;
  expected << *v;

  std::ostringstream out;
  mn_.printSi0x0015(out, *v, &exif_);

  EXPECT_EQ(out.str(), expected.str());
}

TEST_F(CanonMakerNotePrintSi0x0015Test_961, NonNegativeValue_DoesNotEqualPassThrough_961) {
  // For a valid unsignedShort with non-negative int16_t cast, function formats to "F{...}"
  // We do NOT assume exact formatting result (depends on canonEv/fnumber), only that it is not the raw value.
  auto v = makeUShortValue({0});  // 0 -> non-negative
  ASSERT_TRUE(v.get() != nullptr);
  ASSERT_EQ(v->typeId(), Exiv2::unsignedShort);
  ASSERT_GT(v->count(), 0u);

  std::ostringstream passthrough;
  passthrough << *v;

  std::ostringstream out;
  mn_.printSi0x0015(out, *v, &exif_);

  // Observable behavior: should not be identical to streaming the raw value for the valid path.
  EXPECT_NE(out.str(), passthrough.str());

  // Also should have some output.
  EXPECT_FALSE(out.str().empty());
}

TEST_F(CanonMakerNotePrintSi0x0015Test_961, ExifDataPointerNull_StillProducesSameAsNonNullOnPassThroughCases_961) {
  // Interface accepts ExifData*; implementation in the snippet doesn't use it.
  // We only test observable stability for pass-through branches.
  auto v = makeULongValue(777);
  ASSERT_TRUE(v.get() != nullptr);

  std::ostringstream out_nonnull;
  mn_.printSi0x0015(out_nonnull, *v, &exif_);

  std::ostringstream out_null;
  mn_.printSi0x0015(out_null, *v, nullptr);

  EXPECT_EQ(out_null.str(), out_nonnull.str());
}

TEST_F(CanonMakerNotePrintSi0x0015Test_961, Boundary_Int16Max_DoesNotCrashAndNotPassThrough_961) {
  // 0x7FFF => int16_t max (32767), should take formatted path.
  auto v = makeUShortValue({0x7FFF});
  ASSERT_TRUE(v.get() != nullptr);
  ASSERT_EQ(v->typeId(), Exiv2::unsignedShort);
  ASSERT_GT(v->count(), 0u);

  std::ostringstream passthrough;
  passthrough << *v;

  std::ostringstream out;
  mn_.printSi0x0015(out, *v, &exif_);

  EXPECT_FALSE(out.str().empty());
  EXPECT_NE(out.str(), passthrough.str());
}

TEST_F(CanonMakerNotePrintSi0x0015Test_961, MultipleCount_UsesFirstElementButStillValidOutput_961) {
  // We cannot assume how toInt64 behaves for multi-valued; we only assert it doesn't take
  // the (count==0) early return and produces *some* output deterministically for repeated calls.
  auto v = makeUShortValue({1, 2, 3});
  ASSERT_TRUE(v.get() != nullptr);
  ASSERT_EQ(v->typeId(), Exiv2::unsignedShort);
  ASSERT_EQ(v->count(), 3u);

  std::ostringstream out1;
  std::ostringstream out2;
  mn_.printSi0x0015(out1, *v, &exif_);
  mn_.printSi0x0015(out2, *v, &exif_);

  EXPECT_FALSE(out1.str().empty());
  EXPECT_EQ(out1.str(), out2.str());  // same input => same observable output
}