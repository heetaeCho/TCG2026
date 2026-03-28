#include <gtest/gtest.h>
#include "Object.h"

// Test fixture for RefRecursionCheckerRemover
class RefRecursionCheckerRemoverTest_62 : public ::testing::Test {
protected:
    RefRecursionChecker checker;
};

// Test that the destructor removes the ref from the checker
TEST_F(RefRecursionCheckerRemoverTest_62, DestructorRemovesRef_62) {
    Ref ref = {1, 0};
    
    // Insert a ref into the checker
    EXPECT_TRUE(checker.insert(ref));
    
    // Inserting the same ref again should return false (already present)
    EXPECT_FALSE(checker.insert(ref));
    
    // Create a remover in a nested scope; when it goes out of scope,
    // the destructor should remove the ref
    {
        RefRecursionCheckerRemover remover(checker, ref);
    }
    
    // After the remover's destructor ran, inserting the same ref should succeed again
    EXPECT_TRUE(checker.insert(ref));
}

// Test that RefRecursionCheckerRemover works with multiple refs
TEST_F(RefRecursionCheckerRemoverTest_62, MultipleRefsRemoval_62) {
    Ref ref1 = {1, 0};
    Ref ref2 = {2, 0};
    
    EXPECT_TRUE(checker.insert(ref1));
    EXPECT_TRUE(checker.insert(ref2));
    
    // Only remove ref1 via the remover
    {
        RefRecursionCheckerRemover remover(checker, ref1);
    }
    
    // ref1 should be removed, so insert should succeed
    EXPECT_TRUE(checker.insert(ref1));
    
    // ref2 should still be present, so insert should fail
    EXPECT_FALSE(checker.insert(ref2));
}

// Test that the remover correctly handles the ref it was constructed with
TEST_F(RefRecursionCheckerRemoverTest_62, RemoverOnlyRemovesItsOwnRef_62) {
    Ref ref1 = {10, 0};
    Ref ref2 = {20, 0};
    
    EXPECT_TRUE(checker.insert(ref1));
    EXPECT_TRUE(checker.insert(ref2));
    
    {
        RefRecursionCheckerRemover remover1(checker, ref1);
        RefRecursionCheckerRemover remover2(checker, ref2);
        
        // Both refs should still be in the checker (not yet removed)
        EXPECT_FALSE(checker.insert(ref1));
        EXPECT_FALSE(checker.insert(ref2));
    }
    // Both removers destroyed, both refs should be removable now
    
    EXPECT_TRUE(checker.insert(ref1));
    EXPECT_TRUE(checker.insert(ref2));
}

// Test nested scopes with removers
TEST_F(RefRecursionCheckerRemoverTest_62, NestedScopeRemoval_62) {
    Ref ref1 = {5, 0};
    Ref ref2 = {6, 0};
    
    EXPECT_TRUE(checker.insert(ref1));
    
    {
        RefRecursionCheckerRemover remover1(checker, ref1);
        
        EXPECT_TRUE(checker.insert(ref2));
        
        {
            RefRecursionCheckerRemover remover2(checker, ref2);
            
            // Both should be present
            EXPECT_FALSE(checker.insert(ref1));
            EXPECT_FALSE(checker.insert(ref2));
        }
        
        // ref2 removed, ref1 still present
        EXPECT_TRUE(checker.insert(ref2));
        EXPECT_FALSE(checker.insert(ref1));
        
        // Clean up ref2 we just re-inserted
        checker.remove(ref2);
    }
    
    // ref1 should now be removed
    EXPECT_TRUE(checker.insert(ref1));
}

// Test that removing a ref that was never inserted doesn't cause issues
TEST_F(RefRecursionCheckerRemoverTest_62, RemoveNonExistentRef_62) {
    Ref ref = {99, 0};
    
    // The ref was never inserted; creating a remover that will try to remove it
    {
        RefRecursionCheckerRemover remover(checker, ref);
    }
    
    // Should still be able to insert it
    EXPECT_TRUE(checker.insert(ref));
}

// Test with zero-valued ref
TEST_F(RefRecursionCheckerRemoverTest_62, ZeroRef_62) {
    Ref ref = {0, 0};
    
    EXPECT_TRUE(checker.insert(ref));
    EXPECT_FALSE(checker.insert(ref));
    
    {
        RefRecursionCheckerRemover remover(checker, ref);
    }
    
    EXPECT_TRUE(checker.insert(ref));
}

// Test with negative ref num
TEST_F(RefRecursionCheckerRemoverTest_62, NegativeRefNum_62) {
    Ref ref = {-1, 0};
    
    EXPECT_TRUE(checker.insert(ref));
    EXPECT_FALSE(checker.insert(ref));
    
    {
        RefRecursionCheckerRemover remover(checker, ref);
    }
    
    EXPECT_TRUE(checker.insert(ref));
}

// Test RefRecursionChecker basic functionality
class RefRecursionCheckerTest_62 : public ::testing::Test {
protected:
    RefRecursionChecker checker;
};

TEST_F(RefRecursionCheckerTest_62, InsertReturnsTrueForNewRef_62) {
    Ref ref = {1, 0};
    EXPECT_TRUE(checker.insert(ref));
}

TEST_F(RefRecursionCheckerTest_62, InsertReturnsFalseForDuplicate_62) {
    Ref ref = {1, 0};
    EXPECT_TRUE(checker.insert(ref));
    EXPECT_FALSE(checker.insert(ref));
}

TEST_F(RefRecursionCheckerTest_62, RemoveAllowsReinsert_62) {
    Ref ref = {1, 0};
    EXPECT_TRUE(checker.insert(ref));
    checker.remove(ref);
    EXPECT_TRUE(checker.insert(ref));
}

TEST_F(RefRecursionCheckerTest_62, DifferentRefsAreIndependent_62) {
    Ref ref1 = {1, 0};
    Ref ref2 = {2, 0};
    
    EXPECT_TRUE(checker.insert(ref1));
    EXPECT_TRUE(checker.insert(ref2));
    
    EXPECT_FALSE(checker.insert(ref1));
    EXPECT_FALSE(checker.insert(ref2));
}
