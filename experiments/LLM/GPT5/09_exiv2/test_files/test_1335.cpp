// =================================================================================================
// TEST_ID: 1335
// File: test_exifkey_setidx_1335.cpp
// =================================================================================================

#include <gtest/gtest.h>

#include <limits>
#include <memory>
#include <string>

#include <exiv2/tags.hpp>
#include <exiv2/error.hpp>

namespace {

class ExifKeyTest_1335 : public ::testing::Test {
 protected:
  // Use a commonly valid Exif key string. We don't assert any parsing details here—
  // only that constructing a key that is expected to be valid works in this codebase.
  static Exiv2::ExifKey MakeKey() { return Exiv2::ExifKey("Exif.Image.Make"); }
};

TEST_F(ExifKeyTest_1335, SetIdxUpdatesIdx_1335) {
  Exiv2::ExifKey key = MakeKey();

  key.setIdx(0);
  EXPECT_EQ(key.idx(), 0);

  key.setIdx(7);
  EXPECT_EQ(key.idx(), 7);
}

TEST_F(ExifKeyTest_1335, SetIdxCallableOnConstObject_1335) {
  const Exiv2::ExifKey key = MakeKey();

  // setIdx is a const method; verify it can be called and is observable via idx().
  key.setIdx(3);
  EXPECT_EQ(key.idx(), 3);
}

TEST_F(ExifKeyTest_1335, SetIdxAcceptsNegativeValues_1335) {
  Exiv2::ExifKey key = MakeKey();

  key.setIdx(-1);
  EXPECT_EQ(key.idx(), -1);

  key.setIdx(-12345);
  EXPECT_EQ(key.idx(), -12345);
}

TEST_F(ExifKeyTest_1335, SetIdxBoundaryIntMinIntMax_1335) {
  Exiv2::ExifKey key = MakeKey();

  const int kMin = (std::numeric_limits<int>::min)();
  const int kMax = (std::numeric_limits<int>::max)();

  key.setIdx(kMin);
  EXPECT_EQ(key.idx(), kMin);

  key.setIdx(kMax);
  EXPECT_EQ(key.idx(), kMax);
}

TEST_F(ExifKeyTest_1335, CopyConstructorPreservesIdxValue_1335) {
  Exiv2::ExifKey original = MakeKey();
  original.setIdx(11);

  Exiv2::ExifKey copy(original);
  EXPECT_EQ(copy.idx(), 11);

  // After copying, changing one should not affect the other (observable independence).
  original.setIdx(22);
  EXPECT_EQ(original.idx(), 22);
  EXPECT_EQ(copy.idx(), 11);

  copy.setIdx(33);
  EXPECT_EQ(copy.idx(), 33);
  EXPECT_EQ(original.idx(), 22);
}

TEST_F(ExifKeyTest_1335, CopyAssignmentPreservesIdxValue_1335) {
  Exiv2::ExifKey lhs = MakeKey();
  lhs.setIdx(1);

  Exiv2::ExifKey rhs = MakeKey();
  rhs.setIdx(99);

  lhs = rhs;
  EXPECT_EQ(lhs.idx(), 99);

  // Independence after assignment (changing rhs should not retroactively change lhs).
  rhs.setIdx(100);
  EXPECT_EQ(rhs.idx(), 100);
  EXPECT_EQ(lhs.idx(), 99);
}

TEST_F(ExifKeyTest_1335, CloneProducesIndependentObjectWithSameKey_1335) {
  Exiv2::ExifKey key = MakeKey();
  key.setIdx(5);

  Exiv2::ExifKey::UniquePtr cloned = key.clone();
  ASSERT_NE(cloned.get(), nullptr);

  // Observable contract: clone represents the same key string.
  EXPECT_EQ(cloned->key(), key.key());

  // Also verify idx value is preserved and independence holds (observable via public API).
  EXPECT_EQ(cloned->idx(), key.idx());

  key.setIdx(6);
  EXPECT_EQ(key.idx(), 6);
  EXPECT_EQ(cloned->idx(), 5);

  cloned->setIdx(7);
  EXPECT_EQ(cloned->idx(), 7);
  EXPECT_EQ(key.idx(), 6);
}

TEST_F(ExifKeyTest_1335, InvalidKeyStringThrows_1335) {
  // Error/exception case observable through the interface:
  // constructing from an invalid key string should throw.
  EXPECT_ANY_THROW({ Exiv2::ExifKey bad("NotAValid.ExifKey.Format"); });

  // Another malformed example.
  EXPECT_ANY_THROW({ Exiv2::ExifKey bad2(""); });
}

}  // namespace