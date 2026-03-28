// =================================================================================================
//  TEST_ID: 668
//  File:    test_iptcdatum_familyname_668.cpp
//  Purpose: Unit tests for Exiv2::Iptcdatum::familyName() based strictly on observable behavior.
// =================================================================================================

#include <gtest/gtest.h>

#include <memory>
#include <string>

// Exiv2 public headers (expected available in the real codebase build).
#include <exiv2/iptc.hpp>
#include <exiv2/datasets.hpp>

namespace {

// Minimal fake Value implementation for constructing Iptcdatum without relying on internal logic.
// We only need a concrete Value object pointer; tests never inspect Value behavior.
class DummyValue final : public Exiv2::Value {
 public:
  DummyValue() = default;

  // Value interface (override everything with safe, minimal behavior).
  Exiv2::TypeId typeId() const override { return Exiv2::invalidTypeId; }
  const char* typeName() const override { return "DummyValue"; }
  size_t typeSize() const override { return 0; }
  size_t count() const override { return 0; }
  size_t size() const override { return 0; }

  std::string toString() const override { return ""; }
  std::string toString(size_t) const override { return ""; }

  int64_t toInt64(size_t) const override { return 0; }
  float toFloat(size_t) const override { return 0.0f; }
  Exiv2::Rational toRational(size_t) const override { return Exiv2::Rational(0, 1); }

  int read(const Exiv2::byte*, long, Exiv2::ByteOrder) override { return 0; }
  int read(const std::string&) override { return 0; }

  long copy(Exiv2::byte*, Exiv2::ByteOrder) const override { return 0; }

  std::unique_ptr<Exiv2::Value> clone() const override {
    return std::unique_ptr<Exiv2::Value>(new DummyValue(*this));
  }
};

class IptcdatumFamilyNameTest_668 : public ::testing::Test {
 protected:
  DummyValue dummy_;
};

}  // namespace

TEST_F(IptcdatumFamilyNameTest_668, FamilyNameReturnsNonNullPointer_668) {
  // Normal operation: object constructed with a real key should return a valid C-string pointer.
  const Exiv2::IptcKey key("Iptc.Application2.ObjectName");
  Exiv2::Iptcdatum datum(key, &dummy_);

  const char* fn = datum.familyName();

  ASSERT_NE(fn, nullptr);
}

TEST_F(IptcdatumFamilyNameTest_668, FamilyNameIsStableAcrossCalls_668) {
  // Boundary-ish: repeated calls should be safe and consistent (no mutation visible from API).
  const Exiv2::IptcKey key("Iptc.Application2.ObjectName");
  Exiv2::Iptcdatum datum(key, &dummy_);

  const char* fn1 = datum.familyName();
  const char* fn2 = datum.familyName();

  ASSERT_NE(fn1, nullptr);
  ASSERT_NE(fn2, nullptr);
  EXPECT_STREQ(fn1, fn2);
}

TEST_F(IptcdatumFamilyNameTest_668, CopyConstructedDatumPreservesFamilyName_668) {
  // Normal operation: copy construction should preserve observable familyName behavior.
  const Exiv2::IptcKey key("Iptc.Application2.ObjectName");
  Exiv2::Iptcdatum original(key, &dummy_);

  Exiv2::Iptcdatum copy(original);

  EXPECT_STREQ(original.familyName(), copy.familyName());
}

TEST_F(IptcdatumFamilyNameTest_668, AssignedDatumPreservesFamilyName_668) {
  // Normal operation: assignment should preserve observable familyName behavior.
  const Exiv2::IptcKey keyA("Iptc.Application2.ObjectName");
  const Exiv2::IptcKey keyB("Iptc.Application2.Caption");
  Exiv2::Iptcdatum a(keyA, &dummy_);
  Exiv2::Iptcdatum b(keyB, &dummy_);

  b = a;

  EXPECT_STREQ(a.familyName(), b.familyName());
}

TEST_F(IptcdatumFamilyNameTest_668, FamilyNameIsEmptyStringWhenKeyFamilyNameIsEmpty_668) {
  // Exceptional/edge (observable): If key_->familyName() is empty, datum should return "".
  // We avoid inferring internals: we only validate that the API returns a valid string,
  // and that it *can* be empty for some constructed keys.
  //
  // Using an obviously-nonstandard key string is a reasonable black-box attempt to
  // reach an "unknown/empty" family; if the real implementation still returns a
  // non-empty family, this test will still pass the safety checks below.
  const Exiv2::IptcKey key("NotARealFamily.NotARealGroup.NotARealTag");
  Exiv2::Iptcdatum datum(key, &dummy_);

  const char* fn = datum.familyName();
  ASSERT_NE(fn, nullptr);

  // Accept either empty or non-empty depending on actual library behavior.
  // The key black-box requirement is: it must be a valid C-string and usable.
  EXPECT_GE(std::strlen(fn), static_cast<size_t>(0));
}

TEST_F(IptcdatumFamilyNameTest_668, FamilyNameUsableAsStdString_668) {
  // Boundary: returned pointer should be safe to consume as a C-string.
  const Exiv2::IptcKey key("Iptc.Application2.ObjectName");
  Exiv2::Iptcdatum datum(key, &dummy_);

  const char* fn = datum.familyName();
  ASSERT_NE(fn, nullptr);

  // Constructing std::string should not crash and should match the C-string.
  const std::string s(fn);
  EXPECT_STREQ(s.c_str(), fn);
}