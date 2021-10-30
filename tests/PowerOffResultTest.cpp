#include "catch.hpp"

#include "../libpreheatinginterface/src/LibPreheatingInterface.hpp"


using namespace LibPreheatingInterface;

TEST_CASE( "PowerOffResult", "[PowerOffResult]" ) {

    SECTION( "is success when there are two long red flashes" ) {
        PreheatingAnswer answer{
            {},
            {2000, 2000}
        };

        PowerOffResult result{answer};
        
        REQUIRE( result.IsError() == false );
    }

    SECTION( "is error without any flashes" ) {
        PreheatingAnswer answer{
            {},
            {}
        };

        PowerOffResult result{answer};

        REQUIRE( result.IsError() == true );
    }

    SECTION( "out of range when at least 4 fast red flashes" ) {
        PreheatingAnswer answer{
            {},
            {200, 200, 200, 200}
        };

        PowerOffResult result{answer};

        REQUIRE( result.IsError() == true );
        REQUIRE( result.IsOutOfRange() == true );
    }

    SECTION( "normal out of range scenario" ) {
        PreheatingAnswer answer{
            {2000},
            {2000, 200, 200, 200, 200}
        };

        PowerOffResult result{answer};
        REQUIRE( result.IsError() == true );
        REQUIRE( result.IsOutOfRange() == true );
    }
}
