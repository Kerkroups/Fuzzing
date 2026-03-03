#include <iostream>
#include <cstdint>
#include <cstdio>
#include <unistd.h>
#include <stddef.h>

__AFL_FUZZ_INIT();

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
   char filename[] = "/tmp/fuzz_image_XXXXXX";
    int fd = mkstemp(filename);
    if (fd == -1) return 0;

    FILE *out = fdopen(fd, "wb");
    if (!out) {
        close(fd);
        unlink(filename);
        return 0;
    }
    
    fwrite(data, 1, size, out);
    fclose(out);

    try {
        // CODE LOGIC
    } catch(...) {
    }

    unlink(filename);
    return 0;

}

extern "C" int main(int argc, char **argv) {
#ifdef __AFL_HAVE_MANUAL_CONTROL
    __AFL_INIT();
#endif

    while (__AFL_LOOP(10000)) {
        LLVMFuzzerTestOneInput(__AFL_FUZZ_TESTCASE_BUF, __AFL_FUZZ_TESTCASE_LEN);
    }

    return 0;
}

