#include <gtest/gtest.h>
#include <exiv2/exif.hpp>
#include <exiv2/exifkey.hpp>
#include <exiv2/value.hpp>
#include <exiv2/types.hpp>
#include <string>

// We need to access the getMetaVersion function from the Internal namespace.
// Since it's a static function in sonymn_int.cpp, we need to include it or
// declare it. Since it's static, we'll need to test it indirectly or include
// the source. For testing purposes, we'll include the implementation file.
// However, since it's static, we need a workaround.

// Forward declaration won't work for static functions in another TU.
// We'll define a test helper that includes the source or redefine access.
// Since the function is static in sonymn_int.cpp, we include it directly.

// To test a static function, we include the .cpp file
// This is a common testing pattern for static functions
namespace TestInclude {
#include "sonymn_int.cpp"
}

using namespace Exiv2;

class GetMetaVersionTest_1586 : public ::testing::Test {
protected:
    ExifData exifData_;
    std::string val_;
};

// Test: When the key "Exif.SonySInfo1.MetaVersion" exists with asciiString type and non-empty value
TEST_F(GetMetaVersionTest_1586, ReturnsTrue_WhenKeyExistsWithValidAsciiString_1586) {
    exifData_["Exif.SonySInfo1.MetaVersion"] = "DC7303320222000";
    
    bool result = TestInclude::Exiv2::Internal::getMetaVersion(&exifData_, val_);
    
    EXPECT_TRUE(result);
    EXPECT_EQ(val_, "DC7303320222000");
}

// Test: When the key "Exif.SonySInfo1.MetaVersion" does not exist in metadata
TEST_F(GetMetaVersionTest_1586, ReturnsFalse_WhenKeyDoesNotExist_1586) {
    // exifData_ is empty, key does not exist
    bool result = TestInclude::Exiv2::Internal::getMetaVersion(&exifData_, val_);
    
    EXPECT_FALSE(result);
    EXPECT_EQ(val_, "");
}

// Test: When key exists but type is not asciiString (e.g., unsignedShort)
TEST_F(GetMetaVersionTest_1586, ReturnsFalse_WhenTypeIsNotAsciiString_1586) {
    // Add the key with a non-ascii type
    ExifKey key("Exif.SonySInfo1.MetaVersion");
    auto value = Value::create(unsignedShort);
    value->read("42");
    exifData_.add(key, value.get());
    
    bool result = TestInclude::Exiv2::Internal::getMetaVersion(&exifData_, val_);
    
    EXPECT_FALSE(result);
    EXPECT_EQ(val_, "");
}

// Test: When key exists with asciiString type but the string value is a normal version string
TEST_F(GetMetaVersionTest_1586, ReturnsCorrectValue_WhenVersionStringIsSet_1586) {
    exifData_["Exif.SonySInfo1.MetaVersion"] = "1.0";
    
    bool result = TestInclude::Exiv2::Internal::getMetaVersion(&exifData_, val_);
    
    EXPECT_TRUE(result);
    EXPECT_EQ(val_, "1.0");
}

// Test: When val already has a value, it gets overwritten on success
TEST_F(GetMetaVersionTest_1586, OverwritesExistingVal_OnSuccess_1586) {
    val_ = "old_value";
    exifData_["Exif.SonySInfo1.MetaVersion"] = "new_version";
    
    bool result = TestInclude::Exiv2::Internal::getMetaVersion(&exifData_, val_);
    
    EXPECT_TRUE(result);
    EXPECT_EQ(val_, "new_version");
}

// Test: When val already has a value, it gets cleared on failure (key not found)
TEST_F(GetMetaVersionTest_1586, ClearsVal_OnFailure_1586) {
    val_ = "old_value";
    
    bool result = TestInclude::Exiv2::Internal::getMetaVersion(&exifData_, val_);
    
    EXPECT_FALSE(result);
    EXPECT_EQ(val_, "");
}

// Test: When a different key exists but not the target key
TEST_F(GetMetaVersionTest_1586, ReturnsFalse_WhenDifferentKeyExists_1586) {
    exifData_["Exif.Image.Make"] = "Sony";
    
    bool result = TestInclude::Exiv2::Internal::getMetaVersion(&exifData_, val_);
    
    EXPECT_FALSE(result);
    EXPECT_EQ(val_, "");
}

// Test: Key exists with asciiString containing a single character
TEST_F(GetMetaVersionTest_1586, ReturnsTrue_WhenSingleCharacterString_1586) {
    exifData_["Exif.SonySInfo1.MetaVersion"] = "A";
    
    bool result = TestInclude::Exiv2::Internal::getMetaVersion(&exifData_, val_);
    
    EXPECT_TRUE(result);
    EXPECT_EQ(val_, "A");
}

// Test: Key exists with a long version string
TEST_F(GetMetaVersionTest_1586, ReturnsTrue_WhenLongVersionString_1586) {
    std::string longVersion(256, 'v');
    exifData_["Exif.SonySInfo1.MetaVersion"] = longVersion;
    
    bool result = TestInclude::Exiv2::Internal::getMetaVersion(&exifData_, val_);
    
    EXPECT_TRUE(result);
    EXPECT_EQ(val_, longVersion);
}

// Test: Multiple keys exist, including the target key
TEST_F(GetMetaVersionTest_1586, ReturnsTrue_WhenMultipleKeysExistIncludingTarget_1586) {
    exifData_["Exif.Image.Make"] = "Sony";
    exifData_["Exif.SonySInfo1.MetaVersion"] = "TestVersion";
    exifData_["Exif.Image.Model"] = "A7III";
    
    bool result = TestInclude::Exiv2::Internal::getMetaVersion(&exifData_, val_);
    
    EXPECT_TRUE(result);
    EXPECT_EQ(val_, "TestVersion");
}

// Test: Key exists with asciiString containing spaces
TEST_F(GetMetaVersionTest_1586, ReturnsTrue_WhenStringContainsSpaces_1586) {
    exifData_["Exif.SonySInfo1.MetaVersion"] = "Version 1.0 Beta";
    
    bool result = TestInclude::Exiv2::Internal::getMetaVersion(&exifData_, val_);
    
    EXPECT_TRUE(result);
    EXPECT_EQ(val_, "Version 1.0 Beta");
}

// Test: Key exists with asciiString containing special characters
TEST_F(GetMetaVersionTest_1586, ReturnsTrue_WhenStringContainsSpecialChars_1586) {
    exifData_["Exif.SonySInfo1.MetaVersion"] = "v1.0-rc1+build.123";
    
    bool result = TestInclude::Exiv2::Internal::getMetaVersion(&exifData_, val_);
    
    EXPECT_TRUE(result);
    EXPECT_EQ(val_, "v1.0-rc1+build.123");
}
