// File: test_exifdatum_assign_uint32_t_733.cpp
// Unit tests for Exiv2::Exifdatum::operator=(const uint32_t&)
// TEST_ID: 733

#include <gtest/gtest.h>

#include <cstdint>
#include <limits>
#include <memory>

#include <exiv2/exif.hpp>
#include <exiv2/value.hpp>

namespace {

class ExifdatumAssignUint32Test_733 : public ::testing::Test {
protected:
  static Exiv2::Exifdatum MakeDatumWithNullValue() {
    // Use a commonly valid Exif key. The key itself is part of public API.
    Exiv2::ExifKey key("Exif.Image.ImageWidth");
    return Exiv2::Exifdatum(key, nullptr);
  }

  static Exiv2::Exifdatum MakeDatumWithULongValue() {
    Exiv2::ExifKey key("Exif.Image.ImageWidth");
    // If available, pre-seed with an unsigned long value object. This tests assignment
    // when a Value already exists.
    Exiv2::Value::UniquePtr v = Exiv2::Value::create(Exiv2::unsignedLong);
    return Exiv2::Exifdatum(key, v.get());
  }
};

TEST_F(ExifdatumAssignUint32Test_733, AssignReturnsSelfReference_733) {
  auto d = MakeDatumWithNullValue();

  Exiv2::Exifdatum* before = &d;
  Exiv2::Exifdatum& ret = (d = static_cast<uint32_t>(123u));

  EXPECT_EQ(before, &ret);
}

TEST_F(ExifdatumAssignUint32Test_733, AssignZeroUpdatesObservableValue_733) {
  auto d = MakeDatumWithNullValue();

  ASSERT_NO_THROW(d = static_cast<uint32_t>(0u));

  // Observable behavior through public interface.
  EXPECT_EQ(d.toInt64(0), 0);
  EXPECT_GE(d.count(), 1u);
}

TEST_F(ExifdatumAssignUint32Test_733, AssignMaxUint32UpdatesObservableValue_733) {
  auto d = MakeDatumWithNullValue();
  const uint32_t maxv = (std::numeric_limits<uint32_t>::max)();

  ASSERT_NO_THROW(d = maxv);

  // toInt64 should be able to represent uint32_t max exactly.
  EXPECT_EQ(d.toInt64(0), static_cast<int64_t>(maxv));
  EXPECT_GE(d.count(), 1u);
}

TEST_F(ExifdatumAssignUint32Test_733, ReassignOverwritesPreviousValue_733) {
  auto d = MakeDatumWithNullValue();

  ASSERT_NO_THROW(d = static_cast<uint32_t>(10u));
  EXPECT_EQ(d.toInt64(0), 10);

  ASSERT_NO_THROW(d = static_cast<uint32_t>(42u));
  EXPECT_EQ(d.toInt64(0), 42);
}

TEST_F(ExifdatumAssignUint32Test_733, AssignmentWorksWhenValueAlreadyExists_733) {
  auto d = MakeDatumWithULongValue();

  ASSERT_NO_THROW(d = static_cast<uint32_t>(77u));

  EXPECT_EQ(d.toInt64(0), 77);
  EXPECT_GE(d.count(), 1u);
}

TEST_F(ExifdatumAssignUint32Test_733, CopyThenAssignDoesNotChangeOriginal_733) {
  auto original = MakeDatumWithNullValue();
  ASSERT_NO_THROW(original = static_cast<uint32_t>(100u));
  EXPECT_EQ(original.toInt64(0), 100);

  Exiv2::Exifdatum copy(original);
  ASSERT_NO_THROW(copy = static_cast<uint32_t>(200u));

  EXPECT_EQ(copy.toInt64(0), 200);
  // Original should remain observable as previously set.
  EXPECT_EQ(original.toInt64(0), 100);
}

}  // namespace