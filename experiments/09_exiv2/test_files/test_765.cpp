#include <gtest/gtest.h>

#include "exiv2/exif.hpp"

#include "exiv2/value.hpp"



using namespace Exiv2;



class ExifdatumTest_765 : public ::testing::Test {

protected:

    std::unique_ptr<ExifKey> key;

    std::unique_ptr<Value> value;

    Exifdatum* exifdatum;



    void SetUp() override {

        key = std::make_unique<ExifKey>("Exif.Image.Artist");

        value = std::make_unique<StringValue>(stringType);

        exifdatum = new Exifdatum(*key, value.get());

    }



    void TearDown() override {

        delete exifdatum;

    }

};



TEST_F(ExifdatumTest_765, DataAreaReturnsEmptyWhenNoValueSet_765) {

    // Arrange

    Exifdatum exifdatumWithoutValue(*key, nullptr);



    // Act & Assert

    EXPECT_EQ(exifdatumWithoutValue.dataArea().pData_, nullptr);

    EXPECT_EQ(exifdatumWithoutValue.dataArea().size_, 0);

}



TEST_F(ExifdatumTest_765, DataAreaReturnsCorrectBufferWhenValueSet_765) {

    // Arrange

    const byte buffer[] = {1, 2, 3};

    exifdatum->setDataArea(buffer, sizeof(buffer));



    // Act & Assert

    EXPECT_EQ(exifdatum->dataArea().pData_[0], buffer[0]);

    EXPECT_EQ(exifdatum->dataArea().pData_[1], buffer[1]);

    EXPECT_EQ(exifdatum->dataArea().pData_[2], buffer[2]);

    EXPECT_EQ(exifdatum->dataArea().size_, sizeof(buffer));

}



TEST_F(ExifdatumTest_765, DataAreaReturnsConsistentSizeWhenValueSet_765) {

    // Arrange

    const byte buffer[] = {1, 2, 3};

    exifdatum->setDataArea(buffer, sizeof(buffer));



    // Act & Assert

    EXPECT_EQ(exifdatum->dataArea().size_, sizeof(buffer));

}



TEST_F(ExifdatumTest_765, DataAreaReturnsEmptyWhenValueReset_765) {

    // Arrange

    const byte buffer[] = {1, 2, 3};

    exifdatum->setDataArea(buffer, sizeof(buffer));

    exifdatum->setValue(nullptr);



    // Act & Assert

    EXPECT_EQ(exifdatum->dataArea().pData_, nullptr);

    EXPECT_EQ(exifdatum->dataArea().size_, 0);

}
