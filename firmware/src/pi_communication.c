
#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include <c_utils/ringbuffer.h>

#include "settings.h"
#include "crc/crc.h"

enum PiCommand {
    PiCommandNone = 0,
    PiCommandNewSettings = 1,
    PiCommandRequestSensorValues = 2,
};
static enum PiCommand g_current_command = PiCommandNone;


static enum PiCommand match_start_sequence(Ringbuffer *rb_Rx)
{
	size_t count = ringbuffer_used_count(rb_Rx);
	if (count >= 4) {
		while (0 < count--) {
			uint32_t *ptr = ringbuffer_get_readable(rb_Rx);
			uint32_t start;
			memcpy(&start, ptr, 4);// = *ptr; Misaligned access, is that okay?
			if (start == 0x41424344) {
				ringbuffer_flush(rb_Rx, 4);
				return PiCommandNewSettings;
			} else {
				// no match, advance rb 1 byte, try again until magic sequence is found
				ringbuffer_advance(rb_Rx);
			}
		}
	}

	return PiCommandNone;

}

void pi_comm_tasks(Ringbuffer *rb_Rx)
{
    if (g_current_command == PiCommandNone) {
        g_current_command = match_start_sequence(rb_Rx);
    }

    if (g_current_command == PiCommandNewSettings) {
        size_t count = ringbuffer_used_count(rb_Rx);
		if (count >= sizeof(OperationSettings)) {
			OperationSettings *settings = ringbuffer_get_readable(rb_Rx);

            uint16_t res = crc16_usb_stream_check(&settings->crc, (uint8_t*)settings, 20);

            if (res == settings->crc) {
                const bool settings_ok = settings_update(settings);
                if (!settings_ok) {
                    // settings error
                }
            } else {
                // crc error
            }
			ringbuffer_clear(rb_Rx);
			g_current_command = PiCommandNone;
		}
    }
}