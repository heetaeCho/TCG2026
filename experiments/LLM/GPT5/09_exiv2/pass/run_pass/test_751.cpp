// =====================================================================================
// TEST_ID: 751
// Unit tests for Exiv2::Exifdatum::idx()
// File: ./TestProjects/exiv2/src/exif.cpp (interface under test)
// =====================================================================================

#include <gtest/gtest.h>

#include <exiv2/exif.hpp>
#include <exiv2/tags.hpp>
#include <exiv2/value.hpp>

#include <cstdint>
#include <limits>
#include <memory>
#include <string>

namespace {

// Helper: build a minimally valid Value to satisfy Exifdatum constructor.
static std::unique_ptr<Exiv2::Value> MakeSimpleValue() {
  // Pick a common type and populate it with a simple value.
  // We don't assert on any Value behavior; it's only used as a collaborator input.
  std::unique_ptr<Exiv2::Value> v = Exiv2::Value::create(Exiv2::unsignedShort);
  if (v) {
    (void)v->read("1");
  }
  return v;
}

class ExifdatumIdxTest_751 : public ::testing::Test {
 protected:
  static Exiv2::ExifKey MakeKey() {
    // A typical Exif key string. We do not assume anything about parsing beyond construction.
    return Exiv2::ExifKey("Exif.Image.Make");
  }

  static Exiv2::Exifdatum MakeDatumWithKey(const Exiv2::ExifKey& key) {
    auto v = MakeSimpleValue();
    // Pass a non-null Value pointer to avoid assuming nullptr is accepted.
    return Exiv2::Exifdatum(key, v.get());
  }
};

}  // namespace

TEST_F(ExifdatumIdxTest_751, ReturnsSameAsKeyIdx_DefaultKey_751) {
  const Exiv2::ExifKey key = MakeKey();
  const Exiv2::Exifdatum datum = MakeDatumWithKey(key);

  // Black-box expectation derived directly from the provided implementation:
  // idx() reflects key_->idx() (or 0 if no key).
  EXPECT_EQ(datum.idx(), key.idx());
}

TEST_F(ExifdatumIdxTest_751, ReturnsSameAsKeyIdx_AfterSetIdxPositive_751) {
  Exiv2::ExifKey key = MakeKey();
  key.setIdx(123);
  const Exiv2::Exifdatum datum = MakeDatumWithKey(key);

  EXPECT_EQ(datum.idx(), key.idx());
}

TEST_F(ExifdatumIdxTest_751, ReturnsSameAsKeyIdx_WhenIdxIsZero_751) {
  Exiv2::ExifKey key = MakeKey();
  key.setIdx(0);
  const Exiv2::Exifdatum datum = MakeDatumWithKey(key);

  EXPECT_EQ(datum.idx(), key.idx());
}

TEST_F(ExifdatumIdxTest_751, ReturnsSameAsKeyIdx_WhenIdxIsNegative_751) {
  Exiv2::ExifKey key = MakeKey();
  key.setIdx(-7);
  const Exiv2::Exifdatum datum = MakeDatumWithKey(key);

  // Compare to key.idx() to remain robust if the library clamps/normalizes.
  EXPECT_EQ(datum.idx(), key.idx());
}

TEST_F(ExifdatumIdxTest_751, ReturnsSameAsKeyIdx_WhenIdxIsIntMax_751) {
  Exiv2::ExifKey key = MakeKey();
  key.setIdx((std::numeric_limits<int>::max)());
  const Exiv2::Exifdatum datum = MakeDatumWithKey(key);

  EXPECT_EQ(datum.idx(), key.idx());
}

TEST_F(ExifdatumIdxTest_751, CopyConstructorPreservesIdx_751) {
  Exiv2::ExifKey key = MakeKey();
  key.setIdx(42);

  const Exiv2::Exifdatum original = MakeDatumWithKey(key);
  const Exiv2::Exifdatum copy(original);

  EXPECT_EQ(copy.idx(), original.idx());
}

TEST_F(ExifdatumIdxTest_751, CopyAssignmentPreservesIdx_751) {
  Exiv2::ExifKey keyA = MakeKey();
  keyA.setIdx(11);
  const Exiv2::Exifdatum a = MakeDatumWithKey(keyA);

  Exiv2::ExifKey keyB = Exiv2::ExifKey("Exif.Image.Model");
  keyB.setIdx(99);
  Exiv2::Exifdatum b = MakeDatumWithKey(keyB);

  b = a;

  EXPECT_EQ(b.idx(), a.idx());
}

TEST_F(ExifdatumIdxTest_751, SelfAssignmentKeepsIdx_751) {
  Exiv2::ExifKey key = MakeKey();
  key.setIdx(314);
  Exiv2::Exifdatum datum = MakeDatumWithKey(key);

  const int before = datum.idx();
  datum = datum;
  const int after = datum.idx();

  EXPECT_EQ(after, before);
}