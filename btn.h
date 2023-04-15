// -------------------------------
// TXY'S button helper class
// --------------------------------
// serves you wonderful functionality right on the plate :)
  
    // is_pressed = momentary state of button
    // is_holded = momentary state if button is down for at least 1s
      
    // on_pressed = triggered once if button is down
    // on_pressed = triggered once if button is up
    // on_holded = triggered once if button is down for at least 1s
  
  
class aBTN {
  private:
    int bpin;
    long ts = 0;
    bool previous_state = false;
    bool prev_is_holded = false;
    bool flipped_phase = false;
  
  public:
    bool is_pressed = false;
    bool is_holded = false;
  
    bool on_pressed = false;
    bool on_released = false;
    bool on_holded = false;
  
    aBTN(int bpin, bool _flipped_phase) {
      this->bpin = bpin;
      this->flipped_phase = _flipped_phase;
      init();
    }
    void init() {
      pinMode(bpin, INPUT);
  
    }
  
  
    void operateBUTTON() {
  
      this->is_pressed = digitalRead(bpin);
  
        // flip phase if button phase is flipped
       if(this->flipped_phase){this->is_pressed = !this->is_pressed;}
  
        // reset press states
      this->on_pressed = false;
      this->on_released = false;
  
      // if there is any change of state :)
      if (this->previous_state != this->is_pressed) {
  
  
            if (this->is_pressed) {
              
            //button is pressed down -------
            this->ts = millis(); // set timestamp
            this->on_pressed = true;
  
            } else {
            //button is released -------
            this->on_released = true;
            this->is_holded = false;
            this->on_holded = false;
            this->prev_is_holded = false;
            }
  
            // buffer prev state to avoid repeat
            this->previous_state = this->is_pressed;
  
      }
  
        // reset on hold state first
        this->on_holded = false;
  
        // if button is holded for more than 1s and is still pressed!
      if (this->ts + 1500 < millis() && this->is_pressed ) {
  
        this->is_holded = true; // set is holded state each frame here
  
        if (this->prev_is_holded != this->is_holded && this->is_pressed ) {
  
          this->on_holded = true;
          this->prev_is_holded = this->is_holded;
            
        }
      }
    }
};