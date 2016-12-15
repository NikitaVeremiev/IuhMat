#include <string.h> //здесь strlen,strcpy
#include <stdio.h>  //здесь fopen, ftegs, fclose, fwrite
#include <stdlib.h> //здесь qsort
typedef struct List List;
struct List {
	int cnt;
	char* item;
	List *next;
};
int list_get(List *list, char* index);
int list_gget(List *list, char* index);
void list_set(List *list, unsigned index, int item);
List *list_add(List *head, char* item) {
	if(list_get(head, item) == -1)
	{
		List *new_item = (List *) malloc(sizeof(List));
		new_item->item = item;
		new_item->next = NULL;
		new_item->cnt = 1;
		if (head)
		{
			List *list;
			//go to the end
			for (list = head; list->next; list = list->next);
			list->next = new_item; //append
		}
		else
		{
			head = new_item; //init (create) list
		}
	}
	else
	{
		list_set(head, list_get(head, item), list_gget(head, item) + 1);
	}
	return head;
}

int list_gget(List *list,  char* index) {
	unsigned i;
	for (i = 0; list; list = list->next, i++)
		if (strcmp(list->item, index) == 0)
			return list->cnt;
	return -1;
}
int list_get(List *list, char* index) {
	unsigned i;
	for (i = 0; list; list = list->next, i++)
	{
		if (strcmp(list->item, index) == 0)
		{
	//		printf("THIS%s %sTHIS\n", list -> item, index);
			return i;
		}
	}
	return -1;
}
void list_set(List *list, unsigned index, int item) {
	unsigned i;
	for (i = 0; list; list = list->next, i++)
		if (i == index) {
			list->cnt = item;
			return;
		}
}
void list_print(List *list) {
	for ( ; list; list = list->next)
		printf("%s %d->\n", list->item, list->cnt);
	printf("NULL\n");
}
void list_destroy(List *list) {
	if (list) {
		list_destroy(list->next);
		free(list);
	}
}
int main()
{
	List *list = NULL;
        int n, k = 0, i = 0;
	char* t;
        char tmp[1025]; //временная переменная для считывания строки
        FILE * p = fopen("input.txt" , "r"); //открываем файл input.txt в режиме чтения
        char** mas = (char **) malloc(n * sizeof(char *));      // создаем массив указателей, хранящий указатели на каждую строку
	char** mas_cpy = (char **) malloc(n*sizeof(char*));
        for (n = 0; fgets(tmp, sizeof(tmp), p); n++)
        {
                int len = strlen(tmp);
                mas[n] = strdup(tmp); //выделяем память под строку i
		mas_cpy[n] = strdup(tmp);
        }
        fclose(p);      //закрываем файл
	for(i = 0; i < n; i++)
	{
	t = strtok (mas_cpy[i]," ,.-");
	while (t != NULL)           // пока есть лексемы
  	{
		if((t[0] >= 'A') && (t[0] <= 'Z'))
		{
      		list = list_add(list, t);
		k++;
		}
		t = strtok (NULL, " ,.-");
	}
	}
	list_print(list);
	printf("k = %d\n",k);
        p = fopen("output.txt", "w");           //открываем файл в режиме записи
        if(p != NULL)     //проверяем, открылся ли файл
        {
                for(i = 0; i < n; i++)          //цикл выполняем n раз
                {
           
            fprintf(p, "%s", mas[i]);   //записываем строку i в файл
                        free(mas[i]);      //удаляем строку i
		}
                fclose(p); //закрываем файл
        }
        free(mas);  //удаляем массив указателей
	free(mas_cpy);
        return 0;
}
