#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int main ( void ){

  int map_width, map_height;
  static char request[6];
  int investment;

  printf( "Velikost mapy:\n" );
  if( scanf( "%d %d", &map_width, &map_height ) != 2
  || map_width < 1
  || map_height < 1
  || map_width > 2000
  || map_height > 2000 ){
		printf( "Nespravny vstup.\n" );
		return 0;
	}

  static int price_map[3000][3000];

  printf( "Cenova mapa:\n" );

  for ( int i = 0 ; i < map_height; ++i ){
    for ( int k = 0 ; k < map_width; ++k ){
      if( scanf("%d", &price_map[k][i] ) != 1
      || price_map[k][i] < 1 ){
    		printf( "Nespravny vstup.\n" );
    		return 0;
    	}
    }
  }

  int c;

  while ( (c = getchar()) != '\n' && c != EOF ){

  }

  printf("Dotazy:\n");

  while ( 1 ){


    if ( scanf("%s %d", &request[0], &investment) != 2
    || investment < 1
    || ( strcmp(request, "count") != 0 && strcmp(request, "list" ) != 0) ){
      if (getchar()!= EOF)
        printf( "Nespravny vstup.\n" );
      return 0;
    }

    int row = 0, col = 0, sub_row = 0, sub_col = 0, sub_start = 0;
    int area = 0, sub_row_area = 0;
    int price = 0, max_area = 0;
    static int x[3000], y[3000], price_sum[3000];
    int xy_count = 0;
    static int width[3000], height[3000];

    for ( col = 0; col < map_height; ++col ){
      for ( row = 0; row < map_width; ++row ){
          area = 0;
          sub_row_area = 0;
          price = 0;
          if( price_map[row][col] <= investment ){
            // pro kazdy dalsi prvek v radce
            for ( sub_row = row; sub_row < map_width; ++sub_row ){
              // dalsi prvky v sloupci pro kazdy dalsi prvek v radce (predtim)
              sub_row_area += 1;
//////////////////////////
              for ( sub_col = col; sub_col < map_height; ++sub_col ){

                area += 1 * sub_row_area;
                // pro soucet vsech prvku v subarray
                for ( sub_start = 0; sub_start <= sub_row_area - 1; ++sub_start ){
                  price += price_map[sub_row - sub_start][sub_col];
                }

                if ( price > investment ){
                  area -= 1 * sub_row_area;
                  for ( sub_start = 0; sub_start <= sub_row_area - 1; ++sub_start ){
                    price -= price_map[sub_row - sub_start][sub_col];
                  }
                  break;
                }
              }
//////////////////////////
            // ulozi adr. subarraye s max. velikosti, nebo secte pokud se rovna
              if (area > max_area){
                max_area = area;
                xy_count = 0;
                x[xy_count] = row;
                y[xy_count] = col;
                price_sum[xy_count] = price;
                width[xy_count] = sub_row_area;
                height[xy_count] = area / sub_row_area;
               }
              if (area == max_area){
                xy_count += 1;
                x[xy_count] = row;
                y[xy_count] = col;
                price_sum[xy_count] = price;
                width[xy_count] = sub_row_area;
                height[xy_count] = area / sub_row_area;
              }
              area = 0;
              price = 0;
            }
          }
      }
    }

    if ( strcmp(request, "count") == 0 ){
      //* count
      if ( max_area != 0 )
        printf("Max. rozloha: %d (x %d)\n", max_area, xy_count);
      else
        printf("Nenalezeno.\n");
    }
    else{
      //* list
      if ( max_area != 0 ){
        printf("Max. rozloha: %d (x %d)\n", max_area, xy_count);
        for ( int i = 1; i <= xy_count; ++i ){
          printf("%d: %d x %d @ (%d,%d)\n", price_sum[i], width[i], height[i], x[i], y[i]);
        }
      }
      else
        printf("Nenalezeno.\n");
    }


  }



  return 0;
}
