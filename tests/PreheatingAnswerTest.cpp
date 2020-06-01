#include "catch.hpp"
#include "../src/HardwareInterface/PreheatingAnswer.hpp"

using namespace HardwareInterface;

TEST_CASE( "PreheatingAnswer can count flashes", "[PreheatingAnswer]" ) {

    SECTION( "works with empty flashes" ) {
        PreheatingAnswer a{{}, {}};
        REQUIRE( a.CountGreenFlashesWithLength(0) == 0 );
        REQUIRE( a.CountGreenFlashesWithLength(333) == 0 );
        REQUIRE( a.CountGreenFlashesWithLength(1000) == 0 );
    }
    
    SECTION( "counts exact flashes" ) {
        PreheatingAnswer a{{ 100, 200, 100, 100 }, {}};

        REQUIRE( a.CountGreenFlashesWithLength(100) == 3 );
        REQUIRE( a.CountGreenFlashesWithLength(200) == 1 );
        REQUIRE( a.CountGreenFlashesWithLength(300) == 0 );
    }
    
    SECTION( "counts fuzzy flashes up to +/- 10%" ) {
        PreheatingAnswer a{{ 100, 105, 95, 110, 90, 89, 111, 1000, 1100, 900 }, {}};

        REQUIRE( a.CountGreenFlashesWithLength(100) == 5 );
        REQUIRE( a.CountGreenFlashesWithLength(1000) == 3 );
    }

    SECTION( "between two thresholds" ) {
        PreheatingAnswer a{
            { 100, 200, 110, 300, 180, 1300, 550 },
            { 100, 200, 110, 300, 180, 1300, 550 }
        };

        SECTION( "small margin, nothing matches" ) {
            REQUIRE( a.CountGreenFlashesBetween(0, 0) == 0 );
            REQUIRE( a.CountRedFlashesBetween(0, 0) == 0 );
        }

        SECTION( "exact hit" ) {
            REQUIRE( a.CountGreenFlashesBetween(100, 100) == 1 );
            REQUIRE( a.CountRedFlashesBetween(100, 100) == 1 );
        }
        

        SECTION( "wrong order won't find anything" ) {
            REQUIRE( a.CountGreenFlashesBetween(101, 99) == 0 );
            REQUIRE( a.CountRedFlashesBetween(101, 99) == 0 );
        }
        
        SECTION( "close miss" ) {
            REQUIRE( a.CountGreenFlashesBetween(101, 109) == 0 );
            REQUIRE( a.CountRedFlashesBetween(101, 109) == 0 );
        }
        
        SECTION( "fuzzy hits" ) {
            REQUIRE( a.CountGreenFlashesBetween(95, 105) == 1 );
            REQUIRE( a.CountRedFlashesBetween(95, 105) == 1 );

            REQUIRE( a.CountGreenFlashesBetween(100, 200) == 4 );
            REQUIRE( a.CountRedFlashesBetween(100, 200) == 4 );

            REQUIRE( a.CountGreenFlashesBetween(250, 600) == 2 );
            REQUIRE( a.CountRedFlashesBetween(250, 600) == 2 );

            REQUIRE( a.CountGreenFlashesBetween(0, 10000) == 7 );
            REQUIRE( a.CountRedFlashesBetween(0, 10000) == 7 );
        }
    }
}
