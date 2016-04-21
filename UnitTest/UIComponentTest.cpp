//
//  main.cpp
//  Test
//
//  Created by Alvaro Chambi Campos on 4/6/15.
//  Copyright (c) 2015 Alvaro Chambi Campos. All rights reserved.
//

#include <iostream>
#include "UIComponent.h"
#include "gtest/gtest.h"

namespace {
    
    // The fixture for testing class Foo.
    class UIComponentTest : public ::testing::Test {
    protected:
        UIComponentTest() {
            component = new UIComponent;
        }
        
        virtual void SetUp() {
            component->width = 100;
            component->height = 100;
            component->params = Params();
        }
        
        virtual void TearDown() {
            component->width = 100;
            component->height = 100;
            
            component->params = Params();
        }
        
        UIComponent* component;
        
    };
    
    TEST_F(UIComponentTest, InitialFlagsTest)
    {
        UIComponent* uiComponent = new UIComponent;
        
        ASSERT_EQ(0, uiComponent->width);
        ASSERT_EQ(0, uiComponent->height);
        ASSERT_FALSE(uiComponent->isHUD());
        ASSERT_TRUE(uiComponent->isVisible());
        ASSERT_TRUE(uiComponent->parent == nullptr);
    }
    
    TEST_F(UIComponentTest, MeasureDimensionFillTest)
    {
        UIComponent* layout = new UIComponent;
        layout->width = 640;
        layout->height = 480;
        
        component->setParent(layout);
        component->measureDimension();
        
        ASSERT_EQ(640, component->width);
        ASSERT_EQ(480, component->height);
    }
    
    TEST_F(UIComponentTest, measureDimensionWrapTest)
    {
        UIComponent* layout = new UIComponent;
        layout->params.width = 640;
        layout->params.height = 480;
        
        component->texture = std::make_shared<Texture>( Texture() );
        component->texture->setWidth(50);
        component->texture->setHeight(50);
        component->params.width = WRAP;
        component->params.height = WRAP;
        
        component->setParent(layout);
        component->measureDimension();
        
        ASSERT_EQ(50, component->width);
        ASSERT_EQ(50, component->height);
    }
    
    TEST_F(UIComponentTest, MeasureDimensionDefaultTest)
    {
        UIComponent* layout = new UIComponent;
        layout->width = 640;
        layout->height = 480;
        
        Params params;
        params.width = 50;
        params.height = 50;
        params.gravity = CENTER;
        component->setParams(params);
        component->setParent(layout);
        component->measureDimension();
        
        ASSERT_EQ(50, component->width);
        ASSERT_EQ(50, component->height);
    }
    
    TEST_F(UIComponentTest, MeasureDimensionFillInvalidValues)
    {
        UIComponent* layout = new UIComponent;
        layout->width = 0;
        layout->height = -5;
        
        Params params;
        params.width = FILL;
        params.height = FILL;
        params.gravity = CENTER;
        component->setParams(params);
        component->setParent(layout);
        component->measureDimension();
        
        ASSERT_EQ(0, component->width);
        ASSERT_EQ(0, component->height);
    }
    
    TEST_F(UIComponentTest, MeasureDimensionParamsInvalidValues)
    {
        UIComponent* layout = new UIComponent;
        layout->width = 640;
        layout->height = 480;
        
        Params params;
        params.width = -50;
        params.height = 0;
        params.gravity = CENTER;
        component->setParams(params);
        component->setParent(layout);
        component->measureDimension();
        
        ASSERT_EQ(0, component->width);
        ASSERT_EQ(0, component->height);
    }
    
    
    
    TEST_F(UIComponentTest,CenterComponentInParent)
    {
        component->center(glm::vec2(0,0), 500, 500);
        
        ASSERT_EQ(200, component->position.x);
        ASSERT_EQ(200, component->position.y);
    }
    
    TEST_F(UIComponentTest,UpComponentInParent)
    {
        component->up(glm::vec2(0,0), 500, 500);
        
        ASSERT_EQ(200, component->position.x);
        ASSERT_EQ(0, component->position.y);
    }
    
    TEST_F(UIComponentTest, DownComponentInParent)
    {
        component->down(glm::vec2(0,0), 500, 500);
        
        ASSERT_EQ(200, component->position.x);
        ASSERT_EQ(400, component->position.y);
    }
    
    TEST_F(UIComponentTest, RightComponentInParent)
    {
        component->right(glm::vec2(0,0), 500, 500);
        
        ASSERT_EQ(400, component->position.x);
        ASSERT_EQ(200, component->position.y);
    }
    
    TEST_F(UIComponentTest, LeftComponentInParent)
    {
        component->left(glm::vec2(0,0), 500, 500);
        
        ASSERT_EQ(0, component->position.x);
        ASSERT_EQ(200, component->position.y);
    }
    
    TEST_F(UIComponentTest, CenterComponentWithMargins)
    {
        component->params.marginTop = 200;
        component->params.marginLeft = 200;
        
        component->center(glm::vec2(0,0), 500, 500);
        
        ASSERT_EQ(100, component->position.x);
        ASSERT_EQ(100, component->position.y);
    }
    
    TEST_F(UIComponentTest, UpComponentWithMargins)
    {
        component->params.marginTop = 200;
        component->params.marginLeft = 200;
        
        component->up(glm::vec2(0,0), 500, 500);
        
        ASSERT_EQ(100, component->position.x);
        ASSERT_EQ(0, component->position.y);
    }
    
    TEST_F(UIComponentTest, DownComponentWithMargins)
    {
        component->params.marginTop = 200;
        component->params.marginLeft = 200;
        
        component->down(glm::vec2(0,0), 500, 500);
        
        ASSERT_EQ(100, component->position.x);
        ASSERT_EQ(200, component->position.y);
    }
    
    TEST_F(UIComponentTest, LeftComponentWithMargins)
    {
        component->params.marginTop = 200;
        component->params.marginLeft = 200;
        
        component->left(glm::vec2(0,0), 500, 500);
        
        ASSERT_EQ(0, component->position.x);
        ASSERT_EQ(100, component->position.y);
    }
    
    TEST_F(UIComponentTest, RightComponentWithMargins)
    {
        component->params.marginTop = 200;
        component->params.marginLeft = 200;
        
        component->right(glm::vec2(0,0), 500, 500);
        
        ASSERT_EQ(200, component->position.x);
        ASSERT_EQ(100, component->position.y);
    }
    
    TEST_F(UIComponentTest, RescaleContentWiderThanContainer)
    {
        component->width = 600;
        component->readjustDimension(500, 500);
        
        ASSERT_EQ(500, component->width);
        ASSERT_EQ(100, component->height);
        
    }
    
    TEST_F(UIComponentTest, RescaleContentHigherThanContainer)
    {
        component->height = 600;
        component->readjustDimension(500, 500);
        
        ASSERT_EQ(500, component->height);
        ASSERT_EQ(100, component->width);
    }
    
    TEST_F(UIComponentTest, RescaleContentWiderHigherThanContainer)
    {
        component->width = 800;
        component->height = 800;

        component->readjustDimension(100, 100);
        
        ASSERT_EQ(100, component->height);
        ASSERT_EQ(100, component->width);
    }
    
    TEST_F(UIComponentTest, RescaleContentMarginsWiderThanContainer)
    {
        component->params.marginLeft = 250;
        component->params.marginRight = 250;
        
        component->readjustDimension(500, 500);
        
        ASSERT_EQ(100, component->height);
        ASSERT_EQ(0, component->width);
    }
    
    TEST_F(UIComponentTest, RescaleContentMarginsHigherThanContainer)
    {
        component->params.marginTop = 250;
        component->params.marginDown = 250;
        
        component->readjustDimension(500, 500);
        
        ASSERT_EQ(0, component->height);
        ASSERT_EQ(100, component->width);
    }
    
    TEST_F(UIComponentTest, RescaleContentMarginLeft)
    {
        component->params.marginLeft = 450;
        
        component->readjustDimension(500, 500);
        
        ASSERT_EQ(50, component->width);
        ASSERT_EQ(100, component->height);
    }
    
    TEST_F(UIComponentTest, RescaleContentMarginRigth)
    {
        component->params.marginRight = 450;
        component->readjustDimension(500, 500);
        ASSERT_EQ(50, component->width);
        ASSERT_EQ(100, component->height);
    }
    
    TEST_F(UIComponentTest, RescaleContentMarginTop)
    {
        component->params.marginTop = 450;
        component->readjustDimension(500, 500);
        
        ASSERT_EQ(100, component->width);
        ASSERT_EQ(50, component->height);
    }
    
    TEST_F(UIComponentTest, RescaleContentMarginDown)
    {
        component->params.marginDown = 450;
        component->readjustDimension(500, 500);
        
        ASSERT_EQ(100, component->width);
        ASSERT_EQ(50, component->height);
    }
    
    TEST_F(UIComponentTest, ReadjustMarginLeft)
    {
        component->params.marginLeft = 200;
        component->position = glm::vec2(100, 200);
        
        component->readjustPosition();
        
        ASSERT_EQ(300, component->position.x);
        ASSERT_EQ(200, component->position.y);
    }
    
    TEST_F(UIComponentTest, ReadjustMarginTop)
    {
        component->params.marginTop = 200;
        component->position = glm::vec2(200, 100);
        
        component->readjustPosition();
        
        ASSERT_EQ(200, component->position.x);
        ASSERT_EQ(300, component->position.y);
    }
    
    TEST_F(UIComponentTest, ReadjustMarginTopLeft)
    {
        component->params.marginTop = 200;
        component->params.marginLeft = 200;
        component->position = glm::vec2(100, 100);
        
        component->readjustPosition();
        
        ASSERT_EQ(300, component->position.x);
        ASSERT_EQ(300, component->position.y);
    }
    
    TEST_F(UIComponentTest, ReadjustMarginDownRight)
    {
        component->params.marginDown = 200;
        component->params.marginRight = 200;
        component->position = glm::vec2(100, 100);
        
        component->readjustPosition();
        
        ASSERT_EQ(100, component->position.x);
        ASSERT_EQ(100, component->position.y);
    }
    
    //TODO: Implement resize
    
//    TEST_F(UIComponentTest, ResizeWidthTest)
//    {
//        
//        component->resize(0.5, 1);
//        
//        ASSERT_EQ(50, component->width);
//        ASSERT_EQ(100, component->height);
//    }
//    
//    TEST_F(UIComponentTest, ResizeHeightTest)
//    {
//        component->resize(1, 0.5);
//        
//        ASSERT_EQ(100, component->width);
//        ASSERT_EQ(50, component->height);
//    }
//    
//    TEST_F(UIComponentTest, ResizeWidthHeightTest)
//    {
//        
//        component->resize(0.7, 1.5);
//        
//        ASSERT_EQ(70, component->width);
//        ASSERT_EQ(150, component->height);
//    }
//    
//    TEST_F(UIComponentTest, ResizeInvalidValues)
//    {
//        component->resize(-1, 0);
//        
//        ASSERT_EQ(0, component->width);
//        ASSERT_EQ(0, component->height);
//    }
}

//int main(int argc, char **argv) {
//    ::testing::InitGoogleTest(&argc, argv);
//    return RUN_ALL_TESTS();
//}
