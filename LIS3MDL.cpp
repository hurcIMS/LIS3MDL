#include "LIS3MDL.h"
#include <cstdint>
#include <stdint.h>

LIS3MDL::LIS3MDL(){
    m_i2c = new I2C(I2C_SDA,I2C_SCL);
    m_i2c->frequency(400000);
    setup();
}

LIS3MDL::LIS3MDL(I2C* i2c):m_i2c(i2c)
{
    setup();
}

void LIS3MDL::setup()
{
    setRange(CTRL_REG2_FS_4G);
    setOperatingMode(CTRL_REG3_MD_CC);
    setOutputDataRate(ODR_80HZ);
    
    return;
}

uint16_t LIS3MDL::getRawX()
{
    return m_rawX;
}

uint16_t LIS3MDL::getRawY()
{
    return m_rawY;
}

uint16_t LIS3MDL::getRawZ()
{
    return m_rawZ;
}

uint16_t LIS3MDL::getRawTemp()
{
    return m_rawTemp;
}

float LIS3MDL:: getX()
{
    return (float)((int16_t)m_rawX)*m_fsr;
}

float LIS3MDL:: getY()
{
    return (float)((int16_t)m_rawY)*m_fsr;
}

float LIS3MDL:: getZ()
{
    return (float)((int16_t)m_rawZ)*m_fsr;
}

float LIS3MDL:: getTemp()
{
    return (float)((int16_t)m_rawTemp)/8.0f/125.0f+25.0f;
}

void LIS3MDL::readX()
{
    readRegister(MAGN_OUT_X_L, 2);
    m_rawX = *(uint16_t *)&m_buffer[0];

    return;
}

void LIS3MDL::readY()
{
    readRegister(MAGN_OUT_Y_L, 2);
    m_rawY = *(uint16_t *)&m_buffer[0];

    return;    
}

void LIS3MDL::readZ()
{
    readRegister(MAGN_OUT_Z_L, 2);
    m_rawZ = *(uint16_t *)&m_buffer[0];

    return;
}

void LIS3MDL::readTemp()
{
    readRegister(MAGN_TEMP_OUT_L, 2);
    m_rawTemp = *(uint16_t *)&m_buffer[0];

    return;
}

void LIS3MDL::readAll()
{
    readRegister(MAGN_OUT_X_L, 8);
    m_rawX = *(uint16_t *)&m_buffer[0];
    m_rawY = *(uint16_t *)&m_buffer[2];
    m_rawZ = *(uint16_t *)&m_buffer[4];
    m_rawTemp = *(uint16_t *)&m_buffer[6];

    return;    
}

void LIS3MDL::setOutputDataRate(char odr)
{
    readRegister(MAGN_CTRL_REG1, 1);
    char msg = (m_buffer[0] & ~ODR_RESET) | odr;
    writeRegister(MAGN_CTRL_REG1, msg);
    
    if (odr == (ODR_1000HZ) || odr == (ODR_560HZ) || odr == (ODR_300HZ) || odr == (ODR_155HZ)) {
        readRegister(MAGN_CTRL_REG4, 1);
        msg = (m_buffer[0] & ~(0x03U << OMZ_POS)) | (((odr >> OMXY_POS) & 0x03U) << OMZ_POS);    
        writeRegister(MAGN_CTRL_REG4, msg);
    }

    return;
}

void LIS3MDL::setRange(char range)
{
    readRegister(MAGN_CTRL_REG2, 1);
    char msg = (m_buffer[0] & ~FS_RESET) | range;
    writeRegister(MAGN_CTRL_REG2, msg);

    switch (range) {
    case CTRL_REG2_FS_4G:
        m_fsr = 1/8.0f/6842.0f;
        break;
    case CTRL_REG2_FS_8G:
        m_fsr = 1/16.0f/3421.0f;
        break;
    case CTRL_REG2_FS_12G:
        m_fsr = 1/24.0f/2281.0f;
        break;
    case CTRL_REG2_FS_16G:
        m_fsr = 1/32.0f/1711.0f;
        break;
    default:
        m_fsr = 16.0f;
    }

    return;
}

void LIS3MDL::setOperatingMode(char mode)
{
    readRegister(MAGN_CTRL_REG3, 1);
    char msg = (m_buffer[0] &~MD_RESET) | mode;
    writeRegister(MAGN_CTRL_REG3, msg);
}

void LIS3MDL::setOffsets(uint16_t offX, uint16_t offY, uint16_t offZ)
{
    uint16_t msg[3] = {0};
    msg[0] = offX;
    msg[1] = offY;
    msg[2] = offZ;
    writeRegister(OFFSET_X_REG_L_M, (char *)msg, 6);
}

void LIS3MDL::enableTempMeas()
{
    readRegister(MAGN_CTRL_REG1, 1);
    char msg = m_buffer[0] | CTRL_REG1_TEMP_EN;
    writeRegister(MAGN_CTRL_REG1, msg);

    return;
}

void LIS3MDL::disableTempMeas()
{
    readRegister(MAGN_CTRL_REG1, 1);
    char msg = m_buffer[0] & ~CTRL_REG1_TEMP_EN;
    writeRegister(MAGN_CTRL_REG1, msg);

    return;
}

void LIS3MDL::softReset()
{
    char msg = CTRL_REG2_SOFT_RST;
    writeRegister(MAGN_CTRL_REG2, msg);
    
    return;
}

void LIS3MDL::reboot()
{
    char msg = CTRL_REG2_REBOOT;
    writeRegister(MAGN_CTRL_REG2, msg);
    
    return;
}

void LIS3MDL::readRegister(char addr, char nBytes)
{
    m_cmd[0] = addr;    
    m_i2c->write(MAGN_I2C_ADDR, m_cmd, 1);
    m_i2c->read(MAGN_I2C_ADDR, m_buffer,nBytes);

    return;
}

void LIS3MDL::writeRegister(char addr, char msg)
{
    m_cmd[0] = addr;
    m_cmd[1] = msg;
    m_i2c->write(MAGN_I2C_ADDR, m_cmd, 2);

    return;
}

void LIS3MDL::writeRegister(char addr, char* msg, char nBytes)
{
    m_cmd[0] = addr;
    for (int i(1); i<nBytes+1; i++) m_cmd[i] = msg[i-1];
    m_i2c->write(MAGN_I2C_ADDR, m_cmd, nBytes+1);

    return;
}