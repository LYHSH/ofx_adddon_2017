#include "flStage.h"

namespace fl2d {
    
    flStage* flStage::_instance = NULL;
    
    //--------------------------------------------------------------
    //
    flStage* flStage::instance() {
        if(!_instance) {
            _instance = new flStage();
            _instance->setup();
        }
        return _instance;
    };
    void flStage::clear() {
        if(_instance) {
            delete _instance;
            _instance = NULL;
        }
    }
    
    //==============================================================
    // CONSTRUCTOR / DESTRUCTOR
    //==============================================================
    
    //--------------------------------------------------------------
    //
    flStage::flStage() {
        //        debug(true);
        if(debug()) cout << "[flStage]flStage()" << endl;
        
        _typeID = FL_TYPE_STAGE;
        _target = this;
        name("flStage");
        
        this->_stage = this;
        
        //MainTimeline
        _root = new flMovieClip();
        _root->name("root1");
        //        this->addChild(_root);
        
        _stageWidth = ofGetWidth();
        _stageHeight = ofGetHeight();
        
        _isTouchMode = false;
        
        _mouseX = 0;
        _mouseY = 0;
        
        _mouseID = 0;
        
        _isMouseChanged = false;
        
        //        _isKeyDown = false;
        
        _focus = this;
        __isFocus = true;
        
        _topMostHitDisplayObject = NULL;
        _topMostHitDisplayObjectPrev = NULL;
        
        _topMostHitInteractiveObject = NULL;
        _topMostHitInteractiveObjectPrev = NULL;
        
        _currentMouseDownInteractiveObject = NULL;
        //------------------------------------
    }
    
    //--------------------------------------------------------------
    //
    flStage::~flStage() {
        if(debug()) cout << "[flStage]~flStage()" << endl;
        
        _target = NULL;
        name("");
        
        this->_stage = this;
        
        //MainTimeline
        delete _root;
        _root = NULL;
        
        _stageWidth = 0;
        _stageHeight = 0;
        
        _isTouchMode = false;
        
        _mouseX = 0;
        _mouseY = 0;
        
        _mouseID = 0;
        
        _isMouseChanged = false;
        
        //        _isKeyDown = false;
        
        _focus = NULL;
        __isFocus = false;
        
        _topMostHitDisplayObject = NULL;
        _topMostHitDisplayObjectPrev = NULL;
        
        _topMostHitInteractiveObject = NULL;
        _topMostHitInteractiveObjectPrev = NULL;
        
        _currentMouseDownInteractiveObject = NULL;
        
        _lineTopDown.clear();
        _lineTopDownPrev.clear();
        _lineBottomUp.clear();
        _lineBottomUpPrev.clear();
        //------------------------------------
        
        //------------------------------------
        //ofAddListener(ofEvents().mouseMoved, this, &flStage::_mouseMoveEventHandler, _priority);
        ofRemoveListener(ofEvents().mouseDragged, this, &flStage::_mouseDragEventHandler, _settings.mousePriority);
        ofRemoveListener(ofEvents().mousePressed, this, &flStage::_mouseDownEventHandler, _settings.mousePriority);
        ofRemoveListener(ofEvents().mouseReleased, this, &flStage::_mouseUpEventHandler, _settings.mousePriority);
        ofRemoveListener(ofEvents().mouseScrolled, this, &flStage::_mouseScrolledEventHandler, _settings.mousePriority);
        
        ofRemoveListener(ofEvents().keyPressed, this, &flStage::_keyDownEventHandler, _settings.keyboardPriority);
        ofRemoveListener(ofEvents().keyReleased, this, &flStage::_keyUpEventHandler, _settings.keyboardPriority);
        
        ofRemoveListener(ofEvents().windowResized, this, &flStage::_resizeEventHandler, _settings.windowPriority);
        
        if(!_settings.manualUpdate) {
            ofRemoveListener(ofEvents().update, this, &flStage::_updateEventHandler, _settings.updatePriority);
        }
        if(!_settings.manualDraw) {
            ofRemoveListener(ofEvents().draw, this, &flStage::_drawEventHandler, _settings.drawPriority);
        }
        
//        _priority = OF_EVENT_ORDER_BEFORE_APP;
        //------------------------------------

        flBlendMode::destroy();
    }
    
    //==============================================================
    // SETUP / UPDATE / DRAW
    //==============================================================
    
    //--------------------------------------------------------------
    //
    void flStage::setup(flSettings settings) {
        if(debug()) cout << "[flStage]setup()" << endl;
        if(_isSetuped) return;
        _isSetuped = true;
        
        _settings = settings;
        
        //------------------------------------
        //        _priority = OF_EVENT_ORDER_BEFORE_APP;
        //        _priority = OF_EVENT_ORDER_APP;
        //        _priority = OF_EVENT_ORDER_AFTER_APP;
        
        //ofAddListener(ofEvents().mouseMoved, this, &flStage::_mouseMoveEventHandler, _priority);
        ofAddListener(ofEvents().mouseDragged, this, &flStage::_mouseDragEventHandler, _settings.mousePriority);
        ofAddListener(ofEvents().mousePressed, this, &flStage::_mouseDownEventHandler, _settings.mousePriority);
        ofAddListener(ofEvents().mouseReleased, this, &flStage::_mouseUpEventHandler, _settings.mousePriority);
        ofAddListener(ofEvents().mouseScrolled, this, &flStage::_mouseScrolledEventHandler, _settings.mousePriority);
        
        ofAddListener(ofEvents().keyPressed, this, &flStage::_keyDownEventHandler, _settings.keyboardPriority);
        ofAddListener(ofEvents().keyReleased, this, &flStage::_keyUpEventHandler, _settings.keyboardPriority);
        
        ofAddListener(ofEvents().windowResized, this, &flStage::_resizeEventHandler, _settings.windowPriority);
        
        if(!_settings.manualUpdate) {
            ofAddListener(ofEvents().update, this, &flStage::_updateEventHandler, _settings.updatePriority);
        }
        if(!_settings.manualDraw) {
            ofAddListener(ofEvents().draw, this, &flStage::_drawEventHandler, _settings.drawPriority);
        }
        //------------------------------------
        
        flBlendMode::setup(_stageWidth, _stageHeight);
    }
    
    //--------------------------------------------------------------
    //
    void flStage::update() {
        flEvent* event = new flEvent(flEvent::ENTER_FRAME);
        dispatchEvent(event);
        
        //------------------------------------
        if(_topMostHitInteractiveObject) {
            if(_isSprite(_topMostHitInteractiveObject)) {
                flSprite* sprite = (flSprite*) _topMostHitInteractiveObject;
                //------------------------------------
                if(sprite->useHandCursor() == true) {
                    if(sprite->isMouseDown()) {
                        flMouse::changeCursor(FLASH_MOUSE_TYPE_CLOSE_HAND);
                    } else {
                        if(sprite->buttonMode() == true) {
                            flMouse::changeCursor(FLASH_MOUSE_TYPE_POINTING_HAND);
                        } else {
                            flMouse::changeCursor(FLASH_MOUSE_TYPE_OPEN_HAND);
                        }
                    }
                } else {
                    if(sprite->buttonMode() == true) {
                        flMouse::changeCursor(FLASH_MOUSE_TYPE_POINTING_HAND);
                    } else {
                        flMouse::changeCursor(FLASH_MOUSE_TYPE_ARROW);
                    }
                }
                //------------------------------------
            } else {
                flMouse::changeCursor(FLASH_MOUSE_TYPE_ARROW);
            }
        } else {
            flMouse::changeCursor(FLASH_MOUSE_TYPE_ARROW);
        }
        //------------------------------------
        
        //------------------------------------
        
        if(false) {
            if(_topMostHitDisplayObjectPrev != _topMostHitDisplayObject) {
                cout << "\n==========================================================" << endl;
                cout << "[Address]" << endl;
                cout << "topMostHitDisplayObject         = " << _topMostHitDisplayObject << endl;
                cout << "topMostHitDisplayObjectPrev     = " << _topMostHitDisplayObjectPrev << endl;
                cout << "----------------------------------------------------------" << endl;
                cout << "----------------------------------------------------------" << endl;
                cout << "[Name]" << endl;
                if(_topMostHitDisplayObject) cout << "topMostHitDisplayObject         = " << _topMostHitDisplayObject->name().c_str() << endl;
                if(_topMostHitDisplayObjectPrev) cout << "topMostHitDisplayObjectPrev     = " << _topMostHitDisplayObjectPrev->name().c_str() << endl;
                cout << "==========================================================\n" << endl;
            }
            cout << "==========================================================\n" << endl;
            cout << "focus                           = " << _focus << endl;
            if(_focus) cout << "focus                           = " << _focus->name().c_str() << endl;
            cout << "==========================================================\n" << endl;
        }
        //------------------------------------
        
        __isMouseOver = bool(_topMostHitDisplayObject == NULL);
        
        _topMostHitDisplayObjectPrev = _topMostHitDisplayObject;
        _topMostHitDisplayObject = NULL;
        
        _updateChildrenOne(this, children);
        _updateMouse();
        _updateChildrenTwo(this, children);
        
        __isMousePressed	= false;
        __isMouseReleased	= false;
        _isMouseChanged	= false;
        
        //------------------------------------
        
        float mouseXPrev = _mouseX;
        float mouseYPrev = _mouseY;
        _mouseX = ofGetMouseX();
        _mouseY = ofGetMouseY();
        //------------------------------------
        //------------------------------------
        
        if(_mouseX != mouseXPrev || _mouseY != mouseYPrev) _mouseMove();
        //------------------------------------
    }
    
    //--------------------------------------------------------------
    //
    void flStage::draw() {
        //cout << "[flStage]draw() << endl;
        
        //    glEnable(GL_BLEND);
        //    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        //glBlendFunc(GL_SRC_ALPHA, GL_ONE);
        
        
        GLboolean preBlendmodeAlpha = glIsEnabled(OF_BLENDMODE_ALPHA);
        GLboolean preDepthTest = glIsEnabled(GL_DEPTH_TEST);
        
        ofEnableAlphaBlending();
        glDisable(GL_DEPTH_TEST);
        
        flDisplayObjectContainer::draw();
        //_drawChildren(this, children);
        
        if(preDepthTest == GL_TRUE) { glEnable(GL_DEPTH_TEST); } else { glDisable(GL_DEPTH_TEST); }
        if(preBlendmodeAlpha == GL_TRUE) { ofEnableAlphaBlending(); } else { ofDisableAlphaBlending(); }
        
      
    }
    
    //==============================================================
    // PUBLIC METHOD
    //==============================================================
    
    //--------------------------------------------------------------
    //
    int flStage::stageWidth() { return _stageWidth; }
    int flStage::stageHeight() { return _stageHeight; }
    
    //--------------------------------------------------------------
    //
    int flStage::mouseX() { return _mouseX; }
    int flStage::mouseY() { return _mouseY; }
    
    //--------------------------------------------------------------
    //
    //    bool flStage::isMouseDown() { return _bMouseDown; };
    
    //--------------------------------------------------------------
    //
    flInteractiveObject* flStage::focus() { return _focus; }
    
    //--------------------------------------------------------------
    //
    flDisplayObject* flStage::topMostHitDisplayObject() { return _topMostHitDisplayObject; }
    flDisplayObject* flStage::topMostHitDisplayObjectPrev() { return _topMostHitDisplayObjectPrev; }
    
    //--------------------------------------------------------------
    //
    flInteractiveObject* flStage::topMostHitInteractiveObject() { return _topMostHitInteractiveObject; }
    flInteractiveObject* flStage::topMostHitInteractiveObjectPrev() { return _topMostHitInteractiveObjectPrev; }
    
    //--------------------------------------------------------------
    //
    flDisplayObject* flStage::getMostHitDisplayObject(int x, int y) {
        cout << "[flStage]getMostHitDisplayObject(" << x << ", " << y << ")" << endl;
        return _getMostHitDisplayObject(this, children, x, y);
    }
    
//    //--------------------------------------------------------------
//    // TODO
//    void flStage::priority(ofEventOrder value) {
//        if(_priority == value) return;
//        _priority = value;
//
//        //        //------------------------------------
//        //        //ofRemoveListener(ofEvents().mouseMoved, this, &flStage::_mouseMoveEventHandler);
//        //        ofRemoveListener(ofEvents().mouseDragged, this, &flStage::_mouseDragEventHandler);
//        //        ofRemoveListener(ofEvents().mousePressed, this, &flStage::_mouseDownEventHandler);
//        //        ofRemoveListener(ofEvents().mouseReleased, this, &flStage::_mouseUpEventHandler);
//        //
//        //        ofRemoveListener(ofEvents().keyPressed, this, &flStage::_keyDownEventHandler);
//        //        ofRemoveListener(ofEvents().keyReleased, this, &flStage::_keyUpEventHandler);
//        //
//        //        ofRemoveListener(ofEvents().update, this, &flStage::_updateEventHandler);
//        //        ofRemoveListener(ofEvents().draw, this, &flStage::_drawEventHandler);
//        //        ofRemoveListener(ofEvents().windowResized, this, &flStage::_resizeEventHandler);
//        //        //------------------------------------
//        //
//        //        //------------------------------------
//        //        //ofAddListener(ofEvents().mouseMoved, this, &flStage::_mouseMoveEventHandler, _priority);
//        //        ofAddListener(ofEvents().mouseDragged, this, &flStage::_mouseDragEventHandler, _priority);
//        //        ofAddListener(ofEvents().mousePressed, this, &flStage::_mouseDownEventHandler, _priority);
//        //        ofAddListener(ofEvents().mouseReleased, this, &flStage::_mouseUpEventHandler, _priority);
//        //
//        //        ofAddListener(ofEvents().keyPressed, this, &flStage::_keyDownEventHandler, _priority);
//        //        ofAddListener(ofEvents().keyReleased, this, &flStage::_keyUpEventHandler, _priority);
//        //
//        //        ofAddListener(ofEvents().update, this, &flStage::_updateEventHandler, _priority);
//        //        ofAddListener(ofEvents().draw, this, &flStage::_drawEventHandler, _priority);
//        //        ofAddListener(ofEvents().windowResized, this, &flStage::_resizeEventHandler, _priority);
//        //        //------------------------------------
//    }
    
    //==============================================================
    // PROTECTED / PRIVATE METHOD
    //==============================================================
    
    //--------------------------------------------------------------
    //
    void flStage::_updateChildrenOne(flDisplayObject* parent, vector<flDisplayObject*>& children) {
        //cout << "[flStage]_updateChildrenOne()" << endl;
        
        // clear pixel bounds on every loop and recalculate.
        //parent->resetPixelBounds();
        
        for(int i = 0; i < children.size(); i++) {
            flDisplayObject* child;
            child = children[i];
            
            //------------------------------------
            //Dispatch enter-frame-event
            //            if(_isDisplayObject(child)) {
            //                flEvent* event = new flEvent(flEvent::ENTER_FRAME);
            //                child->dispatchEvent(event);
            //            }
            //------------------------------------
            
            if(!child->visible()) continue;
            
            //=========================================== MATRIX.
            // transform child matrix by world matrix.
            flMatrix worldMatrix;
            worldMatrix = parent->concatenatedMatrix();
            worldMatrix.concat(child->matrix());
            child->transform(worldMatrix);
            
            
            //------------------------------------ mouseEnabled
            if(_isInteractiveObject(child)) {
                flInteractiveObject* intObj = (flInteractiveObject*)child;
                if(intObj->mouseEnabled()) {
                    
                    //------------------------------------ hitArea
                    if(_isSprite(child)) {
                        flSprite* sprite = (flSprite*) child;
                        if(sprite->hitArea() == NULL) {
                            if(child->hitTestPoint(_mouseX, _mouseY, true)) {
                                _topMostHitDisplayObject = child;
                            }
                        } else {
                            
                        }
                        
                    } else {
                        if(child->hitTestPoint(_mouseX, _mouseY, true)) {
                            _topMostHitDisplayObject = child;
                        }
                    }
                    //------------------------------------ hitArea
                    
                } else {
                    
                    //------------------------------------ hitArea
                    if(_isSprite(child)) {
                        flSprite* sprite = (flSprite*) child;
                        if(sprite->client) {
                            if(child->hitTestPoint(_mouseX, _mouseY, true)) {
                                _topMostHitDisplayObject = child;
                            }
                        } else {
                            
                        }
                        
                    } else {
                        
                    }
                    //------------------------------------ hitArea
                    
                }
            } else {
                if(child->hitTestPoint(_mouseX, _mouseY, true)) {
                    _topMostHitDisplayObject = child;
                }
            }
            //------------------------------------ mouseEnabled
            //------------------------------------ topMostHitDisplayObject
            
            if(_hasChildren(child)) {
                flDisplayObjectContainer* container;
                container = (flDisplayObjectContainer*)child;
                
                //------------------------------------ mouseChildren
                if(container->mouseChildren()) {
                    if(container->children.size() > 0) {
                        _updateChildrenOne(child, container->children);
                    }
                }
                //------------------------------------ mouseChildren
            }
            
            // compound pixel bounds from children.
            //parent->addToPixelBounds(child->pixelBounds());
        }
    }
    
    
    void flStage::_updateMouse() {
        //cout << "[flStage]_updateMouse()" << endl;
        
        //cout << "_isMouseChanged = " << _isMouseChanged << endl;
        
        bool bHitDisplayObjectChanged = false;
        bHitDisplayObjectChanged = (_topMostHitDisplayObject != _topMostHitDisplayObjectPrev);
        if(!bHitDisplayObjectChanged && !__isMousePressed && !__isMouseReleased) return;
        
        //------------------------------------
        if(false) {
            char frame[10];
            sprintf(frame, "%05llu", ofGetFrameNum());
            cout << "" << endl;
            cout << frame << " :: bHitDisplayObjectChanged = " << (bHitDisplayObjectChanged ? "true" : "false") << endl;
            cout << frame << " :: bMousePressed = "	<< (__isMousePressed ? "true" : "false") << endl;
            cout << frame << " :: bMouseReleased = " << (__isMouseReleased ? "true" : "false") << endl;
            cout << frame << " :: bMouseChanged = " << (_isMouseChanged ? "true" : "false") << endl;
        }
        //------------------------------------
        
        //=========================================== CREATE CHILD / PARENT LINES.
        
        _topMostHitInteractiveObjectPrev = _topMostHitInteractiveObject;
        _topMostHitInteractiveObject = NULL;
        
        flDisplayObject* dispObj;
        flInteractiveObject* intObj;
        
        flDisplayObject* hitDisplayObject = _topMostHitDisplayObject;
        
        _lineBottomUpPrev = _lineBottomUp;
        //_lineTopDown.clear();
        _lineBottomUp.clear();
        
        if(hitDisplayObject) {
            dispObj = hitDisplayObject;
            while(dispObj != this) {
                //------------------------------------ InteractiveObject
                if(_isInteractiveObject(dispObj)) {
                    intObj = (flInteractiveObject*)dispObj;
                    
                    //------------------------------------ mouseEnabled
                    if(intObj->mouseEnabled()) {
                        //                        intObj->__isMouseDown = _bMouseDown;
                        //                            intObj->__isMouseDown = false; // TODO „ÅÇ„Å£„Å¶„Çã„Åã‰∏çÂÆâ
                        intObj->__isMousePressed = false;
                        //_lineTopDown.push_back(intObj);
                        _lineBottomUp.insert(_lineBottomUp.begin(), intObj);
                        
                        if(!_topMostHitInteractiveObject) _topMostHitInteractiveObject = intObj;
                        
                        //------------------------------------ mouseChildren
                        if(_isDisplayObjectContainer(intObj)) {
                            flDisplayObjectContainer* dispObjContainer = (flDisplayObjectContainer*) intObj;
                            if(!dispObjContainer->mouseChildren()) {
                                _lineBottomUp.clear();
                                _lineBottomUp.insert(_lineBottomUp.begin(), intObj);
                                _topMostHitInteractiveObject = intObj;
                            }
                        }
                        //------------------------------------ mouseChildren
                    } else {
                        
                        //------------------------------------ hitArea
                        
                        if(_isSprite(intObj)) {
                            flSprite* sprite = (flSprite*) intObj;
                            if(sprite->client) {
                                dispObj = sprite->client;
                                //sprite->client->dispatchEvent(mouseEvent);
                                //goto pushListEnd;
                                
                                intObj = (flInteractiveObject*)dispObj;
                              //  ressed = false;
                               
                                _lineBottomUp.insert(_lineBottomUp.begin(), intObj);
                                
                                if(!_topMostHitInteractiveObject) _topMostHitInteractiveObject = intObj;
                            } else {
                                
                            }
                        }
                        //------------------------------------ hitArea
                        
                        //------------------------------------ mouseChildren
                        if(_isDisplayObjectContainer(intObj)) {
                            flDisplayObjectContainer* dispObjContainer = (flDisplayObjectContainer*) intObj;
                            if(!dispObjContainer->mouseChildren()) {
                                _lineBottomUp.clear();
                            }
                        }
                        //------------------------------------ mouseChildren
                    }
                    //------------------------------------ mouseEnabled
                }
                //------------------------------------ InteractiveObject
                dispObj	= dispObj->parent();
            }
        }
        //}
        //pushListEnd:
        
        //------------------------------------
        
        if(false) {
            if(_topMostHitInteractiveObject || _topMostHitInteractiveObjectPrev)cout << "\n==========================================================" << endl;
            if(_topMostHitInteractiveObject) cout << "TopMostHitInteractiveObject     = " << _topMostHitInteractiveObject->name().c_str() << endl;
            if(_topMostHitInteractiveObjectPrev) cout << "TopMostHitInteractiveObjectPrev = " << _topMostHitInteractiveObjectPrev->name().c_str() << endl;
            if(_topMostHitInteractiveObject || _topMostHitInteractiveObjectPrev)cout <<         "==========================================================\n" << endl;
        }
        //------------------------------------
        
        //---------------------------------------------------------- MOUSE EVENTS
        
        //------------------------------------
        
        if(_topMostHitInteractiveObjectPrev) {
            if(_topMostHitInteractiveObjectPrev != _topMostHitInteractiveObject) {
                for(int i = 0; i < _lineBottomUpPrev.size(); i++) {
                    intObj = _lineBottomUpPrev[i];
                    bool check = false;
                    
                    
                    for(int ii = 0; ii < _lineBottomUp.size(); ii++) {
                        check = bool(intObj == _lineBottomUp[ii]);
                        if(check) break;
                    }
                    
                    if(!check) {
                        //------------------------------------
                        flMouseEvent* mouseEvent = new flMouseEvent(flMouseEvent::ROLL_OUT);
                        mouseEvent->_target = intObj;
                        intObj->__isRollOver = false;
                        intObj->__isMouseOver = false;
                        intObj->dispatchEvent(mouseEvent);
                        //------------------------------------
                        
                        
                        if(_isDisplayObjectContainer(intObj)) {
                            flDisplayObjectContainer* dispObjContainer = (flDisplayObjectContainer*) intObj;
                            if(!dispObjContainer->mouseChildren()) goto rollOutCheckEnd;
                        }
                    }
                }
            }
        }
    rollOutCheckEnd:
        
        
        if(_topMostHitInteractiveObject) {
            if(_topMostHitInteractiveObject != _topMostHitInteractiveObjectPrev) {
                for(int i = 0; i < _lineBottomUp.size(); i++) {
                    intObj = _lineBottomUp[i];
                    bool check = false;
                    
                    
                    for(int ii = 0; ii < _lineBottomUpPrev.size(); ii++ ) {
                        check = bool(intObj == _lineBottomUpPrev[ii]);
                        if(check) break;
                    }
                    
                    if(!check) {
                        //------------------------------------
                        flMouseEvent* mouseEvent = new flMouseEvent(flMouseEvent::ROLL_OVER);
                        mouseEvent->_target = intObj;
                        intObj->__isRollOver = true;
                        intObj->__isMouseOver = true;
                        intObj->dispatchEvent(mouseEvent);
                        //------------------------------------
                        
                       
                        if(_isDisplayObjectContainer(intObj)) {
                            flDisplayObjectContainer* dispObjContainer = (flDisplayObjectContainer*) intObj;
                            if(!dispObjContainer->mouseChildren()) goto rollOverCheckEnd;
                        }
                    }
                }
            }
        }
    rollOverCheckEnd:
        //------------------------------------
        
        //------------------------------------
        
        if(_topMostHitInteractiveObjectPrev) {
            if(_topMostHitInteractiveObjectPrev != _topMostHitInteractiveObject) {
                for(int i = 0; i < _lineBottomUpPrev.size(); i++) {
                    //------------------------------------
                    flMouseEvent* mouseEvent = new flMouseEvent(flMouseEvent::MOUSE_OUT);
                    mouseEvent->_target = _topMostHitInteractiveObjectPrev;
                    intObj = _lineBottomUpPrev[i];
                    intObj->__isMouseOver = false;
                    intObj->dispatchEvent(mouseEvent);
                    //------------------------------------
                    
                    
                    if(_isDisplayObjectContainer(intObj)) {
                        flDisplayObjectContainer* dispObjContainer = (flDisplayObjectContainer*) intObj;
                        if(!dispObjContainer->mouseChildren()) goto mouseOutCheckEnd;
                    }
                }
            }
        }
    mouseOutCheckEnd:
        
        
        if(_topMostHitInteractiveObject) {
            if(_topMostHitInteractiveObject != _topMostHitInteractiveObjectPrev) {
                for(int i = 0; i < _lineBottomUp.size(); i++ ) {
                    //------------------------------------
                    flMouseEvent* mouseEvent = new flMouseEvent(flMouseEvent::MOUSE_OVER);
                    mouseEvent->_target = _topMostHitInteractiveObject;
                    intObj = _lineBottomUp[i];
                    intObj->__isMouseOver = true;
                    intObj->dispatchEvent(mouseEvent);
                    //------------------------------------
                    
                    
                    if(_isDisplayObjectContainer(intObj)) {
                        flDisplayObjectContainer* dispObjContainer = (flDisplayObjectContainer*) intObj;
                        if(!dispObjContainer->mouseChildren()) goto mouseOverCheckEnd;
                    }
                }
            }
        }
    mouseOverCheckEnd:
        //------------------------------------
        
     
        
        return;
        //----------------------------------------------------------
    }
    
    //--------------------------------------------------------------
   
    void flStage::_updateChildrenTwo(flDisplayObject* parent, vector<flDisplayObject*>& children) {
        for(int i = 0; i < children.size(); i++) {
            flDisplayObject* child;
            child = children[i];
            
            //            if(!child->visible()) continue;
            
            child->__compoundAlpha(parent->__compoundAlpha() * child->_alpha);
            
            if(_hasChildren(child)) {
                flDisplayObjectContainer* container;
                container = (flDisplayObjectContainer*)child;
                
                if(container->children.size() > 0) {
                    _updateChildrenTwo(child, container->children);
                }
            }
            
            // last thing we do is call the update method for each child.
            child->update();
        }
    }
    
    //--------------------------------------------------------------
    
    void flStage::_drawChildren(flDisplayObject* parent, vector<flDisplayObject*>& children) {
        for(int i = 0; i < children.size(); i++) {
            flDisplayObject* child;
            child = children[i];
            if(!child->visible()) continue;
            
            //-- matrix transform.
            bool bIdentity = true;
            bIdentity = child->matrix().isIdentity();
            bIdentity = false;
            
            if(!bIdentity) {
                glPushMatrix();
                glMultMatrixf(child->matrix().getPtr());
            }
            
            //child->drawOnFrame();
            child->draw();
            
            if(_hasChildren(child)) {
                flDisplayObjectContainer* container;
                container = (flDisplayObjectContainer*)child;
                if(container->children.size() > 0) {
                    _drawChildren(child, container->children);
                }
            }
            
            if(!bIdentity) {
                glPopMatrix();
            }
        }
    }
    
    //--------------------------------------------------------------
    //
    flDisplayObject* flStage::_getMostHitDisplayObject(flDisplayObject* parent, vector<flDisplayObject*>& children, int x, int y) {
        //        cout << "[flStage]_getMostHitDisplayObject(" << x << ", " << y << ")" << endl;
        flDisplayObject* mostHitDisplayObject;
        
        int i; int l;
        l = children.size();
        for(i = 0; i < l; i++) {
            flDisplayObject* child;
            child = children[i];
            
            if(!child->visible()) continue;
            
            //------------------------------------ topMostHitDisplayObject
           
            //------------------------------------ mouseEnabled
            if(_isInteractiveObject(child)) {
                flInteractiveObject* intObj = (flInteractiveObject*)child;
                if(intObj->mouseEnabled()) {
                    //------------------------------------ hitArea
                    if(_isSprite(child)) {
                        flSprite* sprite = (flSprite*) child;
                        if(sprite->hitArea() == NULL) {
                            if(child->hitTestPoint(x, y, true)) {
                                mostHitDisplayObject = child;
                            }
                        } else {
                            
                        }
                        
                    } else {
                        if(child->hitTestPoint(x, y, true)) {
                            mostHitDisplayObject = child;
                        }
                    }
                    //------------------------------------ hitArea
                } else {
                    //------------------------------------ hitArea
                    if(_isSprite(child)) {
                        flSprite* sprite = (flSprite*) child;
                        if(sprite->client) {
                            if(child->hitTestPoint(x, y, true)) {
                                mostHitDisplayObject = child;
                            }
                        } else {
                            
                        }
                    } else {
                        
                    }
                    //------------------------------------ hitArea
                    
                }
            } else {
                if(child->hitTestPoint(x, y, true)) {
                    mostHitDisplayObject = child;
                }
            }
            //------------------------------------ mouseEnabled
            //------------------------------------ topMostHitDisplayObject
            
           
            if(_hasChildren(child)) {
                flDisplayObjectContainer* container;
                container = (flDisplayObjectContainer*)child;
                
                //------------------------------------ mouseChildren
                if(container->mouseChildren()) {
                    if(container->children.size() > 0) {
                        flDisplayObject* hitDisplayObject = _getMostHitDisplayObject(child, container->children, x, y);
                        if(hitDisplayObject != NULL) mostHitDisplayObject = hitDisplayObject;
                        //                        mostHitDisplayObject = _getMostHitDisplayObject(child, container->children, x, y);
                    }
                }
                //------------------------------------ mouseChildren
            }
        }
        
        //        if(mostHitDisplayObject) cout << "[flStage]" << mostHitDisplayObject->name() << endl;
        return mostHitDisplayObject;
    }
    
    //--------------------------------------------------------------
    //
    void flStage::_mouseMove() {
        //        if(debug()) cout << "[flStage]_mouseMove()" << endl;
        
        if(_mouseID != 0) return;
        
        flMouseEvent* mouseEvent;
        //----------------------------------------------------------
        mouseEvent = new flMouseEvent(flMouseEvent::MOUSE_MOVE);
        mouseEvent->_target = this;
        mouseEvent->__localX = mouseX();
        mouseEvent->__localY = mouseY();
        mouseEvent->__stageX = mouseX();
        mouseEvent->__stageY = mouseY();
        dispatchEvent(mouseEvent);
        //----------------------------------------------------------
        
        //----------------------------------------------------------
        if(_topMostHitInteractiveObject) {
            mouseEvent = new flMouseEvent(flMouseEvent::MOUSE_MOVE);
            mouseEvent->_target = _topMostHitInteractiveObject;
            mouseEvent->__localX = _topMostHitInteractiveObject->mouseX();
            mouseEvent->__localY = _topMostHitInteractiveObject->mouseY();
            mouseEvent->__stageX = mouseX();
            mouseEvent->__stageY = mouseY();
            _topMostHitInteractiveObject->dispatchEvent(mouseEvent);
        }
        //----------------------------------------------------------
    }
    
    //--------------------------------------------------------------
    //
    void flStage::_debugDraw(flDisplayObject* parent, vector<flDisplayObject*>& children) {
        for(int i = 0; i < children.size(); i++) {
            flDisplayObject* child;
            child = children[i];
            if(!child->visible()) continue;
            
            //-- matrix transform.
            bool bIdentity = true;
            bIdentity = child->matrix().isIdentity();
            bIdentity = false;
            
            if(!bIdentity) {
                glPushMatrix();
                glMultMatrixf(child->matrix().getPtr());
            }
            
            ofSetHexColor(0xff0000);
            float n = 5 / child->scaleX();
            ofDrawLine(-n, 0, n, 0);
            ofDrawLine(0, -n, 0, n);
            
            ofNoFill();
            ofDrawRectangle(child->_rect->left(), child->_rect->top(), child->_rect->right(), child->_rect->bottom());
            ofFill();
            
            ofSetHexColor(0x000000);
            string t = ofToString(child->name()) + " x:" + ofToString(child->x()) + " y:" + ofToString(child->y());
            ofDrawBitmapString(t, -50, -10);
            ofSetHexColor(0xffffff);
            
            if(_hasChildren(child)) {
                flDisplayObjectContainer* container;
                container = (flDisplayObjectContainer*)child;
                if(container->children.size() > 0) {
                    _debugDraw(child, container->children);
                }
            }
            
            if(!bIdentity) {
                glPopMatrix();
            }
        }
    }
    
    //==============================================================
    // EVENT HANDLER
    //==============================================================
    
    //--------------------------------------------------------------
    //
    void flStage::_updateEventHandler(ofEventArgs& event) {
        update();
        
    }
    //--------------------------------------------------------------
    //
    void flStage::_drawEventHandler(ofEventArgs& event) {
        draw();
        //        try {
        //            draw();
        //        } catch(...) {
        //            cout << "[flStage]draw error" << endl;
        //        }
    }
    
    //--------------------------------------------------------------
   
    void flStage::_mouseMoveEventHandler(ofMouseEventArgs& event) {
        if(debug()) cout << "[flStage]_mouseMoveEventHandler()" << endl;
        
        if(_mouseID != 0) return;
        
        //_mouseX = event.x;
        //_mouseY = event.y;
        
        //dispatchEvent(new Event(MouseEvent::MOUSE_MOVE));
        
        flMouseEvent* mouseEvent;
        //------------------------------------
        mouseEvent = new flMouseEvent(flMouseEvent::MOUSE_MOVE);
        mouseEvent->_target = this;
        mouseEvent->__localX = mouseX();
        mouseEvent->__localY = mouseY();
        mouseEvent->__stageX = mouseX();
        mouseEvent->__stageY = mouseY();
        dispatchEvent(mouseEvent);
        //------------------------------------
        //------------------------------------
        if(_topMostHitInteractiveObject) {
            mouseEvent = new flMouseEvent(flMouseEvent::MOUSE_MOVE);
            mouseEvent->_target = _topMostHitInteractiveObject;
            mouseEvent->__localX = _topMostHitInteractiveObject->mouseX();
            mouseEvent->__localY = _topMostHitInteractiveObject->mouseY();
            mouseEvent->__stageX = mouseX();
            mouseEvent->__stageY = mouseY();
            _topMostHitInteractiveObject->dispatchEvent(mouseEvent);
        }
        //------------------------------------
    }
    
    //--------------------------------------------------------------
    //
    void flStage::_mouseDragEventHandler(ofMouseEventArgs& event) {
        if(_mouseID != 0) return;
        
        //------------------------------------
        flMouseEvent* mouseEvent = new flMouseEvent(flMouseEvent::DRAGGING);
        mouseEvent->_target = this;
        mouseEvent->__localX = mouseX();
        mouseEvent->__localY = mouseY();
        mouseEvent->__stageX = mouseX();
        mouseEvent->__stageY = mouseY();
        dispatchEvent(mouseEvent);
        //------------------------------------
    }
    
    //--------------------------------------------------------------
    //
    void flStage::_mouseDownEventHandler(ofMouseEventArgs& event) {
        if(debug()) cout << "[flStage]_mouseDownEventHandler()" << endl;
        
        _mouseID = event.button;
        
        __isMouseDown	= true;
        __isMousePressed = true;
        
        _isMouseChanged = (_mouseID != 0);
        if(_isMouseChanged) _mouseID = 0;
        
        //------------------------------------
        if(_topMostHitInteractiveObject) {
            //            _topMostHitInteractiveObject->__isMousePressed = true; // TODO „ÅÇ„Å£„Å¶„Çã„Åã‰∏çÂÆâ
            
            //------------------------------------
            //2016.6.8
            
            if(_focus != _topMostHitInteractiveObject) {
                flFocusEvent* focusEvent;
                
                
                try {
                    
                    _focus->__isFocus = false;
                    focusEvent = new flFocusEvent(flFocusEvent::FOCUS_OUT);
                    focusEvent->_target = _focus;
                    _focus->dispatchEvent(focusEvent);
                    if(true) {
                        //                        cout << "focus out = " << _focus->name().c_str() << endl;
                    }
                    
                   
                    
                } catch(const char* str ) {
                    
                    cout << str << endl;
                }
                
               
                _focus = _topMostHitInteractiveObject;
                
               
                _focus->__isFocus = true;
                focusEvent = new flFocusEvent(flFocusEvent::FOCUS_IN);
                focusEvent->_target = _focus;
                _focus->dispatchEvent(focusEvent);
                if(true) {
                    //                    cout << "focus in = " << _focus->name().c_str() << endl;
                }
            }
            //------------------------------------
            
            flInteractiveObject* intObj = NULL;
            for(int i = 0; i < _lineBottomUp.size(); i++ ) {
                //------------------------------------
                flMouseEvent* mouseEvent = new flMouseEvent(flMouseEvent::MOUSE_DOWN);
                mouseEvent->_target = _topMostHitInteractiveObject;
                mouseEvent->__localX = _topMostHitInteractiveObject->mouseX();
                mouseEvent->__localY = _topMostHitInteractiveObject->mouseY();
                mouseEvent->__stageX = mouseX();
                mouseEvent->__stageY = mouseY();
                intObj = _lineBottomUp[i];
                intObj->__isMousePressed = true;
                intObj->dispatchEvent(mouseEvent);
                //------------------------------------
                
                
                if(_isDisplayObjectContainer(intObj)) {
                    flDisplayObjectContainer* dispObjContainer = (flDisplayObjectContainer*) intObj;
                    if(!dispObjContainer->mouseChildren()) goto mouseDownCheckEnd;
                }
            }
        mouseDownCheckEnd:
            //------------------------------------
            
            
            
            
            _topMostHitInteractiveObject->__isMouseDown = true;
            _currentMouseDownInteractiveObject = _topMostHitInteractiveObject;
        } else {
            //------------------------------------
            
            if(_focus != this) {
                flFocusEvent* focusEvent;
                
               
                _focus->__isFocus = false;
                focusEvent = new flFocusEvent(flFocusEvent::FOCUS_OUT);
                focusEvent->_target = _focus;
                _focus->dispatchEvent(focusEvent);
                if(true) {
                    //                    cout << "focus out = " << _focus->name().c_str() << endl;
                }
                
                _focus = this;
                
              
                _focus->__isFocus = true;
                focusEvent = new flFocusEvent(flFocusEvent::FOCUS_IN);
                focusEvent->_target = _focus;
                _focus->dispatchEvent(focusEvent);
                
                if(true) {
                    //                    cout << "focus in = " << _focus->name().c_str() << endl;
                }
            }
            //------------------------------------
        }
        //------------------------------------
        
        //------------------------------------
        flMouseEvent* mouseEvent = new flMouseEvent(flMouseEvent::MOUSE_DOWN);
        mouseEvent->_target = this;
        mouseEvent->__localX = mouseX();
        mouseEvent->__localY = mouseY();
        mouseEvent->__stageX = mouseX();
        mouseEvent->__stageY = mouseY();
        this->__isMouseDown = true;
        dispatchEvent(mouseEvent);
        //------------------------------------
        
        //        cout << "isFocus = " << isFocus() << endl;
        //        cout << "flStage->focus = " << focus()->name() << endl;
    }
    
    //--------------------------------------------------------------
    //
    void flStage::_mouseUpEventHandler(ofMouseEventArgs& event) {
        if(_mouseID != 0) return;
        
        __isMouseDown = false;
        __isMouseReleased = true;
        
        
        if(_topMostHitInteractiveObject) {
            flInteractiveObject* intObj = NULL;
            for(int i = 0; i < _lineBottomUp.size(); i++ ) {
                //------------------------------------
                flMouseEvent* mouseEvent = new flMouseEvent(flMouseEvent::MOUSE_UP);
                mouseEvent->_target = _topMostHitInteractiveObject;
                mouseEvent->__localX = _topMostHitInteractiveObject->mouseX();
                mouseEvent->__localY = _topMostHitInteractiveObject->mouseY();
                mouseEvent->__stageX = mouseX();
                mouseEvent->__stageY = mouseY();
                intObj = _lineBottomUp[i];
                //                    intObj->__isMouseDown = true; // TODO „ÅÇ„Å£„Å¶„Çã„Åã‰∏çÂÆâ
                intObj->__isMousePressed = true;
                intObj->dispatchEvent(mouseEvent);
                //------------------------------------
                
                
                if(_isDisplayObjectContainer(intObj)) {
                    flDisplayObjectContainer* dispObjContainer = (flDisplayObjectContainer*) intObj;
                    if(!dispObjContainer->mouseChildren()) goto mouseUpCheckEnd;
                }
            }
        }
    mouseUpCheckEnd:
        //------------------------------------
        
        if(_currentMouseDownInteractiveObject) {
            //            _currentMouseDownInteractiveObject->__isMousePressed = false; // TODO „ÅÇ„Å£„Å¶„Çã„Åã‰∏çÂÆâ
            _currentMouseDownInteractiveObject->__isMouseDown = false;
            _currentMouseDownInteractiveObject = NULL;
        }
        //------------------------------------
        
        //------------------------------------
        flMouseEvent* mouseEvent = new flMouseEvent(flMouseEvent::MOUSE_UP);
        mouseEvent->_target = this;
        mouseEvent->__localX = mouseX();
        mouseEvent->__localY = mouseY();
        mouseEvent->__stageX = mouseX();
        mouseEvent->__stageY = mouseY();
        this->__isMouseDown = false;
        dispatchEvent(mouseEvent);
        //------------------------------------
    }
    
    //--------------------------------------------------------------
    //
    void flStage::_mouseScrolledEventHandler(ofMouseEventArgs& event) {
        //------------------------------------
        flMouseEvent* mouseEvent = new flMouseEvent(flMouseEvent::MOUSE_SCROLLED);
        mouseEvent->_target = this;
        mouseEvent->__localX = mouseX();
        mouseEvent->__localY = mouseY();
        mouseEvent->__stageX = mouseX();
        mouseEvent->__stageY = mouseY();
        mouseEvent->__scrollX = event.scrollX;
        mouseEvent->__scrollY = event.scrollY;
        dispatchEvent(mouseEvent);
        //------------------------------------
    }
    
    //--------------------------------------------------------------
    //
    void flStage::_keyDownEventHandler(ofKeyEventArgs& event) {
        if(debug()) cout << "[flStage]_keyDownEventHandler()" << endl;
        
        int key = event.key;
        //Space
        if(key == 32) flKeyboard::isSpaceKeyDown(true);
        //Shift
        if(key == 2304) flKeyboard::isShiftKeyDown(true);
        
        
        flKeyboardEvent* keyboardEvent;
        
        //------------------------------------
        if(!flKeyboard::__checkKeyIsDown(key)) {
            //        if(_isKeyDown == false) {
            if(debug()) cout << "[flStage]_keyDownEventHandler(KEY_PRESS)" << endl;
            keyboardEvent = new flKeyboardEvent(flKeyboardEvent::KEY_PRESS);
            keyboardEvent->__keyCode = key;
            dispatchEvent(keyboardEvent);
            
            if(_focus != this) {
                keyboardEvent = new flKeyboardEvent(flKeyboardEvent::KEY_PRESS);
                keyboardEvent->__keyCode = key;
                _focus->dispatchEvent(keyboardEvent);
            }
        }
        //------------------------------------
        
        //------------------------------------
        keyboardEvent = new flKeyboardEvent(flKeyboardEvent::KEY_DOWN);
        keyboardEvent->__keyCode = key;
        dispatchEvent(keyboardEvent);
        
        if(_focus != this) {
            keyboardEvent = new flKeyboardEvent(flKeyboardEvent::KEY_DOWN);
            keyboardEvent->__keyCode = key;
            _focus->dispatchEvent(keyboardEvent);
        }
        //------------------------------------
        
        flKeyboard::__addDownKey(key);
        //        _isKeyDown = true;
    }
    
    //--------------------------------------------------------------
    //
    void flStage::_keyUpEventHandler(ofKeyEventArgs& event) {
        if(debug()) cout << "[flStage]_keyUpEventHandler()" << endl;
        
        int key = event.key;
        //Space
        if(key == 32) flKeyboard::isSpaceKeyDown(false);
        //Shift
        if(key == 2304) flKeyboard::isShiftKeyDown(false);
        
        flKeyboardEvent* keyboardEvent;
        
        //------------------------------------
        if(flKeyboard::__checkKeyIsDown(key)) {
            //        if(_isKeyDown) {
            if(debug()) cout << "[flStage]_keyDownEventHandler(KEY_RELEASE)" << endl;
            keyboardEvent = new flKeyboardEvent(flKeyboardEvent::KEY_RELEASE);
            keyboardEvent->__keyCode = key;
            dispatchEvent(keyboardEvent);
            
            if(_focus != this) {
                keyboardEvent = new flKeyboardEvent(flKeyboardEvent::KEY_RELEASE);
                keyboardEvent->__keyCode = key;
                _focus->dispatchEvent(keyboardEvent);
            }
        }
        //------------------------------------
        
        //------------------------------------
        keyboardEvent = new flKeyboardEvent(flKeyboardEvent::KEY_UP);
        keyboardEvent->__keyCode = key;
        dispatchEvent(keyboardEvent);
        
        if(_focus != this) {
            keyboardEvent = new flKeyboardEvent(flKeyboardEvent::KEY_UP);
            keyboardEvent->__keyCode = key;
            _focus->dispatchEvent(keyboardEvent);
        }
        //------------------------------------
        
        flKeyboard::__removeDownKey(key);
        //        _isKeyDown = false;
    }
    
    //==============================================================
    // RESIZE
    //==============================================================
    
    //--------------------------------------------------------------
    //
    void flStage::_resizeEventHandler(ofResizeEventArgs& event) {
        _stageWidth = event.width;
        _stageHeight = event.height;
        
        flBlendMode::resize(_stageWidth, _stageHeight);
    }
    
    //==============================================================
    // UTILITY
    //==============================================================
    
    //--------------------------------------------------------------
    //
    bool flStage::_isInteractiveObject(flDisplayObject* displayObject) {
        bool b = false;
        b = b || (displayObject->typeID() == FL_TYPE_INTERACTIVE_OBJECT);
        b = b || (displayObject->typeID() == FL_TYPE_TEXT_FIELD);
        b = b || (displayObject->typeID() == FL_TYPE_DISPLAY_OBJECT_CONTAINER);
        b = b || (displayObject->typeID() == FL_TYPE_SPRITE);
        b = b || (displayObject->typeID() == FL_TYPE_MOVIE_CLIP);
        
        return b;
    }
    
    //--------------------------------------------------------------
    //
    bool flStage::_isDisplayObject(flDisplayObject* displayObject) {
        bool b = false;
        b = b || (displayObject->typeID() == FL_TYPE_SHAPE);
        b = b || (displayObject->typeID() == FL_TYPE_BITMAP);
        b = b || (displayObject->typeID() == FL_TYPE_SPRITE);
        b = b || (displayObject->typeID() == FL_TYPE_MOVIE_CLIP);
        b = b || (displayObject->typeID() == FL_TYPE_TEXT_FIELD);
        
        return b;
    }
    
    //--------------------------------------------------------------
    //
    bool flStage::_isDisplayObjectContainer(flDisplayObject* displayObject) {
        bool b = false;
        b = b || (displayObject->typeID() == FL_TYPE_DISPLAY_OBJECT_CONTAINER);
        b = b || (displayObject->typeID() == FL_TYPE_SPRITE);
        b = b || (displayObject->typeID() == FL_TYPE_MOVIE_CLIP);
        
        return b;
    }
    
    //--------------------------------------------------------------
    //
    bool flStage::_isSprite(flDisplayObject* displayObject) {
        bool b = false;
        b = b || (displayObject->typeID() == FL_TYPE_SPRITE);
        b = b || (displayObject->typeID() == FL_TYPE_MOVIE_CLIP);
        
        return b;
    }
    
}
