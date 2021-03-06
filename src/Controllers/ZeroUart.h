#ifndef _ZERO_h
#define _ZERO_h

#include <Arduino.h>
#include "Settings.h"
#include "SharedData.h"
#include "BLE/BluetoothHandler.h"

#define ZERO_BAUD_RATE 1200

#define ZERO_DATA_BUFFER_SIZE 30

#define ZERO_MODE_LCD_TO_CNTRL_START_BYTE 0x01
#define ZERO_MODE_CNTRL_TO_LCD_START_BYTE 0x36

// MINIMO CONFIG
#define ZERO_ALLOW_LCD_TO_CNTRL_MODIFICATIONS true
#define ZERO_ALLOW_CNTRL_TO_LCD_MODIFICATIONS true

class ZeroUart {


    // BYTE 3 FROM LCD TO CONTRL ... for each sequence number // brute force
    const byte modeLcd0[256] = {0x80, 0x05, 0x06, 0x2b, 0x34, 0x29, 0x2a, 0x2f, 0x28, 0x2d, 0x2e, 0x53, 0x7c, 0x51, 0x52, 0x57, 0x50, 0x55, 0x56, 0x7b, 0x84, 0x79, 0x7a, 0x7f, 0x78,
                                0x7d, 0x7e, 0x63, 0x0c, 0x61, 0x62, 0x67, 0x60, 0x65, 0x66, 0x0b, 0x14, 0x09, 0x0a, 0x0f, 0x08, 0x0d, 0x0e, 0x33, 0x5c, 0x31, 0x32, 0x37, 0x30, 0x35, 0x36, 0x5b, 0x64, 0x59, 0x5a,
                                0x5f, 0x58, 0x5d, 0x5e, 0x43, 0x6c, 0x41, 0x42, 0x47, 0x40, 0x45, 0x46, 0x6b, 0x74, 0x69, 0x6a, 0x6f, 0x68, 0x6d, 0x6e, 0x13, 0x3c, 0x11, 0x12, 0x17, 0x10, 0x15, 0x16, 0x3b,
                                0x44, 0x39, 0x3a, 0x3f, 0x38, 0x3d, 0x3e, 0x23, 0x4c, 0x21, 0x22, 0x27, 0x20, 0x25, 0x26, 0x4b, 0x54, 0x49, 0x4a, 0x4f, 0x48, 0x4d, 0x4e, 0x73, 0x1c, 0x71, 0x72, 0x77, 0x70,
                                0x75, 0x76, 0x1b, 0x24, 0x19, 0x1a, 0x1f, 0x18, 0x1d, 0x1e, 0x83, 0x2c, 0x81, 0x82, 0x07, 0x80, 0x05, 0x06, 0x2b, 0x34, 0x29, 0x2a, 0x2f, 0x28, 0x2d, 0x2e, 0x53, 0x7c, 0x51, 0x52,
                                0x57, 0x50, 0x55, 0x56, 0x7b, 0x84, 0x79, 0x7a, 0x7f, 0x78, 0x7d, 0x7e, 0x63, 0x0c, 0x61, 0x62, 0x67, 0x60, 0x65, 0x66, 0x0b, 0x14, 0x09, 0x0a, 0x0f, 0x08, 0x0d, 0x0e, 0x33, 0x5c,
                                0x31, 0x32, 0x37, 0x30, 0x35, 0x36, 0x5b, 0x64, 0x59, 0x5a, 0x5f, 0x58, 0x5d, 0x5e, 0x43, 0x6c, 0x41, 0x42, 0x47, 0x40, 0x45, 0x46, 0x6b, 0x74, 0x69, 0x6a, 0x6f, 0x68, 0x6d,
                                0x6e, 0x13, 0x3c, 0x11, 0x12, 0x17, 0x10, 0x15, 0x16, 0x3b, 0x44, 0x39, 0x3a, 0x3f, 0x38, 0x3d, 0x3e, 0x23, 0x4c, 0x21, 0x22, 0x27, 0x20, 0x25, 0x26, 0x4b, 0x54, 0x49, 0x4a,
                                0x4f, 0x48, 0x4d, 0x4e, 0x73, 0x1c, 0x71, 0x72, 0x77, 0x70, 0x75, 0x76, 0x1b, 0x24, 0x19, 0x1a, 0x1f, 0x18, 0x1d, 0x1e, 0x83, 0x2c, 0x81, 0x82, 0x7};
    const byte modeLcd1[256] = {0x85, 0x0a, 0x0b, 0x30, 0x39, 0x2e, 0x2f, 0x34, 0x2d, 0x32, 0x33, 0x58, 0x81, 0x56, 0x57, 0x5c, 0x55, 0x5a, 0x5b, 0x80, 0x89, 0x7e, 0x7f, 0x84,
                                0x7d, 0x82, 0x83, 0x68, 0x11, 0x66, 0x67, 0x6c, 0x65, 0x6a, 0x6b, 0x10, 0x19, 0x0e, 0x0f, 0x14, 0x0d, 0x12, 0x13, 0x38, 0x61, 0x36, 0x37, 0x3c, 0x35, 0x3a, 0x3b, 0x60, 0x69,
                                0x5e, 0x5f, 0x64, 0x5d, 0x62, 0x63, 0x48, 0x71, 0x46, 0x47, 0x4c, 0x45, 0x4a, 0x4b, 0x70, 0x79, 0x6e, 0x6f, 0x74, 0x6d, 0x72, 0x73, 0x18, 0x41, 0x16, 0x17, 0x1c, 0x15, 0x1a,
                                0x1b, 0x40, 0x49, 0x3e, 0x3f, 0x44, 0x3d, 0x42, 0x43, 0x28, 0x51, 0x26, 0x27, 0x2c, 0x25, 0x2a, 0x2b, 0x50, 0x59, 0x4e, 0x4f, 0x54, 0x4d, 0x52, 0x53, 0x78, 0x21, 0x76, 0x77,
                                0x7c, 0x75, 0x7a, 0x7b, 0x20, 0x29, 0x1e, 0x1f, 0x24, 0x1d, 0x22, 0x23, 0x88, 0x31, 0x86, 0x87, 0x0c, 0x85, 0x0a, 0x0b, 0x30, 0x39, 0x2e, 0x2f, 0x34, 0x2d, 0x32, 0x33, 0x58,
                                0x81, 0x56, 0x57, 0x5c, 0x55, 0x5a, 0x5b, 0x80, 0x89, 0x7e, 0x7f, 0x84, 0x7d, 0x82, 0x83, 0x68, 0x11, 0x66, 0x67, 0x6c, 0x65, 0x6a, 0x6b, 0x10, 0x19, 0x0e, 0x0f, 0x14, 0x0d,
                                0x12, 0x13, 0x38, 0x61, 0x36, 0x37, 0x3c, 0x35, 0x3a, 0x3b, 0x60, 0x69, 0x5e, 0x5f, 0x64, 0x5d, 0x62, 0x63, 0x48, 0x71, 0x46, 0x47, 0x4c, 0x45, 0x4a, 0x4b, 0x70, 0x79, 0x6e,
                                0x6f, 0x74, 0x6d, 0x72, 0x73, 0x18, 0x41, 0x16, 0x17, 0x1c, 0x15, 0x1a, 0x1b, 0x40, 0x49, 0x3e, 0x3f, 0x44, 0x3d, 0x42, 0x43, 0x28, 0x51, 0x26, 0x27, 0x2c, 0x25, 0x2a, 0x2b,
                                0x50, 0x59, 0x4e, 0x4f, 0x54, 0x4d, 0x52, 0x53, 0x78, 0x21, 0x76, 0x77, 0x7c, 0x75, 0x7a, 0x7b, 0x20, 0x29, 0x1e, 0x1f, 0x24, 0x1d, 0x22, 0x23, 0x88, 0x31, 0x86, 0x87, 0x0c};
    const byte modeLcd2[256] = {0x8a, 0x0f, 0x10, 0x35, 0x3e, 0x33, 0x34, 0x39, 0x32, 0x37, 0x38, 0x5d, 0x86, 0x5b, 0x5c, 0x61, 0x5a, 0x5f, 0x60, 0x85, 0x8e, 0x83, 0x84, 0x89, 0x82, 0x87,
                                0x88, 0x6d, 0x16, 0x6b, 0x6c, 0x71, 0x6a, 0x6f, 0x70, 0x15, 0x1e, 0x13, 0x14, 0x19, 0x12, 0x17, 0x18, 0x3d, 0x66, 0x3b, 0x3c, 0x41, 0x3a, 0x3f, 0x40, 0x65, 0x6e, 0x63, 0x64,
                                0x69, 0x62, 0x67, 0x68, 0x4d, 0x76, 0x4b, 0x4c, 0x51, 0x4a, 0x4f, 0x50, 0x75, 0x7e, 0x73, 0x74, 0x79, 0x72, 0x77, 0x78, 0x1d, 0x46, 0x1b, 0x1c, 0x21, 0x1a, 0x1f, 0x20, 0x45,
                                0x4e, 0x43, 0x44, 0x49, 0x42, 0x47, 0x48, 0x2d, 0x56, 0x2b, 0x2c, 0x31, 0x2a, 0x2f, 0x30, 0x55, 0x5e, 0x53, 0x54, 0x59, 0x52, 0x57, 0x58, 0x7d, 0x26, 0x7b, 0x7c, 0x81, 0x7a,
                                0x7f, 0x80, 0x25, 0x2e, 0x23, 0x24, 0x29, 0x22, 0x27, 0x28, 0x8d, 0x36, 0x8b, 0x8c, 0x11, 0x8a, 0x0f, 0x10, 0x35, 0x3e, 0x33, 0x34, 0x39, 0x32, 0x37, 0x38, 0x5d, 0x86, 0x5b,
                                0x5c, 0x61, 0x5a, 0x5f, 0x60, 0x85, 0x8e, 0x83, 0x84, 0x89, 0x82, 0x87, 0x88, 0x6d, 0x16, 0x6b, 0x6c, 0x71, 0x6a, 0x6f, 0x70, 0x15, 0x1e, 0x13, 0x14, 0x19, 0x12, 0x17, 0x18,
                                0x3d, 0x66, 0x3b, 0x3c, 0x41, 0x3a, 0x3f, 0x40, 0x65, 0x6e, 0x63, 0x64, 0x69, 0x62, 0x67, 0x68, 0x4d, 0x76, 0x4b, 0x4c, 0x51, 0x4a, 0x4f, 0x50, 0x75, 0x7e, 0x73, 0x74, 0x79,
                                0x72, 0x77, 0x78, 0x1d, 0x46, 0x1b, 0x1c, 0x21, 0x1a, 0x1f, 0x20, 0x45, 0x4e, 0x43, 0x44, 0x49, 0x42, 0x47, 0x48, 0x2d, 0x56, 0x2b, 0x2c, 0x31, 0x2a, 0x2f, 0x30, 0x55, 0x5e,
                                0x53, 0x54, 0x59, 0x52, 0x57, 0x58, 0x7d, 0x26, 0x7b, 0x7c, 0x81, 0x7a, 0x7f, 0x80, 0x25, 0x2e, 0x23, 0x24, 0x29, 0x22, 0x27, 0x28, 0x8d, 0x36, 0x8b, 0x8c, 0x11};


public:
    ZeroUart();

    void setSettings(Settings *);
    void setSharedData(SharedData *);
    void setBluetoothHandler(BluetoothHandler *);

    void setLcdSerialPort(Stream *port);
    void setControllerSerialPort(Stream *port);

    uint8_t getCheckSum(char *string);
    void displayFrame(int mode, char data_buffer[], byte checksum);
    uint8_t modifyModeOld(char var, char data_buffer[]);
    uint8_t getMode(char var, char data_buffer[]);
    uint8_t modifyMode(char var, char data_buffer[]);
    uint8_t modifyMode2(char var, char data_buffer[]);
    uint8_t getBrakeFromCntrlFrame(char var, char data_buffer[]);
    void displayDecodedFrame(int mode, char data_buffer[], byte checksum);
    double getSpeed();
    uint8_t modifyAccel(char var, char data_buffer[]);
    uint16_t generateSpeedRawValue(double speed);
    uint8_t modifySpeed(char var, char data_buffer[], uint8_t byte);
    uint8_t modifyPower(char var, char data_buffer[]);
    uint8_t modifyBrakeFromDisplay(char var, char data_buffer[]);
    uint8_t modifyBrakeFromAnalog(char var, char data_buffer[]);
    uint8_t modifyEco(char var, char data_buffer[]);
    uint8_t modifyPas(char var, char data_buffer[]);

    bool getSerialStatusOkFromContrl();
    bool getSerialStatusOkFromLcd();
    bool getContrlStatusOk();
    bool isContrlInError(char var, char data_buffer[]);

    void readHardSerial(int mode, int *i, Stream *hwSerCntrl, Stream *hwSerLcd, int serialMode, char *data_buffer_ori, char *data_buffer_mod);
    void processSerial(uint32_t i_loop, boolean simulatedDisplay);

private:
    Stream *hwSerCntrl;
    Stream *hwSerLcd;
    BluetoothHandler *blh;

    SharedData *shrd;
    Settings *settings;

    uint32_t timeLastBrake = 0;

    int begin_LcdToCntrl = 1;
    int begin_CntrlToLcd = 1;

    int isModified_LcdToCntrl = 0;
    int isModified_CntrlToLcd = 0;

    int i_LcdRcv = 0;
    int i_CntrlRcv = 0;

    uint32_t timeLastValidFrameFromCntrl = 0;
    uint32_t timeLastValidFrameFromLcd = 0;

    bool cntrlInError = false;

    char data_buffer_lcd_mod[ZERO_DATA_BUFFER_SIZE];
    char data_buffer_cntrl_mod[ZERO_DATA_BUFFER_SIZE];
    char data_buffer_lcd_ori[ZERO_DATA_BUFFER_SIZE];
    char data_buffer_cntrl_ori[ZERO_DATA_BUFFER_SIZE];
};

#endif
