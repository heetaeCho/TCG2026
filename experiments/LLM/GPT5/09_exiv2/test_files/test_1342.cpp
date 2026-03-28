// File: test_tags_defaultTypeId_1342.cpp
// TEST_ID: 1342

#include <gtest/gtest.h>

#include <cstdint>
#include <string>

#include <exiv2/tags.hpp>

namespace {

// Keep TagInfo objects alive for the duration of the tests (in case ExifKey stores pointers).
static const Exiv2::TagInfo kTagInfoAscii{
    /*sectionId_=*/ Exiv2::SectionId::sectionIdNotSet,
    /*typeId_=*/ Exiv2::asciiString,
    /*count_=*/ 1,
    /*printFct_=*/ nullptr,
};

static const Exiv2::TagInfo kTagInfoULong{
    /*sectionId_=*/ Exiv2::SectionId::sectionIdNotSet,
    /*typeId_=*/ Exiv2::unsignedLong,
    /*count_=*/ 1,
    /*printFct_=*/ nullptr,
};

class ExifKeyTest_1342 : public ::testing::Test {};

}  // namespace

TEST_F(ExifKeyTest_1342, DefaultTypeId_ReturnsTagInfoType_WhenConstructedFromTagInfo_1342) {
  const Exiv2::ExifKey keyFromTi(kTagInfoAscii);
  EXPECT_EQ(keyFromTi.defaultTypeId(), kTagInfoAscii.typeId_);
}

TEST_F(ExifKeyTest_1342, DefaultTypeId_ReturnsDifferentType_ForDifferentTagInfo_1342) {
  const Exiv2::ExifKey keyA(kTagInfoAscii);
  const Exiv2::ExifKey keyB(kTagInfoULong);

  EXPECT_EQ(keyA.defaultTypeId(), kTagInfoAscii.typeId_);
  EXPECT_EQ(keyB.defaultTypeId(), kTagInfoULong.typeId_);
  EXPECT_NE(keyA.defaultTypeId(), keyB.defaultTypeId());
}

TEST_F(ExifKeyTest_1342, DefaultTypeId_ForLikelyUnknownKey_MatchesUnknownTagDefault_1342) {
  // Reference "unknown default" via the public API by constructing from Internal::unknownTag.
  // This avoids depending on unknownTag's internal fields in assertions.
  const Exiv2::ExifKey unknownKeyFromInternal(Exiv2::Internal::unknownTag);
  const Exiv2::TypeId unknownDefault = unknownKeyFromInternal.defaultTypeId();

  // Use an unlikely group name to exercise the branch where tagInfo_ is not set (if observable).
  const Exiv2::ExifKey likelyUnknownKey(/*tag=*/static_cast<uint16_t>(0xFFFF),
                                       /*groupName=*/"ThisGroupShouldNotExist_ExifKeyTest_1342");

  EXPECT_EQ(likelyUnknownKey.defaultTypeId(), unknownDefault);
}

TEST_F(ExifKeyTest_1342, DefaultTypeId_IsPreserved_ByCopyConstruction_1342) {
  const Exiv2::ExifKey original(kTagInfoULong);
  const Exiv2::ExifKey copy(original);

  EXPECT_EQ(copy.defaultTypeId(), original.defaultTypeId());
}

TEST_F(ExifKeyTest_1342, DefaultTypeId_IsPreserved_ByCopyAssignment_1342) {
  const Exiv2::ExifKey source(kTagInfoAscii);
  Exiv2::ExifKey target(kTagInfoULong);

  // Sanity: different before assignment (observable via defaultTypeId).
  EXPECT_NE(target.defaultTypeId(), source.defaultTypeId());

  target = source;
  EXPECT_EQ(target.defaultTypeId(), source.defaultTypeId());
}

TEST_F(ExifKeyTest_1342, DefaultTypeId_IsStable_AcrossMultipleCalls_1342) {
  const Exiv2::ExifKey key(kTagInfoAscii);

  const Exiv2::TypeId first = key.defaultTypeId();
  const Exiv2::TypeId second = key.defaultTypeId();
  const Exiv2::TypeId third = key.defaultTypeId();

  EXPECT_EQ(first, second);
  EXPECT_EQ(second, third);
}