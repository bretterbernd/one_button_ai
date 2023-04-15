#include <Arduino.h>

 //#include <SoftwareSerial.h>
 //SoftwareSerial mySerial(2, 3); // RX, TX

#include <Adafruit_NeoPixel.h>
#include <btn.h>


//int timesteps[] = { 100,150,200,300,400,500,650,750,900, 1100, 1300, 1500 };

int timesteps[] = { 50,100,150,200,250,300,400,500,600, 700, 800, 900 };


#define LED_RING_PIN  9 //LED RING PIN
#define NUMPIXELS 12
#define DELAYVAL 10 // Time (in milliseconds) to pause between pixels

//Adafruit_NeoPixel pixels(NUMPIXELS, LED_RING_PIN, NEO_GRB + NEO_KHZ400);

#define PIXEL_COUNT 12
#define PIXEL_TYPE WS2812

Adafruit_NeoPixel pixels = Adafruit_NeoPixel(PIXEL_COUNT, LED_RING_PIN, NEO_GRB+ NEO_KHZ400);

 
aBTN btn1(4,false); 

#define BUZZER_PIN  5 // buzzer_pin

// -------------------------------

bool btn_down = false;

long last_on_ts = 0;
//long last_off_ts = 0;

int curr_on_ts_dist = 0;
//int curr_off_ts_dist = 0;

int curr_closestNodeID = 0;
//int curr_off_interval_id = 0;

int prev_closestNodeID = 0;
//int prev_off_interval_id = 0;

// -------------------------------

bool is_idle = true;
int sleep_time = 2000;
float brif = 0;


float pixel_brights[12];

int prev_step_id = 0;


#include <aCON.h>
#include <aNODE.h>
#include <func.h> 
#include <idle.h>
#include <answer.h>

// ---------------------------------------

int returnEdgeOfArray(int _e){

  int rid = 0;

  for(int i=0;i<12;i++){

      if(timesteps[i]<_e){ rid = i;} 
  }

  if(_e>2000){ rid = 13;}

  return rid;
}

// ---------------------------------------

void setup() {

   Serial.begin(115200);
  pixels.begin(); // INITIALIZE NeoPixel strip object (REQUIRED)
 // mySerial.begin(9600); // initialize SoftwareSerial port

  //last_off_ts = millis();
   
  resetAndInitNodes();
  resetAndInitConnections();

}

void loop() {

  int bri = 0;

  // -------------------------------------------

  if(is_playing_answer){
    play_answer();
    return;
  }
  

  // ---------------------------------------------


  btn1.operateBUTTON();

  // -----------------------------------------
  // ------------------------------------



      if(btn1.on_holded){

      tone(BUZZER_PIN,4200,60);
      resetVISUALS();
      resetEntireBrain();
      return;
    }


  // --------------------------------------
  
   if(last_on_ts + sleep_time < millis() && !is_idle){
         tone(BUZZER_PIN,2200,150);
         is_idle = true;
     
       // sortArrayByConnectionAmount();
        // send_data_via_serial();
        
        //init_idle_visuals();
        init_direct_answer();
  }

 





  // ---------------------------------------  

    int step_id = 0;
      
    if(btn1.is_pressed){  
      int prev_disti = millis() - last_on_ts;

      step_id =  returnEdgeOfArray(prev_disti);
    }


   if(btn1.on_pressed){
    
      step_id = 0;
     last_on_ts =  millis();
      is_idle = false;
      btn_down = true;

    pixel_brights[0] = 220;

     for (int i=1;i<12;i++){
      pixel_brights[i] = 55;
     }

     tone(BUZZER_PIN,7600,4);

  }

  
    // -------------------------------------------


    if(is_idle){


      idle_mode();
      return;
   }

    // -------------------------------------------

    pixels.setPixelColor(0,pixel_brights[0],pixel_brights[0],pixel_brights[0] );
     pixel_brights[0] *= .98; 

    if(step_id != prev_step_id){

        tone(BUZZER_PIN,42600,1);
      
        prev_step_id = step_id;

    }


     // -------------------------------------------------
  // ------------  RELEASE ROUNTINE    ---------------------------
  // -------------------------------------------------


  if(btn1.on_released){

        btn_down = false;
      //  bri = 0;

         curr_on_ts_dist = millis() - last_on_ts;
         curr_closestNodeID = findClosest(curr_on_ts_dist); 
    
          // TODO : also here: avoid input to nn of too long idled inputs!
          if(prev_closestNodeID != -1 ){
            
         
               train_the_network();

          }
          
        
        
          prev_closestNodeID = curr_closestNodeID;
         //tone(BUZZER_PIN,7900,20);
  }







    // --------------------------------------------------

   for (int i=1;i<12;i++){

    uint8_t cbri = pixel_brights[i];

      

      if( i==step_id){  
          pixels.setPixelColor(i,11,11,11 );}
      else if( i < step_id){
        pixels.setPixelColor(i,cbri,0,0 ); 

      }else{
         pixels.setPixelColor(i,0,0,0); 
      }


        //pixels.setPixelColor(i,cbri,cbri,cbri ); 
      //}

      pixel_brights[i] *= .9972; 

             
  }


                        pixels.show();   // Send the updated pixel colors to the hardware.


  
  

  
//--------------------------------------------------------

  return;


  


  

 
  // -------------------------------------------------
  // ------------  PRESS ROUNTINE    ---------------------------
  // -------------------------------------------------

  if(btn1.on_pressed){
    
      is_idle = false;
      btn_down = true;
      bri = 8;
 
 
      last_on_ts =  millis();
      
     //  Serial.print ("DOWN++++++++++++++ : ");
     // Serial.println(curr_off_interval_id);
      tone(BUZZER_PIN,2600,2);
      
   
  }

   if(is_idle){


      idle_mode();
      return;
   }


  

  
   // -------------------------------------------------
  // ------------  LED UDPATE  ---------------------------
  // -------------------------------------------------


                        for (int i=0;i<12;i++){

                              if( curr_closestNodeID == i && btn_down){
                                 bri=22;
                              }else{
                                 bri=0;
                              }
                              pixels.setPixelColor(i, pixels.Color(bri,bri,bri)); 
                        }


                        pixels.show();   // Send the updated pixel colors to the hardware.


                        delay(DELAYVAL); // Pause before next pass through loop

                        //brif *=.78;

}