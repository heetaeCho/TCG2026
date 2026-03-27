// TEST_ID 777
// Unit tests for Exiv2::ExifData::add(const Exiv2::Exifdatum&)
// File under test: ./TestProjects/exiv2/src/exif.cpp

#include <gtest/gtest.h>

#include <exiv2/exif.hpp>
#include <exiv2/value.hpp>

#include <string>
#include <utility>

namespace {

Exiv2::Exifdatum MakeAsciiExifdatum(const std::string& keyStr, const std::string& valueStr) {
  Exiv2::ExifKey key(keyStr);
  Exiv2::Value::UniquePtr v = Exiv2::Value::create(Exiv2::asciiString);
  // `read()` returns an int in Exiv2; we don't assume any particular return value contract here.
  (void)v->read(valueStr);
  return Exiv2::Exifdatum(key, v.get());
}

class ExifDataAddTest_777 : public ::testing::Test {
 protected:
  Exiv2::ExifData data_;
};

}  // namespace

TEST_F(ExifDataAddTest_777, AddSingleDatumMakesContainerNonEmptyAndCountOne_777) {
  EXPECT_TRUE(data_.empty());
  EXPECT_EQ(data_.count(), 0u);

  const Exiv2::Exifdatum d = MakeAsciiExifdatum("Exif.Image.Make", "Canon");
  data_.add(d);

  EXPECT_FALSE(data_.empty());
  EXPECT_EQ(data_.count(), 1u);
}

TEST_F(ExifDataAddTest_777, AddTwoDatumsIncrementsCountTwice_777) {
  const Exiv2::Exifdatum d1 = MakeAsciiExifdatum("Exif.Image.Make", "Canon");
  const Exiv2::Exifdatum d2 = MakeAsciiExifdatum("Exif.Image.Model", "EOS");

  EXPECT_EQ(data_.count(), 0u);

  data_.add(d1);
  EXPECT_EQ(data_.count(), 1u);

  data_.add(d2);
  EXPECT_EQ(data_.count(), 2u);
}

TEST_F(ExifDataAddTest_777, AddedDatumIsObservableViaIteration_777) {
  const Exiv2::Exifdatum d = MakeAsciiExifdatum("Exif.Image.Make", "Canon");
  data_.add(d);

  ASSERT_FALSE(data_.empty());
  ASSERT_EQ(data_.count(), 1u);

  auto it = data_.begin();
  auto end = data_.end();
  ASSERT_NE(it, end);

  EXPECT_EQ(it->key(), "Exif.Image.Make");
  // Also sanity-check that increment reaches end for a single element.
  ++it;
  EXPECT_EQ(it, end);
}

TEST_F(ExifDataAddTest_777, AddCopiesDatumSoOriginalLifetimeDoesNotMatter_777) {
  EXPECT_EQ(data_.count(), 0u);

  {
    Exiv2::Exifdatum temp = MakeAsciiExifdatum("Exif.Image.Make", "Canon");
    data_.add(temp);
  }  // temp destroyed here

  ASSERT_EQ(data_.count(), 1u);

  auto it = data_.begin();
  ASSERT_NE(it, data_.end());
  EXPECT_EQ(it->key(), "Exif.Image.Make");
}

TEST_F(ExifDataAddTest_777, AddSameDatumTwiceIncreasesCountEachTime_777) {
  const Exiv2::Exifdatum d = MakeAsciiExifdatum("Exif.Image.Make", "Canon");

  data_.add(d);
  EXPECT_EQ(data_.count(), 1u);

  data_.add(d);
  EXPECT_EQ(data_.count(), 2u);
}

TEST_F(ExifDataAddTest_777, ClearAfterAddResetsToEmptyAndCountZero_777) {
  data_.add(MakeAsciiExifdatum("Exif.Image.Make", "Canon"));
  ASSERT_FALSE(data_.empty());
  ASSERT_EQ(data_.count(), 1u);

  data_.clear();

  EXPECT_TRUE(data_.empty());
  EXPECT_EQ(data_.count(), 0u);
  EXPECT_EQ(data_.begin(), data_.end());
}