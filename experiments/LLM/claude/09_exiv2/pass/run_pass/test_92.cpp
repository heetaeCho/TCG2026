#include <gtest/gtest.h>
#include "exiv2/matroskavideo.hpp"
#include <sstream>

using namespace Exiv2::Internal;

// Test fixture for MatroskaTag
class MatroskaTagTest_92 : public ::testing::Test {
protected:
};

// ==================== isComposite() Tests ====================

TEST_F(MatroskaTagTest_92, IsComposite_WhenProcessIsComposite_ReturnsTrue_92) {
    MatroskaTag tag(0x1234, "test", UndefinedType, Composite);
    EXPECT_TRUE(tag.isComposite());
}

TEST_F(MatroskaTagTest_92, IsComposite_WhenProcessIsProcess_ReturnsFalse_92) {
    MatroskaTag tag(0x1234, "test", UndefinedType, Process);
    EXPECT_FALSE(tag.isComposite());
}

TEST_F(MatroskaTagTest_92, IsComposite_WhenProcessIsSkip_ReturnsFalse_92) {
    MatroskaTag tag(0x1234, "test", UndefinedType, Skip);
    EXPECT_FALSE(tag.isComposite());
}

TEST_F(MatroskaTagTest_92, IsComposite_WhenProcessIsUndefined_ReturnsFalse_92) {
    MatroskaTag tag(0x1234, "test", UndefinedType, Undefined);
    EXPECT_FALSE(tag.isComposite());
}

// ==================== isSkipped() Tests ====================

TEST_F(MatroskaTagTest_92, IsSkipped_WhenProcessIsSkip_ReturnsTrue_92) {
    MatroskaTag tag(0x1234, "test", UndefinedType, Skip);
    EXPECT_TRUE(tag.isSkipped());
}

TEST_F(MatroskaTagTest_92, IsSkipped_WhenProcessIsProcess_ReturnsFalse_92) {
    MatroskaTag tag(0x1234, "test", UndefinedType, Process);
    EXPECT_FALSE(tag.isSkipped());
}

TEST_F(MatroskaTagTest_92, IsSkipped_WhenProcessIsComposite_ReturnsFalse_92) {
    MatroskaTag tag(0x1234, "test", UndefinedType, Composite);
    EXPECT_FALSE(tag.isSkipped());
}

TEST_F(MatroskaTagTest_92, IsSkipped_WhenProcessIsUndefined_ReturnsFalse_92) {
    MatroskaTag tag(0x1234, "test", UndefinedType, Undefined);
    EXPECT_FALSE(tag.isSkipped());
}

// ==================== operator==() Tests ====================

TEST_F(MatroskaTagTest_92, OperatorEquals_SameId_ReturnsTrue_92) {
    MatroskaTag tag(0xABCD, "test", UndefinedType, Process);
    EXPECT_TRUE(tag == 0xABCD);
}

TEST_F(MatroskaTagTest_92, OperatorEquals_DifferentId_ReturnsFalse_92) {
    MatroskaTag tag(0xABCD, "test", UndefinedType, Process);
    EXPECT_FALSE(tag == 0x1234);
}

TEST_F(MatroskaTagTest_92, OperatorEquals_ZeroId_92) {
    MatroskaTag tag(0, "test", UndefinedType, Process);
    EXPECT_TRUE(tag == 0);
    EXPECT_FALSE(tag == 1);
}

TEST_F(MatroskaTagTest_92, OperatorEquals_MaxId_92) {
    uint64_t maxId = UINT64_MAX;
    MatroskaTag tag(maxId, "test", UndefinedType, Process);
    EXPECT_TRUE(tag == maxId);
    EXPECT_FALSE(tag == 0);
}

// ==================== Constructor Tests ====================

TEST_F(MatroskaTagTest_92, FullConstructor_SetsFields_92) {
    MatroskaTag tag(42, "label", UndefinedType, Composite);
    EXPECT_EQ(tag._id, 42u);
    EXPECT_EQ(tag._label, "label");
    EXPECT_EQ(tag._type, UndefinedType);
    EXPECT_EQ(tag._process, Composite);
}

TEST_F(MatroskaTagTest_92, TwoArgConstructor_SetsDefaultTypeAndProcess_92) {
    MatroskaTag tag(99, "shortlabel");
    EXPECT_EQ(tag._id, 99u);
    EXPECT_EQ(tag._label, "shortlabel");
    EXPECT_EQ(tag._type, UndefinedType);
    EXPECT_EQ(tag._process, Undefined);
}

TEST_F(MatroskaTagTest_92, TwoArgConstructor_IsNotComposite_92) {
    MatroskaTag tag(99, "shortlabel");
    EXPECT_FALSE(tag.isComposite());
}

TEST_F(MatroskaTagTest_92, TwoArgConstructor_IsNotSkipped_92) {
    MatroskaTag tag(99, "shortlabel");
    EXPECT_FALSE(tag.isSkipped());
}

TEST_F(MatroskaTagTest_92, Constructor_EmptyLabel_92) {
    MatroskaTag tag(0, "");
    EXPECT_EQ(tag._label, "");
    EXPECT_EQ(tag._id, 0u);
}

// ==================== dump() Tests ====================

TEST_F(MatroskaTagTest_92, Dump_ProducesOutput_92) {
    MatroskaTag tag(0x1A, "TestTag", UndefinedType, Process);
    std::ostringstream os;
    tag.dump(os);
    std::string output = os.str();
    // dump should produce some non-empty output
    EXPECT_FALSE(output.empty());
}

TEST_F(MatroskaTagTest_92, Dump_ContainsLabel_92) {
    MatroskaTag tag(0x1A, "MyLabel", UndefinedType, Process);
    std::ostringstream os;
    tag.dump(os);
    std::string output = os.str();
    // Expect the label to appear in the dump output
    EXPECT_NE(output.find("MyLabel"), std::string::npos);
}

// ==================== Enum value checks ====================

TEST_F(MatroskaTagTest_92, EnumValues_AreCorrect_92) {
    EXPECT_EQ(Process, 112);
    EXPECT_EQ(Skip, 115);
    EXPECT_EQ(Composite, 99);
    EXPECT_EQ(Undefined, 117);
}

// ==================== Cross-checks between methods ====================

TEST_F(MatroskaTagTest_92, SkipAndComposite_MutuallyExclusive_92) {
    MatroskaTag tagSkip(1, "s", UndefinedType, Skip);
    EXPECT_TRUE(tagSkip.isSkipped());
    EXPECT_FALSE(tagSkip.isComposite());

    MatroskaTag tagComposite(2, "c", UndefinedType, Composite);
    EXPECT_FALSE(tagComposite.isSkipped());
    EXPECT_TRUE(tagComposite.isComposite());
}

TEST_F(MatroskaTagTest_92, ProcessTag_NeitherSkippedNorComposite_92) {
    MatroskaTag tag(1, "p", UndefinedType, Process);
    EXPECT_FALSE(tag.isSkipped());
    EXPECT_FALSE(tag.isComposite());
}
