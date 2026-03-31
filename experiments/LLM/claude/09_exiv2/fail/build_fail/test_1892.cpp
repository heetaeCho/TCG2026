#include <gtest/gtest.h>
#include <string>
#include <vector>
#include <stdexcept>

// Include necessary headers
#include "XMPCore_Impl.hpp"

// We need to bring in the XMP_Throw macro and related types.
// If XMP_Throw is a macro that throws an exception, we need to handle it.
// Based on typical XMP SDK conventions, XMP_Throw throws an XMP_Error.

// Type aliases that may be needed
#ifndef XMP_VarString
typedef std::string XMP_VarString;
#endif

#ifndef XMP_OptionBits
typedef unsigned int XMP_OptionBits;
#endif

#ifndef XMP_StringPtr
typedef const char * XMP_StringPtr;
#endif

typedef std::vector<XPathStepInfo> XMP_ExpandedXPath;

// Declaration of the function under test
extern void ComposeXPath(const XMP_ExpandedXPath & expandedXPath, XMP_VarString * stringXPath);

class ComposeXPathTest_1892 : public ::testing::Test {
protected:
    XMP_VarString result;
    
    // Helper to create a minimal expanded path with schema and root
    XMP_ExpandedXPath MakeBasePath(const std::string& schema, const std::string& rootProp) {
        XMP_ExpandedXPath path;
        path.push_back(XPathStepInfo(schema.c_str(), 0));       // kSchemaStep = 0
        path.push_back(XPathStepInfo(rootProp.c_str(), 0));     // kRootPropStep = 1
        return path;
    }
};

// Test: Only root property step, no additional steps
TEST_F(ComposeXPathTest_1892, RootPropOnly_1892) {
    XMP_ExpandedXPath path = MakeBasePath("http://ns.adobe.com/xap/1.0/", "xmp:CreateDate");
    
    ComposeXPath(path, &result);
    
    EXPECT_EQ(result, "xmp:CreateDate");
}

// Test: Root property with a struct field step
TEST_F(ComposeXPathTest_1892, StructFieldStep_1892) {
    XMP_ExpandedXPath path = MakeBasePath("http://ns.adobe.com/xap/1.0/", "xmp:Root");
    path.push_back(XPathStepInfo("stRef:instanceID", kXMP_StructFieldStep));
    
    ComposeXPath(path, &result);
    
    EXPECT_EQ(result, "xmp:Root/stRef:instanceID");
}

// Test: Root property with a qualifier step
TEST_F(ComposeXPathTest_1892, QualifierStep_1892) {
    XMP_ExpandedXPath path = MakeBasePath("http://ns.adobe.com/xap/1.0/", "xmp:Root");
    path.push_back(XPathStepInfo("xml:lang", kXMP_QualifierStep));
    
    ComposeXPath(path, &result);
    
    EXPECT_EQ(result, "xmp:Root/xml:lang");
}

// Test: Root property with an array index step
TEST_F(ComposeXPathTest_1892, ArrayIndexStep_1892) {
    XMP_ExpandedXPath path = MakeBasePath("http://ns.adobe.com/xap/1.0/", "dc:subject");
    path.push_back(XPathStepInfo("[1]", kXMP_ArrayIndexStep));
    
    ComposeXPath(path, &result);
    
    EXPECT_EQ(result, "dc:subject[1]");
}

// Test: Root property with an array last step
TEST_F(ComposeXPathTest_1892, ArrayLastStep_1892) {
    XMP_ExpandedXPath path = MakeBasePath("http://ns.adobe.com/xap/1.0/", "dc:subject");
    path.push_back(XPathStepInfo("[last()]", kXMP_ArrayLastStep));
    
    ComposeXPath(path, &result);
    
    EXPECT_EQ(result, "dc:subject[last()]");
}

// Test: Root property with a qual selector step
TEST_F(ComposeXPathTest_1892, QualSelectorStep_1892) {
    XMP_ExpandedXPath path = MakeBasePath("http://ns.adobe.com/xap/1.0/", "dc:description");
    path.push_back(XPathStepInfo("[?xml:lang=\"en\"]", kXMP_QualSelectorStep));
    
    ComposeXPath(path, &result);
    
    EXPECT_EQ(result, "dc:description[?xml:lang=\"en\"]");
}

// Test: Root property with a field selector step
TEST_F(ComposeXPathTest_1892, FieldSelectorStep_1892) {
    XMP_ExpandedXPath path = MakeBasePath("http://ns.adobe.com/xap/1.0/", "xmp:Root");
    path.push_back(XPathStepInfo("[stRef:instanceID=\"abc\"]", kXMP_FieldSelectorStep));
    
    ComposeXPath(path, &result);
    
    EXPECT_EQ(result, "xmp:Root[stRef:instanceID=\"abc\"]");
}

// Test: Multiple steps combined - struct field then array index
TEST_F(ComposeXPathTest_1892, MultipleSteps_StructThenArrayIndex_1892) {
    XMP_ExpandedXPath path = MakeBasePath("http://ns.adobe.com/xap/1.0/", "xmp:Root");
    path.push_back(XPathStepInfo("stRef:History", kXMP_StructFieldStep));
    path.push_back(XPathStepInfo("[3]", kXMP_ArrayIndexStep));
    
    ComposeXPath(path, &result);
    
    EXPECT_EQ(result, "xmp:Root/stRef:History[3]");
}

// Test: Multiple steps combined - struct field, array index, struct field
TEST_F(ComposeXPathTest_1892, MultipleSteps_DeepPath_1892) {
    XMP_ExpandedXPath path = MakeBasePath("http://ns.adobe.com/xap/1.0/", "xmp:Root");
    path.push_back(XPathStepInfo("stRef:History", kXMP_StructFieldStep));
    path.push_back(XPathStepInfo("[1]", kXMP_ArrayIndexStep));
    path.push_back(XPathStepInfo("stEvt:action", kXMP_StructFieldStep));
    
    ComposeXPath(path, &result);
    
    EXPECT_EQ(result, "xmp:Root/stRef:History[1]/stEvt:action");
}

// Test: Default/unexpected step kind causes exception
TEST_F(ComposeXPathTest_1892, UnexpectedStepKindThrows_1892) {
    XMP_ExpandedXPath path = MakeBasePath("http://ns.adobe.com/xap/1.0/", "xmp:Root");
    // Use an invalid step kind (0 is not handled by any case)
    path.push_back(XPathStepInfo("invalid", 0));
    
    EXPECT_ANY_THROW(ComposeXPath(path, &result));
}

// Test: Another unexpected step kind value (e.g., 7)
TEST_F(ComposeXPathTest_1892, UnexpectedStepKind7Throws_1892) {
    XMP_ExpandedXPath path = MakeBasePath("http://ns.adobe.com/xap/1.0/", "xmp:Root");
    // 7 is not a valid step kind in the enum (valid: 1-6)
    path.push_back(XPathStepInfo("invalid", 7));
    
    EXPECT_ANY_THROW(ComposeXPath(path, &result));
}

// Test: Step with kXMP_StepIsAlias flag combined with a valid step kind
TEST_F(ComposeXPathTest_1892, StepWithAliasFlag_StructField_1892) {
    XMP_ExpandedXPath path = MakeBasePath("http://ns.adobe.com/xap/1.0/", "xmp:Root");
    // kXMP_StepIsAlias (16) | kXMP_StructFieldStep (1) = 17
    // The mask kXMP_StepKindMask (15) should extract kXMP_StructFieldStep
    path.push_back(XPathStepInfo("stRef:field", kXMP_StepIsAlias | kXMP_StructFieldStep));
    
    ComposeXPath(path, &result);
    
    EXPECT_EQ(result, "xmp:Root/stRef:field");
}

// Test: Step with kXMP_StepIsAlias flag combined with array index step
TEST_F(ComposeXPathTest_1892, StepWithAliasFlag_ArrayIndex_1892) {
    XMP_ExpandedXPath path = MakeBasePath("http://ns.adobe.com/xap/1.0/", "dc:subject");
    path.push_back(XPathStepInfo("[2]", kXMP_StepIsAlias | kXMP_ArrayIndexStep));
    
    ComposeXPath(path, &result);
    
    EXPECT_EQ(result, "dc:subject[2]");
}

// Test: Empty root property step
TEST_F(ComposeXPathTest_1892, EmptyRootProp_1892) {
    XMP_ExpandedXPath path = MakeBasePath("http://ns.adobe.com/xap/1.0/", "");
    
    ComposeXPath(path, &result);
    
    EXPECT_EQ(result, "");
}

// Test: Empty root property with struct field step
TEST_F(ComposeXPathTest_1892, EmptyRootWithStructField_1892) {
    XMP_ExpandedXPath path = MakeBasePath("http://ns.adobe.com/xap/1.0/", "");
    path.push_back(XPathStepInfo("field", kXMP_StructFieldStep));
    
    ComposeXPath(path, &result);
    
    EXPECT_EQ(result, "/field");
}

// Test: Multiple qualifier steps
TEST_F(ComposeXPathTest_1892, MultipleQualifierSteps_1892) {
    XMP_ExpandedXPath path = MakeBasePath("http://ns.adobe.com/xap/1.0/", "xmp:Root");
    path.push_back(XPathStepInfo("xml:lang", kXMP_QualifierStep));
    path.push_back(XPathStepInfo("rdf:type", kXMP_QualifierStep));
    
    ComposeXPath(path, &result);
    
    EXPECT_EQ(result, "xmp:Root/xml:lang/rdf:type");
}

// Test: Array index followed by array last
TEST_F(ComposeXPathTest_1892, ArrayIndexThenArrayLast_1892) {
    XMP_ExpandedXPath path = MakeBasePath("http://ns.adobe.com/xap/1.0/", "dc:subject");
    path.push_back(XPathStepInfo("[1]", kXMP_ArrayIndexStep));
    path.push_back(XPathStepInfo("[last()]", kXMP_ArrayLastStep));
    
    ComposeXPath(path, &result);
    
    EXPECT_EQ(result, "dc:subject[1][last()]");
}

// Test: Struct field followed by qual selector
TEST_F(ComposeXPathTest_1892, StructFieldThenQualSelector_1892) {
    XMP_ExpandedXPath path = MakeBasePath("http://ns.adobe.com/xap/1.0/", "xmp:Root");
    path.push_back(XPathStepInfo("dc:description", kXMP_StructFieldStep));
    path.push_back(XPathStepInfo("[?xml:lang=\"fr\"]", kXMP_QualSelectorStep));
    
    ComposeXPath(path, &result);
    
    EXPECT_EQ(result, "xmp:Root/dc:description[?xml:lang=\"fr\"]");
}

// Test: kXMP_StepIsAlias flag with unexpected step kind still throws
TEST_F(ComposeXPathTest_1892, AliasFlagWithInvalidKindThrows_1892) {
    XMP_ExpandedXPath path = MakeBasePath("http://ns.adobe.com/xap/1.0/", "xmp:Root");
    // kXMP_StepIsAlias (16) | 0 = 16, masked: 0 -> invalid
    path.push_back(XPathStepInfo("bad", kXMP_StepIsAlias));
    
    EXPECT_ANY_THROW(ComposeXPath(path, &result));
}

// Test: Long chain of all different valid step types
TEST_F(ComposeXPathTest_1892, AllValidStepTypes_1892) {
    XMP_ExpandedXPath path = MakeBasePath("http://ns.adobe.com/xap/1.0/", "root");
    path.push_back(XPathStepInfo("field1", kXMP_StructFieldStep));
    path.push_back(XPathStepInfo("qual1", kXMP_QualifierStep));
    path.push_back(XPathStepInfo("[1]", kXMP_ArrayIndexStep));
    path.push_back(XPathStepInfo("[last()]", kXMP_ArrayLastStep));
    path.push_back(XPathStepInfo("[?q=\"v\"]", kXMP_QualSelectorStep));
    path.push_back(XPathStepInfo("[f=\"v\"]", kXMP_FieldSelectorStep));
    
    ComposeXPath(path, &result);
    
    EXPECT_EQ(result, "root/field1/qual1[1][last()][?q=\"v\"][f=\"v\"]");
}
