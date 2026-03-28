#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "exiv2/exif.hpp"
#include "exiv2/value.hpp"
#include "exiv2/nikonmn_int.hpp"

// Mock ExifData class
class MockExifData : public Exiv2::ExifData {
public:
    MOCK_METHOD(ExifDatum&, operator[], (const std::string& key), (override));
    MOCK_METHOD(void, add, (const ExifKey& key, const Exiv2::Value* pValue), (override));
    MOCK_METHOD(void, add, (const ExifDatum& exifdatum), (override));
    MOCK_METHOD(ExifData::iterator, erase, (ExifData::iterator pos), (override));
    MOCK_METHOD(ExifData::iterator, erase, (ExifData::iterator beg, ExifData::iterator end), (override));
    MOCK_METHOD(void, clear, (), (override));
    MOCK_METHOD(void, sortByKey, (), (override));
    MOCK_METHOD(void, sortByTag, (), (override));
    MOCK_METHOD(ExifData::iterator, findKey, (const ExifKey& key), (override));
    MOCK_METHOD(ExifData::iterator, begin, (), (override));
    MOCK_METHOD(ExifData::iterator, end, (), (override));
    MOCK_METHOD(bool, empty, (), (const, override));
    MOCK_METHOD(size_t, count, (), (const, override));
};

// Test fixture
class Nikon3MakerNoteTest : public testing::Test {
protected:
    Exiv2::Internal::Nikon3MakerNote makerNote;
    MockExifData mockExifData;
};

// Test: Normal operation where external flash is on
TEST_F(Nikon3MakerNoteTest, PrintExternalFlashData2Fl6_FlashOn_486) {
    Exiv2::Value value(Exiv2::TypeId::unsignedByte);
    // Setting up a value where the flash control mode is ON (0x80 bit set)
    uint32_t flashValue = 0x80;  // Flash on
    value.setDataArea(reinterpret_cast<const uint8_t*>(&flashValue), sizeof(flashValue));
    
    std::ostringstream os;
    makerNote.printExternalFlashData2Fl6(os, value, &mockExifData);

    // Check if the output is as expected
    EXPECT_EQ(os.str(), "External flash on, ");
}

// Test: Boundary condition with the flash control off
TEST_F(Nikon3MakerNoteTest, PrintExternalFlashData2Fl6_FlashOff_486) {
    Exiv2::Value value(Exiv2::TypeId::unsignedByte);
    // Setting up a value where the flash control mode is OFF (0x80 bit not set)
    uint32_t flashValue = 0x00;  // Flash off
    value.setDataArea(reinterpret_cast<const uint8_t*>(&flashValue), sizeof(flashValue));
    
    std::ostringstream os;
    makerNote.printExternalFlashData2Fl6(os, value, &mockExifData);

    // Check if the output is as expected
    EXPECT_EQ(os.str(), "External flash off");
}

// Test: Edge case where value does not have the expected type
TEST_F(Nikon3MakerNoteTest, PrintExternalFlashData2Fl6_InvalidType_486) {
    Exiv2::Value value(Exiv2::TypeId::asciiString);  // Invalid type (not unsigned byte)
    value.setDataArea(reinterpret_cast<const uint8_t*>("Invalid"), 7);
    
    std::ostringstream os;
    makerNote.printExternalFlashData2Fl6(os, value, &mockExifData);

    // Check that the output is the value as string, since it's an invalid type
    EXPECT_EQ(os.str(), "(Invalid)");
}

// Test: Exceptional case where value count is not 1
TEST_F(Nikon3MakerNoteTest, PrintExternalFlashData2Fl6_InvalidCount_486) {
    Exiv2::Value value(Exiv2::TypeId::unsignedByte);
    uint32_t flashValue = 0x80;
    value.setDataArea(reinterpret_cast<const uint8_t*>(&flashValue), sizeof(flashValue));

    // Set count to something other than 1
    value.setCount(2);

    std::ostringstream os;
    makerNote.printExternalFlashData2Fl6(os, value, &mockExifData);

    // Check if the output is as expected for invalid count
    EXPECT_EQ(os.str(), "(0x80)");
}