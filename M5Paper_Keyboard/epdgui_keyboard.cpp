#include "epdgui_keyboard.h"

static const char* kKeyAlphaMapLowerCase[26] = {
    "q", "w", "e", "r", "t", "y", "u", "i", "o", "p", //10
       "a", "s", "d", "f", "g", "h", "j", "k", "l",   //9
            "z", "x", "c", "v", "b", "n", "m",   //7
    };

static const char* kKeyAlphaMapUpperCase[26] = {
    "Q", "W", "E", "R", "T", "Y", "U", "I", "O", "P", //10
       "A", "S", "D", "F", "G", "H", "J", "K", "L",   //9
            "Z", "X", "C", "V", "B", "N", "M",   //7
    };

static const char* kKeyAlphaMapNumber[26] = {
    "1", "2", "3", "4", "5", "6", "7", "8", "9", "0", //10
       "-", "/", ":", ";", "(", ")", "$", "&", "@",   //9
            "_", "\"", ".", ",", "?", "!", "'",   //7
    };

static const char* kKeyAlphaMapSymbol[26] = {
    "[", "]", "{", "}", "#", "%", "^", "*", "+", "=", //10
       "_", "\\", "|", "~", "<", ">", "", "", "",   //9
//       "_", "\\", "|", "~", "<", ">", "€", "£", "¥",   //9
            "", "", "", "", "", "", "",   //7
//            "•", "✿", "\u221A", "\u221E", "\u2103", "\u2109", "\u2116",   //7
    };

enum
{
    kKeySpace = 26,
    kKeyBackspace,
    kKeyWrap,
    kKeyEsc,
    kKeyCase,
    kKeySwitch,
    kKeyNumber,
    kKeyCtrl
};

enum
{
    kSWCase = 0,
    kSWSwitch,
    kSWNumber,
    kSWCtrl
};

enum
{
    kLayoutLowerAlpha = 0,
    kLayoutUpperAlpha,
    kLayoutNumber,
    kLayoutSymbol
};

EPDGUI_Keyboard::EPDGUI_Keyboard(): EPDGUI_Base()
{    
    const uint16_t kKeyWidth = 72;
    const uint16_t kKeyHeight = 84;
    const uint16_t kKeyInterval = 8;
    const uint16_t kFirstLineY = 122;
    const uint16_t kSecondLineY = 216;
    const uint16_t kThirdLineY = 310;
    const uint16_t k4thLineY = 404;
    const uint16_t kBaseX = 120;

    for(int i = 0; i < 10; i++)
    {
        _btn[i] = new EPDGUI_Button(kKeyAlphaMapLowerCase[i], kBaseX + (kKeyInterval + kKeyWidth) * i, kFirstLineY, kKeyWidth, kKeyHeight);
    }
    for(int i = 10; i < 19; i++)
    {
        _btn[i] = new EPDGUI_Button(kKeyAlphaMapLowerCase[i], kBaseX + 40 + (kKeyInterval + kKeyWidth) * (i - 10), kSecondLineY, kKeyWidth, kKeyHeight);
    }
    for(int i = 19; i < 26; i++)
    {
        _btn[i] = new EPDGUI_Button(kKeyAlphaMapLowerCase[i], kBaseX + 118 + (kKeyInterval + kKeyWidth) * (i - 19), kThirdLineY, kKeyWidth, kKeyHeight);
    }

    _btn[kKeyBackspace] = new EPDGUI_Button("", kBaseX + 792 - 96, kThirdLineY, 96, kKeyHeight);
    _btn[kKeyBackspace]->CanvasNormal()->pushImage(_btn[kKeyBackspace]->getW() / 2 - 16, _btn[kKeyBackspace]->getH() / 2 - 16, 32, 32, ImageResource_backspace_32x32);
    _btn[kKeyBackspace]->CanvasPressed()->fillCanvas(0);
    _btn[kKeyBackspace]->CanvasPressed()->pushImage(_btn[kKeyBackspace]->getW() / 2 - 16, _btn[kKeyBackspace]->getH() / 2 - 16, 32, 32, ImageResource_backspace_32x32);
    _btn[kKeyBackspace]->CanvasPressed()->ReverseColor();
    _btn[kKeyEsc] = new EPDGUI_Button("Esc", kBaseX - (kKeyInterval + kKeyWidth), kFirstLineY, kKeyWidth, kKeyHeight);
    _btn[kKeySpace] = new EPDGUI_Button("Space", kBaseX + 105, k4thLineY, 520, kKeyHeight);
    _btn[kKeyWrap] = new EPDGUI_Button("Enter", kBaseX + 640, k4thLineY, 152, kKeyHeight);

    // function key
    _sw[kSWCase] = new EPDGUI_Switch(2, kBaseX - (kKeyInterval + kKeyWidth), kThirdLineY, 170, kKeyHeight);
    _sw[kSWSwitch] = new EPDGUI_Switch(2, kBaseX - (kKeyInterval + kKeyWidth), k4thLineY, 68, kKeyHeight);
    _sw[kSWNumber] = new EPDGUI_Switch(2, kBaseX, k4thLineY, kKeyWidth + 18, kKeyHeight);
    _sw[kSWCtrl] = new EPDGUI_Switch(2, kBaseX - (kKeyInterval + kKeyWidth), kSecondLineY, kKeyWidth+kKeyWidth/2, kKeyHeight);

    _sw[kSWCase]->Canvas(0)->pushImage(_sw[kSWCase]->getW() / 2 - 16, _sw[kSWCase]->getH() / 2 - 16, 32, 32, ImageResource_upper_32x32);
    _sw[kSWCase]->Canvas(1)->pushImage(_sw[kSWCase]->getW() / 2 - 16, _sw[kSWCase]->getH() / 2 - 16, 32, 32, ImageResource_upper_32x32);
    _sw[kSWCase]->Canvas(1)->ReverseColor();
    _sw[kSWSwitch]->SetLabel(0, "Fn"); //TODO: 
    _sw[kSWSwitch]->SetLabel(1, "Fn");
    _sw[kSWSwitch]->Canvas(1)->ReverseColor();
    _sw[kSWNumber]->SetLabel(0, "123");
    _sw[kSWNumber]->SetLabel(1, "Abc");
    _sw[kSWCtrl]->SetLabel(0, "Ctrl");
    _sw[kSWCtrl]->SetLabel(1, "Ctrl");
    _sw[kSWCtrl]->Canvas(1)->ReverseColor();

    for(int i = 0; i < 30; i++)
    {
        _key[i] = _btn[i];
    }
    _key[kKeyCase] = _sw[kSWCase];
    _key[kKeySwitch] = _sw[kSWSwitch];
    _key[kKeyNumber] = _sw[kSWNumber];
    _key[kKeyCtrl] = _sw[kSWCtrl];

    // _sw[kSWSwitch]->SetHide(true);

    _layout = kLayoutLowerAlpha;
}

EPDGUI_Keyboard::~EPDGUI_Keyboard()
{
    for(int i = 0; i < 30; i++)
    {
        delete _btn[i];
    }
    for(int i = 0; i < 4; i++)
    {
        delete _sw[i];
    }
}

void EPDGUI_Keyboard::Draw(m5epd_update_mode_t mode)
{
    if(_ishide)
    {
        return;
    }
    for(int i = 0; i < 34; i++)
    {
        _key[i]->Draw(mode);
    }
}

void EPDGUI_Keyboard::Draw(M5EPD_Canvas* canvas)
{
    if(_ishide)
    {
        return;
    }
    for(int i = 0; i < 34; i++)
    {
        _key[i]->Draw(canvas);
    }
}

void EPDGUI_Keyboard::Bind(int16_t state, void (* func_cb)(epdgui_args_vector_t&))
{
    
}

void EPDGUI_Keyboard::UpdateState(int16_t x, int16_t y)
{
    if(!_isenable)
    {
        return;
    }
    // log_d("UpdateState %d, %d", x, y);
    for(int i = 0; i < 34; i++)
    {
        bool keypressed = _key[i]->isInBox(x, y);
        _key[i]->UpdateState(x, y);
        if(keypressed)
        {
            if(i < 26)
            {
                String tmp;
                switch(_layout)
                {
                    case kLayoutLowerAlpha:
                     tmp = kKeyAlphaMapLowerCase[i];
//                     _data += kKeyAlphaMapLowerCase[i];
                     if(_sw[kSWCtrl]->getState() == 1) {
                        char c = *tmp.c_str()-0x60; 
                        _data += String(c);
                        //_sw[kSWCtrl]->setState(0);
                     } else {
                       _data += tmp;
                     }
                      break;
                    case kLayoutUpperAlpha:
                     tmp = kKeyAlphaMapUpperCase[i];
//                     _data += kKeyAlphaMapUpperCase[i];
                     if(_sw[kSWCtrl]->getState() == 1) {
                        char c = *tmp.c_str()-0x40; 
                        _data += String(c);
                        //_sw[kSWCtrl]->setState(0);
                     } else {
                        _data += tmp;
                     }
                      break;
                    case kLayoutNumber: _data += kKeyAlphaMapNumber[i]; break;
                    case kLayoutSymbol: _data += kKeyAlphaMapSymbol[i]; break;
                }
            }
            switch(i)
            {
                case kKeyBackspace: _data += "\u0008"; break;
                case kKeySpace: _data += " "; break;
                case kKeyWrap: _data += "\n"; break;
                case kKeyEsc: _data += "\0x1b"; break;
                case kKeyCtrl: _sw[kSWCtrl]->UpdateState(-1, -1); break;
                case kKeyCase:
                {
                    if(_layout == kLayoutNumber || _layout == kLayoutSymbol)
                    {
                        if(_sw[kSWCase]->getState() == 1)
                        {
                            for(int j = 0; j < 26; j++)
                            {
                                _btn[j]->setLabel(kKeyAlphaMapNumber[j]);
                                _layout = kLayoutNumber;
                            }
                        }
                        else
                        {
                            for(int j = 0; j < 26; j++)
                            {
                                _btn[j]->setLabel(kKeyAlphaMapSymbol[j]);
                                _layout = kLayoutSymbol;
                            }
                        }
                        _sw[kSWCase]->UpdateState(-1, -1);
                        Draw(UPDATE_MODE_NONE);
                        M5.EPD.UpdateFull(UPDATE_MODE_GL16);
                    }
                    else
                    {
                        if(_sw[kSWCase]->getState() == 1)
                        {
                            for(int j = 0; j < 26; j++)
                            {
                                _btn[j]->setLabel(kKeyAlphaMapLowerCase[j]);
                                _layout = kLayoutLowerAlpha;
                            }
                        }
                        else
                        {
                            for(int j = 0; j < 26; j++)
                            {
                                _btn[j]->setLabel(kKeyAlphaMapUpperCase[j]);
                                _layout = kLayoutUpperAlpha;
                            }
                        }
                        _sw[kSWCase]->UpdateState(-1, -1);
                        Draw(UPDATE_MODE_NONE);
                        M5.EPD.UpdateFull(UPDATE_MODE_GL16);
                    }
                    break;
                }
                case kKeyNumber:
                {
                    if(_sw[kSWNumber]->getState() == 1)
                    {
                        _sw[kSWCase]->setState(0);
                        _sw[kSWCase]->Canvas(0)->fillCanvas(0);
                        _sw[kSWCase]->Canvas(1)->fillCanvas(0);
                        _sw[kSWCase]->Canvas(0)->drawRect(0, 0, _sw[kSWCase]->getW(), _sw[kSWCase]->getH(), 15);
                        _sw[kSWCase]->Canvas(1)->drawRect(0, 0, _sw[kSWCase]->getW(), _sw[kSWCase]->getH(), 15);
                        _sw[kSWCase]->Canvas(0)->pushImage(_sw[kSWCase]->getW() / 2 - 16, _sw[kSWCase]->getH() / 2 - 16, 32, 32, ImageResource_upper_32x32);
                        _sw[kSWCase]->Canvas(1)->pushImage(_sw[kSWCase]->getW() / 2 - 16, _sw[kSWCase]->getH() / 2 - 16, 32, 32, ImageResource_upper_32x32);
                        _sw[kSWCase]->Canvas(1)->ReverseColor();

                        for(int j = 0; j < 26; j++)
                        {
                            _btn[j]->setLabel(kKeyAlphaMapLowerCase[j]);
                            _layout = kLayoutLowerAlpha;
                        }
                    }
                    else
                    {
                        _sw[kSWCase]->setState(0);
                        _sw[kSWCase]->SetLabel(0, "#+-");
                        _sw[kSWCase]->SetLabel(1, "123");

                        for(int j = 0; j < 26; j++)
                        {
                            _btn[j]->setLabel(kKeyAlphaMapNumber[j]);
                            _layout = kLayoutNumber;
                        }
                    }
                    _sw[kSWNumber]->UpdateState(-1, -1);
                    Draw(UPDATE_MODE_NONE);
                    M5.EPD.UpdateFull(UPDATE_MODE_GL16);
                    break;
                }
            }

        }
    }
  }

String EPDGUI_Keyboard::getData(void)
{
    String data = _data;
    _data = "";
    return data;   
}
