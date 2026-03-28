#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <fstream>
#include <string>
#include <cstdio>
#include <filesystem>

#include "manifest_parser.h"
#include "state.h"
#include "disk_interface.h"

class ManifestFuzzerTest_168 : public ::testing::Test {
protected:
  State state_;
  RealDiskInterface disk_interface_;
  std::string build_file_ = "/tmp/build_test_168.ninja";

  void SetUp() override {
    // Clean up any leftover file
    std::filesystem::remove_all(build_file_);
  }

  void TearDown() override {
    std::filesystem::remove_all(build_file_);
  }

  void WriteBuildFile(const std::string& content) {
    FILE* fp = fopen(build_file_.c_str(), "wb");
    ASSERT_NE(fp, nullptr);
    fwrite(content.data(), content.size(), 1, fp);
    fclose(fp);
  }
};

// Test loading a valid, minimal build file
TEST_F(ManifestFuzzerTest_168, LoadValidMinimalBuildFile_168) {
  std::string content = "rule cc\n  command = gcc $in -o $out\nbuild out: cc in\n";
  WriteBuildFile(content);

  std::string err;
  ManifestParser parser(&state_, &disk_interface_);
  bool result = parser.Load(build_file_, &err);
  EXPECT_TRUE(result) << "Error: " << err;
  EXPECT_TRUE(err.empty());

  // Verify nodes were created
  EXPECT_NE(state_.LookupNode("out"), nullptr);
  EXPECT_NE(state_.LookupNode("in"), nullptr);
}

// Test loading an empty file
TEST_F(ManifestFuzzerTest_168, LoadEmptyFile_168) {
  std::string content = "";
  WriteBuildFile(content);

  std::string err;
  ManifestParser parser(&state_, &disk_interface_);
  bool result = parser.Load(build_file_, &err);
  EXPECT_TRUE(result) << "Error: " << err;
}

// Test loading a file that doesn't exist
TEST_F(ManifestFuzzerTest_168, LoadNonExistentFile_168) {
  std::string err;
  ManifestParser parser(&state_, &disk_interface_);
  bool result = parser.Load("/tmp/nonexistent_file_168.ninja", &err);
  EXPECT_FALSE(result);
  EXPECT_FALSE(err.empty());
}

// Test loading a file with invalid syntax
TEST_F(ManifestFuzzerTest_168, LoadInvalidSyntax_168) {
  std::string content = "this is not valid ninja syntax!@#$%\n";
  WriteBuildFile(content);

  std::string err;
  ManifestParser parser(&state_, &disk_interface_);
  bool result = parser.Load(build_file_, &err);
  EXPECT_FALSE(result);
  EXPECT_FALSE(err.empty());
}

// Test loading a file with only a rule definition (no build edges)
TEST_F(ManifestFuzzerTest_168, LoadOnlyRuleDefinition_168) {
  std::string content = "rule cc\n  command = gcc $in -o $out\n";
  WriteBuildFile(content);

  std::string err;
  ManifestParser parser(&state_, &disk_interface_);
  bool result = parser.Load(build_file_, &err);
  EXPECT_TRUE(result) << "Error: " << err;
  EXPECT_EQ(state_.edges_.size(), 0u);
}

// Test loading a file with multiple build edges
TEST_F(ManifestFuzzerTest_168, LoadMultipleBuildEdges_168) {
  std::string content =
    "rule cc\n"
    "  command = gcc $in -o $out\n"
    "build out1: cc in1\n"
    "build out2: cc in2\n";
  WriteBuildFile(content);

  std::string err;
  ManifestParser parser(&state_, &disk_interface_);
  bool result = parser.Load(build_file_, &err);
  EXPECT_TRUE(result) << "Error: " << err;
  EXPECT_EQ(state_.edges_.size(), 2u);
}

// Test loading a file with pool definitions
TEST_F(ManifestFuzzerTest_168, LoadWithPoolDefinition_168) {
  std::string content =
    "pool link_pool\n"
    "  depth = 4\n"
    "rule link\n"
    "  command = ld $in -o $out\n"
    "  pool = link_pool\n"
    "build out: link in\n";
  WriteBuildFile(content);

  std::string err;
  ManifestParser parser(&state_, &disk_interface_);
  bool result = parser.Load(build_file_, &err);
  EXPECT_TRUE(result) << "Error: " << err;
  EXPECT_NE(state_.LookupPool("link_pool"), nullptr);
}

// Test loading a file with default targets
TEST_F(ManifestFuzzerTest_168, LoadWithDefaultTarget_168) {
  std::string content =
    "rule cc\n"
    "  command = gcc $in -o $out\n"
    "build out: cc in\n"
    "default out\n";
  WriteBuildFile(content);

  std::string err;
  ManifestParser parser(&state_, &disk_interface_);
  bool result = parser.Load(build_file_, &err);
  EXPECT_TRUE(result) << "Error: " << err;
  EXPECT_FALSE(state_.defaults_.empty());
}

// Test loading a file with variable bindings
TEST_F(ManifestFuzzerTest_168, LoadWithVariableBindings_168) {
  std::string content =
    "cflags = -Wall\n"
    "rule cc\n"
    "  command = gcc $cflags $in -o $out\n"
    "build out: cc in\n";
  WriteBuildFile(content);

  std::string err;
  ManifestParser parser(&state_, &disk_interface_);
  bool result = parser.Load(build_file_, &err);
  EXPECT_TRUE(result) << "Error: " << err;
}

// Test with binary/garbage data (simulating fuzzer input)
TEST_F(ManifestFuzzerTest_168, LoadGarbageBinaryData_168) {
  std::string content;
  for (int i = 0; i < 256; ++i) {
    content.push_back(static_cast<char>(i));
  }
  WriteBuildFile(content);

  std::string err;
  ManifestParser parser(&state_, &disk_interface_);
  // Should not crash, may fail to parse
  parser.Load(build_file_, &err);
  // We just check it doesn't crash - no assertion on result
}

// Test with null bytes in data
TEST_F(ManifestFuzzerTest_168, LoadDataWithNullBytes_168) {
  std::string content = "rule cc\n  command = gcc\n";
  content.push_back('\0');
  content += "build out: cc in\n";
  WriteBuildFile(content);

  std::string err;
  ManifestParser parser(&state_, &disk_interface_);
  // Should not crash
  parser.Load(build_file_, &err);
}

// Test loading a file with only whitespace/newlines
TEST_F(ManifestFuzzerTest_168, LoadWhitespaceOnly_168) {
  std::string content = "\n\n\n   \n\n";
  WriteBuildFile(content);

  std::string err;
  ManifestParser parser(&state_, &disk_interface_);
  bool result = parser.Load(build_file_, &err);
  EXPECT_TRUE(result) << "Error: " << err;
}

// Test loading a file with comments
TEST_F(ManifestFuzzerTest_168, LoadWithComments_168) {
  std::string content =
    "# This is a comment\n"
    "rule cc\n"
    "  command = gcc $in -o $out\n"
    "# Another comment\n"
    "build out: cc in\n";
  WriteBuildFile(content);

  std::string err;
  ManifestParser parser(&state_, &disk_interface_);
  bool result = parser.Load(build_file_, &err);
  EXPECT_TRUE(result) << "Error: " << err;
}

// Test ParseTest with valid input
TEST_F(ManifestFuzzerTest_168, ParseTestValidInput_168) {
  std::string input =
    "rule cc\n"
    "  command = gcc $in -o $out\n"
    "build out: cc in\n";
  std::string err;
  ManifestParser parser(&state_, &disk_interface_);
  bool result = parser.ParseTest(input, &err);
  EXPECT_TRUE(result) << "Error: " << err;
}

// Test ParseTest with invalid input
TEST_F(ManifestFuzzerTest_168, ParseTestInvalidInput_168) {
  std::string input = "invalid content here\n";
  std::string err;
  ManifestParser parser(&state_, &disk_interface_);
  bool result = parser.ParseTest(input, &err);
  EXPECT_FALSE(result);
  EXPECT_FALSE(err.empty());
}

// Test ParseTest with empty input
TEST_F(ManifestFuzzerTest_168, ParseTestEmptyInput_168) {
  std::string input = "";
  std::string err;
  ManifestParser parser(&state_, &disk_interface_);
  bool result = parser.ParseTest(input, &err);
  EXPECT_TRUE(result) << "Error: " << err;
}

// Test that state is populated correctly after loading
TEST_F(ManifestFuzzerTest_168, StatePopulatedAfterLoad_168) {
  std::string content =
    "rule cc\n"
    "  command = gcc $in -o $out\n"
    "build foo.o: cc foo.c\n"
    "build bar.o: cc bar.c\n"
    "build app: cc foo.o bar.o\n";
  WriteBuildFile(content);

  std::string err;
  ManifestParser parser(&state_, &disk_interface_);
  bool result = parser.Load(build_file_, &err);
  EXPECT_TRUE(result) << "Error: " << err;
  EXPECT_EQ(state_.edges_.size(), 3u);
  EXPECT_NE(state_.LookupNode("foo.o"), nullptr);
  EXPECT_NE(state_.LookupNode("bar.o"), nullptr);
  EXPECT_NE(state_.LookupNode("app"), nullptr);
  EXPECT_NE(state_.LookupNode("foo.c"), nullptr);
  EXPECT_NE(state_.LookupNode("bar.c"), nullptr);
}

// Test with a very large file
TEST_F(ManifestFuzzerTest_168, LoadLargeFile_168) {
  std::string content = "rule cc\n  command = gcc $in -o $out\n";
  for (int i = 0; i < 1000; ++i) {
    content += "build out" + std::to_string(i) + ": cc in" + std::to_string(i) + "\n";
  }
  WriteBuildFile(content);

  std::string err;
  ManifestParser parser(&state_, &disk_interface_);
  bool result = parser.Load(build_file_, &err);
  EXPECT_TRUE(result) << "Error: " << err;
  EXPECT_EQ(state_.edges_.size(), 1000u);
}

// Test duplicate rule name
TEST_F(ManifestFuzzerTest_168, LoadDuplicateRuleName_168) {
  std::string content =
    "rule cc\n"
    "  command = gcc\n"
    "rule cc\n"
    "  command = g++\n";
  WriteBuildFile(content);

  std::string err;
  ManifestParser parser(&state_, &disk_interface_);
  bool result = parser.Load(build_file_, &err);
  // Duplicate rules should cause an error
  EXPECT_FALSE(result);
  EXPECT_FALSE(err.empty());
}

// Test duplicate output
TEST_F(ManifestFuzzerTest_168, LoadDuplicateOutput_168) {
  std::string content =
    "rule cc\n"
    "  command = gcc $in -o $out\n"
    "build out: cc in1\n"
    "build out: cc in2\n";
  WriteBuildFile(content);

  std::string err;
  ManifestParser parser(&state_, &disk_interface_);
  bool result = parser.Load(build_file_, &err);
  // Duplicate outputs should cause an error
  EXPECT_FALSE(result);
  EXPECT_FALSE(err.empty());
}

// Test rule without command
TEST_F(ManifestFuzzerTest_168, LoadRuleWithoutCommand_168) {
  std::string content =
    "rule cc\n"
    "  description = compile\n"
    "build out: cc in\n";
  WriteBuildFile(content);

  std::string err;
  ManifestParser parser(&state_, &disk_interface_);
  bool result = parser.Load(build_file_, &err);
  // A rule without command should fail
  EXPECT_FALSE(result);
}

// Test build edge referencing non-existent rule
TEST_F(ManifestFuzzerTest_168, LoadBuildWithNonExistentRule_168) {
  std::string content = "build out: nonexistent_rule in\n";
  WriteBuildFile(content);

  std::string err;
  ManifestParser parser(&state_, &disk_interface_);
  bool result = parser.Load(build_file_, &err);
  EXPECT_FALSE(result);
  EXPECT_FALSE(err.empty());
}

// Test that the phony rule works
TEST_F(ManifestFuzzerTest_168, LoadPhonyRule_168) {
  std::string content = "build alias: phony real_file\n";
  WriteBuildFile(content);

  std::string err;
  ManifestParser parser(&state_, &disk_interface_);
  bool result = parser.Load(build_file_, &err);
  EXPECT_TRUE(result) << "Error: " << err;
  EXPECT_NE(state_.LookupNode("alias"), nullptr);
}

// Test with subninja/include referencing non-existent file
TEST_F(ManifestFuzzerTest_168, LoadWithNonExistentSubninja_168) {
  std::string content = "subninja /tmp/nonexistent_sub_168.ninja\n";
  WriteBuildFile(content);

  std::string err;
  ManifestParser parser(&state_, &disk_interface_);
  bool result = parser.Load(build_file_, &err);
  EXPECT_FALSE(result);
  EXPECT_FALSE(err.empty());
}

// Test with include referencing non-existent file
TEST_F(ManifestFuzzerTest_168, LoadWithNonExistentInclude_168) {
  std::string content = "include /tmp/nonexistent_include_168.ninja\n";
  WriteBuildFile(content);

  std::string err;
  ManifestParser parser(&state_, &disk_interface_);
  bool result = parser.Load(build_file_, &err);
  EXPECT_FALSE(result);
  EXPECT_FALSE(err.empty());
}

// Test State Reset after loading
TEST_F(ManifestFuzzerTest_168, StateResetAfterLoad_168) {
  std::string content =
    "rule cc\n"
    "  command = gcc $in -o $out\n"
    "build out: cc in\n";
  WriteBuildFile(content);

  std::string err;
  ManifestParser parser(&state_, &disk_interface_);
  bool result = parser.Load(build_file_, &err);
  EXPECT_TRUE(result) << "Error: " << err;
  EXPECT_FALSE(state_.edges_.empty());

  state_.Reset();
  // After reset, edges should still exist but nodes should be reset
  // (Reset resets node state, not the graph structure)
  EXPECT_FALSE(state_.edges_.empty());
}

// Test RealDiskInterface Stat on non-existent path
TEST_F(ManifestFuzzerTest_168, DiskInterfaceStatNonExistent_168) {
  std::string err;
  TimeStamp t = disk_interface_.Stat("/tmp/definitely_nonexistent_168", &err);
  EXPECT_EQ(t, 0);
}

// Test RealDiskInterface ReadFile on non-existent path
TEST_F(ManifestFuzzerTest_168, DiskInterfaceReadFileNonExistent_168) {
  std::string contents, err;
  DiskInterface::Status status = disk_interface_.ReadFile("/tmp/definitely_nonexistent_168", &contents, &err);
  EXPECT_NE(status, DiskInterface::Okay);
}
