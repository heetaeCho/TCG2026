#include <gtest/gtest.h>
#include <cstdlib>
#include <cstdio>
#include <fstream>
#include <string>
#include <array>
#include <memory>

// Helper to run ninja as a subprocess and capture exit code
class NinjaMainTest_164 : public ::testing::Test {
protected:
    std::string ninja_binary_;
    std::string temp_dir_;

    void SetUp() override {
        // Assume ninja binary is available in path or build directory
        ninja_binary_ = "./ninja";
        temp_dir_ = testing::TempDir();
    }

    void TearDown() override {
        // Clean up any build.ninja files we created
        std::string buildfile = temp_dir_ + "/build.ninja";
        std::remove(buildfile.c_str());
    }

    int RunNinja(const std::string& args) {
        std::string cmd = ninja_binary_ + " " + args + " 2>/dev/null";
        return WEXITSTATUS(std::system(cmd.c_str()));
    }

    int RunNinjaInDir(const std::string& dir, const std::string& args) {
        std::string cmd = ninja_binary_ + " -C " + dir + " " + args + " 2>/dev/null";
        return WEXITSTATUS(std::system(cmd.c_str()));
    }

    void CreateBuildFile(const std::string& dir, const std::string& content) {
        std::string path = dir + "/build.ninja";
        std::ofstream ofs(path);
        ofs << content;
        ofs.close();
    }
};

// Test that --version flag returns success
TEST_F(NinjaMainTest_164, VersionFlagReturnsSuccess_164) {
    int result = RunNinja("--version");
    EXPECT_EQ(0, result);
}

// Test that -h (help) flag returns success
TEST_F(NinjaMainTest_164, HelpFlagReturnsSuccess_164) {
    int result = RunNinja("-h");
    EXPECT_EQ(0, result);
}

// Test that an invalid tool returns non-zero
TEST_F(NinjaMainTest_164, InvalidToolReturnsError_164) {
    int result = RunNinja("-t nonexistent_tool_xyz");
    EXPECT_NE(0, result);
}

// Test that running ninja with no build file in a temp directory fails
TEST_F(NinjaMainTest_164, NoBuildFileReturnsError_164) {
    int result = RunNinjaInDir("/tmp/ninja_test_no_buildfile_164", "");
    EXPECT_NE(0, result);
}

// Test that -t list returns success (listing available tools)
TEST_F(NinjaMainTest_164, ToolListReturnsSuccess_164) {
    int result = RunNinja("-t list");
    EXPECT_EQ(0, result);
}

// Test that an empty build.ninja file is valid (nothing to do)
TEST_F(NinjaMainTest_164, EmptyBuildFileReturnsSuccess_164) {
    CreateBuildFile(temp_dir_, "");
    int result = RunNinjaInDir(temp_dir_, "");
    EXPECT_EQ(0, result);
}

// Test with a minimal valid build.ninja
TEST_F(NinjaMainTest_164, MinimalBuildFileReturnsSuccess_164) {
    CreateBuildFile(temp_dir_, "rule echo\n  command = echo hello\nbuild out: echo\n");
    int result = RunNinjaInDir(temp_dir_, "out");
    EXPECT_EQ(0, result);
    std::remove((temp_dir_ + "/out").c_str());
    std::remove((temp_dir_ + "/.ninja_log").c_str());
    std::remove((temp_dir_ + "/.ninja_deps").c_str());
}

// Test building a nonexistent target returns error
TEST_F(NinjaMainTest_164, NonexistentTargetReturnsError_164) {
    CreateBuildFile(temp_dir_, "");
    int result = RunNinjaInDir(temp_dir_, "nonexistent_target");
    EXPECT_NE(0, result);
}

// Test -C with an invalid directory returns error
TEST_F(NinjaMainTest_164, InvalidDirectoryReturnsError_164) {
    int result = RunNinja("-C /nonexistent/path/xyz_164");
    EXPECT_NE(0, result);
}

// Test -t clean with an empty build file
TEST_F(NinjaMainTest_164, CleanToolWithEmptyBuildFile_164) {
    CreateBuildFile(temp_dir_, "");
    int result = RunNinjaInDir(temp_dir_, "-t clean");
    EXPECT_EQ(0, result);
}
