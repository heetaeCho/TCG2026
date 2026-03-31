#include <gtest/gtest.h>
#include "yaml-cpp/depthguard.h"
#include "yaml-cpp/exceptions.h"
#include "yaml-cpp/mark.h"
#include <string>

namespace YAML {
namespace {

class DeepRecursionTest_91 : public ::testing::Test {
protected:
    Mark defaultMark_;
};

TEST_F(DeepRecursionTest_91, ConstructorSetsDepth_91) {
    DeepRecursion ex(42, defaultMark_, "test message");
    EXPECT_EQ(42, ex.depth());
}

TEST_F(DeepRecursionTest_91, DepthZero_91) {
    DeepRecursion ex(0, defaultMark_, "zero depth");
    EXPECT_EQ(0, ex.depth());
}

TEST_F(DeepRecursionTest_91, DepthNegative_91) {
    DeepRecursion ex(-1, defaultMark_, "negative depth");
    EXPECT_EQ(-1, ex.depth());
}

TEST_F(DeepRecursionTest_91, DepthLargeValue_91) {
    DeepRecursion ex(100000, defaultMark_, "large depth");
    EXPECT_EQ(100000, ex.depth());
}

TEST_F(DeepRecursionTest_91, DepthOne_91) {
    DeepRecursion ex(1, defaultMark_, "depth one");
    EXPECT_EQ(1, ex.depth());
}

TEST_F(DeepRecursionTest_91, IsParserException_91) {
    DeepRecursion ex(10, defaultMark_, "test");
    // DeepRecursion should be catchable as a ParserException
    try {
        throw ex;
    } catch (const ParserException& e) {
        // Successfully caught as ParserException
        SUCCEED();
    } catch (...) {
        FAIL() << "DeepRecursion should be catchable as ParserException";
    }
}

TEST_F(DeepRecursionTest_91, IsStdException_91) {
    DeepRecursion ex(10, defaultMark_, "test");
    try {
        throw ex;
    } catch (const std::exception& e) {
        SUCCEED();
    } catch (...) {
        FAIL() << "DeepRecursion should be catchable as std::exception";
    }
}

TEST_F(DeepRecursionTest_91, EmptyMessage_91) {
    DeepRecursion ex(5, defaultMark_, "");
    EXPECT_EQ(5, ex.depth());
}

TEST_F(DeepRecursionTest_91, CopyPreservesDepth_91) {
    DeepRecursion ex(77, defaultMark_, "copy test");
    DeepRecursion copy(ex);
    EXPECT_EQ(77, copy.depth());
}

TEST_F(DeepRecursionTest_91, DepthMaxInt_91) {
    DeepRecursion ex(std::numeric_limits<int>::max(), defaultMark_, "max int depth");
    EXPECT_EQ(std::numeric_limits<int>::max(), ex.depth());
}

TEST_F(DeepRecursionTest_91, DepthMinInt_91) {
    DeepRecursion ex(std::numeric_limits<int>::min(), defaultMark_, "min int depth");
    EXPECT_EQ(std::numeric_limits<int>::min(), ex.depth());
}

TEST_F(DeepRecursionTest_91, DepthIsConst_91) {
    const DeepRecursion ex(33, defaultMark_, "const test");
    EXPECT_EQ(33, ex.depth());
}

TEST_F(DeepRecursionTest_91, WithSpecificMark_91) {
    Mark mark;
    mark.pos = 10;
    mark.line = 5;
    mark.column = 3;
    DeepRecursion ex(20, mark, "specific mark");
    EXPECT_EQ(20, ex.depth());
}

TEST_F(DeepRecursionTest_91, WhatReturnsNonNull_91) {
    DeepRecursion ex(15, defaultMark_, "some message");
    EXPECT_NE(nullptr, ex.what());
}

}  // namespace
}  // namespace YAML
