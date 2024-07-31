#include <LiquidCrystal.h>
LiquidCrystal lcd(12,11, 8, 7, 4, 2);//port for LCD(d1,d2,d3,d4,d5)
#define Rb 3         //right motor input 1(+ve terminal)
#define Rf 5         //right motor input 2(-ve terminal)
#define Lb 9         //left motor input 1(-ve terminal)
#define Lf 6         //left motor input 2 (+ve terminal)
#define topS 255
#define EXTL A0
#define L A1
#define R A2
#define EXTR A3
#define BLS A4
#define BRS A5
#define I 350
int el,l,r,er,bls,brs ;

void forward()
{
  lcd.setCursor(14,0);
  lcd.print("^^  ");
  lcd.setCursor(14,1);
  lcd.print("!!");
  analogWrite(Rf,255);    //505
  analogWrite(Rb,0);
  analogWrite(Lb,0);
  analogWrite(Lf,255);    //I
  
}
void ruk()
{ lcd.setCursor(14,0);
  lcd.print("__");
  lcd.setCursor(14,1);
  lcd.print("||");
  analogWrite(Rf,topS);
  analogWrite(Rb,topS);
  analogWrite(Lb,topS);
  analogWrite(Lf,topS);
 
}
void reverse()
{
 lcd.setCursor(14,0);
  lcd.print("||  ");
  lcd.setCursor(14,1);
  lcd.print("VV");
   lcd.setCursor(0,1);
  analogWrite(Rf,0);
  analogWrite(Rb,255);        //255
  analogWrite(Lb,255);        //250
  analogWrite(Lf,0);
  delay(100);
 
}
void left()
{ lcd.setCursor(14,0);
  lcd.print("<-");
  lcd.setCursor(14,1);
  lcd.print("<-");
  analogWrite(Rf,0);          //220
  analogWrite(Rb,255);
  analogWrite(Lb,0);          //250
  analogWrite(Lf,255);
  
  }
void right()
{ lcd.setCursor(14,0);
  lcd.print("-> ");
  lcd.setCursor(14,1);
  lcd.print("->");
  analogWrite(Rf,255);
  analogWrite(Rb,0);      //220
  analogWrite(Lb,255);        
  analogWrite(Lf,0);      //250
  
  }
void lcd_sen_val()
{
  el=analogRead(EXTL);
  lcd.setCursor(1,0);
  lcd.print(el/100);
  
  l=analogRead(L);
  lcd.setCursor(3,0);
  lcd.print(l/100);
  
  r=analogRead(R);
  lcd.setCursor(5, 0);
  lcd.print(r/100);
  
  er=analogRead(EXTR);
  lcd.setCursor(7,0);
  lcd.print(er/100);
  
  bls=analogRead(BLS);
  lcd.setCursor(10,0);
  lcd.print(bls/100);
  
  brs=analogRead(BRS);
  lcd.setCursor(12,0);
  lcd.print(brs/100);
}


void setup() 
{
lcd.begin(16, 2);//lcd chalu ho ja
}
void loop()                                                         //*77*    *70*  *07*  *00*
{ lcd.clear();
  lcd_sen_val();
 //---------------------------------------------------------------------------------------------------------------------
                                                                              //*77*    (7770  0777 7777  0770)
 if(l>I&&r>I)
 {
  if(er<I&&el<I)                            //0770
   {   
//    lcd.clear(0,1); 
    lcd.setCursor(0,1);    lcd.print("   ^^FORWARD^^ ");//-----------forward
    forward();  delay(50);
    ruk();      delay(5);   
    }
//===============================  
  if(el<I&&er>I)        //0777                      //right
    {
     lcd.setCursor(0,1);    lcd.print("==>> DETECT");
  while(brs<I)
       {/*brs=analogRead(BRS);        lcd.setCursor(14,0);        lcd.print(brs/100);
        er=analogRead(EXTR);        lcd.setCursor(7,0);        lcd.print(er/100);
        */
        lcd_sen_val();
        ruk();       delay(2);
        forward();   delay(20);
       }
       if(el<I&&l<I&&r<I&&er<I)
       {  
    while(er<I)
      {lcd_sen_val();   
       lcd.setCursor(0,1);    lcd.print("*RIGHT TURN*");
       right();      //delay(40);
      }
       while(l<I)
      {lcd_sen_val();   
       lcd.setCursor(0,1);    lcd.print("RIGHT TURN al ");
       right();      //delay(40);
      }
    }
    /*else
    {forward();
    }     */ }       
//================================
  if(el>I&&er<I)//  7770    //left
    {
     lcd.setCursor(0,1);    lcd.print("<<== DETECT");
     while(brs<550&&bls<I)
     {bls=analogRead(BLS);
      lcd.setCursor(12,0);
      lcd.print(bls/100);
      el=analogRead(EXTL);
      lcd.setCursor(1,0);
      lcd.print(el/100);
      ruk();       delay(5);
      forward();   delay(30);
     }
     lcd_sen_val();    
     while(el<I)
      {lcd_sen_val();    
       lcd.setCursor(0,1);    lcd.print("*LEFT TURN*");
       left();      //delay(40);
      }
      while(r<I)
       {lcd_sen_val();    
        lcd.setCursor(0,1);    lcd.print("LEFT TURN al");
        left();      //delay(40);
       }
    // }
 }      
//=================================
if(er>I&&el>I)        //7777
    {
      lcd.setCursor(0,1);    lcd.print("T || + DETECTED");
     while(brs<550&&bls<550)
     {bls=analogRead(BLS);      lcd.setCursor(12,0);      lcd.print(bls/100);
      brs=analogRead(BRS);      lcd.setCursor(14,0);      lcd.print(brs/100);
      forward();  delay(8);
      ruk();       delay(2);
     }
       if(brs>I&&bls>I)
        { if(er>I&&el>I&&l>I&&r>I)        //7777
          {lcd_sen_val();   
           lcd.setCursor(0,1);    lcd.print("victory   !!!");
           ruk();    delay(5000);}
        }
      lcd.clear();
      while(el<I)
      {lcd_sen_val();    
       lcd.setCursor(0,1);    lcd.print("LEFT TURN");
       left();      //delay(30);
      }  
      while(r<I)
      { lcd_sen_val();    
       lcd.setCursor(0,1);    lcd.print("LEFT TURN");
       left();      //delay(30);
      }   
 }
} 
//---------------------------------------------------------------------------------------------------------------------------
                                                                                             //*07*      ALLIGN TO RIGHT
if(l<I&&r>I)
 {//if(er>I)                                                                                //*077      ALLIGN TO RIGHT
  {
  lcd.setCursor(0,1);       lcd.print("<<=ALLIGN TO RIGHT  ");
  //ruk();                delay(5);                                       
  right();              delay(10);
  forward();            delay(10);                                                                                         //0070
  }
}
//-------------------------------------------------------------------------------------------------------------------------
                                                                                            //*70*      ALLIGN TO LEFT
if(l>I&&r<I)
 {//if(el<I)                                                                                //770*      ALLIGN TO LEFT
 {
  lcd.setCursor(0,1);       lcd.print("<<=ALLIGN TO LEFT  ");
  //ruk();      delay(5);                                       
  left();  delay(10);
  forward();  delay(10); 
 } 
 
 }
//-------------------------------------------------------------------------------------------------------------------------
                                                                                               //*00*        DEAD END 
if(l<I&&r<I)
 {  lcd_sen_val();
    if(el<550&&er<550)
      {
        //if(bls<550||brs<550)
        {while(el<I)
      {lcd_sen_val();    
       lcd.setCursor(0,1);    lcd.print("DEAD END");
       left();      //delay(30);
      }  
      while(r<I)
      { lcd_sen_val();    
       lcd.setCursor(0,1);    lcd.print("DEAD END al");
       left();      //delay(30);
      }  
        }
      }
  //======================================================
    if(el>I)
    {
     while(r<I)
     { lcd_sen_val();    
       lcd.setCursor(0,1);    lcd.print("ALLIGN LEFT");
       left();     //delay(5);
     } 
    }
    //=======================================================
    if(er>I)
    {
     while(r<I)
     { lcd_sen_val();    
       lcd.setCursor(0,1);    lcd.print("ALLIGN RIGHT");
       right();     //delay(5);
     } 
    }
 }      
}

  
//---------------------------------------------------------------------------------------------------------------------------------------------------        

//=========================================XXXXXXXXXXXXXXXXXXXXXXXXXXXXX====================================================XXXXXXXXXXXXXXXXXXXXXXXXXXXXX==============================
