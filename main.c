#include<18F4550.h>

#use delay(clock=4MHz)



#fuses HS, NOWDT  
#use standard_io(A)
#use standard_io(B)
#use standard_io(C)
#use standard_io(D)
#use standard_io(E)

#include <main.h>

#include<HDM64GS12.c> 
#include<graphics.c>

// Character Arrays

char w[] = "  Welcome To H & S  ";
char buy[] = "Press X To Show Bill";
char bill[] = "No. Prod  Qty  Price";
char another_product[] = "Press Y to Buy More";
char thank[] = " Thanks For Shopping ";
char not_found[] = " Not Found ";

char net_bill[] = "Your Net Bill = ";

char prod1[] = " Pizza ";
char prod2[] = " Coke ";
char prod3[] = " Burger ";
char prod4[] = " Sprite ";
char prod5[] = " Fries ";
char prod6[] = " Shami ";

char *key[] = {"0","1","2","3","4","5","6","7","8","9","*","#"};
char *prod_num[] = {"1","2","3","4","5","6"};

char pric1[] = "10";
char pric2[] = "20";
char pric3[] = "30";
char pric4[] = "40";
char pric5[] = "50";
char pric6[] = "60";





// Variables
char extra[3];
char extra2[4];

int L = 0;
int keypadfull =0;
int k = 0;
int counter = 0;
int ten = 0;
int unit = 0;
int space = 0;
int buy_another = 0;
int prod_no = 0;
int qty = 0;

int qty_extra = 0;
long x = 0;
long net = 0;

long pri1 = 10; ///Long is used to convert Integer into Char Thhough built-in function
long pri2 = 20;
long pri3 = 30;
long pri4 = 40;
long pri5 = 50;
long pri6 = 60;


// Functions 

void Display();
void kypd();
void Billing();


void main()
{
      glcd_init(ON); // To initialize display
    while(1)
    {
      Display(); // Function to show list of products and price
      while(1)
      {
         if(1 == input(PIN_B3))  // infinite loop untill pin B3 = 1
         {
            while(input(PIN_B3)==1);
            glcd_rect(0, 0, 127, 127, YES, OFF); // graphics.c built-in function used to clear GLCD
            delay_ms(50);
            break;
         }
      }
      Billing(); // Functions to make bill of products bought by customer
      delay_ms(2000);
      
      L = 0;            // After making one bill reset all variables for next billing
      keypadfull =0;
      k = 0;
      counter = 0;
      ten = 0;
      unit = 0;
      space = 0;
      buy_another = 0;
      prod_no = 0;
      qty = 0;

      qty_extra = 0;
      x = 0;
      net = 0;
      
      glcd_rect(0, 0, 127, 127, YES, OFF);    // Clear GLCD after finishing Billing
    }
   
}

void Display()   /// Function to display list of products and respective price
{
   glcd_text57(2, L, w, 1, ON);  // 1 -> 5 pixel wide & 7 pixel tall char
   L+=8;
   glcd_text57(2, L, buy , 1, ON);
   L+=8;
   
   glcd_line(90, 16, 90, 64, ON);  // glcd_line(x1, y1, x2, y2, color)  
   
   glcd_text57(4, L, prod1, 1, ON);glcd_text57(100, L, pric1, 1, ON); glcd_text57(0, L, prod_num[0], 1, ON);
   L+=8;
   glcd_text57(4, L, prod2, 1, ON);glcd_text57(100, L, pric2, 1, ON);glcd_text57(0, L, prod_num[1], 1, ON);
   L+=8;
   glcd_text57(4, L, prod3, 1, ON);glcd_text57(100, L, pric3, 1, ON);glcd_text57(0, L, prod_num[2], 1, ON);
   L+=8;
   glcd_text57(4, L, prod4, 1, ON);glcd_text57(100, L, pric4, 1, ON);glcd_text57(0, L, prod_num[3], 1, ON);
   L+=8;
   glcd_text57(4, L, prod5, 1, ON);glcd_text57(100, L, pric5, 1, ON);glcd_text57(0, L, prod_num[4], 1, ON);
   L+=8;
   glcd_text57(4, L, prod6, 1, ON);glcd_text57(100, L, pric6, 1, ON);glcd_text57(0, L, prod_num[5], 1, ON);
   L+=8;
   
}

void Billing()  // Function to show bill of customer
{
   L = 0;
   glcd_text57(2, L, another_product , 1, ON);
   L+=8;
   glcd_text57(2, L, bill, 1, ON);
   
   L = 16;
   for(int r=0;r<=5;r++)
   {
      
      Z:prod_no = 1;  // Z as loop in asm
      qty = 0;
      space = 1;
      while(1)  //for product number
      {
         kypd();
         if(counter == 1)
         {
            space+=30;
            space = 8;
            if(ten == 1)
            {
               qty_extra = ten;
               glcd_text57(space, L, prod1, 1, ON);
               space = 1;
            }
            else if(ten == 2)
            {
               qty_extra = ten;
               glcd_text57(space, L, prod2, 1, ON);
               space = 1;
            }
            else if(ten == 3)
            {
               qty_extra = ten;
               glcd_text57(space, L, prod3, 1, ON);
               space = 1;
            }
            else if(ten == 4)
            {
               qty_extra = ten;
               glcd_text57(space, L, prod4, 1, ON);
               space = 1;
            }
            else if(ten == 5)
            {
               qty_extra = ten;
               glcd_text57(space, L, prod5, 1, ON);
               space = 1;
            }
            else if(ten == 6)
            {
               qty_extra = ten;
               glcd_text57(space, L, prod6, 1, ON);
               space = 1;
            }
            else   // if wrong product number is entered
            {
               qty_extra = 0;
               glcd_text57(space, L, not_found, 1, ON);
               delay_ms(20);
               glcd_rect(0, L, 70, 63, YES, OFF);  
               
               space = 1;
               keypadfull =0;
               k = 0;
               counter = 0;
               ten = 0;
               unit = 0;
             
               goto Z;
            }
            
             space-=30;
             keypadfull =0;
             k = 0;
             counter = 0;
             ten = 0;
             unit = 0;
             break;
         }
      }
      
      prod_no = 0;
      qty = 1;
      space = 60;
      while(1) // quantity and price
      {
         
         kypd();
         if(keypadfull == 1)
          {
            space +=30;
            if(qty_extra == 1)
            {
              
               x = pri1*unit;
               sprintf(extra,"%lu",x); // buit-in function to convert integer into char
               glcd_text57(space, L, extra, 1, ON);
               
               space = 1;
            }
            else if(qty_extra == 2)
            {
               
               x = pri2*unit;
               sprintf(extra,"%lu",x);
               glcd_text57(space, L, extra, 1, ON);
               space = 1;
            }
            else if(qty_extra == 3)
            {
               
               x = pri3*unit;
               sprintf(extra,"%lu",x);
               glcd_text57(space, L, extra, 1, ON);
               space = 1;
            }
            else if(qty_extra == 4)
            {
              
               x = pri4*unit;
               sprintf(extra,"%lu",x);
               glcd_text57(space, L, extra, 1, ON);
               space = 1;
            }
            else if(qty_extra == 5)
            {
              
               x = pri5*unit;
               sprintf(extra,"%lu",x);
               glcd_text57(space, L, extra, 1, ON);
               space = 1;
            }
            else if(qty_extra == 6)
            {
               x = pri6*unit;
               sprintf(extra,"%lu",x);
               glcd_text57(space, L, extra, 1, ON);
               space = 1;
            }
                 
          
             space -=30;
             keypadfull =0;
             k = 0;
             counter = 0;
             ten = 0;
             unit = 0;
             break;
          }
      }
      L+=8;
      while(1)
      {
         if(1 == input(PIN_C4))  // Next
         {
            while(input(PIN_C4)==1);
            delay_ms(50);
            net = net + x;
            
            break;
         }
         if(1 == input(PIN_C5) || r==5) // Net
         {
            while(input(PIN_C5)==1);
            delay_ms(50);
            net = net + x;
            
            r = 6;
            glcd_rect(0, 0, 127, 127, YES, OFF);
            delay_ms(10);
            L = 8;
            glcd_text57(1, L, net_bill, 1, ON);
            space = 100;
            
            sprintf(extra2,"%lu",net);
            glcd_text57(space, L, extra2, 1, ON);/// Net Price
            L+=32;
            glcd_text57(2, L, thank, 1, ON);
            
            net = 0;
            
            
            break;
         }
      }
      
    }
}


void kypd()
{
    output_high(PIN_A0);  output_low(PIN_A1);  output_low(PIN_A2);    

    if (1 == input(PIN_A3)) 
    { 
      delay_ms(100); 
      while(input(PIN_A3)==1);
      k = 1; 
      delay_ms(10); 
      counter = counter + 1;
    }
   
    if (1 == input(PIN_A4)) 
    { 
      delay_ms(100);
      while(input(PIN_A4)==1);
      k= 4;             
      delay_ms(10); 
      counter = counter + 1;
    }
   
    if ( 1 == input(PIN_A5 )) 
    { 
      delay_ms(100); 
      while(input(PIN_A5)==1);
      k = 7;            
      delay_ms(10); 
      counter = counter + 1;
    }
   
   /* if (1 == input(PIN_C1 )) 
    { 
      delay_ms(100); 
      while(input(PIN_C1)==1);
      k= 10;              
      delay_ms(10); 
      counter = counter + 1;
    }
    */
    
    output_low(PIN_A0); output_high(PIN_A1); output_low(PIN_A2);
    
    if (1 == input(PIN_A3 ))
    { 
      delay_ms(100); 
      while(input(PIN_A3)==1);
      k =2;       
      delay_ms(10); 
      counter = counter + 1;}
   
    if (1 == input(PIN_A4 )) 
    { 
      delay_ms(100);
      while(input(PIN_A4)==1); 
      k = 5;
      delay_ms(10); 
      counter = counter + 1;
    }
   
    if (1 == input(PIN_A5 )) 
    { 
      delay_ms(100); 
      while(input(PIN_A5)==1); 
      k=8;
      delay_ms(10); 
      counter = counter + 1;
    }
   
    if (1 == input(PIN_C1 ))
    { 
      delay_ms(100); 
      while(input(PIN_C1)==1); 
      k=0; 
      delay_ms(10);
      counter = counter + 1;
    }
    
    
    output_low(PIN_A0); output_low(PIN_A1); output_high(PIN_A2);
    
    if (1 == input(PIN_A3))
    { 
      delay_ms(100);
      while(input(PIN_A3)==1);
      k= 3;         
      delay_ms(10); 
      counter = counter + 1;
    }
   
    if (1 == input(PIN_A4 )) 
    { 
      delay_ms(100); 
      while(input(PIN_A4)==1); 
      k=6;        
      delay_ms(10); 
      counter = counter + 1;
    }
   
    if ( 1 == input(PIN_A5 ))
    { 
      delay_ms(100);
      while(input(PIN_A5)==1);
      k= 9;       
      delay_ms(10); 
      counter = counter + 1;
    }
   
    /*if (1 == input(PIN_C1 )) 
    { 
         delay_ms(100); 
         while(input(PIN_C1)==1); 
         k = 12;        
         delay_ms(10); 
         counter = counter + 1;
    }
    */
    
    if(prod_no == 1)
    {
      if(counter == 1)
      {
        ten=k;
        
        glcd_text57(space, L, key[k], 1, ON);
       }
    }
    
    if(qty == 1)
    {
      if(counter == 1)
      {
        ten=k;
        
        glcd_text57(space, L, key[k], 1, ON);
      }
      else if(counter == 2)
      {
        keypadfull = 1;
        space +=8;
        unit = k;
        unit =(ten*10)+unit;
        
        glcd_text57(space, L,  key[k], 1, ON);
      }
   
        //write_eeprom ( address , pointer , N );
    }
   
}
