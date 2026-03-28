#include <gtest/gtest.h>
#include <sstream>
#include <string>
#include <exiv2/value.hpp>
#include <exiv2/exif.hpp>

namespace Exiv2 {
namespace Internal {
std::ostream& print0x8298(std::ostream& os, const Value& value, const ExifData*);
}
}

using namespace Exiv2;
using namespace Exiv2::Internal;

class Print0x8298Test_1394 : public ::testing::Test {
protected:
    std::ostringstream os;
};

// Test: Simple string without null character outputs as-is
TEST_F(Print0x8298Test_1394, SimpleStringNoNull_1394) {
    AsciiValue value;
    value.read("John Doe");
    print0x8298(os, value, nullptr);
    EXPECT_EQ(os.str(), "John Doe");
}

// Test: String with null separator, photographer and editor both present
TEST_F(Print0x8298Test_1394, PhotographerAndEditor_1394) {
    // Create a string with embedded null
    std::string data("Photographer");
    data += '\0';
    data += "Editor";
    
    DataBuf buf(reinterpret_cast<const byte*>(data.data()), data.size());
    AsciiValue value;
    value.read(reinterpret_cast<const byte*>(data.data()), data.size(), invalidByteOrder);
    
    print0x8298(os, value, nullptr);
    std::string result = os.str();
    // Should contain photographer, separator, and editor
    EXPECT_NE(result.find("Photographer"), std::string::npos);
    EXPECT_NE(result.find("Editor"), std::string::npos);
}

// Test: String with null but empty editor
TEST_F(Print0x8298Test_1394, PhotographerOnlyEmptyEditor_1394) {
    std::string data("Photographer");
    data += '\0';
    
    DataBuf buf(reinterpret_cast<const byte*>(data.data()), data.size());
    AsciiValue value;
    value.read(reinterpret_cast<const byte*>(data.data()), data.size(), invalidByteOrder);
    
    print0x8298(os, value, nullptr);
    std::string result = os.str();
    EXPECT_NE(result.find("Photographer"), std::string::npos);
}

// Test: Photographer is a single space with editor present
TEST_F(Print0x8298Test_1394, SpacePhotographerWithEditor_1394) {
    std::string data(" ");
    data += '\0';
    data += "Editor";
    
    AsciiValue value;
    value.read(reinterpret_cast<const byte*>(data.data()), data.size(), invalidByteOrder);
    
    print0x8298(os, value, nullptr);
    std::string result = os.str();
    // Photographer is " " so it should NOT be printed
    // Editor should be printed without comma prefix
    EXPECT_NE(result.find("Editor"), std::string::npos);
    // Should not start with comma
    if (!result.empty()) {
        EXPECT_NE(result.substr(0, 2), ", ");
    }
}

// Test: Photographer is a single space with empty editor
TEST_F(Print0x8298Test_1394, SpacePhotographerEmptyEditor_1394) {
    std::string data(" ");
    data += '\0';
    
    AsciiValue value;
    value.read(reinterpret_cast<const byte*>(data.data()), data.size(), invalidByteOrder);
    
    print0x8298(os, value, nullptr);
    std::string result = os.str();
    // Both photographer=" " (skipped) and editor="" (empty, skipped)
    EXPECT_EQ(result, "");
}

// Test: Empty string
TEST_F(Print0x8298Test_1394, EmptyString_1394) {
    AsciiValue value;
    value.read("");
    print0x8298(os, value, nullptr);
    EXPECT_EQ(os.str(), "");
}

// Test: Null pointer for ExifData parameter
TEST_F(Print0x8298Test_1394, NullExifDataParam_1394) {
    AsciiValue value;
    value.read("Test Copyright");
    print0x8298(os, value, nullptr);
    EXPECT_EQ(os.str(), "Test Copyright");
}

// Test: String with multiple null characters (only first null matters)
TEST_F(Print0x8298Test_1394, MultipleNulls_1394) {
    std::string data("Photo");
    data += '\0';
    data += "Edit";
    data += '\0';
    data += "Extra";
    
    AsciiValue value;
    value.read(reinterpret_cast<const byte*>(data.data()), data.size(), invalidByteOrder);
    
    print0x8298(os, value, nullptr);
    std::string result = os.str();
    EXPECT_NE(result.find("Photo"), std::string::npos);
}

// Test: Only null character
TEST_F(Print0x8298Test_1394, OnlyNull_1394) {
    std::string data;
    data += '\0';
    
    AsciiValue value;
    value.read(reinterpret_cast<const byte*>(data.data()), data.size(), invalidByteOrder);
    
    print0x8298(os, value, nullptr);
    // Photographer is empty (not " "), editor is empty
    // Empty photographer != " " so it would be printed (empty string)
    // Editor is empty so nothing additional
    std::string result = os.str();
    // Should not crash; result depends on implementation
}

// Test: Verify the comma separator format between photographer and editor
TEST_F(Print0x8298Test_1394, CommaSeparator_1394) {
    std::string data("Alice");
    data += '\0';
    data += "Bob";
    
    AsciiValue value;
    value.read(reinterpret_cast<const byte*>(data.data()), data.size(), invalidByteOrder);
    
    print0x8298(os, value, nullptr);
    std::string result = os.str();
    // Should be "Alice, Bob"
    EXPECT_NE(result.find(", "), std::string::npos);
}

// Test: Long copyright string without null
TEST_F(Print0x8298Test_1394, LongStringNoNull_1394) {
    std::string longStr(1000, 'A');
    AsciiValue value;
    value.read(longStr);
    print0x8298(os, value, nullptr);
    EXPECT_EQ(os.str(), longStr);
}

// Test: Return value is the same ostream
TEST_F(Print0x8298Test_1394, ReturnsSameStream_1394) {
    AsciiValue value;
    value.read("Test");
    std::ostream& result = print0x8298(os, value, nullptr);
    EXPECT_EQ(&result, &os);
}
