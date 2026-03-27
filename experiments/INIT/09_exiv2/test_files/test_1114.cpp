// File: test_typeinfo_typesize_1114.cpp
// Tests for Exiv2::TypeInfo::typeSize(TypeId)
//
// TEST_ID: 1114

#include <gtest/gtest.h>

#include <cstddef>
#include <limits>
#include <string>

#include "exiv2/types.hpp"

namespace {

class TypeInfoTest_1114 : public ::testing::Test {};

// Parameterized coverage for the known TypeId -> size mappings (observable behavior).
struct TypeSizeCase {
  Exiv2::TypeId typeId;
  size_t expectedSize;
};

class TypeInfoTypeSizeParamTest_1114 : public ::testing::TestWithParam<TypeSizeCase> {};

TEST_P(TypeInfoTypeSizeParamTest_1114, ReturnsExpectedSizeForKnownTypeIds_1114) {
  const auto& tc = GetParam();

  // Static call form (as declared in types.hpp)
  EXPECT_EQ(Exiv2::TypeInfo::typeSize(tc.typeId), tc.expectedSize);

  // Instance call form (also observable via the interface; static members may be called through instances)
  Exiv2::TypeInfo ti;
  EXPECT_EQ(ti.typeSize(tc.typeId), tc.expectedSize);
}

INSTANTIATE_TEST_SUITE_P(
    KnownTypeSizes,
    TypeInfoTypeSizeParamTest_1114,
    ::testing::Values(
        TypeSizeCase{Exiv2::invalidTypeId, 0u},
        TypeSizeCase{Exiv2::unsignedByte, 1u},
        TypeSizeCase{Exiv2::asciiString, 1u},
        TypeSizeCase{Exiv2::unsignedShort, 2u},
        TypeSizeCase{Exiv2::unsignedLong, 4u},
        TypeSizeCase{Exiv2::unsignedRational, 8u},
        TypeSizeCase{Exiv2::signedByte, 1u},
        TypeSizeCase{Exiv2::undefined, 1u},
        TypeSizeCase{Exiv2::signedShort, 2u},
        TypeSizeCase{Exiv2::signedLong, 4u},
        TypeSizeCase{Exiv2::signedRational, 8u},
        TypeSizeCase{Exiv2::tiffFloat, 4u},
        TypeSizeCase{Exiv2::tiffDouble, 8u},
        TypeSizeCase{Exiv2::tiffIfd, 4u},
        TypeSizeCase{Exiv2::string, 1u},
        TypeSizeCase{Exiv2::date, 8u},
        TypeSizeCase{Exiv2::time, 11u},
        TypeSizeCase{Exiv2::comment, 1u},
        TypeSizeCase{Exiv2::directory, 1u},
        TypeSizeCase{Exiv2::xmpText, 1u},
        TypeSizeCase{Exiv2::xmpAlt, 1u},
        TypeSizeCase{Exiv2::xmpBag, 1u},
        TypeSizeCase{Exiv2::xmpSeq, 1u},
        TypeSizeCase{Exiv2::langAlt, 1u}));

TEST_F(TypeInfoTest_1114, ReturnsZeroForUnknownTypeId_1114) {
  // Boundary / error-like case: an ID not present in the table should return 0 (observable via interface).
  const auto unknown1 = static_cast<Exiv2::TypeId>(9999);
  const auto unknown2 = static_cast<Exiv2::TypeId>(-1);

  EXPECT_EQ(Exiv2::TypeInfo::typeSize(unknown1), 0u);
  EXPECT_EQ(Exiv2::TypeInfo::typeSize(unknown2), 0u);
}

TEST_F(TypeInfoTest_1114, IsDeterministicAcrossRepeatedCalls_1114) {
  // Normal operation: repeated calls for the same TypeId should produce the same observable result.
  const Exiv2::TypeId tid = Exiv2::unsignedRational;

  const auto first = Exiv2::TypeInfo::typeSize(tid);
  const auto second = Exiv2::TypeInfo::typeSize(tid);
  const auto third = Exiv2::TypeInfo::typeSize(tid);

  EXPECT_EQ(first, second);
  EXPECT_EQ(second, third);
}

TEST_F(TypeInfoTest_1114, DoesNotThrowForAnyTypeIdValue_1114) {
  // Exceptional/error case (observable): function should be safe for arbitrary enum values.
  // We assert "no throw" and that the return is a valid size_t.
  const auto extreme1 = static_cast<Exiv2::TypeId>(std::numeric_limits<int>::min());
  const auto extreme2 = static_cast<Exiv2::TypeId>(std::numeric_limits<int>::max());

  EXPECT_NO_THROW((void)Exiv2::TypeInfo::typeSize(extreme1));
  EXPECT_NO_THROW((void)Exiv2::TypeInfo::typeSize(extreme2));

  // If it doesn't match a known id, the contract observed in other tests is 0.
  // We don't assume internal logic beyond the observable behavior already covered.
  const auto s1 = Exiv2::TypeInfo::typeSize(extreme1);
  const auto s2 = Exiv2::TypeInfo::typeSize(extreme2);
  (void)s1;
  (void)s2;
}

}  // namespace