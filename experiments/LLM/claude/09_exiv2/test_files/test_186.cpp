#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <sstream>

#include "tags_int.hpp"
#include "exiv2/value.hpp"
#include "exiv2/exif.hpp"

using namespace Exiv2;
using namespace Exiv2::Internal;

// Define test TagVocabulary arrays
// TagVocabulary typically has { const char* voc_; const char* label_; }

namespace {

const TagVocabulary testVocab[] = {
    {"auto", "Automatic"},
    {"manual", "Manual"},
    {"program", "Program Mode"},
};

const TagVocabulary singleVocab[] = {
    {"only", "Only Entry"},
};

} // namespace

class PrintTagVocabularyTest_186 : public ::testing::Test {
protected:
    std::ostringstream os;
};

// Test that a known vocabulary value is printed as its label
TEST_F(PrintTagVocabularyTest_186, KnownValuePrintsLabel_186) {
    AsciiValue value;
    value.read("auto");
    
    printTagVocabulary<3, testVocab>(os, value, nullptr);
    
    // The label for "auto" is "Automatic"
    // _() might just pass through the string
    std::string result = os.str();
    EXPECT_TRUE(result.find("Automatic") != std::string::npos) 
        << "Expected 'Automatic' but got: " << result;
}

// Test that another known vocabulary value is printed correctly
TEST_F(PrintTagVocabularyTest_186, KnownValueManualPrintsLabel_186) {
    AsciiValue value;
    value.read("manual");
    
    printTagVocabulary<3, testVocab>(os, value, nullptr);
    
    std::string result = os.str();
    EXPECT_TRUE(result.find("Manual") != std::string::npos)
        << "Expected 'Manual' but got: " << result;
}

// Test that a third known vocabulary value is printed correctly
TEST_F(PrintTagVocabularyTest_186, KnownValueProgramPrintsLabel_186) {
    AsciiValue value;
    value.read("program");
    
    printTagVocabulary<3, testVocab>(os, value, nullptr);
    
    std::string result = os.str();
    EXPECT_TRUE(result.find("Program Mode") != std::string::npos)
        << "Expected 'Program Mode' but got: " << result;
}

// Test that an unknown value prints the fallback format "(value)"
TEST_F(PrintTagVocabularyTest_186, UnknownValuePrintsFallback_186) {
    AsciiValue value;
    value.read("unknown");
    
    printTagVocabulary<3, testVocab>(os, value, nullptr);
    
    std::string result = os.str();
    EXPECT_TRUE(result.find("(") != std::string::npos)
        << "Expected fallback format with parentheses but got: " << result;
    EXPECT_TRUE(result.find(")") != std::string::npos)
        << "Expected closing parenthesis but got: " << result;
}

// Test with empty string value (not found in vocab)
TEST_F(PrintTagVocabularyTest_186, EmptyStringValuePrintsFallback_186) {
    AsciiValue value;
    value.read("");
    
    printTagVocabulary<3, testVocab>(os, value, nullptr);
    
    std::string result = os.str();
    EXPECT_TRUE(result.find("(") != std::string::npos)
        << "Expected fallback format but got: " << result;
}

// Test with single-element vocabulary array - found case
TEST_F(PrintTagVocabularyTest_186, SingleElementVocabFound_186) {
    AsciiValue value;
    value.read("only");
    
    printTagVocabulary<1, singleVocab>(os, value, nullptr);
    
    std::string result = os.str();
    EXPECT_TRUE(result.find("Only Entry") != std::string::npos)
        << "Expected 'Only Entry' but got: " << result;
}

// Test with single-element vocabulary array - not found case
TEST_F(PrintTagVocabularyTest_186, SingleElementVocabNotFound_186) {
    AsciiValue value;
    value.read("missing");
    
    printTagVocabulary<1, singleVocab>(os, value, nullptr);
    
    std::string result = os.str();
    EXPECT_TRUE(result.find("(") != std::string::npos)
        << "Expected fallback format but got: " << result;
}

// Test that the function returns the ostream reference (chaining)
TEST_F(PrintTagVocabularyTest_186, ReturnsOstreamReference_186) {
    AsciiValue value;
    value.read("auto");
    
    std::ostream& returned = printTagVocabulary<3, testVocab>(os, value, nullptr);
    
    EXPECT_EQ(&returned, &os);
}

// Test that the function returns the ostream reference for unknown values too
TEST_F(PrintTagVocabularyTest_186, ReturnsOstreamReferenceForUnknown_186) {
    AsciiValue value;
    value.read("notfound");
    
    std::ostream& returned = printTagVocabulary<3, testVocab>(os, value, nullptr);
    
    EXPECT_EQ(&returned, &os);
}

// Test with nullptr ExifData parameter (should work fine as it's unused)
TEST_F(PrintTagVocabularyTest_186, NullExifDataWorks_186) {
    AsciiValue value;
    value.read("manual");
    
    EXPECT_NO_THROW({
        printTagVocabulary<3, testVocab>(os, value, nullptr);
    });
    
    std::string result = os.str();
    EXPECT_TRUE(result.find("Manual") != std::string::npos);
}

// Test case sensitivity - if the vocab has "auto", "Auto" should not match
TEST_F(PrintTagVocabularyTest_186, CaseSensitiveLookup_186) {
    AsciiValue value;
    value.read("Auto");
    
    printTagVocabulary<3, testVocab>(os, value, nullptr);
    
    std::string result = os.str();
    // "Auto" != "auto", so it should print fallback
    EXPECT_TRUE(result.find("(") != std::string::npos)
        << "Expected case-sensitive mismatch fallback but got: " << result;
}
