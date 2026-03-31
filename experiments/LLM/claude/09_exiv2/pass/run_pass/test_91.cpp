#include <gtest/gtest.h>
#include <string>
#include <sstream>

// Include the necessary headers
// Based on the provided code, we need the MatroskaTag definition
// We'll include the header that contains the struct

// Reproduce the minimal necessary definitions based on the known dependencies
namespace Exiv2 {
namespace Internal {

enum matroskaTypeEnum {
    UndefinedType = 0
    // Other values may exist but aren't needed for testing isSkipped
};

enum matroskaProcessEnum {
    Process = 112,
    Skip = 115,
    Composite = 99,
    Undefined = 117
};

struct MatroskaTag {
    uint64_t _id;
    std::string _label;
    matroskaTypeEnum _type;
    matroskaProcessEnum _process;

    MatroskaTag(uint64_t id, std::string label, matroskaTypeEnum type, matroskaProcessEnum process)
        : _id(id), _label(std::move(label)), _type(type), _process(process) {}

    MatroskaTag(uint64_t id, std::string label)
        : _id(id), _label(std::move(label)), _type(UndefinedType), _process(Undefined) {}

    bool operator==(uint64_t id) const {
        return _id == id;
    }

    bool isSkipped() const {
        return _process == Skip;
    }

    bool isComposite() const {
        return _process == Composite;
    }

    void dump(std::ostream& os) const {
        os << "id: " << _id << ", label: " << _label;
    }
};

}  // namespace Internal
}  // namespace Exiv2

using namespace Exiv2::Internal;

// Test fixture
class MatroskaTagTest_91 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// =============================================================================
// Tests for isSkipped()
// =============================================================================

TEST_F(MatroskaTagTest_91, IsSkipped_WhenProcessIsSkip_ReturnsTrue_91) {
    MatroskaTag tag(1, "test", UndefinedType, Skip);
    EXPECT_TRUE(tag.isSkipped());
}

TEST_F(MatroskaTagTest_91, IsSkipped_WhenProcessIsProcess_ReturnsFalse_91) {
    MatroskaTag tag(1, "test", UndefinedType, Process);
    EXPECT_FALSE(tag.isSkipped());
}

TEST_F(MatroskaTagTest_91, IsSkipped_WhenProcessIsComposite_ReturnsFalse_91) {
    MatroskaTag tag(1, "test", UndefinedType, Composite);
    EXPECT_FALSE(tag.isSkipped());
}

TEST_F(MatroskaTagTest_91, IsSkipped_WhenProcessIsUndefined_ReturnsFalse_91) {
    MatroskaTag tag(1, "test", UndefinedType, Undefined);
    EXPECT_FALSE(tag.isSkipped());
}

TEST_F(MatroskaTagTest_91, IsSkipped_TwoArgConstructor_DefaultProcessIsUndefined_ReturnsFalse_91) {
    MatroskaTag tag(42, "default");
    EXPECT_FALSE(tag.isSkipped());
}

// =============================================================================
// Tests for isComposite()
// =============================================================================

TEST_F(MatroskaTagTest_91, IsComposite_WhenProcessIsComposite_ReturnsTrue_91) {
    MatroskaTag tag(1, "test", UndefinedType, Composite);
    EXPECT_TRUE(tag.isComposite());
}

TEST_F(MatroskaTagTest_91, IsComposite_WhenProcessIsSkip_ReturnsFalse_91) {
    MatroskaTag tag(1, "test", UndefinedType, Skip);
    EXPECT_FALSE(tag.isComposite());
}

TEST_F(MatroskaTagTest_91, IsComposite_WhenProcessIsProcess_ReturnsFalse_91) {
    MatroskaTag tag(1, "test", UndefinedType, Process);
    EXPECT_FALSE(tag.isComposite());
}

TEST_F(MatroskaTagTest_91, IsComposite_WhenProcessIsUndefined_ReturnsFalse_91) {
    MatroskaTag tag(1, "test", UndefinedType, Undefined);
    EXPECT_FALSE(tag.isComposite());
}

TEST_F(MatroskaTagTest_91, IsComposite_TwoArgConstructor_ReturnsFalse_91) {
    MatroskaTag tag(42, "default");
    EXPECT_FALSE(tag.isComposite());
}

// =============================================================================
// Tests for operator==
// =============================================================================

TEST_F(MatroskaTagTest_91, OperatorEquals_SameId_ReturnsTrue_91) {
    MatroskaTag tag(100, "test", UndefinedType, Process);
    EXPECT_TRUE(tag == 100);
}

TEST_F(MatroskaTagTest_91, OperatorEquals_DifferentId_ReturnsFalse_91) {
    MatroskaTag tag(100, "test", UndefinedType, Process);
    EXPECT_FALSE(tag == 200);
}

TEST_F(MatroskaTagTest_91, OperatorEquals_ZeroId_91) {
    MatroskaTag tag(0, "zero", UndefinedType, Process);
    EXPECT_TRUE(tag == 0);
    EXPECT_FALSE(tag == 1);
}

TEST_F(MatroskaTagTest_91, OperatorEquals_MaxUint64Id_91) {
    uint64_t maxId = UINT64_MAX;
    MatroskaTag tag(maxId, "max", UndefinedType, Process);
    EXPECT_TRUE(tag == maxId);
    EXPECT_FALSE(tag == 0);
}

// =============================================================================
// Tests for constructor with 4 arguments
// =============================================================================

TEST_F(MatroskaTagTest_91, FourArgConstructor_SetsFieldsCorrectly_91) {
    MatroskaTag tag(42, "myLabel", UndefinedType, Skip);
    EXPECT_EQ(tag._id, 42u);
    EXPECT_EQ(tag._label, "myLabel");
    EXPECT_EQ(tag._type, UndefinedType);
    EXPECT_EQ(tag._process, Skip);
}

// =============================================================================
// Tests for constructor with 2 arguments (defaults)
// =============================================================================

TEST_F(MatroskaTagTest_91, TwoArgConstructor_SetsDefaultTypeAndProcess_91) {
    MatroskaTag tag(10, "shortLabel");
    EXPECT_EQ(tag._id, 10u);
    EXPECT_EQ(tag._label, "shortLabel");
    EXPECT_EQ(tag._type, UndefinedType);
    EXPECT_EQ(tag._process, Undefined);
}

TEST_F(MatroskaTagTest_91, TwoArgConstructor_EmptyLabel_91) {
    MatroskaTag tag(0, "");
    EXPECT_EQ(tag._id, 0u);
    EXPECT_EQ(tag._label, "");
    EXPECT_EQ(tag._type, UndefinedType);
    EXPECT_EQ(tag._process, Undefined);
}

// =============================================================================
// Tests for dump()
// =============================================================================

TEST_F(MatroskaTagTest_91, Dump_WritesToOstream_91) {
    MatroskaTag tag(123, "testLabel", UndefinedType, Process);
    std::ostringstream oss;
    tag.dump(oss);
    std::string output = oss.str();
    // The dump should produce some output; we check it's not empty
    EXPECT_FALSE(output.empty());
}

TEST_F(MatroskaTagTest_91, Dump_ContainsId_91) {
    MatroskaTag tag(999, "myTag", UndefinedType, Skip);
    std::ostringstream oss;
    tag.dump(oss);
    std::string output = oss.str();
    // The output should contain the ID somewhere
    EXPECT_NE(output.find("999"), std::string::npos);
}

TEST_F(MatroskaTagTest_91, Dump_ContainsLabel_91) {
    MatroskaTag tag(1, "uniqueLabel", UndefinedType, Process);
    std::ostringstream oss;
    tag.dump(oss);
    std::string output = oss.str();
    EXPECT_NE(output.find("uniqueLabel"), std::string::npos);
}

TEST_F(MatroskaTagTest_91, Dump_EmptyLabel_91) {
    MatroskaTag tag(0, "");
    std::ostringstream oss;
    tag.dump(oss);
    std::string output = oss.str();
    // Should still produce some output even with empty label
    EXPECT_FALSE(output.empty());
}

// =============================================================================
// Boundary / edge case tests
// =============================================================================

TEST_F(MatroskaTagTest_91, BoundaryId_Zero_91) {
    MatroskaTag tag(0, "zero", UndefinedType, Process);
    EXPECT_TRUE(tag == 0);
    EXPECT_FALSE(tag.isSkipped());
    EXPECT_FALSE(tag.isComposite());
}

TEST_F(MatroskaTagTest_91, BoundaryId_MaxUint64_91) {
    MatroskaTag tag(UINT64_MAX, "max", UndefinedType, Skip);
    EXPECT_TRUE(tag == UINT64_MAX);
    EXPECT_TRUE(tag.isSkipped());
}

TEST_F(MatroskaTagTest_91, LongLabel_91) {
    std::string longLabel(10000, 'x');
    MatroskaTag tag(1, longLabel, UndefinedType, Composite);
    EXPECT_EQ(tag._label, longLabel);
    EXPECT_TRUE(tag.isComposite());
}

TEST_F(MatroskaTagTest_91, AllProcessEnumValues_91) {
    MatroskaTag tagProcess(1, "p", UndefinedType, Process);
    MatroskaTag tagSkip(2, "s", UndefinedType, Skip);
    MatroskaTag tagComposite(3, "c", UndefinedType, Composite);
    MatroskaTag tagUndefined(4, "u", UndefinedType, Undefined);

    EXPECT_FALSE(tagProcess.isSkipped());
    EXPECT_FALSE(tagProcess.isComposite());

    EXPECT_TRUE(tagSkip.isSkipped());
    EXPECT_FALSE(tagSkip.isComposite());

    EXPECT_FALSE(tagComposite.isSkipped());
    EXPECT_TRUE(tagComposite.isComposite());

    EXPECT_FALSE(tagUndefined.isSkipped());
    EXPECT_FALSE(tagUndefined.isComposite());
}
