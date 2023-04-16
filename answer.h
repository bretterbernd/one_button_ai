
bool is_playing_answer = false;

int node_answer_buffer[12];
int answer_buffer_size = 0;
int curr_playhead = 0;

int tick = 0;
int next_playhead_time_edge = 1;

//int led_base_bri = 1;

void createAnswerPlaylistBuffer(int _root_node_id){


      // set the first node to trigger!
      node_answer_buffer[0] =  _root_node_id;    
      answer_buffer_size = 1;

/*
      //node > return all connections > respective other nodes!
      int next_node = allNODES[ _root_node_id ].returnRandomConnectedNodeWeighted();
      node_answer_buffer[answer_buffer_size] = next_node;
      answer_buffer_size++;
*/
    int _prev_node_id = _root_node_id;

    // create 6er answer! chain
    for(int i=1;i<10;i++){

      // get node id of most prominent connected node!
      int _next_node_id = allNODES[ _prev_node_id ].returnRandomConnectedNodeWeighted();

      if(_next_node_id != -1){ // no more playlist add when no connection found!
        node_answer_buffer[answer_buffer_size] = _next_node_id;
        answer_buffer_size++;
        _prev_node_id = _next_node_id;
      }
    }

    /*
     Serial.println(" ----------ANSWER ------------------ ");
     Serial.print(" init node id: ");  
     Serial.println( node_answer_buffer[0] );
     Serial.print(" answer_len: ");  
     Serial.println( answer_buffer_size );
     */
    
     
}



void init_direct_answer(){

    // pick the most prominent node
    int start_node_id = return_ID_of_MostConnected_Node();
    // todo: pick one of the three most prominent ones!!!


    // reset the playhead for playmode
      curr_playhead = 0;

    // create a new Playlist!
      createAnswerPlaylistBuffer( start_node_id );

      clearPixelBrights();
    is_playing_answer = true;
}

int p_answer_id = -1;

void play_answer(){

    
    // ---------- UPDATE RING ----------------
      for (int i=0;i<12;i++){


          pixels.setPixelColor(i, pixels.Color(
            pixel_brights[i],
            pixel_brights[i],
            pixel_brights[i])); // set pixel color
          pixel_brights[i]*=.91; // dim all colors down by time

 
            // change note event
          //if(  p_answer_id != node_answer_buffer[curr_playhead]  ){

            //  Serial.println(">>>>>>>>>>>>>>>>> pulse new NOTE");
            if(tick == 0){
              pixel_brights[node_answer_buffer[curr_playhead]] = 82;
             }
              //p_answer_id = node_answer_buffer[curr_playhead];
              
          //}

          

          
           
      }
      
     

        pixels.show();   // Send the updated pixel colors to the hardware.
        delay(DELAYVAL); // Pause before next pass through loop
        
        


        if(curr_playhead >= answer_buffer_size){
            is_playing_answer = false;
            clearPixelBrights();
            delay(1000);
            init_idle_visuals();
        }else{
 
           // todo > tick phase applied to lenth of note  
            if(tick>next_playhead_time_edge){
                curr_playhead++;
               
               /*
                Serial.print("play item: ");
                Serial.print(curr_playhead);
                Serial.print(" :: with node_id: ");

                Serial.println(node_answer_buffer[curr_playhead]);
                */
                tick =0;

                next_playhead_time_edge = allNODES[ node_answer_buffer[curr_playhead] ].time_val/10 + 6;

                // play tone along timeval of note!
                tone( BUZZER_PIN, next_playhead_time_edge*50+2000,10);
            }else{
                tick++;
            }
        }

    }
