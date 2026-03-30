// =================================================================================================
// TEST_ID: 1165
// File: test_tiffcreator_1165.cpp
//
// Unit tests for Exiv2::Internal::TiffCreator (black-box; interface/observable behavior only)
// =================================================================================================

#include <gtest/gtest.h>

#include "tiffimage_int.hpp"        // Exiv2::Internal::TiffCreator
#include "tiffcomposite_int.hpp"    // Exiv2::Internal::Tag (extended tag constants)

#include <cstdint>
#include <vector>

namespace {

using Exiv2::IfdId;

class TiffCreatorTest_1165 : public ::testing::Test {
protected:
  static IfdId InvalidIfdId() {
    // Use a clearly out-of-range value to avoid accidentally matching a real IFD id.
    return static_cast<IfdId>(999999);
  }

  static std::vector<uint32_t> BoundaryAndSpecialExtendedTags() {
    return {
        0u,
        1u,
        0xFFFFu,
        0x10000u,
        0x1FFFFu,
        0xFFFFFFFFu,
        static_cast<uint32_t>(Exiv2::Internal::Tag::none),
        static_cast<uint32_t>(Exiv2::Internal::Tag::root),
        static_cast<uint32_t>(Exiv2::Internal::Tag::next),
        static_cast<uint32_t>(Exiv2::Internal::Tag::all),
        static_cast<uint32_t>(Exiv2::Internal::Tag::pana),
        static_cast<uint32_t>(Exiv2::Internal::Tag::fuji),
        static_cast<uint32_t>(Exiv2::Internal::Tag::cmt2),
        static_cast<uint32_t>(Exiv2::Internal::Tag::cmt3),
        static_cast<uint32_t>(Exiv2::Internal::Tag::cmt4),
    };
  }
};

TEST_F(TiffCreatorTest_1165, CreateReturnsNullptrForInvalidGroup_1165) {
  const IfdId invalidGroup = InvalidIfdId();

  for (uint32_t extendedTag : BoundaryAndSpecialExtendedTags()) {
    // Observable behavior: when no table entry exists for the group, create() must return nullptr.
    auto component = Exiv2::Internal::TiffCreator::create(extendedTag, invalidGroup);
    EXPECT_EQ(component, nullptr) << "extendedTag=" << extendedTag;
  }
}

TEST_F(TiffCreatorTest_1165, CreateIsDeterministicForSameInvalidInputs_1165) {
  const IfdId invalidGroup = InvalidIfdId();
  const uint32_t extendedTag = 0xDEADBEEFu;

  auto c1 = Exiv2::Internal::TiffCreator::create(extendedTag, invalidGroup);
  auto c2 = Exiv2::Internal::TiffCreator::create(extendedTag, invalidGroup);

  // With an invalid group, both should be nullptr consistently.
  EXPECT_EQ(c1, nullptr);
  EXPECT_EQ(c2, nullptr);
}

TEST_F(TiffCreatorTest_1165, CreateHandlesBoundaryExtendedTagValuesWithoutThrowing_1165) {
  const IfdId invalidGroup = InvalidIfdId();

  // Primary observable requirement here: no crash/exception and returns a valid UniquePtr (nullptr ok).
  EXPECT_NO_THROW({
    auto c0 = Exiv2::Internal::TiffCreator::create(0u, invalidGroup);
    EXPECT_EQ(c0, nullptr);
  });

  EXPECT_NO_THROW({
    auto c1 = Exiv2::Internal::TiffCreator::create(0xFFFFu, invalidGroup);
    EXPECT_EQ(c1, nullptr);
  });

  EXPECT_NO_THROW({
    auto c2 = Exiv2::Internal::TiffCreator::create(0x10000u, invalidGroup);
    EXPECT_EQ(c2, nullptr);
  });

  EXPECT_NO_THROW({
    auto c3 = Exiv2::Internal::TiffCreator::create(0xFFFFFFFFu, invalidGroup);
    EXPECT_EQ(c3, nullptr);
  });
}

TEST_F(TiffCreatorTest_1165, CreateHandlesSpecialExtendedTagConstantsWithInvalidGroup_1165) {
  const IfdId invalidGroup = InvalidIfdId();

  const std::vector<uint32_t> special = {
      static_cast<uint32_t>(Exiv2::Internal::Tag::none),
      static_cast<uint32_t>(Exiv2::Internal::Tag::root),
      static_cast<uint32_t>(Exiv2::Internal::Tag::next),
      static_cast<uint32_t>(Exiv2::Internal::Tag::all),
  };

  for (uint32_t extendedTag : special) {
    auto component = Exiv2::Internal::TiffCreator::create(extendedTag, invalidGroup);
    EXPECT_EQ(component, nullptr) << "extendedTag=" << extendedTag;
  }
}

}  // namespace