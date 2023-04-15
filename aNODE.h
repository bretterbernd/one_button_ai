const int node_size = 12;

struct aNODE{
 
    int id = -1;
     int time_val = 1;
     //-------------------
    int con_ids[node_size]; // possible connections!
    int con_buff_count = 0;

 

    int returnRandomConnectedNodeWeighted(){

        float weightsum = 0;

        // add all weights together to a sum
        for(int i=0;i<con_buff_count;i++){


            
            weightsum += allCS[con_ids[i]].weight*100;

        }
    
       

        
        float rand_weight = random(weightsum);


          Serial.println("------------------------------");
        Serial.print(" weightsum: ");
        Serial.println(weightsum);  
         Serial.print(" randsum: ");
        Serial.println(rand_weight);   



        // Loop through the array, subtracting each element's weight from the random number
        // until the random number is less than or equal to zero
        for (int i = 0; i < con_buff_count; i++) {
            rand_weight -= allCS[con_ids[i]].weight*100;
            if (rand_weight <= 0) {
            return allCS[con_ids[i]].oid;// return the object of the connection!
            }
        }

            // If we haven't returned yet, there was an error
        return -1;


    }
  
};

aNODE allNODES[node_size]; 

void resetAndInitNodes(){

    for( int i=0; i< node_size-1; i++ ){

        allNODES[i].id = i;
        allNODES[i].time_val = timesteps[i];//int(i*15 + 50);
        allNODES[i].con_buff_count = 0;
 
    }


}


/*
aNODE returnNodeByID( int _id){



}
*/