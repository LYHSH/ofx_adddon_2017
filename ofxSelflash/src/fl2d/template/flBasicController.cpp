#include "flBasicController.h"

namespace fl2d {
    
    //==============================================================
    // CONSTRUCTOR / DESTRUCTOR
    //==============================================================
    
    //--------------------------------------------------------------
    //
    flBasicController::flBasicController() {
        //    cout << "[flBasicController]flBasicController()" << endl;
        
        _target = this;
        name("flBasicController");
        
        useHandCursor(true);
        
        addEventListener(flMouseEvent::ROLL_OVER, this, &flBasicController::_mouseEventHandler);
        addEventListener(flMouseEvent::ROLL_OUT, this, &flBasicController::_mouseEventHandler);
        addEventListener(flMouseEvent::MOUSE_DOWN, this, &flBasicController::_mouseEventHandler);
        //addEventListener(flMouseEvent::MOUSE_UP, this, &flBasicController::_mouseEventHandler);
        
        float marginLeft; float marginTop;
        float spacing; float lineSpacing;
        //--------------------------------------
        marginLeft = 5;
        marginTop = 0;
        spacing = 100;
        lineSpacing = 22;
        
        titleTf = new flTextField();
        titleTf->x(marginLeft + spacing * 0);
        titleTf->y(marginTop + lineSpacing * 0);
        titleTf->width(120);
        titleTf->textColor(0xffffff);
        titleTf->text("[Contoller]");
        titleTf->mouseEnabled(false);
        addChild(titleTf);
        //--------------------------------------
        
        _isMinimize = false;
        
        
        minimizeButton = new flButton(20, 13);
        minimizeButton->labelText(" -");
        minimizeButton->toggleEnabled(true);
        minimizeButton->addEventListener(flMouseEvent::MOUSE_UP, this, &flBasicController::_buttonEventHandler);
        addChild(minimizeButton);
        
        //閉じるボタン
        closeButton = new flButton(20, 13);
        closeButton->labelText(" x");
        closeButton->addEventListener(flMouseEvent::MOUSE_UP, this, &flBasicController::_buttonEventHandler);
        addChild(closeButton);
        
        _backWidth = 0;
        _backHeight = 0;
        
        _minBackWidth = 0;
        _minBackHeight = 22;
        
        _normalBackWidth = 0;
        _normalBackHeight = 0;
        
        _onTop = true;
        
        _dragEnabled = true;
    }
    
    //--------------------------------------------------------------
    //
    flBasicController::~flBasicController() {
        //    cout << "[flBasicController]~flBasicController()" << endl;
        
        _target = NULL;
        
        removeEventListener(flMouseEvent::ROLL_OVER, this, &flBasicController::_mouseEventHandler);
        removeEventListener(flMouseEvent::ROLL_OUT, this, &flBasicController::_mouseEventHandler);
        removeEventListener(flMouseEvent::MOUSE_DOWN, this, &flBasicController::_mouseEventHandler);
        //removeEventListener(flMouseEvent::MOUSE_UP, this, &flBasicController::_mouseEventHandler);
        
        
        minimizeButton->removeEventListener(flMouseEvent::MOUSE_UP, this, &flBasicController::_buttonEventHandler);
        delete minimizeButton;
        minimizeButton = NULL;
        
        
        closeButton->removeEventListener(flMouseEvent::MOUSE_UP, this, &flBasicController::_buttonEventHandler);
        delete closeButton;
        closeButton = NULL;
        
        _backWidth = 0;
        _backHeight = 0;
        
        _minBackWidth = 0;
        _minBackHeight = 0;
        
        _normalBackWidth = 0;
        _normalBackHeight = 0;
        
        _onTop = false;
        
        _dragEnabled = false;
        
        for(auto* radioButtonGroup : radioButtonGroups) {
            delete radioButtonGroup;
            radioButtonGroup = NULL;
        }
        radioButtonGroups.clear();
    }
    
    //==============================================================
    // SETUP / UPDATE / DRAW
    //==============================================================
    
    //--------------------------------------------------------------
    //
    void flBasicController::setup() {
        //Sprite::setup();
        
        _setup();
        
        _updateRect();
        
        float w = width();
        minimizeButton->x(w - (18 + 5 + 18 + 5 + 5));
        minimizeButton->y(4);
        
        closeButton->x(w - (18 + 5 + 5));
        closeButton->y(4);
    }
    
    //==============================================================
    // PUBLIC MEHTOD
    //==============================================================
    
    //--------------------------------------------------------------
    //
    void flBasicController::minimize() {
        if(_isMinimize) return;
        _isMinimize = true;
        minimizeButton->selected(true);
        
        //----------------------------------
        _backWidth = _minBackWidth;
        _backHeight = _minBackHeight;
        
        flGraphics* g;
        g = graphics();
        g->clear();
        g->lineStyle(1, 0xffffff);
        g->beginFill(0x000000, 0.7);
        g->drawRect(0, 0, _backWidth, _backHeight);
        g->endFill();
        //----------------------------------
        
        //----------------------------------
        int i; int l;
        l = numChildren();
        for(i = 0; i < l; i++) {
            flDisplayObject* child = getChildAt(i);
            
            if(child == titleTf) continue;
            if(child == closeButton) continue;
            if(child == minimizeButton) continue;
            
            child->visible(false);
        }
        //    titleTf->visible(true);
        //    minimizeButton->visible(true);
        //    closeButton->visible(true);
        //----------------------------------
    }
    //--------------------------------------------------------------
    //
    void flBasicController::normalize() {
        if(!_isMinimize) return;
        _isMinimize = false;
        
        minimizeButton->selected(false);
        
        //----------------------------------
        _backWidth = _normalBackWidth;
        _backHeight = _normalBackHeight;
        
        flGraphics* g;
        g = graphics();
        g->clear();
        g->lineStyle(1, 0xffffff);
        g->beginFill(0x000000, 0.7);
        g->drawRect(0, 0, _backWidth, _backHeight);
        g->endFill();
        //----------------------------------
        
        //----------------------------------
        int i; int l;
        l = numChildren();
        for(i = 0; i < l; i++) {
            flDisplayObject* child = getChildAt(i);
            
            if(child == titleTf) continue;
            if(child == closeButton) continue;
            if(child == minimizeButton) continue;
            
            child->visible(true);
        }
        
        if(parent()) ((flDisplayObjectContainer*)parent())->addChild(this);
        //----------------------------------
    }
    
    //--------------------------------------------------------------
    //
    void flBasicController::resize(float w, float h) {
        
    }
    
    //==============================================================
    // EVENT HANDLER
    //==============================================================
    
    //--------------------------------------------------------------
    //
    void flBasicController::_mouseEventHandler(flEvent& event) {
        /*
         cout << "\n----------------------------------------------------------" << endl;
         printf("[flBasicController]_mouseEventHandler(%s) %s\n", ofToString(event.type()).c_str(), name().c_str());
         cout << "target = " << ((DisplayObject*)event.target())->name().c_str() << endl;
         cout << "currnetTarget = " << ((DisplayObject*)event.currentTarget())->name().c_str() << endl;
         cout << "----------------------------------------------------------\n" << endl;
         */    
        
        
        if(event.type() == flMouseEvent::ROLL_OVER) {
            flMouseEvent& mouseEvent = *(flMouseEvent*) &event;
            flButton* button = (flButton*)(event.currentTarget());
            
            if(event.target() == this) {
                
            }
        }
        
        if(event.type() == flMouseEvent::ROLL_OUT) {
            flMouseEvent& mouseEvent = *(flMouseEvent*) &event;
            flButton* button = (flButton*)(event.currentTarget());
            
            if(event.target() == this) {
                
            }
        }
        
        if(event.type() == flMouseEvent::MOUSE_OVER) {
            flMouseEvent& mouseEvent = *(flMouseEvent*) &event;
            flButton* button = (flButton*)(event.currentTarget());
            
            if(event.target() == this) {
                
            }
        }
        
        if(event.type() == flMouseEvent::MOUSE_OUT) {
            flMouseEvent& mouseEvent = *(flMouseEvent*) &event;
            flButton* button = (flButton*)(event.currentTarget());
            
            if(event.target() == this) {
                
            }
        }
        
        if(event.type() == flMouseEvent::MOUSE_DOWN) {
            flMouseEvent& mouseEvent = *(flMouseEvent*) &event;
            flButton* button = (flButton*)(event.currentTarget());
            
            if(event.target() == this) {
                if(_dragEnabled) {
                    if(_onTop) ((flDisplayObjectContainer*)parent())->addChild(this);
                    startDrag();
                    stage()->addEventListener(flMouseEvent::MOUSE_UP, this, &flBasicController::_mouseEventHandler);
                }
            }
        }
        
        if(event.type() == flMouseEvent::MOUSE_UP) {
            flMouseEvent& mouseEvent = *(flMouseEvent*) &event;
            flButton* button = (flButton*)(event.currentTarget());
            
            //if(event.target() == this) ((DisplayObjectContainer*)parent())->addChild(this);
            if(event.target() == stage()) {
                stage()->removeEventListener(flMouseEvent::MOUSE_UP, this, &flBasicController::_mouseEventHandler);
                stopDrag();
            }
        }
        
        
        if(event.type() == flCheckBoxEvent::CHANGE) {
            flCheckBoxEvent& checkBoxEvent = *(flCheckBoxEvent*) &event;
            flCheckBox* checkBox = (flCheckBox*)(event.currentTarget());
        }
        
        
        if(event.type() == flRadioButtonEvent::CHANGE) {
            flRadioButtonEvent& radioButtonEvent = *(flRadioButtonEvent*) &event;
            flRadioButton* radio = (flRadioButton*)(event.currentTarget());
        }
        
        
        if(event.type() == flNumberDialerEvent::CHANGE) {
            flNumberDialerEvent& numberDialerEvent = *(flNumberDialerEvent*) &event;
            flNumberDialer* dialer = (flNumberDialer*)(event.currentTarget());
        }
        
       
        if(event.type() == flPadEvent::CHANGE) {
            flPadEvent& padEvent = *(flPadEvent*) &event;
            flPad2D* pad = (flPad2D*)(event.currentTarget());
        }
        
        
        if(event.type() == flSliderEvent::CHANGE) {
            flSliderEvent& sliderEvent = *(flSliderEvent*) &event;
            flSlider* slider = (flSlider*)(event.currentTarget());
        }
        
        
        if(event.type() == flRangeSliderEvent::CHANGE) {
            flRangeSliderEvent& rangeSliderEvent = *(flRangeSliderEvent*) &event;
            flRangeSlider* slider = (flRangeSlider*)(event.currentTarget());
        }
        
        
        if(event.type() == flColorSliderEvent::CHANGE) {
            flColorSliderEvent& colorSliderEvent = *(flColorSliderEvent*) &event;
            flColorSlider* slider = (flColorSlider*)(event.currentTarget());
        }
        
        
        if(event.type() == flJoyStick1Event::CHANGE) {
            flJoyStick1Event& joystickEvent = *(flJoyStick1Event*) &event;
            flJoyStick1* joystick = (flJoyStick1*)(event.currentTarget());
        }
        if(event.type() == flJoyStick1Event::UP) {
            flJoyStick1Event& joystickEvent = *(flJoyStick1Event*) &event;
            flJoyStick1* joystick = (flJoyStick1*)(event.currentTarget());
        }
        if(event.type() == flJoyStick1Event::DOWN) {
            flJoyStick1Event& joystickEvent = *(flJoyStick1Event*) &event;
            flJoyStick1* joystick = (flJoyStick1*)(event.currentTarget());
        }
        if(event.type() == flJoyStick1Event::LEFT) {
            flJoyStick1Event& joystickEvent = *(flJoyStick1Event*) &event;
            flJoyStick1* joystick = (flJoyStick1*)(event.currentTarget());
        }
        if(event.type() == flJoyStick1Event::RIGHT) {
            flJoyStick1Event& joystickEvent = *(flJoyStick1Event*) &event;
            flJoyStick1* joystick = (flJoyStick1*)(event.currentTarget());
        }
        
        
        if(event.type() == flJoyStick2Event::CHANGE) {
            flJoyStick2Event& joystickEvent = *(flJoyStick2Event*) &event;
            flJoyStick2* joystick = (flJoyStick2*)(event.currentTarget());
        }
        if(event.type() == flJoyStick2Event::UP) {
            flJoyStick2Event& joystickEvent = *(flJoyStick2Event*) &event;
            flJoyStick2* joystick = (flJoyStick2*)(event.currentTarget());
        }
        if(event.type() == flJoyStick2Event::DOWN) {
            flJoyStick2Event& joystickEvent = *(flJoyStick2Event*) &event;
            flJoyStick2* joystick = (flJoyStick2*)(event.currentTarget());
        }
        if(event.type() == flJoyStick2Event::LEFT) {
            flJoyStick2Event& joystickEvent = *(flJoyStick2Event*) &event;
            flJoyStick2* joystick = (flJoyStick2*)(event.currentTarget());
        }
        if(event.type() == flJoyStick2Event::RIGHT) {
            flJoyStick2Event& joystickEvent = *(flJoyStick2Event*) &event;
            flJoyStick2* joystick = (flJoyStick2*)(event.currentTarget());
        }
    }
    
    //--------------------------------------------------------------
    //
    void flBasicController::_buttonEventHandler(flEvent& event) {
        if(event.type() == flMouseEvent::MOUSE_UP) {
            if(event.target() == closeButton) dispatchEvent(new flEvent(flEvent::CLOSE));
            if(event.target() == minimizeButton) {
                if(minimizeButton->selected()) {
                    minimize();
                } else {
                    normalize();
                }
            }
        }
    }
    
}
