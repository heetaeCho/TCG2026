#include <gtest/gtest.h>

#include "exiv2/iptc.hpp"

#include "exiv2/error.hpp"



namespace {



using namespace Exiv2;



class IptcdatumTest_685 : public ::testing::Test {

protected:

    Iptcdatum* iptcdatum;

    Value* valuePtr;



    void SetUp() override {

        IptcKey key("Iptc.Application2.Caption");

        valuePtr = new Value();

        iptcdatum = new Iptcdatum(key, valuePtr);

    }



    void TearDown() override {

        delete iptcdatum;

        delete valuePtr;

    }

};



TEST_F(IptcdatumTest_685, ValueReturnsSetValue_685) {

    // Arrange

    std::string expectedValue = "Sample Caption";

    valuePtr->read(expectedValue);



    // Act & Assert

    EXPECT_EQ(iptcdatum->value().toString(), expectedValue);

}



TEST_F(IptcdatumTest_685, ValueThrowsErrorWhenNotSet_685) {

    // Arrange

    IptcKey key("Iptc.Application2.Caption");

    iptcdatum = new Iptcdatum(key, nullptr);



    // Act & Assert

    EXPECT_THROW(iptcdatum->value(), Error);

}



TEST_F(IptcdatumTest_685, CopyFunctionReturnsCorrectSize_685) {

    // Arrange

    byte buffer[1024];

    size_t expectedSize = iptcdatum->size();



    // Act

    size_t resultSize = iptcdatum->copy(buffer, littleEndian);



    // Assert

    EXPECT_EQ(resultSize, expectedSize);

}



TEST_F(IptcdatumTest_685, WriteFunctionReturnsStreamReference_685) {

    // Arrange

    std::ostringstream os;



    // Act

    const std::ostream& resultOs = iptcdatum->write(os, nullptr);



    // Assert

    EXPECT_EQ(&resultOs, &os);

}



TEST_F(IptcdatumTest_685, KeyFunctionReturnsCorrectKey_685) {

    // Arrange

    std::string expectedKey = "Iptc.Application2.Caption";



    // Act & Assert

    EXPECT_EQ(iptcdatum->key(), expectedKey);

}



}  // namespace
