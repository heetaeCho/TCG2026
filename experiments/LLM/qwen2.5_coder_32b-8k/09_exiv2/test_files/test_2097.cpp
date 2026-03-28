#include <gtest/gtest.h>

#include <gmock/gmock.h>



// Assuming necessary includes for XMP classes and functions are already present



TEST(AddSchemaPropsTest_2097, NormalOperation_AddsPropertiesToIterNode_2097) {

    IterInfo info;

    IterNode iterSchema;

    XMP_Node xmpSchema(nullptr, "testSchema", 0);



    // Add some properties to the schema

    xmpSchema.children.push_back(XMP_Node(&xmpSchema, "prop1", 0));

    xmpSchema.children.push_back(XMP_Node(&xmpSchema, "prop2", 0));



    AddSchemaProps(info, iterSchema, &xmpSchema);



    EXPECT_EQ(iterSchema.children.size(), 2);

    EXPECT_EQ(iterSchema.children[0].fullPath, "prop1");

    EXPECT_EQ(iterSchema.children[1].fullPath, "prop2");

}



TEST(AddSchemaPropsTest_2097, Boundary_NoProperties_2097) {

    IterInfo info;

    IterNode iterSchema;

    XMP_Node xmpSchema(nullptr, "testSchema", 0);



    // No properties added to the schema



    AddSchemaProps(info, iterSchema, &xmpSchema);



    EXPECT_EQ(iterSchema.children.size(), 0);

}



TEST(AddSchemaPropsTest_2097, Boundary_EmptySchemaName_2097) {

    IterInfo info;

    IterNode iterSchema;

    XMP_Node xmpSchema(nullptr, "", 0);



    // Add some properties to the schema

    xmpSchema.children.push_back(XMP_Node(&xmpSchema, "prop1", 0));

    xmpSchema.children.push_back(XMP_Node(&xmpSchema, "prop2", 0));



    AddSchemaProps(info, iterSchema, &xmpSchema);



    EXPECT_EQ(iterSchema.children.size(), 2);

    EXPECT_EQ(iterSchema.children[0].fullPath, "prop1");

    EXPECT_EQ(iterSchema.children[1].fullPath, "prop2");

}



TEST(AddSchemaPropsTest_2097, Boundary_EmptyPropertyName_2097) {

    IterInfo info;

    IterNode iterSchema;

    XMP_Node xmpSchema(nullptr, "testSchema", 0);



    // Add properties with empty names to the schema

    xmpSchema.children.push_back(XMP_Node(&xmpSchema, "", 0));

    xmpSchema.children.push_back(XMP_Node(&xmpSchema, "prop2", 0));



    AddSchemaProps(info, iterSchema, &xmpSchema);



    EXPECT_EQ(iterSchema.children.size(), 2);

    EXPECT_EQ(iterSchema.children[0].fullPath, "");

    EXPECT_EQ(iterSchema.children[1].fullPath, "prop2");

}



TEST(AddSchemaPropsTest_2097, Exceptional_SchemaWithNullChildren_2097) {

    IterInfo info;

    IterNode iterSchema;

    XMP_Node xmpSchema(nullptr, "testSchema", 0);



    // Set children to nullptr

    xmpSchema.children.clear();

    xmpSchema.children.push_back(XMP_Node(&xmpSchema, "prop1", 0));



    AddSchemaProps(info, iterSchema, &xmpSchema);



    EXPECT_EQ(iterSchema.children.size(), 1);

    EXPECT_EQ(iterSchema.children[0].fullPath, "prop1");

}
