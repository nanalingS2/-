#include "ms5611.h"

MS5611::MS5611(PinName sda, PinName scl, PinName csb)
    : i2c(sda,scl,csb)
    {
        reset(0x1E);
        wait_ms(1);

        get_atmos_pressure ();
        get_alt();
    }

    void MS5611::reset(long reg)
    {
        long cmd[8] = {reg};
        i2c.write(DEV_ADDR, &cmd, 8, 0);
    }
