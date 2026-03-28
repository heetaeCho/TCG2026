#include "catch2/internal/catch_clara.hpp"
#include <gtest/gtest.h>
#include <string>
#include <vector>

using namespace Catch::Clara::Detail;

// Test fixture for BoundValueRef tests
class BoundValueRefTest_377 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test that BoundValueRef with std::vector<std::string> is a container
TEST_F(BoundValueRefTest_377, VectorStringIsContainer_377) {
    std::vector<std::string> vec;
    BoundValueRef<std::string> ref(vec);
    EXPECT_TRUE(ref.isContainer());
}

// Test that BoundValueRef with std::vector<int> is a container
TEST_F(BoundValueRefTest_377, VectorIntIsContainer_377) {
    std::vector<int> vec;
    BoundValueRef<int> ref(vec);
    EXPECT_TRUE(ref.isContainer());
}

// Test that BoundValueRef with std::vector<double> is a container
TEST_F(BoundValueRefTest_377, VectorDoubleIsContainer_377) {
    std::vector<double> vec;
    BoundValueRef<double> ref(vec);
    EXPECT_TRUE(ref.isContainer());
}

// Test that BoundValueRef with a single string reference is not a container
TEST_F(BoundValueRefTest_377, SingleStringIsNotContainer_377) {
    std::string val;
    BoundValueRef<std::string> ref(val);
    EXPECT_FALSE(ref.isContainer());
}

// Test that BoundValueRef with a single int reference is not a container
TEST_F(BoundValueRefTest_377, SingleIntIsNotContainer_377) {
    int val = 0;
    BoundValueRef<int> ref(val);
    EXPECT_FALSE(ref.isContainer());
}

// Test that BoundValueRef with a single double reference is not a container
TEST_F(BoundValueRefTest_377, SingleDoubleIsNotContainer_377) {
    double val = 0.0;
    BoundValueRef<double> ref(val);
    EXPECT_FALSE(ref.isContainer());
}

// Test that BoundValueRef with a single bool reference is not a container
TEST_F(BoundValueRefTest_377, SingleBoolIsNotContainer_377) {
    bool val = false;
    BoundValueRef<bool> ref(val);
    EXPECT_FALSE(ref.isContainer());
}

// Test setValue on a vector of strings appends values
TEST_F(BoundValueRefTest_377, SetValueOnVectorStringAppends_377) {
    std::vector<std::string> vec;
    BoundValueRef<std::string> ref(vec);
    auto result = ref.setValue("hello");
    EXPECT_EQ(vec.size(), 1u);
    EXPECT_EQ(vec[0], "hello");

    ref.setValue("world");
    EXPECT_EQ(vec.size(), 2u);
    EXPECT_EQ(vec[1], "world");
}

// Test setValue on a single string sets the value
TEST_F(BoundValueRefTest_377, SetValueOnSingleString_377) {
    std::string val;
    BoundValueRef<std::string> ref(val);
    auto result = ref.setValue("test_value");
    EXPECT_EQ(val, "test_value");
}

// Test setValue on a single int parses integer
TEST_F(BoundValueRefTest_377, SetValueOnSingleInt_377) {
    int val = 0;
    BoundValueRef<int> ref(val);
    auto result = ref.setValue("42");
    EXPECT_EQ(val, 42);
}

// Test setValue on vector of ints appends parsed values
TEST_F(BoundValueRefTest_377, SetValueOnVectorIntAppends_377) {
    std::vector<int> vec;
    BoundValueRef<int> ref(vec);
    ref.setValue("10");
    ref.setValue("20");
    EXPECT_EQ(vec.size(), 2u);
    EXPECT_EQ(vec[0], 10);
    EXPECT_EQ(vec[1], 20);
}

// Test that isContainer consistently returns the same value
TEST_F(BoundValueRefTest_377, IsContainerConsistentForVector_377) {
    std::vector<std::string> vec;
    BoundValueRef<std::string> ref(vec);
    EXPECT_TRUE(ref.isContainer());
    EXPECT_TRUE(ref.isContainer()); // calling again should be consistent
}

// Test empty vector is still a container
TEST_F(BoundValueRefTest_377, EmptyVectorIsStillContainer_377) {
    std::vector<int> vec;
    BoundValueRef<int> ref(vec);
    EXPECT_TRUE(ref.isContainer());
    EXPECT_TRUE(vec.empty());
}
