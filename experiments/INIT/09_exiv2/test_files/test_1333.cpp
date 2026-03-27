// SPDX-License-Identifier: GPL-2.0-or-later
// File: test_exifkey_impl_makekey_1333.cpp

#include <gtest/gtest.h>

#include <cstdint>
#include <string>
#include <type_traits>

// Try to include whatever exposes Exiv2::ExifKey and possibly ExifKey::Impl.
#if __has_include(<exiv2/tags.hpp>)
#include <exiv2/tags.hpp>
#elif __has_include("exiv2/tags.hpp")
#include "exiv2/tags.hpp"
#endif

namespace {

// --- Detection helpers (so tests still compile even if some internals are not exposed) ---

template <typename T, typename = void>
struct has_member_tag_ : std::false_type {};
template <typename T>
struct has_member_tag_<T, std::void_t<decltype(std::declval<T&>().tag_)>> : std::true_type {};

template <typename T, typename = void>
struct has_member_ifdId_ : std::false_type {};
template <typename T>
struct has_member_ifdId_<T, std::void_t<decltype(std::declval<T&>().ifdId_)>> : std::true_type {};

template <typename T, typename = void>
struct has_member_tagInfo_ : std::false_type {};
template <typename T>
struct has_member_tagInfo_<T, std::void_t<decltype(std::declval<T&>().tagInfo_)>> : std::true_type {};

template <typename T, typename = void>
struct has_member_groupName_ : std::false_type {};
template <typename T>
struct has_member_groupName_<T, std::void_t<decltype(std::declval<T&>().groupName_)>> : std::true_type {};

template <typename T, typename = void>
struct has_member_key_ : std::false_type {};
template <typename T>
struct has_member_key_<T, std::void_t<decltype(std::declval<T&>().key_)>> : std::true_type {};

template <typename T, typename = void>
struct has_makeKey_ : std::false_type {};
template <typename T>
struct has_makeKey_<T, std::void_t<decltype(std::declval<T&>().makeKey(
    std::declval<uint16_t>(),
    std::declval<Exiv2::IfdId>(),
    std::declval<const Exiv2::TagInfo*>()))>> : std::true_type {};

// --- Fixture ---

class ExifKeyImplTest_1333 : public ::testing::Test {
protected:
  // Create a TagInfo instance we can pass by pointer without relying on any behavior.
  static Exiv2::TagInfo MakeTagInfo() {
    Exiv2::TagInfo ti{};
    // We deliberately do not assume anything about valid combinations here.
    // Just provide a stable object whose address can be compared.
    ti.count_ = 0;
    return ti;
  }
};

}  // namespace

TEST_F(ExifKeyImplTest_1333, MakeKeyIsCallableIfImplIsExposed_1333) {
  // If ExifKey::Impl is not exposed to unit tests via headers, skip gracefully.
#if defined(Exiv2_VERSION) || defined(EXIV2_MAJOR_VERSION) || 1
  // The type itself might not exist in public headers; guard with SFINAE-like usage.
  // If it doesn't compile in your environment, ensure the internal header exposing
  // Exiv2::ExifKey::Impl is included by the __has_include section above.
#endif

  // Hard reference to the type (will fail compilation if not available; in that case,
  // add/include the internal header that exposes it in your test build).
  using Impl = Exiv2::ExifKey::Impl;

  Impl impl{};
  Exiv2::TagInfo ti = MakeTagInfo();

  // We only assert "callable and does not throw" as pure observable behavior.
  ASSERT_TRUE((has_makeKey_<Impl>::value));
  EXPECT_NO_THROW(impl.makeKey(/*tag=*/0, /*ifdId=*/Exiv2::IfdId::ifdIdNotSet, /*tagInfo=*/&ti));
}

TEST_F(ExifKeyImplTest_1333, MakeKeySetsBasicFieldsWhenPublicMembersExist_1333) {
  using Impl = Exiv2::ExifKey::Impl;

  Impl impl{};
  Exiv2::TagInfo ti = MakeTagInfo();

  const uint16_t tag = 0x1234;
  const Exiv2::IfdId ifdId = Exiv2::IfdId::ifdIdNotSet;
  const Exiv2::TagInfo* tagInfoPtr = &ti;

  ASSERT_TRUE((has_makeKey_<Impl>::value));
  ASSERT_NO_THROW(impl.makeKey(tag, ifdId, tagInfoPtr));

  // Verify externally observable effects through public data members (if present).
  if constexpr (has_member_tagInfo_<Impl>::value) {
    EXPECT_EQ(impl.tagInfo_, tagInfoPtr);
  } else {
    GTEST_SKIP() << "ExifKey::Impl::tagInfo_ is not publicly accessible in this build.";
  }

  if constexpr (has_member_tag_<Impl>::value) {
    EXPECT_EQ(impl.tag_, tag);
  } else {
    GTEST_SKIP() << "ExifKey::Impl::tag_ is not publicly accessible in this build.";
  }

  if constexpr (has_member_ifdId_<Impl>::value) {
    EXPECT_EQ(impl.ifdId_, ifdId);
  } else {
    GTEST_SKIP() << "ExifKey::Impl::ifdId_ is not publicly accessible in this build.";
  }
}

TEST_F(ExifKeyImplTest_1333, MakeKeyAcceptsNullTagInfoPointer_1333) {
  using Impl = Exiv2::ExifKey::Impl;

  Impl impl{};
  const uint16_t tag = 1;
  const Exiv2::IfdId ifdId = Exiv2::IfdId::ifdIdNotSet;

  ASSERT_TRUE((has_makeKey_<Impl>::value));
  EXPECT_NO_THROW(impl.makeKey(tag, ifdId, /*tagInfo=*/nullptr));

  // If tagInfo_ is publicly visible, it should reflect what we passed.
  if constexpr (has_member_tagInfo_<Impl>::value) {
    EXPECT_EQ(impl.tagInfo_, nullptr);
  }
}

TEST_F(ExifKeyImplTest_1333, MakeKeyBoundaryTagValuesDoNotThrow_1333) {
  using Impl = Exiv2::ExifKey::Impl;

  Impl impl{};
  Exiv2::TagInfo ti = MakeTagInfo();

  ASSERT_TRUE((has_makeKey_<Impl>::value));

  // Boundary values for uint16_t tag.
  EXPECT_NO_THROW(impl.makeKey(/*tag=*/0, Exiv2::IfdId::ifdIdNotSet, &ti));
  EXPECT_NO_THROW(impl.makeKey(/*tag=*/static_cast<uint16_t>(0xFFFF), Exiv2::IfdId::ifdIdNotSet, &ti));

  // If tag_ is visible, confirm it reflects the last call (observable state).
  if constexpr (has_member_tag_<Impl>::value) {
    EXPECT_EQ(impl.tag_, static_cast<uint16_t>(0xFFFF));
  }
}

TEST_F(ExifKeyImplTest_1333, MakeKeyIncorporatesGroupNameInKeyWhenKeyIsExposed_1333) {
  using Impl = Exiv2::ExifKey::Impl;

  Impl impl{};
  Exiv2::TagInfo ti = MakeTagInfo();

  // This test is only meaningful if groupName_ and key_ are publicly accessible.
  if constexpr (!(has_member_groupName_<Impl>::value && has_member_key_<Impl>::value)) {
    GTEST_SKIP() << "groupName_ and/or key_ are not publicly accessible in this build.";
  } else {
    impl.groupName_ = "UnitTestGroup";
    ASSERT_NO_THROW(impl.makeKey(/*tag=*/0x10, Exiv2::IfdId::ifdIdNotSet, &ti));

    // Based strictly on the provided snippet: key_ = familyName_ + "." + groupName_ + "." + tagName()
    // We don't assume familyName_ or tagName(), but we can assert the ".<groupName_>." delimiter exists.
    const std::string needle = std::string(".") + impl.groupName_ + ".";
    EXPECT_NE(impl.key_.find(needle), std::string::npos);
  }
}