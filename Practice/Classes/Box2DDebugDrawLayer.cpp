#include "Box2DDebugDrawLayer.h"

Box2DDebugDrawLayer* Box2DDebugDrawLayer::create(b2World* _world, float _ptmRatio)
{
  auto box2DDebugDrawLayer = new Box2DDebugDrawLayer(_world, _ptmRatio);
  if (box2DDebugDrawLayer != NULL && box2DDebugDrawLayer->init())
  {
    box2DDebugDrawLayer->autorelease();
    return box2DDebugDrawLayer;
  }
  else
  {
    delete box2DDebugDrawLayer;
    box2DDebugDrawLayer = NULL;
    return NULL;
  }
}
Box2DDebugDrawLayer::Box2DDebugDrawLayer(b2World* _world, float _ptmRatio)
{
	world = _world;
	ptmRatio = _ptmRatio;
}

bool Box2DDebugDrawLayer::init()
{
  if(!Layer::init())
  {
    return false;
  }
  
  debugDraw = new GLESDebugDraw(ptmRatio);
  world->SetDebugDraw(debugDraw);
  
  uint32 flags = 0;
  flags += b2Draw::e_shapeBit;
  flags += b2Draw::e_jointBit;
//   flags += b2Draw::e_aabbBit;
//   flags += b2Draw::e_pairBit;
  flags += b2Draw::e_centerOfMassBit;
  debugDraw->SetFlags(flags);
  
  return true;
}

void Box2DDebugDrawLayer::draw(Renderer *renderer, const Mat4 &transform, uint32_t flags)
{
  ccGLEnableVertexAttribs( kCCVertexAttribFlag_Position );
  kmGLPushMatrix();
  world->DrawDebugData();  
  kmGLPopMatrix();
}
