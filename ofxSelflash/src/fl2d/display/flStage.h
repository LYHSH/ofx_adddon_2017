/**
 
 Original code is julapy :: ofxFlash
 https://github.com/julapy/ofxFlash/blob/master/src/display/ofxFlashStage.h
 
 ActionScript3.0 Reference
 flash.display.Stage
 http://help.adobe.com/ja_JP/FlashPlatform/reference/actionscript/3/flash/display/Stage.html
 
 */

#pragma once

#include "ofMain.h"

#include "flDefinition.h"
#include "flBlendMode.h"
#include "flDisplayObject.h"
#include "flDisplayObjectContainer.h"
#include "flMovieClip.h"
#include "flMouse.h"
#include "flKeyboard.h"
#include "flFocusEvent.h"
#include "flKeyboardEvent.h"
#include "flMouseEvent.h"

namespace fl2d {
    struct flSettings {
        bool manualUpdate = false;
        ofEventOrder updatePriority = OF_EVENT_ORDER_AFTER_APP;
        bool manualDraw = true;
        ofEventOrder drawPriority = OF_EVENT_ORDER_AFTER_APP;
        ofEventOrder mousePriority = OF_EVENT_ORDER_BEFORE_APP;
        ofEventOrder keyboardPriority = OF_EVENT_ORDER_BEFORE_APP;
        ofEventOrder windowPriority = OF_EVENT_ORDER_BEFORE_APP;
    };
    
    class flStage : public flDisplayObjectContainer {
    public:
        
    protected:
        
    private:
        bool _isSetuped = false;
        flSettings _settings;
        
        static flStage* _instance;
        flMovieClip* _root;
        
        int _stageWidth;
        int _stageHeight;
        
        bool _isTouchMode;
        
        int	_mouseX;
        int	_mouseY;

		
        int _mouseID;
       
        bool _isMouseChanged;
        
        //bool _isKeyDown;
        //bool _isKeyPressed;
        //bool _isKeyReleased;
        
        flInteractiveObject* _focus;
        
        flDisplayObject* _topMostHitDisplayObject;
        flDisplayObject* _topMostHitDisplayObjectPrev;
        
        flInteractiveObject* _topMostHitInteractiveObject;
        flInteractiveObject* _topMostHitInteractiveObjectPrev;
        
        flInteractiveObject* _currentMouseDownInteractiveObject;
        
        vector<flInteractiveObject*> _lineTopDown;
        vector<flInteractiveObject*> _lineTopDownPrev;
        vector<flInteractiveObject*> _lineBottomUp;
        vector<flInteractiveObject*> _lineBottomUpPrev;
        
//        ofEventOrder _priority;
        
    public:
        static flStage* instance();
        static void clear();
        
        virtual void setup(flSettings settings = flSettings());
        virtual void update();
        virtual void draw();
        //            virtual void resize();
        
        int stageWidth();
        int stageHeight();
        
        virtual int mouseX();
        virtual int mouseY();
        
        //            virtual bool isMouseDown();
        
        flInteractiveObject* focus();
        
        flDisplayObject* topMostHitDisplayObject();
        flDisplayObject* topMostHitDisplayObjectPrev();
        
        flInteractiveObject* topMostHitInteractiveObject();
        flInteractiveObject* topMostHitInteractiveObjectPrev();
        
        flDisplayObject* getMostHitDisplayObject(int x, int y);
        
//        void priority(ofEventOrder value);
        
    protected:
        
    private:
        flStage();
        virtual ~flStage();
        
        //update
        void _updateChildrenOne(flDisplayObject* parent, vector<flDisplayObject*>& children);
        void _updateMouse();
        //void _updateMouseInteraction();
        void _updateChildrenTwo(flDisplayObject* parent, vector<flDisplayObject*>& children);
        //draw
        void _drawChildren(flDisplayObject* parent, vector<flDisplayObject*>& children);
        
        void _mouseMove();
        
        flDisplayObject* _getMostHitDisplayObject(flDisplayObject* parent, vector<flDisplayObject*>& children, int x, int y);
        
        void _debugDraw(flDisplayObject* parent, vector<flDisplayObject*>& children);
        
        void _updateEventHandler(ofEventArgs& event);
        void _drawEventHandler(ofEventArgs& event);
        
        void _mouseMoveEventHandler(ofMouseEventArgs& event);
        void _mouseDragEventHandler(ofMouseEventArgs& event);
        void _mouseDownEventHandler(ofMouseEventArgs& event);
        void _mouseUpEventHandler(ofMouseEventArgs& event);
        void _mouseScrolledEventHandler(ofMouseEventArgs& event);
        //            void _mouseScrolledEventHandler(int x, int y, float scrollX, float scrollY);
        void _resizeEventHandler(ofResizeEventArgs& event);
        
        void _keyDownEventHandler(ofKeyEventArgs& event);
        void _keyUpEventHandler(ofKeyEventArgs& event);
        
        bool _isInteractiveObject(flDisplayObject* displayObject);
        bool _isDisplayObject(flDisplayObject* displayObject);
        bool _isDisplayObjectContainer(flDisplayObject* displayObject);
        bool _isSprite(flDisplayObject* displayObject);
    };
    
}
