#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "exiv2/basicio.hpp"



namespace {



using namespace Exiv2;



class MemIoTest : public ::testing::Test {

protected:

    void SetUp() override {

        data = new byte[5]{1, 2, 3, 4, 5};

        memIoWithData = std::make_unique<MemIo>(data, 5);

        memIoWithoutData = std::make_unique<MemIo>();

    }



    void TearDown() override {

        delete[] data;

    }



    byte* data;

    std::unique_ptr<MemIo> memIoWithData;

    std::unique_ptr<MemIo> memIoWithoutData;

};



TEST_F(MemIoTest_591, GetbReturnsFirstByte_591) {

    EXPECT_EQ(memIoWithData->getb(), 1);

}



TEST_F(MemIoTest_591, GetbAdvancesIndex_591) {

    memIoWithData->getb();

    EXPECT_EQ(memIoWithData->getb(), 2);

}



TEST_F(MemIoTest_591, GetbReturnsEOFAtEnd_591) {

    for (int i = 0; i < 5; ++i) {

        memIoWithData->getb();

    }

    EXPECT_EQ(memIoWithData->getb(), EOF);

}



TEST_F(MemIoTest_591, EofFlagSetAfterEOF_591) {

    for (int i = 0; i < 6; ++i) {

        memIoWithData->getb();

    }

    EXPECT_TRUE(memIoWithData->eof());

}



TEST_F(MemIoTest_591, GetbDoesNotAdvanceIndexOnEOF_591) {

    for (int i = 0; i < 6; ++i) {

        memIoWithData->getb();

    }

    EXPECT_EQ(memIoWithData->tell(), 5);

}



TEST_F(MemIoTest_591, GetbFromEmptyMemIoReturnsEOF_591) {

    EXPECT_EQ(memIoWithoutData->getb(), EOF);

}



}  // namespace
