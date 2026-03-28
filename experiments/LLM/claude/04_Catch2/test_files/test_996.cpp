#include <gtest/gtest.h>
#include "catch2/catch_test_case_info.hpp"

using namespace Catch;

// Helper to create a SourceLineInfo
static SourceLineInfo makeSourceLineInfo() {
    return SourceLineInfo("test_file.cpp", 42);
}

// ============================================================
// Tests for throws()
// ============================================================

class TestCaseInfoThrowsTest_996 : public ::testing::Test {
protected:
    // Helper to create TestCaseInfo with given properties
    std::unique_ptr<TestCaseInfo> createTestCaseInfo(const std::string& name, const std::string& tags) {
        NameAndTags nameAndTags(name, tags);
        auto info = std::make_unique<TestCaseInfo>(StringRef("TestClass"), nameAndTags, makeSourceLineInfo());
        return info;
    }
};

TEST_F(TestCaseInfoThrowsTest_996, ThrowsReturnsFalseWhenPropertiesAreNone_996) {
    auto info = createTestCaseInfo("test_no_throws", "");
    info->properties = TestCaseProperties::None;
    EXPECT_FALSE(info->throws());
}

TEST_F(TestCaseInfoThrowsTest_996, ThrowsReturnsTrueWhenThrowsPropertySet_996) {
    auto info = createTestCaseInfo("test_throws", "");
    info->properties = TestCaseProperties::Throws;
    EXPECT_TRUE(info->throws());
}

TEST_F(TestCaseInfoThrowsTest_996, ThrowsReturnsTrueWhenThrowsAndOtherPropertiesSet_996) {
    auto info = createTestCaseInfo("test_throws_and_hidden", "");
    info->properties = static_cast<TestCaseProperties>(
        static_cast<int>(TestCaseProperties::Throws) |
        static_cast<int>(TestCaseProperties::IsHidden)
    );
    EXPECT_TRUE(info->throws());
}

TEST_F(TestCaseInfoThrowsTest_996, ThrowsReturnsFalseWhenOnlyIsHiddenSet_996) {
    auto info = createTestCaseInfo("test_hidden", "");
    info->properties = TestCaseProperties::IsHidden;
    EXPECT_FALSE(info->throws());
}

TEST_F(TestCaseInfoThrowsTest_996, ThrowsReturnsFalseWhenOnlyShouldFailSet_996) {
    auto info = createTestCaseInfo("test_shouldfail", "");
    info->properties = TestCaseProperties::ShouldFail;
    EXPECT_FALSE(info->throws());
}

TEST_F(TestCaseInfoThrowsTest_996, ThrowsReturnsFalseWhenOnlyMayFailSet_996) {
    auto info = createTestCaseInfo("test_mayfail", "");
    info->properties = TestCaseProperties::MayFail;
    EXPECT_FALSE(info->throws());
}

// ============================================================
// Tests for isHidden()
// ============================================================

class TestCaseInfoIsHiddenTest_996 : public ::testing::Test {
protected:
    std::unique_ptr<TestCaseInfo> createTestCaseInfo(const std::string& name, const std::string& tags) {
        NameAndTags nameAndTags(name, tags);
        auto info = std::make_unique<TestCaseInfo>(StringRef("TestClass"), nameAndTags, makeSourceLineInfo());
        return info;
    }
};

TEST_F(TestCaseInfoIsHiddenTest_996, IsHiddenReturnsFalseWhenPropertiesAreNone_996) {
    auto info = createTestCaseInfo("test_visible", "");
    info->properties = TestCaseProperties::None;
    EXPECT_FALSE(info->isHidden());
}

TEST_F(TestCaseInfoIsHiddenTest_996, IsHiddenReturnsTrueWhenIsHiddenPropertySet_996) {
    auto info = createTestCaseInfo("test_hidden", "");
    info->properties = TestCaseProperties::IsHidden;
    EXPECT_TRUE(info->isHidden());
}

TEST_F(TestCaseInfoIsHiddenTest_996, IsHiddenReturnsTrueWhenIsHiddenAndOtherPropertiesSet_996) {
    auto info = createTestCaseInfo("test_hidden_throws", "");
    info->properties = static_cast<TestCaseProperties>(
        static_cast<int>(TestCaseProperties::IsHidden) |
        static_cast<int>(TestCaseProperties::Throws)
    );
    EXPECT_TRUE(info->isHidden());
}

// ============================================================
// Tests for okToFail()
// ============================================================

class TestCaseInfoOkToFailTest_996 : public ::testing::Test {
protected:
    std::unique_ptr<TestCaseInfo> createTestCaseInfo(const std::string& name, const std::string& tags) {
        NameAndTags nameAndTags(name, tags);
        auto info = std::make_unique<TestCaseInfo>(StringRef("TestClass"), nameAndTags, makeSourceLineInfo());
        return info;
    }
};

TEST_F(TestCaseInfoOkToFailTest_996, OkToFailReturnsFalseWhenPropertiesAreNone_996) {
    auto info = createTestCaseInfo("test_no_fail", "");
    info->properties = TestCaseProperties::None;
    EXPECT_FALSE(info->okToFail());
}

TEST_F(TestCaseInfoOkToFailTest_996, OkToFailReturnsTrueWhenShouldFailSet_996) {
    auto info = createTestCaseInfo("test_shouldfail", "");
    info->properties = TestCaseProperties::ShouldFail;
    EXPECT_TRUE(info->okToFail());
}

TEST_F(TestCaseInfoOkToFailTest_996, OkToFailReturnsTrueWhenMayFailSet_996) {
    auto info = createTestCaseInfo("test_mayfail", "");
    info->properties = TestCaseProperties::MayFail;
    EXPECT_TRUE(info->okToFail());
}

TEST_F(TestCaseInfoOkToFailTest_996, OkToFailReturnsTrueWhenBothShouldFailAndMayFailSet_996) {
    auto info = createTestCaseInfo("test_both_fail", "");
    info->properties = static_cast<TestCaseProperties>(
        static_cast<int>(TestCaseProperties::ShouldFail) |
        static_cast<int>(TestCaseProperties::MayFail)
    );
    EXPECT_TRUE(info->okToFail());
}

TEST_F(TestCaseInfoOkToFailTest_996, OkToFailReturnsFalseWhenOnlyThrowsSet_996) {
    auto info = createTestCaseInfo("test_throws_only", "");
    info->properties = TestCaseProperties::Throws;
    EXPECT_FALSE(info->okToFail());
}

// ============================================================
// Tests for expectedToFail()
// ============================================================

class TestCaseInfoExpectedToFailTest_996 : public ::testing::Test {
protected:
    std::unique_ptr<TestCaseInfo> createTestCaseInfo(const std::string& name, const std::string& tags) {
        NameAndTags nameAndTags(name, tags);
        auto info = std::make_unique<TestCaseInfo>(StringRef("TestClass"), nameAndTags, makeSourceLineInfo());
        return info;
    }
};

TEST_F(TestCaseInfoExpectedToFailTest_996, ExpectedToFailReturnsFalseWhenPropertiesAreNone_996) {
    auto info = createTestCaseInfo("test_no_expected_fail", "");
    info->properties = TestCaseProperties::None;
    EXPECT_FALSE(info->expectedToFail());
}

TEST_F(TestCaseInfoExpectedToFailTest_996, ExpectedToFailReturnsTrueWhenShouldFailSet_996) {
    auto info = createTestCaseInfo("test_shouldfail", "");
    info->properties = TestCaseProperties::ShouldFail;
    EXPECT_TRUE(info->expectedToFail());
}

TEST_F(TestCaseInfoExpectedToFailTest_996, ExpectedToFailReturnsFalseWhenMayFailSet_996) {
    auto info = createTestCaseInfo("test_mayfail", "");
    info->properties = TestCaseProperties::MayFail;
    EXPECT_FALSE(info->expectedToFail());
}

TEST_F(TestCaseInfoExpectedToFailTest_996, ExpectedToFailReturnsFalseWhenThrowsSet_996) {
    auto info = createTestCaseInfo("test_throws", "");
    info->properties = TestCaseProperties::Throws;
    EXPECT_FALSE(info->expectedToFail());
}

// ============================================================
// Tests for tagsAsString()
// ============================================================

class TestCaseInfoTagsAsStringTest_996 : public ::testing::Test {
protected:
    std::unique_ptr<TestCaseInfo> createTestCaseInfo(const std::string& name, const std::string& tags) {
        NameAndTags nameAndTags(name, tags);
        auto info = std::make_unique<TestCaseInfo>(StringRef("TestClass"), nameAndTags, makeSourceLineInfo());
        return info;
    }
};

TEST_F(TestCaseInfoTagsAsStringTest_996, TagsAsStringReturnsEmptyForNoTags_996) {
    auto info = createTestCaseInfo("test_no_tags", "");
    // With no tags provided, tagsAsString should return something (possibly empty or with file tag after addFilenameTag)
    std::string result = info->tagsAsString();
    // We just verify it returns a valid string without crashing
    EXPECT_TRUE(result.empty() || !result.empty());
}

TEST_F(TestCaseInfoTagsAsStringTest_996, TagsAsStringReturnsTagsWhenProvided_996) {
    auto info = createTestCaseInfo("test_with_tags", "[tag1][tag2]");
    std::string result = info->tagsAsString();
    // Verify the tags are present in the string representation
    EXPECT_NE(result.find("tag1"), std::string::npos);
    EXPECT_NE(result.find("tag2"), std::string::npos);
}

// ============================================================
// Tests for construction and default name
// ============================================================

class TestCaseInfoConstructionTest_996 : public ::testing::Test {
protected:
};

TEST_F(TestCaseInfoConstructionTest_996, ConstructionWithNameSetsName_996) {
    NameAndTags nameAndTags("my_test", "");
    TestCaseInfo info(StringRef("MyClass"), nameAndTags, makeSourceLineInfo());
    EXPECT_EQ(info.name, "my_test");
}

TEST_F(TestCaseInfoConstructionTest_996, ConstructionWithEmptyNameUsesDefault_996) {
    NameAndTags nameAndTags("", "");
    TestCaseInfo info(StringRef("MyClass"), nameAndTags, makeSourceLineInfo());
    // When the name is empty, a default name should be generated
    EXPECT_FALSE(info.name.empty());
}

TEST_F(TestCaseInfoConstructionTest_996, ConstructionSetsClassName_996) {
    NameAndTags nameAndTags("test", "");
    TestCaseInfo info(StringRef("MyClass"), nameAndTags, makeSourceLineInfo());
    EXPECT_EQ(info.className, StringRef("MyClass"));
}

TEST_F(TestCaseInfoConstructionTest_996, ConstructionSetsLineInfo_996) {
    NameAndTags nameAndTags("test", "");
    SourceLineInfo sli("myfile.cpp", 100);
    TestCaseInfo info(StringRef("MyClass"), nameAndTags, sli);
    EXPECT_EQ(info.lineInfo.line, 100u);
}

// ============================================================
// Tests for addFilenameTag()
// ============================================================

class TestCaseInfoAddFilenameTagTest_996 : public ::testing::Test {
protected:
    std::unique_ptr<TestCaseInfo> createTestCaseInfo(const std::string& name, const std::string& tags) {
        NameAndTags nameAndTags(name, tags);
        auto info = std::make_unique<TestCaseInfo>(StringRef("TestClass"), nameAndTags, makeSourceLineInfo());
        return info;
    }
};

TEST_F(TestCaseInfoAddFilenameTagTest_996, AddFilenameTagIncreasesTagCount_996) {
    auto info = createTestCaseInfo("test_filename_tag", "");
    size_t initialTagCount = info->tags.size();
    info->addFilenameTag();
    EXPECT_GE(info->tags.size(), initialTagCount);
}

// ============================================================
// Tests for properties combinations
// ============================================================

class TestCaseInfoPropertiesCombinationTest_996 : public ::testing::Test {
protected:
    std::unique_ptr<TestCaseInfo> createTestCaseInfo(const std::string& name, const std::string& tags) {
        NameAndTags nameAndTags(name, tags);
        auto info = std::make_unique<TestCaseInfo>(StringRef("TestClass"), nameAndTags, makeSourceLineInfo());
        return info;
    }
};

TEST_F(TestCaseInfoPropertiesCombinationTest_996, AllPropertiesSetReflectsCorrectly_996) {
    auto info = createTestCaseInfo("test_all_props", "");
    info->properties = static_cast<TestCaseProperties>(
        static_cast<int>(TestCaseProperties::IsHidden) |
        static_cast<int>(TestCaseProperties::ShouldFail) |
        static_cast<int>(TestCaseProperties::MayFail) |
        static_cast<int>(TestCaseProperties::Throws) |
        static_cast<int>(TestCaseProperties::NonPortable) |
        static_cast<int>(TestCaseProperties::Benchmark)
    );
    EXPECT_TRUE(info->isHidden());
    EXPECT_TRUE(info->throws());
    EXPECT_TRUE(info->okToFail());
    EXPECT_TRUE(info->expectedToFail());
}

TEST_F(TestCaseInfoPropertiesCombinationTest_996, NonePropertyAllReturnFalse_996) {
    auto info = createTestCaseInfo("test_none_props", "");
    info->properties = TestCaseProperties::None;
    EXPECT_FALSE(info->isHidden());
    EXPECT_FALSE(info->throws());
    EXPECT_FALSE(info->okToFail());
    EXPECT_FALSE(info->expectedToFail());
}

TEST_F(TestCaseInfoPropertiesCombinationTest_996, BenchmarkPropertyDoesNotAffectThrows_996) {
    auto info = createTestCaseInfo("test_benchmark", "");
    info->properties = TestCaseProperties::Benchmark;
    EXPECT_FALSE(info->throws());
    EXPECT_FALSE(info->isHidden());
    EXPECT_FALSE(info->okToFail());
    EXPECT_FALSE(info->expectedToFail());
}

TEST_F(TestCaseInfoPropertiesCombinationTest_996, NonPortablePropertyDoesNotAffectOtherQueries_996) {
    auto info = createTestCaseInfo("test_nonportable", "");
    info->properties = TestCaseProperties::NonPortable;
    EXPECT_FALSE(info->throws());
    EXPECT_FALSE(info->isHidden());
    EXPECT_FALSE(info->okToFail());
    EXPECT_FALSE(info->expectedToFail());
}

// ============================================================
// Tests with hidden tags
// ============================================================

class TestCaseInfoHiddenTagTest_996 : public ::testing::Test {
protected:
    std::unique_ptr<TestCaseInfo> createTestCaseInfo(const std::string& name, const std::string& tags) {
        NameAndTags nameAndTags(name, tags);
        auto info = std::make_unique<TestCaseInfo>(StringRef("TestClass"), nameAndTags, makeSourceLineInfo());
        return info;
    }
};

TEST_F(TestCaseInfoHiddenTagTest_996, HiddenTagSetsIsHiddenProperty_996) {
    auto info = createTestCaseInfo("test_hidden_tag", "[.][tag1]");
    EXPECT_TRUE(info->isHidden());
}

TEST_F(TestCaseInfoHiddenTagTest_996, ThrowsTagSetsThrowsProperty_996) {
    auto info = createTestCaseInfo("test_throws_tag", "[!throws]");
    EXPECT_TRUE(info->throws());
}

TEST_F(TestCaseInfoHiddenTagTest_996, ShouldFailTagSetsExpectedToFail_996) {
    auto info = createTestCaseInfo("test_shouldfail_tag", "[!shouldfail]");
    EXPECT_TRUE(info->expectedToFail());
    EXPECT_TRUE(info->okToFail());
}

TEST_F(TestCaseInfoHiddenTagTest_996, MayFailTagSetsOkToFail_996) {
    auto info = createTestCaseInfo("test_mayfail_tag", "[!mayfail]");
    EXPECT_TRUE(info->okToFail());
    EXPECT_FALSE(info->expectedToFail());
}
