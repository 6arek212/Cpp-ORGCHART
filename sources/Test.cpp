#include <iostream>
#include "OrgChart.hpp"
#include "doctest.h"
#include <string>
#include <vector>
using namespace ariel;
using namespace std;

TEST_CASE("Bad Op")
{
    OrgChart org;

    CHECK_THROWS(org.add_sub("tarik", "aaa"));
    org.add_root("Traik");
    CHECK_THROWS(org.add_sub("aa", "bb"));

    CHECK_NOTHROW(org.add_sub("Tarik", "Wissam")
                      .add_sub("Tarik", "Eli")
                      .add_sub("Wissam", "Ella"));


}
