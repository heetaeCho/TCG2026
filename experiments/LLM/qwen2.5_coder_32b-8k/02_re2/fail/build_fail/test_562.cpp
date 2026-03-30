#include <gtest/gtest.h>

#include "prefilter.h"



using namespace re2;



class PrefilterTest_562 : public ::testing::Test {

protected:

    void SetUp() override {

        // Setup can be used to initialize objects if needed

    }



    void TearDown() override {

        // Cleanup can be done here if needed

    }

};



TEST_F(PrefilterTest_562, DebugString_NoneOp_562) {

    Prefilter prefilter(static_cast<Op>(NONE));

    EXPECT_EQ(prefilter.DebugString(), "*no-matches*");

}



TEST_F(PrefilterTest_562, DebugString_AtomOp_562) {

    Prefilter prefilter(static_cast<Op>(ATOM));

    prefilter.set_subs(new std::vector<Prefilter*>());

    prefilter.set_unique_id(1);

    prefilter.atom_ = "test_atom";

    EXPECT_EQ(prefilter.DebugString(), "test_atom");

}



TEST_F(PrefilterTest_562, DebugString_AllOp_562) {

    Prefilter prefilter(static_cast<Op>(ALL));

    EXPECT_EQ(prefilter.DebugString(), "");

}



TEST_F(PrefilterTest_562, DebugString_AndOp_NoSubs_562) {

    Prefilter prefilter(static_cast<Op>(AND));

    prefilter.set_subs(new std::vector<Prefilter*>());

    EXPECT_EQ(prefilter.DebugString(), "");

}



TEST_F(PrefilterTest_562, DebugString_AndOp_OneSub_562) {

    Prefilter subfilter(static_cast<Op>(ATOM));

    subfilter.atom_ = "sub_atom";

    

    std::vector<Prefilter*> subs;

    subs.push_back(&subfilter);

    Prefilter prefilter(static_cast<Op>(AND));

    prefilter.set_subs(new std::vector<Prefilter*>(subs));



    EXPECT_EQ(prefilter.DebugString(), "sub_atom");

}



TEST_F(PrefilterTest_562, DebugString_AndOp_MultipleSubs_562) {

    Prefilter subfilter1(static_cast<Op>(ATOM));

    subfilter1.atom_ = "sub_atom1";

    

    Prefilter subfilter2(static_cast<Op>(ATOM));

    subfilter2.atom_ = "sub_atom2";



    std::vector<Prefilter*> subs;

    subs.push_back(&subfilter1);

    subs.push_back(&subfilter2);



    Prefilter prefilter(static_cast<Op>(AND));

    prefilter.set_subs(new std::vector<Prefilter*>(subs));



    EXPECT_EQ(prefilter.DebugString(), "sub_atom1 sub_atom2");

}



TEST_F(PrefilterTest_562, DebugString_AndOp_NilSub_562) {

    Prefilter subfilter(static_cast<Op>(ATOM));

    subfilter.atom_ = "sub_atom";

    

    std::vector<Prefilter*> subs;

    subs.push_back(&subfilter);

    subs.push_back(nullptr);



    Prefilter prefilter(static_cast<Op>(AND));

    prefilter.set_subs(new std::vector<Prefilter*>(subs));



    EXPECT_EQ(prefilter.DebugString(), "sub_atom <nil>");

}



TEST_F(PrefilterTest_562, DebugString_OrOp_NoSubs_562) {

    Prefilter prefilter(static_cast<Op>(OR));

    prefilter.set_subs(new std::vector<Prefilter*>());

    EXPECT_EQ(prefilter.DebugString(), "()");

}



TEST_F(PrefilterTest_562, DebugString_OrOp_OneSub_562) {

    Prefilter subfilter(static_cast<Op>(ATOM));

    subfilter.atom_ = "sub_atom";

    

    std::vector<Prefilter*> subs;

    subs.push_back(&subfilter);



    Prefilter prefilter(static_cast<Op>(OR));

    prefilter.set_subs(new std::vector<Prefilter*>(subs));



    EXPECT_EQ(prefilter.DebugString(), "(sub_atom)");

}



TEST_F(PrefilterTest_562, DebugString_OrOp_MultipleSubs_562) {

    Prefilter subfilter1(static_cast<Op>(ATOM));

    subfilter1.atom_ = "sub_atom1";

    

    Prefilter subfilter2(static_cast<Op>(ATOM));

    subfilter2.atom_ = "sub_atom2";



    std::vector<Prefilter*> subs;

    subs.push_back(&subfilter1);

    subs.push_back(&subfilter2);



    Prefilter prefilter(static_cast<Op>(OR));

    prefilter.set_subs(new std::vector<Prefilter*>(subs));



    EXPECT_EQ(prefilter.DebugString(), "(sub_atom1|sub_atom2)");

}



TEST_F(PrefilterTest_562, DebugString_OrOp_NilSub_562) {

    Prefilter subfilter(static_cast<Op>(ATOM));

    subfilter.atom_ = "sub_atom";

    

    std::vector<Prefilter*> subs;

    subs.push_back(&subfilter);

    subs.push_back(nullptr);



    Prefilter prefilter(static_cast<Op>(OR));

    prefilter.set_subs(new std::vector<Prefilter*>(subs));



    EXPECT_EQ(prefilter.DebugString(), "(sub_atom|<nil>)");

}



TEST_F(PrefilterTest_562, DebugString_InvalidOp_562) {

    Prefilter prefilter(static_cast<Op>(-1));

    EXPECT_DEATH(prefilter.DebugString(), "Bad op in DebugString: -1");

}
