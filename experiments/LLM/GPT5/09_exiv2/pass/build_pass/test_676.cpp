// =================================================================================================
// TestProjects/exiv2/src/iptc_test_typeSize_676.cpp
// Unit tests for Exiv2::Iptcdatum::typeSize()
// =================================================================================================

#include <gtest/gtest.h>

#include <exiv2/iptc.hpp>
#include <exiv2/types.hpp>

namespace {

class IptcdatumTypeSizeTest_676 : public ::testing::Test {
 protected:
  static Exiv2::IptcKey MakeKey() {
    // Use a well-known IPTC dataset key string (commonly supported by Exiv2).
    return Exiv2::IptcKey("Iptc.Application2.ObjectName");
  }
};

TEST_F(IptcdatumTypeSizeTest_676, TypeSizeMatchesTypeInfoForDefaultConstructedValue_676) {
  const auto key = MakeKey();

  // Constructor takes a Value*; pass nullptr to avoid assuming any particular Value implementation.
  Exiv2::Iptcdatum datum(key, /*pValue=*/nullptr);

  // Black-box invariant from implementation: typeSize() delegates to TypeInfo::typeSize(typeId()).
  EXPECT_EQ(datum.typeSize(), Exiv2::TypeInfo::typeSize(datum.typeId()));
}

TEST_F(IptcdatumTypeSizeTest_676, TypeSizeMatchesTypeInfoAfterAssigningString_676) {
  const auto key = MakeKey();
  Exiv2::Iptcdatum datum(key, /*pValue=*/nullptr);

  ASSERT_NO_THROW({
    datum = std::string("abc");
  });

  EXPECT_EQ(datum.typeSize(), Exiv2::TypeInfo::typeSize(datum.typeId()));
}

TEST_F(IptcdatumTypeSizeTest_676, TypeSizeMatchesTypeInfoAfterAssigningEmptyString_676) {
  const auto key = MakeKey();
  Exiv2::Iptcdatum datum(key, /*pValue=*/nullptr);

  ASSERT_NO_THROW({
    datum = std::string();
  });

  EXPECT_EQ(datum.typeSize(), Exiv2::TypeInfo::typeSize(datum.typeId()));
}

TEST_F(IptcdatumTypeSizeTest_676, TypeSizeMatchesTypeInfoAfterAssigningUInt16_676) {
  const auto key = MakeKey();
  Exiv2::Iptcdatum datum(key, /*pValue=*/nullptr);

  ASSERT_NO_THROW({
    const uint16_t v = 42;
    datum = v;
  });

  EXPECT_EQ(datum.typeSize(), Exiv2::TypeInfo::typeSize(datum.typeId()));
}

TEST_F(IptcdatumTypeSizeTest_676, TypeSizeMatchesTypeInfoAfterMultipleAssignments_676) {
  const auto key = MakeKey();
  Exiv2::Iptcdatum datum(key, /*pValue=*/nullptr);

  ASSERT_NO_THROW({ datum = std::string("first"); });
  EXPECT_EQ(datum.typeSize(), Exiv2::TypeInfo::typeSize(datum.typeId()));

  ASSERT_NO_THROW({
    const uint16_t v = 7;
    datum = v;
  });
  EXPECT_EQ(datum.typeSize(), Exiv2::TypeInfo::typeSize(datum.typeId()));

  ASSERT_NO_THROW({ datum = std::string("second"); });
  EXPECT_EQ(datum.typeSize(), Exiv2::TypeInfo::typeSize(datum.typeId()));
}

TEST_F(IptcdatumTypeSizeTest_676, TypeSizeCallIsStableAcrossRepeatedCalls_676) {
  const auto key = MakeKey();
  Exiv2::Iptcdatum datum(key, /*pValue=*/nullptr);

  const size_t s1 = datum.typeSize();
  const size_t s2 = datum.typeSize();
  const size_t s3 = datum.typeSize();

  EXPECT_EQ(s1, s2);
  EXPECT_EQ(s2, s3);
  EXPECT_EQ(s1, Exiv2::TypeInfo::typeSize(datum.typeId()));
}

TEST_F(IptcdatumTypeSizeTest_676, TypeSizeMatchesTypeInfoAfterSetValueStringWithReturnCode_676) {
  const auto key = MakeKey();
  Exiv2::Iptcdatum datum(key, /*pValue=*/nullptr);

  int rc = 0;
  EXPECT_NO_THROW({
    rc = datum.setValue(std::string("via-setValue"));
  });

  // We don't assume any specific meaning for rc; we only verify observable consistency of typeSize().
  (void)rc;
  EXPECT_EQ(datum.typeSize(), Exiv2::TypeInfo::typeSize(datum.typeId()));
}

TEST_F(IptcdatumTypeSizeTest_676, TypeSizeMatchesTypeInfoAfterLargeStringAssignmentBoundary_676) {
  const auto key = MakeKey();
  Exiv2::Iptcdatum datum(key, /*pValue=*/nullptr);

  std::string big(64 * 1024, 'x');  // boundary-ish: large payload
  ASSERT_NO_THROW({
    datum = big;
  });

  EXPECT_EQ(datum.typeSize(), Exiv2::TypeInfo::typeSize(datum.typeId()));
}

}  // namespace