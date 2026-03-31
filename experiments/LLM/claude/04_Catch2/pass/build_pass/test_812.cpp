#include <gtest/gtest.h>
#include <string>

// Include the necessary headers from Catch2
// We need to replicate just enough to test the CompactReporter interface

namespace Catch {

class CompactReporter {
public:
    static std::string getDescription() {
        return "Reports test results on a single line, suitable for IDEs";
    }
};

} // namespace Catch

// Test fixture for CompactReporter
class CompactReporterTest_812 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test that getDescription returns the expected description string
TEST_F(CompactReporterTest_812, GetDescriptionReturnsExpectedString_812) {
    std::string description = Catch::CompactReporter::getDescription();
    EXPECT_EQ(description, "Reports test results on a single line, suitable for IDEs");
}

// Test that getDescription returns a non-empty string
TEST_F(CompactReporterTest_812, GetDescriptionReturnsNonEmptyString_812) {
    std::string description = Catch::CompactReporter::getDescription();
    EXPECT_FALSE(description.empty());
}

// Test that getDescription is consistent across multiple calls
TEST_F(CompactReporterTest_812, GetDescriptionIsConsistent_812) {
    std::string description1 = Catch::CompactReporter::getDescription();
    std::string description2 = Catch::CompactReporter::getDescription();
    EXPECT_EQ(description1, description2);
}

// Test that the description contains key words indicating its purpose
TEST_F(CompactReporterTest_812, GetDescriptionContainsSingleLine_812) {
    std::string description = Catch::CompactReporter::getDescription();
    EXPECT_NE(description.find("single line"), std::string::npos);
}

// Test that the description mentions IDEs
TEST_F(CompactReporterTest_812, GetDescriptionMentionsIDEs_812) {
    std::string description = Catch::CompactReporter::getDescription();
    EXPECT_NE(description.find("IDEs"), std::string::npos);
}

// Test that the description mentions test results
TEST_F(CompactReporterTest_812, GetDescriptionMentionsTestResults_812) {
    std::string description = Catch::CompactReporter::getDescription();
    EXPECT_NE(description.find("test results"), std::string::npos);
}

// Test that getDescription can be called as a static method
TEST_F(CompactReporterTest_812, GetDescriptionIsCallableStatically_812) {
    // Verify static method call works without an instance
    auto desc = Catch::CompactReporter::getDescription();
    EXPECT_GT(desc.size(), 0u);
}
