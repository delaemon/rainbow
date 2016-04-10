#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define _GNU_SOURCE
#include <getopt.h>
#define STRING_BUF_SIZE 1024
#define DEFAULT_COUNT 1

static struct option longopts[] = {
    {"count", required_argument, NULL, 'c'},
    {0,0,0,0}
};

int
main(int argc, char *argv[]) {
    int opt;
    int count = DEFAULT_COUNT;
    if (argc > 1) {
        while ((opt = getopt_long(argc, argv, "c:", longopts, NULL)) != -1) {
            switch (opt) {
                case 'c':
                    count = atoi(optarg);
                    break;
                case '?':
                    fprintf(stderr, "usage: %s [-c COUNT] [STRING...]\n", argv[0]);
                    break;
            }
        }
    }

    int i = 0;
    char buf[STRING_BUF_SIZE];
    if (optind < argc){
        int len = strlen(argv[optind]);
        for (; i < len; i++) {
            printf("\e[3%dm%c", i * 1 / count % 7 + 1, *argv[optind]++);
        }
        putchar('\n');
    } else if (fgets(buf, STRING_BUF_SIZE, stdin)) {
        int len = strlen(buf);
        for (; i < len; i++) {
            printf("\e[3%dm%c", i * 1 / count % 7 + 1, buf[i]);
        }
    }
    return 0;
}
