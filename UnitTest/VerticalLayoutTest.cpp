//
//  VerticalLayoutTest.cpp
//  ProjectWar
//
//  Created by Alvaro Chambi Campos on 3/9/15.
//  Copyright (c) 2015 Alvaro Chambi Campos. All rights reserved.
//

#include <stdio.h>
#include "gtest/gtest.h"
#include "VerticalLayout.h"

class VerticalLayoutTest : public ::testing::Test
{
public:
    
    VerticalLayoutTest()
    {
        verticalLayout = new VerticalLayout;
        component0 = std::make_shared<UIComponent>( UIComponent() );
        component1 = std::make_shared<UIComponent>( UIComponent() );
        component2 = std::make_shared<UIComponent>( UIComponent() );
    }
    
    virtual void SetUp()
    {
        verticalLayout->width = 500;
        verticalLayout->height = 1000;
    }
    
    virtual void TearDown()
    {
        verticalLayout->components.clear();
        points.clear();
        component0 = std::make_shared<UIComponent>( UIComponent() );
        component1 = std::make_shared<UIComponent>( UIComponent() );
    }
    
    VerticalLayout* verticalLayout;
    std::vector<glm::vec2> points;
    std::shared_ptr<UIComponent> component0;
    std::shared_ptr<UIComponent> component1;
    std::shared_ptr<UIComponent> component2;
};

TEST_F(VerticalLayoutTest, WrapComponentsFitInContainer)
{
    component0->width = 500;
    component0->height = 200;
    
    component1->width = 500;
    component1->height = 200;
    
    verticalLayout->components.push_back(component0);
    verticalLayout->components.push_back(component1);
    
    points = verticalLayout->wrapDisposition();
    
    glm::vec2 start = points.at(0);
    glm::vec2 end = points.at(1);
    ASSERT_EQ(0 , start.x);
    ASSERT_EQ(0 , start.y);
    
    ASSERT_EQ(500 , end.x);
    ASSERT_EQ(200 , end.y);
    
    start = points.at(2);
    end = points.at(3);
    ASSERT_EQ(0, start.x);
    ASSERT_EQ(200 , start.y);
    
    ASSERT_EQ(500 , end.x);
    ASSERT_EQ(400 , end.y);
}

TEST_F(VerticalLayoutTest, WrapComponentsAdjustWidth)
{
    component0->width = 600;
    component0->height = 200;
    
    component1->width = 300;
    component1->height = 200;
    
    verticalLayout->components.push_back(component0);
    verticalLayout->components.push_back(component1);
    
    points = verticalLayout->wrapDisposition();
    
    glm::vec2 start = points.at(0);
    glm::vec2 end = points.at(1);
    ASSERT_EQ(0 , start.x);
    ASSERT_EQ(0 , start.y);
    
    ASSERT_EQ(500 , end.x);
    ASSERT_EQ(200 , end.y);
    
    start = points.at(2);
    end = points.at(3);
    ASSERT_EQ(0, start.x);
    ASSERT_EQ(200 , start.y);
    
    ASSERT_EQ(500 , end.x);
    ASSERT_EQ(400 , end.y);
}

TEST_F(VerticalLayoutTest, WrapComponentsAdjustHeight)
{
    component0->width = 500;
    component0->height = 600;
    
    component1->width = 500;
    component1->height = 500;
    
    verticalLayout->components.push_back(component0);
    verticalLayout->components.push_back(component1);
    
    points = verticalLayout->wrapDisposition();
    
    glm::vec2 start = points.at(0);
    glm::vec2 end = points.at(1);
    ASSERT_EQ(0 , start.x);
    ASSERT_EQ(0 , start.y);
    
    ASSERT_EQ(500 , end.x);
    ASSERT_EQ(600 , end.y);
    
    start = points.at(2);
    end = points.at(3);
    ASSERT_EQ(0, start.x);
    ASSERT_EQ(600 , start.y);
    
    ASSERT_EQ(500 , end.x);
    ASSERT_EQ(1000 , end.y);
}

TEST_F(VerticalLayoutTest, WeightComponentsPositiveValues)
{
    component0->width = 500;
    component0->weight = 3;
    
    component1->width = 500;
    component1->weight = 1;
    
    
    verticalLayout->components.push_back(component0);
    verticalLayout->components.push_back(component1);
    
    points = verticalLayout->weightDisposition();
    
    glm::vec2 start = points.at(0);
    glm::vec2 end = points.at(1);
    ASSERT_EQ(0 , start.x);
    ASSERT_EQ(0 , start.y);
    
    ASSERT_EQ(500 , end.x);
    ASSERT_EQ(750 , end.y);
    
    start = points.at(2);
    end = points.at(3);
    ASSERT_EQ(0, start.x);
    ASSERT_EQ(750 , start.y);
    
    ASSERT_EQ(500 , end.x);
    ASSERT_EQ(1000 , end.y);
}


TEST_F(VerticalLayoutTest, WeightComponentsAdjustWidth)
{
    component0->width = 300;
    component0->weight = 0.5;
    
    component1->width = 600;
    component1->weight = 0.5;
    
    
    verticalLayout->components.push_back(component0);
    verticalLayout->components.push_back(component1);
    
    points = verticalLayout->weightDisposition();
    
    glm::vec2 start = points.at(0);
    glm::vec2 end = points.at(1);
    ASSERT_EQ(0 , start.x);
    ASSERT_EQ(0 , start.y);
    
    ASSERT_EQ(500 , end.x);
    ASSERT_EQ(500 , end.y);
    
    start = points.at(2);
    end = points.at(3);
    ASSERT_EQ(0, start.x);
    ASSERT_EQ(500 , start.y);
    
    ASSERT_EQ(500 , end.x);
    ASSERT_EQ(1000 , end.y);
}


TEST_F(VerticalLayoutTest, WeightComponentsSomeInvalidValues)
{
    component0->width = 500;
    component0->weight = 1;
    
    component1->width = 500;
    component1->weight = -1;
    
    
    verticalLayout->components.push_back(component0);
    verticalLayout->components.push_back(component1);
    
    points = verticalLayout->weightDisposition();
    
    glm::vec2 start = points.at(0);
    glm::vec2 end = points.at(1);
    ASSERT_EQ(0 , start.x);
    ASSERT_EQ(0 , start.y);
    
    ASSERT_EQ(500 , end.x);
    ASSERT_EQ(1000 , end.y);
    
    start = points.at(2);
    end = points.at(3);
    ASSERT_EQ(0, start.x);
    ASSERT_EQ(1000 , start.y);
    
    ASSERT_EQ(500 , end.x);
    ASSERT_EQ(1000 , end.y);
}

TEST_F(VerticalLayoutTest, WeightComponentsAllInvalidValues)
{
    component0->width = 500;
    component0->weight = 0;
    
    component1->width = 500;
    component1->weight = -1;
    
    
    verticalLayout->components.push_back(component0);
    verticalLayout->components.push_back(component1);
    
    points = verticalLayout->weightDisposition();
    
    glm::vec2 start = points.at(0);
    glm::vec2 end = points.at(1);
    ASSERT_EQ(0 , start.x);
    ASSERT_EQ(0 , start.y);
    
    ASSERT_EQ(500 , end.x);
    ASSERT_EQ(0 , end.y);
    
    start = points.at(2);
    end = points.at(3);
    ASSERT_EQ(0, start.x);
    ASSERT_EQ(0, start.y);
    
    ASSERT_EQ(500 , end.x);
    ASSERT_EQ(0 , end.y);
}
