
float answer_energy = 1.0;


void clearPixelBrights(){

  for (int i=0;i<12;i++){
    pixel_brights[i]= 0;

     pixels.setPixelColor(i, pixels.Color(pixel_brights[i],pixel_brights[i],pixel_brights[i]));
  }
  pixels.show();
}


void setPixelBrightsTo(int _v){

  for (int i=0;i<12;i++){
    pixel_brights[i]= _v;

     pixels.setPixelColor(i, pixels.Color(pixel_brights[i],0,0));
  }
  pixels.show();
}
 
// ---------------------------------------

void trigger_a_NODE(int _nid, int _strength){

  // the picked node needs to have connections
   if( allNODES[_nid].con_buff_count > 0 ){

        float shrinking_strength =   answer_energy * _strength;

        if(shrinking_strength>.1){
          pixel_brights[allNODES[_nid].id] = shrinking_strength;
        }
        
       // int next_node_id = allNODES[_nid].triggerAndReturnConnectedNodeID();
   }
 
}

void triggerConnectedNodes(int _bid){

    // go thru all connections of node!
    for( int i=0; i< allNODES[_bid].con_buff_count;i++){

        // get connection
        aC cc =  allCS [ allNODES[_bid].con_ids[i] ];

        trigger_a_NODE(allNODES[cc.oid].id, cc.weight*90 );
        //pixel_brights[allNODES[_nid].id] = 22;

    }
}



// ---------------------------------------
// ---------------------------------------
// ---------------------------------------


void init_idle_visuals(){

 // tone( BUZZER_PIN,8888,70);
   // pick a starting Node
  int startnideid = return_ID_of_MostConnected_Node();
  answer_energy = 1.0;

  //clearPixelBrights();
  delay(1000);
  setPixelBrightsTo(20);
  tone( BUZZER_PIN,888,70);  
  trigger_a_NODE(startnideid,180);

}

// ---------------------------------------
// ---------------------------------------
// ---------------------------------------

void idle_mode(){
    
 // int rpid = int(random(12));
 // pixel_brights[rpid] = 6;

   for (int i=0;i<12;i++){
      pixels.setPixelColor(i, pixels.Color(0,0,pixel_brights[i]));
      pixel_brights[i] *=.8;

      // if brightness comes to critital threshold > trigger again!
      if( pixel_brights[i] < .1 && pixel_brights[i] > .01 ){

        pixel_brights[i] = 0;
        triggerConnectedNodes(i);
        //trigger_a_NODE(i);
      }
   }

    answer_energy *=.997;
    pixels.show();   // Send the updated pixel colors to the hardware.
    delay(DELAYVAL); // Pause before next pass through loop
 
}

// ---------------------------------------


void resetVISUALS(){

   for (int i=0;i<12;i++){
         pixels.setPixelColor(i, pixels.Color(122,2,22)); 
    }

   pixels.show();
   delay(1000);

}