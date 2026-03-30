#include <gtest/gtest.h>



// Assuming RDFTermKind and related constants are defined somewhere in the codebase.

// For the sake of completeness, let's define them here as they are not provided.



typedef unsigned char XMP_Uns8;

typedef XMP_Uns8 RDFTermKind;



const RDFTermKind kRDFTerm_FirstCore = 1;

const RDFTermKind kRDFTerm_LastCore = 10;



// Assuming the function IsCoreSyntaxTerm is part of a class or namespace.

// Since it's a static function, we'll assume it's in a namespace for this example.



namespace XMPMetadata {

    static bool IsCoreSyntaxTerm(RDFTermKind term) {

        if ((kRDFTerm_FirstCore <= term) && (term <= kRDFTerm_LastCore)) return true;

        return false;

    }

}



// Test suite for the IsCoreSyntaxTerm function.

class IsCoreSyntaxTermTest_2117 : public ::testing::Test {};



TEST_F(IsCoreSyntaxTermTest_2117, TermWithinRange_ReturnsTrue_2117) {

    EXPECT_TRUE(XMPMetadata::IsCoreSyntaxTerm(kRDFTerm_FirstCore));

    EXPECT_TRUE(XMPMetadata::IsCoreSyntaxTerm((kRDFTerm_FirstCore + kRDFTerm_LastCore) / 2));

    EXPECT_TRUE(XMPMetadata::IsCoreSyntaxTerm(kRDFTerm_LastCore));

}



TEST_F(IsCoreSyntaxTermTest_2117, TermBelowRange_ReturnsFalse_2117) {

    EXPECT_FALSE(XMPMetadata::IsCoreSyntaxTerm(kRDFTerm_FirstCore - 1));

    EXPECT_FALSE(XMPMetadata::IsCoreSyntaxTerm(0));

}



TEST_F(IsCoreSyntaxTermTest_2117, TermAboveRange_ReturnsFalse_2117) {

    EXPECT_FALSE(XMPMetadata::IsCoreSyntaxTerm(kRDFTerm_LastCore + 1));

    EXPECT_FALSE(XMPMetadata::IsCoreSyntaxTerm(255)); // Assuming XMP_Uns8 is an unsigned char

}



TEST_F(IsCoreSyntaxTermTest_2117, BoundaryTerms_ReturnsTrue_2117) {

    EXPECT_TRUE(XMPMetadata::IsCoreSyntaxTerm(kRDFTerm_FirstCore));

    EXPECT_TRUE(XMPMetadata::IsCoreSyntaxTerm(kRDFTerm_LastCore));

}
