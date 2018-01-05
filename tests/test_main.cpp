#define CATCH_CONFIG_MAIN

#include <string>

#include <catch.hpp>
#include <file.hpp>

TEST_CASE("Testing the File class", "[File]")
{
    Djinni::File testFile1("Filename");

    testFile1.line_buffer[0] = "TestLine1";

    Djinni::File* filepointer = &testFile1;
    REQUIRE(filepointer->getFilename() == testFile1.getFilename());

    filepointer->line_buffer[0] = "Test2";

    REQUIRE(filepointer->line_buffer[0] == testFile1.line_buffer[0]);
}
