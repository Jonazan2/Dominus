//
//  LayoutTest.cpp
//  ProjectWar
//
//  Created by Alvaro Chambi Campos on 29/8/15.
//  Copyright (c) 2015 Alvaro Chambi Campos. All rights reserved.
//

#include <stdio.h>
#include "gtest/gtest.h"
#include "Layout.h"

class LayoutTest : public ::testing::Test
{
public:
    
    LayoutTest()
    {
        layout = new Layout;
    }
    
    virtual void SetUp()
    {
        layout->components.push_back(new UIComponent);
        layout->components.push_back(new UIComponent);
    }
    
    virtual void TearDown()
    {
        dispositionPoints.clear();
        layout->components.clear();
    }
    
    std::vector<glm::vec2> dispositionPoints;
    Layout* layout;
    
};

TEST_F(LayoutTest, LayoutDispositionTest)
{
    layout->width = 640;
    layout->height = 480;
    dispositionPoints = layout->layoutDisposition();
    
    ASSERT_EQ(0, dispositionPoints.at(0).x);
    ASSERT_EQ(0, dispositionPoints.at(0).y);
    
    ASSERT_EQ(640, dispositionPoints.at(1).x);
    ASSERT_EQ(480, dispositionPoints.at(1).y);
    
    ASSERT_EQ(0, dispositionPoints.at(2).x);
    ASSERT_EQ(0, dispositionPoints.at(2).y);
    
    ASSERT_EQ(640, dispositionPoints.at(3).x);
    ASSERT_EQ(480, dispositionPoints.at(3).y);
}

TEST_F(LayoutTest, assignFramesTest)
{
    glm::vec2 start = glm::vec2(0,100);
    glm::vec2 end = glm::vec2(200, 200);
    dispositionPoints.push_back(start);
    dispositionPoints.push_back(end);
    
    start = glm::vec2(200,200);
    end = glm::vec2(400,300);
    dispositionPoints.push_back(start);
    dispositionPoints.push_back(end);
    
    layout->assignFrames(dispositionPoints);

    UIComponent* component = layout->components.front();
    layout->components.pop_front();
    
    ASSERT_EQ(0, component->frame.position.x);
    ASSERT_EQ(100, component->frame.position.y);
    
    ASSERT_EQ(200, component->frame.width);
    ASSERT_EQ(100, component->frame.height);
    
    component = layout->components.front();
    layout->components.pop_front();
    
    ASSERT_EQ(200, component->frame.position.x);
    ASSERT_EQ(200, component->frame.position.y);
    
    ASSERT_EQ(200, component->frame.width);
    ASSERT_EQ(100, component->frame.height);
}