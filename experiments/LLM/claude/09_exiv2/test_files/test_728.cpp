#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <sstream>
#include <string>

#include <exiv2/exif.hpp>
#include <exiv2/exiv2.hpp>

using namespace Exiv2;

class ExifdatumTest_728 : public ::testing::Test {
protected:
    void SetUp() override {
    }
    void TearDown() override {
    }
};

// Test: Creating an Exifdatum with a known ExifKey
TEST_F(ExifdatumTest_728, ConstructWithExifKey_728) {
    ExifKey key("Exif.Image.Make");
    Exifdatum datum(key);
    EXPECT_EQ(datum.key(), "Exif.Image.Make");
    EXPECT_EQ(datum.familyName(), std::string("Exif"));
    EXPECT_EQ(datum.groupName(), "Image");
    EXPECT_EQ(datum.tagName(), "Make");
}

// Test: Copy constructor
TEST_F(ExifdatumTest_728, CopyConstructor_728) {
    ExifKey key("Exif.Image.Model");
    Exifdatum datum(key);
    datum.setValue("TestModel");
    
    Exifdatum copy(datum);
    EXPECT_EQ(copy.key(), "Exif.Image.Model");
    EXPECT_EQ(copy.toString(), "TestModel");
}

// Test: Assignment operator from another Exifdatum
TEST_F(ExifdatumTest_728, AssignmentOperator_728) {
    ExifKey key1("Exif.Image.Make");
    Exifdatum datum1(key1);
    datum1.setValue("Canon");

    ExifKey key2("Exif.Image.Model");
    Exifdatum datum2(key2);
    datum2 = datum1;
    
    EXPECT_EQ(datum2.toString(), "Canon");
}

// Test: Setting string value
TEST_F(ExifdatumTest_728, SetStringValue_728) {
    ExifKey key("Exif.Image.Make");
    Exifdatum datum(key);
    int result = datum.setValue("Nikon");
    EXPECT_EQ(result, 0);
    EXPECT_EQ(datum.toString(), "Nikon");
}

// Test: Assigning a string via operator=
TEST_F(ExifdatumTest_728, AssignString_728) {
    ExifKey key("Exif.Image.Make");
    Exifdatum datum(key);
    datum = std::string("Sony");
    EXPECT_EQ(datum.toString(), "Sony");
}

// Test: Assigning uint16_t value
TEST_F(ExifdatumTest_728, AssignUint16_728) {
    ExifKey key("Exif.Image.Orientation");
    Exifdatum datum(key);
    uint16_t val = 1;
    datum = val;
    EXPECT_EQ(datum.toInt64(0), 1);
}

// Test: Assigning uint32_t value
TEST_F(ExifdatumTest_728, AssignUint32_728) {
    ExifKey key("Exif.Image.ImageWidth");
    Exifdatum datum(key);
    uint32_t val = 1920;
    datum = val;
    EXPECT_EQ(datum.toInt64(0), 1920);
}

// Test: Assigning int16_t value
TEST_F(ExifdatumTest_728, AssignInt16_728) {
    ExifKey key("Exif.Image.Orientation");
    Exifdatum datum(key);
    int16_t val = -1;
    datum = val;
    EXPECT_EQ(datum.toInt64(0), -1);
}

// Test: Assigning int32_t value
TEST_F(ExifdatumTest_728, AssignInt32_728) {
    ExifKey key("Exif.Image.ImageWidth");
    Exifdatum datum(key);
    int32_t val = -100;
    datum = val;
    EXPECT_EQ(datum.toInt64(0), -100);
}

// Test: Assigning URational value
TEST_F(ExifdatumTest_728, AssignURational_728) {
    ExifKey key("Exif.Image.XResolution");
    Exifdatum datum(key);
    URational val(72, 1);
    datum = val;
    EXPECT_EQ(datum.toRational(0), Rational(72, 1));
}

// Test: Assigning Rational value
TEST_F(ExifdatumTest_728, AssignRational_728) {
    ExifKey key("Exif.Photo.ExposureBiasValue");
    Exifdatum datum(key);
    Rational val(-1, 3);
    datum = val;
    Rational result = datum.toRational(0);
    EXPECT_EQ(result.first, -1);
    EXPECT_EQ(result.second, 3);
}

// Test: count() returns 0 when no value is set
TEST_F(ExifdatumTest_728, CountZeroNoValue_728) {
    ExifKey key("Exif.Image.Make");
    Exifdatum datum(key);
    EXPECT_EQ(datum.count(), 0u);
}

// Test: count() returns non-zero after setting a value
TEST_F(ExifdatumTest_728, CountNonZeroAfterSetValue_728) {
    ExifKey key("Exif.Image.Make");
    Exifdatum datum(key);
    datum.setValue("Test");
    EXPECT_GT(datum.count(), 0u);
}

// Test: tag() returns expected tag number
TEST_F(ExifdatumTest_728, TagNumber_728) {
    ExifKey key("Exif.Image.Make");
    Exifdatum datum(key);
    // Make tag is 0x010f
    EXPECT_EQ(datum.tag(), 0x010f);
}

// Test: ifdId() returns a valid IfdId
TEST_F(ExifdatumTest_728, IfdId_728) {
    ExifKey key("Exif.Image.Make");
    Exifdatum datum(key);
    // Should be IfdId::ifd0Id or similar
    EXPECT_NE(datum.ifdId(), IfdId::ifdIdNotSet);
}

// Test: write() with no value set (count == 0)
TEST_F(ExifdatumTest_728, WriteNoValue_728) {
    ExifKey key("Exif.Image.Make");
    Exifdatum datum(key);
    std::ostringstream os;
    datum.write(os, nullptr);
    EXPECT_EQ(os.str(), "");
}

// Test: write() with a value set
TEST_F(ExifdatumTest_728, WriteWithValue_728) {
    ExifKey key("Exif.Image.Make");
    Exifdatum datum(key);
    datum.setValue("Canon");
    std::ostringstream os;
    datum.write(os, nullptr);
    EXPECT_FALSE(os.str().empty());
}

// Test: typeId() after setting a string value
TEST_F(ExifdatumTest_728, TypeIdAfterSetString_728) {
    ExifKey key("Exif.Image.Make");
    Exifdatum datum(key);
    datum.setValue("Test");
    // Make is asciiString type
    EXPECT_EQ(datum.typeId(), asciiString);
}

// Test: typeName() returns non-null
TEST_F(ExifdatumTest_728, TypeName_728) {
    ExifKey key("Exif.Image.Make");
    Exifdatum datum(key);
    datum.setValue("Test");
    EXPECT_NE(datum.typeName(), nullptr);
}

// Test: size() after setting value
TEST_F(ExifdatumTest_728, SizeAfterSetValue_728) {
    ExifKey key("Exif.Image.Make");
    Exifdatum datum(key);
    datum.setValue("Hello");
    EXPECT_GT(datum.size(), 0u);
}

// Test: toString() returns the set string value
TEST_F(ExifdatumTest_728, ToStringReturnsSetValue_728) {
    ExifKey key("Exif.Image.Make");
    Exifdatum datum(key);
    datum.setValue("Olympus");
    EXPECT_EQ(datum.toString(), "Olympus");
}

// Test: getValue() returns a clone of the value
TEST_F(ExifdatumTest_728, GetValueReturnsClone_728) {
    ExifKey key("Exif.Image.Make");
    Exifdatum datum(key);
    datum.setValue("FujiFilm");
    auto val = datum.getValue();
    ASSERT_NE(val, nullptr);
    EXPECT_EQ(val->toString(), "FujiFilm");
}

// Test: ExifData operator[] creates entry if not existing
TEST_F(ExifdatumTest_728, ExifDataOperatorBracket_728) {
    ExifData exifData;
    exifData["Exif.Image.Make"] = "Pentax";
    auto it = exifData.findKey(ExifKey("Exif.Image.Make"));
    ASSERT_NE(it, exifData.end());
    EXPECT_EQ(it->toString(), "Pentax");
}

// Test: ExifData add and findKey
TEST_F(ExifdatumTest_728, ExifDataAddAndFind_728) {
    ExifData exifData;
    ExifKey key("Exif.Image.Model");
    Value::UniquePtr val = Value::create(asciiString);
    val->read("D850");
    exifData.add(key, val.get());
    
    auto it = exifData.findKey(ExifKey("Exif.Image.Model"));
    ASSERT_NE(it, exifData.end());
    EXPECT_EQ(it->toString(), "D850");
}

// Test: ExifData add Exifdatum directly
TEST_F(ExifdatumTest_728, ExifDataAddExifdatum_728) {
    ExifData exifData;
    ExifKey key("Exif.Image.Make");
    Exifdatum datum(key);
    datum.setValue("Leica");
    exifData.add(datum);
    
    auto it = exifData.findKey(ExifKey("Exif.Image.Make"));
    ASSERT_NE(it, exifData.end());
    EXPECT_EQ(it->toString(), "Leica");
}

// Test: ExifData clear
TEST_F(ExifdatumTest_728, ExifDataClear_728) {
    ExifData exifData;
    exifData["Exif.Image.Make"] = "Canon";
    exifData["Exif.Image.Model"] = "EOS R5";
    EXPECT_FALSE(exifData.empty());
    
    exifData.clear();
    EXPECT_TRUE(exifData.empty());
    EXPECT_EQ(exifData.count(), 0u);
}

// Test: ExifData erase single element
TEST_F(ExifdatumTest_728, ExifDataEraseSingle_728) {
    ExifData exifData;
    exifData["Exif.Image.Make"] = "Canon";
    exifData["Exif.Image.Model"] = "EOS R5";
    
    auto it = exifData.findKey(ExifKey("Exif.Image.Make"));
    ASSERT_NE(it, exifData.end());
    exifData.erase(it);
    
    it = exifData.findKey(ExifKey("Exif.Image.Make"));
    EXPECT_EQ(it, exifData.end());
}

// Test: ExifData erase range
TEST_F(ExifdatumTest_728, ExifDataEraseRange_728) {
    ExifData exifData;
    exifData["Exif.Image.Make"] = "Canon";
    exifData["Exif.Image.Model"] = "EOS R5";
    
    exifData.erase(exifData.begin(), exifData.end());
    EXPECT_TRUE(exifData.empty());
}

// Test: ExifData empty on fresh instance
TEST_F(ExifdatumTest_728, ExifDataEmptyInitially_728) {
    ExifData exifData;
    EXPECT_TRUE(exifData.empty());
    EXPECT_EQ(exifData.count(), 0u);
}

// Test: ExifData count
TEST_F(ExifdatumTest_728, ExifDataCount_728) {
    ExifData exifData;
    exifData["Exif.Image.Make"] = "Canon";
    EXPECT_EQ(exifData.count(), 1u);
    exifData["Exif.Image.Model"] = "EOS R5";
    EXPECT_EQ(exifData.count(), 2u);
}

// Test: ExifData sortByKey doesn't crash
TEST_F(ExifdatumTest_728, ExifDataSortByKey_728) {
    ExifData exifData;
    exifData["Exif.Image.Model"] = "EOS R5";
    exifData["Exif.Image.Make"] = "Canon";
    EXPECT_NO_THROW(exifData.sortByKey());
}

// Test: ExifData sortByTag doesn't crash
TEST_F(ExifdatumTest_728, ExifDataSortByTag_728) {
    ExifData exifData;
    exifData["Exif.Image.Model"] = "EOS R5";
    exifData["Exif.Image.Make"] = "Canon";
    EXPECT_NO_THROW(exifData.sortByTag());
}

// Test: findKey returns end() when key not found
TEST_F(ExifdatumTest_728, FindKeyNotFound_728) {
    ExifData exifData;
    auto it = exifData.findKey(ExifKey("Exif.Image.Make"));
    EXPECT_EQ(it, exifData.end());
}

// Test: write() with ExifData pointer
TEST_F(ExifdatumTest_728, WriteWithExifDataPointer_728) {
    ExifData exifData;
    exifData["Exif.Image.Make"] = "Canon";
    
    auto it = exifData.findKey(ExifKey("Exif.Image.Make"));
    ASSERT_NE(it, exifData.end());
    
    std::ostringstream os;
    it->write(os, &exifData);
    EXPECT_FALSE(os.str().empty());
}

// Test: Orientation value written via write()
TEST_F(ExifdatumTest_728, WriteOrientation_728) {
    ExifKey key("Exif.Image.Orientation");
    Exifdatum datum(key);
    uint16_t orientation = 1;
    datum = orientation;
    
    std::ostringstream os;
    datum.write(os, nullptr);
    // Should produce some output (the print function for orientation)
    EXPECT_FALSE(os.str().empty());
}

// Test: Comment type tag uses toString directly
TEST_F(ExifdatumTest_728, WriteCommentTag_728) {
    ExifKey key("Exif.Photo.UserComment");
    Exifdatum datum(key);
    
    // Create a comment value
    Value::UniquePtr val = Value::create(comment);
    val->read("charset=\"Ascii\" Hello World");
    datum.setValue(val.get());
    
    std::ostringstream os;
    datum.write(os, nullptr);
    // For comment type, write() should use value().toString()
    EXPECT_FALSE(os.str().empty());
}

// Test: tagLabel returns a non-empty label for known tags
TEST_F(ExifdatumTest_728, TagLabel_728) {
    ExifKey key("Exif.Image.Make");
    Exifdatum datum(key);
    std::string label = datum.tagLabel();
    EXPECT_FALSE(label.empty());
}

// Test: tagDesc returns description for known tags
TEST_F(ExifdatumTest_728, TagDesc_728) {
    ExifKey key("Exif.Image.Make");
    Exifdatum datum(key);
    // tagDesc may or may not be empty depending on the tag, but should not throw
    EXPECT_NO_THROW(datum.tagDesc());
}

// Test: ifdName returns a valid name
TEST_F(ExifdatumTest_728, IfdName_728) {
    ExifKey key("Exif.Image.Make");
    Exifdatum datum(key);
    const char* name = datum.ifdName();
    EXPECT_NE(name, nullptr);
}

// Test: idx() returns a value (default should be 0)
TEST_F(ExifdatumTest_728, Idx_728) {
    ExifKey key("Exif.Image.Make");
    Exifdatum datum(key);
    EXPECT_NO_THROW(datum.idx());
}

// Test: copy() to a buffer
TEST_F(ExifdatumTest_728, CopyToBuffer_728) {
    ExifKey key("Exif.Image.Orientation");
    Exifdatum datum(key);
    uint16_t val = 1;
    datum = val;
    
    byte buf[256] = {0};
    size_t copied = datum.copy(buf, littleEndian);
    EXPECT_GT(copied, 0u);
}

// Test: typeSize() returns expected size for unsigned short
TEST_F(ExifdatumTest_728, TypeSize_728) {
    ExifKey key("Exif.Image.Orientation");
    Exifdatum datum(key);
    uint16_t val = 1;
    datum = val;
    EXPECT_EQ(datum.typeSize(), 2u);  // unsignedShort is 2 bytes
}

// Test: toFloat conversion
TEST_F(ExifdatumTest_728, ToFloat_728) {
    ExifKey key("Exif.Image.Orientation");
    Exifdatum datum(key);
    uint16_t val = 3;
    datum = val;
    EXPECT_FLOAT_EQ(datum.toFloat(0), 3.0f);
}

// Test: toInt64 conversion
TEST_F(ExifdatumTest_728, ToInt64_728) {
    ExifKey key("Exif.Image.Orientation");
    Exifdatum datum(key);
    uint16_t val = 5;
    datum = val;
    EXPECT_EQ(datum.toInt64(0), 5);
}

// Test: sizeDataArea returns 0 when no data area
TEST_F(ExifdatumTest_728, SizeDataAreaDefault_728) {
    ExifKey key("Exif.Image.Make");
    Exifdatum datum(key);
    datum.setValue("Test");
    EXPECT_EQ(datum.sizeDataArea(), 0u);
}

// Test: dataArea returns empty buffer when no data area
TEST_F(ExifdatumTest_728, DataAreaDefault_728) {
    ExifKey key("Exif.Image.Make");
    Exifdatum datum(key);
    datum.setValue("Test");
    DataBuf buf = datum.dataArea();
    EXPECT_EQ(buf.size(), 0u);
}

// Test: Assigning a Value object
TEST_F(ExifdatumTest_728, AssignValueObject_728) {
    ExifKey key("Exif.Image.Make");
    Exifdatum datum(key);
    
    Value::UniquePtr val = Value::create(asciiString);
    val->read("Panasonic");
    datum = *val;
    
    EXPECT_EQ(datum.toString(), "Panasonic");
}

// Test: setValue with Value pointer
TEST_F(ExifdatumTest_728, SetValuePointer_728) {
    ExifKey key("Exif.Image.Make");
    Exifdatum datum(key);
    
    Value::UniquePtr val = Value::create(asciiString);
    val->read("Sigma");
    datum.setValue(val.get());
    
    EXPECT_EQ(datum.toString(), "Sigma");
}

// Test: Multiple writes to same datum overwrite
TEST_F(ExifdatumTest_728, OverwriteValue_728) {
    ExifKey key("Exif.Image.Make");
    Exifdatum datum(key);
    datum.setValue("First");
    EXPECT_EQ(datum.toString(), "First");
    datum.setValue("Second");
    EXPECT_EQ(datum.toString(), "Second");
}

// Test: ExifData iterator traversal
TEST_F(ExifdatumTest_728, IteratorTraversal_728) {
    ExifData exifData;
    exifData["Exif.Image.Make"] = "Canon";
    exifData["Exif.Image.Model"] = "EOS R5";
    
    int count = 0;
    for (auto it = exifData.begin(); it != exifData.end(); ++it) {
        count++;
    }
    EXPECT_EQ(count, 2);
}
