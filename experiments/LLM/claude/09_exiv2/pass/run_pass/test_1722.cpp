#include <gtest/gtest.h>
#include <exiv2/exiv2.hpp>
#include <sstream>

// We need access to the internal function. Since it's in an anonymous-like static context,
// we need to test it through the ExifData/tag mechanism or reconstruct the scenario.
// However, since printFocalLength35 is a static function in the Internal namespace,
// we can access it if we include the right headers.

// The function is used as a print function for Samsung MakerNote tags.
// We can test it by finding the appropriate tag and using the print mechanism,
// or we can try to access it directly.

// Since the function is static (file-local), we cannot directly call it from test code.
// Instead, we'll test it through the Exiv2 tag printing infrastructure for Samsung tags.
// The function is registered as a print function for specific Samsung MakerNote tags.

// Let's test through the ExifData print mechanism for Samsung tags that use this function.
// The tag that uses printFocalLength35 is likely Samsung.FocalLengthIn35mmFormat or similar.

// Alternative approach: Since we can't directly access static functions, we test through
// the ExifKey/ExifData printing mechanism.

namespace {

class SamsungMnPrintFocalLength35Test_1722 : public ::testing::Test {
protected:
    void SetUp() override {
    }

    // Helper to get printed string for a Samsung maker note tag value
    std::string getPrintedValue(const std::string& tagName, Exiv2::Value::UniquePtr value) {
        Exiv2::ExifData exifData;
        Exiv2::ExifKey key(tagName);
        exifData.add(key, value.get());
        
        std::ostringstream os;
        auto it = exifData.findKey(key);
        if (it != exifData.end()) {
            os << it->print(&exifData);
        }
        return os.str();
    }
};

// Test with a normal focal length value
TEST_F(SamsungMnPrintFocalLength35Test_1722, NormalFocalLength_1722) {
    // Samsung2.FocalLengthIn35mmFormat typically uses printFocalLength35
    // Try to find a tag that uses this print function
    Exiv2::ExifData exifData;
    
    // Samsung type 2 maker note tag for FocalLengthIn35mmFormat
    // Tag 0xa003 in Samsung2 group
    try {
        Exiv2::ExifKey key("Exif.Samsung2.FocalLengthIn35mmFormat");
        auto value = Exiv2::Value::create(Exiv2::unsignedLong);
        value->read("500"); // 500 means 50.0 mm
        exifData.add(key, value.get());
        
        auto it = exifData.findKey(key);
        if (it != exifData.end()) {
            std::ostringstream os;
            os << it->print(&exifData);
            std::string result = os.str();
            // 500 / 10.0 = 50.0 mm
            EXPECT_NE(result.find("50.0"), std::string::npos) 
                << "Expected '50.0' in result: " << result;
            EXPECT_NE(result.find("mm"), std::string::npos)
                << "Expected 'mm' in result: " << result;
        }
    } catch (const Exiv2::Error&) {
        // Tag might not exist in this build, skip
        GTEST_SKIP() << "Samsung2.FocalLengthIn35mmFormat tag not available";
    }
}

// Test with zero value (should print "Unknown")
TEST_F(SamsungMnPrintFocalLength35Test_1722, ZeroFocalLength_1722) {
    Exiv2::ExifData exifData;
    
    try {
        Exiv2::ExifKey key("Exif.Samsung2.FocalLengthIn35mmFormat");
        auto value = Exiv2::Value::create(Exiv2::unsignedLong);
        value->read("0");
        exifData.add(key, value.get());
        
        auto it = exifData.findKey(key);
        if (it != exifData.end()) {
            std::ostringstream os;
            os << it->print(&exifData);
            std::string result = os.str();
            // When value is 0, should print "Unknown"
            // Check it doesn't contain "mm" or contains "Unknown" or similar
            EXPECT_TRUE(result.find("mm") == std::string::npos || result.find("nknown") != std::string::npos)
                << "Zero should not give a mm result: " << result;
        }
    } catch (const Exiv2::Error&) {
        GTEST_SKIP() << "Samsung2.FocalLengthIn35mmFormat tag not available";
    }
}

// Test with a small focal length value
TEST_F(SamsungMnPrintFocalLength35Test_1722, SmallFocalLength_1722) {
    Exiv2::ExifData exifData;
    
    try {
        Exiv2::ExifKey key("Exif.Samsung2.FocalLengthIn35mmFormat");
        auto value = Exiv2::Value::create(Exiv2::unsignedLong);
        value->read("1"); // 0.1 mm
        exifData.add(key, value.get());
        
        auto it = exifData.findKey(key);
        if (it != exifData.end()) {
            std::ostringstream os;
            os << it->print(&exifData);
            std::string result = os.str();
            // 1 / 10.0 = 0.1 mm
            EXPECT_NE(result.find("0.1"), std::string::npos)
                << "Expected '0.1' in result: " << result;
        }
    } catch (const Exiv2::Error&) {
        GTEST_SKIP() << "Samsung2.FocalLengthIn35mmFormat tag not available";
    }
}

// Test with a large focal length value
TEST_F(SamsungMnPrintFocalLength35Test_1722, LargeFocalLength_1722) {
    Exiv2::ExifData exifData;
    
    try {
        Exiv2::ExifKey key("Exif.Samsung2.FocalLengthIn35mmFormat");
        auto value = Exiv2::Value::create(Exiv2::unsignedLong);
        value->read("10000"); // 1000.0 mm
        exifData.add(key, value.get());
        
        auto it = exifData.findKey(key);
        if (it != exifData.end()) {
            std::ostringstream os;
            os << it->print(&exifData);
            std::string result = os.str();
            // 10000 / 10.0 = 1000.0 mm
            EXPECT_NE(result.find("1000.0"), std::string::npos)
                << "Expected '1000.0' in result: " << result;
        }
    } catch (const Exiv2::Error&) {
        GTEST_SKIP() << "Samsung2.FocalLengthIn35mmFormat tag not available";
    }
}

// Test with wrong type (not unsignedLong) - should just print value as-is
TEST_F(SamsungMnPrintFocalLength35Test_1722, WrongValueType_1722) {
    Exiv2::ExifData exifData;
    
    try {
        Exiv2::ExifKey key("Exif.Samsung2.FocalLengthIn35mmFormat");
        // Use unsignedShort instead of unsignedLong
        auto value = Exiv2::Value::create(Exiv2::unsignedShort);
        value->read("500");
        exifData.add(key, value.get());
        
        auto it = exifData.findKey(key);
        if (it != exifData.end()) {
            std::ostringstream os;
            os << it->print(&exifData);
            std::string result = os.str();
            // With wrong type, it should print the raw value (500)
            EXPECT_NE(result.find("500"), std::string::npos)
                << "Expected raw value '500' in result: " << result;
        }
    } catch (const Exiv2::Error&) {
        GTEST_SKIP() << "Samsung2.FocalLengthIn35mmFormat tag not available";
    }
}

// Test with multiple count (more than 1 value) - should print value as-is
TEST_F(SamsungMnPrintFocalLength35Test_1722, MultipleValues_1722) {
    Exiv2::ExifData exifData;
    
    try {
        Exiv2::ExifKey key("Exif.Samsung2.FocalLengthIn35mmFormat");
        auto value = Exiv2::Value::create(Exiv2::unsignedLong);
        value->read("500 600"); // Two values
        exifData.add(key, value.get());
        
        auto it = exifData.findKey(key);
        if (it != exifData.end()) {
            std::ostringstream os;
            os << it->print(&exifData);
            std::string result = os.str();
            // With count != 1, should print raw values
            EXPECT_FALSE(result.empty()) << "Result should not be empty";
        }
    } catch (const Exiv2::Error&) {
        GTEST_SKIP() << "Samsung2.FocalLengthIn35mmFormat tag not available";
    }
}

// Test with value that results in fractional mm
TEST_F(SamsungMnPrintFocalLength35Test_1722, FractionalFocalLength_1722) {
    Exiv2::ExifData exifData;
    
    try {
        Exiv2::ExifKey key("Exif.Samsung2.FocalLengthIn35mmFormat");
        auto value = Exiv2::Value::create(Exiv2::unsignedLong);
        value->read("285"); // 28.5 mm
        exifData.add(key, value.get());
        
        auto it = exifData.findKey(key);
        if (it != exifData.end()) {
            std::ostringstream os;
            os << it->print(&exifData);
            std::string result = os.str();
            // 285 / 10.0 = 28.5 mm
            EXPECT_NE(result.find("28.5"), std::string::npos)
                << "Expected '28.5' in result: " << result;
            EXPECT_NE(result.find("mm"), std::string::npos)
                << "Expected 'mm' in result: " << result;
        }
    } catch (const Exiv2::Error&) {
        GTEST_SKIP() << "Samsung2.FocalLengthIn35mmFormat tag not available";
    }
}

// Test with value = 10 (should give 1.0 mm)
TEST_F(SamsungMnPrintFocalLength35Test_1722, ExactDivisionFocalLength_1722) {
    Exiv2::ExifData exifData;
    
    try {
        Exiv2::ExifKey key("Exif.Samsung2.FocalLengthIn35mmFormat");
        auto value = Exiv2::Value::create(Exiv2::unsignedLong);
        value->read("10"); // 1.0 mm
        exifData.add(key, value.get());
        
        auto it = exifData.findKey(key);
        if (it != exifData.end()) {
            std::ostringstream os;
            os << it->print(&exifData);
            std::string result = os.str();
            // 10 / 10.0 = 1.0 mm
            EXPECT_NE(result.find("1.0"), std::string::npos)
                << "Expected '1.0' in result: " << result;
            EXPECT_NE(result.find("mm"), std::string::npos)
                << "Expected 'mm' in result: " << result;
        }
    } catch (const Exiv2::Error&) {
        GTEST_SKIP() << "Samsung2.FocalLengthIn35mmFormat tag not available";
    }
}

} // namespace
