// SPDX-License-Identifier: GPL-2.0-or-later
// File: test_xmparrayvalue_2169.cpp

#include <gtest/gtest.h>

#include <exiv2/value.hpp>

#include <cstdint>
#include <sstream>
#include <vector>

namespace {

class XmpArrayValueTest_2169 : public ::testing::Test {};

TEST_F(XmpArrayValueTest_2169, ConstructorDoesNotThrow_2169) {
  EXPECT_NO_THROW({
    const Exiv2::TypeId typeId = static_cast<Exiv2::TypeId>(0);
    Exiv2::XmpArrayValue v(typeId);
    (void)v;
  });
}

TEST_F(XmpArrayValueTest_2169, ConstructorSetsArrayTypeToMappingResult_2169) {
  // Black-box: verify the observable post-condition through the public accessor.
  // The ctor in value.cpp calls: setXmpArrayType(xmpArrayType(typeId)).
  const std::vector<Exiv2::TypeId> ids = {
      static_cast<Exiv2::TypeId>(0),
      static_cast<Exiv2::TypeId>(1),
      static_cast<Exiv2::TypeId>(2),
      static_cast<Exiv2::TypeId>(3),
      static_cast<Exiv2::TypeId>(10),
      static_cast<Exiv2::TypeId>(100),
      static_cast<Exiv2::TypeId>(1000),
  };

  for (const auto typeId : ids) {
    Exiv2::XmpArrayValue v(typeId);

    const Exiv2::XmpValue::XmpArrayType expected = Exiv2::XmpValue::xmpArrayType(typeId);
    EXPECT_EQ(v.xmpArrayType(), expected) << "typeId=" << static_cast<int>(typeId);
  }
}

TEST_F(XmpArrayValueTest_2169, ArrayTypeRemainsConsistentAfterEmptyRead_2169) {
  // Black-box: read() is public/virtual; we only check an observable invariant:
  // calling read("") should not change the array-type that ctor set.
  const Exiv2::TypeId typeId = static_cast<Exiv2::TypeId>(2);
  Exiv2::XmpArrayValue v(typeId);

  const Exiv2::XmpValue::XmpArrayType before = v.xmpArrayType();
  (void)v.read(std::string{});
  const Exiv2::XmpValue::XmpArrayType after = v.xmpArrayType();

  EXPECT_EQ(after, before);
}

TEST_F(XmpArrayValueTest_2169, ClonePreservesArrayType_2169) {
  const Exiv2::TypeId typeId = static_cast<Exiv2::TypeId>(3);
  Exiv2::XmpArrayValue v(typeId);

  const auto before = v.xmpArrayType();
  const auto cloned = v.clone();

  ASSERT_NE(cloned.get(), nullptr);

  // Only use public interface on the cloned object.
  // clone() returns a Value-like unique pointer; XmpValue accessors are public.
  const auto* asXmp = dynamic_cast<const Exiv2::XmpValue*>(cloned.get());
  ASSERT_NE(asXmp, nullptr);

  EXPECT_EQ(asXmp->xmpArrayType(), before);
}

TEST_F(XmpArrayValueTest_2169, WriteReturnsSameStreamAndDoesNotThrow_2169) {
  const Exiv2::TypeId typeId = static_cast<Exiv2::TypeId>(1);
  Exiv2::XmpArrayValue v(typeId);

  std::ostringstream oss;
  std::ostream* returned = nullptr;

  EXPECT_NO_THROW({
    std::ostream& ref = v.write(oss);
    returned = &ref;
  });

  EXPECT_EQ(returned, &oss);
}

TEST_F(XmpArrayValueTest_2169, CountIsNonNegativeAndStableAfterConstruction_2169) {
  // Boundary/robustness: count() is size_t; it must be >= 0 by type, but we also
  // ensure it's callable and stable for a fresh instance.
  const Exiv2::TypeId typeId = static_cast<Exiv2::TypeId>(0);
  Exiv2::XmpArrayValue v(typeId);

  const size_t c1 = v.count();
  const size_t c2 = v.count();

  EXPECT_EQ(c1, c2);
}

}  // namespace