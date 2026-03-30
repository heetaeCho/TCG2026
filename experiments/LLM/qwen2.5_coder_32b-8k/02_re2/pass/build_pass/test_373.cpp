#include <gtest/gtest.h>

#include "regexp.h"



using namespace re2;



class CharClassBuilderTest_373 : public ::testing::Test {

protected:

    CharClassBuilder builder;

};



TEST_F(CharClassBuilderTest_373, FoldsASCIINormalOperation_373) {

    EXPECT_TRUE(builder.FoldsASCII());

}



TEST_F(CharClassBuilderTest_373, AddRangeNormalOperation_373) {

    EXPECT_TRUE(builder.AddRange(65, 90)); // A-Z

    EXPECT_TRUE(builder.AddRange(97, 122)); // a-z

}



TEST_F(CharClassBuilderTest_373, FoldsASCIIBoundaryCondition_373) {

    builder.AddRange(65, 90); // A-Z

    builder.AddRange(97, 122); // a-z

    EXPECT_TRUE(builder.FoldsASCII());

}



TEST_F(CharClassBuilderTest_373, AddRangeBoundaryCondition_373) {

    EXPECT_FALSE(builder.AddRange(0, 0)); // Empty range

    EXPECT_TRUE(builder.AddRange(65, 65)); // Single character

}



// Assuming Contains is observable through some means, otherwise it's not testable directly.

// If there was a way to verify contents, we could add more tests for Contains.



TEST_F(CharClassBuilderTest_373, NegateNormalOperation_373) {

    builder.AddRange(65, 90); // A-Z

    builder.Negate();

}



TEST_F(CharClassBuilderTest_373, RemoveAboveNormalOperation_373) {

    builder.AddRange(65, 122); // A-z

    builder.RemoveAbove(90);   // Remove a-z

}



// Assuming GetCharClass returns some observable state, otherwise it's not testable directly.

// If there was a way to verify the returned CharClass, we could add more tests for GetCharClass.



TEST_F(CharClassBuilderTest_373, CopyNormalOperation_373) {

    builder.AddRange(65, 90); // A-Z

    CharClassBuilder* copy = builder.Copy();

    EXPECT_NE(copy, nullptr);

    delete copy;

}



// Assuming AddCharClass merges another CharClassBuilder, otherwise it's not testable directly.

// If there was a way to verify the merged contents, we could add more tests for AddCharClass.



TEST_F(CharClassBuilderTest_373, FullBoundaryCondition_373) {

    // Fill the builder with all possible runes

    // This is just a placeholder as the actual range of Rune is not specified.

    // For demonstration, assuming Rune is within 0 to 127 (ASCII).

    for (int i = 0; i <= 127; ++i) {

        builder.AddRange(i, i);

    }

    EXPECT_TRUE(builder.full());

}



TEST_F(CharClassBuilderTest_373, EmptyBoundaryCondition_373) {

    EXPECT_TRUE(builder.empty());

}
