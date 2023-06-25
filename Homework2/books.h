/**
  ******************************************************************************
  * @file           : books.h
  * @author         : YuwenTianhao
  * @brief          : 由于用到链表，试一下头文件会不会更整洁
  * @attention      : None
  * @date           : 2023/3/14
  ******************************************************************************
  */

#ifndef HOMEWORK2_BOOKS_H
#define HOMEWORK2_BOOKS_H

struct Book;
typedef struct Book *PtrToBook;
typedef PtrToBook ListBook;
typedef PtrToBook Position;

void Insert_Book(Position newBook,Position P, ListBook L);
int Delete_Book(char *name, ListBook L);
Position Find(char *name, ListBook L);
Position FindPrevious(Position P, ListBook L);
int IsLast(Position P, ListBook L);
Position Header(ListBook L);
void initTable(Position P);

int dictionary_cmp(char *a_cmp, char *b_cmp);

#endif //HOMEWORK2_BOOKS_H
