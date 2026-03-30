// ============================================================================
// Test file for ./TestProjects/exiv2/xmpsdk/src/XMPIterator.cpp (TEST_ID: 2097)
// Focus: static AddSchemaProps(IterInfo&, IterNode&, const XMP_Node*)
// ============================================================================

#include <gtest/gtest.h>

#include <cstddef>
#include <cstdint>
#include <memory>
#include <type_traits>
#include <utility>
#include <vector>

// Include the real headers/types used by the implementation.
#include "TestProjects/exiv2/xmpsdk/src/XMPCore_Impl.hpp"
#include "TestProjects/exiv2/xmpsdk/src/XMPIterator.hpp"

// Bring the static function into this translation unit by including the .cpp.
// This is necessary because AddSchemaProps has internal linkage (static).
#include "TestProjects/exiv2/xmpsdk/src/XMPIterator.cpp"

namespace {

// Detection helper: IterNode::options may or may not be visible in the provided snippet.
template <typename T, typename = void>
struct HasPublicOptionsMember : std::false_type {};
template <typename T>
struct HasPublicOptionsMember<T, std::void_t<decltype(std::declval<T&>().options)>> : std::true_type {};

class AddSchemaPropsTest_2097 : public ::testing::Test {
protected:
  using NodeUP = std::unique_ptr<XMP_Node>;

  static NodeUP MakeNode(XMP_Node* parent, XMP_StringPtr name, XMP_OptionBits options) {
    return NodeUP(new XMP_Node(parent, name, options));
  }

  static NodeUP MakeSchemaWithChildren(const std::vector<std::pair<const char*, XMP_OptionBits>>& props) {
    NodeUP schema(new XMP_Node(/*parent*/ nullptr, /*name*/ "schema", /*options*/ 0));

    for (const auto& p : props) {
      NodeUP child(new XMP_Node(schema.get(), p.first, p.second));
      schema->children.push_back(child.get());
      owned_.push_back(std::move(child));  // keep alive; schema likely owns/deletes in destructor too
    }

    return schema;
  }

  void TearDown() override {
    // Important: XMP_Node's destructor may delete its children (common pattern in XMP SDK).
    // To avoid double-delete, we DO NOT delete children manually.
    // We only clear our unique_ptr list by releasing ownership before destruction if needed.
    // In case schema destructor deletes children, our unique_ptrs must not delete them again.
    for (auto& p : owned_) {
      (void)p.release();
    }
    owned_.clear();
  }

  // Storage for heap children created during a test. We release in TearDown to avoid double frees
  // if schema destructor owns/deletes its children.
  static inline std::vector<NodeUP> owned_;
};

}  // namespace

// ----------------------------------------------------------------------------
// Normal operation: adds IterNode entries for each schema child property.
// ----------------------------------------------------------------------------
TEST_F(AddSchemaPropsTest_2097, AddsOneIterChildPerSchemaProperty_2097) {
  IterInfo info;        // unused by AddSchemaProps (black-box expectation: no crash)
  IterNode iterSchema;  // target

  const std::vector<std::pair<const char*, XMP_OptionBits>> props = {
      {"prop:A", static_cast<XMP_OptionBits>(0x01)},
      {"prop:B", static_cast<XMP_OptionBits>(0x10)},
      {"prop:C", static_cast<XMP_OptionBits>(0x8000)},
  };

  auto schema = MakeSchemaWithChildren(props);

  ASSERT_EQ(iterSchema.children.size(), 0U);

  AddSchemaProps(info, iterSchema, schema.get());

  ASSERT_EQ(iterSchema.children.size(), props.size());

  for (size_t i = 0; i < props.size(); ++i) {
    EXPECT_EQ(iterSchema.children[i].fullPath, props[i].first);
    EXPECT_EQ(iterSchema.children[i].leafOffset, 0U);

    if constexpr (HasPublicOptionsMember<IterNode>::value) {
      EXPECT_EQ(iterSchema.children[i].options, props[i].second);
    }
  }

  // Let schema clean up (and potentially delete children). Our TearDown releases child unique_ptrs.
  schema.reset();
}

// ----------------------------------------------------------------------------
// Boundary: empty schema children -> no additions.
// ----------------------------------------------------------------------------
TEST_F(AddSchemaPropsTest_2097, EmptySchemaAddsNothing_2097) {
  IterInfo info;
  IterNode iterSchema;

  std::unique_ptr<XMP_Node> schema(new XMP_Node(nullptr, "schema", 0));
  ASSERT_TRUE(schema->children.empty());

  // Pre-seed iterSchema to ensure no unintended clearing.
  iterSchema.children.push_back(IterNode(/*options*/ 0, /*path*/ "existing", /*leaf*/ 123));

  const size_t before = iterSchema.children.size();

  AddSchemaProps(info, iterSchema, schema.get());

  ASSERT_EQ(iterSchema.children.size(), before);
  EXPECT_EQ(iterSchema.children[0].fullPath, "existing");
  EXPECT_EQ(iterSchema.children[0].leafOffset, 123U);
}

// ----------------------------------------------------------------------------
// Normal operation: appends to existing iterSchema.children (does not overwrite).
// ----------------------------------------------------------------------------
TEST_F(AddSchemaPropsTest_2097, AppendsToExistingIterSchemaChildren_2097) {
  IterInfo info;
  IterNode iterSchema;

  iterSchema.children.push_back(IterNode(/*options*/ 0, /*path*/ "seed", /*leaf*/ 7));

  const std::vector<std::pair<const char*, XMP_OptionBits>> props = {
      {"p1", static_cast<XMP_OptionBits>(0x11)},
      {"p2", static_cast<XMP_OptionBits>(0x22)},
  };
  auto schema = MakeSchemaWithChildren(props);

  AddSchemaProps(info, iterSchema, schema.get());

  ASSERT_EQ(iterSchema.children.size(), 1U + props.size());
  EXPECT_EQ(iterSchema.children[0].fullPath, "seed");
  EXPECT_EQ(iterSchema.children[0].leafOffset, 7U);

  for (size_t i = 0; i < props.size(); ++i) {
    const size_t idx = 1 + i;
    EXPECT_EQ(iterSchema.children[idx].fullPath, props[i].first);
    EXPECT_EQ(iterSchema.children[idx].leafOffset, 0U);

    if constexpr (HasPublicOptionsMember<IterNode>::value) {
      EXPECT_EQ(iterSchema.children[idx].options, props[i].second);
    }
  }

  schema.reset();
}

// ----------------------------------------------------------------------------
// Boundary: many children (loop correctness).
// ----------------------------------------------------------------------------
TEST_F(AddSchemaPropsTest_2097, HandlesManySchemaChildren_2097) {
  IterInfo info;
  IterNode iterSchema;

  std::vector<std::pair<const char*, XMP_OptionBits>> props;
  props.reserve(200);

  // Use stable string storage for C-strings (since XMP_Node ctor takes XMP_StringPtr).
  static std::vector<std::string> names;
  names.clear();
  names.reserve(200);

  for (int i = 0; i < 200; ++i) {
    names.push_back("prop_" + std::to_string(i));
    props.emplace_back(names.back().c_str(), static_cast<XMP_OptionBits>(i));
  }

  auto schema = MakeSchemaWithChildren(props);

  AddSchemaProps(info, iterSchema, schema.get());

  ASSERT_EQ(iterSchema.children.size(), props.size());
  EXPECT_EQ(iterSchema.children.front().fullPath, "prop_0");
  EXPECT_EQ(iterSchema.children.back().fullPath, "prop_199");

  // Spot-check a few indices.
  for (size_t idx : {size_t{0}, size_t{1}, size_t{57}, size_t{199}}) {
    EXPECT_EQ(iterSchema.children[idx].fullPath, props[idx].first);
    EXPECT_EQ(iterSchema.children[idx].leafOffset, 0U);
    if constexpr (HasPublicOptionsMember<IterNode>::value) {
      EXPECT_EQ(iterSchema.children[idx].options, props[idx].second);
    }
  }

  schema.reset();
}