#include <gtest/gtest.h>
#include "exiv2/value.hpp"
#include "exiv2/types.hpp"

namespace {

TEST(GetTypeUint16Test_136, ReturnsUnsignedShort_136) {
  Exiv2::TypeId result = Exiv2::getType<uint16_t>();
  EXPECT_EQ(result, Exiv2::unsignedShort);
}

TEST(GetTypeUint16Test_136, ReturnsCorrectEnumValue_136) {
  Exiv2::TypeId result = Exiv2::getType<uint16_t>();
  EXPECT_EQ(static_cast<int>(result), 3);
}

TEST(GetTypeUint16Test_136, IsNotOtherType_136) {
  Exiv2::TypeId result = Exiv2::getType<uint16_t>();
  EXPECT_NE(result, Exiv2::unsignedByte);
  EXPECT_NE(result, Exiv2::unsignedLong);
  EXPECT_NE(result, Exiv2::signedShort);
  EXPECT_NE(result, Exiv2::invalidTypeId);
  EXPECT_NE(result, Exiv2::undefined);
  EXPECT_NE(result, Exiv2::asciiString);
}

TEST(GetTypeUint16Test_136, ConsistentAcrossMultipleCalls_136) {
  Exiv2::TypeId result1 = Exiv2::getType<uint16_t>();
  Exiv2::TypeId result2 = Exiv2::getType<uint16_t>();
  EXPECT_EQ(result1, result2);
}

}  // namespace
