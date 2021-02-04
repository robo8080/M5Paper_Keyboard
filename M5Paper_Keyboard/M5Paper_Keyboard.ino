#include <M5EPD.h>
#include "keyboard_config.h"
#include "frame_keyboard.h"
#include "binaryttf.h"
#include "ImageResource.h"

#ifdef USE_BLE_KEYBOARD
#include <BleKeyboard.h>
BleKeyboard bleKeyboard("M5Paper-Keyboard", "Espressif", 100);
#endif

void setup()
{
    M5.begin();
    M5.EPD.SetRotation(M5EPD_Driver::ROTATE_180);
    M5.TP.SetRotation(GT911::ROTATE_180);
    M5.EPD.Clear(true);
    M5.RTC.begin();
    
    M5EPD_Canvas initcanvas(&M5.EPD);
    initcanvas.loadFont(binaryttf, sizeof(binaryttf));
    initcanvas.setTextSize(26);
    initcanvas.createRender(26, 128);
    Frame_Base *frame = new Frame_Keyboard();
    EPDGUI_AddFrame("Frame_Keyboard", frame);

    EPDGUI_PushFrame(frame);

#ifdef USE_BLE_KEYBOARD
    bleKeyboard.begin();
#else
    // シリアル通信機能の設定
    // Serial2.begin(unsigned long baud, uint32_t config, int8_t rxPin, int8_t txPin, bool invert)
    Serial2.begin(115200, SERIAL_8N1, 19, 18);
#endif

}
void loop()
{
   EPDGUI_MainLoop();
}
