#include "tst_tokentest.h"
#include "tst_lexertest.h"
#include "tst_parsertest.h"
#include "tst_declarationparsertest.h"
#include "tst_instructionparsertest.h"

#include <gtest/gtest.h>

int main(int argc, char *argv[])
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
