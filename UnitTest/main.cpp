//
//  main.cpp
//  UnitTest
//
//  Created by Alvaro Chambi Campos on 28/2/16.
//  Copyright © 2016 frikazos. All rights reserved.
//

#include "gtest/gtest.h"

int main(int argc, char * argv[])
{
    //::testing::InitGoogleMock(&argc, argv);
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}