#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define NAME_LENGTH 30

typedef struct {
	int health;
	int damage;
	int magic;
	char name[NAME_LENGTH];
}Enemy;

struct Node {
	Enemy enemy;
	Node* next;
};

struct NodeHead {
	int num;
	Node* first;
};

static void PrintColumn()
{
	printf("Please select one of the following operations:\n");
	printf("**********************************\n");
	printf("1. View all enemies' information.\n");
	printf("2. Add new enemies.\n");
	printf("3. Delete enemy.\n");
	printf("4. Sort enemies by damage.\n");
	printf("5. Find enemy.\n");
	printf("6. Clear enemies.\n");
	printf("0. End operation.\n");
	printf("**********************************\n");
}

static void EnemySwap(Node* a, Node* b)
{
	Node tmp;
	tmp.enemy.damage = a->enemy.damage;
	tmp.enemy.health = a->enemy.health;
	tmp.enemy.magic = a->enemy.magic;
	strcpy_s(tmp.enemy.name, NAME_LENGTH, a->enemy.name);
	a->enemy.damage = b->enemy.damage;
	a->enemy.health = b->enemy.health;
	a->enemy.magic = b->enemy.magic;
	strcpy_s(a->enemy.name, NAME_LENGTH, b->enemy.name);
	b->enemy.damage = tmp.enemy.damage;
	b->enemy.health = tmp.enemy.health;
	b->enemy.magic = tmp.enemy.magic;
	strcpy_s(b->enemy.name, NAME_LENGTH, tmp.enemy.name);
}

static void PrintAll(NodeHead* head)
{
	if (head->num == 0)
	{
		printf("Currently no enemy exists.\n");
	}
	else
	{
		Node* p;
		p = head->first;
		while (p != NULL)
		{
			printf("%s : Health--%d  Damage--%d  Magic--%d\n", p->enemy.name, p->enemy.health, p->enemy.damage, p->enemy.magic);
			p = p->next;
		}
	}
}

static void AddEnemy(NodeHead* head, int number)
{
	for (int i = 1; i <= number; i++)
	{
		Node* p = (Node*)malloc(sizeof(Node));
		printf("Please enter the %d-th enemy's name:\n",i);
		scanf_s("%s", p->enemy.name, NAME_LENGTH);
		printf("Please enter the %d-th enemy's health, damage and magic respectively:\n", i);
		scanf_s("%d %d %d", &p->enemy.health, &p->enemy.damage, &p->enemy.magic);
		p->next = head->first;
		head->first = p;
		head->num++;
		printf("Add successfully!\n");
	}
}

static void DeleteEnemy(NodeHead* head)
{
	printf("Enter the name of the target enemy:\n");
	char name[NAME_LENGTH];
	scanf_s("%s", name, NAME_LENGTH);
	Node* p;
	p = head->first;
	bool found = false;
	if (strcmp(name, p->enemy.name) == 0)
	{
		printf("Enemy called %s is found.\n", name);
		head->first = p->next;
		p->next = NULL;
		free(p);
		head->num--;
		printf("Delete successfully!\n");
	}
	else
	{
		while (p->next != NULL)
		{
			if (strcmp(name, p->next->enemy.name) == 0)
			{
				found = true;
				break;
			}
			p = p->next;
		}
	}
	if (found)
	{
		printf("Enemy called %s is found.\n", name);
		Node* tmp = p->next;
		p->next = p->next->next;
		tmp->next = NULL;
		free(tmp);
		head->num--;
		printf("Delete successfully!\n");
	}
	else
	{
		printf("Enemy called %s doesn't exist.", name);
	}
}

static Node* FindEnemy(NodeHead* head)
{
	printf("Enter the name of the expected enemy:\n");
	char name[NAME_LENGTH];
	scanf_s("%s", name, NAME_LENGTH);
	Node* p;
	p = head->first;
	while (p != NULL)
	{
		if (strcmp(name, p->enemy.name) == 0)
		{
			break;
		}
		p = p->next;
	}
	return p;
}

static void EnemySort(NodeHead* head, bool less)
{
	Node* p;
	for (int i = 0; i < head->num; i++)
	{
		Node* p = head->first;
		while (p->next != NULL)
		{
			if (less)
			{
				if (p->enemy.damage > p->next->enemy.damage)
				{
					EnemySwap(p, p->next);
				}
				p = p->next;
			}
			else
			{
				if (p->enemy.damage < p->next->enemy.damage)
				{
					EnemySwap(p, p->next);
				}
				p = p->next;
			}
		}
	}
	printf("Sort successfully!\n");
}

static void ClearEnemy(NodeHead* head)
{
	Node *p, *tmp;
	p = head->first;
	while (p != NULL)
	{
		tmp = p;
		p = p->next;
		tmp->next = NULL;
		free(tmp);
	}
	head->num = 0;
	printf("Clear successfully!\n");
}

int main()
{
	PrintColumn();
	NodeHead nodehead;
	nodehead.first = NULL;
	nodehead.num = 0;
	
	int choice;
	while (scanf_s("%d", &choice))
	{
		if (!choice)break;
		switch (choice)
		{
		case 1:
		{
			PrintAll(&nodehead);
		}
			break;
		case 2:
		{
			printf("How many enemies do you want to add?(within 20)\n");
			int number;
			while (scanf_s("%d", &number))
			{
				if (number <= 0 || number > 20)
				{
					printf("Illegal input, please try again.\n");
				}
				else
				{
					AddEnemy(&nodehead, number);
					break;
				}
			}
		}
			break;
		case 3:
		{
			DeleteEnemy(&nodehead);
		}
			break;
		case 4:
		{
			bool less;
			int input;
			printf("Want it less or greater?\n");
			printf("1. less  2.greater\n");
			scanf_s("%d", &input);
			if (input == 1)
			{
				less = true;
				EnemySort(&nodehead, less);
			}
			else if (input == 2)
			{
				less = false;
				EnemySort(&nodehead, less);
			}
			else
			{
				printf("Invalid input.\n");
			}
		}
			break;
		case 5:
		{
			Node* p;
			if ((p = FindEnemy(&nodehead)) != NULL)
			{
				printf("Enemy found.\n");
				printf("Its health--%d  its damage--%d  its magic--%d\n", p->enemy.health, p->enemy.damage, p->enemy.magic);
			}
		}
			break;
		case 6:
		{
			ClearEnemy(&nodehead);
		}
			break;
		default:
		{
			printf("Invalid input, try again.\n");
		}
			break;
		}
		system("pause");
		system("cls");
		PrintColumn();
	}

	printf("Exit successfully!\n");
	system("pause");
	
	return 0;
}