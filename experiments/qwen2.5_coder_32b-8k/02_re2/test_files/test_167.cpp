#include <gtest/gtest.h>

#include "re2/regexp.h"

#include <set>



using namespace re2;



class CharClassBuilderTest_167 : public ::testing::Test {

protected:

    CharClassBuilder *builder;

    

    void SetUp() override {

        builder = new CharClassBuilder();

    }

    

    void TearDown() override {

        delete builder;

    }

};



TEST_F(CharClassBuilderTest_167, InitialStateNotFull_167) {

    EXPECT_FALSE(builder->full());

}



TEST_F(CharClassBuilderTest_167, AddRangeWithinLimit_167) {

    EXPECT_TRUE(builder->AddRange(0, 10));

    EXPECT_FALSE(builder->full());

}



TEST_F(CharClassBuilderTest_167, AddRangeUpToFull_167) {

    for (Rune i = 0; i < Runemax; ++i) {

        builder->AddRange(i, i);

    }

    builder->AddRange(Runemax, Runemax);

    EXPECT_TRUE(builder->full());

}



TEST_F(CharClassBuilderTest_167, AddRangeBeyondFull_167) {

    for (Rune i = 0; i < Runemax; ++i) {

        builder->AddRange(i, i);

    }

    builder->AddRange(Runemax, Runemax);

    EXPECT_FALSE(builder->AddRange(Runemax + 1, Runemax + 1));

}



TEST_F(CharClassBuilderTest_167, AddCharClassNotFull_167) {

    CharClassBuilder other;

    other.AddRange(0, 10);

    builder->AddCharClass(&other);

    EXPECT_FALSE(builder->full());

}



TEST_F(CharClassBuilderTest_167, RemoveAboveNotFull_167) {

    builder->AddRange(0, Runemax - 1);

    builder->RemoveAbove(Runemax - 1);

    EXPECT_FALSE(builder->full());

}



TEST_F(CharClassBuilderTest_167, NegateDoesNotChangeFull_167) {

    for (Rune i = 0; i < Runemax; ++i) {

        builder->AddRange(i, i);

    }

    builder->Negate();

    EXPECT_TRUE(builder->full());

}



TEST_F(CharClassBuilderTest_167, GetCharClassNotNull_167) {

    EXPECT_NE(builder->GetCharClass(), nullptr);

}



TEST_F(CharClassBuilderTest_167, AddRangeFlagsNotFull_167) {

    builder->AddRangeFlags(0, 10, Regexp::ParseFlags());

    EXPECT_FALSE(builder->full());

}
