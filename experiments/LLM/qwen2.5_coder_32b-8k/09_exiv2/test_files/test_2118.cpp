#include <gtest/gtest.h>



// Assuming RDFTermKind is an enumeration or a type that can be compared with integers.

enum RDFTermKind {

    kRDFTerm_FirstOld = 1,

    kRDFTerm_SomeOldTerm = 2,

    kRDFTerm_LastOld = 3,

    kRDFTerm_NewTerm = 4

};



// Assuming the function IsOldTerm is part of a class or namespace, I'll assume it's in a global scope for simplicity.

extern bool IsOldTerm(RDFTermKind term);



class ParseRDFTest_2118 : public ::testing::Test {

protected:

    // Additional setup if needed can be done here

};



TEST_F(ParseRDFTest_2118, IsOldTerm_ReturnsTrueForFirstOld_2118) {

    EXPECT_TRUE(IsOldTerm(kRDFTerm_FirstOld));

}



TEST_F(ParseRDFTest_2118, IsOldTerm_ReturnsTrueForLastOld_2118) {

    EXPECT_TRUE(IsOldTerm(kRDFTerm_LastOld));

}



TEST_F(ParseRDFTest_2118, IsOldTerm_ReturnsTrueForMiddleOld_2118) {

    EXPECT_TRUE(IsOldTerm(kRDFTerm_SomeOldTerm));

}



TEST_F(ParseRDFTest_2118, IsOldTerm_ReturnsFalseForNewTerm_2118) {

    EXPECT_FALSE(IsOldTerm(kRDFTerm_NewTerm));

}



TEST_F(ParseRDFTest_2118, IsOldTerm_ReturnsFalseForBelowRange_2118) {

    EXPECT_FALSE(IsOldTerm(static_cast<RDFTermKind>(kRDFTerm_FirstOld - 1)));

}



TEST_F(ParseRDFTest_2118, IsOldTerm_ReturnsFalseForAboveRange_2118) {

    EXPECT_FALSE(IsOldTerm(static_cast<RDFTermKind>(kRDFTerm_LastOld + 1)));

}
