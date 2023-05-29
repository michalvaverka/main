/**
    @filename:  main.c
    @author:    Michal Vaverka

    @description:
                Main file containing the whole solution

    @projectdescription: 
                The task was to write a code capable of using STDIN and STDOUT, while being compiled with
                "-ffreestanding -nostdlib -nostdinc -static -m32"; no standard libraries.

                This task was given to me in subject OSY (Operacni systemy) and I managed to get full points.

    @predisclaimer:
                Disclaimer and rules on usage are listed in order to avoid plagiarization in academic institutions.
    
    @disclaimer:
        !!! READ !!!
                Any part of this code can be used IF AND ONLY IF all of the following conditions hold:
                    1) The whole header of this file (from the @filename to the end of the @disclaimer section) must be pasted
                            directly above where the borrowed snippet/whole code is used,
                    2) The project borrowing this code IS NOT commercial, NOR accademical,
                    3) The creator of project borrowing this code will NOT present this project to a superior figure in his organization.

                Any usage in compliance with rules listed above is allowed.

                Michal Vaverka, 2023.
*/
#define STDIN_FILENO 0
#define STDOUT_FILENO 1

#define __NR_exit_group 252
#define __NR_write 4
#define __NR_read 3

void _exit(int err_num)
{
    unsigned syscall = __NR_exit_group;
    asm volatile (
        "int $0x80;"
        : 
        : "a" (syscall), "b" (err_num)
        : "memory" );
}

int strlen(const char *string)
{
    int ret = 0;
    while(string[ret] != '\0') ret++;

    return ret;
}

int isnum(char ch)
{
    return ch >= '0' && ch <= '9';
}

int isspc(char ch)
{
    return ch == ' ' || ch == '\n';
}

/* Adding on the end of buffer (keeping termination) */
void add_to_buff(char *buff, char to_push)
{
    int end_index = strlen(buff);

    buff[end_index] = to_push;
    buff[end_index + 1] = '\0';
}

char get_hex_digit(unsigned digit)
{
    char ret;

    switch (digit)
    {
        case 10:
            ret = 'a';
            break;
        case 11:
            ret = 'b';
            break;
        case 12:
            ret = 'c';
            break;
        case 13:
            ret = 'd';
            break;
        case 14:
            ret = 'e';
            break;
        case 15:
            ret = 'f';
            break;
        default:
            ret = '$';
            break;
    }

    return ret;
}

/* Adds decadic number in hexadecimal format to a given buff */
void dec_to_hex_string(char *buff, unsigned num_to_conv)
{
    char conv_buff[30];
    int i;

    for (i = 0; i < 30; i++)
    {
        conv_buff[i] = 0;
    }

    /* Converting to hex string, keeping it backwards in local buffer */
    unsigned temp;
    for (i = 0; ; i++)
    {
        temp = num_to_conv % 16;
        conv_buff[i] = temp < 10 ? temp + '0' : get_hex_digit(temp);
        num_to_conv = num_to_conv / 16;
        if (num_to_conv == 0) break;
    }

    /* Adding to buff in correct order */
    for (; i >= 0; i--)
    {
        add_to_buff(buff, conv_buff[i]);
    }
}

void sprintf(char *buff, const char *fmt, unsigned num_to_print)
{
    int fmt_index = 0;
    buff[0] = '\0';
    while (fmt[fmt_index] != '\0')
    {
        if (fmt[fmt_index] != '%')
        {
            add_to_buff(buff, fmt[fmt_index]);
        } else
        {
            fmt_index++;
            if (fmt[fmt_index] == 'x')
            {
                dec_to_hex_string(buff, num_to_print);
            }
        }

        fmt_index++;
    }
}

// i386          ebx   ecx   edx   esi   edi   ebp   -
int write(int file, char *buff, int to_write)
{
    unsigned syscall = __NR_write;
    int ret;

    asm volatile (
        "int $0x80;"
        : "=a" (ret)
        : "a" (syscall), "b" (file), "c" ((const char *) buff), "d" (to_write) 
        : "memory", "cc" );

    return ret;
}

int read(int file, char *buff, int to_read)
{
    unsigned syscall = __NR_read;
    int ret;
    
    asm volatile (
        "int $0x80;"
        : "=a" (ret)
        : "a" (syscall), "b" (file), "c" ((const char *) buff), "d" (to_read)
        : "memory", "cc"
    );

    return ret;
}

static void print(unsigned num)
{
    char buf[32];
    sprintf(buf, "0x%x\n", num);
    int ret = write(STDOUT_FILENO, buf, strlen(buf));
    
    if (ret == -1)
        _exit(1);
}

int main()
{
    char buf[32];
    unsigned num = 0;
    int i;
    int num_digits = 0;
    unsigned chars_to_process = 0;

    for (/* no init */; /* no end condition */; i++, chars_to_process--) {
        if (chars_to_process == 0) {
            int ret = read(STDIN_FILENO, buf, sizeof(buf));
            if (ret < 0)
                return 1;
            i = 0;
            chars_to_process = ret;
        }
        if (
            num_digits > 0
            && (chars_to_process == 0 /* EOF */ || !isnum(buf[i]))
        ) {
            print(num);
            num_digits = 0;
            num = 0;
        }
        if (
            chars_to_process == 0 /* EOF */
            || (!isspc(buf[i]) && !isnum(buf[i]))
        )
            return 0;

        if (isnum(buf[i])) {
            num = num * 10 + buf[i] - '0';
            num_digits++;
        }
    }
}

void _start()
{
    int ret = main();
    _exit(ret);
}
