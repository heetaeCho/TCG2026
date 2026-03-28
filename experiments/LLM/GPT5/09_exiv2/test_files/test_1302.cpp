// SPDX-License-Identifier: GPL-2.0-or-later
//
// Unit tests for Exiv2::XmpData::operator[]
//
// File under test (partial implementation provided):
//   ./TestProjects/exiv2/src/xmp.cpp
//
// This test suite treats XmpData as a black box and verifies only observable
// behavior through the public interface.
//
// The TEST_ID is 1302

#include <gtest/gtest.h>

#include <exiv2/xmp_exiv2.hpp>

#include <string>

namespace {

// Keep the fixture name aligned with the required TEST_ID naming convention.
class XmpDataOperatorBracketTest_1302 : public ::testing::Test {
 protected:
  Exiv2::XmpData data;
};

static std::string MakeKey(const char* suffix) {
  // Use a common XMP-ish prefix; correctness of key parsing is owned by XmpKey.
  // Tests here only rely on observable behavior of XmpData.
  return std::string("Xmp.dc.") + suffix;
}

}  // namespace

TEST_F(XmpDataOperatorBracketTest_1302, EmptyDataThenAccessInsertsAndReturnsRef_1302) {
  ASSERT_TRUE(data.empty());
  const long before = data.count();

  Exiv2::Xmpdatum& d = data[MakeKey("title")];

  (void)d;  // We only care that a reference is returned and container changes are observable.
  EXPECT_FALSE(data.empty());
  EXPECT_EQ(data.count(), before + 1);
}

TEST_F(XmpDataOperatorBracketTest_1302, AccessSameKeyTwiceDoesNotIncreaseCount_1302) {
  ASSERT_TRUE(data.empty());

  Exiv2::Xmpdatum& first = data[MakeKey("creator")];
  const long afterFirst = data.count();
  ASSERT_EQ(afterFirst, 1);

  Exiv2::Xmpdatum& second = data[MakeKey("creator")];
  const long afterSecond = data.count();

  // Observable behavior expectation: existing element is returned, no new one inserted.
  EXPECT_EQ(afterSecond, afterFirst);

  // Stronger observable check: same key should yield same element reference.
  // This is implied by the provided implementation (returns *pos), but still observable.
  EXPECT_EQ(&second, &first);
}

TEST_F(XmpDataOperatorBracketTest_1302, AccessDifferentKeysInsertsDistinctEntries_1302) {
  ASSERT_TRUE(data.empty());

  Exiv2::Xmpdatum& a = data[MakeKey("subject")];
  ASSERT_EQ(data.count(), 1);

  Exiv2::Xmpdatum& b = data[MakeKey("description")];
  ASSERT_EQ(data.count(), 2);

  EXPECT_NE(&a, &b);
}

TEST_F(XmpDataOperatorBracketTest_1302, ReferenceStaysValidAcrossRepeatedSameKeyLookups_1302) {
  // This test avoids assuming anything about internal storage stability across *growth*.
  // It only verifies that repeated lookups for the same key return the same address.
  Exiv2::Xmpdatum& first = data[MakeKey("rights")];
  for (int i = 0; i < 10; ++i) {
    Exiv2::Xmpdatum& again = data[MakeKey("rights")];
    EXPECT_EQ(&again, &first);
  }
}

TEST_F(XmpDataOperatorBracketTest_1302, BoundaryEmptyStringKeyIsHandledAndObservableCountChanges_1302) {
  // Boundary: empty key string. We do not assume whether it is "valid" semantically;
  // we only check observable behavior (no crash; count changes or not is observable).
  const long before = data.count();

  Exiv2::Xmpdatum& d = data[std::string()];
  (void)d;

  // If empty string is treated as a key, it should insert once on first access.
  // If XmpKey throws internally, test would fail by exception; we don't catch it
  // here because behavior is what we want to observe in this environment.
  EXPECT_EQ(data.count(), before + 1);

  // Second access should not increase further if the same key maps to the same datum.
  Exiv2::Xmpdatum& d2 = data[std::string()];
  (void)d2;
  EXPECT_EQ(data.count(), before + 1);
  EXPECT_EQ(&d2, &d);
}

TEST_F(XmpDataOperatorBracketTest_1302, BoundaryVeryLongKeyStringDoesNotCorruptContainer_1302) {
  // Boundary: very long key.
  std::string longKey(4096, 'a');
  // Put something that looks like a typical XMP key at the front to reduce chance
  // of unrelated parsing edge-cases; still "long".
  longKey = std::string("Xmp.dc.") + longKey;

  const long before = data.count();
  Exiv2::Xmpdatum& d = data[longKey];
  (void)d;

  EXPECT_EQ(data.count(), before + 1);

  // Same long key again should not change count and should return same element.
  Exiv2::Xmpdatum& d2 = data[longKey];
  EXPECT_EQ(data.count(), before + 1);
  EXPECT_EQ(&d2, &d);
}

TEST_F(XmpDataOperatorBracketTest_1302, InteractionWithFindKeyAfterInsertionKeyIsFindable_1302) {
  // Verify external observable interaction with another public function: findKey.
  // We do not assume findKey internals; only that once operator[] inserts,
  // findKey can locate the same key.
  const std::string key = MakeKey("format");

  Exiv2::Xmpdatum& inserted = data[key];
  (void)inserted;

  Exiv2::XmpKey xk(key);
  auto it = data.findKey(xk);

  ASSERT_NE(it, data.end());

  // If iterator dereference yields a datum, it should refer to the same object as operator[] returned.
  EXPECT_EQ(&(*it), &inserted);
}

TEST_F(XmpDataOperatorBracketTest_1302, InteractionWithClearAfterInsertionBecomesEmpty_1302) {
  data[MakeKey("a")];
  data[MakeKey("b")];
  ASSERT_FALSE(data.empty());
  ASSERT_GE(data.count(), 2);

  data.clear();

  EXPECT_TRUE(data.empty());
  EXPECT_EQ(data.count(), 0);
  EXPECT_EQ(data.begin(), data.end());
}

TEST_F(XmpDataOperatorBracketTest_1302, ErrorCaseInvalidKeyIfThrowsThenExceptionPropagates_1302) {
  // "Exceptional or error cases (if observable)".
  //
  // We cannot assume what XmpKey considers invalid. However, we *can* write a test
  // that is resilient: it passes if either (a) no exception is thrown, or (b) an
  // exception is thrown and container state remains consistent.
  //
  // We'll try a key that is often problematic in parsers: contains embedded NUL.
  std::string weirdKey = std::string("Xmp.dc.") + std::string("bad\0key", 7);

  const long before = data.count();
  try {
    Exiv2::Xmpdatum& d = data[weirdKey];
    (void)d;
    // If no exception, we should have inserted exactly one entry for that same key.
    EXPECT_EQ(data.count(), before + 1);
    Exiv2::Xmpdatum& d2 = data[weirdKey];
    EXPECT_EQ(data.count(), before + 1);
    EXPECT_EQ(&d2, &d);
  } catch (...) {
    // If an exception is thrown, at minimum it should not have partially inserted
    // multiple entries; container should remain usable and count should be unchanged.
    EXPECT_EQ(data.count(), before);
    EXPECT_TRUE(data.count() >= 0);
  }
}