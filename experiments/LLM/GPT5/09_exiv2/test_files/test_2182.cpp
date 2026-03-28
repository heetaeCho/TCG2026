// =================================================================================================
// Test file for Exiv2::ExifKey (constructor: ExifKey(const TagInfo&))
// File under test: ./TestProjects/exiv2/src/tags.cpp
// TEST_ID: 2182
// =================================================================================================

#include <gtest/gtest.h>

#include <cstdint>
#include <string>
#include <type_traits>

#include <exiv2/error.hpp>
#include <exiv2/ifd.hpp>
#include <exiv2/tags.hpp>

namespace {

// ---- Small helpers to optionally validate Exiv2::Error::code() if that API exists ----
template <typename T, typename = void>
struct HasCodeMethod : std::false_type {};
template <typename T>
struct HasCodeMethod<T, std::void_t<decltype(std::declval<const T&>().code())>> : std::true_type {};

template <typename ErrorT>
void ExpectErrorCodeIfAvailable(const ErrorT& err, Exiv2::ErrorCode expected) {
  if constexpr (HasCodeMethod<ErrorT>::value) {
    EXPECT_EQ(err.code(), expected);
  } else {
    (void)err;
    (void)expected;
    SUCCEED();
  }
}

// If Exiv2::groupName(IfdId) exists (it should), prefer comparing to it.
// We avoid hard dependency on its signature beyond being callable.
inline std::string GroupNameOf(Exiv2::IfdId ifd) {
  return Exiv2::groupName(ifd);
}

// Build a TagInfo that is valid for ExifKey(const TagInfo&).
// We only set the fields that are referenced by the provided implementation (tag_, ifdId_).
inline Exiv2::TagInfo MakeTagInfo(Exiv2::IfdId ifd, uint16_t tag) {
  Exiv2::TagInfo ti{};
  ti.ifdId_ = ifd;
  ti.tag_ = tag;
  return ti;
}

class ExifKey_TagInfoCtorTest_2182 : public ::testing::Test {};

}  // namespace

TEST_F(ExifKey_TagInfoCtorTest_2182, ThrowsForInvalidIfdId_2182) {
  // The constructor explicitly rejects IFDs that are neither Exif IFDs nor MakerNote IFDs.
  const auto ti = MakeTagInfo(Exiv2::IfdId::ifdIdNotSet, /*tag=*/0x010F);

  try {
    (void)Exiv2::ExifKey(ti);
    FAIL() << "Expected Exiv2::Error to be thrown for invalid IFD id";
  } catch (const Exiv2::Error& e) {
    ExpectErrorCodeIfAvailable(e, Exiv2::ErrorCode::kerInvalidIfdId);
  }
}

TEST_F(ExifKey_TagInfoCtorTest_2182, ConstructsAndExposesBasicPropertiesForExifIfd_2182) {
  // Use a well-known EXIF IFD (IFD0 is expected to be an Exif IFD).
  const auto ti = MakeTagInfo(Exiv2::IfdId::ifd0Id, /*tag=*/0x010F);

  Exiv2::ExifKey key(ti);

  EXPECT_EQ(key.ifdId(), Exiv2::IfdId::ifd0Id);
  EXPECT_EQ(key.tag(), 0x010F);
  EXPECT_EQ(key.groupName(), GroupNameOf(Exiv2::IfdId::ifd0Id));

  // key() should produce a stable, non-empty key string.
  EXPECT_FALSE(key.key().empty());
  // familyName() should be non-null and non-empty for a valid key.
  ASSERT_NE(key.familyName(), nullptr);
  EXPECT_NE(std::string(key.familyName()), std::string());
}

TEST_F(ExifKey_TagInfoCtorTest_2182, SupportsBoundaryTagsForValidIfd_2182) {
  // Boundary-ish tags (0 and max uint16_t). We only verify construction and observables.
  {
    const auto ti0 = MakeTagInfo(Exiv2::IfdId::ifd0Id, /*tag=*/0u);
    Exiv2::ExifKey key0(ti0);
    EXPECT_EQ(key0.ifdId(), Exiv2::IfdId::ifd0Id);
    EXPECT_EQ(key0.tag(), 0u);
    EXPECT_FALSE(key0.key().empty());
  }
  {
    const auto timax = MakeTagInfo(Exiv2::IfdId::ifd0Id, /*tag=*/0xFFFFu);
    Exiv2::ExifKey keymax(timax);
    EXPECT_EQ(keymax.ifdId(), Exiv2::IfdId::ifd0Id);
    EXPECT_EQ(keymax.tag(), 0xFFFFu);
    EXPECT_FALSE(keymax.key().empty());
  }
}

TEST_F(ExifKey_TagInfoCtorTest_2182, CloneProducesEquivalentKeyStringAndProperties_2182) {
  const auto ti = MakeTagInfo(Exiv2::IfdId::ifd0Id, /*tag=*/0x0132);
  Exiv2::ExifKey key(ti);

  auto cloned = key.clone();
  ASSERT_TRUE(cloned);

  EXPECT_EQ(cloned->key(), key.key());
  EXPECT_EQ(cloned->groupName(), key.groupName());
  EXPECT_EQ(cloned->tag(), key.tag());
  EXPECT_EQ(cloned->tagName(), key.tagName());
}

TEST_F(ExifKey_TagInfoCtorTest_2182, CopyConstructionPreservesObservableProperties_2182) {
  const auto ti = MakeTagInfo(Exiv2::IfdId::ifd0Id, /*tag=*/0x9003);
  Exiv2::ExifKey original(ti);

  Exiv2::ExifKey copy(original);

  EXPECT_EQ(copy.key(), original.key());
  EXPECT_EQ(copy.groupName(), original.groupName());
  EXPECT_EQ(copy.ifdId(), original.ifdId());
  EXPECT_EQ(copy.tag(), original.tag());
  EXPECT_EQ(copy.tagName(), original.tagName());
}

TEST_F(ExifKey_TagInfoCtorTest_2182, AssignmentPreservesObservableProperties_2182) {
  const auto tiA = MakeTagInfo(Exiv2::IfdId::ifd0Id, /*tag=*/0x829A);
  const auto tiB = MakeTagInfo(Exiv2::IfdId::ifd0Id, /*tag=*/0x829D);

  Exiv2::ExifKey a(tiA);
  Exiv2::ExifKey b(tiB);

  const std::string aKeyBefore = a.key();
  const std::string bKeyBefore = b.key();
  ASSERT_NE(aKeyBefore, bKeyBefore);  // sanity for the test intent (different tags)

  b = a;

  EXPECT_EQ(b.key(), a.key());
  EXPECT_EQ(b.groupName(), a.groupName());
  EXPECT_EQ(b.ifdId(), a.ifdId());
  EXPECT_EQ(b.tag(), a.tag());
  EXPECT_EQ(b.tagName(), a.tagName());
}