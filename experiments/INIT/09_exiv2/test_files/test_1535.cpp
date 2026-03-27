// SPDX-License-Identifier: GPL-2.0-or-later
// Tests for Exiv2::Internal::NikonArrayIdx::operator==(const Key&)
//
// File under test: ./TestProjects/exiv2/src/makernote_int.cpp

#include <gtest/gtest.h>

#include <cstring>
#include <string>

#include "makernote_int.cpp"  // Intentionally include the TU to access Internal types.

namespace {

// Helper to build a Key in the most tolerant way (aggregate init when possible).
static Exiv2::Internal::NikonArrayIdx::Key MakeKey(decltype(Exiv2::Internal::NikonArrayIdx::Key::tag_) tag,
                                                  const char* ver,
                                                  decltype(Exiv2::Internal::NikonArrayIdx::Key::size_) size) {
  Exiv2::Internal::NikonArrayIdx::Key k{};
  k.tag_ = tag;
  k.ver_ = ver;
  k.size_ = size;
  return k;
}

static Exiv2::Internal::NikonArrayIdx MakeIdx(int idx,
                                              decltype(Exiv2::Internal::NikonArrayIdx::Key::tag_) tag,
                                              const char* ver,
                                              decltype(Exiv2::Internal::NikonArrayIdx::Key::size_) size) {
  Exiv2::Internal::NikonArrayIdx a{};
  a.idx_ = idx;
  a.tag_ = tag;
  a.ver_ = ver;
  a.size_ = size;
  return a;
}

class NikonArrayIdxTest_1535 : public ::testing::Test {};

TEST_F(NikonArrayIdxTest_1535, ReturnsTrueWhenTagVersionAndSizeMatch_1535) {
  const auto idx = MakeIdx(/*idx*/ 7, /*tag*/ 0x1234, /*ver*/ "0100", /*size*/ 16);
  const auto key = MakeKey(/*tag*/ 0x1234, /*ver*/ "0100", /*size*/ 16);

  EXPECT_TRUE(idx == key);
}

TEST_F(NikonArrayIdxTest_1535, ReturnsFalseWhenTagDiffers_1535) {
  const auto idx = MakeIdx(/*idx*/ 7, /*tag*/ 0x1234, /*ver*/ "0100", /*size*/ 16);
  const auto key = MakeKey(/*tag*/ 0x1235, /*ver*/ "0100", /*size*/ 16);

  EXPECT_FALSE(idx == key);
}

TEST_F(NikonArrayIdxTest_1535, ReturnsTrueWhenKeyVersionHasMatchingPrefix_1535) {
  const auto idx = MakeIdx(/*idx*/ 7, /*tag*/ 0x1234, /*ver*/ "0100", /*size*/ 16);
  const auto key = MakeKey(/*tag*/ 0x1234, /*ver*/ "0100-extra-suffix", /*size*/ 16);

  // operator== compares only the first strlen(idx.ver_) bytes.
  EXPECT_TRUE(idx == key);
}

TEST_F(NikonArrayIdxTest_1535, ReturnsFalseWhenVersionPrefixDoesNotMatch_1535) {
  const auto idx = MakeIdx(/*idx*/ 7, /*tag*/ 0x1234, /*ver*/ "0100", /*size*/ 16);
  const auto key = MakeKey(/*tag*/ 0x1234, /*ver*/ "0200", /*size*/ 16);

  EXPECT_FALSE(idx == key);
}

TEST_F(NikonArrayIdxTest_1535, ReturnsFalseWhenKeyVersionShorterThanIdxVersion_1535) {
  const auto idx = MakeIdx(/*idx*/ 7, /*tag*/ 0x1234, /*ver*/ "Nikon", /*size*/ 16);
  const auto key = MakeKey(/*tag*/ 0x1234, /*ver*/ "Nik", /*size*/ 16);

  EXPECT_FALSE(idx == key);
}

TEST_F(NikonArrayIdxTest_1535, TreatsZeroSizeAsWildcard_1535) {
  const auto idx = MakeIdx(/*idx*/ 7, /*tag*/ 0x1234, /*ver*/ "0100", /*size*/ 0);

  const auto key1 = MakeKey(/*tag*/ 0x1234, /*ver*/ "0100", /*size*/ 1);
  const auto key2 = MakeKey(/*tag*/ 0x1234, /*ver*/ "0100", /*size*/ 999);

  EXPECT_TRUE(idx == key1);
  EXPECT_TRUE(idx == key2);
}

TEST_F(NikonArrayIdxTest_1535, RequiresExactSizeMatchWhenSizeIsNonZero_1535) {
  const auto idx = MakeIdx(/*idx*/ 7, /*tag*/ 0x1234, /*ver*/ "0100", /*size*/ 16);

  const auto match = MakeKey(/*tag*/ 0x1234, /*ver*/ "0100", /*size*/ 16);
  const auto mismatch = MakeKey(/*tag*/ 0x1234, /*ver*/ "0100", /*size*/ 15);

  EXPECT_TRUE(idx == match);
  EXPECT_FALSE(idx == mismatch);
}

TEST_F(NikonArrayIdxTest_1535, EmptyIdxVersionMatchesAnyKeyVersionWhenOtherFieldsAllow_1535) {
  const auto idx = MakeIdx(/*idx*/ 7, /*tag*/ 0x1234, /*ver*/ "", /*size*/ 0);

  const auto keyA = MakeKey(/*tag*/ 0x1234, /*ver*/ "whatever", /*size*/ 1);
  const auto keyB = MakeKey(/*tag*/ 0x1234, /*ver*/ "", /*size*/ 999);

  EXPECT_TRUE(idx == keyA);
  EXPECT_TRUE(idx == keyB);
}

}  // namespace