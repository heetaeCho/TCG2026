#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "./TestProjects/exiv2/src/nikonmn_int.hpp"
#include "exiv2/exif.hpp"
#include "exiv2/value.hpp"

// Mocking dependencies
using ::testing::_;
using ::testing::Mock;

namespace Exiv2 {
namespace Internal {

// Test fixture class for Nikon3MakerNote tests
class Nikon3MakerNoteTest : public ::testing::Test {
protected:
    // Helper function to simulate the metadata findKey function
    std::shared_ptr<ExifData> mockMetadata(bool containsKey) {
        auto metadata = std::make_shared<ExifData>();
        auto exifKey = ExifKey("Exif.NikonAf2.ContrastDetectAF");
        if (containsKey) {
            metadata->add(exifKey, std::make_shared<Value>(TypeId::uint32_t));
        }
        return metadata;
    }
};

// TEST_ID 461: Test when contrastDetectAF is found and equals 0
TEST_F(Nikon3MakerNoteTest, PrintAf2AreaMode_ContrastDetectAfOff_461) {
    ExifData metadata;
    Value value(TypeId::uint32_t);
    std::ostream os(nullptr);

    // Mock the metadata to return a valid key
    metadata.add(ExifKey("Exif.NikonAf2.ContrastDetectAF"), std::make_shared<Value>(TypeId::uint32_t));

    Nikon3MakerNote makerNote;
    // Expectation for the return value of the print function to check if it returns the expected output
    EXPECT_CALL(os, write(_, _)).Times(1);

    makerNote.printAf2AreaMode(os, value, &metadata);
}

// TEST_ID 462: Test when contrastDetectAF is not found (returns the default value)
TEST_F(Nikon3MakerNoteTest, PrintAf2AreaMode_ContrastDetectAfOn_462) {
    ExifData metadata;
    Value value(TypeId::uint32_t);
    std::ostream os(nullptr);

    // Mock the metadata to not return the key
    auto metadataWithoutKey = mockMetadata(false);

    Nikon3MakerNote makerNote;
    // Expectation for the return value of the print function to check if it returns the expected output
    EXPECT_CALL(os, write(_, _)).Times(1);

    makerNote.printAf2AreaMode(os, value, metadataWithoutKey.get());
}

// TEST_ID 463: Boundary test where contrastDetectAF key exists but has no value
TEST_F(Nikon3MakerNoteTest, PrintAf2AreaMode_NoValue_463) {
    ExifData metadata;
    Value value(TypeId::uint32_t);
    std::ostream os(nullptr);

    // Add the contrastDetectAF key but without a valid value
    auto exifKey = ExifKey("Exif.NikonAf2.ContrastDetectAF");
    metadata.add(exifKey, std::make_shared<Value>(TypeId::uint32_t));

    Nikon3MakerNote makerNote;
    // Expectation for the return value of the print function to check if it returns the expected output
    EXPECT_CALL(os, write(_, _)).Times(1);

    makerNote.printAf2AreaMode(os, value, &metadata);
}

// TEST_ID 464: Test when metadata is null (edge case)
TEST_F(Nikon3MakerNoteTest, PrintAf2AreaMode_NullMetadata_464) {
    ExifData metadata;
    Value value(TypeId::uint32_t);
    std::ostream os(nullptr);

    Nikon3MakerNote makerNote;
    // Expectation for the return value of the print function to check if it handles the null metadata gracefully
    EXPECT_CALL(os, write(_, _)).Times(1);

    makerNote.printAf2AreaMode(os, value, nullptr);  // Null metadata
}

// TEST_ID 465: Test when printAf2AreaMode returns a specific string (contrastDetectAF == 0)
TEST_F(Nikon3MakerNoteTest, PrintAf2AreaMode_ContrastDetectAfOffString_465) {
    ExifData metadata;
    Value value(TypeId::uint32_t);
    std::ostream os(nullptr);

    auto metadataWithKey = mockMetadata(true);

    Nikon3MakerNote makerNote;
    std::string expectedOutput = "Single-point AF";  // Example expected output from EXV_PRINT_TAG

    // Verify the returned string matches the expected output
    EXPECT_CALL(os, write(_, _)).Times(1).WillOnce(testing::Return(expectedOutput));

    makerNote.printAf2AreaMode(os, value, metadataWithKey.get());
}

}  // namespace Internal
}  // namespace Exiv2