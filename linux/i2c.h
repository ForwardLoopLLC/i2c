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
        //! Constructor opens I2C as slave
        /*!
            \param bus the I2C bus where the peripheral hardware is connected
           \param addr the address where the I2C device can be found on the `bus` 
        */ 
        I2C(const uint8_t bus, const uint8_t addr);
        //! Destructor cleans up I2C resources
        ~I2C();
        //! Check if there was an error during object construction
        /*!
            \return True, if constructor failed. False, if succeeded.
        */ 
        bool error();
        //! Pause main thread execution
        /*!
            \param delay time in milliseconds to pause 
        */
        void wait(const int delay);
        //! Read one byte from a register
        /*!
            \param reg the register to read
            \return value read from the register
        */
        uint8_t read_byte(const uint8_t reg);
        //! Write one byte to a register
        /*!
            \param reg the register to write to 
            \param data the byte to write to `reg`
            \return False, if write failed. True, if write succeeded. 
        */
        bool write_byte(const uint8_t reg, uint8_t data);
        //! Read one word from a register
        /*!
            \param reg the register to read
            \return value read from the register
        */
        uint16_t read_word(const uint16_t reg);
        //! Write one word to a register
        /*!
            \param reg the register to write to 
            \param data the word to write to `reg`
            \return False, if write failed. True, if write succeeded. 
        */
        bool write_word(const uint8_t reg, uint16_t data);
        //! Read multiple bytes into an array 
        /*!
            \param reg the first register to read
            \param length the number of bytes to read
            \param block array to hold bytes that have been read
            \return False, if read failed. True, if read ucceeded. 
        */
        bool read_block(const uint8_t reg, uint8_t length, uint8_t* block);
        //bool write_block(const uint8_t reg, uint8_t length,  uint8_t* data);
        //! Enable SMBus packet error checking
        /*!
            \return False, if enable failed. True, if enable succeeded.
        */ 
        bool enablePacketErrorChecking(); 
        //! Disable SMBus packet error checking
        /*!
            \return False, if disable failed. True, if disable succeeded.
        */ 
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

void I2C::wait(const int delay) {
    // delay is in microseconds
    usleep(delay);
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

bool I2C::read_block(const uint8_t reg, uint8_t length, uint8_t* block) {
    if(i2c_smbus_read_i2c_block_data(file, reg, length, block) <= 0) {
        return false;
    }
    return true;
}

#endif
