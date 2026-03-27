// ============================================================================
// Unit tests for Exiv2::Exifdatum::operator=(const int32_t&)
// File: test_exifdatum_assign_int32_736.cpp
// ============================================================================

#include <gtest/gtest.h>

#include <cstdint>
#include <limits>

#include <exiv2/exif.hpp>

namespace {

class ExifdatumAssignInt32Test_736 : public ::testing::Test {
 protected:
  // Use a well-known Exif key string that should exist in Exiv2.
  // (We don't depend on its internal meaning; only that ExifKey can be constructed.)
  static Exiv2::ExifKey MakeKey() { return Exiv2::ExifKey("Exif.Image.ImageWidth"); }
};

TEST_F(ExifdatumAssignInt32Test_736, ReturnsSelfReference_736) {
  Exiv2::ExifKey key = MakeKey();
  Exiv2::Exifdatum datum(key, nullptr);

  Exiv2::Exifdatum* addr_before = &datum;
  Exiv2::Exifdatum& ret = (datum = static_cast<int32_t>(123));

  EXPECT_EQ(addr_before, &ret);
}

TEST_F(ExifdatumAssignInt32Test_736, AssignSetsReadableIntegralValue_736) {
  Exiv2::ExifKey key = MakeKey();
  Exiv2::Exifdatum datum(key, nullptr);

  const int32_t v = 42;
  EXPECT_NO_THROW(datum = v);

  // Observable behavior through the public interface: value is accessible as an integer/string.
  EXPECT_EQ(datum.toInt64(0), static_cast<int64_t>(v));
  EXPECT_EQ(datum.count(), static_cast<size_t>(1));

  // toString() should reflect the assigned value in some way; at minimum, it shouldn't be empty.
  EXPECT_FALSE(datum.toString().empty());
}

TEST_F(ExifdatumAssignInt32Test_736, AssignHandlesInt32MinBoundary_736) {
  Exiv2::ExifKey key = MakeKey();
  Exiv2::Exifdatum datum(key, nullptr);

  const int32_t v = (std::numeric_limits<int32_t>::min)();
  EXPECT_NO_THROW(datum = v);
  EXPECT_EQ(datum.toInt64(0), static_cast<int64_t>(v));
  EXPECT_EQ(datum.count(), static_cast<size_t>(1));
}

TEST_F(ExifdatumAssignInt32Test_736, AssignHandlesInt32MaxBoundary_736) {
  Exiv2::ExifKey key = MakeKey();
  Exiv2::Exifdatum datum(key, nullptr);

  const int32_t v = (std::numeric_limits<int32_t>::max)();
  EXPECT_NO_THROW(datum = v);
  EXPECT_EQ(datum.toInt64(0), static_cast<int64_t>(v));
  EXPECT_EQ(datum.count(), static_cast<size_t>(1));
}

TEST_F(ExifdatumAssignInt32Test_736, SupportsChainedAssignment_736) {
  Exiv2::ExifKey key = MakeKey();
  Exiv2::Exifdatum datum(key, nullptr);

  // Chaining relies only on the operator returning a reference.
  EXPECT_NO_THROW((datum = static_cast<int32_t>(7)) = static_cast<int32_t>(9));

  EXPECT_EQ(datum.toInt64(0), static_cast<int64_t>(9));
  EXPECT_EQ(datum.count(), static_cast<size_t>(1));
}

}  // namespace