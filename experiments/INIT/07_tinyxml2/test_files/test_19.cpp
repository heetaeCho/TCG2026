// File: ./TestProjects/tinyxml2/tests/mempoolt_itemsize_test_19.cpp

#include <gtest/gtest.h>

#include "TestProjects/tinyxml2/tinyxml2.h"

namespace {

using namespace tinyxml2;

// These tests focus ONLY on observable behavior of the public interface:
// MemPoolT<ITEM_SIZE>::ItemSize() const.

TEST(MemPoolTTest_19, ItemSizeReturnsTemplateParameter_Small_19)
{
    MemPoolT<1> pool;
    EXPECT_EQ(pool.ItemSize(), static_cast<size_t>(1));
}

TEST(MemPoolTTest_19, ItemSizeReturnsTemplateParameter_Typical_19)
{
    MemPoolT<16> pool;
    EXPECT_EQ(pool.ItemSize(), static_cast<size_t>(16));
}

TEST(MemPoolTTest_19, ItemSizeReturnsTemplateParameter_Larger_19)
{
    MemPoolT<1024> pool;
    EXPECT_EQ(pool.ItemSize(), static_cast<size_t>(1024));
}

TEST(MemPoolTTest_19, ItemSizeCanBeCalledOnConstObject_19)
{
    const MemPoolT<8> pool;
    EXPECT_EQ(pool.ItemSize(), static_cast<size_t>(8));
}

TEST(MemPoolTTest_19, ItemSizeThroughBasePointerUsesOverride_19)
{
    MemPoolT<32> derived;
    MemPool* base = &derived;  // verify virtual override is used through base
    ASSERT_NE(base, nullptr);
    EXPECT_EQ(base->ItemSize(), static_cast<size_t>(32));
}

TEST(MemPoolTTest_19, ItemSizeBoundary_ZeroSize_19)
{
    // Boundary condition: ITEM_SIZE == 0 (valid template argument for size_t).
    MemPoolT<0> pool;
    EXPECT_EQ(pool.ItemSize(), static_cast<size_t>(0));
}

}  // namespace
