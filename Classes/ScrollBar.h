
#ifndef _SCROLL_BAR_H_
#define _SCROLL_BAR_H_

#include "cocos2d.h"
#include "cocos-ext.h"

USING_NS_CC;
USING_NS_CC_EXT;

enum {
	VERTICAL_IN = 1,
	VERTICAL_OUT = 2,
	HORIZONTAL_IN = 3,
	HORIZONTAL_OUT = 4,
};

class ScrollBar : public CCScale9Sprite
{
private:
	int _type;
	float _fadeDelayTime;
	float _svFixSize, _nowContentSize, _beforeContentSize, _barSize;
	bool _canFade;
	CCScrollView* _target;

public:
	ScrollBar( CCScrollView* table, int type );
	virtual ~ScrollBar();
	static ScrollBar* create( CCScrollView* table, int type );

	void SetCanFadeBar( bool isFade ) { _canFade = isFade; }
	void SetFadeDelayTime( float fadeDelayTime ) { _fadeDelayTime = fadeDelayTime; }

	void FadeOut( float dt );
	void FadeIn( float dt );
	void RefreshPosition();
	void RefreshScale();
	void Refresh();
};

#endif