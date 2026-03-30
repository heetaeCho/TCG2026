#include <gtest/gtest.h>

#include "ExpatAdapter.cpp"  // Assuming ExpatAdapter class is defined in this file



class ExpatAdapterTest : public ::testing::Test {

protected:

    void SetUp() override {

        adapter = XMP_NewExpatAdapter();

    }



    void TearDown() override {

        delete adapter;

    }



    ExpatAdapter* adapter;

};



TEST_F(ExpatAdapterTest_2090, NewInstanceIsNotNull_2090) {

    EXPECT_NE(adapter, nullptr);

}



// Assuming there are no other public methods or observable behaviors in the given snippet,

// we can only test that an instance is created successfully.
