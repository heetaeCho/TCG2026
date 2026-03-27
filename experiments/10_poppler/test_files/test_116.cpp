#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "Dict.h"



class DictTest : public ::testing::Test {

protected:

    DictTest() : dict(nullptr) {}



    void SetUp() override {

        XRef* xref = new XRef();

        dict = std::make_unique<Dict>(xref);

    }



    void TearDown() override {

        // No need to delete xref as it's managed by the Dict class

    }



    std::unique_ptr<Dict> dict;

};



TEST_F(DictTest_116, GetValNF_ReturnsCorrectValue_116) {

    Object obj("value");

    dict->add("key", std::move(obj));



    const Object& retrievedObj = dict->getValNF(0);

    EXPECT_EQ(retrievedObj.getString(), "value");

}



TEST_F(DictTest_116, GetValNF_OutOfBounds_ThrowsNoException_116) {

    // Assuming getValNF does not throw an exception for out of bounds

    // and returns a default constructed Object instead.

    const Object& retrievedObj = dict->getValNF(0);

    EXPECT_EQ(retrievedObj.isNull(), true);

}



TEST_F(DictTest_116, GetValNF_AfterAdd_ReturnsCorrectValue_116) {

    Object obj("value");

    dict->add("key", std::move(obj));



    const Object& retrievedObj = dict->getValNF(0);

    EXPECT_EQ(retrievedObj.getString(), "value");

}



TEST_F(DictTest_116, GetValNF_AfterSet_ReturnsCorrectValue_116) {

    Object obj("initial_value");

    dict->add("key", std::move(obj));



    Object newObj("updated_value");

    dict->set("key", std::move(newObj));



    const Object& retrievedObj = dict->getValNF(0);

    EXPECT_EQ(retrievedObj.getString(), "updated_value");

}



TEST_F(DictTest_116, GetValNF_AfterRemove_ReturnsDefaultValue_116) {

    Object obj("value");

    dict->add("key", std::move(obj));

    dict->remove("key");



    const Object& retrievedObj = dict->getValNF(0);

    EXPECT_EQ(retrievedObj.isNull(), true);

}



TEST_F(DictTest_116, GetLength_ReturnsCorrectSize_116) {

    EXPECT_EQ(dict->getLength(), 0);



    Object obj("value");

    dict->add("key", std::move(obj));



    EXPECT_EQ(dict->getLength(), 1);

}
