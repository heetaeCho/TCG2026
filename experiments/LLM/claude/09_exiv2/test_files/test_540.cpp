#include <gtest/gtest.h>
#include <exiv2/exiv2.hpp>
#include <exiv2/easyaccess.hpp>

class FlashEnergyTest_540 : public ::testing::Test {
protected:
    Exiv2::ExifData ed;
};

TEST_F(FlashEnergyTest_540, ReturnsEndWhenExifDataIsEmpty_540) {
    auto it = Exiv2::flashEnergy(ed);
    EXPECT_EQ(it, ed.end());
}

TEST_F(FlashEnergyTest_540, FindsExifPhotoFlashEnergy_540) {
    Exiv2::ExifKey key("Exif.Photo.FlashEnergy");
    Exiv2::Value::UniquePtr value = Exiv2::Value::create(Exiv2::unsignedRational);
    value->read("123/1");
    ed.add(key, value.get());

    auto it = Exiv2::flashEnergy(ed);
    ASSERT_NE(it, ed.end());
    EXPECT_EQ(it->key(), "Exif.Photo.FlashEnergy");
}

TEST_F(FlashEnergyTest_540, FindsExifImageFlashEnergy_540) {
    Exiv2::ExifKey key("Exif.Image.FlashEnergy");
    Exiv2::Value::UniquePtr value = Exiv2::Value::create(Exiv2::unsignedRational);
    value->read("456/1");
    ed.add(key, value.get());

    auto it = Exiv2::flashEnergy(ed);
    ASSERT_NE(it, ed.end());
    EXPECT_EQ(it->key(), "Exif.Image.FlashEnergy");
}

TEST_F(FlashEnergyTest_540, PrefersExifPhotoOverExifImage_540) {
    // Add Exif.Photo.FlashEnergy first
    {
        Exiv2::ExifKey key("Exif.Photo.FlashEnergy");
        Exiv2::Value::UniquePtr value = Exiv2::Value::create(Exiv2::unsignedRational);
        value->read("100/1");
        ed.add(key, value.get());
    }
    // Add Exif.Image.FlashEnergy second
    {
        Exiv2::ExifKey key("Exif.Image.FlashEnergy");
        Exiv2::Value::UniquePtr value = Exiv2::Value::create(Exiv2::unsignedRational);
        value->read("200/1");
        ed.add(key, value.get());
    }

    auto it = Exiv2::flashEnergy(ed);
    ASSERT_NE(it, ed.end());
    EXPECT_EQ(it->key(), "Exif.Photo.FlashEnergy");
}

TEST_F(FlashEnergyTest_540, ReturnsEndWhenNoMatchingKey_540) {
    // Add an unrelated key
    Exiv2::ExifKey key("Exif.Photo.ExposureTime");
    Exiv2::Value::UniquePtr value = Exiv2::Value::create(Exiv2::unsignedRational);
    value->read("1/100");
    ed.add(key, value.get());

    auto it = Exiv2::flashEnergy(ed);
    EXPECT_EQ(it, ed.end());
}

TEST_F(FlashEnergyTest_540, FindsImageFlashEnergyWhenPhotoNotPresent_540) {
    // Add unrelated key and Exif.Image.FlashEnergy
    {
        Exiv2::ExifKey key("Exif.Photo.ExposureTime");
        Exiv2::Value::UniquePtr value = Exiv2::Value::create(Exiv2::unsignedRational);
        value->read("1/100");
        ed.add(key, value.get());
    }
    {
        Exiv2::ExifKey key("Exif.Image.FlashEnergy");
        Exiv2::Value::UniquePtr value = Exiv2::Value::create(Exiv2::unsignedRational);
        value->read("300/1");
        ed.add(key, value.get());
    }

    auto it = Exiv2::flashEnergy(ed);
    ASSERT_NE(it, ed.end());
    EXPECT_EQ(it->key(), "Exif.Image.FlashEnergy");
}

TEST_F(FlashEnergyTest_540, ReturnedIteratorIsConst_540) {
    Exiv2::ExifKey key("Exif.Photo.FlashEnergy");
    Exiv2::Value::UniquePtr value = Exiv2::Value::create(Exiv2::unsignedRational);
    value->read("50/1");
    ed.add(key, value.get());

    Exiv2::ExifData::const_iterator it = Exiv2::flashEnergy(ed);
    ASSERT_NE(it, ed.end());
    // Verify we can read the value through the const_iterator
    EXPECT_FALSE(it->value().toString().empty());
}

TEST_F(FlashEnergyTest_540, MultipleCallsReturnConsistentResults_540) {
    Exiv2::ExifKey key("Exif.Photo.FlashEnergy");
    Exiv2::Value::UniquePtr value = Exiv2::Value::create(Exiv2::unsignedRational);
    value->read("75/1");
    ed.add(key, value.get());

    auto it1 = Exiv2::flashEnergy(ed);
    auto it2 = Exiv2::flashEnergy(ed);
    ASSERT_NE(it1, ed.end());
    ASSERT_NE(it2, ed.end());
    EXPECT_EQ(it1->key(), it2->key());
    EXPECT_EQ(it1->value().toString(), it2->value().toString());
}

TEST_F(FlashEnergyTest_540, WorksWithOnlyImageFlashEnergy_540) {
    Exiv2::ExifKey key("Exif.Image.FlashEnergy");
    Exiv2::Value::UniquePtr value = Exiv2::Value::create(Exiv2::unsignedRational);
    value->read("999/10");
    ed.add(key, value.get());

    auto it = Exiv2::flashEnergy(ed);
    ASSERT_NE(it, ed.end());
    EXPECT_EQ(it->key(), "Exif.Image.FlashEnergy");
    EXPECT_EQ(it->value().toString(), "999/10");
}

TEST_F(FlashEnergyTest_540, ReturnsEndAfterClearingData_540) {
    Exiv2::ExifKey key("Exif.Photo.FlashEnergy");
    Exiv2::Value::UniquePtr value = Exiv2::Value::create(Exiv2::unsignedRational);
    value->read("50/1");
    ed.add(key, value.get());

    // First, verify it's found
    auto it = Exiv2::flashEnergy(ed);
    ASSERT_NE(it, ed.end());

    // Clear and verify it returns end
    ed.clear();
    it = Exiv2::flashEnergy(ed);
    EXPECT_EQ(it, ed.end());
}
