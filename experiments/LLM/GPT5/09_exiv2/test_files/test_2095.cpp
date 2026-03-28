// =================================================================================================
// Copyright Adobe
// SPDX-License-Identifier: BSD-3-Clause
// =================================================================================================
//
// Unit tests for ExpatAdapter CharacterData handling (via public ParseBuffer interface).
// File under test: ./TestProjects/exiv2/xmpsdk/src/ExpatAdapter.cpp
//
// TEST_ID: 2095
// =================================================================================================

#include <gtest/gtest.h>

#include <cstring>
#include <string>

// ExpatAdapter is expected to be part of the xmpsdk sources in this repo.
// Adjust include paths if your build system requires different paths.
#include "ExpatAdapter.hpp"
#include "XMLParserAdapter.hpp"

namespace {

using namespace std;

class ExpatAdapterCharacterDataHandlerTest_2095 : public ::testing::Test {
protected:
  // Helper: find the first element child of the root tree node.
  static XML_Node* FindFirstElementUnderRoot(XMLParserAdapter& adapter) {
    // adapter.tree is kRootNode; element children should appear in tree.content.
    for (XML_Node* child : adapter.tree.content) {
      if (child != nullptr && child->kind == kElemNode) return child;
    }
    return nullptr;
  }

  // Helper: collect all direct CDATA children of an element node.
  static std::vector<XML_Node*> CollectDirectCDataChildren(XML_Node* elem) {
    std::vector<XML_Node*> out;
    if (elem == nullptr) return out;
    for (XML_Node* child : elem->content) {
      if (child != nullptr && child->kind == kCDataNode) out.push_back(child);
    }
    return out;
  }

  // Helper: concatenate the value fields of direct CDATA children.
  static std::string ConcatDirectCDataValues(XML_Node* elem) {
    std::string out;
    for (XML_Node* n : CollectDirectCDataChildren(elem)) {
      out += n->value;
    }
    return out;
  }
};

TEST_F(ExpatAdapterCharacterDataHandlerTest_2095, ParsesCharacterDataIntoCDataNode_2095) {
  ExpatAdapter adapter;

  const char* xml = "<root>abc</root>";
  adapter.ParseBuffer(xml, std::strlen(xml), /*last*/ true);

  XML_Node* rootElem = FindFirstElementUnderRoot(adapter);
  ASSERT_NE(rootElem, nullptr);
  EXPECT_EQ(rootElem->name, "root");

  auto cdataNodes = CollectDirectCDataChildren(rootElem);
  ASSERT_GE(cdataNodes.size(), 1u) << "Expected at least one CDATA node under <root>.";

  // Observable behavior: character data should appear as CDATA node(s) with the same content.
  EXPECT_EQ(ConcatDirectCDataValues(rootElem), "abc");
}

TEST_F(ExpatAdapterCharacterDataHandlerTest_2095, ParsesWhitespaceAsCharacterData_2095) {
  ExpatAdapter adapter;

  const char* xml = "<root>  \n\t </root>";
  adapter.ParseBuffer(xml, std::strlen(xml), /*last*/ true);

  XML_Node* rootElem = FindFirstElementUnderRoot(adapter);
  ASSERT_NE(rootElem, nullptr);
  EXPECT_EQ(rootElem->name, "root");

  auto cdataNodes = CollectDirectCDataChildren(rootElem);
  ASSERT_GE(cdataNodes.size(), 1u) << "Expected whitespace character data to be represented.";

  // The exact segmentation is parser-dependent; we assert the concatenation matches the literal.
  EXPECT_EQ(ConcatDirectCDataValues(rootElem), "  \n\t ");
}

TEST_F(ExpatAdapterCharacterDataHandlerTest_2095, SplittingInputAcrossBuffersPreservesText_2095) {
  ExpatAdapter adapter;

  // Feed the same logical XML in multiple chunks to exercise repeated character-data events.
  const std::string part1 = "<root>he";
  const std::string part2 = "llo</root>";

  adapter.ParseBuffer(part1.data(), part1.size(), /*last*/ false);
  adapter.ParseBuffer(part2.data(), part2.size(), /*last*/ true);

  XML_Node* rootElem = FindFirstElementUnderRoot(adapter);
  ASSERT_NE(rootElem, nullptr);
  EXPECT_EQ(rootElem->name, "root");

  auto cdataNodes = CollectDirectCDataChildren(rootElem);
  ASSERT_GE(cdataNodes.size(), 1u);

  // Observable behavior: regardless of event segmentation, the resulting content should match.
  EXPECT_EQ(ConcatDirectCDataValues(rootElem), "hello");
}

TEST_F(ExpatAdapterCharacterDataHandlerTest_2095, MultipleCharacterDataRegionsAppearInOrder_2095) {
  ExpatAdapter adapter;

  // Two separate character-data regions due to nested element boundaries.
  const char* xml = "<root>a<b/>c</root>";
  adapter.ParseBuffer(xml, std::strlen(xml), /*last*/ true);

  XML_Node* rootElem = FindFirstElementUnderRoot(adapter);
  ASSERT_NE(rootElem, nullptr);
  EXPECT_EQ(rootElem->name, "root");

  // We only validate direct CDATA children (text nodes adjacent to <b/> are direct children of <root>).
  auto cdataNodes = CollectDirectCDataChildren(rootElem);
  ASSERT_GE(cdataNodes.size(), 2u) << "Expected at least 2 CDATA nodes for 'a' and 'c' regions.";

  // Order should be preserved in content vector: "a" then "c" when concatenated (ignoring <b/>).
  EXPECT_EQ(ConcatDirectCDataValues(rootElem), "ac");
}

}  // namespace