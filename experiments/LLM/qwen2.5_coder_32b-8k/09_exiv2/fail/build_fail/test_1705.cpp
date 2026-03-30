#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "tiffvisitor_int.hpp"

#include "makernote_int.hpp"

#include "value.hpp"

#include "tiffcomposite_int.hpp"

#include "tags.hpp"



using namespace Exiv2;

using namespace Exiv2::Internal;



class TiffReaderTest : public ::testing::Test {

protected:

    const byte testData[10] = { 0x49, 0x49, 0x2A, 0x00, 0x08, 0x00, 0x00, 0x00, 0x3E, 0x00 };

    TiffComponent root;

    TiffReader reader{testData, sizeof(testData), &root, {}};

};



TEST_F(TiffReaderTest, VisitMnEntry_NormalOperation_1705) {

    TiffMnEntry mnEntry(0x0112, IfdId::ifd0Id, IfdId::canonId);

    reader.visitMnEntry(&mnEntry);



    EXPECT_NE(mnEntry.mn_.get(), nullptr);

}



TEST_F(TiffReaderTest, VisitMnEntry_NoMakeTag_1705) {

    TiffFinder finder(0x0112, IfdId::ifd0Id);

    root.accept(finder);

    auto te = dynamic_cast<const TiffEntryBase*>(finder.result());

    EXPECT_EQ(te, nullptr);



    TiffMnEntry mnEntry(0x0112, IfdId::ifd0Id, IfdId::canonId);

    reader.visitMnEntry(&mnEntry);



    EXPECT_EQ(mnEntry.mn_.get(), nullptr);

}



TEST_F(TiffReaderTest, VisitMnEntry_MakeTagNoValue_1705) {

    auto value = std::make_unique<Value>(TypeId::asciiString);

    TiffEntryBase makeEntry(0x010f, IfdId::ifd0Id, ttAscii);

    makeEntry.setValue(std::move(value));



    root.addChild(makeEntry.clone());

    

    TiffMnEntry mnEntry(0x0112, IfdId::ifd0Id, IfdId::canonId);

    reader.visitMnEntry(&mnEntry);



    EXPECT_EQ(mnEntry.mn_.get(), nullptr);

}



TEST_F(TiffReaderTest, VisitMnEntry_MakeTagWithValue_1705) {

    auto value = std::make_unique<Value>(TypeId::asciiString);

    value->setDataArea(testData, sizeof(testData));

    TiffEntryBase makeEntry(0x010f, IfdId::ifd0Id, ttAscii);

    makeEntry.setValue(std::move(value));



    root.addChild(makeEntry.clone());

    

    TiffMnEntry mnEntry(0x0112, IfdId::ifd0Id, IfdId::canonId);

    reader.visitMnEntry(&mnEntry);



    EXPECT_NE(mnEntry.mn_.get(), nullptr);

}



TEST_F(TiffReaderTest, VisitMnEntry_InvalidMakeTag_1705) {

    auto value = std::make_unique<Value>(TypeId::asciiString);

    value->setDataArea(testData, sizeof(testData));

    TiffEntryBase makeEntry(0x010f, IfdId::ifd0Id, ttAscii);

    makeEntry.setValue(std::move(value));



    root.addChild(makeEntry.clone());

    

    TiffMnEntry mnEntry(0x0112, IfdId::ifd0Id, IfdId::canonId);

    reader.visitMnEntry(&mnEntry);



    EXPECT_NE(mnEntry.mn_.get(), nullptr);

}



TEST_F(TiffReaderTest, VisitMnEntry_MakeTagWithNullValue_1705) {

    TiffEntryBase makeEntry(0x010f, IfdId::ifd0Id, ttAscii);



    root.addChild(makeEntry.clone());

    

    TiffMnEntry mnEntry(0x0112, IfdId::ifd0Id, IfdId::canonId);

    reader.visitMnEntry(&mnEntry);



    EXPECT_EQ(mnEntry.mn_.get(), nullptr);

}



TEST_F(TiffReaderTest, VisitMnEntry_SetStartCalled_1705) {

    auto value = std::make_unique<Value>(TypeId::asciiString);

    value->setDataArea(testData, sizeof(testData));

    TiffEntryBase makeEntry(0x010f, IfdId::ifd0Id, ttAscii);

    makeEntry.setValue(std::move(value));



    root.addChild(makeEntry.clone());

    

    TiffMnEntry mnEntry(0x0112, IfdId::ifd0Id, IfdId::canonId);

    reader.visitMnEntry(&mnEntry);



    EXPECT_NE(mnEntry.start(), nullptr);

}



TEST_F(TiffReaderTest, VisitMnEntry_MakeTagWithInvalidValue_1705) {

    auto value = std::make_unique<Value>(TypeId::asciiString);

    value->setDataArea(testData, sizeof(testData));

    TiffEntryBase makeEntry(0x010f, IfdId::ifd0Id, ttAscii);

    makeEntry.setValue(std::move(value));



    root.addChild(makeEntry.clone());

    

    TiffMnEntry mnEntry(0x0112, IfdId::ifd0Id, IfdId::canonId);

    reader.visitMnEntry(&mnEntry);



    EXPECT_NE(mnEntry.mn_.get(), nullptr);

}
