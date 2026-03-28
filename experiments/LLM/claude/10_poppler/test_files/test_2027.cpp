#include <gtest/gtest.h>
#include <memory>
#include "Object.h"
#include "Dict.h"

// The function under test is static in Annot.cc, so we need to include it
// or declare it. Since it's static, we include the implementation.
// We need a way to call recursiveMergeDicts. Since it's static, we may need
// to either make it accessible or test it indirectly.

// For testing purposes, we replicate the function signature and include the source.
// In practice, this would be exposed through a test helper or the static keyword removed.

// Forward declare / include necessary headers
#include "Annot.h"

// Since recursiveMergeDicts is static in Annot.cc, we need to include the .cc
// to access it in tests, or we use a workaround.
// We'll define a wrapper that matches the static function.

// Include the actual implementation to get access to the static function
namespace {
#include "Annot.cc"
}

class RecursiveMergeDictsTest_2027 : public ::testing::Test {
protected:
    void SetUp() override {
        // XRef can be nullptr for basic dict operations in many poppler builds
        xref = nullptr;
    }

    XRef *xref;

    Dict *createDict() {
        return new Dict(xref);
    }
};

// Test: Keys in secondary but not in primary are added to primary
TEST_F(RecursiveMergeDictsTest_2027, SecondaryKeysAddedToPrimary_2027) {
    Dict *primary = createDict();
    Dict *secondary = createDict();

    secondary->add("Key1", Object(42));
    secondary->add("Key2", Object(3.14));

    RefRecursionChecker checker;
    recursiveMergeDicts(primary, secondary, &checker);

    // Key1 and Key2 should now be in primary
    EXPECT_TRUE(primary->hasKey("Key1"));
    EXPECT_TRUE(primary->hasKey("Key2"));

    Object val1 = primary->lookup("Key1");
    ASSERT_TRUE(val1.isInt());
    EXPECT_EQ(val1.getInt(), 42);

    Object val2 = primary->lookup("Key2");
    ASSERT_TRUE(val2.isReal());
    EXPECT_DOUBLE_EQ(val2.getReal(), 3.14);

    delete primary;
    delete secondary;
}

// Test: Keys already in primary are NOT overwritten by secondary
TEST_F(RecursiveMergeDictsTest_2027, ExistingKeysNotOverwritten_2027) {
    Dict *primary = createDict();
    Dict *secondary = createDict();

    primary->add("Key1", Object(100));
    secondary->add("Key1", Object(200));

    RefRecursionChecker checker;
    recursiveMergeDicts(primary, secondary, &checker);

    Object val = primary->lookup("Key1");
    ASSERT_TRUE(val.isInt());
    EXPECT_EQ(val.getInt(), 100);

    delete primary;
    delete secondary;
}

// Test: Empty secondary dict causes no changes to primary
TEST_F(RecursiveMergeDictsTest_2027, EmptySecondaryNoChange_2027) {
    Dict *primary = createDict();
    Dict *secondary = createDict();

    primary->add("Key1", Object(42));

    RefRecursionChecker checker;
    recursiveMergeDicts(primary, secondary, &checker);

    EXPECT_EQ(primary->getLength(), 1);
    EXPECT_TRUE(primary->hasKey("Key1"));

    delete primary;
    delete secondary;
}

// Test: Empty primary dict gets all keys from secondary
TEST_F(RecursiveMergeDictsTest_2027, EmptyPrimaryGetsAllSecondaryKeys_2027) {
    Dict *primary = createDict();
    Dict *secondary = createDict();

    secondary->add("A", Object(1));
    secondary->add("B", Object(2));
    secondary->add("C", Object(3));

    RefRecursionChecker checker;
    recursiveMergeDicts(primary, secondary, &checker);

    EXPECT_EQ(primary->getLength(), 3);
    EXPECT_TRUE(primary->hasKey("A"));
    EXPECT_TRUE(primary->hasKey("B"));
    EXPECT_TRUE(primary->hasKey("C"));

    delete primary;
    delete secondary;
}

// Test: Both primary and secondary are empty
TEST_F(RecursiveMergeDictsTest_2027, BothEmptyDicts_2027) {
    Dict *primary = createDict();
    Dict *secondary = createDict();

    RefRecursionChecker checker;
    recursiveMergeDicts(primary, secondary, &checker);

    EXPECT_EQ(primary->getLength(), 0);

    delete primary;
    delete secondary;
}

// Test: Nested dicts are recursively merged
TEST_F(RecursiveMergeDictsTest_2027, NestedDictsRecursivelyMerged_2027) {
    Dict *primary = createDict();
    Dict *secondary = createDict();

    Dict *primaryInner = createDict();
    primaryInner->add("InnerKey1", Object(10));

    Dict *secondaryInner = createDict();
    secondaryInner->add("InnerKey2", Object(20));

    primary->add("Nested", Object(primaryInner));
    secondary->add("Nested", Object(secondaryInner));

    RefRecursionChecker checker;
    recursiveMergeDicts(primary, secondary, &checker);

    Object nestedObj = primary->lookup("Nested");
    ASSERT_TRUE(nestedObj.isDict());

    Dict *mergedInner = nestedObj.getDict();
    EXPECT_TRUE(mergedInner->hasKey("InnerKey1"));
    EXPECT_TRUE(mergedInner->hasKey("InnerKey2"));

    Object innerVal1 = mergedInner->lookup("InnerKey1");
    ASSERT_TRUE(innerVal1.isInt());
    EXPECT_EQ(innerVal1.getInt(), 10);

    Object innerVal2 = mergedInner->lookup("InnerKey2");
    ASSERT_TRUE(innerVal2.isInt());
    EXPECT_EQ(innerVal2.getInt(), 20);

    delete primary;
    delete secondary;
}

// Test: Primary has dict value, secondary has non-dict value for same key - no merge
TEST_F(RecursiveMergeDictsTest_2027, PrimaryDictSecondaryNonDictNoMerge_2027) {
    Dict *primary = createDict();
    Dict *secondary = createDict();

    Dict *primaryInner = createDict();
    primaryInner->add("InnerKey", Object(10));

    primary->add("Key1", Object(primaryInner));
    secondary->add("Key1", Object(999));

    RefRecursionChecker checker;
    recursiveMergeDicts(primary, secondary, &checker);

    // Primary should keep its dict value
    Object val = primary->lookup("Key1");
    ASSERT_TRUE(val.isDict());

    delete primary;
    delete secondary;
}

// Test: Primary has non-dict value, secondary has dict value for same key - no overwrite
TEST_F(RecursiveMergeDictsTest_2027, PrimaryNonDictSecondaryDictNoOverwrite_2027) {
    Dict *primary = createDict();
    Dict *secondary = createDict();

    Dict *secondaryInner = createDict();
    secondaryInner->add("InnerKey", Object(20));

    primary->add("Key1", Object(42));
    secondary->add("Key1", Object(secondaryInner));

    RefRecursionChecker checker;
    recursiveMergeDicts(primary, secondary, &checker);

    // Primary should keep its non-dict value
    Object val = primary->lookup("Key1");
    ASSERT_TRUE(val.isInt());
    EXPECT_EQ(val.getInt(), 42);

    delete primary;
    delete secondary;
}

// Test: Mixed keys - some overlap, some unique
TEST_F(RecursiveMergeDictsTest_2027, MixedOverlapAndUniqueKeys_2027) {
    Dict *primary = createDict();
    Dict *secondary = createDict();

    primary->add("A", Object(1));
    primary->add("B", Object(2));

    secondary->add("B", Object(20));
    secondary->add("C", Object(30));

    RefRecursionChecker checker;
    recursiveMergeDicts(primary, secondary, &checker);

    EXPECT_EQ(primary->getLength(), 3);

    Object valA = primary->lookup("A");
    ASSERT_TRUE(valA.isInt());
    EXPECT_EQ(valA.getInt(), 1);

    // B should retain primary's value
    Object valB = primary->lookup("B");
    ASSERT_TRUE(valB.isInt());
    EXPECT_EQ(valB.getInt(), 2);

    // C should be added from secondary
    Object valC = primary->lookup("C");
    ASSERT_TRUE(valC.isInt());
    EXPECT_EQ(valC.getInt(), 30);

    delete primary;
    delete secondary;
}

// Test: Deep nesting - three levels
TEST_F(RecursiveMergeDictsTest_2027, ThreeLevelNestedMerge_2027) {
    Dict *primary = createDict();
    Dict *secondary = createDict();

    Dict *pLevel1 = createDict();
    Dict *pLevel2 = createDict();
    pLevel2->add("DeepKey1", Object(100));
    pLevel1->add("Level2", Object(pLevel2));
    primary->add("Level1", Object(pLevel1));

    Dict *sLevel1 = createDict();
    Dict *sLevel2 = createDict();
    sLevel2->add("DeepKey2", Object(200));
    sLevel1->add("Level2", Object(sLevel2));
    secondary->add("Level1", Object(sLevel1));

    RefRecursionChecker checker;
    recursiveMergeDicts(primary, secondary, &checker);

    Object l1 = primary->lookup("Level1");
    ASSERT_TRUE(l1.isDict());

    Object l2 = l1.getDict()->lookup("Level2");
    ASSERT_TRUE(l2.isDict());

    EXPECT_TRUE(l2.getDict()->hasKey("DeepKey1"));
    EXPECT_TRUE(l2.getDict()->hasKey("DeepKey2"));

    delete primary;
    delete secondary;
}

// Test: Secondary value is deep-copied (modifying secondary after merge doesn't affect primary)
TEST_F(RecursiveMergeDictsTest_2027, DeepCopyFromSecondary_2027) {
    Dict *primary = createDict();
    Dict *secondary = createDict();

    secondary->add("Key1", Object(42));

    RefRecursionChecker checker;
    recursiveMergeDicts(primary, secondary, &checker);

    // Modify secondary
    secondary->set("Key1", Object(999));

    // Primary should still have original value
    Object val = primary->lookup("Key1");
    ASSERT_TRUE(val.isInt());
    EXPECT_EQ(val.getInt(), 42);

    delete primary;
    delete secondary;
}

// Test: Single key in both primary and secondary with different non-dict types
TEST_F(RecursiveMergeDictsTest_2027, SameKeyDifferentNonDictTypes_2027) {
    Dict *primary = createDict();
    Dict *secondary = createDict();

    primary->add("Key1", Object(42));        // int
    secondary->add("Key1", Object(3.14));    // double

    RefRecursionChecker checker;
    recursiveMergeDicts(primary, secondary, &checker);

    // Primary retains its value
    Object val = primary->lookup("Key1");
    ASSERT_TRUE(val.isInt());
    EXPECT_EQ(val.getInt(), 42);

    delete primary;
    delete secondary;
}

// Test: Multiple unique keys in secondary all get added
TEST_F(RecursiveMergeDictsTest_2027, MultipleUniqueSecondaryKeys_2027) {
    Dict *primary = createDict();
    Dict *secondary = createDict();

    for (int i = 0; i < 10; i++) {
        std::string key = "Key" + std::to_string(i);
        secondary->add(key, Object(i));
    }

    RefRecursionChecker checker;
    recursiveMergeDicts(primary, secondary, &checker);

    EXPECT_EQ(primary->getLength(), 10);

    for (int i = 0; i < 10; i++) {
        std::string key = "Key" + std::to_string(i);
        EXPECT_TRUE(primary->hasKey(key));
        Object val = primary->lookup(key);
        ASSERT_TRUE(val.isInt());
        EXPECT_EQ(val.getInt(), i);
    }

    delete primary;
    delete secondary;
}
