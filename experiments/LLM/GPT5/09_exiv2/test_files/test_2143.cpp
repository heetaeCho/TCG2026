// =================================================================================================
// TEST_ID: 2143
// Unit tests for static CompareNodeValues in ./TestProjects/exiv2/xmpsdk/src/XMPMeta.cpp
// =================================================================================================

#include <gtest/gtest.h>

#include <string>

// Pull in core XMP types (XMP_Node, XMP_OptionBits, XMP_PropIsSimple, option masks).
#include "TestProjects/exiv2/xmpsdk/src/XMPCore_Impl.hpp"
#include "TestProjects/exiv2/xmpsdk/include/XMP_Const.h"

// Include the production .cpp so the TU can see the internal-linkage function.
// IMPORTANT: This assumes your test target is not also linking another compiled XMPMeta.cpp object.
#include "TestProjects/exiv2/xmpsdk/src/XMPMeta.cpp"

namespace {

class CompareNodeValuesTest_2143 : public ::testing::Test {
 protected:
  static XMP_Node MakeNode(const char* name,
                          const char* value,
                          XMP_OptionBits options) {
    // Parent is irrelevant for CompareNodeValues.
    return XMP_Node(/*_parent=*/nullptr, /*_name=*/name, /*_value=*/value, /*_options=*/options);
  }
};

TEST_F(CompareNodeValuesTest_2143, SimpleVsSimple_OrdersByValueLexicographically_2143) {
  XMP_Node left = MakeNode("n1", "apple", 0);
  XMP_Node right = MakeNode("n2", "banana", 0);

  EXPECT_TRUE(CompareNodeValues(&left, &right));
  EXPECT_FALSE(CompareNodeValues(&right, &left));
}

TEST_F(CompareNodeValuesTest_2143, SimpleVsSimple_EqualValues_IsNotLess_2143) {
  XMP_Node left = MakeNode("n1", "same", 0);
  XMP_Node right = MakeNode("n2", "same", 0);

  EXPECT_FALSE(CompareNodeValues(&left, &right));
  EXPECT_FALSE(CompareNodeValues(&right, &left));
}

TEST_F(CompareNodeValuesTest_2143, CompositeVsComposite_OrdersByCompositeMaskValue_2143) {
  // Use two different composite forms (struct vs array) to force ordering by masked options.
  XMP_Node left = MakeNode("n1", "zzz", kXMP_PropValueIsStruct);
  XMP_Node right = MakeNode("n2", "aaa", kXMP_PropValueIsArray);

  const bool lr = CompareNodeValues(&left, &right);
  const bool rl = CompareNodeValues(&right, &left);

  // Strict weak ordering: if one is less, the reverse must be false.
  EXPECT_NE(lr, rl);
}

TEST_F(CompareNodeValuesTest_2143, CompositeVsComposite_SameCompositeMask_IsNotLess_2143) {
  // Same composite bits (array form ordered), even if values differ, "less" should be false.
  const XMP_OptionBits opts = kXMP_PropValueIsArray | kXMP_PropArrayIsOrdered;

  XMP_Node left = MakeNode("n1", "a", opts);
  XMP_Node right = MakeNode("n2", "b", opts);

  EXPECT_FALSE(CompareNodeValues(&left, &right));
  EXPECT_FALSE(CompareNodeValues(&right, &left));
}

TEST_F(CompareNodeValuesTest_2143, SimpleVsComposite_OrdersByCompositeMaskValue_2143) {
  XMP_Node simple = MakeNode("s", "zzz", 0);
  XMP_Node composite = MakeNode("c", "aaa", kXMP_PropValueIsStruct);

  const bool sc = CompareNodeValues(&simple, &composite);
  const bool cs = CompareNodeValues(&composite, &simple);

  // Must be a strict ordering: exactly one direction is true.
  EXPECT_NE(sc, cs);
}

TEST_F(CompareNodeValuesTest_2143, Boundary_EmptyStringValues_ForSimpleNodes_2143) {
  XMP_Node empty = MakeNode("e", "", 0);
  XMP_Node nonEmpty = MakeNode("n", "x", 0);

  EXPECT_TRUE(CompareNodeValues(&empty, &nonEmpty));
  EXPECT_FALSE(CompareNodeValues(&nonEmpty, &empty));
}

TEST_F(CompareNodeValuesTest_2143, Boundary_VeryLongValues_ForSimpleNodes_2143) {
  std::string longA(4096, 'a');
  std::string longB(4096, 'b');

  XMP_Node left = MakeNode("n1", longA.c_str(), 0);
  XMP_Node right = MakeNode("n2", longB.c_str(), 0);

  EXPECT_TRUE(CompareNodeValues(&left, &right));
  EXPECT_FALSE(CompareNodeValues(&right, &left));
}

}  // namespace