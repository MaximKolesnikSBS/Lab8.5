/*
    Автор: Максим Колесник
    Группа: СБС-001-О-01
    Задание№: 8: 5)
    Цель: Написать программу для создания N-арного дерева.
*/

#include <iostream>
#include <cstdio>
#include <cctype>
using namespace std;

int N; // определяет арность дерева

struct Node
{
    int v; // значение в узле дерева
    int n; // кол-во узлов в поддереве с корнем в данном узле
    Node** cld; // массив потомков
    Node() : v(0), n(1), cld(new Node* [N]) { for (int i = 0; i < N; ++i) cld[i] = 0; }
};

Node* root = 0; // корень дерева

int parseTreeR(Node*& r, char*& s) // парсит дерево из скобочной последовательности; возвращает кол-во узлов в поддереве
{
    int n = 0; // здесь накапливаем узлы поддерева
    int m; // не знаю как объяснить, чтобы не запутать

    if (isdigit(*s))
    {
        r = new Node(); // создаем очередной узел дерева
        n = 1; // и запоминаем, что в поддереве с корнем в этом узле есть 1 узел
        do { r->v = r->v * 10 + *s++ - '0'; } while (isdigit(*s)); // парсим значение в узле
        for (int i = 0; i < N; ++i) // рекурсивно парсим всех потомков
            if (*s == '(' && (m = parseTreeR(r->cld[i], ++s)) >= 0 && *s == ')')
            {
                ++s; n += m;
            }
        return r->n = n;
    }
    else if (*s == ')') return n; // особый случай: пустой узел ( типа такого: () )
    else return -1; // если криво ввели скобочную последовательность, то надо об этом сообщить "наверх"
}

bool parseTree(char* s) // обертка над парсилкой дерева parseTreeR
{
    int m;
    if (*s == '(')
    {
        m = parseTreeR(root, ++s);
        if (m == -1) return false;
        if (*s == ')' && *++s == 0) return true;
        else return false;
    }
    return false;
}

void showTreeR(Node* r, int sh) // распечатка дерева
{
    if (!r) return;
    for (int j = 0; j < sh; ++j) putchar(' ');
    printf("%d\n", r->v);
    for (int i = 0; i < N; ++i)
        showTreeR(r->cld[i], sh + 5);
}

void showTree() // обертка над печаталкой дерева
{
    printf("\nTree:\n\n");
    showTreeR(root, 0);
    printf("\n");
}

int main()
{
    N = 3; // задаем арность дерева
//  char s[] = "(1)";
//  char s[] = "(1(2(3)(4)))";
    char s[] = "(1(2(5(6)))(3(7(8)(2)))(4))"; // дерево в виде скобочной последовательности

    if (parseTree(s)) // если дерево удачно спарсилось из скобочной последовательности
    {
        showTree();
    }
    else
        printf("Bad tree\n\n");

    return 0;
}