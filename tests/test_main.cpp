#define CATCH_CONFIG_MAIN

#include <string>

#include <catch.hpp>
#include <file.hpp>
#include <miscellaneous.hpp>

TEST_CASE("Testing the File class", "[File]")
{
    Djinni::File testFile1;
	testFile1.set_filename("filename");

    testFile1.line_buffer[0] = "TestLine1";

    Djinni::File* filepointer = &testFile1;
    REQUIRE(filepointer->get_filename() == testFile1.get_filename());

    filepointer->line_buffer[0] = "Test2";

    REQUIRE(filepointer->line_buffer[0] == testFile1.line_buffer[0]);
}

TEST_CASE("Testing the miscellaneous functions and variables", "[Misc]")
{
	// digit_num function. Should return the # of digits in a number
    REQUIRE(Djinni::Miscellaneous::digit_num(1) == 1);
    REQUIRE(Djinni::Miscellaneous::digit_num(123) == 3);
    REQUIRE(Djinni::Miscellaneous::digit_num(1000000001) == 10);
    REQUIRE(Djinni::Miscellaneous::digit_num(3011) == 4);
    REQUIRE(Djinni::Miscellaneous::digit_num(-1) == 2);
}
