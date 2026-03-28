#include <gtest/gtest.h>
#include <string>

// Type definitions matching XMP SDK
typedef unsigned int XMP_OptionBits;
typedef const char* XMP_StringPtr;
typedef std::string XMP_VarString;
typedef int XMP_Index;

// Constants from XMP_Const.h
const XMP_OptionBits kXMP_PropArrayIsAlternate = 2048;
const XMP_OptionBits kXMP_PropArrayIsOrdered = 1024;
const XMP_OptionBits kXMP_PropArrayIsUnordered = 512;

// Declaration of the function under test
static void EmitRDFArrayTag(XMP_OptionBits arrayForm, XMP_VarString& outputStr,
                            XMP_StringPtr newline, XMP_StringPtr indentStr,
                            XMP_Index indent, XMP_Index arraySize, bool isStartTag) {
    if ((!isStartTag) && (arraySize == 0)) return;

    for (XMP_Index level = indent; level > 0; --level) outputStr += indentStr;

    if (isStartTag) {
        outputStr += "<rdf:";
    } else {
        outputStr += "</rdf:";
    }

    if (arrayForm & kXMP_PropArrayIsAlternate) {
        outputStr += "Alt";
    } else if (arrayForm & kXMP_PropArrayIsOrdered) {
        outputStr += "Seq";
    } else {
        outputStr += "Bag";
    }

    if (isStartTag && (arraySize == 0)) outputStr += '/';

    outputStr += '>';
    outputStr += newline;
}

class EmitRDFArrayTagTest_2107 : public ::testing::Test {
protected:
    XMP_VarString output;

    void SetUp() override {
        output.clear();
    }
};

// --- Normal operation tests ---

TEST_F(EmitRDFArrayTagTest_2107, StartTagBagNonEmpty_2107) {
    EmitRDFArrayTag(kXMP_PropArrayIsUnordered, output, "\n", "\t", 0, 5, true);
    EXPECT_EQ(output, "<rdf:Bag>\n");
}

TEST_F(EmitRDFArrayTagTest_2107, StartTagSeqNonEmpty_2107) {
    EmitRDFArrayTag(kXMP_PropArrayIsOrdered, output, "\n", "\t", 0, 5, true);
    EXPECT_EQ(output, "<rdf:Seq>\n");
}

TEST_F(EmitRDFArrayTagTest_2107, StartTagAltNonEmpty_2107) {
    EmitRDFArrayTag(kXMP_PropArrayIsAlternate, output, "\n", "\t", 0, 5, true);
    EXPECT_EQ(output, "<rdf:Alt>\n");
}

TEST_F(EmitRDFArrayTagTest_2107, EndTagBagNonEmpty_2107) {
    EmitRDFArrayTag(kXMP_PropArrayIsUnordered, output, "\n", "\t", 0, 5, false);
    EXPECT_EQ(output, "</rdf:Bag>\n");
}

TEST_F(EmitRDFArrayTagTest_2107, EndTagSeqNonEmpty_2107) {
    EmitRDFArrayTag(kXMP_PropArrayIsOrdered, output, "\n", "\t", 0, 5, false);
    EXPECT_EQ(output, "</rdf:Seq>\n");
}

TEST_F(EmitRDFArrayTagTest_2107, EndTagAltNonEmpty_2107) {
    EmitRDFArrayTag(kXMP_PropArrayIsAlternate, output, "\n", "\t", 0, 5, false);
    EXPECT_EQ(output, "</rdf:Alt>\n");
}

// --- Boundary conditions ---

TEST_F(EmitRDFArrayTagTest_2107, StartTagBagEmptyArray_2107) {
    // When isStartTag=true and arraySize=0, should produce self-closing tag
    EmitRDFArrayTag(kXMP_PropArrayIsUnordered, output, "\n", "\t", 0, 0, true);
    EXPECT_EQ(output, "<rdf:Bag/>\n");
}

TEST_F(EmitRDFArrayTagTest_2107, StartTagSeqEmptyArray_2107) {
    EmitRDFArrayTag(kXMP_PropArrayIsOrdered, output, "\n", "\t", 0, 0, true);
    EXPECT_EQ(output, "<rdf:Seq/>\n");
}

TEST_F(EmitRDFArrayTagTest_2107, StartTagAltEmptyArray_2107) {
    EmitRDFArrayTag(kXMP_PropArrayIsAlternate, output, "\n", "\t", 0, 0, true);
    EXPECT_EQ(output, "<rdf:Alt/>\n");
}

TEST_F(EmitRDFArrayTagTest_2107, EndTagEmptyArrayReturnsEarly_2107) {
    // When isStartTag=false and arraySize=0, function should return immediately
    EmitRDFArrayTag(kXMP_PropArrayIsUnordered, output, "\n", "\t", 0, 0, false);
    EXPECT_EQ(output, "");
}

TEST_F(EmitRDFArrayTagTest_2107, EndTagSeqEmptyArrayReturnsEarly_2107) {
    EmitRDFArrayTag(kXMP_PropArrayIsOrdered, output, "\n", "\t", 0, 0, false);
    EXPECT_EQ(output, "");
}

TEST_F(EmitRDFArrayTagTest_2107, EndTagAltEmptyArrayReturnsEarly_2107) {
    EmitRDFArrayTag(kXMP_PropArrayIsAlternate, output, "\n", "\t", 0, 0, false);
    EXPECT_EQ(output, "");
}

// --- Indentation tests ---

TEST_F(EmitRDFArrayTagTest_2107, IndentLevel1_2107) {
    EmitRDFArrayTag(kXMP_PropArrayIsUnordered, output, "\n", "\t", 1, 3, true);
    EXPECT_EQ(output, "\t<rdf:Bag>\n");
}

TEST_F(EmitRDFArrayTagTest_2107, IndentLevel3_2107) {
    EmitRDFArrayTag(kXMP_PropArrayIsOrdered, output, "\n", "\t", 3, 3, true);
    EXPECT_EQ(output, "\t\t\t<rdf:Seq>\n");
}

TEST_F(EmitRDFArrayTagTest_2107, IndentLevel0_2107) {
    EmitRDFArrayTag(kXMP_PropArrayIsUnordered, output, "\n", "\t", 0, 3, true);
    EXPECT_EQ(output, "<rdf:Bag>\n");
}

TEST_F(EmitRDFArrayTagTest_2107, IndentWithSpaces_2107) {
    EmitRDFArrayTag(kXMP_PropArrayIsUnordered, output, "\n", "  ", 2, 3, true);
    EXPECT_EQ(output, "    <rdf:Bag>\n");
}

TEST_F(EmitRDFArrayTagTest_2107, IndentEndTag_2107) {
    EmitRDFArrayTag(kXMP_PropArrayIsUnordered, output, "\n", "\t", 2, 3, false);
    EXPECT_EQ(output, "\t\t</rdf:Bag>\n");
}

// --- Newline variations ---

TEST_F(EmitRDFArrayTagTest_2107, EmptyNewline_2107) {
    EmitRDFArrayTag(kXMP_PropArrayIsUnordered, output, "", "\t", 0, 3, true);
    EXPECT_EQ(output, "<rdf:Bag>");
}

TEST_F(EmitRDFArrayTagTest_2107, CRLFNewline_2107) {
    EmitRDFArrayTag(kXMP_PropArrayIsOrdered, output, "\r\n", "\t", 0, 3, true);
    EXPECT_EQ(output, "<rdf:Seq>\r\n");
}

// --- arrayForm with combined flags ---

TEST_F(EmitRDFArrayTagTest_2107, AlternateOverridesOrdered_2107) {
    // If both Alternate and Ordered are set, Alternate should win
    XMP_OptionBits combined = kXMP_PropArrayIsAlternate | kXMP_PropArrayIsOrdered;
    EmitRDFArrayTag(combined, output, "\n", "\t", 0, 3, true);
    EXPECT_EQ(output, "<rdf:Alt>\n");
}

TEST_F(EmitRDFArrayTagTest_2107, NoArrayFormBitsMeansBag_2107) {
    // If no array form bits are set, defaults to Bag
    EmitRDFArrayTag(0, output, "\n", "\t", 0, 3, true);
    EXPECT_EQ(output, "<rdf:Bag>\n");
}

// --- Append to existing output ---

TEST_F(EmitRDFArrayTagTest_2107, AppendsToExistingString_2107) {
    output = "existing content ";
    EmitRDFArrayTag(kXMP_PropArrayIsOrdered, output, "\n", "\t", 0, 1, true);
    EXPECT_EQ(output, "existing content <rdf:Seq>\n");
}

// --- Array size edge cases ---

TEST_F(EmitRDFArrayTagTest_2107, ArraySizeOne_2107) {
    EmitRDFArrayTag(kXMP_PropArrayIsUnordered, output, "\n", "\t", 0, 1, true);
    EXPECT_EQ(output, "<rdf:Bag>\n");
}

TEST_F(EmitRDFArrayTagTest_2107, ArraySizeLarge_2107) {
    EmitRDFArrayTag(kXMP_PropArrayIsAlternate, output, "\n", "\t", 0, 10000, true);
    EXPECT_EQ(output, "<rdf:Alt>\n");
}

TEST_F(EmitRDFArrayTagTest_2107, EndTagArraySizeOne_2107) {
    EmitRDFArrayTag(kXMP_PropArrayIsUnordered, output, "\n", "\t", 0, 1, false);
    EXPECT_EQ(output, "</rdf:Bag>\n");
}

// --- Empty indent string ---

TEST_F(EmitRDFArrayTagTest_2107, EmptyIndentString_2107) {
    EmitRDFArrayTag(kXMP_PropArrayIsOrdered, output, "\n", "", 5, 3, true);
    EXPECT_EQ(output, "<rdf:Seq>\n");
}

// --- Self-closing tag with indent ---

TEST_F(EmitRDFArrayTagTest_2107, SelfClosingWithIndent_2107) {
    EmitRDFArrayTag(kXMP_PropArrayIsAlternate, output, "\n", "\t", 2, 0, true);
    EXPECT_EQ(output, "\t\t<rdf:Alt/>\n");
}

// --- Combined test: multiple calls ---

TEST_F(EmitRDFArrayTagTest_2107, StartAndEndTagPair_2107) {
    EmitRDFArrayTag(kXMP_PropArrayIsOrdered, output, "\n", "\t", 1, 2, true);
    EmitRDFArrayTag(kXMP_PropArrayIsOrdered, output, "\n", "\t", 1, 2, false);
    EXPECT_EQ(output, "\t<rdf:Seq>\n\t</rdf:Seq>\n");
}
