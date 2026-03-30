// =================================================================================================
// TEST_ID: 2099
// Unit tests for static helper AddNodeOffspring in XMPIterator.cpp
// =================================================================================================

#include <gtest/gtest.h>

#include <memory>
#include <vector>

// Pull in the real SDK headers/types used by XMPIterator.cpp.
#include "XMP_Const.h"
#include "XMPIterator.hpp"
#include "XMPCore_Impl.hpp"

// NOTE: AddNodeOffspring is a file-local static in XMPIterator.cpp.
// To test it without re-implementing logic, include the .cpp so the symbol is in this TU.
#include "XMPIterator.cpp"

namespace {

class XMPIterator_AddNodeOffspringTest_2099 : public ::testing::Test {
protected:
  // Helper to create an XMP_Node and keep ownership locally.
  XMP_Node* MakeNode(XMP_Node* parent, const char* name, XMP_OptionBits options) {
    owned_.push_back(std::make_unique<XMP_Node>(parent, name, options));
    return owned_.back().get();
  }

  // Overload for name+value (not required by AddNodeOffspring, but handy in case the real type requires it elsewhere).
  XMP_Node* MakeNode(XMP_Node* parent, const char* name, const char* value, XMP_OptionBits options) {
    owned_.push_back(std::make_unique<XMP_Node>(parent, name, value, options));
    return owned_.back().get();
  }

private:
  std::vector<std::unique_ptr<XMP_Node>> owned_;
};

TEST_F(XMPIterator_AddNodeOffspringTest_2099, AddsQualifiersWhenPresentAndNotOmitted_2099) {
  IterInfo info;
  info.options = 0;  // qualifiers NOT omitted

  IterNode iterParent(/*options*/ 0, /*fullPath*/ "ns:Prop", /*leafOffset*/ 0);

  // xmpParent has qualifiers.
  XMP_Node* xmpParent = MakeNode(nullptr, "Prop", /*options*/ kXMP_PropHasQualifiers);
  XMP_Node* q1 = MakeNode(xmpParent, "xml:lang", /*options*/ kXMP_PropIsQualifier);
  XMP_Node* q2 = MakeNode(xmpParent, "rdf:type", /*options*/ kXMP_PropIsQualifier);

  xmpParent->qualifiers.push_back(q1);
  xmpParent->qualifiers.push_back(q2);

  AddNodeOffspring(info, iterParent, xmpParent);

  ASSERT_EQ(iterParent.qualifiers.size(), 2u);

  // Observable path formatting: "Prop/?Qual"
  EXPECT_EQ(iterParent.qualifiers[0].fullPath, "ns:Prop/?xml:lang");
  EXPECT_EQ(iterParent.qualifiers[1].fullPath, "ns:Prop/?rdf:type");

  // Observable leafOffset passed into IterNode for qualifiers.
  const size_t expectedLeafOffset = std::string("ns:Prop").size() + 2;  // "/?" added
  EXPECT_EQ(iterParent.qualifiers[0].leafOffset, expectedLeafOffset);
  EXPECT_EQ(iterParent.qualifiers[1].leafOffset, expectedLeafOffset);
}

TEST_F(XMPIterator_AddNodeOffspringTest_2099, OmitsQualifiersWhenOptionSet_2099) {
  IterInfo info;
  info.options = kXMP_IterOmitQualifiers;

  IterNode iterParent(/*options*/ 0, /*fullPath*/ "ns:Prop", /*leafOffset*/ 0);

  XMP_Node* xmpParent = MakeNode(nullptr, "Prop", /*options*/ kXMP_PropHasQualifiers);
  XMP_Node* q1 = MakeNode(xmpParent, "xml:lang", /*options*/ kXMP_PropIsQualifier);
  xmpParent->qualifiers.push_back(q1);

  AddNodeOffspring(info, iterParent, xmpParent);

  EXPECT_TRUE(iterParent.qualifiers.empty());
}

TEST_F(XMPIterator_AddNodeOffspringTest_2099, AddsStructChildrenWithSlashSeparator_2099) {
  IterInfo info;
  info.options = 0;

  IterNode iterParent(/*options*/ 0, /*fullPath*/ "ns:Struct", /*leafOffset*/ 0);

  // Parent must be composite; make it a struct.
  XMP_Node* xmpParent = MakeNode(nullptr, "Struct", /*options*/ kXMP_PropValueIsStruct);

  XMP_Node* c1 = MakeNode(xmpParent, "FieldA", /*options*/ 0);
  XMP_Node* c2 = MakeNode(xmpParent, "FieldB", /*options*/ 0);
  xmpParent->children.push_back(c1);
  xmpParent->children.push_back(c2);

  AddNodeOffspring(info, iterParent, xmpParent);

  ASSERT_EQ(iterParent.children.size(), 2u);

  EXPECT_EQ(iterParent.children[0].fullPath, "ns:Struct/FieldA");
  EXPECT_EQ(iterParent.children[1].fullPath, "ns:Struct/FieldB");

  // Observable leafOffset passed into IterNode after adding '/' for struct.
  const size_t expectedLeafOffset = std::string("ns:Struct").size() + 1;
  EXPECT_EQ(iterParent.children[0].leafOffset, expectedLeafOffset);
  EXPECT_EQ(iterParent.children[1].leafOffset, expectedLeafOffset);
}

TEST_F(XMPIterator_AddNodeOffspringTest_2099, AddsArrayChildrenAsOneBasedXPathIndices_2099) {
  IterInfo info;
  info.options = 0;

  IterNode iterParent(/*options*/ 0, /*fullPath*/ "ns:Array", /*leafOffset*/ 0);

  // Parent must be composite; make it an array.
  XMP_Node* xmpParent = MakeNode(nullptr, "Array", /*options*/ kXMP_PropValueIsArray);

  // Children names should be ignored for array paths; still need nodes present.
  XMP_Node* c1 = MakeNode(xmpParent, "Ignored1", /*options*/ 0);
  XMP_Node* c2 = MakeNode(xmpParent, "Ignored2", /*options*/ 0);
  XMP_Node* c3 = MakeNode(xmpParent, "Ignored3", /*options*/ 0);
  xmpParent->children.push_back(c1);
  xmpParent->children.push_back(c2);
  xmpParent->children.push_back(c3);

  AddNodeOffspring(info, iterParent, xmpParent);

  ASSERT_EQ(iterParent.children.size(), 3u);

  EXPECT_EQ(iterParent.children[0].fullPath, "ns:Array[1]");
  EXPECT_EQ(iterParent.children[1].fullPath, "ns:Array[2]");
  EXPECT_EQ(iterParent.children[2].fullPath, "ns:Array[3]");

  // For arrays, the leafOffset used for children should match iterParent.fullPath.size()
  // (no '/' inserted for arrays in this helper).
  const size_t expectedLeafOffset = std::string("ns:Array").size();
  EXPECT_EQ(iterParent.children[0].leafOffset, expectedLeafOffset);
  EXPECT_EQ(iterParent.children[1].leafOffset, expectedLeafOffset);
  EXPECT_EQ(iterParent.children[2].leafOffset, expectedLeafOffset);
}

TEST_F(XMPIterator_AddNodeOffspringTest_2099, DoesNothingWhenNoQualifiersAndNoChildren_2099) {
  IterInfo info;
  info.options = 0;

  IterNode iterParent(/*options*/ 0, /*fullPath*/ "ns:Empty", /*leafOffset*/ 0);

  XMP_Node* xmpParent = MakeNode(nullptr, "Empty", /*options*/ 0);
  ASSERT_TRUE(xmpParent->qualifiers.empty());
  ASSERT_TRUE(xmpParent->children.empty());

  AddNodeOffspring(info, iterParent, xmpParent);

  EXPECT_TRUE(iterParent.qualifiers.empty());
  EXPECT_TRUE(iterParent.children.empty());
}

}  // namespace