#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "exiv2/matroskavideo.hpp"  // Assuming this is the correct header file

namespace Exiv2 {
namespace Internal {

// TEST_ID: 91
TEST(MatroskaTagTest_91, IsSkipped_ReturnsTrueWhenProcessIsSkip_91) {
    MatroskaTag tag(1, "label", matroskaTypeEnum::UndefinedType, matroskaProcessEnum::Skip);
    EXPECT_TRUE(tag.isSkipped());
}

// TEST_ID: 92
TEST(MatroskaTagTest_92, IsSkipped_ReturnsFalseWhenProcessIsNotSkip_92) {
    MatroskaTag tag(1, "label", matroskaTypeEnum::UndefinedType, matroskaProcessEnum::Process);
    EXPECT_FALSE(tag.isSkipped());
}

// TEST_ID: 93
TEST(MatroskaTagTest_93, ConstructorWithIdAndLabel_InitializesCorrectly_93) {
    uint64_t id = 12345;
    std::string label = "TestLabel";
    MatroskaTag tag(id, label);

    EXPECT_EQ(tag._id, id);
    EXPECT_EQ(tag._label, label);
    EXPECT_EQ(tag._type, matroskaTypeEnum::UndefinedType);
    EXPECT_EQ(tag._process, matroskaProcessEnum::Undefined);
}

// TEST_ID: 94
TEST(MatroskaTagTest_94, ConstructorWithIdLabelTypeProcess_InitializesCorrectly_94) {
    uint64_t id = 67890;
    std::string label = "AnotherLabel";
    matroskaTypeEnum type = matroskaTypeEnum::UndefinedType;
    matroskaProcessEnum process = matroskaProcessEnum::Composite;

    MatroskaTag tag(id, label, type, process);

    EXPECT_EQ(tag._id, id);
    EXPECT_EQ(tag._label, label);
    EXPECT_EQ(tag._type, type);
    EXPECT_EQ(tag._process, process);
}

// TEST_ID: 95
TEST(MatroskaTagTest_95, IsComposite_ReturnsTrueWhenProcessIsComposite_95) {
    MatroskaTag tag(1, "label", matroskaTypeEnum::UndefinedType, matroskaProcessEnum::Composite);
    EXPECT_TRUE(tag.isComposite());
}

// TEST_ID: 96
TEST(MatroskaTagTest_96, IsComposite_ReturnsFalseWhenProcessIsNotComposite_96) {
    MatroskaTag tag(1, "label", matroskaTypeEnum::UndefinedType, matroskaProcessEnum::Skip);
    EXPECT_FALSE(tag.isComposite());
}

// TEST_ID: 97
TEST(MatroskaTagTest_97, EqualityOperator_ReturnsTrueWhenIdsAreEqual_97) {
    uint64_t id = 12345;
    MatroskaTag tag1(id, "label");
    MatroskaTag tag2(id, "anotherLabel");

    EXPECT_TRUE(tag1 == id);
    EXPECT_TRUE(tag2 == id);
}

// TEST_ID: 98
TEST(MatroskaTagTest_98, EqualityOperator_ReturnsFalseWhenIdsAreNotEqual_98) {
    uint64_t id1 = 12345;
    uint64_t id2 = 67890;
    MatroskaTag tag1(id1, "label");
    MatroskaTag tag2(id2, "anotherLabel");

    EXPECT_FALSE(tag1 == id2);
    EXPECT_FALSE(tag2 == id1);
}

}  // namespace Internal
}  // namespace Exiv2