#ifndef I2C_LINUX_H
#define I2C_LINUX_H
#include <stdio.h>
#include <sys/ioctl.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdint.h>
#include <linux/i2c-dev.h>

class I2C {
    public:
        I2C(const uint8_t bus, const uint8_t addr);
        ~I2C();
        bool error();
        void wait(const int duration);
        uint8_t read_byte(const uint8_t reg);
        bool write_byte(const uint8_t reg, uint8_t data);
        uint16_t read_word(const uint16_t reg);
        bool write_word(const uint8_t reg, uint16_t data);
        uint8_t* read_block(const uint8_t reg, uint8_t length);
        bool write_block(const uint8_t reg, uint8_t length,  uint8_t* data);
        bool enablePacketErrorChecking(); 
        bool disablePacketErrorChecking(); 
    private:
        int file;
        bool err = false;
        int open(const uint8_t bus);
};

I2C::I2C(const uint8_t bus, const uint8_t addr) {
    file = open(bus);
    if (file < 0) {
        err = true;
    }
    if (ioctl(file, I2C_SLAVE, addr) < 0) {
        err = true;
    }
}

I2C::~I2C() {
    close(file);
}

bool I2C::error() {
    return err;
}

bool I2C::enablePacketErrorChecking() {
    if (ioctl(file, I2C_PEC, 1) < 0) {
        return false;
    }
    return true;
}

bool I2C::disablePacketErrorChecking() {
    if (ioctl(file, I2C_PEC, 0) < 0) {
        return false;
    }
    return true;
}


int I2C::open(const uint8_t bus) {
    char filename[20];
    snprintf(filename, 19,"/dev/i2c-%d", bus);
    // unistd open
    int file = ::open(filename, O_RDWR);
    if (file < 0) {
        err = true; 
    }
    return file;
}

void I2C::wait(const int duration) {
    // duration is in microseconds
    usleep(duration);
}

uint8_t I2C::read_byte(const uint8_t reg) {
    uint8_t data_byte = (uint8_t)i2c_smbus_read_byte_data(file, (__u8)reg);
    return data_byte;
}

bool I2C::write_byte(const uint8_t reg, uint8_t data) {
    if (i2c_smbus_write_byte_data(file, (__u8)reg, (__u8)data) < 0) {
        return false;
    }
    return true; 
}

uint16_t I2C::read_word(const uint16_t reg) {
    uint16_t data_word = (uint16_t)i2c_smbus_read_word_data(file, (__u16)reg);
    return data_word;
}

bool I2C::write_word(const uint8_t reg, uint16_t data) {
    if (i2c_smbus_write_word_data(file, (__u16)reg, (__u16)data) < 0) {
        return false;
    }
    return true; 
}
#endif
