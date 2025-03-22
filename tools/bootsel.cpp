#include <iostream>
#include <libusb.h>

#define RESET_REQUEST_BOOTSEL 1
#define PICO_VENDOR_ID 0x2E8A
#define PICO_APP_PID 0x000A
#define PICO_BOOT_PID 0x0003
#define USB_INTERFACE 2


int main(int argc, const char* argv[]) {
    uint8_t request = RESET_REQUEST_BOOTSEL;
    libusb_device_handle* handle = nullptr;
    libusb_context* ctx = nullptr;

    // Initialize libusb
    if (libusb_init(&ctx) != LIBUSB_SUCCESS) {
        std::cerr << "Failed to initialize libusb" << std::endl;
        return -1;
    }

    // Open device with the Pico's VID and PID
    handle = libusb_open_device_with_vid_pid(ctx, PICO_VENDOR_ID, PICO_APP_PID);
    if (handle == nullptr) {
      if (libusb_open_device_with_vid_pid(ctx, PICO_VENDOR_ID, PICO_BOOT_PID)) {
        std::cout << "Pico already in BOOTSEL mode." << std::endl;
        return 0;
      }
      std::cerr << "Pico not available." << std::endl;
      libusb_exit(ctx);
      return -1;
    }

    // Claim the interface
    if (libusb_claim_interface(handle, USB_INTERFACE)) {
        std::cerr << "Pico has no interface#2." << std::endl;
        libusb_close(handle);
        libusb_exit(ctx);
        return -1;
    }

    // Send control transfer to reset to BOOTSEL mode
    libusb_control_transfer(handle, 1, request, 0, USB_INTERFACE, nullptr, 0, 10);
    std::cout << "Pico entering BOOTSEL mode." << std::endl;

    // Release interface and clean up
    libusb_release_interface(handle, USB_INTERFACE);
    libusb_close(handle);
    libusb_exit(ctx);

    return 0;
}

