#include <gtest/gtest.h>
#include <vector>
#include <string>

// Include necessary headers
#include "XMPCore_Impl.hpp"
#include "XMPIterator.hpp"

// Since AddSchemaProps is a static function in XMPIterator.cpp, we need to either
// make it accessible or test it through the public interface. Given that it's static,
// we'll need to include the source file or use a workaround.
// For testing purposes, we'll include the cpp file to access the static function.
#include "XMPIterator.cpp"

class AddSchemaPropsTest_2097 : public ::testing::Test {
protected:
    void SetUp() override {
    }

    void TearDown() override {
    }
};

// Test: Adding properties from a schema with no children results in empty iterSchema children
TEST_F(AddSchemaPropsTest_2097, EmptySchemaProducesNoChildren_2097) {
    IterInfo info;
    IterNode iterSchema;
    XMP_Node xmpSchema(nullptr, "testSchema", 0);

    AddSchemaProps(info, iterSchema, &xmpSchema);

    EXPECT_TRUE(iterSchema.children.empty());
}

// Test: Adding properties from a schema with one child
TEST_F(AddSchemaPropsTest_2097, SingleChildProperty_2097) {
    IterInfo info;
    IterNode iterSchema;
    XMP_Node xmpSchema(nullptr, "testSchema", 0);

    XMP_Node* child1 = new XMP_Node(&xmpSchema, "prop1", 0x01);
    xmpSchema.children.push_back(child1);

    AddSchemaProps(info, iterSchema, &xmpSchema);

    ASSERT_EQ(iterSchema.children.size(), 1u);
    EXPECT_EQ(iterSchema.children[0].fullPath, "prop1");
    EXPECT_EQ(iterSchema.children[0].leafOffset, 0u);
}

// Test: Adding properties from a schema with multiple children
TEST_F(AddSchemaPropsTest_2097, MultipleChildProperties_2097) {
    IterInfo info;
    IterNode iterSchema;
    XMP_Node xmpSchema(nullptr, "testSchema", 0);

    XMP_Node* child1 = new XMP_Node(&xmpSchema, "prop1", 0x01);
    XMP_Node* child2 = new XMP_Node(&xmpSchema, "prop2", 0x02);
    XMP_Node* child3 = new XMP_Node(&xmpSchema, "prop3", 0x04);
    xmpSchema.children.push_back(child1);
    xmpSchema.children.push_back(child2);
    xmpSchema.children.push_back(child3);

    AddSchemaProps(info, iterSchema, &xmpSchema);

    ASSERT_EQ(iterSchema.children.size(), 3u);
    EXPECT_EQ(iterSchema.children[0].fullPath, "prop1");
    EXPECT_EQ(iterSchema.children[1].fullPath, "prop2");
    EXPECT_EQ(iterSchema.children[2].fullPath, "prop3");
}

// Test: Options are correctly propagated to IterNode children
TEST_F(AddSchemaPropsTest_2097, OptionsArePropagated_2097) {
    IterInfo info;
    IterNode iterSchema;
    XMP_Node xmpSchema(nullptr, "testSchema", 0);

    XMP_OptionBits opts = 0xABCD;
    XMP_Node* child1 = new XMP_Node(&xmpSchema, "propWithOptions", opts);
    xmpSchema.children.push_back(child1);

    AddSchemaProps(info, iterSchema, &xmpSchema);

    ASSERT_EQ(iterSchema.children.size(), 1u);
    EXPECT_EQ(iterSchema.children[0].options, opts);
}

// Test: Leaf offset is set to 0 for all added children
TEST_F(AddSchemaPropsTest_2097, LeafOffsetIsZero_2097) {
    IterInfo info;
    IterNode iterSchema;
    XMP_Node xmpSchema(nullptr, "testSchema", 0);

    XMP_Node* child1 = new XMP_Node(&xmpSchema, "prop1", 0);
    XMP_Node* child2 = new XMP_Node(&xmpSchema, "prop2", 0);
    xmpSchema.children.push_back(child1);
    xmpSchema.children.push_back(child2);

    AddSchemaProps(info, iterSchema, &xmpSchema);

    ASSERT_EQ(iterSchema.children.size(), 2u);
    EXPECT_EQ(iterSchema.children[0].leafOffset, 0u);
    EXPECT_EQ(iterSchema.children[1].leafOffset, 0u);
}

// Test: The name (fullPath) of IterNode matches the XMP_Node name
TEST_F(AddSchemaPropsTest_2097, FullPathMatchesNodeName_2097) {
    IterInfo info;
    IterNode iterSchema;
    XMP_Node xmpSchema(nullptr, "mySchema", 0);

    std::string longName = "dc:very_long_property_name_for_testing_purposes";
    XMP_Node* child1 = new XMP_Node(&xmpSchema, longName, 0);
    xmpSchema.children.push_back(child1);

    AddSchemaProps(info, iterSchema, &xmpSchema);

    ASSERT_EQ(iterSchema.children.size(), 1u);
    EXPECT_EQ(iterSchema.children[0].fullPath, longName);
}

// Test: Existing children in iterSchema are preserved when adding new ones
TEST_F(AddSchemaPropsTest_2097, ExistingChildrenPreserved_2097) {
    IterInfo info;
    IterNode iterSchema;

    // Pre-populate iterSchema with an existing child
    iterSchema.children.push_back(IterNode(0, "existingProp", 0));

    XMP_Node xmpSchema(nullptr, "testSchema", 0);
    XMP_Node* child1 = new XMP_Node(&xmpSchema, "newProp", 0);
    xmpSchema.children.push_back(child1);

    AddSchemaProps(info, iterSchema, &xmpSchema);

    ASSERT_EQ(iterSchema.children.size(), 2u);
    EXPECT_EQ(iterSchema.children[0].fullPath, "existingProp");
    EXPECT_EQ(iterSchema.children[1].fullPath, "newProp");
}

// Test: visitStage of added IterNode children defaults to kIter_BeforeVisit
TEST_F(AddSchemaPropsTest_2097, VisitStageIsBeforeVisit_2097) {
    IterInfo info;
    IterNode iterSchema;
    XMP_Node xmpSchema(nullptr, "testSchema", 0);

    XMP_Node* child1 = new XMP_Node(&xmpSchema, "prop1", 0);
    xmpSchema.children.push_back(child1);

    AddSchemaProps(info, iterSchema, &xmpSchema);

    ASSERT_EQ(iterSchema.children.size(), 1u);
    EXPECT_EQ(iterSchema.children[0].visitStage, kIter_BeforeVisit);
}

// Test: IterNode children list of added nodes is empty (no nested children added)
TEST_F(AddSchemaPropsTest_2097, AddedNodesHaveNoChildren_2097) {
    IterInfo info;
    IterNode iterSchema;
    XMP_Node xmpSchema(nullptr, "testSchema", 0);

    // Create an XMP_Node with its own children
    XMP_Node* child1 = new XMP_Node(&xmpSchema, "prop1", 0);
    XMP_Node* grandchild = new XMP_Node(child1, "subprop1", 0);
    child1->children.push_back(grandchild);
    xmpSchema.children.push_back(child1);

    AddSchemaProps(info, iterSchema, &xmpSchema);

    ASSERT_EQ(iterSchema.children.size(), 1u);
    // The function only adds top-level properties, not their descendants
    EXPECT_TRUE(iterSchema.children[0].children.empty());
}

// Test: Property with empty name
TEST_F(AddSchemaPropsTest_2097, EmptyPropertyName_2097) {
    IterInfo info;
    IterNode iterSchema;
    XMP_Node xmpSchema(nullptr, "testSchema", 0);

    XMP_Node* child1 = new XMP_Node(&xmpSchema, "", 0);
    xmpSchema.children.push_back(child1);

    AddSchemaProps(info, iterSchema, &xmpSchema);

    ASSERT_EQ(iterSchema.children.size(), 1u);
    EXPECT_EQ(iterSchema.children[0].fullPath, "");
}

// Test: Large number of children
TEST_F(AddSchemaPropsTest_2097, LargeNumberOfChildren_2097) {
    IterInfo info;
    IterNode iterSchema;
    XMP_Node xmpSchema(nullptr, "testSchema", 0);

    const size_t numChildren = 1000;
    for (size_t i = 0; i < numChildren; ++i) {
        std::string name = "prop" + std::to_string(i);
        XMP_Node* child = new XMP_Node(&xmpSchema, name, static_cast<XMP_OptionBits>(i));
        xmpSchema.children.push_back(child);
    }

    AddSchemaProps(info, iterSchema, &xmpSchema);

    ASSERT_EQ(iterSchema.children.size(), numChildren);
    for (size_t i = 0; i < numChildren; ++i) {
        std::string expectedName = "prop" + std::to_string(i);
        EXPECT_EQ(iterSchema.children[i].fullPath, expectedName);
        EXPECT_EQ(iterSchema.children[i].options, static_cast<XMP_OptionBits>(i));
    }
}

// Test: info parameter is unused - function should work regardless of info state
TEST_F(AddSchemaPropsTest_2097, InfoParameterUnused_2097) {
    IterInfo info1;
    IterInfo info2(0x1234, nullptr);

    IterNode iterSchema1;
    IterNode iterSchema2;

    XMP_Node xmpSchema(nullptr, "testSchema", 0);
    XMP_Node* child1 = new XMP_Node(&xmpSchema, "prop1", 0x10);
    xmpSchema.children.push_back(child1);

    AddSchemaProps(info1, iterSchema1, &xmpSchema);
    AddSchemaProps(info2, iterSchema2, &xmpSchema);

    // Both should produce the same result regardless of info state
    ASSERT_EQ(iterSchema1.children.size(), iterSchema2.children.size());
    EXPECT_EQ(iterSchema1.children[0].fullPath, iterSchema2.children[0].fullPath);
    EXPECT_EQ(iterSchema1.children[0].options, iterSchema2.children[0].options);
}

// Test: Properties with various option bits
TEST_F(AddSchemaPropsTest_2097, VariousOptionBits_2097) {
    IterInfo info;
    IterNode iterSchema;
    XMP_Node xmpSchema(nullptr, "testSchema", 0);

    XMP_Node* child1 = new XMP_Node(&xmpSchema, "prop1", 0x00000000);
    XMP_Node* child2 = new XMP_Node(&xmpSchema, "prop2", 0xFFFFFFFF);
    XMP_Node* child3 = new XMP_Node(&xmpSchema, "prop3", 0x80000000);
    xmpSchema.children.push_back(child1);
    xmpSchema.children.push_back(child2);
    xmpSchema.children.push_back(child3);

    AddSchemaProps(info, iterSchema, &xmpSchema);

    ASSERT_EQ(iterSchema.children.size(), 3u);
    EXPECT_EQ(iterSchema.children[0].options, 0x00000000u);
    EXPECT_EQ(iterSchema.children[1].options, 0xFFFFFFFFu);
    EXPECT_EQ(iterSchema.children[2].options, 0x80000000u);
}
