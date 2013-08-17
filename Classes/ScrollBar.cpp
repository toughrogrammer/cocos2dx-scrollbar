
#include "ScrollBar.h"

#define barFixSize 10.0f
#define barMinSize 20.0f

const char* VERTICAL_TEXTURE_PATH = "scrollbar\\barV.png";
const char* HORIZONTAL_TEXTURE_PATH = "scrollbar\\barH.png";

ScrollBar::ScrollBar( CCScrollView* sv, int type )
	: _type( type )
	, _fadeDelayTime( 1.0f )
	, _svFixSize( 0 )
	, _nowContentSize( 0 )
	, _beforeContentSize( 0 )
	, _barSize( 0 )
	, _canFade( true )
	, _target( sv )
{
	CCPoint svPosition = _target->getPosition();
	CCSize svSize = _target->cocos2d::CCNode::getContentSize();
	
	switch( type )
	{
	case VERTICAL_IN:
	case VERTICAL_OUT:
		initWithFile( VERTICAL_TEXTURE_PATH, 
			CCRectMake( 0, 0, barFixSize, barMinSize ),
			CCRectMake( 2, 5, 6, 10 ) );
		_svFixSize = svSize.height;
		_nowContentSize = _beforeContentSize = _target->getContentSize().height;
		break;
	case HORIZONTAL_IN:
	case HORIZONTAL_OUT:
		initWithFile( HORIZONTAL_TEXTURE_PATH, 
			CCRectMake( 0, 0, barMinSize, barFixSize ),
			CCRectMake( 5, 2, 10, 6 ) );
		_svFixSize = svSize.width;
		_nowContentSize = _beforeContentSize = _target->getContentSize().width;
		break;
	}

	// Is there some bug on CCScale9Sprite? Anchor point is not working.... 
	// There is not difference with anchor point (0, 0) and (0.5, 0.5)
	setAnchorPoint( CCPointMake( 0.5, 0.5 ) );
	Refresh();

	_target->addChild( this, 0, 10 );

	scheduleOnce( schedule_selector( ScrollBar::FadeOut ), _fadeDelayTime );
}


ScrollBar::~ScrollBar()
{

}


ScrollBar* ScrollBar::create( CCScrollView* sv, int type )
{
	ScrollBar *pReturn = new ScrollBar( sv, type );
	if( pReturn )
	{
		pReturn->autorelease();
		return pReturn;
	}
	else
	{
		delete pReturn;
		return NULL;
	}
}


void ScrollBar::FadeOut( float dt )
{
	if( _canFade )
	{
		float x, y;
		switch( _type )
		{
		case VERTICAL_IN:
		case VERTICAL_OUT:
			x = 0.0f;
			y = 1.0f;
			break;

		case HORIZONTAL_IN:
		case HORIZONTAL_OUT:
			x = 1.0f;
			y = 0.0f;
			break;
		}

		CCAction* action = CCScaleTo::create( 0.1f, x, y );
		this->runAction( action );
	}
}


void ScrollBar::FadeIn( float dt )
{
	if( _canFade )
	{
		CCAction* action = CCScaleTo::create( 0.1f, 1.0f, 1.0f );
		this->runAction( action );
	}
}


void ScrollBar::RefreshPosition()
{
	CCSize targetContentSize = _target->getContentSize();
	CCSize targetViewSize = _target->getViewSize();
	CCPoint targetOffset = _target->getContentOffset();

	float x, y;
	float ratio;
	switch( _type )
	{
	case VERTICAL_IN:
	case VERTICAL_OUT:
		ratio = ( -targetOffset.y / (targetContentSize.height - targetViewSize.height) );
		y = (-targetOffset.y + targetViewSize.height) - (targetViewSize.height * ( 1 - ratio )) + (( 0.5 - ratio ) * this->getContentSize().height);
		this->setPosition( CCPointMake( targetViewSize.width - this->getContentSize().width/2, y ) );
		break;
	case HORIZONTAL_IN:
	case HORIZONTAL_OUT:
		ratio = ( -targetOffset.x / (targetContentSize.width - targetViewSize.width) );
		x = (-targetOffset.x + targetViewSize.width) - (targetViewSize.width * (1 - ratio)) + ((0.5 - ratio) * this->getContentSize().width);
		this->setPosition( CCPointMake( x, this->getContentSize().height/2 ) );
		break;
	}

	CCLog( "Pos(%.2f, %.2f)  TargetSize(%.2f, %.2f)  TargetViewSize(%.2f, %.2f)  TargetOffset(%.2f, %.2f)",
		this->getPositionX(), 
		this->getPositionY(),
		targetContentSize.width,
		targetContentSize.height,
		targetViewSize.width,
		targetViewSize.height,
		targetOffset.x,
		targetOffset.y);
}


void ScrollBar::RefreshScale()
{
	_beforeContentSize = _nowContentSize;

	float result = ( _svFixSize / _nowContentSize ) * _svFixSize;
	_barSize = result;

	switch( _type )
	{
	case VERTICAL_IN:
	case VERTICAL_OUT:
		this->setContentSize( CCSizeMake( barFixSize, result ) );
		break;
	case HORIZONTAL_IN:
	case HORIZONTAL_OUT:
		this->setContentSize( CCSizeMake( result, barFixSize ) );
		break;
	}

	setAnchorPoint( CCPointMake( 0.5, 0.5 ) );
}


void ScrollBar::Refresh()
{
	if( this->getScaleX() == 0.0f || this->getScaleY() == 0.0f )
		FadeIn(NULL);

	unscheduleAllSelectors();
	//scheduleOnce( schedule_selector(UIFlowScrollBar::FadeOut), _fadeDelayTime );

	float offset = 0;
	switch( _type )
	{
	case VERTICAL_IN:
	case VERTICAL_OUT:
		offset = _target->getContentOffset().y;
		_nowContentSize = _target->getContentSize().height;
		break;

	case HORIZONTAL_IN:
	case HORIZONTAL_OUT:
		offset = _target->getContentOffset().x;
		_nowContentSize = _target->getContentSize().width;
		break;
	}

	this->setVisible( _nowContentSize >= _svFixSize );

	RefreshScale();
	RefreshPosition();
}