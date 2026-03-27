// File: test_iptcdatum_key_665.cpp
// TEST_ID: 665

#include <gtest/gtest.h>

#include <exiv2/iptc.hpp>
#include <exiv2/value.hpp>

#include <memory>
#include <string>

namespace {

// Keep the fixture name consistent with the TEST_ID requirement.
class IptcdatumTest_665 : public ::testing::Test {
protected:
  static std::unique_ptr<Exiv2::Value> MakeAsciiValue(const std::string& s) {
    // Use a common, stable Value type for IPTC string-like payloads.
    Exiv2::Value::UniquePtr v = Exiv2::Value::create(Exiv2::asciiString);
    if (v.get() != nullptr) {
      (void)v->read(s);
    }
    return std::unique_ptr<Exiv2::Value>(v.release());
  }
};

}  // namespace

TEST_F(IptcdatumTest_665, KeyMatchesProvidedIptcKey_WithNullValue_665) {
  // Arrange
  const Exiv2::IptcKey k("Iptc.Application2.Caption");

  // Act
  Exiv2::Iptcdatum d(k, nullptr);

  // Assert
  EXPECT_EQ(d.key(), k.key());
  EXPECT_FALSE(d.key().empty());
}

TEST_F(IptcdatumTest_665, KeyMatchesProvidedIptcKey_WithConcreteValue_665) {
  // Arrange
  const Exiv2::IptcKey k("Iptc.Application2.Headline");
  auto v = MakeAsciiValue("hello");

  // Act
  Exiv2::Iptcdatum d(k, v.get());

  // Assert
  EXPECT_EQ(d.key(), k.key());
  EXPECT_FALSE(d.key().empty());
}

TEST_F(IptcdatumTest_665, KeyIsStableAcrossCopyConstruction_665) {
  // Arrange
  const Exiv2::IptcKey k("Iptc.Application2.Byline");
  auto v = MakeAsciiValue("author");
  Exiv2::Iptcdatum original(k, v.get());

  // Act
  Exiv2::Iptcdatum copy(original);

  // Assert
  EXPECT_EQ(copy.key(), original.key());
  EXPECT_EQ(copy.key(), k.key());
}

TEST_F(IptcdatumTest_665, KeyIsStableAcrossCopyAssignment_665) {
  // Arrange
  const Exiv2::IptcKey k1("Iptc.Application2.City");
  const Exiv2::IptcKey k2("Iptc.Application2.CountryName");
  auto v1 = MakeAsciiValue("Seoul");
  auto v2 = MakeAsciiValue("Korea");

  Exiv2::Iptcdatum a(k1, v1.get());
  Exiv2::Iptcdatum b(k2, v2.get());

  // Pre-check
  EXPECT_EQ(a.key(), k1.key());
  EXPECT_EQ(b.key(), k2.key());

  // Act
  b = a;

  // Assert
  EXPECT_EQ(b.key(), a.key());
  EXPECT_EQ(b.key(), k1.key());
}

TEST_F(IptcdatumTest_665, KeyWithEmptyStringKeyInput_IsConsistentWithIptcKeyKey_665) {
  // Boundary: empty textual key input.
  const Exiv2::IptcKey emptyKey(std::string());

  // Construct with nullptr value (should be acceptable for metadata without payload in many cases).
  Exiv2::Iptcdatum d(emptyKey, nullptr);

  // We only assert consistency with the observable IptcKey::key() result.
  EXPECT_EQ(d.key(), emptyKey.key());
}

TEST_F(IptcdatumTest_665, KeyDoesNotChangeAfterSettingValueFromString_665) {
  // Arrange
  const Exiv2::IptcKey k("Iptc.Application2.ObjectName");
  Exiv2::Iptcdatum d(k, nullptr);
  const std::string before = d.key();

  // Act
  // setValue(string) returns int; we don't assume specific return codes here, only that key() is unaffected.
  (void)d.setValue(std::string("obj"));

  // Assert
  EXPECT_EQ(d.key(), before);
  EXPECT_EQ(d.key(), k.key());
}