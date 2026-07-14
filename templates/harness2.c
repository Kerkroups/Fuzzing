#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <unistd.h>

#include <LightGBM/c_api.h>

__AFL_FUZZ_INIT();

int parse_data(const char *filename)
{
    // Code logig;
}

int main(void)
{
#ifdef __AFL_HAVE_MANUAL_CONTROL
    __AFL_INIT();
#endif

    unsigned char *buf = __AFL_FUZZ_TESTCASE_BUF;
    const char *tmpfile = "/tmp/afl_input.txt";

    while (__AFL_LOOP(10000)) {

        int len = __AFL_FUZZ_TESTCASE_LEN;

        FILE *f = fopen(tmpfile, "wb");
        if (!f)
            continue;

        fwrite(buf, 1, len, f);
        fclose(f);

        parse_data(tmpfile);
    }

    unlink(tmpfile);

    return 0;
}
