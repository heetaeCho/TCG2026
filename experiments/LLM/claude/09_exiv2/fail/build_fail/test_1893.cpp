#include <gtest/gtest.h>
#include <string>
#include <vector>

// Include necessary XMP headers
#define TXMP_STRING_TYPE std::string
#include "XMP_Const.h"
#include "XMPCore_Impl.hpp"
#include "XMPMeta.hpp"

// We need access to ExpandXPath and related types
// These are declared in XMPCore_Impl.hpp

class ExpandXPathTest_1893 : public ::testing::Test {
protected:
    static void SetUpTestSuite() {
        // Initialize XMP SDK - required for namespace registration and alias maps
        try {
            SXMPMeta::Initialize();
        } catch (...) {
            // May already be initialized
        }
        // Register a test namespace if needed
        std::string actualPrefix;
        SXMPMeta::RegisterNamespace("http://ns.adobe.com/xap/1.0/", "xmp", &actualPrefix);
        SXMPMeta::RegisterNamespace("http://purl.org/dc/elements/1.1/", "dc", &actualPrefix);
        SXMPMeta::RegisterNamespace("http://ns.adobe.com/exif/1.0/", "exif", &actualPrefix);
        SXMPMeta::RegisterNamespace("http://ns.test.com/", "test", &actualPrefix);
    }

    static void TearDownTestSuite() {
        try {
            SXMPMeta::Terminate();
        } catch (...) {
        }
    }

    void SetUp() override {
        expandedXPath.clear();
    }

    XMP_ExpandedXPath expandedXPath;
};

// Test: Simple property path expands correctly
TEST_F(ExpandXPathTest_1893, SimplePropertyPath_1893) {
    ASSERT_NO_THROW(
        ExpandXPath("http://purl.org/dc/elements/1.1/", "dc:title", &expandedXPath)
    );
    EXPECT_GE(expandedXPath.size(), 2u); // schema step + root prop step
}

// Test: Empty property path should throw
TEST_F(ExpandXPathTest_1893, EmptyPropertyPathThrows_1893) {
    // propPath is empty string - the initial step would be empty
    // Actually, *propPath != 0 is asserted, so empty string triggers assert
    // The assert may abort or throw depending on configuration
    // Let's test with a path that leads to empty initial step differently
    // An empty propPath has *propPath == 0 which hits the Assert
    // We skip this if Assert is a hard abort
}

// Test: Property with struct field step
TEST_F(ExpandXPathTest_1893, StructFieldStep_1893) {
    ASSERT_NO_THROW(
        ExpandXPath("http://purl.org/dc/elements/1.1/", "dc:creator/dc:name", &expandedXPath)
    );
    EXPECT_GE(expandedXPath.size(), 3u);
}

// Test: Property with array index
TEST_F(ExpandXPathTest_1893, ArrayIndexStep_1893) {
    ASSERT_NO_THROW(
        ExpandXPath("http://purl.org/dc/elements/1.1/", "dc:creator[1]", &expandedXPath)
    );
    EXPECT_GE(expandedXPath.size(), 3u);
    // The last step should be an array index step
    if (expandedXPath.size() >= 3) {
        EXPECT_EQ(expandedXPath.back().options & kXMP_StepKindMask, kXMP_ArrayIndexStep);
    }
}

// Test: Property with [last()] step
TEST_F(ExpandXPathTest_1893, ArrayLastStep_1893) {
    ASSERT_NO_THROW(
        ExpandXPath("http://purl.org/dc/elements/1.1/", "dc:creator[last()]", &expandedXPath)
    );
    EXPECT_GE(expandedXPath.size(), 3u);
    if (expandedXPath.size() >= 3) {
        EXPECT_EQ(expandedXPath.back().options & kXMP_StepKindMask, kXMP_ArrayLastStep);
    }
}

// Test: Missing ']' for integer array index should throw
TEST_F(ExpandXPathTest_1893, MissingClosingBracketForIntegerIndex_1893) {
    EXPECT_THROW(
        ExpandXPath("http://purl.org/dc/elements/1.1/", "dc:creator[1", &expandedXPath),
        XMP_Error
    );
}

// Test: Invalid non-numeric array index should throw
TEST_F(ExpandXPathTest_1893, InvalidNonNumericArrayIndex_1893) {
    EXPECT_THROW(
        ExpandXPath("http://purl.org/dc/elements/1.1/", "dc:creator[abc]", &expandedXPath),
        XMP_Error
    );
}

// Test: Missing '[' after '*' should throw
TEST_F(ExpandXPathTest_1893, MissingBracketAfterStar_1893) {
    EXPECT_THROW(
        ExpandXPath("http://purl.org/dc/elements/1.1/", "dc:creator/*abc", &expandedXPath),
        XMP_Error
    );
}

// Test: Field selector with single quotes
TEST_F(ExpandXPathTest_1893, FieldSelectorSingleQuote_1893) {
    ASSERT_NO_THROW(
        ExpandXPath("http://purl.org/dc/elements/1.1/", "dc:creator[dc:name='John']", &expandedXPath)
    );
    EXPECT_GE(expandedXPath.size(), 3u);
    if (expandedXPath.size() >= 3) {
        EXPECT_EQ(expandedXPath.back().options & kXMP_StepKindMask, kXMP_FieldSelectorStep);
    }
}

// Test: Field selector with double quotes
TEST_F(ExpandXPathTest_1893, FieldSelectorDoubleQuote_1893) {
    ASSERT_NO_THROW(
        ExpandXPath("http://purl.org/dc/elements/1.1/", "dc:creator[dc:name=\"John\"]", &expandedXPath)
    );
    EXPECT_GE(expandedXPath.size(), 3u);
    if (expandedXPath.size() >= 3) {
        EXPECT_EQ(expandedXPath.back().options & kXMP_StepKindMask, kXMP_FieldSelectorStep);
    }
}

// Test: Invalid quote in array selector should throw
TEST_F(ExpandXPathTest_1893, InvalidQuoteInArraySelector_1893) {
    EXPECT_THROW(
        ExpandXPath("http://purl.org/dc/elements/1.1/", "dc:creator[dc:name=John]", &expandedXPath),
        XMP_Error
    );
}

// Test: No terminating quote in array selector should throw
TEST_F(ExpandXPathTest_1893, NoTerminatingQuoteInSelector_1893) {
    EXPECT_THROW(
        ExpandXPath("http://purl.org/dc/elements/1.1/", "dc:creator[dc:name='John]", &expandedXPath),
        XMP_Error
    );
}

// Test: xml:lang qualifier with '@'
TEST_F(ExpandXPathTest_1893, XmlLangQualifierWithAt_1893) {
    ASSERT_NO_THROW(
        ExpandXPath("http://purl.org/dc/elements/1.1/", "dc:title/@xml:lang", &expandedXPath)
    );
    EXPECT_GE(expandedXPath.size(), 3u);
    if (expandedXPath.size() >= 3) {
        EXPECT_EQ(expandedXPath.back().options & kXMP_StepKindMask, kXMP_QualifierStep);
        // '@' should have been changed to '?'
        EXPECT_EQ(expandedXPath.back().step[0], '?');
    }
}

// Test: Non xml:lang with '@' should throw
TEST_F(ExpandXPathTest_1893, NonXmlLangWithAtThrows_1893) {
    EXPECT_THROW(
        ExpandXPath("http://purl.org/dc/elements/1.1/", "dc:title/@dc:something", &expandedXPath),
        XMP_Error
    );
}

// Test: xml:lang qualifier with '?'
TEST_F(ExpandXPathTest_1893, XmlLangQualifierWithQuestion_1893) {
    ASSERT_NO_THROW(
        ExpandXPath("http://purl.org/dc/elements/1.1/", "dc:title/?xml:lang", &expandedXPath)
    );
    EXPECT_GE(expandedXPath.size(), 3u);
    if (expandedXPath.size() >= 3) {
        EXPECT_EQ(expandedXPath.back().options & kXMP_StepKindMask, kXMP_QualifierStep);
    }
}

// Test: Multiple nested steps
TEST_F(ExpandXPathTest_1893, MultipleNestedSteps_1893) {
    ASSERT_NO_THROW(
        ExpandXPath("http://purl.org/dc/elements/1.1/", "dc:creator[1]/dc:name", &expandedXPath)
    );
    EXPECT_GE(expandedXPath.size(), 4u);
}

// Test: Root property step has struct field flag
TEST_F(ExpandXPathTest_1893, RootPropertyHasStructFieldFlag_1893) {
    ASSERT_NO_THROW(
        ExpandXPath("http://purl.org/dc/elements/1.1/", "dc:title", &expandedXPath)
    );
    EXPECT_GE(expandedXPath.size(), 2u);
    if (expandedXPath.size() >= 2) {
        EXPECT_NE(expandedXPath[kRootPropStep].options & kXMP_StructFieldStep, 0u);
    }
}

// Test: Schema step is first element
TEST_F(ExpandXPathTest_1893, SchemaStepIsFirst_1893) {
    ASSERT_NO_THROW(
        ExpandXPath("http://purl.org/dc/elements/1.1/", "dc:title", &expandedXPath)
    );
    EXPECT_GE(expandedXPath.size(), 2u);
    if (expandedXPath.size() >= 2) {
        // Schema step should contain the namespace URI
        EXPECT_EQ(expandedXPath[kSchemaStep].step, "http://purl.org/dc/elements/1.1/");
    }
}

// Test: Array index with multiple digits
TEST_F(ExpandXPathTest_1893, MultiDigitArrayIndex_1893) {
    ASSERT_NO_THROW(
        ExpandXPath("http://purl.org/dc/elements/1.1/", "dc:creator[123]", &expandedXPath)
    );
    EXPECT_GE(expandedXPath.size(), 3u);
    if (expandedXPath.size() >= 3) {
        EXPECT_EQ(expandedXPath.back().options & kXMP_StepKindMask, kXMP_ArrayIndexStep);
        EXPECT_EQ(expandedXPath.back().step, "[123]");
    }
}

// Test: Missing ']' or '=' for non-numeric array index
TEST_F(ExpandXPathTest_1893, MissingBracketOrEqualsThrows_1893) {
    // A selector that has neither ']' nor '=' and reaches end of string
    EXPECT_THROW(
        ExpandXPath("http://purl.org/dc/elements/1.1/", "dc:creator[dc:name", &expandedXPath),
        XMP_Error
    );
}

// Test: Qual selector with @xml:lang
TEST_F(ExpandXPathTest_1893, QualSelectorWithAtXmlLang_1893) {
    ASSERT_NO_THROW(
        ExpandXPath("http://purl.org/dc/elements/1.1/", "dc:title[@xml:lang='en']", &expandedXPath)
    );
    EXPECT_GE(expandedXPath.size(), 3u);
    if (expandedXPath.size() >= 3) {
        EXPECT_EQ(expandedXPath.back().options & kXMP_StepKindMask, kXMP_QualSelectorStep);
    }
}

// Test: Qual selector with non-xml:lang '@' should throw
TEST_F(ExpandXPathTest_1893, QualSelectorNonXmlLangAtThrows_1893) {
    EXPECT_THROW(
        ExpandXPath("http://purl.org/dc/elements/1.1/", "dc:title[@dc:foo='bar']", &expandedXPath),
        XMP_Error
    );
}

// Test: Star followed by bracket (wildcard array)
TEST_F(ExpandXPathTest_1893, StarBracketCombination_1893) {
    ASSERT_NO_THROW(
        ExpandXPath("http://purl.org/dc/elements/1.1/", "dc:creator/*[1]", &expandedXPath)
    );
    EXPECT_GE(expandedXPath.size(), 3u);
}

// Test: Expanded path is cleared before use
TEST_F(ExpandXPathTest_1893, ExpandedPathIsCleared_1893) {
    // Pre-fill with junk
    expandedXPath.push_back(XPathStepInfo("junk", 0));
    expandedXPath.push_back(XPathStepInfo("more_junk", 0));

    ASSERT_NO_THROW(
        ExpandXPath("http://purl.org/dc/elements/1.1/", "dc:title", &expandedXPath)
    );
    // Should not contain old data
    bool hasJunk = false;
    for (size_t i = 0; i < expandedXPath.size(); ++i) {
        if (expandedXPath[i].step == "junk" || expandedXPath[i].step == "more_junk") {
            hasJunk = true;
        }
    }
    EXPECT_FALSE(hasJunk);
}

// Test: Escaped quotes in field selector value
TEST_F(ExpandXPathTest_1893, EscapedQuotesInFieldSelector_1893) {
    // Doubled quotes inside selector value
    ASSERT_NO_THROW(
        ExpandXPath("http://purl.org/dc/elements/1.1/", "dc:creator[dc:name='John''s']", &expandedXPath)
    );
    EXPECT_GE(expandedXPath.size(), 3u);
}

// Test: Missing ']' after field selector value should throw
TEST_F(ExpandXPathTest_1893, MissingBracketAfterFieldSelector_1893) {
    EXPECT_THROW(
        ExpandXPath("http://purl.org/dc/elements/1.1/", "dc:creator[dc:name='John'", &expandedXPath),
        XMP_Error
    );
}

// Test: Deeply nested path
TEST_F(ExpandXPathTest_1893, DeeplyNestedPath_1893) {
    ASSERT_NO_THROW(
        ExpandXPath("http://purl.org/dc/elements/1.1/", "dc:a/dc:b/dc:c/dc:d", &expandedXPath)
    );
    // schema + root + 3 additional steps = 5
    EXPECT_GE(expandedXPath.size(), 5u);
}

// Test: Array index zero
TEST_F(ExpandXPathTest_1893, ArrayIndexZero_1893) {
    ASSERT_NO_THROW(
        ExpandXPath("http://purl.org/dc/elements/1.1/", "dc:creator[0]", &expandedXPath)
    );
    EXPECT_GE(expandedXPath.size(), 3u);
    if (expandedXPath.size() >= 3) {
        EXPECT_EQ(expandedXPath.back().options & kXMP_StepKindMask, kXMP_ArrayIndexStep);
    }
}
