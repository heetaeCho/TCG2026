#include <gtest/gtest.h>

#include "TestProjects/poppler/poppler/Object.h"



class RefRecursionCheckerRemoverTest : public ::testing::Test {

protected:

    RefRecursionChecker checker;

    Ref ref = 1; // Assuming Ref is an integer type for this test



    void SetUp() override {

        // Setup code, if any

    }



    void TearDown() override {

        // Teardown code, if any

    }

};



TEST_F(RefRecursionCheckerRemoverTest_62, ConstructorAddsToChecker_62) {

    RefRecursionCheckerRemover remover(checker, ref);

    EXPECT_TRUE(checker.insert(ref)); // Assuming insert returns false if the ref is already in the set

}



TEST_F(RefRecursionCheckerRemoverTest_62, DestructorRemovesFromChecker_62) {

    {

        RefRecursionCheckerRemover remover(checker, ref);

        EXPECT_FALSE(checker.insert(ref)); // Assuming insert returns false if the ref is already in the set

    }

    EXPECT_TRUE(checker.insert(ref)); // After destruction, the ref should be removed from the checker

}



TEST_F(RefRecursionCheckerRemoverTest_62, DoubleAdditionDoesNotAffectChecker_62) {

    RefRecursionCheckerRemover remover1(checker, ref);

    RefRecursionCheckerRemover remover2(checker, ref); // This should not add another reference to the checker

    EXPECT_FALSE(checker.insert(ref)); // Assuming insert returns false if the ref is already in the set

}



TEST_F(RefRecursionCheckerRemoverTest_62, DifferentRefsDoNotInterfere_62) {

    Ref ref1 = 1;

    Ref ref2 = 2;



    RefRecursionCheckerRemover remover1(checker, ref1);

    RefRecursionCheckerRemover remover2(checker, ref2);



    EXPECT_FALSE(checker.insert(ref1)); // Assuming insert returns false if the ref is already in the set

    EXPECT_FALSE(checker.insert(ref2)); // Assuming insert returns false if the ref is already in the set



    {

        RefRecursionCheckerRemover remover3(checker, ref1);

    }



    EXPECT_TRUE(checker.insert(ref1));  // After destruction of remover3, ref1 should be removed

    EXPECT_FALSE(checker.insert(ref2)); // ref2 should still not be insertable

}



TEST_F(RefRecursionCheckerRemoverTest_62, DeleteCopyConstructorIsDisabled_62) {

    RefRecursionCheckerRemover remover(checker, ref);

    RefRecursionCheckerRemover* copy = nullptr;

    EXPECT_DEATH(copy = new RefRecursionCheckerRemover(remover), "");

}



TEST_F(RefRecursionCheckerRemoverTest_62, DeleteAssignmentOperatorIsDisabled_62) {

    RefRecursionCheckerRemover remover1(checker, ref);

    RefRecursionCheckerRemover remover2(checker, ref + 1);



    EXPECT_DEATH(remover2 = remover1, "");

}
