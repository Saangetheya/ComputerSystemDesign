// global.h

// int MEMORY_SIZE = 262144; // 1024 * 256  // modified to 200
int MEMORY_SIZE = 262144;
int OS_SIZE = 1024; // 1024 * 100
int OS_START = 0;
int OS_END = 1024;      // OS_START + OS_SIZE
int STACK_SIZE = 10240; // 1024 * 10
int STACK_START = 1024; // OS_END
int STACK_END = 11264;  // STACK_START + STACK_SIZE
// int HEAP_SIZE = 51200;            // 1024 * 50 // modified to 40
int HEAP_SIZE = 51200;
int HEAP_START = 11264;   // STACK_END
int HEAP_END = 576716800; // HEAP_START + HEAP_SIZE
// int IO_DISPLAY_SIZE = 65536;      // 1024 * 64
int IO_DISPLAY_SIZE = 38912;      // modified to 38
int IO_DISPLAY_START = 576716800; // HEAP_END
int IO_DISPLAY_END = 576782336;   // IO_DISPLAY_START + IO_DISPLAY_SIZE
int IO_KEYBOARD_SIZE = 1;

int IO_KEYBOARD_START = 576782336; // IO_DISPLAY_END

// seekto=229376 in memory.txt

int IO_KEYBOARD_END = 576782337; // IO_KEYBOARD_START + IO_KEYBOARD_SIZE
int FONTMAP_SIZE = 2048;         // 1024 * 2
int FONTMAP_START = 576782337;   // IO_KEYBOARD_END
int FONTMAP_END = 576784385;     // FONTMAP_START + FONTMAP_SIZE
// int TEMP_SIZE = 38912;           // 1024 * 38
int TEMP_SIZE = 10240;      // modified to 10
int TEMP_START = 576784385; // FONTMAP_END
int TEMP_END = 576823297;   // TEMP_START + TEMP_SIZE

// Keyboard constants
int KEYBOARD_WAIT_TIME = 5;

// Control codes

int CTRL_CODE_BACKSPACE = 8; // 0x08
int CTRL_CODE_ENTER = 10;    // 0x0A

int CTRL_CODE_CTRL = 17;     // 0x11
int CTRL_CODE_ALT = 18;      // 0x12
int CTRL_CODE_SHIFT = 16;    // 0x10
int CTRL_CODE_CAPSLOCK = 20; // 0x14
int CTRL_CODE_BACKSPACE = 8; // 0x08

int ROW_CHAR_SIZE = 80;    // modified from 128
int COLUMN_CHAR_SIZE = 60; // modified from 64
int SCREEN_LOCK = 0;       // 0x00
int MUL_CONS = 9;

int max_com_len = 10; // max command length

// current path in the OS
char *path;

char *memory;
char **font_map;

int LINE = 0;   // current line (ROW)
int COLUMN = 0; // current column (COL)

int INT_END_POINT = 46; // 0x2E

int focus_mode = 0;
int focus_mode_col = 0;

// rand_gen.h
// rand_gen.c
int rand_lfsr;
int rand_bit;

int rand_engine = 44257; // 0xACE1u

char **board;
char player = 'X';
char computer = 'O';

// memory.c
int __load_char_as_bits(char c, char *out)
{
  int g, i;
  g = c;
  for (i = 0; i < 8; i++)
  {
    out[i] = (g & 1) + '0';
    g = g >> 1;
  }
  return 1;
}

char mread_char(int addr)
{
  return memory[addr];
}

char mwrite(char c, int addr)
{
  memory[addr] = c;
  return memory[addr];
}

// @brief initialize the memory. just create a memory file filled with zeroes
int minit()
{
  int i;
  for (i = 0; i < MEMORY_SIZE; i++)
  {
    memory[i] = 0;
  }
  return 1;
}

// @brief Initializes keyboard
int keyboard_init()
{
  int start, end, i;
  char c;

  start = IO_KEYBOARD_START;
  end = IO_KEYBOARD_START + IO_KEYBOARD_SIZE;

  c = '\0';

  for (i = start; i < end; i++)
  {

    mwrite(c, i);
  }
}

int keyboard_clear_input()
{
  char c;
  c = 0;
  mwrite(c, IO_KEYBOARD_START);
  return 0;
}

char keyboard_get_input()
{
  char input, f, c;

  input = 0;

  // printf("Keyboard start: %d\n", IO_KEYBOARD_START);

  for (; true;)
  {
    minit();
    f = mread_char(IO_KEYBOARD_START);
    // printf("Keyboard input: %c\n", f);
    if (f != 0)
    {
      input = f;
      c = 0;
      mwrite(c, IO_KEYBOARD_START);
      break;
    }
  }
  return input;
}

int keyboard_get_int()
{
  int ans;
  ans = 0;

  for (; true;)
  {

    char f, c;

    f = mread_char(IO_KEYBOARD_START);
    c = 0;

    mwrite(c, IO_KEYBOARD_START);

    if (f == INT_END_POINT)
    {
      break;
    }
    elif (f != 0)
    {
      if (f >= '0' && f <= '9')
      {
        ans = ans * 10 + (f - '0');
      }
      elif (f == 8) // '\b'
      {
        ans = ans / 10;
      }
      else
      {
        break;
      }
    }
  }

  return ans;
}

int convert_keyinput_to_string(char input, char *out)
{
  if (input == CTRL_CODE_ALT)
  {
    // ENTR
    out[0] = 'E';
    out[1] = 'N';
    out[2] = 'T';
    out[3] = 'R';
  }
  elif (input == CTRL_CODE_ALT)
  {
    // ALT
    out[0] = 'A';
    out[1] = 'L';
    out[2] = 'T';
    out[3] = '\0';
  }
  elif (input == CTRL_CODE_SHIFT)
  {
    // SHFT
    out[0] = 'S';
    out[1] = 'H';
    out[2] = 'F';
    out[3] = 'T';
  }
  else
  {
    out[0] = input;
    out[1] = '\0';
  }
  return 1;
}

char manipulate_input(char c)
{
  return c;
}

int isEscape(char input)
{
  return input == 27; // 0x1B
}

// **************************** UTILITY **************************
// @brief write_char writes a character included in fontmap at the last location
// @note takes care of word wrapping
// @returns 1 if not able to write else 0
int write_char(char c)
{
  // use write and read from mem.c
  if (SCREEN_LOCK == 0)
  {

    if (c == 10) // '\n'
    {
      COLUMN = 0;
      LINE = LINE + 8;
      if (LINE == 8 * COLUMN_CHAR_SIZE)
      {
        LINE = 0;
        COLUMN = 0;

        return 1;
      }

      return 0;
    }
    elif (c == 13) //'\r'
    {
      COLUMN = 0;
      return 0;
    }
    elif (c == 12) //'\f'
    {
      LINE = LINE + 8;
      if (LINE >= 8 * COLUMN_CHAR_SIZE)
      {
        LINE = 0;
        COLUMN = 0;
        return 1;
      }

      return 0;
    }
    elif (c == 9) // '\t'
    {
      COLUMN = COLUMN + 4;
      if (COLUMN >= ROW_CHAR_SIZE)
      {
        COLUMN = 0;
        LINE = LINE + 8;
        if (LINE >= 8 * COLUMN_CHAR_SIZE)
        {
          LINE = 0;
          COLUMN = 0;
          return 1;
        }
      }

      return 0;
    }
    elif (c == CTRL_CODE_BACKSPACE)
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
          LINE = LINE - 8;
        }
      }
      else
      {
        COLUMN--;
      }

      int A, i;
      char c;
      A = IO_DISPLAY_START + ROW_CHAR_SIZE * LINE + COLUMN;
      c = 0;
      for (i = 0; i < 8; i++)
      {
        mwrite(c, A + ROW_CHAR_SIZE * i);
      }

      return 0;
    }
    else
    {
      int A, i;
      char font[8];
      for (i = 0; i < 8; i++)
      {
        font[i] = font_map[c][i];
      }

      A = IO_DISPLAY_START + ROW_CHAR_SIZE * LINE + COLUMN; // location of the first character in the line
      for (i = 0; i < 8; i++)
      {
        mwrite(font[i], A + ROW_CHAR_SIZE * i);
      }

      COLUMN++;
      if (COLUMN == ROW_CHAR_SIZE)
      { // if the row is full
        COLUMN = 0;
        LINE = LINE + 8;
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
    {
      return 1;
    }
    if (col < 0 || col >= ROW_CHAR_SIZE)
    {
      return 1;
    }

    int A, i;
    char font[8];
    for (i = 0; i < 8; i++)
    {
      font[i] = font_map[c][i];
    }

    A = IO_DISPLAY_START + ROW_CHAR_SIZE * line + col; // location of the first character in the line
    for (i = 0; i < 8; i++)
    {
      mwrite(font[i], A + ROW_CHAR_SIZE * i);
    }

    return 0;
  }

  return 1;
}

// ******************************************************************************

int write_string(char *msg, int len)
{
  int g, i;
  if (SCREEN_LOCK == 0)
  {
    g = 0;
    for (i = 0; i < len; i++)
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
  int g, i;
  g = 0;
  for (i = 0; i < len; i++)
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
      line = line + 8;
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
    int count;
    count = 0;
    for (; a > 0;)
    {
      temp[count++] = (a % 10) + '0';
      a = a / 10;
    }
    int i;
    for (i = count - 1; i >= 0; i--)
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
  {
    return 1;
  }
  if (col < 0 || col >= ROW_CHAR_SIZE)
  {
    return 1;
  }

  LINE = line;
  COLUMN = col;

  return 0;
}

int get_cursor_pos(int *vals)
{
  vals[0] = LINE;
  vals[1] = COLUMN;
}

int write_string_at_col(char *msg, int len, int line, int col)
{
  if (SCREEN_LOCK == 0)
  {
    if (line >= 8 * COLUMN_CHAR_SIZE)
    {
      return 1;
    }
    if (col >= ROW_CHAR_SIZE || col < 0)
    {
      return 1;
    }

    int g, i;
    g = 0;
    for (i = 0; i < len; i++)
    {
      g = write_char_at(msg[i], line, col);
      if (g != 0)
      {
        return g;
      }

      line = line + 8;

      if (line == 8 * COLUMN_CHAR_SIZE)
      {
        line = 0;
        col = 0;

        return 1;
      }

      if (col == ROW_CHAR_SIZE)
      {
        col = 0;
        line = line + 8;
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
    {
      return 1;
    }

    int A, i;
    char c;

    A = IO_DISPLAY_START + ROW_CHAR_SIZE * line;
    c = 0;
    for (i = 0; i < ROW_CHAR_SIZE * 8; i++)
    {
      mwrite(c, A + i);
    }

    return 0;
  }

  return 1;
}

int write_zero_line()
{
  if (SCREEN_LOCK == 0)
  {
    int A, i;
    char c;

    A = IO_DISPLAY_START + ROW_CHAR_SIZE * LINE;
    c = 0;
    for (i = 0; i < ROW_CHAR_SIZE * 8; i++)
    {
      mwrite(c, A + i);
    }

    return 0;
  }

  return 1;
}

int write_face(char **font)
{
  if (SCREEN_LOCK == 0)
  {

    LINE = LINE + 8;
    COLUMN = 0;

    int A, i, j;
    A = IO_DISPLAY_START + LINE * ROW_CHAR_SIZE + COLUMN;

    for (i = 0; i < 128; i++)
    {
      for (j = 0; j < 16; j++)
      {
        mwrite(font[i][j], A + i * ROW_CHAR_SIZE + j);
      }
    }

    LINE = LINE + 128;
    COLUMN = 0;

    if (LINE >= 8 * COLUMN_CHAR_SIZE)
    {
      LINE = 0;
      COLUMN = 0;
    }
  }
  return 1;
}

// @brief Shifts the entire display map by one 1 unit upwards
int display_up()
{
  if (SCREEN_LOCK == 0)
  {
    int A, i, j, addr;
    char c;

    A = IO_DISPLAY_START;
    c = 0;
    for (j = 0; j < 8; j++)
    {
      for (addr = 0; addr < IO_DISPLAY_SIZE - ROW_CHAR_SIZE; addr++)
      {
        int temp;
        temp = mread_char(A + addr + ROW_CHAR_SIZE);
        // reverse temp
        int temp2;
        temp2 = 0;

        for (i = 0; i < 8; i++)
        {
          if ((temp >> i) & 1)
          {
            temp2 = temp2 | (1 << (7 - i));
          }
        }
        char temp3;
        temp3 = temp2;
        mwrite(temp3, A + addr);
      }
    }

    // clear the last line (A)
    for (i = 0; i < ROW_CHAR_SIZE * 8; i++)
    {
      mwrite(c, A + i);
    }

    // update the current line
    LINE = LINE - 8;
    if (LINE < 0)
    {
      LINE = 0;
    }

    return 0;
  }

  return 1;
}

// @brief Shifts the entire display map by one 1 unit downwards
int display_down()
{
  if (SCREEN_LOCK == 0)
  {
    int A, i, j, addr;
    char c;

    A = IO_DISPLAY_START;
    c = 0;
    for (j = 0; j < 8; j++)
    {
      for (addr = IO_DISPLAY_SIZE - ROW_CHAR_SIZE; addr >= 0; addr--)
      {
        int temp;
        temp = mread_char(A + addr);
        // reverse temp
        int temp2;
        temp2 = 0;

        for (i = 0; i < 8; i++)
        {
          if ((temp >> i) & 1)
          {
            temp2 = temp2 | (1 << (7 - i));
          }
        }

        char temp3;
        temp3 = temp2;
        mwrite(temp3, A + addr + ROW_CHAR_SIZE);
      }
    }

    // clear the first line (A)
    for (i = 0; i < ROW_CHAR_SIZE * 8; i++)
    {
      mwrite(c, A + i);
    }

    // update the current line
    LINE = LINE + 8;
    if (LINE >= 8 * COLUMN_CHAR_SIZE)
    {
      LINE = 8 * COLUMN_CHAR_SIZE - 1;
    }

    return 0;
  }

  return 1;
}

// reset the entire display
int clear_screen()
{
  if (SCREEN_LOCK == 0)
  {
    int A, i;
    char c;

    A = IO_DISPLAY_START + IO_DISPLAY_SIZE - 1;
    c = 0;
    for (i = A; i >= IO_DISPLAY_START; i--)
    {
      mwrite(c, i);
    }

    LINE = 0;
    COLUMN = 0;
  }
  return 0;
}

// save only the visible content of the display while switching to focus mode
int save_screen()
{
  int A, D, i;
  A = IO_DISPLAY_START;
  D = TEMP_START;

  for (i = 0; i < IO_DISPLAY_SIZE; i++)
  {
    char temp, temp1;
    int temp3;
    temp = mread_char(A + i);
    temp1 = D + i;

    temp3 = temp;
    mwrite(temp1, temp3);
  }
  return 1;
}

// retrieve the saved screen from the memory after exiting focus mode
int retrieve_screen()
{
  int A, D, i;
  A = IO_DISPLAY_START;
  D = TEMP_START;

  for (i = 0; i < IO_DISPLAY_SIZE; i++)
  {
    char temp, temp1;
    int temp3;
    temp = mread_char(D + i);
    temp1 = A + i;

    temp3 = temp;
    mwrite(temp1, temp3);
  }
  return 1;
}

// reset the entire display
int clear_screen()
{
  if (SCREEN_LOCK == 0)
  {
    int A, i;
    char c;

    A = IO_DISPLAY_START + IO_DISPLAY_SIZE - 1;
    c = 0;
    for (i = A; i >= IO_DISPLAY_START; i--)
    {
      mwrite(c, i);
    }

    LINE = 0;
    COLUMN = 0;
  }
  return 1;
}

// commands supported:
// :xx => not supported becoz we need directory structures

// 1. q --> exit focus mode
// 2. w --> save the file
// 3. wq --> save and exit
// 4. x --> save and exit
// 5. i --> insert mode
// 6. v --> visual mode
// 7. r --> read mode

// @brief: display info panel during focus mode (as seen in vim)
// enable vim like functionality
// store all the present content and show vim like functionality

int focus_info_panel()
{
  if (SCREEN_LOCK == 0)
  {
    save_screen();
    clear_screen();
    focus_mode = 1;
    focus_mode_col = 0;

    int command_mode;
    command_mode = 0;

    int visual_mode;
    visual_mode = 1;
    int edit_mode;
    edit_mode = 0;

    for (; true;)
    {
      char input;
      input = keyboard_get_input();
      input = manipulate_input(input);

      if (command_mode == 0)
      {
        if (isEscape(input))
        {
          command_mode = 1;
        }

        if (visual_mode == 1)
        {
          if (input == 'i')
          {
            visual_mode = 0;
            edit_mode = 1;
          }
        }
        elif (edit_mode == 1)
        {
          // non command mode and write to the display edit screen
          char content_to_write[4];
          convert_keyinput_to_string(input, content_to_write);
          int i;
          for (i = 0; i < 4; i++)
          {
            if (content_to_write[i] != '\0')
            {
              write_char(content_to_write[i]);
            }
          }
        }
      }
      // else
      // {
      // qf: exit focus mode
      // qc: exit command mode and return to visual mode
      // w: save the file
      // wq: save and exit focus mode
      // }
    }
  }

  return 1;
}

int set_seed(int seed)
{
  rand_engine = (((seed | rand_engine) * 7621) + 1) % 32768;
  rand_lfsr = rand_engine;
  return 1;
}

int rand()
{
  rand_bit = ((rand_lfsr >> 0) ^ (rand_lfsr >> 2) ^ (rand_lfsr >> 3) ^ (rand_lfsr >> 5)) & 1;
  rand_lfsr = (rand_lfsr >> 1) | (rand_bit << 15);

  return rand_lfsr % 100;
}

// 0 easy, 1 mid , 2 hard

int initializeBoard()
{
  int i, j;
  for (i = 0; i < 3; i++)
  {
    for (j = 0; j < 3; j++)
    {
      board[i][j] = 32; // ' '
    }
  }
  return 0;
}

int printBoard()
{
  int i, j;
  char c1, c2, c3, c4, c5;

  c1 = 32;  // ' '
  c4 = 124; // '|'
  c5 = 10;  // '/n'
  write_string("     1 2 3\n", 11);
  for (i = 0; i < 3; i++)
  {
    c3 = 49 + i;
    write_char(c1);
    write_char(c1);
    write_char(c1);
    write_char(c1);
    write_char(c3);
    for (j = 0; j < 3; j++)
    {
      write_char(board[i][j]);
      if (j < 2)
      {
        write_char(c4);
      }
    }
    write_char(c5);
    if (i < 2)
    {
      write_string("     -----\n", 11);
    }
  }
  write_char(c5);
  return 1;
}

int isBoardFull()
{
  int i, j;
  for (i = 0; i < 3; i++)
  {
    for (j = 0; j < 3; j++)
    {
      if (board[i][j] == 32) // ' '
      {
        return 0;
      }
    }
  }
  return 1;
}

int isGameOver(char player)
{
  int i;
  for (i = 0; i < 3; i++)
  {
    if (board[i][0] == player && board[i][1] == player && board[i][2] == player)
    {
      return 1;
    }
    if (board[0][i] == player && board[1][i] == player && board[2][i] == player)
    {
      return 1;
    }
  }
  if (board[0][0] == player && board[1][1] == player && board[2][2] == player)
  {
    return 1;
  }
  if (board[0][2] == player && board[1][1] == player && board[2][0] == player)
  {
    return 1;
  }
  return 0;
}

int makeMove(int row, int col, char player)
{
  if (row < 0 || row >= 3 || col < 0 || col >= 3 || board[row][col] != 32)
  {
    return 0;
  }
  board[row][col] = player;
  return 1;
}

int computerMove_easy()
{
  int row, col;

  row = rand() % 3;
  col = rand() % 3;
  for (; (makeMove(row, col, computer) == 0);)
  {
    row = rand() % 3;
    col = rand() % 3;
  }
  return 1;
}

int minimax(char **board, int depth, int isMaximizing)
{
  char result;
  if (isGameOver(computer) == 1)
  {
    result = 1;
  }
  elif (isGameOver(player) == 1)
  {
    result = -1;
  }
  elif (isBoardFull() == 1)
  {
    result = 0;
  }
  else
  {
    result = 2;
  }

  if (result != 2)
  {
    return result;
  }

  int bestScore;
  char currentPlayer;

  if (isMaximizing)
  {
    bestScore = -1000;
    currentPlayer = computer;
  }
  else
  {
    bestScore = 1000;
    currentPlayer = player;
  }

  int i, j;

  for (i = 0; i < 3; i++)
  {
    for (j = 0; j < 3; j++)
    {
      if (board[i][j] == 32) // ' '
      {
        board[i][j] = currentPlayer;
        int score;
        score = minimax(board, depth + 1, 1 - isMaximizing);
        board[i][j] = 32; // ' '
        if (isMaximizing == 1)
        {
          if (score > bestScore)
          {
            bestScore = score;
          }
        }
        else
        {
          if (score < bestScore)
          {
            bestScore = score;
          }
        }
      }
    }
  }

  return bestScore;
}

int computerMove_hard()
{
  int bestScore, bestMove[2], i, j;
  bestScore = -1000;
  bestMove[0] = -1;
  bestMove[1] = -1;

  for (i = 0; i < 3; i++)
  {
    for (j = 0; j < 3; j++)
    {
      if (board[i][j] == 32) // ' '
      {
        board[i][j] = computer;
        int score;
        score = minimax(board, 0, 0);
        board[i][j] = 32; //' '
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
  return 1;
}

int computerMove_med()
{
  int i, j;
  // Check for a win or block the player from winning
  for (i = 0; i < 3; i++)
  {
    for (j = 0; j < 3; j++)
    {
      if (board[i][j] == 32)
      {
        board[i][j] = computer;
        if (isGameOver(computer) == 1)
        {
          return 1; // Computer wins
        }
        board[i][j] = 32; // Undo the move
      }
    }
  }

  // Try to take the center if it's available
  if (board[1][1] == 32)
  {
    board[1][1] = computer;
    return 0; // No win yet
  }

  // Try to take a corner
  int corners[4][2];
  // {{0, 0}, {0, 2}, {2, 0}, {2, 2}};
  corners[0][0] = 0;
  corners[0][1] = 0;

  corners[1][0] = 0;
  corners[1][1] = 2;

  corners[2][0] = 2;
  corners[2][1] = 0;

  corners[3][0] = 2;
  corners[3][1] = 2;

  for (i = 0; i < 4; i++)
  {
    int row;
    row = corners[i][0];
    int col;
    col = corners[i][1];
    if (board[row][col] == 32)
    {
      board[row][col] = computer;
      return 0; // No win yet
    }
  }

  // Take any available edge
  int edges[4][2];
  // {{0, 1}, {1, 0}, {1, 2}, {2, 1}};
  edges[0][0] = 0;
  edges[0][1] = 1;

  edges[1][0] = 1;
  edges[1][1] = 0;

  edges[2][0] = 1;
  edges[2][1] = 2;

  edges[3][0] = 2;
  edges[3][1] = 1;

  for (i = 0; i < 4; i++)
  {
    int row;
    row = edges[i][0];
    int col;
    col = edges[i][1];
    if (board[row][col] == 32)
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

  for (; true;)
  {
    clear_screen();
    write_string("Welcome to Tic-Tac-Toe!\n\n", 25);

    if (game_diff == 0)
    {
      write_string("Easy Mode\n\n", 11);
    }
    elif (game_diff == 1)
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

    row = row - 48;
    col = col - 48;

    row--; // Adjust for 0-based indexing
    col--;

    if (makeMove(row, col, player) == 0)
    {
      write_string("Invalid move! Try again.\n", 25);
      continue;
    }

    if (isGameOver(player) == 1)
    {
      printBoard();
      write_string("Congratulations! You win!\n", 26);
      break;
    }

    if (isBoardFull() == 1)
    {
      printBoard();
      write_string("It's a draw!\n", 13);
      break;
    }

    if (game_diff == 0)
    {
      computerMove_easy();
    }
    elif (game_diff == 1)
    {
      computerMove_med();
    }
    else
    {
      computerMove_hard();
    }

    if (isGameOver(computer) == 1)
    {
      printBoard();
      write_string("Computer wins! You lose.\n", 25);
      break;
    }

    if (isBoardFull() == 1)
    {
      printBoard();
      write_string("It's a draw!\n", 13);
      break;
    }
  }

  return 0;
}

int os_start()
{
  // initialize the kernel
  minit();
  return 1;
}

int display_1()
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
  return 1;
}

int initial_display()
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
  return 1;
}

int int_input()
{
  clear_screen();
  keyboard_clear_input();

  write_string("Enter an integer: \n", 19);
  int input;
  char c;

  c = 10; // '\n'
  input = keyboard_get_int();
  write_string("The integer is: ", 16);
  write_int(input);
  write_char(c);
}

// function to capture data from memory and update the display
int terminal()
{
  // init_memory();
  clear_screen();
  initial_display();
  int isn;
  isn = 0;

  for (; true;)
  {
    // get input from keyboard
    char input;
    input = keyboard_get_input();

    if (input == 'c')
    {
      clear_screen();
      isn = 0;
    }
    elif (input == 'd')
    {
      display_1();
      isn = 0;
    }
    elif (input == 'q')
    {
      clear_screen();
      write_string("Exiting Terminal\n", 17);
      break;
    }
    elif (input == 'e')
    {
      tic_tac_toe(0);
      isn = 0;
    }
    elif (input == 'm')
    {
      tic_tac_toe(1);
      isn = 0;
    }
    elif (input == 'h')
    {
      tic_tac_toe(2);
      isn = 0;
    }
    elif (input == 'i')
    {
      int_input();
    }
    elif (input == 't')
    {
      clear_screen();
      initial_display();
      isn = 0;
    }
    elif (input == 'r')
    {
      int seed, count, i;
      char c1, c2, c3;

      seed = 0;
      count = 0;
      c1 = 10; // '\n'
      c2 = 32; // ' '
      c3 = 58; // ':'

      write_string("Enter the seed for the random number generator: \n", 49);
      seed = keyboard_get_int();
      write_string("Enter the count of random numbers you want: \n", 45);
      count = keyboard_get_int();

      write_string("The random numbers are: \n\n", 26);
      set_seed(seed);

      for (i = 0; i < count; i++)
      {
        int random;
        random = rand();
        write_char(c2);
        write_int(i + 1);
        write_char(c2);
        write_char(c3);
        write_char(c2);
        write_int(random);
        write_char(c1);
      }
    }
    else
    {
      if (isn == 0)
      {
        isn = 1;
        write_string("\nCharacter printing\n", 20);
      }
      write_char(input);
    }
  }
  return 1;
}

int display_test()
{
  char c1, c2, c3, c4;
  c1 = 10; // '\n'
  c2 = 13; // '\r'
  c3 = 9;  // '\t'
  c4 = CTRL_CODE_BACKSPACE;

  clear_screen();
  write_string("Team RISC V1\n\n\n", 16);
  write_string_at("Welcome to Flex OS\n\n", 20, 24, 0);

  set_cursor_pos(32, 0);
  write_char(c1);
  write_string("Namo 2024!\n\n", 12);
  write_string("India lifts the World Cup after 28 years!", 42);

  int val[2];

  write_char(c1);
  // write_face(font_2);

  get_cursor_pos(val);

  int line, col;
  line = val[0];
  col = val[1];

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
  write_char(c2);
  write_zero_line();
  write_string("CS 342", 6);
  write_char(c4);

  write_char(c3);
  write_string("After Tab", 9);
  return 1;
}

int main()
{
  int i;

  path = malloc(sizeof(char) * 128);
  memory = malloc(sizeof(char) * MEMORY_SIZE);
  font_map = malloc(sizeof(*) * 128);
  for (i = 0; i < 128; i++)
  {
    font_map[i] = malloc(sizeof(char) * 8);
  }

  board = malloc(sizeof(*) * 3);
  for (i = 0; i < 3; i++)
  {
    board[i] = malloc(sizeof(char) * 3);
  }

  // U+0000
  font_map[0][0] = 0;
  font_map[0][1] = 0;
  font_map[0][2] = 0;
  font_map[0][3] = 0;
  font_map[0][4] = 0;
  font_map[0][5] = 0;
  font_map[0][6] = 0;
  font_map[0][7] = 0;

  // U+0001
  font_map[1][0] = 0;
  font_map[1][1] = 0;
  font_map[1][2] = 0;
  font_map[1][3] = 0;
  font_map[1][4] = 0;
  font_map[1][5] = 0;
  font_map[1][6] = 0;
  font_map[1][7] = 0;

  // U+0002
  font_map[2][0] = 0;
  font_map[2][1] = 0;
  font_map[2][2] = 0;
  font_map[2][3] = 0;
  font_map[2][4] = 0;
  font_map[2][5] = 0;
  font_map[2][6] = 0;
  font_map[2][7] = 0;

  // U+0003
  font_map[3][0] = 0;
  font_map[3][1] = 0;
  font_map[3][2] = 0;
  font_map[3][3] = 0;
  font_map[3][4] = 0;
  font_map[3][5] = 0;
  font_map[3][6] = 0;
  font_map[3][7] = 0;

  // U+0004
  font_map[4][0] = 0;
  font_map[4][1] = 0;
  font_map[4][2] = 0;
  font_map[4][3] = 0;
  font_map[4][4] = 0;
  font_map[4][5] = 0;
  font_map[4][6] = 0;
  font_map[4][7] = 0;

  // U+0005
  font_map[5][0] = 0;
  font_map[5][1] = 0;
  font_map[5][2] = 0;
  font_map[5][3] = 0;
  font_map[5][4] = 0;
  font_map[5][5] = 0;
  font_map[5][6] = 0;
  font_map[5][7] = 0;

  // U+0006
  font_map[6][0] = 0;
  font_map[6][1] = 0;
  font_map[6][2] = 0;
  font_map[6][3] = 0;
  font_map[6][4] = 0;
  font_map[6][5] = 0;
  font_map[6][6] = 0;
  font_map[6][7] = 0;

  // U+0007
  font_map[7][0] = 0;
  font_map[7][1] = 0;
  font_map[7][2] = 0;
  font_map[7][3] = 0;
  font_map[7][4] = 0;
  font_map[7][5] = 0;
  font_map[7][6] = 0;
  font_map[7][7] = 0;

  // U+0008
  font_map[8][0] = 0;
  font_map[8][1] = 0;
  font_map[8][2] = 0;
  font_map[8][3] = 0;
  font_map[8][4] = 0;
  font_map[8][5] = 0;
  font_map[8][6] = 0;
  font_map[8][7] = 0;

  // U+0009
  font_map[9][0] = 0;
  font_map[9][1] = 0;
  font_map[9][2] = 0;
  font_map[9][3] = 0;
  font_map[9][4] = 0;
  font_map[9][5] = 0;
  font_map[9][6] = 0;
  font_map[9][7] = 0;

  // U+000A
  font_map[10][0] = 0;
  font_map[10][1] = 0;
  font_map[10][2] = 0;
  font_map[10][3] = 0;
  font_map[10][4] = 0;
  font_map[10][5] = 0;
  font_map[10][6] = 0;
  font_map[10][7] = 0;

  // U+000B
  font_map[11][0] = 0;
  font_map[11][1] = 0;
  font_map[11][2] = 0;
  font_map[11][3] = 0;
  font_map[11][4] = 0;
  font_map[11][5] = 0;
  font_map[11][6] = 0;
  font_map[11][7] = 0;

  // U+000C
  font_map[12][0] = 0;
  font_map[12][1] = 0;
  font_map[12][2] = 0;
  font_map[12][3] = 0;
  font_map[12][4] = 0;
  font_map[12][5] = 0;
  font_map[12][6] = 0;
  font_map[12][7] = 0;

  // U+000D
  font_map[13][0] = 0;
  font_map[13][1] = 0;
  font_map[13][2] = 0;
  font_map[13][3] = 0;
  font_map[13][4] = 0;
  font_map[13][5] = 0;
  font_map[13][6] = 0;
  font_map[13][7] = 0;

  // U+000E
  font_map[14][0] = 0;
  font_map[14][1] = 0;
  font_map[14][2] = 0;
  font_map[14][3] = 0;
  font_map[14][4] = 0;
  font_map[14][5] = 0;
  font_map[14][6] = 0;
  font_map[14][7] = 0;

  // U+000F
  font_map[15][0] = 0;
  font_map[15][1] = 0;
  font_map[15][2] = 0;
  font_map[15][3] = 0;
  font_map[15][4] = 0;
  font_map[15][5] = 0;
  font_map[15][6] = 0;
  font_map[15][7] = 0;

  // U+0010
  font_map[16][0] = 0;
  font_map[16][1] = 0;
  font_map[16][2] = 0;
  font_map[16][3] = 0;
  font_map[16][4] = 0;
  font_map[16][5] = 0;
  font_map[16][6] = 0;
  font_map[16][7] = 0;

  // U+0011
  font_map[17][0] = 0;
  font_map[17][1] = 0;
  font_map[17][2] = 0;
  font_map[17][3] = 0;
  font_map[17][4] = 0;
  font_map[17][5] = 0;
  font_map[17][6] = 0;
  font_map[17][7] = 0;

  // U+0012
  font_map[18][0] = 0;
  font_map[18][1] = 0;
  font_map[18][2] = 0;
  font_map[18][3] = 0;
  font_map[18][4] = 0;
  font_map[18][5] = 0;
  font_map[18][6] = 0;
  font_map[18][7] = 0;

  // U+0013
  font_map[19][0] = 0;
  font_map[19][1] = 0;
  font_map[19][2] = 0;
  font_map[19][3] = 0;
  font_map[19][4] = 0;
  font_map[19][5] = 0;
  font_map[19][6] = 0;
  font_map[19][7] = 0;

  // U+0014
  font_map[20][0] = 0;
  font_map[20][1] = 0;
  font_map[20][2] = 0;
  font_map[20][3] = 0;
  font_map[20][4] = 0;
  font_map[20][5] = 0;
  font_map[20][6] = 0;
  font_map[20][7] = 0;

  // U+0015
  font_map[21][0] = 0;
  font_map[21][1] = 0;
  font_map[21][2] = 0;
  font_map[21][3] = 0;
  font_map[21][4] = 0;
  font_map[21][5] = 0;
  font_map[21][6] = 0;
  font_map[21][7] = 0;

  // U+0016
  font_map[22][0] = 0;
  font_map[22][1] = 0;
  font_map[22][2] = 0;
  font_map[22][3] = 0;
  font_map[22][4] = 0;
  font_map[22][5] = 0;
  font_map[22][6] = 0;
  font_map[22][7] = 0;

  // U+0017
  font_map[23][0] = 0;
  font_map[23][1] = 0;
  font_map[23][2] = 0;
  font_map[23][3] = 0;
  font_map[23][4] = 0;
  font_map[23][5] = 0;
  font_map[23][6] = 0;
  font_map[23][7] = 0;

  // U+0018
  font_map[24][0] = 0;
  font_map[24][1] = 0;
  font_map[24][2] = 0;
  font_map[24][3] = 0;
  font_map[24][4] = 0;
  font_map[24][5] = 0;
  font_map[24][6] = 0;
  font_map[24][7] = 0;

  // U+0019
  font_map[25][0] = 0;
  font_map[25][1] = 0;
  font_map[25][2] = 0;
  font_map[25][3] = 0;
  font_map[25][4] = 0;
  font_map[25][5] = 0;
  font_map[25][6] = 0;
  font_map[25][7] = 0;

  // U+001A
  font_map[26][0] = 0;
  font_map[26][1] = 0;
  font_map[26][2] = 0;
  font_map[26][3] = 0;
  font_map[26][4] = 0;
  font_map[26][5] = 0;
  font_map[26][6] = 0;
  font_map[26][7] = 0;

  // U+001B
  font_map[27][0] = 0;
  font_map[27][1] = 0;
  font_map[27][2] = 0;
  font_map[27][3] = 0;
  font_map[27][4] = 0;
  font_map[27][5] = 0;
  font_map[27][6] = 0;
  font_map[27][7] = 0;

  // U+001C
  font_map[28][0] = 0;
  font_map[28][1] = 0;
  font_map[28][2] = 0;
  font_map[28][3] = 0;
  font_map[28][4] = 0;
  font_map[28][5] = 0;
  font_map[28][6] = 0;
  font_map[28][7] = 0;

  // U+001D
  font_map[29][0] = 0;
  font_map[29][1] = 0;
  font_map[29][2] = 0;
  font_map[29][3] = 0;
  font_map[29][4] = 0;
  font_map[29][5] = 0;
  font_map[29][6] = 0;
  font_map[29][7] = 0;

  // U+001E
  font_map[30][0] = 0;
  font_map[30][1] = 0;
  font_map[30][2] = 0;
  font_map[30][3] = 0;
  font_map[30][4] = 0;
  font_map[30][5] = 0;
  font_map[30][6] = 0;
  font_map[30][7] = 0;

  // U+001F
  font_map[31][0] = 0;
  font_map[31][1] = 0;
  font_map[31][2] = 0;
  font_map[31][3] = 0;
  font_map[31][4] = 0;
  font_map[31][5] = 0;
  font_map[31][6] = 0;
  font_map[31][7] = 0;

  // U+0020 ( )
  font_map[32][0] = 0;
  font_map[32][1] = 0;
  font_map[32][2] = 0;
  font_map[32][3] = 0;
  font_map[32][4] = 0;
  font_map[32][5] = 0;
  font_map[32][6] = 0;
  font_map[32][7] = 0;

  // U+0021 (!)
  font_map[33][0] = 24;
  font_map[33][1] = 60;
  font_map[33][2] = 60;
  font_map[33][3] = 24;
  font_map[33][4] = 24;
  font_map[33][5] = 0;
  font_map[33][6] = 24;
  font_map[33][7] = 0;

  // U+0022 (")
  font_map[34][0] = 54;
  font_map[34][1] = 54;
  font_map[34][2] = 0;
  font_map[34][3] = 0;
  font_map[34][4] = 0;
  font_map[34][5] = 0;
  font_map[34][6] = 0;
  font_map[34][7] = 0;

  // U+0023 (#)
  font_map[35][0] = 54;
  font_map[35][1] = 54;
  font_map[35][2] = 127;
  font_map[35][3] = 54;
  font_map[35][4] = 127;
  font_map[35][5] = 54;
  font_map[35][6] = 54;
  font_map[35][7] = 0;

  // U+0024 ($)
  font_map[36][0] = 12;
  font_map[36][1] = 62;
  font_map[36][2] = 3;
  font_map[36][3] = 30;
  font_map[36][4] = 48;
  font_map[36][5] = 31;
  font_map[36][6] = 12;
  font_map[36][7] = 0;

  // U+0025 (%)
  font_map[37][0] = 0;
  font_map[37][1] = 99;
  font_map[37][2] = 51;
  font_map[37][3] = 24;
  font_map[37][4] = 12;
  font_map[37][5] = 102;
  font_map[37][6] = 99;
  font_map[37][7] = 0;

  // U+0026 (&)
  font_map[38][0] = 28;
  font_map[38][1] = 54;
  font_map[38][2] = 28;
  font_map[38][3] = 110;
  font_map[38][4] = 59;
  font_map[38][5] = 51;
  font_map[38][6] = 110;
  font_map[38][7] = 0;

  // U+0027 (')
  font_map[39][0] = 6;
  font_map[39][1] = 6;
  font_map[39][2] = 3;
  font_map[39][3] = 0;
  font_map[39][4] = 0;
  font_map[39][5] = 0;
  font_map[39][6] = 0;
  font_map[39][7] = 0;

  // U+0028 (()
  font_map[40][0] = 24;
  font_map[40][1] = 12;
  font_map[40][2] = 6;
  font_map[40][3] = 6;
  font_map[40][4] = 6;
  font_map[40][5] = 12;
  font_map[40][6] = 24;
  font_map[40][7] = 0;

  // U+0029 ())
  font_map[41][0] = 6;
  font_map[41][1] = 12;
  font_map[41][2] = 24;
  font_map[41][3] = 24;
  font_map[41][4] = 24;
  font_map[41][5] = 12;
  font_map[41][6] = 6;
  font_map[41][7] = 0;

  // U+002A (*)
  font_map[42][0] = 0;
  font_map[42][1] = 102;
  font_map[42][2] = 60;
  font_map[42][3] = 255;
  font_map[42][4] = 60;
  font_map[42][5] = 102;
  font_map[42][6] = 0;
  font_map[42][7] = 0;

  // U+002B (+)
  font_map[43][0] = 0;
  font_map[43][1] = 12;
  font_map[43][2] = 12;
  font_map[43][3] = 63;
  font_map[43][4] = 12;
  font_map[43][5] = 12;
  font_map[43][6] = 0;
  font_map[43][7] = 0;

  // U+002C (,)
  font_map[44][0] = 0;
  font_map[44][1] = 0;
  font_map[44][2] = 0;
  font_map[44][3] = 0;
  font_map[44][4] = 0;
  font_map[44][5] = 12;
  font_map[44][6] = 12;
  font_map[44][7] = 6;

  // U+002D (-)
  font_map[45][0] = 0;
  font_map[45][1] = 0;
  font_map[45][2] = 0;
  font_map[45][3] = 63;
  font_map[45][4] = 0;
  font_map[45][5] = 0;
  font_map[45][6] = 0;
  font_map[45][7] = 0;

  // U+002E (.)
  font_map[46][0] = 0;
  font_map[46][1] = 0;
  font_map[46][2] = 0;
  font_map[46][3] = 0;
  font_map[46][4] = 0;
  font_map[46][5] = 12;
  font_map[46][6] = 12;
  font_map[46][7] = 0;

  // U+002F (/)
  font_map[47][0] = 96;
  font_map[47][1] = 48;
  font_map[47][2] = 24;
  font_map[47][3] = 12;
  font_map[47][4] = 6;
  font_map[47][5] = 3;
  font_map[47][6] = 1;
  font_map[47][7] = 0;

  // U+0030 (0)
  font_map[48][0] = 62;
  font_map[48][1] = 99;
  font_map[48][2] = 115;
  font_map[48][3] = 123;
  font_map[48][4] = 111;
  font_map[48][5] = 103;
  font_map[48][6] = 62;
  font_map[48][7] = 0;

  // U+0031 (1)
  font_map[49][0] = 12;
  font_map[49][1] = 14;
  font_map[49][2] = 12;
  font_map[49][3] = 12;
  font_map[49][4] = 12;
  font_map[49][5] = 12;
  font_map[49][6] = 63;
  font_map[49][7] = 0;

  // U+0032 (2)
  font_map[50][0] = 30;
  font_map[50][1] = 51;
  font_map[50][2] = 48;
  font_map[50][3] = 28;
  font_map[50][4] = 6;
  font_map[50][5] = 51;
  font_map[50][6] = 63;
  font_map[50][7] = 0;

  // U+0033 (3)
  font_map[51][0] = 30;
  font_map[51][1] = 51;
  font_map[51][2] = 48;
  font_map[51][3] = 28;
  font_map[51][4] = 48;
  font_map[51][5] = 51;
  font_map[51][6] = 30;
  font_map[51][7] = 0;

  // U+0034 (4)
  font_map[52][0] = 56;
  font_map[52][1] = 60;
  font_map[52][2] = 54;
  font_map[52][3] = 51;
  font_map[52][4] = 127;
  font_map[52][5] = 48;
  font_map[52][6] = 120;
  font_map[52][7] = 0;

  // U+0035 (5)
  font_map[53][0] = 63;
  font_map[53][1] = 3;
  font_map[53][2] = 31;
  font_map[53][3] = 48;
  font_map[53][4] = 48;
  font_map[53][5] = 51;
  font_map[53][6] = 30;
  font_map[53][7] = 0;

  // U+0036 (6)
  font_map[54][0] = 28;
  font_map[54][1] = 6;
  font_map[54][2] = 3;
  font_map[54][3] = 31;
  font_map[54][4] = 51;
  font_map[54][5] = 51;
  font_map[54][6] = 30;
  font_map[54][7] = 0;

  // U+0037 (7)
  font_map[55][0] = 63;
  font_map[55][1] = 51;
  font_map[55][2] = 48;
  font_map[55][3] = 24;
  font_map[55][4] = 12;
  font_map[55][5] = 12;
  font_map[55][6] = 12;
  font_map[55][7] = 0;

  // U+0038 (8)
  font_map[56][0] = 30;
  font_map[56][1] = 51;
  font_map[56][2] = 51;
  font_map[56][3] = 30;
  font_map[56][4] = 51;
  font_map[56][5] = 51;
  font_map[56][6] = 30;
  font_map[56][7] = 0;

  // U+0039 (9)
  font_map[57][0] = 30;
  font_map[57][1] = 51;
  font_map[57][2] = 51;
  font_map[57][3] = 62;
  font_map[57][4] = 48;
  font_map[57][5] = 24;
  font_map[57][6] = 14;
  font_map[57][7] = 0;

  // U+003A (:)
  font_map[58][0] = 0;
  font_map[58][1] = 12;
  font_map[58][2] = 12;
  font_map[58][3] = 0;
  font_map[58][4] = 0;
  font_map[58][5] = 12;
  font_map[58][6] = 12;
  font_map[58][7] = 0;

  // U+003B (;)
  font_map[59][0] = 0;
  font_map[59][1] = 12;
  font_map[59][2] = 12;
  font_map[59][3] = 0;
  font_map[59][4] = 0;
  font_map[59][5] = 12;
  font_map[59][6] = 12;
  font_map[59][7] = 6;

  // U+003C (<)
  font_map[60][0] = 24;
  font_map[60][1] = 12;
  font_map[60][2] = 6;
  font_map[60][3] = 3;
  font_map[60][4] = 6;
  font_map[60][5] = 12;
  font_map[60][6] = 24;
  font_map[60][7] = 0;

  // U+003D (=)
  font_map[61][0] = 0;
  font_map[61][1] = 0;
  font_map[61][2] = 63;
  font_map[61][3] = 0;
  font_map[61][4] = 0;
  font_map[61][5] = 63;
  font_map[61][6] = 0;
  font_map[61][7] = 0;

  // U+003E (>)
  font_map[62][0] = 6;
  font_map[62][1] = 12;
  font_map[62][2] = 24;
  font_map[62][3] = 48;
  font_map[62][4] = 24;
  font_map[62][5] = 12;
  font_map[62][6] = 6;
  font_map[62][7] = 0;

  // U+003F (?)
  font_map[63][0] = 30;
  font_map[63][1] = 51;
  font_map[63][2] = 48;
  font_map[63][3] = 24;
  font_map[63][4] = 12;
  font_map[63][5] = 0;
  font_map[63][6] = 12;
  font_map[63][7] = 0;

  // U+0040 (@)
  font_map[64][0] = 62;
  font_map[64][1] = 99;
  font_map[64][2] = 123;
  font_map[64][3] = 123;
  font_map[64][4] = 123;
  font_map[64][5] = 3;
  font_map[64][6] = 30;
  font_map[64][7] = 0;

  // U+0041 (A)
  font_map[65][0] = 12;
  font_map[65][1] = 30;
  font_map[65][2] = 51;
  font_map[65][3] = 51;
  font_map[65][4] = 63;
  font_map[65][5] = 51;
  font_map[65][6] = 51;
  font_map[65][7] = 0;

  // U+0042 (B)
  font_map[66][0] = 63;
  font_map[66][1] = 102;
  font_map[66][2] = 102;
  font_map[66][3] = 62;
  font_map[66][4] = 102;
  font_map[66][5] = 102;
  font_map[66][6] = 63;
  font_map[66][7] = 0;

  // U+0043 (C)
  font_map[67][0] = 60;
  font_map[67][1] = 102;
  font_map[67][2] = 3;
  font_map[67][3] = 3;
  font_map[67][4] = 3;
  font_map[67][5] = 102;
  font_map[67][6] = 60;
  font_map[67][7] = 0;

  // U+0044 (D)
  font_map[68][0] = 31;
  font_map[68][1] = 54;
  font_map[68][2] = 102;
  font_map[68][3] = 102;
  font_map[68][4] = 102;
  font_map[68][5] = 54;
  font_map[68][6] = 31;
  font_map[68][7] = 0;

  // U+0045 (E)
  font_map[69][0] = 127;
  font_map[69][1] = 70;
  font_map[69][2] = 22;
  font_map[69][3] = 30;
  font_map[69][4] = 22;
  font_map[69][5] = 70;
  font_map[69][6] = 127;
  font_map[69][7] = 0;

  // U+0046 (F)
  font_map[70][0] = 127;
  font_map[70][1] = 70;
  font_map[70][2] = 22;
  font_map[70][3] = 30;
  font_map[70][4] = 22;
  font_map[70][5] = 6;
  font_map[70][6] = 15;
  font_map[70][7] = 0;

  // U+0047 (G)
  font_map[71][0] = 60;
  font_map[71][1] = 102;
  font_map[71][2] = 3;
  font_map[71][3] = 3;
  font_map[71][4] = 115;
  font_map[71][5] = 102;
  font_map[71][6] = 124;
  font_map[71][7] = 0;

  // U+0048 (H)
  font_map[72][0] = 51;
  font_map[72][1] = 51;
  font_map[72][2] = 51;
  font_map[72][3] = 63;
  font_map[72][4] = 51;
  font_map[72][5] = 51;
  font_map[72][6] = 51;
  font_map[72][7] = 0;

  // U+0049 (I)
  font_map[73][0] = 30;
  font_map[73][1] = 12;
  font_map[73][2] = 12;
  font_map[73][3] = 12;
  font_map[73][4] = 12;
  font_map[73][5] = 12;
  font_map[73][6] = 30;
  font_map[73][7] = 0;

  // U+004A (J)
  font_map[74][0] = 120;
  font_map[74][1] = 48;
  font_map[74][2] = 48;
  font_map[74][3] = 48;
  font_map[74][4] = 51;
  font_map[74][5] = 51;
  font_map[74][6] = 30;
  font_map[74][7] = 0;

  // U+004B (K)
  font_map[75][0] = 103;
  font_map[75][1] = 102;
  font_map[75][2] = 54;
  font_map[75][3] = 30;
  font_map[75][4] = 54;
  font_map[75][5] = 102;
  font_map[75][6] = 103;
  font_map[75][7] = 0;

  // U+004C (L)
  font_map[76][0] = 15;
  font_map[76][1] = 6;
  font_map[76][2] = 6;
  font_map[76][3] = 6;
  font_map[76][4] = 70;
  font_map[76][5] = 102;
  font_map[76][6] = 127;
  font_map[76][7] = 0;

  // U+004D (M)
  font_map[77][0] = 99;
  font_map[77][1] = 119;
  font_map[77][2] = 127;
  font_map[77][3] = 127;
  font_map[77][4] = 107;
  font_map[77][5] = 99;
  font_map[77][6] = 99;
  font_map[77][7] = 0;

  // U+004E (N)
  font_map[78][0] = 99;
  font_map[78][1] = 103;
  font_map[78][2] = 111;
  font_map[78][3] = 123;
  font_map[78][4] = 115;
  font_map[78][5] = 99;
  font_map[78][6] = 99;
  font_map[78][7] = 0;

  // U+004F (O)
  font_map[79][0] = 28;
  font_map[79][1] = 54;
  font_map[79][2] = 99;
  font_map[79][3] = 99;
  font_map[79][4] = 99;
  font_map[79][5] = 54;
  font_map[79][6] = 28;
  font_map[79][7] = 0;

  // U+0050 (P)
  font_map[80][0] = 63;
  font_map[80][1] = 102;
  font_map[80][2] = 102;
  font_map[80][3] = 62;
  font_map[80][4] = 6;
  font_map[80][5] = 6;
  font_map[80][6] = 15;
  font_map[80][7] = 0;

  // U+0051 (Q)
  font_map[81][0] = 30;
  font_map[81][1] = 51;
  font_map[81][2] = 51;
  font_map[81][3] = 51;
  font_map[81][4] = 59;
  font_map[81][5] = 30;
  font_map[81][6] = 56;
  font_map[81][7] = 0;

  // U+0052 (R)
  font_map[82][0] = 63;
  font_map[82][1] = 102;
  font_map[82][2] = 102;
  font_map[82][3] = 62;
  font_map[82][4] = 54;
  font_map[82][5] = 102;
  font_map[82][6] = 103;
  font_map[82][7] = 0;

  // U+0053 (S)
  font_map[83][0] = 30;
  font_map[83][1] = 51;
  font_map[83][2] = 7;
  font_map[83][3] = 14;
  font_map[83][4] = 56;
  font_map[83][5] = 51;
  font_map[83][6] = 30;
  font_map[83][7] = 0;

  // U+0054 (T)
  font_map[84][0] = 63;
  font_map[84][1] = 45;
  font_map[84][2] = 12;
  font_map[84][3] = 12;
  font_map[84][4] = 12;
  font_map[84][5] = 12;
  font_map[84][6] = 30;
  font_map[84][7] = 0;

  // U+0055 (U)
  font_map[85][0] = 51;
  font_map[85][1] = 51;
  font_map[85][2] = 51;
  font_map[85][3] = 51;
  font_map[85][4] = 51;
  font_map[85][5] = 51;
  font_map[85][6] = 63;
  font_map[85][7] = 0;

  // U+0056 (V)
  font_map[86][0] = 51;
  font_map[86][1] = 51;
  font_map[86][2] = 51;
  font_map[86][3] = 51;
  font_map[86][4] = 51;
  font_map[86][5] = 30;
  font_map[86][6] = 12;
  font_map[86][7] = 0;

  // U+0057 (W)
  font_map[87][0] = 99;
  font_map[87][1] = 99;
  font_map[87][2] = 99;
  font_map[87][3] = 107;
  font_map[87][4] = 127;
  font_map[87][5] = 119;
  font_map[87][6] = 99;
  font_map[87][7] = 0;

  // U+0058 (X)
  font_map[88][0] = 99;
  font_map[88][1] = 99;
  font_map[88][2] = 54;
  font_map[88][3] = 28;
  font_map[88][4] = 28;
  font_map[88][5] = 54;
  font_map[88][6] = 99;
  font_map[88][7] = 0;

  // U+0059 (Y)
  font_map[89][0] = 51;
  font_map[89][1] = 51;
  font_map[89][2] = 51;
  font_map[89][3] = 30;
  font_map[89][4] = 12;
  font_map[89][5] = 12;
  font_map[89][6] = 30;
  font_map[89][7] = 0;

  // U+005A (Z)
  font_map[90][0] = 127;
  font_map[90][1] = 99;
  font_map[90][2] = 49;
  font_map[90][3] = 24;
  font_map[90][4] = 76;
  font_map[90][5] = 102;
  font_map[90][6] = 127;
  font_map[90][7] = 0;

  // U+005B ([)
  font_map[91][0] = 30;
  font_map[91][1] = 6;
  font_map[91][2] = 6;
  font_map[91][3] = 6;
  font_map[91][4] = 6;
  font_map[91][5] = 6;
  font_map[91][6] = 30;
  font_map[91][7] = 0;

  // U+005C (\)
  font_map[92][0] = 3;
  font_map[92][1] = 6;
  font_map[92][2] = 12;
  font_map[92][3] = 24;
  font_map[92][4] = 48;
  font_map[92][5] = 96;
  font_map[92][6] = 64;
  font_map[92][7] = 0;

  // U+005D (])
  font_map[93][0] = 30;
  font_map[93][1] = 24;
  font_map[93][2] = 24;
  font_map[93][3] = 24;
  font_map[93][4] = 24;
  font_map[93][5] = 24;
  font_map[93][6] = 30;
  font_map[93][7] = 0;

  // U+005E (^)
  font_map[94][0] = 8;
  font_map[94][1] = 28;
  font_map[94][2] = 54;
  font_map[94][3] = 99;
  font_map[94][4] = 0;
  font_map[94][5] = 0;
  font_map[94][6] = 0;
  font_map[94][7] = 0;

  // U+005F (_)
  font_map[95][0] = 0;
  font_map[95][1] = 0;
  font_map[95][2] = 0;
  font_map[95][3] = 0;
  font_map[95][4] = 0;
  font_map[95][5] = 0;
  font_map[95][6] = 0;
  font_map[95][7] = 255;

  // U+0060 (`)
  font_map[96][0] = 12;
  font_map[96][1] = 12;
  font_map[96][2] = 24;
  font_map[96][3] = 0;
  font_map[96][4] = 0;
  font_map[96][5] = 0;
  font_map[96][6] = 0;
  font_map[96][7] = 0;

  // U+0061 (a)
  font_map[97][0] = 0;
  font_map[97][1] = 0;
  font_map[97][2] = 30;
  font_map[97][3] = 48;
  font_map[97][4] = 62;
  font_map[97][5] = 51;
  font_map[97][6] = 110;
  font_map[97][7] = 0;

  // U+0062 (b)
  font_map[98][0] = 7;
  font_map[98][1] = 6;
  font_map[98][2] = 6;
  font_map[98][3] = 62;
  font_map[98][4] = 102;
  font_map[98][5] = 102;
  font_map[98][6] = 59;
  font_map[98][7] = 0;

  // U+0063 (c)
  font_map[99][0] = 0;
  font_map[99][1] = 0;
  font_map[99][2] = 30;
  font_map[99][3] = 51;
  font_map[99][4] = 3;
  font_map[99][5] = 51;
  font_map[99][6] = 30;
  font_map[99][7] = 0;

  // U+0064 (d)
  font_map[100][0] = 56;
  font_map[100][1] = 48;
  font_map[100][2] = 48;
  font_map[100][3] = 62;
  font_map[100][4] = 51;
  font_map[100][5] = 51;
  font_map[100][6] = 110;
  font_map[100][7] = 0;

  // U+0065 (e)
  font_map[101][0] = 0;
  font_map[101][1] = 0;
  font_map[101][2] = 30;
  font_map[101][3] = 51;
  font_map[101][4] = 63;
  font_map[101][5] = 3;
  font_map[101][6] = 30;
  font_map[101][7] = 0;

  // U+0066 (f)
  font_map[102][0] = 28;
  font_map[102][1] = 54;
  font_map[102][2] = 6;
  font_map[102][3] = 15;
  font_map[102][4] = 6;
  font_map[102][5] = 6;
  font_map[102][6] = 15;
  font_map[102][7] = 0;

  // U+0067 (g)
  font_map[103][0] = 0;
  font_map[103][1] = 0;
  font_map[103][2] = 110;
  font_map[103][3] = 51;
  font_map[103][4] = 51;
  font_map[103][5] = 62;
  font_map[103][6] = 48;
  font_map[103][7] = 31;

  // U+0068 (h)
  font_map[104][0] = 7;
  font_map[104][1] = 6;
  font_map[104][2] = 54;
  font_map[104][3] = 110;
  font_map[104][4] = 102;
  font_map[104][5] = 102;
  font_map[104][6] = 103;
  font_map[104][7] = 0;

  // U+0069 (i)
  font_map[105][0] = 12;
  font_map[105][1] = 0;
  font_map[105][2] = 14;
  font_map[105][3] = 12;
  font_map[105][4] = 12;
  font_map[105][5] = 12;
  font_map[105][6] = 30;
  font_map[105][7] = 0;

  // U+006A (j)
  font_map[106][0] = 48;
  font_map[106][1] = 0;
  font_map[106][2] = 48;
  font_map[106][3] = 48;
  font_map[106][4] = 48;
  font_map[106][5] = 51;
  font_map[106][6] = 51;
  font_map[106][7] = 30;

  // U+006B (k)
  font_map[107][0] = 7;
  font_map[107][1] = 6;
  font_map[107][2] = 102;
  font_map[107][3] = 54;
  font_map[107][4] = 30;
  font_map[107][5] = 54;
  font_map[107][6] = 103;
  font_map[107][7] = 0;

  // U+006C (l)
  font_map[108][0] = 14;
  font_map[108][1] = 12;
  font_map[108][2] = 12;
  font_map[108][3] = 12;
  font_map[108][4] = 12;
  font_map[108][5] = 12;
  font_map[108][6] = 30;
  font_map[108][7] = 0;

  // U+006D (m)
  font_map[109][0] = 0;
  font_map[109][1] = 0;
  font_map[109][2] = 51;
  font_map[109][3] = 127;
  font_map[109][4] = 127;
  font_map[109][5] = 107;
  font_map[109][6] = 99;
  font_map[109][7] = 0;

  // U+006E (n)
  font_map[110][0] = 0;
  font_map[110][1] = 0;
  font_map[110][2] = 31;
  font_map[110][3] = 51;
  font_map[110][4] = 51;
  font_map[110][5] = 51;
  font_map[110][6] = 51;
  font_map[110][7] = 0;

  // U+006F (o)
  font_map[111][0] = 0;
  font_map[111][1] = 0;
  font_map[111][2] = 30;
  font_map[111][3] = 51;
  font_map[111][4] = 51;
  font_map[111][5] = 51;
  font_map[111][6] = 30;
  font_map[111][7] = 0;

  // U+0070 (p)
  font_map[112][0] = 0;
  font_map[112][1] = 0;
  font_map[112][2] = 59;
  font_map[112][3] = 102;
  font_map[112][4] = 102;
  font_map[112][5] = 62;
  font_map[112][6] = 6;
  font_map[112][7] = 15;

  // U+0071 (q)
  font_map[113][0] = 0;
  font_map[113][1] = 0;
  font_map[113][2] = 110;
  font_map[113][3] = 51;
  font_map[113][4] = 51;
  font_map[113][5] = 62;
  font_map[113][6] = 48;
  font_map[113][7] = 120;

  // U+0072 (r)
  font_map[114][0] = 0;
  font_map[114][1] = 0;
  font_map[114][2] = 59;
  font_map[114][3] = 110;
  font_map[114][4] = 102;
  font_map[114][5] = 6;
  font_map[114][6] = 15;
  font_map[114][7] = 0;

  // U+0073 (s)
  font_map[115][0] = 0;
  font_map[115][1] = 0;
  font_map[115][2] = 62;
  font_map[115][3] = 3;
  font_map[115][4] = 30;
  font_map[115][5] = 48;
  font_map[115][6] = 31;
  font_map[115][7] = 0;

  // U+0074 (t)
  font_map[116][0] = 8;
  font_map[116][1] = 12;
  font_map[116][2] = 62;
  font_map[116][3] = 12;
  font_map[116][4] = 12;
  font_map[116][5] = 44;
  font_map[116][6] = 24;
  font_map[116][7] = 0;

  // U+0075 (u)
  font_map[117][0] = 0;
  font_map[117][1] = 0;
  font_map[117][2] = 51;
  font_map[117][3] = 51;
  font_map[117][4] = 51;
  font_map[117][5] = 51;
  font_map[117][6] = 110;
  font_map[117][7] = 0;

  // U+0076 (v)
  font_map[118][0] = 0;
  font_map[118][1] = 0;
  font_map[118][2] = 51;
  font_map[118][3] = 51;
  font_map[118][4] = 51;
  font_map[118][5] = 30;
  font_map[118][6] = 12;
  font_map[118][7] = 0;

  // U+0077 (w)
  font_map[119][0] = 0;
  font_map[119][1] = 0;
  font_map[119][2] = 99;
  font_map[119][3] = 107;
  font_map[119][4] = 127;
  font_map[119][5] = 127;
  font_map[119][6] = 54;
  font_map[119][7] = 0;

  // U+0078 (x)
  font_map[120][0] = 0;
  font_map[120][1] = 0;
  font_map[120][2] = 99;
  font_map[120][3] = 54;
  font_map[120][4] = 28;
  font_map[120][5] = 54;
  font_map[120][6] = 99;
  font_map[120][7] = 0;

  // U+0079 (y)
  font_map[121][0] = 0;
  font_map[121][1] = 0;
  font_map[121][2] = 51;
  font_map[121][3] = 51;
  font_map[121][4] = 51;
  font_map[121][5] = 62;
  font_map[121][6] = 48;
  font_map[121][7] = 31;

  // U+007A (z)
  font_map[122][0] = 0;
  font_map[122][1] = 0;
  font_map[122][2] = 63;
  font_map[122][3] = 25;
  font_map[122][4] = 12;
  font_map[122][5] = 38;
  font_map[122][6] = 63;
  font_map[122][7] = 0;

  // U+007B ({)
  font_map[123][0] = 56;
  font_map[123][1] = 12;
  font_map[123][2] = 12;
  font_map[123][3] = 7;
  font_map[123][4] = 12;
  font_map[123][5] = 12;
  font_map[123][6] = 56;
  font_map[123][7] = 0;

  // U+007C (|)
  font_map[124][0] = 24;
  font_map[124][1] = 24;
  font_map[124][2] = 24;
  font_map[124][3] = 0;
  font_map[124][4] = 24;
  font_map[124][5] = 24;
  font_map[124][6] = 24;
  font_map[124][7] = 0;

  // U+007D (})
  font_map[125][0] = 7;
  font_map[125][1] = 12;
  font_map[125][2] = 12;
  font_map[125][3] = 56;
  font_map[125][4] = 12;
  font_map[125][5] = 12;
  font_map[125][6] = 7;
  font_map[125][7] = 0;

  // U+007E (~)
  font_map[126][0] = 110;
  font_map[126][1] = 59;
  font_map[126][2] = 0;
  font_map[126][3] = 0;
  font_map[126][4] = 0;
  font_map[126][5] = 0;
  font_map[126][6] = 0;
  font_map[126][7] = 0;

  // U+007F
  font_map[127][0] = 0;
  font_map[127][1] = 0;
  font_map[127][2] = 0;
  font_map[127][3] = 0;
  font_map[127][4] = 0;
  font_map[127][5] = 0;
  font_map[127][6] = 0;
  font_map[127][7] = 0;

  return 0;
}