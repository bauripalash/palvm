#include <stdio.h>
#include <stdbool.h>

typedef enum
{
	PSH,
	ADD,
	POP,
	SET,
	PREG,
	HLT
} Insts;

typedef enum
{
	X,
	Y,
	Z,
	IP,
	SP,
	REG_NUM
} Regs;

int regs[REG_NUM];

const int prog[] = {
	SET, X, 10,
	PREG,
	HLT};

int stk[256];
#define ipx (regs[IP])
#define spx (regs[SP])
bool running = true;

int get_ins()
{
	return prog[ipx];
}

void eval(int ins)
{
	switch (ins)
	{
	case HLT:
	{
		running = false;
		break;
	}
	case PSH:
	{
		spx++;
		stk[spx] = prog[++ipx];
		break;
	}
	case POP:
	{
		int pop_val = stk[spx--];
		printf("val-> %d\n", pop_val);
		break;
	}
	case ADD:
	{
		int a_val = stk[spx--];
		int b_val = stk[spx--];
		int res = b_val + a_val;
		spx++;

		stk[spx] = res;
		break;
	}
	case SET:
	{
		ipx++;
		int reg_name = prog[ipx];
		ipx++;
		int val = prog[ipx];
		regs[reg_name] = val;

		break;
	}
	case PREG:
	{
		ipx++;

		for (int i = 0; i != REG_NUM; i++)
		{
			printf("%d -> %d\n", i, regs[i]);
		}
		break;
	}
	}
}

int main()
{

	while (running)
	{
		int p = get_ins();
		eval(p);
		ipx++;
	}

	return 0;
}
