#pragma once

#include <gtest/gtest.h>
#include <gmock/gmock-matchers.h>

#include "parser.h"

using namespace testing;

//TEST(declarationParserTest, constructorTest)
//{
//}

TEST(declarationParserTest, constantPass)
{
    parser testParser;
    string testString = "  .data\n  constantC = 352";

    stringstream testSS;
    testSS << testString;

    EXPECT_TRUE(testParser.parseStream(testSS));
}

//TEST(declarationParserTest, constantFail)
//{
//    parser testParser;
//    string testString = ".data\nconstantA = H2";

//    stringstream testSS;
//    testSS << testString;

//    EXPECT_FALSE(testParser.parseStream(testSS));
//}
