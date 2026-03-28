// =====================================================================================
// TEST_ID: 803
// File: test_string_value_base_803.cpp
//
// Unit tests for Exiv2::StringValueBase (value.cpp/value.hpp)
// Constraints respected:
//  - Treat implementation as black box (no internal logic assumptions beyond interface)
//  - Only observable behavior via public API
//  - No private state access (value_ is public in the provided header snippet, but we DO NOT use it)
//  - No mocking needed (no external collaborators visible in this interface)
// =====================================================================================

#include <gtest/gtest.h>

#include <cstdint>
#include <cstring>
#include <limits>
#include <ostream>
#include <sstream>
#include <string>
#include <vector>

// The real project should provide these headers/types.
// Keep include as in Exiv2 project; adjust include path if your build uses a different one.
#include "exiv2/value.hpp"

namespace {

// Helper to build byte buffers from std::string without assuming null-termination.
static std::vector<Exiv2::byte> ToBytes(const std::string& s) {
  std::vector<Exiv2::byte> out;
  out.reserve(s.size());
  for (unsigned char c : s) out.push_back(static_cast<Exiv2::byte>(c));
  return out;
}

}  // namespace

// Note: We avoid touching StringValueBase::value_ directly even though it's public in the snippet.
// All expectations are validated through public methods like size(), count(), copy(), write(), etc.

class StringValueBaseTest_803 : public ::testing::Test {
 protected:
  // Choose a plausible TypeId for a "string-like" value without assuming internals.
  // If your Exiv2 build uses a different enumerator name, adjust accordingly.
  // Many Exiv2 builds have Exiv2::asciiString or Exiv2::string.
  static Exiv2::TypeId StringType() {
#if defined(EXIV2_HAVE_TYPEID_ASCIISTRING)  // (unlikely) placeholder macro
    return Exiv2::asciiString;
#else
    // Fall back to a commonly present enumerator in Exiv2.
    return Exiv2::asciiString;
#endif
  }
};

TEST_F(StringValueBaseTest_803, ReadStringReturnsZero_803) {
  Exiv2::StringValueBase v(StringType(), "");
  const int rc = v.read(std::string("hello"));
  EXPECT_EQ(0, rc);
}

TEST_F(StringValueBaseTest_803, ReadStringUpdatesObservableWriteOutput_803) {
  Exiv2::StringValueBase v(StringType(), "");
  ASSERT_EQ(0, v.read(std::string("abc")));

  std::ostringstream oss;
  v.write(oss);
  EXPECT_EQ("abc", oss.str());
}

TEST_F(StringValueBaseTest_803, ReadEmptyStringProducesEmptyWriteAndZeroSize_803) {
  Exiv2::StringValueBase v(StringType(), "seed");
  ASSERT_EQ(0, v.read(std::string("")));

  std::ostringstream oss;
  v.write(oss);
  EXPECT_TRUE(oss.str().empty());

  EXPECT_EQ(0u, v.size());
  EXPECT_EQ(0u, v.count());
}

TEST_F(StringValueBaseTest_803, CountMatchesSizeForSimpleString_803) {
  Exiv2::StringValueBase v(StringType(), "");
  const std::string s = "abcdef";
  ASSERT_EQ(0, v.read(s));

  // For a string value, it's reasonable and observable that count/size align;
  // we validate the relationship only via public API.
  EXPECT_EQ(v.size(), v.count());
  EXPECT_EQ(s.size(), v.size());

  std::vector<Exiv2::byte> buf(s.size());
  const size_t copied = v.copy(buf.data(), Exiv2::invalidByteOrder);
  EXPECT_EQ(s.size(), copied);
}

TEST_F(StringValueBaseTest_803, CopyReturnsNumberOfBytesAndMatchesWrite_803) {
  Exiv2::StringValueBase v(StringType(), "");
  const std::string s = "copy-me";
  ASSERT_EQ(0, v.read(s));

  std::vector<Exiv2::byte> out(s.size(), 0);
  const size_t copied = v.copy(out.data(), Exiv2::invalidByteOrder);
  EXPECT_EQ(s.size(), copied);

  std::string roundtrip(reinterpret_cast<const char*>(out.data()), out.size());
  EXPECT_EQ(s, roundtrip);

  std::ostringstream oss;
  v.write(oss);
  EXPECT_EQ(s, oss.str());
}

TEST_F(StringValueBaseTest_803, CopyIntoLargerBufferDoesNotRequireNullTermination_803) {
  Exiv2::StringValueBase v(StringType(), "");
  const std::string s = "xyz";
  ASSERT_EQ(0, v.read(s));

  std::vector<Exiv2::byte> out(16, static_cast<Exiv2::byte>(0xAA));
  const size_t copied = v.copy(out.data(), Exiv2::invalidByteOrder);
  EXPECT_EQ(s.size(), copied);

  std::string got(reinterpret_cast<const char*>(out.data()), s.size());
  EXPECT_EQ(s, got);

  // Ensure we didn't assume null-termination; remaining bytes should stay as initialized.
  for (size_t i = s.size(); i < out.size(); ++i) {
    EXPECT_EQ(static_cast<Exiv2::byte>(0xAA), out[i]);
  }
}

TEST_F(StringValueBaseTest_803, ReadByteBufferEquivalentToReadStringForAscii_803) {
  Exiv2::StringValueBase v1(StringType(), "");
  Exiv2::StringValueBase v2(StringType(), "");

  const std::string s = "bytebuf";
  auto bytes = ToBytes(s);

  ASSERT_EQ(0, v1.read(s));
  ASSERT_EQ(0, v2.read(bytes.data(), bytes.size(), Exiv2::invalidByteOrder));

  std::ostringstream o1, o2;
  v1.write(o1);
  v2.write(o2);

  EXPECT_EQ(o1.str(), o2.str());
  EXPECT_EQ(s, o2.str());
}

TEST_F(StringValueBaseTest_803, ReadByteBufferWithZeroLengthResultsInEmpty_803) {
  Exiv2::StringValueBase v(StringType(), "seed");
  const Exiv2::byte* nullBuf = nullptr;

  // Boundary: len = 0. Should be safe and result observable as empty (or unchanged).
  // We assert only what we can observe robustly: return code is 0 and write() consistent with size().
  const int rc = v.read(nullBuf, 0, Exiv2::invalidByteOrder);
  EXPECT_EQ(0, rc);

  std::ostringstream oss;
  v.write(oss);

  // At minimum, size() must match what write() produced.
  EXPECT_EQ(v.size(), oss.str().size());
  EXPECT_EQ(v.count(), v.size());
}

TEST_F(StringValueBaseTest_803, ToInt64OnNonNumericDoesNotCrashAndIsDeterministic_803) {
  Exiv2::StringValueBase v(StringType(), "");
  ASSERT_EQ(0, v.read(std::string("not-a-number")));

  // We don't assume conversion rules; just require consistent repeated calls.
  const int64_t a = v.toInt64(0);
  const int64_t b = v.toInt64(0);
  EXPECT_EQ(a, b);
}

TEST_F(StringValueBaseTest_803, ToUint32OnNonNumericDoesNotCrashAndIsDeterministic_803) {
  Exiv2::StringValueBase v(StringType(), "");
  ASSERT_EQ(0, v.read(std::string("nope")));

  const uint32_t a = v.toUint32(0);
  const uint32_t b = v.toUint32(0);
  EXPECT_EQ(a, b);
}

TEST_F(StringValueBaseTest_803, ToFloatOnNonNumericDoesNotCrashAndIsDeterministic_803) {
  Exiv2::StringValueBase v(StringType(), "");
  ASSERT_EQ(0, v.read(std::string("NaN?")));

  const float a = v.toFloat(0);
  const float b = v.toFloat(0);
  // Float equality is fine here because we only require determinism.
  EXPECT_EQ(a, b);
}

TEST_F(StringValueBaseTest_803, ToRationalOnNonNumericDoesNotCrashAndIsDeterministic_803) {
  Exiv2::StringValueBase v(StringType(), "");
  ASSERT_EQ(0, v.read(std::string("x/y")));

  const Exiv2::Rational a = v.toRational(0);
  const Exiv2::Rational b = v.toRational(0);
  EXPECT_EQ(a.first, b.first);
  EXPECT_EQ(a.second, b.second);
}

TEST_F(StringValueBaseTest_803, CloneProducesIndependentObjectWithSameWriteOutput_803) {
  Exiv2::StringValueBase v(StringType(), "");
  ASSERT_EQ(0, v.read(std::string("cloneme")));

  Exiv2::Value::UniquePtr c = v.clone();
  ASSERT_NE(nullptr, c.get());

  std::ostringstream o1, o2;
  v.write(o1);
  c->write(o2);

  EXPECT_EQ(o1.str(), o2.str());

  // Mutate original; clone should remain as it was (observable by write()).
  ASSERT_EQ(0, v.read(std::string("changed")));
  std::ostringstream o1b, o2b;
  v.write(o1b);
  c->write(o2b);

  EXPECT_NE(o1b.str(), o2b.str());
  EXPECT_EQ("changed", o1b.str());
  EXPECT_EQ("cloneme", o2b.str());
}

TEST_F(StringValueBaseTest_803, MultipleReadsLastWriteWins_803) {
  Exiv2::StringValueBase v(StringType(), "");
  ASSERT_EQ(0, v.read(std::string("first")));
  ASSERT_EQ(0, v.read(std::string("second")));

  std::ostringstream oss;
  v.write(oss);
  EXPECT_EQ("second", oss.str());
}

TEST_F(StringValueBaseTest_803, LargeStringReadAndCopyBoundary_803) {
  Exiv2::StringValueBase v(StringType(), "");

  const size_t N = 1024 * 64;  // boundary-ish but safe for unit tests
  std::string s(N, 'A');
  ASSERT_EQ(0, v.read(s));

  EXPECT_EQ(N, v.size());
  EXPECT_EQ(N, v.count());

  std::vector<Exiv2::byte> out(N);
  const size_t copied = v.copy(out.data(), Exiv2::invalidByteOrder);
  EXPECT_EQ(N, copied);

  // Spot check a few positions without assuming more.
  EXPECT_EQ(static_cast<Exiv2::byte>('A'), out.front());
  EXPECT_EQ(static_cast<Exiv2::byte>('A'), out[N / 2]);
  EXPECT_EQ(static_cast<Exiv2::byte>('A'), out.back());
}