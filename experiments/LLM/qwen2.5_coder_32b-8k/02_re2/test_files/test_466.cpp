#include <gtest/gtest.h>

#include "prefilter.h"

#include <vector>



using namespace re2;



class PrefilterTest_466 : public ::testing::Test {

protected:

    void SetUp() override {

        // Setup any common objects or states here if needed.

    }



    void TearDown() override {

        // Cleanup any resources or states here if needed.

    }

};



TEST_F(PrefilterTest_466, Constructor_AllOp_466) {

    Prefilter prefilter(Op::ALL);

    EXPECT_EQ(prefilter.op(), Op::ALL);

}



TEST_F(PrefilterTest_466, Constructor_NoneOp_466) {

    Prefilter prefilter(Op::NONE);

    EXPECT_EQ(prefilter.op(), Op::NONE);

}



TEST_F(PrefilterTest_466, Constructor_AtomOp_466) {

    Prefilter prefilter(Op::ATOM);

    EXPECT_EQ(prefilter.op(), Op::ATOM);

}



TEST_F(PrefilterTest_466, Constructor_AndOp_466) {

    Prefilter prefilter(Op::AND);

    EXPECT_EQ(prefilter.op(), Op::AND);

}



TEST_F(PrefilterTest_466, Constructor_OrOp_466) {

    Prefilter prefilter(Op::OR);

    EXPECT_EQ(prefilter.op(), Op::OR);

}



TEST_F(PrefilterTest_466, SetAndGetUniqueId_466) {

    Prefilter prefilter(Op::ATOM);

    int id = 123;

    prefilter.set_unique_id(id);

    EXPECT_EQ(prefilter.unique_id(), id);

}



TEST_F(PrefilterTest_466, SetAndGetSubs_466) {

    Prefilter prefilter(Op::AND);

    std::vector<Prefilter*> subs = {new Prefilter(Op::ATOM), new Prefilter(Op::NONE)};

    prefilter.set_subs(&subs);

    EXPECT_EQ(prefilter.subs(), &subs);

    for (auto sub : subs) {

        delete sub;

    }

}



TEST_F(PrefilterTest_466, AtomAccess_466) {

    Prefilter prefilter(Op::ATOM);

    std::string atom = "test_atom";

    prefilter.set_subs(new std::vector<Prefilter*>{});

    prefilter.atom_ = atom; // Direct assignment for test purposes

    EXPECT_EQ(prefilter.atom(), atom);

}



TEST_F(PrefilterTest_466, DebugString_AllOp_466) {

    Prefilter prefilter(Op::ALL);

    std::string expected_debug_string = "ALL";

    EXPECT_EQ(prefilter.DebugString(), expected_debug_string);

}



TEST_F(PrefilterTest_466, DebugString_NoneOp_466) {

    Prefilter prefilter(Op::NONE);

    std::string expected_debug_string = "NONE";

    EXPECT_EQ(prefilter.DebugString(), expected_debug_string);

}



TEST_F(PrefilterTest_466, DebugString_AtomOp_466) {

    Prefilter prefilter(Op::ATOM);

    std::string atom = "test_atom";

    prefilter.set_subs(new std::vector<Prefilter*>{});

    prefilter.atom_ = atom; // Direct assignment for test purposes

    std::string expected_debug_string = "ATOM(test_atom)";

    EXPECT_EQ(prefilter.DebugString(), expected_debug_string);

}



TEST_F(PrefilterTest_466, DebugString_AndOp_NoSubs_466) {

    Prefilter prefilter(Op::AND);

    std::string expected_debug_string = "AND()";

    EXPECT_EQ(prefilter.DebugString(), expected_debug_string);

}



TEST_F(PrefilterTest_466, DebugString_OrOp_NoSubs_466) {

    Prefilter prefilter(Op::OR);

    std::string expected_debug_string = "OR()";

    EXPECT_EQ(prefilter.DebugString(), expected_debug_string);

}



TEST_F(PrefilterTest_466, DebugString_AndOp_WithSubs_466) {

    Prefilter prefilter(Op::AND);

    std::vector<Prefilter*> subs = {new Prefilter(Op::ATOM), new Prefilter(Op::NONE)};

    subs[0]->set_subs(new std::vector<Prefilter*>{});

    subs[0]->atom_ = "test_atom"; // Direct assignment for test purposes

    subs[1]->set_subs(new std::vector<Prefilter*>{});

    prefilter.set_subs(&subs);

    std::string expected_debug_string = "AND(ATOM(test_atom), NONE)";

    EXPECT_EQ(prefilter.DebugString(), expected_debug_string);

    for (auto sub : subs) {

        delete sub;

    }

}



TEST_F(PrefilterTest_466, DebugString_OrOp_WithSubs_466) {

    Prefilter prefilter(Op::OR);

    std::vector<Prefilter*> subs = {new Prefilter(Op::ATOM), new Prefilter(Op::NONE)};

    subs[0]->set_subs(new std::vector<Prefilter*>{});

    subs[0]->atom_ = "test_atom"; // Direct assignment for test purposes

    subs[1]->set_subs(new std::vector<Prefilter*>{});

    prefilter.set_subs(&subs);

    std::string expected_debug_string = "OR(ATOM(test_atom), NONE)";

    EXPECT_EQ(prefilter.DebugString(), expected_debug_string);

    for (auto sub : subs) {

        delete sub;

    }

}



TEST_F(PrefilterTest_466, EqualityOperator_SameObject_466) {

    Prefilter prefilter(Op::ALL);

    EXPECT_TRUE(prefilter == prefilter);

}



TEST_F(PrefilterTest_466, EqualityOperator_DifferentOp_466) {

    Prefilter prefilter1(Op::ALL);

    Prefilter prefilter2(Op::NONE);

    EXPECT_FALSE(prefilter1 == prefilter2);

}



TEST_F(PrefilterTest_466, EqualityOperator_SameAtom_466) {

    Prefilter prefilter1(Op::ATOM);

    Prefilter prefilter2(Op::ATOM);

    prefilter1.set_subs(new std::vector<Prefilter*>{});

    prefilter2.set_subs(new std::vector<Prefilter*>{});

    prefilter1.atom_ = "test_atom"; // Direct assignment for test purposes

    prefilter2.atom_ = "test_atom"; // Direct assignment for test purposes

    EXPECT_TRUE(prefilter1 == prefilter2);

}



TEST_F(PrefilterTest_466, EqualityOperator_DifferentAtom_466) {

    Prefilter prefilter1(Op::ATOM);

    Prefilter prefilter2(Op::ATOM);

    prefilter1.set_subs(new std::vector<Prefilter*>{});

    prefilter2.set_subs(new std::vector<Prefilter*>{});

    prefilter1.atom_ = "test_atom"; // Direct assignment for test purposes

    prefilter2.atom_ = "different_atom"; // Direct assignment for test purposes

    EXPECT_FALSE(prefilter1 == prefilter2);

}



TEST_F(PrefilterTest_466, EqualityOperator_SameSubs_466) {

    Prefilter prefilter1(Op::AND);

    Prefilter prefilter2(Op::AND);

    std::vector<Prefilter*> subs1 = {new Prefilter(Op::ATOM), new Prefilter(Op::NONE)};

    std::vector<Prefilter*> subs2 = {new Prefilter(Op::ATOM), new Prefilter(Op::NONE)};

    subs1[0]->set_subs(new std::vector<Prefilter*>{});

    subs1[0]->atom_ = "test_atom"; // Direct assignment for test purposes

    subs1[1]->set_subs(new std::vector<Prefilter*>{}); 

    subs2[0]->set_subs(new std::vector<Prefilter*>{});

    subs2[0]->atom_ = "test_atom"; // Direct assignment for test purposes

    subs2[1]->set_subs(new std::vector<Prefilter*>{}); 



    prefilter1.set_subs(&subs1);

    prefilter2.set_subs(&subs2);



    EXPECT_TRUE(prefilter1 == prefilter2);



    for (auto sub : subs1) {

        delete sub;

    }

    for (auto sub : subs2) {

        delete sub;

    }

}



TEST_F(PrefilterTest_466, EqualityOperator_DifferentSubsCount_466) {

    Prefilter prefilter1(Op::AND);

    Prefilter prefilter2(Op::AND);

    std::vector<Prefilter*> subs1 = {new Prefilter(Op::ATOM)};

    std::vector<Prefilter*> subs2 = {new Prefilter(Op::ATOM), new Prefilter(Op::NONE)};



    prefilter1.set_subs(&subs1);

    prefilter2.set_subs(&subs2);



    EXPECT_FALSE(prefilter1 == prefilter2);



    for (auto sub : subs1) {

        delete sub;

    }

    for (auto sub : subs2) {

        delete sub;

    }

}



TEST_F(PrefilterTest_466, EqualityOperator_DifferentSubsUniqueIds_466) {

    Prefilter prefilter1(Op::AND);

    Prefilter prefilter2(Op::AND);



    std::vector<Prefilter*> subs1 = {new Prefilter(Op::ATOM), new Prefilter(Op::NONE)};

    std::vector<Prefilter*> subs2 = {new Prefilter(Op::ATOM), new Prefilter(Op::NONE)};



    subs1[0]->set_subs(new std::vector<Prefilter*>{});

    subs1[1]->set_subs(new std::vector<Prefilter*>{});



    subs2[0]->set_subs(new std::vector<Prefilter*>{});

    subs2[0]->atom_ = "test_atom"; // Direct assignment for test purposes

    subs2[1]->set_subs(new std::vector<Prefilter*>{}); 



    subs1[0]->set_unique_id(1);

    subs1[1]->set_unique_id(2);



    subs2[0]->set_unique_id(3);

    subs2[1]->set_unique_id(4);



    prefilter1.set_subs(&subs1);

    prefilter2.set_subs(&subs2);



    EXPECT_FALSE(prefilter1 == prefilter2);



    for (auto sub : subs1) {

        delete sub;

    }

    for (auto sub : subs2) {

        delete sub;

    }

}
