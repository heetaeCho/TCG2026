// =================================================================================================
// TEST_ID 2094
// Unit tests for static EndElementHandler in ExpatAdapter.cpp
// =================================================================================================

#include <gtest/gtest.h>

#include <cstddef>
#include <type_traits>

// Include the .cpp directly so the TU can see the file-static EndElementHandler.
#include "xmpsdk/src/ExpatAdapter.cpp"

// -------------------------------------------------------------------------------------------------

class ExpatAdapterTest_2094 : public ::testing::Test {
protected:
  ExpatAdapter adapter;
};

// Normal operation: pop_back removes exactly one entry.
TEST_F(ExpatAdapterTest_2094, PopsExactlyOneNodeFromParseStack_2094) {
  using StackT = decltype(adapter.parseStack);
  using ValueT = typename StackT::value_type;

  adapter.parseStack.clear();
  adapter.parseStack.push_back(ValueT{});  // first
  adapter.parseStack.push_back(ValueT{});  // second
  adapter.parseStack.push_back(ValueT{});  // third

  const size_t before = adapter.parseStack.size();
  ASSERT_GE(before, 1u);

  EndElementHandler(&adapter, "AnyName");

  EXPECT_EQ(adapter.parseStack.size(), before - 1);
}

// Boundary: stack size 1 -> becomes empty.
TEST_F(ExpatAdapterTest_2094, PopsLastNodeWhenStackHasOneElement_2094) {
  using StackT = decltype(adapter.parseStack);
  using ValueT = typename StackT::value_type;

  adapter.parseStack.clear();
  adapter.parseStack.push_back(ValueT{});

  ASSERT_EQ(adapter.parseStack.size(), 1u);

  EndElementHandler(&adapter, "Element");

  EXPECT_TRUE(adapter.parseStack.empty());
}

// Name parameter is ignored: the same stack behavior regardless of the name.
TEST_F(ExpatAdapterTest_2094, NameIsIgnoredForStackBehavior_2094) {
  using StackT = decltype(adapter.parseStack);
  using ValueT = typename StackT::value_type;

  adapter.parseStack.clear();
  adapter.parseStack.push_back(ValueT{});
  adapter.parseStack.push_back(ValueT{});

  const size_t before = adapter.parseStack.size();

  EndElementHandler(&adapter, "A");
  EXPECT_EQ(adapter.parseStack.size(), before - 1);

  // Rebuild and try a different name.
  adapter.parseStack.clear();
  adapter.parseStack.push_back(ValueT{});
  adapter.parseStack.push_back(ValueT{});

  EndElementHandler(&adapter, "SomeOtherName");
  EXPECT_EQ(adapter.parseStack.size(), before - 1);
}

// Observable non-stack state in the base adapter remains unchanged by EndElementHandler.
TEST_F(ExpatAdapterTest_2094, DoesNotChangePublicBaseStateExceptParseStack_2094) {
  using StackT = decltype(adapter.parseStack);
  using ValueT = typename StackT::value_type;

  // Set some public fields from XMLParserAdapter (visible through the interface).
  adapter.rootCount = 7;
  adapter.charEncoding = static_cast<XMP_OptionBits>(123);
  adapter.pendingCount = 9;

  adapter.parseStack.clear();
  adapter.parseStack.push_back(ValueT{});
  adapter.parseStack.push_back(ValueT{});

  EndElementHandler(&adapter, "X");

  EXPECT_EQ(adapter.rootCount, 7u);
  EXPECT_EQ(adapter.charEncoding, static_cast<XMP_OptionBits>(123));
  EXPECT_EQ(adapter.pendingCount, 9u);
  EXPECT_EQ(adapter.parseStack.size(), 1u);
}