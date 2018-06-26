#include "linux/i2c.h" //drivers

int main() {
    // Start communicating on I2C bus 0 at address 0x68
    I2C i2c(0, 0x68); 
    if(i2c.error()) {
        printf("ERROR: I2C failed to initialize.\n");
    }
    printf("I2c initialized.\n");

    // configure SMBus packet error checking
    if(!i2c.enablePacketErrorChecking()) {
        printf("ERROR: failed to enable PEC.\n");
    }
    if(!i2c.disablePacketErrorChecking()) {
        printf("ERROR: failed to disable PEC.\n");
    }

    // read bytes, words, and blocks of bytes
    // read a byte from register 0x00
    uint8_t byte = i2c.read_byte(0x00); 

    // read a word from register 0x00
    uint16_t word = i2c.read_word(0x00); 

    // read eight bytes starting from register 0x00
    uint8_t block[8];
    if(!i2c.read_block(0x00, 8, block)) {
        printf("ERROR: failed to read block of bytes.\n");
    }

    // write bytes and words
    // write 0xFF to register 0x00
    if(!i2c.write_byte(0x00, 0xFF)) {
        printf("ERROR: failed to write byte.\n");
    }

    // write 0xFFFF to register 0x00
    if(!i2c.write_word(0x00, 0xFFFF)) {
        printf("ERROR: failed to write word.\n");
    }

    return 0;
}
