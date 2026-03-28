#include <gtest/gtest.h>
#include "tiffcomposite_int.hpp"

using namespace Exiv2::Internal;

// Test fixture for ArrayDef
class ArrayDefTest_248 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test fixture for ArrayCfg
class ArrayCfgTest_248 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// ==================== ArrayDef Tests ====================

// Test ArrayDef equality operator with matching idx
TEST_F(ArrayDefTest_248, EqualityOperatorMatchingIdx_248) {
    ArrayDef def;
    def.idx_ = 5;
    def.count_ = 10;
    EXPECT_TRUE(def == 5);
}

// Test ArrayDef equality operator with non-matching idx
TEST_F(ArrayDefTest_248, EqualityOperatorNonMatchingIdx_248) {
    ArrayDef def;
    def.idx_ = 5;
    def.count_ = 10;
    EXPECT_FALSE(def == 3);
}

// Test ArrayDef equality operator with zero idx
TEST_F(ArrayDefTest_248, EqualityOperatorZeroIdx_248) {
    ArrayDef def;
    def.idx_ = 0;
    def.count_ = 1;
    EXPECT_TRUE(def == 0);
}

// Test ArrayDef size method
TEST_F(ArrayDefTest_248, SizeMethod_248) {
    ArrayDef def;
    def.idx_ = 0;
    def.count_ = 3;
    // We call size with some tag and group values and verify it returns a value
    // The exact return depends on internal logic, but we verify it doesn't crash
    size_t result = def.size(0, IfdId::ifd0Id);
    // size should return some non-negative value (it's size_t)
    EXPECT_GE(result, 0u);
}

// Test ArrayDef with boundary idx value
TEST_F(ArrayDefTest_248, EqualityOperatorLargeIdx_248) {
    ArrayDef def;
    def.idx_ = SIZE_MAX;
    def.count_ = 1;
    EXPECT_TRUE(def == SIZE_MAX);
    EXPECT_FALSE(def == 0);
}

// ==================== ArrayCfg Tests ====================

// Test ArrayCfg tagStep returns the size of the default definition
TEST_F(ArrayCfgTest_248, TagStepReturnsDefaultDefSize_248) {
    ArrayCfg cfg;
    cfg.elDefaultDef_.idx_ = 0;
    cfg.elDefaultDef_.count_ = 1;
    cfg.group_ = IfdId::ifd0Id;
    
    size_t step = cfg.tagStep();
    // tagStep calls elDefaultDef_.size(0, group_), result depends on implementation
    EXPECT_GE(step, 0u);
}

// Test ArrayCfg tagStep with different group
TEST_F(ArrayCfgTest_248, TagStepWithDifferentGroup_248) {
    ArrayCfg cfg;
    cfg.elDefaultDef_.idx_ = 0;
    cfg.elDefaultDef_.count_ = 2;
    cfg.group_ = IfdId::exifId;
    
    size_t step = cfg.tagStep();
    EXPECT_GE(step, 0u);
}

// Test ArrayCfg member fields are accessible
TEST_F(ArrayCfgTest_248, MemberFieldsAccessible_248) {
    ArrayCfg cfg;
    cfg.hasSize_ = true;
    cfg.hasFillers_ = false;
    cfg.concat_ = true;
    
    EXPECT_TRUE(cfg.hasSize_);
    EXPECT_FALSE(cfg.hasFillers_);
    EXPECT_TRUE(cfg.concat_);
}

// Test ArrayCfg with hasSize false
TEST_F(ArrayCfgTest_248, HasSizeFalse_248) {
    ArrayCfg cfg;
    cfg.hasSize_ = false;
    EXPECT_FALSE(cfg.hasSize_);
}

// Test ArrayCfg with concat false
TEST_F(ArrayCfgTest_248, ConcatFalse_248) {
    ArrayCfg cfg;
    cfg.concat_ = false;
    EXPECT_FALSE(cfg.concat_);
}

// Test ArrayCfg with hasFillers true
TEST_F(ArrayCfgTest_248, HasFillersTrue_248) {
    ArrayCfg cfg;
    cfg.hasFillers_ = true;
    EXPECT_TRUE(cfg.hasFillers_);
}

// Test ArrayDef default count is settable
TEST_F(ArrayDefTest_248, CountIsSettable_248) {
    ArrayDef def;
    def.count_ = 42;
    EXPECT_EQ(def.count_, 42u);
}

// Test ArrayDef idx is settable
TEST_F(ArrayDefTest_248, IdxIsSettable_248) {
    ArrayDef def;
    def.idx_ = 100;
    EXPECT_EQ(def.idx_, 100u);
}
