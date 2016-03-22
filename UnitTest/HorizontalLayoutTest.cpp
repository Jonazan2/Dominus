//
//  HorizontalLayoutTest.cpp
//  ProjectWar
//
//  Created by Alvaro Chambi Campos on 3/9/15.
//  Copyright (c) 2015 Alvaro Chambi Campos. All rights reserved.
//

#include <stdio.h>
#include "gtest/gtest.h"
#include "HorizontalLayout.h"

class HorizontalLayoutTest : public ::testing::Test
{
public:
    
    HorizontalLayoutTest()
    {
        horizontalLayout = new HorizontalLayout;
        component0 = new UIComponent;
        component1 = new UIComponent;
        component2 = new UIComponent;
    }
    
    virtual void SetUp()
    {
        horizontalLayout->width = 1000;
        horizontalLayout->height = 500;
    }
    
    virtual void TearDown()
    {
        horizontalLayout->components.clear();
        points.clear();
        component0 = new UIComponent;
        component1 = new UIComponent;
    }
    
    HorizontalLayout* horizontalLayout;
    std::vector<glm::vec2> points;
    UIComponent* component0;
    UIComponent* component1;
    UIComponent* component2;
};

TEST_F(HorizontalLayoutTest, WrapComponentsFitInContainer)
{
    component0->width = 200;
    component0->height = 500;
    
    component1->width = 200;
    component1->height = 500;
    
    horizontalLayout->components.push_back(component0);
    horizontalLayout->components.push_back(component1);
    
    points = horizontalLayout->wrapDisposition();
    
    glm::vec2 start = points.at(0);
    glm::vec2 end = points.at(1);
    ASSERT_EQ(0 , start.x);
    ASSERT_EQ(0 , start.y);
    
    ASSERT_EQ(200 , end.x);
    ASSERT_EQ(500 , end.y);
    
    start = points.at(2);
    end = points.at(3);
    ASSERT_EQ(200, start.x);
    ASSERT_EQ(0 , start.y);
    
    ASSERT_EQ(400 , end.x);
    ASSERT_EQ(500 , end.y);
}

TEST_F(HorizontalLayoutTest, WrapComponentsAdjustWidth)
{
    component0->width = 600;
    component0->height = 500;
    
    component1->width = 500;
    component1->height = 500;
    
    horizontalLayout->components.push_back(component0);
    horizontalLayout->components.push_back(component1);
    
    points = horizontalLayout->wrapDisposition();
    
    glm::vec2 start = points.at(0);
    glm::vec2 end = points.at(1);
    ASSERT_EQ(0 , start.x);
    ASSERT_EQ(0 , start.y);
    
    ASSERT_EQ(600 , end.x);
    ASSERT_EQ(500 , end.y);
    
    start = points.at(2);
    end = points.at(3);
    ASSERT_EQ(600, start.x);
    ASSERT_EQ(0 , start.y);
    
    ASSERT_EQ(1000 , end.x);
    ASSERT_EQ(500 , end.y);
}

TEST_F(HorizontalLayoutTest, WrapComponentsAdjustHeight)
{
    component0->width = 200;
    component0->height = 600;
    
    component1->width = 200;
    component1->height = 300;
    
    horizontalLayout->components.push_back(component0);
    horizontalLayout->components.push_back(component1);
    
    points = horizontalLayout->wrapDisposition();
    
    glm::vec2 start = points.at(0);
    glm::vec2 end = points.at(1);
    ASSERT_EQ(0 , start.x);
    ASSERT_EQ(0 , start.y);
    
    ASSERT_EQ(200 , end.x);
    ASSERT_EQ(500 , end.y);
    
    start = points.at(2);
    end = points.at(3);
    ASSERT_EQ(200, start.x);
    ASSERT_EQ(0 , start.y);
    
    ASSERT_EQ(400 , end.x);
    ASSERT_EQ(500 , end.y);
}

TEST_F(HorizontalLayoutTest, WeightComponentsPositiveValues)
{
    component0->height = 500;
    component0->weight = 3;
    
    component1->height = 500;
    component1->weight = 1;
    
    
    horizontalLayout->components.push_back(component0);
    horizontalLayout->components.push_back(component1);
    
    points = horizontalLayout->weightDisposition();
    
    glm::vec2 start = points.at(0);
    glm::vec2 end = points.at(1);
    ASSERT_EQ(0 , start.x);
    ASSERT_EQ(0 , start.y);
    
    ASSERT_EQ(750 , end.x);
    ASSERT_EQ(500 , end.y);
    
    start = points.at(2);
    end = points.at(3);
    ASSERT_EQ(750, start.x);
    ASSERT_EQ(0 , start.y);
    
    ASSERT_EQ(1000 , end.x);
    ASSERT_EQ(500 , end.y);
}

TEST_F(HorizontalLayoutTest, WeightComponentsAdjustHeight)
{
    component0->height = 600;
    component0->weight = 1;
    
    component1->height = 300;
    component1->weight = 1;
    
    
    horizontalLayout->components.push_back(component0);
    horizontalLayout->components.push_back(component1);
    
    points = horizontalLayout->weightDisposition();
    
    glm::vec2 start = points.at(0);
    glm::vec2 end = points.at(1);
    ASSERT_EQ(0 , start.x);
    ASSERT_EQ(0 , start.y);
    
    ASSERT_EQ(500 , end.x);
    ASSERT_EQ(500 , end.y);
    
    start = points.at(2);
    end = points.at(3);
    ASSERT_EQ(500, start.x);
    ASSERT_EQ(0 , start.y);
    
    ASSERT_EQ(1000 , end.x);
    ASSERT_EQ(500 , end.y);
}

TEST_F(HorizontalLayoutTest, WeightComponentsSomeInvalidValues)
{
    component0->height = 500;
    component0->weight = 1;
    
    component1->height = 500;
    component1->weight = -1;
    
    
    horizontalLayout->components.push_back(component0);
    horizontalLayout->components.push_back(component1);
    
    points = horizontalLayout->weightDisposition();
    
    glm::vec2 start = points.at(0);
    glm::vec2 end = points.at(1);
    ASSERT_EQ(0 , start.x);
    ASSERT_EQ(0 , start.y);
    
    ASSERT_EQ(1000 , end.x);
    ASSERT_EQ(500 , end.y);
    
    start = points.at(2);
    end = points.at(3);
    ASSERT_EQ(1000, start.x);
    ASSERT_EQ(0 , start.y);
    
    ASSERT_EQ(1000 , end.x);
    ASSERT_EQ(500 , end.y);
}

TEST_F(HorizontalLayoutTest, WeightComponentsAllInvalidValues)
{
    component0->height = 500;
    component0->weight = 0;
    
    component1->height = 500;
    component1->weight = -1;
    
    
    horizontalLayout->components.push_back(component0);
    horizontalLayout->components.push_back(component1);
    
    points = horizontalLayout->weightDisposition();
    
    glm::vec2 start = points.at(0);
    glm::vec2 end = points.at(1);
    ASSERT_EQ(0 , start.x);
    ASSERT_EQ(0 , start.y);
    
    ASSERT_EQ(0 , end.x);
    ASSERT_EQ(500 , end.y);
    
    start = points.at(2);
    end = points.at(3);
    ASSERT_EQ(0, start.x);
    ASSERT_EQ(0, start.y);
    
    ASSERT_EQ(0 , end.x);
    ASSERT_EQ(500 , end.y);
}