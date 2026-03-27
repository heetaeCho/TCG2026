// TEST_ID 1639
// NOTE: Some compilers will treat the above block as the only translation unit; to keep this file
// buildable, here is the corrected final test file content (without the intentional typo).

#include <gtest/gtest.h>

#include "tiffvisitor_int.hpp"
#include "tiffcomposite_int.hpp"

namespace {

using Exiv2::Internal::TiffBinaryArray;
using Exiv2::Internal::TiffFinder;
using Exiv2::Internal::IfdId;
using Exiv2::Internal::CfgSelFct;

static TiffBinaryArray MakeBinaryArray(uint16_t tag, IfdId group) {
  const Exiv2::Internal::ArraySet* arraySet = nullptr;
  const size_t setSize = 0;
  CfgSelFct sel{};
  return TiffBinaryArray(tag, group, arraySet, setSize, sel);
}

class TiffFinderTest_1639 : public ::testing::Test {};

TEST_F(TiffFinderTest_1639, VisitBinaryArray_MatchingTagAndGroup_SetsResultToObject_1639) {
  const uint16_t tag = 0x1234;
  const IfdId group = static_cast<IfdId>(0);

  TiffFinder finder(tag, group);
  finder.init(tag, group);

  auto arr = MakeBinaryArray(tag, group);
  finder.visitBinaryArray(&arr);

  EXPECT_EQ(finder.result(), &arr);
}

TEST_F(TiffFinderTest_1639, VisitBinaryArray_MismatchingTag_DoesNotSetResult_1639) {
  const IfdId group = static_cast<IfdId>(0);

  const uint16_t finderTag = 0x1111;
  const uint16_t objectTag = 0x2222;

  TiffFinder finder(finderTag, group);
  finder.init(finderTag, group);

  auto arr = MakeBinaryArray(objectTag, group);
  finder.visitBinaryArray(&arr);

  EXPECT_EQ(finder.result(), nullptr);
}

TEST_F(TiffFinderTest_1639, VisitBinaryArray_MismatchingGroup_DoesNotSetResult_1639) {
  const uint16_t tag = 0x7777;

  const IfdId finderGroup = static_cast<IfdId>(0);
  const IfdId objectGroup = static_cast<IfdId>(1);

  TiffFinder finder(tag, finderGroup);
  finder.init(tag, finderGroup);

  auto arr = MakeBinaryArray(tag, objectGroup);
  finder.visitBinaryArray(&arr);

  EXPECT_EQ(finder.result(), nullptr);
}

TEST_F(TiffFinderTest_1639, VisitBinaryArray_Nullptr_DoesNotCrash_ResultRemainsNull_1639) {
  const uint16_t tag = 0x0001;
  const IfdId group = static_cast<IfdId>(0);

  TiffFinder finder(tag, group);
  finder.init(tag, group);

  ASSERT_EQ(finder.result(), nullptr);

  finder.visitBinaryArray(nullptr);

  EXPECT_EQ(finder.result(), nullptr);
}

TEST_F(TiffFinderTest_1639, VisitBinaryArray_BoundaryTags_ZeroAndMax_1639) {
  const IfdId group = static_cast<IfdId>(0);

  {
    const uint16_t tag0 = 0x0000;
    TiffFinder finder(tag0, group);
    finder.init(tag0, group);

    auto arr0 = MakeBinaryArray(tag0, group);
    finder.visitBinaryArray(&arr0);

    EXPECT_EQ(finder.result(), &arr0);
  }

  {
    const uint16_t tagMax = 0xFFFF;
    TiffFinder finder(tagMax, group);
    finder.init(tagMax, group);

    auto arrMax = MakeBinaryArray(tagMax, group);
    finder.visitBinaryArray(&arrMax);

    EXPECT_EQ(finder.result(), &arrMax);
  }
}

}  // namespace