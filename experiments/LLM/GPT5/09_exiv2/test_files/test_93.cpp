#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "exiv2/matroskavideo.hpp"  // Include the header file where MatroskaTag is defined

namespace Exiv2 {
namespace Internal {

// Mock external dependencies if necessary (currently no external dependencies, so no mocks required).

class MatroskaTagTest_93 : public ::testing::Test {
protected:
    // Setup and teardown if required (currently not needed for the given class).
};

// Test for MatroskaTag constructor with all parameters.
TEST_F(MatroskaTagTest_93, ConstructorWithAllParams_93) {
    uint64_t id = 12345;
    std::string label = "TestLabel";
    matroskaTypeEnum type = matroskaTypeEnum::Video;  // Assuming matroskaTypeEnum has Video as a value
    matroskaProcessEnum process = matroskaProcessEnum::Processing;  // Assuming matroskaProcessEnum has Processing as a value

    MatroskaTag tag(id, label, type, process);

    // Check that the fields are correctly initialized.
    EXPECT_EQ(tag._id, id);
    EXPECT_EQ(tag._label, label);
    EXPECT_EQ(tag._type, type);
    EXPECT_EQ(tag._process, process);
}

// Test for MatroskaTag constructor with default values for type and process.
TEST_F(MatroskaTagTest_93, ConstructorWithDefaults_93) {
    uint64_t id = 67890;
    std::string label = "DefaultLabel";

    MatroskaTag tag(id, label);

    // Check that type and process are initialized to the default values.
    EXPECT_EQ(tag._id, id);
    EXPECT_EQ(tag._label, label);
    EXPECT_EQ(tag._type, matroskaTypeEnum::UndefinedType);
    EXPECT_EQ(tag._process, matroskaProcessEnum::Undefined);
}

// Test for equality operator (`operator==`).
TEST_F(MatroskaTagTest_93, EqualityOperator_93) {
    uint64_t id = 11111;
    std::string label = "EqualLabel";
    matroskaTypeEnum type = matroskaTypeEnum::Audio;
    matroskaProcessEnum process = matroskaProcessEnum::PostProcessing;

    MatroskaTag tag1(id, label, type, process);
    MatroskaTag tag2(id, label, type, process);
    MatroskaTag tag3(22222, "DifferentLabel", matroskaTypeEnum::Video, matroskaProcessEnum::Processing);

    EXPECT_TRUE(tag1 == id);
    EXPECT_FALSE(tag1 == tag3._id);
}

// Test for the `isSkipped()` method (assuming it checks some internal state).
TEST_F(MatroskaTagTest_93, IsSkipped_93) {
    uint64_t id = 55555;
    std::string label = "SkippedLabel";
    MatroskaTag tag(id, label);

    // Assuming isSkipped returns false by default unless set otherwise.
    EXPECT_FALSE(tag.isSkipped());

    // If you had a way to set the skipped state, you would test it here.
    // tag.setSkipped(true);
    // EXPECT_TRUE(tag.isSkipped());
}

// Test for the `isComposite()` method (assuming it checks for some composite state).
TEST_F(MatroskaTagTest_93, IsComposite_93) {
    uint64_t id = 33333;
    std::string label = "CompositeLabel";
    MatroskaTag tag(id, label);

    // Assuming isComposite returns false by default unless set otherwise.
    EXPECT_FALSE(tag.isComposite());

    // If you had a way to set the composite state, you would test it here.
    // tag.setComposite(true);
    // EXPECT_TRUE(tag.isComposite());
}

// Test for the `dump()` method, verifying its output.
TEST_F(MatroskaTagTest_93, Dump_93) {
    uint64_t id = 98765;
    std::string label = "DumpLabel";
    matroskaTypeEnum type = matroskaTypeEnum::Text;
    matroskaProcessEnum process = matroskaProcessEnum::PreProcessing;

    MatroskaTag tag(id, label, type, process);
    std::ostringstream os;
    tag.dump(os);

    std::string expected_output = " MatroskaTag id: [0x181d] label:[DumpLabel] type:[3] process :[2]\n";
    EXPECT_EQ(os.str(), expected_output);
}

}  // namespace Internal
}  // namespace Exiv2