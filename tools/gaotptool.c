#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include "../src/gaotp.c"

void print_help() {
    printf(
        "Usage: gaotptool\n"
        "    -s, --secret-key <secret_key>     The base32-encoded secret key used to generate one-time password\n"
        "    [-u, --unix-time <unix_time>]     The unix timestamp used to generate one-time password\n"
    );
}

int main(int argc, char **argv) {

    char* secret_key = NULL;
    int64_t unix_time = -1;
    int c;

    // https://www.gnu.org/software/libc/manual/html_node/Getopt-Long-Option-Example.html
    while (1) {
        static struct option long_options[] = {          
            {"secret-key",  required_argument, 0,   's'},
            {"unix-time",   required_argument, 0,   'u'},
            {"help",        no_argument,       0,   'h'},
            {NULL,          0,                 NULL, 0}
        };
      /* getopt_long stores the option index here. */
        int option_index = 0;

        c = getopt_long(argc, argv, "s:u:h", long_options, &option_index);

        /* Detect the end of the options. */
        if (c == -1)
            break;
        switch (c) {
            case 's':
                secret_key = optarg;
                break;
            case 'u':
                unix_time = strtol(optarg, NULL, 10);
                break;
            case 'h':
                print_help();
                return 0;
            case '?':
                print_help();
                return 1;
            default:
                return 1;
        }
    }
    /* Print any remaining command line arguments (not options). */
    if (optind < argc) {        
        while (optind < argc)
            printf ("%s ", argv[optind++]);
        putchar ('\n');
        print_help();
        return 1;
    }

    if (secret_key == NULL) {
        print_help();
        return 1;
    }
    int otp = get_otp(secret_key, unix_time);
    if (otp == -1) {
        fprintf(stderr, "secret_key [%s] is not a valid base32 string\n", secret_key);
        return 1;
    } else if (otp == -2) {
        fprintf(stderr, "malloc() failed\n");
    } else if (otp < 0) {
        fprintf(stderr, "unknown error %d\n", otp);
    }

    printf("%06d\n", otp);
    return 0;
}
