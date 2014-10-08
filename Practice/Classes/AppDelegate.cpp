#include "AppDelegate.h"
#include "GameScene.h"
#include "GameScene2.h"
#include "MainScene.h"

USING_NS_CC;

AppDelegate::AppDelegate() {

}

AppDelegate::~AppDelegate() 
{
}

void AppDelegate::initGLContextAttrs()
{
    //red,green,blue,alpha,depth,stencil
    GLContextAttrs glContextAttrs = {8, 8, 8, 8, 24, 8};
    GLView::setGLContextAttrs(glContextAttrs);
}

bool AppDelegate::applicationDidFinishLaunching()
{
    auto director = Director::getInstance();
    auto glview = director->getOpenGLView();
    if(!glview) {
        glview = GLViewImpl::create("My Game");
        director->setOpenGLView(glview);

		glview->setFrameSize(1280, 720);
		glview->setDesignResolutionSize(1280, 720, ResolutionPolicy::NO_BORDER);
    }

    // turn on display FPS
    director->setDisplayStats(true);
    director->setAnimationInterval(1.0 / 60);

    // create a scene. it's an autorelease object
    auto scene = GameScene2::createScene();

    // run
    director->runWithScene(scene);
    return true;
}



void AppDelegate::applicationDidEnterBackground() {
    Director::getInstance()->stopAnimation();
}
void AppDelegate::applicationWillEnterForeground() {
    Director::getInstance()->startAnimation();
}
