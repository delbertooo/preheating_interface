#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include "../PreheatingAnswer.hpp"


TEST_CASE( "PreheatingAnswer can count flashes", "[PreheatingAnswer]" ) {

    SECTION( "works with empty flashes" ) {
        std::vector<unsigned long> greens;
        std::vector<unsigned long> reds;
        PreheatingAnswer a(greens, reds);
        REQUIRE( a.CountGreenFlashesWithLength(0) == 0 );
        REQUIRE( a.CountGreenFlashesWithLength(333) == 0 );
        REQUIRE( a.CountGreenFlashesWithLength(1000) == 0 );
    }
    
    SECTION( "counts exact flashes" ) {
        std::vector<unsigned long> greens{ 100, 200, 100, 100 };
        std::vector<unsigned long> reds;
        PreheatingAnswer a(greens, reds);

        REQUIRE( a.CountGreenFlashesWithLength(100) == 3 );
        REQUIRE( a.CountGreenFlashesWithLength(200) == 1 );
        REQUIRE( a.CountGreenFlashesWithLength(300) == 0 );
    }
    
    SECTION( "counts fuzzy flashes up to +/- 10%" ) {
        std::vector<unsigned long> greens{ 100, 105, 95, 110, 90, 89, 111, 1000, 1100, 900 };
        std::vector<unsigned long> reds;
        PreheatingAnswer a(greens, reds);

        REQUIRE( a.CountGreenFlashesWithLength(100) == 5 );
        REQUIRE( a.CountGreenFlashesWithLength(1000) == 3 );
    }
}
