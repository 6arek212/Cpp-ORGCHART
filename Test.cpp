#include <iostream>
#include "OrgChart.hpp"
#include "doctest.h"
#include <string>
#include <vector>
using namespace ariel;
using namespace std;

TEST_CASE("Bad OP")
{
    OrgChart org;

    CHECK_THROWS(org.add_sub("tarik", "aaa"));
    org.add_root("Tarik");
    CHECK_THROWS(org.add_sub("aa", "bb"));

    CHECK_NOTHROW(org.add_sub("Tarik", "Wissam")
                      .add_sub("Tarik", "Eli")
                      .add_sub("Wissam", "Ella"));
}

TEST_CASE("Iteratos Test")
{

    OrgChart org;
    org.add_root("Tarik").add_sub("Tarik", "Wissam").add_sub("Tarik", "Eli").add_sub("Wissam", "Ella");

    // Level Order
    vector<string> names{"Tarik", "Wissam", "Eli", "Ella"};
    size_t i = 0;
    for (Iterator it = org.begin(); it != org.end(); ++it)
    {
        CHECK(*it == names[i]);
        i++;
    }

    // Reveresed Level Order
    names = vector<string>{"Ella", "Wissam", "Eli", "Tarik"};
    i = 0;
    for (Iterator it = org.begin_reverse_order(); it != org.end_reverse_order(); ++it)
    {
        CHECK(*it == names[i]);
        i++;
    }

    // pre order
    names = vector<string>{"Tarik", "Wissam", "Ella", "Eli"};
    i = 0;
    for (Iterator it = org.begin_preorder(); it != org.end_preorder(); ++it)
    {
        CHECK(*it == names[i]);
        i++;
    }
}

TEST_CASE("invalid input")
{
    OrgChart organization;
    organization.add_root("CEO")
        .add_sub("CEO", "CTO")
        .add_sub("CEO", "CFO")
        .add_sub("CEO", "COO")
        .add_sub("CTO", "VP_SW")
        .add_sub("COO", "VP_BI");
    std::string str = "C";
    for (int i = 0; i < 10; i++)
    {
        CHECK_THROWS(organization.add_sub(str, "VP_BI"));
        str += "B";
    }
}