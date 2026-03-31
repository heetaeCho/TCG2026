#include <gtest/gtest.h>
#include <string>
#include <vector>

// Include necessary headers
#include "util.h"
#include "string_piece.h"

// We need to access CGroupSubSys which is defined in util.cc
// Since it's a struct, we may need to declare it or include appropriately.
// Based on the provided code, CGroupSubSys is in util.cc

// Forward declaration or re-declaration of the struct for testing purposes
// (since the struct is defined in util.cc, we need access to it)

// If the struct isn't exposed via a header, we might need to include util.cc directly
// or replicate the struct definition. Given the constraints, we'll assume it's accessible.

// Helper: split function used internally
extern std::vector<StringPiece> SplitStringPiece(StringPiece input, char sep);

struct CGroupSubSys {
    int id;
    std::string name;
    std::vector<std::string> subsystems;
    bool parse(std::string& line);
};

class CGroupSubSysTest_150 : public ::testing::Test {
protected:
    CGroupSubSys cgroup;
};

// Test normal parsing with a single subsystem
TEST_F(CGroupSubSysTest_150, ParseNormalSingleSubsystem_150) {
    std::string line = "1:cpu:/";
    bool result = cgroup.parse(line);
    EXPECT_TRUE(result);
    EXPECT_EQ(cgroup.id, 1);
    EXPECT_EQ(cgroup.name, "/");
    ASSERT_EQ(cgroup.subsystems.size(), 1u);
    EXPECT_EQ(cgroup.subsystems[0], "cpu");
}

// Test normal parsing with multiple subsystems (comma-separated)
TEST_F(CGroupSubSysTest_150, ParseMultipleSubsystems_150) {
    std::string line = "2:cpu,cpuacct:/user";
    bool result = cgroup.parse(line);
    EXPECT_TRUE(result);
    EXPECT_EQ(cgroup.id, 2);
    EXPECT_EQ(cgroup.name, "/user");
    ASSERT_EQ(cgroup.subsystems.size(), 2u);
    EXPECT_EQ(cgroup.subsystems[0], "cpu");
    EXPECT_EQ(cgroup.subsystems[1], "cpuacct");
}

// Test parsing with id = 0
TEST_F(CGroupSubSysTest_150, ParseIdZero_150) {
    std::string line = "0::/init.scope";
    bool result = cgroup.parse(line);
    EXPECT_TRUE(result);
    EXPECT_EQ(cgroup.id, 0);
    EXPECT_EQ(cgroup.name, "/init.scope");
}

// Test parsing fails when no colon is present
TEST_F(CGroupSubSysTest_150, ParseFailsNoColon_150) {
    std::string line = "no_colon_here";
    bool result = cgroup.parse(line);
    EXPECT_FALSE(result);
}

// Test parsing fails when only one colon is present
TEST_F(CGroupSubSysTest_150, ParseFailsOneColon_150) {
    std::string line = "1:cpu_only";
    bool result = cgroup.parse(line);
    EXPECT_FALSE(result);
}

// Test parsing with empty subsystem field
TEST_F(CGroupSubSysTest_150, ParseEmptySubsystemField_150) {
    std::string line = "0::/";
    bool result = cgroup.parse(line);
    EXPECT_TRUE(result);
    EXPECT_EQ(cgroup.id, 0);
    EXPECT_EQ(cgroup.name, "/");
}

// Test parsing with large id
TEST_F(CGroupSubSysTest_150, ParseLargeId_150) {
    std::string line = "999:memory:/docker/abc123";
    bool result = cgroup.parse(line);
    EXPECT_TRUE(result);
    EXPECT_EQ(cgroup.id, 999);
    EXPECT_EQ(cgroup.name, "/docker/abc123");
    ASSERT_EQ(cgroup.subsystems.size(), 1u);
    EXPECT_EQ(cgroup.subsystems[0], "memory");
}

// Test parsing with empty name after second colon
TEST_F(CGroupSubSysTest_150, ParseEmptyName_150) {
    std::string line = "1:cpu:";
    bool result = cgroup.parse(line);
    EXPECT_TRUE(result);
    EXPECT_EQ(cgroup.id, 1);
    EXPECT_EQ(cgroup.name, "");
    ASSERT_EQ(cgroup.subsystems.size(), 1u);
    EXPECT_EQ(cgroup.subsystems[0], "cpu");
}

// Test parsing with many subsystems
TEST_F(CGroupSubSysTest_150, ParseManySubsystems_150) {
    std::string line = "3:cpu,cpuacct,memory,blkio:/sys";
    bool result = cgroup.parse(line);
    EXPECT_TRUE(result);
    EXPECT_EQ(cgroup.id, 3);
    EXPECT_EQ(cgroup.name, "/sys");
    ASSERT_EQ(cgroup.subsystems.size(), 4u);
    EXPECT_EQ(cgroup.subsystems[0], "cpu");
    EXPECT_EQ(cgroup.subsystems[1], "cpuacct");
    EXPECT_EQ(cgroup.subsystems[2], "memory");
    EXPECT_EQ(cgroup.subsystems[3], "blkio");
}

// Test parsing empty string
TEST_F(CGroupSubSysTest_150, ParseEmptyString_150) {
    std::string line = "";
    bool result = cgroup.parse(line);
    EXPECT_FALSE(result);
}

// Test parsing with name containing colons after the second colon
TEST_F(CGroupSubSysTest_150, ParseNameWithColons_150) {
    std::string line = "1:cpu:/path:with:colons";
    bool result = cgroup.parse(line);
    EXPECT_TRUE(result);
    EXPECT_EQ(cgroup.id, 1);
    // The name should be everything after the second colon
    // Since line is modified (first colon replaced with \0), and name = line.substr(second+1),
    // the name should capture "/path:with:colons"
    EXPECT_EQ(cgroup.name, "/path:with:colons");
}

// Test parsing with non-numeric id (atoi returns 0 for non-numeric)
TEST_F(CGroupSubSysTest_150, ParseNonNumericId_150) {
    std::string line = "abc:cpu:/test";
    bool result = cgroup.parse(line);
    EXPECT_TRUE(result);
    EXPECT_EQ(cgroup.id, 0); // atoi("abc") returns 0
    EXPECT_EQ(cgroup.name, "/test");
}

// Test parsing with negative id
TEST_F(CGroupSubSysTest_150, ParseNegativeId_150) {
    std::string line = "-1:cpu:/test";
    bool result = cgroup.parse(line);
    EXPECT_TRUE(result);
    EXPECT_EQ(cgroup.id, -1);
    EXPECT_EQ(cgroup.name, "/test");
}

// Test that parse modifies the line (replaces colons with null)
TEST_F(CGroupSubSysTest_150, ParseModifiesLine_150) {
    std::string line = "1:cpu:/test";
    cgroup.parse(line);
    // The first and second colons should have been replaced with '\0'
    EXPECT_EQ(line[1], '\0');
    EXPECT_EQ(line[5], '\0');
}

// Test parsing with only two colons and minimal content
TEST_F(CGroupSubSysTest_150, ParseMinimalValidLine_150) {
    std::string line = "0::";
    bool result = cgroup.parse(line);
    EXPECT_TRUE(result);
    EXPECT_EQ(cgroup.id, 0);
    EXPECT_EQ(cgroup.name, "");
}

// Test line that starts with a colon
TEST_F(CGroupSubSysTest_150, ParseStartsWithColon_150) {
    std::string line = ":cpu:/test";
    bool result = cgroup.parse(line);
    EXPECT_TRUE(result);
    EXPECT_EQ(cgroup.id, 0); // atoi("") returns 0
    EXPECT_EQ(cgroup.name, "/test");
    ASSERT_EQ(cgroup.subsystems.size(), 1u);
    EXPECT_EQ(cgroup.subsystems[0], "cpu");
}
