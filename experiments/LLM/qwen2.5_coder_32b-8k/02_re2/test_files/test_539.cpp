#include <gtest/gtest.h>

#include "prefilter.cc"



using namespace re2;



class PrefilterInfoTest : public ::testing::Test {

protected:

    Prefilter::Info* info;



    void SetUp() override {

        info = new Prefilter::Info();

    }



    void TearDown() override {

        delete info;

    }

};



TEST_F(PrefilterInfoTest_539, InitialStateIsExactFalse_539) {

    EXPECT_FALSE(info->is_exact());

}



TEST_F(PrefilterInfoTest_539, ExactReturnsReferenceToSSet_539) {

    SSet& exact_set = info->exact();

    // We cannot verify the contents but we can check if it's accessible.

    EXPECT_TRUE(&exact_set != nullptr);

}



TEST_F(PrefilterInfoTest_539, TakeMatchReturnsNullPointerInitially_539) {

    EXPECT_EQ(info->TakeMatch(), nullptr);

}



// Boundary conditions for static methods

TEST_F(PrefilterInfoTest_539, AltWithTwoInfosDoesNotCrash_539) {

    Prefilter::Info* a = new Prefilter::Info();

    Prefilter::Info* b = new Prefilter::Info();

    EXPECT_NO_THROW(Prefilter::Info::Alt(a, b));

    delete a;

    delete b;

}



TEST_F(PrefilterInfoTest_539, ConcatWithTwoInfosDoesNotCrash_539) {

    Prefilter::Info* a = new Prefilter::Info();

    Prefilter::Info* b = new Prefilter::Info();

    EXPECT_NO_THROW(Prefilter::Info::Concat(a, b));

    delete a;

    delete b;

}



TEST_F(PrefilterInfoTest_539, AndWithTwoInfosDoesNotCrash_539) {

    Prefilter::Info* a = new Prefilter::Info();

    Prefilter::Info* b = new Prefilter::Info();

    EXPECT_NO_THROW(Prefilter::Info::And(a, b));

    delete a;

    delete b;

}



TEST_F(PrefilterInfoTest_539, StarWithOneInfoDoesNotCrash_539) {

    Prefilter::Info* a = new Prefilter::Info();

    EXPECT_NO_THROW(Prefilter::Info::Star(a));

    delete a;

}



TEST_F(PrefilterInfoTest_539, PlusWithOneInfoDoesNotCrash_539) {

    Prefilter::Info* a = new Prefilter::Info();

    EXPECT_NO_THROW(Prefilter::Info::Plus(a));

    delete a;

}



TEST_F(PrefilterInfoTest_539, QuestWithOneInfoDoesNotCrash_539) {

    Prefilter::Info* a = new Prefilter::Info();

    EXPECT_NO_THROW(Prefilter::Info::Quest(a));

    delete a;

}



TEST_F(PrefilterInfoTest_539, EmptyStringStaticMethodReturnsValidPtr_539) {

    EXPECT_NE(Prefilter::Info::EmptyString(), nullptr);

}



TEST_F(PrefilterInfoTest_539, NoMatchStaticMethodReturnsValidPtr_539) {

    EXPECT_NE(Prefilter::Info::NoMatch(), nullptr);

}



TEST_F(PrefilterInfoTest_539, AnyCharOrAnyByteStaticMethodReturnsValidPtr_539) {

    EXPECT_NE(Prefilter::Info::AnyCharOrAnyByte(), nullptr);

}



TEST_F(PrefilterInfoTest_539, CClassWithNullPointerDoesNotCrash_539) {

    EXPECT_NO_THROW(Prefilter::Info::CClass(nullptr, false));

}



TEST_F(PrefilterInfoTest_539, LiteralStaticMethodReturnsValidPtr_539) {

    Rune r = 0;

    EXPECT_NE(Prefilter::Info::Literal(r), nullptr);

}



TEST_F(PrefilterInfoTest_539, LiteralLatin1StaticMethodReturnsValidPtr_539) {

    Rune r = 0;

    EXPECT_NE(Prefilter::Info::LiteralLatin1(r), nullptr);

}



TEST_F(PrefilterInfoTest_539, AnyMatchStaticMethodReturnsValidPtr_539) {

    EXPECT_NE(Prefilter::Info::AnyMatch(), nullptr);

}
