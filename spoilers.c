finclude <fcntl.h>
#include <stddef.h>
#include <unistd.h>

int main(int argc, char **argv)
{
    if (argc != 2)
    {
        write(2, "Invalid number of arguments\n", 28);
        return 1;
    }
    int fd = open(argv[1], O_RDONLY);
    if (fd == -1)
    {
        write(2, "Could not open file\n", 20);
        return 1;
    }
    off_t k = lseek(fd, -1, SEEK_END);
    char s[1] = { 0 };
    char v[3] = { 0 };
    // v[2] = 0;
    off_t i = 1;
    int l = 0;
    while ((i < k) && (l < 2))
    {
        lseek(fd, -i, SEEK_END);
        ssize_t r = read(fd, s, 1);
        if (r == -1)
            return 1;
        i++;
        if (!((s[0] == '\n') || (s[0] == '\f') || (s[0] == '\r')
              || (s[0] == '\t') || (s[0] == '\v') || (s[0] == 32)))
        {
            v[l] = s[0];
            l++;
        }
    }
    char z = v[0];
    v[0] = v[1];
    v[1] = z;
    char q = '\n';
    if (l == 2)
    {
        write(STDOUT_FILENO, v, 2);
        write(STDOUT_FILENO, &q, 1);
        return 0;
    }
    write(2, "File is not long enough\n", 24);
    return 1;
}
