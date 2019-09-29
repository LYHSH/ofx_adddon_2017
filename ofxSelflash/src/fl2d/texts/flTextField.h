/**
 
 ActionScript3.0 Reference
 flash.text.TextField
 http://help.adobe.com/ja_JP/FlashPlatform/reference/actionscript/3/flash/text/TextField.html
 
 */

#pragma once

#include "flstringutil.h"

#include "flDefinition.h"
#include "flTextFieldAutoSize.h"
#include "flFont.h"
#include "flInteractiveObject.h"
#include "flGraphics.h"
#include "flMouseEvent.h"

//#define TEXT_FIELD_TYPE_DYNAMIC    "dynamic"
//#define TEXT_FIELD_TYPE_INPUT      "input"

using namespace flinternal;

namespace fl2d {
    
    class flTextField : public flInteractiveObject {
        
    public:
        static string TEXT_FIELD_TYPE_DYNAMIC;
        static string TEXT_FIELD_TYPE_INPUT;
        
    protected:
        
    private:
        float _labelNormalColor;
        float _labelOverColor;
        float _labelActiveColor;
        float _labelDeactiveColor;
        
        ofFloatColor _lineColor;
        ofFloatColor _normalColor;
        ofFloatColor _overColor;
        ofFloatColor _activeColor;
        ofFloatColor _deactiveColor;
        
        flGraphics* _graphics;
        
        ofFloatColor _textColor;
        vector<string> _texts;
        string _text;
        
        string _type;
        
        float _textWidth;
        float _textHeight;
        
        string _autoSize;
        float _tx;
        int _numLine;
        
        int _activeLineWidth;
        
       
        
        bool _addedListeners;
        
        bool _isActive;
        bool _enabled;
        
    public:
        flTextField();
        virtual ~flTextField();
        
        virtual float width();
        virtual void width(float value);
        
        virtual float height();
        virtual void height(float value);
        
        virtual float textWidth();
        virtual float textHeight();
        
        virtual float alpha();
        virtual void alpha(float value);
        
        virtual const string text();
        virtual void text(const string& value, int color = -1);
        virtual void appendText(const string& value);
        
        virtual const string& type();
        virtual void type(const string& value);
        
        int textColor();
        void textColor(int value);
        void textColor(ofFloatColor value);
        
        string autoSize();
        void autoSize(string value);
        
        bool active();
        void active(bool value);
        
        bool enabled();
        void enabled(bool value);
        
        //            bool enabledAntiAliasing() { return _enabledAntiAliasing; }
        //            void enabledAntiAliasing(bool value) { _enabledAntiAliasing = value; }
        
        
    protected:
        virtual void update();
        virtual void draw(bool applyMatrix = true);
        virtual void _draw();
        
        virtual void __compoundAlpha(float value);
        
        virtual void _drawGraphics(const ofFloatColor& lineColor, const ofFloatColor& fillColor, float thickness = 1.0);
        virtual void _drawGraphics(int lineColor, int fillColor, float thickness = 1.0);
        
    private:
        void _addListeners();
        void _removeListeners();
        
        void _keyPressedEventHandler(ofKeyEventArgs& event);
        void _keyReleasedEventHandler(ofKeyEventArgs& event);
        
        void _mouseEventHandler(flEvent& event);
        
        void _eventHandler(flEvent& event);
    };
}
