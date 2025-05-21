/******************************************************************************************
 * Data Structures in C++
 * ISBN: 7-302-33064-6 & 7-302-33065-3 & 7-302-29652-2 & 7-302-26883-3
 * Junhui DENG, deng@tsinghua.edu.cn
 * Computer Science & Technology, Tsinghua University
 * Copyright (c) 2003-2024.
 ******************************************************************************************/

/******************************************************************************************
 * Test of Skiplist
 ******************************************************************************************/

#include "skipList_test.h"

/******************************************************************************************
 * ������ת��
 ******************************************************************************************/
template <typename K, typename V> //key��value
void testSkiplist ( Rank n ) {
   Skiplist<K, V> L;
   while ( L.size() < n )
      switch ( dice ( 3 ) ) {
         case 0: { //���ң��ɹ��� <= 33.3%
            K key = dice ( ( K ) n * 3 ); //[0, 3n)��Χ�ڵ�key
            printf ( "Searching for " ); print ( key ); printf ( " ... " );
            V* pValue = L.get ( key );
            pValue ? printf ( "found with " ), print ( *pValue ) : printf ( "Not found" ); printf ( "\n\n" );
            break;
         }
         case 1: { //ɾ�����ɹ��� <= 33.3%
            K key = dice ( ( K ) n * 3 ); //[0, 3n)��Χ�ڵ�key
            printf ( "Removing " ); print ( key ); printf ( " ... " );
            if ( L.remove ( key ) ) { printf ( "Done\n" ); print(L); }
            else printf ( "Entry not exists\n\n" );
            break;
         }
         default: {//���룬�ɹ��� == 100%
            K k = dice ( ( K ) n * 3 ); V v = ( V ) 'A' + dice ( 26 ); //��[0, 2n)*['A'~'Z']��Χ�ڵĴ���
            printf ( "Inserting <" ); print ( k ); printf ( "," ); print ( v ); printf ( "> ... " );
            L.put ( k, v ); printf ( "Done\n" );
            print ( L );
            break;
         }
      }
   while ( L.size() > 0 ) {
      K key = dice ( ( K ) n * 3 ); //[0, 3n)��Χ�ڵ�key
      printf ( "Removing " ); print ( key ); printf ( " ... " );
      L.remove ( key ) ? printf ( "Done\n" ) : printf ( "Entry not exists\n" );
      print ( L ); printf("\n");
   }
}

/******************************************************************************************
 * ������
 ******************************************************************************************/
int main ( int argc, char* argv[] ) {
   if ( 2 > argc ) { printf ( "Usage: %s <size of Test>\a\a\n", argv[0] ); return 1; }
   srand((unsigned int)time(NULL)); //�������
   //srand( 31415926 ); //�̶����ӣ������ӣ������ã�
   testSkiplist<int, char> ( atoi ( argv[1] ) ); //Ԫ�����Ϳ�������������ѡ��
   return 0;
}