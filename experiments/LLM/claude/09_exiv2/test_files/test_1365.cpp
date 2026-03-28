#include <gtest/gtest.h>
#include <sstream>
#include <string>

#include <exiv2/tags.hpp>
#include <exiv2/exiv2.hpp>

// Internal declarations needed
namespace Exiv2 {
namespace Internal {
void taglist(std::ostream& os, IfdId ifdId);
const TagInfo* tagList(IfdId ifdId);
}
}

class TaglistTest_1365 : public ::testing::Test {
protected:
    std::ostringstream oss;
};

// Test that taglist with a known valid IfdId (ifdIdExif) produces non-empty output
TEST_F(TaglistTest_1365, ValidIfdIdProducesOutput_1365) {
    Exiv2::Internal::taglist(oss, Exiv2::IfdId::ifd0Id);
    std::string result = oss.str();
    // A valid IFD should have at least some tags
    EXPECT_FALSE(result.empty());
}

// Test that taglist output ends with newline for valid IFD
TEST_F(TaglistTest_1365, OutputEndsWithNewline_1365) {
    Exiv2::Internal::taglist(oss, Exiv2::IfdId::ifd0Id);
    std::string result = oss.str();
    if (!result.empty()) {
        EXPECT_EQ(result.back(), '\n');
    }
}

// Test that taglist with exifId produces non-empty output
TEST_F(TaglistTest_1365, ExifIfdProducesOutput_1365) {
    Exiv2::Internal::taglist(oss, Exiv2::IfdId::exifId);
    std::string result = oss.str();
    EXPECT_FALSE(result.empty());
}

// Test that taglist with gpsId produces non-empty output
TEST_F(TaglistTest_1365, GpsIfdProducesOutput_1365) {
    Exiv2::Internal::taglist(oss, Exiv2::IfdId::gpsId);
    std::string result = oss.str();
    EXPECT_FALSE(result.empty());
}

// Test that taglist with iopId produces non-empty output
TEST_F(TaglistTest_1365, IopIfdProducesOutput_1365) {
    Exiv2::Internal::taglist(oss, Exiv2::IfdId::iopId);
    std::string result = oss.str();
    EXPECT_FALSE(result.empty());
}

// Test that taglist with an invalid/unknown IfdId produces empty output
TEST_F(TaglistTest_1365, InvalidIfdIdProducesEmptyOutput_1365) {
    Exiv2::Internal::taglist(oss, Exiv2::IfdId::lastId);
    std::string result = oss.str();
    EXPECT_TRUE(result.empty());
}

// Test that each line in the output is separated by newline characters
TEST_F(TaglistTest_1365, OutputContainsMultipleNewlines_1365) {
    Exiv2::Internal::taglist(oss, Exiv2::IfdId::ifd0Id);
    std::string result = oss.str();
    // Count newlines - should be multiple for a valid IFD
    size_t count = 0;
    for (char c : result) {
        if (c == '\n') count++;
    }
    EXPECT_GT(count, 1u);
}

// Test that calling taglist multiple times appends to the stream
TEST_F(TaglistTest_1365, MultipleCallsAppendToStream_1365) {
    Exiv2::Internal::taglist(oss, Exiv2::IfdId::ifd0Id);
    std::string firstResult = oss.str();

    Exiv2::Internal::taglist(oss, Exiv2::IfdId::exifId);
    std::string combinedResult = oss.str();

    EXPECT_GT(combinedResult.size(), firstResult.size());
    // The combined result should start with the first result
    EXPECT_EQ(combinedResult.substr(0, firstResult.size()), firstResult);
}

// Test that taglist with ifd1Id (thumbnail IFD) produces output
TEST_F(TaglistTest_1365, Ifd1ProducesOutput_1365) {
    Exiv2::Internal::taglist(oss, Exiv2::IfdId::ifd1Id);
    std::string result = oss.str();
    // ifd1Id typically shares tags with ifd0Id
    EXPECT_FALSE(result.empty());
}

// Test that calling taglist on an empty stream works correctly
TEST_F(TaglistTest_1365, EmptyStreamInitialState_1365) {
    EXPECT_TRUE(oss.str().empty());
    Exiv2::Internal::taglist(oss, Exiv2::IfdId::ifd0Id);
    EXPECT_FALSE(oss.str().empty());
}
