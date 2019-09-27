#include <stdbool.h>

#include "drivers_api.h"

/* SSM states for activate_ssm */
enum SSM_STATE {
    /*
    SSM_INITIAL_ABORT_1,
    SSM_INITIAL_ABORT_2,
    SSM_INITIAL_ABORT_3,
    SSM_CLEAR_EP2,
    SSM_TURN_OFF,

    SSM_TURN_ON,

    SSM_ASK_INTERRUPT,
    */
    SSM_WAIT_INTERRUPT,
    SSM_RECEIVE_FINGER,
    /*
    SSM_SUBMIT_IMAGE,

    SSM_NEXT_RECEIVE,
    SSM_WAIT_ANOTHER_SCAN,
    */

    SSM_STATES_AMOUNT
};

/* The main driver structure */
struct vfs_0097_dev_t {
    /* One if we were asked to read fingerprint, zero otherwise */
    bool active;

    /* Control packet parameter for send_control_packet */
    uint8_t *control_packet;

    /* For dev_deactivate to check whether ssm still running or not */
    bool ssm_active;

    /* Current async transfer */
    struct libusb_transfer *transfer;

    /* Should we call fpi_imgdev_activate_complete or
     * fpi_imgdev_deactivate_complete */
    bool need_report;

    /* Should we wait more for interrupt */
    bool wait_interrupt;

    /* Received fingerprint raw lines */
    struct vfs_line *lines_buffer;

    /* Current number of received bytes and current memory used by data */
    uint32_t bytes, memory;

    /* USB buffer for fingerprint */
    uint8_t *usb_buffer;

    /* Received interrupt data */
    uint8_t interrupt[8];
};
