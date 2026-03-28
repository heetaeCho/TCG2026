// File: test_iptcdatum_typeid_674.cpp
// TEST_ID: 674

#include <gtest/gtest.h>

#include <exiv2/iptc.hpp>
#include <exiv2/value.hpp>
#include <exiv2/types.hpp>

namespace {

Exiv2::IptcKey MakeAnyIptcKey() {
  // Use a commonly valid IPTC key string in Exiv2.
  // (Tests rely only on public constructors; no internal behavior is assumed.)
  return Exiv2::IptcKey("Iptc.Application2.ObjectName");
}

}  // namespace

class IptcdatumTest_674 : public ::testing::Test {
 protected:
  Exiv2::IptcKey key_{MakeAnyIptcKey()};
};

TEST_F(IptcdatumTest_674, TypeIdReturnsInvalidWhenConstructedWithNullValue_674) {
  ASSERT_NO_THROW({
    Exiv2::Iptcdatum d(key_, nullptr);
    EXPECT_EQ(Exiv2::invalidTypeId, d.typeId());
  });
}

TEST_F(IptcdatumTest_674, TypeIdMatchesValueTypeWhenConstructedWithNonNullValue_674) {
  auto v = Exiv2::Value::create(Exiv2::asciiString);
  ASSERT_NE(nullptr, v.get());

  Exiv2::Iptcdatum d(key_, v.get());
  EXPECT_EQ(Exiv2::asciiString, d.typeId());
}

TEST_F(IptcdatumTest_674, TypeIdBecomesInvalidAfterSetValueNull_674) {
  auto v = Exiv2::Value::create(Exiv2::unsignedShort);
  ASSERT_NE(nullptr, v.get());

  Exiv2::Iptcdatum d(key_, v.get());
  ASSERT_EQ(Exiv2::unsignedShort, d.typeId());

  ASSERT_NO_THROW(d.setValue(nullptr));
  EXPECT_EQ(Exiv2::invalidTypeId, d.typeId());
}

TEST_F(IptcdatumTest_674, TypeIdReflectsLatestSetValue_674) {
  Exiv2::Iptcdatum d(key_, nullptr);
  EXPECT_EQ(Exiv2::invalidTypeId, d.typeId());

  auto v1 = Exiv2::Value::create(Exiv2::unsignedLong);
  ASSERT_NE(nullptr, v1.get());
  ASSERT_NO_THROW(d.setValue(v1.get()));
  EXPECT_EQ(Exiv2::unsignedLong, d.typeId());

  auto v2 = Exiv2::Value::create(Exiv2::tiffDouble);
  ASSERT_NE(nullptr, v2.get());
  ASSERT_NO_THROW(d.setValue(v2.get()));
  EXPECT_EQ(Exiv2::tiffDouble, d.typeId());
}

TEST_F(IptcdatumTest_674, CopyConstructionPreservesTypeId_674) {
  auto v = Exiv2::Value::create(Exiv2::signedLongLong);
  ASSERT_NE(nullptr, v.get());

  Exiv2::Iptcdatum original(key_, v.get());
  ASSERT_EQ(Exiv2::signedLongLong, original.typeId());

  Exiv2::Iptcdatum copy(original);
  EXPECT_EQ(original.typeId(), copy.typeId());
}

TEST_F(IptcdatumTest_674, CopyAssignmentPreservesTypeId_674) {
  auto v1 = Exiv2::Value::create(Exiv2::unsignedRational);
  ASSERT_NE(nullptr, v1.get());
  Exiv2::Iptcdatum a(key_, v1.get());
  ASSERT_EQ(Exiv2::unsignedRational, a.typeId());

  Exiv2::Iptcdatum b(key_, nullptr);
  ASSERT_EQ(Exiv2::invalidTypeId, b.typeId());

  b = a;
  EXPECT_EQ(a.typeId(), b.typeId());
}

TEST_F(IptcdatumTest_674, TypeIdDoesNotThrowAcrossTransitions_674) {
  Exiv2::Iptcdatum d(key_, nullptr);
  EXPECT_NO_THROW((void)d.typeId());

  auto v = Exiv2::Value::create(Exiv2::date);
  ASSERT_NE(nullptr, v.get());

  EXPECT_NO_THROW(d.setValue(v.get()));
  EXPECT_NO_THROW((void)d.typeId());

  EXPECT_NO_THROW(d.setValue(nullptr));
  EXPECT_NO_THROW((void)d.typeId());
}