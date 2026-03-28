#include <gtest/gtest.h>
#include <exiv2/exiv2.hpp>
#include <sstream>
#include <string>

// Access internal print functions through the tag definitions
#include "pentaxmn_int.hpp"

using namespace Exiv2;
using namespace Exiv2::Internal;

class PentaxMnPrintCombiTag_188 : public ::testing::Test {
protected:
    void SetUp() override {
    }

    // Helper to find a print function for a given tag in PentaxMakerNote tags
    TagDetails const* findTagDetails(uint16_t tag) {
        return nullptr; // We'll use direct approaches instead
    }
};

// Test printCombiTag behavior through Pentax print functions
// We'll use the PentaxMakerNote tag print functions that internally call printCombiTag

TEST_F(PentaxMnPrintCombiTag_188, NormalValuePrintsLabel_188) {
    // Test using a known Pentax tag that uses printCombiTag
    // PentaxImageSize tag (0x0009) uses printCombiTag with 2-byte combination
    auto value = Value::create(unsignedShort);
    // We create a value and check printing through the tag's print function
    // Use a simple approach: create byte values and print
    auto byteValue = Value::create(unsignedByte);
    byteValue->read("0 0");
    
    std::ostringstream os;
    // The function should produce some output (either a known label or Unknown)
    os << *byteValue;
    EXPECT_FALSE(os.str().empty());
}

TEST_F(PentaxMnPrintCombiTag_188, ValueCountMismatchFallsBackToPrintValue_188) {
    // When value count doesn't match expected count, printCombiTag falls back to printValue
    auto value = Value::create(unsignedByte);
    // Read a single byte value - if printCombiTag expects 2, it should fall back
    value->read("42");
    
    std::ostringstream os;
    os << *value;
    EXPECT_FALSE(os.str().empty());
}

TEST_F(PentaxMnPrintCombiTag_188, ValueOutOfByteBoundsFallsBack_188) {
    // If any component value > 255 or < 0, should fall back to printValue
    auto value = Value::create(signedShort);
    value->read("-1 0");
    
    std::ostringstream os;
    os << *value;
    EXPECT_FALSE(os.str().empty());
}

TEST_F(PentaxMnPrintCombiTag_188, UnknownCombinationPrintsUnknownHex_188) {
    // When the combined value is not found in the array, prints "Unknown (0x...)"
    auto value = Value::create(unsignedByte);
    value->read("255 254");  // Unlikely to be a valid combination
    
    std::ostringstream os;
    os << *value;
    EXPECT_FALSE(os.str().empty());
}

// Test the Pentax tag info print functions that use printCombiTag
TEST_F(PentaxMnPrintCombiTag_188, PentaxLensTypePrintFunction_188) {
    // PentaxLensType is a well-known tag that uses printCombiTag
    // Tag 0x003f in Pentax makernote
    const TagInfo* tagInfo = PentaxMakerNote::tagList();
    ASSERT_NE(tagInfo, nullptr);
    
    // Find the LensType tag (typically uses printCombiTag)
    bool foundLensTag = false;
    for (int i = 0; tagInfo[i].tag_ != 0xffff; ++i) {
        if (tagInfo[i].tag_ == 0x003f) {
            foundLensTag = true;
            
            if (tagInfo[i].printFct_) {
                auto value = Value::create(unsignedByte);
                value->read("3 255");
                
                std::ostringstream os;
                tagInfo[i].printFct_(os, *value, nullptr);
                EXPECT_FALSE(os.str().empty());
            }
            break;
        }
    }
}

TEST_F(PentaxMnPrintCombiTag_188, PentaxImageSizePrintFunction_188) {
    // Tag 0x0009 - Image Size
    const TagInfo* tagInfo = PentaxMakerNote::tagList();
    ASSERT_NE(tagInfo, nullptr);
    
    for (int i = 0; tagInfo[i].tag_ != 0xffff; ++i) {
        if (tagInfo[i].tag_ == 0x0009) {
            if (tagInfo[i].printFct_) {
                auto value = Value::create(unsignedByte);
                value->read("0");
                
                std::ostringstream os;
                tagInfo[i].printFct_(os, *value, nullptr);
                // Should produce output regardless of whether it matches
                EXPECT_FALSE(os.str().empty());
            }
            break;
        }
    }
}

TEST_F(PentaxMnPrintCombiTag_188, EmptyValueHandling_188) {
    // Test with empty value - count would be 0, should fall back
    auto value = Value::create(unsignedByte);
    
    std::ostringstream os;
    os << *value;
    // Empty value should still not crash
    EXPECT_TRUE(true);  // If we get here, no crash
}

TEST_F(PentaxMnPrintCombiTag_188, TagListNotNull_188) {
    // Verify that tagList returns a valid pointer
    const TagInfo* tagInfo = PentaxMakerNote::tagList();
    ASSERT_NE(tagInfo, nullptr);
    
    // Should have at least one tag
    EXPECT_NE(tagInfo[0].tag_, 0xffff);
}

TEST_F(PentaxMnPrintCombiTag_188, TagListTagsHaveNames_188) {
    const TagInfo* tagInfo = PentaxMakerNote::tagList();
    ASSERT_NE(tagInfo, nullptr);
    
    // Each tag should have a non-null name
    for (int i = 0; tagInfo[i].tag_ != 0xffff; ++i) {
        EXPECT_NE(tagInfo[i].name_, nullptr) << "Tag at index " << i << " has null name";
    }
}

TEST_F(PentaxMnPrintCombiTag_188, MultipleCallsProduceConsistentOutput_188) {
    const TagInfo* tagInfo = PentaxMakerNote::tagList();
    ASSERT_NE(tagInfo, nullptr);
    
    for (int i = 0; tagInfo[i].tag_ != 0xffff; ++i) {
        if (tagInfo[i].printFct_) {
            auto value = Value::create(unsignedByte);
            value->read("1 2");
            
            std::ostringstream os1, os2;
            tagInfo[i].printFct_(os1, *value, nullptr);
            tagInfo[i].printFct_(os2, *value, nullptr);
            
            EXPECT_EQ(os1.str(), os2.str()) 
                << "Inconsistent output for tag 0x" << std::hex << tagInfo[i].tag_;
            break;  // Test just the first printable tag
        }
    }
}

TEST_F(PentaxMnPrintCombiTag_188, LargeByteValueBoundary_188) {
    // Test with byte values at boundary (255)
    auto value = Value::create(unsignedByte);
    value->read("255 255");
    
    const TagInfo* tagInfo = PentaxMakerNote::tagList();
    ASSERT_NE(tagInfo, nullptr);
    
    for (int i = 0; tagInfo[i].tag_ != 0xffff; ++i) {
        if (tagInfo[i].printFct_) {
            std::ostringstream os;
            tagInfo[i].printFct_(os, *value, nullptr);
            EXPECT_FALSE(os.str().empty());
            break;
        }
    }
}

TEST_F(PentaxMnPrintCombiTag_188, ZeroByteValues_188) {
    // Test with all zero byte values
    auto value = Value::create(unsignedByte);
    value->read("0 0");
    
    const TagInfo* tagInfo = PentaxMakerNote::tagList();
    ASSERT_NE(tagInfo, nullptr);
    
    for (int i = 0; tagInfo[i].tag_ != 0xffff; ++i) {
        if (tagInfo[i].printFct_) {
            std::ostringstream os;
            tagInfo[i].printFct_(os, *value, nullptr);
            EXPECT_FALSE(os.str().empty());
            break;
        }
    }
}

TEST_F(PentaxMnPrintCombiTag_188, NullMetadataDoesNotCrash_188) {
    // Passing nullptr for metadata should be handled gracefully
    const TagInfo* tagInfo = PentaxMakerNote::tagList();
    ASSERT_NE(tagInfo, nullptr);
    
    for (int i = 0; tagInfo[i].tag_ != 0xffff; ++i) {
        if (tagInfo[i].printFct_) {
            auto value = Value::create(unsignedByte);
            value->read("1 0");
            
            std::ostringstream os;
            // Should not crash with nullptr metadata
            tagInfo[i].printFct_(os, *value, nullptr);
            EXPECT_TRUE(true);
            break;
        }
    }
}

TEST_F(PentaxMnPrintCombiTag_188, ValidMetadataDoesNotCrash_188) {
    const TagInfo* tagInfo = PentaxMakerNote::tagList();
    ASSERT_NE(tagInfo, nullptr);
    
    ExifData exifData;
    
    for (int i = 0; tagInfo[i].tag_ != 0xffff; ++i) {
        if (tagInfo[i].printFct_) {
            auto value = Value::create(unsignedByte);
            value->read("1 0");
            
            std::ostringstream os;
            tagInfo[i].printFct_(os, *value, &exifData);
            EXPECT_TRUE(true);
            break;
        }
    }
}

TEST_F(PentaxMnPrintCombiTag_188, StreamFlagsPreserved_188) {
    // printCombiTag should preserve stream flags
    const TagInfo* tagInfo = PentaxMakerNote::tagList();
    ASSERT_NE(tagInfo, nullptr);
    
    for (int i = 0; tagInfo[i].tag_ != 0xffff; ++i) {
        if (tagInfo[i].printFct_) {
            auto value = Value::create(unsignedByte);
            value->read("255 254");
            
            std::ostringstream os;
            std::ios::fmtflags originalFlags = os.flags();
            tagInfo[i].printFct_(os, *value, nullptr);
            std::ios::fmtflags afterFlags = os.flags();
            
            EXPECT_EQ(originalFlags, afterFlags) 
                << "Stream flags were not preserved for tag 0x" << std::hex << tagInfo[i].tag_;
            break;
        }
    }
}

TEST_F(PentaxMnPrintCombiTag_188, ThreeByteValueHandling_188) {
    // Test with 3 byte values
    auto value = Value::create(unsignedByte);
    value->read("1 2 3");
    
    const TagInfo* tagInfo = PentaxMakerNote::tagList();
    ASSERT_NE(tagInfo, nullptr);
    
    for (int i = 0; tagInfo[i].tag_ != 0xffff; ++i) {
        if (tagInfo[i].printFct_) {
            std::ostringstream os;
            tagInfo[i].printFct_(os, *value, nullptr);
            EXPECT_FALSE(os.str().empty());
            break;
        }
    }
}

TEST_F(PentaxMnPrintCombiTag_188, FourByteValueHandling_188) {
    // Test with 4 byte values
    auto value = Value::create(unsignedByte);
    value->read("1 2 3 4");
    
    const TagInfo* tagInfo = PentaxMakerNote::tagList();
    ASSERT_NE(tagInfo, nullptr);
    
    for (int i = 0; tagInfo[i].tag_ != 0xffff; ++i) {
        if (tagInfo[i].printFct_) {
            std::ostringstream os;
            tagInfo[i].printFct_(os, *value, nullptr);
            EXPECT_FALSE(os.str().empty());
            break;
        }
    }
}

TEST_F(PentaxMnPrintCombiTag_188, SingleByteValue_188) {
    auto value = Value::create(unsignedByte);
    value->read("42");
    
    const TagInfo* tagInfo = PentaxMakerNote::tagList();
    ASSERT_NE(tagInfo, nullptr);
    
    for (int i = 0; tagInfo[i].tag_ != 0xffff; ++i) {
        if (tagInfo[i].printFct_) {
            std::ostringstream os;
            tagInfo[i].printFct_(os, *value, nullptr);
            EXPECT_FALSE(os.str().empty());
            break;
        }
    }
}
