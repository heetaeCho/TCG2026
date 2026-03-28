// File: ./TestProjects/ninja/tests/pool_name_test_76.cc

#include "state.h"

#include <gtest/gtest.h>
#include <string>

class PoolTest_76 : public ::testing::Test {};

// Normal operation: constructor should store the given name and return it via name().
TEST_F(PoolTest_76, ReturnsConstructorName_76) {
  std::string name = "default";
  Pool pool(name, /*depth=*/1);

  EXPECT_EQ("default", pool.name());
}

// Normal operation: multiple Pool instances keep their own names independently.
TEST_F(PoolTest_76, MultiplePoolsHaveIndependentNames_76) {
  Pool pool1("compile", /*depth=*/1);
  Pool pool2("link", /*depth=*/2);

  EXPECT_EQ("compile", pool1.name());
  EXPECT_EQ("link", pool2.name());
}

// Boundary: empty string name should be preserved.
TEST_F(PoolTest_76, EmptyNameIsPreserved_76) {
  std::string empty_name = "";
  Pool pool(empty_name, /*depth=*/1);

  EXPECT_TRUE(pool.name().empty());
}

// Boundary / object lifetime: Pool should keep its own copy of the name,
// not a reference to the original std::string variable.
TEST_F(PoolTest_76, NameIsIndependentOfSourceString_76) {
  std::string source = "original";
  Pool pool(source, /*depth=*/1);

  // Change the original string after constructing the Pool.
  source = "modified";

  // Pool::name() should still return the original contents.
  EXPECT_EQ("original", pool.name());
}

// Normal operation with special characters: name() should round-trip arbitrary text.
TEST_F(PoolTest_76, NameSupportsSpecialCharacters_76) {
  std::string special_name = "콘솔 pool_#1 🚀";
  Pool pool(special_name, /*depth=*/1);

  EXPECT_EQ(special_name, pool.name());
}
