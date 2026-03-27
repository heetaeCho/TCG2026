// =================================================================================================
// TestProjects/exiv2/xmpsdk/src/ExpatAdapter_2096_test.cpp
// =================================================================================================

#include <gtest/gtest.h>

#include <string>
#include <vector>

#include "XMLParserAdapter.hpp"
#include "ExpatAdapter.hpp" // Expected to exist in the codebase under xmpsdk/src

namespace {

using namespace std;

static void ParseAll(Exiv2::XMPToolkit::ExpatAdapter& adapter, const std::string& xml) {
  ASSERT_NO_THROW(adapter.ParseBuffer(xml.data(), xml.size(), /*last*/ true));
}

static void CollectAllNodes(Exiv2::XMPToolkit::XML_Node* node,
                            std::vector<Exiv2::XMPToolkit::XML_Node*>& out) {
  if (node == nullptr) return;
  out.push_back(node);
  for (auto* a : node->attrs) {
    CollectAllNodes(a, out);
  }
  for (auto* c : node->content) {
    CollectAllNodes(c, out);
  }
}

static std::vector<Exiv2::XMPToolkit::XML_Node*> FindPINodesByName(
    Exiv2::XMPToolkit::XML_Node& root, const std::string& name) {
  std::vector<Exiv2::XMPToolkit::XML_Node*> all;
  CollectAllNodes(&root, all);

  std::vector<Exiv2::XMPToolkit::XML_Node*> matches;
  for (auto* n : all) {
    if (n == nullptr) continue;
    if (n->kind == Exiv2::XMPToolkit::kPINode && n->name == name) {
      matches.push_back(n);
    }
  }
  return matches;
}

static Exiv2::XMPToolkit::XML_Node* FindFirstElementByName(Exiv2::XMPToolkit::XML_Node& root,
                                                          const std::string& name) {
  std::vector<Exiv2::XMPToolkit::XML_Node*> all;
  CollectAllNodes(&root, all);
  for (auto* n : all) {
    if (n == nullptr) continue;
    if (n->kind == Exiv2::XMPToolkit::kElemNode && n->name == name) return n;
  }
  return nullptr;
}

}  // namespace

// -------------------------------------------------------------------------------------------------
// TEST_ID 2096
// -------------------------------------------------------------------------------------------------

TEST(ExpatAdapterTest_2096, XpacketPIAtTopLevelCreatesPINodes_2096) {
  Exiv2::XMPToolkit::ExpatAdapter adapter;

  // Two xpacket processing instructions around a minimal root element.
  const std::string xml =
      "<?xpacket begin=\"\xEF\xBB\xBF\" id=\"W5M0MpCehiHzreSzNTczkc9d\"?>"
      "<root/>"
      "<?xpacket end=\"w\"?>";

  ParseAll(adapter, xml);

  auto pi = FindPINodesByName(adapter.tree, "xpacket");
  ASSERT_EQ(pi.size(), 2U);

  EXPECT_EQ(pi[0]->kind, Exiv2::XMPToolkit::kPINode);
  EXPECT_EQ(pi[0]->name, "xpacket");
  EXPECT_FALSE(pi[0]->value.empty());  // Data should be present for the first PI.

  EXPECT_EQ(pi[1]->kind, Exiv2::XMPToolkit::kPINode);
  EXPECT_EQ(pi[1]->name, "xpacket");
  EXPECT_FALSE(pi[1]->value.empty());  // Data should be present for the second PI.
}

TEST(ExpatAdapterTest_2096, NonXpacketPIIsIgnored_2096) {
  Exiv2::XMPToolkit::ExpatAdapter adapter;

  const std::string xml =
      "<?foo something?>"
      "<root/>"
      "<?bar other?>";

  ParseAll(adapter, xml);

  // The handler explicitly ignores all PI targets except "xpacket".
  auto xpacket = FindPINodesByName(adapter.tree, "xpacket");
  EXPECT_TRUE(xpacket.empty());

  // Also ensure we didn't accidentally create PI nodes for foo/bar.
  auto foo = FindPINodesByName(adapter.tree, "foo");
  auto bar = FindPINodesByName(adapter.tree, "bar");
  EXPECT_TRUE(foo.empty());
  EXPECT_TRUE(bar.empty());
}

TEST(ExpatAdapterTest_2096, XpacketPIWithoutDataStoresEmptyValue_2096) {
  Exiv2::XMPToolkit::ExpatAdapter adapter;

  // PI with no data: <?xpacket?>
  const std::string xml = "<?xpacket?><root/>";

  ParseAll(adapter, xml);

  auto pi = FindPINodesByName(adapter.tree, "xpacket");
  ASSERT_EQ(pi.size(), 1U);
  EXPECT_EQ(pi[0]->kind, Exiv2::XMPToolkit::kPINode);
  EXPECT_EQ(pi[0]->name, "xpacket");
  EXPECT_TRUE(pi[0]->value.empty());
}

TEST(ExpatAdapterTest_2096, XpacketPINestedInsideElementIsAttachedToThatElement_2096) {
  Exiv2::XMPToolkit::ExpatAdapter adapter;

  const std::string xml = "<root><?xpacket end=\"w\"?></root>";

  ParseAll(adapter, xml);

  auto* rootElem = FindFirstElementByName(adapter.tree, "root");
  ASSERT_NE(rootElem, nullptr);

  // Expect exactly one xpacket PI node somewhere in the tree.
  auto pi = FindPINodesByName(adapter.tree, "xpacket");
  ASSERT_EQ(pi.size(), 1U);

  // And it should be present under the root element's content (direct child).
  bool foundAsDirectChild = false;
  for (auto* c : rootElem->content) {
    if (c && c->kind == Exiv2::XMPToolkit::kPINode && c->name == "xpacket") {
      foundAsDirectChild = true;
      EXPECT_EQ(c->value, "end=\"w\"");
      break;
    }
  }
  EXPECT_TRUE(foundAsDirectChild);
}

TEST(ExpatAdapterTest_2096, XpacketPIWithLargeDataPreservesValue_2096) {
  Exiv2::XMPToolkit::ExpatAdapter adapter;

  std::string bigData(4096, 'A');
  const std::string xml = "<?xpacket " + bigData + "?>"
                          "<root/>";

  ParseAll(adapter, xml);

  auto pi = FindPINodesByName(adapter.tree, "xpacket");
  ASSERT_EQ(pi.size(), 1U);
  EXPECT_EQ(pi[0]->value, bigData);
}