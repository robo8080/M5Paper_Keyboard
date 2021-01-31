#include "frame_keyboard.h"

//uint16_t textsize = 26;

Frame_Keyboard::Frame_Keyboard() : Frame_Base()
{
    _frame_name = "Frame_Keyboard";
//    uint8_t language = GetLanguage();
    keyboard = new EPDGUI_Keyboard();
//    exitbtn("Home");
//    _canvas_title->drawString("M5Paper Keyboard", 270, 34);
    _canvas_title->drawString("M5Paper Keyboard", 250, 34);
//    _key_exit->AddArgs(EPDGUI_Button::EVENT_RELEASED, 0, (void*)(&_is_run));
//    _key_exit->Bind(EPDGUI_Button::EVENT_RELEASED, &Frame_Base::exit_cb);
}

Frame_Keyboard::~Frame_Keyboard()
{
//    delete inputbox;
    delete keyboard;
//    delete key_textclear;
//    delete key_textsize_plus;
//    delete key_textsize_reset;
//    delete key_textsize_minus;
}

int Frame_Keyboard::init(epdgui_args_vector_t &args)
{
    _is_run = 1;
    M5.EPD.Clear();
    _canvas_title->pushCanvas(0, 8, UPDATE_MODE_NONE);
    EPDGUI_AddObject(keyboard);
//    EPDGUI_AddObject(_key_exit);
    return 6;
}
uint32_t _time = 0;
uint32_t _next_update_time = 0;

int Frame_Keyboard::run(void)
{

    if((millis() - _time) > _next_update_time)
    {
    char buf[20];
    _canvas_title->fillCanvas(0);
//    _bar->drawFastHLine(0, 43, 540, 15);
    _canvas_title->setTextDatum(CC_DATUM);
//    _canvas_title->setTextDatum(CL_DATUM);
//    _bar->drawString("M5Paper", 10, 27);
    _canvas_title->drawString("M5Paper Keyboard", 250, 34);

    // Battery
    _canvas_title->setTextDatum(CR_DATUM);
    _canvas_title->pushImage(498, 8+7, 32, 32, ImageResource_status_bar_battery_32x32);
    uint32_t vol = M5.getBatteryVoltage();

    if(vol < 3300)
    {
        vol = 3300;
    }
    else if(vol > 4350)
    {
        vol = 4350;
    }
    float battery = (float)(vol - 3300) / (float)(4350 - 3300);
    if(battery <= 0.01)
    {
        battery = 0.01;
    }
    if(battery > 1)
    {
        battery = 1;
    }
    uint8_t px = battery * 25;
    sprintf(buf, "%d%%", (int)(battery * 100));
    _canvas_title->drawString(buf, 498 - 10, 27+7);
    _canvas_title->fillRect(498 + 3, 8 + 10+7, px, 13, 15);
    // _bar->pushImage(498, 8, 32, 32, 2, ImageResource_status_bar_battery_charging_32x32);

//    // Time
    rtc_time_t time_struct;
    rtc_date_t date_struct;
    M5.RTC.getTime(&time_struct);
//    M5.RTC.getDate(&date_struct);
//    sprintf(buf, "%2d:%02d", time_struct.hour, time_struct.min);
//    _bar->setTextDatum(CC_DATUM);
//    _bar->drawString(buf, 270, 27);
    _canvas_title->pushCanvas(0, 0, UPDATE_MODE_GL16);

    _time = millis();
    _next_update_time = (60 - time_struct.sec) * 1000;
    }

    String text = keyboard->getData();
    Serial.print(text);
    Serial2.print(text);
//    inputbox->AddText(text);
//    inputbox->AddText(keyboard->getData());
    return 1;
}
