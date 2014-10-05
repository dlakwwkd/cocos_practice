#include "cocos2d.h"
#include "Box2D/Box2D.h"
#include "GLES-Render.h"

USING_NS_CC;

class Box2DDebugDrawLayer : public cocos2d::Layer
{
private:
  b2World* world;
  GLESDebugDraw* debugDraw;
  float ptmRatio;
 
public:
  Box2DDebugDrawLayer(b2World* _world, float _ptmRatio);
  static Box2DDebugDrawLayer* create(b2World* _world, float _ptmRatio);
  virtual bool init();
  virtual void draw(Renderer *renderer, const Mat4 &transform, uint32_t flags) override;
};
