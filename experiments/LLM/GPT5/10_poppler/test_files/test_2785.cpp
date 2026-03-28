// StructElement_ContentData_test_2785.cpp

#include <gtest/gtest.h>

#include <climits>
#include <type_traits>

#include "StructElement.h"
#include "Object.h"

namespace {

using ContentData = StructElement::ContentData;

class StructElementContentDataTest_2785 : public ::testing::Test {};

TEST_F(StructElementContentDataTest_2785, ConstructibleFromRef_2785) {
  static_assert(std::is_constructible_v<ContentData, Ref>,
                "ContentData must be constructible from Ref (by value).");
  static_assert(std::is_constructible_v<ContentData, const Ref&>,
                "ContentData must be constructible from const Ref&.");
  SUCCEED();
}

TEST_F(StructElementContentDataTest_2785, RefConstructorIsExplicit_2785) {
  // `explicit ContentData(const Ref r);` => should NOT allow implicit conversion.
  static_assert(!std::is_convertible_v<Ref, ContentData>,
                "Ref -> ContentData must not be implicitly convertible (explicit ctor).");
  SUCCEED();
}

TEST_F(StructElementContentDataTest_2785, ConstructibleFromIntMcid_2785) {
  static_assert(std::is_constructible_v<ContentData, int>,
                "ContentData must be constructible from int (mcid).");
  SUCCEED();
}

TEST_F(StructElementContentDataTest_2785, IntConstructorIsExplicit_2785) {
  // `explicit ContentData(int mcidA)` => should NOT allow implicit conversion.
  static_assert(!std::is_convertible_v<int, ContentData>,
                "int -> ContentData must not be implicitly convertible (explicit ctor).");
  SUCCEED();
}

TEST_F(StructElementContentDataTest_2785, CanConstructWithInvalidRef_2785) {
  // Observable behavior: construction should be possible with a Ref value returned by INVALID().
  // Do not assume any specific INVALID() contents; just ensure construction compiles and runs.
  const Ref invalid = Ref::INVALID();
  ContentData cd(invalid);
  (void)cd;
  SUCCEED();
}

TEST_F(StructElementContentDataTest_2785, BoundaryRefValues_DoNotCrashOnConstruction_2785) {
  // Boundary-style inputs: extreme int values in Ref fields.
  Ref r1{INT_MAX, INT_MAX};
  Ref r2{INT_MIN, INT_MIN};
  Ref r3{INT_MAX, INT_MIN};

  ContentData c1(r1);
  ContentData c2(r2);
  ContentData c3(r3);

  (void)c1;
  (void)c2;
  (void)c3;
  SUCCEED();
}

TEST_F(StructElementContentDataTest_2785, BoundaryMcidValues_DoNotCrashOnConstruction_2785) {
  // Boundary-style inputs: extreme int values for mcid.
  ContentData c1(0);
  ContentData c2(INT_MAX);
  ContentData c3(INT_MIN);

  (void)c1;
  (void)c2;
  (void)c3;
  SUCCEED();
}

}  // namespace