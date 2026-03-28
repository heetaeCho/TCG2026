#include <gtest/gtest.h>
#include <memory>
#include "Function.h"

class IdentityFunctionTest_355 : public ::testing::Test {
protected:
    void SetUp() override {
        func = std::make_unique<IdentityFunction>();
    }

    std::unique_ptr<IdentityFunction> func;
};

TEST_F(IdentityFunctionTest_355, Constructor_CreatesValidObject_355) {
    IdentityFunction identityFunc;
    EXPECT_TRUE(identityFunc.isOk());
}

TEST_F(IdentityFunctionTest_355, IsOk_ReturnsTrue_355) {
    EXPECT_TRUE(func->isOk());
}

TEST_F(IdentityFunctionTest_355, GetType_ReturnsIdentityType_355) {
    Function::Type type = func->getType();
    EXPECT_EQ(type, Function::Type::Identity);
}

TEST_F(IdentityFunctionTest_355, Transform_SingleValue_355) {
    double in[1] = {0.5};
    double out[1] = {0.0};
    func->transform(in, out);
    EXPECT_DOUBLE_EQ(out[0], 0.5);
}

TEST_F(IdentityFunctionTest_355, Transform_ZeroValue_355) {
    double in[1] = {0.0};
    double out[1] = {-1.0};
    func->transform(in, out);
    EXPECT_DOUBLE_EQ(out[0], 0.0);
}

TEST_F(IdentityFunctionTest_355, Transform_OneValue_355) {
    double in[1] = {1.0};
    double out[1] = {0.0};
    func->transform(in, out);
    EXPECT_DOUBLE_EQ(out[0], 1.0);
}

TEST_F(IdentityFunctionTest_355, Transform_NegativeValue_355) {
    double in[1] = {-0.5};
    double out[1] = {0.0};
    func->transform(in, out);
    EXPECT_DOUBLE_EQ(out[0], -0.5);
}

TEST_F(IdentityFunctionTest_355, Transform_MultipleValues_355) {
    double in[4] = {0.1, 0.2, 0.3, 0.4};
    double out[4] = {0.0, 0.0, 0.0, 0.0};
    func->transform(in, out);
    EXPECT_DOUBLE_EQ(out[0], 0.1);
    EXPECT_DOUBLE_EQ(out[1], 0.2);
    EXPECT_DOUBLE_EQ(out[2], 0.3);
    EXPECT_DOUBLE_EQ(out[3], 0.4);
}

TEST_F(IdentityFunctionTest_355, Transform_LargeValue_355) {
    double in[1] = {1e10};
    double out[1] = {0.0};
    func->transform(in, out);
    EXPECT_DOUBLE_EQ(out[0], 1e10);
}

TEST_F(IdentityFunctionTest_355, Transform_VerySmallValue_355) {
    double in[1] = {1e-15};
    double out[1] = {0.0};
    func->transform(in, out);
    EXPECT_DOUBLE_EQ(out[0], 1e-15);
}

TEST_F(IdentityFunctionTest_355, Copy_ReturnsValidCopy_355) {
    auto copied = func->copy();
    ASSERT_NE(copied, nullptr);
    EXPECT_TRUE(copied->isOk());
}

TEST_F(IdentityFunctionTest_355, Copy_ReturnsSameType_355) {
    auto copied = func->copy();
    ASSERT_NE(copied, nullptr);
    EXPECT_EQ(copied->getType(), Function::Type::Identity);
}

TEST_F(IdentityFunctionTest_355, Copy_IndependentOfOriginal_355) {
    auto copied = func->copy();
    ASSERT_NE(copied, nullptr);

    double in[1] = {0.75};
    double out1[1] = {0.0};
    double out2[1] = {0.0};

    func->transform(in, out1);
    copied->transform(in, out2);

    EXPECT_DOUBLE_EQ(out1[0], out2[0]);
}

TEST_F(IdentityFunctionTest_355, Copy_MultipleCopies_355) {
    auto copy1 = func->copy();
    auto copy2 = func->copy();
    ASSERT_NE(copy1, nullptr);
    ASSERT_NE(copy2, nullptr);
    EXPECT_TRUE(copy1->isOk());
    EXPECT_TRUE(copy2->isOk());
    EXPECT_NE(copy1.get(), copy2.get());
}

TEST_F(IdentityFunctionTest_355, Transform_BoundaryValues_355) {
    double in[2] = {0.0, 1.0};
    double out[2] = {-1.0, -1.0};
    func->transform(in, out);
    EXPECT_DOUBLE_EQ(out[0], 0.0);
    EXPECT_DOUBLE_EQ(out[1], 1.0);
}

TEST_F(IdentityFunctionTest_355, Transform_PreservesExactValues_355) {
    double in[3] = {0.123456789012345, 0.987654321098765, 0.555555555555555};
    double out[3] = {0.0, 0.0, 0.0};
    func->transform(in, out);
    EXPECT_DOUBLE_EQ(out[0], in[0]);
    EXPECT_DOUBLE_EQ(out[1], in[1]);
    EXPECT_DOUBLE_EQ(out[2], in[2]);
}
