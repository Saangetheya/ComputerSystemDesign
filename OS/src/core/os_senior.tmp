int KEYBOARD;
int MAPSTART;
char *Buffer;
int current_buffer_index;
int line;
int character;
char *memory;
int displayLock;

int snake_len;
int seed;
int R_food;
int C_food;

int current_process;
int prev_process;
int pid;
int *os_reg;
int *p1_reg;
int *p2_reg;
int *p3_reg;
int *p4_reg;
int *temp_reg;
int *all_processes;
int *from_proc;

char get_char()
{
	int k;
	for (;;)
	{
		k = memory[KEYBOARD];
		if (k != 0)
		{
			return k;
		}
	}
}

int strlen(char *str)
{
	int count;
	count = 0;
	for (;;)
	{
		int ch;
		ch = str[count];
		if (ch == 0)
		{
			break;
		}
		count++;
	}
	return count;
}

int clear_shell()
{
	int i;
	for (i = 9599; i >= 0; i--)
	{
		memory[i] = 0;
	}
	line = 0;
	character = 0;
	return 0;
}

int display(char *arr, int size, int l, int c)
{
	int displayStart;
	displayStart = 320 * l;

	int k;

	for (k = 0; k < 8; k++)
	{
		int j;
		int a;
		a = k * 40; 
		for (j = 0; j < size; j++)
		{
			int m;
			m = a + j + c;
			if (c + j >= 40)
			{
				break;
			}
			int b;
			b = arr[j];
			b = b * 8;
			memory[displayStart + m] = memory[MAPSTART + b + k];
		}
	}
	return 0;
}

int welcome_screen()
{
	char *str;
	str = "########################################";
	display(str, 40, 0, 0);
	display(str, 40, 29, 0);
	int i;
	for (i = 1; i < 39; i++)
	{
		str[i] = 32;
	}
	for (i = 1; i < 29; i++)
	{
		display(str, 40, i, 0);
	}
	char *hello;
	hello = "Hello World!!!";
	int len;
	len = strlen(hello);

	display(hello, len, 15, 13);

	int key;
	for (;;)
	{
		key = get_char();
		if (key == 13)
		{
			break;
		}
	}
	clear_shell();

	return 0;
}

int get_line()
{
	int i;
	for (i = 0; i < 40; i++)
	{
		Buffer[i] = 0;
	}
	i = 0;
	for (;;)
	{
		if (i == 40)
		{
			break;
		}
		int temp;
		temp = get_char();
		if (temp == 13)
		{
			break;
		}
		elif (temp == 8)
		{
			if (i != 0)
			{
				i--;
				Buffer[i] = 0;
			}
		}
		else
		{
			Buffer[i] = temp;
			i++;
		}
		display(Buffer, 35, line, character);
	}
	current_buffer_index = 0;
	line = (line + 1) % 30;
	if (line == 0)
	{
		clear_shell();
	}
	character = 0;
	return i;
}

int strcmp(char *str1, char *str2)
{
	int len1, len2;
	len1 = strlen(str1);
	len2 = strlen(str2);

	if (len1 != len2)
	{
		return 1;
	}

	int i;
	int l1, l2;
	for (i = 0; i < len1; i++)
	{
		l1 = str1[i];
		l2 = str2[i];
		if (l1 != l2)
		{
			return 1;
		}
	}
	return 0;
}

int print_string(char *buff, int len, int newline)
{
	int i;
	for (; displayLock == 1;)
	{
		i = 0;
	}
	displayLock = 1;
	for (i = 0; i < len; i++)
	{
		if (character == 40)
		{
			line = (line + 1) % 30;
			if (line == 0)
			{
				clear_shell();
			}
			character = 0;
		}
		if (line == 30)
		{
			clear_shell();
		}

		char *b;
		int bu;
		bu = buff;
		bu = bu + i;
		b = bu;
		display(b, 1, line, character);
		character++;
	}
	if (newline == 1)
	{
		line = (line + 1) % 30;
		if (line == 0)
		{
			clear_shell();
		}
		character = 0;
	}
	displayLock = 0;
	return 0;
}

int get_string(char *buff)
{
	int i;
	i = 0;
	int current;
	current = Buffer[current_buffer_index];

	if (current == 0 || current_buffer_index >= 40)
	{
		get_line();
	}

	for (;;)
	{
		current = Buffer[current_buffer_index];
		if (current == 0 || current == 32 || current_buffer_index >= 40)
		{
			current_buffer_index++;
			return i;
		}
		else
		{
			buff[i] = Buffer[current_buffer_index];
			current_buffer_index++;
			i++;
		}
	}
	return 0;
}

int get_num()
{
	char buff[10];
	int size;
	size = get_string(buff);
	int num;
	num = 0;
	int i;
	int b;
	b = buff[0];
	if (b == 45)
	{
		for (i = 1; i < size; i++)
		{
			b = buff[i];
			if (b < 48 || b > 57)
			{
				return 0;
			}
			num = num * 10;
			num = num + b - 48;
		}
		return 0 - num;
	}

	for (i = 0; i < size; i++)
	{
		b = buff[i];
		if (b < 48 || b > 57)
		{
			return 0;
		}
		num = num * 10;
		num = num + b - 48;
	}
	return num;
}

int reverse(char *str, int len)
{
	int i;
	int j;
	i = 0;
	j = len - 1;
	for (i = 0; i < j; i++)
	{
		char temp;
		temp = str[i];
		str[i] = str[j];
		str[j] = temp;
		i++;
		j--;
	}
	return 0;
}
int print_num(int num, int newline)
{
	char buff[10];
	int i;
	i = 0;
	int b;
	b = 1;
	if (num < 0)
	{
		num = 0 - num;
		b = 0;
	}
	for (;;)
	{
		buff[i] = num % 10 + 48;
		i++;
		num = num / 10;
		if (num == 0)
		{
			break;
		}
	}
	if (b == 0)
	{
		buff[i] = 45;
		i++;
	}
	reverse(buff, i);
	print_string(buff, i, newline);
	return 0;
}

int processReturn()
{
	__asm__("label", "return_process_begin:", pid);
	// this should store the returned process id to R11;
	__asm__("processReturnEnter", "dummy", pid);

	int pr_process;
	__asm__("store", "R11", pr_process);

	int curIndex;
	int i;
	curIndex = 10;
	for (i = 1; i < 5; i++)
	{
		if (pr_process == all_processes[i])
		{
			curIndex = i;
		}
	}

	all_processes[curIndex] = 0;

	if (curIndex == 10)
	{
		char *prompt1;
		prompt1 = "Some problem occured, system crashing";
		int len;
		len = strlen(prompt1);
		print_string(prompt1, len, 1);
	}

	int next_process;
	next_process = 10;
	for (i = curIndex + 1; i < 5; i++)
	{
		if (all_processes[i] != 0)
		{
			next_process = i;
			break;
		}
	}

	if (next_process == 10)
	{
		for (i = 1; i <= curIndex; i++)
		{
			if (all_processes[i] != 0)
			{
				next_process = i;
				break;
			}
		}
	}

	if (next_process == 10)
	{
		char *prompt1;
		prompt1 = "Some problem occured, system crashing";
		int len;
		len = strlen(prompt1);
		print_string(prompt1, len, 1);
	}

	int next_id;
	next_id = all_processes[next_process];

	__asm__("load", "R11", next_id);
	if (next_process == 1)
	{
		__asm__("processReturnExit", "dummy", next_id);
		__asm__("switch", "1", next_id);
	}
	elif (next_process == 2)
	{
		__asm__("processReturnExit", "dummy", next_id);
		__asm__("switch", "2", next_id);
	}
	elif (next_process == 3)
	{
		__asm__("processReturnExit", "dummy", next_id);
		__asm__("switch", "3", next_id);
	}
	elif (next_process == 4)
	{
		__asm__("processReturnExit", "dummy", next_id);
		__asm__("switch", "4", next_id);
	}
	return 0;
}

int fork()
{
	int process;
	__asm__("store", "R11", process);

	int i;
	int core;
	core = 10;
	for (i = 1; i < 5; i++)
	{
		if (all_processes[i] == 0)
		{
			core = i;
			break;
		}
	}

	if (core == 10)
	{
		char *prompt;
		int len;
		prompt = "Cannot create a process, process overload";
		len = strlen(prompt);
		print_string(prompt, len, 1);
		len = 0;
		__asm__("forkReturn", "dummy", len);
		return 0;
	}

	int id;
	all_processes[core] = pid;
	id = pid;
	++pid;

	int *proc_reg;

	if (core == 0)
	{
		proc_reg = os_reg;
	}
	elif (core == 1)
	{
		proc_reg = p1_reg;
	}
	elif (core == 2)
	{
		proc_reg = p2_reg;
	}
	elif (core == 3)
	{
		proc_reg = p3_reg;
	}
	elif (core == 4)
	{
		proc_reg = p4_reg;
	}

	// set the new process variables

	// r7
	proc_reg[1] = 0;
	// r8
	proc_reg[2] = 0;
	// r9
	proc_reg[3] = 0;
	// r10
	proc_reg[4] = 0;
	// r12 aka heap
	proc_reg[5] = 55000 + core * 5000;
	// r14 aka stack
	proc_reg[6] = 53000 + core * 5000;

	// r5 - the jump address is known after compilation
	if (process == 1001)
	{
		__asm__("fork", "start_shell", proc_reg);
	}
	elif (process == 1002)
	{
		__asm__("fork", "print_A", proc_reg);
	}
	elif (process == 1003)
	{
		__asm__("fork", "print_B", proc_reg);
	}
	elif (process == 1004)
	{
		__asm__("fork", "print_C", proc_reg);
	}
	elif (process == 1005)
	{
		__asm__("fork", "print_D", proc_reg);
	}

	__asm__("forkReturn", "dummy", id);
	return 0;
}

int create_process(int process)
{
	prev_process = current_process;
	int cur_core;
	int i;
	cur_core = 10;
	for (i = 0; i < 5; i++)
	{
		if (all_processes[i] == current_process)
		{
			cur_core = i;
			break;
		}
	}

	if (cur_core == 0)
	{
		from_proc = os_reg;
	}
	elif (cur_core == 1)
	{
		from_proc = p1_reg;
	}
	elif (cur_core == 2)
	{
		from_proc = p2_reg;
	}
	elif (cur_core == 3)
	{
		from_proc = p3_reg;
	}
	elif (cur_core == 4)
	{
		from_proc = p4_reg;
	}

	__asm__("forkEnter", "dummy", process);
	__asm__("label", "create_process_return:", process);
	int id;
	__asm__("store", "R11", id);
	return id;
}

int switch ()
{
	__asm__("label", "switch_begin:", pid);
	__asm__("switchEnter", "dummy", pid);

	int pr_process;
	__asm__("store", "R11", pr_process);

	// print_string("p",1,0);
	// print_num(pr_process,0);

	int curIndex;
	int i;
	curIndex = 10;
	for (i = 1; i < 5; i++)
	{
		if (pr_process == all_processes[i])
		{
			curIndex = i;
		}
	}

	// print_string("c",1,0);
	// print_num(curIndex,0);
	// print_string("switch", 6,0);

	if (curIndex == 1)
	{
		from_proc = p1_reg;
	}
	elif (curIndex == 2)
	{
		from_proc = p2_reg;
	}
	elif (curIndex == 3)
	{
		from_proc = p3_reg;
	}
	elif (curIndex == 4)
	{
		from_proc = p4_reg;
	}

	from_proc[0] = temp_reg[0];
	from_proc[1] = temp_reg[1];
	from_proc[2] = temp_reg[2];
	from_proc[3] = temp_reg[3];
	from_proc[4] = temp_reg[4];
	from_proc[5] = temp_reg[5];
	from_proc[6] = temp_reg[6];

	if (curIndex == 10)
	{
		char *prompt1;
		prompt1 = "Some problem occured, system crashing";
		int len;
		len = strlen(prompt1);
		print_string(prompt1, len, 1);
	}
	int next_process;
	next_process = 10;
	for (i = curIndex + 1; i < 5; i++)
	{
		if (all_processes[i] != 0)
		{
			next_process = i;
			break;
		}
	}

	if (next_process == 10)
	{
		for (i = 1; i <= curIndex; i++)
		{
			if (all_processes[i] != 0)
			{
				next_process = i;
				break;
			}
		}
	}
	if (next_process == 10)
	{
		char *prompt1;
		prompt1 = "Some problem occured, system crashing";
		int len;
		len = strlen(prompt1);
		print_string(prompt1, len, 1);
	}

	// print_string("np", 2,0);
	// print_num(next_process, 0);

	int next_id;
	next_id = all_processes[next_process];

	// print_string("ni", 2,0);
	// print_num(next_id,0);

	__asm__("load", "R11", next_id);
	if (next_process == 1)
	{
		__asm__("switchReturn", "dummy", next_id);
		__asm__("switch", "1", next_id);
	}
	elif (next_process == 2)
	{
		__asm__("switchReturn", "dummy", next_id);
		__asm__("switch", "2", next_id);
	}
	elif (next_process == 3)
	{
		__asm__("switchReturn", "dummy", next_id);
		__asm__("switch", "3", next_id);
	}
	elif (next_process == 4)
	{
		__asm__("switchReturn", "dummy", next_id);
		__asm__("switch", "4", next_id);
	}
	return 0;
}

int print_A()
{
	int i;
	int k;
	int j;
	char *a;
	a = "a";
	for (i = 0; i < 10; i++)
	{
		for (j = 0; j < 10000; j++)
		{
			k = 0;
		}
		print_string(a, 1, 0);
	}
	return 0;
}

int print_B()
{
	int i;
	char *a;
	a = "b";
	int k;
	int j;
	for (i = 0; i < 100; i++)
	{
		for (j = 0; j < 10000; j++)
		{
			k = 0;
		}
		print_string(a, 1, 0);
	}

	for (;;)
	{
		i = 0;
	}
	return 0;
}

int print_C()
{
	int i;
	int k;
	int j;
	char *a;
	a = "c";
	for (i = 0; i < 100; i++)
	{
		for (j = 0; j < 10000; j++)
		{
			k = 0;
		}
		print_string(a, 1, 0);
	}

	for (;;)
	{
		i = 0;
	}
	return 0;
}

int print_D()
{
	int i;
	int k;
	int j;
	char *a;
	a = "d";
	for (i = 0; i < 100; i++)
	{
		for (j = 0; j < 10000; j++)
		{
			k = 0;
		}
		print_string(a, 1, 0);
	}

	for (;;)
	{
		i = 0;
	}
	return 0;
}

int fibonacci()
{
	char *prompt;
	int len;
	prompt = "Enter n";
	len = strlen(prompt);
	print_string(prompt, len, 1);

	int num;
	num = get_num();

	prompt = "The ";
	len = strlen(prompt);
	print_string(prompt, len, 0);

	print_num(num, 0);

	prompt = "th fibonacci number is: ";
	len = strlen(prompt);
	print_string(prompt, len, 0);

	if (num == 0)
	{
		print_num(1, 1);
	}
	elif (num == 1)
	{
		print_num(1, 1);
	}
	else
	{
		int i;
		int a;
		int b;
		a = 1;
		b = 1;
		for (i = 2; i <= num; i++)
		{
			int temp;
			temp = b;
			b = a;
			a = a + temp;
		}
		print_num(a, 1);
	}
	return 0;
}

int reverse_string()
{
	char str[30];
	int i;
	for (i = 0; i < 30; i++)
	{
		str[i] = 0;
	}
	int clen;

	char *prompt;
	int len;
	prompt = "Enter the String";
	len = strlen(prompt);
	print_string(prompt, len, 1);

	get_line();
	clen = get_string(str);

	prompt = "The Reverse of ";
	len = strlen(prompt);
	print_string(prompt, len, 0);

	print_string(str, clen, 0);

	int j;
	i = 0;
	j = clen - 1;

	for (; i < j;)
	{
		char temp;
		temp = str[i];
		str[i] = str[j];
		str[j] = temp;
		i++;
		j--;
	}

	prompt = " is ";
	len = strlen(prompt);
	print_string(prompt, len, 0);

	print_string(str, clen, 1);

	return 0;
}

int prime()
{
	char *prompt;
	int len;
	prompt = "Enter the number";
	len = strlen(prompt);

	print_string(prompt, len, 1);

	int n;
	n = get_num();

	int b;
	b = 1;
	int i;
	for (i = 2; i <= (n / 2) && n != 2; i++)
	{
		if (n % i == 0)
		{
			b = 0;
			break;
		}
	}

	if (b == 1)
	{
		print_num(n, 0);
		prompt = " is a prime number";
		len = strlen(prompt);
		print_string(prompt, len, 1);
	}
	else
	{
		print_num(n, 0);
		prompt = " is not a prime number";
		len = strlen(prompt);
		print_string(prompt, len, 1);
	}

	return 0;
}

int partition(int *arr, int low, int high)
{
	int pivot;
	pivot = arr[high];

	int i;
	i = low - 1;

	int j;
	for (j = low; j <= high; j++)
	{
		if (arr[j] < pivot)
		{
			i++;
			int temp;
			temp = arr[i];
			arr[i] = arr[j];
			arr[j] = temp;
		}
	}

	int t;
	t = arr[i + 1];
	arr[i + 1] = arr[high];
	arr[high] = t;
	return i + 1;
}

int quick_sort(int *arr, int low, int high)
{
	if (low < high)
	{
		int pi;
		pi = partition(arr, low, high);
		quick_sort(arr, low, pi - 1);
		quick_sort(arr, pi + 1, high);
	}

	return 0;
}

int sort()
{
	int n;
	char *prompt;
	int len;

	prompt = "Enter the number of elements";
	len = strlen(prompt);
	print_string(prompt, len, 1);

	n = get_num();

	prompt = "Enter the elements";
	len = strlen(prompt);
	print_string(prompt, len, 1);

	int arr[n];
	int i;
	for (i = 0; i < n; i++)
	{
		arr[i] = get_num();
	}

	prompt = "Sorted Array is";
	len = strlen(prompt);
	print_string(prompt, len, 1);

	quick_sort(arr, 0, n - 1);

	prompt = " ";
	len = 1;
	for (i = 0; i < n; i++)
	{
		print_num(arr[i], 0);
		print_string(prompt, len, 0);
	}
	print_string(prompt, len, 1);

	return 0;
}

int getIndex(int *values, int n)
{
	int i;
	for (i = 0; i < n; i++)
	{
		if (values[i] == 0 - 1)
		{
			return i;
		}
	}
	return 0 - 1;
}

int insert(int val, int *values, int *left, int *right, int n)
{
	if (values[0] == 0 - 1)
	{
		values[0] = val;
	}
	else
	{
		int root;
		root = 0;
		for (;;)
		{
			if (values[root] == val)
			{
				break;
			}
			elif (val < values[root])
			{
				if (left[root] == 0 - 1)
				{
					int index;
					index = getIndex(values, n);
					left[root] = index;
					values[index] = val;
					break;
				}
				else
				{
					root = left[root];
				}
			}
			elif (val > values[root])
			{
				if (right[root] == 0 - 1)
				{
					int index;
					index = getIndex(values, n);
					right[root] = index;
					values[index] = val;
					break;
				}
				else
				{
					root = right[root];
				}
			}
		}
	}
	return 0;
}

int inorder(int *values, int *left, int *right, int index)
{
	if (index != 0 - 1)
	{
		inorder(values, left, right, left[index]);
		print_num(values[index], 0);
		print_string(" ", 1, 0);
		inorder(values, left, right, right[index]);
	}

	return 0;
}

int tree()
{
	int n;
	char *prompt;
	int len;
	prompt = "Enter the Number of Elements";
	len = strlen(prompt);
	print_string(prompt, len, 1);

	n = get_num();

	int values[n];
	int left[n];
	int right[n];

	int i;
	for (i = 0; i < n; i++)
	{
		values[i] = 0 - 1;
		left[i] = 0 - 1;
		right[i] = 0 - 1;
	}

	prompt = "Enter the values";
	len = strlen(prompt);
	print_string(prompt, len, 1);

	for (i = 0; i < n; i++)
	{
		int k;
		k = get_num();
		insert(k, values, left, right, n);
	}

	prompt = "Inorder Traversal of the Tree";
	len = strlen(prompt);
	print_string(prompt, len, 1);

	inorder(values, left, right, 0);
	print_string(" ", 1, 1);
	return 0;
}

int get_keypress()
{
	int k;
	k = memory[KEYBOARD];
	return k;
}

int get_random()
{
	int a;
	int b;
	int m;
	a = 307;
	b = 401;
	m = 821;

	seed = (a * seed + b) % m;
	return seed;
}

// food for snake
int set_food(int *R_pos, int *C_pos)
{
	int r;
	int c;
	for (;;)
	{
		r = get_random();
		r = r % 30;
		c = get_random();
		c = c % 40;

		int i;
		int do;
		do
			= 1;
		for (i = 0; i < snake_len; i++)
		{
			if (r == R_pos[i] && c == C_pos[i])
			{
				do
					= 0;
				break;
			}
		}
		if (do == 1)
		{
			R_food = r;
			C_food = c;
			break;
		}
	}
	return 0;
}

int display_game_over()
{
	char *str;
	str = "########################################";

	display(str, 40, 0, 0);
	display(str, 40, 29, 0);
	int i;
	for (i = 1; i < 39; i++)
	{
		str[i] = 32;
	}
	for (i = 1; i < 29; i++)
	{
		display(str, 40, i, 0);
	}

	char *hello;
	hello = "Game Over";
	display(hello, 9, 14, 16);
	char *score;
	score = "Score is ";
	display(score, 9, 15, 15);
	line = 15;
	character = 24;
	print_num(snake_len, 0);
	return 0;
}

int displayPlayer(int *R_pos, int *C_pos)
{
	char *head;
	head = "0";
	char *body;
	body = "*";
	char *space;
	space = " ";
	int i;
	display(head, 1, R_pos[0], C_pos[0]);
	for (i = 1; i < snake_len; i++)
	{
		display(body, 1, R_pos[i], C_pos[i]);
	}
	display(space, 1, R_pos[snake_len], C_pos[snake_len]);

	char *food;
	food = "+";
	display(food, 1, R_food, C_food);
	return 0;
}

int movePlayer(int *R_pos, int *C_pos, int action)
{
	int R_head;
	R_head = R_pos[0];
	int C_head;
	C_head = C_pos[0];

	int left;
	left = 97;
	int right;
	right = 100;
	int up;
	up = 119;
	int down;
	down = 115;

	if (action == right)
	{
		if (C_head == 39)
		{
			C_head = 0;
		}
		else
		{
			C_head++;
		}
	}
	elif (action == left)
	{
		if (C_head == 0)
		{
			C_head = 39;
		}
		else
		{
			C_head--;
		}
	}
	elif (action == up)
	{
		if (R_head == 0)
		{
			R_head = 29;
		}
		else
		{
			R_head--;
		}
	}
	else
	{
		if (R_head == 29)
		{
			R_head = 0;
		}
		else
		{
			R_head++;
		}
	}

	int body;
	for (body = snake_len; body >= 1; body--)
	{
		R_pos[body] = R_pos[body - 1];
		C_pos[body] = C_pos[body - 1];
	}
	R_pos[0] = R_head;
	C_pos[0] = C_head;

	if (R_pos[0] == R_food && C_pos[0] == C_food)
	{
		set_food(R_pos, C_pos);
		snake_len++;
	}

	int game_over;
	game_over = 0;
	for (body = 1; body < snake_len; body++)
	{
		if (R_pos[body] == R_pos[0] && C_pos[body] == C_pos[0])
		{
			game_over = 1;
			break;
		}
	}
	return game_over;
}

int snake_game()
{
	clear_shell();
	snake_len = 9;
	seed = 97;
	int action;
	action = 100;

	int last;
	last = 100;

	int R_pos[100];
	int C_pos[100];

	int score;
	score = 0;

	int j;
	for (j = 0; j < snake_len + 1; j++)
	{
		R_pos[j] = 10;
	}

	for (j = snake_len; j >= 0; j--)
	{
		C_pos[j] = snake_len - j + 2;
	}

	set_food(R_pos, C_pos);
	displayPlayer(R_pos, C_pos);

	int sp;
	sp = 2;
	int k;

	for (;;)
	{
		for (j = 0; j < (2 - sp) * 500; j++)
		{
			k = 0;
		}
		sp = snake_len / 20;
		action = get_keypress();
		if (action == 0)
		{
			action = last;
		}
		elif (action == 97 && last == 100)
		{
			action = last;
		}
		elif (action == 100 && last == 97)
		{
			action = last;
		}
		elif (action == 119 && last == 115)
		{
			action = last;
		}
		elif (action == 115 && last == 119)
		{
			action = last;
		}
		else
		{
			last = action;
		}

		int game_over;
		game_over = movePlayer(R_pos, C_pos, action);
		if (game_over == 1)
		{
			display_game_over();
			break;
		}
		else
		{
			displayPlayer(R_pos, C_pos);
		}
	}

	int key;
	for (;;)
	{
		key = get_char();
		if (key == 13)
		{
			break;
		}
	}

	clear_shell();
	line = 0;
	character = 0;

	return 0;
}

int parse_command()
{
	char command[20];
	int i;
	for (i = 0; i < 20; i++)
	{
		command[i] = 0;
	}
	int clen;
	get_line();
	clen = get_string(command);

	char *clear;
	char *ls;
	char *fibo;
	char *tr;
	char *qsort;
	char *pri;
	char *rev;
	char *snake;
	char *exit;
	char *command_not_found;
	char *space;
	clear = "clear";
	ls = "ls";
	fibo = "fibo";
	tr = "tree";
	qsort = "quicksort";
	pri = "prime";
	rev = "reverse";
	snake = "snake";
	exit = "exit";
	command_not_found = "Command Not Found";
	space = " ";

	if (strcmp(command, clear) == 0)
	{
		clear_shell();
	}
	elif (strcmp(command, ls) == 0)
	{
		print_string(fibo, 4, 0);
		print_string(space, 1, 0);
		print_string(tr, 4, 0);
		print_string(space, 1, 0);
		print_string(qsort, 9, 0);
		print_string(space, 1, 0);
		print_string(pri, 5, 0);
		print_string(space, 1, 0);
		print_string(rev, 7, 1);

		print_string(snake, 5, 0);
		print_string(space, 1, 0);
		print_string(clear, 5, 0);
		print_string(space, 1, 0);
		print_string(ls, 2, 0);
		print_string(space, 1, 0);
		print_string(exit, 4, 1);
	}
	elif (strcmp(command, fibo) == 0)
	{
		fibonacci();
	}
	elif (strcmp(command, rev) == 0)
	{
		reverse_string();
	}
	elif (strcmp(command, pri) == 0)
	{
		prime();
	}
	elif (strcmp(command, qsort) == 0)
	{
		sort();
	}
	elif (strcmp(command, tr) == 0)
	{
		tree();
	}
	elif (strcmp(command, snake) == 0)
	{
		snake_game();
	}
	else
	{
		print_string(command_not_found, 17, 1);
	}
	return 1;
}

// this function will start the shell;
int start_shell()
{
	welcome_screen();
	char *arrow;
	arrow = "--->";
	int len;
	len = strlen(arrow);
	for (;;)
	{
		display(arrow, len, line, character);
		character = character + 4;
		int r;
		r = parse_command();
		if (r == 2)
		{
			break;
		}
	}
	return 0;
}

int main()
{
	pid = 1;
	current_process = pid;
	__asm__("load", "R3", current_process);

	KEYBOARD = 76000;
	line = 0;
	character = 0;
	Buffer = malloc(40);
	current_buffer_index = 0;
	MAPSTART = 42368;
	memory = 0;
	displayLock = 0;

	int i;
	for (i = 0; i < 40; i++)
	{
		Buffer[i] = 0;
	}

	os_reg = malloc(28);
	p1_reg = malloc(28);
	p2_reg = malloc(28);
	p3_reg = malloc(28);
	p4_reg = malloc(28);
	temp_reg = malloc(28);
	all_processes = malloc(20);

	all_processes[0] = current_process;
	all_processes[1] = 0;
	all_processes[2] = 0;
	all_processes[3] = 0;
	all_processes[4] = 0;

	++pid;
	int id;
	id = create_process(1001);
	create_process(1002);
	create_process(1003);
	__asm__("load", "R11", id);
	__asm__("switch", "1", id);
	return 0;
}
