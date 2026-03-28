// File: node_path_test_35.cc

#include "graph.h"

#include <gtest/gtest.h>

// Simple fixture for Node path() tests.
class NodePathTest_35 : public ::testing::Test {
 protected:
  // Helper to create a Node with given path and some arbitrary slash_bits.
  Node MakeNode(const std::string& path, uint64_t slash_bits = 0) {
    return Node(path, slash_bits);
  }
};

// [Normal operation] path() should return the same path string
// that was provided at construction time.
TEST_F(NodePathTest_35, ReturnsOriginalPathAfterConstruction_35) {
  const std::string input_path = "build.ninja";
  Node node = MakeNode(input_path, /*slash_bits=*/0);

  EXPECT_EQ(input_path, node.path());
}

// [Boundary] path() should correctly handle an empty path string.
TEST_F(NodePathTest_35, HandlesEmptyPath_35) {
  const std::string empty_path = "";
  Node node = MakeNode(empty_path, /*slash_bits=*/0);

  EXPECT_EQ(empty_path, node.path());
  EXPECT_TRUE(node.path().empty());
}

// [Boundary / special characters] path() should preserve paths containing
// directories, dots, dashes, and other typical filesystem characters.
TEST_F(NodePathTest_35, PreservesComplexPathWithDirectoriesAndDots_35) {
  const std::string complex_path = "src/../build/output-file-01.o";
  Node node = MakeNode(complex_path, /*slash_bits=*/0x3);

  EXPECT_EQ(complex_path, node.path());
}

// [Boundary / encoding] path() should work with non-ASCII characters as well,
// since it exposes a std::string and does not impose encoding restrictions.
TEST_F(NodePathTest_35, SupportsNonAsciiPath_35) {
  const std::string utf8_path = u8"경로/파일이름.txt";
  Node node = MakeNode(utf8_path, /*slash_bits=*/0);

  EXPECT_EQ(utf8_path, node.path());
}

// [Stability] Multiple calls to path() should consistently return
// the same value over the lifetime of the Node object.
TEST_F(NodePathTest_35, ReturnsConsistentPathOnMultipleCalls_35) {
  const std::string input_path = "dir/subdir/file.cc";
  Node node = MakeNode(input_path, /*slash_bits=*/1);

  const std::string& first = node.path();
  const std::string& second = node.path();
  const std::string& third = node.path();

  EXPECT_EQ(input_path, first);
  EXPECT_EQ(input_path, second);
  EXPECT_EQ(input_path, third);
}
