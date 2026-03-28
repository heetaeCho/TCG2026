#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "exiv2/exif.hpp"

#include "./TestProjects/exiv2/src/easyaccess.cpp"



using namespace Exiv2;

using testing::_;

using testing::Return;



class WhiteBalanceTest_518 : public ::testing::Test {

protected:

    ExifData ed;

};



TEST_F(WhiteBalanceTest_518, CanonSiWhiteBalanceFound_518) {

    Exifdatum datum("Exif.CanonSi.WhiteBalance", Value::create(TypeId::shortType));

    ed.add(datum);



    auto it = whiteBalance(ed);

    EXPECT_NE(it, ed.end());

    EXPECT_EQ(it->key(), "Exif.CanonSi.WhiteBalance");

}



TEST_F(WhiteBalanceTest_518, FujifilmWhiteBalanceFound_518) {

    Exifdatum datum("Exif.Fujifilm.WhiteBalance", Value::create(TypeId::shortType));

    ed.add(datum);



    auto it = whiteBalance(ed);

    EXPECT_NE(it, ed.end());

    EXPECT_EQ(it->key(), "Exif.Fujifilm.WhiteBalance");

}



TEST_F(WhiteBalanceTest_518, SigmaWhiteBalanceFound_518) {

    Exifdatum datum("Exif.Sigma.WhiteBalance", Value::create(TypeId::shortType));

    ed.add(datum);



    auto it = whiteBalance(ed);

    EXPECT_NE(it, ed.end());

    EXPECT_EQ(it->key(), "Exif.Sigma.WhiteBalance");

}



TEST_F(WhiteBalanceTest_518, Nikon1WhiteBalanceFound_518) {

    Exifdatum datum("Exif.Nikon1.WhiteBalance", Value::create(TypeId::shortType));

    ed.add(datum);



    auto it = whiteBalance(ed);

    EXPECT_NE(it, ed.end());

    EXPECT_EQ(it->key(), "Exif.Nikon1.WhiteBalance");

}



TEST_F(WhiteBalanceTest_518, Nikon2WhiteBalanceFound_518) {

    Exifdatum datum("Exif.Nikon2.WhiteBalance", Value::create(TypeId::shortType));

    ed.add(datum);



    auto it = whiteBalance(ed);

    EXPECT_NE(it, ed.end());

    EXPECT_EQ(it->key(), "Exif.Nikon2.WhiteBalance");

}



TEST_F(WhiteBalanceTest_518, Nikon3WhiteBalanceFound_518) {

    Exifdatum datum("Exif.Nikon3.WhiteBalance", Value::create(TypeId::shortType));

    ed.add(datum);



    auto it = whiteBalance(ed);

    EXPECT_NE(it, ed.end());

    EXPECT_EQ(it->key(), "Exif.Nikon3.WhiteBalance");

}



TEST_F(WhiteBalanceTest_518, OlympusWhiteBalanceFound_518) {

    Exifdatum datum("Exif.Olympus.WhiteBalance", Value::create(TypeId::shortType));

    ed.add(datum);



    auto it = whiteBalance(ed);

    EXPECT_NE(it, ed.end());

    EXPECT_EQ(it->key(), "Exif.Olympus.WhiteBalance");

}



TEST_F(WhiteBalanceTest_518, OlympusCsWhiteBalanceFound_518) {

    Exifdatum datum("Exif.OlympusCs.WhiteBalance", Value::create(TypeId::shortType));

    ed.add(datum);



    auto it = whiteBalance(ed);

    EXPECT_NE(it, ed.end());

    EXPECT_EQ(it->key(), "Exif.OlympusCs.WhiteBalance");

}



TEST_F(WhiteBalanceTest_518, PanasonicWhiteBalanceFound_518) {

    Exifdatum datum("Exif.Panasonic.WhiteBalance", Value::create(TypeId::shortType));

    ed.add(datum);



    auto it = whiteBalance(ed);

    EXPECT_NE(it, ed.end());

    EXPECT_EQ(it->key(), "Exif.Panasonic.WhiteBalance");

}



TEST_F(WhiteBalanceTest_518, MinoltaCs5DWhiteBalanceFound_518) {

    Exifdatum datum("Exif.MinoltaCs5D.WhiteBalance", Value::create(TypeId::shortType));

    ed.add(datum);



    auto it = whiteBalance(ed);

    EXPECT_NE(it, ed.end());

    EXPECT_EQ(it->key(), "Exif.MinoltaCs5D.WhiteBalance");

}



TEST_F(WhiteBalanceTest_518, MinoltaCs7DWhiteBalanceFound_518) {

    Exifdatum datum("Exif.MinoltaCs7D.WhiteBalance", Value::create(TypeId::shortType));

    ed.add(datum);



    auto it = whiteBalance(ed);

    EXPECT_NE(it, ed.end());

    EXPECT_EQ(it->key(), "Exif.MinoltaCs7D.WhiteBalance");

}



TEST_F(WhiteBalanceTest_518, MinoltaCsNewWhiteBalanceFound_518) {

    Exifdatum datum("Exif.MinoltaCsNew.WhiteBalance", Value::create(TypeId::shortType));

    ed.add(datum);



    auto it = whiteBalance(ed);

    EXPECT_NE(it, ed.end());

    EXPECT_EQ(it->key(), "Exif.MinoltaCsNew.WhiteBalance");

}



TEST_F(WhiteBalanceTest_518, MinoltaCsOldWhiteBalanceFound_518) {

    Exifdatum datum("Exif.MinoltaCsOld.WhiteBalance", Value::create(TypeId::shortType));

    ed.add(datum);



    auto it = whiteBalance(ed);

    EXPECT_NE(it, ed.end());

    EXPECT_EQ(it->key(), "Exif.MinoltaCsOld.WhiteBalance");

}



TEST_F(WhiteBalanceTest_518, MinoltaWhiteBalanceFound_518) {

    Exifdatum datum("Exif.Minolta.WhiteBalance", Value::create(TypeId::shortType));

    ed.add(datum);



    auto it = whiteBalance(ed);

    EXPECT_NE(it, ed.end());

    EXPECT_EQ(it->key(), "Exif.Minolta.WhiteBalance");

}



TEST_F(WhiteBalanceTest_518, PentaxWhiteBalanceFound_518) {

    Exifdatum datum("Exif.Pentax.WhiteBalance", Value::create(TypeId::shortType));

    ed.add(datum);



    auto it = whiteBalance(ed);

    EXPECT_NE(it, ed.end());

    EXPECT_EQ(it->key(), "Exif.Pentax.WhiteBalance");

}



TEST_F(WhiteBalanceTest_518, PentaxDngWhiteBalanceFound_518) {

    Exifdatum datum("Exif.PentaxDng.WhiteBalance", Value::create(TypeId::shortType));

    ed.add(datum);



    auto it = whiteBalance(ed);

    EXPECT_NE(it, ed.end());

    EXPECT_EQ(it->key(), "Exif.PentaxDng.WhiteBalance");

}



TEST_F(WhiteBalanceTest_518, Sony1WhiteBalanceFound_518) {

    Exifdatum datum("Exif.Sony1.WhiteBalance", Value::create(TypeId::shortType));

    ed.add(datum);



    auto it = whiteBalance(ed);

    EXPECT_NE(it, ed.end());

    EXPECT_EQ(it->key(), "Exif.Sony1.WhiteBalance");

}



TEST_F(WhiteBalanceTest_518, Sony2WhiteBalanceFound_518) {

    Exifdatum datum("Exif.Sony2.WhiteBalance", Value::create(TypeId::shortType));

    ed.add(datum);



    auto it = whiteBalance(ed);

    EXPECT_NE(it, ed.end());

    EXPECT_EQ(it->key(), "Exif.Sony2.WhiteBalance");

}



TEST_F(WhiteBalanceTest_518, Sony1WhiteBalance2Found_518) {

    Exifdatum datum("Exif.Sony1.WhiteBalance2", Value::create(TypeId::shortType));

    ed.add(datum);



    auto it = whiteBalance(ed);

    EXPECT_NE(it, ed.end());

    EXPECT_EQ(it->key(), "Exif.Sony1.WhiteBalance2");

}



TEST_F(WhiteBalanceTest_518, Sony2WhiteBalance2Found_518) {

    Exifdatum datum("Exif.Sony2.WhiteBalance2", Value::create(TypeId::shortType));

    ed.add(datum);



    auto it = whiteBalance(ed);

    EXPECT_NE(it, ed.end());

    EXPECT_EQ(it->key(), "Exif.Sony2.WhiteBalance2");

}



TEST_F(WhiteBalanceTest_518, Sony1MltCsA100WhiteBalanceFound_518) {

    Exifdatum datum("Exif.Sony1MltCsA100.WhiteBalance", Value::create(TypeId::shortType));

    ed.add(datum);



    auto it = whiteBalance(ed);

    EXPECT_NE(it, ed.end());

    EXPECT_EQ(it->key(), "Exif.Sony1MltCsA100.WhiteBalance");

}



TEST_F(WhiteBalanceTest_518, SonyMinoltaWhiteBalanceFound_518) {

    Exifdatum datum("Exif.SonyMinolta.WhiteBalance", Value::create(TypeId::shortType));

    ed.add(datum);



    auto it = whiteBalance(ed);

    EXPECT_NE(it, ed.end());

    EXPECT_EQ(it->key(), "Exif.SonyMinolta.WhiteBalance");

}



TEST_F(WhiteBalanceTest_518, CasioWhiteBalanceFound_518) {

    Exifdatum datum("Exif.Casio.WhiteBalance", Value::create(TypeId::shortType));

    ed.add(datum);



    auto it = whiteBalance(ed);

    EXPECT_NE(it, ed.end());

    EXPECT_EQ(it->key(), "Exif.Casio.WhiteBalance");

}



TEST_F(WhiteBalanceTest_518, Casio2WhiteBalanceFound_518) {

    Exifdatum datum("Exif.Casio2.WhiteBalance", Value::create(TypeId::shortType));

    ed.add(datum);



    auto it = whiteBalance(ed);

    EXPECT_NE(it, ed.end());

    EXPECT_EQ(it->key(), "Exif.Casio2.WhiteBalance");

}



TEST_F(WhiteBalanceTest_518, Casio2WhiteBalance2Found_518) {

    Exifdatum datum("Exif.Casio2.WhiteBalance2", Value::create(TypeId::shortType));

    ed.add(datum);



    auto it = whiteBalance(ed);

    EXPECT_NE(it, ed.end());

    EXPECT_EQ(it->key(), "Exif.Casio2.WhiteBalance2");

}



TEST_F(WhiteBalanceTest_518, PhotoWhiteBalanceFound_518) {

    Exifdatum datum("Exif.Photo.WhiteBalance", Value::create(TypeId::shortType));

    ed.add(datum);



    auto it = whiteBalance(ed);

    EXPECT_NE(it, ed.end());

    EXPECT_EQ(it->key(), "Exif.Photo.WhiteBalance");

}



TEST_F(WhiteBalanceTest_518, NoWhiteBalanceFound_518) {

    auto it = whiteBalance(ed);

    EXPECT_EQ(it, ed.end());

}
