#include "catch.hpp"
#include "../src/HardwareInterface/PreheatingAnswer.hpp"

using namespace HardwareInterface;

TEST_CASE( "PreheatingAnswer can count flashes", "[PreheatingAnswer]" ) {

    SECTION( "works with empty flashes" ) {
        std::vector<unsigned long> greens;
        std::vector<unsigned long> reds;
        PreheatingAnswer a{greens, reds};
        REQUIRE( a.CountGreenFlashesWithLength(0) == 0 );
        REQUIRE( a.CountGreenFlashesWithLength(333) == 0 );
        REQUIRE( a.CountGreenFlashesWithLength(1000) == 0 );
    }
    
    SECTION( "counts exact flashes" ) {
        std::vector<unsigned long> greens{ 100, 200, 100, 100 };
        std::vector<unsigned long> reds;
        PreheatingAnswer a{greens, reds};

        REQUIRE( a.CountGreenFlashesWithLength(100) == 3 );
        REQUIRE( a.CountGreenFlashesWithLength(200) == 1 );
        REQUIRE( a.CountGreenFlashesWithLength(300) == 0 );
    }
    
    SECTION( "counts fuzzy flashes up to +/- 10%" ) {
        std::vector<unsigned long> greens{ 100, 105, 95, 110, 90, 89, 111, 1000, 1100, 900 };
        std::vector<unsigned long> reds;
        PreheatingAnswer a{greens, reds};

        REQUIRE( a.CountGreenFlashesWithLength(100) == 5 );
        REQUIRE( a.CountGreenFlashesWithLength(1000) == 3 );
    }

    SECTION( "between two thresholds" ) {
        std::vector<unsigned long> greens{ 100, 200, 110, 300, 180, 1300, 550 };
        std::vector<unsigned long> reds{ greens };
        PreheatingAnswer a{greens, reds};

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
