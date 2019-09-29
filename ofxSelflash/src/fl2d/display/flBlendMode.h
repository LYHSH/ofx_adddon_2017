/**
 
 Original code is Akira-Hayasaka :: ofxPSBlend
 https://github.com/Akira-Hayasaka/ofxPSBlend
 
 ActionScript3.0 Reference
 flash.display.BlendMode
 http://help.adobe.com/ja_JP/FlashPlatform/reference/actionscript/3/flash/display/BlendMode.html
 
 */

#pragma once

#include "ofMain.h"

namespace fl2d {
    
    class flBlendMode {
    public:
        
        static string ADD;
        
        static string ALPHA;
        //
        static string ALPHA_TEST;
        
        static string DARKEN;
        static string DIFFERENCE_;
        static string ERASE;
        static string HARDLIGHT;
        static string INVERT;
        static string LAYER;
        static string LIGHTEN;
        static string MULTIPLY;
        static string NORMAL;
        static string OVERLAY;
        static string SCREEN;
        static string SHADER;
        static string SUBTRACT;
        
    protected:
        
    private:
        static ofFbo* _base;
        static ofShader* _blendShader;
        static int _width;
        static int _height;
        
    public:
        static void enable(string value);
        static void disable();
        
        static void setup(int width, int height);
        static void draw(ofTexture& blendTgt, int blendMode = 0, int x = 0, int y = 0);
        static void draw(ofTexture& blendTgt, int blendMode, int x, int y, int width, int height);
        
        static void resize(int width, int height);
        
        static void begin();
        static void end();
        
        static string blendMode(int blendMode);
        
        static void destroy();
        
    protected:
        
    private:
        static void _loadShader();
        
        //            static string _getFragmentProgramGL3();
        //            static string _getFragmentProgramGL2();
        
    };
    
}
