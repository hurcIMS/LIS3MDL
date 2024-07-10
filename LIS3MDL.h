#ifndef LIS3MDL_H_
#define LIS3MDL_H_

#include <cstdint>
#define MAGN_I2C_ADDR       0x1cU<<1

#define OFFSET_X_REG_L_M    0x05U       /* R/W */
#define OFFSET_X_REG_H_M    0x06U       /* R/W */
#define OFFSET_Y_REG_L_M    0x07U       /* R/W */
#define OFFSET_Y_REG_H_M    0x08U       /* R/W */
#define OFFSET_Z_REG_L_M    0x09U       /* R/W */
#define OFFSET_Z_REG_H_M    0x0aU       /* R/W */

#define MAGN_WHO_AM_I       0x0fU       /* R */

#define MAGN_CTRL_REG1      0x20U       /* R/W */
#define CTRL_REG1_TEMP_EN   0x0U<<7
#define OMXY_POS            0x05U
#define CTRL_REG1_OMXY_LP   0x00U
#define CTRL_REG1_OMXY_MP   0x01U
#define CTRL_REG1_OMXY_HP   0x02U
#define CTRL_REG1_OMXY_UP   0x03U
#define CTRL_REG1_DO_0HZ625 0x00U<<2
#define CTRL_REG1_DO_1HZ25  0x01U<<2
#define CTRL_REG1_DO_2HZ5   0x02U<<2
#define CTRL_REG1_DO_5HZ    0x03U<<2
#define CTRL_REG1_DO_10HZ   0x04U<<2
#define CTRL_REG1_DO_20HZ   0x05U<<2
#define CTRL_REG1_DO_40HZ   0x06U<<2
#define CTRL_REG1_DO_80HZ   0x07U<<2
#define CTRL_REG1_FAST_ODR  0x01U<<1
#define CTRL_REG1_ST        0x01U<<0

#define ODR_1000HZ          CTRL_REG1_FAST_ODR | (CTRL_REG1_OMXY_LP << OMXY_POS)
#define ODR_560HZ           CTRL_REG1_FAST_ODR | (CTRL_REG1_OMXY_MP << OMXY_POS)
#define ODR_300HZ           CTRL_REG1_FAST_ODR | (CTRL_REG1_OMXY_HP << OMXY_POS) 
#define ODR_155HZ           CTRL_REG1_FAST_ODR | (CTRL_REG1_OMXY_UP << OMXY_POS) 
#define ODR_80HZ            CTRL_REG1_DO_80HZ
#define ODR_40HZ            CTRL_REG1_DO_40HZ
#define ODR_20HZ            CTRL_REG1_DO_20HZ
#define ODR_10HZ            CTRL_REG1_DO_10HZ
#define ODR_5HZ             CTRL_REG1_DO_5HZ
#define ODR_2HZ5            CTRL_REG1_DO_2HZ5
#define ODR_1HZ25           CTRL_REG1_DO_1HZ25
#define ODR_0HZ625          CTRL_REG1_DO_0HZ625
#define ODR_RESET           0x0fU<<1

#define MAGN_CTRL_REG2      0x21U       /* R/W */
#define CTRL_REG2_FS_4G     0x00U<<5
#define CTRL_REG2_FS_8G     0x01U<<5        
#define CTRL_REG2_FS_12G    0x02U<<5        
#define CTRL_REG2_FS_16G    0x03U<<5
#define CTRL_REG2_REBOOT    0x01U<<3
#define CTRL_REG2_SOFT_RST  0x01U<<2
#define FS_RESET            0x03U<<5

#define MAGN_CTRL_REG3      0x22U       /* R/W */
#define CTRL_REG3_LP        0x01U<<5
#define CTRL_REG3_SIM       0x01U<<2
#define CTRL_REG3_MD_CC     0x00U<<0
#define CTRL_REG3_MD_SC     0x01U<<0
#define CTRL_REG3_MD_PD1    0x02U<<0
#define CTRL_REG3_MD_PD2    0x03U<<0
#define MD_RESET            0x03U<<0

#define MAGN_CTRL_REG4      0x23U       /* R/W */
#define CTRL_REG4_BLE       0x01U<<1
#define OMZ_POS             0x02U
#define CTRL_REG4_OMZ_LP    0x00U<<2
#define CTRL_REG4_OMZ_MP    0x01U<<2
#define CTRL_REG4_OMZ_HP    0x02U<<2
#define CTRL_REG4_OMZ_UP    0x03U<<2

#define MAGN_CTRL_REG5      0x24U       /* R/W */
#define CTRL_REG5_FAST_READ 0x01U<<7
#define CTRL_REG5_BDU       0x01U<<6

#define MAGN_STATUS_REG     0x27U       /* R */
#define STATUS_REG_ZYXOR    0x01U<<7
#define STATUS_REG_ZOR      0x01U<<6
#define STATUS_REG_YOR      0x01U<<5
#define STATUS_REG_XOR      0x01U<<4
#define STATUS_REG_ZYXDA    0x01U<<3
#define STATUS_REG_ZDA      0x01U<<2
#define STATUS_REG_YDA      0x01U<<1
#define STATUS_REG_XDA      0x01U<<0

#define MAGN_OUT_X_L        0x28U       /* R */
#define MAGN_OUT_X_H        0x29U       /* R */

#define MAGN_OUT_Y_L        0x2aU       /* R */
#define MAGN_OUT_Y_H        0x2bU       /* R */

#define MAGN_OUT_Z_L        0x2cU       /* R */
#define MAGN_OUT_Z_H        0x2dU       /* R */

#define MAGN_TEMP_OUT_L     0x2eU       /* R */
#define MAGN_TEMP_OUT_H     0x2fU       /* R */

#define MAGN_INT_CFG        0x30U       /* R/W */
#define INT_CFG_XIEN        0x01U<<7
#define INT_CFG_YIEN        0x01U<<6
#define INT_CFG_ZIEN        0x01U<<5
#define INT_CFG_IEA         0x01U<<2
#define INT_CFG_LIR         0x01U<<1
#define INT_CFG_IEN         0x01U<<0

#define MAGN_INT_SRC        0x31U       /* R */
#define INT_SRC_PTH_X       0x01U<<7
#define INT_SRC_PTH_Y       0x01U<<6
#define INT_SRC_PTH_Z       0x01U<<5
#define INT_SRC_NTH_X       0x01U<<4
#define INT_SRC_NTH_Y       0x01U<<3
#define INT_SRC_NTH_Z       0x01U<<2
#define INT_SRC_MROI        0x01U<<1
#define INT_SRC_INT         0x01U<<0

#define MAGN_INT_THS_L      0x32U       /* R/W */
#define MAGN_INT_THS_H      0x33U       /* R/W */

#include "mbed.h"

class LIS3MDL{
    public:
        LIS3MDL();
        LIS3MDL(I2C* i2c);

        virtual ~LIS3MDL(){};

        uint16_t getRawX(), getRawY(), getRawZ(), getRawTemp();
        float getX(), getY(), getZ(), getTemp();
        float m_fsr;

        void readX();
        void readY();
        void readZ();
        void readTemp();
        void readAll();

        void setOutputDataRate(char odr);
        void setRange(char range);
        void setOperatingMode(char mode);

        void setOffsets(uint16_t offX, uint16_t offY, uint16_t offZ);

        void enableTempMeas();
        void disableTempMeas();

        void softReset();
        void reboot();

    private:
        void setup();    

        void writeRegister(char addr, char msg);
        void writeRegister(char addr, char* msg, char nBytes);
        void readRegister(char addr, char nBytes);

        I2C* m_i2c;
        char m_cmd[2] = {0};
        char m_buffer[10] = {0};
        uint16_t m_rawX, m_rawY, m_rawZ, m_rawTemp = 0;
        uint16_t m_offX, m_offY, m_offZ = 0;
};


#endif