#include "validity.h"

#define FP_COMPONENT "validity"

enum {
    VALIDITY_138a_0097,
};

static int dev_discover(struct libusb_device_descriptor *dsc, uint32_t *devtype) {
    if (dsc->idProduct == 0x0097)
        return 1;
    return 0;
}

static int dev_init(struct fp_img_dev *dev, unsigned long driver_data) {
    // TODO
    return 0;
}

static void dev_deinit(struct fp_img_dev *dev) {
	void *user_data;
	user_data = FP_INSTANCE_DATA(FP_DEV(dev));
	g_free(user_data);
	libusb_release_interface(fpi_dev_get_usb_dev(FP_DEV(dev)), 0);
	fpi_imgdev_close_complete(dev);
}

static int dev_activate(struct fp_img_dev *dev) {
    //TODO
    return 0;
}

static void dev_deactivate(struct fp_img_dev *dev) {
    // TODO
}

static const struct usb_id id_table[] = {
	{ .vendor = 0x138a, .product = 0x0097, .driver_data = VALIDITY_138a_0097 },
	{ 0, 0, 0, },
};

struct fp_img_driver validity_driver = {
    .driver = {
        .id = VALIDITY_ID,
        .name = FP_COMPONENT,
        .full_name = "Validity90 driver",
        .id_table = id_table,
        .scan_type = FP_SCAN_TYPE_SWIPE,
        .discover = dev_discover,
    },
    .flags = 0,
    .img_width = -1,
    .img_height = -1,

    .open = dev_init,
    .close = dev_deinit,
    .activate = dev_activate,
    .deactivate = dev_deactivate,
};
