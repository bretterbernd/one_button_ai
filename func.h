 
int findClosest(int target ) {
    int closestIndex = 0;  // initialize index of closest element to first element in array
    int diff = abs(target - allNODES[0].time_val);  // initialize diff to absolute difference between target and first element
    
    for (int i = 1; i < node_size; i++) {
        int curr_diff = abs(target - allNODES[i].time_val);  // calculate absolute difference between target and current element
        if (curr_diff < diff) {
            closestIndex = i;  // update index of closest element if current element is closer to target
            diff = curr_diff;  // update diff to current absolute difference
        }
    }
    
    return closestIndex;
}

// ----------------------------------------------------------


void sortArrayByConnectionAmount() {
    bool sorted = false;
    int size = node_size;
    while (!sorted) {
        sorted = true;
        for (int i = 0; i < size - 1; i++) {
            if (allNODES[i].con_buff_count > allNODES[i+1].con_buff_count) {
                // swap the elements
                aNODE temp = allNODES[i];
                allNODES[i] = allNODES[i+1];
                allNODES[i+1] = temp;
                sorted = false;
            }
        }
    }
}

// --------------------------------------------------------


int return_ID_of_MostConnected_Node( ) {

    int highestValue = -1;
    int highestValueId = -1;
    
    for (int i = 0; i < node_size; i++) {
        if (allNODES[i].con_buff_count > highestValue) {
            highestValue = allNODES[i].con_buff_count;
            highestValueId = allNODES[i].id;
        }
    }
    
    return highestValueId;
}

 

//-----------------------------------------------------
 
 int returnConnection_ID_By_SVAL_OVAL(int _sid, int _oid){

    int rid = -1;
 
    for(int i=0;i<connection_buffer_count;i++){
/*

                Serial.println(" ");
                Serial.print("allCONNECTIONS[i]->sid");
                Serial.println(allCONNECTIONS[i]->sid);
                Serial.print("allCONNECTIONS[i]->oid");
                Serial.println( allCONNECTIONS[i]->oid);
                Serial.println(" ");
*/

        if(allCS[i].sid == _sid){


             if(allCS[i].oid == _oid){

                // found a match!
               // Serial.println("found one");
                return i;
            
            }


        }

        
 
    }

    return rid;
}





// --------------------------------------------------------
 


  void  send_data_via_serial(){

       Serial.print("init \n");
      
     for (int i = 0; i < connection_buffer_count; i++) {
 
        Serial.print(i);
        Serial.print(",");
        Serial.print(allCS[i].sid);
        Serial.print(",");
        Serial.print(allCS[i].oid);
        Serial.print(",");
        Serial.print(int(allCS[i].weight*100));
        Serial.print("\n");
        
        delay(20);
        

     }

      Serial.print("end \n");

  }


// --------------------------------------------------------

  void train_the_network(){
 
      degrow_network();

     int curr_con_id = returnConnection_ID_By_SVAL_OVAL(prev_closestNodeID,curr_closestNodeID);
 
    if(curr_con_id == -1){

              // do not create more connections than allowed!
              if(connection_buffer_count<connection_max){

                        // create a new connection
                        allCS[connection_buffer_count].sid = prev_closestNodeID;
                        allCS[connection_buffer_count].oid = curr_closestNodeID;
          
                        Serial.println(" ------------------------------------------ ");
                        Serial.print(" create new connection:  ");
                        Serial.println( allCS[connection_buffer_count].sid );
                        Serial.println( allCS[connection_buffer_count].oid );
                      //  Serial.println(" ------------------------------------------ ");

  
                      // link the connection to the subject NODE!
                        if(allNODES[prev_closestNodeID].con_buff_count< node_size){
                          allNODES[prev_closestNodeID].con_ids[ allNODES[prev_closestNodeID].con_buff_count ] = allCS[connection_buffer_count].id;
                          allNODES[prev_closestNodeID].con_buff_count++;
                        }

                      // count up!
                      connection_buffer_count++;
 
                }

      }else{
           Serial.println(" added weight up >>>>>>>>>>>>>>>>>>>>>>>>>>> :  ");
          allCS[curr_con_id].weight += 1.0;
      }

  }

  // ---------------------------------------

  void resetEntireBrain(){


       resetAndInitNodes();
       resetAndInitConnections();
       prev_closestNodeID = 0;

  }