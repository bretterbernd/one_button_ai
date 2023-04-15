
const int connection_max = 64;

struct aC{

    int id = -1;
    int sid=-1;
    int oid=-1;
    float weight = 1.0;

};



struct aCON{
 
        int sid = -1;
        int oid = -1;
        float weight = 1.0;
 
};

// maximal 512 connections available!
 
int connection_buffer_count = 0;
 
aC allCS[connection_max];


void resetAndInitConnections(){


    for (int i = 0; i < connection_max; i++) {
        allCS[i].id = i;
        allCS[i].weight = 1.0;
    //allCS[i].value = i * 3.14;
    }

    connection_buffer_count = 0;
}
 


/*
void addNewConnection(int _sid, int _oid){
 
    allCONNECTIONS[connection_buffer_count].sid = _sid;
    allCONNECTIONS[connection_buffer_count].oid = _oid;
    connection_buffer_count++;
    
}
*/


// degenerate the network as a natural "forget" process!
void degrow_network(){

     for(int i=0;i<connection_buffer_count;i++){

        allCS[i].weight *=.98;

     }

}

 

int returnConnectionID_byNODE_IDS(int _sid, int _oid){

    int rid = -1;
            // go thu all connections
           for(int i=0;i<connection_buffer_count;i++){

                
 

           }

 
    return rid;


}

void updating_network(){

         //  degrow_network(); // degenerate the nn

          
    
          //int parsed_c_id = returnConnectionID_byNODE_IDS(int(prev_closestNodeID),int(curr_closestNodeID));

            // Serial.println ("----------------" );
          //  Serial.print ("parsed_suitable_connection: " );
          // Serial.println (parsed_c_id );

           
           // addNewConnection(int(prev_closestNodeID),int(curr_closestNodeID));
            return;
         
         
         
         
        //  if(parsed_c_id == -1){
            // create a new connection
            //addNewConnection(prev_on_interval_id,curr_on_interval_id );
        //  }else{
            Serial.println ("ADD NEW WEIGHT   ++++++++++++++ : ");
            //allCONNECTIONS[parsed_c_id]->weight += 1;
       //   }

}

