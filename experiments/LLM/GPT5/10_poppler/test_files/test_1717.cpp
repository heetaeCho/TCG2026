#include <gtest/gtest.h>

#include "StructTreeRoot.h"
#include "Dict.h"
#include "Object.h"

// NOTE: These tests treat StructTreeRoot as a black box and only validate
// observable behavior through its public interface (getRoleMap()).

class StructTreeRootTest_1717 : public ::testing::Test {};

// Normal operation / error-like case: RoleMap missing -> nullptr
TEST_F(StructTreeRootTest_1717, GetRoleMapReturnsNullWhenMissing_1717)
{
    Dict rootDict(nullptr); // XRef* can be nullptr for unit-level construction

    StructTreeRoot root(/*docA=*/nullptr, rootDict);

    EXPECT_EQ(root.getRoleMap(), nullptr);
}

// Boundary / error-like case: RoleMap present but not a dictionary -> nullptr
TEST_F(StructTreeRootTest_1717, GetRoleMapReturnsNullWhenNotDict_1717)
{
    Dict rootDict(nullptr);
    rootDict.add("RoleMap", Object(42)); // non-dict

    StructTreeRoot root(/*docA=*/nullptr, rootDict);

    EXPECT_EQ(root.getRoleMap(), nullptr);
}

// Normal operation: RoleMap present and is a dictionary -> non-null and usable
TEST_F(StructTreeRootTest_1717, GetRoleMapReturnsDictWhenPresent_1717)
{
    Dict rootDict(nullptr);

    auto *roleMapDict = new Dict(nullptr);
    roleMapDict->add("H1", Object(objName, "P"));
    rootDict.add("RoleMap", Object(roleMapDict));

    StructTreeRoot root(/*docA=*/nullptr, rootDict);

    Dict *rm = root.getRoleMap();
    ASSERT_NE(rm, nullptr);

    Object v = rm->lookup("H1");
    EXPECT_TRUE(v.isName());
    EXPECT_STREQ(v.getName(), "P");

    // Stability: repeated calls should remain consistent (no assumptions beyond pointer equality).
    EXPECT_EQ(root.getRoleMap(), rm);
}

// Boundary: RoleMap is an empty dictionary -> still non-null (dict), length 0
TEST_F(StructTreeRootTest_1717, GetRoleMapReturnsEmptyDictWhenEmpty_1717)
{
    Dict rootDict(nullptr);

    auto *emptyRoleMap = new Dict(nullptr);
    rootDict.add("RoleMap", Object(emptyRoleMap));

    StructTreeRoot root(/*docA=*/nullptr, rootDict);

    Dict *rm = root.getRoleMap();
    ASSERT_NE(rm, nullptr);
    EXPECT_EQ(rm->getLength(), 0);
}