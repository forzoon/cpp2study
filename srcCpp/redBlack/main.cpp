/******************************************************************************************
 * Data Structures in C++
 * ISBN: 7-302-33064-6 & 7-302-33065-3 & 7-302-29652-2 & 7-302-26883-3
 * Junhui DENG, deng@tsinghua.edu.cn
 * Computer Science & Technology, Tsinghua University
 * Copyright (c) 2003-2024.
 ******************************************************************************************/

/******************************************************************************************
 * Test of RedBlack Tree
 ******************************************************************************************/
#include "RedBlack_test.h"

/******************************************************************************************
 * Test a RedBlack
 ******************************************************************************************/
template <typename T> void testRedBlack( Rank n ) {
   RedBlack<T> rb;
   while ( rb.size() < n ) {
      T e = dice ( ( T ) n * 3 ); //[0, 3n)��Χ�ڵ�e
      switch ( dice ( 6 ) ) {
         case 0: { //���ң����� = 1/6��
            printf ( "Searching for " ); print ( e ); printf ( " ...\n" );
            BinNodePosi<T> p = rb.search ( e );
            p ?
            printf ( "Found with" ), print ( p ), printf ( "\n" ) :
            printf ( "Not found\n" );
            break;
         }
         case 1:
         case 2: { //ɾ�������� = 2/6)
            printf ( "Removing " ); print ( e ); printf ( " ...\n" );
            rb.remove ( e ) ? printf ( "Done\n" ), print ( rb ) : printf ( "Not exists\n" );
            break;
         }
         default: { //���루���� = 3/6)
            printf ( "Inserting " ); print ( e ); printf ( " ...\n" );
            BinNodePosi<T> p = rb.insert ( e );
            if ( p->data != e ) { print ( p->data ); printf ( " <> " ); print ( e ); printf ( "\n" ); }
            printf ( "Done with" ), print ( p ), printf ( "\n" ), print ( rb );
            break;
         }
      }
   }
   while ( rb.size() > 0 ) {
      T e = dice ( ( T ) n * 3 ); //[0, 3n)��Χ�ڵ�e
      printf ( "Removing " ); print ( e ); printf ( " ...\n" );
      rb.remove ( e ) ? printf ( "Done\n" ), print ( rb ) : printf ( "Not exists\n" );
   }
}

/******************************************************************************************
 * ���������
 ******************************************************************************************/
int main( int argc, char* argv[] ) {
   if ( 2 > argc ) { printf( "Usage: %s <size of Test>\a\a\n", argv[0] ); return 1; }
   srand((unsigned int)time(NULL)); //�������
   //srand( 31415926 ); //�̶����ӣ������ӣ������ã�
   testRedBlack<int>( atoi( argv[1] ) ); //Ԫ�����Ϳ�������������ѡ��
   return 0;
}