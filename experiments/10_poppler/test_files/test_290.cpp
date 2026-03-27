#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "Link.h"



class LinkGoToRTest_290 : public ::testing::Test {

protected:

    // Assuming we have a way to create a valid LinkGoToR object for testing

    std::unique_ptr<LinkGoToR> link;



    void SetUp() override {

        // Mock objects or setup if needed, but since we treat implementation as black box,

        // we assume the constructor works correctly.

        // This is a placeholder as actual construction might require valid Object instances.

        link = std::make_unique<LinkGoToR>(nullptr, nullptr);

    }

};



TEST_F(LinkGoToRTest_290, GetNamedDest_ReturnsValidPointer_290) {

    const GooString* namedDest = link->getNamedDest();

    EXPECT_NE(namedDest, nullptr); // Expect the pointer to be non-null

}



TEST_F(LinkGoToRTest_290, GetNamedDest_ConsistentAcrossCalls_290) {

    const GooString* firstCall = link->getNamedDest();

    const GooString* secondCall = link->getNamedDest();

    EXPECT_EQ(firstCall, secondCall); // Expect the same pointer to be returned on each call

}



// Assuming isOk() and getKind() are part of the interface and can be tested

TEST_F(LinkGoToRTest_290, IsOk_ReturnsTrueForValidObject_290) {

    EXPECT_TRUE(link->isOk()); // Expect true if object is validly constructed

}



TEST_F(LinkGoToRTest_290, GetKind_ReturnsExpectedValue_290) {

    EXPECT_EQ(link->getKind(), LinkActionKind::goToR); // Assuming goToR is the correct kind for LinkGoToR

}



// Tests for getFileName and getDest are similar to getNamedDest

TEST_F(LinkGoToRTest_290, GetFileName_ReturnsValidPointer_290) {

    const GooString* fileName = link->getFileName();

    EXPECT_NE(fileName, nullptr); // Expect the pointer to be non-null

}



TEST_F(LinkGoToRTest_290, GetDest_ReturnsValidPointer_290) {

    const LinkDest* dest = link->getDest();

    EXPECT_NE(dest, nullptr); // Expect the pointer to be non-null

}
