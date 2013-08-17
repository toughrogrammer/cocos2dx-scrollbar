#include "TestScene.h"
#include "DataManager.h"
#include "TableViewController.h"
#include "TableViewCell.h"
#include "ScrollBar.h"


CCScene* TestScene::scene()
{
	// 'scene' is an autorelease object
	CCScene *scene = CCScene::create();

	// 'layer' is an autorelease object
	TestScene *layer = TestScene::create();

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}

// on "init" you need to initialize your instance
bool TestScene::init()
{
	//////////////////////////////
	// 1. super init first
	if ( !CCLayerColor::initWithColor( ccc4(0, 0, 255, 255) ) )
	{
		return false;
	}

	CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
	CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();

	/////////////////////////////
	// 2. add a menu item with "X" image, which is clicked to quit the program
	//    you may modify it.

	// add a "close" icon to exit the progress. it's an autorelease object
	CCMenuItemImage *pCloseItem = CCMenuItemImage::create(
		"CloseNormal.png",
		"CloseSelected.png",
		this,
		menu_selector(TestScene::menuCloseCallback));

	pCloseItem->setPosition(ccp(origin.x + visibleSize.width - pCloseItem->getContentSize().width/2 ,
		origin.y + pCloseItem->getContentSize().height/2));

	CCMenuItemFont *createValue = CCMenuItemFont::create( "Add item", this, menu_selector(TestScene::generateItem) );
	createValue->setPosition( ccp( 100, visibleSize.height * 0.8 ) );

	// create menu, it's an autorelease object
	CCMenu* pMenu = CCMenu::create(pCloseItem, createValue, NULL);
	pMenu->setPosition(CCPointZero);
	this->addChild(pMenu, 1);

	/////////////////////////////
	// 3. add your codes below...

	// Change value below variable
	bool isV = true;

	_tableViewController = new TableViewController( CCSizeMake( 50, 100 ) );
	_tableView = CCTableView::create( _tableViewController, CCSizeMake( 200, 150 ) );
	_tableView->setDelegate( _tableViewController );
	//Bug :: TableView anchor point is not working
	//_tableView->setAnchorPoint( ccp( 0.5, 0.5 ) );
	_tableView->setPosition( ccp( visibleSize.width/2 - _tableView->getViewSize().width/2, visibleSize.height/2 - _tableView->getViewSize().height/2 ) );
	if( isV )
	{
		_tableView->setDirection( kCCScrollViewDirectionVertical );
		_scrollBar = ScrollBar::create( _tableView, VERTICAL_IN );
	}
	else
	{
		_tableView->setDirection( kCCScrollViewDirectionHorizontal );
		_scrollBar = ScrollBar::create( _tableView, HORIZONTAL_IN );
	}
	_tableView->setVerticalFillOrder( kCCTableViewFillTopDown );
	_tableView->reloadData();
	this->addChild( _tableView );

	_tableViewController->LaunchScrollBar( _scrollBar );

	return true;
}


void TestScene::onExit()
{
	if( _tableViewController )
		delete _tableViewController;
}


void TestScene::generateItem(CCObject* pSender)
{
	static int n = 20;
	DataManager::Self()->AddData( n++ );
	_tableView->reloadData();
}

void TestScene::menuCloseCallback(CCObject* pSender)
{
	CCDirector::sharedDirector()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	exit(0);
#endif
}
