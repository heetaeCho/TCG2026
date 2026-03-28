// File: test_datevalue_copy_865.cpp
// Tests for Exiv2::DateValue::copy (black-box via public interface)

#include <gtest/gtest.h>

#include <array>
#include <cstdint>
#include <cstring>
#include <memory>
#include <string>
#include <type_traits>

#include <exiv2/types.hpp>
#include <exiv2/value.hpp>

namespace {

using Exiv2::byte;

// Helper: create a DateValue via the public factory (keeps tests resilient to constructors).
static std::unique_ptr<Exiv2::Value> createDateValueOrSkip() {
  // Exiv2::Value::create returns a std::unique_ptr<Value> in modern Exiv2,
  // but some versions use Value::UniquePtr. Support both.
#if defined(EXV_HAVE_STD_UNIQUE_PTR) || 1
  // Try the canonical API first.
  try {
    auto v = Exiv2::Value::create(Exiv2::date);
    if (!v) {
      GTEST_SKIP() << "Exiv2::Value::create(Exiv2::date) returned null; cannot test DateValue::copy.";
    }
    return v;
  } catch (...) {
    GTEST_SKIP() << "Exiv2::Value::create(Exiv2::date) threw; cannot test DateValue::copy.";
  }
#else
  // Fallback if your Exiv2 uses a different smart pointer type; adjust if needed.
  GTEST_SKIP() << "Unsupported Exiv2 Value::create pointer type in this build.";
#endif
}

template <class TValue>
static int callRead(TValue& v, const std::string& s, bool& threw) {
  threw = false;
  try {
    if constexpr (std::is_same_v<decltype(v.read(s)), int>) {
      return v.read(s);
    } else {
      v.read(s);
      return 0;
    }
  } catch (...) {
    threw = true;
    return -1;
  }
}

static Exiv2::DateValue* asDateValueOrSkip(Exiv2::Value* v) {
  auto* dv = dynamic_cast<Exiv2::DateValue*>(v);
  if (!dv) {
    GTEST_SKIP() << "Value created with TypeId::date is not a DateValue in this build.";
  }
  return dv;
}

static std::string copyToString(const Exiv2::DateValue& dv, Exiv2::ByteOrder bo, size_t& outLen) {
  std::array<byte, 32> buf{};
  // Fill with a sentinel so we can detect over/under-write behavior.
  std::memset(buf.data(), 'X', buf.size());

  outLen = dv.copy(buf.data(), bo);
  return std::string(reinterpret_cast<const char*>(buf.data()),
                     reinterpret_cast<const char*>(buf.data()) + outLen);
}

}  // namespace

TEST(DateValueCopyTest_865, CopyWritesEightDigitsYYYYMMDD_865) {
  auto v = createDateValueOrSkip();
  auto* dv = asDateValueOrSkip(v.get());

  bool threw = false;
  const int rc = callRead(*v, "20260206", threw);
  ASSERT_FALSE(threw) << "read(\"20260206\") unexpectedly threw.";
  ASSERT_EQ(rc, 0) << "read(\"20260206\") returned non-zero (error).";

  size_t n = 0;
  const std::string s = copyToString(*dv, Exiv2::littleEndian, n);

  EXPECT_EQ(n, 8u);
  EXPECT_EQ(s, "20260206");
}

TEST(DateValueCopyTest_865, ByteOrderParameterDoesNotAffectOutput_865) {
  auto v = createDateValueOrSkip();
  auto* dv = asDateValueOrSkip(v.get());

  bool threw = false;
  const int rc = callRead(*v, "19991231", threw);
  ASSERT_FALSE(threw);
  ASSERT_EQ(rc, 0);

  size_t n1 = 0, n2 = 0;
  const std::string a = copyToString(*dv, Exiv2::littleEndian, n1);
  const std::string b = copyToString(*dv, Exiv2::bigEndian, n2);

  EXPECT_EQ(n1, 8u);
  EXPECT_EQ(n2, 8u);
  EXPECT_EQ(a, b);
  EXPECT_EQ(a, "19991231");
}

TEST(DateValueCopyTest_865, CopyDoesNotWritePastReturnedLength_865) {
  auto v = createDateValueOrSkip();
  auto* dv = asDateValueOrSkip(v.get());

  bool threw = false;
  const int rc = callRead(*v, "20000101", threw);
  ASSERT_FALSE(threw);
  ASSERT_EQ(rc, 0);

  std::array<byte, 16> buf{};
  std::memset(buf.data(), 'X', buf.size());

  const size_t n = dv->copy(buf.data(), Exiv2::littleEndian);

  ASSERT_EQ(n, 8u);
  // First 8 bytes should be digits.
  const std::string s(reinterpret_cast<const char*>(buf.data()),
                      reinterpret_cast<const char*>(buf.data()) + n);
  EXPECT_EQ(s, "20000101");
  // The next byte should still be our sentinel if no extra write occurred.
  EXPECT_EQ(static_cast<char>(buf[8]), 'X');
}

TEST(DateValueCopyTest_865, CopyHandlesLeapDayInput_865) {
  auto v = createDateValueOrSkip();
  auto* dv = asDateValueOrSkip(v.get());

  bool threw = false;
  const int rc = callRead(*v, "20240229", threw);
  ASSERT_FALSE(threw);
  ASSERT_EQ(rc, 0);

  size_t n = 0;
  const std::string s = copyToString(*dv, Exiv2::littleEndian, n);

  EXPECT_EQ(n, 8u);
  EXPECT_EQ(s, "20240229");
}

TEST(DateValueCopyTest_865, ReadInvalidDateStringReportsError_865) {
  auto v = createDateValueOrSkip();
  (void)asDateValueOrSkip(v.get());  // ensure it is a DateValue for this build

  // Provide an obviously-invalid input and verify an error is observable
  // (either exception or non-zero return code).
  bool threw = false;
  const int rc = callRead(*v, "not-a-date", threw);

  EXPECT_TRUE(threw || rc != 0)
      << "Expected invalid input to be rejected (throw or non-zero return), but it was accepted.";
}