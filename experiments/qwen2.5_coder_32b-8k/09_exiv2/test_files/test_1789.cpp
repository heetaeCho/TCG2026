#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "crwimage_int.hpp"

#include "exiv2/types.hpp"



namespace Exiv2 {

namespace Internal {



class CiffHeaderTest_1789 : public ::testing::Test {

protected:

    CiffHeader ciffHeader;

};



TEST_F(CiffHeaderTest_1789, AddValidData_1789) {

    uint16_t crwTagId = 0x0805;

    uint16_t crwDir = 0x0001;

    DataBuf data(4);

    ciffHeader.add(crwTagId, crwDir, std::move(data));

}



TEST_F(CiffHeaderTest_1789, AddEmptyData_1789) {

    uint16_t crwTagId = 0x0805;

    uint16_t crwDir = 0x0001;

    DataBuf data;

    ciffHeader.add(crwTagId, crwDir, std::move(data));

}



TEST_F(CiffHeaderTest_1789, AddBoundaryTagId_1789) {

    uint16_t crwTagId = 0xFFFF; // Maximum value for a 16-bit unsigned integer

    uint16_t crwDir = 0x0001;

    DataBuf data(4);

    ciffHeader.add(crwTagId, crwDir, std::move(data));

}



TEST_F(CiffHeaderTest_1789, AddBoundaryCrwDir_1789) {

    uint16_t crwTagId = 0x0805;

    uint16_t crwDir = 0xFFFF; // Maximum value for a 16-bit unsigned integer

    DataBuf data(4);

    ciffHeader.add(crwTagId, crwDir, std::move(data));

}



} // namespace Internal

} // namespace Exiv2
