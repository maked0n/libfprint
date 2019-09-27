#include "vfs0097.h"

#define FP_COMPONENT "vfs0097"

static int dev_discover(struct libusb_device_descriptor *dsc,
                        uint32_t *devtype) {
    if (dsc->idProduct == 0x0097) return 1;
    return 0;
}

static void activate_ssm(fpi_ssm *ssm, struct fp_dev *_dev, void *user_data) {
    // TODO
}

static void dev_open_callback(fpi_ssm *ssm, struct fp_dev *_dev,
                              void *user_data) {
    /* Notify open complete */
    fpi_imgdev_open_complete(user_data, 0);
    fpi_ssm_free(ssm);
}

static int dev_init(struct fp_img_dev *dev, unsigned long driver_data) {
    struct vfs_0097_dev_t *vdev;

    /* Claim usb interface */
    int error = libusb_claim_interface(fpi_dev_get_usb_dev(FP_DEV(dev)), 0);
    if (error < 0) {
        /* Interface not claimed, return error */
        fp_err("could not claim interface 0");
        return error;
    }
    vdev = g_malloc0(sizeof(struct vfs_0097_dev_t));
    fp_dev_set_instance_data(FP_DEV(dev), vdev);

    /* Clearing previous device state */
    fpi_ssm *ssm =
        fpi_ssm_new(FP_DEV(dev), activate_ssm, SSM_STATES_AMOUNT, dev);
    fpi_ssm_start(ssm, dev_open_callback);
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
    // TODO
    return 0;
}

static void dev_deactivate(struct fp_img_dev *dev) {
    // TODO
}

static const struct usb_id id_table[] = {
    {.vendor = 0x138a, .product = 0x0097},
    {
        0,
        0,
        0,
    },
};

struct fp_img_driver validity_driver = {
    .driver =
        {
            .id = VFS0097_ID,
            .name = FP_COMPONENT,
            .full_name = "Validity VFS0097",
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
