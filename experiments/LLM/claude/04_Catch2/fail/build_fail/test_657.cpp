#include "gtest/gtest.h"
#include "catch2/internal/catch_clara.hpp"

using namespace Catch::Clara;
using namespace Catch::Clara::Detail;

class BoundFlagRefTest_657 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test that setFlag with true sets the referenced bool to true
TEST_F(BoundFlagRefTest_657, SetFlagTrue_SetsRefToTrue_657) {
    bool flag = false;
    BoundFlagRef boundRef(flag);
    
    auto result = boundRef.setFlag(true);
    
    EXPECT_TRUE(flag);
}

// Test that setFlag with false sets the referenced bool to false
TEST_F(BoundFlagRefTest_657, SetFlagFalse_SetsRefToFalse_657) {
    bool flag = true;
    BoundFlagRef boundRef(flag);
    
    auto result = boundRef.setFlag(false);
    
    EXPECT_FALSE(flag);
}

// Test that setFlag returns an ok result
TEST_F(BoundFlagRefTest_657, SetFlag_ReturnsOkResult_657) {
    bool flag = false;
    BoundFlagRef boundRef(flag);
    
    auto result = boundRef.setFlag(true);
    
    EXPECT_TRUE(static_cast<bool>(result));
}

// Test that setFlag returns a result with Matched type
TEST_F(BoundFlagRefTest_657, SetFlag_ReturnsMatchedType_657) {
    bool flag = false;
    BoundFlagRef boundRef(flag);
    
    auto result = boundRef.setFlag(true);
    
    EXPECT_EQ(result.type(), ResultBase::Ok);
}

// Test that setFlag with true when ref is already true
TEST_F(BoundFlagRefTest_657, SetFlagTrue_WhenAlreadyTrue_657) {
    bool flag = true;
    BoundFlagRef boundRef(flag);
    
    auto result = boundRef.setFlag(true);
    
    EXPECT_TRUE(flag);
    EXPECT_TRUE(static_cast<bool>(result));
}

// Test that setFlag with false when ref is already false
TEST_F(BoundFlagRefTest_657, SetFlagFalse_WhenAlreadyFalse_657) {
    bool flag = false;
    BoundFlagRef boundRef(flag);
    
    auto result = boundRef.setFlag(false);
    
    EXPECT_FALSE(flag);
    EXPECT_TRUE(static_cast<bool>(result));
}

// Test that the error message is empty on successful setFlag
TEST_F(BoundFlagRefTest_657, SetFlag_ErrorMessageIsEmpty_657) {
    bool flag = false;
    BoundFlagRef boundRef(flag);
    
    auto result = boundRef.setFlag(true);
    
    EXPECT_TRUE(result.errorMessage().empty());
}

// Test that m_ref correctly references the original variable
TEST_F(BoundFlagRefTest_657, Constructor_ReferencesOriginalVariable_657) {
    bool flag = false;
    BoundFlagRef boundRef(flag);
    
    EXPECT_EQ(&boundRef.m_ref, &flag);
}

// Test multiple calls to setFlag toggle the value correctly
TEST_F(BoundFlagRefTest_657, SetFlag_MultipleCalls_TogglesCorrectly_657) {
    bool flag = false;
    BoundFlagRef boundRef(flag);
    
    boundRef.setFlag(true);
    EXPECT_TRUE(flag);
    
    boundRef.setFlag(false);
    EXPECT_FALSE(flag);
    
    boundRef.setFlag(true);
    EXPECT_TRUE(flag);
}

// Test that setFlag returns ok result for both true and false
TEST_F(BoundFlagRefTest_657, SetFlag_BothValues_ReturnOk_657) {
    bool flag = false;
    BoundFlagRef boundRef(flag);
    
    auto result1 = boundRef.setFlag(true);
    EXPECT_TRUE(static_cast<bool>(result1));
    
    auto result2 = boundRef.setFlag(false);
    EXPECT_TRUE(static_cast<bool>(result2));
}
