#include <gtest/gtest.h>

#include "TestProjects/poppler/poppler/Form.cc"

#include "TestProjects/poppler/poppler/Object.h"

#include "TestProjects/poppler/poppler/Dict.h"



using namespace std;



class FieldLookupTest : public ::testing::Test {

protected:

    void SetUp() override {

        xref = new XRef(nullptr, nullptr);

        field = make_unique<Dict>(xref);

        usedParents = new RefRecursionChecker();

    }



    void TearDown() override {

        delete usedParents;

        delete xref;

    }



    XRef* xref;

    unique_ptr<Dict> field;

    RefRecursionChecker* usedParents;

};



TEST_F(FieldLookupTest_1517, KeyInField_1517) {

    // Arrange

    Object value(42);

    field->add("testKey", move(value));

    

    // Act

    Object result = fieldLookup(field.get(), "testKey", usedParents);



    // Assert

    EXPECT_TRUE(result.isInt());

    EXPECT_EQ(result.getInt(), 42);

}



TEST_F(FieldLookupTest_1517, KeyInParentDict_1517) {

    // Arrange

    auto parent = make_unique<Dict>(xref);

    Object value(43);

    parent->add("testKey", move(value));



    Ref ref{1, 0};

    field->set("Parent", Object(ref));

    

    xref->put(ref, ObjNum(ref.num), ObjGen(ref.gen), Dict::copy(parent.get()));



    // Act

    Object result = fieldLookup(field.get(), "testKey", usedParents);



    // Assert

    EXPECT_TRUE(result.isInt());

    EXPECT_EQ(result.getInt(), 43);

}



TEST_F(FieldLookupTest_1517, KeyNotPresent_1517) {

    // Arrange and Act

    Object result = fieldLookup(field.get(), "nonExistentKey", usedParents);



    // Assert

    EXPECT_TRUE(result.isNull());

}



TEST_F(FieldLookupTest_1517, RecursiveParent_1517) {

    // Arrange

    auto parent = make_unique<Dict>(xref);

    Ref ref{2, 0};

    field->set("Parent", Object(ref));



    auto grandparent = make_unique<Dict>(xref);

    Object value(44);

    grandparent->add("testKey", move(value));

    Ref gRef{3, 0};



    parent->set("Parent", Object(gRef));



    xref->put(ref, ObjNum(ref.num), ObjGen(ref.gen), Dict::copy(parent.get()));

    xref->put(gRef, ObjNum(gRef.num), ObjGen(gRef.gen), Dict::copy(grandparent.get()));



    // Act

    Object result = fieldLookup(field.get(), "testKey", usedParents);



    // Assert

    EXPECT_TRUE(result.isInt());

    EXPECT_EQ(result.getInt(), 44);

}



TEST_F(FieldLookupTest_1517, RecursiveParentCycle_1517) {

    // Arrange: Create a cycle in parent references

    Ref ref{1, 0};

    field->set("Parent", Object(ref));

    xref->put(ref, ObjNum(ref.num), ObjGen(ref.gen), Dict::copy(field.get()));



    // Act

    Object result = fieldLookup(field.get(), "testKey", usedParents);



    // Assert: Should not enter infinite loop and return null

    EXPECT_TRUE(result.isNull());

}
