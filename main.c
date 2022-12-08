#include <pebble.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NUM_MENU_SECTIONS 5
#define NUM_FIRST_MENU_ITEMS 1
#define NUM_SECOND_MENU_ITEMS 1
#define NUM_THIRD_MENU_ITEMS 1
#define NUM_FOURTH_MENU_ITEMS 1
#define NUM_FIFTH_MENU_ITEMS 1

#define typeof __typeof__
#define SWAP(x, y) do { typeof(x) SWAP = x; x = y; y = SWAP; } while (0)

static Window *s_main_window;
static MenuLayer *s_menu_layer;
char ba[4] = {0,0,0,'\0'};
char i[4] = {0,0,0,'\0'};
char c[4] = {33,0,0,'\0'};
char h[4] = {0,0,0,'\0'};
char v[4] = {0,0,0,'\0'};
static int l='c';


char* itoa(int num, char* str, int base);
void reverse(char str[], int length);

void reverse(char str[], int length)
{
    int start = 0;
    int end = length -1;
    while (start < end)
    {
        SWAP(*(str+start), *(str+end));
        start+=1;
        end-=1;
    }
}

// Implementation of itoa()
char* itoa(int num, char* str, int base)
{
    int i = 0;
    int isNegative = 0;
 
    /* Handle 0 explicitely, otherwise empty string is printed for 0 */
    if (num == 0)
    {
        str[i++] = '0';
        str[i] = '\0';
        return str;
    }
 
    // In standard itoa(), negative numbers are handled only with 
    // base 10. Otherwise numbers are considered unsigned.
    if (num < 0 && base == 10)
    {
        isNegative = 1;
        num = -num;
    }
 
    // Process individual digits
    while (num != 0)
    {
        int rem = num % base;
        str[i++] = (rem > 9)? (rem-10) + 'a' : rem + '0';
        num = num/base;
    }
 
    // If number is negative, append '-'
    if (isNegative)
        str[i++] = '-';
 
    str[i] = '\0'; // Append string terminator
 
    // Reverse the string
    reverse(str, i);
 
    return str;
}


static uint16_t menu_get_num_sections_callback(MenuLayer *menu_layer, void *data) {
  
  APP_LOG(APP_LOG_LEVEL_DEBUG, "Get section nums!");
  
  return NUM_MENU_SECTIONS;
}

static uint16_t menu_get_num_rows_callback(MenuLayer *menu_layer, uint16_t section_index, void *data) {
  
  APP_LOG(APP_LOG_LEVEL_DEBUG, "Get row nums!");
  
  switch (section_index) {
    case 0:
      return NUM_FIRST_MENU_ITEMS;
    case 1:
      return NUM_SECOND_MENU_ITEMS;
    case 2:
      return NUM_THIRD_MENU_ITEMS;
    case 3:
      return NUM_FOURTH_MENU_ITEMS;
    case 4:
      return NUM_FIFTH_MENU_ITEMS;
    default:
      return 0;
    
  }
}

static int16_t menu_get_header_height_callback(MenuLayer *menu_layer, uint16_t section_index, void *data) {
  return MENU_CELL_BASIC_HEADER_HEIGHT;
}

static void menu_draw_header_callback(GContext* ctx, const Layer *cell_layer, uint16_t section_index, void *data) {
  // Determine which section we're working with
  
  APP_LOG(APP_LOG_LEVEL_DEBUG, "Draw header!");
  
  switch (section_index) {
    case 0:
        menu_cell_basic_header_draw(ctx, cell_layer, "Char");
    break;
    
    case 1:
        menu_cell_basic_header_draw(ctx, cell_layer, "Hex");
    break;
  
    case 2:
        menu_cell_basic_header_draw(ctx, cell_layer, "Int");
    break;
  
    case 3:
        menu_cell_basic_header_draw(ctx, cell_layer, "Custom Base Select");
    break;
  
    case 4:
        menu_cell_basic_header_draw(ctx, cell_layer, "Custom Base Result");
    break;  
  }
}

static void menu_draw_row_callback(GContext* ctx, const Layer *cell_layer, MenuIndex *cell_index, void *data) {
  // Determine which section we're going to draw in
  
  APP_LOG(APP_LOG_LEVEL_DEBUG, "Row callback!");
  
  switch (cell_index->section) {
    case 0:
      switch (cell_index->row) {
        case 0:
        menu_cell_basic_draw(ctx, cell_layer, c, NULL, NULL);
        break; 
      }
    break;

    case 1:
      // Use the row to specify which item we'll draw
      switch (cell_index->row) {
        case 0:
          
          menu_cell_basic_draw(ctx, cell_layer, h, NULL, NULL);
          break;
      }
    break;
    
    case 2:
      switch (cell_index->row) {
        case 0:
          
         menu_cell_basic_draw(ctx, cell_layer, i, NULL, NULL);
         break;
      }
    break;
    
    case 3:
      switch (cell_index->row) {
        case 0:
          
         menu_cell_basic_draw(ctx, cell_layer, ba, NULL, NULL);
         break;
      }
    break;
    
    case 4:
      switch(cell_index->row) {
          case 0:
          
         menu_cell_basic_draw(ctx, cell_layer, v, NULL, NULL);
         break;
      }
    break;
    }
}



static void menu_select_callback(MenuLayer *menu_layer, MenuIndex *cell_index, void *data) {
  
  APP_LOG(APP_LOG_LEVEL_DEBUG, "Menu callback!");
  
    switch (cell_index->section) {
    case 0:
      switch (cell_index->row) {
        case 0:
        
          APP_LOG(APP_LOG_LEVEL_DEBUG, "Char pressed!");
        
          if ((*c>125)||(l!='c')){
            *c=32;
          }
          *c+=1;
  
          snprintf(h, 4,"%02x",*c); 
          snprintf(i, 4,"%d",*c);  
          itoa(*c,v,*ba-48);
          l='c';
        
          APP_LOG(APP_LOG_LEVEL_DEBUG, "Char done!");
        
        break; 
      }
    break;
    
    case 1:
      
      switch (cell_index->row) {
        case 0:
        
        APP_LOG(APP_LOG_LEVEL_DEBUG, "Hex pressed!");
        
         if (l!='h'){
            *c=-1;
          }
          *c+=1;
  
          snprintf(h, 4,"%02x",*c); 
          snprintf(i, 4,"%d",*c);  
          itoa(*c,v,*ba-48);
          l='h';
        
          APP_LOG(APP_LOG_LEVEL_DEBUG, "Hex done!");
        
          break;
      }
    break;
    
    case 2:
      switch (cell_index->row) {
        case 0:
        
        APP_LOG(APP_LOG_LEVEL_DEBUG, "Int pressed!");
        
         if (l!='i'){
            *c=-1;
          }
          *c+=1;
  
          snprintf(h, 4,"%02x",*c); 
          snprintf(i, 4,"%d",*c);  
          itoa(*c,v,*ba-48);
          l='i';
         
        APP_LOG(APP_LOG_LEVEL_DEBUG, "Int done!");
        
         break;
      }
    break;
      
    case 3:
      switch (cell_index->row) {
        case 0:
        
        APP_LOG(APP_LOG_LEVEL_DEBUG, "Base increment pressed!");
        
         if ((l!='b') || (*ba>56)){
          
          *ba='1';
          }
          *ba+=1;
  
          snprintf(h, 4,"%02x",*c); 
          snprintf(i, 4,"%d",*c);  
          itoa(*c,v,*ba-48);
          l='b';
         
        APP_LOG(APP_LOG_LEVEL_DEBUG, "Base increment done!");
        
         break;
      }
    break;
  
    case 4:
      switch (cell_index->row) {
        case 0:
        
        APP_LOG(APP_LOG_LEVEL_DEBUG, "Custom base pressed!");
        
         if (l!='r'){
            *c=-1;
          }
          *c+=1;
  
          snprintf(h, 4,"%02x",*c); 
          snprintf(i, 4,"%d",*c);  
          itoa(*c,v,*ba-48);
          l='r';
         
        APP_LOG(APP_LOG_LEVEL_DEBUG, "Custom base done!");
        
         break;
      }
    break;      
      
    }  
      
      
      
  layer_mark_dirty(menu_layer_get_layer(s_menu_layer));

}


static void main_window_load(Window *window) {
  
  APP_LOG(APP_LOG_LEVEL_DEBUG, "Created window!");
  
  snprintf(h, 4,"%02x",*c); 
  snprintf(i, 4,"%d",*c);  
  itoa(*c,v,*ba-48);
  
  Layer *window_layer = window_get_root_layer(window);
  GRect bounds = layer_get_frame(window_layer);
  
  APP_LOG(APP_LOG_LEVEL_DEBUG, "Prep menu layer init!");
  
  // Create the menu layer
  s_menu_layer = menu_layer_create(bounds);
  
  APP_LOG(APP_LOG_LEVEL_DEBUG, "Created menu layer bounds!");
  
  menu_layer_set_callbacks(s_menu_layer, NULL, (MenuLayerCallbacks){
    .get_num_sections = menu_get_num_sections_callback,
    .get_num_rows = menu_get_num_rows_callback,
    .get_header_height = menu_get_header_height_callback,
    .draw_header = menu_draw_header_callback,
    .draw_row = menu_draw_row_callback,
    .select_click = menu_select_callback,
  });
  
  APP_LOG(APP_LOG_LEVEL_DEBUG, "Create menu layer!");

  // Bind the menu layer's click config provider to the window for interactivity
  menu_layer_set_click_config_onto_window(s_menu_layer, window);

  layer_add_child(window_layer, menu_layer_get_layer(s_menu_layer));
  
  APP_LOG(APP_LOG_LEVEL_DEBUG, "Added window layer!");
  
}

static void main_window_unload(Window *window) {
  // Destroy the menu layer
  menu_layer_destroy(s_menu_layer);
  }

static void init() {
  s_main_window = window_create();
  window_set_window_handlers(s_main_window, (WindowHandlers) {
    .load = main_window_load,
    .unload = main_window_unload,
  });
  
  if(s_main_window != NULL){
    window_stack_push(s_main_window, true);
    APP_LOG(APP_LOG_LEVEL_DEBUG, "Just pushed main window!");
  }
  else{
    APP_LOG(APP_LOG_LEVEL_DEBUG, "Couldn't push main window!");
  }
  
  
}

static void deinit() {
  window_destroy(s_main_window);
}

int main(void) {
  APP_LOG(APP_LOG_LEVEL_DEBUG, "Started main!");
  init();
  app_event_loop();
  deinit();
}
                                
