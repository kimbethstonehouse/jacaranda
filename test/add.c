int atoi(char *c) {
    return *c-0x30;
}

int main(int argc, char **argv) {
    return atoi(argv[1]) + atoi(argv[2]);
}