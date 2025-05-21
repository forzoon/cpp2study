/******************************************************************************************
 * Data Structures in C++
 * ISBN: 7-302-33064-6 & 7-302-33065-3 & 7-302-29652-2 & 7-302-26883-3
 * Junhui DENG, deng@tsinghua.edu.cn
 * Computer Science & Technology, Tsinghua University
 * Copyright (c) 2003-2024.
 ******************************************************************************************/

/******************************************************************************************
 * Test of stack
 ******************************************************************************************/
#include "stack_test.h"

int testID = 0; //���Ա��

/******************************************************************************************
 * ����ջ
 ******************************************************************************************/
template <typename T> //Ԫ������
void testStack ( Rank n ) {
   Stack<T> S;
   printf ( "\n  ==== Test %2d. Growing stack\n", testID++ );
   while ( S.size() < n ) {
      if ( S.empty() || ( 30 < ( rand() % 100 ) ) ) { //70%������ջ
         T e = (T) dice ( 2 * n );
         printf ( "pushing " ); print ( e ); printf ( " ...\n" );
         S.push ( e );
      } else { //30%���ʳ�ջ
         printf ( "popping with ... " ); print ( S.pop() ); printf ( "\n" );
      }
      print ( S );
   }
   printf ( "\n  ==== Test %2d. Shrinking stack\n", testID++ );
   while ( !S.empty() ) {
      if ( 70 < dice ( 100 ) ) { //70%������ջ
         T e = (T) dice ( 2 * n );
         printf ( "pushing " ); print ( e ); printf ( " ...\n" );
         S.push ( e );
      } else { //70%���ʳ�ջ
         printf ( "popping with ... " ); print ( S.pop() ); printf ( "\n" );
      }
      print ( S );
   }
}


/******************************************************************************************
 * ����ջ
 ******************************************************************************************/
int main ( int argc, char* argv[] ) {
   if ( 2 > argc ) { printf ( "Usage: %s <size of Test>\a\a\n", argv[0] ); return 1; }
   srand((unsigned int)time(NULL)); //�������
   //srand( 31415926 ); //�̶����ӣ������ӣ������ã�
   testStack<int> ( atoi ( argv[1] ) ); //Ԫ�����Ϳ�������������ѡ��
   return 0;
}