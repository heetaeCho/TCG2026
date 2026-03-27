#include <gtest/gtest.h>

#include "exiv2/exif.hpp"

#include "exiv2/tags.hpp"



using namespace Exiv2;



class ExifdatumTest : public ::testing::Test {

protected:

    std::unique_ptr<ExifKey> key;

    const Value* value = nullptr;

    Exifdatum exifdatum;



    void SetUp() override {

        key = std::make_unique<ExifKey>("Exif.Image.Artist");

        exifdatum = Exifdatum(*key, value);

    }

};



TEST_F(ExifdatumTest_NormalOperation_751, IdxReturnsCorrectValue_751) {

    EXPECT_EQ(exifdatum.idx(), 0); // Default idx should be 0

}



TEST_F(ExifdatumTest_BoundaryConditions_751, IdxAfterSettingKeyIdx_751) {

    key->setIdx(42);

    exifdatum = Exifdatum(*key, value);

    EXPECT_EQ(exifdatum.idx(), 42); // idx should reflect the set index

}



TEST_F(ExifdatumTest_ExceptionalCases_751, IdxWithNullKey_751) {

    Exifdatum exifdatumWithoutKey(nullptr, value);

    EXPECT_EQ(exifdatumWithoutKey.idx(), 0); // No key means default idx should be 0

}
