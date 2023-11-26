#define MEMORY_SIZE 1024 * 256
#define OS_SIZE 1024 * 100
#define OS_START 0
#define OS_END OS_START + OS_SIZE
#define STACK_SIZE 1024 * 10
#define STACK_START OS_END
#define STACK_END STACK_START + STACK_SIZE
#define HEAP_SIZE 1024 * 50
#define HEAP_START STACK_END
#define HEAP_END HEAP_START + HEAP_SIZE
#define IO_DISPLAY_SIZE 1024 * 64
#define IO_DISPLAY_START HEAP_END
#define IO_DISPLAY_END IO_DISPLAY_START + IO_DISPLAY_SIZE
#define IO_KEYBOARD_SIZE 1

#define IO_KEYBOARD_START IO_DISPLAY_END
// seekto=229376 in memory.txt

#define IO_KEYBOARD_END IO_KEYBOARD_START + IO_KEYBOARD_SIZE
#define FONTMAP_SIZE 1024 * 2
#define FONTMAP_START IO_KEYBOARD_END
#define FONTMAP_END FONTMAP_START + FONTMAP_SIZE
#define TEMP_SIZE 1024 * 38
#define TEMP_START FONTMAP_END
#define TEMP_END TEMP_START + TEMP_SIZE

// Keyboard constants
#define KEYBOARD_WAIT_TIME 5

// Control codes

#define CTRL_CODE_BACKSPACE 0x08
#define CTRL_CODE_ENTER 0x0A

#define CTRL_CODE_CTRL 0x11
#define CTRL_CODE_ALT 0x12
#define CTRL_CODE_SHIFT 0x10
#define CTRL_CODE_CAPSLOCK 0x14
#define CTRL_CODE_BACKSPACE 0x08

char font_map[128][8] = {
    {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, // U+0000 (nul)
    {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, // U+0001
    {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, // U+0002
    {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, // U+0003
    {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, // U+0004
    {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, // U+0005
    {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, // U+0006
    {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, // U+0007
    {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, // U+0008
    {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, // U+0009
    {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, // U+000A
    {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, // U+000B
    {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, // U+000C
    {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, // U+000D
    {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, // U+000E
    {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, // U+000F
    {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, // U+0010
    {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, // U+0011
    {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, // U+0012
    {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, // U+0013
    {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, // U+0014
    {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, // U+0015
    {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, // U+0016
    {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, // U+0017
    {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, // U+0018
    {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, // U+0019
    {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, // U+001A
    {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, // U+001B
    {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, // U+001C
    {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, // U+001D
    {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, // U+001E
    {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, // U+001F
    {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, // U+0020 (space)
    {0x18, 0x3C, 0x3C, 0x18, 0x18, 0x00, 0x18, 0x00}, // U+0021 (!)
    {0x36, 0x36, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, // U+0022 (")
    {0x36, 0x36, 0x7F, 0x36, 0x7F, 0x36, 0x36, 0x00}, // U+0023 (#)
    {0x0C, 0x3E, 0x03, 0x1E, 0x30, 0x1F, 0x0C, 0x00}, // U+0024 ($)
    {0x00, 0x63, 0x33, 0x18, 0x0C, 0x66, 0x63, 0x00}, // U+0025 (%)
    {0x1C, 0x36, 0x1C, 0x6E, 0x3B, 0x33, 0x6E, 0x00}, // U+0026 (&)
    {0x06, 0x06, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00}, // U+0027 (')
    {0x18, 0x0C, 0x06, 0x06, 0x06, 0x0C, 0x18, 0x00}, // U+0028 (()
    {0x06, 0x0C, 0x18, 0x18, 0x18, 0x0C, 0x06, 0x00}, // U+0029 ())
    {0x00, 0x66, 0x3C, 0xFF, 0x3C, 0x66, 0x00, 0x00}, // U+002A (*)
    {0x00, 0x0C, 0x0C, 0x3F, 0x0C, 0x0C, 0x00, 0x00}, // U+002B (+)
    {0x00, 0x00, 0x00, 0x00, 0x00, 0x0C, 0x0C, 0x06}, // U+002C (,)
    {0x00, 0x00, 0x00, 0x3F, 0x00, 0x00, 0x00, 0x00}, // U+002D (-)
    {0x00, 0x00, 0x00, 0x00, 0x00, 0x0C, 0x0C, 0x00}, // U+002E (.)
    {0x60, 0x30, 0x18, 0x0C, 0x06, 0x03, 0x01, 0x00}, // U+002F (/)
    {0x3E, 0x63, 0x73, 0x7B, 0x6F, 0x67, 0x3E, 0x00}, // U+0030 (0)
    {0x0C, 0x0E, 0x0C, 0x0C, 0x0C, 0x0C, 0x3F, 0x00}, // U+0031 (1)
    {0x1E, 0x33, 0x30, 0x1C, 0x06, 0x33, 0x3F, 0x00}, // U+0032 (2)
    {0x1E, 0x33, 0x30, 0x1C, 0x30, 0x33, 0x1E, 0x00}, // U+0033 (3)
    {0x38, 0x3C, 0x36, 0x33, 0x7F, 0x30, 0x78, 0x00}, // U+0034 (4)
    {0x3F, 0x03, 0x1F, 0x30, 0x30, 0x33, 0x1E, 0x00}, // U+0035 (5)
    {0x1C, 0x06, 0x03, 0x1F, 0x33, 0x33, 0x1E, 0x00}, // U+0036 (6)
    {0x3F, 0x33, 0x30, 0x18, 0x0C, 0x0C, 0x0C, 0x00}, // U+0037 (7)
    {0x1E, 0x33, 0x33, 0x1E, 0x33, 0x33, 0x1E, 0x00}, // U+0038 (8)
    {0x1E, 0x33, 0x33, 0x3E, 0x30, 0x18, 0x0E, 0x00}, // U+0039 (9)
    {0x00, 0x0C, 0x0C, 0x00, 0x00, 0x0C, 0x0C, 0x00}, // U+003A (:)
    {0x00, 0x0C, 0x0C, 0x00, 0x00, 0x0C, 0x0C, 0x06}, // U+003B (;)
    {0x18, 0x0C, 0x06, 0x03, 0x06, 0x0C, 0x18, 0x00}, // U+003C (<)
    {0x00, 0x00, 0x3F, 0x00, 0x00, 0x3F, 0x00, 0x00}, // U+003D (=)
    {0x06, 0x0C, 0x18, 0x30, 0x18, 0x0C, 0x06, 0x00}, // U+003E (>)
    {0x1E, 0x33, 0x30, 0x18, 0x0C, 0x00, 0x0C, 0x00}, // U+003F (?)
    {0x3E, 0x63, 0x7B, 0x7B, 0x7B, 0x03, 0x1E, 0x00}, // U+0040 (@)
    {0x0C, 0x1E, 0x33, 0x33, 0x3F, 0x33, 0x33, 0x00}, // U+0041 (A)
    {0x3F, 0x66, 0x66, 0x3E, 0x66, 0x66, 0x3F, 0x00}, // U+0042 (B)
    {0x3C, 0x66, 0x03, 0x03, 0x03, 0x66, 0x3C, 0x00}, // U+0043 (C)
    {0x1F, 0x36, 0x66, 0x66, 0x66, 0x36, 0x1F, 0x00}, // U+0044 (D)
    {0x7F, 0x46, 0x16, 0x1E, 0x16, 0x46, 0x7F, 0x00}, // U+0045 (E)
    {0x7F, 0x46, 0x16, 0x1E, 0x16, 0x06, 0x0F, 0x00}, // U+0046 (F)
    {0x3C, 0x66, 0x03, 0x03, 0x73, 0x66, 0x7C, 0x00}, // U+0047 (G)
    {0x33, 0x33, 0x33, 0x3F, 0x33, 0x33, 0x33, 0x00}, // U+0048 (H)
    {0x1E, 0x0C, 0x0C, 0x0C, 0x0C, 0x0C, 0x1E, 0x00}, // U+0049 (I)
    {0x78, 0x30, 0x30, 0x30, 0x33, 0x33, 0x1E, 0x00}, // U+004A (J)
    {0x67, 0x66, 0x36, 0x1E, 0x36, 0x66, 0x67, 0x00}, // U+004B (K)
    {0x0F, 0x06, 0x06, 0x06, 0x46, 0x66, 0x7F, 0x00}, // U+004C (L)
    {0x63, 0x77, 0x7F, 0x7F, 0x6B, 0x63, 0x63, 0x00}, // U+004D (M)
    {0x63, 0x67, 0x6F, 0x7B, 0x73, 0x63, 0x63, 0x00}, // U+004E (N)
    {0x1C, 0x36, 0x63, 0x63, 0x63, 0x36, 0x1C, 0x00}, // U+004F (O)
    {0x3F, 0x66, 0x66, 0x3E, 0x06, 0x06, 0x0F, 0x00}, // U+0050 (P)
    {0x1E, 0x33, 0x33, 0x33, 0x3B, 0x1E, 0x38, 0x00}, // U+0051 (Q)
    {0x3F, 0x66, 0x66, 0x3E, 0x36, 0x66, 0x67, 0x00}, // U+0052 (R)
    {0x1E, 0x33, 0x07, 0x0E, 0x38, 0x33, 0x1E, 0x00}, // U+0053 (S)
    {0x3F, 0x2D, 0x0C, 0x0C, 0x0C, 0x0C, 0x1E, 0x00}, // U+0054 (T)
    {0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x3F, 0x00}, // U+0055 (U)
    {0x33, 0x33, 0x33, 0x33, 0x33, 0x1E, 0x0C, 0x00}, // U+0056 (V)
    {0x63, 0x63, 0x63, 0x6B, 0x7F, 0x77, 0x63, 0x00}, // U+0057 (W)
    {0x63, 0x63, 0x36, 0x1C, 0x1C, 0x36, 0x63, 0x00}, // U+0058 (X)
    {0x33, 0x33, 0x33, 0x1E, 0x0C, 0x0C, 0x1E, 0x00}, // U+0059 (Y)
    {0x7F, 0x63, 0x31, 0x18, 0x4C, 0x66, 0x7F, 0x00}, // U+005A (Z)
    {0x1E, 0x06, 0x06, 0x06, 0x06, 0x06, 0x1E, 0x00}, // U+005B ([)
    {0x03, 0x06, 0x0C, 0x18, 0x30, 0x60, 0x40, 0x00}, // U+005C (\)
    {0x1E, 0x18, 0x18, 0x18, 0x18, 0x18, 0x1E, 0x00}, // U+005D (])
    {0x08, 0x1C, 0x36, 0x63, 0x00, 0x00, 0x00, 0x00}, // U+005E (^)
    {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF}, // U+005F (_)
    {0x0C, 0x0C, 0x18, 0x00, 0x00, 0x00, 0x00, 0x00}, // U+0060 (`)
    {0x00, 0x00, 0x1E, 0x30, 0x3E, 0x33, 0x6E, 0x00}, // U+0061 (a)
    {0x07, 0x06, 0x06, 0x3E, 0x66, 0x66, 0x3B, 0x00}, // U+0062 (b)
    {0x00, 0x00, 0x1E, 0x33, 0x03, 0x33, 0x1E, 0x00}, // U+0063 (c)
    {0x38, 0x30, 0x30, 0x3e, 0x33, 0x33, 0x6E, 0x00}, // U+0064 (d)
    {0x00, 0x00, 0x1E, 0x33, 0x3f, 0x03, 0x1E, 0x00}, // U+0065 (e)
    {0x1C, 0x36, 0x06, 0x0f, 0x06, 0x06, 0x0F, 0x00}, // U+0066 (f)
    {0x00, 0x00, 0x6E, 0x33, 0x33, 0x3E, 0x30, 0x1F}, // U+0067 (g)
    {0x07, 0x06, 0x36, 0x6E, 0x66, 0x66, 0x67, 0x00}, // U+0068 (h)
    {0x0C, 0x00, 0x0E, 0x0C, 0x0C, 0x0C, 0x1E, 0x00}, // U+0069 (i)
    {0x30, 0x00, 0x30, 0x30, 0x30, 0x33, 0x33, 0x1E}, // U+006A (j)
    {0x07, 0x06, 0x66, 0x36, 0x1E, 0x36, 0x67, 0x00}, // U+006B (k)
    {0x0E, 0x0C, 0x0C, 0x0C, 0x0C, 0x0C, 0x1E, 0x00}, // U+006C (l)
    {0x00, 0x00, 0x33, 0x7F, 0x7F, 0x6B, 0x63, 0x00}, // U+006D (m)
    {0x00, 0x00, 0x1F, 0x33, 0x33, 0x33, 0x33, 0x00}, // U+006E (n)
    {0x00, 0x00, 0x1E, 0x33, 0x33, 0x33, 0x1E, 0x00}, // U+006F (o)
    {0x00, 0x00, 0x3B, 0x66, 0x66, 0x3E, 0x06, 0x0F}, // U+0070 (p)
    {0x00, 0x00, 0x6E, 0x33, 0x33, 0x3E, 0x30, 0x78}, // U+0071 (q)
    {0x00, 0x00, 0x3B, 0x6E, 0x66, 0x06, 0x0F, 0x00}, // U+0072 (r)
    {0x00, 0x00, 0x3E, 0x03, 0x1E, 0x30, 0x1F, 0x00}, // U+0073 (s)
    {0x08, 0x0C, 0x3E, 0x0C, 0x0C, 0x2C, 0x18, 0x00}, // U+0074 (t)
    {0x00, 0x00, 0x33, 0x33, 0x33, 0x33, 0x6E, 0x00}, // U+0075 (u)
    {0x00, 0x00, 0x33, 0x33, 0x33, 0x1E, 0x0C, 0x00}, // U+0076 (v)
    {0x00, 0x00, 0x63, 0x6B, 0x7F, 0x7F, 0x36, 0x00}, // U+0077 (w)
    {0x00, 0x00, 0x63, 0x36, 0x1C, 0x36, 0x63, 0x00}, // U+0078 (x)
    {0x00, 0x00, 0x33, 0x33, 0x33, 0x3E, 0x30, 0x1F}, // U+0079 (y)
    {0x00, 0x00, 0x3F, 0x19, 0x0C, 0x26, 0x3F, 0x00}, // U+007A (z)
    {0x38, 0x0C, 0x0C, 0x07, 0x0C, 0x0C, 0x38, 0x00}, // U+007B ({)
    {0x18, 0x18, 0x18, 0x00, 0x18, 0x18, 0x18, 0x00}, // U+007C (|)
    {0x07, 0x0C, 0x0C, 0x38, 0x0C, 0x0C, 0x07, 0x00}, // U+007D (})
    {0x6E, 0x3B, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, // U+007E (~)
    {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}  // U+007F
};

char memory[MEMORY_SIZE];

void __load_char_as_bits(char c, char *out)
{
    int g = c;
    for (int i = 0; i < 8; i++)
    {
        out[i] = (g & 1) + '0';
        g >>= 1;
    }
}

char mread_char(int addr)
{
    return memory[addr];
}

void mwrite(char c, int addr)
{
    memory[addr] = c;
}

void minit()
{
    for (int i = 0; i < MEMORY_SIZE; i++)
    {
        memory[i] = 0;
    }
}

#define ROW_CHAR_SIZE 128
#define COLUMN_CHAR_SIZE 64
#define SCREEN_LOCK 0x00
#define MUL_CONS 9

const int max_com_len = 10; // max command length

// current path in the OS
char path[128];

int LINE = 0;   // current line (ROW)
int COLUMN = 0; // current column (COL)

int write_char(char c);
int write_char_at(char c, int line, int col);
int write_int(int a);

int write_string(char *msg, int len)
{
    if (SCREEN_LOCK == 0)
    {
        int g = 0;
        for (int i = 0; i < len; i++)
        {
            g = write_char(msg[i]);

            if (g != 0)
            {
                return g;
            }
        }
        return 0;
    }
}

int write_string_at(char *msg, int len, int line, int col)
{
    int g = 0;
    for (int i = 0; i < len; i++)
    {
        g = write_char_at(msg[i], line, col);
        if (g != 0)
        {
            return g;
        }

        col++;
        if (col == ROW_CHAR_SIZE)
        {
            col = 0;
            line += 8;
        }

        if (line == 8 * COLUMN_CHAR_SIZE)
        {
            line = 0;
            col = 0;

            return 1;
        }
    }
    return 0;
}

int write_int(int a)
{
    if (SCREEN_LOCK == 0)
    {
        char temp[10];
        int count = 0;
        while (a > 0)
        {
            temp[count++] = (a % 10) + '0';
            a /= 10;
        }

        for (int i = count - 1; i >= 0; i--)
        {
            write_char(temp[i]);
        }

        return 0;
    }

    return 1;
}

int set_cursor_pos(int line, int col)
{
    if (line < 0 || line >= 8 * COLUMN_CHAR_SIZE)
        return 1;
    if (col < 0 || col >= ROW_CHAR_SIZE)
        return 1;

    LINE = line;
    COLUMN = col;

    return 0;
}

void get_cursor_pos(int *vals)
{
    vals[0] = LINE;
    vals[1] = COLUMN;
}

int write_string_at_col(char *msg, int len, int line, int col)
{
    if (SCREEN_LOCK == 0)
    {
        if (line >= 8 * COLUMN_CHAR_SIZE)
            return 1;
        if (col >= ROW_CHAR_SIZE || col < 0)
            return 1;

        int g = 0;
        for (int i = 0; i < len; i++)
        {
            g = write_char_at(msg[i], line, col);
            if (g != 0)
            {
                return g;
            }

            line += 8;

            if (line == 8 * COLUMN_CHAR_SIZE)
            {
                line = 0;
                col = 0;

                return 1;
            }

            if (col == ROW_CHAR_SIZE)
            {
                col = 0;
                line += 8;
            }
        }
    }

    return 1;
}

int write_zero_line_at(int line)
{
    if (SCREEN_LOCK == 0)
    {
        if (line < 0 || line >= 8 * COLUMN_CHAR_SIZE)
            return 1;

        int A = IO_DISPLAY_START + ROW_CHAR_SIZE * line;
        for (int i = 0; i < ROW_CHAR_SIZE * 8; i++)
        {
            mwrite(0, A + i);
        }

        return 0;
    }

    return 1;
}

int write_zero_line()
{
    if (SCREEN_LOCK == 0)
    {
        int A = IO_DISPLAY_START + ROW_CHAR_SIZE * LINE;
        for (int i = 0; i < ROW_CHAR_SIZE * 8; i++)
        {
            mwrite(0, A + i);
        }

        return 0;
    }

    return 1;
}

int write_char(char c)
{
    // use write and read from mem.c
    if (SCREEN_LOCK == 0)
    {

        if (c == '\n')
        {
            COLUMN = 0;
            LINE += 8;
            if (LINE == 8 * COLUMN_CHAR_SIZE)
            {
                LINE = 0;
                COLUMN = 0;

                return 1;
            }

            return 0;
        }
        else if (c == '\r')
        {
            COLUMN = 0;
            return 0;
        }
        else if (c == '\f')
        {
            LINE += 8;
            if (LINE >= 8 * COLUMN_CHAR_SIZE)
            {
                LINE = 0;
                COLUMN = 0;
                return 1;
            }

            return 0;
        }
        else if (c == '\t')
        {
            COLUMN += 4;
            if (COLUMN >= ROW_CHAR_SIZE)
            {
                COLUMN = 0;
                LINE += 8;
                if (LINE >= 8 * COLUMN_CHAR_SIZE)
                {
                    LINE = 0;
                    COLUMN = 0;
                    return 1;
                }
            }

            return 0;
        }
        else if (c == CTRL_CODE_BACKSPACE)
        {
            if (COLUMN == 0)
            {
                if (LINE == 0)
                {
                    return 0;
                }
                else
                {
                    COLUMN = ROW_CHAR_SIZE - 1;
                    LINE -= 8;
                }
            }
            else
            {
                COLUMN--;
            }

            int A = IO_DISPLAY_START + ROW_CHAR_SIZE * LINE + COLUMN;
            for (int i = 0; i < 8; i++)
            {
                mwrite(0, A + ROW_CHAR_SIZE * i);
            }

            return 0;
        }
        else
        {
            char font[8];
            for (int i = 0; i < 8; i++)
            {
                font[i] = font_map[c][i];
            }

            int A = IO_DISPLAY_START + ROW_CHAR_SIZE * LINE + COLUMN; // location of the first character in the line
            for (int i = 0; i < 8; i++)
            {
                mwrite(font[i], A + ROW_CHAR_SIZE * i);
            }

            COLUMN++;
            if (COLUMN == ROW_CHAR_SIZE)
            { // if the row is full
                COLUMN = 0;
                LINE += 8;
                return 0;
            }

            if (LINE == 8 * COLUMN_CHAR_SIZE)
            { // if the screen is full
                LINE = 0;
                COLUMN = 0;

                return 1;
            }

            return 0;
        }
    }

    return 1;
}

int write_char_at(char c, int line, int col)
{
    if (SCREEN_LOCK == 0)
    {

        if (line < 0 || line >= 8 * COLUMN_CHAR_SIZE)
            return 1;
        if (col < 0 || col >= ROW_CHAR_SIZE)
            return 1;

        char font[8];
        for (int i = 0; i < 8; i++)
        {
            font[i] = font_map[c][i];
        }

        int A = IO_DISPLAY_START + ROW_CHAR_SIZE * line + col; // location of the first character in the line
        for (int i = 0; i < 8; i++)
        {
            mwrite(font[i], A + ROW_CHAR_SIZE * i);
        }

        return 0;
    }

    return 1;
}

void write_face(char font[128][16])
{
    if (SCREEN_LOCK == 0)
    {

        LINE += 8;
        COLUMN = 0;

        int A = IO_DISPLAY_START + LINE * ROW_CHAR_SIZE + COLUMN;

        for (int i = 0; i < 128; i++)
        {
            for (int j = 0; j < 16; j++)
            {
                mwrite(font[i][j], A + i * ROW_CHAR_SIZE + j);
            }
        }

        LINE += 128;
        COLUMN = 0;

        if (LINE >= 8 * COLUMN_CHAR_SIZE)
        {
            LINE = 0;
            COLUMN = 0;
        }
    }
}

int display_up()
{
    if (SCREEN_LOCK == 0)
    {
        int A = IO_DISPLAY_START;
        for (int j = 0; j < 8; j++)
        {
            for (int addr = 0; addr < IO_DISPLAY_SIZE - ROW_CHAR_SIZE; addr++)
            {
                char temp = mread_char(A + addr + ROW_CHAR_SIZE);
                // reverse temp
                char temp2 = 0;

                for (int i = 0; i < 8; i++)
                {
                    if ((temp >> i) & 1)
                    {
                        temp2 |= (1 << (7 - i));
                    }
                }

                mwrite(temp2, A + addr);
            }
        }

        // clear the last line (A)
        for (int i = 0; i < ROW_CHAR_SIZE * 8; i++)
        {
            mwrite(0, A + i);
        }

        // update the current line
        LINE -= 8;
        if (LINE < 0)
        {
            LINE = 0;
        }

        return 0;
    }

    return 1;
}

int display_down()
{
    if (SCREEN_LOCK == 0)
    {
        int A = IO_DISPLAY_START;

        for (int j = 0; j < 8; j++)
        {
            for (int addr = IO_DISPLAY_SIZE - ROW_CHAR_SIZE; addr >= 0; addr--)
            {
                char temp = mread_char(A + addr);
                // reverse temp
                char temp2 = 0;

                for (int i = 0; i < 8; i++)
                {
                    if ((temp >> i) & 1)
                    {
                        temp2 |= (1 << (7 - i));
                    }
                }

                mwrite(temp2, A + addr + ROW_CHAR_SIZE);
            }
        }
        // clear the first line (A)
        for (int i = 0; i < ROW_CHAR_SIZE * 8; i++)
        {
            mwrite(0, A + i);
        }

        // update the current line
        LINE += 8;
        if (LINE >= 8 * COLUMN_CHAR_SIZE)
        {
            LINE = 8 * COLUMN_CHAR_SIZE - 1;
        }

        return 0;
    }

    return 1;
}

// reset the entire display
void clear_screen()
{
    if (SCREEN_LOCK == 0)
    {
        int A = IO_DISPLAY_START + IO_DISPLAY_SIZE - 1;
        for (int i = A; i >= IO_DISPLAY_START; i--)
        {
            mwrite(0, i);
        }

        LINE = 0;
        COLUMN = 0;
    }
}

#define INT_END_POINT 0x2E

void keyboard_init()
{
    int start = IO_KEYBOARD_START;
    int end = IO_KEYBOARD_START + IO_KEYBOARD_SIZE;
    for (int i = start; i < end; i++)
    {
        mwrite('\0', i);
    }
}

int keyboard_clear_input()
{
    mwrite(0, IO_KEYBOARD_START);
    return 0;
}

char keyboard_get_input()
{
    char input = 0;
    keyboard_clear_input();

    while (1)
    {
        char f = mread_char(IO_KEYBOARD_START);
        if (f != 0)
        {
            input = f;
            mwrite(0, IO_KEYBOARD_START);
            break;
        }
    }

    return input;
}

int keyboard_get_int()
{
    int ans = 0;

    while (1)
    {

        char f = mread_char(IO_KEYBOARD_START);
        mwrite(0, IO_KEYBOARD_START);

        if (f == INT_END_POINT)
        {
            break;
        }
        else if (f != 0)
        {
            if (f >= '0' && f <= '9')
            {
                ans = ans * 10 + (f - '0');
            }
            else if (f == '\b')
            {
                ans /= 10;
            }
            else
            {
                break;
            }
        }
    }

    return ans;
}

void convert_keyinput_to_string(char input, char *out)
{
    switch (input)
    {
    case CTRL_CODE_ENTER:
    {
        // ENTR
        out[0] = 'E';
        out[1] = 'N';
        out[2] = 'T';
        out[3] = 'R';
    }

    case CTRL_CODE_ALT:
    {
        // ALT
        out[0] = 'A';
        out[1] = 'L';
        out[2] = 'T';
        out[3] = '\0';
    }

    case CTRL_CODE_SHIFT:
    {
        // SHFT
        out[0] = 'S';
        out[1] = 'H';
        out[2] = 'F';
        out[3] = 'T';
    }

    default:
    {
        out[0] = input;
        out[1] = '\0';
    }
    }
}

int isEscape(char input)
{
    return input == 0x1B;
}

int rand_lfsr;
int rand_bit;

int rand_engine = 0xACE1u;

void set_seed(int seed)
{
    rand_engine = (((seed | rand_engine) * 7621) + 1) % 32768;
    rand_lfsr = rand_engine;
}

int rand()
{
    rand_bit = ((rand_lfsr >> 0) ^ (rand_lfsr >> 2) ^ (rand_lfsr >> 3) ^ (rand_lfsr >> 5)) & 1;
    rand_lfsr = (rand_lfsr >> 1) | (rand_bit << 15);

    return rand_lfsr % 100;
}

char board[3][3];
char player = 'X', computer = 'O';

// 0 easy, 1 mid , 2 hard

void initializeBoard()
{
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            board[i][j] = ' ';
        }
    }
}

void printBoard()
{
    write_string("     1 2 3\n", 11);
    for (int i = 0; i < 3; i++)
    {
        write_char(' ');
        write_char(' ');
        write_char(' ');
        write_char(' ');
        write_char(49 + i);
        for (int j = 0; j < 3; j++)
        {
            write_char(board[i][j]);
            if (j < 2)
                write_char('|');
        }
        write_char('\n');
        if (i < 2)
            write_string("     -----\n", 11);
    }
    write_char('\n');
}

int isBoardFull()
{
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            if (board[i][j] == ' ')
                return 0;
        }
    }
    return 1;
}

int isGameOver(char player)
{
    for (int i = 0; i < 3; i++)
    {
        if (board[i][0] == player && board[i][1] == player && board[i][2] == player)
            return 1;
        if (board[0][i] == player && board[1][i] == player && board[2][i] == player)
            return 1;
    }
    if (board[0][0] == player && board[1][1] == player && board[2][2] == player)
        return 1;
    if (board[0][2] == player && board[1][1] == player && board[2][0] == player)
        return 1;
    return 0;
}

int makeMove(int row, int col, char player)
{
    if (row < 0 || row >= 3 || col < 0 || col >= 3 || board[row][col] != ' ')
        return 0;
    board[row][col] = player;
    return 1;
}

void computerMove_easy()
{
    int row, col;

    do
    {
        row = rand() % 3;
        col = rand() % 3;
    } while (!makeMove(row, col, computer));
}

int minimax(char board[3][3], int depth, int isMaximizing)
{
    char result = isGameOver(computer) ? 1 : isGameOver(player) ? -1
                                         : isBoardFull()        ? 0
                                                                : 2;
    if (result != 2)
        return result;

    int bestScore = isMaximizing ? -1000 : 1000;
    char currentPlayer = isMaximizing ? computer : player;

    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            if (board[i][j] == ' ')
            {
                board[i][j] = currentPlayer;
                int score = minimax(board, depth + 1, !isMaximizing);
                board[i][j] = ' ';
                if (isMaximizing)
                {
                    if (score > bestScore)
                        bestScore = score;
                }
                else
                {
                    if (score < bestScore)
                        bestScore = score;
                }
            }
        }
    }

    return bestScore;
}

void computerMove_hard()
{
    int bestScore = -1000;
    int bestMove[2] = {-1, -1};

    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            if (board[i][j] == ' ')
            {
                board[i][j] = computer;
                int score = minimax(board, 0, 0);
                board[i][j] = ' ';
                if (score > bestScore)
                {
                    bestScore = score;
                    bestMove[0] = i;
                    bestMove[1] = j;
                }
            }
        }
    }

    makeMove(bestMove[0], bestMove[1], computer);
}
int computerMove_med()
{
    // Check for a win or block the player from winning
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            if (board[i][j] == ' ')
            {
                board[i][j] = computer;
                if (isGameOver(computer))
                {
                    return 1; // Computer wins
                }
                board[i][j] = ' '; // Undo the move
            }
        }
    }

    // Try to take the center if it's available
    if (board[1][1] == ' ')
    {
        board[1][1] = computer;
        return 0; // No win yet
    }

    // Try to take a corner
    const int corners[4][2] = {{0, 0}, {0, 2}, {2, 0}, {2, 2}};
    for (int i = 0; i < 4; i++)
    {
        int row = corners[i][0];
        int col = corners[i][1];
        if (board[row][col] == ' ')
        {
            board[row][col] = computer;
            return 0; // No win yet
        }
    }

    // Take any available edge
    const int edges[4][2] = {{0, 1}, {1, 0}, {1, 2}, {2, 1}};
    for (int i = 0; i < 4; i++)
    {
        int row = edges[i][0];
        int col = edges[i][1];
        if (board[row][col] == ' ')
        {
            board[row][col] = computer;
            return 0; // No win yet
        }
    }

    return 0; // No moves left (shouldn't reach this point)
}

int tic_tac_toe(int game_diff)
{
    set_seed(1);
    initializeBoard();

    while (1)
    {
        clear_screen();
        write_string("Welcome to Tic-Tac-Toe!\n\n", 25);

        if (game_diff == 0)
        {
            write_string("Easy Mode\n\n", 11);
        }
        else if (game_diff == 1)
        {
            write_string("Medium Mode\n\n", 13);
        }
        else
        {
            write_string("Hard Mode\n\n", 11);
        }

        printBoard();
        int row, col;

        write_string("Enter your move (row and column, e.g., 1 enter 2 enter): \n", 58);
        row = keyboard_get_input();
        col = keyboard_get_input();

        row -= 48;
        col -= 48;

        row--; // Adjust for 0-based indexing
        col--;

        if (!makeMove(row, col, player))
        {
            write_string("Invalid move! Try again.\n", 25);
            continue;
        }

        if (isGameOver(player))
        {
            printBoard();
            write_string("Congratulations! You win!\n", 26);
            break;
        }

        if (isBoardFull())
        {
            printBoard();
            write_string("It's a draw!\n", 13);
            break;
        }

        if (game_diff == 0)
            computerMove_easy();
        else if (game_diff == 1)
            computerMove_med();
        else
            computerMove_hard();

        if (isGameOver(computer))
        {
            printBoard();
            write_string("Computer wins! You lose.\n", 25);
            break;
        }

        if (isBoardFull())
        {
            printBoard();
            write_string("It's a draw!\n", 13);
            break;
        }
    }

    return 0;
}

void os_start()
{
    // initialize the kernel
    minit();
}

void display_1()
{
    write_string("This content is shown from inside the screen\n", 45);
    // write_face(font_0);
    write_string("\n\n", 2);

    write_string("Functionality of the Display:\n", 30);
    write_string("1. Write a string\n", 18);
    write_string("2. Write a character\n", 21);
    write_string("3. Write a face\n", 16);
    write_string("4. Write a string at a given position\n", 38);
    write_string("5. Write a character at a given position\n", 41);
    write_string("6. Set cursor position\n", 23);
    write_string("7. Get cursor position\n", 23);
    write_string("8. Clear screen\n", 16);
    write_string("9. Clear line\n", 14);
    write_string("10. Print New Line\n", 19);
    write_string("11. Print Tab\n", 14);
    write_string("12. Support Backspace\n", 22);
    write_string("13. Print Form Feed\n", 20);
    write_string("14. Print Carriage Return\n", 26);
    write_string("15. Print Integer\n", 18);

    write_string("\n\n", 2);
    write_string("The End\n", 8);
}

void initial_display()
{
    write_string("Welcome to Flex OS\n\n", 20);
    write_string("Press 'c' to clear screen\n\n", 27);
    write_string("Press 'd' to display some example content\n\n", 43);
    write_string("Press 'e' to play tic tac toe with the computer (easy)\n\n", 56);
    write_string("Press 'm' to play tic tac toe with the computer (medium)\n\n", 58);
    write_string("Press 'h' to play tic tac toe with the computer (hard)\n\n", 56);
    write_string("Press 't' to return back to terminal\n\n", 38);
    write_string("Press 'r' to get random numbers\n\n", 33);
    write_string("Press 'i' to get integer input\n\n", 32);
    write_string("Press 'q' to exit terminal\n", 27);
}

void int_input()
{
    clear_screen();
    keyboard_clear_input();

    write_string("Enter an integer: \n", 19);
    int input = keyboard_get_int();
    write_string("The integer is: ", 16);
    write_int(input);
    write_char('\n');
}

// function to capture data from memory and update the display
void terminal()
{
    // init_memory();
    clear_screen();
    initial_display();
    int isn = 0;

    while (1)
    {
        // get input from keyboard
        char input = keyboard_get_input();

        if (input == 'c')
        {
            clear_screen();
            isn = 0;
        }
        else if (input == 'd')
        {
            display_1();
            isn = 0;
        }
        else if (input == 'q')
        {
            clear_screen();
            write_string("Exiting Terminal\n", 17);
            break;
        }
        else if (input == 'e')
        {
            tic_tac_toe(0);
            isn = 0;
        }
        else if (input == 'm')
        {
            tic_tac_toe(1);
            isn = 0;
        }
        else if (input == 'h')
        {
            tic_tac_toe(2);
            isn = 0;
        }
        else if (input == 'i')
        {
            int_input();
        }
        else if (input == 't')
        {
            clear_screen();
            initial_display();
            isn = 0;
        }
        else if (input == 'r')
        {
            int seed = 0;
            int count = 0;

            write_string("Enter the seed for the random number generator: \n", 49);
            seed = keyboard_get_int();
            write_string("Enter the count of random numbers you want: \n", 45);
            count = keyboard_get_int();

            write_string("The random numbers are: \n\n", 26);
            set_seed(seed);

            for (int i = 0; i < count; i++)
            {
                int random = rand();
                write_char(' ');
                write_int(i + 1);
                write_char(' ');
                write_char(':');
                write_char(' ');
                write_int(random);
                write_char('\n');
            }
        }
        else
        {
            if (!isn)
            {
                isn = 1;
                write_string("\nCharacter printing\n", 20);
            }
            write_char(input);
        }
    }
}

void display_test()
{
    clear_screen();
    write_string("Team RISC V1\n\n\n", 16);
    write_string_at("Welcome to Flex OS\n\n", 20, 24, 0);

    set_cursor_pos(32, 0);
    write_char('\n');
    write_string("Namo 2024!\n\n", 12);
    write_string("India lifts the World Cup after 28 years!", 42);

    int val[2];

    write_char('\n');
    // write_face(font_2);

    get_cursor_pos(val);

    int line = val[0];
    int col = val[1];

    write_string_at("Hindu", 5, line - 104, col + 20);
    write_string_at_col("Bharat", 6, line - 112, col + 35);

    get_cursor_pos(val);
    line = val[0];

    set_cursor_pos(line - 8, 0);

    // write_char('\n');
    // write_face(font_0);
    // write_char('\n');
    // write_face(font_1);
    // write_char('\n');

    write_string("Kakkos: \f", 9);
    get_cursor_pos(val);
    line = val[0];
    write_char('\r');
    write_zero_line(line);
    write_string("CS 342", 6);
    write_char(CTRL_CODE_BACKSPACE);

    write_char('\t');
    write_string("After Tab", 9);
}

int main()
{
    os_start();
    terminal();
    return 0;
}
